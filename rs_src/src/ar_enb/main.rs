// ar_enb: LTE eNodeB implementation in Rust

#[allow(dead_code)]
#[allow(non_snake_case)]
#[allow(unused_variables)]
#[allow(non_upper_case_globals)]
#[allow(unused_imports)]

extern crate ngr;

// use ngr::rrc;
// use ngr::pdcp;
// use ngr::phy;
use ngr::security::*;

fn main() {
    // let mut l1 = phy::PhysicalLayer::new();
    
    // println!("\nBefore\ncodeword: {:?}\nscrambled bits {:?}", l1.codeword, l1.scrambled_bits);
    // phy::scrambling::run(&mut l1);
    // println!("\nAfter\ncodeword: {:?}\nscrambled bits {:?}", l1.codeword, l1.scrambled_bits);

    let kenb: Vec<u128> = vec![45; 2];
    let k: u64;
    k = kdf(kenb, ALGO_TYPE_RRC_INT, ALGO_ID_128_EIA2);
    println!("k: 0x0{:x}", k);
}