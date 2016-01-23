#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <testing.h>
#include <Arduino.h>
#include <rover.h>
#include "../avoid.h"

Rover rover;
Avoid avoid(rover);

void set_up() {
  MockArduino::instance().reset();
  avoid.setup(10);
}

void test_no_obstruction(){
  avoid.ranger.distance_cm = 35;
  avoid.loop(200);
  assertEqual("forward(10)", avoid.rover.calls.back());
}

void test_obstruction_go_left(){
  MockArduino::instance().random_values.push_back(1);
  avoid.ranger.distance_cm = 10;
  avoid.loop(250);
  assertEqual("back_curve(0, 250)", avoid.rover.calls.back());
}

void test_obstruction_go_right(){
  MockArduino::instance().random_values.push_back(0);
  avoid.ranger.distance_cm = 10;
  avoid.loop(205);
  assertEqual("back_curve(205, 0)", avoid.rover.calls.back());
}

void test_obstruction_cleared(){
  MockArduino::instance().random_values.push_back(0);
  avoid.ranger.distance_cm = 10;
  avoid.loop(200);
  avoid.ranger.distance_cm = 135;
  avoid.loop(255);
  assertEqual("forward(255)", avoid.rover.calls.back());
}

TestFunc tests[] = {&test_no_obstruction,
                    &test_obstruction_go_left,
                    &test_obstruction_go_right,
                    &test_obstruction_cleared,
                    0};

int main(void) {
  return run(tests, set_up);
}


