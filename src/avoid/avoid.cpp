#include <Arduino.h>
#include "avoid.h"

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required
// This looks a lot like a main.ino file...
// So maybe no abstraction is required, just work with the arduino structure.

void Avoid::enter_running(){
  state = running;
  rover.forward(rover.max_speed);
}

void Avoid::enter_obstructed(){
  state = obstructed;
  rover.back_curve(0, rover.max_speed);
}

void Avoid::setup(){
  rover.setup();
  enter_running();
}

void Avoid::loop(){
  int range = rover.range();
  DEBUG_PRINT(range)
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

