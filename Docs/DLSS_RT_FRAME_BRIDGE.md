# Experimental DLSS / ray tracing bridge

Status: frame transport prototype, **not working DLSS or ray tracing**.
Development branch: `agent/dlss-rt-bridge`, based on current `origin/main`
after checking open PRs and renderer history (2026-10-11).

## Architecture

Battlezone and its native load chain stay Win32/DX11. An opt-in OpenShim
presentation observer copies completed SDR color into a shared GPU texture.
A separately built x64 DX12 diagnostic helper imports it on the same adapter.
The helper can verify synthetic pixels, save color/depth artifacts, or display a non-activating preview.
The normal game `Present` still runs. No input forwarding or presentation
takeover exists at this milestone.

This proves a route around the 32-bit in-process SDK boundary without replacing
Ogre or converting the game executable. It does not prove that Streamline will
accept a complete cross-process host integration. Reflex/simulation timing,
input focus, and presentation ownership remain explicit feasibility gates.

## Build and reproduce

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
```

The smoke uses a **real x86 process** and x64 DX12 consumer. Each published
frame encodes its ID into a solid RGBA color. GPU readback checks every pixel
against the descriptor's frame ID, then tests a clean consumer reconnect. Both
single-sample and 4x MSAA resolve paths are exercised, plus odd-width RGBA/BGRA
readback and BMP channel/orientation checks. Synthetic sources exit
on a deadline; backpressure is verified after the consumer exits.

The helper reports hardware DXR capability separately from effective feature
state. It explicitly prints `DLSS=not-integrated RT=not-integrated`. Capture to
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
is assumed. The optional V2 depth image is exported alongside color; it is not
tagged as a DLSS input or advertised as qualified main scene depth.

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
pass identity, camera constants and projection qualification remain next.

## Transport and failure contract

- A versioned 128-byte wire descriptor contains only fixed-width fields, the
  adapter LUID, dimensions/format, timestamps and producer-local NT handle
  values. V2 retains the 128-byte size and adds optional depth metadata/handle;
  V1 helpers must be rebuilt and reject the new version. The helper duplicates
  handles from that PID; it never treats wire
  integers as pointers or directly uses a foreign handle.
- Named metadata lives in the session-local namespace and uses the creator's
  default Windows security descriptor. There is no elevation, global object,
  helper autostart, injected x64 DLL, or third-party SDK download.
- One consumer owns one slot. CPU publication uses interlocked transitions:
  Free -> Writing -> Ready -> Reading -> Free. A shared D3D11/D3D12 fence orders
  the producer's copy. The consumer returns Free only after its own GPU copy
  completes. D3D12 leaves the shared resource in COMMON before returning it.
- Capture never waits for a consumer. Busy slots skip frames. A crashed/stalled
  reader leaves the slot unavailable instead of allowing concurrent GPU writes.
  A clean reader exit allows reconnect. Crash recovery needs a new session.
- V2 accepts RGBA8/BGRA8 SDR, one mip/array layer, and same-adapter sharing.
  MSAA color is resolved to a single-sample shared texture. Optional raw candidate
  depth is shared R32_FLOAT with the same extent and fence/frame ID. Its per-frame
  status explicitly records disabled/missing/unsupported/failed input. Consumer
  clear selection uses a separate interlocked control word, never slot-owned
  fields. HDR, cross-adapter transport, cameras and motion vectors remain absent.
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
6. Integrate signed NVIDIA Streamline binaries in the helper, check feature
   support/HAGS/driver requirements, and prove SL Reflex/frame IDs and timing
   represent the actual game simulation and final presentation across processes.
7. Enable fixed 2x FG first. Validate buffers with NVIDIA's development tools,
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

Start with a static terrain/mesh export and a small DXR ray-query diagnostic.
Then build/update BLAS/TLAS for real scene instances. The first game effect
should be bounded ray-traced sun shadows or ambient occlusion, composited with
the matched raster frame. Material/albedo/normal data and raster-lighting
integration are required to avoid double-darkening an already shadowed color
frame. Denoising needs temporal history, depth/normal and motion validity.
Reflections and path tracing follow only after geometry/material coverage and
skinned/dynamic acceleration structure updates are demonstrated.

RT and FG have separate effective states. A DXR-capable adapter is not evidence
of ray-traced pixels; more output presents are not evidence of correct DLSS.

## Qualification and packaging

Native Windows checkpoint, 2026-10-11:

- Release Win32 suite build succeeded.
- All 98 engine-independent regression tests passed.
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
- Qualified main scene depth/cameras, gameplay input/focus, Steam, Proton/Wine, coordinated
  presentation takeover, real latency, DLSS and ray-traced effects are unverified.

The helper is a standalone **development tool**, excluded from the suite's
deploy/release payload. The existing native game binaries remain Win32. Native
Windows synthetic hardware tests do not qualify Wine/Proton, Steam or gameplay.
Record unavailable lanes as unverified; do not publish the helper as part of
the supported bundle before deliberate architecture/packaging review.

## Primary references

- [Microsoft D3D11/D3D12 interop and synchronization](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-with-direct3d-11--direct-2d-and-gdi)
- [Microsoft shared NT texture handles](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgiresource1-createsharedhandle)
- [Microsoft depth/format-family copies and sample-layout requirements](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-copyresource)
- [NVIDIA DLSS Frame Generation integration](https://github.com/NVIDIA-RTX/Streamline/blob/main/docs/ProgrammingGuideDLSS_G.md)
- [NVIDIA sample](https://github.com/NVIDIA-RTX/Streamline_Sample)
- [Microsoft DXR specification](https://microsoft.github.io/DirectX-Specs/d3d/Raytracing.html)
