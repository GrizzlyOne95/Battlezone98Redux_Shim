#!/usr/bin/env python3
"""Convert terrain HD paint colour and _n tiles from PNG to DXT5 DDS.

Colour and normal+height slices may ship as DXT5 (BC3) with a full mip chain;
control maps stay uncompressed PNG because the shim builds them into their own
uncompressed array and live paint rewrites them. Every one of these images
uses alpha (height or layer weight), so DXT1 is not an option.

The script never touches its input. It writes the DDS files and a rewritten
copy of the manifest into --out, mirroring paths relative to the mod folder,
so the result can be reviewed and then copied over the mod. PNGs the
rewritten manifest no longer names are listed, not deleted: other content
may still load them.

  python scripts/Convert-TerrainPaintDds.py MOD_DIR cr_terrain_hd.json --dry-run
  python scripts/Convert-TerrainPaintDds.py MOD_DIR cr_terrain_hd.json --out OUT_DIR

A material is converted whole or not at all: if any of its colour/_n slices
cannot convert (missing file, also used as a control elsewhere), it keeps
PNG for every slice, since one array cannot mix formats.
"""
from __future__ import annotations

import argparse
import io
import json
import os
import struct
import sys

CONTROL_SLICES = {5: {4}, 9: {4}, 18: {4, 13}}
DDS_HEADER = 128
DDSD_MIPMAPCOUNT = 0x20000
DDSCAPS_COMPLEX, DDSCAPS_TEXTURE, DDSCAPS_MIPMAP = 0x8, 0x1000, 0x400000


