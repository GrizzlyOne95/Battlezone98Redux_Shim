"""Classify Redux TRN keys as live or dead.

A key being parsed proves nothing -- Redux reads more of the 1.5 TRN format than
it implements. The test is the destination global: find where the parsed value
lands, then look for any read of it from outside the parser. Two shapes count as
live -- an xref from another function, or the parser handing the buffer straight
to a loader.

Validated against SkyTexture/SunTexture (both render) as positive controls.
"""
import struct, sys
from capstone import *

EXE = r"C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe"
b = open(EXE, "rb").read()

pe = struct.unpack("<I", b[0x3c:0x40])[0]
nsec = struct.unpack("<H", b[pe+6:pe+8])[0]
opt = struct.unpack("<H", b[pe+20:pe+22])[0]
IMG = struct.unpack("<I", b[pe+24+28:pe+24+32])[0]
SEC = []
for i in range(nsec):
    e = b[pe+24+opt+40*i: pe+24+opt+40*i+40]
    vs, sva, rs, sra = struct.unpack("<4I", e[8:24])
    SEC.append((e[:8].rstrip(b"\0").decode(), sva, vs, sra, rs))
TEXT = next(s for s in SEC if s[0] == ".text")

def f2v(fo):
    for _, sva, vs, sra, rs in SEC:
        if sra <= fo < sra + rs:
            return IMG + sva + (fo - sra)
def v2f(v):
    r = v - IMG
    for _, sva, vs, sra, rs in SEC:
        if sva <= r < sva + vs:
            return sra + (r - sva)

md = Cs(CS_ARCH_X86, CS_MODE_32)

def xrefs(va, only_text=True):
    """Every 4-byte little-endian occurrence of this address."""
    n = struct.pack("<I", va)
    lo, hi = (TEXT[3], TEXT[3]+TEXT[4]) if only_text else (0, len(b))
    return [f2v(i) for i in range(lo, hi-4) if b[i:i+4] == n]

def func_bounds(va):
    """MSVC function containing va: back to a prologue after int3 padding,
    forward to the ret before the next padding run."""
    fo = v2f(va)
    lo = fo
    while lo > TEXT[3] + 8:
        if b[lo-1] == 0xCC and b[lo] in (0x55, 0x53, 0x56, 0x57) :
            break
        lo -= 1
    hi = fo
    while hi < TEXT[3] + TEXT[4] - 8:
        if b[hi] == 0xC3 and b[hi+1] == 0xCC:
            hi += 1
            break
        hi += 1
    return f2v(lo), f2v(hi)

def before(va, back):
    """Instructions ending exactly at `va`, by trying each start offset."""
    for k in range(back, 4, -1):
        ins = list(md.disasm(b[v2f(va-k):v2f(va)], va-k))
        if ins and ins[-1].address + ins[-1].size == va:
            return ins
    return []

def block_copies():
    """(src, bytes, site) for every `mov esi,imm / mov ecx,imm / rep movsd`.

    A global inside one of these is consumed without any direct xref to it --
    the whole [NormalView] set is copied into the live view struct in one go,
    so without this every key but the first reads as dead."""
    out = []
    lo, hi = TEXT[3], TEXT[3] + TEXT[4]
    for i in range(lo, hi - 2):
        if b[i] == 0xF3 and b[i+1] == 0xA5:          # rep movsd
            ins = before(f2v(i), 0x30)
            src = cnt = None
            for x in ins:
                if x.mnemonic == "mov" and x.op_str.startswith("esi, 0x"):
                    src = imm(x.op_str.split(", ")[1])
                if x.mnemonic == "mov" and x.op_str.startswith("ecx, "):
                    cnt = imm(x.op_str.split(", ")[1])
            if src and cnt:
                out.append((src, cnt * 4, f2v(i)))
    return out

BLOCKS = None

def copied_by(addr):
    global BLOCKS
    if BLOCKS is None:
        BLOCKS = block_copies()
    return [(s, n, site) for s, n, site in BLOCKS if s <= addr < s + n]

WRITERS = ("mov", "movss", "movsd", "movups", "movaps", "movd", "movq", "fstp", "fst")

def is_read(ref, addr):
    """True unless the instruction only stores to [addr]."""
    ins, k = window(ref, back=0x20, fwd=0x10)
    if k is None:
        return True                       # undecodable: keep it, do not hide it
    x = ins[k]
    ops = x.op_str.split(",", 1)
    mem = "[0x%x]" % addr
    if len(ops) == 2 and mem in ops[0] and x.mnemonic in WRITERS:
        return False                      # a pure store
    return True

