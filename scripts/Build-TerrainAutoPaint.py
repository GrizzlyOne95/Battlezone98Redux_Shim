#!/usr/bin/env python3
"""Generate four- or eight-material terrain paint weights from each map's own MAT layout.

The hand-painted prototype (Build-TerrainPaintPack.py) needs an artist and a
live game capture per map. This script derives both from the map files:

* the RGBA control map (two for eight layers) comes from the per-cell material
  words in <map>.mat, mapped to the paint layers per world by the recipe, then blurred;
* the terrain fingerprint and world bounds come from <map>.hg2 alone, with
  the same hash the runtime computes (see Docs/terrain-paint.md), so no game
  launch is needed. An export capture can override or cross-check them.

One multi-map manifest is written for all listed maps; the runtime picks the
entry whose fingerprint and bounds match the live mission. Gameplay terrain
files are only read. Artwork and generated packs stay local.
"""
import argparse
import base64
import heapq
import importlib.util
import io
import json
import math
from pathlib import Path
import re
import struct
import sys
import zipfile

import numpy as np
from PIL import Image, ImageEnhance, ImageFilter

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
# HG2 height units in metres. Inferred, not measured in game: at 0.1 m the MAT
# rock cells of stock misn04/misn08/misn14 have a median slope of 27-35 degrees
# and their other cells 0-8, which matches how those maps read in play.
HEIGHT_UNIT_METERS = 0.1


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
    """Texture type index -> name on its section header (e.g. 'Sandy').

    Headers carry the name as a comment ('[TextureType0] // Sandy') or as bare
    text ('[TextureType1] Liquid Sulphur', stock Venus and Io); many carry none.
    """
    names = {}
    for line in Path(path).read_text(encoding="latin-1").splitlines():
        match = re.match(r"\s*\[TextureType(\d+)\]\s*(?://)?\s*(.*?)\s*$", line, re.IGNORECASE)
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


def read_trn_pad(path):
    """Height the engine gives samples outside the HG2: (int)([Size] Height / 0.1).

    The default zone that fills unloaded terrain takes this value (0 when the
    TRN has no [Size] Height); stock Titan sets Height=50, so its border is 500.
    """
    section = ""
    for line in Path(path).read_text(encoding="latin-1").splitlines():
        header = re.match(r"\s*\[(\w+)\]", line)
        if header:
            section = header.group(1).lower()
            continue
        value = re.match(r"\s*Height\s*=\s*([-+0-9.eE]+)", line, re.IGNORECASE)
        if section == "size" and value:
            return int(np.float32(value.group(1)) / np.float32(0.1)) & 0xFFF
    return 0


def terrain_fingerprint(zx, zz, plane, pad=0):
    """Runtime CaptureTerrainPaintMap hash, reproduced from the HG2 alone.

    The engine builds (zx+1) x (zz+1) terrain zones; zone (i, j) covers file
    samples [256*i - 128, 256*i + 128), anything outside the file reads the
    TRN pad height (read_trn_pad). Zones hash in (x, z) order, each as its
    coordinates then 256x256 heights masked to 12 bits.
    """
    nx, nz = zx + 1, zz + 1
    padded = np.full((nz * ZONE_SAMPLES, nx * ZONE_SAMPLES), pad, dtype=np.uint32)
    padded[128:128 + plane.shape[0], 128:128 + plane.shape[1]] = plane & 0xFFF
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

def unit_weights(n, index):
    return [1.0 if i == index else 0 for i in range(n)]


def normalize(pixel):
    """Scale a weight vector to sum to 255 (largest remainders); _paint.normalize for any length."""
    total = sum(pixel)
    if total == 0:
        return tuple(255 if i == 0 else 0 for i in range(len(pixel)))
    values = [v * 255 / total for v in pixel]
    result = [math.floor(v) for v in values]
    for i in sorted(range(len(pixel)), key=lambda i: (values[i] - result[i], -i), reverse=True)[:255 - sum(result)]:
        result[i] += 1
    return tuple(result)


def weight_images(weights):
    """The RGBA images behind a map's weights: one for four layers, a pair for eight."""
    return list(weights) if isinstance(weights, tuple) else [weights]


def weights_key(weights):
    return b"".join(image.tobytes() for image in weight_images(weights))


def cell_weights(cells, type_weights, transition, fallback=None):
    """Per-cell layer weights from MAT words.

    Word bits: 15-12 base type, 11-8 next type, bit 7 cap(0)/diagonal(1).
    A cell whose two types match is solid. Otherwise it blends the base with
    the next type: caps by transition['cap'], diagonals by transition['diagonal'].
    """
    base = (cells >> 12) & 15
    other = (cells >> 8) & 15
    diagonal = (cells >> 7) & 1
    if fallback is None:
        fallback = (0, 1, 0, 0)
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


def smoothstep(low, high, x):
    t = np.clip((x - low) / (high - low), 0, 1)
    return t * t * (3 - 2 * t)


def cell_slope_degrees(plane, cell_shape):
    """Mean slope of each MAT cell's 4 x 4 height samples (cell c is sample 4c)."""
    heights = plane.astype(np.float64) * HEIGHT_UNIT_METERS
    gz, gx = np.gradient(heights, SAMPLE_METERS)
    degrees = np.degrees(np.arctan(np.hypot(gx, gz)))
    rows, cols = cell_shape
    return degrees[:rows * CELL_SAMPLES, :cols * CELL_SAMPLES].reshape(rows, CELL_SAMPLES, cols, CELL_SAMPLES).mean(axis=(1, 3))


