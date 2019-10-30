//   Copyright (c) 2019 AR
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

pub mod layer_mapping;
pub mod modulation;
pub mod ofdm;
pub mod precoding;
pub mod re_mapping;
pub mod scrambling;

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
