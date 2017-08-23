#include "VehicleLight.h"
#include <Arduino.h>

VehicleLight::VehicleLight(int pin_red,int pin_amber,int pin_green)
:_pin_red(pin_red),_pin_amber(pin_amber),_pin_green(pin_green){;}

void VehicleLight::init(){
  pinMode(_pin_red,OUTPUT);
  pinMode(_pin_amber,OUTPUT);
  pinMode(_pin_green,OUTPUT);
  stop();
}

void VehicleLight::stop(){
  digitalWrite(_pin_red,HIGH);
  digitalWrite(_pin_amber,LOW);
  digitalWrite(_pin_green,LOW);
}

void VehicleLight::go(){
  digitalWrite(_pin_red,LOW);
  digitalWrite(_pin_amber,LOW);
  digitalWrite(_pin_green,HIGH);
}
