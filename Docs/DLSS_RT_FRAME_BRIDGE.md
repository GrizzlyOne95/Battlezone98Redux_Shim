# Experimental DLSS / ray tracing bridge

Status: a local GOG/RTX 5080 companion preview runs **experimental DLSS Frame
Generation and hardware DXR ambient occlusion**. This is a renderer experiment,
not a playable presentation replacement or complete scene ray tracing.
Development branch: `agent/dlss-rt-bridge`, based on current `origin/main`
after checking open PRs and renderer history (2026-10-11).

## Architecture

Battlezone and its native load chain stay Win32/DX11. An opt-in OpenShim
presentation observer copies completed SDR color into a shared GPU texture.
A separately built x64 DX12 diagnostic helper imports it on the same adapter.
The helper verifies synthetic pixels, saves artifacts, and displays a preview.
An explicit Streamline build owns a proxy DX12 swapchain for frame generation;
an explicit DXR build traces rays against reconstructed visible depth geometry.
The normal game `Present` still runs. No input forwarding or presentation
takeover exists at this milestone.

This proves a route around the 32-bit in-process SDK boundary without replacing
Ogre or converting the game executable. Streamline accepts the helper's private
copies and reports additional presentations. Reflex markers and pacing describe
the helper, not the game simulation. Coordinated input/presentation, end-to-end
latency, dense object motion and full geometry remain feasibility gates.

## Current experimental demo

Local validation on 2026-10-12 used NVIDIA Streamline **2.14.1**, an RTX 5080,
GOG `misn03.bzn`, the shader-oriented PlayerCam projection, pre-clear depth
ordinal 3, and scene color before the first identity overlay `DrawIndexed`.
A combined run imported 600 actual game frames: the SDK reported **550 extra
presentations** across 550 multi-present calls, with last `DLSSGStatus=0`.
DXR AO ran on 550 valid frames, building up to 323584 visible triangles and
tracing eight hemisphere rays per surface pixel. Missing inputs switched FG off
for that frame; they did not reuse stale depth or camera data.
A subsequent recorded window demo imported 180 game frames, reported 176 extra
SDK presentations and executed 176 DXR frames. Windows Graphics Capture recorded
342 frames from the helper's own output window, encoded to a visually inspected
12.27-second clip. That capture count is not an independent generated-frame count.

Build optional features from an explicitly downloaded local NVIDIA SDK:

```powershell
cmake -S tools/frame_bridge -B build/frame-bridge-x64 -A x64 `
  -DFRAME_BRIDGE_STREAMLINE_SDK=C:/path/to/streamline-sdk-v2.14.1 `
  -DFRAME_BRIDGE_DXR=ON -DFRAME_BRIDGE_RECORD_WINDOW=ON -DFRAME_BRIDGE_GPU_TESTS=ON
cmake --build build/frame-bridge-x64 --config Release
# Production SDK: interpolation requires the preview to have focus.
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 240 `
  -StreamlineDirectory C:/path/to/streamline-sdk-v2.14.1/bin/x64 -VisibleRayTracing
# Explicit development diagnostic: stages signed development DLLs privately,
# enables the SDK's runWhenNoFocus option, and retains its watermark.
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 240 `
  -StreamlineDirectory C:/path/to/streamline-sdk-v2.14.1/bin/x64/development `
  -StreamlineDevelopment -VisibleRayTracing -RecordWindow -RecordFrames
python tools/frame_bridge/Encode-Window-Recording.py `
  build/<run>/demo-window.bzrvid build/<run>/battlezone-dlss-dxr-window-demo.mp4
# Optional full-resolution video of renderer inputs, explicitly labeled:
python tools/frame_bridge/Encode-Window-Recording.py `
  build/<run>/demo-rendered.bzrvid build/<run>/battlezone-dlss-dxr-inputs.mp4
```

Streamline and DXR options default off at build time. SDK headers, DLLs, logs,
recordings and game-derived images are local artifacts, excluded from release
and deployment payloads. Runtime loading checks NVIDIA's embedded signature.
Production mode loads the supplied runtime directly. Development mode stages a
private copy beside its report, writes plugin JSON there, and must not ship.
The helper never downloads runtimes. Its project GUID identifies this experiment,
not a registered NVIDIA game application ID or production approval.

`-RecordFrames` records the helper's GPU readback with frame IDs and SDK counters.
Its labeled video shows rendered **input frames**, not the SDK's generated
images. The helper's preview occupies at most half the primary work area's width
and height, leaving part of the source game visible: covering its whole window
caused a live source-rendering timeout while simulation continued. Its swapchain
and recorded readback retain the source resolution.
Optional `-RecordWindow` accepts only the helper's own HWND through
Windows Graphics Capture. Earlier full-size live previews received no WGC frames
and failed explicitly. The smaller preview recorded 342 live output frames in
the final combined run. Neither mode
captures the desktop. Both record timestamps, and the encoder samples that
timeline at 60 Hz. Encoded FPS and repeated images are
**not** a generated-frame count or pacing benchmark. The SDK report supplies
presentation evidence independently. Camera-motion-only FG can produce artifacts
on moving objects, animated pilots, particles, cockpit overrides and HUD edges.
HUDless color/postprocessing parity and the conservative difference mask are
not generally qualified. DXR only sees the current visible depth mesh: there is
no hidden/offscreen geometry, complete material data, ray-traced reflection/GI,
denoising or authoritative object/camera lifecycle yet.

## Build and reproduce

### Optional DX12 cinematic effects

`--visual-preset cinematic` / `Game-Smoke-Test.ps1 -VisualEnhancements` enables
three additional GPU effects: half-resolution separable bloom, distance haze
from reconstructed view-space depth, and exposure/contrast/saturation grading.
They are SDR raster post effects, not additional ray tracing, HDR reconstruction
or physically calibrated mission lighting. Bloom uses the captured scene before
the observed HUD boundary. The haze color/density is an artistic preset; clear
sky and invalid depth receive no haze. A power contrast curve preserves dark
detail instead of clipping shadows around a linear contrast pivot.

The pass runs after optional DXR AO and tags its processed scene to DLSS when FG
is requested. Outputs, bloom intermediates and original input copies are helper
owned; normal private-input/fence lifetimes still apply. Final compositing adds
an effect delta to the original raster image and smoothly attenuates it where
scene/final differences suggest HUD coverage, retaining the original FXAA
detail. This remains an approximate mask: low-opacity or identical-color HUD,
particles and depth silhouettes need engine-aware validation.

```powershell
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -Frames 180 `
  -VisualEnhancements -VisibleRayTracing `
  -StreamlineDirectory C:/path/to/streamline-sdk-v2.14.1/bin/x64/development `
  -StreamlineDevelopment -RecordFrames
# Also works without Streamline or DXR:
./tools/frame_bridge/Game-Smoke-Test.ps1 -Mission misn03.bzn -VisualEnhancements
```

