#ifndef avoid_h
#define avoid_h
#include <rover.h>
#include <VL53L0X.h>

//TODO: Interrupt-based range checking?
// algorithm is setup, loop and callback function set
// setup() configures iterrupts and callback is required
// This looks a lot like a main.ino file...
// So maybe no abstraction is required, just work with the arduino structure.

class Avoid{
  public: 
    const static uint16_t min_range_mm = 300;
    const static uint16_t go_range_mm = 500;

  private:
    VL53L0X &lidar;
    Rover &rover;

    enum State {running, obstructed};
    State state;

  public: 
    Avoid(Rover &rover_, VL53L0X &lidar_)
      :lidar(lidar_), rover(rover_){;}
    void enter_running(unsigned int speed);
    void enter_obstructed(unsigned int speed);
    void setup(unsigned int speed);
    void loop(unsigned int speed);
};

#endif
