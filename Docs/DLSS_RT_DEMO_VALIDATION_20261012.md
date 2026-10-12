# Experimental Battlezone DLSS Frame Generation and DXR AO demo

Native Windows/GOG checkpoint: 2026-10-12, branch `agent/dlss-rt-bridge`.
This is a separate DX12 preview of actual game frames. The original Win32
game still renders and presents; this is not a supported gameplay mod or a
production-quality DLSS integration.

## Requested, effective and observed behavior

| Feature | Requested setup | Observed behavior | Limit |
|---|---|---|---|
| DLSS Frame Generation | Optional local Streamline 2.14.1 SDK; signed development runtime; one generated frame | RTX 5080 support check succeeded; 176 extra SDK presentations across 180 real helper Present calls; final status zero | Camera-only motion; helper-only Reflex; generated-frame count not independently measured |
| Ray tracing | Optional inline DXR visible-depth AO | 176 frames executed GPU mesh construction, BLAS/TLAS building and eight-ray AO | Only geometry in current depth; no complete materials, hidden geometry, denoising, reflections or GI |
| Scene/depth/camera | V5 wire; pre-clear ordinal 3; before-overlay scene boundary | 176 valid and four missing input frames; PlayerCam shader projection; 8x D24/S8; 1266x513 | Manual boundary and HUD policy are not generally qualified |
| Window recording | WGC restricted to the helper's own HWND | 342 captured output frames encoded to a visually inspected 12.27-second video | Capture count and encoded FPS are not a generated-frame count or benchmark |
| Input recording | Owned renderer readbacks and per-frame SDK counters | Separate 360-input-frame run encoded to a labeled 25.05-second video | Input readbacks do not capture generated images |

The optional features default off. No SDK binaries, game-derived captures or
recordings are included in Git or the release/deployment bundle. Development
SDK DLLs are copied into a private run directory; NVIDIA's embedded interposer
signature is verified before loading. The diagnostic `runWhenNoFocus` option
does not qualify production focus behavior. The project GUID is an experiment
identifier, not a registered NVIDIA application ID.

## Current local demo evidence

The final GOG `misn03.bzn` window recording is stored locally under
`build/game-bridge-20261012-092036-403/`:

- `dlss-fg-report.json`: 180 real Present calls, 176 SDK extra presentations and
  multi-present calls, final status zero, four history resets/missing inputs.
- `game-dxr-ao.bmp.json`: 176 traced frames, 323584 triangle capacity and eight
  rays per surface pixel, with explicit geometry/HUD qualification limits.
- `demo-window.bzrvid`: 342 timestamped frames from only the helper's own window.
  The encoded `build/battlezone-dlss-dxr-window-demo.mp4` is 12.27 seconds;
  a representative frame and the clip were visually checked.
- `shader-camera-trace.summary.json`: 30 clean frames, seven variants, 7737
  linked draws, 536 object-transform groups, 368 single-transform candidates
  and 22 changing groups. No read errors or overflow; lifetimes remain unqualified.
- `restore-manifest.json`: all 60 deployment/config files matched their original
  SHA256 values after graceful game exit.

The separate full-resolution renderer-input run is stored locally under
`build/game-bridge-20261012-091652-814/`:

- `consumer.log`: 360 imported frames, 350 DXR frames, 323584 triangle capacity,
  eight rays per surface pixel, matched final color/depth/camera/scene captures.
- `dlss-fg-report.json`: 360 real Present calls, 350 SDK-reported extra
  presentations and multi-present calls, final status zero, 11 history resets,
  10 missing input frames. Maximum capability was five generated frames;
  the experiment requested only one.
- `game-dxr-ao.bmp` and its JSON: hardware AO output and explicit geometry/HUD
  qualification limits. `game-frame.bmp` is the matched raster baseline.
- `demo-rendered.bzrvid`: timestamps, monotonic captured frame IDs, SDK counts,
  current RT/FG flags and owned BGRA input images.
- `restore-manifest.json`: all 60 deployment/config files matched their original
  SHA256 values after graceful game exit.

The encoded artifact is `build/battlezone-dlss-dxr-demo.mp4`, with explicit
renderer-input labeling and a JSON sidecar. The video was visually inspected.
It shows the actual game rendering, AO output and changing SDK counters. It
does not show independently captured generated images or establish FPS gains.

Earlier combined GOG validation imported 600 frames, reported 550 extra SDK
presentations and executed 550 DXR frames. Its matched raster/AO image comparison
changed 11484 of 649458 pixels by more than two channel levels, with maximum
darkening 52. This establishes executed AO without establishing a generally
correct HUD mask or lighting model.

