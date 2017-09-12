# GTPv1U test client

from ts.ts29281_lte_gtpv1_u import *

import socket

gtp_peer = GTPv1()

HOST = socket.gethostbyname(socket.gethostname())
PORT = gtp_peer.port_number

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect((HOST, PORT))

# Test 1: Send EchoRequest Message
# Send raw binary over the UDP socket
data = bytearray.fromhex('320100040000000000000000')
s.sendto(data, (HOST, PORT))

# Should receive an EchoResponse + Recovery IE: 0
received = s.recv(1024)

print "Sent:     {}".format(data)
print "Received: {}".format(received)

s.close()



