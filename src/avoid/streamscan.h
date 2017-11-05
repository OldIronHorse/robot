#ifndef streamscan_h
#define streamscan_h

#include "scan.h"

class StreamScan: public Scan{
  private:
    Stream &_stream;

  public:
    StreamScan(Rover &rover_, VL53L0X &lidar_, Stream &stream_)
      :Scan(rover_, lidar_), _stream(stream_){;}

    void loop(unsigned int speed);
};

#endif
