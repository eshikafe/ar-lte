
//   Copyright (c) 2018 Aigbe Research
//   e_cpri.rs

//   Reference:
//   	eCPRI v1.1
//   	Common Public Radio Interface: eCPRI Interface Specification
//   	http://www.cpri.info/downloads/eCPRI_v_1_1_2018_01_10.pdf

//  * Experiment with DPDK
//  * Option 8 split option / split point E

//  eCPRI Services
//  -----------------------------------------------------
//  User Data | Real-Time Control | other eCPRI services |
//  -----------------------------------------------------
//             eCPRI protocol layer                      |
//  -----------------------------------------------------
//                    UDP                                |
//  -----------------------------------------------------
//                   IP


// The maximum supported payload size is 2^16 -1 but the actual size may
// be further limited by the maximum payload size of the underlying transport network.


const MAX_PAYLOAD_SIZE: u32 = 65535;

// 3.2.3.2. Common Header

struct e_cpri_header {
	rev_r_c: u8,       // eCPRI protocol revision: 4, Reserved: 3 , C: 1 
	msg_type: u8,      //3.2.4. Message Types */
	payload_size: u16, //eCPRI Payload Size is the size in bytes of
	                   // the payload part corresponding to the eCPRI message                        */
}

// 3.2.3. eCPRI Message Format
struct e_cpri_msg {
	header: e_cpri_header,
	payload: [u8; MAX_PAYLOAD_SIZE],
}

// 3.2.4. Message Types
enum e_cpri_msg_type {
    MSG_TYPE_IQ_DATA = 0,
    MSG_TYPE_BIT_SEQUENCE,
    MSG_TYPE_REAL_TIME_CTRL_DATA,
    MSG_TYPE_GENERIC_DATA_TRANSFER,
    MSG_TYPE_REMOTE_MEMORY_ACCESS,
    MSG_TYPE_ONE_WAY_DELAY_MEASUREMENT,
    MSG_TYPE_REMOTE_RESET,
    MSG_TYPE_EVENT_INDICATION,
    // Reserved: 8 - 63
    // Vendor Specific: 64 - 255
}

struct generic_data_transfer_msg_type {
	//	PC_ID:
	//		o An identifier of a series of “Generic Data Transfer” messages.
	//		o For example, identifier of a physical channel, a user, a layer, an antenna port, etc. or in case of control, an identifier for control / configuration / status / measurement or other indication.
	//		o How to allocate values to PC_ID is vendor specific.
	pc_id: u32,

    //  SEQ_ID:
	//	o 4-byte field of each message in a series of “Generic Data Transfer” messages.
	//	o For example, identifier of
	//		▪ message sequence
	//		▪ data time relation to frame, OFDM symbol, a block of sub-carriers or sub-carrier etc.
	//		▪ identifier for completion of transfer phase
	//	o How to allocate values to SEQ_ID is vendor specific
	 
	seq_id: u32,
	data: &u8,
}

// 3.2.4.8. Message Type #7: Event Indication

const EVENT_TYPE_FAULTS_INDICATION: u8 = 0x00;
const EVENT_TYPE_INDICATION_ACKNOWLEDGE: u8 = 0x01;
const EVENT_TYPE_NOTIFICATION_INDICATION: u8 = 0x02;
const EVENT_TYPE_SYNCHRONIZATION_REQUEST: u8 = 0x03;
const EVENT_TYPE_SYNCHRONIZATION_ACKNOWLEDGE: u8 = 0x04;
const EVENT_TYPE_SYNCHRONIZATION_END_INDICATION: u8 = 0x05;
// 0x06 ... 0xFF reserved 

const ELEMENT_ID_ALL_ELEMENTS: u16 = 0xFFFF;
// 0x0000 ... 0xFFFE vendor specific usage 

const RAISE_A_FAULT: u8 = 0x0;
const CEASE_A_FAULT: u8 = 0x1;
// 0x2 ... 0xf reserved 

// Fault/Notification numbers
// eCPRI fauls and notifcations

const GENERAL_USERPLANE_HW_FAULT: u16 = 0x000;
const GENERAL_USERPLANE_SW_FAULT: u16 = 0x001;
// 0x002 ... 0x3ff eCPRI reserved 
const UNKNOWN_MSG_TYPE_RECEIVED: u16 = 0x400;
const USERPLANE_DATA_BUFFER_UNDERFLOW: u16 = 0x401;
const USERPLANE_DATA_BUFFER_OVERFLOW: u16 = 0x402;
const USERPLANE_DATA_ARRIVED_TOO_EARLY: u16 = 0x403;
const USERPLANE_DATA_RECEIVED_TOO_LATE: u16 = 0x404;
// 0x405 ... 0x7ff

struct fault_notif {
	element_id: u16,
	raise_cease: u8,
	fault_notif: u16,
	additional_info: u32,
}

struct event_indication_msg_type {
	event_id: u8,
	event_type: u8,
	seq_num: u8,  // Sequence Number
	num_faults_notif: u8, // = N 
	fn: &fault_notif,
}
