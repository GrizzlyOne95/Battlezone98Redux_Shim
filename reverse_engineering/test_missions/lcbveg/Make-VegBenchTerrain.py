"""Generate lcbveg.hg2 and lcbveg.mat: an Achilles valley for content testing.

## Why this map is not lcbench's

Every other map in this family reuses lcbench's heightfield on purpose: holding
the geometry fixed is what lets a difference between two captures be attributed
to the renderer rather than to the ground. That is the right rule for a renderer
benchmark and the wrong one here.

lcbench's heightfield is a plain at raw height 0 with a steep berm through it --
75% of its material cells report painter elevation 0, and only slope
discriminates anything. A river cannot be painted into a surface with no low
ground, and Achilles' river, waterfall and tree tiles are exactly what this
mission exists to put on screen. So this map is synthesised: a meandering
channel through rolling grassland, wooded mid-slopes and rocky ridges.

The tradeoff is explicit. Use lcbworld/lcbachil for renderer captures, where the
shared geometry matters. Use this for content, where having somewhere for water
to be matters more.

## Encoding

Both formats are written through Battlezone98Redux_WorldBuilder rather than by
hand. An earlier draft of this script reverse-engineered the .mat from lcbench
and got two things wrong that would have produced a plausible, silently broken
file: it read the type nibbles backwards (the high nibble is Base/from, the low
is Next/to), and it assumed a flat 256x256 row-major grid when the real layout
is 4x4 zones of 64x64 stored zone by zone. WorldBuilder's mat_codec is
MakeTRN-compatible and already validated against the published format notes and
BZMapIO, so it is the authority here.

It also counts transitions whose CapTo*/DiagonalTo* tiles the .trn does not
declare. That matters more than it sounds: an undeclared tile key does not fail,
it silently draws the default tile, which reads as a rendering bug rather than a
missing declaration.

An earlier version of this script failed the build on any such tile. That bar
turned out to be stricter than the game's own content: every Achilles .trn
declares only (0,1), (0,5) and (1,2), yet stock misn17.mat emits 1705
undeclared (0,2) grass<->rocky transitions -- 2.6% of its cells. So the check
reports the rate and warns only well above it. This map currently sits at the
same 2.6%.

Worth knowing while looking at the output: no shipped Achilles map paints
material 3 (river) or 4 (waterfall) at all. misn17, misn18 and multdm14 use
only grass, trees, rocky and Base. Those tilesets are declared by every Achilles
.trn and have never been rendered by anything, so this map is the first thing
that puts them on screen -- and if they turn out to be broken, that is a
discovery rather than a regression.

Usage:
    python Make-VegBenchTerrain.py [--worldbuilder <repo>] [--seed 7]
"""

import argparse
import io
import math
import os
import sys

ZONES = 4                  # 4x4 zones of 1280 world units = 5120, matching the .trn
SAMPLES_PER_ZONE = 256     # HG2 density: 5 world units per sample
DIM = ZONES * SAMPLES_PER_ZONE
WORLD_UNITS = ZONES * 1280.0
UNITS_PER_SAMPLE = WORLD_UNITS / DIM

# Achilles' own material numbering, straight from Edit/trn/achilles.trn.
GRASS, TREES, ROCKY, RIVER, WATERFALL, BASE = 0, 1, 2, 3, 4, 5

# Painter elevation is trunc(min_raw_height_in_neighbourhood / 5), so these are
# raw heights divided by five. Kept as raw here and converted once, so the
# terrain and the rules cannot drift apart silently.
RIVER_BED_RAW = 60
FLOODPLAIN_RAW = 430
WOODED_RAW = 980


def default_worldbuilder():
    here = os.path.dirname(os.path.abspath(__file__))
    for candidate in (
            os.path.join(here, "..", "..", "..", "Battlezone98Redux_WorldBuilder"),
            r"C:\Users\iestu\Documents\GIT\Battlezone98Redux_WorldBuilder"):
        resolved = os.path.normpath(candidate)
        if os.path.isfile(os.path.join(resolved, "mat_codec.py")):
            return resolved
    return None


