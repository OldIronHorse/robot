#ifndef scan_h
#define scan_h

#include <Arduino.h>
#include <rover.h>
#include <VL53L0X.h>

class Scan{
  protected:
    Rover &_rover;
    VL53L0X &_lidar;
    bool _running;
    int _angle;
    int _step;

  public:
    Scan(Rover &rover_, VL53L0X &lidar_)
      :_rover(rover_), _lidar(lidar_),
       _running(true), _angle(0), _step(5){;}

    void setup(unsigned int speed);
    void loop(unsigned int speed);
    void start(unsigned int speed);
};

#endif
