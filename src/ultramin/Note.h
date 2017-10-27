#ifndef NOTE_H
#define NOTE_H

class Note{
  public:
    Note() :_pitch(-1),_duration(-1){;}
    Note(int pitch, int duration):_pitch(pitch),_duration(duration){;}
    bool is_eot()const {
      return -1 == _pitch;
    }

    int _pitch;
    int _duration;
};

#endif // NOTE_H
