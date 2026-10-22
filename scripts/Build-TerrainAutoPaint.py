#!/usr/bin/env python3
"""Generate four-material terrain paint weights from each map's own MAT layout.

The hand-painted prototype (Build-TerrainPaintPack.py) needs an artist and a
live game capture per map. This script derives both from the map files:

* the RGBA control map comes from the per-cell material words in <map>.mat,
  mapped to the four paint layers per world by the recipe, then blurred;
* the terrain fingerprint and world bounds come from <map>.hg2 alone, with
  the same hash the runtime computes (see Docs/terrain-paint.md), so no game
  launch is needed. An export capture can override or cross-check them.

One multi-map manifest is written for all listed maps; the runtime picks the
entry whose fingerprint and bounds match the live mission. Gameplay terrain
files are only read. Artwork and generated packs stay local.
"""
import argparse
import base64
import importlib.util
import io
import json
import math
from pathlib import Path
import re
import struct
import sys

import numpy as np
from PIL import Image

_here = Path(__file__).parent


def _load(name, file):
    spec = importlib.util.spec_from_file_location(name, _here / file)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


_hd = _load("terrain_hd_pack", "Build-TerrainHdPack.py")
_paint = _load("terrain_paint_pack", "Build-TerrainPaintPack.py")

SAMPLE_METERS = 5.0          # one HG2 height sample
CELL_SAMPLES = 4             # one MAT cell = 4 height samples = 20 m
ZONE_SAMPLES = 256           # HG2 samples per zone edge
MAT_ZONE_CELLS = 64
# Native terrain frame, measured on stock misn04 from an OPENSHIM_TERRAIN_
# GEOMETRY_EXPORT snapshot (all 66,049 vertices of one zone matched the HG2
# heights exactly) and its in-game paint capture (fingerprint
# 73f9729303821983, bounds -3190,-2570,3210,2550):
#   * file sample (sx, sz) sits at world X = 5 * (sx - 128 * zonesX) and
#     Z = -5 * (sz - 128 * zonesZ): file rows run toward -Z (south first is
#     the file's name for it, but Z decreases);
#   * the engine builds a (zonesX + 1) x (zonesZ + 1) grid of zones. Zone i
#     starts at file sample 256 * i - 128 and its mesh vertices are the 257
#     samples from start + 2 (a 10 m half-cell shift), so samples outside
#     the file read as zero and a MAT cell c spans mesh samples 4c + 2 .. 4c + 6.
MESH_SAMPLE_BIAS = 2


