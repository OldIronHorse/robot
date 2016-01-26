#include "scan.h"

void Scan::setup(unsigned int speed){
}

void Scan::loop(unsigned int speed){
  if(_running){
    _rover.forward(speed);
    _scanner.write(90);
    int range = _ranger.Ranging(CM);
    if(range < 30){
      _rover.stop();
      _running = false;
    }
  }else{
    // scan
    int max_range = 0;
    int max_range_angle = 0;
    for(int angle = 0; angle <= 180; angle += 10){
      _scanner.write(angle);
      delay(100);
      int range = _ranger.Ranging(CM);
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
        _rover.turn_right_10();
      }
    }else if(max_range_angle < 90){
      // turn left
      int turn_count = (90 - max_range_angle)/10;
      for(int i = 0; i < turn_count; ++i){
        _rover.turn_left_10();
      }
    }
    // move
    _running = true;
    _rover.forward(speed);
  }
}