## Integration checks

Shared inputs are copied into owned helper textures before releasing the
single-slot GPU mailbox. The helper waits for GPU reads and drains its presenting
queue after Present before reusing those SDK inputs. It never passes game
pointers to the x64 process. Resize or device replacement disables the native
capture rather than reusing stale resources.

DLSS receives a helper frame token, pixel motion normalized with `1/width` and
`1/height`, raw depth, matched scene color, projection/inverse projection and
current/previous clip transforms. Ogre column-vector transforms are transposed
for Streamline's row-vector convention. The GPU camera-motion test checks every
pixel against analytic perspective motion, including sky rotation, offscreen
vectors and invalid depth. Missing or incompatible inputs disable FG; history
loss resets temporal transforms. There are no object/skinning motion vectors or
authoritative engine camera-cut events.

Reflex/PCL markers cover the helper's loop. They do not cover Battlezone's
simulation, input sampling or native render submission. The conservative HUD
difference mask can be confused by FXAA and postprocessing; it is not a qualified
UI alpha channel. AO can darken already shaded raster lighting. The visible-depth
mesh rejects invalid depth and large discontinuities but cannot provide hidden
or offscreen occluders.

## Validation and known failures

- Win32 Release build and all 101 native CTest tests passed, including the real
  cross-thread patcher and concurrent detour-publication regression.
- All six x86 and eight x64 helper tests passed, including hardware DXR and GPU
  motion. A separate build with no Streamline/DXR/WGC also succeeded.
- Ten transport lanes verified 2000 color frames, 1200 depth/camera pairs and
  600 scene pairs, including reconnects, MSAA, odd sizes, RGBA and BGRA.
- A full-size helper preview covering the source game caused a one-frame
  transport timeout while game simulation continued. A smaller on-monitor
  preview completed the recorded run; the swapchain retains source resolution.
- Earlier full-size live previews received zero WGC frames and failed explicitly.
  The final smaller preview recorded 342 live output-window frames. The separate
  readback fallback labels its input images. Neither recording's capture/encoded
  count is treated as an independently measured generated-frame count.
- A production-runtime live run reported zero generated presentations after
  the foreground request was denied. The explicit development mode subsequently
  demonstrated generation without repeated focus stealing.

Input/focus/Alt-Tab behavior, end-to-end latency, pacing, visual interpolation
quality, dense object motion, camera cuts, complete HUD/material/geometry
coverage, gameplay presentation takeover and Steam/Proton/Wine remain open.
Reproduction commands are in [the frame bridge guide](DLSS_RT_FRAME_BRIDGE.md).

## Cinematic DX12 follow-up

An optional preset adds SDR scene bloom, depth haze and exposure/contrast/
saturation grading. Its four compute passes extract/blur half-resolution scene
highlights and composite the processed scene. It can run independently of
Streamline/DXR. With both enabled, it processes the AO scene and supplies the
enhanced scene to DLSS, preserving the private-resource completion boundaries.

The follow-up live run is `build/game-bridge-20261012-110749-944/`: 180 imported
1280x681 frames, 166 effective cinematic/DXR frames, 166 extra SDK presentations,
14 missing input frames and final DLSS-G status zero. The labeled input recording
encoded to `build/battlezone-cinematic-demo.mp4` (13.73 seconds). Its captured
frames and matching `game-cinematic.bmp`/`game-cinematic-scene.bmp` were visually
inspected. `build/battlezone-cinematic-before-after.png` compares the same scene
frame before HUD; a separate HUD comparison is retained. The scene/final outputs
changed 418681/190855 pixels by more than two levels. All 60 deployment/config
files were restored after graceful exit.

Nine x64 helper/GPU tests and 101 native regressions passed. The new hardware
test checks neutral RGBA/BGRA inputs, distinct HUD and alpha, near/far haze,
NaN/sky exclusion, bloom halos/history clearing, color grading, smooth handling
of small raster differences and nonfinite parameter rejection. A standalone
90-frame headless cinematic smoke passed without Streamline/DXR, exercising
both scene and final readbacks plus recording; its synthetic producer exited
on its own deadline.

These are artistic SDR effects. Haze is not derived from authoritative mission
atmosphere/lighting. Final compositing uses a smooth scene/final difference mask
and adds the effect delta to the original raster pixels to retain FXAA detail.
General HUD opacity, transparent smoke and depth silhouettes remain unqualified;
visible artifacts remain around some smoke/silhouette regions. WGC returned zero
frames in the first cinematic run with SDK display-query errors; the labeled
renderer-input fallback subsequently passed. No output-window video is claimed
for this preset run, and no generated-frame or FPS count is inferred from it.

