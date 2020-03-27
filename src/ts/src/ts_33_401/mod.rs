// Copyright (c) 2018 STOBA Networks
//
// Compliance: 
//    3GPP TS 33.401 version 12.13.0 Release 12
//    3GPP TS 33.220 V12.3.0
//    3GPP TS 35.215 V15.0.0 (2018-06)

use hmac_sha256::*;

// Table A.7-1: Algorithm type distinguishers
const ALG_TYPE_RRC_ENC: u8 = 0x03;
const ALG_TYPE_RRC_INT: u8 = 0x04;
const ALG_TYPE_UP_ENC: u8 = 0x05;
const ALG_TYPE_UP_INT: u8 = 0x06;

// 5.1.4.1 Integrity requirements
// EPS Integrity Algorithm Identity
const ALGO_ID_EIA0: u8 = 0;     // Null Integrity Protection algorithm
const ALGO_ID_128_EIA1: u8 = 1; // SNOW 3G based algorithm
const ALGO_ID_128_EIA2: u8 = 2; // AES based algorithm
const ALGO_ID_128_EIA3: u8 = 3; // ZUC based algorithm

// 5.1.3.2 Algorithm Identifier Values 
// EPS Encryption Algorithm Identity
const ALGO_ID_EEA0: u8 = 0; 
const ALGO_ID_128_EEA1: u8 = 1;
const ALGO_ID_128_EEA2: u8 = 2;
const ALGO_ID_128_EEA3: u8 = 3;


fn kdf(key: &[u8], s: &[u8]) -> [u8; 32] {
    HMAC::mac(s, key) // 256 bits
 }


// A.7 Algorithm Key Derivation Functions
fn algo_kdf(k_enb: &[u8], algo_type: u8, algo_id: u8) -> [u8; 32] {
    let fc: u8 = 0x15; 
    let p0: u8 = algo_type;            // algorithm type distinguisher
    let l0: [u8;2] = [0x00, 0x01];     // length of algorithm type distinguisher (i.e 0x00 0x01)
    let p1: u8 = algo_id;              // algorithm identity
    let l1: [u8;2] = [0x00, 0x01];     // length of algorithm identity (i.e. 0x00 0x01)

    // S = FC || P0 || L0 || P1 || L1 || P2 || L2 || P3 || L3 ||... || Pn || Ln
    let s = &[fc, p0, l0[0], l0[1], p1, l1[0], l1[1]];  
    kdf(k_enb, s)
}


pub fn k_rrc_int_key(k_enb: &[u8]) -> [u8; 16] {
    let k = algo_kdf(k_enb, ALG_TYPE_RRC_INT, ALGO_ID_128_EIA2);
    let mut k_rrcint: [u8; 16] = Default::default();
    k_rrcint.clone_from_slice(&k[16..32]); // Truncate 256 bits to 128 bits
    k_rrcint 	
}

pub fn k_rrc_enc_key(k_enb: &[u8]) -> [u8; 16] {
    let k = algo_kdf(k_enb, ALG_TYPE_RRC_ENC, ALGO_ID_128_EEA2);
    let mut k_rrcenc: [u8; 16] = Default::default();
    k_rrcenc.clone_from_slice(&k[16..32]);
    k_rrcenc
} 

pub fn k_up_int_key(k_enb: &[u8]) -> [u8; 16] {
    let k = algo_kdf(k_enb, ALG_TYPE_UP_INT, ALGO_ID_128_EIA2);
    let mut k_upint: [u8; 16] = Default::default();
    k_upint.clone_from_slice(&k[16..32]); 
    k_upint
}

pub fn k_up_enc_key(k_enb: &[u8]) -> [u8; 16] {
    let k = algo_kdf(k_enb, ALG_TYPE_UP_ENC, ALGO_ID_128_EEA2);
    let mut k_upenc: [u8; 16] = Default::default();
    k_upenc.clone_from_slice(&k[16..32]);
    k_upenc
}

// B.1 128-bit ciphering algorithm 
// used by the PDCP layer to encrypt the data part of the PDCP PDU
// Input:
// 	Key: 128 bits
// 	Count: 32 bits
// 	Bearer: 5 bits
// 	Direction: 1 bit (0 - uplink, 1 - downlink)
// 	Length: length(Msg)
// Ouput:
//  KeyStream Block: Length bits
 fn eea2_128_enc(key: &[u8], count: u32, bearer: u8, direction: bool, length: u32, data: &[u8]) {
 
 }

 // Integrity
 //fn eia2_128_int(Key, Count, Bearer, Direction, Length, Data) -> u128 {
// 	//todo.
 //}//




