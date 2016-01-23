#include <Arduino.h>
#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include "avoid.h"

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required

void Avoid::enter_running(unsigned int speed){
  state = running;
  rover.forward(speed);
}

void Avoid::enter_obstructed(unsigned int speed){
  state = obstructed;
  if(random(0, 2) > 0){
    rover.back_curve(0, speed);
  }else{
    rover.back_curve(speed, 0);
  }
  delay(1000);
}

void Avoid::setup(unsigned int speed){
  randomSeed(analogRead(0));
  rover.setup();
  enter_running(speed);
}

void Avoid::loop(unsigned int speed){
  int range = ranger.Ranging(CM);
  DEBUG_PRINTLN(range)
  switch(state){
    case running:
      if(range < min_range_cm){
        enter_obstructed(speed);
      }
      break;
    case obstructed:
      if(range > go_range_cm){
        enter_running(speed);
      }
      break;
  }
}
