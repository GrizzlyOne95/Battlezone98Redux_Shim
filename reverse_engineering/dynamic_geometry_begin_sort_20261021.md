# DynamicGeometry begin/sort CPU work (2026-10-21)

Effect sprites (smoke, flames, tracers, explosions, beams) are drawn through
Redux's `DynamicGeometry` (DG). Each effect calls `begin()` and then emits
vertices, and `prepareForSubmit` sorts the resulting pieces and merges runs
of compatible ones into the batches Ogre draws. This note covers what that
costs per frame and the three changes on branch `agent/dg-begin-sort`. It
contains mechanics and measurements only.

All addresses are GOG Redux 2.2.301 and live as named, signature-checked rows
in `scripts/patches.json`:

| Row | Address | Role |
|---|---|---|
| `DynamicGeometryBeginByMaterial` | 0x00679D70 | `begin(const MaterialPtr&, op, dist)`, thiscall, `ret 0xC` |
| `DynamicGeometryBeginByName` | 0x00679BC0 | `begin(const std::string&, op, dist)`, thiscall, `ret 0xC` |
| `DynamicGeometrySortLess` | 0x00678950 | main piece comparator (cdecl) |
| `DynamicGeometryOpaqueSortLess` | 0x00678B40 | opaque-run re-sort comparator (cdecl) |
| `DynamicGeometrySetSquaredViewDepth` | existing row | depth key setter (already hooked for alpha batching) |

## Step 0: pieces per frame

`OPENSHIM_DG_BEGIN_STATS=1` counts begins and new pieces per `prepareForSubmit`
call. In the measured combat scene there is one prepare per frame.

| Scenario (DX11, avtank, 50 m, facing) | begin by material / frame | begin by name / frame | new pieces / frame |
|---|---|---|---|
| combat 80, stock | 1230-1510 | ~10 | 880-1150 |
| combat 40, features on | 385-1190 | 5-10 | 176-653 (+44-153 absorbed) |
| combat 80, features on | 1770-1900 | ~10 | 1105-1223 (+225-282 absorbed) |

The estimate of about 1000 pieces per frame holds. Roughly 70-75% of begins
open a new piece in stock. After the sort and merge, the profiler sees only
about 105-145 batches per frame, so most pieces exist only to be merged again.

## Why stock opens so many pieces

Stock `begin()` reuses the current piece only when the new piece matches on:

- the exact squared view depth (`batch+0xB0 == d*d`);
- the operation type;
- the material;
- the identity-projection and identity-view bytes, against `dg+0x150/0x151`;
- the queue group, which comes from the DG's virtual at vtable `+0xB0`.

Every sprite sits at a slightly different distance, so the exact depth test
almost never passes.

The distance is clamped first with `(0 < d || 0 == d) ? d : 0`, so NaN and
negative distances become 0.

The sort reads only the depth *key* (`batch+0x34`), not the squared depth. The
depth-key setter writes `+0xB0` and `+0x34` and reads only the group (`+0xAC`).
OpenShim's existing alpha-batching hook on that setter also reads the blended
flag (`+0x31`) and coarsens blended keys to a stride of 8 world units. As a
result, many neighbouring sprites share a key even though their squared depths
differ.

## Step 1: piece reuse (`[Fixes] DynamicGeometryPieceReuse`, default 1)

The hook on `begin(MaterialPtr)` tries to absorb the begin into the current
piece when stock would not. It requires all of the following:

- a non-negative distance; anything else falls through to stock;
- every field stock compares except the exact depth: operation, material
  (non-null), the two identity bytes and the queue group;
- the piece is mergeable, which excludes occlusion-query pieces;
- the piece is non-empty (`dg+0x1D4` vertex cursor != `piece+0x54`);
- the piece still writes to the current staging buffer
  (`dg+0x190 == piece+0x78`);
- the new piece's depth key equals the current piece's key. The key is
  computed by calling the live key setter, through whatever detour is
  installed, on a scratch 0xB4-byte piece carrying the same blended flag and
  group, so it always matches what stock would have stored.

If the current piece already has the exact squared depth, stock reuses it
anyway and the hook just forwards the call.

