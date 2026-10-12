# Native terrain geometry for DXR diagnostics

Development checkpoint, 2026-10-12, `agent/dlss-rt-bridge`. The DXR diagnostic
can now trace an owned native terrain snapshot in addition to the mesh derived
from visible depth. The live presenter still uses depth geometry only. This
checkpoint is static capture/replay, not live complete-scene ray tracing.

## Capture and replay

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 60 `
  -NativeTerrainSnapshot -VisibleRayTracing
python tools/frame_bridge/Prepare-RT-Capture.py build/game-bridge-<run>
./build/frame-bridge-x64/Release/frame_bridge_visible_rt_gpu_tests.exe `
  build/game-bridge-<run>/rt-capture-input.bin build/game-bridge-<run>/depth-only-ao.rgba
./build/frame-bridge-x64/Release/frame_bridge_visible_rt_gpu_tests.exe `
  build/game-bridge-<run>/rt-capture-input.bin build/game-bridge-<run>/native-terrain-ao.rgba `
  build/game-bridge-<run>/native-terrain.bin
```

The default-off process variable `OPENSHIM_TERRAIN_GEOMETRY_EXPORT` requests a
new absolute output path. After 120 game-thread render observations following
terrain selection, the existing hash-qualified terrain adapter captures all
sixteen clusters in that selected zone. Every cluster must pass its existing
mesh-name, operation, buffer-count, stride and index-range guards. No new patch
site is introduced. The exported Ogre full-node-transform and released DX11
index-buffer getter use the same exact Ogre/renderer gates as other terrain
adapters. Native index buffer vtable identity is checked before readback.

The actual vertex declaration must specify POSITION0 from slot zero, offset
zero, FLOAT3 or FLOAT4, and TEXCOORD1 from slot two, offset zero, FLOAT1. The
terrain vertex shader replaces object Y with that height stream. FLOAT3 gets
the same implicit W=1 as the D3D input assembler. Actual index bytes select the
vertices, and the full node transform converts them into world coordinates.
Transforms and output positions must be finite/bounded; unsupported layouts
decline. An undisplaced base-terrain run is required. Meshes, materials, native
height/collision data and resource bindings are read only.

Readback stalls the game thread once and is a diagnostic, not a shipping
per-frame architecture. The binary contains a fixed 48-byte little-endian header
and expanded float3 triangle vertices. PID, mission generation, cluster/count
limits, payload FNV-1a integrity and finite world bounds are checked by the
reader before use. Initial mission generation zero is valid when the adapter
starts after RUN_STARTED. No pointers or Ogre/COM lifetimes cross the file.
The JSON companion records mesh names, transforms, height extrema and limits.
These game-derived files remain ignored local artifacts, never public assets.

## DXR ownership and coordinate contract

`VisibleRayTracing::SetNativeGeometry` validates and owns an immutable copy of
the snapshot before recording begins. Its native BLAS uses expanded world
triangles; the ordinary depth BLAS remains in view coordinates. The TLAS has
one depth instance transformed by inverse camera view and an optional identity
native-world instance. Ray origins/directions use the same inverse-view matrix.
Camera views must be rigid to preserve the meter-based radius/bias contract.
The native BLAS builds once; the depth BLAS/TLAS rebuild per record. Upload data
and acceleration structures remain helper-owned for the entire recording life.
The caller must complete the prior submission before rewriting instance data.

Microsoft's [DXR specification](https://microsoft.github.io/DirectX-Specs/d3d/Raytracing.html)
defines the triangle buffers, instance transforms, resource states and build
ordering used here. These APIs do not establish game-specific geometry/camera
alignment; that requires separate captured and analytic evidence.

## Evidence

- All 107 Win32 Release CTest tests pass. New native snapshot tests reject
  corrupt/truncated/oversized/nonfinite payloads and trailing bytes, and cover
  exact float/PID/count roundtrip and initial generation zero.
- All seven x86 and ten x64 helper/GPU tests pass. Hardware DXR preserves a
  single plane and coarse distant D24 plane, shades an analytic corner, and
  shades an explicit native wall absent from depth (45576 pixels darkened by
  more than two levels). Camera/world translation differs by at most one SDR
  step; rigid rotation produces identical output.
  Adding duplicate coplanar native triangles produces no false self-occlusion.
- GOG `misn03`, PID 8592, local `build/game-bridge-20261012-170604-679/`:
  exported 16 clusters, 614400 expanded vertices / 204800 native triangles in
  a 7372848-byte binary. The companion imported 60 1600x900 frames and executed
  depth-only DXR on 57 matched frames. All 60 deployment/config hashes restored
  after graceful exit zero. Snapshot and frame capture are separate observations
  in the same mission, not a synchronized live geometry transport.
- Exact-frame hardware replay compared depth-only AO with depth-plus-native AO.
  Native geometry changed/darkened 7308 pixels by more than two levels, maximum
  channel change 57; alpha was unchanged, with no brighter pixels over two.
  102611 native triangles were entirely outside at least one camera clip plane.
  The labeled comparison was visually inspected. This establishes that the
  native snapshot is not merely a copy of current depth coverage, not that each
  changed pixel comes from an offscreen occluder or that artistic acceptance is
  complete. General smoke/HUD opacity is still unqualified.
- First export declined on an assumed FLOAT4 W; explicit native declaration
  inspection corrected FLOAT3 input expansion. A second attempt declined the
  legitimate initial generation zero and its bridge lost depth/camera inputs;
  neither is counted as a qualified native replay. All files restored safely.

## Remaining work

The snapshot covers one selected native zone, not all loaded or offscreen map
geometry. It omits buildings, vehicles and particles. There are no live dirty
generations, deforming terrain updates, device/session reconnects or a transport
matching geometry to frame lifetime. Base triangles omit procedural/authored
domain relief. Normal/material/opacity data, direct-light direction and linear
lighting are still missing. The effect remains AO, with no ray-traced sunlight
shadows, reflections, GI or denoiser. Camera origin conventions and broad moving
camera/terrain-deformation acceptance require further qualification before a
live native geometry option is exposed. No FPS or latency gain is claimed.

The next integration must publish owned geometry with mission and dirty IDs,
retire old data on map/device changes, and compare ray geometry against native
raster surfaces before enabling new shadow modes. Windows/GOG is the captured
lane; Steam, Proton/Wine and release packaging remain unverified. No native
geometry assets or SDK binaries are shipped by this checkpoint.