def cell_relief_meters(plane, cell_shape, radius_meters):
    """Each MAT cell's mean height minus its surroundings about `radius_meters` across:
    negative in hollows and valleys, positive on ridges and hilltops."""
    cells = cell_heights_meters(plane, cell_shape)
    return cells - blur(cells, radius_meters / (CELL_SAMPLES * SAMPLE_METERS))


def cell_heights_meters(plane, cell_shape):
    rows, cols = cell_shape
    heights = plane.astype(np.float64) * HEIGHT_UNIT_METERS
    return heights[:rows * CELL_SAMPLES, :cols * CELL_SAMPLES].reshape(rows, CELL_SAMPLES, cols, CELL_SAMPLES).mean(axis=(1, 3))


_NEIGHBOURS = [(dr, dc, math.hypot(dr, dc) * CELL_SAMPLES * SAMPLE_METERS)
               for dr in (-1, 0, 1) for dc in (-1, 0, 1) if dr or dc]


def fill_depressions(heights, rise=1e-3):
    """Priority flood from the map edge: every cell is raised to at least `rise`
    metres above the lowest neighbour it can drain through, so each cell has a
    downhill path off the map and filled pits slope gently to their outlets."""
    rows, cols = heights.shape
    h = heights.ravel().tolist()
    filled, done = list(h), [False] * (rows * cols)
    queue = []
    for i in range(rows * cols):
        r, c = divmod(i, cols)
        if r in (0, rows - 1) or c in (0, cols - 1):
            queue.append((h[i], i)); done[i] = True
    heapq.heapify(queue)
    while queue:
        z, i = heapq.heappop(queue)
        r, c = divmod(i, cols)
        for dr, dc, _ in _NEIGHBOURS:
            rr, cc = r + dr, c + dc
            j = rr * cols + cc
            if 0 <= rr < rows and 0 <= cc < cols and not done[j]:
                done[j] = True
                filled[j] = max(h[j], z + rise)
                heapq.heappush(queue, (filled[j], j))
    return np.reshape(filled, heights.shape)


def erosion_fields(heights):
    """One water and sediment routing pass over the cell grid, highest cell first.

    Pits are filled first (fill_depressions), so water crosses them toward the
    map edge instead of stopping in every hollow. Water spreads to every lower
    neighbour in proportion to the drop per metre to the fourth power: mostly
    downhill, so it gathers into channels. Each cell carries up to its
    stream-power capacity, sqrt(upstream area) x steepest drop; below capacity
    it picks up sediment (scour), above it it drops some (deposit), which
    happens where slopes ease and across filled pits. Returns upstream area in
    cells, deposit, scour and how deep each cell was filled, all on the cell grid.
    """
    rows, cols = heights.shape
    n = rows * cols
    smooth = blur(heights, 0.75)
    filled = fill_depressions(smooth)
    h = filled.ravel().tolist()
    area, carried, deposit, scour = [1.0] * n, [0.0] * n, [0.0] * n, [0.0] * n
    for i in np.argsort(-np.asarray(h), kind="stable").tolist():
        r, c = divmod(i, cols)
        lower, total, steepest = [], 0.0, 0.0
        for dr, dc, dist in _NEIGHBOURS:
            rr, cc = r + dr, c + dc
            if 0 <= rr < rows and 0 <= cc < cols:
                drop = (h[i] - h[rr * cols + cc]) / dist
                if drop > 0:
                    lower.append((rr * cols + cc, drop ** 4)); total += drop ** 4
                    steepest = max(steepest, drop)
        if not lower:   # an outlet on the map edge: what it carries leaves
            continue
        capacity = math.sqrt(area[i]) * steepest
        if carried[i] > capacity:
            dropped = 0.5 * (carried[i] - capacity); deposit[i] += dropped; carried[i] -= dropped
        else:
            picked = 0.3 * (capacity - carried[i]); scour[i] += picked; carried[i] += picked
        for j, w in lower:
            area[j] += area[i] * w / total
            carried[j] += carried[i] * w / total
    shape = heights.shape
    return np.reshape(area, shape), np.reshape(deposit, shape), np.reshape(scour, shape), filled - smooth


def coverage_mask(raw, coverage):
    """0..1 mask that is full on the top `coverage` fraction of cells by `raw`
    and fades out over the next `coverage`. Cells below 5% of the strongest
    signal stay 0, so a map with few such features is not filled with noise."""
    flat = raw.ravel()
    rank = np.empty(flat.size)
    rank[np.argsort(flat, kind="stable")] = np.arange(flat.size) / max(flat.size - 1, 1)
    floor = max(0.05 * np.percentile(flat, 99.5), 1e-12)
    return np.where(raw > floor, smoothstep(1 - 2 * coverage, 1 - coverage, rank.reshape(raw.shape)), 0.0)


def erosion_masks(plane, cell_shape, erosion):
    """The recipe's erosion masks on the cell grid, keyed like the recipe."""
    heights = cell_heights_meters(plane, cell_shape)
    area, deposit, scour, fill = erosion_fields(heights)
    masks = {}
    if "channel" in erosion:
        rule = erosion["channel"]
        hectares = area * (CELL_SAMPLES * SAMPLE_METERS) ** 2 / 10000
        # Across a filled pit or dead-flat ground the routed path is a straight line,
        # not a stream bed, so channels fade out there.
        gz, gx = np.gradient(blur(heights, 1.5), CELL_SAMPLES * SAMPLE_METERS)
        sloped = smoothstep(0.5, 2, np.degrees(np.arctan(np.hypot(gx, gz))))
        masks["channel"] = (smoothstep(math.log(rule["startHectares"]), math.log(rule["fullHectares"]), np.log(hectares))
                            * (1 - smoothstep(0.2, 1, fill)) * sloped)
    if "deposit" in erosion:
        masks["deposit"] = coverage_mask(deposit, erosion["deposit"]["coverage"])
    if "scour" in erosion:
        masks["scour"] = coverage_mask(scour, erosion["scour"]["coverage"])
    if "talus" in erosion:
        rule = erosion["talus"]
        steep = smoothstep(28, 40, cell_slope_degrees(plane, cell_shape))
        sigma = rule.get("radiusMeters", 60) / (CELL_SAMPLES * SAMPLE_METERS)
        below = heights - blur(heights, sigma) < 0   # the foot of the slope, not its rim
        masks["talus"] = coverage_mask(np.clip(blur(steep, sigma) - steep, 0, None) * below, rule["coverage"])
    # Soften the 20 m cell edges a little; the weight map is blurred again later.
    return {key: blur(mask, 0.7) for key, mask in masks.items()}


