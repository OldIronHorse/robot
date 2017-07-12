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
  assertEqual("Started...\n",Serial._buffer);
}

DEFINE_TEST(setup_init_and_loop)
  rover.loop();
  assertEqual("Started...\nA",Serial._buffer);
  rover.loop();
  assertEqual("Started...\nAB",Serial._buffer);
}

TestFunc tests[] = {&setup_and_init,
                    &setup_init_and_loop,
                    0};

int main(void) {
  return run(tests, set_up);
}