### Why the result is pixel-identical

Each absorbed piece would, in stock, have become a piece P' right after the
current piece P, with:

- an equal sort key;
- an equal blended flag, material, operation, identity bytes and group;
- a larger creation index (`+0x2C`, the list size at begin).

The sort orders by group, key (descending), blended, material, operation,
identity projection, identity view and finally creation index. P and P' tie
on every field before the creation index. Any third piece that sorts between
them would have to tie as well and was created between them, but nothing was
created between them because P was the current piece. So P' lands directly
after P.

The merge step then joins P' into P's batch, because they share the
mergeable flag and the same staging buffer, and P is non-empty, so the merge
does not skip it. The merged batch keeps P's `+0xB0`, which is the head's
value. Absorbing therefore produces the same vertex and index ranges, the
same material, the same position in the queue and the same `+0xB0` that stock
produces after its merge.

The opaque-run re-sort ignores the key but uses the same field chain, and the
same argument holds.

### Edge cases

- **The 0x10000 shared-buffer split.** When the staging buffer fills, stock
  starts a new staging index. The staging-index condition blocks reuse across
  that boundary, so a piece never spans two buffers.
- **Staging-overflow re-begin.** Stock re-begins internally when a piece
  overflows its buffer. That re-begin reuses the head's depth, which matches
  what an absorbed piece would have produced.
- **Empty current piece.** Stock's merge skips empty pieces, so the next
  piece would become the merged head. Reuse is refused for empty pieces.

`tests/dynamic_geometry_batching_tests.cpp` models stock and reuse through the
sort, the opaque re-sort and the merge over 400 random piece streams. The
resulting batches are identical: 47,396 stock pieces become 40,258 with reuse,
with 0 mismatches.

## Step 2: material handle cache (`[Experimental] DynamicGeometryMaterialCache`, default 0)

`begin(std::string)` resolves the name through `MaterialManager::getByName`
(via 0x006799C0 and 0x0067A4D0) and falls back to the DG default material at
`dg+0x140`.

The cache keeps one entry: the owner, the name, and the material that the
current piece holds. The entry is trusted only while the current piece still
holds that exact material, which also keeps the pointer alive. It is flushed
every prepare and whenever the owner changes. On a hit, the hook calls the
by-material path with the current piece's `MaterialPtr`, or absorbs the begin
directly.

Measured result: there are only about 10 by-name begins per frame and the
cache hit **0** times. Consecutive by-name begins never ask for the material
the current piece holds. The cache is correct but buys nothing, so it ships as
an opt-in experimental key (env `OPENSHIM_DG_MATERIAL_CACHE`).

## Step 3: fast comparator (`[Fixes] DynamicGeometryFastSort`, default 1)

The stock comparators read the material through a call to 0x00416400 and
read the identity bytes through OgreMain's exported
`Renderable::getUseIdentityProjection` and `getUseIdentityView`, called
through the IAT on every compare. The fast comparator is an exact restatement
of the same order. It reads the fields directly, with these semantics:

- null pointers order first;
- the key compare has `comiss` semantics, so NaN compares as neither smaller
  nor greater;
- the material compares unsigned and the operation signed.

At install time it decodes the identity byte offsets from the OgreMain
getters, following E9 and FF25 thunks from the exe's IAT slot and expecting
`8A 41 xx C3`. Measured offsets: projection `+0x11`, view `+0x12`. If either
offset does not decode, every batching hook stays uninstalled (fail closed).

With `OPENSHIM_DG_SORT_VERIFY=1`, each compare also calls the stock comparator
and counts disagreements. Across the stats runs it checked about 61 million
compares, with **0 mismatches** and 0 faults.

## Step 4: additive flattening

Skipped. It would change the blend order of overlapping additive sprites,
which cannot be pixel-identical, and it needs its own parity study.

## Parity

- **In-game sort verify:** 0 mismatches in about 61 million compares; 0 SEH
  faults in any arm.
