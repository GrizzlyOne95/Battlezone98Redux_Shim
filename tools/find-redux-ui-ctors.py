#!/usr/bin/env python3
"""Locate Redux `cUI_*` widget constructors in the shipped executable.

The private PDB in this repo is from a different build than the shipped GOG
exe -- different CodeView GUID, and a .text section roughly twice the size --
so its RVAs cannot be used directly and several constructors gained parameters
between the two. What the shipped image does still carry is RTTI, and that is
enough to find any polymorphic class by name:

    ".?AVcUI_X@@" string  ->  TypeDescriptor        (string - 8)
    -> CompleteObjectLocator  (.rdata dword == TD, struct starts 12 bytes back)
    -> vftable                (.rdata dword == COL, vftable starts 4 later)
    -> the functions in .text that store that vftable pointer

Those functions are the constructor and the destructors. They are told apart by
`ret N`: __thiscall cleans its own stack arguments, so N is 4 * argument count,
and destructors are `ret` or `ret 4`.

The method is calibrated against three constructors OpenShim already had
hard-coded, and reproduces all three exactly:

    cUI_Button  0x007C2480    cUI_Text  0x007CC390    cUI_View  0x007D1CC0

`--args N` additionally reads the arguments at each call site, resolving string
pointers and the `movss` constants the compiler uses to pass floats. That is how
the signatures of constructors whose parameter list changed between builds were
recovered.

Usage:
    python find-redux-ui-ctors.py --exe <battlezone98redux.exe>
    python find-redux-ui-ctors.py --exe <exe> --call-sites 0x007CF410 --args 10
"""
from __future__ import annotations

import argparse
import re
import struct
import subprocess
import sys

# Argument counts are the shipped build's, measured from `ret N`.
KNOWN = {
    'cUI_View': 8,
    'cUI_Button': 9,
    'cUI_Text': 8,
    'cUI_TextEntry': 10,
    'cUI_Selectlist': 11,
    'cUI_Checklist': 7,
    'cUI_Slider': 7,
    'cUI_ProgressBar': 7,
    'cUI_TextPopup': 7,
    'cUI_Alert': 7,
    'cUI_Parent': 3,
    'cUI_Multiplayer_SettingButton': 16,
}


def load(path):
    data = open(path, 'rb').read()
    e = struct.unpack_from('<I', data, 0x3C)[0]
    nsec = struct.unpack_from('<H', data, e + 6)[0]
    optsz = struct.unpack_from('<H', data, e + 20)[0]
    base = struct.unpack_from('<I', data, e + 24 + 28)[0]
    secs = []
    for i in range(nsec):
        o = e + 24 + optsz + i * 40
        name = data[o:o + 8].rstrip(b'\x00').decode()
        vsz, va, rsz, ptr = struct.unpack_from('<IIII', data, o + 8)
        secs.append({'name': name, 'va': base + va, 'vsz': vsz, 'ptr': ptr, 'rsz': rsz})
    return data, secs


def section(secs, name):
    return next((s for s in secs if s['name'] == name), None)


def va_to_off(secs, va):
    for s in secs:
        if s['va'] <= va < s['va'] + max(s['vsz'], s['rsz']):
            off = s['ptr'] + (va - s['va'])
            return off if off < s['ptr'] + s['rsz'] else None
    return None


def scan_dword(data, sec, value, aligned=True):
    """Offsets in `sec` holding `value`, as VAs. Data tables are 4-byte
    aligned; immediates inside instructions are not, so .text needs an
    unaligned search."""
    target = struct.pack('<I', value)
    hits = []
    start, end = sec['ptr'], sec['ptr'] + sec['rsz']
    pos = data.find(target, start, end)
    while pos >= 0:
        if not aligned or (pos - start) % 4 == 0:
            hits.append(sec['va'] + (pos - start))
        pos = data.find(target, pos + 1, end)
    return hits


def function_start(data, text, off):
    """Walk back to the int3 padding MSVC puts between functions."""
    lo = text['ptr']
    i = off
    while i > lo:
        if data[i - 1] == 0xCC and data[i - 2] == 0xCC:
            return i
        i -= 1
    return None


def first_ret(data, text, off, limit=0x3000):
    """imm16 of the first `ret N`, or 0 for a bare `ret`. The argument byte
    count is a small multiple of four with a zero high byte, which rejects most
    stray 0xC2 bytes inside other instructions."""
    end = min(off + limit, text['ptr'] + text['rsz'])
    i = off
    while i < end - 2:
        if data[i] == 0xC2 and data[i + 2] == 0 and data[i + 1] % 4 == 0 and data[i + 1] < 0x80:
            return data[i + 1]
        if data[i] == 0xC3:
            return 0
        i += 1
    return None


