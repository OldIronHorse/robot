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

#define CONNECTOR "mqtt"
#define TOPIC "logbucket/iot-test/home/dining_room/light_level"

void setup(){
  Ciao.begin();
}

void loop(){
  int a0 = analogRead(A0);
  Ciao.write(CONNECTOR, TOPIC, String(a0));
  delay(5000);
}
