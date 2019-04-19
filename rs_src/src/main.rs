//#[macro_use]
//extern crate lazy_static;
#[allow(dead_code)]
#[allow(non_snake_case)]
#[allow(unused_variables)]
#[allow(non_upper_case_globals)]

mod rrc;
mod pdcp;
mod phy;


fn main() {
    let mut l1 = phy::PhysicalLayer::new();
    
    println!("\nBefore\ncodeword: {:?}\nscrambled bits {:?}", l1.codeword, l1.scrambled_bits);
    phy::scrambling::run(&mut l1);
    println!("\nAfter\ncodeword: {:?}\nscrambled bits {:?}", l1.codeword, l1.scrambled_bits);

}

