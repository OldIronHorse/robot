#ifndef ROVER_H
#define ROVER_H

#include <vector>
#include <string>

using namespace std;

class Rover{
  public:
    const static unsigned int max_speed = 255;

    long mock_range;
    vector<string> calls;

    void reset();
    long range();
    void setup();
    void forward(unsigned int speed);
    void back_curve(unsigned int left_speed, unsigned int right_speed);
};

#endif
