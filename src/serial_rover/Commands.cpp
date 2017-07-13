#include "Commands.h"
#include <Arduino.h>

void Commands::init(int speed){
  Serial.begin(speed);
}

bool Commands::read(){
  if(Serial.available() > 0){
    return true;
  }else{
    return false;
  }
}