def build_heights(seed):
    """A valley: river channel, floodplain, wooded slopes, rocky rim.

    Deliberately analytic rather than noise-based. The point of a fixture is
    that two people looking at it are looking at the same thing, and a closed
    form is reproducible without shipping a noise table.
    """
    import numpy as np

    axis = np.arange(DIM, dtype=np.float64)
    x = axis[None, :] / float(DIM)   # 0..1 west to east
    z = axis[:, None] / float(DIM)   # 0..1 north to south

    # Rolling base, a few octaves of smooth relief.
    base = (0.50 * np.sin(x * math.tau * 1.3 + 0.7) * np.cos(z * math.tau * 0.9)
            + 0.28 * np.sin(x * math.tau * 2.7 + 2.1) * np.cos(z * math.tau * 2.3 + 1.1)
            + 0.14 * np.sin(x * math.tau * 5.1) * np.cos(z * math.tau * 4.3 + 0.4))
    base = (base - base.min()) / (base.max() - base.min())

    # The channel meanders in z as a function of x, so it crosses the map east
    # to west and is never a straight line the eye can dismiss.
    meander = 0.5 + 0.13 * np.sin(x * math.tau * 1.15) + 0.05 * np.sin(x * math.tau * 2.9 + 1.3)
    distance = np.abs(z - meander)

    channel_half = 0.022          # ~113 world units of open water
    bank_half = 0.075             # to the top of the bank

    # 1 in the channel, falling smoothly to 0 at the top of the bank.
    carve = np.clip((bank_half - distance) / (bank_half - channel_half), 0.0, 1.0)
    carve = np.where(distance <= channel_half, 1.0, carve)
    carve = carve * carve * (3.0 - 2.0 * carve)   # smoothstep

    # A rocky rim around the edge so the map has steep ground somewhere
    # predictable, which is what the rocky rule keys on.
    # np.maximum rather than maximum.reduce over a list: x is (1, DIM) and z is
    # (DIM, 1), which reduce will not broadcast but pairwise maximum will.
    edge = np.clip((0.09 - x) / 0.09, 0.0, 1.0)
    edge = np.maximum(edge, np.clip((x - 0.91) / 0.09, 0.0, 1.0))
    edge = np.maximum(edge, np.clip((0.09 - z) / 0.09, 0.0, 1.0))
    edge = np.maximum(edge, np.clip((z - 0.91) / 0.09, 0.0, 1.0))
    edge = edge * edge

    raw = (FLOODPLAIN_RAW
           + base * (WOODED_RAW - FLOODPLAIN_RAW)
           + edge * 1900.0)
    raw = raw * (1.0 - carve) + RIVER_BED_RAW * carve

    heights = np.rint(np.clip(raw, 0, 4095)).astype("uint16")
    return heights