EROSION_RULES = ("talus", "deposit", "channel", "scour")


def variation_noise(cell_shape, meters, seed):
    """Smooth 0..1 patch field on the MAT cell grid; deterministic per seed."""
    noise = np.random.default_rng(seed).random(cell_shape)
    noise = blur(noise, meters / (CELL_SAMPLES * SAMPLE_METERS) / 2)
    low, high = np.percentile(noise, (5, 95))
    return smoothstep(0.3, 0.7, (noise - low) / max(high - low, 1e-9))


def cell_field(cells, plane, recipe, seed):
    """Per-cell layer weights (one per recipe layer): MAT types, then optional variation patches and slope.

    variation: {"meters", "amount", "types": {type: weights}} blends each listed
    type toward its alternate weights inside noise patches about `meters` wide,
    so a map painted almost entirely with one type does not repeat one tile.
    shape: {"radiusMeters", "rangeMeters", "amount", "types", "hollow", "ridge"}
    blends cells of the listed types (all when omitted) toward `hollow` where the
    ground sits below its surroundings and toward `ridge` where it stands above,
    reaching `amount` at `rangeMeters` of difference: lush valleys, dry crests.
    A list of such rules applies each in turn (say a wide one for valleys and a
    narrow one for crevices and worn crests).
    erosion: {"talus", "deposit", "channel", "scour"}, each {"weights", "amount",
    optional "types"} plus its threshold (see erosion_masks), blends cells toward
    `weights` by masks from a water and sediment routing pass over the HG2.
    slope: {"weights", "startDegrees", "fullDegrees"} blends steep cells toward
    a rock layer whatever their MAT type.
    """
    types = {int(k): v for k, v in recipe["typeWeights"].items()}
    fallback = recipe.get("undefinedTypeWeights", unit_weights(len(recipe["layers"]), 1))
    weights = cell_weights(cells, types, recipe["transition"], fallback)
    variation = recipe.get("variation")
    if variation:
        amount = variation.get("amount", 0.5)
        alternate = dict(types)
        for index, vector in variation["types"].items():
            alternate[int(index)] = [(1 - amount) * a + amount * b for a, b in zip(types[int(index)], vector)]
        patches = variation_noise(cells.shape, variation.get("meters", 150), seed)[..., None]
        weights = weights * (1 - patches) + cell_weights(cells, alternate, recipe["transition"], fallback) * patches
    def type_mask(rule):
        return np.isin((cells >> 12) & 15, rule["types"]) if "types" in rule else np.ones(cells.shape, dtype=bool)
    shapes = recipe.get("shape", [])
    for shape in (shapes if isinstance(shapes, list) else [shapes]) if plane is not None else []:
        relief = cell_relief_meters(plane, cells.shape, shape["radiusMeters"])
        for key, sign in (("hollow", -1), ("ridge", 1)):
            if key in shape:
                t = (shape.get("amount", 0.5) * smoothstep(0, shape["rangeMeters"], sign * relief) * type_mask(shape))[..., None]
                weights = weights * (1 - t) + np.asarray(shape[key], dtype=np.float64) * t
    erosion = recipe.get("erosion")
    if erosion and plane is not None:
        masks = erosion_masks(plane, cells.shape, erosion)
        for key in EROSION_RULES:
            if key in erosion:
                rule = erosion[key]
                t = (rule.get("amount", 0.5) * masks[key] * type_mask(rule))[..., None]
                weights = weights * (1 - t) + np.asarray(rule["weights"], dtype=np.float64) * t
    slope = recipe.get("slope")
    if slope and plane is not None:
        steep = smoothstep(slope["startDegrees"], slope["fullDegrees"], cell_slope_degrees(plane, cells.shape))[..., None]
        weights = weights * (1 - steep) + np.asarray(slope["weights"], dtype=np.float64) * steep
    return weights


def rasterize(cells, zx, zz, bounds, size, recipe, plane=None, seed=0):
    """Weight map (size x size RGBA uint8; a pair of them for eight layers), row 0 at minimum Z, normalised to 255."""
    n = len(recipe["layers"])
    weights = cell_field(cells, plane, recipe, seed)
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
    field[outside] = np.asarray(recipe.get("outsideWeights", unit_weights(n, 1)), dtype=np.float64)
    meters_per_pixel = (bounds[2] - bounds[0]) / size
    field = blur(field, recipe.get("blurMeters", 12) / meters_per_pixel)
    field = np.clip(field, 0, None)
    total = field.sum(axis=2, keepdims=True)
    field = np.where(total > 1e-9, field / np.maximum(total, 1e-9), np.array(unit_weights(n, 0)))
    pixels = [normalize(tuple(np.clip(np.rint(p * 255), 0, 255).astype(int))) for p in field.reshape(-1, n)]
    if n == 4:
        image = Image.new("RGBA", (size, size))
        image.putdata(pixels)
        return image
    packed = np.array(pixels, dtype=np.uint8).reshape(size, size, n)
    return tuple(Image.fromarray(packed[..., k:k + 4], "RGBA") for k in range(0, n, 4))


