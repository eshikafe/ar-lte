
/*
	Copyright (c) 2018 Aigbe Research

	hmac_sha256 uses the SHA256 hash function to 
    compute a hash-based Message Authentication Code (HMAC).

 */
#ifndef HMAC_SHA256_H
#define HMAC_SHA256_H

/* Sn(x) - right rotation by n bits */
#define S2(x) 	(((x & 0xffffffff) >> 2) | (x << 30))
#define S6(x)	(((x & 0xffffffff) >> 6) | (x << 26))
#define S7(x)   (((x & 0xffffffff) >> 7) | (x << 25))
#define S11(x)  (((x & 0xffffffff) >> 11) | (x << 21))
#define S13(x)  (((x & 0xffffffff) >> 13) | (x << 19))
#define S18(x)  (((x & 0xffffffff) >> 18) | (x << 14))
#define S19(x)  (((x & 0xffffffff) >> 19) | (x << 13))
#define S22(x)  (((x & 0xffffffff) >> 22) | (x << 10))
#define S25(x)  (((x & 0xffffffff) >> 25) | (x << 7))

/* Rn(x) - right shift by n bits */
#define R3(x)  ((x & 0xffffffff) >> 3)
#define R10(x) ((x & 0xffffffff) >> 10)

/*
	Six logical functions are used in SHA-256. Each of these functions operates on
	32-bit words and produces a 32-bit word as output. Each function is defined as follows:
 */
#define Ch(x, y, z)     ((x & y) ^ (~x & z))
#define Maj(x, y, z)    ((x & y) ^ (x & z) ^ (y & z))
#define SIGMA_0(x)           (S2(x) ^ S13(x) ^ S22(x))
#define SIGMA_1(x)           (S6(x) ^ S11(x) ^ S25(x))
#define sigma_0(x)           (S7(x) ^ S18(x) ^ R3(x))
#define sigma_1(x)           (S17(x) ^ S19(x) ^ R10(x))

/*
   derived key = HMAC-SHA-256 ( Key , S ) 

*/

void hmac_sha256();

static void sha256();
static void hmac();


#endif /* hmac_sha256.h */