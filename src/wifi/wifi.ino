#include <WiFi.h>

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

char ssid[] = "yourNetwork";      // your network SSID (name)
char pass[] = "secretPassword";   // your network password

WiFiServer server(80);

void setup(){
  DEBUG_INIT(9600);
  DEBUG_PRINT("SSID: ");
  DEBUG_PRINTLN(ssid);
  DEBUG_PRINT("Password: ");
  DEBUG_PRINTLN(pass);
  while(WiFi.status() != WL_CONNECTED){
    DEBUG_PRETTYPRINT("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    delay(10000);
  }
  DEBUG_PRETTYPRINT("Connected to WiFi.");
  DEBUG_PRINT("IP Address: ");
  DEBUG_PRINT(WiFi.localIP());
  DEBUG_PRINT("Singal Strength (RSSI): ");
  DEBUG_PRINT(WiFi.RSSI());
  DEBUG_PRETTYPRINT("Starting server...");
  server.begin();
  DEBUG_PRETTYPRINT("Server started.");
}

void loop(){
  WiFiClient client = server.available();
  if(client){
    DEBUG_PRETTYPRINT("New client...");
    boolean currentLineIsBlank = true;
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        DEBUG_PRINT(c);
        if('\n' == c && currentLineIsBlank){
          // end of request, send response
        }else if('\n' == c){
          // starting a new line
          currentLineIsBlank = true;
        }else if('\r' != c){
          // request char
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    DEBUG_PRETTYPRINT("Client disconnected.");
  }
}
