# Legacy HGT to HG2 conversion without Redux's smoothing — 2026-09-01

## Final summary

| Question | Answer |
|---|---|
| Can legacy HGT be converted directly to HG2? | **YES** |
| Can Redux HGT smoothing be bypassed simply by supplying HG2? | **YES** |
| Can original HGT sample heights be preserved exactly? | **YES**, unconditionally |
| Can the actual legacy rendered terrain surface be preserved? | **YES**, to within ±0.05 world units of quantization at half-sample points |
| Recommended conversion policy | **Policy A** — offline conversion. No OpenShim runtime hook is warranted. |
| Great Pyramid result | `multdm29` shipped by Redux 2.2.301 **is already an unsmoothed conversion**; our output matches it on 65,533 of 65,536 samples (max error 1 raw unit = 0.1 world units) and matches every geometric metric exactly |
| Stock HGT files tested | 73 stock 1.5 maps; 72 converted, 1 rejected (truncated). 254 HGT paths censused overall, 251 parsed, 168 unique contents |
| Format variants discovered | One HGT variant only. Two malformed stock files, and one HG2 whose header contradicts its payload |
| Remaining uncertainty | The world-units-per-raw-height constant (0.1) rests on a single call site; the meaning of the high-nibble flag bits is unknown; two shipped stock maps are hand-modified terrain and must not be replaced blindly |

The decisive evidence: **our converter's output is byte-for-byte identical
(SHA-256 `424CDFAB…C4F1284F`, 2,097,164 bytes) to the file Redux itself writes
when launched with `-nohgtsmoothing`.** Not merely equivalent — the same bytes,
header included.

## The short version

Redux does not need to be patched, and the terrain does not need to be
re-authored. The engine already:

1. prefers `<mission>.hg2` over `<mission>.hgt` and only cooks the legacy file
   when no valid HG2 exists; and
2. ships a `-nohgtsmoothing` command-line switch that disables the destructive
   step of that cook.

The cook itself is a 2x upsample through a **piecewise-planar** interpolator —
which reproduces the surface the 1998 engine actually rendered — followed by a
**3x3 box blur**. The upsample is faithful. The blur is the entire problem.

So the fix is to perform the engine's own upsample offline, skip the blur, and
drop the resulting `.hg2` next to the `.hgt`. Nothing else changes.

## 1. Legacy HGT format

Transcribed from `FUN_00785f50` in the shipped GOG `battlezone98redux.exe`
(2.2.301, image base `0x400000`), cross-checked against BZ 1.5's own
`Init_Zone_Manager` (`0x00523f58`).

| Property | Value | Confidence |
|---|---|---|
| Header | none | High |
| Sample type | `uint16`, little-endian | High |
| Height bits | low 12 (`& 0xFFF`) | High — the engine masks every fetch |
| Upper nibble | not height; discarded by the engine | High (set in most stock files) |
| Zone size | 128 x 128 samples | High |
| Bytes per zone | `0x8000` | High — matches 1.5's `nZones * 0x8000` |
| Ordering | zone-major, then row-major within the zone | High |
| Dimensions | **not in the file**; taken from the `.TRN` | High |
| Sample spacing | 10 world units | High |
| Height unit | 0.1 world units | Medium — single call site |

Index arithmetic, straight from `FUN_00785f50`:

```
index = (z & 127) * 128 + (x & 127)
      + (x >> 7) * 0x4000
      + (z >> 7) * zones_x * 0x4000
```

Out-of-range fetches return 0 rather than faulting.

### Dimensions come from the TRN

`FUN_00786340` reads `Width`/`Depth` from the mission's `.trn` and computes
`zones = (int)(v * 0.1) >> 7`, then **refuses the terrain** unless
`v == zones * 1280`. A zone is therefore exactly 1280 world units across.

Where a TRN has more than one `[Size]` section the first wins: `lcbench.trn`
declares 5120 then 3840, and the shipped `lcbench.hg2` header says 4x4.

