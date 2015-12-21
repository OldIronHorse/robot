/*
 * Mock IRremote
 * Version 0.1 December 2015
 */

#ifndef IRremote_h
#define IRremote_h


// Results returned from the decoder
class decode_results {
public:
  int decode_type; // NEC, SONY, RC5, UNKNOWN
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
};

// Values for decode_type
#define NEC 1
#define SONY 2
#define RC5 3
#define RC6 4
#define UNKNOWN -1

// Decoded value for NEC when a repeat code is received
#define REPEAT 0xffffffff

// main class for receiving IR
class IRrecv
{
public:
  IRrecv(int recvpin)
    :_recvpin(recvpin), _value(0){;}
  void blink13(int blinkflag);
  int decode(decode_results *results){
    if(0 != _value){
      results->value = _value;
      return 1;
    }
    return 0;
  }
  void enableIRIn(){;}
  void resume(){;}

  int _recvpin;
  unsigned long _value;
};

#endif
