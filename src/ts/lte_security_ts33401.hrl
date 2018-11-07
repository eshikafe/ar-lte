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

