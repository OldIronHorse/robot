#include <stdio.h>
#include <algorithm>
#include <testing.h>
#include <Arduino.h>
#include <Servo.h>
#include <rover.h>
#include <VL53L0X.h>
#include "../avoid.h"
#include "../scan.h"

Rover rover;
VL53L0X ranger;
Avoid avoid(rover, ranger);
Scan scan(rover, ranger);

void set_up() {
  MockArduino::instance().reset();
  rover.reset();
  avoid.setup(10);
  scan.setup(10);
}

//Avoid
DEFINE_TEST(no_obstruction)
  ranger._distance_mm = 350;
  avoid.loop(200);
  assertEqual("forward(10)", rover.calls.back());
}

DEFINE_TEST(obstruction_go_left)
  MockArduino::instance().random_values.push_back(1);
  ranger._distance_mm = 100;
  avoid.loop(250);
  assertEqual("back_curve(0, 250)", rover.calls.back());
}

DEFINE_TEST(obstruction_go_right)
  MockArduino::instance().random_values.push_back(0);
  ranger._distance_mm = 100;
  avoid.loop(205);
  assertEqual("back_curve(205, 0)", rover.calls.back());
}

DEFINE_TEST(obstruction_cleared)
  MockArduino::instance().random_values.push_back(0);
  ranger._distance_mm = 100;
  avoid.loop(200);
  ranger._distance_mm = 1350;
  avoid.loop(255);
  assertEqual("forward(255)", rover.calls.back());
}

//Scan
DEFINE_TEST(scan_start_no_obstruction)
  ranger._distance_mm = 500;
  scan.start(100);
  assertEqual("forward(100)", rover.calls.back());
}

DEFINE_TEST(scan_no_obstruction)
  ranger._distance_mm = 500;
  scan.start(100);
  scan.loop(100);
  assertEqual("forward(100)", rover.calls.back());
}

DEFINE_TEST(scan_obstruction_initial)
  ranger._distance_mm = 500;
  scan.start(100);
  scan.loop(100);
  ranger._distance_mm = 15;
  scan.loop(100);
  assertEqual("right(255)", rover.calls.back());
}

DEFINE_TEST(scan_obstruction_scan)
  //TODO: fix the mapping or orientation to range
  list<uint16_t> ranges = {
    25,24,23,22,21,20,19,18,17,16,
    25,24,23,22,21,20,19,18,17,16,
    25,24,23,99,21,20,19,18,17,16,
    25,24,23,22,21,20,19,18,17,16,
    25,24,23,22,21,20,19,18,17,16,
    25,24,23,22,21,20,19,18,17,16,
    25,24,23,22,21,20,19,18,17,16};
  ranger._distance_mm = 500;
  scan.start(100);
  scan.loop(100);
  ranger._distance_mm = 15;
  int j = 0;
  do{
    scan.loop(100);
    MockArduino::instance().millis += 110;
    ranger._distance_mm = ranges.front();
    ranges.pop_front();
    ++j;
  }while(rover.calls.back() != "left(255)" && !ranges.empty());
  /*
  while(rover.calls.back() != "forward(100)"){
    scan.loop(100);
  }
  */
  for(vector<string>::iterator i = rover.calls.begin(); i != rover.calls.end(); ++i){
    cout << *i << " ";
  }
  cout << endl;
  assertEqual(99,scan._max_range);
  assertEqual(24,scan._max_range_turn_index);
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
ADD_TEST(scan_obstruction_initial)
ADD_TEST(scan_obstruction_scan)
END_TEST_SUITE

int main(void) {
  return run(tests_avoid, set_up) +
         run(tests_scan, set_up);
}

// blank comment
