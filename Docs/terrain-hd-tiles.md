# Full-resolution terrain tiles

`HD Terrain Tiles` in OpenShim Options enables experimental DX11 diffuse tile
replacement. A texture pack is required; the option does not create new artwork.
Restart the game after changing it. It is off by default and works with
`Terrain Micro Detail`.

Each terrain tile samples an independent texture-array slice at its full image
resolution. The existing map chooses the tile ID, rotation and transition. The
renderer adds local tile UVs to native terrain meshes and specializes their
shared material. No proxy mesh is used. Heights, triangles, collision, AI and
gameplay terrain files are unchanged. Stock normal, detail, specular, emissive,
lighting, fog and shadow maps retain their existing atlas coordinates.

## Creating a pack

Put ordinary PNG or DDS images in an Ogre resource directory loaded by the
game/mod. All images, including the fallback, must have matching dimensions,
pixel format and mip count. DDS files must be ordinary 2D images, not prebuilt
DX10 arrays. Use tile artwork with compatible edges and baked transitions;
this keeps the original tile system and does not add brush painting or blending
between arbitrary new materials.

Save this manifest beside `battlezone98redux.exe` as `terrain_hd_tiles.json`:

```json
{
  "schema": "bzr-openshim-terrain-hd-v1",
  "materials": {
    "MA_DETAIL_ATLAS": {
      "sliceCount": 256,
      "diffuseResource": "mars_atlas_d.dds",
      "fallback": "my_terrain_fallback.png",
      "tiles": {
        "9": "my_tile_009.png",
        "10": "my_tile_010.png"
      }
    }
  }
}
```

Keys are the engine's decoded tile indices, including its transition tiles;
they are not terrain type numbers. Unmapped indices use the fallback image.
Use `256` slices for a complete pack. A smaller pack must still cover every
index the mission uses. Exact material-name bindings take priority over `*`.
Select a planet/map-appropriate manifest; the system does not infer artwork
from the material name shared between different terrains.
The optional `diffuseResource` guard requires the ordinary native diffuse
pass's exact texture resource name before allocating the HD array, installing
streams or changing material bindings. Only compatible passes using that
atlas are replaced; shadow techniques using `black.dds` remain unchanged.
Exported packs include this guard; older diagnostic manifests remain supported.

Enable the option or set:

```ini
[Terrain]
TerrainHdEnabled = 1
TerrainHdManifest = terrain_hd_tiles.json
```

The manifest path may also be absolute. Image names are Ogre resource names,
not filesystem paths relative to the manifest. Preserve filename case for
Proton/Wine. Missing/incompatible resources or unknown native layouts decline
the replacement and retain stock terrain. The native path currently requires
one shared terrain material per mission and compatible per-pixel DX11 programs.

Texture resolution and tile count affect GPU memory. A 256-slice uncompressed
RGBA8 array with full mips costs about 85 MiB at 256 pixels per tile, 341 MiB at
512, or 1.33 GiB at 1024. Ogre may also retain source images in its resource
cache. Additional semantic vertex buffers cost approximately 80 MiB for the
320-mesh test mission. Compressed DDS can reduce texture memory. Editor tile
changes refresh the semantic buffers after native full rebuilds; mission exit
restores native shaders, diffuse textures and buffer declarations.

## Visible diagnostic test

Generate asymmetric numbered tiles in a registered resource directory. For a
local development deployment the Enhanced resource directory is registered:

```powershell
$game = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux'
./scripts/New-TerrainHdSmokeTiles.ps1 `
  -OutputDirectory "$game/openshim/renderer/enhanced" `
  -ManifestPath "$game/terrain_hd_smoke.json" -TileSize 256
./reverse_engineering/run_terrain_tessellation_test.ps1 `
  -HdTiles -HdManifest terrain_hd_smoke.json `
  -MicroRelief -Factor 4 -RunSeconds 65 -Deploy
```

