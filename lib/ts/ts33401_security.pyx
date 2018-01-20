# ts33401_security.py
#
# 3GPP System Architecture Evolution (SAE); Security architecture
# Compliance: 3GPP TS 33.401 version 12.13.0 Release 12) 
# 
# Copyright (c) 2017 Aigbe Research

from libc.stdint cimport *

# 5.1.3.1 Ciphering requirements 
# UEs and eNBs shall implement EEA0, 128-EEA1 and 128-EEA2 for both RRC signalling ciphering and UP ciphering.
# UEs and eNBs may implement 128-EEA3 for both RRC signalling ciphering and UP ciphering.
 
cdef enum:
    CIPHERING_EEA0     = 0b0000 # Null ciphering algorithm
    CIPHERING_128_EEA1 = 0b0001 # SNOW 3G based algorithm
    CIPHERING_128_EEA2 = 0b0010 # AES based algorithm
    CIPHERING_128_EEA3 = 0b0011 # ZUC based algorithm

# 5.1.4.1 Integrity requirements
# UEs and eNBs shall implement 128-EIA1 and 128-EIA2 for RRC signalling integrity protection. 
# UEs and eNBs may implement 128-EIA3 for RRC signalling integrity protection.
# UEs shall implement EIA0 for integrity protection of NAS and RRC signalling. As specified in clause 5.1.4.1 of this
#   specification, EIA0 is only allowed for unauthenticated emergency calls. 
#   EIA0 shall not be used for integrity protection between RN and DeNB.
#   
# Implementation of EIA0 in MMEs, RNs and eNBs is optional, 
# EIA0, if implemented, shall be disabled in MMEs, RNs and eNBs in the deployments where support of unauthenticated emergency calling is not a regulatory requirement. 
 
cdef enum:
    INTEGRITY_EIA0     = 0b0000
    INTEGRITY_128_EIA1 = 0b0001
    INTEGRITY_128_EIA2 = 0b0010
    INTEGRITY_128_EIA3 = 0b0011

# Key Derivation FUnctions

# A.2 KASME derivation function 
cdef kasme_kdf(CK, IK, SQN, AK, uint16_t MCC, uint16_t MNC):
    FC = 0x10
    SN_ID = (MCC >> 8) | (MCC & 0x0F00) | 

    P0 = SN_ID
    L0 = len(SN_ID)
    P1 = SQN ^ AK
    L1 = len(P1)



