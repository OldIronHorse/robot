#define DEBUG
#include <DebugUtils.h>
#include <rover.h>

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required
// This looks a lot like a main.ino file...
// So maybe no abstraction is required, just work with the arduino structure.

void setup(){
  DEBUG_INIT(9600)
  rover::setup();
}

const long min_range_cm = 30;
const long go_range_cm = 100;

void loop(){
  DEBUG_PRINT(rover::range())
  if(rover::range() < min_range_cm){
    while(rover::range() < go_range_cm){
      rover::back_curve(0, rover::max_speed);
      //rover::right(rover::max_speed);
    }
    delay(300);
  }else{
    rover::forward(rover::max_speed);
  }
}

