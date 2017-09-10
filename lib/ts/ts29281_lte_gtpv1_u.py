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

		self.message = {}
		# message:
		#    -------------
		#    H E A D E R
		#    -------------
		#    P A Y L O A D
		#    -------------
		#    RAW DATA
		#    -------------
		self.message['header'] = {}
		self.message['payload'] = {}
		self.message['raw'] = {}

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

	def echo_request_handler(self):
		pass

	def echo_response_handler(self, dest_port):
		udp_src_port = self.port_number
		pass

	def error_indication_handler(self):
		dest_port = self.port_number
		
	def end_marker_handler(self):
		dest_port = self.port_number

	def g_pdu_handler(self):
		dest_port = self.port_number
	def supported_ext_hdr_notf_handler(self):
		dest_port = self.port_number

	def handle_request(self, data):
		msg_type = data['header']['MT']
		if msg_type == GTP_ECHO_REQUEST:
			return self.echo_request_handler()
		elif msg_type == GTP_ECHO_RESPONSE:
			return self.echo_response_handler()
		elif msg_type == GTP_G_PDU:
			return self.g_pdu_handler()
		elif msg_type == GTP_END_MARKER:
			return self.end_marker_handler()
		elif msg_type == GTP_ERROR_INDICATION:
			return self.error_indication_handler()
		elif msg_type == GTP_SUPPORTED_EXTENSION_HEADERS_NOTIFICIATION:
			return self.supported_ext_hdr_notf_handler()
		else:
			return "unknown message type"


	def get_message(self, packet, src):
		# Convert received packets into binary data
		self.message['raw'] = ConstBitStream(bytearray(packet))
		self.read_header()
		return self.message

	def read_header(self):
		# Always present
		self.message['header']['Version'] = self.message['raw'].read('uint:' + str(self.header_bits['Version']))
		self.message['header']['PT'] = self.message['raw'].read('uint:' + str(self.header_bits['PT']))
		self.message['header']['SpareBit'] = self.message['raw'].read('uint:' + str(self.header_bits['SpareBit']))
		self.message['header']['E'] = self.message['raw'].read('uint:' + str(self.header_bits['E']))
		self.message['header']['S'] = self.message['raw'].read('uint:' + str(self.header_bits['S']))
		self.message['header']['PN'] = self.message['raw'].read('uint:' + str(self.header_bits['PN']))
		self.message['header']['MT'] = self.message['raw'].read('uint:' + str(self.header_bits['MessageType']))
		self.message['header']['Length'] = self.message['raw'].read('uint:' + str(self.header_bits['Length']))
		self.message['header']['TEID'] = '0x'+self.message['raw'].read('hex:' + str(self.header_bits['TEID']))

		# Optional
		if self.message['header']['S'] == 1:
			self.message['payload']['SN'] = '0x'+self.message['raw'].read('hex:' + str(self.header_bits['SequenceNumber']))
		# Next Extension Header present and should be interpreted
		elif self.message['header']['E'] == 1:
			self.message['payload']['NEHT'] = self.message['raw'].read('uint:' + str(self.header_bits['NextExtensionHeaderType']))
		elif self.message['header']['PN'] == 1:
			self.message['payload']['N-PDU'] = self.message['raw'].read('uint:' + str(self.header_bits['NPDUNumber']))

		#return self.message
		
	# Dump header
	def _show_header_info(self, r):
		print "GTP Header"
		print "Version: {0}\n Flags: \n\tProtocol Type: {1}\n\tExtension Type: {2}\n\tSequence Number: {3}\n\tN-PDU Number: {4} \n" \
		"Message Type: {5} ({6}) \n Message Length: {7} \n TEID: {8} \n" \
		.format(r['header']['Version'], r['header']['PT'], r['header']['E'], r['header']['S'], r['header']['PN'], r['header']['MT'], self.message_type[r['header']['MT']], r['header']['Length'], r['header']['TEID'])

		if r['header']['S'] == 1:
			print "Sequence Number: {0} \n".format(r['payload']['SN'])
		elif r['header']['E'] == 1:
			print "Next Extension Header Type: {0} \n".format(r['payload']['NEHT'])
		elif r['header']['PN'] == 1:
			print "N-PDU Number: {0} \n".format(r['payload']['N-PDU'])


		
		




