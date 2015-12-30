#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "testing.h"
#include "Arduino.h"

#include "../ir_cmd.h"

void set_up() {
  MockArduino::instance().reset();
}

void test_cmd_from_value(){
  assertEqual(0x25, ir_cmd::cmd_from_value(0x725));
  assertEqual(0x25, ir_cmd::cmd_from_value(0xF25));
}

void test_repeat_flag_from_value(){
  assertEqual(0x7, ir_cmd::repeat_flag_from_value(0x725));
  assertEqual(0xF, ir_cmd::repeat_flag_from_value(0xF25));
}

TestFunc tests[] = {&test_cmd_from_value,
                    &test_repeat_flag_from_value,
                    0};

int main(void) {
  return run(tests, set_up);
}


