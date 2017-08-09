#!/usr/bin/env python3

parsers={b'P': lambda l: [b'P',int(l[0]),int(l[1]),int(l[2]),l[3]==b'O']}

class Arm:
  def __init__(self,ser):
    self.ser=ser

  def move_to(self,pan,shoulder,elbow,is_open):
    self.ser.write('M:{}:{}:{}:{}\n'.format(pan,shoulder,elbow,'O' if is_open else 'C').encode('utf-8'))

  def read(self):
    line=self.ser.readline().split(b':')
    return parsers[line[0]](line[1:])

