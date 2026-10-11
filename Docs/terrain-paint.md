# Four-material terrain painting prototype

This experimental DX11 path blends four independent, repeating diffuse
materials across native terrain using a saved RGBA weight map. Painting is
continuous across stock tile boundaries and uses actual native vertex X/Z
positions plus cluster translation. Camera position, native tile orientation
and atlas rectangles do not determine the new diffuse coordinates.

Enable the existing **HD Terrain Tiles** option, select the generated manifest
through `[Terrain] TerrainHdManifest`, and restart. **Terrain Micro Detail**
works alongside it. The original tile-array mode remains supported.
There are no new INI keys. Stock heights, collision, indices, AI and gameplay
terrain files are unchanged. Native packed UVs are still independently audited
before installation and retained for auxiliary maps and shadow-only passes.

## Build and paint

1. Capture the target mission using `OPENSHIM_TERRAIN_HD_EXPORT` as described
   in [terrain-hd-tiles.md](terrain-hd-tiles.md). The updated exporter includes
   `paintMap`: native world bounds in metres, row order and a terrain fingerprint.
   Older captures without this field cannot author a paint pack.
2. Build a pack using Python and Pillow:

```powershell
python scripts/Build-TerrainPaintPack.py `
  --capture build/terrain-paint/misn04-capture.json `
  --recipe scripts/terrain-packs/mars-paint.json `
  --source-root '<your ground texture directory>' `
  --output build/terrain-paint/mars --size 2048 --weight-size 1024
```

3. Open the generated `openshim_mars_paint_editor.html` in a current browser.
   It is self-contained and works offline. Pick sand, soil, gravel or rock;
   set brush radius in metres and strength; drag to paint. The coloured view
   is a top-down weight preview with material thumbnail swatches, not a
   rendered view of the game or a heightmap. Minimum Z is the top row, and
   maximum X is the right edge. Undo/redo retains twelve strokes.
4. **Save weights PNG**, then rebuild with `--weights '<saved PNG>' --force`
   added to the command. This uses the edited weights instead of the example
   recipe strokes. The exporter normalizes all pixels to a total weight of 255.
5. Copy only the four `*_layer0..3.png` files and `*_control.png` to a registered
   Ogre resource directory, and the main manifest beside the game executable.
   Set `TerrainHdManifest = openshim_mars_paint.json`, enable HD Terrain Tiles,
   and restart the target mission. The weight source, project JSON and editor
   are authoring files and need not be installed as game resources.

The provided Mars recipe references the user's local 4K albedo ZIP members;
it contains no artwork. It starts from rocky soil and adds several broad soft
patches to demonstrate blending. It does **not** convert the mission's existing
tile layout to weights. Preserve original gameplay MAT/HG2/TRN files. Artwork,
game captures and generated packages remain local and are never committed.

The adjacent project JSON records material sources/hashes, repeats, dimensions
and map identity. Repeats are independently specified for the four layers in
the recipe (`repeatMeters`). The material textures and editable paint map
have independent authoring resolutions. The browser's PNG codec stores raw
RGBA bytes: PNG alpha represents the fourth layer's weight, so ordinary canvas
export or image compositing would lose the first three channels wherever that
weight is zero. Save/load preserves those transparent RGB pixels.

## Runtime format and guards

Paint extends `bzr-openshim-terrain-hd-v1` material bindings with:

```json
"paint": {
  "schema": "bzr-openshim-terrain-paint-v1",
  "terrainFingerprint": "0123456789abcdef",
  "boundsMeters": [-3200, -2560, 3200, 2560],
  "rowZero": "minZ",
  "repeatMeters": [24, 16, 12, 24]
}
```

The illustration's fingerprint/bounds are placeholders; use the live capture.
Exactly five explicit slices are required: four material images then one RGBA
control image. The diffuse-resource identity guard is mandatory. Canonical
zone coordinates and every native height sample contribute to a 64-bit FNV
map fingerprint. This is an accidental
misapplication guard, not a security hash. Native sample-storage origins are
excluded because the engine can relocate them between launches. World bounds
must also match exactly.
A mismatched mission, incompatible layout/resource or unknown shader declines
before binding the replacement. Editing terrain heights requires a fresh
capture and regenerated manifest. Runtime dirty mesh rebuilds refresh position
streams; painting requires rebuilding the pack and restarting the game.

