#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Servo.h>
#include <VL53L0X.h>

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

#define SCAN_STEP 2
#define TRACK_STEP 5

VL53L0X lidar;
Servo scanner;

enum Mode {SCAN, TRACK};
Mode mode = SCAN;
int scan_angle = 0;
uint16_t target_range = UINT16_MAX;
int target_angle = 0;

void setup(){
  DEBUG_INIT(9600)
  lidar.init();
}

void loop(){
  uint16_t range = lidar.readRangeSingleMillimeters();
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
      if(scan_angle > 180){
        mode = TRACK;
      }
      break;
    case TRACK:
      int down_angle = target_angle - TRACK_STEP;
      int up_angle = target_angle + TRACK_STEP;
      scanner.write(target_angle);
      target_range = lidar.readRangeSingleMillimeters();
      scanner.write(down_angle);
      uint16_t down_range = lidar.readRangeSingleMillimeters();
      scanner.write(up_angle);
      uint16_t up_range = lidar.readRangeSingleMillimeters();
      DEBUG_PRINT(down_angle)
      DEBUG_PRINT('|')
      DEBUG_PRINT(down_range)
      DEBUG_PRINT('>')
      DEBUG_PRINT(F("TRACK: "))
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
}
