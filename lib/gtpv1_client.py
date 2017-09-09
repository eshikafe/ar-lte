# GTPv1U test client

from ts.ts29281_lte_gtpv1_u import *

import socket

gtp_peer = GTPv1()

HOST = socket.gethostbyname(socket.gethostname())
PORT = gtp_peer.port_number

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect((HOST, PORT))
s.sendto('0x320200060000000000000000e00', (HOST, PORT))

s.close()



