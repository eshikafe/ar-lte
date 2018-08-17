/*
	Copyright (c) 2018 Aigbe Research

	hmac_sha256 uses the SHA256 hash function to 
    compute a hash-based Message Authentication Code (HMAC).

References:
    https://en.wikipedia.org/wiki/SHA-2
    https://csrc.nist.gov/csrc/media/publications/fips/198/1/final/documents/fips-198-1_final.pdf

 */


#include "hmac_sha256.h"
#include <stdint.h>


/* SHA256 */
static void sha256(unit8_t *msg, size_t l)
{

	/* 
	Initialize hash values:
       The initial hash value H(0) is the following sequence of 32-bit words (which are
       obtained by taking the fractional parts of the square roots of the first eight primes: 2,3,5,7,11,13,17 and 19):
    */
	uint32_t h[8] = {
		0x6a09e667, /* h0 */
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19  /* h7 */
	};

	/* Initialize array of round constants:
	     These are the first 32 bits of the fractional parts of the cube roots of the first 64 primes.
	*/

	uint32_t k[64] = {
	   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

   /*
   		Pre-processing (Padding): 
   		pad the message in such away that the result is a multiple of 512 bits long
		Suppose the length of the message M, in bits, is L. 
		Append the bit "1" to the end of the message.
		Append k zero bits, where k is the smallest non-negative solution to the equation L+1+k = 448 mod 512. 
		append K '0' bits, where K is the minimum number >= 0 such that L + 1 + K + 64 is a multiple of 512
		To this append the 64-bit block which is equal to the number L written in binarys
    */

}


/* HMAC */
static void hmac(unit8_t *K, uint8_t data) {
/*
       HMAC

       To compute a MAC over the data ‘text’ using the HMAC function, the following operation is performed:
			MAC(text) = HMAC(K, text) = H((K0 ⊕ opad )|| H((K0 ⊕ ipad) || text))

		Table 1: The HMAC Algorithm
        STEP-BY-STEP DESCRIPTION
	Step 1 If the length of K = B: set K0 = K. Go to step 4.
	Step 2 If the length of K > B: hash K to obtain an L byte string, then append (B-L)
			zeros to create a B-byte string K0 (i.e., K0 = H(K) || 00...00). Go to step 4.
	Step 3 If the length of K < B: append zeros to the end of K to create a B-byte string K0
			(e.g., if K is 20 bytes in length and B = 64, then K will be appended with 44 zero bytes x’00’).
	Step 4 Exclusive-Or K0 with ipad to produce a B-byte string: K0 ⊕ ipad.
	Step 5 Append the stream of data 'text' to the string resulting from step 4:
			(K0 ⊕ ipad) || text.
	Step 6 Apply H to the stream generated in step 5: H((K0 ⊕ ipad) || text).
	Step 7 Exclusive-Or K0 with opad: K0 ⊕ opad.
	Step 8 Append the result from step 6 to step 7:
			(K0 ⊕ opad) || H((K0 ⊕ ipad) || text).
	Step 9 Apply H to the result from step 8:
			H((K0 ⊕ opad )|| H((K0 ⊕ ipad) || text)).
    */
   

}


/* HMAC-SHA256 */
void hmac_sha256()
{
	/*
		Use the sha256() hash function to compute a hmac code with the hmac() function
 	*/
 
}