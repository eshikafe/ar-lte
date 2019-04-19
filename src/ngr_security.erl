% Copyright (c) 2018 Aigbe Research
% ar_lte_security.erl

-module(ngr_security).

-export([k_rrc_int/1, k_rrc_enc/1]).

-include("ts/ar_lte_security.hrl").

% KeNB => 32bits 
k_rrc_int(KeNB) when size(KeNB) == 32 ->
	ar_lte_security_ts33401:kdf(KeNB, ?ALGO_TYPE_RRC_INT, ?ALGO_ID_128_EIA2).


k_rrc_enc(KeNB) when size(KeNB) == 32 ->
	ar_lte_security_ts33401:kdf(KeNB, ?ALGO_TYPE_RRC_ENC, ?ALGO_ID_128_EEA2).