## Geyser and washed-building correction

The annotated cinematic capture exposed self-shadow flecks in the geyser and
excess nearby haze. AO-only isolation reproduced the flecks. Ray origins were
derived from full-resolution depth while the BLAS used two-pixel triangles;
coarse geometry and D24 quantization could place origins behind their own mesh.
The revised shader projects origins onto the traced triangle plane, uses a
depth-dependent eight-step quantization offset, bounds mesh edge size against
the AO radius, and declines unstable depth neighborhoods. This sacrifices
under-resolved/edge contact AO rather than treat it as reliable opacity data.

On the exact previous 1280x681 capture, hardware replay reduced geyser-crop
pixels darkened more than five channel levels from 443 to three, with maximum
darkening 149 to eight. `build/geyser-ao-fix-isolation.png` shows original,
previous AO and revised AO from that same capture; its crop is `(890,280)` to
`(990,420)`. This is an offline GPU replay, distinct from live validation.

Haze starts at 120 view units with density 0.00035 and maximum blend 0.25. The
marked buildings were approximately 62–66 units away and are now outside its
effect. These are artistic view-space settings, not calibrated atmospheric units.

The live validation run `build/game-bridge-20261012-114439-494/` imported 181
1280x720 frames, executed cinematic/DXR on 166, reported 166 extra SDK presents,
and ended with status zero and 15 missing input frames. The harness waited one
frame beyond the requested 180 for valid final inputs. Matched original/enhanced
scene and final images were inspected; the geyser's heavy flecks were absent in
the inspected frame and nearby building contrast was retained. The labeled input
recording encoded to `build/battlezone-geyser-fixed-demo.mp4` (13.93 seconds).
The same-frame scene/building comparison is
`build/battlezone-geyser-building-fixed.png`. All 60 deployment/config hashes
were restored after graceful game exit.

Nine x64 helper/GPU tests and 101 native regressions passed, along with a no-SDK
build. A new D24-quantized distant-plane fixture checks false self-occlusion;
the near-corner fixture retains hardware occlusion. Additional haze checks cover
the near exclusion distance and maximum cap. This corrects the observed artifacts
through conservative depth confidence and preset tuning; it does not qualify
general particle opacity, HUD alpha or physically correct atmosphere.

## Scene-layer reference milestone

The bounded material/draw probe now records exact D3D11 blend/depth policies,
color target/sample layout, pixel shader identity and exported Ogre pass/material
names. Ordered observations cover three frames within the normal 30-frame trace.
Names are copied while getters are valid; native material object offsets are not
read. String ABI decoding is bounded and checked against PlayerCam. Analysis
keeps opacity and opaque-scene qualification false.

The normal GOG trace `build/game-bridge-20261012-121444-414/` completed 30 frames
with seven variants, 7145 linked draws, 499 transform groups, 714 ordered draws,
zero errors/overflow, and checked string decoding. Each sampled main-view frame
had 140 depth-writing draws after its first world-effect candidate. Terrain
atlas/glow blending, sky and smoke therefore cannot be separated by a generic
first-blended-draw snapshot.

The explicit reference run `build/game-bridge-20261012-121245-883/` imported 120
1600x900 frames and logged at least 23700 omitted effect draws over the whole
launch. It intentionally suppresses qualified main-view `DrawIndexed` calls of
the bound `Effect_fragmentHLSL4` delegate, after matching its actual PS binding,
depth/blend/target/viewport policy and excluding identity HUD. Inspection showed
geyser smoke absent while terrain/buildings/sky/cockpit and HUD remained.
The ordinary run imported another 120 frames with smoke present and no omitted
draws. Both restored all 60 files with hashes after graceful exit.

`build/battlezone-scene-layer-reference.png` compares these separate runs. It
establishes a reference for further work, not an authoritative opacity mask,
complete opaque render product or playable enhancement. There is no separate
transparent layer yet. The reference harness rejects FG/DXR/cinematic/Frida
combinations, requires actual suppression evidence and emits explicit limits.

