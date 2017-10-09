#!/usr/bin/env python3

from unittest import main, TestCase

import nunchuk

class TestUnpack(TestCase):
  def test_all_positive(self):
    self.assertEqual((True,True,100,200,300,400,500),
                     nunchuk.unpack('1|1|100|200|300|400|500\r\n'))
  def test_all_negative(self):
    self.assertEqual((True,True,-100,-200,-300,-400,-500),
                     nunchuk.unpack('1|1|-100|-200|-300|-400|-500\r\n'))
  def test_false_false(self):
    self.assertEqual((False,False,100,200,300,400,500),
                     nunchuk.unpack('0|0|100|200|300|400|500\r\n'))
  def test_false_true(self):
    self.assertEqual((False,True,100,200,300,400,500),
                     nunchuk.unpack('0|1|100|200|300|400|500\r\n'))
  def test_true_false(self):
    self.assertEqual((True,False,100,200,300,400,500),
                     nunchuk.unpack('1|0|100|200|300|400|500\r\n'))

if '__main__'==__name__:
  main()