# ------------------------------------------------------------------- packs

def validate_recipe(recipe):
    if recipe.get("schema") != "bzr-openshim-terrain-autopaint-v1" or len(recipe.get("layers", [])) not in (4, 8):
        raise ValueError("recipe needs schema bzr-openshim-terrain-autopaint-v1 and four or eight layers")
    n = len(recipe["layers"])
    if n == 8 and recipe.get("diffuseOnly", False):
        raise ValueError("eight layers need the full material form, not diffuseOnly")
    for key in ("typeWeights", "typeNames", "transition"):
        if key not in recipe:
            raise ValueError(f"recipe is missing {key}")
    for index, names in recipe["typeNames"].items():
        if not (isinstance(names, str) or (isinstance(names, list) and names and all(isinstance(n, str) for n in names))):
            raise ValueError(f"typeNames[{index}] must be a name or a non-empty list of names")
    for index, vector in recipe["typeWeights"].items():
        if not (0 <= int(index) <= 15) or len(vector) != n or any(v < 0 for v in vector) or sum(vector) <= 0:
            raise ValueError(f"typeWeights[{index}] needs {n} non-negative weights with a positive sum")
    for key in ("cap", "diagonal"):
        if not 0 <= recipe["transition"].get(key, -1) <= 1:
            raise ValueError("transition cap/diagonal must be 0..1")
    def weight_vector(vector):
        return isinstance(vector, list) and len(vector) == n and all(v >= 0 for v in vector) and sum(vector) > 0
    for key in ("undefinedTypeWeights", "outsideWeights"):
        if key in recipe and not weight_vector(recipe[key]):
            raise ValueError(f"{key} needs {n} non-negative weights with a positive sum")
    if "variation" in recipe:
        variation = recipe["variation"]
        if not 0 < variation.get("amount", 0.5) <= 1 or not 20 <= variation.get("meters", 150) <= 2000:
            raise ValueError("variation needs amount in (0,1] and meters from 20 to 2000")
        for index, vector in variation.get("types", {}).items():
            if index not in recipe["typeWeights"] or not weight_vector(vector):
                raise ValueError(f"variation.types[{index}] needs a mapped type and {n} weights")
    if not 0 <= recipe.get("heightBlend", 0.5) <= 4:
        raise ValueError("heightBlend must be 0..4")
    for layer in recipe["layers"]:
        if not 0 <= layer.get("heightMeters", 0) <= 32 or not 0 < layer.get("specularScale", 1) <= 4:
            raise ValueError(f"layer {layer.get('name')} needs heightMeters 0..32 and specularScale in (0,4]")
        if type(layer.get("detile", False)) is not bool:
            raise ValueError(f"layer {layer.get('name')} detile must be true or false")
        strength = layer.get("proceduralCraters", False)
        if type(strength) not in (bool, int, float) or not 0 <= strength <= 1:
            raise ValueError(f"layer {layer.get('name')} proceduralCraters must be true, false or 0..1")
        strength = layer.get("proceduralDetail", False)
        if type(strength) not in (bool, int, float) or not 0 <= strength <= 1:
            raise ValueError(f"layer {layer.get('name')} proceduralDetail must be true, false or 0..1")
    if "far" in recipe:
        far = recipe["far"]
        if not (2 <= far.get("scale", 0) <= 16 and 0 <= far.get("startMeters", -1) < far.get("endMeters", -1) <= 100000
                and 0 <= far.get("amount", -1) <= 1):
            raise ValueError("far needs scale 2..16, 0 <= startMeters < endMeters and amount 0..1")
    if "macro" in recipe:
        macro = recipe["macro"]
        if not (10 <= macro.get("meters", 0) <= 10000 and 0 <= macro.get("brightness", -1) <= 0.5
                and 0 <= macro.get("saturation", -1) <= 1 and -1 <= macro.get("hue", 0) <= 1):
            raise ValueError("macro needs meters 10..10000, brightness 0..0.5, saturation 0..1 and hue -1..1")
    crater_layers = [layer.get("proceduralCraters", False) for layer in recipe["layers"]]
    if "craters" in recipe:
        craters = recipe["craters"]
        if not (1 <= craters.get("cellMeters", 0) <= 1000 and 0 < craters.get("depth", 0) <= 0.5
                and 0 < craters.get("coverage", 0) <= 1 and craters.get("octaves", 0) in (1, 2, 3)):
            raise ValueError("craters needs cellMeters 1..1000, depth (0,0.5], coverage (0,1] and octaves 1..3")
        if not any(crater_layers):
            raise ValueError("craters needs at least one layer with proceduralCraters")
    elif any(crater_layers):
        raise ValueError("proceduralCraters needs the recipe's craters settings")
    detail_layers = [layer.get("proceduralDetail", False) for layer in recipe["layers"]]
    if "detail" in recipe:
        detail = recipe["detail"]
        if not (2 <= detail.get("waveMeters", 0) <= 1000 and 0 < detail.get("heightMeters", 0) <= 4
                and detail.get("octaves", 0) in (1, 2, 3, 4, 5) and 0 <= detail.get("damping", 1) <= 4):
            raise ValueError("detail needs waveMeters 2..1000, heightMeters (0,4], octaves 1..5 and damping 0..4")
        if not any(detail_layers):
            raise ValueError("detail needs at least one layer with proceduralDetail")
        if recipe.get("diffuseOnly", False):
            raise ValueError("detail needs the full material form, not diffuseOnly")
    elif any(detail_layers):
        raise ValueError("proceduralDetail needs the recipe's detail settings")
    if "slope" in recipe:
        slope = recipe["slope"]
        if not weight_vector(slope.get("weights")) or not 0 <= slope.get("startDegrees", -1) < slope.get("fullDegrees", -1) <= 90:
            raise ValueError(f"slope needs {n} weights and 0 <= startDegrees < fullDegrees <= 90")
    known = {int(k) for k in recipe["typeWeights"]}
    def mapped_types(rule):
        return all(isinstance(t, int) and t in known for t in rule.get("types", []))
    if "shape" in recipe:
        shapes = recipe["shape"] if isinstance(recipe["shape"], list) else [recipe["shape"]]
        for shape in shapes:
            if not (isinstance(shape, dict) and 20 <= shape.get("radiusMeters", 0) <= 1000 and 0 < shape.get("rangeMeters", 0) <= 100
                    and 0 < shape.get("amount", 0.5) <= 1 and ("hollow" in shape or "ridge" in shape)
                    and all(weight_vector(shape[k]) for k in ("hollow", "ridge") if k in shape) and mapped_types(shape)):
                raise ValueError("shape needs radiusMeters 20..1000, rangeMeters (0,100], amount (0,1], "
                                 "hollow and/or ridge weights and mapped types")
    if "erosion" in recipe:
        erosion = recipe["erosion"]
        if not erosion or set(erosion) - set(EROSION_RULES):
            raise ValueError(f"erosion needs one or more of {', '.join(EROSION_RULES)}")
        for key, rule in erosion.items():
            if not (weight_vector(rule.get("weights")) and 0 < rule.get("amount", 0.5) <= 1 and mapped_types(rule)):
                raise ValueError(f"erosion.{key} needs {n} weights, amount (0,1] and mapped types")
        channel = erosion.get("channel", {"startHectares": 1, "fullHectares": 2})
        if not 0 < channel.get("startHectares", 0) < channel.get("fullHectares", 0) <= 100000:
            raise ValueError("erosion.channel needs 0 < startHectares < fullHectares <= 100000")
        for key in ("deposit", "scour", "talus"):
            if key in erosion and not 0 < erosion[key].get("coverage", 0) <= 0.5:
                raise ValueError(f"erosion.{key} needs coverage (0,0.5]")
        if "talus" in erosion and not 20 <= erosion["talus"].get("radiusMeters", 60) <= 1000:
            raise ValueError("erosion.talus needs radiusMeters 20..1000")


