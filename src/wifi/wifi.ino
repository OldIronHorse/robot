#include <UnoWiFiDevEd.h>

#define DEBUG_OUTPUT
#include <DebugUtils.h>

/*******************************************************************************
Interface:

Set pin mode
POST http://<host>/pins/<pin>&mode=[read|write]

Read from pin
GET http://<host>/pins/<pin>

Write to pin
POST http://<host>/pins/<pin>&value=[true|false]
POST http://<host>/pins/<pin>&value=<n>
*******************************************************************************/


void setup(){
  Wifi.begin();
  Wifi.println("Server is up...");
}

void loop(){
  while(Wifi.available()){
    Wifi.println("Processing...");
    String cmd = Wifi.readStringUntil('/');
    Wifi.print("Command: ");
    Wifi.println(cmd);
  }
}
