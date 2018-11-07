/* 
  Copyright (c) 2015 - 2017 Aigbe Research

  lte_phy_ts36211.c
 
 TS 36.211: Physical channels and modulation 
    The scope of this specification is to establish the characteristics of the Layer-1 physical channels, 
    generation of physical layer signals and modulation, and to specify:
 		- Definition of the uplink, downlink and sidelink physical channels;
       - The structure of the physical channels, frame format, physical resource elements, etc.;
	- Modulation mapping (BPSK, QPSK, etc);
		- Physical shared channel in uplink, downlink and sidelink;
 		- Reference signals in uplink, downlink and sidelink;
		- Random access channel;
		- Primary and secondary synchronization signals;
		- Primary and secondary sidelink synchronization signals;
		- OFDM signal generation in downlink;
		- SC-FDMA signal generation in uplink and sidelink;
		- Scrambling, modulation and up conversion;
		- Uplink-downlink and sidelink timing relations;
		- Layer mapping and precoding in downlink, uplink and sidelink. 
		
		Reference: 3GPP TS 36.201 version 12.2.0 Release 12, Section 5.3
				
 Physical layer processing:
	  scrambling
	  modulation
	  layer mapping
	  precoding
	  mapping to resource elements
	  OFDM signal generation

	Input to the physical layer: codewords
  

*/

#include <math.h>
#include <stdint.h>
#include "ue_radio_tx_reception_ts36101.h"



# Frame structure (4)
cdef double Ts =  1/(15000*2048) # seconds (basic time unit)
cdef double Tf = 307200 * Ts    # 10ms duration (radio frame duration)

LTE_PHY_RADIO_FRAME_TYPE1 = "FDD"
LTE_PHY_RADIO_FRAME_TYPE2 = "TDD"

cdef enum:
  LTE_PHY_FDD_HALF_DUPLEX
  LTE_PHY_FDD_FULL_DUPLEX

# Frame structure type 1 (4.1)
# 
#   1 radio frame (Tf) = 20 slots = 10 subframes = 10ms
#   1 slot (T_slot_fdd) = 0.5ms
#   1 subframe = 2 slots = 1ms [2i and 2i+1, i = subframe]
#   
#   For FDD, DL transmission = 10 subframes, UL transmission = 10 subframes
#   in each Tf interval
cdef double T_slot = 15360 * Ts # 0.5ms (radio frame type1/type2 slot duration)

# Uplink physical channels (5.1.1)
# PUSCH
# PUCCH
# PRACH
#
# UL Physical channel:
# resource_elements
# sets of resource_elements
# Transmitted signal/slot:
#   resource grid:
#     N_UL_RB*N_RB_SC
#     num_uplink_symb (N_UL_symb)
#     N_UL_RB:
#       uplink tx bw configured in the cell
# SC-FDMA symbols in a slot depends on
# UL_CyclicPrefixLength Table 5.2.3.1
# 
#  Antenna port
#  1 resource grid per ant_port
#  num_ant_port
#  ant_port used for tx of a phy channel
#  
#  


cdef int Nc = 1600

cdef double _a = 1/sqrt(2)
cdef double _b = 1/sqrt(10)
cdef double _c = 1/sqrt(42)

# BPSK - TS 36.211 V12.2.0, section 7.1.1, Table 7.1.1-1
_bpsk = (complex(_a,_a), complex(-_a,-_a))

# QPSK - TS 36.211 V12.2.0, section 7.1.2, Table 7.1.2-1
_qpsk = (complex(_a,_a), complex(_a,-_a),complex(-_a,_a),complex(-_a,-_a))

# 16QAM - TS 36.211 V12.2.0, section 7.1.3, Table 7.1.3-1
_16qam = (complex(_b,_b), complex(_b,3*_b), complex(3*_b,_b), complex(3*_b,3*_b),
           complex(_b,-_b), complex(_b,-3*_b), complex(3*_b,-_b), complex(3*_b,-3*_b),
           complex(-_b,_b), complex(-_b,3*_b), complex(-3*_b,_b), complex(-3*_b,3*_b),
           complex(-_b,-_b), complex(-_b,-3*_b), complex(-3*_b,-_b),complex(-3*_b,-3*_b)
           )

