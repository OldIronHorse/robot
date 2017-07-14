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
    if('\n' == c){
      // Command complete
      // TODO parse buffer
      if(0 == strncmp("FWD",_cmd_buffer,3)){
        _verb = FORWARD;
      }else if(0 == strncmp("BWD",_cmd_buffer,3)){
        _verb = BACKWARD;
      }else if(0 == strncmp("RT",_cmd_buffer,2)){
        _verb = RIGHT;
      }else if(0 == strncmp("LT",_cmd_buffer,2)){
        _verb = LEFT;
      }else if(0 == strncmp("STP",_cmd_buffer,3)){
        _verb = STOP;
      }
      _cmd_buffer_next = 0;
    }else if(_cmd_buffer_next < CMD_BUFFER_LENGTH){
      _cmd_buffer[_cmd_buffer_next] = c;
      _cmd_buffer_next++;
    }
  }
}
