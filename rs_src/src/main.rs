mod ar_lte_phy;

fn main() {
    //todo
    // target: src/lib.rs

    let x1 = ar_lte_phy::ts_36211::x_1();
    assert_eq!(0x54d21b24, x1);
}