def load_map(name, files, recipe, capture_path, weight_size, trust_capture=False):
    hg2, mat, trn = files
    zx, zz, plane = read_hg2(hg2)
    cells = read_mat(mat, zx, zz)
    types = read_trn_types(trn)
    for index, expected in recipe["typeNames"].items():
        # A list accepts any of several names: the stock and Campaign
        # Reimagined copies of one world often label (or omit) types differently.
        accepted = [expected] if isinstance(expected, str) else expected
        if types.get(int(index), "").lower() not in [e.lower() for e in accepted]:
            raise ValueError(f"{name}: TRN texture type {index} is '{types.get(int(index))}', "
                             f"recipe expects {accepted}; add a recipe for this world layout")
    # MAT words can name a type the TRN never defines (stock misn04 has nine
    # such cells in its last column). The engine draws its default tile there,
    # so the recipe supplies undefinedTypeWeights; large counts are an error.
    base, other = (cells >> 12) & 15, (cells >> 8) & 15
    undefined = ~(np.isin(base, [int(k) for k in recipe["typeWeights"]]) & np.isin(other, [int(k) for k in recipe["typeWeights"]]))
    if undefined.mean() > 0.01:
        raise ValueError(f"{name}: {undefined.sum()} cells use texture types the recipe does not map; add a world recipe")
    fingerprint = terrain_fingerprint(zx, zz, plane, read_trn_pad(trn))
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
    weights = rasterize(cells, zx, zz, bounds, weight_size, recipe, plane, int(fingerprint[:8], 16) ^ recipe.get("variation", {}).get("seed", 0))
    return {"name": name, "zones": (zx, zz), "fingerprint": fingerprint, "bounds": bounds,
            "weights": weights, "source": source,
            "histogram": {int(t): int(c) for t, c in zip(*np.unique(cells >> 12, return_counts=True))}}


