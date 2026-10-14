#!/usr/bin/env python3
"""Export engine-indexed HD terrain tiles. Inputs and generated art stay local."""
import argparse
import csv
import hashlib
import io
import json
import math
from pathlib import Path
import re
import sys
import zipfile

from PIL import Image, ImageStat


def read_json(path):
    return json.loads(Path(path).read_text(encoding="utf-8-sig"))


def pixel_box(rect, width, height):
    if not isinstance(rect, list) or len(rect) != 4:
        raise ValueError("tile rectangle must contain u, v, w, h")
    if any(type(v) not in (int, float) or not math.isfinite(v) for v in rect):
        raise ValueError("tile rectangle must be finite")
    u, v, w, h = rect
    if min(u, v) < 0 or min(w, h) <= 0 or u + w > 1.000001 or v + h > 1.000001:
        raise ValueError("tile rectangle is outside the atlas")
    pixels = (u * width, v * height, (u + w) * width, (v + h) * height)
    if any(abs(p - round(p)) > 0.001 for p in pixels):
        raise ValueError("tile rectangle does not align to atlas pixels")
    return tuple(round(p) for p in pixels)


def csv_names(path, width, height):
    """Match names to actual rectangles, never CSV row numbers to tile IDs."""
    names = {}
    if path:
        with Path(path).open(encoding="utf-8-sig", newline="") as source:
            for row in csv.reader(source):
                if len(row) != 5:
                    raise ValueError("atlas CSV needs name,u,v,w,h rows")
                box = pixel_box([float(v) for v in row[1:]], width, height)
                if row[0].strip():
                    names.setdefault(box, []).append(row[0].strip().upper())
    return names


def source_path(root, relative):
    if not isinstance(relative, str) or not relative or Path(relative).is_absolute():
        raise ValueError("artwork paths must be relative to --source-root")
    path = (root / relative).resolve()
    if not path.is_relative_to(root):
        raise ValueError("artwork path escapes --source-root")
    return path


def load_art(root, entry):
    if not isinstance(entry, dict) or ("file" in entry) == ("archive" in entry):
        raise ValueError("artwork needs exactly one file or archive source")
    if "archive" in entry:
        path = source_path(root, entry["archive"])
        member = entry.get("member", "")
        if not member or member.startswith(("/", "\\")) or ".." in member.replace("\\", "/").split("/"):
            raise ValueError("unsafe artwork archive member")
        with zipfile.ZipFile(path) as archive:
            info = archive.getinfo(member)
            if info.file_size > 256 * 1024 * 1024:
                raise ValueError("artwork archive member exceeds 256 MiB")
            data = archive.read(info)
        image = Image.open(io.BytesIO(data))
        identity = {"archive": entry["archive"], "member": member,
                    "sha256": hashlib.sha256(data).hexdigest()}
    else:
        path = source_path(root, entry["file"])
        image = Image.open(path)
        identity = {"file": entry["file"], "sha256": hashlib.sha256(path.read_bytes()).hexdigest()}
    image.load()
    return image.convert("RGB"), identity


def replacement_tile(stock, artwork, edge_pixels, match_color):
    size = stock.width
    if type(edge_pixels) is not int or not 1 <= edge_pixels <= size // 2:
        raise ValueError("edgePixels must be between 1 and half the tile size")
    artwork = artwork.resize(stock.size, Image.Resampling.LANCZOS)
    if match_color:
        target = ImageStat.Stat(stock.convert("RGB")).mean
        actual = ImageStat.Stat(artwork).mean
        channels = []
        for channel, desired, observed in zip(artwork.split(), target, actual):
            scale = desired / max(observed, 1)
            channels.append(channel.point([min(255, round(v * scale)) for v in range(256)]))
        artwork = Image.merge("RGB", channels)
    # Preserve the original edge exactly. Transitions retain their entire stock
    # tile; a pilot solid replacement fades to its stock neighbours at the edge.
    mask = Image.new("L", stock.size)
    mask.putdata([
        round(255 * min(1, min(x, y, size - 1 - x, size - 1 - y) / edge_pixels))
        for y in range(size) for x in range(size)
    ])
    result = Image.composite(artwork.convert("RGBA"), stock, mask)
    result.putalpha(stock.getchannel("A"))
    return result


