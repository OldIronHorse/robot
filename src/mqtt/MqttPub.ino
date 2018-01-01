/*
File: MqttPub.ino

This example simply publishes analog data into a MQTT topic. Before use it,
please configure the MQTT server address via Uno WiFi Web Panel. Topics are
automatically created (or subscribed) via api calls into the sketch. You can use
a maximum of 3 topics.

Note: works only with Arduino Uno WiFi Developer Edition.
*/

#include <LiquidCrystal.h>
#include <Wire.h>
#include <lib/SC16IS750.h>
#include <lib/espduino.h>
#include <lib/mqtt.h>

#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

WifiData espSerial;
ESP esp(&espSerial);
MQTT mqtt(&esp);

void mqttData(void* response)
{
  RESPONSE res(response);
	String mqtt_topic = res.popString();
	String mqtt_data = res.popString();
  espSerial.print(mqtt_topic);
  espSerial.print(":");
  espSerial.println(mqtt_data);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(mqtt_topic);
  lcd.setCursor(0,1);
  lcd.print(mqtt_data);
}

void setup(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Starting...");
  espSerial.begin(9600);
	esp.enable();
	delay(1000);
	esp.reset();
	delay(1000);
  espSerial.println("\nStarting...");
  mqtt.dataCb.attach(mqttData);
  if(mqtt.begin("arduino","","",60,true)){
    espSerial.println("\tMQTT started.");
  }
  mqtt.subscribe("arduino/data",0);
  mqtt.subscribe("arduino/now_playing",0);
  mqtt.subscribe("squeezebox/kitchen/now_playing",0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ready.");
}

void loop(){
  esp.process();
}

/*
void setup() {
	Ciao.begin();
}


void loop(){
	delay(500);
	CiaoData data = Ciao.read(CONNECTOR, "arduino/data");
	if (!data.isEmpty()){
		const char* value = data.get(2);
    Ciao.write(CONNECTOR, "arduino/analog/A1", value); // pushes data into a channel called PIN_A1
  }
}
*/
