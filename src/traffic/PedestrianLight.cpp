#include "PedestrianLight.h"
#include <Arduino.h>

PedestrianLight::PedestrianLight(int pin_red,int pin_green)
:_pin_red(pin_red),_pin_green(pin_green){;}

void PedestrianLight::init(){
  pinMode(_pin_red,OUTPUT);
  pinMode(_pin_green,OUTPUT);
  stop();
} 

void PedestrianLight::stop(){
  digitalWrite(_pin_red,HIGH);
  digitalWrite(_pin_green,LOW);
}

void PedestrianLight::go(){
  digitalWrite(_pin_red,LOW);
  digitalWrite(_pin_green,HIGH);
}
