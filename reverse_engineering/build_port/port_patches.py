#!/usr/bin/env python3
"""Carry scripts/patches.json from one battlezone98redux.exe build to another.

When BZR ships a new executable, every fixed address in patches.json is
suspect. This tool re-finds each one in the new build from the code around it
in the old build, so a new patches.json can be produced in minutes and only
the entries that really changed need a human.

How an address is carried across:

  code   Take the instructions at (and just before) the old address, mask the
         bytes that legitimately move between builds -- absolute addresses
         inside the image and relative branch/call displacements -- and look
         for that signature in the new .text. Signatures grow until they are
         unique in the old build; several independent windows must agree.
         Struct offsets and immediates are NOT masked, so a function whose
         field offsets changed fails to port instead of porting silently.

  data   Find the instructions in the old .text that reference the address,
         carry each instruction across as code, and read the operand back out
         of the new build. Independent references vote. An address nothing
         references directly is placed relative to the nearest referenced
         neighbour, and is reported as inferred.

Every "pattern" is re-checked against the new build, and rewritten when the
only bytes that differ are masked ones (an embedded absolute address that
moved). "expected"/"expected_original" guard bytes are regenerated the same way.

Nothing is trusted on a single weak signal: anything short of agreement is
reported as CONFLICT/NOTFOUND/INFERRED and is left at its old value in the
output, so the runtime guards keep refusing it until someone looks.

Steam executables are SteamStub-encrypted on disk; unpack them with Steamless
first. Requires capstone and pefile.

  python port_patches.py OLD.exe NEW.exe [--patches scripts/patches.json]
         [--out ported_patches.json] [--report port_report.md]
         [--addresses extra.txt]
"""
import argparse
import bisect
import collections
import json
import math
import re
import struct
import sys
from pathlib import Path

import capstone
import pefile

REPO = Path(__file__).resolve().parents[2]

# Signature windows tried, in bytes (rounded up to whole instructions).
SIG_LENGTHS = (12, 16, 24, 32, 48, 64, 96, 128)
BACK_CONTEXT = (8, 16, 32, 48)
MAX_XREFS = 16
MAX_NEST = 2


