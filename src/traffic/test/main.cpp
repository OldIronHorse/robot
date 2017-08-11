#include <testing.h>
#include <Arduino.h>
#include "../VehicleLight.h"

VehicleLight light(3,4,5);

void vehicle_set_up(){
  MockArduino::instance().reset();
  light.init();
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
  light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_wait)
  light.wait();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_go)
  light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(HIGH,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_caution)
  light.caution();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
}

DEFINE_TEST(vehicle_sequence)
  light.stop();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
  light.wait();
  assertEqual(HIGH,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
  light.go();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(LOW,MockArduino::instance().pin_out[4]);
  assertEqual(HIGH,MockArduino::instance().pin_out[5]);
  light.caution();
  assertEqual(LOW,MockArduino::instance().pin_out[3]);
  assertEqual(HIGH,MockArduino::instance().pin_out[4]);
  assertEqual(LOW,MockArduino::instance().pin_out[5]);
  light.stop();
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

int main(void){
  return run(vehicle_light_tests,vehicle_set_up);
}
