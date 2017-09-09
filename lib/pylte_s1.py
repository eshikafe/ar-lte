# pylte_s1.py
#
# 3GPP LTE S1 implementation in Python 
# Copyright (c) 2017 Aigbe Research

from ts.ts29281_lte_gtpv1_u import *
from ts.ts36413_s1ap import *

import SocketServer
import logging
import socket

log_format = '%(asctime)-15s [%(levelname)s] [%(name)s] %(message)s'
logging.basicConfig(format=log_format, level=logging.INFO)
logger = logging.getLogger('pylte_s1')

# S1 User Plane
s1_u = GTPv1()
s1u_host = socket.gethostbyname(socket.gethostname())
s1u_port = s1_u.port_number

# S1 Control Plane


# Handler for S1-U
class S1UserPlaneMessageHandler(SocketServer.BaseRequestHandler):
	"""
	Callback for GTPv1-U messages
	"""
	def handle(self):
		data = self.request[0]
		if data:
			msg = s1_u.handle_message(data)
			logger.info("[GTPv1-U] SGW IP: %s:%s, Message Type: %s, teid: %s", self.client_address[0], self.client_address[1], s1_u.message_type[msg['MT']], msg['TEID'])



s1u = SocketServer.UDPServer((s1u_host, s1u_port), S1UserPlaneMessageHandler)
try:
	logger.info("eNodeB IP: %s, Port: %s", s1u_host, s1u_port)
	s1u.serve_forever()
except (SystemExit, KeyboardInterrupt):
	logger.error('Interrupted')
	raise
except Exception, e:
	logger.error('error', exc_info=True)


