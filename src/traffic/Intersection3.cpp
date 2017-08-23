#include "Intersection3.h"
#include "VehicleLight.h"
#include "PedestrianLight.h"

Intersection3::Intersection3(VehicleLight& ns_vehicle,
                             VehicleLight& ew_vehicle,
                             PedestrianLight& peds)
:_ns_vehicle(ns_vehicle),_ew_vehicle(ew_vehicle),_peds(peds),_state(ALL_STOP){;}

void Intersection3::init(){
  _state=ALL_STOP;
  _ns_vehicle.init();
  _ew_vehicle.init();
  _peds.init();
}
void Intersection3::next(){
}

Intersection3::State Intersection3::state(){
  return _state;
}