All 103 native tests and script syntax checks passed. The native predicate
declines ordinary gameplay, depth-writing terrain/glow, identity HUD, unmatched
shaders, unknown programs and unsupported target/blend policies. Layer-analysis
tests distinguish those classes and reject unchecked observations. Initial
reference attempts safely omitted no draws because material program names differ
from concrete bound HLSL delegate names; the exact delegate identity was then
observed and validated. DLL identity pins limit this to the qualified native GOG
build; Steam/Proton/Wine and other missions remain unqualified.

## Native terrain plus DX12 preview checkpoint

The bridge harness now has an explicit, default-off `-TerrainMicroRelief`
lane, reusing the existing native terrain implementation rather than modifying
the DX12 depth mesh to imitate terrain detail. Fixed factor 4 and procedural
displacement amplitude 0.25 were exercised on GOG DX11 `misn03`, with the
optional DXR AO, cinematic preset and signed development DLSS-G runtime.

Qualified local run `build/game-bridge-20261012-123033-433/`, PID 67844:

- The native `MN_DETAIL_ATLAS` material accepted 27 specialized passes and
  padded 144 terrain mesh bounds. Runtime VS/HS/DS linkage was audited.
- A visible native terrain submission recorded 12800 input patches, 12800
  hull invocations, 243200 domain invocations, 33801 clipped primitives and
  14404 pixel invocations. This is one sampled cluster, not a frame-wide
  triangle count or performance measurement.
- The companion imported 120 1280x720 frames. It used 111 matched input frames
  for DXR AO and cinematic effects; nine lacked inputs. DLSS-G reported 111
  extra SDK presentations, with final status zero and ten history resets.
  Camera-only motion and helper-only Reflex remain unchanged.
- Frame 120 scene, enhanced scene, final and depth captures were saved. The
  enhanced scene was visually inspected: terrain, structures, geysers and
  cockpit remained visible. These images do not establish a pixel-aligned
  untessellated-versus-tessellated comparison or generated-frame quality.
- Graceful shutdown returned code zero. All 27 material passes, all 144 padded
  bounds and all 60 deployment/config files were restored. The report only
  accepts this launch's PID-tagged installation, visible GPU statistics and
  complete restoration evidence.

All 103 existing CTest regressions passed. The shader compiler/linkage script
passed 110 shader compilations across ten eligible terrain permutations, factors
1/2/4 and micro-relief variants. Script parsing and incompatible
particle-reference/terrain option rejection passed without another game launch.
Replaying the final validator with another PID's otherwise-valid GPU/cleanup
log also rejected the capture without emitting a qualification report.
An initial combined capture rendered and restored correctly but was rejected
by the new exit-code gate: the launch wrapper returned `Get-Process` without
retaining its handle. The harness now opens the process handle while alive and
records the exit code after graceful shutdown; only the rerun qualified.

`terrain-bridge-report.json` deliberately marks adaptive subdivision, material
height maps, full geometry export and performance qualification false. This
adds a reproducible combined demo, not a new production tessellation renderer.
The domain shader adds small procedural relief; it does not smooth large-scale
terrain or change gameplay collision. DXR still reconstructs visible depth
rather than consuming native hull/domain output or offscreen terrain geometry.
See [DLSS_RT_TERRAIN_AND_MATERIAL_PLAN.md](DLSS_RT_TERRAIN_AND_MATERIAL_PLAN.md)
for the next implementation and acceptance gates.

## Adaptive terrain checkpoint

The default-off native adaptive hull policy now measures shared projected
edges using the current pass's viewport. It requests fractional-even factors
2..4 with a bounded pixel target, preserving fixed displacement phase. Its
new float4 parameter is validated and bound through hash-qualified exported
Ogre APIs to the public viewport-size auto constant. Fixed modes remain integer.
The harness's `-TerrainAdaptive` requires the factor-4 relief lane and records
actual requested policy, rasterization and restoration in the terrain report.

Local GOG `misn03` run `build/game-bridge-20261012-124653-034/`, PID 44252,
imported 120 frames at 1266x513. The sampled visible terrain draw had 12800
patches, 12800 hull invocations, 89600 domain invocations, 24872 clipped
primitives and 3358 pixel invocations. This is below the previous uniform
factor-4 sample's 243200 domain invocations for 12800 patches. Different
captures/targets and sampled clusters prevent an FPS or frame-cost comparison.
DXR/cinematic effects ran on 110 frames and DLSS-G reported 110 extra SDK
presentations, final status zero. Frame 120 images/depth were saved and the
enhanced scene was visually inspected. All 27 terrain passes, 144 padded bounds
and 60 deployment/config file hashes were restored; the game exited with zero.

