#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Ultrasonic.h>
#include <toneAC.h>

#include "pitches.h"

Ultrasonic ranger(12, 13);

void setup(){
  DEBUG_INIT(9600)
}

void loop(){
  int range = ranger.Ranging(CM);
  DEBUG_PRINT(F("range: "))
  DEBUG_PRINTLN(range)
  toneAC(map(range, 10, 100, NOTE_B0, NOTE_DS8));
  delay(1);
}
