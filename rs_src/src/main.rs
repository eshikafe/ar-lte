mod ts_36211;

fn main() {
    //todo
    // target: src/lib.rs

    let x1 = ts_36211::x_1();
    println!(" x_1() => 0x{:x}, expects: 0x54d21b24; Result:{}", x1, x1 ==0x54d21b24);
}