The harness saves matched `game-frame.bmp`, `game-scene.bmp`,
`game-cinematic.bmp` and `game-cinematic-scene.bmp`, with effective frame counts
and qualification limits in `game-cinematic.bmp.json`. Direct helper options
`--capture-enhanced-bmp` and `--capture-enhanced-scene-bmp` permit headless
captures; use `--show` for the optional preview window.

Local follow-up validation imported 180 GOG frames at 1280x681, executed the
cinematic and DXR passes on 166 valid frames, and reported 166 extra DLSS SDK
presentations with final status zero. The matched scene comparison changed
418681 pixels by more than two channel levels; the final HUD view changed
190855. Actual image pairs and the 13.73-second labeled renderer-input video
were visually inspected. These counts establish effect execution, not general
visual correctness. The provisional depth/opacity assumptions still cause
artifacts around transparent smoke and some silhouettes.

All nine x64 helper/GPU tests and 101 native regressions passed. New GPU checks
cover every pixel of odd RGBA/BGRA neutral inputs, exact distinct-HUD/alpha
preservation, depth-dependent haze, clear/NaN depth, bloom spread and history
clearing, independent exposure changes and finite parameter rejection. A
90-frame x86-to-x64 cinematic run also passed without SDK/DXR or a helper window.
The combined game's 60 deployment/config files were restored and hash-checked.

WGC again received zero frames in the first cinematic live run while the SDK
logged display-configuration query failures. The subsequent renderer-input run
completed successfully. The earlier successful output-window recording remains
valid; smaller placement does not guarantee WGC availability in every desktop
context. Input recordings are explicitly labeled and do not independently
capture/count generated images.

### Transport build

From the repository root on native Windows with Visual Studio and Windows SDK:

```powershell
cmake -S tools/frame_bridge -B build/frame-bridge-x86 -A Win32
cmake --build build/frame-bridge-x86 --config Release
cmake -S tools/frame_bridge -B build/frame-bridge-x64 -A x64
cmake --build build/frame-bridge-x64 --config Release
# On a development machine with a suitable GPU, register lifecycle GPU tests:
cmake -S tools/frame_bridge -B build/frame-bridge-x86 -DFRAME_BRIDGE_GPU_TESTS=ON
cmake -S tools/frame_bridge -B build/frame-bridge-x64 -DFRAME_BRIDGE_GPU_TESTS=ON
ctest --test-dir build/frame-bridge-x86 -C Release --output-on-failure
ctest --test-dir build/frame-bridge-x64 -C Release --output-on-failure
./tools/frame_bridge/Smoke-Test.ps1
# Optional: also exercise the DX12 swapchain preview without activating it.
./tools/frame_bridge/Smoke-Test.ps1 -Show
# Target the analytic moving-camera lane during development:
./tools/frame_bridge/Smoke-Test.ps1 -Cases depth-motion
```

The smoke uses a **real x86 process** and x64 DX12 consumer. Each published
frame encodes its ID into a solid RGBA color. GPU readback checks every pixel
against the descriptor's frame ID, then tests a clean consumer reconnect. Both
single-sample and 4x MSAA resolve paths are exercised, plus odd-width RGBA/BGRA
readback and BMP channel/orientation checks. Synthetic sources exit
on a deadline; backpressure is verified after the consumer exits.

The plain helper reports hardware DXR capability separately from effective feature
state and prints `DLSS=not-integrated RT=not-integrated`. Optional preview modes
name their experimental state and emit SDK/DXR reports. Capture to
GPU-copy timing includes startup/attach delay and verification readback; it is
**not a gameplay latency measurement or a performance benchmark**.

## Game color capture (initial GOG qualification)

The plugin builds the same producer used by the synthetic test. Capture is off
unless `OPENSHIM_FRAME_BRIDGE` is exactly `1` at startup. It can also be supplied
through the existing `[Environment]` redirect. No shipped INI enables it.
The DX11 discovery hooks are requested independently of FXAA; enabling capture
does not enable FXAA, DLSS, ray tracing, or change the renderer selection.

