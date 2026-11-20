#!/usr/bin/env python3
"""Build the single-player player-paint masks from Campaign Reimagined's.

Campaign Reimagined ships one co-op team mask per unit texture
(Assets/Textures/crteam_<stem>_d.dds: 512x512 DXT5 with full mips, paint
weight in alpha) and a `<material>_tm` twin per painted material
(Materials/CR_TeamSkins.material, `set_texture_alias TeamMask ...`).

This script keeps the twins whose `<material>` is a stock Redux material with
the same DiffuseMap (so the mask's UVs fit), and for each mask they use writes
resources/renderer/enhanced/openshim_paint_<stem>.dds as BC4 (one channel,
read as .r by OSE_TEAM_MASK_R). A DXT5 alpha block is bit-identical to a BC4
block, so the conversion copies the first 8 bytes of every 16-byte block, mips
included, and is lossless.

It also writes the neutral openshim_team_off.dds (4x4 BC4, all zero) the stock
import binds by default, and include/sp_player_paint_masks.inc, the
material -> mask table include/sp_player_paint_policy.h compiles in.

Usage:
  python scripts/build_sp_paint_masks.py \
      --game-dir "<Battlezone 98 Redux>" \
      --cr-dir "<Campaign-Reimagined>" [--check]
"""

import argparse
import os
import re
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
PAYLOAD = REPO / "resources" / "renderer" / "enhanced"
TABLE = REPO / "include" / "sp_player_paint_masks.inc"
OFF_NAME = "openshim_team_off.dds"
PREFIX = "openshim_paint_"

DDSD_CAPS, DDSD_HEIGHT, DDSD_WIDTH, DDSD_PIXELFORMAT = 0x1, 0x2, 0x4, 0x1000
DDSD_MIPMAPCOUNT, DDSD_LINEARSIZE = 0x20000, 0x80000
DDPF_FOURCC = 0x4
DDSCAPS_COMPLEX, DDSCAPS_TEXTURE, DDSCAPS_MIPMAP = 0x8, 0x1000, 0x400000


def material_blocks(text):
    """(name, body) for every top-level `material <name> [: parent] { ... }`."""
    text = re.sub(r"//[^\n]*", "", text)
    out = []
    for m in re.finditer(r"^[ \t]*material[ \t]+([^\s:{]+)[^{\n]*\s*\{", text, re.M):
        depth, pos = 0, text.index("{", m.start())
        start = pos
        while pos < len(text):
            if text[pos] == "{":
                depth += 1
            elif text[pos] == "}":
                depth -= 1
                if depth == 0:
                    break
            pos += 1
        out.append((m.group(1), text[start:pos + 1]))
    return out


def alias(body, name):
    m = re.search(r"\bset_texture_alias[ \t]+" + name + r"[ \t]+(\S+)", body)
    return m.group(1).lower() if m else None


def stock_materials(game_dir):
    found = {}
    for sub in ("BZ_ASSETS", "BZ_ASSETS_CORE"):
        for root, _, files in os.walk(game_dir / sub):
            for f in files:
                if f.lower().endswith(".material"):
                    text = (Path(root) / f).read_text(encoding="latin-1")
                    for name, body in material_blocks(text):
                        found.setdefault(name.lower(), alias(body, "DiffuseMap"))
    return found


def dds_header(width, height, mips, top_size, fourcc):
    flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_LINEARSIZE
    caps = DDSCAPS_TEXTURE
    if mips > 1:
        flags |= DDSD_MIPMAPCOUNT
        caps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP
    pixel_format = struct.pack("<II4s5I", 32, DDPF_FOURCC, fourcc, 0, 0, 0, 0, 0)
    header = struct.pack("<7I", 124, flags, height, width, top_size, 0, mips) + b"\0" * 44
    header += pixel_format + struct.pack("<5I", caps, 0, 0, 0, 0)
    assert len(header) == 124
    return b"DDS " + header


