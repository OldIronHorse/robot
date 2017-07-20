#include <Servo.h>

class Mearm{
  public:
    Mearm();

    void attach(int pin_pan, int pin_shoulder, int pin_elbow, int pin_gripper);

    void init();
    
    void gripper(bool is_open);
    void elbow(int angle);
    void shoulder(int angle);
    void pan(int angle);

    void move_to(int pan, int shoulder, int elbow, bool gripper_open);
    bool is_moving();
    void move();

    enum Joint{PAN, SHOULDER, ELBOW, GRIPPER};

    Servo _servos[4];

    int _start[4];
    int _end[4];
    double _step_size[4];
    int _step;
    int _step_count;
};
