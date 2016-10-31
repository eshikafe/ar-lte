# ts36211_lte_phy_channels_modulation.pyx
# 
# TS 36.211: Physical channels and modulation 
#    The scope of this specification is to establish the characteristics of the Layer-1 physical channels, 
#    generation of physical layer signals and modulation, and to specify:
# 		- Definition of the uplink, downlink and sidelink physical channels;
#       - The structure of the physical channels, frame format, physical resource elements, etc.;
#		- Modulation mapping (BPSK, QPSK, etc);
#		- Physical shared channel in uplink, downlink and sidelink;
# 		- Reference signals in uplink, downlink and sidelink;
#		- Random access channel;
#		- Primary and secondary synchronization signals;
#		- Primary and secondary sidelink synchronization signals;
#		- OFDM signal generation in downlink;
#		- SC-FDMA signal generation in uplink and sidelink;
#		- Scrambling, modulation and up conversion;
#		- Uplink-downlink and sidelink timing relations;
#		- Layer mapping and precoding in downlink, uplink and sidelink. 
#		
#		Reference: 3GPP TS 36.201 version 12.2.0 Release 12, Section 5.3
#				
# Physical layer processing:
#	scrambling
#	modulation
#	layer mapping
#	precoding
#	mapping to resource elements
#	OFDM signal generation
#
#	Input to the physical layer: codewords
#  
#  # Copyright (c) 2015 - 2016 Austin Aigbe (eshikafe@gmail.com)

import cython

from libc.math cimport *

# Frame structure (4)
Ts = cython.declare(cython.double, 1/(15000*2048)) # seconds (basic time unit)
Tf = cython.declare(cython.double, 307200 * Ts)    # 10ms duration (radio frame duration)

LTE_PHY_RADIO_FRAME_TYPE1 = "FDD"
LTE_PHY_RADIO_FRAME_TYPE2 = "TDD"

LTE_PHY_FDD_HALF_DUPLEX = 0
LTE_PHY_FDD_FULL_DUPLEX = 1

# Frame structure type 1 (4.1)
# 
#   1 radio frame (Tf) = 20 slots = 10 subframes = 10ms
#   1 slot (T_slot_fdd) = 0.5ms
#   1 subframe = 2 slots = 1ms [2i and 2i+1, i = subframe]
#   
#   For FDD, DL transmission = 10 subframes, UL transmission = 10 subframes
#   in each Tf interval
T_slot = 15360 * Ts # 0.5ms (radio frame type1/type2 slot duration)

# Uplink physical channels (5.1.1)
#   A set of resource elements (RE) carrying information originating 
#   from higher layers.
#   Interface = between ts36212 and ts36211
# PUSCH
# PUCCH
# PRACH
# 
# Uplink physical signals (5.1.2) 
#   used by the physical layer but does not carry information originating
#   from higher layers.
# Reference signal

Nc = cython.declare(cython.int, 1600)

_a = cython.declare(cython.double,1/math.sqrt(2))
_b = cython.declare(cython.double,1/math.sqrt(10))
_c = cython.declare(cython.double,1/math.sqrt(42))

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

class Scrambling:
    def __init__(self, cinit, _b):
        self.cinit = cinit
        self.mbits = len(_b)
        self._b = _b
        
    def scramble(self):
        # sb[i] = (_b[i] + _c[i]) mod 2
        _c = self._pseudo_random_sequence()
        sb = []
        sb = [self._b[i]^_c[i] for i in range(self.mbits)]
        return sb
    
    def _pseudo_random_sequence(self):
        # TS 36.211 V12.2.0, section 7.2
        # Pseudo-random sequences are defined by _a length-31 Gold sequence
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
        
    def _x2(self):
        x2 = self.cinit
        for i in range(Nc-31):
            # Advance the 2nd m-sequence
            n = ((x2 >> 3)^(x2 >> 2)^(x2 >> 1)^x2) & 0x1
            x2 = (x2 >> 1) | (n << 30)
        return x2
            
    def _x1(self):
        # The first m-sequence shall be initialized with x1(0)=1,x1(n)=0,n=1,2,...,30.
        x1=1
        # Advance the 1st m-sequence
        for i in range(Nc-31):
            n = ((x1 >> 3)^(x1)) & 0x01
            x1 = (x1 >> 1) | (n << 30)
        return x1 # '0x54d21b24' = hex(x1)
        

class Modulation:
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
        r = [_bpsk[_b[i]] for i in range(self.nbits)]
        return r
    
    def mod_qpsk(self):
        r = []
        _b = self.sbits
        r = [_qpsk[_b[i]*2 + _b[i+1]] for i in range(0, self.nbits, 2)]  
        return r
    
    def mod_16qam(self):
        r = []
        _b = self.sbits
        r = [_16qam[_b[i]*8 + _b[i+1]*4 + _b[i+2]*2 + _b[i+3]] for i in range(0, self.nbits, 4)]  
        return r
        
    def mod_64qam(self):
        r = []
        _b = self.sbits
        r = [_64qam[_b[i]*32 + _b[i+1]*16 + _b[i+2]*8 + _b[i+3]*4 + _b[i+4]*2 + _b[i+5]] for i in range(0, self.nbits, 4)]  
        return r
               
class LayerMapping:
    pass
class Precoding:
    pass
class ResourceElementMapping:
    pass
class OFDMSignalGenerator:
    pass

# Test
# s = Scrambling(100,[1,1,0,1,1,0,0,0])
# sb = s.scramble()

# m = Modulation(sb)
# msb = m.lte_phy_mod_16qam()

# print sb
# print msb

