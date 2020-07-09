#!/usr/bin/python

# Server Side.
buff = 16

def throw (n):
        import random
        distribution = [0, 0, 0, 0, 0, 0]
        for i in range(n):
                j = random.randint(1, 6) - 1
                distribution[j] += 1

        return distribution

host = 'localhost'
port = 6123
addr = (host, port)

from socket import *
UDPSock = socket(AF_INET, SOCK_DGRAM)
UDPSock.bind(addr)

while True:
        print('Waiting for client')
        (data, addr) = UDPSock.recvfrom(buff)

        if not data:
                print('Error, no string from client!')
                break
        else:
                print('Anzahl von Wuerfe: {}'.format(data))
                res = throw(int(data))
                UDPSock.sendto(str(res), addr)

UDPSock.close()