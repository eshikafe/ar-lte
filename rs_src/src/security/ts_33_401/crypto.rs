// Copyright (c) 2018 Aigbe Research
//
// Compliance: 
//    3GPP TS 33.401 version 12.13.0 Release 12
//    3GPP TS 33.220 V12.3.0
//    3GPP TS 35.215 V15.0.0 (2018-06)


// Table A.7-1: Algorithm type distinguishers
pub const ALGO_TYPE_NAS_ENC: u8 = 1;
pub const ALGO_TYPE_NAS_INT: u8 = 2;
pub const ALGO_TYPE_RRC_ENC: u8 = 3;
pub const ALGO_TYPE_RRC_INT: u8 = 4;
pub const ALGO_TYPE_UP_ENC: u8 = 5;
pub const ALGO_TYPE_UP_INT: u8 = 6;

// 5.1.4.1 Integrity requirements
// EPS Integrity Algorithm Identity
pub const ALGO_ID_EIA0: u8 = 0;     // Null Integrity Protection algorithm
pub const ALGO_ID_128_EIA1: u8 = 1; // SNOW 3G based algorithm
pub const ALGO_ID_128_EIA2: u8 = 2; // AES based algorithm
pub const ALGO_ID_128_EIA3: u8 = 3; // ZUC based algorithm

// 5.1.3.2 Algorithm Identifier Values 
// EPS Encryption Algorithm Identity
pub const ALGO_ID_EEA0: u8 = 0; 
pub const ALGO_ID_128_EEA1: u8 = 1;
pub const ALGO_ID_128_EEA2: u8 = 2;
pub const ALGO_ID_128_EEA3: u8 = 3;


// Use the sha256() hash function to compute a hmac code with the hmac() function
// fn hmac_sha256(Key: Vec<128>, Data) -> Vec<u128> {
// 	crypto:hmac(sha256, Key, Data, 16)
// }

// Key Derivation Function (KDF)
// Inputs: k_enb (256 bits), algo_type (8 bits), algo_id (8 bits)
// Output keys (128 bits): KRRCint, KRRCenc, KUPint or KUPenc
pub fn kdf(k_enb: Vec<u128>, algo_type: u8, algo_id: u8) -> u64 {
	let fc: u64 = 15; 
	let p0: u64 = algo_type as u64;  // algorithm type distinguisher
	let l0: u64 = 1;     // length of algorithm type distinguisher (i.e 0x00 0x01)
	let p1: u64 = algo_id as u64;    // algorithm identity
	let l1: u64 = 1;     // length of algorithm identity (i.e. 0x00 0x01)

    // S = FC || P0 || L0 || P1 || L1 || P2 || L2 || P3 || L3 ||... || Pn || Ln */
    let s: u64 = (fc << 56 | p0 << 48 | l0 << 32 | p1 << 24 | l1 << 8) & 0xffffffffffffff00; 
    //hmac_sha256(k_enb, s)
    return s;
}

// % ciphering algorithm
// %  used by the PDCP layer to encrypt the data part of the PDCP PDU
// %  Key: 128 bits
// %  Count: 32 bits
// %  Bearer: 5 bits
// %  Direction: 1 bit (0 - uplink, 1 - downlink)
// %  Length: length(Msg)
// fn eea2_128_encrypt(Key: u128, Count: u32, Bearer: u8, Direction: u8, Length: u32, Data: Vec<u8>) -> u128 {
// 	crypto:block_encrypt(ecb_aes, KeyStream, Data)
// }
// fn eia2_128_int(Key, Count, Bearer, Direction, Length, Data) -> u128 {
// 	//todo.
// }




