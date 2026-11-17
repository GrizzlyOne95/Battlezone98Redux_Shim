# Visual terrain micro relief prototype

Experimental, off by default. The OpenShim Options page exposes **Terrain Micro
Detail** on page 1, beside the DX11 rendering controls. Its On/Off choice saves
`[Terrain] TerrainMicroRelief = 0/1` in `openshim.ini` and takes effect after a
game restart. On uses factor 4 and the 0.25-world-unit relief preset. DX11 is
required; unsupported renderer/build/terrain contracts retain native terrain.

This extends the native tessellation submission test with shallow procedural
surface detail. It changes rendered terrain and
render bounds only: collision, pathfinding, placement, height files, networking,
and the native terrain vertex/index buffers are unchanged.

## Surface and coordinates

The domain shader evaluates smooth periodic value noise with 2.5-world-unit
cells and an 80-unit period. The experimental amplitude defaults to 0.25 world
units; the test harness accepts 0 through 1. Zero selects the original
zero-displacement tessellation path. This is an art/geometry proof rather than
a calibrated material height map or large-scale hill smoothing.

The native per-pixel VS stays active. Inverse world-view reconstructs object
position from its view-position output. Native terrain nodes must have unit
scale, identity rotation, and X/Z translations aligned to the noise period;
unsupported transforms decline the test. Matching periodic phase makes
duplicate vertices and neighboring clusters agree without welding atlas seams.
This works with camera-relative world/view transforms as well as ordinary
transforms. No camera-driven height fade is applied: fixed ground points keep
the same height when the camera moves.

The initial inverse-view-only, sine-wave/fade prototype passed submission checks
but the user observed moving waves. That version is rejected as visual
acceptance. The revised shader reconstructs object coordinates and uses static
noise. Looking at a stationary image or positive GPU counters cannot validate
camera-motion behavior.

The shader adds a vertical offset, transforms the original normal by the
displacement Jacobian's inverse transpose, adjusts optional tangents, and
updates view position, clip position, depth, and shadow receiver coordinates.
It preserves the original VS/PS, atlas UV, COLOR0, native receiver bias, and
texture bindings. Ogre owns the domain-stage auto constants; no new native
address or competing D3D draw hook is introduced.

## Render bounds and lifetime

Before attaching nonzero relief, the test pads finite native mesh AABBs and
sphere radii by the maximum amplitude. It validates each mesh through the
existing cluster identity seam, checks the required restoration export, and
invalidates scene-node bounds. Zone construction/process seams maintain the
padding for new clusters and native full rebuilds. Padding does not accumulate.

Native shared material settings are restored before mesh bounds. Restoration
looks up meshes by resource name and requires matching identity and owned
expanded bounds; it preserves independently changed native bounds. A failed
bounds refresh retires displacement before subsequent terrain rendering.

## Lattice smoothing (TerrainTessellationSmoothing)

Opt-in, not in the settings page: `[Terrain] TerrainTessellationSmoothing = 1`
(env `OPENSHIM_TERRAIN_TESSELLATION_SMOOTHING`) and
`TerrainTessellationSmoothingMax = 4.0` (env `..._SMOOTHING_MAX`, clamped to
0.5..12 world units). Both are capture overrides, so a harness value beats the
INI. Each tessellated point takes its height from a smooth surface through the
native 5 m height lattice instead of the flat stock triangle; the offset from
the stock surface is vertical only, clamped to the Max, and stacks under the
micro relief. Visual only: collision and gameplay heights are unchanged.

Requirements, each failing closed with one `[TERRAIN-TESS] lattice smoothing
off: ...` log line and the rest of the terrain unchanged:

- `TerrainMicroRelief = 1` with a qualified DX11 relief variant.
- An installed HD paint pack. Redux renders camera-relative, so the domain
  stage has no absolute position except in paint mode, where `hdUV` carries
  native world XZ and `tileSlice` native world Y. Other relief variants
  (noise, HD tiles, height textures) do not smooth.
- A deployed `openshim\renderer\enhanced\openshim_terrain_tessellation_test.hlsl`
  that contains `OPENSHIM_LATTICE_SMOOTH`; an older file logs a Warn line.
- A lattice <-> world mapping check: one cluster's native vertex positions and
  heights must land on the lattice texels they are mapped to (at most 1% off,
  0.02 m), using the source cluster or up to 24 others until one has 2 m of
  relief. A flat-only map declines rather than smooth unverified.

Data: `include/terrain_lattice_smoothing.h` holds the mapping and the CPU
reference of the shader curve. The whole runtime zone rectangle (the same rect
live paint reads, one zone more per axis than the file) is read through the
engine height reader into an `R16_UINT` DEFAULT texture of masked 0.1 m units
(exact integers, half the size of R32_FLOAT; 1280x1280 is 3.2 MB). Texel
(tx, tz) is storage sample (baseX + tx, baseZ + tz), baseX = minZoneX * 256 +
originX - 128, at world X = 5 (tx - 128 columns), Z = -5 (tz - 128 rows). The
two offsets are per-map `#define OPENSHIM_LATTICE_OFFSET`; programs are named by
source hash and installed per mission, so this is the same pattern as the paint
bounds defines. The view binds on DS slot `t126` through
`TerrainHeight::DomainBinding` (second view next to the height slot 127, saved
and restored per owned domain, never on the hull or pixel stages).

Curve: separable Catmull-Rom over the 4x4 neighbourhood, rows along x and then
the column along z. Each 1D pass is clamped to its own segment, so the surface
stays within the central 2x2 samples (no overshoot at cliff lips), is exact at
the samples and continuous across cells. Where a clamp engages the surface is
C0 only (a slope kink at the clamp line). The normal is the analytic bicubic
gradient; pinned at the Max clamp it keeps the stock normal; relief slope
correction stacks on either. World XZ and the stock height are re-interpolated
from the control points with `precise` unfused products, so both patches of a
shared edge compute bit-identical results (WARP test).

