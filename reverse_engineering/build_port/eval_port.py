#!/usr/bin/env python3
"""Measure port_patches.py against two real builds, using strings as truth.

String literals keep their text across builds, so they give an oracle that
does not depend on the porter's own method:

  site      an instruction that pushes/moves a string address must, once
            carried across, still reference a string with the same text
  function  a function entry must, once carried across, reference the same
            set of string texts in its body
  data      a string's own address must carry across to the same text

A "wrong" is a confident (OK) answer that fails the oracle; that number must
stay at zero. NOTFOUND/CONFLICT/WEAK are safe misses.

  python eval_port.py OLD.exe NEW.exe [--samples 300] [--seed 1]
"""
import argparse
import collections
import difflib
import random
import re
import struct

import port_patches as pp


def cstring(img, va, limit=200):
    b = img.read(va - 1, limit + 1)
    if not b or b[0] != 0:      # must be the start of a string, not a tail
        return None
    b = b[1:]
    s = b.split(b"\0", 1)[0]
    if len(s) < 5 or len(s) >= limit or any(c < 0x20 or c > 0x7E for c in s):
        return None
    return s


def string_sites(img):
    """[(insn_va, string_va)] for push imm32 / mov r32, imm32 of a string."""
    out = []
    for m in re.finditer(rb"[\x68\xB8-\xBF]", img.text):
        va = img.text_lo + m.start()
        v = img.dword(va + 1)
        # The opcode byte must start a real instruction, not sit inside one.
        if v and img.in_image(v) and not img.in_text(v) and cstring(img, v) \
                and va in img.boundaries_before(va):
            out.append((va, v))
    return out


def function_strings(img, f, limit=0x600):
    """String texts whose addresses appear anywhere in the function body.

    Raw dword scan up to the next int3 padding run, so it does not depend on
    a linear decode surviving jump tables or odd bytes.
    """
    blob = img.read(f, limit) or b""
    end = blob.find(b"\xCC\xCC")
    blob = blob[: end if end > 0 else limit]
    texts = set()
    for k in range(len(blob) - 3):
        v = struct.unpack_from("<I", blob, k)[0]
        if img.in_image(v) and not img.in_text(v):
            t = cstring(img, v)
            if t:
                texts.add(t)
    return texts


def similar(x, y):
    """Same text, or the same text with an edit (e.g. a version number)."""
    if x is None or y is None:
        return False
    return x == y or difflib.SequenceMatcher(None, x, y).ratio() >= 0.7


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("old_exe")
    ap.add_argument("new_exe")
    ap.add_argument("--samples", type=int, default=300)
    ap.add_argument("--seed", type=int, default=1)
    a = ap.parse_args()
    old, new = pp.Image(a.old_exe), pp.Image(a.new_exe)
    p = pp.Porter(old, new)
    rnd = random.Random(a.seed)
    sites = string_sites(old)
    tally = collections.defaultdict(collections.Counter)
    wrong = []

    for insn, s in rnd.sample(sites, min(a.samples, len(sites))):
        r = p.code.port(insn)
        st = r["status"]
        if st == "OK":
            v = new.dword(r["new"] + 1)
            ok = v is not None and cstring(new, v) == cstring(old, s)
            st = "OK" if ok else "WRONG"
            if not ok:
                wrong.append(("site", insn, r))
        tally["site"][st] += 1

    funcs = sorted({old.function_start(i) for i, _ in rnd.sample(sites, min(a.samples * 2, len(sites)))} - {None})
    funcs = [f for f in funcs if function_strings(old, f)]
    for f in rnd.sample(funcs, min(a.samples, len(funcs))):
        r = p.code.port(f)
        st = r["status"]
        if st == "OK":
            so, sn = function_strings(old, f), function_strings(new, r["new"])
            # A function the patch edited may gain or lose a string; only a
            # mostly-different set means the port landed somewhere else.
            ok = bool(so & sn) and (so <= sn or sn <= so or len(so & sn) * 2 >= len(so | sn))
            st = "OK" if ok else "WRONG"
            if not ok:
                wrong.append(("function", f, r))
        tally["function"][st] += 1

    strs = sorted({s for _, s in sites})
    for s in rnd.sample(strs, min(a.samples, len(strs))):
        r = p.data.port(s)
        st = r["status"]
        if st == "OK":
            ok = similar(cstring(new, r["new"]), cstring(old, s))
            st = "OK" if ok else "WRONG"
            if not ok:
                wrong.append(("data", s, r))
        tally["data"][st] += 1

    for k, c in tally.items():
        n = sum(c.values())
        print("%-9s n=%-4d " % (k, n) + "  ".join("%s=%d (%.0f%%)" % (s, v, 100.0 * v / n) for s, v in sorted(c.items())))
    for kind, va, r in wrong[:20]:
        print("WRONG", kind, "0x%08X" % va, {k: v for k, v in r.items() if k != "evidence"}, [e["strategy"] for e in r.get("evidence", [])])


if __name__ == "__main__":
    main()
