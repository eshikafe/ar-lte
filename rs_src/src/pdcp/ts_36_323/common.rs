

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
enum pdu_type {
    PDU_TYPE_STATUS_REPORT = 0,
    PDU_TYPE_ROHC_FEEDBACK_PKT = 1,
    /* 010 - 111 are reserved */
}

// 6.3.14 SDU Type 
enum sdu_type {
    SDU_TYPE_IP = 0,
    SDU_TYPE_ARP = 1
};

// 4.3.1
pub const MAX_PDCP_SDU: u32 = 8188 * 8;
