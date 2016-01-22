#include <Arduino.h>
#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include "avoid.h"

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required

void Avoid::enter_running(){
  state = running;
  rover.forward(rover.max_speed);
}

void Avoid::enter_obstructed(){
  state = obstructed;
  if(random(0, 2) > 0){
    rover.back_curve(0, rover.max_speed);
  }else{
    rover.back_curve(rover.max_speed,0);
  }
  delay(1000);
}

void Avoid::setup(){
  randomSeed(analogRead(0));
  rover.setup();
  enter_running();
}

void Avoid::loop(){
  int range = ranger.Ranging(CM);
  DEBUG_PRINTLN(range)
  switch(state){
    case running:
      if(range < min_range_cm){
        enter_obstructed();
      }
      break;
    case obstructed:
      if(range > go_range_cm){
        enter_running();
      }
      break;
  }
}

