#ifndef avoid_h
#define avoid_h
#include <Ultrasonic.h>
#include <rover.h>

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required
// This looks a lot like a main.ino file...
// So maybe no abstraction is required, just work with the arduino structure.

class Avoid{
  public: 
    const static long min_range_cm = 30;
    const static long go_range_cm = 50;

    Ultrasonic ranger;
    Rover &rover;

  private:
    enum State {running, obstructed};
    State state;

  public: 
    Avoid(Rover &rover_):ranger(12, 13), rover(rover_){;}
    void enter_running(unsigned int speed);
    void enter_obstructed(unsigned int speed);
    void setup(unsigned int speed);
    void loop(unsigned int speed);
};

#endif
