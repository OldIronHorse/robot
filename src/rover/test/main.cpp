#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include "Arduino.h"
#include "../../../libraries/rover/rover.h"

Rover* pRover;

void set_up() {
  cout << "set_up" << endl;
  MockArduino::instance().reset();
  pRover = new Rover();
}

void tear_down() {
  cout << "tear_down" << endl;
  delete pRover;
}

void test_setup(){
  cout << "test_setup" << endl;
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

void test_forward(){
  cout << "test_forward" << endl;
  pRover->forward(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(LOW, MockArduino::instance().pin_out[8]);
}

void test_back(){
  cout << "test_back" << endl;
  pRover->back(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  assertEqual(HIGH, MockArduino::instance().pin_out[8]);
}

void test_stop(){
  cout << "test_stop" << endl;
  pRover->stop();
  assertEqual(0, MockArduino::instance().pin_out[5]);
  assertEqual(0, MockArduino::instance().pin_out[6]);
}

void test_right(){
  cout << "test_right" << endl;
  pRover->right(200);
  assertEqual(200, MockArduino::instance().pin_out[5]);
  assertEqual(200, MockArduino::instance().pin_out[6]);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
  assertEqual(HIGH, MockArduino::instance().pin_out[8]);
}

void test_left(){
  cout << "test_left" << endl;
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


