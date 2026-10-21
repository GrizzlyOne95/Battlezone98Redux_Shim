# Full-resolution terrain tiles

`HD Terrain Tiles` in OpenShim Options enables experimental DX11 diffuse tile
replacement. Version 2 packs also support independent normal, specular and
emissive tiles. A texture pack is required; the option does not create new artwork.
Restart the game after changing the tile option. It is off by default and works
with `Terrain Micro Detail`. Activation also requires the **effective DX11
Enhanced profile**. Redux/Retro retain the ordinary atlas without allocating
HD arrays. Leaving Enhanced during a mission restores the atlas material and
native streams; returning to Enhanced rearms native discovery.

Each terrain tile samples an independent texture-array slice at its full image
resolution. The existing map chooses the tile ID, rotation and transition. The
renderer adds local tile UVs to native terrain meshes and specializes their
shared material. No proxy mesh is used. Heights, triangles, collision, AI and
gameplay terrain files are unchanged. Stock normal, detail, specular, emissive,
lighting, fog and shadow maps retain their existing atlas coordinates unless
the pack explicitly replaces a supported material channel.

## Source material packs (v2, experimental)

Use `bzr-openshim-terrain-hd-v2` for source-authored material tiles. Each
material requires a `diffuseResource` identity guard, `sliceCount` (1..256),
`fallback`, `tiles`, and either a **256-entry** `sliceRemap` array or `tileRects`.
A remap entry at each native tile ID selects a physical array slice. For example, 18 distinct Mars
tiles occupy 18 slices even when many native tile IDs refer to the same art.
The CPU's native tile identities and UV parity checks remain unchanged.

For painless authoring, generate `tileRects` from the selected CSV's alias and
rectangle metadata, with entries such as
`{"rect":[0,0,0.125,0.125],"slice":0}`. OpenShim matches these against the
running engine's table, so no preliminary game capture or hand-authored native
ID table is needed. Choose one mapping form, not both. Every used native
rectangle must resolve unambiguously; unknown/conflicting rectangles decline
the pack. This reads only layout metadata, never atlas image pixels. Keep the
material and channel identity guards accurate when changing a map's material.

`releaseSourceTextures: true` declares the tile images to be transient array
upload inputs. OpenShim removes manager references only for input resources it
created, unloading each override after copying it and keeping the fallback
until all slices are populated. Resources already present before the upload
are preserved. Default is
false for shared-resource packs. This is ownership cleanup, not a guarantee
that a graphics driver's caches immediately return their memory.

Optional `normal`, `specular`, and `emissive` objects each contain an exact
`sourceResource` guard, `fallback`, and `tiles` with every physical slice:

```json
"normal": {
  "sourceResource": "ST_MARS_ATLAS_N_RGB8.dds",
  "encoding": "rgb-xyz-linear",
  "fallback": "crhd_mars_ma00sa0_n.dds",
  "tiles": { "0": "crhd_mars_ma00sa0_n.dds" }
}
```

This fragment illustrates a one-slice channel; list all slices in a real pack.
Normal tiles use linear RGB XYZ normals in the engine's tangent convention.
Their tangent frame follows oriented local tile UVs, avoiding quantized atlas
derivatives. Specular retains the existing shader's intensity interpretation;
this is not a new metal/rough material model. Diffuse color conversion and all
lighting remain with the selected terrain shader. The stock detail layer stays
separate. Each channel may have its own resolution/format, but its slices must
agree on dimensions, format and mip count. Missing channels retain stock maps.

All configured arrays and shader variants must succeed before the shared
material is changed. A mismatched source channel, unsupported shader contract,
missing tile, or conflicting surface-normal manifest declines the whole pack.
V2 requires native terrain and cannot be combined with four-material paint.
An optional per-material `microReliefScale` (finite **0..4**, default **1**)
scales Terrain Micro Detail's procedural displacement after that HD pack has
successfully installed. It does not enable micro detail or derive geometry
heights from normal maps. The shader and culling bounds use the same scaled
amplitude, capped at the existing one-meter envelope; `0` flattens relief.
Restart after editing the manifest. Failed/missing packs retain baseline
relief. CR exposes a value for each world in `Config/cr_terrain_hd.json`.