Before testing, deploy the complete development load chain with
`scripts/Deploy-OpenShim.ps1`, following `Docs/AGENT_PATCH_WORKFLOW.md`. Use
`reverse_engineering/BZRHarness.ps1` and `BZR_FORCE_WINDOWED=1`; stop the game
through the harness, never with a forced process kill. Once `[FrameBridge]`
logs the process ID:

```powershell
./build/frame-bridge-x64/Release/frame_bridge_presenter.exe --pid <game-pid> --frames 600 --show
# Save the final imported frame without opening a helper window:
./build/frame-bridge-x64/Release/frame_bridge_presenter.exe --pid <game-pid> --frames 120 --capture-bmp build/game-frame.bmp
# Reversible deployment, harness launch, mission capture and hash-checked restore:
./tools/frame_bridge/Game-Smoke-Test.ps1
# Extra opt-in depth diagnostics. These are not qualified DLSS inputs.
./tools/frame_bridge/Game-Smoke-Test.ps1 -Depth -DepthClearOrdinal 2
./tools/frame_bridge/Game-Smoke-Test.ps1 -DepthSweep
# Require a matched camera observation in each saved final pair:
./tools/frame_bridge/Game-Smoke-Test.ps1 -DepthSweep -Camera
./tools/frame_bridge/Game-Smoke-Test.ps1 -Camera -DepthClearOrdinal 2 -Mission misn03.bzn
# Bounded shader-parameter reads, detached before the final capture:
./tools/frame_bridge/Game-Smoke-Test.ps1 -Camera -DepthClearOrdinal 2 -Mission misn03.bzn -ShaderCameraTrace
python tools/frame_bridge/Inspect-Shader-Cameras.py build/<run>/shader-camera-trace.jsonl
# CPU camera-motion diagnostic, explicitly omitting object motion and HUD:
./tools/frame_bridge/Game-Smoke-Test.ps1 -CameraMotion -DepthClearOrdinal 2 -Mission misn03.bzn -ShaderCameraTrace
python tools/frame_bridge/Inspect-Camera-Motion.py build/<run>/game-camera-motion.pfm --color build/<run>/game-frame.bmp
# Matched pre-HUD scene candidate observed locally in vehicle/on-foot missions:
./tools/frame_bridge/Game-Smoke-Test.ps1 -SceneColor -DepthClearOrdinal 3 -Mission misn03.bzn
# Diagnose earlier boundaries; these can contain HUD or black render targets:
./tools/frame_bridge/Game-Smoke-Test.ps1 -SceneColor -DepthSweep -SceneStage pre-clear
# Inspect a PFM with Python + Pillow; contrast is not linearized depth:
python tools/frame_bridge/Inspect-Capture.py build/<run>/game-depth.pfm --color build/<run>/game-frame.bmp
```

Do **not** pass `--verify` for game frames: that flag expects synthetic colors.
The preview is a separate fixed-size diagnostic window, not a playable
replacement for the game window. Do not disable original presentation yet.

The game smoke takes the machine-wide launch mutex before deployment, snapshots
the complete deployment surface and existing root configs, and uses the normal
deployment script. It forces windowed DX11, observes depth and enables background
simulation for the test process. It waits for mission initialization, captures
120 frames, requests a graceful close and restores every snapshotted file with
SHA256 checks. Logs, images and a restore manifest stay under ignored `build/`.
If graceful close fails, it leaves the game running and retains the snapshot;
never restore a live game's DLLs or force-kill it. Deployment's timestamped binary
backups and new empty resource directories may remain as recovery artifacts.

On GOG `misn01.bzn`, the x64 helper imported 120 actual frames and saved a visually
inspected frame containing lunar terrain, cockpit and HUD. This harness run used
a 584x900 RGBA8 swapchain; that unusual diagnostic window size is not a resolution
or aspect-ratio qualification. Original presentation continued. The first image
readback exposed a final-row padding bug, now covered by the odd-width smoke.
Focus/input/Alt-Tab, resize recovery, more missions and playable takeover remain
unqualified.

## Depth extraction foundation

The same mission's observation-only depth log identified a **candidate** main
surface: 584x900 D24_UNORM_S8_UINT, 8x MSAA, depth-only bind flags and frequent
bindings alongside matching-size render targets. Other observed surfaces were
4096x4096, 512x512 and 292x450 R32_TYPELESS with shader access. Dimensions alone
cannot prove pass identity. Main-world versus cockpit clear timing, satellite,
scope, mission transitions, resize and projection direction still need evidence.

`DepthExtractor` is built by the plugin and standalone GPU test tool. It
copies D24/S8 or D32 depth to an owned typeless texture with matching sample
layout, creates a depth-plane SRV and computes a single-sample R32_FLOAT result.
It never modifies the game's source description and never uses color resolve
for depth. The caller explicitly selects minimum or maximum across samples;
these are raw device-depth values, not linear depth. No projection convention
is assumed. The optional depth image is exported alongside color as a candidate.
The explicit experimental FG preview tags a private copy with its matched
camera convention; complete scene/cockpit coverage is still unqualified.

`OPENSHIM_FRAME_BRIDGE_DEPTH=1` additionally opts into depth capture, requiring
`OPENSHIM_FRAME_BRIDGE=1`. It starts the existing scene-depth observer even when
its separate diagnostic switch is off. The observer reasserts the clear hook
after OM bindings because the runtime replaces context vtables during the frame.
Attaching the clear hook only at Present produced no clear observations in the
local run. Stock resource descriptions and real clears remain intact. The shader
compiler is loaded from System32 when depth extraction initializes, so disabled
and DX9 paths acquire no new mandatory compiler DLL import.

