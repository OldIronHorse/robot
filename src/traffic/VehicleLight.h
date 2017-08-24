#ifndef VehicleLight_h
#define VehicleLight_h

class VehicleLight{
  public:
    VehicleLight(int pin_red,int pin_amber,int pin_green);
    void init();
    void tic();

    void stop();
    void go();

  private:
    void set_stop();
    void set_wait();
    void set_go();
    void set_caution();

    int _pin_red;
    int _pin_amber;
    int _pin_green;

    enum State {STOP,WAIT,GO,CAUTION};
    State _current;
    State _next;
};

#endif