def dxt5_bytes(width: int, height: int) -> int:
    """Payload bytes of a full DXT5 mip chain (no header)."""
    total = 0
    while True:
        total += max(1, (width + 3) // 4) * max(1, (height + 3) // 4) * 16
        if width == 1 and height == 1:
            return total
        width, height = max(1, width // 2), max(1, height // 2)


def png_size(path: str) -> tuple[int, int]:
    with open(path, "rb") as handle:
        head = handle.read(24)
    if head[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError(f"not a PNG: {path}")
    return struct.unpack(">II", head[16:24])


def encode_dxt5_mips(path: str) -> bytes:
    """One DDS: a DXT5 header with a mip count, then every level's blocks."""
    from PIL import Image  # imported late so --dry-run needs no Pillow

    image = Image.open(path).convert("RGBA")
    header = None
    levels = []
    while True:
        buffer = io.BytesIO()
        image.save(buffer, "DDS", pixel_format="DXT5")
        data = buffer.getvalue()
        if data[:4] != b"DDS " or data[84:88] != b"DXT5":
            raise RuntimeError("Pillow did not write a legacy DXT5 header")
        if header is None:
            header = bytearray(data[:DDS_HEADER])
        expected = max(1, (image.width + 3) // 4) * max(1, (image.height + 3) // 4) * 16
        if len(data) - DDS_HEADER != expected:
            raise RuntimeError(f"unexpected DXT5 level size {len(data) - DDS_HEADER} != {expected}")
        levels.append(data[DDS_HEADER:])
        if image.width == 1 and image.height == 1:
            break
        # Alpha is height or weight, not coverage: resize each band on its
        # own, since resizing RGBA premultiplies colour by alpha.
        size = (max(1, image.width // 2), max(1, image.height // 2))
        image = Image.merge("RGBA", [band.resize(size, Image.Resampling.BOX) for band in image.split()])
    flags, = struct.unpack_from("<I", header, 8)
    struct.pack_into("<I", header, 8, flags | DDSD_MIPMAPCOUNT)
    struct.pack_into("<I", header, 28, len(levels))
    caps, = struct.unpack_from("<I", header, 108)
    struct.pack_into("<I", header, 108, caps | DDSCAPS_COMPLEX | DDSCAPS_TEXTURE | DDSCAPS_MIPMAP)
    return bytes(header) + b"".join(levels)


def index_mod(mod: str) -> dict[str, str]:
    found: dict[str, str] = {}
    for root, _, files in os.walk(mod):
        for name in files:
            found.setdefault(name.lower(), os.path.join(root, name))
    return found


def control_names(manifest: dict) -> set[str]:
    names: set[str] = set()
    for material in manifest.get("materials", {}).values():
        paint = material.get("paint")
        if not paint:
            continue
        for key, value in material.get("tiles", {}).items():
            if int(key) in CONTROL_SLICES.get(material.get("sliceCount", 0), set()):
                names.add(value.lower())
        for entry in paint.get("maps", []):
            for key in ("control", "control2"):
                if entry.get(key):
                    names.add(entry[key].lower())
    return names


def plan(manifest: dict, files: dict[str, str]):
    """Returns ({png name: path} to convert, {material: reason} skipped)."""
    controls = control_names(manifest)
    convert: dict[str, str] = {}
    skipped: dict[str, str] = {}
    for name, material in manifest.get("materials", {}).items():
        if not material.get("paint"):
            skipped[name] = "no paint block"
            continue
        control = CONTROL_SLICES.get(material.get("sliceCount", 0))
        if control is None:
            skipped[name] = f"sliceCount {material.get('sliceCount')} has no control layout"
            continue
        wanted = [v for k, v in material.get("tiles", {}).items() if int(k) not in control]
        if not material.get("fallback"):
            skipped[name] = "no fallback"
            continue
        wanted.append(material["fallback"])
        reason = None
        for value in wanted:
            lower = value.lower()
            if lower in controls:
                reason = f"{value} is also a control map"
            elif not lower.endswith((".png", ".dds")):
                reason = f"{value} is not PNG or DDS"
            elif lower.endswith(".png") and lower not in files:
                reason = f"{value} missing"
            if reason:
                break
        if reason:
            skipped[name] = reason
            continue
        for value in wanted:
            if value.lower().endswith(".png"):
                convert[value.lower()] = files[value.lower()]
    return convert, skipped


def rewrite(manifest: dict, converted: set[str], skipped: dict[str, str]) -> dict:
    """Swaps .png for .dds in converted materials only; a skipped material
    keeps PNG even where it shares a file with a converted one."""
    out = json.loads(json.dumps(manifest))
    swap = lambda value: value[:-4] + ".dds" if value.lower() in converted else value
    for name, material in out.get("materials", {}).items():
        if name in skipped:
            continue
        material["fallback"] = swap(material.get("fallback", ""))
        material["tiles"] = {k: swap(v) for k, v in material.get("tiles", {}).items()}
    return out


def referenced(manifest: dict) -> set[str]:
    names: set[str] = set()
    for material in manifest.get("materials", {}).values():
        names.add(material.get("fallback", "").lower())
        names.update(v.lower() for v in material.get("tiles", {}).values())
        for entry in (material.get("paint") or {}).get("maps", []):
            names.update(entry[k].lower() for k in ("control", "control2") if entry.get(k))
    return names


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("mod", help="mod folder holding the manifest and textures")
    parser.add_argument("manifest", help="manifest path relative to the mod folder")
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--dry-run", action="store_true", help="report sizes without encoding")
    mode.add_argument("--out", help="empty output folder for DDS files and the rewritten manifest")
    args = parser.parse_args()

    mod = os.path.abspath(args.mod)
    manifest_path = os.path.join(mod, args.manifest)
    with open(manifest_path, encoding="utf-8") as handle:
        manifest = json.load(handle)
    files = index_mod(mod)
    convert, skipped = plan(manifest, files)
    for name, reason in sorted(skipped.items()):
        print(f"skip material {name}: {reason}")

    if args.out:
        out = os.path.abspath(args.out)
        if os.path.splitdrive(out)[0].lower() == os.path.splitdrive(mod)[0].lower() and \
                os.path.commonpath([out, mod]) == mod:
            parser.error("--out must be outside the mod folder")
        if os.path.isdir(out) and os.listdir(out):
            parser.error("--out must be empty")

    before = after = 0
    for lower, path in sorted(convert.items()):
        before += os.path.getsize(path)
        if args.dry_run:
            width, height = png_size(path)
            after += DDS_HEADER + dxt5_bytes(width, height)
            continue
        data = encode_dxt5_mips(path)
        target = os.path.join(out, os.path.relpath(path, mod))[:-4] + ".dds"
        os.makedirs(os.path.dirname(target), exist_ok=True)
        with open(target, "wb") as handle:
            handle.write(data)
        after += len(data)
        print(f"wrote {os.path.relpath(target, out)} ({len(data) / 2**20:.1f} MiB)")

    rewritten = rewrite(manifest, set(convert), skipped)
    if args.out:
        target = os.path.join(out, args.manifest)
        os.makedirs(os.path.dirname(target) or out, exist_ok=True)
        with open(target, "w", encoding="utf-8", newline="\n") as handle:
            json.dump(rewritten, handle, indent=2)
            handle.write("\n")

    still = referenced(rewritten)
    orphaned = sorted(name for name in convert if name not in still)
    print(f"converted {len(convert)} PNGs: {before / 2**20:.1f} MiB -> {after / 2**20:.1f} MiB DDS"
          f"{' (estimate)' if args.dry_run else ''}; saves {(before - after) / 2**20:.1f} MiB once the PNGs go")
    print(f"PNGs the manifest no longer names ({len(orphaned)}); delete only if nothing else loads them:")
    for name in orphaned:
        print(f"  {os.path.relpath(convert[name], mod)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
