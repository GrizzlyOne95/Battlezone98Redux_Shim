# Live terrain paint (prototype)

Multi-map paint packs (CR's `cr_terrain_hd.json`) only paint missions with a
baked entry; any other map logs `paint pack has no map entry for this mission`
and keeps the stock atlas. Live paint generates the control images at load
from the map's own heights and MAT words, with the same recipe the offline
builder uses. It is a **fallback only**: a baked entry always wins.

Off by default. Two things turn it on:

1. The material's `paint` block carries a `live` autopaint recipe
   (`scripts/terrain-packs/<world>-autopaint.json`). The recipe must have one
   layer per paint layer, and the pack must use the multi-map form.
   `scripts/Add-LivePaintRecipe.py <manifest> <output>` adds them to a copy of a
   manifest, matching worlds by `diffuseResource`.
2. The environment variable `OPENSHIM_TERRAIN_PAINT_LIVE=1`.

`OPENSHIM_TERRAIN_PAINT_LIVE_DUMP=<dir>` also writes `live_<fingerprint>.bin`
(the generator's input) and `.rgba` (its output) for the offline check below.

## Hook

`InstallNativeTerrainHd()` in `src/patches/terrain_native_hd.inl`, at the
point where `TerrainPaint::SelectMap` finds no entry and `MapMayGrow` says the
map is complete (so the same retry/deferral rules still apply):

1. `ReadLivePaintInput` reads the file rectangle back from the engine:
   heights from `g_heightAt` (masked to 13 bits like the HG2 reader) and MAT
   words from `g_terrainWordAt` at every fourth sample. The engine holds one zone
   more per axis than the file, and file sample (0,0) sits at the centre of the
   lowest zone, `minZone * 256 + origin`. A rectangle that is not full, or
   smaller than 2x2 runtime zones, declines.
2. Decline if more than 1% of the MAT cells use a tile type the recipe does not
   map (the map is probably from another world that shares the atlas).
3. The binding takes the captured fingerprint and bounds, so the existing
   `map accepted` check and log run unchanged. The first baked entry's control
   PNGs stand in for slices 4 and 13 while the texture array is built.
4. After `BuildTerrainHdTextureArray`, `TerrainLivePaint::Generate` runs at the
   array's width and `UploadLivePaint` overwrites slices 4 (and 13 for eight
   layers) at every mip with `UpdateSubresource`. It requires an uncompressed
   8-bit square array; B8G8R8A8 is swizzled, sRGB gets raw bytes like the PNG path.

Any failure throws into the installer's existing catch, which restores the
stock material and logs `native tiles declined: ...`.

## Recipe and parity

`include/terrain_live_paint.h` is a C++ port of `scripts/Build-TerrainAutoPaint.py`
`rasterize()` plus the control step (bilinear upscale and joint normalise to
255): type weights and transitions, outside weights, blur, shape (ridge/hollow),
erosion (talus, channel, deposit, scour), slope and layer edges. The seed is the
builder's: the fingerprint's first 32 bits xor the first variation rule's seed.

`tests/terrain_live_paint_parity.py` compares the two on the same data, with the
noise terms stripped (variation and ragged edges):

| Map | Recipe | Size | max diff | mean diff |
| --- | --- | --- | --- | --- |
| synthetic 1x1 | 8 layers, every rule | 256 / 512 | 3 | 0.016 |
| stock multdm05 | Titan (4 layers) | 1024 | 0 | 0 |
| stock mult01 | Mars (8 layers, edge) | 1024 | 2 | 0.0001 |

The noise terms use a hash where Python uses numpy's PCG64, so they match only
statistically: per-layer shares with variation on agree within 0.005 on the
stock maps (within 0.015 on the 1x1 synthetic map). That is
why live output is not a replacement for a baked entry, only a fallback.

## Load-time cost

Generation runs once per mission, on the loading thread, after the texture
array is built. Offline (CLI, including process start), 4x4 file zones at
1024 px take about 1.2 s. In game, 4x4 file zones at the 2048 px array width
took 1367 ms and 1425 ms (two runs), logged as the `ms=` field of
`[TERRAIN-PAINT] live paint generated`.

## Live result

Stock Titan `multdm05` (no baked entry), CR's pack with the Titan recipe added
by `Add-LivePaintRecipe.py`, DX11, windowed:

```
[TERRAIN-PAINT] live paint selected fingerprint=2ce5b40ef5047c67 fileZones=4x4 undefined=0.0000
[TERRAIN-PAINT] map accepted fingerprint=2ce5b40ef5047c67 zones=25 bounds=(-3190.0,-3210.0,3210.0,3190.0)
[TERRAIN-PAINT] live paint generated fileZones=4x4 size=2048 images=1 ms=1425
```

`terrain_live_paint_parity.py --dump` on that run's dump: 0 of 1048576 height
samples and 0 of 65536 MAT words differ from `multdm05.hg2`/`.mat`, and the CLI
reproduces the in-game control image byte for byte, so the engine read and its
orientation are correct. A frame capture at 4 s shows the painted terrain with
no seams or stock-atlas tiles; that is a visual spot check, not a comparison
against a baked pack.

CR's Mars pack is 4-layer while `mars-autopaint.json` has 8 layers, so the
script leaves Mars without a live recipe; Mars needs a 4-layer recipe first.

## Known gaps

- No TRN `typeNames` guard at runtime (the offline builder checks the TRN's
  tile names against the recipe); the 1% unmapped-cell check stands in for it.
- Noise is hash-based, not PCG64 (above).
- Single-map packs (`paint.maps` empty) are not supported: they already name
  one map.
- Generation is single-threaded and blocks loading for its duration.
- Memory caps for the 32-bit process: maps over 64 file zones and arrays wider
  than 2048 px decline (the slope fields and the upscale grow with both).