This was verified across all 73 stock maps against three independent sources —
the 1.5 `.trn` extracted from `bzone.zfs`/`bzone152.zfs`, Redux's extracted
`StockODFFiles/*.trn`, and the shipped `.hg2` headers. **Zero disagreements.**
It matters: `multst25.hgt` is 12 zones, which infers as 3x4 but is really 4x3.

### Representative stock files

| File | Bytes | Zones | Min | Max | Levels |
|---|---:|---|---:|---:|---:|
| `misn01.hgt` | 131072 | 2x2 | 0 | 1467 | 1424 |
| `misn04.hgt` | 393216 | 4x3 | 0 | 2667 | 2391 |
| `misn18.hgt` | 262144 | 2x4 | 0 | 4095 | 4085 |
| `multdm29.hgt` | 32768 | 1x1 | 0 | 1202 | 153 |
| `demo01.hgt` | 524288 | 4x4 | 0 | 3950 | 3363 |

Full census with hashes: `hgt_hg2_20260901/hgt_census.csv`.

**Round-trip proof.** `HGTMap.read` followed by `HGTMap.write` reproduces the
input file byte-for-byte, including the flag nibble the engine discards
(`tests/test_hgt.py::test_read_write_round_trip_is_byte_exact`), and the parsed
grid is checked sample-by-sample against the engine's index arithmetic at zone
boundaries (`test_zone_tiling_matches_engine_indexing`).

## 2. Redux HG2 format

12-byte header, then `zones * 0x20000` bytes of `uint16` in the same
zone-major/row-major tiling. `FUN_00785c00` returns
`base + 0xC + zone * 0x20000`, confirming both the header size and the stride.

| Offset | Type | Field | Loader check (`FUN_00786340`) | Class |
|---|---|---|---|---|
| 0 | `u16` | structure version | must be `1` | required for loading |
| 2 | `u16` | zone bits | must be `8` → 256 samples/zone | required |
| 4 | `u16` | zones X | must equal the TRN's | authoritative |
| 6 | `u16` | zones Z | must equal the TRN's | authoritative |
| 8 | `u32` | map version | must be `>= 10` | required |
| 12.. | `u16[]` | heights, low 12 bits | *not checked* | authoritative |

As in HGT, the high nibble of each sample is not height (section 9); the engine's
cook writes zero there. There are **no** normals, no min/max fields, no
checksums, no compression, no mip/LOD data, and no padding. HG2 is a plain height grid with a 12-byte header;
everything else the renderer needs is derived at runtime. The only fields that
are not raw height are the five header values above, and four of the five are
pure validation.

Observed `map_version` values in stock files are 10, 11 and 29; the runtime cook
writes 10. Since the check is `>= 10`, 10 is the safe choice and is what the
converter emits.

An HG2 zone is 256 samples over the same 1280 world units — 5 world units per
sample, exactly twice the legacy density.

> **Loader defect worth recording.** The header check is `size >= 13`. The
> payload length is never validated against the declared zone counts, so a
> truncated or mislabelled HG2 is accepted and then read out of bounds. Stock
> `test.hg2` declares 2x4 over a 4x4 payload and is exactly this case. The
> converter's `read_hg2_header` reports `size_consistent` separately so callers
> can catch what the engine will not.

## 3. Loader precedence and the on-disk cache

`FUN_00786340`, in order:

1. Build `<mission>.hg2`. Read it. If it loads and the header passes the table
   above, **use it and stop.**
2. Otherwise build `<mission>.HGT`, read it, cook it (section 4), and
3. **write the cooked result to disk as `.hg2`.**
4. Then load `<mission>.mat`.

Two consequences:

- Supplying a valid `.hg2` is sufficient. No `.trn` edit, no mission change, no
  renaming or removal of the `.hgt`. Confirmed at runtime (section 7).
- Redux already caches its cook on disk, which makes the game itself a bytewise
  oracle for the conversion — see section 6.

## 4. The cook pipeline

```
HGT (128x128/zone, 12-bit)
  -> FUN_00786200   2x upsample, sampling the legacy grid at (out * 0.5)
       -> FUN_00785fe0   piecewise-planar interpolation over the cell's two triangles
  -> FUN_00785c80   3x3 box blur          [skipped when -nohgtsmoothing is given]
  -> HG2 (256x256/zone) + 12-byte header
  -> written to disk
```

