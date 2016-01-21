#include <rover.h>
#include <sstream>

void Rover::reset(){
  mock_range = 0;
  calls.empty();
}

long Rover::range(){
  return mock_range;
}

void Rover::setup(){
  reset();
}

void Rover::forward(unsigned int speed){
  stringstream s;
  s << "forward(" << speed << ")";
  calls.push_back(s.str());
}

void Rover::back_curve(unsigned int left_speed, unsigned int right_speed){
  stringstream s;
  s << "back_curve(" << left_speed << ", " << right_speed << ")";
  calls.push_back(s.str());
}