The helper's `--depth-clear-ordinal 0..8` selects a diagnostic boundary. Zero
extracts the depth bound at Present. Positive values snapshot immediately before
the nth matching-size depth clear between Presents. These are manual selectors,
not semantic world/cockpit pass identification. The private snapshot preserves
the original sample layout, is reduced at Present and copied alongside color
before a single shared fence signal. A busy prior slot can prevent an earlier
snapshot; validity resets on each publication and missing sources never reuse
prior depth as valid. Clear counts are lower bounds when hooks detach.

`--capture-depth-pfm PATH` saves a valid final candidate as bottom-up little-endian
float PFM with a JSON sidecar containing frame ID, timestamp, format, samples,
reduction and clear boundary. Color/BMP and depth/PFM share the same mailbox frame.
If the requested final frame lacks depth, artifact capture waits at most 120
extra frames for a complete pair, then fails. The inspector makes percentile
contrast previews; their brightness is not linear depth.

The live GOG experiment at 1600x900 found Present-bound 8x D24/S8 was uniformly
1.0, demonstrating why terminal capture alone is insufficient. Pre-clear ordinal
2 produced a non-flat candidate in frame 120: minimum 0.678355277, maximum 1,
770338 non-clear pixels. The saved comparison visibly contains terrain and
nearby geometry. A same-session 1/2/3 sweep with the separate scene-depth switch
off saved three pairs over 361 consumed frames. Ordinal 1 was entirely clear;
ordinals 2 and 3 held non-flat geometry. This does not yet distinguish their
pass semantics or establish world/cockpit projection compatibility. Missing
pre-clear snapshots were reported and the final pair waited for valid depth.

The caller must serialize immediate-context access and keep the extractor output
unbound during extraction. The extractor restores the compute shader (including
class instances) and t0/u0/b0 bindings and leaves raster/OM state alone. D16,
arrays, extra mips, unsupported sample layouts, changed dimensions or foreign
devices fail closed. Start/Stop may recreate resources; Output is borrowed and
must not be retained as a bare pointer across either call.

Hardware tests rasterize a per-pixel, per-sample depth gradient into typed depth
textures without SRV bind flags. They verify every output pixel for both sample
reductions, at 1/2/4/8 samples in both x86 and x64, including edge dispatches,
preserved caller compute/DSV state, resize rejection and stopped state. The
optional D3D11 debug layer was unavailable on this machine; tests report that
limitation explicitly. Producer tests also cover pre-clear snapshots surviving
the real clear, missing/unsupported depth invalidation, occupied metadata,
recovery and reset at each Present. Cross-process tests verify per-frame color
and depth IDs, MSAA extraction, reconnects and PFM bytes. Semantic scene/cockpit
pass identity and draw-level projection qualification remain next.

## Camera observation foundation

V5 retains the owned camera snapshot and explicitly labels its matrix source.
It reads the active DX11 render system's viewport through exported Ogre APIs,
then reads that viewport's `Camera::getViewMatrix(true)` and
`Frustum::getProjectionMatrixWithRSDepth()` as the **camera baseline for shaders**,
near/far clip distances, dimensions and name. No camera pointers or native object
offsets are dereferenced in the helper. A numeric identity is diagnostic only;
the snapshot owns all matrix/name bytes and does not keep an Ogre object alive.
Missing APIs, an inactive DX11 backend, invalid dimensions, non-finite data,
singular/non-affine view transforms or guarded getter faults fail closed.

For pre-clear capture, the camera is observed immediately at the selected depth
snapshot boundary. For ordinal zero, it is observed at Present. It shares the
color/depth frame ID and ownership handoff and is invalidated when that frame
lacks depth. Its timestamp must precede the color capture, and its dimensions,
stage and clear ordinal must match the depth candidate. Occupied mailboxes keep
their existing camera metadata intact; missing snapshots cannot reuse old camera
data. This is a **viewport observation**, not proof of the camera/projection used
by each preceding draw. Native shader/AutoParam camera overrides may differ.

The helper writes `protocolVersion`, `cameraObservation.matrixSource`, `view`
and `projection` into the PFM sidecar. Matrices use Ogre row-major storage and
column-vector multiplication. The source distinguishes the camera shader
baseline, the earlier viewport RS convention and synthetic fixtures; unknown
sources are invalid. V3 descriptors are rejected rather than interpreting their
old `projectionRS` as the shader baseline. The centered
perspective inspector checks near/far endpoints and positive clip W for both
forward-Z signs. It recognizes standard/reversed and finite/infinite far planes;
orthographic, oblique, asymmetric or transposed cases stay unqualified. These
facts describe the observed matrix, not a guarantee that the entire depth texture
uses it. No linear-depth product or game-ready dense motion vectors are produced.

The bounded `-ShaderCameraTrace` tool observes exported AutoParamDataSource
view/projection getter results, copying values while each getter is live and
invalidating pairs on camera/renderable changes. It records the camera-relative
flag and groups reads by scene dimensions and preceding viewport depth clears.
It discards the partial attachment frame, observes 30 complete frames with
bounded variant/source/thread storage, detaches, and never spawns or terminates
the game. The harness rejects errors, overflow or incomplete results. Its output
includes executable/DLL/script hashes and the PID/command; trace addresses and
matrices remain in ignored build artifacts. These counters observe Ogre clears,
not the bridge's exact matching DSV clear ordinal.

