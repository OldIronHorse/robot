#include "scan.h"

#define TURN_STEP_MS 100
#define MAX_TURN_STEPS 36

void Scan::setup(unsigned int speed){
}

void Scan::loop(unsigned int speed){
  switch(_state){
    case FORWARD:{
        uint16_t range = _lidar.readRangeSingleMillimeters();
        if(range < 250){
          _rover.stop();
          _state = SCAN;
          _turn_index = 0;
          _max_range = range;
          _max_range_turn_index = 0;
          _last_ranging_ms = millis();
          _rover.right(Rover::max_speed);
        }
      }
      break;
    case SCAN:
      if(millis() - _last_ranging_ms > TURN_STEP_MS){
        _rover.stop();
        ++_turn_index;
        uint16_t range = _lidar.readRangeSingleMillimeters();
        if(range > _max_range){
          _max_range = range;
          _max_range_turn_index = _turn_index;
        }
        if(_turn_index < MAX_TURN_STEPS){
          _rover.right(Rover::max_speed);
        }else{
          _rover.left(Rover::max_speed);
          _state = TURN;
        }
      }
      break;
    case TURN:
        uint16_t range = _lidar.readRangeSingleMillimeters();
        if(max(range,_max_range) - min(range,_max_range) < 5){
          _rover.forward(speed);
          _state = FORWARD;
        }
        break;
  }
}


void Scan::start(unsigned int speed){
  _state = FORWARD;
  _rover.forward(speed);
  loop(speed);
}
