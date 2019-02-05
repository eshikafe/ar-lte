#[macro_use]
extern crate lazy_static;

mod phy_layer;

fn main() {
   println!("BPSK Symbol (I + jQ) = {} + j{}", phy_layer::ts_36211::BPSK_SYMBOL[0].i,
                     phy_layer::ts_36211::BPSK_SYMBOL[0].q);
}


// LTE Physical Layer procedure tests
#[test]
fn test_x1() {
    let x1 = phy_layer::ts_36211::x_1();
    //assert_eq!(x1,0x54d21b24);
    println!("x1 = 0x{:x}", x1);
}

#[test]
fn test_x2() {
    let x2 = phy_layer::ts_36211::x_2(100);
    println!("x2 = 0x{:x}", x2);
}