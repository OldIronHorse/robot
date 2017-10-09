#include <Wire.h>
#include <UnoWiFiDevEd.h>

void setup(){
  Wifi.begin();
  Wifi.print("Echo server up...");
}

void loop(){
  if(Wifi.available()){
    Wifi.print(Wifi.read());
  }
}
