#ifndef VehicleLight_h
#define VehicleLight_h

class VehicleLight{
  public:
    VehicleLight(int pin_red,int pin_amber,int pin_green);
    void init();

    void stop();
    void wait();
    void go();
    void caution();

  private:
    int _pin_red;
    int _pin_amber;
    int _pin_green;
};

#endif
