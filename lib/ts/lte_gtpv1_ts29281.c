/*
 Copyright (c) 2018 Aigbe Research

 lte_gtpv1_u_ts29281.c
 
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


void set_gtp_octet1(struct gtpv1_u_msg *packet, uint8_t flag)
{
	packet->hdr.flag = flag;  /* ver=001, pt=1, spare=0, e=0, s=1, pn=0 */

}
	# Input:
	#  mt: Message Type - 1 octet
	# Output: 
	#  BitStream
void set_gtp_message_type_octet(struct gtpv1_u_msg *packet, uint8_t mt)
{
	packet->hdr.msg_type = mt;
}

void set_gtp_teid_octet(struct gtpv1_u_msg *packet, uint32_t teid)
{
	packet->hdr.teid = teid;
}

void set_gtp_seq_num_octet(struct gtpv1_u_msg *packet, uint16_t seq_num)
{
	packet->hdr.seq_num = seq_num;
}

	
void set_gtp_message_length(struct gtpv1_u_msg *packet, uint16_t msg_length)
{
	packet->hdr.length = msg_length;
}

/* TS 29.281 7.2 Path Management Messages */
	 
/* TS 29.281 7.2.1 Echo Request */

void echo_request_handler(struct gtpv1_u_msg *packet, uint8_t *data)
{
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
}

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


		
	