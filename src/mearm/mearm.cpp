#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Arduino.h>
#include "mearm.h"

const int Mearm::_max[] = {180,180,180,175};
const int Mearm::_min[] = {  0, 85, 80,120};

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
    _servos[i].write(100);
  }
}

void Mearm::gripper(int angle){
  _servos[GRIPPER].write(apply_limits(GRIPPER,angle));
}

void Mearm::elbow(int angle){
  _servos[ELBOW].write(apply_limits(ELBOW,angle));
}

void Mearm::shoulder(int angle){
  _servos[SHOULDER].write(apply_limits(SHOULDER,angle));
}

void Mearm::pan(int angle){
  _servos[PAN].write(apply_limits(PAN,angle));
}

int Mearm::apply_limits(int joint, int angle){
  DEBUG_PRINT(joint)
  DEBUG_PRINT(":")
  DEBUG_PRINT(_min[joint])
  DEBUG_PRINT(",")
  DEBUG_PRINT(angle)
  DEBUG_PRINT(",")
  DEBUG_PRINTLN(_max[joint]);
  return min(_max[joint],max(_min[joint],angle));
}

void Mearm::move_to(int pan, int shoulder, int elbow, int gripper){
  _end[GRIPPER] = gripper;
  _end[PAN] = pan;
  _end[SHOULDER] = shoulder;
  _end[ELBOW] = elbow;

  int delta[4];
  _step_count = 0;
  for(int i = 0; i < 4; ++i){
    _end[i] = apply_limits(i,_end[i]);
    _start[i] = _servos[i].read();
    delta[i] = _end[i] - _start[i];
    _step_count = max(_step_count, abs(delta[i]));
    DEBUG_PRINT(i)
    DEBUG_PRINT(":")
    DEBUG_PRINT(_start[i])
    DEBUG_PRINT("->")
    DEBUG_PRINT(_end[i])
    DEBUG_PRINT(" ")
    DEBUG_PRINT(delta[i])
    DEBUG_PRINTLN()
  }

  DEBUG_PRINT("_step_count = ")
  DEBUG_PRINTLN(_step_count)
  for(int i = 0; i < 4; ++i){
    _step_size[i] = double(delta[i]) / _step_count;
    DEBUG_PRINT(_step_size[i])
    DEBUG_PRINT(",")
  }
  DEBUG_PRINTLN()
  _step = 1;
}

bool Mearm::is_moving(){
  return _step > 0;
}

void Mearm::move(){
  //DEBUG_PRINT("_step = ")
  //DEBUG_PRINTLN(_step)
  if(_step > 0){
    for(int i = 0; i < 4; ++i){
      _servos[i].write(_start[i] + (_step * _step_size[i]));
      DEBUG_PRINT(_start[i] + (_step * _step_size[i]))
      DEBUG_PRINT(",")
    }
    DEBUG_PRINTLN()
    ++_step;
    if(_step > _step_count){
      _step = 0;
    }
  }
}
