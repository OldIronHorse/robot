#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <rover.h>
#include <IRremote.h>
#include <ir_cmd.h>
#include <Ultrasonic.h>
#include <Servo.h>
#include "image.h"

Servo scanner;
IRrecv ir_recv(9);
decode_results ir_results;
Rover rover;
Ultrasonic ranger(12, 13);

void right_10_degrees(){
  rover.right(Rover::max_speed);
  delay(100);
  rover.stop();
}

void left_10_degrees(){
  rover.left(Rover::max_speed);
  delay(100);
  rover.stop();
}

void setup(){
  DEBUG_INIT(9600)
  rover.stop();  
  scanner.attach(10);
  ir_recv.enableIRIn();
  DEBUG_PRINTLN("setup() complete")
}

int scanner_pos = 0;
int scanner_delta = 2;

void scan(int step, int *ranges){
  for(int i = 0; i < 180/step; ++i){
    scanner.write(i * step);
    ranges[i] = ranger.Ranging(CM);
    delay(100);
  }
}

int ranges[90];
const int step = 2;

void loop(){
  scan(step, ranges);
#ifdef DEBUG_OUTPUT
  DEBUG_PRINTLN("Ranges:")
  for(int i = 0; i < 36; ++i){
    DEBUG_PRINT(i*2)
    DEBUG_PRINT(":")
    DEBUG_PRINT(ranges[i])
    DEBUG_PRINT(", ")
  }
  DEBUG_PRINTLN("")
#endif
  int index = max_index(90, ranges);
  int heading = index*step;
  DEBUG_PRINT("Max range: ")
  DEBUG_PRINT(ranges[index])
  DEBUG_PRINT(" at ")
  DEBUG_PRINT(heading)
  if(heading > 90){
    // turn right
    int angle = heading - 90;
    for(int turned = 0; turned < angle; turned += 10){
      right_10_degrees();
    }
  }else if(heading < 90){
    // turn left
    int angle = 90 - heading;
    for(int turned = 0; turned < angle; turned += 10){
      right_10_degrees();
    }
  }
  rover.forward(Rover::max_speed);
  /*
  if(ir_recv.decode(&ir_results)){
    DEBUG_PRINTLN("Got IR Command")
    if(ir_cmd::ok == ir_cmd::cmd_from_value(ir_results.value)){
      DEBUG_PRINTLN("Got IR OK")
      int ranges[36];
      for(int i = 0; i < 36; ++i){
        ranges[i] = ranger.Ranging(CM);
        right_10_degrees();
        delay(100);
      }
    }
  }
  ir_recv.resume();
  */
  delay(1000);
}
