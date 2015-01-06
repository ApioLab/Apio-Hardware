import serial # if you have not already done so
import string
import sys

ser = serial.Serial('/dev/tty.usbmodem411', 115200)
ser.open

while True:
	ser.write("l16:onoff:0-")
	line =ser.readline()
	print line