class Image:
    """A PE mapped at its preferred base, readable by virtual address."""

    def __init__(self, path):
        self.path = str(path)
        pe = pefile.PE(self.path, fast_load=True)
        self.base = pe.OPTIONAL_HEADER.ImageBase
        self.size = pe.OPTIONAL_HEADER.SizeOfImage
        self.mem = bytearray(self.size)
        self.sections = []
        for s in pe.sections:
            raw = s.get_data()[: max(s.Misc_VirtualSize, 0) or len(s.get_data())]
            self.mem[s.VirtualAddress: s.VirtualAddress + len(raw)] = raw
            name = s.Name.rstrip(b"\0").decode(errors="replace")
            lo = self.base + s.VirtualAddress
            hi = lo + max(s.Misc_VirtualSize, s.SizeOfRawData)
            self.sections.append((name, lo, hi, bool(s.Characteristics & 0x20000000)))
            self.raw_spans = getattr(self, "raw_spans", []) + [(lo, lo + len(raw), bool(s.Characteristics & 0x20000000))]
        text = [s for s in self.sections if s[0] == ".text"] or [s for s in self.sections if s[3]]
        self.text_lo, self.text_hi = text[0][1], text[0][2]
        self.text = bytes(self.mem[self.text_lo - self.base: self.text_hi - self.base])
        self.timestamp = pe.FILE_HEADER.TimeDateStamp
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True
        self._xref_index = None
        self._bounds = {}
        self._calls = None

    def in_image(self, va):
        return self.base <= va < self.base + self.size

    def in_text(self, va):
        return self.text_lo <= va < self.text_hi

    def section_of(self, va):
        for name, lo, hi, ex in self.sections:
            if lo <= va < hi:
                return name, ex
        return None, False

    def read(self, va, n):
        o = va - self.base
        if o < 0 or o + n > self.size:
            return None
        return bytes(self.mem[o: o + n])

    def dword(self, va):
        b = self.read(va, 4)
        return None if b is None else struct.unpack("<I", b)[0]

    # -- disassembly ------------------------------------------------------

    def decode(self, va, max_bytes):
        """Linear decode from va; stops at the first undecodable byte."""
        code = self.read(va, max_bytes) or b""
        return list(self.md.disasm(code, va))

    def boundaries_before(self, va, span=64):
        """Instruction starts in [va-span+16, va] that most decodes agree on.

        x86 decoding resynchronises within a few instructions, so a start that
        decodes begun at many different earlier offsets keep landing on is
        real. Decodes that die on a bad byte before reaching va are ignored.
        """
        key = (va, span)
        if key in self._bounds:
            return self._bounds[key]
        votes = collections.Counter()
        runs = 0
        for back in range(16, span + 1):
            start = va - back
            if start < self.text_lo:
                continue
            starts, reached = [], False
            for i in self.decode(start, back + 16):
                if i.address > va:
                    reached = True
                    break
                starts.append(i.address)
                if i.address + i.size > va:
                    reached = True
            if reached:
                runs += 1
                votes.update(a for a in starts if a >= va - span + 16)
        out = sorted(a for a, n in votes.items() if runs and n * 10 >= runs * 6)
        self._bounds[key] = out
        return out

    def function_start(self, va, limit=0x4000):
        """Best guess at the entry of the function containing va: the first
        instruction after a run of int3/nop padding or a ret."""
        lo = max(self.text_lo, va - limit)
        blob = self.read(lo, va - lo + 1)
        for m in reversed(list(re.finditer(rb"(?:\xC3|\xC2..)\xCC+|\xCC\xCC+", blob, re.DOTALL))):
            s = lo + m.end()
            if s <= va:
                return s
        return None

    def call_index(self):
        """{target: [sites]} for every E8/E9 rel32 in .text landing in .text."""
        if self._calls is None:
            idx = collections.defaultdict(list)
            t, lo = self.text, self.text_lo
            for m in re.finditer(rb"[\xE8\xE9]", t):
                p = m.start()
                if p + 5 > len(t):
                    break
                tgt = (lo + p + 5 + struct.unpack_from("<i", t, p + 1)[0]) & 0xFFFFFFFF
                if self.text_lo <= tgt < self.text_hi:
                    idx[tgt].append(lo + p)
            self._calls = idx
        return self._calls

    def mask_for(self, start, length, loose=False):
        """(bytes, mask) for whole instructions covering [start, start+length).

        Masked: 4-byte immediates/displacements that are addresses inside the
        image, and relative branch/call displacements. With loose, 1-byte
        branch displacements too. Returns None if the bytes do not decode.
        """
        got = self.mask_fields(start, length, loose)
        return None if got is None else got[:2]

    def mask_fields(self, start, length, loose=False):
        """mask_for plus the 4-byte fields it masked, as
        [(offset, insn_end_offset, is_relative, absolute_value)]."""
        insns = []
        end = start
        for i in self.decode(start, length + 16):
            insns.append(i)
            end = i.address + i.size
            if end >= start + length:
                break
        if end < start + length:
            return None
        data = bytearray(self.read(start, end - start))
        mask = bytearray(b"\xff" * len(data))
        fields = []
        for i in insns:
            base = i.address - start
            rel = (capstone.x86.X86_GRP_JUMP in i.groups or capstone.x86.X86_GRP_CALL in i.groups)
            if i.imm_size and i.imm_offset:
                imm = i.operands[-1].imm & 0xFFFFFFFF if i.operands and i.operands[-1].type == capstone.x86.X86_OP_IMM else None
                masked = False
                if rel and (i.imm_size == 4 or loose):
                    masked = True
                elif i.imm_size == 4 and imm is not None and self.in_image(imm):
                    masked = True
                elif i.imm_size == 4:
                    raw = struct.unpack_from("<I", data, base + i.imm_offset)[0]
                    masked = self.in_image(raw)
                if masked:
                    for k in range(i.imm_size):
                        mask[base + i.imm_offset + k] = 0
                    if i.imm_size == 4:
                        o = base + i.imm_offset
                        raw = struct.unpack_from("<I", data, o)[0]
                        value = (i.address + i.size + raw) & 0xFFFFFFFF if rel else raw
                        fields.append((o, base + i.size, rel, value))
            if i.disp_size == 4 and i.disp_offset:
                raw = struct.unpack_from("<I", data, base + i.disp_offset)[0]
                if self.in_image(raw):
                    for k in range(4):
                        mask[base + i.disp_offset + k] = 0
                    fields.append((base + i.disp_offset, base + i.size, False, raw))
        return bytes(data), bytes(mask), fields

    # -- references -------------------------------------------------------

    def operand_xrefs(self, target, limit=MAX_XREFS):
        """Instructions in .text whose 4-byte operand equals target.

        Returns [(insn_start, operand_offset)].
        """
        needle = struct.pack("<I", target)
        out = []
        pos = self.text.find(needle)
        while pos >= 0 and len(out) < limit:
            va = self.text_lo + pos
            for back in range(1, 11):
                s = va - back
                insn = next(iter(self.decode(s, 16)), None)
                if insn is None or insn.address + insn.size < va + 4:
                    continue
                if (insn.disp_size == 4 and insn.disp_offset == back) or (insn.imm_size == 4 and insn.imm_offset == back):
                    # The instruction must sit on a real boundary.
                    if s in self.boundaries_before(s, 40) or s - 40 < self.text_lo:
                        out.append((s, back))
                        break
            pos = self.text.find(needle, pos + 1)
        return out

    def referenced_dwords(self):
        """Sorted list of in-image dwords that appear as operands in .text."""
        if self._xref_index is None:
            vals = set()
            t = self.text
            for pos in range(0, len(t) - 3):
                v = struct.unpack_from("<I", t, pos)[0]
                if self.in_image(v) and not self.in_text(v):
                    vals.add(v)
            self._xref_index = sorted(vals)
        return self._xref_index


