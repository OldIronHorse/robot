#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include <rover.h>
#include "../avoid.h"

Avoid avoid;

void set_up() {
  avoid.setup();
}

void test_no_obstruction(){
  avoid.rover.mock_range = 35;
  avoid.loop();
  assertEqual("forward(255)", avoid.rover.calls.back());
}

void test_obstruction(){
  avoid.rover.mock_range = 10;
  avoid.loop();
  assertEqual("back_curve(0, 255)", avoid.rover.calls.back());
}

void test_obstruction_cleared(){
  avoid.rover.mock_range = 10;
  avoid.loop();
  avoid.rover.mock_range = 135;
  avoid.loop();
  assertEqual("forward(255)", avoid.rover.calls.back());
}

TestFunc tests[] = {&test_no_obstruction,
                    &test_obstruction,
                    &test_obstruction_cleared,
                    0};

int main(void) {
  return run(tests, set_up);
}


