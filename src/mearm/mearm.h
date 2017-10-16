#ifndef mearm_h
#define mearm_h
#include <Servo.h>

class Mearm{
  public:
    Mearm();

    void attach(int pin_pan, int pin_shoulder, int pin_elbow, int pin_gripper);

    void init();
    
    void gripper(int angle);
    void elbow(int angle);
    void shoulder(int angle);
    void pan(int angle);

    void move_to(int pan, int shoulder, int elbow, int gripper);
    bool is_moving();
    void move();

    int apply_limits(int joint, int angle);

    enum Joint{PAN=0, SHOULDER=1, ELBOW=2, GRIPPER=3};

    Servo _servos[4];

    int _start[4];
    int _end[4];
    double _step_size[4];
    int _step;
    int _step_count;

    static const int _max[];
    static const int _min[];
};
#endif