The trace now follows `_updateAutoParams` into vertex parameter binding and
`getConstantBuffer`, then observes actual D3D11 Draw/DrawIndexed/instanced calls
inside Ogre `_render`. At each draw it checks the bound VS constant buffer's
identity and records the bound DSV format/dimension and depth-test/write policy.
All COM getter references are released immediately. Context-vtable changes are
handled by bounded reattachment, and nested wrapper forwarding is counted once.
Parameter associations reset each frame and on camera/renderable changes;
unlinked draws stay explicitly unlinked. This proves an observed update/bind/draw
identity chain, not matrix content in the buffer or shader semantics/coverage.

The first clean vehicle trace found three 4096x4096 shadow cameras, two main
1600x900 parameter groups with zeroed view translations, and a final identity
view/projection override. The main projection matched `WithRSDepth`, differing
from the earlier `getProjectionMatrixRS` in the Z/W signs. V4 therefore uses the
shader-oriented projection with the absolute camera view. Camera-relative
world transforms, per-renderable overrides, target flipping and actual constant
buffer/draw/depth ownership still need qualification. A matching getter pair
alone is not proof that all geometry in a depth texture used that pair.

`--require-camera` with `--capture-depth-pfm` (or harness `-Camera`) requires a
matching finite camera observation in the final pair. The same 120-extra-frame
bound applies when waiting for a complete pair; lack of camera data fails the
capture instead of substituting identity matrices. The synthetic depth smoke
uses explicitly artificial camera fixtures whose translation encodes the GPU
frame ID, and verifies this ID and the projection in both live metadata and JSON.
They never stand in for missing camera inputs in the game.

GOG qualification on 2026-10-11:

- `misn01.bzn`: camera-required ordinal 1/2/3 sweep imported 360 frames and saved
  three matched pairs at 1600x900 with 8x D24/S8 depth. All boundaries reported
  `PlayerCam`, near 0.0799999982, far 1125, aspect 1.77777784 and vertical FOV
  64.3664372 degrees. This earlier V3 projection uses positive view Z and maps near
  to approximately 0 and far to approximately 1 (standard depth).
- `misn03.bzn`: another 120-frame camera-required capture saved non-flat depth
  and visually inspected cockpit/world color, with the same viewport camera and
  projection facts. All 60 deployment/config files restored with original hashes.
- A viewport getter returning the same `PlayerCam` at each clear does **not**
  distinguish world/cockpit passes or prove their shader matrices are identical.
  The next trace must observe the actual draw/AutoParam camera and projection,
  including cockpit/secondary views and camera cuts, before temporal history or
camera-reprojected motion can be labeled usable by DLSS. Draw linkage now covers
the tested primary passes; per-shader constant layout, semantic geometry/HUD
coverage and mission/camera lifecycle remain open.

Pure camera tests cover both handedness signs, reversed depth, infinite far,
transposition, off-axis projections, invalid clip ranges/matrices/names, boundary
and extent mismatches and future observation timestamps. Producer GPU tests
cover metadata preservation and camera invalidation/recovery beside depth.

## Captured camera history and motion diagnostic

The companion keeps two owned camera observations and accepts a diagnostic pair
only for consecutive captured IDs, increasing capture/observation timestamps,
an interval of at most 250 ms, matching producer/adapter/resource identities,
camera names/identities, dimensions, projection/clip/source convention and depth
format/sample/reduction/boundary. Missing inputs clear history. Discontinuities
reseed history; an explicit reset also suppresses pairing. The current wire does
not count original game Presents or provide authoritative camera-cut events, so
this is captured-frame continuity, not qualified engine temporal history.

`--capture-camera-motion-pfm PATH` requires `--capture-depth-pfm`, at least two
frames and a matching camera pair. It waits within the existing 120-extra-frame
bound for complete history and fails closed if no comparable pair arrives. The
CPU diagnostic applies `previousVP * inverse(currentVP)` to each current depth
pixel center, using the **absolute shader-camera view**. Camera-relative world
translations must not be subtracted again. Only recognized centered perspective
inputs are accepted, including reversed depth and infinite far. Background,
non-finite depth, behind-camera and offscreen prior projections are invalid.

The RGB float PFM stores previous-minus-current X/Y in top-down pixel units and
a validity channel, with bottom-up little-endian PFM storage. Invalid pixels
have zero channels and validity zero. Metadata includes both captured IDs,
the prior view, interval and `diagnosticOnly=true`, `dlssReady=false`. It uses
current depth and assumes a static world; there is no object/skinning motion,
prior-depth occlusion validation, HUD policy, per-draw override coverage or
qualified camera-cut handling. It is never tagged to Streamline or composited
into the game. The inspector checks payload/metadata consistency and creates a
motion comparison image with an explicit pixel color scale.

Tests check analytic lateral/vertical translation and rotation, stationary
pixels, standard/reversed/infinite projection, offscreen/behind-camera points,
missing inputs and history resets. A separate synthetic moving-camera fixture
shifts the view by 0.001 per captured frame. Its cross-process smoke checks every
RGB motion pixel against analytic perspective motion derived from actual GPU
depth readback, including the offscreen validity mask and matching 119/120 IDs.

## Transport and failure contract

### V5 scene color and native overlay seam

`OPENSHIM_FRAME_BRIDGE_SCENE_COLOR=1` requires the bridge and depth switches.
It allocates a separate shared scene texture and a private capture texture.
Both use the same slot/frame/fence as depth, camera and final color. Metadata
records candidate/missing/unsupported/failed state, source, stage and the matched
depth ordinal. Scene absence never reuses an earlier image as valid.

