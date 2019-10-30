// ar_enb: LTE eNodeB implementation in Rust

#[allow(dead_code)]
#[allow(non_snake_case)]
#[allow(unused_variables)]
#[allow(non_upper_case_globals)]
#[allow(unused_imports)]

extern crate ngr;
use ngr::security::*;


fn main() {
    // let mut l1 = phy::PhysicalLayer::new();
    
    // println!("\nBefore\ncodeword: {:?}\nscrambled bits {:?}", l1.codeword, l1.scrambled_bits);
    // phy::scrambling::run(&mut l1);
    // println!("\nAfter\ncodeword: {:?}\nscrambled bits {:?}", l1.codeword, l1.scrambled_bits);
    let kenb: &[u8] = &[0u8; 32];
    let k: [u8; 16] = k_rrc_int_key(kenb);
    println!("{:?}", k);
}