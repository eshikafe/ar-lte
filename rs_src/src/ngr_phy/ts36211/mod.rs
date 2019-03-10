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

mod common;
mod scrambling;
mod modulation;
mod layer_mapping;
mod precoding;
mod re_mapping;
mod ofdm_signal_gen;


pub fn scramble(bits: Vec<u8>, num_bits: usize) -> Vec<u8>{
    let cinit: u32 = 100;
    scrambling::scramble(bits, num_bits, cinit)
}


pub fn demodulate() {

}

pub fn modulate() {

}

pub fn map_layer() {
    // TODO
}

pub fn precode() {
    // TODO
}

pub fn re_map() {
    // TODO
}
        
    

               