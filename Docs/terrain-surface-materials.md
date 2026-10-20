# Authored terrain normal lighting

Development checkpoint: 2026-10-12, `agent/dlss-rt-bridge`. An explicit height
artwork recipe can now produce a guarded terrain normal atlas for native DX11
lighting. This is normal mapping: the height images do **not** displace geometry.
The existing procedural tessellation relief remains a separate geometric effect.

## Authoring contract

`scripts/Build-TerrainSurfacePack.py` uses the same live engine-index-to-atlas
capture as the HD diffuse authoring path. Obtain that capture using
`OPENSHIM_TERRAIN_HD_EXPORT`; see [terrain-hd-tiles.md](terrain-hd-tiles.md).
The atlas rectangles describe logical engine indices, not CSV row numbers.
The builder does not read or modify gameplay terrain formats.

Example local recipe:

```json
{
  "schema": "bzr-openshim-terrain-surface-art-v1",
  "sourceNormalResource": "moon_atlas_n.dds",
  "tileMeters": 20,
  "edgePixels": 16,
  "tiles": {
    "7": {"height": "regolith_height.png", "heightMeters": 0.25}
  }
}
```

```powershell
python scripts/Build-TerrainSurfacePack.py `
  --capture build/moon-atlas.json --normal-atlas C:/assets/MOON_ATLAS_N.dds `
  --recipe C:/art/moon-surface.json --source-root C:/art `
  --output build/moon-surface --prefix openshim_moon_surface
```

Height inputs are single-channel linear 8-bit, 16-bit or floating-point images,
with explicit finite ranges. RGB photographs are rejected. A value of 0.5 is
neutral; 0..1 maps to negative/positive `heightMeters`, bounded to (0,1]. A
quintic envelope reduces height and slope to zero at tile edges. Central
differences in physical tile units perturb the existing texture-space normal.
The native UV-derived frame applies the terrain's rotation/reflection. No
albedo-to-height guess or gamma conversion is applied.

The base-mip outer border retains the original normal pixels exactly. Other
rectangles remain unchanged at that mip. Identical rectangles alias: a selected
height applies to every engine index using that rectangle. Conflicting edits to
aliases or partial overlaps decline before output is written. Aliased indices
are listed in the report. This preserves the current atlas representation; it
does not allow different height art for two indices sharing one rectangle.

The tool writes an uncompressed linear RGBA8 DDS with a complete mip chain.
Normals are renormalized after mip downsampling. The whole atlas's distant mips
still combine nearby rectangles, so this is not an independent-slice/no-bleed
material representation. It retains stock atlas UV quantization and needs broad
seam, orientation and artistic acceptance. Outputs include source hashes,
height extrema, rectangle/engine mapping and normal DDS hash; the manifest is
written last. Existing outputs are refused. Assets stay local and are not
included in the repository or normal deployment payload.

## Runtime and capture

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 120 `
  -TerrainMicroRelief -TerrainAdaptive `
  -TerrainSurfaceManifest build/moon-surface/openshim_moon_surface.json
# Optional combined preview:
# add -VisualEnhancements -VisibleRayTracing -StreamlineDirectory <SDK>/bin/x64/development -StreamlineDevelopment
```

The harness stages the manifest and referenced DDS into the registered Enhanced
resource directory, snapshots both, and restores/removes them with the other
deployment/config files. The default-off native process variable is
`OPENSHIM_TERRAIN_SURFACE_MANIFEST`; no persistent setting or UI was added.

Runtime schema `bzr-openshim-terrain-surface-v1` requires an exact material,
source diffuse resource and source normal resource; `normalEncoding` is
`rgb-xyz-linear` and `heightUsage` is `normal-lighting-only`. A `heightAtlas`
field is currently rejected. Recognized per-pixel DX11 terrain fragment
programs must sample the normal at t2 using the existing atlas UV, enable normal
mapping, and avoid unsupported unpack/basis/retro overrides. The replacement
must be a matching single-sample linear RGBA8 2D texture. Native executable,
Ogre and renderer identity gates apply. Missing assets or unsupported material
contracts retain original normals. Unknown custom materials are not promoted
to compatibility merely because their names resemble stock materials.

Each original texture is retained before any binding changes. Mission teardown
restores only the same material owner and bindings still holding our replacement;
foreign changes are left alone. The read-only GPU draw check uses a nonblocking
terrain-owner lock and compares the actual PS t2 resource plus its linear SRV
format. Pipeline statistics must show visible terrain rasterization with that
resource bound. Installation messages alone do not qualify a capture.

Terrain discovery can run before the `OpenShimEnhanced` resource group is
initialized. The normal installer now waits for its exported group-readiness
API, then retries on the existing game-thread render tick. The wait is bounded
to 600 observations and real failures finish the attempt for that mission.
The mission reset clears this state. Surface GPU queries wait for the actual
normal resource rather than exhausting their samples during bootstrap.

`terrain-surface-report.json` requires fresh PID-tagged installation, bound
resource/raster evidence and full normal-pass restoration. The usual terrain
report additionally verifies tessellation/material/bounds cleanup and clean
process exit. It explicitly leaves geometry heights, broad camera/seam and
artistic acceptance false.

