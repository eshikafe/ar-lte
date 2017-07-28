#  TS 36.101

# 5.6 Transmission bandwidth
 
cdef enum tx_bw_config_nrb:
	N_RB_1_4MHZ = 6
	N_RB_3MHZ = 15
	N_RB_5MHZ = 25
	N_RB_10MHZ = 50
	N_RB_15MHZ = 75
	N_RB_20MHZ = 100
	N_RB_MAX = 110

# 5.6A Channel bandwidth for carrier aggregation

cdef int PRB_BW_MHZ = 0.18
