// Frame structure (4)
const TS: f64 =  1.0/(15000.0*2048.0);  // seconds (basic time unit)
const TF: f64 = 307200.0 * TS;      // 10ms duration (radio frame duration)

const T_SLOT: f64 = 15360.0 * TS; // 0.5ms (radio frame type1/type2 slot duration) */

pub enum ModulationType {
    ModTypeBPSK,
    ModTypeQPSK,
    ModType16QAM,
    ModType64QAM,
}

pub const NC: u32 = 1600;

// Modulation symbol x = I+jQ
pub struct IQ {
    pub i: f64, // real
    pub q: f64, // imaginary
}

// LTE
pub enum PhysicalChannel {
    // Uplink 5.1.1
    PUSCH, // Physical Uplink Shared Channel
    PUCCH, // Physical Uplink Control Channel
    PRACH, // Physcial Random Access Channel
    
    // Physical signals 5.1.2, 6.1.2
    RefSignal, // Reference Signal
    SyncSignal, // Synchronization Signal

    // Downlink 6.1.1
    PDSCH,
    PBCH,
    PMCH,
    PCFICH,
    PDCCH,
    PHICH
}

pub enum Direction {
    Uplink = 0,
    Downlink,
}

pub struct RadioFrame {
    N_cell_id: u32,
}

pub struct PhysicalLayer {
    channel_type: PhysicalChannel,
    direction: Direction,
    scrambled_bits: Vec<u32>,
    codeword_q: Vec<u32>,
    radio_frame: RadioFrame,
}