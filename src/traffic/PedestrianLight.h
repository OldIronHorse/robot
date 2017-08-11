#ifndef PedestrianLight_h
#define PedestrianLight_h

class PedestrianLight{
  public:
    PedestrianLight(int pin_red,int pin_green);
    void init();
    void stop();
    void go();

  private:
    int _pin_red;
    int _pin_green;
};

#endif
