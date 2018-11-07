% Copyright (c) 2018 Aigbe Research
%
%  3GPP TS 33.401 version 12.13.0 Release 12

-module(lte_security_ts33401_SUITE).

-compile(export_all).

-include("ct.hrl").

-record(test_set,
        {key, count, bearer, direction, length, plaintext, ciphertext}).

all() ->
	[eea2_128].

init_per_suite(Config) ->
	Config.

end_per_suite(Config) ->
	Config.

eea2_128(_Config) ->
	F = fun(#test_set{key = Key, count = Count, bearer = Bearer, length = Length, plaintext = Plaintext, ciphertext = Ciphertext}) ->
				Ciphertext = lte_security_ts33401:eea2_128_encryption(Key, Count, Bearer, Direction, Length, Plaintext)
	end,
	lists:foreach(F, [test_set(N) || N <- lists:seq(1, 2)]).
 

% C.1.1 Test Set 1 

test_set(1) ->
	#test_set{
    	key = <<211,197,213,146,50,127,177,28,64,53,198,104,10,248,198,209>>
    	count = <<57,138,89,180>>,
    	bearer = <<(16#15):5>>,
    	direction = 1,
    	length = 253, % bits
    	plaintext = 16#981ba6824c1bfb1ab485472029b71d808ce33e2cc3c0b5fc1f3de8a6dc66b1f0,
    	ciphertext = <<(16#e9fed8a63d155304d71df20bf3e82214b20ed7dad2f233dc3c22d7bdeeed8e78):256>>
    	}

test_set(2) ->
	#test_set{
    	key = <<43,214,69,159,130,196,64,224,149,44,73,16,72,5,255,72>>,
    	count = <<198,117,166,75>>,
    	bearer = <<12:5>>,
    	direction = 1,
    	length = 798, % bits
    	plaintext = 16#7ec61272743bf1614726446a6c38ced166f6ca76eb5430044286346cef130f92922b03450d3a9975e5bd2ea0eb55ad8e1b199e3ec4316020e9a1b285e762795359b7bdfd39bef4b2484583d5afe082aee638bf5fd5a606193901a08f4ab41aab9b134880,
    	ciphertext = 16#5961605353c64bdca15b195e288553a910632506d6200aa790c4c806c99904cf2445cc50bb1cf168a49673734e081b57e324ce5259c0e78d4cd97b870976503c0943f2cb5ae8f052c7b7d392239587b8956086bcab18836042e2e6ce42432a17105c53d0
    	}

 