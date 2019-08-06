//   Copyright (c) 2019 Aigbe Research
//   modulation.rs
//   TS 36.211: Physical channels and modulation

//   0, 1  => x=I+jQ

// use super::common::IQ;

// const A_: f64 = 1.0/2.0_f64.sqrt();
// const B: f64 = 1.0/10.0_f64.sqrt();
// const C: f64 = 1.0/42.0_f64.sqrt();

// BPSK - TS 36.211 V12.2.0, section 7.1.1, Table 7.1.1-1
// ModSymBpsk: [IQ; 2] = [IQ{i: *A, q: *A}, IQ{i: -*A, q: -*A}];

//     // QPSK - TS 36.211 V12.2.0, section 7.1.2, Table 7.1.2-1
//     pub static ref ModSymQpsk: [IQ; 4]  = [
//         IQ{i: *A, q: *A}, IQ{i: *A, q: -*A},
//         IQ{i: -*A, q: *A},IQ{i: -*A, q: -*A}
//     ];

//     //16QAM - TS 36.211 V12.2.0, section 7.1.3, Table 7.1.3-1
//     pub static ref ModSym16Qam: [IQ; 16] = [
//         IQ{i: *B, q: *B}, IQ{i: *B, q: *B*3.0},
//         IQ{i: *B*3.0, q: *B}, IQ{i: *B*3.0, q: *B*3.0},
//         IQ{i: *B, q: -*B}, IQ{i: *B, q: *B*-3.0},
//         IQ{i: *B, q: *B}, IQ{i: *B*3.0, q: *B*-3.0},
//         IQ{i: -*B, q: *B},IQ{i: -*B, q: *B*3.0},
//         IQ{i: *B*3.0, q: *B}, IQ{i: *B*-3.0, q: *B*3.0},
//         IQ{i: -*B, q: -*B}, IQ{i: -*B, q: *B*-3.0},
//         IQ{i: *B*-3.0, q: -*B},IQ{i: *B*-3.0, q: *B*-3.0}
//     ];

//     // 64QAM - TS 36.211 V12.2.0, section 7.1.4, Table 7.1.4-1
//     pub static ref ModSym64Qam: [IQ; 64] = [
//         IQ{i: *C*3.0, q: *C*3.0}, IQ{i: 3.0**C, q: *C}, IQ{i: *C, q: 3.0**C}, IQ{i: *C, q: *C},
//            IQ{i: 3.0**C, q: 5.0**C}, IQ{i: 3.0**C, q: 7.0**C}, IQ{i: *C, q: 5.0**C}, IQ{i: *C, q: 7.0**C},
//            IQ{i: 5.0**C, q: 3.0**C}, IQ{i: 5.0**C, q: *C}, IQ{i: 7.0**C, q: 3.0**C}, IQ{i: 7.0**C, q: *C},
//            IQ{i: 5.0**C, q: 5.0**C}, IQ{i: 5.0**C, q: 7.0**C}, IQ{i: 7.0**C, q: 5.0**C}, IQ{i: 7.0**C, q: 7.0**C},
//            IQ{i: 3.0**C, q: -3.0**C}, IQ{i: 3.0**C, q: -*C}, IQ{i: *C, q: -3.0**C}, IQ{i: *C, q: -*C},
//            IQ{i: 3.0**C, q: -5.0**C}, IQ{i: 3.0**C, q: -7.0**C}, IQ{i: *C, q: -5.0**C}, IQ{i: *C, q: -7.0**C},
//            IQ{i: 5.0**C, q: -3.0**C}, IQ{i: 5.0**C, q: -*C}, IQ{i: 7.0**C, q: -3.0**C}, IQ{i: 7.0**C, q: -*C},
//            IQ{i: 5.0**C, q: -5.0**C}, IQ{i: 5.0**C, q: -7.0**C}, IQ{i: 7.0**C, q: -5.0**C}, IQ{i: 7.0**C, q: -7.0**C},
//            IQ{i: 3.0**C, q: 3.0**C}, IQ{i: -3.0**C, q: *C}, IQ{i: -*C, q: 3.0**C}, IQ{i: -*C, q: *C},
//            IQ{i: -3.0**C, q: 5.0**C}, IQ{i: -3.0**C, q: 7.0**C}, IQ{i: -*C, q: 5.0**C}, IQ{i: -*C, q: 7.0**C},
//            IQ{i: -5.0**C, q: 3.0**C}, IQ{i: -5.0**C, q: *C}, IQ{i: -7.0**C, q: 3.0**C}, IQ{i: -7.0**C, q: *C},
//            IQ{i: -5.0**C, q: 5.0**C}, IQ{i: -5.0**C, q: 7.0**C}, IQ{i: -7.0**C, q: 5.0**C}, IQ{i: -7.0**C, q: 7.0**C},
//            IQ{i: -3.0**C, q: -3.0**C}, IQ{i: -3.0**C, q: -*C}, IQ{i: -*C, q: -3.0**C}, IQ{i: -*C, q: -*C},
//            IQ{i: -3.0**C, q: -5.0**C}, IQ{i: -3.0**C, q: -7.0**C}, IQ{i: -*C, q: -5.0**C}, IQ{i: -*C, q: -7.0**C},
//            IQ{i: -5.0**C, q: -3.0**C}, IQ{i: -5.0**C, q: -*C}, IQ{i: -7.0**C, q: -3.0**C}, IQ{i: -7.0**C, q: -*C},
//            IQ{i: -5.0**C, q: -5.0**C}, IQ{i: -5.0**C, q: -7.0**C}, IQ{i: -7.0**C, q: -5.0**C}, IQ{i: -7.0**C, q: -7.0**C}
//     ];
// }

// Modulation mapper (TS 36.211 V12.2.0 7.1)
// The modulation mapper takes binary digits, 0 or 1, as input
// and produces complex-valued modulation symbols, x=I+jQ, as output
// fn modulation_mapper(bits: &[u8], n_bits: usize, mod_type: ModulationType) {

//     match mod_type {
//         ModulationType::ModTypeBPSK => {
//             // 1 bit at a time
//             let mod_symbol = vec![IQ{i: 0.0, q: 0.0}; n_bits];
//             for i in 0..n_bits {
//                 mod_symbol[i].I = BPSK_SYMBOL[bits[i]].i;
//                 mod_symbol[i].Q = BPSK_SYMBOL[bits[i]].q;
//                 println!("{},{}", mod_symbol[i].i, mod_symbol[i].q)
//             }
//         }

//         ModulationType::ModTypeQPSK => println!("QPSK"),
//         ModulationType::ModType16QAM => println!("16QAM"),
//         ModulationType::ModType64QAM => println!("64QAM"),

//     }

// }

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
