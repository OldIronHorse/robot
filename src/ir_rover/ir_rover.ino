#include <rover.h>
#include "ir_cmd.h"

void setup(){
  rover::setup();
  //Serial.begin(9600);
}

decode_results results;

void loop(){
  if(rover::ir_recv.decode(&results)){
    unsigned long cmd = ir_cmd::cmd_from_value(results.value);
    //Serial.println(cmd, HEX);
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
        rover::left(rover::quarter_speed*3);
        break;
      case ir_cmd::skip_forward:
        rover::forward_curve(rover::max_speed,rover::max_speed);
        break;
      case ir_cmd::skip_back:
        rover::forward_curve(3*rover::quarter_speed,rover::max_speed);
        break;
      case ir_cmd::ffwd:
        rover::back_curve(rover::max_speed,3*rover::quarter_speed);
        break;
      case ir_cmd::rwd:
        rover::back_curve(3*rover::quarter_speed,rover::max_speed);
        break;
      case ir_cmd::ok:
        rover::stop();
        break;
      //TODO: pre-programmed moves for digits 0-9
      // Make sure rover still responds to input

      //TODO: volume keys for speed control?
    }
    //TODO
    // use & 0xFF mask to get value
    // use right shift to check for repeat/repress
    rover::ir_recv.resume();
  }
  //Serial.println(rover::range());
  /*
  if(rover::range() < 20){
    rover::back(rover::max_speed);
    delay(300);
    rover::stop();
  }
  */
}
