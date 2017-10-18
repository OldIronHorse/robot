#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <VL53L0X.h>

VL53L0X lidar;
Servo scanner;

void setup(){
  DEBUG_INIT(9600)
  scanner.attach(10);
}

void loop(){
  uint16_t range[181];
  for(int a = 0; a < 181; ++a){
    scanner.write(a);
    delay(10);
    range[a] = lidar.readRangeSingleMillimeters();
    DEBUG_PRINT(a)
    DEBUG_PRINT(':')
    DEBUG_PRINT(range[a])
    DEBUG_PRINT(' ')
  }
  DEBUG_PRINTLN()
  scanner.write(0);
  delay(1000);
}
