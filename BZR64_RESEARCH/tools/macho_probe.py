#!/usr/bin/env python3
"""Mach-O reconstruction probe for the Battlezone 98 Redux macOS x86_64 final.

Read-only. Resolves virtual addresses to file offsets, symbolizes addresses from
an llvm-nm dump, dumps Itanium-ABI vtables and typeinfo chains, and hexdumps.

Usage:
  macho_probe.py <binary> sections
  macho_probe.py <binary> vtable <va> [slots]
  macho_probe.py <binary> typeinfo <va>
  macho_probe.py <binary> hex <va> <len>
  macho_probe.py <binary> ptrs <va> <count>
  macho_probe.py <binary> sym <va>

A sibling <binary>.nmcache (llvm-nm --defined-only --numeric-sort output) is used
for symbolization when present; otherwise pass --nm <file>.
"""
import struct
import sys
import bisect
import os
import subprocess

LC_SEGMENT_64 = 0x19

CXXFILT_CANDIDATES = [
    r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\llvm-cxxfilt.exe",
    "llvm-cxxfilt",
]


class MachO:
    def __init__(self, path, nm=None):
        self.path = path
        self.data = open(path, "rb").read()
        self.sections = []
        self.segments = []
        self._parse()
        self.syms = []
        self._sva = []
        self._load_syms(nm)

    def _parse(self):
        magic, = struct.unpack_from("<I", self.data, 0)
        if magic != 0xFEEDFACF:
            raise SystemExit("not a thin 64-bit Mach-O (magic %08x)" % magic)
        ncmds, = struct.unpack_from("<I", self.data, 16)
        off = 32
        for _ in range(ncmds):
            cmd, cmdsize = struct.unpack_from("<II", self.data, off)
            if cmd == LC_SEGMENT_64:
                segname = self.data[off + 8:off + 24].rstrip(b"\0").decode()
                vmaddr, vmsize, fileoff, filesize = struct.unpack_from("<QQQQ", self.data, off + 24)
                nsects, = struct.unpack_from("<I", self.data, off + 64)
                self.segments.append((segname, vmaddr, vmsize, fileoff, filesize))
                so = off + 72
                for _s in range(nsects):
                    sn = self.data[so:so + 16].rstrip(b"\0").decode()
                    sg = self.data[so + 16:so + 32].rstrip(b"\0").decode()
                    addr, size = struct.unpack_from("<QQ", self.data, so + 32)
                    foff, = struct.unpack_from("<I", self.data, so + 48)
                    flags, = struct.unpack_from("<I", self.data, so + 64)
                    self.sections.append(("%s,%s" % (sg, sn), addr, size, foff, flags))
                    so += 80
            off += cmdsize

    def _load_syms(self, nm):
        cache = nm or (self.path + ".nmcache")
        if not os.path.exists(cache):
            return
        for line in open(cache, "r", errors="replace"):
            p = line.split()
            if len(p) < 3:
                continue
            try:
                va = int(p[0], 16)
            except ValueError:
                continue
            self.syms.append((va, " ".join(p[2:])))
        self.syms.sort()
        self._sva = [s[0] for s in self.syms]

    def _sec(self, va):
        for rec in self.sections:
            name, addr, size, foff, flags = rec
            if size and addr <= va < addr + size:
                return rec
        return None

    def va2off(self, va):
        rec = self._sec(va)
        if not rec:
            return None
        name, addr, size, foff, flags = rec
        # S_ZEROFILL == 1, S_THREAD_LOCAL_ZEROFILL == 0x12: no file bytes
        if (flags & 0xFF) in (1, 0x12):
            return None
        return foff + (va - addr)

    def secname(self, va):
        rec = self._sec(va)
        return rec[0] if rec else "?"

    def read(self, va, n):
        off = self.va2off(va)
        if off is None:
            return None
        return self.data[off:off + n]

    def qword(self, va):
        b = self.read(va, 8)
        if not b or len(b) < 8:
            return None
        return struct.unpack("<Q", b)[0]

    def sym(self, va):
        if not self.syms or not va:
            return None
        i = bisect.bisect_right(self._sva, va) - 1
        if i < 0:
            return None
        sva, name = self.syms[i]
        return (name, va - sva)


