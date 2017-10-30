#ifndef NOTE_H
#define NOTE_H

#include "pitches.h"

class Note{
  public:
    Note() :_pitch(NOTE_NONE),_duration(0){;}
    Note(int pitch, int duration):_pitch(pitch),_duration(duration){;}

    int _pitch;
    int _duration;

    const static Note NONE;
};

#define NOTE_NONE Note(0,0)

inline bool operator==(const Note& lhs, const Note& rhs){
  return lhs._pitch == rhs._pitch && lhs._duration == rhs._duration;
}

inline bool operator!=(const Note& lhs, const Note& rhs){
  return !(lhs == rhs);
}

#endif // NOTE_H