def locate(data, secs, cls):
    text, rdata, dsec = section(secs, '.text'), section(secs, '.rdata'), section(secs, '.data')
    pos = data.find(('.?AV%s@@' % cls).encode() + b'\x00')
    if pos < 0:
        return None, [], []

    str_va = None
    for s in secs:
        if s['ptr'] <= pos < s['ptr'] + s['rsz']:
            str_va = s['va'] + (pos - s['ptr'])
            break
    td = str_va - 8

    cols = [h - 12 for s in (rdata, dsec) for h in scan_dword(data, s, td)]
    vtables = sorted({h + 4 for c in cols for s in (rdata, dsec) for h in scan_dword(data, s, c)})

    fns = set()
    for vt in vtables:
        for ref in scan_dword(data, text, vt, aligned=False):
            off = va_to_off(secs, ref)
            fs = function_start(data, text, off)
            if fs is None:
                continue
            fns.add((text['va'] + (fs - text['ptr']), first_ret(data, text, fs)))
    return td, vtables, sorted(fns)


def call_sites(data, secs, target):
    text = section(secs, '.text')
    sites = []
    i, end = text['ptr'], text['ptr'] + text['rsz']
    while i < end - 5:
        if data[i] == 0xE8:
            rel = struct.unpack_from('<i', data, i + 1)[0]
            site = text['va'] + (i - text['ptr'])
            if site + 5 + rel == target:
                sites.append(site)
        i += 1
    return sites


def read_string(data, secs, va):
    off = va_to_off(secs, va)
    if off is None:
        return None
    end = data.find(b'\x00', off, off + 128)
    if end <= off:
        return None
    raw = data[off:end]
    return raw.decode() if all(32 <= c < 127 for c in raw) and len(raw) >= 2 else None


def dump_args(data, secs, exe, objdump, site, nargs):
    out = subprocess.run(
        [objdump, '-d', '--no-show-raw-insn',
         '--start-address=0x%X' % (site - 0x140), '--stop-address=0x%X' % (site + 5), exe],
        capture_output=True, text=True).stdout.splitlines()

    insns = []
    for line in out:
        m = re.match(r'\s*([0-9a-f]+):\s+(.*)', line)
        if m:
            insns.append(m.group(2).strip())

    args = []
    k = len(insns) - 1
    while k >= 0 and len(args) < nargs:
        ins = insns[k]
        if ins.startswith('pushl'):
            operand = ins.split(None, 1)[1]
            if operand.startswith('$'):
                tok = operand.split()[0][1:]
                n = int(tok, 16) if tok.startswith('0x') else int(tok)
                s = read_string(data, secs, n)
                args.append('"%s"' % s if s else '%d (0x%X)' % (n, n))
            else:
                # A float argument is `pushl <reg>` followed immediately by
                # `movss <const>,%xmm0` and a store into the new stack slot.
                val = operand
                if k + 2 < len(insns):
                    mm = re.match(r'movss\s+(0x[0-9a-f]+),\s*%xmm0', insns[k + 1])
                    if mm and '(%esp)' in insns[k + 2]:
                        off = va_to_off(secs, int(mm.group(1), 16))
                        if off is not None:
                            val = '%gf' % struct.unpack_from('<f', data, off)[0]
                args.append(val)
        k -= 1
    return args


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--exe', required=True)
    ap.add_argument('--call-sites', help='dump call-site arguments for this VA instead')
    ap.add_argument('--args', type=int, default=8, help='argument count for --call-sites')
    ap.add_argument('--limit', type=int, default=4, help='call sites to print')
    ap.add_argument('--objdump',
                    default=r'C:\Program Files\Microsoft Visual Studio\2022\Community'
                            r'\VC\Tools\Llvm\bin\llvm-objdump.exe')
    args = ap.parse_args()

    data, secs = load(args.exe)

    if args.call_sites:
        target = int(args.call_sites, 16)
        sites = call_sites(data, secs, target)
        print('%d call sites of 0x%08X' % (len(sites), target))
        for site in sites[:args.limit]:
            print('\n=== 0x%08X ===' % site)
            for i, a in enumerate(dump_args(data, secs, args.exe, args.objdump, site, args.args), 1):
                print('   arg%-2d %s' % (i, a))
        return

    for cls, argc in KNOWN.items():
        td, vtables, fns = locate(data, secs, cls)
        if td is None:
            print('%-32s no RTTI in this build' % cls)
            continue
        want = argc * 4
        ctor = next((f for f, r in fns if r == want), None)
        print('%-32s vftable=%s' % (cls, ','.join('0x%08X' % v for v in vtables)))
        for f, r in fns:
            tag = '  <== ctor (%d args)' % argc if f == ctor else ''
            print('        0x%08X  ret 0x%02X%s' % (f, r or 0, tag))
        if ctor is None:
            print('        no function with ret 0x%02X; argument count may differ in this build' % want)


if __name__ == '__main__':
    main()
