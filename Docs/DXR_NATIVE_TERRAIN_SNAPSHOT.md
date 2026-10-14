# Native terrain geometry for DXR diagnostics

Development checkpoint, 2026-10-12, `agent/dlss-rt-bridge`. The DXR diagnostic
can now trace an owned native terrain snapshot in addition to the mesh derived
from visible depth. A new default-off live presenter path also consumes
revisioned selected-zone snapshots under a per-frame validity lease. Static
replay and the live prototype remain distinct from complete-scene ray tracing.

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

Static readback stalls the game thread once and is a diagnostic, not a shipping
per-frame architecture. The binary contains a fixed 48-byte little-endian header
and expanded float3 triangle vertices. PID, mission generation, cluster/count
limits, payload FNV-1a integrity and finite world bounds are checked by the
reader before use. Initial mission generation zero is valid when the adapter
starts after RUN_STARTED. No pointers or Ogre/COM lifetimes cross the file.
The JSON companion records mesh names, transforms, height extrema and limits.
These game-derived files remain ignored local artifacts, never public assets.

## Live selected-zone prototype

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 240 `
  -NativeTerrainLive -NativeTerrainRefreshProbe
```

`-NativeTerrainLive` requests base terrain and hardware DXR. Its process flag
`OPENSHIM_TERRAIN_GEOMETRY_LIVE=1` accompanies the export prefix. Immutable
snapshots use `<prefix>.g<revision>.bin`; the process-lifetime revision never
resets on a mission owner reset. Old artifacts stay local for diagnostics and
are never implicitly reused. Readback is repeated only after invalidation and
120 new render observations. This settling interval is experimental and is not
a measured streaming/performance policy.

The producer and helper share a separate 80-byte V2 named mapping and named mutex
under `Local\\OpenShim.NativeGeometry.v2.<pid>`. Header fields are copied under
the mutex; Ready and the refresh request use Win32 interlocked operations.
Readers/publishers use zero-timeout mutex acquisition. Busy access and abandoned
reads decline; a publisher may reinitialize abandoned state before publication.
Invalidation clears Ready independently of the mutex before engine
zone rebuilding. The mapping contains PID, mission generation, revision,
payload hash, triangle count, QPC frequency, the earliest valid camera QPC and
an optional unit world-space direction toward the game's sun;
it contains no paths, pointers, COM objects or geometry bytes. The color/depth
mailbox remains V5 and unchanged.

All sixteen selected-zone full/height/next-height dirty bytes are checked before
the existing native zone-processing call. A dirty/unreadable entry invalidates
the lease. Selected-zone reconstruction and mission-owner reset invalidate it
as well. New snapshot/metadata files close before the producer prepares a Ready
publication. Missing API/build/layout guards retain depth-only fallback.
Changes to the captured sun direction or its validity also invalidate the lease.

The helper accepts only recognized camera-for-shaders frames with camera QPC
at or after snapshot validity, correct capture ordering and matching QPC clock
frequency. It verifies file/header PID, mission generation, count and hash, then
rechecks publication after I/O. Busy, stale, invalid or missing leases disable
native geometry for that frame. Malformed payloads fail that revision. Native
BLAS replacement/retirement occurs only after the preceding helper/SDK GPU work
has completed. Depth-only rays continue while a fresh snapshot is pending.
Native resources remain private to the helper and are released on its exit.

The optional refresh probe requests a new revision after thirty native ray
frames. The producer invalidates and captures again without changing gameplay
terrain. This tests fallback/reload of the real live geometry path; it is not a
terrain deformation or mission-switch test. `native-live-report.json` requires
fresh export evidence, clean exit, actual native ray frames and a valid final
native capture; the probe additionally requires invalidation and two loads.

Win32 [interlocked exchange](https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockedexchange)
and [mutex wait](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject)
contracts underpin this cross-process publication. No compatibility claim is
inferred for Wine/Proton from native Windows tests.

## DXR ownership and coordinate contract

`VisibleRayTracing::SetNativeGeometry` validates and owns an immutable copy of
the snapshot before recording begins. Its native BLAS uses expanded world
triangles; the ordinary depth BLAS remains in view coordinates. The TLAS has
one depth instance transformed by inverse camera view and an optional identity
native-world instance. Ray origins/directions use the same inverse-view matrix.
Camera views must be rigid to preserve the meter-based radius/bias contract.
The native BLAS builds once; the depth BLAS/TLAS rebuild per record. Upload data
and acceleration structures remain helper-owned for the entire recording life.
The caller must complete the prior submission before rewriting instance data
or replacing/clearing native geometry. The live helper already drains its
command and SDK queues before the next frame's geometry decision.

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

Live follow-up: all 108 Win32 Release tests, eight x86 helper tests and eleven
x64 helper/GPU tests pass. New tests use an actual child process to read Ready,
decline mutex contention, observe invalidation, consume a refresh once, read
revision two and observe publisher shutdown. Pure tests reject foreign PID,
old camera timestamps, inconsistent capture ordering/clock domains and invalid
headers. Hardware DXR tests replace a real BLAS and retire it after GPU
completion; old occluders disappear and depth-only output is restored.

GOG misn03 PID 29556, local `build/game-bridge-20261012-175414-392/`, imported
240 1600x900 frames. DXR executed on 212 matched frames; 205 used the native
204800-triangle zone and seven used depth-only fallback. The refresh probe
invalidated revision one, exported/reloaded revision two and ended with a
valid native final frame. The two snapshot hashes were identical, confirming
this was renewal of unchanged terrain, not proof of deformation support.
Mission teardown logged revision-two invalidation. Exit code was zero and all
60 deployment/config hashes restored. The live capture and same-frame
original/processed comparison were inspected; AO darkened 47343 pixels by more
than two levels, maximum channel change 72. This compares original raster with
combined depth/native AO, not the incremental native-only contribution.

