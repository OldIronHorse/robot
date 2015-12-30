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
