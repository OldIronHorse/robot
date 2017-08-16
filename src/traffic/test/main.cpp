#include <testing.h>
#include <Arduino.h>
#include "../VehicleLight.h"
#include "../PedestrianLight.h"
#include "../Intersection3.h"

VehicleLight v_light(3,4,5);

void vehicle_set_up(){
  MockArduino::instance().reset();
  v_light.init();
}

DEFINE_TEST(vehicle_initial_state)
  assertEqual(OUTPUT,MockArduino::instance().pin_mode[3]);
  assertEqual(OUTPUT,MockArduino::instance().pin_mode[4]);
  assertEqual(OUTPUT,MockArduino::instance().pin_mode[5]);
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_stop)
  v_light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_wait)
  v_light.wait();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_go)
  v_light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(HIGH,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_caution)
  v_light.caution();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_sequence)
  v_light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
  v_light.wait();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
  v_light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(HIGH,MockArduino::instance().pin_out[5]);
  v_light.caution();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
  v_light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

BEGIN_TEST_SUITE(vehicle_light_tests)
ADD_TEST(vehicle_initial_state)
ADD_TEST(vehicle_stop)
ADD_TEST(vehicle_wait)
ADD_TEST(vehicle_go)
ADD_TEST(vehicle_caution)
ADD_TEST(vehicle_sequence)
END_TEST_SUITE

PedestrianLight p_light(3,4);

void pedestrian_set_up(){
  MockArduino::instance().reset();
  p_light.init();
}

DEFINE_TEST(pedestrian_initial_state)
  assertEqual(OUTPUT,MockArduino::instance().pin_mode[3]);
  assertEqual(OUTPUT,MockArduino::instance().pin_mode[4]);
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
}

DEFINE_TEST(pedestrian_stop)
  p_light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
}

DEFINE_TEST(pedestrian_go)
  p_light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
}

DEFINE_TEST(pedestrian_sequence)
  p_light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  p_light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  p_light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  p_light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
}

BEGIN_TEST_SUITE(pedestrian_light_tests)
ADD_TEST(pedestrian_initial_state)
ADD_TEST(pedestrian_stop)
ADD_TEST(pedestrian_go)
ADD_TEST(pedestrian_sequence)
END_TEST_SUITE

// Test suite for simple 2-way plus pedestrian intersection (3-phase)

PedestrianLight all_peds(3,4);
VehicleLight ns_vehicle(5,6,7);
VehicleLight ew_vehicle(8,9,10);

Intersection3 inter3(ns_vehicle,ew_vehicle,all_peds);

void intersection_3_set_up(void){
  MockArduino::instance().reset();
  inter3.init();
}

DEFINE_TEST(intersection_3_initial)
  // pedestrian red
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  // North-South red
  assertEqual(HIGH,MockArduino::instance().pin_out[5]);
  assertEqual(LOW,MockArduino::instance().pin_out[6]);
  assertEqual(LOW,MockArduino::instance().pin_out[7]);
  // East-West red
  assertEqual(HIGH,MockArduino::instance().pin_out[8]);
  assertEqual(LOW,MockArduino::instance().pin_out[9]);
  assertEqual(LOW,MockArduino::instance().pin_out[10]);
}

BEGIN_TEST_SUITE(intersection_3_tests)
ADD_TEST(intersection_3_initial)
END_TEST_SUITE


int main(void){
  return run(vehicle_light_tests,vehicle_set_up) +
         run(pedestrian_light_tests,pedestrian_set_up) +
         run(intersection_3_tests,intersection_3_set_up);
}
