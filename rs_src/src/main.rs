#[macro_use]
extern crate lazy_static;

mod ngr_phy;

fn main() {

    for _i in 0..64 {
        println!("64QAM Symbol {}: (I + jQ) = {} + {}j",_i, 
        ngr_phy::ts_36211::ModSym64Qam[_i].i,
        ngr_phy::ts_36211::ModSym64Qam[_i].q);
    }
   
}


// LTE Physical Layer procedure tests
#[test]
fn test_x1() {
    let x1 = ngr_phy::ts_36211::x_1();
    //assert_eq!(x1,0x54d21b24);
    println!("x1 = 0x{:x}", x1);
}

#[test]
fn test_x2() {
    let x2 = ngr_phy::ts_36211::x_2(100);
    println!("x2 = 0x{:x}", x2);
}