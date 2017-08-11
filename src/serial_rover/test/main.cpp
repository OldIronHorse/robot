#include <testing.h>
#include <Arduino.h>
#include "../SerialRover.h"
#include "../Commands.h"

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

BEGIN_TEST_SUITE(rover_read_tests)
ADD_TEST(setup_and_init)
ADD_TEST(setup_init_and_loop)
ADD_TEST(setup_init_and_read_loop)
END_TEST_SUITE

void setup_format(){
  Serial.begin(9600);
  Serial._out_buffer.clear();
}

DEFINE_TEST(serial_print_integer)
  Serial.print(78);
  assertEqual("78", Serial._out_buffer);
}

DEFINE_TEST(serial_println_integer)
  Serial.println(78);
  assertEqual("78\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_decimal)
  Serial.print(1.23456);
  assertEqual("1.23", Serial._out_buffer);
}

DEFINE_TEST(serial_println_decimal)
  Serial.println(1.23456);
  assertEqual("1.23\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_char)
  Serial.print('N');
  assertEqual("N", Serial._out_buffer);
}

DEFINE_TEST(serial_println_char)
  Serial.println('N');
  assertEqual("N\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_string)
  Serial.print("Hello world.");
  assertEqual("Hello world.", Serial._out_buffer);
}

DEFINE_TEST(serial_println_string)
  Serial.println("Hello world.");
  assertEqual("Hello world.\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_bin)
  Serial.print(78, BIN);
  assertEqual("1001110", Serial._out_buffer);
}

DEFINE_TEST(serial_println_bin)
  Serial.println(78, BIN);
  assertEqual("1001110\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_oct)
  Serial.print(78, OCT);
  assertEqual("116", Serial._out_buffer);
}

DEFINE_TEST(serial_println_oct)
  Serial.println(78, OCT);
  assertEqual("116\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_dec)
  Serial.print(78, DEC);
  assertEqual("78", Serial._out_buffer);
}

DEFINE_TEST(serial_println_dec)
  Serial.println(78, DEC);
  assertEqual("78\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_hex)
  Serial.print(78, HEX);
  assertEqual("4E", Serial._out_buffer);
}

DEFINE_TEST(serial_println_hex)
  Serial.println(78, HEX);
  assertEqual("4E\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_0dp)
  Serial.print(1.23456, 0);
  assertEqual("1", Serial._out_buffer);
}

DEFINE_TEST(serial_println_0dp)
  Serial.println(1.23456, 0);
  assertEqual("1\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_2dp)
  Serial.print(1.23456, 2);
  assertEqual("1.23", Serial._out_buffer);
}

DEFINE_TEST(serial_println_2dp)
  Serial.println(1.23456, 2);
  assertEqual("1.23\n", Serial._out_buffer);
}

DEFINE_TEST(serial_print_4dp)
  Serial.print(1.23456, 4);
  assertEqual("1.2346", Serial._out_buffer);
}

DEFINE_TEST(serial_println_4dp)
  Serial.println(1.23456, 4);
  assertEqual("1.2346\n", Serial._out_buffer);
}

TestFunc print_tests[] = {&serial_print_integer,
                          &serial_print_decimal,
                          &serial_print_char,
                          &serial_print_string,
                          &serial_print_bin,
                          &serial_print_oct,
                          &serial_print_dec,
                          &serial_print_hex,
                          &serial_print_0dp,
                          &serial_print_2dp,
                          &serial_print_4dp,
                          0};

TestFunc println_tests[] = {&serial_println_integer,
                            &serial_println_decimal,
                            &serial_println_char,
                            &serial_println_string,
                            &serial_println_bin,
                            &serial_println_oct,
                            &serial_println_dec,
                            &serial_println_hex,
                            &serial_println_0dp,
                            &serial_println_2dp,
                            &serial_println_4dp,
                            0};

Commands cmds;

void setup_commands(){
  cmds.init(9600);
}

void teardown_commands(){
  Serial._out_buffer.clear();
  Serial._in_buffer.clear();
}

DEFINE_TEST(scan)
  Serial._in_buffer = "SCN\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::SCAN,cmds._verb);
}

DEFINE_TEST(forward)
  Serial._in_buffer = "FWD\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::FORWARD,cmds._verb);
}

DEFINE_TEST(backward)
  Serial._in_buffer = "BWD\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::BACKWARD,cmds._verb);
}

DEFINE_TEST(right)
  Serial._in_buffer = "RT\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::RIGHT,cmds._verb);
}

DEFINE_TEST(left)
  Serial._in_buffer = "LT\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::LEFT,cmds._verb);
}

DEFINE_TEST(stop)
  Serial._in_buffer = "STP\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::STOP,cmds._verb);
}

DEFINE_TEST(multiple_commands)
  Serial._in_buffer = "FWD\nLT\nBWD\nRT\nSTP\n";
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::FORWARD,cmds._verb);
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::LEFT,cmds._verb);
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::BACKWARD,cmds._verb);
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::RIGHT,cmds._verb);
  while(Serial.available() > 0 && cmds._verb == Commands::NONE){
    cmds.read();
  }
  assertEqual(Commands::STOP,cmds._verb);
}

BEGIN_TEST_SUITE(commands_tests)
ADD_TEST(forward)
ADD_TEST(backward)
ADD_TEST(right)
ADD_TEST(left)
ADD_TEST(stop)
ADD_TEST(scan)
END_TEST_SUITE

int main(void) {
  return run(rover_read_tests, set_up) + 
         run(print_tests, setup_format) + 
         run(println_tests, setup_format) +
         run(commands_tests, setup_commands, teardown_commands);
}