A development build can be replaced by the Campaign Reimagined suite updater.
The local verifier reports this branch's inherited `1.0.0.34` below the installed
suite's `1.0.0.46`; that is an updater-version gate, not a terrain test pass.
Redeploy before each development run and verify DLL hashes afterward. No release
version or updater policy was changed for this experiment.

The harness temporarily changes only the two HD INI keys and restores them.
It requires a fresh process, the HD array and semantic stream at an actual
terrain submission, rasterized pixels, and complete material/stream cleanup.
The colored numbers are diagnostic art. Leave the HD option off for normal
play until a suitable artwork pack is installed.

Local Windows/GOG DX11 runs on 2026-10-04 (PIDs 19632 and 23936) visibly rendered
the numbered textures over native terrain. All 320 meshes passed exact packed
UV parity, and 28 material passes accepted replacement VS/PS programs. The
combined micro-relief run passed VS/HS/DS signature checks and produced
243,200 domain invocations per sampled cluster; the second run also verified
the array SRV and 28-byte semantic stream during a draw. Both runs restored
all 320 streams and 28 passes and exited cleanly. A further factor-2 run
(PID 10516) passed with micro relief disabled, including array draw proof and
complete stream/material restoration. Steam, Proton/Wine, longer
mission/editor lifecycle tests, broad rotation/transition visual acceptance
and production artwork/performance qualification remain unverified.

The small tessellation upgrade in this workstream uses quintic relief
interpolation. Its first and second derivatives vanish at noise-cell edges,
reducing curvature kinks while preserving fixed phase and bounded visual
displacement. The shipped GPU test checks boundary curvature, analytic slopes,
camera independence, periodic seams and displacement limits.

## Atlas exporter and Mars pilot

`scripts/Build-TerrainHdPack.py` creates a complete engine-indexed baseline
from a live mapping capture and the installed game's diffuse atlas. CSV rows
are **not** semantic tile IDs: the stock Mars CSV repeats `MA11SA0.MAP`, and
native indices 9 and 10 both resolve to its later rectangle. Capture the real
mapping rather than assuming CSV order. The exporter reads the validated
256-entry engine table; it does not parse or modify TRN/HG2/MAT/LGT files.

For a fresh DX11 Mars mission, set an absolute output filename in the process
environment before launching through the harness:

```powershell
New-Item -ItemType Directory -Force build/terrain-mars-pack | Out-Null
$env:OPENSHIM_TERRAIN_HD_EXPORT = Join-Path (Get-Location) 'build/terrain-mars-pack/mars-atlas.json'
try {
    ./reverse_engineering/run_terrain_tessellation_test.ps1 -Mission misn04.bzn -RunSeconds 65 -Deploy
} finally {
    Remove-Item Env:/OPENSHIM_TERRAIN_HD_EXPORT
}
```

The diagnostic makes one capture per fresh process, before any native HD
binding. Keep HD off for this capture and give the file's parent directory
permission to receive output. The existing harness enables its flat
tessellation submission test; the export flag alone does not alter terrain.

Install Python 3.9+ and Pillow 9.1+ (`python -m pip install 'Pillow>=9.1'`), then build:

```powershell
$game = 'C:/Program Files (x86)/GOG Galaxy/Games/Battlezone 98 Redux'
$atlas = "$game/BZ_ASSETS/pc/textures/TerrainTextures/BZ_TERRAIN_ATLASES_DIFF_DDS/mars_atlas_d.dds"
$csv = "$game/BZ_ASSETS/common/materials/ma_detail_atlas.csv"
python scripts/Build-TerrainHdPack.py `
  --capture build/terrain-mars-pack/mars-atlas.json --atlas $atlas --atlas-csv $csv `
  --output build/terrain-mars-pack/baseline --prefix openshim_mars_baseline
```

The baseline only enlarges existing artwork, which establishes correct tile
assignment rather than creating new detail. Images retain the atlas crop's
orientation; the native renderer applies the map's original rotation. Missing
used IDs, wrong atlas identity/dimensions, invalid or fractional pixel crops
and unknown recipe tile names fail before publishing a manifest. Existing
outputs require `--force`. Exact pixel equivalence to stock is not promised:
native stock UVs are quantized, while HD samples continuous local tile UVs.

