#include <IRremote.h>

IRrecv irrecv(9);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  if(irrecv.decode(&results)){
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

// Repeat/Repress mask
// 0x7__
// 0xF__

// stop 0x_36
// play 0x_35
// pause 0x_30
// rwd 0x_32
// ffwd 0x_34
// skip back 0x_24
// skip forward 0x_1E
// on/off 0x_3D
// digits 0x_0n
// home 0x_3B
// "back" 0x_1F
// "menu" 0x_0D
// "tv" 0x_1C
// "ok" 0x_25
// vol+ 0x_10
// vol- 0x_11
// ch+ 0x_20
// ch- 0x_21
// mute 0x_0F
// "prev" 0x_12
// "text" 0x_0A
// "cc" 0x_0E
