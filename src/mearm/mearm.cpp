#include <Arduino.h>
#include "mearm.h"

Mearm::Mearm()
:_step(0),_step_count(0){;}

void Mearm::attach(int pin_pan, int pin_shoulder, int pin_elbow, int pin_gripper){
  _servos[GRIPPER].attach(pin_gripper);
  _servos[ELBOW].attach(pin_elbow);
  _servos[SHOULDER].attach(pin_shoulder);
  _servos[PAN].attach(pin_pan);
}

void Mearm::init(){
  for(int i = 0; i < 4; ++i){
    _servos[i].write(90);
  }
}

void Mearm::gripper(bool is_open){
  if(is_open){
    _servos[GRIPPER].write(90);
  }else{
    _servos[GRIPPER].write(0);
  }
}

void Mearm::elbow(int angle){
  _servos[ELBOW].write(angle);
}

void Mearm::shoulder(int angle){
  _servos[SHOULDER].write(angle);
}

void Mearm::pan(int angle){
  _servos[PAN].write(angle);
}

void Mearm::move_to(int pan, int shoulder, int elbow, bool gripper_open){
  if(gripper_open){
    _end[GRIPPER] = 90;
  }else{
    _end[GRIPPER] = 0;
  }
  _end[PAN] = pan;
  _end[SHOULDER] = shoulder;
  _end[ELBOW] = elbow;

  int delta[4];
  _step_count = 0;
  for(int i = 0; i < 4; ++i){
    _start[i] = _servos[PAN].read();
    delta[i] = _end[i] - _start[i];
    _step_count = max(_step_count, abs(delta[i]));
  }
  for(int i = 0; i < 4; ++i){
    _step_size[i] = double(delta[i]) / _step_count;
  }
  _step = 1;
}

bool Mearm::is_moving(){
 return _step > 0;
}

void Mearm::move(){
  if(_step > 0){
    for(int i = 0; i < 4; ++i){
      _servos[i].write(_start[i] + (_step * _step_size[i]));
    }
    ++_step;
    if(_step > _step_count){
      _step = 0;
    }
  }
}
