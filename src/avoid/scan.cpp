#include "scan.h"

void Scan::setup(unsigned int speed){
}

void Scan::loop(unsigned int speed){
  if(_running){
    uint16_t range = _lidar.readRangeSingleMillimeters();
    if(range < 250){
      _rover.stop();
      _running = false;
    }
  }else{
    // scan
    uint16_t max_range = 0;
    uint16_t max_range_angle = 0;
    for(uint16_t angle = 0; angle <= 180; angle += 10){
      //TODO: turn rover
      delay(100);
      uint16_t range = _lidar.readRangeSingleMillimeters();
      if(range > max_range){
        max_range = range;
        max_range_angle = angle;
      }
    }
    // turn
    if(max_range_angle > 90){
      // turn right
      int turn_count = (max_range_angle - 90)/10;
      for(int i = 0; i < turn_count; ++i){
        _rover.back_curve(0, Rover::max_speed);
        delay(200);
      }
    }else if(max_range_angle < 90){
      // turn left
      int turn_count = (90 - max_range_angle)/10;
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
  _rover.forward(speed);
  loop(speed);
}
