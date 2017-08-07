#include "cmdarm.h"

CmdArm::CmdArm(Mearm &arm)
:_arm(arm){
  memset(_cmd, 0, MAX_CMD_LEN);
}

void CmdArm::read(){
  if(Serial.available() > 0){
    char c = Serial.read();
    if('\n' == c){
      const char* verb = strtok(_cmd, ":");
      if(NULL != verb){
        if(0 == strcmp(verb, "M")){
          //M:nnn:nnn:nnn:[C|O]
          const char* szPan = strtok(NULL, ":");
          const char* szShoulder= strtok(NULL, ":");
          const char* szElbow = strtok(NULL, ":");
          const char* szGripper = strtok(NULL, ":");
          if(NULL != szPan && NULL != szShoulder && NULL != szElbow && NULL != szGripper){
            bool gripper = (*szGripper == 'O');
            int pan = atoi(szPan);
            int shoulder = atoi(szShoulder);
            int elbow = atoi(szElbow);
            _arm.move_to(pan, shoulder, elbow, gripper);
          }
        }
      }
      memset(_cmd, 0, MAX_CMD_LEN);
      _next = 0;
    }else{
      _cmd[_next] = c;
      ++_next;
    }
  }
}

void CmdArm::mark(){
  Serial.print("P:");
  Serial.print(_arm._servos[Mearm::PAN].read());
  Serial.print(":");
  Serial.print(_arm._servos[Mearm::SHOULDER].read());
  Serial.print(":");
  Serial.print(_arm._servos[Mearm::ELBOW].read());
  if(90==_arm._servos[Mearm::GRIPPER].read()){
    Serial.println(":O");
  }else{
    Serial.println(":C");
  }
}
