#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Ultrasonic.h>

UltrasonicRanger ranger(12, 13);

void setup(){
  DEBUG_BEGIN(9600)
}

void loop(){
  int range = ranger.ranging(CM);
  DEBUG_PRINTLN(range)
}
