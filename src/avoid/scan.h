#ifndef scan_h
#define scan_h

#include <Arduino.h>
#include <rover.h>
#include <Servo.h>
#include <Ultrasonic.h>

class Scan{
  private:
    Rover &_rover;
    Servo &_scanner;
    Ultrasonic &_ranger;
    bool _running;

  public:
    Scan(Rover &rover_, Ultrasonic &ranger_, Servo &scanner_)
      :_rover(rover_), _scanner(scanner_), _ranger(ranger_), 
       _running(true){;}

    void setup(unsigned int speed);
    void loop(unsigned int speed);
};

#endif
