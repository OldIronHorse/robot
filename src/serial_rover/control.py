#!/usr/bin/python3

import serial

ser = serial.Serial('/dev/tty/ACM*',9600)
print(ser.name)
ser.write(b'FWD\n')
ser.write(b'STP\n')
ser.write(b'SCN\n')
scan_data = ser.readline()
print('scan:', scan_data)
ser.close()
