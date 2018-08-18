/* lte_pdcp_ts36323.h
 
Reference Document:
 LTE;
 Evolved Universal Terrestrial Radio Access (E-UTRA);
 Packet Data Convergence Protocol (PDCP) specification
 3GPP TS 36.323, 3GPP Release 12.2.0
 https://www.etsi.org/deliver/etsi_ts/136300_136399/136323/12.02.00_60/ts_136323v120200p.pdf

 Copyright (c) 2016 Aigbe Research

*/

//#include "rohc_rfc3095.h"
#include <stdint.h> /* for uint8_t, uint16_t etc */


// 7.3 Constants
#define REORDERING_WINDOW_PDCP_SN_12 2048
#define REORDERING_WINDOW_PDCP_SN_15 16384

#define MAX_PDCP_SN_16 65535
#define MAX_PDCP_SN_15 32767
#define MAX_PDCP_SN_12 4095
#define MAX_PDCP_SN_7 127
#define MAX_PDCP_SN_5 31


enum sfn {
    SFN_16 = 0,
    SFN_15,
    SFN_12,
    SFN_7,
    SFN_5
};

#define PDCP_USER_PLANE 0
#define PDCP_CONTROL_PLANE 1
    
#define PDCP_TX 0
#define PDCP_RX 1

/* 6.3.7 */
#define PDCP_D_C_CONTROL_PDU 0
#define PDCP_D_C_DATA_PDU 1

/* 6.3.8 PDU Type */
enum pdu_type {
    PDU_TYPE_STATUS_REPORT = 0,
    PDU_TYPE_ROHC_FEEDBACK_PKT = 1,
    /* 010 - 111 are reserved */
};

/* 6.3.14 SDU Type */
enum sdu_type {
    SDU_TYPE_IP = 0,
    SDU_TYPE_ARP = 1
};

#define MAX_PDCP_SDU 8188 * 8 /* Octets  TS 36.323 4.3.1 */

/* Control plane PDCP Data PDU - 6.2.2 */
struct pdcp_data_pdu_srb {
    uint8_t r,             /* 3 bits */
    uint8_t pdcp_sfn,      /* 5 bits - SRBs */
    uint8_t* data,         /* PDCP SDU - 6.3.3 */
    uint32_t mac_i         /* 32 bits */
};

# 6.2.3 User plane PDCP Data PDU with long PDCP SN (12 bits)
cdef struct pdcp_data_pdu_long_sn:
    char dc        # 1 bit
    char r         # 3 bits - 0 # 6.3.6
    short pdcp_sn  # 12 bits - DRBs, if configured by upper layers (pdcp-SN-Size [3]) 
    char* data     # PDCP SDU

# 6.2.4 User plane PDCP Data PDU with short PDCP SN (7 bits) 
cdef struct pdcp_data_pdu_short_sn:
    char dc       # 1 bit
    char pdcp_sn  # 7 bits - DRBs, if configured by upper layers (pdcp-SN-Size [3]) 
    char* data    # PDCP SDU

# 6.2.5 PDCP Control PDU for interspersed ROHC feedback packet
cdef struct pdcp_ctrl_pdu_rohc:
    char dc                 # 1 bit
    char pdu_type           # 3 bits
    int r                   # 4 bits
    char* inter_rohc_pkt
    
# 6.2.6 PDCP Control PDU for PDCP status report
# 6.2.6.1
cdef struct pdcp_ctrl_pdu_12:
    char dc                 # 1 bit
    char pdu_type           # 3 bits
    short fms               # 12 bits
    char* bitmap

# 6.2.6.2
cdef struct pdcp_ctrl_pdu_15:
    char dc                 # 1 bit
    char pdu_type           # 3 bits
    char r                  # 5 bits - 0
    short fms               # 15 bits
    char* bitmap            # variable length