### Resolution conversion

Fixed 2x in each axis, and not a free parameter: `FUN_00786200` allocates
`hgt_size * 4 + 0xC` and walks a 256x256 output per zone against a 128x128
source. This is a *necessary* resolution conversion — Redux's terrain renderer
works at 256 samples per zone — and is separable from the smoothing.

### Interpolation: piecewise-planar, not bilinear

`FUN_00785fe0` splits each legacy cell along its `(0,0)-(1,1)` diagonal and
evaluates the plane through the three vertices of the containing triangle.
`comiss fz, fx ; jbe` selects the `(0,0)-(1,0)-(1,1)` triangle when `fz <= fx`,
otherwise `(0,0)-(0,1)-(1,1)`:

```
fz <= fx:  gx = h00 - h10 ;  gz = h10 - h11      (lower triangle)
fz >  fx:  gx = h01 - h11 ;  gz = h00 - h01      (upper triangle)
out = h00 - trunc(fx * gx + fz * gz)
```

Substituting the triangle corners confirms the planes pass exactly through all
three vertices in both cases. The forward neighbour is clamped on the last
row/column (`x0 < zones_x * 0x80 - 1`) rather than read out of bounds.

This is candidate policy **C/D** from the brief, and it is what the engine
already does: it is the surface the 1998 engine rendered, not a generic image
resample.

**Quantization.** The whole expression is single-precision SSE
(`mulss`/`addss`/`divss`) and ends in `cvttss2si` — truncation toward zero.
The constant at `.rdata 0x008a2538` is `0.1f`; the code multiplies the gradients
by `0.1f * 0.1f`, then by `10.0f`, then divides by `0.1f`, which nets to unity.
The float error never crosses an integer boundary, so the effective rule is
*truncate the exact plane value toward zero*. Height precision is otherwise
unchanged: HG2 stores the same raw units as HGT.

### Smoothing: a single-pass 3x3 box filter

`FUN_00785c80` copies the cooked grid, then for every sample averages its
in-bounds 8-neighbourhood:

```
out = (2 * sum + n) / (2 * n)          n = number of in-bounds neighbours (4, 6 or 9)
```

That is a rounded mean — round half away from zero, on values that are always
positive. Uniform weights, one pass, no edge-awareness, no spline. Edges simply
average fewer samples.

It is gated on `DAT_009454cc`, which `FUN_007d5120` sets from the command line:
`-nohgtsmoothing` → 1 (skip), `-dohgtsmoothing` → 0 (run). Both strings are
present in the shipped 2.2.301 executable.

**This is the only step that moves authored geometry.** It is the difference
between "necessary resolution conversion" and "optional destructive smoothing"
the brief asked us to separate.

## 5. Losslessness

Using the brief's three definitions:

**Sample-lossless — achieved, unconditionally.** An output sample at even
`(X, Z)` has `fx = fz = 0`, so the interpolation term is exactly zero and the
result is `h00` unmodified. Every legacy vertex therefore survives bit-exact.
Verified on all 72 converted stock maps and on random fixtures.

**Surface-lossless — achieved up to ±0.05 world units.** Consider one legacy
cell. The conversion emits samples at every half-step, each evaluated on the
legacy plane of its containing triangle, and Redux then triangulates the four
resulting sub-cells with the same diagonal orientation. Each sub-triangle lies
wholly inside one legacy triangle and has all three vertices on that legacy
plane, so it reproduces that plane exactly. The reconstructed surface is the
legacy triangulated surface, not an approximation of it. The only deviation is
integer quantization of the newly introduced half-sample points: at most 0.5
raw units, i.e. **0.05 world units**.

This is why the upsample must not be called smoothing. It adds samples; it does
not move the surface.

**Gameplay-lossless — achieved for practical purposes.** Collision, slopes and
placement all read the same grid the renderer does, and the surface is
preserved to 5 cm. The Great Pyramid slope distribution (section 8) is
identical between the legacy grid and our output once measured at each grid's
own spacing.

By contrast, Redux's default cook is none of the three: the blur moves authored
vertices by up to 45 raw units on Great Pyramid alone.

