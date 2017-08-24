#include "VehicleLight.h"
#include <Arduino.h>

VehicleLight::VehicleLight(int pin_red,int pin_amber,int pin_green)
:_pin_red(pin_red),_pin_amber(pin_amber),_pin_green(pin_green){;}

void VehicleLight::init(){
  pinMode(_pin_red,OUTPUT);
  pinMode(_pin_amber,OUTPUT);
  pinMode(_pin_green,OUTPUT);
  set_stop();
  _next = STOP;
}

void VehicleLight::set_stop(){
  digitalWrite(_pin_red,HIGH);
  digitalWrite(_pin_amber,LOW);
  digitalWrite(_pin_green,LOW);
  _current = STOP;
}

void VehicleLight::set_wait(){
  digitalWrite(_pin_red,HIGH);
  digitalWrite(_pin_amber,HIGH);
  digitalWrite(_pin_green,LOW);
  _current = WAIT;
}

void VehicleLight::set_go(){
  digitalWrite(_pin_red,LOW);
  digitalWrite(_pin_amber,LOW);
  digitalWrite(_pin_green,HIGH);
  _current = GO;
}

void VehicleLight::set_caution(){
  digitalWrite(_pin_red,LOW);
  digitalWrite(_pin_amber,HIGH);
  digitalWrite(_pin_green,LOW);
  _current = CAUTION;
}

void VehicleLight::tic(){
  if(_next != _current){
    switch(_next){
      case STOP:
        set_stop();
        break;
      case WAIT:
        set_wait();
        _next = GO;
        break;
      case GO:
        set_go();
        break;
      case CAUTION:
        set_caution();
        _next = STOP;
        break;
    } 
  }
}

void VehicleLight::stop(){
  _next = CAUTION;
}

void VehicleLight::go(){
  _next = WAIT;
}
