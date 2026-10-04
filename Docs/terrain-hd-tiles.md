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
