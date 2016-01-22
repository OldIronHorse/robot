#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Ultrasonic.h>
#include <IRremote.h>
#include <rover.h>
#include "avoid.h"
#include "ir_cmd.h"

//TODO: Switchable modes (via IR remote)
// - remote controlled via IR
// - autonomous
//  - various modes and strategies?
//    - control parameters via IR remote?

Rover rover;
Avoid avoid(rover);
IRrecv ir_recv(9);
decode_results results;
enum Mode {REMOTE, AUTO};
Mode mode;
unsigned int speed = Rover::max_speed;

void setup(){
  DEBUG_INIT(9600)
  avoid.setup();
  ir_recv.enableIRIn();
  mode = REMOTE;
  rover.stop();
}

void loop(){
  //TODO: mode changed?
  unsigned int cmd = ir_cmd::none;
  if(ir_recv.decode(&results)){
    cmd = ir_cmd::cmd_from_value(results.value);
    ir_recv.resume();
    switch(cmd){
      case ir_cmd::d1:
        mode = REMOTE;
        rover.stop();
        break;
      case ir_cmd::d2:
        mode = AUTO;
        rover.forward(speed);
        break;
    }
  }
  switch(mode){
    case AUTO:
      avoid.loop();
      break;
    case REMOTE:
      //TODO: read ir_cmd and action it
      switch(cmd){
        case ir_cmd::up:
          rover.forward(speed);
          break;
        case ir_cmd::down:
          rover.back(speed);
          break;
        case ir_cmd::right:
          rover.right(speed);
          break;
        case ir_cmd::left:
          rover.left(speed);
          break;
        case ir_cmd::skip_forward:
          rover.forward_curve(speed,0.75*speed);
          break;
        case ir_cmd::skip_back:
          rover.forward_curve(0.75*speed,speed);
          break;
        case ir_cmd::ffwd:
          rover.forward_curve(speed,0);
          break;
        case ir_cmd::rwd:
          rover.forward_curve(0,speed);
          break;
        case ir_cmd::ok:
          rover.stop();
          break;
      }
      break;
  }
  delay(100);
}


