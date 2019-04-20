// Copyright (c) 2018 Aigbe Research
// phy.rs - LTE/5G Physical Layer Implementation in Rust
// Compliance: 
//      3GPP TS 36.211  
//      3GPP TS 36.212 
//      3GPP TS 36.216 
//      3GPP TS 36.213 
//      3GPP TS 36.214 

// LTE
pub mod common;
pub use ts_36_211::*;
pub mod ts_36_211; // Physical channels and modulation

pub mod ts_36_212; // Multiplexing and channel coding
pub mod ts_36_213; // Physical layer for relaying operation
pub mod ts_36_214; // Physical layer procedures
pub mod ts_36_216; // Physical layer - Measurements

// 5G NR
// ts_38_211	NR - Physical channels and modulation
// ts_38_212	NR - Multiplexing and channel coding
// ts_38_213	NR - Physical layer procedures for control
// ts_38_214	NR - Physical layer procedures for data
// ts_38_215	NR - Physical layer measurements
