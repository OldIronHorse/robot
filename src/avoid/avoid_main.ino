#include <UnoWiFiDevEd.h>
#include <IRremote.h>
#include <Servo.h>
#include <rover.h>
#include <ir_cmd.h>
#include "avoid.h"
#include "scan.h"
#include "streamscan.h"

//TODO: Control via WiFi and telnet

Servo scanner;
Rover rover;
Ultrasonic ranger(12, 13);
Avoid avoid(rover, ranger);
Scan scan(rover, ranger, scanner);
StreamScan stream_scan(rover, ranger, scanner, Wifi);
IRrecv ir_recv(9);
decode_results results;
enum Mode {REMOTE, AVOID, SCAN, STREAM_SCAN};
Mode mode;
unsigned int speed = Rover::max_speed;
unsigned int last_cmd = ir_cmd::none;

void setup(){
  Wifi.begin();
  scanner.attach(10);
  rover.setup();
  avoid.setup(speed);
  scan.setup(speed);
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
        mode = AVOID;
        scanner.write(90);
        rover.forward(speed);
        break;
      case ir_cmd::d3:
        mode = SCAN;
        scan.start(speed);
        break;
      case ir_cmd::d4:
        mode = STREAM_SCAN;
        stream_scan.start(speed);
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


