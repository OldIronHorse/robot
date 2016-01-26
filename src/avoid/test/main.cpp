#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <testing.h>
#include <Arduino.h>
#include <Servo.h>
#include <rover.h>
#include "../avoid.h"
#include "../scan.h"

Rover rover;
Ultrasonic ranger(12, 13);
Avoid avoid(rover, ranger);
Servo scanner;
Scan scan(rover, ranger, scanner);

void set_up() {
  cout << "setup" << endl;
  MockArduino::instance().reset();
  rover.reset();
  avoid.setup(10);
  scan.setup(10);
}

//Avoid
void test_no_obstruction(){
  cout << "test_no_obstruction" << endl;
  ranger.distance_cm = 35;
  avoid.loop(200);
  assertEqual("forward(10)", rover.calls.back());
}

void test_obstruction_go_left(){
  cout << "test_obstruction_go_left" << endl;
  MockArduino::instance().random_values.push_back(1);
  ranger.distance_cm = 10;
  avoid.loop(250);
  assertEqual("back_curve(0, 250)", rover.calls.back());
}

void test_obstruction_go_right(){
  cout << "test_obstruction_go_right" << endl;
  MockArduino::instance().random_values.push_back(0);
  ranger.distance_cm = 10;
  avoid.loop(205);
  assertEqual("back_curve(205, 0)", rover.calls.back());
}

void test_obstruction_cleared(){
  cout << "test_obstruction_cleared" << endl;
  MockArduino::instance().random_values.push_back(0);
  ranger.distance_cm = 10;
  avoid.loop(200);
  ranger.distance_cm = 135;
  avoid.loop(255);
  assertEqual("forward(255)", rover.calls.back());
}

//Scan
void test_scan_no_obstruction(){
  cout << "test_scan_no_obstruction" << endl;
  ranger.distance_cm = 50;
  scan.loop(100);
  assertEqual(90, scanner.m_angle);
  assertEqual("forward(100)", rover.calls.back());
}
//TODO stop, scan. turn tests

TestFunc tests[] = {&test_no_obstruction,
                    &test_obstruction_go_left,
                    &test_obstruction_go_right,
                    &test_obstruction_cleared,
                    &test_scan_no_obstruction,
                    0};

int main(void) {
  return run(tests, set_up);
}


