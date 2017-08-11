#include <Servo.h>
#include <Ultrasonic.h>
#include <rover.h>
#include "Commands.h"

Servo scanner;
Ultrasonic ranger(12,13);
Rover rover;
Commands cmds;
unsigned int speed = Rover::max_speed;


void setup() {
  scanner.attach(10);
  rover.setup();
  cmds.init(9600);
  rover.stop();
}

void loop() {
  cmds.read();
  switch(cmds._verb){
    case Commands::FORWARD:
      rover.forward(speed);
      break;
    case Commands::BACKWARD:
      rover.back(speed);
      break;
    case Commands::STOP:
      rover.stop();
      break;
    case Commands::RIGHT:
      rover.right(speed);
      break;
    case Commands::LEFT:
      rover.left(speed);
      break;
    case Commands::SCAN:
      for(int angle = 0; angle < 180; angle += 10){
        scanner.write(angle);
        delay(100);
        Serial.print(angle);
        Serial.print(':');
        Serial.print(ranger.Ranging(CM));
        Serial.print(',');
      }
      scanner.write(90);
      Serial.print('\n');
      break;
  }
  cmds._verb = Commands::NONE;
}
