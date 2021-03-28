# pyserial-test.py
# test serial communication with Arduino
#
# require pip install pyserial
#
# Usage: python3 pyserial-test.py
#
# yluo
#
import serial 

# serial port dev file name
# need to change based on the particular host machine
serialDevFile = 'COM3'
ser=serial.Serial(serialDevFile, 9600, timeout=1)

while True:
    line = ser.readline()
    print(line)
    #X = input()
    #ser.write(X.encode())
    if line == b'w':
        print("Hello")
