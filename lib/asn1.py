# asn1.py
#
# Copyright 2017 Aigbe Research


from libmich.asn1.processor import *

class S1AP:
    def __init__(self):
        load_module('S1AP')
        ASN1.ASN1Obj.CODEC = PER
        PER.VARIANT = 'A'
        self.s1ap_pdu = GLOBAL.TYPE['S1AP-PDU']

    # msg: string
    def decode_s1ap_msg(self, msg):
        if isinstance(msg, str):
            hex_msg = bytearray.fromhex(msg)
            self.s1ap_pdu.decode(hex_msg)
            return self.s1ap_pdu()
        else:
            return

    def encode_s1ap_msg(self, msg):
        self.s1ap_pdu.encode()
        

class RRC:
    def __init__(self):
        load_module('RRCLTE')
        ASN1.ASN1Obj.CODEC = PER
        PER.VARIANT = 'A'
        self.rrc_pdu = GLOBAL.TYPE['S1AP-PDU']

    # msg: string
    def decode_rrc_msg(self, msg):
        if isinstance(msg, str):
            hex_msg = bytearray.fromhex(msg)
            self.rrc_pdu.decode(hex_msg)
            return self.rrc_pdu()
        else:
            return

    def encode_rrc_msg(self, msg):
        self.rrc_pdu.encode()


class X2AP:
    def __init__(self):
        load_module('X2AP')
        ASN1.ASN1Obj.CODEC = PER
        PER.VARIANT = 'A'
        self.x2ap_pdu = GLOBAL.TYPE['S1AP-PDU']

    # msg: string
    def decode_x2ap_msg(self, msg):
        if isinstance(msg, str):
            hex_msg = bytearray.fromhex(msg)
            self.x2ap_pdu.decode(hex_msg)
            return self.x2ap_pdu()
        else:
            return

    def encode_x2ap_msg(self, msg):
        self.x2ap_pdu.encode()
