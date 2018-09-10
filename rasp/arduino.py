import os
import serial

ser = serial.Serial(os.environ.get('DEVICE'), 9600)
ser.baudrate = 9600

def sendCommand(command):
    print(ser.readline())
    ser.write(command.encode())
    print(ser.readline())
    return