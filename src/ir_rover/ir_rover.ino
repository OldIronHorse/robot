#include <rover.h>
#include "ir_cmd.h"

void setup(){
  rover::setup();
  //Serial.begin(9600);
}

decode_results results;

unsigned long speed = rover::max_speed;
unsigned long last_cmd = 0;

void square(){
  for(int i = 0; i < 4; ++i){
    rover::forward(rover::max_speed);
    delay(700);
    rover::right(rover::max_speed);
    delay(900);
  }
  rover::stop();
}

void loop(){
  if(rover::ir_recv.decode(&results)){
    unsigned long cmd = ir_cmd::cmd_from_value(results.value);
    //Serial.println(cmd, HEX);
    switch(cmd){
      case ir_cmd::vol_up:
        speed = min(speed + 5, rover::max_speed);
        break;
      case ir_cmd::vol_down:
        speed = max(5, speed - 5);
        break;
      default:
        last_cmd = cmd;
        break;
    }
    switch(last_cmd){
      case ir_cmd::up:
        rover::forward(speed);
        break;
      case ir_cmd::down:
        rover::back(speed);
        break;
      case ir_cmd::right:
        rover::right(speed);
        break;
      case ir_cmd::left:
        rover::left(speed);
        break;
      case ir_cmd::skip_forward:
        rover::forward_curve(speed,0.75*speed);
        break;
      case ir_cmd::skip_back:
        rover::forward_curve(0.75*speed,speed);
        break;
      case ir_cmd::ffwd:
        rover::forward_curve(speed,0);
        break;
      case ir_cmd::rwd:
        rover::forward_curve(0,speed);
        break;
      case ir_cmd::ok:
        rover::stop();
        break;
      case ir_cmd::d1:
        square();
        break;
      //TODO: pre-programmed moves for digits 0-9
      // Make sure rover still responds to input
    }
    //TODO
    // use & 0xFF mask to get value
    // use right shift to check for repeat/repress
    rover::ir_recv.resume();
  }
  //Serial.println(rover::range());
  /*
  if(rover::range() < 20){
    rover::back(speed);
    delay(300);
    rover::stop();
  }
  */
}
