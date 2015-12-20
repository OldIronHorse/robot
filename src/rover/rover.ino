#include <Ultrasonic.h>
#include "rover.h"

Ultrasonic ranger(12, 13);

void setup(){
  rover::setup();
}

void loop(){
  while(ranger.Ranging(CM) < 20){
    rover::right(128);
    delay(100);
  }
  rover::forward(rover::max_speed);
}
