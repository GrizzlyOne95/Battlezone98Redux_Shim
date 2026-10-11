#!/usr/bin/env python3
"""Generate scripts/patches.json engine_addresses rows for addresses that
feature code still writes as literals.

  python make_engine_rows.py battlezone98redux.exe Name=0x00ABCDEF[:note] ...
  python make_engine_rows.py battlezone98redux.exe --from rows.txt

Code rows get guard bytes: whole instructions covering at least --guard bytes
from the address, taken from the exe (which must be the reference build).
ResolveEngineAddress compares them with live memory, so on any other build
the row reads as Mismatch and the feature stands down. Data rows (anything
outside .text: globals, vtables, tables) are written as kind "data"; they
carry no guard, so port_patches.py is what keeps them honest across builds.

Prints a JSON array of rows to stdout, ready to paste into engine_addresses.
"""
import argparse
import json
import sys

import port_patches as pp


def row(img, name, va, note, guard):
    r = {"name": name, "address": "0x%08X" % va}
    if img.in_text(va):
        if va not in img.boundaries_before(va):
            sys.exit("%s 0x%08X is not an instruction start; guard its instruction instead" % (name, va))
        got = img.mask_for(va, guard)
        if got is None:
            sys.exit("%s 0x%08X does not decode" % (name, va))
        r["expected"] = " ".join("%02X" % b for b in got[0])
    elif img.in_image(va):
        r["kind"] = "data"
    else:
        sys.exit("%s 0x%08X is outside the image" % (name, va))
    if note:
        r["identity"] = note
    return r


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("exe")
    ap.add_argument("specs", nargs="*", help="Name=0xADDRESS[:identity note]")
    ap.add_argument("--from", dest="from_file", help="file with one spec per line")
    ap.add_argument("--guard", type=int, default=12, help="minimum guard bytes for code rows")
    a = ap.parse_args()
    specs = list(a.specs)
    if a.from_file:
        specs += [l.strip() for l in open(a.from_file, encoding="utf-8") if l.strip() and not l.startswith("#")]
    img = pp.Image(a.exe)
    rows = []
    for spec in specs:
        name, rest = spec.split("=", 1)
        addr, _, note = rest.partition(":")
        rows.append(row(img, name.strip(), int(addr, 16), note.strip(), a.guard))
    print(json.dumps(rows, indent=2))


if __name__ == "__main__":
    main()
