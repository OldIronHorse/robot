#include <Arduino.h>
#include "mearm.h"

void Mearm::attach(int pin_pan, int pin_shoulder, int pin_elbow, int pin_gripper){
  _gripper.attach(pin_gripper);
}

void Mearm::init(){
  _gripper.write(90);
  _elbow.write(90);
  _shoulder.write(90);
  _pan.write(90);
}

void Mearm::gripper_open(){
  _gripper.write(90);
}

void Mearm::gripper_close(){
  _gripper.write(0);
}
