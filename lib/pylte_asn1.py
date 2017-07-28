# pylte_asn1.py
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

import os
import sys
from itu import x691_per
from itu import x680_asn1

opt = {}

# Lexical analysis and parsing
def lex_and_parse():
    lexical_items = x680_asn1.analyze_lex(opt['file'])
    p = x680_asn1.parse(lexical_items)
    
def input_file_type(file_name):
    f, ext = os.path.splitext(file_name)
    if ext == '.asn':
        f2, ext2 = os.path.splitext(f)
        if ext2 == '':
            if os.path.isfile(file_name):
                return {'single_file':file_name}
            else:
                return {'error':file_name + " does not exist"}
        elif ext2 == '.set':
            if os.path.isfile(file_name):
                pid = open(file_name,'r')
                file_list = pid.read().split('\n')
                pid.close()
                return {'multiple_files_file':file_list}
            else:
                return {'error':file_name + ' does not exist'}
        else:
            return {'error':'Unsupported file naming'}
    else:
        return {'error':'Unsupported file extension: '+ext}
     
def compile_multiple(mfile, options):
    pass

def compile_single(sfile, options):
    tp = lex_and_parse()
    base = os.path.splitext[0]
    out_file = base
    db_file = base + '.asn1db'
    opt = {'file':sfile,'outfile':out_file,'dbfile':db_file}
    process(tp,opt)
    
def compile_asn(f,options):
    ret = input_file_type(f)
    if 'single_file' in ret.keys():
        compile1(f, options)
    elif 'multiple_files_file' in ret.keys():
        compile_multiple(ret['multiple_files_file'], options)
    else:
        print ret
        sys.exit()
    
def compile(asn1_mod, options = {'encoding': 'per', 'verbose': False}):
    """        
        Compiles the ASN.1 module asn1_mod and generates an Python module asn1_mod.py
        with encode and decode functions for the types defined in asn_mod.

        For each ASN.1 value defined in the module, a Python function that returns the
        value in Python representation is generated.

        asn1_mod is a filename with extension ".asn".
        The generated Python module always gets the same name as the ASN.1 module.

        The compiler generates the following files:
            asn1_mod_h.py (if any SET or SEQUENCE is defined)
            asn1_mod.py - Python module with encode, decode, and value functions
            asn1_mod.asn1db - Intermediate format used by the compiler when modules IMPORT definitions from each other
    """

    compile_asn(asn1_mod, options)



