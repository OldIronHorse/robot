#include "rover.h"

void forward(){
  rover::forward(rover::max_speed);
  delay(2000);
  rover::right(rover::max_speed);
  delay(500);
}

void turn_right_to_avoid(long min_range_cm, long go_range_cm){
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

