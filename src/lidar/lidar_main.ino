#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <VL53L0X.h>

VL53L0X lidar;
Ultrasonic ranger(12, 13);
Servo scanner;

void setup(){
  DEBUG_INIT(9600)
  scanner.attach(10);
}

void loop(){
  for(int a = 0; a < 181; ++a){
    scanner.write(a);
    delay(10);
    uint16_t l_range = lidar.readRangeSingleMillimeters();
    int u_range = ranger.Ranging(CM);
    DEBUG_PRINT(a)
    DEBUG_PRINT(':')
    DEBUG_PRINT(l_range)
    DEBUG_PRINT(',')
    DEBUG_PRINT(u_range)
    DEBUG_PRINT(' ')
  }
  DEBUG_PRINTLN()
  scanner.write(0);
  delay(1000);
}
