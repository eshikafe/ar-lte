# pyLTE
LTE Test Bed Platform

**This is a work in progress!**

This test bed is based on LTE Release 12 (version 12.2.0).
It implements the LTE physical layer, MAC layer and RRC layer in Python.

Conforms with the following 3GPP Specifications:
- TS 36.211 - Physical layer channel modulation
- TS 36.212 - Multiplexing and channel coding
- TS 36.213 - Physical layer procedures
- TS 36.214 - Physical layer measurements
- TS 36.216 - Physical layer relaying operation
- TS 36.321 - MAC protocol
- TS 36.331 - RRC protocol
- TS 36.323 - PDCP protocol

ITU:
- X.680 - ASN1
- X.691 - ASN1 PER encoding

RFC:
- RFC 3095 - RoHC (Robust Header Compression)

Use cases:
- Spectrum refarming research.
- USSD over LTE testing.
- UE compliance testing. 
- 4G communication lab for Universities and research Labs. 
- Low cost eNodeB implementation (1.3L slim PC DH170 + USRP B210).
- LTE security research. 
- Embedded IOT research.
- RaspberryPi, USRP, OpenCellular
- erlEPC (https://github.com/eshikafe/erlEPC)
- Cloud RAN
- mmWave Research

**Architecture**
<img src='https://github.com/eshikafe/pyLTE/blob/master/pyLTE-arch-02.png' alt='pyLTE Architecture' title='pyLTE Architecture' />
