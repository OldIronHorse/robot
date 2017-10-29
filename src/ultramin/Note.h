#ifndef NOTE_H
#define NOTE_H

#include "pitches.h"

class Note{
  public:
    Note() :_pitch(0),_duration(0){;}
    Note(int pitch, int duration):_pitch(pitch),_duration(duration){;}

    int _pitch;
    int _duration;
};

#define NOTE_NONE Note(0,0)

bool operator==(const Note& lhs, const Note& rhs){
  return lhs._pitch == rhs._pitch && lhs._duration == rhs._duration;
}

bool operator!=(const Note& lhs, const Note& rhs){
  return !(lhs == rhs);
}

#endif // NOTE_H
