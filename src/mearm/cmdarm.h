#include <Arduino.h>
#include "mearm.h"

#define MAX_CMD_LEN 20

class CmdArm{
  public:
    CmdArm(Mearm &arm);

    void read();
    void mark();

    Mearm &_arm;

    char _cmd[MAX_CMD_LEN];
    int _next;
};
