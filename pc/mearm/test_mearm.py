#!/usr/bin/env python3
import mearm
from unittest import main,TestCase

class MockSerial:
  def __init__(self):
    self.out_buffer=b""
    self.in_buffer=b""
  
  def write(self,s):
    self.out_buffer+=s
    return len(s)

  def readline(self):
    [line, rest]=self.in_buffer.split(b'\n')
    self.in_buffer=rest
    return line;

class TestMoveTo(TestCase):
  def setUp(self):
    self.ser=MockSerial()
    self.arm=mearm.Arm(self.ser)

  def test_single(self):
    self.arm.move_to(135,10,120,False)
    self.assertEqual(b'M:135:10:120:C\n',self.ser.out_buffer)

class TestRecord(TestCase):
  def setUp(self):
    self.ser=MockSerial()
    self.arm=mearm.Arm(self.ser)

  def test_single(self):
    self.ser.in_buffer=b'P:45:85:125:O\n'
    self.assertEqual((b'P',45,85,125,True),  self.arm.read())

if __name__=='__main__':
  main()
