#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include "Arduino.h"

#include "../rover.h"
#include "../algo.h"

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

void test_back(){
  rover::back(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  assertEqual(HIGH, MockArduino::instance().pin_out[8]);
}

void test_stop(){
  rover::stop();
  assertEqual(0, MockArduino::instance().pin_out[5]);
  assertEqual(0, MockArduino::instance().pin_out[6]);
}

void test_right(){
  rover::right(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

void test_left(){
  rover::left(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(HIGH, MockArduino::instance().pin_out[8]);
}

void test_turn_right_to_avoid_no_obstruction(){
  rover::ranger.distance_cm = 30;
  turn_right_to_avoid(20);
  assertEqual(255, MockArduino::instance().pin_out[5]);
  assertEqual(255, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

void test_turn_right_to_avoid_obstruction(){
  rover::ranger.distance_cm = 10;
  turn_right_to_avoid(20);
  assertEqual(127, MockArduino::instance().pin_out[5]);
  assertEqual(127, MockArduino::instance().pin_out[6]);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

TestFunc tests[] = {&test_setup,
                    &test_forward,
                    &test_back,
                    &test_stop,
                    &test_right,
                    &test_left,
                    &test_turn_right_to_avoid_no_obstruction,
                    &test_turn_right_to_avoid_obstruction,
                    0};

int main(void) {
  return run(tests, set_up);
}


