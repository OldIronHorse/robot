#include "scan.h"

#define TURN_STEP_MS 100
#define MAX_TURN_STEPS 36

void Scan::setup(unsigned int speed){
}

void Scan::loop(unsigned int speed){
  if(_running){
    uint16_t range = _lidar.readRangeSingleMillimeters();
    if(range < 250){
      _rover.stop();
      _running = false;
      _turn_index = 0;
      _max_range = range;
      _max_range_turn_index = 0;
      _last_ranging_ms = millis();
      _rover.right(Rover::max_speed);
    }
  }else{
    // scan
    if(millis() - _last_ranging_ms > TURN_STEP_MS){
      _rover.stop();
      ++_turn_index;
      uint16_t range = _lidar.readRangeSingleMillimeters();
      if(range > _max_range){
        _max_range = range;
        _max_range_turn_index = _turn_index;
      }
      _rover.right(Rover::max_speed);
      if(_turn_index >= MAX_TURN_STEPS){
        delay(_max_range_turn_index * TURN_STEP_MS);
        _rover.forward(speed);
        _running = true;
      }
    }
  }
}


void Scan::start(unsigned int speed){
  _running = true;
  _rover.forward(speed);
  loop(speed);
}
