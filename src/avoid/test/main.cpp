#include <stdio.h>
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
  MockArduino::instance().reset();
  rover.reset();
  avoid.setup(10);
  scan.setup(10);
}

//Avoid
DEFINE_TEST(no_obstruction)
  ranger.distance_cm = 35;
  avoid.loop(200);
  assertEqual("forward(10)", rover.calls.back());
}

DEFINE_TEST(obstruction_go_left)
  MockArduino::instance().random_values.push_back(1);
  ranger.distance_cm = 10;
  avoid.loop(250);
  assertEqual("back_curve(0, 250)", rover.calls.back());
}

DEFINE_TEST(obstruction_go_right)
  MockArduino::instance().random_values.push_back(0);
  ranger.distance_cm = 10;
  avoid.loop(205);
  assertEqual("back_curve(205, 0)", rover.calls.back());
}

DEFINE_TEST(obstruction_cleared)
  MockArduino::instance().random_values.push_back(0);
  ranger.distance_cm = 10;
  avoid.loop(200);
  ranger.distance_cm = 135;
  avoid.loop(255);
  assertEqual("forward(255)", rover.calls.back());
}

//Scan
DEFINE_TEST(scan_start_no_obstruction)
  ranger.distance_cm = 50;
  scan.start(100);
  assertEqual(90, scanner.m_angle);
  assertEqual("forward(100)", rover.calls.back());
}

DEFINE_TEST(scan_no_obstruction)
  ranger.distance_cm = 50;
  scan.start(100);
  scan.loop(100);
  assertEqual("forward(100)", rover.calls.back());
}
//TODO stop, scan. turn tests

BEGIN_TEST_SUITE(tests_avoid)
ADD_TEST(no_obstruction)
ADD_TEST(obstruction_go_left)
ADD_TEST(obstruction_go_right)
ADD_TEST(obstruction_cleared)
END_TEST_SUITE

BEGIN_TEST_SUITE(tests_scan)
ADD_TEST(scan_start_no_obstruction)
ADD_TEST(scan_no_obstruction)
END_TEST_SUITE

//TODO Is the macro version really better?
TestFunc tests[] = {&no_obstruction,
                    &obstruction_go_left,
                    &obstruction_go_right,
                    &obstruction_cleared,
                    &scan_start_no_obstruction,
                    &scan_no_obstruction,
                    0};

int main(void) {
  return run(tests_avoid, set_up) +
         run(tests_scan, set_up);
}
