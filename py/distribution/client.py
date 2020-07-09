#!/usr/bin/python

# Client..
data = 60000 # nums of distribution!
# firstDigit = int( str(data[0:0]) )
firstDigit = 6
buff = (len( str(data / firstDigit) ) + 2) * firstDigit

host = 'localhost'
port = 6123
addr = (host, port)

from socket import *
UDPSock = socket(AF_INET, SOCK_DGRAM)
UDPSock.sendto(str(data), addr)

(result, addr) = UDPSock.recvfrom(buff)

print('Server address: {}'.format(addr))
print('Result: {}'.format(result))

UDPSock.close()