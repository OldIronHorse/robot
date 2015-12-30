#include "rover.h"
#include "algo.h"

void setup(){
  rover::setup();
}

void loop(){
  if(rover::range() < 30){
    while(rover::range() < 100){
      rover::right(rover::max_speed);
    }
    delay(300);
  }else{
    rover::forward(rover::max_speed);
  }
  //forward();
  //turn_right_to_avoid(20);
  /*switch(rover::command_state()){
    case rover::cmd_go:
      turn_right_to_avoid(20);
    default:
      rover::stop();
  }*/
}
