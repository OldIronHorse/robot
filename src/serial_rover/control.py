#!/usr/bin/python3

import serial
import time

with serial.Serial('/dev/ttyACM1',9600) as ser:
  print(ser.name)
  time.sleep(5);
  ser.write(b'FWD\n')
  print('FWD...')
  print(ser.readline())
  time.sleep(5);
  ser.write(b'STP\n')
  print('STP...')
  print(ser.readline())
  time.sleep(5);
  ser.write(b'SCN\n')
  print('SCN...')
  print(ser.readline())
  print('Reading...')
  print(ser.readline())
