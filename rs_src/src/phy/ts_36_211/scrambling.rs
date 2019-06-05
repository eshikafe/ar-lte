//   Copyright (c) 2019 Aigbe Research
//   scrambling.rs
//   TS 36.211: Physical channels and modulation 

// scrambling of coded bits in each of the codewords to be transmitted on a physical channel


#[allow(dead_code)]
#[allow(non_snake_case)]
#[allow(unused_variables)]
#[allow(non_upper_case_globals)]

use crate::phy::*;

pub fn run(phy_layer: &mut PhysicalLayer) {
    match phy_layer.channel_type {
        PhysicalChannel::PUSCH => scramble_pusch(phy_layer),
        PhysicalChannel::PUCCH => scramble_pucch(phy_layer),
        PhysicalChannel::PBCH => scramble_pbch(phy_layer),
        PhysicalChannel::PCFICH => scramble_pcfich(phy_layer),
        PhysicalChannel::PDCCH => scramble_pdcch(phy_layer), 
        _ => println!("scrambling not implemented"),
    }
}

// Generates pseudo random sequence
// TS 36.211 V12.2.0, section 7.2
// Pseudo-random sequences are defined by _a length-31 Gold sequence

fn generate_prs(Mpn: usize, c_init: u32) -> Vec<u32> {
    let mut x1: Vec<u32> = vec![0; Mpn + Nc as usize + 31];
    let mut x2: Vec<u32> = vec![0; Mpn + Nc as usize + 31];
    let mut c = vec![0; Mpn];
    let n: usize = 0;
    
    // Convert c_init to block of bits and initialize
    // x2 with the first 31 bits of c_init 
    for n in 0 ..= 30 {
        x2[n] = (c_init >> n) & 0x1;
    }
    
    x1[0] = 1;

    for n in 0 .. Nc as usize + Mpn {
        x1[n+31] = (x1[n+3] + x1[n]) & 0x1;
        x2[n+31] = (x2[n+3] + x2[n+2] + x2[n+1] + x2[n]) & 0x1;
    }

    for n in 0 .. Mpn {
        c[n] = (x1[n+Nc as usize] + x2[n+Nc as usize]) & 0x1;
    }
    return c;
}

// 5.3.1 Scrambling of the Physical Uplink Shared Channel (PUSCH)
// Input: codeword
// Output: a block of scrambled bits
fn scramble_pusch(phy_layer: &mut PhysicalLayer) {
    let mut i: usize = 0;
    let Mbit = phy_layer.codeword.len();

    // Initialize the scrambling sequence generator
    // c_init = n_RNTI ⋅ 2^14 + q ⋅ 2^13 + [n_s/2] ⋅ 2^9 + N_cell_id at the start of each subframe
    let c_init = 1; //(n_rnti << 14) | (0 << 13) | ((n_s >> 1) << 9) | N_cell_id;
    let c: Vec<u32> = generate_prs(Mbit, c_init);
    let x = 0;
    let y = 0;
    // Scrambling algorithm for PUSCH
    while i < Mbit {
        if phy_layer.codeword[i] == x { // ACK/NACK or Rank Indication placeholder bits 
            phy_layer.scrambled_bits[i] = 0;
        } else {
            if phy_layer.codeword[i] == y {  // ACK/NACK or Rank Indication repetition placeholder bits 
                phy_layer.scrambled_bits[i] = phy_layer.scrambled_bits[i-1];
            } else { // Data or channel quality coded bits, Rank Indication coded bits or ACK/NACK coded bits 
                phy_layer.scrambled_bits[i] = (phy_layer.codeword[i] + c[i]) & 01;
            }
        }
        i = i + 1;
    }
}

fn scramble_pucch(phy_layer: &mut PhysicalLayer) {
    // TODO
}

// 6.6.1 PBCH Scrambling
fn scramble_pbch(phy_layer: &mut PhysicalLayer) {
    let c_init: u32 = phy_layer.radio_frame.N_cell_id;
    let Mbit = phy_layer.codeword.len(); // 1920
    let i: usize = 0;
    let c: Vec<u32> = generate_prs(Mbit, c_init);
    println!("pseudo random sequence = {:?}", c);

    // _b[i] = (b[i]+c[i])mod2
    for i in 0 .. Mbit {
        phy_layer.scrambled_bits[i] = (phy_layer.codeword[i] + c[i]) & 0x1;
    }
}

fn scramble_pcfich(phy_layer: &mut PhysicalLayer) {
    // TODO
}

fn scramble_pdcch(phy_layer: &mut PhysicalLayer) {
    // TODO
}
