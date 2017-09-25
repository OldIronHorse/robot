#include "Commands.h"
#include <Arduino.h>

void Commands::init(int speed){
  _verb = NONE;
  Serial.begin(speed);
  _cmd_buffer_next = 0;
}

void Commands::read(){
  if(Serial.available() > 0){
    char c = Serial.read();
    Serial.print(c);
    if('\n' == c){
      // Command complete
      // TODO parse buffer
      if(0 == strncmp_P(_cmd_buffer, (const char*)F("FWD"),3)){
        _verb = FORWARD;
      }else if(0 == strncmp_P(_cmd_buffer, (const char*)F("BWD"),3)){
        _verb = BACKWARD;
      }else if(0 == strncmp_P(_cmd_buffer, (const char*)F("RT"),2)){
        _verb = RIGHT;
      }else if(0 == strncmp_P(_cmd_buffer, (const char*)F("LT"),2)){
        _verb = LEFT;
      }else if(0 == strncmp_P(_cmd_buffer, (const char*)F("STP"),3)){
        _verb = STOP;
      }else if(0 == strncmp_P(_cmd_buffer, (const char*)F("SCN"),2)){
        _verb = SCAN;
      }
      _cmd_buffer_next = 0;
    }else if(_cmd_buffer_next < CMD_BUFFER_LENGTH){
      _cmd_buffer[_cmd_buffer_next] = c;
      _cmd_buffer_next++;
    }
  }
}