The initial adaptive run `build/game-bridge-20261012-124422-365/` installed
and rasterized correctly, but its window changed size and the bridge failed
closed with `DXGI_ERROR_UNSUPPORTED`, leaving original game presentation active.
The companion could not connect to that disabled producer. Native resources
and all files restored; that run is not a qualified combined capture.

All 104 CTest regressions pass. The new WARP test executes the shipped GPU edge
policy with reversed endpoints, distance/resolution changes, degenerate edges,
NaN/Inf/extreme coordinates, zero/invalid viewport and behind-camera W values.
Actual fractional hull/domain draws cover a shared diagonal without raster
gaps and produce fewer domain invocations in the distant-detail case (36 vs
144 on WARP). The compiler/linkage script passes 150 shaders over ten terrain
permutations, including adaptive with/without relief. Script parsing and
unsupported adaptive flag/cap rejection also pass.

`adaptiveSubdivision=true` records this bounded prototype. Cross-cluster camera
motion acceptance, authored height maps, full geometry export and performance
qualification remain false. Long movement/deformation/viewport tests are still
required; matching synthetic endpoints does not prove native seams under every
floating-point transform. No generated-frame quality or FPS gain is inferred.

## Authored terrain normal-lighting checkpoint

`Build-TerrainSurfacePack.py` now consumes a live engine tile/atlas capture and
explicit single-channel linear height images. It produces a linear RGB normal
atlas with original base-mip borders and renormalized mips. Engine-index aliases
are reported; conflicts/partial rectangle overlaps, unknown IDs and escaped
source paths decline before publication. Physical slope units, 8/16-bit/float
height ranges and provenance are explicit. This does not emit geometry heights.

The default-off native surface path requires the original material and
diffuse/normal resource identities, compatible normal-mapped terrain programs
and a linear RGBA8 texture descriptor. Original textures are retained and only
our owned replacement bindings are restored. A read-only immediate-context
check compares actual PS t2 resource and SRV format during pipeline-statistics
samples. Capture qualification requires fresh visible GPU evidence and complete
normal restoration, in addition to the existing terrain cleanup gate.

The local test uses deliberately strong generated ridge height art over 13 used
Moon engine indices; this is diagnostic art, not a finished terrain pack.
The 1024x1024 atlas has 11 mip levels. PID 41680, run
`build/game-bridge-20261012-144809-425/`, imported 120 1268x513 frames, installed
six normal passes, and confirmed the actual resource at a visible draw with
104886 pixel invocations. PID 29072, combined run
`build/game-bridge-20261012-145351-651/`, imported 120 1266x513 frames, ran
DXR/cinematic effects on 105 and reported 105 extra SDK presentations, final
status zero. Its authored-normal sample had 151786 domain invocations and
17251 pixel invocations. Both runs restored six normal bindings, 27 tessellation
passes, 144 padded bounds and all 62 deployment/config files, with exit code zero.

The baseline/surface scene captures were visually inspected. Their comparison
shows changed terrain shading while buildings/sky/cockpit remain; these are
separate runs, not identical game/particle state. No FPS, generated-image quality,
full displacement or broad artistic/seam acceptance is inferred.

Wrong Mars diffuse identity on Moon, PID 53148 in
`build/game-bridge-20261012-152728-985/`, produced a fresh `no guarded
normal-mapped terrain pass` decline and installed no normal replacement. All
terrain resources and 62 files restored. The known game-window resize limitation
disabled its bridge before helper connection, so this is native rejection
evidence only. Earlier negative attempts failed before usable bridge capture;
they are not promoted to a successful capture or completed surface report.

Win32 Release build and all 105 CTest regressions pass, including seven
surface-authoring cases. Python/script parsing checks pass. The schema,
commands, limitations and next domain-resource requirement are documented in
[terrain-surface-materials.md](terrain-surface-materials.md). Height artwork
currently changes normals only; geometric relief remains procedural. Full
texture-driven domain displacement is not implemented.

## Texture-height GPU candidate and surface startup follow-up

The authoring tool now optionally emits a one-mip signed R32_FLOAT height atlas
in meters and a separate unqualified native-height manifest. Zero guard bands
precede its quintic taper. Conflicting floating-point heights on alias tiles
are rejected even when their RGB normal values quantize identically.

