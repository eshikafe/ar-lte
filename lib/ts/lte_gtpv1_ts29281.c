/*
	Copyright (c) 2018 Aigbe Research

  lte_gtpv1_u_ts29281.py
 
 References: 
 	3GPP TS 29.281 - General Packet Radio System (GPRS) Tunnelling Protocol User Plane (GTPv1-U) 
*/

#include "lte_gtpv1_ts29281.h"

class GTPv1:
	def __init__(self):

		self.message = {}

		# message format:
		#    -----------------
		#      H E A D E R
		#    -----------------
		#      P A Y L O A D
		#    ------------------
		#      RAW DATA in hex
		#    ------------------
		
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

		# TS 29.281 6 GTPv1-U messages
		self.message_type = {
							1: 'Echo Request',
							2: 'Echo Response',
							26: 'Error indication',
							31: 'Supported Extension Headers Notification',
							254: 'End Marker',
							255: 'G-PDU'		
						}

	# Inputs:
	#  ver: GTP version 1
	#  pt: protocol type
	#  spare: spare bit = 0
	#  e: extension header flag
	#  s: sequence number flag
	#  pn: n-pdu number flag
	#  
	#  Output: BitStream
	#  
void set_gtp_octet1(struct gtpv1_u *packet, uint8_t flag)
{
	packet -> gtp
ver=1, pt=1, spare=0, e=0, s=1, pn=0):

		return pack('uint:{0},uint:{1},uint:{2},uint:{3},uint:{4},uint:{5}'.format(self.header_bits['Version'], \
			self.header_bits['PT'], self.header_bits['SpareBit'], self.header_bits['E'], self.header_bits['S'],\
			self.header_bits['PN'] \
			), ver, pt, spare, e, s, pn)
}
	# Input:
	#  mt: Message Type - 1 octet
	# Output: 
	#  BitStream
	def set_gtp_message_type_octet(self, mt):
		return pack('uint:{0}'.format(self.header_bits['MessageType']), mt)

	# Input:
	#  teid: Tunnel Endpoint Identifier (hex value) [4 octets (32 bits)]
	# Output:
	#  BitStream
	def set_gtp_teid_octet(self, teid):
		return pack('hex:{0}'.format(self.header_bits['TEID']), teid)

	# Input:
	#  seq_num: Sequence Number (hex value) - 2 octets
	# Output: 
	#  BitStream
	def set_gtp_seq_num_octet(self, seq_num):
		return pack('hex:{0}'.format(self.header_bits['SequenceNumber']), seq_num)

	# Input:
	#  msg_length: Message Length - 2 octets
	# Output: 
	#  BitStream
	def set_gtp_message_length(self, msg_length):
		return pack('uint:{0}'.format(self.header_bits['Length']), msg_length)

	# TS 29.281 7.2 Path Management Messages
	 
	# TS 29.281 7.2.1 Echo Request 
	def echo_request_handler(self, data):
		gtp_response = {}
		gtp_response['header'] = {}
		gtp_response['payload'] = {}
		gtp_response['raw'] = {}

		gtp_ver = data['header']['Version']
		gtp_proto_type = data['header']['PT']

		# Indicates the presence of a meaningful value of the Next
		# Extension Header field. If 1 then interprete the NEH field
		gtp_ext_hdr_flag = data['header']['E']

		# Echo Request, Echo Response: S = 1
		gtp_seq_num_flag = data['header']['S']
		gtp_npdu_num_flag = data['header']['PN']
		octet1 = self.set_gtp_octet1(gtp_ver, gtp_proto_type, 0, gtp_ext_hdr_flag, gtp_seq_num_flag, gtp_npdu_num_flag)


		# TS 29.281 7.2.2 Echo Response
		# The message shall be sent as a response to a received Echo Request. 
		gtp_msg_type = GTP_ECHO_RESPONSE
		octet2_msg_type = self.set_gtp_message_type_octet(gtp_msg_type)

		gtp_teid = data['header']['TEID']
		octet4_teid = self.set_gtp_teid_octet(gtp_teid)

		gtp_seq_num = data['payload']['SN']
		octet5_seq_num = self.set_gtp_seq_num_octet(gtp_seq_num)

		# Recovery IE
		# The Restart Counter value in the Recovery information element shall not be used, i.e. it shall be set to zero by the
		# sender and shall be ignored by the receiver. The Recovery information element is mandatory due to backwards
		# compatibility reasons. 
		recovery_ie = pack('uint:8', 14)
		restart_counter_value = pack('uint:8', 0)
		octet6_ie = recovery_ie + restart_counter_value

		# Message Length in bytes
		gtp_msg_len = len(octet5_seq_num + recovery_ie + restart_counter_value)/8
		octet3_msg_len = self.set_gtp_message_length(gtp_msg_len)

		# Prepare the response
		gtp_response['header']['Version'] = gtp_ver
		gtp_response['header']['PT'] = gtp_proto_type
		gtp_response['header']['E'] = gtp_ext_hdr_flag
		gtp_response['header']['S'] = gtp_seq_num_flag
		gtp_response['header']['PN'] = gtp_npdu_num_flag
		gtp_response['header']['MT'] = gtp_msg_type
		gtp_response['header']['Length'] = gtp_msg_len
		gtp_response['header']['TEID'] = gtp_teid
		gtp_response['payload']['SN'] = gtp_seq_num
		octets = octet1 + octet2_msg_type + octet3_msg_len + octet4_teid + octet5_seq_num + octet6_ie
		gtp_response['raw'] = bytearray(octets._getbytes())

		return gtp_response


	# 7.2.2 Echo Response 
	def echo_response_handler(self, dest_port):
		udp_src_port = self.port_number
		pass

	def supported_ext_hdr_notf_handler(self):
		dest_port = self.port_number


	def error_indication_handler(self):
		dest_port = self.port_number
		
	def end_marker_handler(self):
		dest_port = self.port_number

	def g_pdu_handler(self):
		dest_port = self.port_number
	

	def handle_request(self, data):
		msg_type = data['header']['MT']
		if msg_type == GTP_ECHO_REQUEST:
			return self.echo_request_handler(data)
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


	# Inputs:
	# 	packet: bytearray.fromhex(...)
	# 	src: (ip_addr, port)
	def get_message(self, packet, src):
		# Convert received packets into binary data
		# from bytearray.fromhex
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
		self.message['header']['TEID'] = self.message['raw'].read('hex:' + str(self.header_bits['TEID']))

		# Optional
		if self.message['header']['S'] == 1:
			self.message['payload']['SN'] = self.message['raw'].read('hex:' + str(self.header_bits['SequenceNumber']))
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


		
		




