#include <testing.h>
#include <Arduino.h>
#include "../SerialRover.h"

SerialRover rover;

void set_up() {
  MockArduino::instance().reset();
  rover.init();
}

DEFINE_TEST(setup_and_init)
  assertEqual(9600,Serial._speed);
  assertEqual("Started...\n",Serial._out_buffer);
}

DEFINE_TEST(setup_init_and_loop)
  rover.loop();
  assertEqual("Started...\nA",Serial._out_buffer);
  rover.loop();
  assertEqual("Started...\nAB",Serial._out_buffer);
}

DEFINE_TEST(setup_init_and_read_loop)
  assertEqual(OUTPUT, MockArduino::instance().pin_mode[7]);
  Serial._in_buffer = "HLLHL";
  rover.read_loop();
  assertEqual("LLHL", Serial._in_buffer);
  assertEqual(HIGH, MockArduino::instance().pin_out[7]);
  rover.read_loop();
  assertEqual("LHL", Serial._in_buffer);
  assertEqual(LOW, MockArduino::instance().pin_out[7]);
}

TestFunc tests[] = {&setup_and_init,
                    &setup_init_and_loop,
                    &setup_init_and_read_loop,
                    0};

int main(void) {
  return run(tests, set_up);
}