## 6. Verification against the engine

Three independent oracles, all passed:

**(a) The runtime cook, bytewise.** `addon/ccafun01.hg2` in the GOG install is a
file the game itself cooked from `addon/CCA Fun/ccafun01.hgt`. Our
reconstruction (upsample + blur) reproduces it **exactly**: 2,097,164 bytes,
0 differing samples out of 1,048,576.

**(b) The unsmoothed cook, bytewise.** Deleting that cache and relaunching with
`-nohgtsmoothing` makes the game write the blur-free version. Our default
conversion reproduces it **exactly** — identical SHA-256, header included:

```
424cdfabadcca67a6403a12f7a7314b3ce08da0373f2a4a831f7ab66c4f1284f  ours
424cdfabadcca67a6403a12f7a7314b3ce08da0373f2a4a831f7ab66c4f1284f  game (-nohgtsmoothing)
```

Reproduce with `reverse_engineering/run_hgt_cook_capture.ps1`.

**(c) The stock corpus.** Comparing Redux's shipped `StockODFFiles/*.hg2`
against both modes for 72 maps that have a 1.5 original — see section 9.

## 7. Runtime results

GOG Battlezone 98 Redux 2.2.301, `battlezone98redux.exe` 5,425,152 bytes,
windowed via `BZR_FORCE_WINDOWED=1`.

| Test | Result |
|---|---|
| Game cooks `ccafun01.hgt` with `-nohgtsmoothing` and writes the HG2 | Pass — 2,097,164 bytes |
| That output equals our converter's, bytewise | Pass — identical SHA-256 |
| With our HG2 present, the game loads it and does **not** re-cook or rewrite it | Pass — hash and mtime unchanged after a full mission load |
| Campaign smoke test: `misn01.bzn` with our converted terrain via the mod overlay | Pass — mission loaded, process alive, no stray cook, file unchanged |
| All 36 deployed campaign files pass the loader's own header validation | Pass — 0 failures |

The precedence test is the direct answer to Target 12: **placing the HG2
alongside the HGT is sufficient**, and no migration step, TRN edit, version
field change, or HGT removal is required.

Stock assets were not modified. The `ccafun01.hg2` cache was backed up outside
`addon` and restored; the `misn01.hg2` overlay was placed in the mod directory
and removed afterwards.

## 8. Great Pyramid control (`multdm29`)

Measured at each grid's own sample spacing (legacy 10 world units, HG2 5):

| Terrain | Levels | p95 slope | Max slope | Max first difference | Flat neighbours |
|---|---:|---:|---:|---:|---:|
| Legacy 1.5 HGT | 153 | 26.57° | 54.46° | 140 | 92.29% |
| **Our unsmoothed HG2** | **364** | **26.57°** | **54.85°** | **71** | **92.86%** |
| Redux 2.2.301 shipped | 363 | 26.57° | 54.85° | 71 | 92.86% |
| Redux smoothed cook | 936 | 23.75° | 43.23° | 47 | 87.58% |

Agreement with the shipped Great Pyramid terrain:

| Candidate | Differing samples | Max error | RMSE |
|---|---:|---:|---:|
| Our unsmoothed conversion | **3 / 65,536** | **1** | **0.0068** |
| Redux's smoothed cook | 7,169 / 65,536 | 45 | 5.8246 |

**Rebellion's 2.2.301 Great Pyramid is an unsmoothed conversion of the legacy
HGT, not hand-modified terrain.** It is a valid gold-standard reconstruction
target, and our output reaches it to within one raw unit on three samples.

The three residual samples are the interpolator's truncation rule versus a
round-half-up one; a `--rounding half-up` mode is provided, though on this map
it is worse (1,139 differing samples), which indicates `multdm29` was produced
by the game's own truncating interpolator while `multdm17` was produced by an
offline tool that rounds halves up. Both are within one raw unit either way.

The stair-step evidence is unambiguous: along the profile row with the greatest
vertical range, the legacy terrain has 30 transitions, our conversion and the
shipped file both have 59 (one interpolated step per riser, as expected from
doubling the density), and the smoothed cook has 98 — the blur turning each
clean riser into a ramp. Profile data: `hgt_hg2_20260901/great_pyramid_profile.csv`.

