#ifndef IR_CMD_H
#define IR_CMD_H

namespace ir_cmd {
// Repeat/Repress mask
// 0x7__
// 0xF__

const unsigned long up = 0x14;
const unsigned long down = 0x15;
const unsigned long right = 0x17;
const unsigned long left = 0x16;
// stop 0x_36
// play 0x_35
// pause 0x_30
const unsigned long rwd = 0x32;
const unsigned long ffwd = 0x34;
const unsigned long skip_back = 0x24;
const unsigned long skip_forward = 0x1E;
// on/off 0x_3D
// digits 0x_0n
const unsigned long d0 = 0x00;
const unsigned long d1 = 0x01;
const unsigned long d2 = 0x02;
const unsigned long d3 = 0x03;
const unsigned long d4 = 0x04;
const unsigned long d5 = 0x05;
const unsigned long d6 = 0x06;
const unsigned long d7 = 0x07;
const unsigned long d8 = 0x08;
const unsigned long d9 = 0x09;
// home 0x_3B
// "back" 0x_1F
// "menu" 0x_0D
// "tv" 0x_1C
const unsigned long ok = 0x25;
// vol+ 0x_10
// vol- 0x_11
// ch+ 0x_20
// ch- 0x_21
// mute 0x_0F
// "prev" 0x_12
// "text" 0x_0A
// "cc" 0x_0E

unsigned long cmd_from_value(unsigned long value){
  return (value & 0xFF);
}

unsigned long repeat_flag_from_value(unsigned long value){
  return (value >> 8);
}
}
#endif
