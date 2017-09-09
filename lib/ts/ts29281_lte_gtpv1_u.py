# ts29281_lte_gtpv1_u.py
# Reference: 3GPP TS 29.281, 3GPP TS 29.060
# Copyright 2017 Aigbe Research

from bitstring import ConstBitStream

GTP_ECHO_REQUEST = 1
GTP_ECHO_RESPONSE = 2
GTP_ERROR_INDICATION = 26
GTP_SUPPORTED_EXTENSION_HEADERS_NOTIFICIATION = 31
GTP_END_MARKER = 254
GTP_G_PDU = 255

class GTPv1:
	def __init__(self):

		self.packet = None
		self.message = {}
		# TS 29.281 4.4.2
		self.port_number = 2152
		self.header_minimum_length = 8 # bytes

		# TS 29.281 Section 5 GTP-U Header
		self.header_bits = {'Version': 3, 'PT': 1, 'SpareBit': 1, 'E': 1, 'S': 1, 'PN': 1,
							'MessageType': 8,
							'Length': 16, # length of payload in bytes
							'TEID': 32,
							 # Payload
							'SequenceNumber': 16, # Optional field
							'NPDUNumber': 8,     # Optional
							'NextExtensionHeaderType': 8  # Optional
				   		}

		# TS 29.281 6
		self.message_type = {
							1: 'Echo Request',
							2: 'Echo Response',
							26: 'Error indication',
							31: 'Supported Extension Headers Notification',
							254: 'End Marker',
							255: 'G-PDU'		
						}

	def echo_request(self):
		pass

	def echo_response(self):
		pass

	def error_indication(self):
		pass
	def end_marker(self):
		pass
	def g_pdu(self):
		pass
	def supported_ext_hdr_notf(self):
		pass

	def handle_message(self, packet):
		self.packet = ConstBitStream(packet)
		self.read_header()
		msg_type = self.message['MT']
		if msg_type == GTP_ECHO_REQUEST:
			self.echo_request()
		elif msg_type == GTP_ECHO_RESPONSE:
			self.echo_response()
		elif msg_type == GTP_G_PDU:
			self.g_pdu()
		elif msg_type == GTP_END_MARKER:
			self.end_marker()
		elif msg_type == GTP_ERROR_INDICATION:
			self.error_indication()
		elif msg_type == GTP_SUPPORTED_EXTENSION_HEADERS_NOTIFICIATION:
			self.supported_ext_hdr_notf()
		else:
			return "unknown message type"
		return self.message

	def read_header(self):
		# Always present
		self.message['Version'] = self.packet.read('uint:' + str(self.header_bits['Version']))
		self.message['PT'] = self.packet.read('uint:' + str(self.header_bits['PT']))
		self.message['SpareBit'] = self.packet.read('uint:' + str(self.header_bits['SpareBit']))
		self.message['E'] = self.packet.read('uint:' + str(self.header_bits['E']))
		self.message['S'] = self.packet.read('uint:' + str(self.header_bits['S']))
		self.message['PN'] = self.packet.read('uint:' + str(self.header_bits['PN']))
		self.message['MT'] = self.packet.read('uint:' + str(self.header_bits['MessageType']))
		self.message['Length'] = self.packet.read('uint:' + str(self.header_bits['Length']))
		self.message['TEID'] = '0x'+self.packet.read('hex:' + str(self.header_bits['TEID']))

		# Optional
		if self.message['S'] == 1:
			self.message['SN'] = '0x'+self.packet.read('hex:' + str(self.header_bits['SequenceNumber']))
		# Next Extension Header present and should be interpreted
		elif self.message['E'] == 1:
			self.message['NEHT'] = self.packet.read('uint:' + str(self.header_bits['NextExtensionHeaderType']))
		elif self.message['PN'] == 1:
			self.message['N-PDU'] = self.packet.read('uint:' + str(self.header_bits['NPDUNumber']))

		#return self.message
		
	# Dump header
	def _show_header_info(self, r):
		print "GTP Header"
		print "Version: {0}\n Flags: \n\tProtocol Type: {1}\n\tExtension Type: {2}\n\tSequence Number: {3}\n\tN-PDU Number: {4} \n" \
		"Message Type: {5} ({6}) \n Message Length: {7} \n TEID: {8} \n" \
		.format(r['Version'], r['PT'], r['E'], r['S'], r['PN'], r['MT'], self.message_type[r['MT']], r['Length'], r['TEID'])

		if r['S'] == 1:
			print "Sequence Number: {0} \n".format(r['SN'])
		elif r['E'] == 1:
			print "Next Extension Header Type: {0} \n".format(r['NEHT'])
		elif r['PN'] == 1:
			print "N-PDU Number: {0} \n".format(r['N-PDU'])


		
		




