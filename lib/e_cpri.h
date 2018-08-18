/* 
  Copyright (c) 2018 Aigbe Research
  e_cpri.h
  
  Reference:
  	eCPRI v1.1
  	Common Public Radio Interface: eCPRI Interface Specification
  	http://www.cpri.info/downloads/eCPRI_v_1_1_2018_01_10.pdf

 * Experiment with DPDK
 * Option 8 split option / split point E
 
 eCPRI Services
 -----------------------------------------------------
 User Data | Real-Time Control | other eCPRI services |
 -----------------------------------------------------
            eCPRI protocol layer                      |
 -----------------------------------------------------
                   UDP                                |
 -----------------------------------------------------
 
*/

/*
		The maximum supported payload size is 2^16 -1 but the actual size may 
		be further limited by the maximum payload size of the underlying transport network.
*/

#define MAX_PAYLOAD_SIZE 65535

/* 3.2.3.2. Common Header */

struct e_cpri_header {
	uint8_t rev_r_c;  /* eCPRI protocol revision: 4, Reserved: 3 , C: 1 */
	uint8_t msg_type;   /* 3.2.4. Message Types */
	uint16_t payload_size; /* eCPRI Payload Size is the size in bytes of 
	                          the payload part corresponding to the eCPRI message
	                        */
};

/* 3.2.3. eCPRI Message Format */

struct e_cpri_msg {
	uint8_t msg_type;
	struct e_cpri_header hdr;
	uint8_t payload[MAX_PAYLOAD_SIZE];
};

/* 3.2.4. Message Types */
enum e_cpri_msg_type {

MSG_TYPE_IQ_DATA = 0,
MSG_TYPE_BIT_SEQUENCE,
MSG_TYPE_REAL_TIME_CTRL_DATA,
MSG_TYPE_GENERIC_DATA_TRANSFER,
MSG_TYPE_REMOTE_MEMORY_ACCESS,
MSG_TYPE_ONE_WAY_DELAY_MEASUREMENT,
MSG_TYPE_REMOTE_RESET,
MSG_TYPE_EVENT_INDICATION,
/* Reserved: 8 - 63 */
/* Vendor Specific: 64 - 255 */
};

struct generic_data_transfer_msg_type {
	/*
		PC_ID:
			o An identifier of a series of “Generic Data Transfer” messages.
			o For example, identifier of a physical channel, a user, a layer, an antenna port, etc. or in case of control, an identifier for control / configuration / status / measurement or other indication.
			o How to allocate values to PC_ID is vendor specific.
	 */
	uint32_t pc_id;
	/*
	   SEQ_ID:
		o 4-byte field of each message in a series of “Generic Data Transfer” messages.
		o For example, identifier of
			▪ message sequence
			▪ data time relation to frame, OFDM symbol, a block of sub-carriers or sub-carrier etc.
			▪ identifier for completion of transfer phase
		o How to allocate values to SEQ_ID is vendor specific
	 */
	uint32_t seq_id;
	uint8_t *data;	
};

/* 3.2.4.8. Message Type #7: Event Indication */

#define EVENT_TYPE_FAULTS_INDICATION 0x00
#define EVENT_TYPE_INDICATION_ACKNOWLEDGE 0x01
#define EVENT_TYPE_NOTIFICATION_INDICATION 0x02
#define EVENT_TYPE_SYNCHRONIZATION_REQUEST 0x03
#define EVENT_TYPE_SYNCHRONIZATION_ACKNOWLEDGE 0x04
#define EVENT_TYPE_SYNCHRONIZATION_END_INDICATION 0x05
/* 0x06 ... 0xFF reserved */

#define ELEMENT_ID_ALL_ELEMENTS 0xFFFF
/* 0x0000 ... 0xFFFE vendor specific usage */

#define RAISE_A_FAULT 0x0
#define CEASE_A_FAULT 0x1
/* 0x2 ... 0xf reserved */

/* 
Fault/Notification numbers 
eCPRI fauls and notifcations
*/
#define GENERAL_USERPLANE_HW_FAULT 0x000
#define GENERAL_USERPLANE_SW_FAULT 0x001
/* 0x002 ... 0x3ff eCPRI reserved */
#define UNKNOWN_MSG_TYPE_RECEIVED 0x400
#define USERPLANE_DATA_BUFFER_UNDERFLOW 0x401
#define USERPLANE_DATA_BUFFER_OVERFLOW 0x402
#define USERPLANE_DATA_ARRIVED_TOO_EARLY 0x403
#define USERPLANE_DATA_RECEIVED_TOO_LATE 0x404
/* 0x405 ... 0x7ff */

struct fault_notif {
	uint16_t element_id;
	uint8_t raise_cease;
	uint16_t fault_notif;
	uint32_t additional_info;
};

struct event_indication_msg_type {
	uint8_t event_id;
	uint8_t event_type;
	uint8_t seq_num;  /* Sequence Number */
	uint8_t num_faults_notif; /* = N */
	struct fault_notif *fn;
};