# -- signature search ------------------------------------------------------

def to_regex(data, mask):
    parts = []
    for b, m in zip(data, mask):
        parts.append(re.escape(bytes([b])) if m else b".")
    return re.compile(b"".join(parts), re.DOTALL)


def find_all(img, data, mask, limit=3):
    rx = to_regex(data, mask)
    hits = []
    for m in rx.finditer(img.text):
        hits.append(img.text_lo + m.start())
        if len(hits) >= limit:
            break
    return hits


class Anchors:
    """Signature-independent old->new pairs, and the layout check built on them.

    A string whose text is unique in both builds pins its own address; if it
    is referenced exactly once in each build, the referencing instruction is
    pinned too. A patch inserts and removes bytes but keeps layout order, so
    the shift (new - old) is locally constant between edits. An answer whose
    shift disagrees with the anchors on both sides of it landed on a
    look-alike somewhere else (repeated binding code, inlined copies).
    """

    TOL = 0x20     # function alignment slack
    REACH = 0x4000 # anchors further away than this say nothing

    def __init__(self, old, new):
        so, sn = self._strings(old), self._strings(new)
        code, data = [], []
        for text, a in so.items():
            b = sn.get(text)
            if b is None:
                continue
            data.append((a, b - a))
            ra, rb = self._refs(old, a), self._refs(new, b)
            if len(ra) == 1 and len(rb) == 1:
                code.append((ra[0], rb[0] - ra[0]))
        self.code = self._clean(sorted(code))
        self.data = self._clean(sorted(data))

    @staticmethod
    def _strings(img):
        seen = collections.defaultdict(list)
        for lo, hi, ex in img.raw_spans:
            if ex:
                continue
            blob = bytes(img.mem[lo - img.base: hi - img.base])
            for m in re.finditer(rb"[\x20-\x7e]{6,}\x00", blob):
                seen[m.group()].append(lo + m.start())
        return {k: v[0] for k, v in seen.items() if len(v) == 1}

    @staticmethod
    def _refs(img, va):
        needle, out = struct.pack("<I", va), []
        p = img.text.find(needle)
        while p >= 0 and len(out) < 2:
            out.append(img.text_lo + p)
            p = img.text.find(needle, p + 1)
        return out

    @staticmethod
    def _clean(pairs):
        """Drop anchors that disagree with both neighbours (chance matches)."""
        keep = []
        for i, (a, d) in enumerate(pairs):
            prev = pairs[i - 1][1] if i else None
            nxt = pairs[i + 1][1] if i + 1 < len(pairs) else None
            if prev is None or nxt is None or abs(d - prev) <= Anchors.TOL or abs(d - nxt) <= Anchors.TOL:
                keep.append((a, d))
        return keep

    def check(self, old_va, new_va, in_text):
        """True/False when anchors bracket old_va, None when they do not."""
        pairs = self.code if in_text else self.data
        if not pairs:
            return None
        i = bisect.bisect_left(pairs, (old_va, -(1 << 40)))
        left = pairs[i - 1] if i and old_va - pairs[i - 1][0] <= self.REACH else None
        right = pairs[i] if i < len(pairs) and pairs[i][0] - old_va <= self.REACH else None
        if left is None or right is None:
            return None
        d, dl, dr = new_va - old_va, left[1], right[1]
        if dl == dr:
            # Nothing between the anchors moved relative to them: an exact
            # shift is required (repeated table code sits closer than TOL).
            return d == dl
        if not in_text:
            return None   # the linker reorders pooled data; no local rule
        # An edit lies between the anchors; the shift steps from dl to dr.
        return min(dl, dr) - self.TOL <= d <= max(dl, dr) + self.TOL