def build_pack(capture_path, atlas_path, output, tile_size=512, prefix="openshim_mars",
               atlas_csv=None, recipe_path=None, source_root=None, force=False):
    if not re.fullmatch(r"[a-z][a-z0-9_]{0,63}", prefix):
        raise ValueError("prefix must be a lowercase Ogre resource name")
    if type(tile_size) is not int or tile_size not in (64, 128, 256, 512, 1024, 2048):
        raise ValueError("tile size must be a power of two from 64 to 2048")
    capture = read_json(capture_path)
    if not isinstance(capture, dict) or capture.get("schema") != "bzr-openshim-terrain-atlas-v1":
        raise ValueError("input must be a live terrain atlas capture")
    if not isinstance(capture.get("material"), str) or not capture["material"]:
        raise ValueError("capture material is missing")
    if Path(atlas_path).name.lower() != str(capture.get("diffuseResource", "")).lower():
        raise ValueError("atlas filename does not match the captured diffuse resource")
    with Image.open(atlas_path) as image:
        atlas = image.convert("RGBA")
    if atlas.size != (capture.get("width"), capture.get("height")):
        raise ValueError("atlas dimensions do not match the live capture")
    boxes = {}
    if not isinstance(capture.get("tiles"), dict):
        raise ValueError("capture tile table is missing")
    for key, rect in capture["tiles"].items():
        if not re.fullmatch(r"0|[1-9][0-9]*", key) or not 0 <= int(key) < 256:
            raise ValueError("engine tile index must be 0..255")
        boxes[int(key)] = pixel_box(rect, *atlas.size)
    if not boxes or not capture.get("usedIndices") or any(
        type(i) is not int or i not in boxes for i in capture["usedIndices"]
    ):
        raise ValueError("capture must cover every used engine tile")
    names = csv_names(atlas_csv, *atlas.size)
    recipe = read_json(recipe_path) if recipe_path else {}
    if not isinstance(recipe, dict) or (recipe_path and recipe.get("schema") != "bzr-openshim-terrain-art-v1"):
        raise ValueError("unsupported artwork recipe")
    if type(recipe.get("matchStockColor", True)) is not bool:
        raise ValueError("matchStockColor must be a boolean")
    replacements = recipe.get("replacements", {})
    if not isinstance(replacements, dict):
        raise ValueError("recipe replacements must be a name-to-artwork object")
    available_names = {name for box in boxes.values() for name in names.get(box, [])}
    if any(name not in available_names for name in replacements):
        raise ValueError("recipe tile name is not in the captured atlas/CSV")
    if replacements and (not source_root or not atlas_csv):
        raise ValueError("artwork recipes need --source-root and --atlas-csv")
    root = Path(source_root).resolve() if source_root else None
    # Prepare everything before writing output, so an invalid recipe leaves no
    # partially published manifest. Input art/game files are never modified.
    resources, tiles, rows, sources = {}, {}, [], {}
    for index, box in sorted(boxes.items()):
        aliases = names.get(box, [])
        selected = [name for name in aliases if name in replacements]
        if len(selected) > 1:
            raise ValueError("multiple recipe replacements address the same atlas rectangle")
        stock = atlas.crop(box).resize((tile_size, tile_size), Image.Resampling.LANCZOS)
        tile = stock
        if selected:
            name = selected[0]
            if name not in sources:
                artwork, identity = load_art(root, replacements[name])
                sources[name] = (artwork, identity)
            tile = replacement_tile(stock, sources[name][0],
                recipe.get("edgePixels", max(1, tile_size // 16)), recipe.get("matchStockColor", True))
        # Duplicate table slots share source resources, but retain their native
        # array slice IDs. This reduces disk/cache duplication, not array memory.
        digest = hashlib.sha256(tile.tobytes()).hexdigest()
        resource = resources.get(digest)
        if resource is None:
            resource = (f"{prefix}_{index:03d}.png", tile)
            resources[digest] = resource
        tiles[str(index)] = resource[0]
        rows.append({"index": index, "names": aliases, "box": box,
                     "resource": resource[0], "replacement": selected[0] if selected else None})
    slice_count = max(boxes) + 1
    manifest = {"schema": "bzr-openshim-terrain-hd-v1", "materials": {
        capture["material"]: {"sliceCount": slice_count, "diffuseResource": capture["diffuseResource"],
                              "fallback": tiles[str(min(boxes))], "tiles": tiles}}}
    report = {"schema": "bzr-openshim-terrain-pack-report-v1", "material": capture["material"],
        "diffuseResource": capture["diffuseResource"], "atlasSha256": hashlib.sha256(Path(atlas_path).read_bytes()).hexdigest(),
        "tileSize": tile_size, "sliceCount": slice_count, "uniqueImages": len(resources),
        "arrayMiBWithMips": round(slice_count * tile_size**2 * 4 * 4 / 3 / 1024**2, 2),
        "capturedUsedIndices": capture["usedIndices"], "tiles": rows,
        "artwork": {name: value[1] for name, value in sources.items()}}
    output = Path(output)
    manifest_path = output / f"{prefix}.json"
    report_path = output / f"{prefix}_report.json"
    preview_path = output / f"{prefix}_preview.jpg"
    targets = [output / name for name, _ in resources.values()] + [manifest_path, report_path, preview_path]
    if not force and any(path.exists() for path in targets):
        raise ValueError("output files already exist; use a new directory/prefix or --force")
    output.mkdir(parents=True, exist_ok=True)
    for name, tile in resources.values():
        tile.save(output / name)
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    # One preview per unique source rectangle, including its actual engine ID.
    from PIL import ImageDraw
    preview = Image.new("RGB", (8 * 144, math.ceil(len(resources) / 8) * 168), "#202020")
    draw = ImageDraw.Draw(preview)
    for ordinal, (name, tile) in enumerate(resources.values()):
        x, y = ordinal % 8 * 144, ordinal // 8 * 168
        preview.paste(tile.convert("RGB").resize((144, 144)), (x, y))
        draw.text((x + 3, y + 146), name[len(prefix) + 1:], fill="white")
    preview.save(preview_path)
    return manifest_path, report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--capture", required=True, type=Path)
    parser.add_argument("--atlas", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--atlas-csv", type=Path)
    parser.add_argument("--recipe", type=Path)
    parser.add_argument("--source-root", type=Path)
    parser.add_argument("--tile-size", type=int, default=512)
    parser.add_argument("--prefix", default="openshim_mars")
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()
    try:
        path, report = build_pack(args.capture, args.atlas, args.output, args.tile_size,
            args.prefix, args.atlas_csv, args.recipe, args.source_root, args.force)
        print(json.dumps({"manifest": str(path), "slices": report["sliceCount"],
                          "uniqueImages": report["uniqueImages"], "arrayMiB": report["arrayMiBWithMips"]}))
    except (ValueError, KeyError, OSError, zipfile.BadZipFile) as error:
        parser.exit(1, f"Terrain pack: {error}\n")


if __name__ == "__main__":
    main()