## Current limits

This is diffuse-only painting with the stock lighting pipeline. Normal,
detail and specular maps retain their stock atlas coordinates, and materials
are blended before the stock colour-space processing. Diffuse repetition is
explicit, with
UV gradients taken before wrapping so repeat boundaries do not select
incorrect mip levels. Material height assets,
height-based blending and physically based material maps are future work.
The bounded procedural micro relief remains separate from the paint layers.

The initial implementation packs control weights into slice 4 of the same
texture array to reuse the validated native binding/upload/lifetime path.
All five uploaded slices therefore share resolution and mip count. A
1024-pixel source weight map is upscaled for a 2048-pixel material pack; this
does not add painting detail. Control sampling uses level zero and a half-texel
edge clamp to prevent wraparound with the shared repeating sampler. Separate
control textures, mip-aware control sampling and streamed map pages remain
future improvements. Five 2048-pixel RGBA8 slices with full mips cost about
107 MiB, plus source caches and the existing native semantic streams.

The editor is a standalone authoring prototype. It has no game camera view,
terrain contours, WorldBuilder integration, in-game brush or live reload.
It supports four layers at a time and square 64..2048-pixel weight maps.
It renders rectangular world bounds stretched into its square top-down view;
brush distance is still calculated in world metres. The first prototype targets
one captured terrain shape; maps sharing the exact geometry may reuse it. Steam, Proton/Wine, broad editor/mission lifecycle,
artistic acceptance and performance qualification remain unverified.

Automated checks cover the pack contract, soft brushes, normalized weights,
source boundaries, raw PNG channels, map/coordinate contracts, preserved
auxiliary UVs, native `ps_4_0` compilation and WARP readback of four-layer
blending, zero-weight fallback, opaque output and map-edge clamping.

For the optional offline browser qualification, install Node.js and Playwright,
then run `node tests/terrain_paint_editor_browser_tests.js <editor.html>
<ignored-output-directory> [browser.exe]`. It verifies an actual brush stroke,
PNG download, exact undo/redo and PNG reload through a headless browser. The
regular CTest suite does not require a browser or proprietary textures.

Local GOG DX11 qualification on 2026-10-04 installed the 2048-pixel five-slice
paint array on all 320 `misn04` meshes and 27 diffuse passes (PID 34616).
A factor-4 micro-relief run recorded 243,200 domain invocations and 1,638,013
pixel invocations on an observed terrain draw, then restored all 320 streams,
27 passes and 320 padded bounds. The independently launched `misn05` editor
(PID 23928, 256 meshes) rejected the pack's geometry fingerprint before array
creation; stock terrain remained and exit was clean. The positive-only harness
reported failure for this deliberate rejection, as expected. An earlier
`misn05` launch stayed in briefing and did not qualify.

All 80 CTest entries passed, including seven paint-pack authoring cases,
the raw PNG codec, portable coordinate/configuration checks and GPU blending.
An offline headless Edge run exercised real brush input, PNG downloads,
exact undo/redo and reload; Pillow independently confirmed that RGB weights
survived zero PNG alpha. Desktop game screenshots could not be captured
because the Windows capture API reported desktop composition disabled;
broad in-game artistic/seam and camera-motion acceptance remains open.

During development, a live dump identified inconsistent JSON serializer
argument code in an incremental LTCG binary. A clean rebuild/full link removed
the crash; final runs used a full link. Keep this evidence separate from the
Windows commit-limit failure during an earlier startup. The shape fingerprint
excludes stock material words, which varied across fresh launches despite
identical height data, as well as the engine's sample-storage relocation bias.

The browser-edited PNG was rebuilt into a second 2048-pixel pack and submitted
on `misn04` in a fresh process (PID 52140), with flat factor-2 tessellation and
micro relief disabled. All 320 streams and 27 passes installed and restored,
the geometry fingerprint matched again, and an observed draw recorded 89,600
domain invocations with rasterized pixels. This qualifies the saved-brush-PNG
to rebuilt resources to native game submission path; it is not visual artistic
acceptance.