class CodePorter:
    def __init__(self, old, new, anchors=None):
        self.old, self.new = old, new
        self.anchors = anchors
        self.cache = {}
        self.data = None      # DataPorter, set by Porter
        self._busy = set()    # addresses being ported, to break reference cycles
        self._nest = 0        # fallback nesting depth (see port)

    def _window(self, start, target, length, loose):
        """Grow a signature at start until unique in old; return new hits."""
        got = self.old.mask_for(start, length, loose)
        if got is None:
            return None
        data, mask = got
        if target - start >= len(data):
            return None
        if len(find_all(self.old, data, mask, 2)) != 1:
            return "ambiguous"
        hits = find_all(self.new, data, mask, 3)
        return [h + (target - start) for h in hits], len(data)

    def port(self, va, depth=0):
        """Carry a code address across. Returns a result dict.

        Byte signatures first. When those cannot tell the target apart (code
        the compiler emitted several identical copies of, or a short tail
        such as call/pop/ret), fall back to carrying its callers or operand
        references across, and then to its containing function's entry.
        """
        # Fallbacks port other addresses, which may fall back in turn; only
        # the outermost MAX_NEST levels may, so a chain of look-alikes cannot
        # recurse without bound. The cache key records whether they were
        # allowed, so a shallow answer is never reused as a full one.
        full = depth == 0 and self._nest < MAX_NEST
        key = (va, full)
        if key in self.cache:
            return self.cache[key]
        if not self.old.in_text(va):
            return {"status": "NOT-CODE"}
        r = self._port_sig(va)
        if r["status"] not in ("OK",) and full:
            ev = list(r.get("evidence", []))
            if va not in self._busy:
                self._busy.add(va)
                self._nest += 1
                try:
                    ev += self._port_refs(va)
                    ev += self._port_pinned(va)
                    ev += self._port_via_function(va)
                finally:
                    self._nest -= 1
                    self._busy.discard(va)
            r = self._decide(ev, va) if ev else r
        self.cache[key] = r
        return r

    def _decide(self, evidence, va):
        rejected = []
        if self.anchors is not None:
            keep = []
            for e in evidence:
                (keep if self.anchors.check(va, e["new"], True) is not False else rejected).append(e)
            evidence = keep
        cands = collections.Counter(e["new"] for e in evidence)
        if not cands:
            status = "SHIFT-MISMATCH" if rejected else "NOTFOUND"
            return {"status": status, "evidence": rejected,
                    "candidates": sorted({e["new"] for e in rejected})}
        if len(cands) > 1:
            return {"status": "CONFLICT", "evidence": evidence, "candidates": sorted(cands)}
        new = next(iter(cands))
        strict = [e for e in evidence if not e["strategy"].endswith("~")]
        # One signature hit alone is not enough: when the code around the
        # target was edited, a leftover look-alike can be the only match.
        # Accept two independent agreeing signals, an operand-verified hit,
        # or one hit that the anchors on both sides confirm.
        strong = any(e["strategy"].startswith(("pinned", "function+")) for e in evidence)
        layout = self.anchors.check(va, new, True) if self.anchors is not None else None
        ok = len(evidence) >= 2 or strong or layout is True
        return {"status": "OK" if ok and strict else "WEAK", "new": new, "evidence": evidence,
                "layout": layout}

    def _port_refs(self, va):
        """Callers (rel32 call/jmp) and operand references, carried across."""
        ev = []
        for site in self.old.call_index().get(va, [])[:MAX_XREFS]:
            r = self.port(site, depth=1)
            if r["status"] == "OK":
                op = self.new.read(r["new"], 5)
                if op and op[0] == self.old.read(site, 1)[0]:
                    tgt = (r["new"] + 5 + struct.unpack("<i", op[1:5])[0]) & 0xFFFFFFFF
                    ev.append({"strategy": "ref-call", "new": tgt, "len": 0})
        for insn, off in self.old.operand_xrefs(va, 8):
            r = self.port(insn, depth=1)
            if r["status"] == "OK":
                v = self.new.dword(r["new"] + off)
                if v is not None:
                    ev.append({"strategy": "ref-operand", "new": v, "len": 0})
        return ev

    def _port_pinned(self, va):
        """Tell identical-looking copies apart by their masked operands.

        Carries the absolute addresses and call targets the signature masked
        out across on their own (globals by their other references, callees
        as code), then keeps the only new hit whose operands are those.
        """
        bounds = self.old.boundaries_before(va)
        start = va if va in bounds else max([b for b in bounds if b < va], default=None)
        if start is None:
            return []
        ported = {}

        def carry(value):
            if value not in ported:
                ported[value] = None
                if value not in self._busy:
                    self._busy.add(value)
                    try:
                        if self.old.in_text(value):
                            r = self.port(value, depth=1)
                        elif self.data is not None:
                            r = self.data.port(value)
                        else:
                            r = {}
                    finally:
                        self._busy.discard(value)
                    if r.get("status") == "OK":
                        ported[value] = r["new"]
            return ported[value]

        def field(h, off, end, rel):
            raw = self.new.dword(h + off)
            return (h + end + raw) & 0xFFFFFFFF if rel else raw

        for length in (16, 24, 32, 48, 64, 96, 128):
            got = self.old.mask_fields(start, (va - start) + length)
            if got is None:
                return []
            data, mask, fields = got
            if not fields:
                continue
            hits = find_all(self.new, data, mask, 512)
            if not hits:
                return []
            if len(hits) >= 512:
                continue
            pinned = [(o, e, rl, carry(v)) for o, e, rl, v in fields[:12]]
            pinned = [p for p in pinned if p[3] is not None]
            if not pinned:
                continue
            keep = [h for h in hits if all(field(h, o, e, rl) == v for o, e, rl, v in pinned)]
            if len(keep) == 1:
                return [{"strategy": "pinned%d" % len(pinned), "new": keep[0] + (va - start), "len": len(data)}]
            if not keep:
                return []
        return []

    def _port_via_function(self, va):
        f = self.old.function_start(va)
        if f is None or f == va:
            return []
        r = self.port(f, depth=1)
        if r["status"] != "OK":
            return []
        n = va - f + 16
        a, b = self.old.mask_for(f, n) or (None, None)
        if a is None:
            return []
        got = self.new.read(r["new"], len(a))
        if got is None or any(m and x != y for x, y, m in zip(a, got, b)):
            return []
        return [{"strategy": "function+%#x" % (va - f), "new": r["new"] + (va - f), "len": len(a)}]

    def _port_sig(self, va):
        old = self.old
        bounds = old.boundaries_before(va)
        starts = []
        if va in bounds:
            starts.append(("fwd", va))
            insn_start = va
        else:
            prior = [b for b in bounds if b < va]
            insn_start = prior[-1] if prior else None
            if insn_start is not None:
                starts.append(("insn", insn_start))
        for back in BACK_CONTEXT:
            cands = [b for b in bounds if va - back - 4 <= b <= va - back]
            if cands:
                starts.append(("back%d" % back, cands[0]))
        evidence = []
        for label, s in starts:
            for loose in (False, True):
                found = None
                for length in SIG_LENGTHS:
                    res = self._window(s, va, (va - s) + length, loose)
                    if res is None:
                        break
                    if res == "ambiguous":
                        continue
                    hits, n = res
                    if len(hits) == 1:
                        found = (hits[0], n)
                        continue          # keep growing: longer agreement is stronger
                    if not hits:
                        break             # a longer window cannot match either
                    # several hits in new although unique in old: keep growing
                if found:
                    evidence.append({"strategy": label + ("~" if loose else ""), "new": found[0], "len": found[1]})
                    break
        return self._decide(evidence, va)