## Terrain sunlight ray preview

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 120 -TerrainShadows preview
# Color diagnostic: green = matched sunlit terrain, magenta = terrain blocks sun.
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 120 -TerrainShadows mask
```

Both modes imply native live terrain, matched scene/depth/camera capture and a
visible separate DX12 window. Ordinary game presentation remains original.
`--rt-terrain-shadows preview|mask` is the helper option, requiring an absolute
live geometry prefix. No shipped INI/UI setting or release payload enables it.

The adapter reuses the existing `TerrainMasterLight` engine row. Exact Ogre
SHA-256 and the exported Light primary ShadowCaster vtable/type guard each
read. The released sun constructor sets directional type and light direction;
the exported `getDerivedDirection` supplies Ogre world coordinates. Rays use
its negation, not the differently handed game sun-sprite global. Static Ghidra
analysis established constructor/vtable/export semantics; live GOG PID 45868
read unit toward-sun `(0.819152117, 0.573576510, 0)`. No raw address or new hook
was introduced. The V2 lease transports the captured vector and invalidates if
it changes or becomes unavailable; geometry binary V1 and frame mailbox V5 stay
unchanged. The versioned mapping name avoids mixing the older 64-byte ABI.

A primary camera ray against native instance mask 2 must match captured depth
within a bounded bias/quantization tolerance. The native triangle supplies its
geometric normal. Only matched, frontlit terrain receivers launch a 512-meter
sun visibility ray, again against native mask 2. The visible depth mesh cannot
cast these shadows. Missing sun/geometry and mismatched receivers decline.
The bias is 5 cm. A follow-up derives a bounded within-pixel MSAA depth tolerance
from the native plane and neighboring projection rays; normal/material detail
and general silhouette coverage remain unqualified. See the building replay
reference below for the matching correction and hardware evidence.

Preview multiplies the existing SDR raster lighting by 0.55 on blocked matched
receivers, alongside AO. This is an artistic preview: ambient/direct light are
not separated and existing raster shadows may be multiplied twice. Mask mode
disables AO while showing matched lit/blocked coverage. Its colors are debug
information. Geometry outside the selected zone cannot block sunlight, so a
green pixel establishes no hit in captured geometry, not whole-map visibility.
The final HUD difference mask is still approximate; alpha is retained.

Hardware analytic tests establish an offscreen wall eight meters from the
receiver casting onto 24816 pixels, with identical magenta blocked coverage,
unchanged exposed half, no native-plane self-shadow and no shadow on mismatched
receivers. Missing/invalid sun, alpha/HUD retention, world camera rotation and
translation pass. Translation changes only the 193 pixels lying exactly on
the hard-shadow boundary. All 109 native, eight x86 and eleven x64 helper/GPU
tests pass, and the Win32 Release shim builds.

GOG `misn03`, PID 45868, `build/game-bridge-20261012-181307-609/`, completed
120 1600x900 imports and 106 live native-terrain sunlight ray frames. It exited
zero and restored all 60 deployment/config hashes. A precise same-frame
pre-overlay replay visibly marks 350887 matched sunlit terrain pixels and zero blocked
pixels. The base view is exposed: new terrain sun shadows add no appreciable
change there. The inspected debug coverage and cropped original/AO comparison
explain why this view still looks similar; buildings/vehicles cannot cast
native sunlight shadows yet. This is executed ray work, not a claimed visible
terrain-shadow improvement at that pose.

The first sun run declined because a nonexistent simple Light vtable export
was requested; the released constructor exposed the correct primary table and
the next run passed. A later `misn01` attempt exported terrain/sun but could not
open the color mailbox and is not a qualified image capture. A further launch
was refused while another user game was active; it was left untouched.

Replay packaging now takes the nine-digit camera from matched depth metadata,
checks camera/QPC/pass identity, and offers `--scene-only` to inspect the actual
pre-overlay scene without final HUD pixels. The camera writer always preserves
float round-trip precision. Packaging tests pin precision, row orientation,
scene/final selection and mismatched-camera rejection. `Compare-RT-Captures.py`
provides original/processed crops and an explicitly amplified pixel delta;
the before/after colors are not graded to exaggerate the comparison.

## Remaining work

The live snapshot covers one selected native zone, not all loaded or offscreen
map geometry. [Building shadow replay](DXR_BUILDING_SHADOW_REPLAY.md) now adds
captured stock building poses as occluders in a frozen diagnostic; these are not
live leased casters. Vehicles and particles remain omitted, although visible
depth may contribute some opaque surfaces. Dirty/mission invalidation and
revision publication are implemented; real deforming terrain, mission cycling,
device/session reconnects and broad moving-camera qualification remain open.
The prototype uses diagnostic file I/O and one selected zone, not a production
geometry transport. Base triangles omit procedural/authored
domain relief. Normal/material/opacity data and linear direct/ambient lighting
separation are still missing. Terrain sunlight rays are available only as the
partial preview above; full-scene shadows, reflections, GI and a denoiser remain
absent. Camera origin conventions and broad moving
camera/terrain-deformation acceptance require further qualification before a
live native geometry option is exposed. No FPS or latency gain is claimed.

The next integration must qualify actual deformation/mission/device retirement,
cover native objects and further zones, and qualify receiver/MSAA/opacity and
lighting replacement before enabling gameplay shadows. Foreign/custom material
geometry behavior is not qualified by these captures. Windows/GOG is the captured
lane; Steam, Proton/Wine and release packaging remain unverified. No native
geometry assets or SDK binaries are shipped by this checkpoint.
