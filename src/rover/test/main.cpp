#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include "Arduino.h"
#include "../../../libraries/rover/rover.h"

Rover* pRover;

void set_up() {
  MockArduino::instance().reset();
  pRover = new Rover();
}

void tear_down() {
  delete pRover;
}

DEFINE_TEST(test_setup)
  pRover->setup();
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[5]);
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[6]);
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[7]);
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[8]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
  assertEqual(0, MockArduino::instance().pin_out[5]);
  assertEqual(0, MockArduino::instance().pin_out[6]);
}

DEFINE_TEST(test_forward)
  pRover->forward(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

DEFINE_TEST(test_back)
  pRover->back(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  assertEqual(HIGH, MockArduino::instance().pin_out[8]);
}

DEFINE_TEST(test_stop)
  pRover->stop();
  assertEqual(0, MockArduino::instance().pin_out[5]);
  assertEqual(0, MockArduino::instance().pin_out[6]);
}

DEFINE_TEST(test_right)
  pRover->right(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(HIGH, MockArduino::instance().pin_out[8]);
}

DEFINE_TEST(test_left)
  pRover->left(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

TestFunc tests[] = {&test_setup,
                    &test_forward,
                    &test_back,
                    &test_stop,
                    &test_right,
                    &test_left,
                    0};

int main(void) {
  return run(tests, set_up, tear_down);
}


