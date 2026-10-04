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
