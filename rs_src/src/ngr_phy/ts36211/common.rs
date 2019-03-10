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
