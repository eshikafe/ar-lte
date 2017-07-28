# x680_asn1.py
# ASN.1: Specification of basic notation
# Based on ITU-T X.680(08/2015)
#
# Copyright 2017 Austin Aigbe
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import plex


def tokenise(f):
    lno = 0
    fp = open(f,'r')

    while 1:
        l = fp.readline()
        lno = lno + 1

        # eof
        if l = '':
            break
        # skip one-line comments - X.680 12.6.3 
        elif l[0:2] == '--':
            continue
        # skip multiple-line comments - X.680 12.6.4
        elif l[0:2] == '/*':
            if '*/' in l:
                continue
            else:
                while 1:
                    l = fp.readline()
                    lno = lno + 1
                    if '*/' in l:
                        break
                continue
        elif:
            
    
    
    
    return token # list of tokens
    
def parse(tokens):
    pass

# 12.38 Reserved words
# 
reserved_words = Str('ABSENT',          'ENCODED',           'INTERSECTION',     'SEQUENCE',
                     'ABSTRACT-SYNTAX',  'ENCODING-CONTROL', 'ISO646String',     'SET',
                     'ALL',              'END',              'MAX',              'SETTINGS',
                     'APPLICATION',      'ENUMERATED',       'MIN',              'SIZE',
                     'AUTOMATIC',        'EXCEPT',           'MINUS-INFINITY',   'STRING',
                     'BEGIN',            'EXPLICIT',         'NOT-A-NUMBER',     'SYNTAX',
                     'BIT',              'EXPORTS',          'NULL',             'T61String',
                     'BMPString',        'EXTENSIBILITY',    'NumericString',    'TAGS',
                     'BOOLEAN',          'EXTERNAL',         'OBJECT',           'TeletexString',
                     'BY',               'FALSE',            'ObjectDescriptor', 'TIME',
                     'CHARACTER',        'FROM',             'OCTET',            'TIME-OF-DAY',
                     'CHOICE',           'GeneralizedTime',  'OF',               'TRUE',
                     'CLASS',            'GeneralString',    'OID-IRI',          'TYPE-IDENTIFIER',
                     'COMPONENT',        'GraphicString',    'OPTIONAL',         'UNION',
                     'COMPONENTS',       'IA5String',        'PATTERN',          'UNIQUE',
                     'CONSTRAINED',      'IDENTIFIER',       'PDV',              'UNIVERSAL',
                     'CONTAINING',       'IMPLICIT',         'PLUS-INFINITY',    'UniversalString',
                     'DATE',             'IMPLIED',          'PRESENT',          'UTCTime',
                     'DATE-TIME',        'IMPORTS',          'PrintableString',  'UTF8String',
                     'DEFAULT',          'INCLUDES',         'PRIVATE',          'VideotexString',
                     'DEFINITIONS',      'INSTANCE',         'REAL',             'VisibleString',
                     'DURATION',         'INSTRUCTIONS',     'RELATIVE-OID',     'WITH',
                     'EMBEDDED',         'INTEGER',          'RELATIVE-OID-IRI')
