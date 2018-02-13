/*
File: MqttPub.ino

This example simply publishes analog data into a MQTT topic. Before use it,
please configure the MQTT server address via Uno WiFi Web Panel. Topics are
automatically created (or subscribed) via api calls into the sketch. You can use
a maximum of 3 topics.

Note: works only with Arduino Uno WiFi Developer Edition.
*/

#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <LiquidCrystal.h>

#define DEBUG_OUTPUT
#include <DebugUtils.h>

#define CONNECTOR "mqtt"
#define TOPIC_DISPLAY "squeezebox/display/Dining Room"
#define TOPIC_COMMAND "squeezebox/command/Dining Room"

LiquidCrystal lcd(12,11,5,4,3,2);

void setup(){
  DEBUG_INIT(9600)
  Ciao.begin();
  lcd.begin(16,2);
  lcd.print("Loading...");
  pinMode(8,INPUT);
  DEBUG_PRINTLN("setup complete.")
}

int play_pause = 0;

void loop(){
  CiaoData data = Ciao.read(CONNECTOR, TOPIC_DISPLAY);
  if (!data.isEmpty()){
    const char* value = data.get(2);
    DEBUG_PRINT("Display received: ")
    DEBUG_PRINTLN(value)
    lcd.clear();
    const char* pc = value;
    for(; *pc != '\t' && *pc != 0; ++pc){
      lcd.print(*pc);
    }
    lcd.setCursor(0,1);
    for(++pc; *pc != '\t' && *pc != 0; ++pc){
      lcd.print(*pc);
    }
  }
  int button = digitalRead(8);
  if(play_pause != button){ 
    DEBUG_PRINT("play/pause: ")
    DEBUG_PRINTLN(button)
    play_pause = button;
    if(play_pause){
      DEBUG_PRINTLN("publishing...")
      Ciao.write(CONNECTOR, TOPIC_COMMAND, "pause");
    }
  }
}
