// scrambling of coded bits in each of the codewords to be transmitted on a physical channel

use super::common::*;

pub fn scramble(phy_layer: &PhysicalLayer, c_init: u32) {
    match phy_layer.channel_type {
        PhysicalChannel::PUSCH => scramble_pusch(&phy_layer),
        PhysicalChannel::PUCCH => scramble_pucch(&phy_layer),
        PhysicalChannel::PBCH => scramble_pbch(&phy_layer),
        PhysicalChannel::PCFICH => scramble_pcfich(&phy_layer),
        PhysicalChannel::PDCCH => scramble_pdcch(&phy_layer), 
        _ => println!("scrambling not implemented"),
    }
}

// Generates pseudo random sequence
// TS 36.211 V12.2.0, section 7.2
// Pseudo-random sequences are defined by _a length-31 Gold sequence
// Adapted from srsLTE: srsLTE/lib/src/phy/common/sequence.c
//              OpenLTE liblte_phy.cc
fn generate_prs(M_pn: usize, c_init: u32) -> Vec<u32> {
    let mut x1: Vec<u32> = vec![0; M_pn + Nc as usize + 31];
    let mut x2: Vec<u32> = vec![0; M_pn + Nc as usize + 31];
    let mut c = vec![0; M_pn];
    let mut n: usize = 0;

    for n in 0 ..= 30 {
        x2[n] = (c_init >> n) & 0x1;
    }
    
    x1[0] = 1;

    for n in 0 .. Nc as usize + M_pn {
        x1[n+31] = (x1[n+3] + x1[n]) & 0x1;
        x2[n+31] = (x2[n+3] + x2[n+2] + x2[n+1] + x2[n]) & 0x1;
    }

    for n in 0 .. M_pn {
        c[n] = (x1[n+Nc as usize] + x2[n+Nc as usize]) & 0x1;
    }
    return c;
}

// 5.3.1 Scrambling of the Physical uplink shared channel
fn scramble_pusch(phy_layer: &PhysicalLayer) {
    let i: usize = 0;
    let Mbit = phy_layer.codeword_q.len();

    while i < Mbit {
        if phy_layer.codeword_q
    }
}

fn scramble_pucch(phy_layer: &PhysicalLayer) {
    // TODO
}

// 6.6.1 PBCH Scrambling
fn scramble_pbch(phy_layer: &PhysicalLayer) {
    let c_init: u32 = phy_layer.radio_frame.N_cell_id;
    let Mbit = phy_layer.codeword_q.len(); // 1920
    let i: usize = 0;
    let c: Vec<u32> = generate_prs(Mbit, c_init);

    // _b[i] = (b[i]+c[i])mod2
    for i in 0 .. Mbit {
        phy_layer.scrambled_bits.push((phy_layer.codeword_q[i] + c[i]) & 0x1);
    }
}

fn scramble_pcfich(phy_layer: &PhysicalLayer) {
    // TODO
}

fn scramble_pdcch(phy_layer: &PhysicalLayer) {
    // TODO
}
