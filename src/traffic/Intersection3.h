#ifndef Intersection3_h
#define Intersection3_h

class VehicleLight;
class PedestrianLight;

class Intersection3{
  public:
    enum State {ALL_STOP,NS_GO,EW_GO,PED_GO};

    Intersection3(VehicleLight& ns_vehicle,
                  VehicleLight& ew_vehicle,
                  PedestrianLight& peds);

    void init();
    void next();
    State state();

  private:
    State _state;
    VehicleLight& _ns_vehicle;
    VehicleLight& _ew_vehicle;
    PedestrianLight& _peds;
};

#endif