Add `--recipe scripts/terrain-packs/mars-pilot.json --source-root <textures>`
and change output/prefix to `pilot`/`openshim_mars_pilot` to use the supplied
Mars albedo archives. The recipe replaces nine named solid dune, soil and rock
variants. It preserves stock alpha, matches average stock color and fades to
the original crop at the edges over 32 output pixels. Baked transition tiles
remain stock, enlarged to the same 512-pixel dimensions. This is a partial
artwork pilot: preserved transition/detail/normal/specular maps have their
original detail, and stock-edge bands can remain visible. Material height and
normal assets in those archives are not applied by this diffuse-only path.

Artwork sources may be loose files (`{"file":"relative/albedo.png"}`) or
specific ZIP members (`{"archive":"art.zip","member":"albedo.png"}`). ZIPs
are read without extracting them, and artwork paths must remain inside the
explicit source root. The builder writes a contact sheet and provenance
report with content hashes beside the manifest. User artwork and game-derived
images/captures stay local; only the exporter, recipe and tests belong in Git.

Copy the generated PNGs to a registered Ogre resource directory, such as
`$game/openshim/renderer/enhanced`, and the generated manifest beside the game
executable. Select `openshim_mars_pilot.json` with `TerrainHdManifest` and
enable **HD Terrain Tiles** in OpenShim Options, then restart with DX11. The
baseline occupies 18 unique source images; the pilot occupies 19. Both cover
all 256 native slots and allocate approximately 341 MiB for the 512-pixel
RGBA8 array with mips, plus source caches and native semantic streams.

`python tests/terrain_hd_pack_tests.py` checks scrambled IDs, crop orientation,
duplicate source regions/names, partial overrides, original edge/alpha
preservation, source identity and path boundaries. CTest includes this suite
when its Python interpreter has Pillow; configuration reports a missing
dependency. Linux/Proton authoring uses the same script and case-preserved
resource filenames; native Steam/Proton/Wine qualification remains separate.

The first 512-pixel native run faulted during Ogre's pixel-buffer upload path.
HD uploads now resolve the exact-build backend's exported `GetTex2D` getter
and validate source/destination descriptors, slice bounds and device identity
before explicit [DX11 subresource copies](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-copysubresourceregion).
Each source mip is copied to the destination slice's corresponding mip without
scaling or implicit mip generation. `terrain_hd_texture_copy_tests` uses WARP
readback to check 512-pixel mip chains, first/last slices including index 255,
untouched neighbouring slices, row orientation and invalid/cross-device copies.

On 2026-10-04, GOG DX11 `misn04` baseline PID 46296 and artwork-plus-relief
PID 5408 both rendered the 512-pixel, 256-slice array on actual native terrain.
Each audited 320 mesh streams and replaced/restored 27 diffuse material passes;
the shadow technique using `black.dds` was retained. GPU evidence confirmed
the array/semantic stream at rasterized draws. The pilot also restored all
320 relief bounds, and a live screenshot showed the new cracked-soil artwork.
The complete CTest suite passed 76/76, including seven Python authoring tests.
These short runs establish the authoring path and submission/lifetime behavior;
broad seam/rotation artistic acceptance and production performance remain open.

The subsequent `misn05` pilot/relief run (PID 50948) also passed native GPU
submission and clean restoration for its 256 meshes and 27 diffuse passes.
Its independently captured 256-slot table and diffuse resource matched
`misn04` exactly. The earlier unattended `misn05` attempt never selected a
cluster and did not qualify; the rerun reached active terrain before the user
stopped Computer Use, after which no further UI automation was performed.
The user subsequently confirmed that the second mission worked as well.
A deliberately wrong `moon_atlas_d.dds` guard on Mars (PID 8824) declined
before array allocation or HD material installation and kept stock terrain.
The positive-test harness reported failure for that deliberate negative case,
as expected; fresh-session logs established rejection and clean game exit.
