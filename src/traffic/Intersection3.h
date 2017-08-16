#ifndef Intersection3_h
#define Intersection3_h

class VehicleLight;
class PedestrianLight;

class Intersection3{
  public:
    Intersection3(VehicleLight& ns_vehicle,
                  VehicleLight& ew_vehicle,
                  PedestrianLight& peds);

    void init();

  private:
    VehicleLight& _ns_vehicle;
    VehicleLight& _ew_vehicle;
    PedestrianLight& _peds;
};

#endif