def dxt5_to_bc4(data, source):
    if data[:4] != b"DDS ":
        raise ValueError(f"{source}: not a DDS file")
    size, _, height, width, _, _, mips = struct.unpack_from("<7I", data, 4)
    fourcc = data[84:88]
    if size != 124 or fourcc != b"DXT5":
        raise ValueError(f"{source}: expected a DXT5 DDS, got {fourcc!r}")
    mips = max(mips, 1)
    pos, out = 128, bytearray()
    w, h = width, height
    for _ in range(mips):
        blocks = max(1, (w + 3) // 4) * max(1, (h + 3) // 4)
        level = data[pos:pos + blocks * 16]
        if len(level) != blocks * 16:
            raise ValueError(f"{source}: truncated mip {w}x{h}")
        for i in range(0, len(level), 16):
            out += level[i:i + 8]
        pos += blocks * 16
        w, h = max(1, w // 2), max(1, h // 2)
    top = max(1, (width + 3) // 4) * max(1, (height + 3) // 4) * 8
    return dds_header(width, height, mips, top, b"ATI1") + bytes(out)


def off_texture():
    return dds_header(4, 4, 1, 8, b"ATI1") + b"\0" * 8


def build(game_dir, cr_dir):
    stock = stock_materials(game_dir)
    skins = (cr_dir / "Materials" / "CR_TeamSkins.material").read_text(encoding="latin-1")
    table, masks, skipped = [], {}, []
    for name, body in material_blocks(skins):
        if not name.lower().endswith("_tm"):
            continue
        source = name[:-3]
        mask = alias(body, "TeamMask")
        diffuse = alias(body, "DiffuseMap")
        if source.lower() not in stock:
            skipped.append(f"{source} (not stock)")
            continue
        if not mask or stock[source.lower()] != diffuse:
            skipped.append(f"{source} (DiffuseMap {stock[source.lower()]} != {diffuse})")
            continue
        m = re.fullmatch(r"crteam_(\w+)_d\.dds", mask)
        if not m:
            raise ValueError(f"{name}: unexpected TeamMask name {mask}")
        out_name = PREFIX + m.group(1) + ".dds"
        if out_name not in masks:
            path = cr_dir / "Assets" / "Textures" / mask
            masks[out_name] = dxt5_to_bc4(path.read_bytes(), path.name)
        table.append((source.lower(), out_name))
    table.sort()
    lines = [
        "// GENERATED by scripts/build_sp_paint_masks.py -- do not edit.",
        "// Stock material -> single-player paint mask (BC4, openshim/renderer/enhanced).",
    ]
    lines += [f'{{ "{src}", "{mask}" }},' for src, mask in table]
    files = {PAYLOAD / k: v for k, v in masks.items()}
    files[PAYLOAD / OFF_NAME] = off_texture()
    files[TABLE] = ("\n".join(lines) + "\n").encode("ascii")
    return files, table, skipped


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--game-dir", required=True, type=Path)
    ap.add_argument("--cr-dir", required=True, type=Path)
    ap.add_argument("--check", action="store_true", help="fail if the checked-in outputs differ")
    args = ap.parse_args()
    files, table, skipped = build(args.game_dir, args.cr_dir)
    stale = sorted(p for p in PAYLOAD.glob(PREFIX + "*.dds") if p not in files)
    if args.check:
        bad = [str(p) for p, data in files.items() if not p.exists() or p.read_bytes() != data]
        bad += [f"{p} (no longer generated)" for p in stale]
        for b in bad:
            print("out of date:", b)
        return 1 if bad else 0
    for p in stale:
        p.unlink()
    for p, data in files.items():
        p.write_bytes(data)
    total = sum(len(v) for p, v in files.items() if p.suffix == ".dds")
    masks = sum(1 for p in files if p.name.startswith(PREFIX))
    print(f"{len(table)} materials, {masks} masks + {OFF_NAME}, {total / 1024 / 1024:.2f} MB")
    for s in skipped:
        print("skipped:", s)
    return 0


if __name__ == "__main__":
    sys.exit(main())
