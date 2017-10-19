#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Servo.h>
//#include <VL53L0X.h>
#include <Ultrasonic.h>

/* track the closes object
 *
 * 1. scan field to find closest object (within a minimum distance)
 * 2. narrow scan object and track it as it moves
 *
 * TODO: 
 * - revert to full scan if lock is lost
 * - steer rover to face target
 * - drive rover towards target
 * - stop at minimum distance
 */

#if ARDUINO_VERSION < 108
#define UINT16_MAX 65536
#define LONG_MAX 2147483647L
#endif

#define SCAN_STEP 2
#define TRACK_STEP 10
#define MIN_ANGLE 45
#define MAX_ANGLE 135

//VL53L0X lidar;
Ultrasonic ranger(12, 13);
Servo scanner;

enum Mode {SCAN, TRACK};
Mode mode = SCAN;
int scan_angle = MIN_ANGLE;
//uint16_t target_range = UINT16_MAX;
long target_range = LONG_MAX;
int target_angle = MIN_ANGLE;

void setup(){
  DEBUG_INIT(9600)
  scanner.attach(10);
  //lidar.init();
}

void loop(){
  //uint16_t range = lidar.readRangeSingleMillimeters();
  long range = ranger.Ranging(CM);
  switch(mode){
    case SCAN:
      scanner.write(scan_angle);
      target_range = min(range, target_range);
      DEBUG_PRINT(F("SCAN: "))
      DEBUG_PRINT(scan_angle)
      DEBUG_PRINT('|')
      DEBUG_PRINT(range)
      DEBUG_PRINT(' ')
      DEBUG_PRINT(target_angle)
      DEBUG_PRINT('|')
      DEBUG_PRINT(target_range)
      DEBUG_PRINTLN()
      if(target_range == range){
        target_angle = scan_angle;
      }
      scan_angle += SCAN_STEP;
      if(scan_angle > MAX_ANGLE){
        mode = TRACK;
        DEBUG_PRINT(F("Target Angle: "))
        DEBUG_PRINTLN(target_angle)
      }
      break;
    case TRACK:
      int down_angle = target_angle - TRACK_STEP;
      int up_angle = target_angle + TRACK_STEP;
      scanner.write(target_angle);
      delay(100);
      //target_range = lidar.readRangeSingleMillimeters();
      target_range = ranger.Ranging(CM);
      scanner.write(down_angle);
      delay(100);
      //uint16_t down_range = lidar.readRangeSingleMillimeters();
      long down_range = ranger.Ranging(CM);
      scanner.write(up_angle);
      delay(100);
      //uint16_t up_range = lidar.readRangeSingleMillimeters();
      long up_range = ranger.Ranging(CM);
      DEBUG_PRINT(F("TRACK: "))
      DEBUG_PRINT(down_angle)
      DEBUG_PRINT('|')
      DEBUG_PRINT(down_range)
      DEBUG_PRINT('>')
      DEBUG_PRINT(target_angle)
      DEBUG_PRINT('|')
      DEBUG_PRINT(target_range)
      DEBUG_PRINT('<')
      DEBUG_PRINT(up_angle)
      DEBUG_PRINT('|')
      DEBUG_PRINT(up_range)
      DEBUG_PRINTLN()
      if(down_range > target_range){
        target_angle = up_angle;
      }else if(up_range > target_range){
        target_angle = down_angle;
      }
      break;
  }
  target_angle = min(MAX_ANGLE, max(MIN_ANGLE, target_angle));
  delay(1);
}
