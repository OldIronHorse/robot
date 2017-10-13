#!/usr/bin/env python3

from unittest import main, TestCase
from scan_chart import parse

class ParseDataString(TestCase):
  def test_empty(self):
    self.assertEqual([],
                     parse('SCAN\n'))
  def test_integers(self):
    self.assertEqual([(0,12),(5,23),(3,6)],
                     parse('SCAN|0:12|5:23|3:6\n'))
  def test_float(self):
    self.assertEqual([(0,12.0),(5,23.345),(3,6.2123)],
                     parse('SCAN|0:12.0|5:23.345|3:6.2123\n'))

if __name__ == '__main__':
  main()

