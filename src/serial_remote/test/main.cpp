#include <testing.h>
#include <Arduino.h>
#include "../Remote.h"

Remote remote;

void set_up(){
  remote.setup(9600);  
}

DEFINE_TEST(set_digital_output)
  Serial._in_buffer = "PM:07:O\n";
  while(Serial.available() > 0){
    remote.loop();
  }
  assertEqual(OUTPUT,MockArduino::instance().pin_mode[7]);
}

BEGIN_TEST_SUITE(pins)
ADD_TEST(set_digital_output)
END_TEST_SUITE

int main(){
  return run(pins,set_up);
}
