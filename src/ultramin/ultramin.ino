#define DEBUG_OUTPUT
#include <DebugUtils.h>
//#include <Ultrasonic.h>
#include <toneAC.h>

#include "pitches.h"

const int notes[] = {
  NOTE_B0,
  NOTE_C1,
  NOTE_CS1,
  NOTE_D1,
  NOTE_DS1,
  NOTE_E1,
  NOTE_F1,
  NOTE_FS1,
  NOTE_G1,
  NOTE_GS1,
  NOTE_A1,
  NOTE_AS1,
  NOTE_B1,
  NOTE_C2,
  NOTE_CS2,
  NOTE_D2,
  NOTE_DS2,
  NOTE_E2,
  NOTE_F2,
  NOTE_FS2,
  NOTE_G2,
  NOTE_GS2,
  NOTE_A2,
  NOTE_AS2,
  NOTE_B2,
  NOTE_C3,
  NOTE_CS3,
  NOTE_D3,
  NOTE_DS3,
  NOTE_E3,
  NOTE_F3,
  NOTE_FS3,
  NOTE_G3,
  NOTE_GS3,
  NOTE_A3,
  NOTE_AS3,
  NOTE_B3,
  NOTE_C4,
  NOTE_CS4,
  NOTE_D4,
  NOTE_DS4,
  NOTE_E4,
  NOTE_F4,
  NOTE_FS4,
  NOTE_G4,
  NOTE_GS4,
  NOTE_A4,
  NOTE_AS4,
  NOTE_B4,
  NOTE_C5,
  NOTE_CS5,
  NOTE_D5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_F5,
  NOTE_FS5,
  NOTE_G5,
  NOTE_GS5,
  NOTE_A5,
  NOTE_AS5,
  NOTE_B5,
  NOTE_C6,
  NOTE_CS6,
  NOTE_D6,
  NOTE_DS6,
  NOTE_E6,
  NOTE_F6,
  NOTE_FS6,
  NOTE_G6,
  NOTE_GS6,
  NOTE_A6,
  NOTE_AS6,
  NOTE_B6,
  NOTE_C7,
  NOTE_CS7,
  NOTE_D7,
  NOTE_DS7,
  NOTE_E7,
  NOTE_F7,
  NOTE_FS7,
  NOTE_G7,
  NOTE_GS7,
  NOTE_A7,
  NOTE_AS7,
  NOTE_B7,
  NOTE_C8,
  NOTE_CS8,
  NOTE_D8,
  NOTE_DS8,
};

int tune[][2] = {
  {NOTE_C5,1000},
  {NOTE_D5,500},
  {NOTE_E5,1000},
  {NOTE_F5,500},
  {NOTE_G5,1000},
  {NOTE_A6,500},
  {NOTE_B6,1000},
  {NOTE_C6,500},
  {0,0}
};

//Ultrasonic ranger(12, 13);
int step = 0;
int last_millis = 0;

void setup(){
  DEBUG_INIT(9600)
  pinMode(A0,INPUT);
  step = 0;
}

void loop(){
  int current_millis = millis();
  if(current_millis - last_millis > tune[step][1]){
    last_millis = current_millis;
    //int range = ranger.Ranging(CM);
    //DEBUG_PRINT(F("range: "))
    //DEBUG_PRINT(range)
    //toneAC(map(range, 0, 1023, NOTE_B0, NOTE_DS8));
    //toneAC(map(range, 10, 100, NOTE_B0, NOTE_DS8));
    //toneAC(notes[map(range, 0, 1023, 0, 91)],5);
    //toneAC(notes[map(range, 10, 100, 0, 91)]);
    ++step;
    if(0 == tune[step][0]){
      step = 0;
    }
  }
  int vol = map(analogRead(A0),0,1023,0,9);
  DEBUG_PRINT(F(" vol: "))
  DEBUG_PRINTLN(vol)
  toneAC(tune[step][0],vol);
}
