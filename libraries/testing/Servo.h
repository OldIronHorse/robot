#ifndef Servo_h
#define Servo_h
#include <list>

class Servo {
  public:
    Servo();
    ~Servo();
    
    void attach(int pin, int min=544, int max=2400);
    void write(int angle);
    void writeMicroseconds(int mu_sec);

    int readMicroseconds();

    int m_pin;
    int m_min;
    int m_max;

    int m_angle;
    int m_mu_sec;

    std::list<int> musec_calls;
};
#endif
