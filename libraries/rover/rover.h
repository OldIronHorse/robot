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

IRrecv ir_recv(9);

void setup(){
  pinMode(PIN_SPEED_1, OUTPUT);
  pinMode(PIN_SPEED_2, OUTPUT);
  pinMode(PIN_DIRECTION_1, OUTPUT);
  pinMode(PIN_DIRECTION_2, OUTPUT);

  analogWrite(PIN_SPEED_1, 0);
  analogWrite(PIN_SPEED_2, 0);
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, LOW);

  ir_recv.enableIRIn();
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
  digitalWrite(PIN_DIRECTION_2, HIGH);
  digitalWrite(PIN_DIRECTION_1, LOW);
  analogWrite(PIN_SPEED_2, speed);
  analogWrite(PIN_SPEED_1, speed);
}

void back_curve(unsigned int left_speed, unsigned int right_speed){
  digitalWrite(PIN_DIRECTION_1, HIGH);
  digitalWrite(PIN_DIRECTION_2, HIGH);
  analogWrite(PIN_SPEED_2, left_speed);
  analogWrite(PIN_SPEED_1, right_speed);
}
void forward_curve(unsigned int left_speed, unsigned int right_speed){
  digitalWrite(PIN_DIRECTION_1, LOW);
  digitalWrite(PIN_DIRECTION_2, LOW);
  analogWrite(PIN_SPEED_2, left_speed);
  analogWrite(PIN_SPEED_1, right_speed);
}

void right(unsigned int speed){
  digitalWrite(PIN_DIRECTION_2, LOW);
  digitalWrite(PIN_DIRECTION_1, HIGH);
  analogWrite(PIN_SPEED_1, speed);
  analogWrite(PIN_SPEED_2, speed);
}

}

#endif
