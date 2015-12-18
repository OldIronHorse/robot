#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include "Arduino.h"


void set_up() {
  MockArduino::instance().reset();
}

void test_dummy(){
  assertEqual(1,0);
}

TestFunc tests[] = {&test_dummy,
                    0};

int main(void) {
  return run(tests, set_up);
}


