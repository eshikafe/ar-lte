// Copyright (c) 2016 Aigbe Research


// 6.3.6 R
pub const R: u8 = 0b0;

// 6.3.7 D/C
pub const D_C_CONTROL_PDU: u8 = 0b0;
pub const D_C_DATA_PDU: u8 = 0b1;

// 7.3 Constants
pub const REORDERING_WINDOW_PDCP_SN_12: u32 = 2048;
pub const REORDERING_WINDOW_PDCP_SN_15: u32 = 16384;

pub const MAX_PDCP_SN_16: u32 = 65535;
pub const MAX_PDCP_SN_15: u32 = 32767;
pub const MAX_PDCP_SN_12: u32 = 4095;
pub const MAX_PDCP_SN_7: u8 = 127;
pub const MAX_PDCP_SN_5: u8 = 31;


pub enum Sfn {
    SFN_16 = 0,
    SFN_15,
    SFN_12,
    SFN_7,
    SFN_5
}

pub const PDCP_USER_PLANE: u8 = 0;
pub const PDCP_CONTROL_PLANE: u8 = 1;
    
pub const PDCP_TX: u8 = 0;
pub const PDCP_RX: u8 = 1;

// 6.3.7 
pub const PDCP_D_C_CONTROL_PDU: u8 = 0;
pub const PDCP_D_C_DATA_PDU: u8 = 1;

// 6.3.8 PDU Type
enum PduType {
    PDU_TYPE_STATUS_REPORT = 0b000,
    PDU_TYPE_ROHC_FEEDBACK_PKT = 0b001,
    PDU_TYPE_LWA_STATUS_REPORT = 0b010, // Rel 14
    PDU_TYPE_LWA_END_MARKER_PKT = 0b011, // Rel 14
    // 111 are reserved
}

// 6.3.14 SDU Type 
enum SduType {
    SDU_TYPE_IP = 0,
    SDU_TYPE_ARP = 1
};

// 4.3.1
pub const MAX_PDCP_SDU: u32 = 8188 * 8;

use super::rrc;

struct PdcpEntity {
    // 7.1 State variables
    
    pdcp_config: RrcPdcpConfig,
    //the PDCP SN of the next PDCP SDU for a given 
    // PDCP entity
    next_pdcp_tx_sn: u32,
    //the HFN value for the generation of the COUNT 
    // value used for PDCP PDUs for agiven PDCP entity
    tx_hfn: u32, 
    next_pdcp_rx_sn: u32,
    rx_hfn: u32,
    last_submitted_pdcp_rx_sn: u32,
    reordering_pdcp_rx_count: u32,

    // 7.2 Timers
    discard_timer: u32,
    t_reordering: u32,
    t_status_report_type1: u32,
    t_status_report_type2: u32,

    // 7.3 Constants
    reordering_window: u32,
    maximum_pdcp_sn: u32,

    // A PDCP PDU is a bit string that is byte aligned (i.e. multiple of 8 bits) in length
    pdu: Vec<u8>,

}

struct PdcpPdu {
    // 6.3 Parameters 
    pdcp_sn: Vec<u8>,
    data: Vec<u8>,
    mac_i: u32,
    count: u32,
}