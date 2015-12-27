#include "rover.h"
#include "algo.h"

void setup(){
  rover::setup();
}

void loop(){
  forward();
  //turn_right_to_avoid(20);
  /*switch(rover::command_state()){
    case rover::cmd_go:
      turn_right_to_avoid(20);
    default:
      rover::stop();
  }*/
}
