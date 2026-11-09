"""Live paint parity: the C++ generator (include/terrain_live_paint.h) against
scripts/Build-TerrainAutoPaint.py on the same MAT and HG2 data.

Variation and ragged-edge noise are stripped from the recipe first: the C++
side uses a hash where Python uses numpy's PCG64, so those can only match in
distribution, which the second pass reports (mean per layer, not per pixel).

    terrain_live_paint_parity.py --generator <terrain_live_paint_tests.exe>
        synthetic map (CTest)
    ... --map <name.hg2> <name.mat> <world-autopaint.json> [--size N]
        a real map; prints the differences and fails over tolerance
"""
import argparse
import copy
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import time

import numpy as np
from PIL import Image

spec = importlib.util.spec_from_file_location("autopaint", Path(__file__).parents[1] / "scripts/Build-TerrainAutoPaint.py")
auto = importlib.util.module_from_spec(spec)
spec.loader.exec_module(auto)

MAX_DIFF, MEAN_DIFF = 3, 0.25


def synthetic():
    """Same map as Synthetic() in terrain_live_paint_tests.cpp."""
    x, z = np.meshgrid(np.arange(256), np.arange(256))
    plane = (np.abs(x - 100) * np.abs(z - 150) // 4 % 3000 + 2 * x + x * x // 128).astype(np.uint16)
    cx, cz = np.meshgrid(np.arange(64), np.arange(64))
    base = np.where((cx // 16 + cz // 16) % 2 == 1, 3, 0)
    nxt = np.where(((cx + 1) // 16 + cz // 16) % 2 == 1, 3, 0)
    cells = (base << 12 | nxt << 8 | (cx % 2) << 7).astype(np.uint16)
    return 1, 1, plane, cells


def strip_noise(recipe):
    recipe = copy.deepcopy(recipe)
    recipe.pop("variation", None)
    for layer in recipe["layers"]:
        if "edge" in layer:
            layer["edge"].pop("ragged", None)
    return recipe


def python_controls(recipe, zx, zz, plane, cells, size, seed):
    """rasterize() plus the builder's control step (bilinear upscale, joint normalise)."""
    bounds = auto.terrain_bounds(zx, zz)
    weight_size = min(recipe.get("weightSize", 1024), size)
    weights = auto.rasterize(cells, zx, zz, bounds, weight_size, recipe, plane, seed)
    channels = [np.asarray(c.resize((size, size), Image.Resampling.BILINEAR))
                for image in auto.weight_images(weights) for c in image.split()]
    return auto.normalize_array(np.stack(channels, axis=-1)).astype(np.int32)


def cpp_controls(generator, recipe, zx, zz, plane, cells, size, seed, work):
    bounds = auto.terrain_bounds(zx, zz)
    (work / "recipe.json").write_text(json.dumps(recipe))
    (work / "input.bin").write_bytes(struct.pack("<ii4fI", zx, zz, *bounds, seed)
                                     + cells.astype("<u2").tobytes() + plane.astype("<u2").tobytes())
    start = time.perf_counter()
    subprocess.run([generator, work / "recipe.json", work / "input.bin", work / "out.rgba", str(size)], check=True)
    print(f"c++ generator {zx}x{zz} zones at {size}px: {time.perf_counter() - start:.2f} s (includes process start and file IO)")
    n = len(recipe["layers"])
    raw = np.frombuffer((work / "out.rgba").read_bytes(), dtype=np.uint8).reshape(n // 4, size, size, 4)
    return np.concatenate(list(raw), axis=-1).astype(np.int32)


def compare(generator, recipe, zx, zz, plane, cells, size, seed=0):
    with tempfile.TemporaryDirectory() as work:
        work = Path(work)
        exact = strip_noise(recipe)
        diff = np.abs(python_controls(exact, zx, zz, plane, cells, size, seed)
                      - cpp_controls(generator, exact, zx, zz, plane, cells, size, seed, work))
        print(f"no-noise recipe: max {diff.max()} mean {diff.mean():.4f} pixels>1 {np.mean(diff.max(axis=-1) > 1):.4%}")
        ok = diff.max() <= MAX_DIFF and diff.mean() <= MEAN_DIFF
        if "variation" in recipe:
            py = python_controls(recipe, zx, zz, plane, cells, size, seed).mean(axis=(0, 1)) / 255
            cc = cpp_controls(generator, recipe, zx, zz, plane, cells, size, seed, work).mean(axis=(0, 1)) / 255
            print("with variation, layer share python " + " ".join(f"{v:.3f}" for v in py)
                  + " | c++ " + " ".join(f"{v:.3f}" for v in cc))
    return ok


def check_dump(generator, dump, hg2, mat, recipe_path):
    """A live dump (OPENSHIM_TERRAIN_PAINT_LIVE_DUMP) against the map's own files:
    the engine-read heights and MAT words must equal the files, and the CLI must
    reproduce the in-game images from the dumped input."""
    raw = Path(dump).read_bytes()
    zx, zz, *_ = struct.unpack_from("<ii4fI", raw)
    cells_n = zx * zz * 64 * 64
    cells = np.frombuffer(raw, "<u2", cells_n, 28).reshape(zz * 64, zx * 64)
    plane = np.frombuffer(raw, "<u2", cells_n * 16, 28 + cells_n * 2).reshape(zz * 256, zx * 256)
    fzx, fzz, fplane = auto.read_hg2(hg2)
    fcells = auto.read_mat(mat, fzx, fzz)
    ok = (fzx, fzz) == (zx, zz)
    print(f"zones dump {zx}x{zz} file {fzx}x{fzz}")
    if ok:
        hd, cd = np.count_nonzero(plane != fplane), np.count_nonzero(cells != fcells)
        print(f"height samples differing {hd}/{plane.size}; material words differing {cd}/{cells.size}")
        ok = hd == 0 and cd == 0
    game = Path(dump).with_suffix(".rgba").read_bytes()
    size = int(round((len(game) // 4 // (len(json.loads(Path(recipe_path).read_text())["layers"]) // 4)) ** 0.5))
    with tempfile.TemporaryDirectory() as work:
        out = Path(work) / "out.rgba"
        subprocess.run([generator, recipe_path, dump, out, str(size)], check=True)
        same = out.read_bytes() == game
    print(f"cli reproduces in-game images at {size}px: {same}")
    return ok and same


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--generator", required=True)
    parser.add_argument("--map", nargs=3, metavar=("HG2", "MAT", "RECIPE"))
    parser.add_argument("--dump", nargs=4, metavar=("LIVE_BIN", "HG2", "MAT", "RECIPE"))
    parser.add_argument("--size", type=int, default=256)
    args = parser.parse_args()
    if args.dump:
        return 0 if check_dump(args.generator, *args.dump) else 1
    if args.map:
        zx, zz, plane = auto.read_hg2(args.map[0])
        cells = auto.read_mat(args.map[1], zx, zz)
        recipe = json.loads(Path(args.map[2]).read_text())
    else:
        zx, zz, plane, cells = synthetic()
        recipe = json.loads(Path(__file__).with_name("terrain_live_paint_recipe.json").read_text())
    return 0 if compare(args.generator, recipe, zx, zz, plane, cells, args.size) else 1


if __name__ == "__main__":
    sys.exit(main())