def make_seamless(image):
    """Wrap-blend a nearly tileable image so its edges meet when repeated.

    The half-offset copy has the original's interior on its border, so it
    wraps continuously; it replaces the original near the edges and fades out
    toward the centre. Stock solid tiles mostly tile already; this hides the
    few whose generated replacements left a visible edge.
    """
    a = np.asarray(image.convert("RGB"), dtype=np.float64)
    h, w = a.shape[:2]
    shifted = np.roll(a, (h // 2, w // 2), axis=(0, 1))
    ry = 1 - np.abs(np.linspace(-1, 1, h))
    rx = 1 - np.abs(np.linspace(-1, 1, w))
    keep = np.clip(np.minimum.outer(ry, rx) * 4, 0, 1)[..., None]
    return Image.fromarray(np.clip(a * keep + shifted * (1 - keep) + 0.5, 0, 255).astype(np.uint8))


# Megascans and Poly Haven member names for each map, keyed by the colour map's suffix.
_SIBLINGS = {"normal": ("Normal", "normal", "nor_gl", "nor_dx"),
             "height": ("Displacement", "height", "disp"),
             "roughness": ("Roughness", "roughness", "rough")}
_COLOR_SUFFIXES = ("BaseColor", "Basecolor", "Albedo", "albedo", "diff", "diffuse")


def _sibling_names(name, kind):
    """Candidate names for a colour map's sibling, swapping the colour token.

    The token may end the stem (Megascans _BaseColor.jpg) or precede a
    resolution tag (Poly Haven _diff_2k.png).
    """
    stem, dot, extension = name.rpartition(".")
    for color in _COLOR_SUFFIXES:
        head, found, tail = stem.rpartition(color)
        if found and (not tail or re.fullmatch(r"_\d+[kK]", tail)):
            for suffix in _SIBLINGS[kind]:
                for ext in (extension, "jpg", "png", "exr"):
                    yield f"{head}{suffix}{tail}.{ext}"


def material_source(root, layer, kind):
    """Source entry for a layer's normal/height/roughness map, or None.

    An explicit layer[kind] is a member of the layer's archive (string) or a
    full source entry (dict). Without one, siblings are found by the usual
    token swap, for example _BaseColor.jpg -> _Normal.jpg or
    _diff_2k.png -> _nor_gl_2k.png, among archive members or next to a file.
    """
    explicit = layer.get(kind)
    if isinstance(explicit, dict):
        return explicit
    if "archive" not in layer:
        if isinstance(explicit, str):
            return {"file": explicit}
        if not layer.get("file"):
            return None
        for candidate in _sibling_names(layer["file"], kind):
            if _hd.source_path(root, candidate).is_file():
                return {"file": candidate}
        return None
    if isinstance(explicit, str):
        return {"archive": layer["archive"], "member": explicit}
    with zipfile.ZipFile(_hd.source_path(root, layer["archive"])) as archive:
        names = set(archive.namelist())
    for candidate in _sibling_names(layer["member"], kind):
        if candidate in names:
            return {"archive": layer["archive"], "member": candidate}
    return None


def wrap_blend(a):
    """make_seamless for a float array of any channel count."""
    h, w = a.shape[:2]
    shifted = np.roll(a, (h // 2, w // 2), axis=(0, 1))
    ry = 1 - np.abs(np.linspace(-1, 1, h))
    rx = 1 - np.abs(np.linspace(-1, 1, w))
    keep = np.clip(np.minimum.outer(ry, rx) * 4, 0, 1)
    keep = keep[..., None] if a.ndim == 3 else keep
    return a * keep + shifted * (1 - keep)


def gray(image, size):
    a = np.asarray(image.convert("RGB").resize((size, size), Image.Resampling.LANCZOS), dtype=np.float64) / 255
    return a[..., 0]


def normalize_height(h, clip=1):
    """Centre on the median and stretch the clip..100-clip percentiles to 0..1."""
    lo, mid, hi = np.percentile(h, (clip, 50, 100 - clip))
    span = max(hi - lo, 1e-6)
    return np.clip((h - mid) / span + 0.5, 0, 1)


def height_slopes(h, meters, repeat):
    """Metres of rise per metre along +column and +row of a tiling height."""
    texel = repeat / h.shape[0]
    dx = (np.roll(h, -1, axis=1) - np.roll(h, 1, axis=1)) * meters / (2 * texel)
    dy = (np.roll(h, -1, axis=0) - np.roll(h, 1, axis=0)) * meters / (2 * texel)
    return dx, dy


def orient_normal(n, h):
    """Flip normal X/Y so they agree with the height: +x along +column, +y along +row.

    That matches the paint shader's cotangent frame (T along world X / +u,
    B along world Z / +v). DirectX and OpenGL normal maps differ only in Y,
    so each axis is checked against the height gradient instead of trusted.
    """
    dx, dy = height_slopes(h, 1, h.shape[0])
    flips = []
    for axis, slope in ((0, dx), (1, dy)):
        agreement = float(np.mean(n[..., axis] * -slope))
        if agreement < 0:
            n[..., axis] = -n[..., axis]
        flips.append(agreement < 0)
    return n, flips


def crater_field(size, repeat, craters):
    """Tileable impact craters in metres: parabolic bowls with raised rims.

    Diameters follow a power law between minMeters and maxMeters (many small,
    few large) and depth is a fifth of the diameter, as on the Moon. Positions
    wrap, so the field tiles exactly. Deterministic for a given seed.
    """
    rng = np.random.default_rng(craters.get("seed", 1))
    lo, hi = craters.get("minMeters", 1), craters.get("maxMeters", 10)
    texel = repeat / size
    field = np.zeros((size, size))
    for _ in range(int(craters.get("count", 40))):
        u = rng.random()
        diameter = lo * (hi / lo) ** (1 - np.sqrt(u))  # skewed toward small craters
        radius = diameter / 2 / texel
        extent = int(np.ceil(radius * 1.8)) + 1
        cx, cy = rng.random(2) * size
        offsets = np.arange(-extent, extent + 1)
        xs = (int(cx) + offsets) % size
        ys = (int(cy) + offsets) % size
        dx = (int(cx) + offsets - cx)[None, :]
        dy = (int(cy) + offsets - cy)[:, None]
        r = np.sqrt(dx * dx + dy * dy) / radius
        # Large craters are shallower for their size; floors flatten and rims sharpen.
        depth = 0.2 * diameter ** 0.8
        rim = 0.3 * depth
        bowl = np.where(r < 1, (r ** 3 - 1) * depth + rim, rim * np.exp(-((r - 1) / 0.18) ** 2))
        field[np.ix_(ys, xs)] += np.where(r < 1.8, bowl, 0)
    return field


def material_maps(root, layer, diffuse, size, repeat):
    """(normal RGB, height, specular) planes for one layer plus their identity.

    Missing maps are derived: height from the colour's high-passed luminance,
    the normal from that height, specular as neutral 0.5.
    """
    identity = {}
    def load(kind):
        entry = material_source(root, layer, kind)
        if entry is None:
            return None
        image, source = _hd.load_art(root, entry)
        identity[kind] = source
        return image
    height_image = load("height")
    if height_image is not None:
        height = normalize_height(gray(height_image, size))
    else:
        lum = gray(diffuse, size)
        blur = np.asarray(Image.fromarray((lum * 255).astype(np.uint8)).filter(
            ImageFilter.GaussianBlur(max(size / 32, 1))), dtype=np.float64) / 255
        height = normalize_height(lum - blur)
        identity["height"] = "derived from colour luminance"
    normal_image = load("normal")
    source = None
    if normal_image is not None:
        source = np.asarray(normal_image.convert("RGB").resize((size, size), Image.Resampling.LANCZOS), dtype=np.float64) / 127.5 - 1
        source, flips = orient_normal(source, height)
        identity["normalFlipXY"] = flips
    if layer.get("craters"):
        # Craters carry the shape; the source height stays as fine texture.
        craters = crater_field(size, repeat, layer["craters"])
        detail = layer["craters"].get("detail", 0.1)
        height = normalize_height(craters / max(np.ptp(craters), 1e-6) + (height - 0.5) * detail, 0.05)
        identity["craters"] = layer["craters"]
    if source is not None and not layer.get("craters"):
        n = source
    else:
        # Bump strength for derived normals: a few decimetres over the repeat.
        dx, dy = height_slopes(height, layer.get("derivedReliefMeters", 0.25), repeat)
        n = np.dstack((-dx, -dy, np.ones_like(dx)))
        identity["normal"] = "derived from height"
        if source is not None:
            # The source normal keeps its fine detail on top of the crater shape.
            n[..., :2] += source[..., :2] / np.maximum(source[..., 2:], 0.2)
            identity["normal"] = "derived from height plus source detail"
    rough_image = load("roughness")
    if rough_image is not None:
        specular = (1 - gray(rough_image, size)) * layer.get("specularScale", 1)
    else:
        specular = np.full((size, size), 0.5 * layer.get("specularScale", 1))
    if layer.get("seamless"):
        n, height, specular = wrap_blend(n), wrap_blend(height), wrap_blend(specular)
    n /= np.maximum(np.linalg.norm(n, axis=2, keepdims=True), 1e-6)
    return n, np.clip(height, 0, 1), np.clip(specular, 0, 1), identity


def to_u8(a):
    return np.clip(a * 255 + 0.5, 0, 255).astype(np.uint8)


def match_mean(image, reference):
    """Scale each channel so the image's mean colour equals the reference's.

    Lets photographic layer art take the palette of a world's existing tiles
    without repainting it.
    """
    a = np.asarray(image.convert("RGB"), dtype=np.float64)
    target = np.asarray(reference.convert("RGB"), dtype=np.float64).reshape(-1, 3).mean(axis=0)
    scale = target / np.maximum(a.reshape(-1, 3).mean(axis=0), 1e-6)
    return Image.fromarray(np.clip(a * scale + 0.5, 0, 255).astype(np.uint8))


def build_pack(maps, recipe, source_root, output, size, prefix, force):
    output = Path(output)
    if output.exists() and any(output.iterdir()) and not force:
        raise ValueError("output is non-empty; use --force")
    root = Path(source_root).resolve()
    layers, identities, repeats, normals = [], [], [], []
    # Full material (9 slices per four layers) unless the recipe asks for diffuse only.
    material = not recipe.get("diffuseOnly", False)
    n = len(recipe["layers"])
    if n not in (4, 8) or (n == 8 and not material):
        raise ValueError("a pack needs four layers, or eight with the full material form")
    for layer in recipe["layers"]:
        repeat = layer.get("repeatMeters")
        if type(repeat) not in (int, float) or not 1 <= repeat <= 4096 or not layer.get("name"):
            raise ValueError("each layer needs a name and repeatMeters from 1 to 4096")
        art, identity = _hd.load_art(root, layer)
        art = art.resize((size, size), Image.Resampling.LANCZOS)
        if "saturation" in layer:
            # Mute off-world tints (rust, moss) before the mean match recolours.
            saturation = layer["saturation"]
            if type(saturation) not in (int, float) or not 0 <= saturation <= 2:
                raise ValueError("layer saturation must be from 0 to 2")
            art = ImageEnhance.Color(art.convert("RGB")).enhance(saturation)
            identity = dict(identity, saturation=saturation)
        if layer.get("matchMean"):
            reference, reference_identity = _hd.load_art(root, {"file": layer["matchMean"]})
            art = match_mean(art, reference)
            identity = dict(identity, matchMean=reference_identity)
        if layer.get("gain"):
            # Per-channel trim measured from in-game before/after shots.
            gain = layer["gain"]
            if len(gain) != 3 or not all(0.25 <= g <= 4 for g in gain):
                raise ValueError("layer gain needs three factors from 0.25 to 4")
            art = Image.fromarray(np.clip(np.asarray(art.convert("RGB"), dtype=np.float64) * gain + 0.5, 0, 255).astype(np.uint8))
            identity = dict(identity, gain=gain)
        if layer.get("seamless"):
            art = make_seamless(art)
            identity = dict(identity, seamless=True)
        if material:
            normal, height, specular, maps_identity = material_maps(root, layer, art, size, repeat)
            identity = dict(identity, material=maps_identity)
            # Diffuse alpha carries specular; the normal slice carries height.
            rgb = np.asarray(art.convert("RGB"))
            layers.append(Image.fromarray(np.dstack((rgb, to_u8(specular))), "RGBA"))
            normals.append(Image.fromarray(np.dstack((to_u8(normal * 0.5 + 0.5), to_u8(height))), "RGBA"))
        else:
            layers.append(art.convert("RGBA"))
        identities.append(identity)
        repeats.append(repeat)
    capture_material = recipe.get("material", "MA_DETAIL_ATLAS")
    output.mkdir(parents=True, exist_ok=True)
    resources = [f"{prefix}_layer{i}.png" for i in range(n)]
    normal_resources = [f"{prefix}_layer{i}_n.png" for i in range(n)] if material else []
    for resource, image in zip(resources + normal_resources, layers + normals):
        image.save(output / resource)
    entries, summary, controls, terrains = [], [], {}, {}
    for info in maps:
        weights = info["weights"]
        key = weights_key(weights)
        # The runtime tells maps apart only by terrain, so two missions sharing
        # one (CR misn15 and misn15b) need one entry and identical paint.
        terrain = (info["fingerprint"], tuple(info["bounds"]))
        if terrain in terrains:
            if weights_key(terrains[terrain]["weights"]) != key:
                raise ValueError(f"{info['name']} and {terrains[terrain]['name']} share terrain {info['fingerprint']} "
                                 "but paint differently; the runtime cannot tell them apart")
            summary.append(dict({k: info[k] for k in ("name", "fingerprint", "bounds", "source", "histogram")},
                                sharesEntryWith=terrains[terrain]["name"]))
            continue
        terrains[terrain] = info
        # Maps with identical layouts (for example the stock and Campaign
        # Reimagined copies of one mission) share a single control image.
        suffixes = ["control", "control2"][:n // 4]
        if key not in controls:
            # Eight layers normalise jointly across both images.
            channels = [np.asarray(c.resize((size, size), Image.Resampling.BILINEAR)) for image in weight_images(weights) for c in image.split()]
            stacked = np.stack(channels, axis=-1).reshape(-1, n)
            packed = np.array([normalize(tuple(p)) for p in stacked.tolist()], dtype=np.uint8).reshape(size, size, n)
            names = [f"{prefix}_{info['name']}_{suffix}.png" for suffix in suffixes]
            for k, name in enumerate(names):
                Image.fromarray(packed[..., 4 * k:4 * k + 4], "RGBA").save(output / name)
            controls[key] = names
        for k, image in enumerate(weight_images(weights)):
            image.save(output / f"{prefix}_{info['name']}_weights{k + 1 if k else ''}.png")
        entry = {"terrainFingerprint": info["fingerprint"], "boundsMeters": info["bounds"], "control": controls[key][0]}
        if n == 8:
            entry["control2"] = controls[key][1]
        entries.append(entry)
        summary.append({k: info[k] for k in ("name", "fingerprint", "bounds", "source", "histogram")})
    # Each bank of four layers is nine slices: diffuse 0-3, control 4, normal+height 5-8.
    tiles = {str(i // 4 * 9 + i % 4): name for i, name in enumerate(resources)}
    tiles["4"] = entries[0]["control"]
    if n == 8:
        tiles["13"] = entries[0]["control2"]
    tiles.update({str(i // 4 * 9 + 5 + i % 4): name for i, name in enumerate(normal_resources)})
    paint = {"schema": "bzr-openshim-terrain-paint-v1", "rowZero": "minZ", "repeatMeters": repeats, "maps": entries}
    if any(layer.get("detile") for layer in recipe["layers"]):
        paint["detile"] = [1 if layer.get("detile") else 0 for layer in recipe["layers"]]
    if "far" in recipe:
        far = recipe["far"]
        paint["far"] = [far["scale"], far["startMeters"], far["endMeters"], far["amount"]]
    if "macro" in recipe:
        macro = recipe["macro"]
        paint["macro"] = [macro["meters"], macro["brightness"], macro["saturation"]] + ([macro["hue"]] if macro.get("hue") else [])
    if material:
        paint["heightBlend"] = recipe.get("heightBlend", 0.5)
        paint["heightMeters"] = [layer.get("heightMeters", 0) for layer in recipe["layers"]]
        if "craters" in recipe:
            craters = recipe["craters"]
            paint["craters"] = [craters["cellMeters"], craters["depth"], craters["coverage"], craters["octaves"]]
            paint["craterLayers"] = [float(layer.get("proceduralCraters", 0)) for layer in recipe["layers"]]
        if "detail" in recipe:
            detail = recipe["detail"]
            paint["detail"] = [detail["waveMeters"], detail["heightMeters"], detail["octaves"], detail.get("damping", 1)]
            paint["detailLayers"] = [float(layer.get("proceduralDetail", 0)) for layer in recipe["layers"]]
    manifest = {"schema": "bzr-openshim-terrain-hd-v1", "materials": {capture_material: {
        "sliceCount": 9 * (n // 4) if material else 5, "diffuseResource": recipe["diffuseResource"], "fallback": resources[0],
        "tiles": tiles, "paint": paint}}}
    (output / f"{prefix}.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    project = {"schema": "bzr-openshim-terrain-autopaint-project-v1", "prefix": prefix, "materialSize": size,
               "layers": recipe["layers"], "sources": identities, "maps": summary}
    (output / f"{prefix}_project.json").write_text(json.dumps(project, indent=2) + "\n", encoding="utf-8")
    if n == 4:
        write_editors(maps, recipe, layers, repeats, identities, output, prefix, size)
    else:
        print("Eight-layer pack: the weight editor only handles four layers, so none was written")
    return manifest


def write_editors(maps, recipe, layers, repeats, identities, output, prefix, size):
    """One standalone editor per map, preloaded with the generated weights, for touch-up."""
    previews = []
    for image in layers:
        stream = io.BytesIO(); image.convert("RGB").resize((128, 128), Image.Resampling.LANCZOS).save(stream, format="PNG")
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
