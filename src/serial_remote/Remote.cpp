#include <memory.h>
#include <Arduino.h>
#include "Remote.h"

#include <iostream>

Remote::Remote()
:_next_cmd_buffer(0){
  memset(_cmd_buffer,0,sizeof(_cmd_buffer));
}


void Remote::setup(int baud){
  Serial.begin(baud);
}

void Remote::loop(){
  if(Serial.available() > 0){
    char c = Serial.read();
    if(c == '\n'){
      if(0 == strncmp("PM",_cmd_buffer,2)){
        std::cout << _cmd_buffer << std::endl;
        // pinMode PM:nn:[I|O]
        _cmd_buffer[5] = 0;
        int pin = atoi(&_cmd_buffer[3]);
        std::cout << pin << std::endl << _cmd_buffer[6] << std::endl;
        switch(_cmd_buffer[6]){
          case 'I':
            pinMode(pin,INPUT);
            break;
          case 'O':
            pinMode(pin,OUTPUT);
            break;
        }
      }
      _next_cmd_buffer = 0;
      memset(_cmd_buffer,0,sizeof(_cmd_buffer));
    }else{
      _cmd_buffer[_next_cmd_buffer] = c;
      _next_cmd_buffer++;
    }
  }
}
