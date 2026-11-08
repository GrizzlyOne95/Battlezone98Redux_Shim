"""Build openshim_dxbc_seed.pack from a warm shader_cache/dxbc directory.

Usage: python tools/build_dxbc_seed.py <game root>/shader_cache/dxbc resources/renderer/enhanced/openshim_dxbc_seed.pack

Warm the cache first: a clean shader_cache, then main menu, an MP game room
and a mission on the settings players use. Layout: include/dxbc_cache_policy.h.
"""
import struct
import sys
from pathlib import Path

MAGIC = 0x43425844
ENTRY_VERSION = 2
HEADER = struct.Struct("<IIQIIQ")


def main(src: str, dst: str) -> int:
    entries = {}
    skipped = 0
    for f in sorted(Path(src).glob("*.dxbc")):
        data = f.read_bytes()
        if len(data) < HEADER.size:
            skipped += 1
            continue
        magic, version, key, _pre, blob_size, _hash = HEADER.unpack_from(data)
        if (magic != MAGIC or version != ENTRY_VERSION or blob_size != len(data) - HEADER.size
                or f.stem.lower() != f"{key:016x}" or data[HEADER.size:HEADER.size + 4] != b"DXBC"):
            skipped += 1
            continue
        entries[key] = data
    out = bytearray(b"OSDXSEED")
    out += struct.pack("<II", 1, len(entries))
    for key in sorted(entries):
        out += struct.pack("<I", len(entries[key])) + entries[key]
    Path(dst).write_bytes(out)
    print(f"{len(entries)} entries, {len(out)} bytes -> {dst} (skipped {skipped})")
    return 0


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    sys.exit(main(sys.argv[1], sys.argv[2]))