class DataPorter:
    def __init__(self, old, new, code):
        self.old, self.new, self.code = old, new, code
        self.cache = {}

    def _vote(self, va):
        votes = collections.Counter()
        refs = self.old.operand_xrefs(va)
        for insn, off in refs:
            r = self.code.port(insn)
            if r["status"] in ("OK", "WEAK"):
                v = self.new.dword(r["new"] + off)
                if v is not None:
                    votes[v] += 2 if r["status"] == "OK" else 1
        return refs, votes

    def _confirmed(self, va, best, votes):
        """Two agreeing confident references, or identical initialised contents.

        One reference is not enough on its own: a patch can change which
        object an instruction uses (a mission script now pushing another
        file name), and the instruction still ports correctly while the
        object it used to name has moved elsewhere. Pooled data does not keep
        layout order, so the anchors cannot confirm data either.
        """
        if votes[best] >= 4:
            return True
        a, b = self.old.read(va, 16), self.new.read(best, 16)
        if not a or not b or not any(a[:4]):
            return False
        n = a.find(b"\0") + 1 if a[:1].isalnum() else 16  # strings: compare text
        return n >= 4 and a[:n] == b[:n]

    def port(self, va):
        if va in self.cache:
            return self.cache[va]
        refs, votes = self._vote(va)
        if votes:
            (best, n), total = votes.most_common(1)[0], sum(votes.values())
            status = "OK" if n >= 2 and n * 4 >= total * 3 else ("WEAK" if n == total else "CONFLICT")
            if status == "OK" and not self._confirmed(va, best, votes):
                status = "WEAK"
            r = {"status": status, "new": best, "refs": len(refs), "votes": dict(votes)}
            if status == "OK" and self.code.anchors is not None and \
                    self.code.anchors.check(va, best, False) is False:
                status = r["status"] = "SHIFT-MISMATCH"
            if status == "CONFLICT":
                r["candidates"] = sorted(votes)
                r.pop("new")
        else:
            # Nothing references it directly: place it next to the closest
            # referenced neighbour (struct members, array tails, vtable slots).
            idx = self.old.referenced_dwords()
            i = bisect.bisect_right(idx, va)
            neigh = [idx[j] for j in (i - 1, i - 2, i, i + 1) if 0 <= j < len(idx) and abs(idx[j] - va) <= 0x200]
            neigh.sort(key=lambda n: abs(n - va))
            r = {"status": "NOTFOUND", "refs": 0}
            for n in neigh[:3]:
                _, nv = self._vote(n)
                if nv:
                    best, cnt = nv.most_common(1)[0]
                    if cnt * 4 >= sum(nv.values()) * 3:
                        r = {"status": "INFERRED", "new": best + (va - n), "via": "0x%08X%+d" % (n, va - n)}
                        break
        if r["status"] in ("INFERRED", "WEAK"):
            # A slot holding a code pointer (vtable entry, callback table) is
            # confirmed when the function it points at carries across to
            # exactly what the new slot holds.
            c = self.old.dword(va)
            if c is not None and self.old.in_text(c):
                f = self.code.port(c)
                if f["status"] == "OK" and self.new.dword(r["new"]) == f["new"]:
                    r = dict(r, status="OK", via=r.get("via", "xrefs") + "; slot holds ported 0x%08X" % f["new"])
        self.cache[va] = r
        return r