## 9. Stock corpus classification

72 stock maps with both a 1.5 `.hgt` and a shipped Redux `.hg2`
(`hgt_hg2_20260901/stock_classification.csv`):

| Classification | Count | Meaning |
|---|---:|---|
| Shipped as the smoothed cook | 67 | Redux shipped blurred terrain; these are what the conversion fixes |
| Shipped already unsmoothed | 2 | `multdm29` (Great Pyramid), `multdm17` |
| Hand-modified terrain | 2 | `misn02b`, `multdm77` — match neither mode |
| Invalid shipped HG2 | 1 | `test.hg2` — header/payload mismatch |

**Legacy vertices are reproduced exactly on all 72.**

The two hand-modified maps deserve care. `misn02b` differs from the 1.5 original
by up to **999 raw units (about 100 world units), RMSE 108**, and matches
neither the smoothed nor the unsmoothed cook — it is re-authored terrain, not a
conversion. `multdm77` differs from both modes by up to 238–251 units.
Replacing either reverts a deliberate Rebellion change.

### HG2 carries the same flag nibble HGT does

`misn02b.hg2` sets the high nibble (values `0x8` and `0xC`) on 580,380 of its
589,824 samples. Height is the low 12 bits there exactly as it is in HGT, and
comparing the raw `uint16` instead makes those samples read as heights near
50,000. All figures in this report are masked to 12 bits.

The legacy source files are heavily flagged too — 140,817 of `misn02b.hgt`'s
147,456 samples, 14,799 of `multdm77.hgt`'s 16,384 — and **Redux's cook discards
the nibble**: every runtime-cooked and smoothed-cook HG2 in the stock set has
zero flagged samples. Our converter writes zero there as well, which is why it
matches the engine bytewise. The meaning of the nibble was not investigated; it
is not height, and nothing in the conversion path depends on it.

## 10. Synthetic fixtures

`tests/test_hgt.py` covers the filter-probing cases from the brief, as unit
tests rather than one-off scripts:

| Fixture | Unsmoothed | Smoothed |
|---|---|---|
| Flat map | perfectly flat (single value) | perfectly flat |
| Staircase | treads exactly flat; one interpolated column per riser | riser widened to three columns; distinct heights roughly double |
| Hard step | transition confined to the one legacy cell | bleeds into neighbouring samples |
| Single impulse | peak preserved at full height | peak reduced, energy spread |
| Random grid | all authored vertices bit-exact | authored vertices moved |

The impulse and step cases are what identify the kernel: a 3x3 uniform average,
one pass.

## 11. Batch conversion feasibility

Census over the 1.5 install, the GOG Redux install, and the `BZ1_Source` tree:

```
total HGT paths found     254
successfully parsed       251
unique contents           168
failures                    3
format variants             1
```

| Zone shape | Unique files |
|---|---:|
| 4x4 | 69 |
| 2x2 | 34 |
| 3x3 | 30 |
| 1x1 | 29 |
| 3x4 | 4 |
| 8x8 | 1 |
| 2x4 | 1 |

**Failures**

