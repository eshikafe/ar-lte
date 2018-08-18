/*
	Copyright (c) 2018 Aigbe Research

  lte_gtpv1_u_ts29281.py
 
 References: 
 	3GPP TS 29.281 - General Packet Radio System (GPRS) Tunnelling Protocol User Plane (GTPv1-U)
 	3GPP TS 29.060 - GTP across the Gn and Gp interface 
*/

//from bitstring import ConstBitStream, pack
#include <stdint.h> 

/* 6 GTPv1-U message */

#define GTP_ECHO_REQUEST  1
#define GTP_ECHO_RESPONSE 2
#define GTP_ERROR_INDICATION  26
#define GTP_SUPPORTED_EXTENSION_HEADERS_NOTIFICIATION  31
#define GTP_END_MARKER 254
#define GTP_G_PDU 255

#define GTP_DESTINATION_PORT 2152

/* 5 GTP-U Header */

struct header {
	uint8_t flag,               /* Ver, pt, spare, E, S, PN */
	uint8_t msg_type,   		/* Message Type */
	uint16_t length,
	uint32_t teid, 				/* Tunnel Endpoint Identifier */
	uint16_t seq_num,   		/* Sequence Number [optional] */
	uint8_t n_pdu_num,  		/* N-PDU Number [optional] */
	uint8_t next_ext_hdr_type	/* Next Extension Header Type [optional] */
};

struct gtpv1_u {
	struct header hdr,

}