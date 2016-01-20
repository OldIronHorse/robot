#define DEBUG
#include <DebugUtils.h>
#include <rover.h>
#include "algo.h"

void setup(){
  DEBUG_INIT(9600)
  rover::setup();
}

void loop(){
  //forward();
  turn_right_to_avoid(30, 100);
  /*switch(rover::command_state()){
    case rover::cmd_go:
      turn_right_to_avoid(20);
    default:
      rover::stop();
  }*/
}
