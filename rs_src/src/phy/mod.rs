// Copyright (c) 2018 Aigbe Research
// phy.rs - LTE/5G Physical Layer Implementation in Rust
// Compliance: 
//      3GPP TS 36.211  
//      3GPP TS 36.212 
//      3GPP TS 36.216 
//      3GPP TS 36.213 
//      3GPP TS 36.214 

// LTE
pub mod ts36211; // Physical channels and modulation
pub use ts36211::common::*;
pub use ts36211::scrambling;
pub use ts36211::modulation;
pub use ts36211::layer_mapping;
pub use ts36211::precoding;
pub use ts36211::re_mapping;
pub use ts36211::ofdm;

pub mod ts36212; // Multiplexing and channel coding
pub mod ts36213; // Physical layer for relaying operation
pub mod ts36214; // Physical layer procedures
pub mod ts36216; // Physical layer - Measurements

// 5G NR

