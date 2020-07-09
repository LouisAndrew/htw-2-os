#!/usr/bin/python

# server

def double (n):
        return 2 * n

host = 'localhost'
port = 6116
addr = (host, port) # create addr var -> a tuple containing host and addr.
buff = 128 # length of buffer.

from socket import *
UDPSock = socket(AF_INET, SOCK_DGRAM) # create UDP Socket
UDPSock.bind(addr)

while True:
        print('Searching for client')
        (data, addr) = UDPSock.recvfrom(buff)
        if data:
                res = double(int(data))
                UDPSock.sendto(str(res), addr)
        else:
                print('Error, no data received from client.')
                break