def world_to_sample(world_x, world_z, zones_x, zones_z):
    """World metres to (fractional) file sample coordinates."""
    return (world_x / SAMPLE_METERS + ZONE_SAMPLES // 2 * zones_x,
            ZONE_SAMPLES // 2 * zones_z - world_z / SAMPLE_METERS)


# ---------------------------------------------------------------- map files

def read_hg2(path):
    """Return (zones_x, zones_z, plane) where plane[z, x] is the 13-bit height."""
    raw = Path(path).read_bytes()
    version, bits, zx, zz, map_version = struct.unpack_from("<HHHHI", raw)
    if version != 1 or bits != 8 or zx < 1 or zz < 1 or len(raw) != 12 + zx * zz * 0x20000:
        raise ValueError(f"{path}: not a 256-sample HG2 height file")
    zones = np.frombuffer(raw, dtype="<u2", offset=12).reshape(zz, zx, ZONE_SAMPLES, ZONE_SAMPLES)
    plane = zones.transpose(0, 2, 1, 3).reshape(zz * ZONE_SAMPLES, zx * ZONE_SAMPLES) & 0x1FFF
    return zx, zz, plane


def read_mat(path, zx, zz):
    """Return cells[z, x] of 16-bit material words (zone-major file order)."""
    raw = Path(path).read_bytes()
    if len(raw) != zx * zz * MAT_ZONE_CELLS * MAT_ZONE_CELLS * 2:
        raise ValueError(f"{path}: MAT size does not match a {zx}x{zz} zone map")
    zones = np.frombuffer(raw, dtype="<u2").reshape(zz, zx, MAT_ZONE_CELLS, MAT_ZONE_CELLS)
    return zones.transpose(0, 2, 1, 3).reshape(zz * MAT_ZONE_CELLS, zx * MAT_ZONE_CELLS)


def read_trn_types(path):
    """Texture type index -> comment on its section header (e.g. 'Sandy')."""
    names = {}
    for line in Path(path).read_text(encoding="latin-1").splitlines():
        match = re.match(r"\s*\[TextureType(\d+)\]\s*(?://\s*(.*?))?\s*$", line, re.IGNORECASE)
        if match:
            names.setdefault(int(match.group(1)), (match.group(2) or "").strip())
    return names


# --------------------------------------------------- fingerprint and bounds

_FNV_OFFSET = 14695981039346656037
_FNV_PRIME = 1099511628211
_MASK64 = (1 << 64) - 1


def _hash_u32(h, values):
    for value in values:
        h ^= value & 255; h = (h * _FNV_PRIME) & _MASK64
        h ^= (value >> 8) & 255; h = (h * _FNV_PRIME) & _MASK64
        h ^= (value >> 16) & 255; h = (h * _FNV_PRIME) & _MASK64
        h ^= (value >> 24) & 255; h = (h * _FNV_PRIME) & _MASK64
    return h


def terrain_fingerprint(zx, zz, plane):
    """Runtime CaptureTerrainPaintMap hash, reproduced from the HG2 alone.

    The engine builds (zx+1) x (zz+1) terrain zones; zone (i, j) covers file
    samples [256*i - 128, 256*i + 128), anything outside the file reads zero.
    Zones hash in (x, z) order, each as its coordinates then 256x256 heights.
    """
    nx, nz = zx + 1, zz + 1
    padded = np.zeros((nz * ZONE_SAMPLES, nx * ZONE_SAMPLES), dtype=np.uint32)
    padded[128:128 + plane.shape[0], 128:128 + plane.shape[1]] = plane
    h = _hash_u32(_FNV_OFFSET, [nx * nz])
    for i in range(nx):
        for j in range(nz):
            h = _hash_u32(h, [i, j])
            block = padded[j * ZONE_SAMPLES:(j + 1) * ZONE_SAMPLES, i * ZONE_SAMPLES:(i + 1) * ZONE_SAMPLES]
            h = _hash_u32(h, block.ravel().tolist())
    return f"{h:016x}"


def terrain_bounds(zx, zz):
    """Native world bounds in metres: min X, min Z, max X, max Z.

    The mesh spans file samples [-128 + 2, (zones + 1) * 256 - 128 + 2) on each
    axis; X grows with the sample index and Z shrinks with it.
    """
    low = -ZONE_SAMPLES // 2 + MESH_SAMPLE_BIAS
    high_x = (zx + 1) * ZONE_SAMPLES - ZONE_SAMPLES // 2 + MESH_SAMPLE_BIAS
    high_z = (zz + 1) * ZONE_SAMPLES - ZONE_SAMPLES // 2 + MESH_SAMPLE_BIAS
    half_x, half_z = ZONE_SAMPLES // 2 * zx, ZONE_SAMPLES // 2 * zz
    return [(low - half_x) * SAMPLE_METERS, -(high_z - half_z) * SAMPLE_METERS,
            (high_x - half_x) * SAMPLE_METERS, -(low - half_z) * SAMPLE_METERS]


# ------------------------------------------------------------- weight map

def cell_weights(cells, type_weights, transition, fallback=(0, 1, 0, 0)):
    """Per-cell RGBA layer weights from MAT words.

    Word bits: 15-12 base type, 11-8 next type, bit 7 cap(0)/diagonal(1).
    A cell whose two types match is solid. Otherwise it blends the base with
    the next type: caps by transition['cap'], diagonals by transition['diagonal'].
    """
    base = (cells >> 12) & 15
    other = (cells >> 8) & 15
    diagonal = (cells >> 7) & 1
    table = np.tile(np.asarray(fallback, dtype=np.float64), (16, 1))
    for index, vector in type_weights.items():
        table[index] = vector
    amount = np.where(base == other, 0.0, np.where(diagonal == 1, transition["diagonal"], transition["cap"]))
    return table[base] * (1 - amount)[..., None] + table[other] * amount[..., None]


def blur(field, sigma_pixels):
    """Separable Gaussian over the first two axes with edge replication."""
    if sigma_pixels <= 0:
        return field
    radius = max(1, int(math.ceil(sigma_pixels * 3)))
    taps = np.exp(-0.5 * (np.arange(-radius, radius + 1) / sigma_pixels) ** 2)
    taps /= taps.sum()
    for axis in (0, 1):
        padded = np.pad(field, [(radius, radius) if a == axis else (0, 0) for a in range(field.ndim)], mode="edge")
        out = np.zeros_like(field)
        length = field.shape[axis]
        for k, tap in enumerate(taps):
            out += tap * np.take(padded, np.arange(k, k + length), axis=axis)
        field = out
    return field


def rasterize(cells, zx, zz, bounds, size, recipe):
    """Weight map (size x size RGBA uint8), row 0 at minimum Z, normalised to 255."""
    weights = cell_weights(cells, {int(k): v for k, v in recipe["typeWeights"].items()}, recipe["transition"],
                           recipe.get("undefinedTypeWeights", [0, 1, 0, 0]))
    px = (np.arange(size) + 0.5) / size
    world_x = bounds[0] + px * (bounds[2] - bounds[0])
    world_z = bounds[1] + px * (bounds[3] - bounds[1])
    sample_x, sample_z = world_to_sample(world_x, world_z, zx, zz)
    sample_x, sample_z = sample_x - MESH_SAMPLE_BIAS, sample_z - MESH_SAMPLE_BIAS
    raw_x = np.floor(sample_x / CELL_SAMPLES).astype(int)
    raw_z = np.floor(sample_z / CELL_SAMPLES).astype(int)
    cx = np.clip(raw_x, 0, cells.shape[1] - 1)
    cz = np.clip(raw_z, 0, cells.shape[0] - 1)
    field = weights[np.ix_(cz, cx)]
    # The engine's terrain grid is half a zone wider than the file on every
    # side. Those skirt cells carry no authored material, so use one neutral
    # layer there instead of smearing the edge cells outward in streaks.
    outside = ((raw_x < 0) | (raw_x >= cells.shape[1]))[None, :] | ((raw_z < 0) | (raw_z >= cells.shape[0]))[:, None]
    field[outside] = np.asarray(recipe.get("outsideWeights", [0, 1, 0, 0]), dtype=np.float64)
    meters_per_pixel = (bounds[2] - bounds[0]) / size
    field = blur(field, recipe.get("blurMeters", 12) / meters_per_pixel)
    field = np.clip(field, 0, None)
    total = field.sum(axis=2, keepdims=True)
    field = np.where(total > 1e-9, field / np.maximum(total, 1e-9), np.array([1.0, 0, 0, 0]))
    image = Image.new("RGBA", (size, size))
    image.putdata([_paint.normalize(tuple(np.clip(np.rint(p * 255), 0, 255).astype(int)))
                   for p in field.reshape(-1, 4)])
    return image


# ------------------------------------------------------------------- packs

def validate_recipe(recipe):
    if recipe.get("schema") != "bzr-openshim-terrain-autopaint-v1" or len(recipe.get("layers", [])) != 4:
        raise ValueError("recipe needs schema bzr-openshim-terrain-autopaint-v1 and exactly four layers")
    for key in ("typeWeights", "typeNames", "transition"):
        if key not in recipe:
            raise ValueError(f"recipe is missing {key}")
    for index, vector in recipe["typeWeights"].items():
        if not (0 <= int(index) <= 15) or len(vector) != 4 or any(v < 0 for v in vector) or sum(vector) <= 0:
            raise ValueError(f"typeWeights[{index}] needs four non-negative weights with a positive sum")
    for key in ("cap", "diagonal"):
        if not 0 <= recipe["transition"].get(key, -1) <= 1:
            raise ValueError("transition cap/diagonal must be 0..1")


def load_map(name, files, recipe, capture_path, weight_size, trust_capture=False):
    hg2, mat, trn = files
    zx, zz, plane = read_hg2(hg2)
    cells = read_mat(mat, zx, zz)
    types = read_trn_types(trn)
    for index, expected in recipe["typeNames"].items():
        if types.get(int(index), "").lower() != expected.lower():
            raise ValueError(f"{name}: TRN texture type {index} is '{types.get(int(index))}', "
                             f"recipe expects '{expected}'; add a recipe for this world layout")
    # MAT words can name a type the TRN never defines (stock misn04 has nine
    # such cells in its last column). The engine draws its default tile there,
    # so the recipe supplies undefinedTypeWeights; large counts are an error.
    base, other = (cells >> 12) & 15, (cells >> 8) & 15
    undefined = ~(np.isin(base, [int(k) for k in recipe["typeWeights"]]) & np.isin(other, [int(k) for k in recipe["typeWeights"]]))
    if undefined.mean() > 0.01:
        raise ValueError(f"{name}: {undefined.sum()} cells use texture types the recipe does not map; add a world recipe")
    fingerprint = terrain_fingerprint(zx, zz, plane)
    bounds = terrain_bounds(zx, zz)
    source = "offline HG2"
    if capture_path:
        capture = _hd.read_json(capture_path)["paintMap"]
        if trust_capture:
            # Live values win when the offline model cannot reproduce them (stock
            # misn05 is such a map, see Docs/terrain-paint.md).
            fingerprint, bounds = capture["terrainFingerprint"], [float(v) for v in capture["boundsMeters"]]
        elif capture["terrainFingerprint"] != fingerprint or [float(v) for v in capture["boundsMeters"]] != bounds:
            raise ValueError(f"{name}: capture {capture['terrainFingerprint']} {capture['boundsMeters']} "
                             f"disagrees with the offline result {fingerprint} {bounds}")
        source = "offline HG2, confirmed by capture" if not trust_capture else "live capture (offline model disagrees or was bypassed)"
    weights = rasterize(cells, zx, zz, bounds, weight_size, recipe)
    return {"name": name, "zones": (zx, zz), "fingerprint": fingerprint, "bounds": bounds,
            "weights": weights, "source": source,
            "histogram": {int(t): int(c) for t, c in zip(*np.unique(cells >> 12, return_counts=True))}}


def build_pack(maps, recipe, source_root, output, size, prefix, force):
    output = Path(output)
    if output.exists() and any(output.iterdir()) and not force:
        raise ValueError("output is non-empty; use --force")
    root = Path(source_root).resolve()
    layers, identities, repeats = [], [], []
    for layer in recipe["layers"]:
        repeat = layer.get("repeatMeters")
        if type(repeat) not in (int, float) or not 1 <= repeat <= 4096 or not layer.get("name"):
            raise ValueError("each layer needs a name and repeatMeters from 1 to 4096")
        art, identity = _hd.load_art(root, layer)
        layers.append(art.resize((size, size), Image.Resampling.LANCZOS).convert("RGBA"))
        identities.append(identity)
        repeats.append(repeat)
    capture_material = recipe.get("material", "MA_DETAIL_ATLAS")
    output.mkdir(parents=True, exist_ok=True)
    resources = [f"{prefix}_layer{i}.png" for i in range(4)]
    for resource, image in zip(resources, layers):
        image.save(output / resource)
    entries, summary, controls = [], [], {}
    for info in maps:
        weights = info["weights"]
        # Maps with identical layouts (for example the stock and Campaign
        # Reimagined copies of one mission) share a single control image.
        key = weights.tobytes()
        if key not in controls:
            control = Image.merge("RGBA", tuple(c.resize((size, size), Image.Resampling.BILINEAR) for c in weights.split()))
            control.putdata([_paint.normalize(p) for p in control.getdata()])
            controls[key] = f"{prefix}_{info['name']}_control.png"
            control.save(output / controls[key])
        control_name = controls[key]
        weights.save(output / f"{prefix}_{info['name']}_weights.png")
        entries.append({"terrainFingerprint": info["fingerprint"], "boundsMeters": info["bounds"], "control": control_name})
        summary.append({k: info[k] for k in ("name", "fingerprint", "bounds", "source", "histogram")})
    tiles = {str(i): name for i, name in enumerate(resources)}
    tiles["4"] = entries[0]["control"]
    paint = {"schema": "bzr-openshim-terrain-paint-v1", "rowZero": "minZ", "repeatMeters": repeats, "maps": entries}
    manifest = {"schema": "bzr-openshim-terrain-hd-v1", "materials": {capture_material: {
        "sliceCount": 5, "diffuseResource": recipe["diffuseResource"], "fallback": resources[0],
        "tiles": tiles, "paint": paint}}}
    (output / f"{prefix}.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    project = {"schema": "bzr-openshim-terrain-autopaint-project-v1", "prefix": prefix, "materialSize": size,
               "layers": recipe["layers"], "sources": identities, "maps": summary}
    (output / f"{prefix}_project.json").write_text(json.dumps(project, indent=2) + "\n", encoding="utf-8")
    write_editors(maps, recipe, layers, repeats, identities, output, prefix, size)
    return manifest


def write_editors(maps, recipe, layers, repeats, identities, output, prefix, size):
    """One standalone editor per map, preloaded with the generated weights, for touch-up."""
    previews = []
    for image in layers:
        stream = io.BytesIO(); image.resize((128, 128), Image.Resampling.LANCZOS).save(stream, format="PNG")
        previews.append("data:image/png;base64," + base64.b64encode(stream.getvalue()).decode("ascii"))
    template = (_here / "terrain-paint-editor.html").read_text(encoding="utf-8")
    code = (_here / "terrain-paint-codec.js").read_text(encoding="utf-8")
    for info in maps:
        paint = {"schema": "bzr-openshim-terrain-paint-v1", "terrainFingerprint": info["fingerprint"],
                 "boundsMeters": info["bounds"], "rowZero": "minZ", "repeatMeters": repeats}
        payload = {"schema": "bzr-openshim-terrain-paint-project-v1", "paint": paint, "prefix": f"{prefix}_{info['name']}",
                   "materialSize": size, "weightSize": info["weights"].width, "layers": recipe["layers"],
                   "sources": identities, "previews": previews,
                   "weights": base64.b64encode(info["weights"].tobytes()).decode("ascii")}
        html = template.replace("__PAINT_PROJECT__", json.dumps(payload).replace("<", "\\u003c")).replace("__PAINT_CODE__", code)
        (output / f"{prefix}_{info['name']}_editor.html").write_text(html, encoding="utf-8")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--recipe", required=True, help="autopaint recipe JSON (layers, type weights, transitions)")
    parser.add_argument("--source-root", required=True, help="directory the recipe's artwork paths are relative to")
    parser.add_argument("--output", required=True)
    parser.add_argument("--map", action="append", required=True, metavar="NAME=STEM",
                        help="map name and either a file stem (STEM.hg2/.mat/.trn) or HG2,MAT,TRN paths (repeatable)")
    parser.add_argument("--capture", action="append", default=[], metavar="NAME=FILE",
                        help="optional OPENSHIM_TERRAIN_HD_EXPORT capture to cross-check that map")
    parser.add_argument("--trust-capture", action="store_true", help="use --capture fingerprint/bounds instead of requiring the offline values to agree")
    parser.add_argument("--size", type=int, default=2048, help="material and control upload size")
    parser.add_argument("--weight-size", type=int, default=1024)
    parser.add_argument("--prefix", default="openshim_mars_auto")
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()
    try:
        recipe = _hd.read_json(args.recipe)
        validate_recipe(recipe)
        captures = dict(item.split("=", 1) for item in args.capture)
        if args.size not in (64, 128, 256, 512, 1024, 2048) or args.weight_size not in (64, 128, 256, 512, 1024, 2048):
            raise ValueError("sizes must be powers of two from 64 to 2048")
        if not re.fullmatch(r"[a-z][a-z0-9_]{0,63}", args.prefix):
            raise ValueError("invalid resource prefix")
        maps = []
        for item in args.map:
            name, spec = item.split("=", 1)
            if not re.fullmatch(r"[a-z][a-z0-9_]{0,31}", name):
                raise ValueError(f"invalid map name {name}")
            parts = spec.split(",")
            files = tuple(Path(p) for p in parts) if len(parts) == 3 else tuple(Path(parts[0]).with_suffix(e) for e in (".hg2", ".mat", ".trn"))
            if len(parts) not in (1, 3):
                raise ValueError("--map takes a stem or exactly HG2,MAT,TRN")
            info = load_map(name, files, recipe, captures.get(name), args.weight_size, args.trust_capture)
            print(f"{name}: zones {info['zones'][0]}x{info['zones'][1]} fingerprint {info['fingerprint']} "
                  f"bounds {info['bounds']} ({info['source']}) types {info['histogram']}")
            maps.append(info)
        build_pack(maps, recipe, args.source_root, args.output, args.size, args.prefix, args.force)
        print(f"Built auto-paint pack for {len(maps)} map(s): {args.output}")
    except (OSError, ValueError, KeyError, TypeError) as error:
        parser.exit(1, f"Auto-paint pack declined: {error}\n")


if __name__ == "__main__":
    main()
