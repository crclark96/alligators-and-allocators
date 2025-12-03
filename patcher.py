#!/usr/bin/python3

import struct
import sys

cxa_finalize_offset = 0x1060
patch_offset = 0x11e1

with open(sys.argv[1], 'rb+') as f:
    offset = struct.pack("<i", cxa_finalize_offset - patch_offset - 5)
    call_opcode = struct.pack("<B", 0xe8)
    call_cxa_f = b''.join([call_opcode, offset])
    print(f"encoding: {call_cxa_f}")
    f.seek(patch_offset)
    f.write(call_cxa_f)


