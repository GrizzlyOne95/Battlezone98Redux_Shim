# Terrain and material improvements for the DX12 bridge

Development branch: `agent/dlss-rt-bridge`, 2026-10-12. This plan extends
the scene-layer work in [DLSS_RT_FRAME_BRIDGE.md](DLSS_RT_FRAME_BRIDGE.md).
The companion currently receives raster color, depth and camera data, not a
complete engine scene. Moving those images into DX12 does not itself subdivide
terrain, recover clipped lighting or provide material height maps.

## Existing implementation to reuse

The native terrain path already has default-off DX11 hull/domain shaders in
`resources/renderer/enhanced/openshim_terrain_tessellation_test.hlsl`, installed
through `src/patches/terrain_tessellation_test.inl`. Fixed factors 1, 2 and 4
subdivide three-control-point triangle patches. Optional bounded, static,
procedural micro-relief displaces vertices and updates surface normals,
projected depth and shadow-receiver coordinates. It preserves the native mesh
and gameplay height/collision data. Render bounds are padded and restored.
Existing exact-build/API gates retain native rendering if qualification fails.

This is actual geometry subdivision in the original renderer. It reaches the
companion through the resulting color/depth exports. DX11 already supports
hardware subdivision and displacement through hull/domain stages; using that
existing path is a deliberate first integration step. See Microsoft's
[tessellation stages](https://learn.microsoft.com/en-us/windows/win32/direct3d11/direct3d-11-advanced-stages-tessellation).

Native HD diffuse arrays and semantic tile streams also exist. Their current
material identity/orientation and ownership contracts are described in
[terrain-hd-tiles.md](terrain-hd-tiles.md) and
[terrain-render-path.md](terrain-render-path.md). Reuse their engine-indexed
mapping and dynamic update classification. Enlarged stock albedo alone does
not create new material detail, and the diffuse path does not yet apply the
height/normal/roughness artwork from an asset pack.

## Combined demo lane

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 120 `
  -TerrainMicroRelief -TerrainTessellationFactor 4 -TerrainReliefAmplitude 0.25 `
  -VisualEnhancements -VisibleRayTracing `
  -StreamlineDirectory C:/path/to/streamline-sdk-v2.14.1/bin/x64/development `
  -StreamlineDevelopment
# Native terrain plus the transport also works without the optional effects:
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -TerrainMicroRelief
```

The harness applies temporary process environment settings, captures a matched
scene/depth/camera product, exits gracefully, and restores deployment/config
hashes. `terrain-bridge-report.json` requires this PID's requested factor and
amplitude, actual visible tessellated GPU submissions, matching restored
material-pass counts, complete bounds restoration and clean exit. An install
message or old session's statistics cannot qualify a run. Wireframe is disabled
for this lane, and the particle-omission reference cannot be combined with it.
The report distinguishes fixed and adaptive subdivision. Material height maps,
full terrain geometry export, cross-cluster camera-motion acceptance and
performance qualification remain false.

The 2026-10-12 GOG `misn03` run imported 120 frames at 1280x720, with 111
effective DXR/cinematic frames and 111 extra SDK presentations reported by
DLSS-G. A sampled visible native terrain draw produced 243200 domain invocations;
144 padded bounds and 27 material passes were restored on clean exit. All 60
deployment/config hashes were restored. Detailed evidence and remaining limits
are in [DLSS_RT_DEMO_VALIDATION_20261012.md](DLSS_RT_DEMO_VALIDATION_20261012.md).

## Implementation sequence and acceptance

| Milestone | Concrete work | Required evidence |
|---|---|---|
| Native tessellation plus bridge | Exercise the existing micro-relief shader with owned scene/depth captures, DXR AO and optional DLSS-G | Fresh GPU patch/HS/DS/raster statistics, real captured scene, complete restoration; no FPS claim |
| Adaptive subdivision (prototype implemented) | Bounded projected shared-edge factors from both endpoints and Ogre's active viewport, using fractional-even factors 2..4 | GPU reversal/finite/viewport response and fractional raster coverage pass; live combined demo passes. Extended cross-cluster camera motion and performance comparison remain open |
| Authored height displacement (GPU candidate implemented) | Signed R32 meter atlas, guarded tile edges and explicit mip-zero domain samples; native submission binding pending | 96 actual domain/SO GPU runs cover geometry/normal/depth/shadow-receiver agreement and orientation/fallback. Live resource ownership, contacts and broad camera/cluster acceptance remain open |
| Detail shading and materials | Add material detail normals and roughness with explicit channel/color-space rules; retain compatible stock maps and lighting | Tangent/orientation correctness, stable distant mips, no brightened buildings or atlas bleed; review each planet's assets |
| Native terrain geometry for DXR (live selected-zone prototype) | Owned native streams/transforms, world BLAS and revisioned validity lease with dirty/mission invalidation | Static replay and live GOG refresh/fallback/reload pass. Actual deformation/mission/device cycling, full-map/object/relief coverage and terrain sunlight shadows remain open |
| Temporal reconstruction | Add dynamic object/terrain motion, camera-cut handling and transparent reactive coverage before DLAA/DLSS SR | History rejection on particles/disocclusion, stationary UI, moving units and changing terrain; the current camera-only FG preview remains distinct |
| Lighting and runtime | Recover linear scene lighting before SDR clipping; add measured queue/fence/pacing improvements | HDR/alpha/material contract tested before exposure/tone mapping; separate engine/GPU/bridge timings establish actual benefit |

Subdivision must add useful shape. The current domain shader interpolates the
original triangles and adds small procedural relief; increasing its factor
alone does not smooth the authoritative large-scale height field or reproduce
authored rocks, dunes or craters. A smoothing surface needs a separately
qualified height/normal reconstruction and a defined limit on divergence from
gameplay terrain. Avoid visually moving the ground beneath building foundations
or unit contacts while collision still uses the original terrain.

Adaptive factors must depend on the shared edge, not a triangle's center or
unshared material UVs. Otherwise adjacent patches can request different edge
samples. Tile UVs can be discontinuous at duplicated native vertices: compatible
height evaluation at those seams is a separate requirement from matching
tessellation factors. Bound and filter height detail so distant geometry cannot
alias even when normal shading remains detailed. Microsoft's
[hull-shader design](https://learn.microsoft.com/en-us/windows/win32/direct3d11/direct3d-11-advanced-stages-hull-shader-design)
documents the patch/control-point and factor interface; it does not establish
that these game-specific seam contracts are already met.

Raster domain-shader output is not automatically reusable as a DXR acceleration
structure. The current AO still rebuilds a mesh from visible depth. Complete
terrain shadows need a separately owned geometry representation, with the same
displacement policy if the ray-traced surface is meant to match the rasterized
surface. Shadow-receiver coordinates alone do not implement displaced shadow
casters or offscreen occluders.

The separate [native terrain snapshot](DXR_NATIVE_TERRAIN_SNAPSHOT.md) now feeds
base native triangles into a world-space BLAS for exact-frame diagnostic replay.
It includes sixteen clusters in the selected zone independently of screen
coverage. The default-off live presenter now accepts the zone under a
revisioned validity lease and falls back during renewal. Full scene ownership,
deformation/device qualification, relief matching and lighting replacement remain
required; the refresh probe does not change terrain. A further terrain-only
sunlight visibility preview now uses the actual Ogre directional light and
native geometric normals. Its native receiver depth match is deliberately
strict, its SDR attenuation is artistic, and its green/magenta mask is a debug
view. An exposed GOG base view executes rays without producing new terrain
shadows. Native buildings/vehicles and a genuinely shadowed game camera pose
are the next visual acceptance targets; hardware analytic offscreen shadows
already pass. See the snapshot document for tests and live evidence.

Triplanar cliff texturing, height-aware terrain blending, improved particle
lighting and a proper linear/HDR scene are worthwhile extensions once their
material/layer inputs exist. Mesh shaders, sampler feedback and variable-rate
shading are later optimization candidates. Profile the engine, tessellation,
copies, DXR and presentation first; the DX12 companion does not remove the
Win32 engine's CPU limits, draw submission or address-space limit.

## Adaptive prototype checkpoint

Add `-TerrainAdaptive -TerrainTargetPixels 12` to the combined command above.
The lane requires `-TerrainMicroRelief` and a factor-4 maximum. Target pixels
are bounded to 4..64; larger values request less subdivision. The native flag
`OPENSHIM_TERRAIN_TESSELLATION_ADAPTIVE=1` defaults off, and
`OPENSHIM_TERRAIN_TESSELLATION_TARGET_PIXELS` defaults to 12. No persistent UI
or INI setting was added.

The hull shader measures projected endpoint separation in pixels and requests
`clamp(length/targetPixels, 2, 4)` per shared edge. Its interior uses the maximum
edge request. It uses fractional-even partitioning; fixed modes retain integer
partitioning. Nonfinite values, invalid viewport dimensions and nonpositive or
very small endpoint W values retain the cap rather than culling terrain.
The displacement function and its object-space phase do not change with LOD.

The new hull parameter uses the hash-qualified Ogre exported parameter APIs,
requires an actual single float4 constant, and binds the logical slot to
`ACT_VIEWPORT_SIZE=111` from the public
[Ogre 1.10 parameter contract](https://github.com/OGRECave/ogre/blob/v1.10.0/OgreMain/include/OgreGpuProgramParams.h).
Ogre updates width/height and reciprocal dimensions for the active pass; no
fixed window size or guessed GPU buffer offset is used. Shader source hashes
include adaptive policy/target values, keeping cached variants distinct.

All 104 regressions and 150 shader compilation/interface checks pass. New GPU
tests execute the actual shipped function and hull/domain stages on WARP:
edge reversal, finite conservative fallback, distance/resolution response,
continuous requests, and complete coverage across a two-triangle shared
diagonal at fractional factors. Distant/near test draws recorded 36/144 domain
invocations; this is test-device evidence, not a game benchmark.

GOG `misn03` run `build/game-bridge-20261012-124653-034/` imported 120 frames at
1266x513. The actual native terrain sample recorded 89600 domain invocations
for 12800 patches and rasterized pixels. All 27 passes and 144 padded bounds
were restored, with clean process exit and all 60 file hashes restored. DXR and
cinematic effects executed on 110 frames; DLSS-G reported 110 extra SDK
presentations with final status zero. The captured enhanced scene was inspected.
An earlier run installed/rasterized correctly but the bridge disabled itself
on a game-window resize; it supplies no qualified combined capture.

The short live run establishes integration, not broad watertightness or an FPS
gain. Duplicated cluster endpoints can carry slightly different floating-point
transforms, and authored height seams are not yet available. Longer camera,
viewport, contact, deformation and cross-cluster tests remain required.

## Authored normal-lighting checkpoint

Explicit engine tile height images now feed a border-preserving normal-atlas
authoring tool and a default-off, guarded native normal replacement. Two live
GOG captures passed actual bound-resource/raster checks and restored all six
normal bindings, terrain resources and 62 deployment/config files. The combined
120-frame preview executed DXR/cinematic on 105 frames and reported 105 extra
SDK presentations with status zero. All 105 regressions pass.

The detailed schema, authoring/capture commands and geometry-stage requirements
are in [terrain-surface-materials.md](terrain-surface-materials.md). Height art
currently changes normal lighting only. Procedural relief remains the source of
geometry displacement; texture-driven heights, independent normal/height tile
arrays and roughness are still pending. The ridge test art validates the path
and is not a finished terrain artwork pack.

## Qualification limits

The candidate texture-height shader now displaces geometry in isolated WARP
domain-stage tests. It is not enabled by the native material installer. The
authoring tool's optional height manifest declares native integration
unqualified, and the existing game capture remains procedural relief plus
normal mapping. The shipped backend's shared texture-stage switch was checked
through released-module static analysis; a safely restored submission binding
still needs live qualification. All 106 CTest tests and 160 shader/interface
checks pass. See the surface-material document for the exact evidence boundary.

The original game still presents. Tessellation is currently native DX11; DX12
consumes its images. The helper does not rerender the complete terrain scene.
This development lane is separate from a supported gameplay integration.
Steam, Proton/Wine, other missions, editor/deformation and long camera/contact
tests need separate acceptance. No assets or generated captures are committed.

Native geometry follow-up: the companion now leases a selected base terrain
zone and traces sunlight from the actual Ogre direction. A separate
[building pose replay](DXR_BUILDING_SHADOW_REPLAY.md) adds real native building
occluders and visibly shadows the hangar's surrounding ground. Plane-derived
MSAA receiver matching improves ground coverage. Captured building poses are
not live casters, and domain relief is still absent from these base triangles.
Pose/lifetime transport, all zones, material opacity and direct-light replacement
remain prerequisites for full gameplay shadows.