def window(ref, back=0x40, fwd=0x50):
    """`ref` is where the 4 operand bytes sit, which is 1-3 bytes into the
    instruction, and disassembling from an arbitrary offset desynchronises --
    so try several starts and keep the first that decodes an instruction
    actually covering those bytes."""
    for back in range(back, 3, -1):
        ins = list(md.disasm(b[v2f(ref-back): v2f(ref+fwd)], ref-back))
        k = next((i for i, x in enumerate(ins)
                  if x.address <= ref < x.address + x.size), None)
        if k is not None and ins[k].address + ins[k].size >= ref + 4:
            return ins, k
    return [], None

def imm(op):
    try:
        return int(op, 16) if op.startswith("0x") else int(op)
    except ValueError:
        return None


def occurrences(key):
    """Every NUL-delimited copy of the literal. The same key name lives in
    several string pools; only one of them is the one the parser pushes."""
    pat, out, start = key.encode() + b"\0", [], 0
    while True:
        i = b.find(pat, start)
        if i < 0:
            return out
        if i == 0 or b[i-1] == 0:
            out.append(i)
        start = i + 1

READ_INT, READ_STR, READ_FLT = 0x787AC0, 0x787A30, 0x787B60
STORES = ("mov", "movss", "movsd", "fstp", "fst")

def dest_of(site):
    """Where the value parsed at this call site is stored.

    Exactly three readers exist. int (0x787AC0) and float (0x787B60) return in
    eax/st0 and the caller stores to an absolute address; the string reader
    (0x787A30) takes (section, key, default, dest, size, file), so counting
    back from the key push, -1 is the default "" and -2 is the buffer. Guessing
    a fallback makes every unrecognised key report the file-context pointer,
    so an unknown shape returns None and says so instead."""
    ins, k = window(site, back=0x60, fwd=0x60)
    if k is None:
        return None, "undecodable"
    call = next((x for x in ins[k:k+8] if x.mnemonic == "call"), None)
    if not call:
        return None, "no call"
    helper = imm(call.op_str)
    if helper == READ_STR:
        pushes = [x for x in ins[:k] if x.mnemonic == "push"]
        if len(pushes) >= 2:
            d = imm(pushes[-2].op_str)
            if d and d > 0x500000:
                return d, "str"
        return None, "str args unclear"
    if helper in (READ_INT, READ_FLT):
        for x in ins[ins.index(call)+1: ins.index(call)+12]:
            if x.mnemonic in STORES and "ptr [0x" in x.op_str:
                seg = x.op_str.split("[")[1].split("]")[0]
                d = imm(seg)
                if d and d > 0x500000 and x.op_str.index("[") < (x.op_str.index(",") if "," in x.op_str else len(x.op_str)):
                    return d, "int" if helper == READ_INT else "float"
        return None, "store not found"
    return None, "indirect call" if helper is None else ("helper %s" % hex(helper))

def classify(key):
    sites = []
    for fo in occurrences(key):
        for s in xrefs(f2v(fo)):
            sites.append((f2v(fo), s))
    if not sites:
        return dict(key=key, status="NOT IN EXE" if not occurrences(key) else "never referenced")
    rows = []
    for kva, site in sites:
        d, how = dest_of(site)
        if d is None:
            rows.append(dict(site=site, dest=None, note="unresolved (%s)" % how))
            continue
        lo, hi = func_bounds(site)
        cons = [x for x in xrefs(d) if not (lo <= x <= hi) and is_read(x, d)]
        blk = copied_by(d)
        ins, k = window(site, back=0x60, fwd=0xA0)
        inline = any(x.mnemonic == "push" and imm(x.op_str) == d and
                     any(y.mnemonic == "call" for y in ins[i+1:i+4])
                     for i, x in enumerate(ins)) if k is not None else False
        if cons:
            rows.append(dict(site=site, dest=d, live=True,
                             note="read at " + ",".join("%08x" % c for c in cons[:3])))
        elif blk:
            rows.append(dict(site=site, dest=d, live=True,
                             note="copied by %08x (+%d)" % (blk[0][2], d - blk[0][0])))
        elif inline:
            rows.append(dict(site=site, dest=d, live=True, note="consumed in parser"))
        else:
            rows.append(dict(site=site, dest=d, live=False, note="parsed, never read"))
    return dict(key=key, rows=rows)

if __name__ == "__main__":
    print("%-20s %-9s %-11s %s" % ("key", "verdict", "stored at", "evidence"))
    for key in sys.argv[1:]:
        r = classify(key)
        if "rows" not in r:
            print("%-20s %-9s %-11s %s" % (key, "-", "-", r["status"]))
            continue
        live = any(x.get("live") for x in r["rows"])
        best = next((x for x in r["rows"] if x.get("live")), r["rows"][0])
        print("%-20s %-9s %-11s %s" % (
            key, "LIVE" if live else "DEAD",
            ("%08x" % best["dest"]) if best["dest"] else "-", best["note"]))
