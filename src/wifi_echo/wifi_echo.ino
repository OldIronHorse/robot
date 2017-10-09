#include <Wire.h>
#include <UnoWiFiDevEd.h>

// connect a telnet client to port 23

void setup(){
  Wifi.begin();
  Wifi.print("Echo server up...");
}

void loop(){
  if(Wifi.available()){
    Wifi.print(Wifi.read());
  }
}
