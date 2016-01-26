#ifndef ROVER_H
#define ROVER_H

#include <vector>
#include <string>

using namespace std;

class Rover{
  public:
    const static unsigned int max_speed = 255;

    vector<string> calls;

    void reset();
    void setup();
    void stop();
    void forward(unsigned int speed);
    void back_curve(unsigned int left_speed, unsigned int right_speed);
    void turn_right_10();
    void turn_left_10();
};

#endif