# 6.2.8 RN user plane PDCP Data PDU with integrity protection
cdef struct pdcp_data_pdu_int_protect:
    char dc                 # 1 bit
    char r                  # 3 bits
    short pdcp_sn           # 12 bits - DRBs, if configured by upper layers (pdcp-SN-Size [3]) 
    char* data              # PDCP SDU
    int mac_i               # 32 bits

/* 6.2.9 User plane PDCP Data PDU with extended PDCP SN (15 bits) */
struct pdcp_data_pdu_extended {
    char dc,                 /* 1 bit - 0 or 1 */
    uint16_t pdcp_sn,        /* 15 bits - DRBs, if configured by upper layers (pdcp-SN-Size [3]) */
    uint8_t* data,           /* PDCP SDU */
    uint32_t mac_i           /* 32 bits */
};

/* 6.2.10 User plane PDCP Data PDU for SLRB */
struct pdcp_data_pdu_slrb {
    uint8_t sdu_type,           /* 3 bits */
    uint8_t pgk_index,          /* 5 bits */
    uint16_t ptk_identity,      /* 2 octets - 16 bits */
    uint16_t pdcp_sn,           /* 2 octets - SLRBs   */
    uint8_t* data
};

cdef union Timer:
    unsigned int discardTimer
    unsigned int tReordering
    
struct pdcp_pdu {
    int plane;           /* user plane or control plane */
    int type;            /* control or data pdu */
    int direction,       /* Transmitting or receiving */
    char *pdcp_sdu,      /* 6.3.3 Data */
    int logical_channel, /* SRBs, DRBs, and SLRBs mapped on DCCH, DTCH, and STCH */
    int sfn_type,
    union pdcp_pdu_type {
        struct pdcp_data_pdu_srb pps,
        struct pdcp_data_pdu_long_sn ppls,
        struct pdcp_data_pdu_short_sn ppss,
        struct pdcp_ctrl_pdu_rohc ppr,
        struct pdcp_ctl_pdu_12 pcp12,
        struct pdcp_ctrl_pdu_15 pcp15,
        struct pdcp_data_pdu_int_protect pdpip,
        struct pdcp_data_pdu_extended pdpe,
        struct pdcp_data_pdu_slrb pdps,
    }
        
};

struct pdcp_entity {
    def __init__(self, pdcp_pdu data, Timer timer):
        # Separate the SDU data from the PDU
        self.pdcp_sdu = data.pdcp_sdu
        data.pdcp_sdu = NULL
        self.pdcp_pdu = data

        # 7.1 Variables
        # PDCP SN of the next PDCP SDU for a given PDCP entity
        cdef unsigned int self.next_pdcp_tx_sn = 0

        # HFN value for the generation of the COUNT value
        #  used for PDCP PDUs for a given PDCP entity
        cdef unsigned int self.tx_hfn = 0

        # The next expected PDCP SN by the receiver for a given PDCP entity
        cdef unsigned int self.next_pdcp_rx_sfn = 0

        cdef unsigned int self.rx_hfn = 0

        # Last_Submitted_PDCP_RX_SN indicates the SN of the last PDCP SDU delivered to the upper layers.
        cdef unsigned int self.last_submitted_pdcp_rx_sfn = MAXIMUM_PDCP_SN[self.pdcp_pdu.sfn_type]

        # This variable is used only when the reordering function is used.
        # This variable holds the value of the COUNT following
        #  the COUNT value associated with the PDCP PDU which triggered t-Reordering
        cdef uint self.reordering_pdcp_rx_count

        # 7.2 Timers
        # The duration of the timer is configured by upper layers.
        # In the transmitter, a new timer is started upon reception of an SDU from upper layer. 
        cdef uint self.discardTimer = timer.discardTimer

        # This timer is used to detect loss of PDCP PDUs as specified
        # in the subclause 5.1.2.1.4. If t-Reordering is running,
        # t-Reordering shall not be started additionally, i.e. only one tReordering
        # per PDCP entity is running at a given time. 
        cdef uint self.tReordering = timer.tReordering

}