/*
 Copyright (c) 2018 Aigbe Research

 lte_gtpv1_u_ts29281.h

 Goal:
  Use DPDK to accelerate GTPv1 user plane packet processing
 
 References: 
 	3GPP TS 29.281 - General Packet Radio System (GPRS) Tunnelling Protocol User Plane (GTPv1-U)
 	3GPP TS 29.060 - GTP across the Gn and Gp interface 
*/

#include <stdint.h> 

/* 6 GTPv1-U message */

#define GTP_ECHO_REQUEST  1
#define GTP_ECHO_RESPONSE 2
#define GTP_ERROR_INDICATION  26
#define GTP_SUPPORTED_EXTENSION_HEADERS_NOTIFICIATION  31
#define GTP_END_MARKER 254
#define GTP_G_PDU 255

#define GTP_DESTINATION_PORT 2152

/* DPDK */
#define ENABLE_DPDK 1
#define DISABLE_DPDK 0

/* 5 GTP-U Header */

struct gtpv1_header {
	uint8_t  flag;               /* Ver:3, pt:1, spare:1, E:1, S:1, PN:1 */
	uint8_t  msg_type;   		/* Message Type */
	uint16_t length;            /* Length in octets of the payload */
	uint32_t teid; 				/* Tunnel Endpoint Identifier */
	uint16_t seq_num;   		/* Sequence Number [optional] */
	uint8_t  n_pdu_num;  		/* N-PDU Number [optional] */
	uint8_t  next_ext_hdr_type;	/* Next Extension Header Type [optional] */
} __attribute__((packed));

/* GTPv1-U message */
struct gtpv1_u_msg {
	struct gtpv1_header hdr;


} __attribute__((packed));