The same per-material object accepts independent detail controls (all finite):

| Field | Range | Default | Effect |
|---|---|---|---|
| `detailContrast` | 0..1 | 0.55 | Brightness modulation around neutral detail; zero removes its colour modulation. |
| `detailNormalStrength` | 0..4 | 2.2 | Luminance-gradient detail normal strength; zero disables both detail-normal layers. |
| `detailNormalNearScale` | 0..1 | 0.55 | Relative strength of the finer 32x normal layer. |

These apply only to the owned native HD DX11 Enhanced fragment programs.
They leave authored D/N/S/E textures and geometry amplitude independent.
Defaults retain the current source exactly, including Mars's existing look.
Changed values specialize the shader before its existing source-hashed cache
name is calculated, so materials cannot share stale tuned variants. No extra
texture, uniform, slot or persistent source image is allocated. Unknown shader
contracts or invalid values decline installation and retain the stock owner.
Restart after editing; use the `[TERRAIN-HD] detail tuning` log to verify the
actual material/values. Detail-map resolution remains the existing 2048px
contract. DX9/Retro/Redux fallback is unchanged.

An optional `heightTexture` replaces the procedural field when micro detail
is enabled and the guarded HD pack installs. It is a **file path relative to
the manifest**, using case-correct `/` separators, paired with
`"heightEncoding": "signed-unit-r32"`. Absolute/drive-relative/parent paths
decline. Unlike D/N/S/E Ogre resource names, this file is read directly into an
owned GPU texture, with no retained Ogre image/source cache. The narrow format
is one-mip, ordinary 2D legacy DDS D3DFMT_R32F (114), 16..4096 pixels per axis.
Every sample must be finite within -1..1. It is multiplied by the effective
relief amplitude (including `microReliefScale`); zero is neutral. It is not the
older world-meter height DDS contract. Missing/invalid requested height art
declines tessellation and restores the HD/native material owner.

The texture uses the original atlas UV/layout solely as a geometry lookup.
It must author exact flat borders covering quantized UV insets and the bilinear
footprint. The existing GPU-tested domain kernel handles rotated/reflected
UVs and updates normals/tangents, clip/depth and shadow receiver coordinates.
It replaces noise and does not also generate matching normal-map slopes.
Collision, shadow casting and DXR terrain geometry remain separate.

The public D3D11 `DSSetShader` hook (ordinal pinned against the Windows SDK)
binds t127 only for exact owned domain shader COM objects. Leaving them restores
the previous slot; a foreign replacement is preserved. Mission/profile cleanup
restores any remaining scope and releases owned resources. PS bindings are
untouched. No requested height means no height allocation or substitution.

Windows/GOG Moon PID 61460 confirmed actual DS t127 height plus HD mask 7 on a
rasterized native draw (243,200 DS / 59,949 PS invocations), with 1,626 balanced
binding/restoration scopes and all 136 staged files restored. PID 48852 passed
a closer ground-region view with 1,202 balanced scopes. Both screenshots were
inspected. The five CR art tests and 112 native tests pass, including 192 actual
GPU domain-output cases in signed-meter and scaled signed-unit modes, ownership/
restore/foreign-writer/PS preservation and malformed height input. The Release
Win32 load chain builds. Profile/device cycling and Steam/Proton/Wine runtime
are unverified; this remains an opt-in prototype.
The ordinary-settings trial PID 59068 also passed without a diagnostic
tessellation flag or terrain probe: both terrain feature settings installed
0.625 m texture relief, with 1,056 balanced binding scopes and all 136 files
restored. Its close screenshot was inspected.

