#ifndef IR_CMD_H
#define IR_CMD_H

namespace ir_cmd {
// Repeat/Repress mask
// 0x7__
// 0xF__
const unsigned long none = 0;

const unsigned long up = 0x14;
const unsigned long down = 0x15;
const unsigned long right = 0x17;
const unsigned long left = 0x16;
const unsigned long stop = 0x36;
const unsigned long play = 0x35;
const unsigned long pause = 0x30;
const unsigned long rwd = 0x32;
const unsigned long ffwd = 0x34;
const unsigned long skip_back = 0x24;
const unsigned long skip_forward = 0x1E;
const unsigned long on_off = 0x3D;
// digits
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

const unsigned long home = 0x3B;
const unsigned long back = 0x1F;
const unsigned long menu = 0x0D;
const unsigned long tv = 0x1C;
const unsigned long ok = 0x25;
const unsigned long vol_up = 0x10;
const unsigned long vol_down = 0x11;
const unsigned long ch_up = 0x20;
const unsigned long ch_down = 0x21;
const unsigned long mute = 0x0F;
const unsigned long prev = 0x12;
const unsigned long text = 0x0A;
const unsigned long cc = 0x0E;

unsigned long cmd_from_value(unsigned long value){
  return (value & 0xFF);
}

unsigned long repeat_flag_from_value(unsigned long value){
  return (value >> 8);
}
}
#endif
