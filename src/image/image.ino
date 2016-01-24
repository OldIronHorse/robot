#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <rover.h>
#include <IRremote.h>
#include <ir_cmd.h>
#include <Ultrasonic.h>

IRrecv ir_recv(9);
decode_results ir_results;
Rover rover;
Ultrasonic ranger(12, 13);

void right_10_degrees(){
  rover.right(Rover::max_speed);
  delay(100);
  rover.stop();
}

void setup(){
  DEBUG_INIT(9600)
  rover.stop();  
  ir_recv.enableIRIn();
  DEBUG_PRINTLN("setup() complete")
}

void loop(){
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
#ifdef DEBUG_OUTPUT
      DEBUG_PRINTLN("Ranges:")
      for(int i = 0; i < 36; ++i){
        DEBUG_PRINT(ranges[i])
        DEBUG_PRINT(" ")
      }
      DEBUG_PRINTLN("")
#endif
    }
  }
  ir_recv.resume();
  delay(100);
}
