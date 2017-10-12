#ifndef scan_h
#define scan_h

#include <Arduino.h>
#include <rover.h>
#include <Servo.h>
#include <Ultrasonic.h>

class Scan{
  protected:
    Rover &_rover;
    Ultrasonic &_ranger;
    bool _running;
    int _angle;
    int _step;

  public:
    Servo &_scanner;
    Scan(Rover &rover_, Ultrasonic &ranger_, Servo &scanner_)
      :_rover(rover_), _scanner(scanner_), _ranger(ranger_),
       _running(true), _angle(0), _step(5){;}

    void setup(unsigned int speed);
    void loop(unsigned int speed);
    void start(unsigned int speed);
};

#endif
