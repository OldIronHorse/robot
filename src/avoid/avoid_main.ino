#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <UnoWiFiDevEd.h>
#include <IRremote.h>
#include <rover.h>
#include <ir_cmd.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "avoid.h"
#include "scan.h"

//TODO: Control via WiFi and telnet

Rover rover;
VL53L0X lidar;
Avoid avoid(rover, lidar);
Scan scan(rover, lidar);
IRrecv ir_recv(9);
decode_results results;
enum Mode {REMOTE, AVOID, SCAN};
Mode mode;
unsigned int speed = Rover::max_speed;
unsigned int last_cmd = ir_cmd::none;

void setup(){
  DEBUG_INIT(9600)
  Wifi.begin();
  Wire.begin();
  lidar.init();
  lidar.setTimeout(500);
  lidar.setMeasurementTimingBudget(20000); // high speed
  //lidar.setMeasurementTimingBudget(200000); // high accuracy
  rover.setup();
  avoid.setup(speed);
  scan.setup(speed);
  ir_recv.enableIRIn();
  mode = REMOTE;
  rover.stop();
  Wifi.println("Rover started.");
  Wifi.println("mode = REMOTE");
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
        Wifi.println("mode = REMOTE");
        break;
      case ir_cmd::d2:
        mode = AVOID;
        rover.forward(speed);
        Wifi.println("mode = AVOID");
        break;
      case ir_cmd::d3:
        mode = SCAN;
        scan.start(speed);
        Wifi.println("mode = SCAN");
        break;
      case ir_cmd::vol_up:
        speed = min(speed + 5, Rover::max_speed);
        if(AVOID == mode){
          avoid.enter_running(speed);
        }else{
          cmd = last_cmd;
        }
        break;
      case ir_cmd::vol_down:
        speed = max(5, speed - 5);
        if(AVOID == mode){
          avoid.enter_running(speed);
        }else{
          cmd = last_cmd;
        }
        break;
    }
  }
  switch(mode){
    case SCAN:
      scan.loop(speed);
      break;
    case AVOID:
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


