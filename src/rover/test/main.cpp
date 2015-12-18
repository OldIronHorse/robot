#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include "Arduino.h"

#include "../rover.h"

void set_up() {
  MockArduino::instance().reset();
}

void test_setup(){
  rover::setup();
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[5]);
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[6]);
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[7]);
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[8]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
  assertEqual(0, MockArduino::instance().pin_out[5]);
  assertEqual(0, MockArduino::instance().pin_out[6]);
}

void test_forward(){
  rover::forward(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

TestFunc tests[] = {&test_setup,
                    &test_forward,
                    0};

int main(void) {
  return run(tests, set_up);
}


