#ifndef TUNE_H
#define TUNE_H
#include "Note.h"

#include <iostream>
using namespace std;

enum State {BEGIN,PITCH_NUM,INTRA_SEP,DUR,INTER_SEP};

void parse_tune(const char* szTune,  Note notes[]){
  cout << "Called with: " << szTune << endl;
  State state = BEGIN;
  int note_index = 0;
  char note_alpha;
  char note_num;
  char dur[5];
  int dur_index;
  while(0 != szTune){
    cout << "state = " << state << endl;
    cout << " note_alpha = " << note_alpha << endl;
    cout << " note_num = " << note_num << endl;
    switch(state){
      case BEGIN:
        if(*szTune >= 'A' && *szTune <= 'G'){
          note_alpha = *szTune;
          state = PITCH_NUM;
        }else{
          return;
        }
        break;
      case PITCH_NUM:
        cout << "PITCH_NUM: " << szTune << endl;
        if(*szTune >= '0' && *szTune <= '8'){
          note_num = *szTune;
          state = INTRA_SEP;
        }else{
          return;
        }
        break;
      case INTRA_SEP:
        cout << "INTRA_SEP: " << szTune << endl;
        if(*szTune == '|'){
          state = DUR;
          memset(dur,0,5*sizeof(char));
          dur_index = 0;
        }else{
          return;
        }
        break;
      case DUR:
        cout << "DUR: " << szTune << endl;
        if(*szTune >= '0' && *szTune <= '9' && dur_index < 5){
          dur[dur_index] = *szTune;
          ++dur_index;
        }else{
          notes[note_index]._duration = atoi(dur);
          //TODO set pitch
          state = BEGIN;
        }
        break;
      default:
        cout << "default: " << szTune << endl;
        return;
    }
    ++szTune;
  }
}

#endif //TUNE_H