# -- patches.json ---------------------------------------------------------

def parse_hex(s):
    return int(s, 16)


def fmt(va):
    return "0x%08X" % va


def parse_pattern(p):
    data, mask = bytearray(), bytearray()
    for t in p.split():
        if t.startswith("?"):
            data.append(0)
            mask.append(0)
        else:
            data.append(int(t, 16))
            mask.append(0xFF)
    return bytes(data), bytes(mask)


def render_pattern(data, mask):
    return " ".join("%02X" % b if m else "??" for b, m in zip(data, mask))


def scan(img, pattern, limit=3):
    d, m = parse_pattern(pattern)
    return find_all(img, d, m, limit)


class Porter:
    def __init__(self, old, new):
        self.old, self.new = old, new
        self.anchors = Anchors(old, new)
        self.code = CodePorter(old, new, self.anchors)
        self.data = DataPorter(old, new, self.code)
        self.code.data = self.data

    def port_any(self, va):
        if self.old.in_text(va):
            r = dict(self.code.port(va))
            r["kind"] = "code"
        elif self.old.in_image(va):
            r = dict(self.data.port(va))
            r["kind"] = "data"
        else:
            r = {"status": "NOT-IN-IMAGE", "kind": "?"}
        return r

    def rebase_bytes(self, old_va, new_va, old_bytes_hex, keep_mask=None):
        """New guard/pattern bytes at new_va, if they differ from the old ones
        only where the old instructions hold movable addresses."""
        od, om = parse_pattern(old_bytes_hex)
        n = len(od)
        nd = self.new.read(new_va, n)
        if nd is None:
            return None, "unreadable"
        got = self.old.mask_for(old_va, n)
        mv = got[1][:n] if got else b"\xff" * n
        diffs = [i for i in range(n) if om[i] and nd[i] != od[i]]
        bad = [i for i in diffs if mv[i]]
        if bad:
            return None, "bytes differ at +%s" % ",".join("%d" % i for i in bad[:6])
        return render_pattern(nd, om), ("rebased %d byte(s)" % len(diffs) if diffs else "same")

    def port_pattern_entry(self, e, result_of):
        """Shared logic for patches/resolves/globals entries with a pattern."""
        out = {}
        old_hits = scan(self.old, e["pattern"])
        new_hits = scan(self.new, e["pattern"])
        out["old_hits"], out["new_hits"] = len(old_hits), len(new_hits)
        off = e.get("offset", 0)
        if len(old_hits) != 1:
            out["status"] = "OLD-PATTERN-%d" % len(old_hits)
            return out
        m_old = old_hits[0]
        r = self.code.port(m_old)
        if r["status"] not in ("OK", "WEAK"):
            # The pattern start may have changed while the anchor did not.
            r2 = self.code.port(m_old + off)
            if r2["status"] in ("OK", "WEAK"):
                r = dict(r2)
                r["new"] -= off
            else:
                out["status"] = r["status"]
                out["evidence"] = r.get("evidence")
                return out
        m_new = r["new"]
        out["status"] = r["status"]
        if len(new_hits) == 1 and new_hits[0] != m_new:
            out["status"] = "CONFLICT"
            out["detail"] = "old pattern matches new at %s, port says %s" % (fmt(new_hits[0]), fmt(m_new))
            return out
        pat, why = self.rebase_bytes(m_old, m_new, e["pattern"])
        if pat is None:
            out["status"] = "CHANGED"
            out["detail"] = "pattern " + why
            return out
        out["pattern"] = pat
        out["pattern_note"] = why
        if len(scan(self.new, pat)) != 1:
            out["status"] = "NEW-PATTERN-NOT-UNIQUE"
        anchor_old, anchor_new = m_old + off, m_new + off
        out["result"] = result_of(anchor_old, anchor_new)
        return out


