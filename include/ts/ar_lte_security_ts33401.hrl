% Table A.7-1: Algorithm type distinguishers
-define(ALGO_TYPE_NAS_ENC, <<1:8>>).
-define(ALGO_TYPE_NAS_INT, <<2:8>>).
-define(ALGO_TYPE_RRC_ENC, <<3:8>>).
-define(ALGO_TYPE_RRC_INT, <<4:8>>).
-define(ALGO_TYPE_UP_ENC,  <<5:8>>).
-define(ALGO_TYPE_UP_INT,  <<6:8>>).

% 5.1.4.1 Integrity requirements
% EPS Integrity Algorithm Identity
-define(ALGO_ID_EIA0, 0).     % Null Integrity Protection algorithm */
-define(ALGO_ID_128_EIA1, 1). % SNOW 3G based algorithm */
-define(ALGO_ID_128_EIA2, 2). % AES based algorithm */
-define(ALGO_ID_128_EIA3, 3). % ZUC based algorithm */

% 5.1.3.1 Ciphering requirements 
% 5.1.3.2 Algorithm Identifier Values 
% EPS Encryption Algorithm Identity
-define(ALGO_ID_EEA0, 0). 
-define(ALGO_ID_128_EEA1, 1).
-define(ALGO_ID_128_EEA2, 2). 
-define(ALGO_ID_128_EEA3, 3).

