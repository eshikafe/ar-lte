//   Copyright (c) 2019 Aigbe Research
//   ts_36211.rs
//   TS 36.211: Physical channels and modulation 
//
//  Physical layer processing:
// 	  scrambling
// 	  modulation
// 	  layer mapping
// 	  precoding
// 	  mapping to resource elements
// 	  OFDM signal generation
//
// 	Input to the physical layer: codewords


// Frame structure (4)
const Ts: f64 =  1.0/(15000.0*2048.0);  // seconds (basic time unit)
const Tf: f64 = 307200.0 * Ts;      // 10ms duration (radio frame duration)

const LTE_PHY_RADIO_FRAME_TYPE1: &str = "FDD";
const LTE_PHY_RADIO_FRAME_TYPE2: &str = "TDD";

enum RadioTxType {
  LTE_PHY_FDD_HALF_DUPLEX,
  LTE_PHY_FDD_FULL_DUPLEX,
}

//  Frame structure type 1 (4.1)
//    1 radio frame (Tf) = 20 slots = 10 subframes = 10ms
//    1 slot (T_slot_fdd) = 0.5ms
//    1 subframe = 2 slots = 1ms [2i and 2i+1, i = subframe]
//    For FDD, DL transmission = 10 subframes, UL transmission = 10 subframes
//    in each Tf interval

const T_slot: f64 = 15360.0 * Ts; // 0.5ms (radio frame type1/type2 slot duration) */

//  Uplink physical channels (5.1.1)
//     PUSCH
//     PUCCH
//     PRACH

//  UL Physical channel:
//     resource_elements
//     sets of resource_elements
//     Transmitted signal/slot:
//       resource grid:
//       N_UL_RB*N_RB_SC
//       num_uplink_symb (N_UL_symb)
//       N_UL_RB:
//         uplink tx bw configured in the cell
//  SC-FDMA symbols in a slot depends on
//  UL_CyclicPrefixLength Table 5.2.3.1
 
//   Antenna port
//   1 resource grid per ant_port
//   num_ant_port
//   ant_port used for tx of a phy channel
 

struct ul_phy_channel
{
  resource_elements: u32,
}

enum ModulationType {
    MOD_TYPE_BPSK,
    MOD_TYPE_QPSK,
    MOD_TYPE_16QAM,
    MOD_TYPE_64QAM,
}

const Nc: u32 = 1600;

const _a: f64 = 1.0/2.0_f64.sqrt();
const _b: f64 = 1.0/10.0_f64.sqrt();
const _c: f64 = 1.0/42.0_f64.sqrt();

struct ModulationSymbol {
    // I+jQ
    I: f64, // real
    Q: f64, // imaginary
}

// BPSK - TS 36.211 V12.2.0, section 7.1.1, Table 7.1.1-1 */
const bpsk_sym: [ModulationSymbol; 2] = [ModulationSymbol{I: _a, Q: _a}, ModulationSymbol{I: -_a, Q: -_a}];

// QPSK - TS 36.211 V12.2.0, section 7.1.2, Table 7.1.2-1
// _qpsk = (complex(_a,_a), complex(_a,-_a),complex(-_a,_a),complex(-_a,-_a))

// // 16QAM - TS 36.211 V12.2.0, section 7.1.3, Table 7.1.3-1
// _16qam = (complex(_b,_b), complex(_b,3*_b), complex(3*_b,_b), complex(3*_b,3*_b),
//            complex(_b,-_b), complex(_b,-3*_b), complex(3*_b,-_b), complex(3*_b,-3*_b),
//            complex(-_b,_b), complex(-_b,3*_b), complex(-3*_b,_b), complex(-3*_b,3*_b),
//            complex(-_b,-_b), complex(-_b,-3*_b), complex(-3*_b,-_b),complex(-3*_b,-3*_b)
//            )

// // 64QAM - TS 36.211 V12.2.0, section 7.1.4, Table 7.1.4-1
// _64qam = (complex(3*_c,3*_c), complex(3*_c,_c), complex(_c,3*_c), complex(_c,_c),
//            complex(3*_c,5*_c), complex(3*_c,7*_c), complex(_c,5*_c), complex(_c,7*_c),
//            complex(5*_c,3*_c), complex(5*_c,_c), complex(7*_c,3*_c), complex(7*_c,_c),
//            complex(5*_c,5*_c), complex(5*_c,7*_c), complex(7*_c,5*_c), complex(7*_c,7*_c),
//            complex(3*_c,-3*_c), complex(3*_c,-_c), complex(_c,-3*_c), complex(_c,-_c),
//            complex(3*_c,-5*_c), complex(3*_c,-7*_c), complex(_c,-5*_c), complex(_c,-7*_c),
//            complex(5*_c,-3*_c), complex(5*_c,-_c), complex(7*_c,-3*_c), complex(7*_c,-_c),
//            complex(5*_c,-5*_c), complex(5*_c,-7*_c), complex(7*_c,-5*_c), complex(7*_c,-7*_c),
//            complex(3*_c,3*_c), complex(-3*_c,_c), complex(-_c,3*_c), complex(-_c,_c),
//            complex(-3*_c,5*_c), complex(-3*_c,7*_c), complex(-_c,5*_c), complex(-_c,7*_c),
//            complex(-5*_c,3*_c), complex(-5*_c,_c), complex(-7*_c,3*_c), complex(-7*_c,_c),
//            complex(-5*_c,5*_c), complex(-5*_c,7*_c), complex(-7*_c,5*_c), complex(-7*_c,7*_c),
//            complex(-3*_c,-3*_c), complex(-3*_c,-_c), complex(-_c,-3*_c), complex(-_c,-_c),
//            complex(-3*_c,-5*_c), complex(-3*_c,-7*_c), complex(-_c,-5*_c), complex(-_c,-7*_c),
//            complex(-5*_c,-3*_c), complex(-5*_c,-_c), complex(-7*_c,-3*_c), complex(-7*_c,-_c),
//            complex(-5*_c,-5*_c), complex(-5*_c,-7*_c), complex(-7*_c,-5*_c), complex(-7*_c,-7*_c)
//         )

