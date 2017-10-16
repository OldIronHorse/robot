#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include "mearm.h"

Mearm arm;
int last_millis = 0;
bool from = true;

void setup(){
  DEBUG_INIT(9600);
  arm.attach(3,5,6,9);
  arm.init();
  pinMode(13,OUTPUT);
}
/*
void loop(){
  int current_millis = millis();
  if(arm.is_moving()){
    if((current_millis - last_millis) > 10){
      last_millis = current_millis;
      arm.move();
    }
  }else if(from){
    DEBUG_PRINTLN("from...")
    arm.move_to(80,90,100,45);
    digitalWrite(13,HIGH);
    from = false;
  }else{
    DEBUG_PRINTLN("to...")
    arm.move_to(120,135,135,135);
    digitalWrite(13,LOW);
    from = true;
  }
}
*/

int angle = 0;
int delta = 10;

void loop(){
  arm.pan(angle);
  DEBUG_PRINT(angle)
  DEBUG_PRINT(":")
  DEBUG_PRINTLN(arm._servos[Mearm::PAN].read())
  angle += delta;
  delay(1000);
  if(angle>=180 || angle<=0){
    delta *= -1;
  }
}