The shipped test shader has a default-inactive `OPENSHIM_HEIGHT_TEST` candidate.
Actual `TerrainDomain` execution and geometry stream output pass 96 Win32 WARP
runs: signed texture heights move geometry, retain base slopes, support rotated
and reflected UVs, and update normal/tangent/clip/depth/shadow-receiver outputs.
Camera translation, zero-border seams, degenerate UVs, invalid/missing heights
and unchanged PS resources are checked. All 160 shader/interface compilations
and 106 CTest tests pass (nine authoring cases). This is GPU geometry evidence;
the native game installer does not select the candidate or bind its resource.
No live texture-displaced game geometry, shadow casting or FPS gain is claimed.

A native control exposed a startup race: PID 40292, local
`build/game-bridge-20261012-155553-879/`, requested the staged normal texture
before `OpenShimEnhanced` registration. It retained original normals, captured
60 bridge frames, restored terrain and 62 file hashes, and exited cleanly. Its
surface qualification correctly failed. The installer now defers until the
existing resource group is initialized, retries on the game-thread render tick
with a 600-observation bound, and delays GPU samples until the actual normal
resource is bound. Real errors still finish the attempt for that mission.

The corrected Win32 Release build passed the follow-up control: PID 71268,
`build/game-bridge-20261012-160045-586/`, 120 frames at 1268x513 with 116 matched
depth candidates. Actual authored-normal binding and visible terrain produced
190036 domain and 104840 pixel invocations. All six normal bindings, 27 terrain
passes, 144 bounds and 62 deployment/config file hashes restored with exit zero.
The scene capture was inspected. This run exercises existing procedural relief
and normal mapping; DXR/DLSS were not requested. Its bootstrap happened before
terrain selection, so a deliberately delayed-bootstrap sequence remains to be
qualified separately.

The Enhanced fork parity command was run before shader work and reported 14
missing CR counterparts in the current sibling checkout. None of those 14
shared shaders were changed; only the separate terrain tessellation experiment
was extended. General CR shader parity is therefore unavailable, not passed.
GOG native and WARP evidence does not establish Steam/Proton/Wine compatibility.

## Native terrain DXR snapshot checkpoint

The new [native terrain capture/replay](DXR_NATIVE_TERRAIN_SNAPSHOT.md) exports
base position/height/index streams plus full node transforms from sixteen
selected-zone clusters. It imports these owned world triangles into a second
DXR BLAS alongside visible depth. Analytic hardware tests establish occlusion
from geometry absent from depth, with translated/rotated world-camera agreement.

PID 8592, GOG misn03, `build/game-bridge-20261012-170604-679/`, exported 204800
native triangles and completed 60 1600x900 game frames, 57 depth-only DXR frames,
graceful exit zero and all 60 file hash restorations. A paired frame-60 replay
with native geometry darkened 7308 pixels by more than two levels versus the
same depth-only AO, maximum channel change 57 and exact alpha preservation.
102611 captured native triangles lie outside at least one view clip plane.
The real labeled comparison was inspected. This is a static snapshot from the
same mission, not synchronized live native scene transport or full RT shadows.
All 107 native, seven x86 helper and ten x64 helper/GPU tests pass. Earlier
declined/invalid-input attempts are recorded separately in the snapshot doc.

## Live native terrain validity and renewal checkpoint

A separate 64-byte Win32 mapping/mutex publishes native snapshot PID, mission,
revision/hash/count and earliest valid camera QPC. The helper checks the clock,
frame ordering and snapshot ownership and rechecks after I/O. Native terrain
dirty flags, selected-zone construction and mission reset invalidate Ready;
renewed immutable files rebuild the native BLAS only after preceding GPU work
has completed. The ordinary V5 color/depth transport remains unchanged.

GOG misn03 PID 29556, `build/game-bridge-20261012-175414-392/`, imported 240
1600x900 frames. Hardware DXR processed 212 matched inputs; 205 used leased
native terrain and seven fell back to depth-only during renewal. A refresh
request after thirty native ray frames invalidated revision one, loaded
revision two and ended with a valid native final frame. Both geometry hashes
were identical: this is real renewal plumbing on unchanged terrain, not a
deformation test. Mission exit invalidated revision two, returned zero and
restored all 60 deployment/config file hashes.

The inspected original/live-AO comparison used the same captured frame 240.
Combined depth/native AO darkened 47343 pixels by more than two levels, maximum
channel change 72. It does not isolate the added native geometry contribution.
Native terrain coverage is still one zone and the UI/particle mask is still
provisional. All 108 native, eight x86 and eleven x64 helper/GPU tests pass,
including child-process lease contention/invalidation and hardware BLAS
replacement/retirement. Actual deformation, mission/device cycling, broad
camera movement, custom material geometry and Steam/Proton/Wine remain open.
