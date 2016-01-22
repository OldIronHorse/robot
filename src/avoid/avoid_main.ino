#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <avoid.h>
#include <Ultrasonic.h>

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required
// This looks a lot like a main.ino file...
// So maybe no abstraction is required, just work with the arduino structure.

Avoid avoid;

void setup(){
  DEBUG_INIT(9600)
  avoid.setup();
}

void loop(){
  avoid.loop();
  delay(100);
}

