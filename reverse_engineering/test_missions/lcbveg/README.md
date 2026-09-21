# lcbveg — Achilles vegetation and water bench

lcbench's shape asking a different question. lcbench holds a scene fixed and
measures frame cost; this holds a scene fixed and asks what ground content
**looks like**. No combat, no spawning, nothing moving.

On Achilles because it is the only vegetated world Redux ships — its terrain
types are authored `grass`, `trees`, `rocky rock`, `river`, `waterfall` and
`base`. Grass on Moon can be proven present but never proven to look right,
which is why misn02b was the wrong place to judge it.

## Install and run

```
powershell -ExecutionPolicy Bypass -File scripts\Install-VegetationBench.ps1
battlezone98redux.exe lcbveg
```

Tune by editing `addon\lcbveg\lcbvcfg.odf` and relaunching. No rebuild, no
redeploy — the same idiom as `lcbcfg.odf`.

**Campaign Reimagined must be active.** The grass mesh and material are CR's,
and CR's `TerrainClutter` is what the bench exists to exercise. Without it the
mission still runs, on a built-in fallback placer, and says so in the log.

## Scenarios

| `scenario` | What you get |
| --- | --- |
| `ladder` (default) | Five patches ahead of the spawn, density stepping **geometrically** from 0.05 to 0.80. One screenshot shows the whole usable range instead of one guess from it. |
| `single` | One patch centred on the player, at `density`. |
| `off` | Bare Achilles. The control. |

Density is instances per square unit; the log reports the **spacing** each patch
actually achieved, which is the number that predicts whether it reads as ground
cover. Roughly: 7 units apart is bare ground, 1.7 is a grass field.

## Terrain-type filtering

`restrictToTerrainTypes = 1` places blades only where the material grid says the
ground is one of `terrainTypes` (default `"0"`, grass). So grass stays out of
the river and off the rock.

This is the first thing to supply CR's `terrainTypeAt` callback. `TerrainClutter`
has accepted `terrainTypes` plus a lookup since it was written, and nothing had
ever passed one, so that path had never run.

The lookup reads `lcbveg.mat` once through `bzfile` in binary mode and indexes
it directly. The indexing is verified against WorldBuilder's own decoder — zero
mismatches over a sampled grid — because the layout is easy to get wrong (see
below).

## The map is generated, not committed

`Make-VegBenchTerrain.py` writes `lcbveg.hg2`, `lcbveg.mat` and `lcbveg.lgt`.
They are gitignored: reproducible from the script, and 3.3 MB of binary that
does not need to be in history.

```
python Make-VegBenchTerrain.py [--worldbuilder <repo>] [--seed 7]
```

It needs [Battlezone98Redux_WorldBuilder][wb] for the `.mat` and `.hg2` codecs.
Those live there deliberately and this script does not carry a second copy.

[wb]: ../../../../Battlezone98Redux_WorldBuilder

### Why this map does not reuse lcbench's heightfield

Every other map in this family does, on purpose: fixed geometry is what lets a
difference between two captures be attributed to the renderer. That is right for
a renderer benchmark and wrong here.

lcbench's heightfield is a plain at raw height 0 with a berm through it — 75% of
its material cells report painter elevation 0, and only slope discriminates
anything at all. **A river cannot be painted into a surface with no low ground.**
So this map is synthesised: a meandering channel through rolling grassland,
wooded mid-slopes and a rocky rim.

Use `lcbworld/lcbachil` for renderer captures, where shared geometry matters.
Use this for content, where somewhere for water to be matters more.

Current composition: 69.1% grass, 18.1% rocky, 7.9% river, 4.9% trees.

## Two things worth knowing about the formats

**The `.mat` layout is easy to get wrong in a way that looks almost right.** It
is 4×4 zones of 64×64 cells, two bytes per cell, stored *zone by zone* — not a
flat 256×256 row-major grid. Each entry is a little-endian uint16 whose second
byte is `(Base << 4) | Next`; **Base is the high nibble**. An earlier draft of
this fixture had both of those backwards and would have produced a plausible,
silently scrambled file.

**No shipped Achilles map paints river or waterfall at all.** `misn17`, `misn18`
and `multdm14` use only grass, trees, rocky and base. Those two tilesets are
declared by every Achilles `.trn` and have never been rendered by anything, so
this map is the first thing to put them on screen. If they turn out to be
broken, that is a discovery rather than a regression.

## Undeclared transitions

An undeclared `CapTo*`/`DiagonalTo*` key does not fail — it silently draws the
default tile, which reads as a rendering bug rather than a missing declaration.
The generator counts them.

It does not fail the build on them, because that bar is stricter than the game's
own content: every Achilles `.trn` declares only (0,1), (0,5) and (1,2), yet
stock `misn17.mat` emits 1705 undeclared (0,2) grass↔rocky transitions, 2.6% of
its cells. This map sits at the same 2.6%.

## Known gaps

- **The lightmap is uniform, not baked.** `lcbveg.lgt` is filled with `0x92`,
  the unshadowed value across 71% of `lcbench.lgt`. There is no baker here, and
  the alternative — reusing lcbench's — would paint a flat plain's shadows onto
  a valley, where the mismatch would look like a lighting bug.
- **No pond object.** The `pond` class label is ported and live (OpenShim logs
  `[POND] installed BzE-compatible classLabel=pond support`), but a pond needs a
  water mesh, and the only one on this machine belongs to a third-party BzE
  addon. The river here is painted terrain, not water geometry. Adding a real
  pond means authoring a water plane mesh first.
- **The spawn point comes from `lcbench.bzn`** and is wherever that puts it. The
  mission logs which material it landed on; if that is ever `river`, move the
  patches rather than the spawn.
