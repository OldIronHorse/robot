#include "cmdarm.h"

CmdArm::CmdArm(Mearm &arm)
:_arm(arm){;}

void CmdArm::read(){
  if(Serial.available() > 0){
    char c = Serial.read();
    if('\n' == c){
      //TODO: parse command
      switch(_cmd[0]){
        case 'M':
          //M:nnn:nnn:nnn:c
          bool gripper = (_cmd[14] == 'O');
          _cmd[5] = 0;
          _cmd[9] = 0;
          _cmd[13] = 0;
          int pan = atoi(&_cmd[2]);
          int shoulder = atoi(&_cmd[6]);
          int elbow = atoi(&_cmd[10]);
          _arm.move_to(pan, shoulder, elbow, gripper);
          break;
      }
      memset(_cmd, 0, MAX_CMD_LEN);
      _next = 0;
    }else{
      _cmd[_next] = c;
      ++_next;
    }
  }
}

