#include <Arduino.h>
#include "SerialRover.h"

SerialRover::SerialRover():_c('A'),_light(LOW)
{;}

void SerialRover::init(){
  Serial.begin(9600);
  Serial.println("Started...");
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
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

void SerialRover::read_loop(){
  if(Serial.available() > 0){
    int c = Serial.read();
    switch(c){
      case 'H':
        digitalWrite(7,HIGH);
        break;
      case 'L':
        digitalWrite(7,LOW);
        break;
    }
  }
}
