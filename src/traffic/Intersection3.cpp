#include "Intersection3.h"
#include "VehicleLight.h"
#include "PedestrianLight.h"

Intersection3::Intersection3(VehicleLight& ns_vehicle,
                             VehicleLight& ew_vehicle,
                             PedestrianLight& peds)
:_ns_vehicle(ns_vehicle),_ew_vehicle(ew_vehicle),_peds(peds){;}

void Intersection3::init(){
  _ns_vehicle.init();
  _ew_vehicle.init();
  _peds.init();
}