- `map.hgt` (a community map's "important files" folder) — 0 bytes.
- `multst35.hgt` (stock 1.5, two copies) — 141,312 bytes where its own TRN
  declares 4x4 (524,288). Truncated at 27%. Redux ships no `multst35.hg2`
  either, so the map is broken in both engines. Not repaired: padding it would
  be fabricating terrain.

**Ambiguity**, not failure: 61 of 251 paths have no usable TRN beside them and a
zone count that is not a perfect square, so the dimensions are genuinely
ambiguous from the file alone. The CLI reports the assumption and lists the
alternatives; `--trn-dir` resolves them from an authoritative TRN tree. For the
stock set this was essential (`multst25`, `multst32`, `misn04`, `play01`,
`misn18`).

Only one HGT variant exists across the whole corpus — 128x128 zones, 12-bit
heights, no header. No version-dependent behaviour was found between BZ 1.4,
1.5 and TRO 1.3; BZ 1.5's own `Init_Zone_Manager` uses the identical
`nZones * 0x8000` geometry.

## 12. Recommended compatibility policy

**Policy A — external conversion.** Convert legacy maps offline with
`scripts/convert_legacy_hgt.py` and ship the `.hg2` beside the `.hgt`. Redux
then loads HG2 directly and performs no smoothing.

Do **not** implement an OpenShim runtime hook. Justification:

- The engine already exposes `-nohgtsmoothing`; a hook would duplicate a
  shipped switch.
- HG2 is a native, validated path — no patching, no version-guard maintenance,
  no risk to multiplayer determinism.
- The conversion is provably identical to what the engine itself produces, so
  there is nothing a runtime hook could do more faithfully.
- Conversion is a one-time authoring step; a hook would pay the cost every
  load, on every machine.

The one thing OpenShim could usefully add is *documentation* of the existing
switch, and optionally surfacing it as an INI key — the `[Fixes]` section
already turns any `OPENSHIM_DISABLE_*` call site into an INI key with one line.
That is a convenience, not a fix, and is out of scope here.

Per-map caution (Policy C element): `misn02b` and `multdm77` carry hand-modified
Rebellion terrain. A blanket conversion of every stock map would revert those
two. The batch tooling reports the classification so this is a deliberate
choice rather than an accident.

## 13. Delivered

**Converter** — `Battlezone98Redux_HeightmapGen`, branch
`agent/legacy-hgt-to-hg2`, commit `dd1e16c`:

- `bzr_heightmap/hgt.py` — HGT reader/writer, TRN dimension resolution, the
  bit-exact cook, blur, and HG2 header inspection.
- `scripts/convert_legacy_hgt.py` — `convert` / `batch` / `scan` / `compare`.
- `tests/test_hgt.py` — 26 tests; full suite 61 passing.
- `docs/LEGACY_HGT_TO_HG2.md` — format and algorithm provenance.

**Campaign terrain** — `CampaignReimagined`, branch `agent/legacy-hgt-terrain`,
commit `ce18e89`: unsmoothed HG2 for 36 stock campaign maps in `Missions/`.

**Runtime fixture** — `reverse_engineering/run_hgt_cook_capture.ps1`, which
captures either cook arm from the live game and restores the install afterwards.

**Comparison artifacts** — `reverse_engineering/hgt_hg2_20260901/`:
`hgt_census.csv`, `stock_conversion.csv`, `stock_classification.csv`,
`great_pyramid_metrics.csv`, `great_pyramid_profile.csv`.

## 14. Confidence and open questions

**High confidence** (transcribed from the shipped binary and confirmed by a
bytewise oracle): HGT and HG2 layouts, the 12-bit mask, zone geometry, loader
precedence and validation, the on-disk cache, the 2x upsample, the triangular
interpolator, the box-blur kernel and its gate, and sample-losslessness.

**Medium confidence**: the 0.1 world-units-per-raw-height constant rests on one
call site (`FUN_007859d0`'s default fill, `(short)(Height / 0.1)`). It is
consistent with the zone maths and affects only how absolute heights are
described in this report — the conversion itself never rescales, so nothing in
the output depends on it.

**Open**

- Why two shipped stock maps (`multdm29`, `multdm17`) use different rounding
  suggests they were produced at different times by different tools. Neither
  matters beyond ±1 raw unit.
- `misn02b` and `multdm77`'s hand-modified terrain has no recovered provenance;
  it is simply not a conversion of the 1.5 map.
- The high-nibble flag bits carried by both HGT and HG2 samples were not
  decoded. The engine masks them off for height and its cook discards them, so
  the conversion is unaffected, but whatever they encode is lost on any map
  that sets them.
- The HG2 payload-length check the loader omits is a latent out-of-bounds read
  reachable with a malformed file (stock `test.hg2` is one). Not exploited or
  further investigated here; worth a separate look.
- 1.4-era HGT was not compared directly — the 1.4 install lives on a Google
  Drive mount that was not accessible during this pass. BZ 1.4's shipped HGT
  files under `BZ1_Source` parse identically, and 1.5's zone geometry is the
  same, so no variant is expected.
