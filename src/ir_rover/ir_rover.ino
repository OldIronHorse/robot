#include <rover.h>
#include "ir_cmd.h"

void setup(){
  rover::setup();
  Serial.begin(9600);
}

decode_results results;

void loop(){
  if(rover::ir_recv.decode(&results)){
    unsigned long cmd = ir_cmd::cmd_from_value(results.value);
    Serial.println(cmd, HEX);
    switch(cmd){
      case ir_cmd::up:
        rover::forward(rover::max_speed);
        break;
      case ir_cmd::down:
        rover::back(rover::max_speed);
        break;
      case ir_cmd::right:
        rover::right(rover::max_speed);
        break;
      case ir_cmd::left:
        rover::left(rover::max_speed);
        break;
      case ir_cmd::skip_forward:
        rover::curve(rover::max_speed,rover::max_speed*0.75);
        break;
      case ir_cmd::skip_back:
        rover::curve(rover::max_speed*0.75,rover::max_speed);
        break;
      case ir_cmd::ok:
        rover::stop();
        break;
    }
    //TODO switch on rover::ir_value
    // use & 0xFF mask to get value
    // use right shift to check for repeat/repress
    rover::ir_recv.resume();
    //rover::stop();
  }
}
