#ifndef ROVER_H
#define ROVER_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Rover{
  public:
    const static unsigned int max_speed = 255;

    vector<string> calls;

    void reset() {
      calls.clear();
    }
    void setup() {
      reset();
    }
    void stop(){
      calls.push_back("stop()");
    }

    void right(unsigned int speed){
      stringstream s;
      s << "right(" << speed << ")";
      calls.push_back(s.str());
    }

    void left(unsigned int speed){
      stringstream s;
      s << "left(" << speed << ")";
      calls.push_back(s.str());
    }

    void turn_right_10(){
      calls.push_back("turn_right_10()");
    }

    void turn_left_10(){
      calls.push_back("turn_left_10()");
    }

    void forward(unsigned int speed){
      stringstream s;
      s << "forward(" << speed << ")";
      calls.push_back(s.str());
    }

    void back_curve(unsigned int left_speed, unsigned int right_speed){
      stringstream s;
      s << "back_curve(" << left_speed << ", " << right_speed << ")";
      calls.push_back(s.str());
    }
};

#endif
