#include <Servo.h>

class Mearm{
  public:
    void attach(int pin_pan, int pin_shoulder, int pin_elbow, int pin_gripper);

    void init();
    
    void gripper_open();
    void gripper_close();

    Servo _gripper;
    Servo _elbow;
    Servo _shoulder;
    Servo _pan;
};
