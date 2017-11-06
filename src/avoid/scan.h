#ifndef scan_h
#define scan_h

#include <Arduino.h>
#include <rover.h>
#include <VL53L0X.h>

class Scan{
  public:
    Rover &_rover;
    VL53L0X &_lidar;
    enum State {FORWARD,SCAN,TURN};
    State _state;
    int _turn_index;
    int _max_range_turn_index;
    uint16_t _max_range;
    unsigned long _last_ranging_ms;

  public:
    Scan(Rover &rover_, VL53L0X &lidar_)
      :_rover(rover_), _lidar(lidar_),
       _state(FORWARD){;}

    void setup(unsigned int speed);
    void loop(unsigned int speed);
    void start(unsigned int speed);
};

#endif
