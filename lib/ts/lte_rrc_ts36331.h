/* 
(c) 2018 Aigbe Research

rrc_ts36331.h
 
 3GPP TS 36.331, Evolved Universal Terrestrial Radio Access (E-UTRA); 
 Radio Resource Control (RRC) Protocol specification

Reference:
 https://www.etsi.org/deliver/etsi_ts/136300_136399/136331/14.02.02_60/ts_136331v140202p.pdf
 
*/

/*

EstablishmentCause ::= ENUMERATED {
 emergency, highPriorityAccess, mt-Access, mo-Signalling,
 mo-Data, delayTolerantAccess-v1020, mo-VoiceCall-v1280,
spare1}
-- ASN1STOP 
 */
enum EstablishmentCause {
	emergency = 0,
	highPriorityAccess,
	mt_Access,
	mo_Signalling,
	mo_Data,
	delayTolerantAccess_v1020,
	mo_VoiceCall_v1280,
	spare1
};


/* MMEC ::= BIT STRING (SIZE (8)) */
typedef uint8_t MMEC;

/* 
	S-TMSI ::= SEQUENCE {
 		mmec MMEC,
 		m-TMSI BIT STRING (SIZE (32))
}
*/
typedef struct S_TMSI {
	MMEC mmec;
	uint32_t m_TMSI;
} S_TMSI;

/*
 InitialUE-Identity ::= CHOICE {
      s-TMSI S-TMSI,
      randomValue BIT STRING (SIZE (40))
}
*/
union InitialUE_Identity {
	S_TMSI s_tmsi;
	uint64_t random_value;
};

/*
	RRCConnectionRequest-r8-IEs ::= SEQUENCE {
 ue-Identity InitialUE-Identity,
 establishmentCause EstablishmentCause,
 spare BIT STRING (SIZE (1))
}
 */
typedef struct RRCConnectionRequest_r8_IEs {
	union InitialUE_Identity ue_identity;
	enum EstablishmentCause est_cause;
	uint8_t spare;
} RRCConnectionRequest_r8_IEs;

/*

-- ASN1START
RRCConnectionRequest ::= SEQUENCE {
 criticalExtensions CHOICE {
 rrcConnectionRequest-r8 RRCConnectionRequest-r8-IEs,
 criticalExtensionsFuture SEQUENCE {}
 }
}
*/

struct RRCConnectionRequest {
	RRCConnectionRequest_r8_IEs rrc_con_req_r8;
};

void encode_rrc_con_req(struct RRCConnectionRequest *msg, struct asn1_msg );
void decode_rrc_con_req(struct RRCConnectionRequest *msg, struct asn1_msg);
