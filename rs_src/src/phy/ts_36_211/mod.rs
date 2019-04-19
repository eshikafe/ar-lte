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

// Roadmap: GPU support for baseband processing

pub mod common;
pub mod scrambling;
pub mod modulation;
pub mod layer_mapping;
pub mod precoding;
pub mod re_mapping;
pub mod ofdm;


// pub fn scramble(phy_layer: &mut PhysicalLayer){
//     scrambling::run(phy_layer);
// }


// pub fn demodulate() {

// }

// pub fn modulate() {

// }

// pub fn map_layer() {
//     // TODO
// }

// pub fn precode() {
//     // TODO
// }

// pub fn re_map() {
//     // TODO
// }
        
    

               