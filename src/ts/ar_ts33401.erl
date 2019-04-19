% Copyright (c) 2018 Aigbe Research
% ar_ts33401.erl
%
% Compliance: 
%    3GPP TS 33.401 version 12.13.0 Release 12
%    3GPP TS 33.220 V12.3.0
%    3GPP TS 35.215 V15.0.0 (2018-06)

-module(ar_ts33401).

-export([kdf/3]).

-export([eea2_128_encrypt/6, eia2_128_integrity/6]).

% Use the sha256() hash function to compute a hmac code with the hmac() function
hmac_sha256(Key, Data) ->
	crypto:hmac(sha256, Key, Data, 16).

% Key Derivation Function (KDF)
% Output keys: 
%			KRRCint, 
%			KRRCenc, 
%			KUPint, 
%			KUPenc
kdf(KeNB, AlgoType, AlgoId) when size(KeNB) == 32 ->
	FC = <<15:8>>, 
	P0 = AlgoType,         % algorithm type distinguisher
	L0 = <<1:16>>,         % length of algorithm type distinguisher (i.e 0x00 0x01)
	P1= AlgoId,            % algorithm identity
	L1 = <<1:16>>,         % length of algorithm identity (i.e. 0x00 0x01)

    % S = FC || P0 || L0 || P1 || L1 || P2 || L2 || P3 || L3 ||... || Pn || Ln */
    S = <<FC/binary, P0/binary, L0/binary, P1/binary, L1/binary>>, 
    hmac_sha256(KeNB, S).

% ciphering algorithm
%  used by the PDCP layer to encrypt the data part of the PDCP PDU
%  Key: 128 bits
%  Count: 32 bits
%  Bearer: 5 bits
%  Direction: 1 bit (0 - uplink, 1 - downlink)
%  Length: length(Msg)
eea2_128_encrypt(Key, Count, Bearer, Direction, Length, Data) ->
	crypto:block_encrypt(ecb_aes, KeyStream, Data).

eia2_128_int(Key, Count, Bearer, Direction, Length, Data) ->
	todo.




