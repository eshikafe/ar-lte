//#[macro_use]
//extern crate lazy_static;

mod ngr_phy;

fn main() {
    test_x1();
    test_x2();  
}


// LTE Physical Layer procedure tests
fn test_x1() {
    let x1 = ngr_phy::ts36211::x1();
    //assert_eq!(x1,0x54d21b24);
    println!("x1 = 0x{:x}", x1);
}

fn test_x2() {
    let x2 = ngr_phy::ts36211::x2(100);
    println!("x2 = 0x{:x}", x2);
}