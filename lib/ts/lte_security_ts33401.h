/* lte_security_ts33401.h

 3GPP System Architecture Evolution (SAE); Security architecture
 Compliance: 3GPP TS 33.401 version 12.13.0 Release 12
 
 Copyright (c) 2017 Aigbe Research
*/

#include <stdint.h>
#include "hmac_sha256.h"

/* Table A.7-1: Algorithm type distinguishers */
#define NAS_enc_alg 0x01
#define NAS_int_alg 0x02
#define RRC_enc_alg 0x03
#define RRC_int_alg 0x04
#define UP_enc_alg  0x05
#define UP_int_alg  0x06

/* 5.1.3.1 Ciphering requirements 
UEs and eNBs shall implement EEA0, 128-EEA1 and 128-EEA2 for both RRC signalling ciphering and UP ciphering.
UEs and eNBs may implement 128-EEA3 for both RRC signalling ciphering and UP ciphering.

UEs and MMEs shall implement EEA0, 128-EEA1 and 128-EEA2 for NAS signalling ciphering. 
UEs and MMEs may implement 128-EEA3 for NAS signalling ciphering.

5.1.3.2 Algorithm Identifier Values 
*/

enum eps_encryption_algorithm_id {
    ID_EEA0     = 0, /* Null ciphering algorithm */
    ID_128_EEA1 = 1, /* SNOW 3G based algorithm */
    ID_128_EEA2 = 2, /* AES based algorithm */
    ID_128_EEA3 = 3  /* ZUC based algorithm */
};

/* 5.1.4.1 Integrity requirements
# UEs and eNBs shall implement 128-EIA1 and 128-EIA2 for RRC signalling integrity protection. 
# UEs and eNBs may implement 128-EIA3 for RRC signalling integrity protection.
# UEs shall implement EIA0 for integrity protection of NAS and RRC signalling. As specified in clause 5.1.4.1 of this
#   specification, EIA0 is only allowed for unauthenticated emergency calls. 
#   EIA0 shall not be used for integrity protection between RN and DeNB.
#   
# Implementation of EIA0 in MMEs, RNs and eNBs is optional, 
# EIA0, if implemented, shall be disabled in MMEs, RNs and eNBs in the deployments where support of unauthenticated emergency calling is not a regulatory requirement. 
*/
enum eps_integrity_algorithm_id {
    ID_EIA0     = 0, /* Null Integrity Protection algorithm */
    ID_128_EIA1 = 1, /* SNOW 3G based algorithm */
    ID_128_EIA2 = 2, /* AES based algorithm */
    ID_128_EIA3 = 3 /* ZUC based algorithm */
};

/* Key Derivation Function

A.2 KASME derivation function
*/ 



static void trunc_kdf(uint8_t *key_256, uint8_t *key_128);

/*
6.2 

Keys for RRC traffic:
K_RRC_int is a key, which shall only be used for the protection of RRC traffic with a particular integrity
algorithm. KRRCint is derived by ME and eNB from KeNB, as well as an identifier for the integrity algorithm
using the KDF as specified in clause A.7.
*/
void generate_rrc_integrity_key(uint8_t *K_eNB, 
                                enum eps_integrity_algorithm_id int_algo_id, 
                                uint8_t *K_RRC_int );

/*
K_RRC_enc is a key, which shall only be used for the protection of RRC traffic with a particular encryption
algorithm. KRRCenc is derived by ME and eNB from KeNB as well as an identifier for the encryption algorithm
using the KDF as specified in clause A.7. 
 */
void generate_rrc_encryption_key(uint8_t *K_eNB, 
                                 enum eps_encryption_algorithm_id algo_id, 
                                 uint8_t *K_RRC_enc );


/*
Keys for UP traffic:
KUPenc is a key, which shall only be used for the protection of UP traffic with a particular encryption algorithm.
This key is derived by ME and eNB from KeNB, as well as an identifier for the encryption algorithm using the
KDF as specified in clause A.7.
*/
void generate_user_plane_encryption_key(uint8_t *K_eNB, 
                                        enum eps_encryption_algorithm_id algo_id, 
                                        uint8_t *K_UP_enc);

/*
KUPint is a key, which shall only be used for the protection of UP traffic between RN and DeNB with a
particular integrity algorithm. This key is derived by RN and DeNB from KeNB, as well as an identifier for the
integrity algorithm using the KDF as specified in clause A.7. 
 */
void generate_user_plane_integrity_key(uint8_t *K_eNB, 
                                       enum eps_integrity_algorithm_id algo_id,
                                       uint8_t *K_RRC_int );


/*
 Intermediate keys:
- NH is a key derived by ME and MME to provide forward security as described in clause 7.2.8.

- KeNB* is a key derived by ME and eNB when performing an horizontal or vertical key derivation as specified in
clause 7.2.8 using a KDF as specified in clause A5. 

 */