The 2026-10-20 Windows/GOG Moon trial (PID 56724) installed factor-4 native
terrain with `displacement=0.625` for the 2.5 scale. All 144 mesh bounds used
the same amplitude; an actual native draw reported 243,200 DS invocations,
50,555 PS invocations and `hdMaterialMask=7`. All 82 passes, 144 bounds/streams
and 135 staged files restored. The screenshot was inspected. All 111 CTests
pass and the Release Win32 load chain builds. Other world art settings and
Steam/Proton/Wine runtime remain unverified.
Exit restores all replaced texture units and native programs/streams and removes
owned arrays. Version 1 diffuse packs remain supported.

CR's `Tools/Build-MarsHdTileSources.py` exports the saved Stock World Terrain HD
revision 6 Mars recipe **before its packing stage**. It uses the individual
material cache, authored normal/reflectance inputs, existing corrections and
shared transition masks. It never crops the installed atlas. The companion CR
document `Docs/MARS_HD_TERRAIN_EXAMPLE.md` describes the one-command
`Tools/New-MarsHdTerrainExample.ps1` workflow: generate editable DDS files,
prepare automatic mapping, and optionally preview without a capture/bind step.
Existing DDS art edits survive subsequent previews. The native capture remains
available for diagnosing a different material's exact channel identities.

At 1024 pixels with complete mips, 18 BC1 diffuse slices, RGB24 normals
(typically RGBA8 on the GPU), and BC1 specular slices use about 120 MiB of array
storage, plus Ogre/driver source caches and semantic streams. Emissive arrays are
optional; the current Mars source has intentionally black emissive maps.

Validation on 2026-10-20: all 111 CTests pass, the 72 exported source DDS files
have complete mip payloads, and the specialized PS4 shader compiles in ordinary,
shadow, PSSM v2 and IBL variants. Windows/GOG DX11 CR `misn04` PID 44572 rendered
the source pack using CR's Enhanced/IBL selecting material: 320 meshes passed
packed-UV parity and 82 passes installed/restored. A rasterized native draw
reported 12,172 pixel invocations with `hdTiles=1 hdMaterialMask=3`. All 320
streams, three arrays and 57 programs were restored/released, and the helper
restored 130 temporary files by hash. The screenshot was inspected. Broader
seam/rotation art acceptance, performance and other platforms remain open.
GPU query evidence reports
`hdMaterialMask` (normal=1, specular=2, emissive=4) only when the exact owned
arrays are bound at a native terrain submission.

### 32-bit application RAM

The Windows/GOG executable tested here has `LARGE_ADDRESS_AWARE` set. The local
probe records its actual PE flag, private commit and lifetime peak commit, plus
a read-only `VirtualQueryEx` scan for committed/reserved/free address space and
the largest free region. Private commit is not the same as total occupied
virtual address space or GPU VRAM. See Microsoft's
[process counters](https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-process_memory_counters_ex)
and [address-space query](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualqueryex).

An initial `misn04` A/B with the same Enhanced profile and camera measured
352 MiB atlas versus 527 MiB HD private commit at both 1K and 2K. Changing native
HD semantic streams from CPU-mappable dynamic buffers to GPU-default buffers
saved about 85 MiB in the 2K trial. The final fresh A/B measured about 443 MiB
for 1K, 442 MiB for 2K and 353 MiB atlas, about
90 MiB extra. The upload still supports complete terrain-rebuild refreshes via
`UpdateSubresource`, without a persistent CPU mapping or Ogre shadow buffer.
The semantic payload is still about 80.4 MiB across 320 meshes.

The 1K run peaked at 612 MiB private commit. The 2K HD lifetime private-commit
peak was 883 MiB versus 430 MiB for the atlas; peak occupied VA was 1,546 MiB
versus 1,068 MiB. Settled free VA was 2,910 MiB versus 3,040 MiB, with a largest
free block of about 2,045 MiB in all three runs. The 1K default therefore has
a substantially smaller measured loading peak than 2K.
Evidence: CR local `run-20261020-132505` (atlas PID 13348),
`run-20261020-133006` (1K PID 61980) and `run-20261020-133056` (2K PID 10228),
`memory.json`. These are short mission
benchmarks, not worst-case campaign/co-op/save-load budgets. Steam/Proton/Wine
memory and long-session fragmentation remain unqualified.

