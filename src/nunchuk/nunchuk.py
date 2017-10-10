#!/usr/bin/env python3

import serial

def unpack(line):
  fields = line.split('|')
  return (fields[0]=='1',fields[1]=='1',int(fields[2]),int(fields[3]),int(fields[4]),int(fields[5]),int(fields[6]))

if '__main__' == __name__:
  ser = serial.Serial('/dev/ttyACM0',9600)
  while True:
    print(unpack(ser.readline()))
  
