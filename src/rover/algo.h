#include "rover.h"

void turn_right_to_avoid(long min_range_cm){
  if(rover::range() < min_range_cm){
    rover::right(rover::max_speed/2);
  }else{
    rover::forward(rover::max_speed);
  }
}

