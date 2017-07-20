#include "cmdarm.h"

CmdArm::CmdArm(Mearm &arm)
:_arm(arm){;}

void CmdArm::read(){
  if(Serial.available() > 0){
    char c = Serial.read();
    if('\n' == c){
      //TODO: parse command
    }else{
      _cmd[_next] = c;
      ++_next;
    }
  }
}