Stage 0 captures before the selected depth clear, either from its bound RT0 or
an explicitly supplied DXGI backbuffer. Local sweeps showed why this is only a
diagnostic: matching RT0 images were black, and early backbuffer captures could
already contain HUD. Stage 1 waits for a later overlay boundary. The native
observer pins the released Ogre DLL hash, named AutoParam view/projection exports
and prologues. It detects the observed identity view/overlay projection and
captures the backbuffer before the first indexed overlay draw, after the
full-screen compositor's non-indexed draw. The camera matrices must match the
private depth snapshot; the first successful capture is latched for that frame.
Temporary backbuffer references are released within the observation. A separately
owned swapchain reference is reset on capture shutdown.

Vehicle and on-foot GOG pairs showed terrain, craft and physical cockpit/weapon
geometry in stage-1 scene color, with radar, gauges, labels and reticles absent.
This is bounded local evidence, not a general HUD contract: other shaders can
bypass AutoParam getters, inherited parameter state can be stale, and post-HUD
FXAA makes scene/final differences unsuitable as an exact UI alpha layer.
Metadata retains `candidateOnly=true` and `hudFreeQualified=false`.

The render-thread export detours exposed a startup patcher deadlock: a cached
thread snapshot created by a different writer could include and suspend its new
caller while that caller held the patch mutex. Snapshot reuse now requires the
same calling thread, and suspension independently excludes the current thread.
A regression alternates real executable-memory writes from two OS threads and
requires bounded completion. Overlay detours also publish their callable
original before their jump becomes reachable; a concurrent-caller regression
checks this through the actual inline helper. The affected local game was recovered and closed
gracefully; test deployment files were restored with original hashes.

The bounded shader trace also copies single world matrices and the native
camera-relative origin through the observed parameter/bind/draw chain. A vehicle
trace grouped 434 renderable observations, including 288 single-transform
candidates and 19 changed groups. Renderable lifetimes, pointer reuse, mesh
identity, skinning and dense object motion remain unqualified; no numeric native
identity is used by the companion as a live pointer.

### Experimental helper GPU work

Streamline loads before DXGI use. Only factory/swapchain and command-queue
creation use upgraded proxies; ordinary resources and lists use the native
device. Depth and pre-HUD color are copied into private helper textures before
releasing the shared slot. An independent GPU completion after SDK presentation
protects these private inputs before reuse. Tokens, common constants, resource
tags and helper Reflex present markers share the same helper frame index.
Unsupported SDK/runtime/device paths fail the helper while ordinary game
presentation remains active. Missing inputs clear tags and configure FG off.

GPU camera motion reconstructs previous-minus-current pixel displacement from
current depth and the captured camera pair. A rotation-only transform handles
clear-depth sky, and offscreen correspondences retain displacement. Missing
history uses the SDK reset flag; it is not qualified engine camera-cut handling.
The GPU test checks 2211 pixels against analytic depth-dependent translation,
including offscreen motion, sky translation rejection and invalid depth. The
CPU PFM diagnostic remains separate and is never used as an SDK texture.

The DXR prototype creates view-space triangles from a two-pixel depth grid,
rejects silhouette bridges and invalid depth, builds BLAS/TLAS, and uses inline
ray queries for ambient occlusion. It reconstructs normals from neighboring
depth and traces eight bounded hemisphere rays. It writes a canonical RGBA
scene plus an approximate HUD-preserving final image; a graphics blit supports
RGBA/BGRA swapchains. Hardware tests require a flat plane to have no self-AO,
a wall/floor corner to have actual ray occlusion, and distinct UI pixels to
remain unchanged. Captured geometry and output can also be inspected offline
using `Prepare-RT-Capture.py` and the GPU diagnostic executable.

- A versioned 448-byte V5 wire descriptor contains only fixed-width fields, the
  adapter LUID, dimensions/format, timestamps and producer-local NT handle
  values and owned camera data. V3 grew the V1/V2 descriptor's 128-byte prefix
  to 384 bytes; V5 adds scene color/source/stage and its interlocked selection.
  Old helpers must be rebuilt and reject the new version. The helper duplicates
  handles from that PID; it never treats wire
  integers as pointers or directly uses a foreign handle.
- Named metadata lives in the session-local namespace and uses the creator's
  default Windows security descriptor. There is no elevation, global object,
  helper autostart, injected x64 DLL, or runtime SDK download.
- One consumer owns one slot. CPU publication uses interlocked transitions:
  Free -> Writing -> Ready -> Reading -> Free. A shared D3D11/D3D12 fence orders
  the producer's copy. The consumer returns Free only after its own GPU copy
  completes. D3D12 leaves the shared resource in COMMON before returning it.
- Capture never waits for a consumer. Busy slots skip frames. A crashed/stalled
  reader leaves the slot unavailable instead of allowing concurrent GPU writes.
  A clean reader exit allows reconnect. Crash recovery needs a new session.
- V4 keeps the 384-byte layout and adds an explicit camera matrix source in
  previously reserved space, rejecting V3 to prevent projection ambiguity.
- V5 accepts RGBA8/BGRA8 SDR, one mip/array layer, and same-adapter sharing.
  MSAA color is resolved to a single-sample shared texture. Optional raw candidate
  depth is shared R32_FLOAT with the same extent and fence/frame ID. Its per-frame
  status explicitly records disabled/missing/unsupported/failed input. Consumer
  clear selection uses a separate interlocked control word, never slot-owned
  fields. A guarded viewport camera observation is optional and unqualified for
  draw-level use. HDR, cross-adapter transport, authoritative engine history and
  dense object/animation motion remain absent.
