#ifndef TUNE_H
#define TUNE_H

#include "Note.h"

#include <iostream>
using namespace std;

enum Parsing {PITCH,DURATION};

void parse_tune(const char* szTune,  Note notes[]){
  cout << "Called with: " << szTune << endl;
  const char* from = szTune;
  const char* to = szTune;
  cout << "*from: " << int(*from) << endl;
  cout << "*from: " << *from << endl;
  int note_index = 0;
  char buffer[10];
  int pitch;
  memset(buffer,0,10*sizeof(char));
  Parsing parsing = PITCH;
  while(0 != *to){
    switch(parsing){
      case PITCH:
        if('|' == *to){
          memcpy(buffer,from,to-from);
          pitch = atoi(buffer);
          memset(buffer,0,10*sizeof(char));
          parsing = DURATION;
          from = to + 1;
        }
        break;
      case DURATION:
        if(',' == *to || '\n' == *to){
          memcpy(buffer,from,to-from);
          notes[note_index]._pitch = pitch;
          notes[note_index]._duration = atoi(buffer);
          ++note_index;
          memset(buffer,0,10*sizeof(char));
          parsing = PITCH;
          from = to + 1;
        }
        break;
    }
    ++to;
  }
  notes[note_index]._pitch = 0;
  notes[note_index]._duration = 0;
}

#endif //TUNE_H
