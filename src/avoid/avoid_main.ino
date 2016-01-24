#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <IRremote.h>
#include <rover.h>
#include "avoid.h"
#include <ir_cmd.h>

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
unsigned int last_cmd = ir_cmd::none;

void setup(){
  DEBUG_INIT(9600)
  avoid.setup(speed);
  ir_recv.enableIRIn();
  mode = REMOTE;
  rover.stop();
}

void loop(){
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
      case ir_cmd::vol_up:
        speed = min(speed + 5, Rover::max_speed);
        if(AUTO == mode){
          avoid.enter_running(speed);
        }else{
          cmd = last_cmd;
        }
        break;
      case ir_cmd::vol_down:
        speed = max(5, speed - 5);
        if(AUTO == mode){
          avoid.enter_running(speed);
        }else{
          cmd = last_cmd;
        }
        break;
    }
  }
  switch(mode){
    case AUTO:
      avoid.loop(speed);
      break;
    case REMOTE:
      switch(cmd){
        case ir_cmd::up:
          rover.forward(speed);
          last_cmd = cmd;
          break;
        case ir_cmd::down:
          rover.back(speed);
          last_cmd = cmd;
          break;
        case ir_cmd::right:
          rover.right(speed);
          last_cmd = cmd;
          break;
        case ir_cmd::left:
          rover.left(speed);
          last_cmd = cmd;
          break;
        case ir_cmd::skip_forward:
          rover.forward_curve(speed,0.75*speed);
          last_cmd = cmd;
          break;
        case ir_cmd::skip_back:
          rover.forward_curve(0.75*speed,speed);
          last_cmd = cmd;
          break;
        case ir_cmd::ffwd:
          rover.forward_curve(speed,0);
          last_cmd = cmd;
          break;
        case ir_cmd::rwd:
          rover.forward_curve(0,speed);
          last_cmd = cmd;
          break;
        case ir_cmd::ok:
          rover.stop();
          last_cmd = cmd;
          break;
      }
      break;
  }
  delay(100);
}