- Resizing or device replacement disables game capture for the session. Normal
  presentation continues; the helper exits on inactive metadata/producer death.
  Backbuffer references are local to the hook and released before `Present`.
- The helper's GPU waits are bounded; failed waits do not acknowledge a frame.
  The single-slot implementation intentionally prioritizes correctness over
  throughput. A ring and asynchronous presentation require separate measurement.

## DLSS milestones

1. Qualify game color capture, actual preview, game input/Alt-Tab and device loss.
2. Add session generations/resizing, a measured bounded ring, and coordinated
   presentation. Preserve the ordinary game window as a recoverable fallback.
3. Capture scene depth and matched current/previous camera constants. Handle
   MSAA depth explicitly; ordinary color ResolveSubresource is not a depth solve.
4. Add dense motion vectors for terrain, rigid vehicles, animated pilots,
   cockpit rendering and supported effects. Camera-only reconstruction is a
   restricted static-scene diagnostic, not full motion-vector support.
5. Capture pre-HUD scene color and a UI alpha/color layer at the same resolution.
6. Expand the signed NVIDIA Streamline preview integration, check feature
   support/HAGS/driver requirements, and prove SL Reflex/frame IDs and timing
   represent the actual game simulation and final presentation across processes.
7. Qualify the experimental fixed 2x FG path. Validate buffers with NVIDIA's development tools,
   image quality, actual generated presents, end-to-end latency and safe fallback
   before considering Blackwell multi-frame generation.

DLSS Frame Generation can be developed at native rendering resolution; DLSS
Super Resolution is a separate milestone. Never replace missing depth/vectors
with dummy inputs and report the resulting switch as implemented frame gen.

## Ray tracing milestones

The companion's color texture alone cannot produce correct scene ray tracing.
The capture contract needs world-space geometry, indices, instance transforms,
stable mesh/material identity, camera data and lights. It also needs alpha-test
semantics and an explicit policy for animated/deformed geometry and destruction.

The current visible-depth DXR AO preview is a bounded ray-query experiment.
Export static terrain/meshes, then build/update BLAS/TLAS for real scene instances
to replace its incomplete visible-only geometry. A fully qualified game effect
should be bounded ray-traced sun shadows or ambient occlusion, composited with
the matched raster frame. Material/albedo/normal data and raster-lighting
integration are required to avoid double-darkening an already shadowed color
frame. Denoising needs temporal history, depth/normal and motion validity.
Reflections and path tracing follow only after geometry/material coverage and
skinned/dynamic acceleration structure updates are demonstrated.

RT and FG have separate effective states. A DXR-capable adapter is not evidence
of ray-traced pixels; more output presents are not evidence of correct DLSS.

## Qualification and packaging

Native Windows V5 checkpoint, 2026-10-12:

- Release Win32 build succeeded; all **101** native regression tests passed.
  The new test alternates executable patch writers across two OS threads and
  executes a target concurrently while installing a detour, checking that its
  original trampoline is published before the hook becomes reachable.
- All **six x86** and **eight x64** helper tests passed, including owned scene
  capture, analytical camera motion, and real hardware inline DXR. A plain x64
  build without Streamline, DXR or WGC also succeeded.
- The ten-lane x86-to-x64 smoke verified every pixel in **2000** color frames,
  including **1200** depth/camera pairs and **600** scene-color pairs, with
  reconnects, bounded backpressure, odd extents and RGBA/BGRA/MSAA coverage.
- Real GOG `misn03.bzn` combined preview: **600** imported frames, **550** SDK
  extra presentations, **550** multi-present calls, final status zero; **550**
  DXR frames. A same-frame comparison changed 11484 of 649458 pixels by more
  than two channel levels, with maximum darkening 52. This demonstrates
  executed AO, not complete scene geometry or generally correct compositing.
- An independent 240-frame combined run reported **223** extra presentations
  and 223 DXR frames. WGC received zero frames in that live run and failed
  explicitly. The final smaller preview imported **180** game frames, reported
  **176** extra presentations and executed **176** DXR frames; WGC then recorded
  **342** output-window frames. Its 12.27-second clip was visually inspected.
- All live test deployments restored and hash-verified the 60-file configuration
  and binary surface after graceful game exit. Other running game sessions are
  left untouched; optional launch waiting still rechecks the shared harness lock.
- GPU readback recording labels renderer inputs and associates frame IDs with
  SDK counters. Generated images, pacing, input latency and gameplay quality
  require separate validation; no FPS improvement is claimed.
- Recorded combined GOG run: **360** imported frames, **350** extra SDK
  presentations, **350** DXR frames and final SDK status zero. The labeled
  25.05-second renderer-input video was encoded and visually inspected.
  The smaller preview eliminated the observed source-frame timeout.
- The final bounded trace completed 30 frames with seven camera variants, zero
  read errors/overflow, and 7737 draws linked to matching same-frame bindings.
  It observed 536 renderable transform groups, 368 single-transform candidates
  and 22 changing groups. Buffer contents, renderable lifetimes and dense object
  motion remain unqualified.

See [the demo validation report](DLSS_RT_DEMO_VALIDATION_20261012.md) for current
feature states, local evidence and remaining quality gates.

Native Windows checkpoint, 2026-10-11:

