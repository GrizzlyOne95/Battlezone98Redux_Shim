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
