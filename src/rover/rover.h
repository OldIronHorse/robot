#ifndef rover_h
#define rover_h

#include <Ultrasonic.h>
#include <IRremote.h>

#define PIN_SPEED_2 5
#define PIN_SPEED_1 6
#define PIN_DIRECTION_2 7
#define PIN_DIRECTION_1 8

namespace rover{

const unsigned int max_speed = 255;

Ultrasonic ranger(12, 13);

long range(){
  return ranger.Ranging(CM);
}

IRrecv remote(11);

const int cmd_stop = 0;
const int cmd_go = 1;

int cmd_state = cmd_stop;

int command_state(){
  decode_results result;
  if(remote.decode(&result)){
    //TODO: map result.value to stop/go
    remote.resume();
  }
  return cmd_state;
}

void setup(){
  pinMode(PIN_SPEED_1, OUTPUT);
  pinMode(PIN_SPEED_2, OUTPUT);
  pinMode(PIN_DIRECTION_1, OUTPUT);
  pinMode(PIN_DIRECTION_2, OUTPUT);

  analogWrite(PIN_SPEED_1, 0);
  analogWrite(PIN_SPEED_2, 0);
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, LOW);

  remote.enableIRIn();
}

void forward(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, LOW);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

void back(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, HIGH);
  digitalWrite(PIN_DIRECTION_2, HIGH);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

void stop(){
  analogWrite(PIN_SPEED_1, 0);
  analogWrite(PIN_SPEED_2, 0);
}

void left(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, HIGH);
  digitalWrite(PIN_DIRECTION_2, LOW);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

void right(unsigned int speed){
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, HIGH);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

}

#endif