def paint_rules():
    """Disjoint elevation/slope bands, so rule order cannot change the result.

    Together they cover every (elevation, slope) pair, which matters because
    generate_mat runs strict: an uncovered sample raises rather than silently
    falling back to material 0.
    """
    river_top = RIVER_BED_RAW * 3 // 5          # a little above the bed
    grass_top = FLOODPLAIN_RAW * 2 // 5
    return [
        # Anything low enough is water, at any slope: that is the channel.
        {"mat_id": RIVER, "min_h": 0, "max_h": river_top,
         "min_s": 0, "max_s": 90, "mask_path": ""},
        # Calm low ground is grass.
        {"mat_id": GRASS, "min_h": river_top + 1, "max_h": grass_top,
         "min_s": 0, "max_s": 25, "mask_path": ""},
        # Calm mid ground is wooded.
        {"mat_id": TREES, "min_h": grass_top + 1, "max_h": WOODED_RAW // 5,
         "min_s": 0, "max_s": 25, "mask_path": ""},
        # Calm high ground is bare rock again, above the tree line.
        {"mat_id": ROCKY, "min_h": WOODED_RAW // 5 + 1, "max_h": 4095,
         "min_s": 0, "max_s": 25, "mask_path": ""},
        # Anything steep above the waterline is rock, whatever its height.
        {"mat_id": ROCKY, "min_h": river_top + 1, "max_h": 4095,
         "min_s": 26, "max_s": 90, "mask_path": ""},
    ]


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    parser = argparse.ArgumentParser()
    parser.add_argument("--worldbuilder", default=default_worldbuilder())
    parser.add_argument("--trn", default=os.path.join(here, "lcbveg.trn"))
    parser.add_argument("--out-hg2", default=os.path.join(here, "lcbveg.hg2"))
    parser.add_argument("--out-mat", default=os.path.join(here, "lcbveg.mat"))
    parser.add_argument("--out-lgt", default=os.path.join(here, "lcbveg.lgt"))
    parser.add_argument("--seed", type=int, default=7)
    args = parser.parse_args()

    if not args.worldbuilder or not os.path.isfile(
            os.path.join(args.worldbuilder, "mat_codec.py")):
        print("Battlezone98Redux_WorldBuilder not found. Pass --worldbuilder "
              "<repo>. The .mat and .hg2 encoders live there deliberately; "
              "this script does not carry a second copy of them.",
              file=sys.stderr)
        return 2
    sys.path.insert(0, args.worldbuilder)

    import numpy as np
    import hg2_codec
    import mat_codec

    heights = build_heights(args.seed)
    hg2_codec.write_hg2(args.out_hg2, heights, ZONES, ZONES)

    # Lightmap: (zones + 1) * 256 * 256 bytes, a bordered per-zone layout.
    # Filled uniformly with the unshadowed value rather than baked, because
    # there is no baker here and the alternative -- reusing lcbench's -- would
    # paint a flat plain's shadows onto a valley, where the mismatch would read
    # as a lighting bug rather than as a missing lightmap. 0x92 is the value
    # covering 71% of lcbench.lgt; its shadowed counterpart is 0x38.
    lit = bytes([0x92]) * ((ZONES * ZONES + 1) * 256 * 256)
    with open(args.out_lgt, "wb") as handle:
        handle.write(lit)

    # parse_trn_painter only recognises a section line that ENDS with ']', but
    # every Achilles .trn labels its sections "[TextureType0] // grass". Left
    # alone, every TextureType block is skipped and the declared-transition set
    # comes back empty -- which makes the check below vacuous rather than
    # wrong, the worst kind of passing test. Strip trailing comments first.
    sanitised = os.path.join(here, ".lcbveg-trn-sanitised.tmp")
    with io.open(args.trn, encoding="cp1252", errors="replace", newline=None) as src:
        cleaned = []
        for line in src:
            if line.lstrip().startswith("["):
                line = line.split("//", 1)[0].rstrip() + os.linesep
            cleaned.append(line)
    with io.open(sanitised, "w", encoding="cp1252", newline="") as dst:
        dst.writelines(cleaned)
    try:
        painter = mat_codec.parse_trn_painter(sanitised)
    finally:
        try:
            os.remove(sanitised)
        except OSError:
            pass
    if not painter.texture_types:
        print("FAIL: no TextureType sections parsed from %s" % args.trn,
              file=sys.stderr)
        return 1
    rules = paint_rules()
    entries, stats = mat_codec.generate_mat(
        heights, rules, ZONES, ZONES,
        cap_transitions=painter.cap_transitions,
        diagonal_transitions=painter.diagonal_transitions,
        legacy_seed=args.seed, strict=True)
    mat_codec.write_mat(args.out_mat, entries, ZONES, ZONES)

    names = {GRASS: "grass", TREES: "trees", ROCKY: "rocky",
             RIVER: "river", WATERFALL: "waterfall", BASE: "base"}
    decoded = np.vectorize(lambda v: mat_codec.decode_entry(int(v)).base)(entries)
    total = float(decoded.size)

    print("worldbuilder : %s" % args.worldbuilder)
    print("hg2          : %s  (%dx%d samples, %.0f world units, %.1f units/sample)"
          % (args.out_hg2, DIM, DIM, WORLD_UNITS, UNITS_PER_SAMPLE))
    print("raw height   : min=%d max=%d" % (heights.min(), heights.max()))
    print("mat          : %s  (%d cells)" % (args.out_mat, decoded.size))
    print("lgt          : %s  (uniform 0x92, unshadowed)" % args.out_lgt)
    print("trn declares : types=%s caps=%s diagonals=%s"
          % (list(painter.texture_types),
             sorted(painter.cap_transitions), sorted(painter.diagonal_transitions)))
    for value in sorted(set(int(v) for v in np.unique(decoded))):
        count = int((decoded == value).sum())
        print("  material %d %-9s %6d cells  %5.1f%%"
              % (value, names.get(value, "?"), count, 100.0 * count / total))
    print("tiles        : solid=%d cap=%d diagonal=%d ambiguous=%d"
          % (stats.solid_tiles, stats.cap_tiles, stats.diagonal_tiles,
             stats.ambiguous_tiles))
    print("unmatched    : %d" % stats.unmatched_samples)
    print("unsupported transitions: %d" % stats.unsupported_transition_tiles)

    # Not a failure, on the evidence. Stock misn17.mat emits 1705 undeclared
    # (0,2) grass<->rocky transitions over 65536 cells -- 2.6% -- against a .trn
    # that declares only (0,1), (0,5) and (1,2). Shipped Achilles content would
    # not pass a hard zero here, so a hard zero is the wrong bar. Report the
    # rate, and only complain when it is well outside what ships.
    rate = 100.0 * stats.unsupported_transition_tiles / total
    print("             (%.1f%% of cells; stock misn17 runs at 2.6%%)" % rate)
    if rate > 8.0:
        print("", file=sys.stderr)
        print("WARNING: undeclared transitions are far above the rate stock "
              "Achilles content runs at. Those cells draw the default tile "
              "instead of failing, so this will read as a rendering bug rather "
              "than as a missing declaration.", file=sys.stderr)
    if stats.unmatched_samples:
        print("\nFAIL: %d samples matched no layer rule."
              % stats.unmatched_samples, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
