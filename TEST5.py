#!/usr/bin/python
import serial
import time
import struct
import string
import binascii
from decimal import *
COM12=serial.Serial('COM29',115200,timeout=0.0001)
smile=open("christel.txt","r+") #Put name of TSP file here
file2= smile.read()
file2=file2.replace("\n","\r")
file2=file2.replace("  "," ")
file2_list= file2.split("\r")

x=0
y=0
smile=smile.seek(0,0)
for x in range (0,len(file2_list)):
    file2_list[x]=file2_list[x].split(" ")
int_list_2= file2_list
for y in range(0,len (int_list_2)):
    int_list_2[y][0]=(int(round(float((file2_list[y][0])))))*1
    int_list_2[y][1]=int(round(float((file2_list[y][1]))))*1
h=Decimal(0)
b=0
total=0
#for b in range(0,len(int_list_2)):
for b in range(0,len(int_list_2)):
        while (COM12.read()!= "a"):
                   h=Decimal(h+1)
        total=Decimal(total+h)       
        print "Recieved"        
        print Decimal(h/10000),
        h=0
        #time.sleep(1)
        print "Seconds"
        #time.sleep(3)
        #COM12.write (0xFF)
        COM12.write (struct.pack('H',4*(int_list_2[b][0])))
        COM12.write (struct.pack('H',4*(int_list_2[b][1])))
        print (file2.split("\r")[b])
        
        #time.sleep(0.001)
        
print Decimal((total/10000)-Decimal(2.5)),
print "Seconds"