- Release Win32 suite build succeeded.
- All 100 engine-independent regression tests passed (including camera/history validation).
- Wire descriptor, producer GPU lifecycle and depth extraction tests passed in x86 and x64.
- The x86-to-x64 smoke verified all pixels of 400 frames: 120 followed by a
  reconnect of 80, for both single-sample and 4x MSAA sources. The first consumer
  also exercised successful DX12 swapchain presents in each lane.
- Busy-mailbox capture skips and bounded synthetic shutdown passed. Resize
  deactivation and refusal to reuse a retained descriptor passed GPU lifecycle
  tests. Hardware reported DXR tier 1.2; no ray tracing was executed.
- A second consumer was rejected without clearing the existing owner's claim.
  The headless smoke also verified another 400 frames across both sample modes.
- A further 800 synthetic frames passed across RGBA8/BGRA8, odd-width padded
  readback, 4x MSAA, reconnects and BMP pixel checks.
- GOG `misn01.bzn`: 120 actual game frames imported to DX12, final BMP visually
  inspected; full development deployment/config surface restored with hashes.
- V2 smoke checked 1200 synthetic color frames, including 400 paired depth
  frames, in x86-to-x64 single-sample/MSAA transport and reconnect lanes.
- GOG pre-clear experiment saved matched raw depth/color at 1600x900, 8x D24/S8;
  the same-session boundary sweep consumed 361 frames and produced three pairs.
  All 60 deployment/config files were restored and hash-verified after exit.
- V3 smoke checked another 1200 synthetic color frames, including 400 paired
  depth/camera frames with matching IDs, projection facts and JSON checks.
- Camera-required GOG runs imported 360 sweep frames and 120 vehicle-mission
  frames, saving four final color/depth/camera pairs;
  wire, camera, producer GPU and depth GPU tests pass in x86/x64 (4/4 each).
- Bounded GOG vehicle shader-camera trace completed 30 frames with six matrix
  groups, zero read errors and no overflow, followed by a 120-frame matched
  color/depth/camera capture. Deployment/config hashes were restored after exit.
- V4 vehicle qualification repeated the clean 30-frame trace, directly observed
  the camera-relative flag and matched both main parameter views to the camera
  view with its translation removed. The 120-frame final pair labels
  `camera-for-shaders`, with negative view Z and standard near/far endpoints.
- V4 synthetic smoke verified 1200 color frames, including 400 synchronized
  depth/camera frames with explicit `synthetic` matrix sources and V4 JSON.
- V4 on-foot mission repeated 30 clean trace frames (eight groups including an
  additional 512x512 camera), then imported 120 frames with the same labelled
  negative-view-Z shader baseline. All 60 deployment/config hashes restored.
- Draw-policy vehicle trace: 30 clean frames, 7105 observed D3D11 draws, 7015
  linked to same-frame camera parameters and matching VS constant buffers.
  The 90 unlinked calls used an 800x450 pass without a complete camera pair.
  The final 1600x900 identity-matrix group had depth testing disabled or writes
  disabled. Semantic world/cockpit coverage and buffer contents remain open.
- The vehicle run imported 120 frames and wrote a 119/120 camera-motion
  diagnostic with 985152 valid pixels, maximum 4.70e-10 pixels for the stationary
  camera. This checks plumbing; moving-game camera accuracy is unverified.
- The on-foot run imported 120 frames after a clean 30-frame trace of 6930
  draws (6840 linked, 90 half-resolution calls unlinked). Its stationary-camera
  diagnostic had 769629 valid pixels and maximum 7.28e-10 pixels. Both mission
  runs restored all 60 deployment/config hashes after graceful exit.
- Extended smoke verified 1400 synthetic color frames, including 600 paired
  depth/camera frames. The new moving-camera lane checked all motion pixels:
  59911 valid and 362 offscreen pixels, maximum 1.59790313 pixels. All five helper
  tests pass in x86/x64; all 100 regression tests pass.
- Qualified main scene depth/cameras, gameplay input/focus, Steam, Proton/Wine, coordinated
  presentation takeover, real latency, production-quality DLSS and complete
  ray-traced effects remain unqualified; the local preview is experimental.

The helper is a standalone **development tool**, excluded from the suite's
deploy/release payload. The existing native game binaries remain Win32. Native
Windows synthetic hardware tests do not qualify Wine/Proton, Steam or gameplay.
Record unavailable lanes as unverified; do not publish the helper as part of
the supported bundle before deliberate architecture/packaging review.

## Primary references

- [Microsoft D3D11/D3D12 interop and synchronization](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-with-direct3d-11--direct-2d-and-gdi)
- [Microsoft shared NT texture handles](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgiresource1-createsharedhandle)
- [Microsoft depth/format-family copies and sample-layout requirements](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-copyresource)
- [Microsoft bound vertex constant-buffer ownership](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-vsgetconstantbuffers)
- [Microsoft bound depth-test/write state ownership](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-omgetdepthstencilstate)
- [NVIDIA DLSS Frame Generation integration](https://github.com/NVIDIA-RTX/Streamline/blob/main/docs/ProgrammingGuideDLSS_G.md)
- [NVIDIA sample](https://github.com/NVIDIA-RTX/Streamline_Sample)
- [Ogre AutoParamDataSource camera-relative and shader projection semantics](https://github.com/OGRECave/ogre/blob/v1.10.0/OgreMain/src/OgreAutoParamDataSource.cpp)
- [Microsoft DXR specification](https://microsoft.github.io/DirectX-Specs/d3d/Raytracing.html)
