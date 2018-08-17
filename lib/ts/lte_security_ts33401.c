#include "lte_security_ts33401.h"
#include <stdio.h>

void main()
{
	uint8_t i = 2;
	uint8_t *k_rrc_int;
	uint8_t *k_enb;

	*k_enb = 0x05;
	k_rrc_int = &i;

	
	generate_rrc_integrity_key(k_enb, ID_128_EIA2, k_rrc_int);

	printf("k_rrc_int[0] 0x%x\n", k_rrc_int[0]);
	printf("k_rrc_int[1] %d\n", k_rrc_int[1]);
	printf("k_rrc_int[2] 0x%x\n", k_rrc_int[2]);
	printf("k_rrc_int[3] 0x%x\n", k_rrc_int[3]);
	printf("k_rrc_int[6] 0x%x\n", k_rrc_int[6]);
	
}


/* TS 33.401: A.7 Algorithm key derivation functions

  TS 33.220: B.2 Generic key derivation function 
   FC - single octet used to distinguish between different instances of the algorithm
   P0 ... Pn are the n+1 input parameter encodings
   L0 ... Ln are the two-octet representations of the length of the corresponding input parameter encodings P0..Pn. 

   The final output, i.e. the derived key is equal to the KDF computed on the string S using the key, denoted Key.
   The present document defines the following KDF:
       derived key = HMAC-SHA-256 ( Key , S )
     as specified in [22] and [23]

*/

void generate_rrc_integrity_key(uint8_t *K_eNB, 
	                            enum eps_integrity_algorithm_id algo_id, 
	                            uint8_t *K_RRC_int )
{
	uint8_t FC = 0x15; 
	uint8_t P0 = RRC_int_alg;   /* algorithm type distinguisher */
	uint16_t L0 = 0x0001;       /* length of algorithm type distinguisher (i.e 0x00 0x01) */
	uint8_t P1= algo_id;        /* algorithm identity */
	uint16_t L1 = 0x0001;       /* length of algorithm identity (i.e. 0x00 0x01) */

    /* S = FC || P0 || L0 || P1 || L1 || P2 || L2 || P3 || L3 ||... || Pn || Ln */
    uint8_t S[7] = {FC, P0, L0>>2, L0, P1, L1>>2, L1}; 
	

    //*K_RRC_int = FC;
	K_RRC_int = hmac_sha256(K_eNB, S);
	printf("K_RRC_int[0] 0x%x\n", K_RRC_int[0]);
	printf("K_RRC_int[1] %d\n", K_RRC_int[1]);
	printf("K_RRC_int[2] 0x%x\n", K_RRC_int[2]);
	printf("K_RRC_int[3] 0x%x\n", K_RRC_int[3]);
	printf("K_RRC_int[6] 0x%x\n", K_RRC_int[6]);
}

void generate_user_plane_encryption_key(uint8_t *K_eNB, 
                                        enum eps_encryption_algorithm_id algo_id, 
                                        uint8_t *K_UP_enc)
{
	uint8_t FC = 0x15; 
	uint8_t P0 = UP_enc_alg;  /* algorithm type distinguisher */
	uint16_t L0 = 0x0001;     /* length of algorithm type distinguisher (i.e 0x00 0x01) */
	uint8_t P1= algo_id;        /* algorithm identity */
	uint16_t L1 = 0x0001;     /* length of algorithm identity (i.e. 0x00 0x01) */

	uint8_t S[7] = {FC, P0, L0>>2, L0, P1, L1>>2, L1}; 

	K_UP_enc = hmac_sha256(K_eNB, S);	
}