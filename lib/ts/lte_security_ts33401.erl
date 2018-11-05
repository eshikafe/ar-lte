% Copyright (c) 2018 Aigbe Research
% lte_security_ts33401.erl
%
% Compliance: 
%    3GPP TS 33.401 version 12.13.0 Release 12
%    TS 33.220 V12.3.0 

-module(lte_security_ts33401).

% Table A.7-1: Algorithm type distinguishers
-define(NAS_ENC_ALG, <<1:8>>).
-define(NAS_INT_ALG, <<2:8>>).
-define(RRC_ENC_ALG, <<3:8>>).
-define(RRC_INT_ALG, <<4:8>>).
-define(UP_ENC_ALG,  <<5:8>>).
-define(UP_INT_ALG,  <<6:8>>).

% 5.1.4.1 Integrity requirements
% EPS Integrity Algorithm Identity
-define(ID_EIA0, 0).     % Null Integrity Protection algorithm */
-define(ID_128_EIA1, 1). % SNOW 3G based algorithm */
-define(ID_128_EIA2, 2). % AES based algorithm */
-define(ID_128_EIA3, 3). % ZUC based algorithm */

% 5.1.3.1 Ciphering requirements 
% 5.1.3.2 Algorithm Identifier Values 
% EPS Encryption Algorithm Identity
-define(ID_EEA0, 0). 
-define(ID_128_EEA1, 1).
-define(ID_128_EEA2, 2). 
-define(ID_128_EEA3, 3).

% Use the sha256() hash function to compute a hmac code with the hmac() function
hmac_sha256(Key, Data) ->
	crypto:hmac(sha256, Key, Data, 128).

% key derivation function
%   KRRCint, KRRCenc, KUPint, KUPenc
kdf(KeNB, AlgoType, AlgoId) when size(KeNB) == 32 ->
	FC = <<15:8>>, 
	P0 = AlgoType,         % algorithm type distinguisher
	L0 = <<1:16>>,         % length of algorithm type distinguisher (i.e 0x00 0x01)
	P1= AlgoId,            % algorithm identity
	L1 = <<1:16>>,         % length of algorithm identity (i.e. 0x00 0x01)

    % S = FC || P0 || L0 || P1 || L1 || P2 || L2 || P3 || L3 ||... || Pn || Ln */
    S = <<FC/binary, P0/binary, L0/binary, P1/binary, L1/binary>>, 
    hmac_sha256(K_eNB, S).



% A.2 Kasm derivation function
k_asme_df(CK, IK, MCC, MNC) ->
    MCC_String = integer_to_list(MCC),
    MNC_String = integer_to_list(MNC),
    [MCC3, MCC2, MCC1] = MCC_String,
    [MNC3, MNC2, MNC1] = MNC_String, % 2 or 3

    case length(MNC_String) of
    	2 ->
    		[MNC2, MNC1] = MNC_String,
    		MNC3 = "0";
    	3 ->
    		[MNC3, MNC2, MNC1] = MNC_String
    end,
    SN_id = <<(list_to_integer([MCC2])):4, (list_to_integer([MCC1])):4, 
              (list_to_integer([MCC3])):4, (list_to_integer([MNC3])):4,
              (list_to_integer([MNC2])):4, (list_to_integer([MNC1])):4>>,
	FC = <<10:8>,
	P0 = SN_id,
	L0 = <<3:16>>,
	P1 = SQN xor AK,
	L1 = <<6:16>>,
	S = <<FC/binary, P0/binary, L0/binary, P1/binary, L1/binary>>,
	Key = <<CK/binary, IK/binary>>,
	hmac_sha256(Key, S),
	SN_id.