# 64QAM - TS 36.211 V12.2.0, section 7.1.4, Table 7.1.4-1
_64qam = (complex(3*_c,3*_c), complex(3*_c,_c), complex(_c,3*_c), complex(_c,_c),
           complex(3*_c,5*_c), complex(3*_c,7*_c), complex(_c,5*_c), complex(_c,7*_c),
           complex(5*_c,3*_c), complex(5*_c,_c), complex(7*_c,3*_c), complex(7*_c,_c),
           complex(5*_c,5*_c), complex(5*_c,7*_c), complex(7*_c,5*_c), complex(7*_c,7*_c),
           complex(3*_c,-3*_c), complex(3*_c,-_c), complex(_c,-3*_c), complex(_c,-_c),
           complex(3*_c,-5*_c), complex(3*_c,-7*_c), complex(_c,-5*_c), complex(_c,-7*_c),
           complex(5*_c,-3*_c), complex(5*_c,-_c), complex(7*_c,-3*_c), complex(7*_c,-_c),
           complex(5*_c,-5*_c), complex(5*_c,-7*_c), complex(7*_c,-5*_c), complex(7*_c,-7*_c),
           complex(3*_c,3*_c), complex(-3*_c,_c), complex(-_c,3*_c), complex(-_c,_c),
           complex(-3*_c,5*_c), complex(-3*_c,7*_c), complex(-_c,5*_c), complex(-_c,7*_c),
           complex(-5*_c,3*_c), complex(-5*_c,_c), complex(-7*_c,3*_c), complex(-7*_c,_c),
           complex(-5*_c,5*_c), complex(-5*_c,7*_c), complex(-7*_c,5*_c), complex(-7*_c,7*_c),
           complex(-3*_c,-3*_c), complex(-3*_c,-_c), complex(-_c,-3*_c), complex(-_c,-_c),
           complex(-3*_c,-5*_c), complex(-3*_c,-7*_c), complex(-_c,-5*_c), complex(-_c,-7*_c),
           complex(-5*_c,-3*_c), complex(-5*_c,-_c), complex(-7*_c,-3*_c), complex(-7*_c,-_c),
           complex(-5*_c,-5*_c), complex(-5*_c,-7*_c), complex(-7*_c,-5*_c), complex(-7*_c,-7*_c)
        )

cdef class PhysicalLayerScrambling:
    cdef int cinit
    cdef int mbits
    def __init__(self, int cinit, _b):
        self.cinit = cinit
        self.mbits = len(_b)
        self._b = _b
        
    cdef scramble(self):
        # sb[i] = (_b[i] + _c[i]) mod 2
        _c = self._pseudo_random_sequence()
        sb = []
        sb = [self._b[i]^_c[i] for i in range(self.mbits)]
        return sb
    
    cdef _pseudo_random_sequence(self):
        # TS 36.211 V12.2.0, section 7.2
        # Pseudo-random sequences are defined by _a length-31 Gold sequence
        cdef int i
        cdef int x1, n1, x2, n2

        x1 = self._x1()
        x2 = self._x2()
        _c = []
        for i in range(self.mbits):
            n1 = ((x1 >> 3) ^ x1) & 0x1
            n2 = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1

            x1 = (x1 >> 1) | (n1 << 30)
            x2 = (x2 >> 1) | (n2 << 30)
            _c.append(n1 ^ n2)
        return _c
        
    cdef _x2(self):
        x2 = self.cinit
        cdef int i = 0
        for i in range(Nc-31):
            # Advance the 2nd m-sequence
            n = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1
            x2 = (x2 >> 1) | (n << 30)
        return x2
            
    cdef _x1(self):
        # The first m-sequence shall be initialized with x1(0)=1,x1(n)=0,n=1,2,...,30.
        cdef int x1=1
        cdef int i
        # Advance the 1st m-sequence
        for i in range(Nc-31):
            n = ((x1 >> 3)^(x1)) & 0x01
            x1 = (x1 >> 1) | (n << 30)
        return x1 # '0x54d21b24' = hex(x1)
        

class PhysicalLayerModulationMapper:
    """
    Modulation mapper (TS 36.211 V12.2.0 7.1)
    The modulation mapper takes binary digits, 0 or 1, as input
    and produces complex-valued modulation symbols, x=I+jQ, as output
    """
    def __init__(self, sbits):
        self.sbits = sbits
        self.nbits = len(self.sbits)
        
    def mod_bpsk(self):
        r = []
        _b= self.sbits
        # 1 bit at a time
        r = [_bpsk[_b[i]] for i in range(self.nbits)]
        return r
    
    def mod_qpsk(self):
        r = []
        _b = self.sbits
        # 2 bits at a time
        r = [_qpsk[_b[i]*2 + _b[i+1]] for i in range(0, self.nbits, 2)]  
        return r
    
    def mod_16qam(self):
        r = []
        _b = self.sbits
        # 4 bits at a time
        r = [_16qam[_b[i]*8 + _b[i+1]*4 + _b[i+2]*2 + _b[i+3]] for i in range(0, self.nbits, 4)]  
        return r
        
    def mod_64qam(self):
        r = []
        _b = self.sbits
        # 6 bits at a time
        r = [_64qam[_b[i]*32 + _b[i+1]*16 + _b[i+2]*8 + _b[i+3]*4 + _b[i+4]*2 + _b[i+5]] for i in range(0, self.nbits, 4)]  
        return r
               
class PhysicalLayerLayerMapping:
    pass
class PhysicalLayerPrecoding:
    pass
class PhysicalLayerResourceElementMapping:
    pass
class PhysicalLayerOFDMSignalGenerator:
    pass

# Test
# s = PhysicalLayerScrambling(100,[1,1,0,1,1,0,0,0])
# sb = s.scramble()

# m = PhysicalLayerModulation(sb)
# msb = m.mod_16qam()

# print sb
# print msb

