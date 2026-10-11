# Experimental DLSS / ray tracing bridge

Status: frame transport prototype, **not working DLSS or ray tracing**.
Development branch: `agent/dlss-rt-bridge`, based on current `origin/main`
after checking open PRs and renderer history (2026-10-11).

## Architecture

Battlezone and its native load chain stay Win32/DX11. An opt-in OpenShim
presentation observer copies completed SDR color into a shared GPU texture.
A separately built x64 DX12 diagnostic helper imports it on the same adapter.
The helper can verify synthetic pixels or display a non-activating preview.
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
single-sample and 4x MSAA resolve paths are exercised. Synthetic sources exit
on a deadline; backpressure is verified after the consumer exits.

The helper reports hardware DXR capability separately from effective feature
state. It explicitly prints `DLSS=not-integrated RT=not-integrated`. Capture to
GPU-copy timing includes startup/attach delay and verification readback; it is
**not a gameplay latency measurement or a performance benchmark**.

## Game capture (not yet qualified)

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
```

Do **not** pass `--verify` for game frames: that flag expects synthetic colors.
The preview is a separate fixed-size diagnostic window, not a playable
replacement for the game window. Do not disable original presentation yet.

## Transport and failure contract

- A versioned 128-byte wire descriptor contains only fixed-width fields, the
  adapter LUID, dimensions/format, timestamps and producer-local NT handle
  values. The helper duplicates handles from that PID; it never treats wire
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
- V1 accepts RGBA8/BGRA8 SDR, one mip/array layer, and same-adapter sharing.
  MSAA color is resolved to a single-sample shared texture. HDR, cross-adapter
  transport, scene depth and motion vectors are outside V1.
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
- Wire descriptor and producer GPU lifecycle tests passed in x86 and x64.
- The x86-to-x64 smoke verified all pixels of 400 frames: 120 followed by a
  reconnect of 80, for both single-sample and 4x MSAA sources. The first consumer
  also exercised successful DX12 swapchain presents in each lane.
- Busy-mailbox capture skips and bounded synthetic shutdown passed. Resize
  deactivation and refusal to reuse a retained descriptor passed GPU lifecycle
  tests. Hardware reported DXR tier 1.2; no ray tracing was executed.
- A second consumer was rejected without clearing the existing owner's claim.
  The headless smoke also verified another 400 frames across both sample modes.
- Real Battlezone capture/visual/input testing, Steam, Proton/Wine, coordinated
  presentation takeover, real latency, DLSS and ray-traced effects are unverified.

The helper is a standalone **development tool**, excluded from the suite's
deploy/release payload. The existing native game binaries remain Win32. Native
Windows hardware tests do not qualify Wine/Proton, Steam or the game itself.
Record unavailable lanes as unverified; do not publish the helper as part of
the supported bundle before deliberate architecture/packaging review.

## Primary references

- [Microsoft D3D11/D3D12 interop and synchronization](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-with-direct3d-11--direct-2d-and-gdi)
- [Microsoft shared NT texture handles](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgiresource1-createsharedhandle)
- [NVIDIA DLSS Frame Generation integration](https://github.com/NVIDIA-RTX/Streamline/blob/main/docs/ProgrammingGuideDLSS_G.md)
- [NVIDIA sample](https://github.com/NVIDIA-RTX/Streamline_Sample)
- [Microsoft DXR specification](https://microsoft.github.io/DirectX-Specs/d3d/Raytracing.html)
