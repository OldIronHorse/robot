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
    const static long go_range_cm = 100;

    Rover rover;
    Ultrasonic ranger;

  private:
    enum State {running, obstructed};
    State state;

  public: 
    Avoid():ranger(12, 13){;}
    void enter_running();
    void enter_obstructed();
    void setup();
    void loop();
};

#endif