## Observed checkpoint

The local Moon test uses generated single-channel diagnostic ridge artwork,
not a production terrain pack. A live mapping captured 13 used engine IDs and
11 distinct rectangles in the 1024x1024 stock atlas. The pack has 11 normal mip
levels. The strong ridges make a changed lighting response easy to inspect.

- GOG `misn03`, PID 41680, `build/game-bridge-20261012-144809-425/`: imported
  120 frames at 1268x513. Six normal-mapped passes changed. A visible terrain
  sample bound the authored normal resource with 104886 pixel invocations.
  All six normal bindings, 27 tessellation passes, 144 padded bounds and 62
  deployment/config files restored, with exit code zero.
- Combined PID 29072, `build/game-bridge-20261012-145351-651/`: 120 frames at
  1266x513; DXR/cinematic effects on 105 matched frames and 105 extra SDK
  presentations reported by DLSS-G, final status zero. Native normal resource
  and restoration evidence passed. The generated input captures are not a
  generated-frame recording or FPS benchmark.
- The inspected before/after comparison uses separate runs in the same mission,
  not identical particle/game state or a pixel-aligned performance experiment.
  Stock textures and explicit height-normal detail are visibly distinguishable.
- A wrong Mars diffuse identity on Moon declined with `no guarded
  normal-mapped terrain pass`; no authored normals installed. The companion
  also failed because of the known bridge resize limitation, so that negative
  run qualifies only native rejection, not a successful combined capture.

The Win32 Release build and all 105 CTest tests pass, including seven authoring
cases for height precision/range, gradients, exact borders, aliases/overlap,
normal mip data, source bounds, identity and no-output-on-rejection.

## Next geometry step

The candidate height resource and shader are now implemented and GPU-tested;
native submission binding is still pending. `--geometry-height` adds a separate
`<prefix>_height.dds` and `<prefix>_height.json` to the normal authoring outputs.
It uses signed R32_FLOAT world-meter heights, one mip and explicit bilinear
`Load` sampling. Unedited rectangles are zero. A flat band of
`ceil(atlasWidth / 160) + 2` pixels precedes the quintic taper to cover Redux's
quantized UV endpoint inset and a bilinear footprint. Conflicting float heights
on aliased rectangles decline even when their quantized normals are identical.
The height manifest records the maximum absolute sample and marks native
integration unqualified. It cannot be used with `-TerrainSurfaceManifest`.
Future geometry integration must retain the stock normal map for this same
height art or separate finer detail; applying both the generated height normals
and the matching geometric slope would count the authored slope twice.

`OPENSHIM_HEIGHT_TEST` selects the candidate path in the shipped terrain test
shader; the native installer does **not** set this define. The shader computes
the UV-to-object-XZ Jacobian from the three control points, handles reflected
and rotated mappings, samples explicit height meters, and uses the existing
normal/tangent/clip/depth/shadow-receiver displacement updates. Invalid samples,
missing textures or degenerate geometry/UV Jacobians retain base geometry.
Camera translation does not change the texture's height at a fixed UV.

The Win32 WARP test captures actual `TerrainDomain` output through geometry
stream output. Its 96 runs cover flat/sloped bases, signed height planes,
rotation/reflection, translated cameras, zero seam bands, invalid/missing
textures and pixel-stage resource retention. This establishes GPU geometry
behavior, not game integration, cross-cluster camera acceptance, performance,
or displaced shadow casting. All 160 shader/interface checks and 106 CTest
tests pass, including nine surface authoring cases.

Texture-driven domain displacement must have its own height resource, physical
scale, stable tile UVs, explicit mip policy, geometry normal/depth update and
owned binding/restoration. An RGB normal atlas cannot supply authoritative
height values after the fact. The builder emits normal data by default and an
explicit candidate height resource with `--geometry-height`; neither output
silently enables a native domain texture binding.

Public Ogre 1.10 exposes domain binding types, but the stock DX11 implementation
uses a render-operation texture list and a current binding-type switch when it
sets stage resources. Appending a domain-only texture unit must therefore be
qualified on the released renderer while verifying both PS and DS resources;
API existence alone is insufficient. See
[Ogre texture binding types](https://github.com/OGRECave/ogre/blob/v1.10.0/OgreMain/include/OgreTextureUnitState.h)
and [DX11 stage binding](https://github.com/OGRECave/ogre/blob/v1.10.0/RenderSystems/Direct3D11/src/OgreD3D11RenderSystem.cpp).
An owned draw-scoped resource path is another candidate, with exact program and
target checks plus restoration before the next draw. Neither path is implemented
by this checkpoint. Complete DXR terrain geometry, displaced shadow casting,
contacts and the broader platform matrix remain separate work.

Released-renderer static qualification used Ghidra against SHA256
`78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0`,
the named `_render` export and its independent domain/fragment resource-call
branches. It confirmed a shared binding-mode field gating stage texture arrays;
the released enum values differ from public 1.10, another reason to avoid
unqualified SDK assumptions. The named `getDomainShader` export returns a
borrowed native domain shader. This is static evidence, not a qualified detour
or lifetime/submission proof. Raw analysis output stays local.