def anchor_result(img, anchor, mode):
    if mode == "rel32_target":
        if img.read(anchor, 1) != b"\xE8":
            return None
        return (anchor + 5 + struct.unpack("<i", img.read(anchor + 1, 4))[0]) & 0xFFFFFFFF
    if mode == "abs32_operand":
        return img.dword(anchor)
    return anchor


def port_patches(p, d):
    rows = []
    out = json.loads(json.dumps(d))

    def row(section, e, old, res, new=None, note=""):
        rows.append({"section": section, "name": e.get("name", section), "old": old,
                     "new": new, "status": res, "note": note})

    for i, e in enumerate(d.get("patches", [])):
        o = out["patches"][i]
        old = parse_hex(e["fallback"]) or None
        r = p.port_pattern_entry(e, lambda a_old, a_new: (a_old, a_new))
        if "result" in r:
            a_old, a_new = r["result"]
            note = r.get("pattern_note", "")
            if old is not None and a_old != old:
                note += "; fallback was %s but pattern+offset is %s" % (fmt(old), fmt(a_old))
            if r["status"] == "OK":
                o["pattern"] = r["pattern"]
                if old is not None:
                    o["fallback"] = fmt(a_new)
            row("patches", e, old, r["status"], a_new, note)
        else:
            row("patches", e, old, r["status"], None, r.get("detail", "old hits %s" % r.get("old_hits")))

    for i, e in enumerate(d.get("resolves", [])):
        o = out["resolves"][i]
        mode = e.get("mode", "address")
        old = parse_hex(e["fallback"]) if "fallback" in e else None

        def res(a_old, a_new, mode=mode):
            return anchor_result(p.old, a_old, mode), anchor_result(p.new, a_new, mode)
        r = p.port_pattern_entry(e, res)
        if "result" in r:
            v_old, v_new = r["result"]
            note = r.get("pattern_note", "")
            status = r["status"]
            if v_new is None:
                status, note = "CHANGED", "anchor in new build is not a %s" % mode
            elif old is not None and v_old != old:
                note += "; fallback %s differs from scanned %s" % (fmt(old), fmt(v_old))
            if old is not None and v_new is not None:
                # Cross-check: carry the fallback itself across independently.
                ind = p.port_any(old)
                if ind.get("status") in ("OK", "WEAK") and ind["new"] != v_new:
                    status, note = "CONFLICT", note + "; fallback ports to %s" % fmt(ind["new"])
            if status == "OK":
                o["pattern"] = r["pattern"]
                if old is not None:
                    o["fallback"] = fmt(v_new)
            row("resolves", e, old, status, v_new, note)
        elif old is not None and e.get("prefer") == "fallback":
            ind = p.port_any(old)
            if ind.get("status") == "OK":
                o["fallback"] = fmt(ind["new"])
            row("resolves", e, old, ind["status"], ind.get("new"), "pinned fallback; pattern: " + r["status"])
        else:
            row("resolves", e, old, r["status"], None, r.get("detail", "old hits %s" % r.get("old_hits")))

    for i, e in enumerate(d.get("engine_addresses", [])):
        o = out["engine_addresses"][i]
        old = parse_hex(e["address"])
        r = p.port_any(old)
        status, note, new = r["status"], "", r.get("new")
        if status in ("OK", "WEAK") and "expected" in e:
            exp, why = p.rebase_bytes(old, new, e["expected"])
            if exp is None:
                status, note = "CHANGED", "expected " + why
            else:
                note = "expected " + why
                if status == "OK":
                    o["expected"] = exp
        elif status == "INFERRED":
            note = "via " + r["via"]
        if status == "OK":
            o["address"] = fmt(new)
        row("engine_addresses", e, old, status, new, note)

    for i, e in enumerate(d.get("globals", [])):
        o = out["globals"][i]
        old = parse_hex(e["fallback"])
        r = p.port_any(old)
        status, note, new = r["status"], "", r.get("new")
        if "pattern" in e:
            pr = p.port_pattern_entry(e, lambda a, b: (a, b))
            if pr.get("result") and pr["result"][1] != new:
                status, note = "CONFLICT", "pattern says %s" % fmt(pr["result"][1])
            elif "pattern" in pr and status == "OK":
                o["pattern"] = pr["pattern"]
        if status in ("OK", "WEAK") and "expected_original" in e:
            exp, why = p.rebase_bytes(old, new, e["expected_original"])
            if exp is None:
                status, note = "CHANGED", "expected_original " + why
            else:
                note = (note + "; " if note else "") + "expected_original " + why
                if status == "OK":
                    o["expected_original"] = exp
        if status == "OK":
            o["fallback"] = fmt(new)
        row("globals", e, old, status, new, note)

    for i, e in enumerate(d.get("static_pointers", [])):
        o = out["static_pointers"][i]
        old = parse_hex(e["address"])
        r = p.port_any(old)
        if r["status"] == "OK":
            o["address"] = fmt(r["new"])
        row("static_pointers", e, old, r["status"], r.get("new"), r.get("via", r["kind"]))

    agp = d.get("audio_gas_pattern")
    if agp:
        n_old, n_new = len(scan(p.old, agp["pattern"])), len(scan(p.new, agp["pattern"]))
        row("audio_gas_pattern", {"name": "audio_gas_pattern"}, None,
            "OK" if n_new == 1 else "CHANGED", None, "old hits %d, new hits %d" % (n_old, n_new))
    return out, rows


