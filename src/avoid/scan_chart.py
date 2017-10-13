#!/usr/bin/env python3

import leather
import random

# SCAN[|<angle>:<range>]...<eol>

def parse(s):
  return [tuple([float(x) for x in p.split(':')]) for p in s.split('|')[1:]]

if __name__ == '__main__':
  #data = [(x,100*random.random()) for x in range(0,180)]
  data = parse('SCAN|0:100|45:75|90:50|135:40|180:60\n')

  chart = leather.Chart('X-Y Test Plot')
  chart.add_line(data)
  chart.to_svg('xy_test.svg')
