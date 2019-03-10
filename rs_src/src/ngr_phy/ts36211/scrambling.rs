use super::common::*;

pub fn scramble(bits: Vec<u8>, n_bits: usize, cinit: u32) -> Vec<u8> {
    // sb[i] = (_b[i] + *C[i]) mod 2
    let prs = pseudo_rand_seq(n_bits, cinit);
    let s_bits: Vec<u8> = Vec::new();
    for i in 0..n_bits {
       s_bits.push(bits[i] ^ prs[i]);
    }
    s_bits
}

fn x_2(cinit: u32) -> u32 {
    let mut x2: u32 = cinit;
    let mut n: u32 = 0;
    for _i in 0..(NC-31) {
        // Advance the 2nd m-sequence
        n = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1;
        x2 = (x2 >> 1) | (n << 30);
    }
    x2
}

fn x_1() -> u32 {
    // The first m-sequence shall be initialized with x1(0)=1,x1(n)=0,n=1,2,...,30.
    let mut x1: u32 = 1;
    let mut n: u32 = 0;
    // Advance the 1st m-sequence
    for i in 0..(NC-31) {
        n = ((x1 >> 3)^(x1)) & 0x01;
        x1 = (x1 >> 1) | (n << 30);
    }            
    x1  //'0x54d21b24' = hex(x1)
}


// Generates pseudo random sequence
// TS 36.211 V12.2.0, section 7.2
// Pseudo-random sequences are defined by _a length-31 Gold sequence
fn pseudo_rand_seq(len: usize, c_init: u32) -> Vec<u32> {
    let mut x1: u32 = 0;
    let mut n1: u32 = 0;
    let mut x2: u32 = 0;
    let mut n2: u32 = 0;
    let i: usize = 0;

    x1 = x_1();
    x2 = x_2(c_init);
    let mut c = vec![0; len];
    for _i in 0..len {
        n1 = ((x1 >> 3) ^ x1) & 0x1;
        n2 = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1;
        x1 = (x1 >> 1) | (n1 << 30);
        x2 = (x2 >> 1) | (n2 << 30);
        c.push(n1 ^ n2);
    }
    c
}