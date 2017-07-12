#include <Arduino.h>
#include "SerialRover.h"

SerialRover::SerialRover():_c('A'),_light(LOW)
{;}

void SerialRover::init(){
  Serial.start(9600);
  Serial.println("Started...\n");
}

void SerialRover::loop(){
  Serial.print(_c);
  ++_c;
  if(_c > 'Z') {
    _c = 'A';
  }
  if(_light == LOW) {
    _light = HIGH;
  } else {
    _light = LOW;
  }
  digitalWrite(13, _light);
  delay(1000);
}
