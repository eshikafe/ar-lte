// Copyright (c) 2018 Aigbe Research
// ar_lte_phy.rs
// LTE Physical Layer
// Compliance: 3GPP TS 36.211

// Physical layer processing:
// 	  scrambling
// 	  modulation
// 	  layer mapping
// 	  precoding
// 	  mapping to resource elements
// 	  OFDM signal generation

// 	Input to the physical layer: codewords


const N_SYMB_DL_NORMAL_CP: u8 = 7;

fn pseudo_rand_seq() {
    // TS 36.211 V12.2.0, section 7.2
   // Pseudo-random sequences are defined by _a length-31 Gold sequence
   i:u32;
   x1:u32, n1:u32, x2:u32, n2:u32;

}
