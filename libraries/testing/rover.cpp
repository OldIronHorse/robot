#include <rover.h>
#include <sstream>

void Rover::reset(){
  calls.clear();
}

void Rover::setup(){
  reset();
}

void Rover::stop(){
  calls.push_back("stop()");
}

void Rover::turn_right_10(){
  calls.push_back("turn_right_10()");
}

void Rover::turn_left_10(){
  calls.push_back("turn_left_10()");
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
