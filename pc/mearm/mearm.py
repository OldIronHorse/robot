#!/usr/bin/env python3

class Arm:
  def __init__(self,ser):
    self.ser=ser

  def move_to(self,x,y,z,is_open):
    self.ser.write('M:{}:{}:{}:{}\n'.format(x,y,z,'O' if is_open else 'C').encode('utf-8'))