- **Model test:** identical batch output over 400 random streams.
- **Screenshots** (off, on, off, on at 10, 14, 18, 22 and 26 s; combat 80).
  The live sim is not frame-deterministic, so these can only bound the
  difference.
  - At 10 s and 14 s the scenes still line up. Off-vs-on mean absolute
    difference was 0.00 and 0.27-0.40, against an off-vs-off noise floor of
    0.00 and 0.62.
  - From 18 s on, the runs diverge in content (camera, explosions) in both
    the off-vs-off and off-vs-on pairs.
  - No off-vs-on pair exceeded the off-vs-off envelope.

## Benchmarks

`run_live_combat_benchmark.ps1`, DX11, avtank, combat 40 and 80, 50 m, facing,
windowed. Off and on arms are interleaved with alternating order. In the off
arm all three features are disabled, so no batching hook installs: stock.

- `dg cpu` is the profiler's measured `prepareForSubmit` time per frame.
- `draws` is draw plus indexed draw calls per frame.

Engagement in the on arm, from the stats runs: about 44-153 absorbed begins
per frame at combat 40 and 225-282 at combat 80. Fast sort engaged on every
compare.

### Round 1 (3 repeats, 8 s windows, cache on)

| count | arm | frame mean ms | p99 ms | dg cpu ms | draws |
|---|---|---|---|---|---|
| 40 | off | 10.40 | 16.2 | 0.283 | 461 |
| 40 | on | 34.47* | 39.8* | 0.202 | 430 |
| 80 | off | 14.17 | 20.4 | 0.531 | 749 |
| 80 | on | 13.50 | 24.4 | 0.326 | 660 |

\* One 40-unit on run hit a 78 ms stall. The first repeat of each arm ran
cold at about 19 ms. Frame time in this round is noise-dominated. The
`prepareForSubmit` CPU drop is consistent in every pair.

### Round 2 (5 repeats, 20 s windows, warmup discarded, shipping config)

| count | arm | frame median ms | frame mean ms | p99 median ms | dg cpu ms (mean) | dg cpu per 1k DG verts | draws |
|---|---|---|---|---|---|---|---|
| 40 | off | 6.46 | 11.17 | 7.8 | 0.247 | 0.0167 | 453 |
| 40 | on | 18.63 | 16.25 | 33.7 | 0.182 | 0.0126 | 412 |
| 80 | off | 20.22 | 16.14 | 33.7 | 0.398 | 0.0237 | 634 |
| 80 | on | 20.11 | 15.99 | 33.9 | 0.272 | 0.0169 | 581 |

Every run's frame time falls into one of two modes, about 6-10 ms or about
18-21 ms, in both arms. Within a mode the arms match: for example, at 80 the
fast-mode runs are off 10.10 and 9.29 against on 9.03 and 10.42. The mode is
set by the host (window focus or contention from other sessions), not by the
arm, so five repeats cannot resolve a sub-millisecond change in frame time,
and none is claimed. What is resolved is `prepareForSubmit` CPU:

- 26% lower at combat 40;
- 32% lower at combat 80;
- 25-29% lower when normalised per thousand DG vertices.

The time saved inside `begin()` by skipping piece construction, and the cost
of the hook's key computation, both fall outside that measurement.

Draws and DG batches per frame read lower in the on arm. So do DG vertices
and animation calls, which DG does not affect, so this is scene variance (how
much of the fight is in view during the window), not a batching difference.
Vertices per batch overlap between the arms: 115-154 off, 118-167 on.

## Files

- `include/dynamic_geometry_batching.h`: offsets, comparator, reuse
  predicate and name cache, as pure byte-level helpers shared with the tests.
- `src/patches/dynamic_geometry_hooks.cpp`: the detours, install and fail
  closed, counters, and the `[DgBatching]` log line.
- `src/patches/openshim_env_mapping.cpp`, `openshim.ini`,
  `openshim.ini.example`, `scripts/run_ini_tests.ps1` and
  `src/patches/bzr_options_ui.cpp`: the settings.
- `tests/dynamic_geometry_batching_tests.cpp`: the unit and model tests.

Diagnostics:

- `OPENSHIM_DG_BEGIN_STATS=1` logs per-prepare counts every 10 s.
- `OPENSHIM_DG_SORT_VERIFY=1` cross-checks every compare against stock.
- The hooks stand down on the Steam executable.