def write_report(path, rows, old, new, extra_rows=()):
    allrows = list(rows) + list(extra_rows)
    cnt = collections.Counter(r["status"] for r in allrows)
    deltas = collections.Counter((r["new"] - r["old"]) for r in allrows
                                 if r["status"] == "OK" and r["old"] is not None and r["new"] is not None)
    lines = ["# patches.json port report", "",
             "- old: `%s` (timestamp 0x%08X)" % (old.path, old.timestamp),
             "- new: `%s` (timestamp 0x%08X)" % (new.path, new.timestamp),
             "- result: " + ", ".join("%s %d" % kv for kv in sorted(cnt.items())),
             "- most common address shifts: " + ", ".join("%+#x x%d" % kv for kv in deltas.most_common(6)),
             "",
             "Only OK rows are written to the ported json. Everything else keeps its old",
             "value, so the runtime guards keep rejecting it until it is fixed by hand.",
             "", "| status | section | name | old | new | note |", "|---|---|---|---|---|---|"]
    order = {"CONFLICT": 0, "CHANGED": 1, "NOTFOUND": 2, "WEAK": 3, "INFERRED": 4}
    for r in sorted(allrows, key=lambda r: (order.get(r["status"], 5), r["section"])):
        lines.append("| %s | %s | %s | %s | %s | %s |" % (
            r["status"], r["section"], r["name"].replace("|", "/"),
            fmt(r["old"]) if r["old"] is not None else "",
            fmt(r["new"]) if r["new"] is not None else "", r["note"].replace("|", "/")))
    Path(path).write_text("\n".join(lines) + "\n", encoding="utf-8")
    return cnt


def entropy(b):
    c = collections.Counter(b)
    return -sum(v / len(b) * math.log2(v / len(b)) for v in c.values()) if b else 0.0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("old_exe")
    ap.add_argument("new_exe")
    ap.add_argument("--patches", default=str(REPO / "scripts" / "patches.json"))
    ap.add_argument("--out", default="ported_patches.json")
    ap.add_argument("--report", default="port_report.md")
    ap.add_argument("--addresses", help="extra addresses to carry across, one hex value per line (e.g. literals still in C++)")
    a = ap.parse_args()

    old, new = Image(a.old_exe), Image(a.new_exe)
    for img in (old, new):
        if entropy(img.text[:1 << 20]) > 7.9:
            sys.exit("%s: .text looks encrypted (SteamStub); unpack it with Steamless first" % img.path)
    p = Porter(old, new)
    d = json.loads(Path(a.patches).read_text(encoding="utf-8"))
    out, rows = port_patches(p, d)

    extra = []
    if a.addresses:
        for line in Path(a.addresses).read_text().split():
            va = int(line, 16)
            r = p.port_any(va)
            extra.append({"section": "extra", "name": fmt(va), "old": va, "new": r.get("new"),
                          "status": r["status"], "note": r.get("via", r["kind"])})

    Path(a.out).write_text(json.dumps(out, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    cnt = write_report(a.report, rows, old, new, extra)
    print("ported:", ", ".join("%s=%d" % kv for kv in sorted(cnt.items())))
    print("json  :", a.out)
    print("report:", a.report)


if __name__ == "__main__":
    main()
