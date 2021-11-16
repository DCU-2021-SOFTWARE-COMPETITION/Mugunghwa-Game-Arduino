import serial
import pygame
import time
import requests
import json

print("file open")

# 노래 재생
pygame.mixer.init()

mugung1 = pygame.mixer.Sound("1sec_mugunghwa.mp3")
mugung2 = pygame.mixer.Sound("2sec_mugunghwa.mp3")
mugung3 = pygame.mixer.Sound("3sec_mugunghwa.mp3")

ser = serial.Serial('/dev/tty.usbmodem114201',9600,timeout=1)
ser.flush()

while True :
    ser.write(bytes('g', encoding='ascii'))
    line = ser.readline().decode('utf-8').rstrip()
    if line == 'g' :
        break


while True :
    if ser.in_waiting > 0 :
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        if line == 'p1' :
            mugung1.play()
            time.sleep(1.0)
        elif line == 'p2' :
            mugung2.play()
            time.sleep(2.0)
        elif line == 'p3' :
            mugung3.play()
            time.sleep(1.0)
        elif line == 'intrrupt!' :
            sec = ser.readline().decode('utf-8').rstrip()
            sec = float(sec)

            requests.post('http://203.250.32.29:8080/home/record', {'recordScore':sec})

            print(sec)
            break