Repeated profile changes originally accumulated roughly 90 MiB private commit
per HD reload. The terrain handoff helper used a reference-count assumption
that did not match the released Ogre build. Copy/release now use Ogre's own
exported operations under the existing exact-module gate, including final
control-block destruction inside Ogre. No control-block byte offset is used.
The three-cycle GOG trial (PID 55196, CR local `run-20261020-131930`) returned
to 359.9, 360.6 and 361.3 MiB in Redux; HD settled at 447.3 MiB after the final
resume. EXU was loaded only as that trial's profile-switch driver. All 320
retired streams reported one remaining binding-owned reference before removal,
and all passes/resources/files were restored. The screenshot was inspected.
This is a bounded regression check, not a long-session leak proof.
Startup Redux was also tested with HD opted in (PID 18404, CR local
`run-20261020-133145`): the effective-profile gate retained the atlas and no
HD array/material allocation occurred.

The released Ogre backend subtracts two levels from explicit compressed-array
mip requests, while its source loader already reports the shortened chain.
V2 compensates that request and still requires exact GPU descriptor equality
before copying. The live 1024-pixel arrays contained nine BC1 diffuse/specular
levels and eleven RGB normal levels; exported files retain all eleven levels.
This behavior also appears in the
[upstream Ogre 1.10 implementation](https://github.com/OGRECave/ogre/blob/v1.10.0/RenderSystems/Direct3D11/src/OgreD3D11Texture.cpp#L455-L458).
Each pass guards/binds only channels enabled in its real shader defines; lower
detail techniques retain their omitted-map bindings.

## Creating a pack

Put ordinary PNG or DDS images in an Ogre resource directory loaded by the
game/mod. All images, including the fallback, must have matching dimensions,
pixel format and mip count. DDS files must be ordinary 2D images, not prebuilt
DX10 arrays. Use tile artwork with compatible edges and baked transitions;
this mode keeps the original tile system. The separate experimental
[four-material paint mode](terrain-paint.md) uses continuous RGBA weights
and a standalone brush editor instead of the map's tile choices.

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
TerrainHdManifest = auto
```

The manifest path may also be explicit (relative to the game folder, or absolute). Image names are Ogre resource names,
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

## Pack discovery and the separate-pack layout

The HD terrain pack is a separately subscribed Workshop item (or a GOG
`mods\<id>\` folder) holding `cr_terrain_hd.json` plus flat `crhd_*.dds` images.
BZR does not honor Workshop dependencies, so OpenShim finds and mounts it
itself. With the shipped `TerrainHdManifest = auto` (or an empty value) the
manifest is searched, first match wins, in: the game folder, then each
subfolder (sorted by name) of `addon\`, `mods\`, `packaged_mods\` and the Steam
`workshop\content\301650\` directory, for `terrain_hd_tiles.json` then
`cr_terrain_hd.json`, directly in each root. An explicit absolute path, or a
relative path that exists under the game folder, overrides discovery; a relative
path that does not exist (for example the legacy `terrain_hd_tiles.json` in an
old ini) falls back to discovery. The chosen file is logged once as
`[TERRAIN-HD] manifest resolved path="..." source=explicit|auto`.

The capability probe and the loader share one resolver
(`ResolveTerrainHdManifestAt`), so the Options UI and the renderer agree. Before
the first tile loads, the manifest's folder is added as a non-recursive
FileSystem location in an Ogre group named `OpenShimTerrainHd`, unless the first
texture is already resolvable (Redux mounted the folder itself). Any failure
logs a warning and keeps the stock atlas.

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
