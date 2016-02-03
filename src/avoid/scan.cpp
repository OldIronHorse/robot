#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include "scan.h"

void Scan::setup(unsigned int speed){
}

void Scan::loop(unsigned int speed){
  if(_running){
    int range = _ranger.Ranging(CM);
    if(range < 50){
      _rover.stop();
      _running = false;
    }
  }else{
    // scan
    DEBUG_PRINTLN("Scanning...")
    int max_range = 0;
    int max_range_angle = 0;
    for(int angle = 0; angle <= 180; angle += 10){
      _scanner.write(angle);
      delay(100);
      int range = _ranger.Ranging(CM);
      DEBUG_PRINT(angle)
      DEBUG_PRINT(":")
      DEBUG_PRINTLN(range)
      if(range > max_range && range < 1000){
        max_range = range;
        max_range_angle = angle;
      }
    }
    _scanner.write(90);
    DEBUG_PRINT("max_range: ")
    DEBUG_PRINTLN(max_range)
    DEBUG_PRINT("max_range_angle: ")
    DEBUG_PRINTLN(max_range_angle)
    // turn
    if(max_range_angle > 90){
      // turn right
      DEBUG_PRINT("Turning right ")
      int turn_count = (max_range_angle - 90)/10;
      DEBUG_PRINT(turn_count)
      DEBUG_PRINTLN(" steps")
      for(int i = 0; i < turn_count; ++i){
        _rover.back_curve(0, Rover::max_speed);
        delay(200);
      }
    }else if(max_range_angle < 90){
      // turn left
      DEBUG_PRINT("Turning left ")
      int turn_count = (90 - max_range_angle)/10;
      DEBUG_PRINT(turn_count)
      DEBUG_PRINTLN(" steps")
      for(int i = 0; i < turn_count; ++i){
        _rover.back_curve(Rover::max_speed, 0);
        delay(200);
      }
    }
    // move
    _running = true;
    _rover.forward(speed);
  }
}


void Scan::start(unsigned int speed){
  _running = true;
  _scanner.write(90);
  _rover.forward(speed);
  loop(speed);
}