Bounds: the hull cull sweep (`OPENSHIM_RELIEF_SWEEP`) and the padded render
bounds both grow by the Max. The adaptive hull adds `min(Max, 0.25 x the
edge's world-Y drop)` to each edge's painted relief span, so level ground
stays thin and cliff edges (6 m drop or more) reach full scale. Endpoints
only, so both patches of an edge agree (`terrain_paint_gpu_tests`). Normals
blend from the smoothed to the stock normal over the last quarter of the
bound, so the clamp line leaves no shading seam.

Deformation: the zone-process hook reads every cluster's height (0x250),
next-height (0x260) and full (0x270) dirty byte before the original consumes
them. After it, each dirty cluster's 65x65 window plus a 16-sample margin is
re-read through the height reader, compared, and only a changed bounding
rectangle is uploaded with `UpdateSubresource`. A full-dirty byte refreshes that
zone's whole window; a map-wide rebuild arrives as every zone. Device recovery
and mission teardown release the lattice through the tessellation restore path,
and the next install rebuilds it.

Logs: `[TERRAIN-TESS] lattice smoothing installed size=WxH max=M`, a mapping
line (zones, base, offsets, format, slot), a 2 s rate-limited Debug refresh
line, and a release line with batch/upload counts.

Tests: `terrain_lattice_smoothing_tests` (CPU curve: exact at samples, no
overshoot, symmetric, continuous, slopes, mapping, dirty windows),
`terrain_smoothing_gpu_tests` (WARP: shared edge bit-identical, matches the CPU
reference, clamp engaged, flat lattice does not move),
`terrain_height_domain_gpu_tests` (lattice slot bind/restore) and the HD
smoothing variants in `scripts/Test-TerrainTessellationShaders.py`. Harness:
`run_terrain_tessellation_test.ps1 -MicroRelief -Smoothing [-SmoothingMax 4]`.

## Run and validation

Build Release/Win32 and deploy with the normal full-load-chain harness:

```powershell
./reverse_engineering/run_terrain_tessellation_test.ps1 -Factor 4 -MicroRelief -ReliefAmplitude 0.25 -RunSeconds 65 -Deploy
```

`-Wireframe` can be combined with relief. `-ReliefAmplitude 0` is the flat
control. The process-only controls are `OPENSHIM_TERRAIN_MICRO_RELIEF_TEST` and
`OPENSHIM_TERRAIN_MICRO_RELIEF_AMPLITUDE`, alongside the existing tessellation
factor/wireframe controls. An explicit process value for
`OPENSHIM_TERRAIN_MICRO_RELIEF_TEST` overrides the saved UI choice for harness
runs, including a flat control when the UI choice is On. Without an override,
the saved setting applies. Amplitude/factor overrides remain developer controls.

The shader linkage check compiles 110 shaders across ten native permutations,
baseline factors 1/2/4 and relief factors 2/4. The Windows CTest
`terrain_microrelief_gpu_tests` executes the shipped HLSL on Microsoft's WARP
device and checks amplitude bounds, zero fallback, cluster phase agreement,
camera/coordinate recovery, and analytic slopes against finite differences of
GPU heights. It needs no game installation. Linux keeps the existing host test
lane; this GPU check is Windows-only.
Release/Win32 built successfully and all 74 Windows CTest tests passed.

The 2026-10-04 UI follow-up also passed the INI completeness/default-policy,
lossless writer and preset migration checks. GOG DX11 PID 11924 showed the new
page-1 row as Off, then clicking it saved `TerrainMicroRelief = 1`, displayed
On and the restart-required status. The game exited cleanly. PID 29760 then
initialized the terrain path from that saved setting with every terrain test
environment override removed. That run exited before cluster selection, so it
does not add a second rendering acceptance result. UI automation stopped after
the user's physical Escape input; no further automated UI input was sent.

Initial Windows/GOG run PID 59828 installed 27 shared passes, padded/restored all
320 discovered meshes, and exited cleanly. Factor 4 recorded 12,800 IA patches,
12,800 hull invocations, 243,200 domain invocations, and 92,480 pixel invocations.
Those counters establish submission, not the rejected wave prototype's visual
correctness.

Revised Windows/GOG DX11 runs on 2026-10-04 (PIDs 36196 and 19400) used the
static object-coordinate shader, factor 4 and amplitude 0.25. Both installed
27 passes and padded/restored all 320 meshes with a clean exit. PID 19400
recorded 12,800 IA patches, 12,800 hull invocations, 243,200 domain invocations,
135,954 clip primitives and 1,623,356 pixel invocations. The user confirmed
"Ground stayed fixed" after the corrected camera-motion test. This is initial
visual acceptance of the movement fix, not full terrain qualification.

The post-run Windows verifier passed patch-config identity and latest-session
stale-config checks, but failed updater precedence: this branch's shim version
1.0.0.34 is older than the installed mod's bundled 1.0.0.46. Use full redeployment
before subsequent tests; this checkpoint does not bump a release version.

Remaining qualification includes controlled moving-camera image comparisons, terrain
overlaps/cluster edges, slopes and foundation/bridge/water contacts, height-only
deformation, full rebuilds, mission hops, auxiliary passes, device recreation,
GPU cost, and Steam/Proton/Wine. Fixed factor 4 is expensive; distance-based
subdivision and material-specific art remain future work. The small amplitude
limits visible gameplay-surface mismatch but cannot eliminate it.
