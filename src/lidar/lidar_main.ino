#define DEBUG_OUTPUT
#include <DebugUtils.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X lidar;
Ultrasonic ranger(12, 13);
Servo scanner;

void setup(){
  DEBUG_INIT(9600)
  DEBUG_PRINTLN(F("Starting Wire..."))
  Wire.begin();
  DEBUG_PRINTLN(F("Initialising lidar..."))
  lidar.init();
  lidar.setTimeout(500);
  lidar.setMeasurementTimingBudget(20000); // high speed
  //lidar.setMeasurementTimingBudget(200000); // high accuracy
  DEBUG_PRINTLN(F("Attaching scanner.."))
  scanner.attach(10);
  DEBUG_PRINTLN(F("setup complete :-)"))
}

void loop(){
  /*
  Serial.print(lidar.readRangeSingleMillimeters());
  if(lidar.timeoutOccurred()){
    Serial.print(F("TIMEOUT!"));
  }
  Serial.println();
  */
  for(int a = 0; a < 181; a += 10){
    DEBUG_PRINT(F("scanner.write "))
    DEBUG_PRINTLN(a)
    scanner.write(a);
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
