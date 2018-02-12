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
#include <Ultrasonic.h>

//#define DEBUG_OUTPUT
#include <DebugUtils.h>

#define CONNECTOR "mqtt"
#define TOPIC_LIGHT_LEVEL "logbucket/iot-test/home/dining_room/light_level"
#define TOPIC_TANK_LEVEL "logbucket/iot-test/home/dining_room/tank_level"

#define TOPIC_LIGHT "iot-test/#"

int tank_alert_level = 50;
int tank_last_level = 0;

Ultrasonic ranger(12,13);
int light = LOW;

void setup(){
  DEBUG_INIT(9600)
  Ciao.begin();
  pinMode(8, OUTPUT);
  DEBUG_PRINTLN("setup complete.")
}

void loop(){
  //TODO: light level alarm: 
  //  set alarm level by inbound message
  //  notify when level breached
  CiaoData data = Ciao.read(CONNECTOR, TOPIC_LIGHT);
  DEBUG_PRINT("Received: ")
  DEBUG_PRINT(data.get(0))
  DEBUG_PRINT(": ")
  DEBUG_PRINT(data.get(1))
  DEBUG_PRINT(": ")
  DEBUG_PRINTLN(data.get(2))
  if (!data.isEmpty()){
    const char* value = data.get(2);
    DEBUG_PRINT("Received: ")
    DEBUG_PRINTLN(value)

  }
  digitalWrite(8, light);
  int light_level = analogRead(A0);
  //Ciao.write(CONNECTOR, TOPIC_LIGHT_LEVEL, String(light_level));
  long tank_level = ranger.Ranging(CM);
  if(tank_level < tank_alert_level && tank_last_level > tank_alert_level){
    Ciao.write(CONNECTOR, TOPIC_TANK_LEVEL, "LOW");
  }
  tank_last_level = tank_level;
  delay(5000);
} 