def demangle_many(names):
    if not names:
        return []
    exe = None
    for c in CXXFILT_CANDIDATES:
        if c == "llvm-cxxfilt" or os.path.exists(c):
            exe = c
            break
    if not exe:
        return list(names)
    try:
        p = subprocess.run([exe], input="\n".join(names), capture_output=True, text=True)
        out = p.stdout.splitlines()
        if len(out) == len(names):
            return out
    except Exception:
        pass
    return list(names)


def fmt(m, va, dem):
    if not va:
        return "0"
    s = m.sym(va)
    if not s:
        return "%016x  <no symbol>" % va
    name, delta = s
    d = dem.get(name, name)
    return "%016x  %s%s" % (va, d, ("+0x%x" % delta) if delta else "")


def build_dem(m, addrs):
    names = []
    for q in addrs:
        if q:
            s = m.sym(q)
            if s:
                names.append(s[0])
    return dict(zip(names, demangle_many(names))) if names else {}


def main():
    argv = sys.argv[1:]
    nm = None
    if "--nm" in argv:
        i = argv.index("--nm")
        nm = argv[i + 1]
        del argv[i:i + 2]
    if len(argv) < 2:
        print(__doc__)
        return 1
    path, cmd = argv[0], argv[1]
    args = argv[2:]
    m = MachO(path, nm)

    if cmd == "sections":
        for name, addr, size, foff, flags in m.sections:
            print("%-30s va=%016x size=%-10d fileoff=%-10d flags=%08x" % (name, addr, size, foff, flags))
        return 0

    if not args:
        print(__doc__)
        return 1
    va = int(args[0], 16)

    if cmd == "vtable":
        n = int(args[1]) if len(args) > 1 else 40
        raw = [m.qword(va + 8 * i) for i in range(n)]
        dem = build_dem(m, raw)
        print("vtable at %016x (%s)" % (va, m.secname(va)))
        print("  [-2] offset-to-top : 0x%x" % (raw[0] or 0))
        print("  [-1] typeinfo      : %s" % fmt(m, raw[1] or 0, dem))
        for i in range(2, n):
            if raw[i] is None:
                break
            print("  [%3d] %s" % (i - 2, fmt(m, raw[i], dem)))
        return 0

    if cmd == "typeinfo":
        vptr = m.qword(va)
        namep = m.qword(va + 8)
        b3 = m.qword(va + 16)
        dem = build_dem(m, [vptr, namep, b3])
        print("typeinfo at %016x" % va)
        print("  vptr  -> %s" % fmt(m, vptr, dem))
        raw_name = (m.read(namep, 96) or b"").split(b"\0")[0] if namep else b""
        print("  name  -> %016x %r" % (namep or 0, raw_name))
        print("  +0x10 -> %s" % fmt(m, b3 or 0, dem))
        blob = m.read(va, 64)
        print("  raw   : %s" % (blob.hex() if blob else "<none>"))
        return 0

    if cmd == "hex":
        n = int(args[1]) if len(args) > 1 else 64
        b = m.read(va, n)
        if b is None:
            print("no file bytes (zerofill) at %016x (%s)" % (va, m.secname(va)))
            return 0
        for i in range(0, len(b), 16):
            chunk = b[i:i + 16]
            print("%016x  %-47s  %s" % (va + i, " ".join("%02x" % c for c in chunk),
                                        "".join(chr(c) if 32 <= c < 127 else "." for c in chunk)))
        return 0

    if cmd == "ptrs":
        n = int(args[1]) if len(args) > 1 else 8
        raw = [m.qword(va + 8 * i) for i in range(n)]
        dem = build_dem(m, raw)
        for i, q in enumerate(raw):
            if q is None:
                break
            print("  +0x%03x  %s" % (i * 8, fmt(m, q, dem)))
        return 0

    if cmd == "sym":
        s = m.sym(va)
        if not s:
            print("no symbol")
            return 0
        print("%s+0x%x  (%s)" % (demangle_many([s[0]])[0], s[1], m.secname(va)))
        return 0

    print("unknown command", cmd)
    return 1


if __name__ == "__main__":
    sys.exit(main())
