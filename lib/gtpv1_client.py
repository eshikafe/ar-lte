# GTPv1U test client

from ts.ts29281_lte_gtpv1_u import *

import socket

gtp_peer = GTPv1()

HOST = '148.135.48.11' #socket.gethostbyname(socket.gethostname())
PORT = gtp_peer.port_number

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect((HOST, PORT))

# Send raw binary over the UDP socket
data = bytearray.fromhex('320100040000000000000000')
s.sendto(raw_data, (HOST, PORT))

#received = s.recv(1024)

print "Sent:     {}".format(data)
#print "Received: {}".format(received)

s.close()



