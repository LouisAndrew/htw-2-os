#!/usr/bin/python

# client!
host = 'localhost'
port = 6116
addr = (host, port)
buff = 128

userIn = raw_input('Please insert an integer')

from socket import *
UDPSock = socket(AF_INET, SOCK_DGRAM)
UDPSock.sendto(userIn, addr)

(data, addr) = UDPSock.recvfrom(buff)
print('Server said, ', data)