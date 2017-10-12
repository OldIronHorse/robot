#ifndef streamscan_h
#define streamscan_h

#include "scan.h"

class StreamScan: public Scan{
  private:
    Stream &_stream;

  public:
    StreamScan(Rover &rover_, Ultrasonic &ranger_, Servo &scanner_, Stream &stream_)
      :Scan(rover_, ranger_, scanner_), _stream(stream_){;}

    void loop(unsigned int speed);
};

#endif
