#include "rover.h"

void setup(){
  rover::setup();
}

void loop(){
  rover::forward(rover::max_speed);
}