// Pseudo random sequences
// TS 36.211 V12.2.0, section 7.2
// Pseudo-random sequences are defined by _a length-31 Gold sequence
fn pseudo_rand_seq(n_bits: u32, cinit: u32) -> u32 {
    let i: u32  = 0;
    let x1: u32 = 0;
    let n1: u8 = 0;
    let x2: u32 = 0;
    let n2: u8 = 0;

    x1 = x_1();
    x2 = x_2(cinit);
    let c: [u32; n_bits] = [0; n_bits];
    for i in 0..n_bits {
        n1 = ((x1 >> 3) ^ x1) & 0x1;
        n2 = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1;
        x1 = (x1 >> 1) | (n1 << 30);
        x2 = (x2 >> 1) | (n2 << 30);
        c[i] = n1 ^ n2;
    }
    c
}

fn x_2(cinit: u32) -> u32 {
    let x2: u32 = cinit;
    let n: u8 = 0;
    for i in 0..(Nc-31) {
        // Advance the 2nd m-sequence
        n = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1;
        x2 = (x2 >> 1) | (n << 30);
    }
    x2
}

pub fn x_1() -> u32 {
    // The first m-sequence shall be initialized with x1(0)=1,x1(n)=0,n=1,2,...,30.
    let x1: u32 = 1;
    let n: u8 = 0;
    // Advance the 1st m-sequence
    for i in 0..(Nc-31) {
        n = ((x1 >> 3)^(x1)) & 0x01;
        x1 = (x1 >> 1) | (n << 30);
    }            
    x1  //'0x54d21b24' = hex(x1)
}

fn scrambling(bits: &[u8], n_bits: u32, cinit: u32) -> &[u8] {
    // sb[i] = (_b[i] + _c[i]) mod 2
    let prs = pseudo_rand_seq(n_bits);
    let s_bits: &[u8];
    for i in 0..n_bits {
       s_bits[i] = bits[i]^prs[i]
    }
    s_bits
}

// Modulation mapper (TS 36.211 V12.2.0 7.1)
// The modulation mapper takes binary digits, 0 or 1, as input
// and produces complex-valued modulation symbols, x=I+jQ, as output
fn modulation_mapper(bits: &[u8], n_bits: u32, mod_type: ModulationType) -> ModulationSymbol {
    if let mod_type = ModulationType::MOD_TYPE_BPSK {
        // 1 bit at a time
        let sym: [ModulationSymbol; n_bits] = [ModulationSymbol{I: 0.0, Q: 0.0}; n_bits];
        for i in 0..n_bits {
            sym[i].I = bpsk_sym[bits[i]].I;
            sym[i].Q = bpsk_sym[bits[i]].Q;
        }
        sym
    }
}

fn layer_mapping() {
    // TODO
}

fn precoding() {
    // TODO
}

fn resource_element_mapping() {
    // TODO
}
        
    
    
// class PhysicalLayerModulationMapper:
//     """
    
//     """
//     def __init__(self, sbits):
//         self.sbits = sbits
//         self.nbits = len(self.sbits)
        
//     def mod_bpsk(self):
//         r = []
//         _b= self.sbits
//         # 1 bit at a time
//         r = [_bpsk[_b[i]] for i in range(self.nbits)]
//         return r
    
//     def mod_qpsk(self):
//         r = []
//         _b = self.sbits
//         # 2 bits at a time
//         r = [_qpsk[_b[i]*2 + _b[i+1]] for i in range(0, self.nbits, 2)]  
//         return r
    
//     def mod_16qam(self):
//         r = []
//         _b = self.sbits
//         # 4 bits at a time
//         r = [_16qam[_b[i]*8 + _b[i+1]*4 + _b[i+2]*2 + _b[i+3]] for i in range(0, self.nbits, 4)]  
//         return r
        
//     def mod_64qam(self):
//         r = []
//         _b = self.sbits
//         # 6 bits at a time
//         r = [_64qam[_b[i]*32 + _b[i+1]*16 + _b[i+2]*8 + _b[i+3]*4 + _b[i+4]*2 + _b[i+5]] for i in range(0, self.nbits, 4)]  
//         return r
               