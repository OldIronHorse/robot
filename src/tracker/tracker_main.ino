#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Servo.h>
#include <VL53L0X.h>

/* track the closes object
 *
 * 1. scan field to find closest object (within a minimum distance)
 * 2. narrow scan object as it moves
 * 3. revert to full scan if lock is lost
 */

#define SCAN_STEP 2
#define TRACK_STEP 1

VL53L0X lidar;
Servo scanner;

enum Mode {SCAN, TRACK};
Mode mode = SCAN;
uint16_t target_range = 0;
int target_angle = 0;

void setup(){
  DEBUG_INIT(9600)
  lidar.init();
}

void loop(){
  uint16_t range = lidar.readRangeSingleMillimeters();
  switch(mode){
    case SCAN:
      for(int angle = 0; angle <= 180; angle += SCAN_STEP){
        scanner.write(angle);
        if(0 == target_range){
          target_range = range;
          target_angle = angle;
        }else{
          target_range = min(range, target_range);
          if(target_range == range){
            target_angle = angle;
          }
        }
      }
      mode = TRACK;
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
      if(down_range > target_range){
        target_angle = up_angle;
      }else if(up_range > target_range){
        target_angle = down_angle;
      }
      break;
  }
}
