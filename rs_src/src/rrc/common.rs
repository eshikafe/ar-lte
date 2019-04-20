// PDCP-Config information element 

pub enum DiscardTimer {
    Ms50 = 50,
    Ms100 = 100,
    Ms150 = 150,
    Ms300 = 300,
    Ms500 = 500,
    Ms750 = 750,
    Ms1500 = 1500,
    Infinity = 0,
}

// pdcp-SN-Size
pub enum PdcpSnSize {
    Len7Bits = 7,
    Len12Bits = 12,
}

pub struct PdcpConfig {
    pub discard_timer: DiscardTimer,
    pub rlc_am_status_report_required: bool,
    pub rlc_um_sn_size: PdcpSnSize,
    //header_compression:
}