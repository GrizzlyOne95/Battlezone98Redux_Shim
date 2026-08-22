# Stock Destruction Render-Submission Performance Investigation — 2026-08-21

## Result

The destruction slowdown is not inherently a DX11 problem. Controlled GOG
2.2.301 tests reproduce the same two upstream amplifiers in DX9 and DX11:

1. blended destruction effects are split by executable-side `DynamicGeometry`
   into many depth-keyed batches even when material and render state match;
2. rigid `chunk1/chunk2` Ogre Entities retain `castShadows=true`, so transient
   debris is visited by the main view and shadow cameras.

The render paths diverge only after the shared Ogre render operation. DX11
reaches `D3D11RenderSystem::_render` and `ID3D11DeviceContext` draw methods;
DX9 reaches `D3D9RenderSystem::_render` and predominantly
`IDirect3DDevice9::DrawIndexedPrimitive`. The corrected GOG policies therefore
remain renderer-neutral across DX9 and DX11 while their install gates remain
build-specific and fail closed.

The corrections do not explain every millisecond of a large battle. They do
remove the two demonstrated submission amplifiers. In DX9 the alpha correction
is the larger independent win; the exact chunk-shadow correction removes the
duplicated traversal but yields a smaller frame-time gain. No separate D3D9
driver or fixed-function bottleneck was established by this work.

## Controlled reproduction

`reverse_engineering/test_missions/stock_chunk_tail.lua` uses a stock map as a
terrain/player donor, creates seven rows of eight `svtank` (56 total), waits
three seconds, applies one lethal burst, then performs no scripted work during
the debris tail. Fixed `print()` markers identify the baseline, destruction,
alpha-effect, persistent-debris, and long-tail windows. The earlier 28-object
version was retained for initial repeats, but the 56-object load gives a
clearer CPU-side signal on fast current hardware.

The reported DX9 window is +3 through +18 seconds after the scripted
`destroy-begin` marker. It excludes startup and the instantaneous creation
spike while including both the alpha-effect phase and persistent native debris.
`reverse_engineering/analyze_stock_chunk_profile.ps1` performs the timestamp
alignment and aggregation.

### DX9 independent configurations

The representative heavy runs differ by at most 2% in native chunk creation;
stock and chunk-shadow-only match exactly at 1,632 chunks. The combined row is
the second combined run, and an exact 1,664-chunk stock/combined pair is shown
separately below because unlocked DX9 frame rate has material run variance.

| Metric | A. Stock (1,632) | B. Chunk shadow only (1,632) | C. Alpha batching only (1,600) | D. Both (1,664) |
|---|---:|---:|---:|---:|
| FPS | 86.11 | 88.26 | 100.72 | 84.21 |
| Mean frame | 13.98 ms | 13.56 ms | 12.17 ms | 13.61 ms |
| p95 | 15.47 ms | 15.22 ms | 13.50 ms | 15.47 ms |
| p99 | 16.37 ms | 15.98 ms | 14.10 ms | 16.68 ms |
| Ogre submissions/frame | 2,223.0 | 2,098.1 | 1,900.7 | 2,007.2 |
| Ogre submission CPU/frame | 1.055 ms | 1.052 ms | 0.951 ms | 0.941 ms |
| DynamicGeometry batches/call | 159.4 | 158.5 | 65.4 | 64.2 |
| chunk render-queue calls/frame | 249.1 | 139.5 | 223.7 | 165.7 |
| chunk Entities retaining shadow state | 113.1 | 9.5 | 94.2 | 15.3 |
| D3D9 indexed draws/frame | 2,218.9 | 2,094.1 | 1,896.7 | 2,003.2 |
| D3D9 render-state sets/frame | 163.8 | 164.5 | 131.8 | 130.5 |
| D3D9 texture sets/frame | 452.4 | 450.0 | 290.1 | 290.3 |
| D3D9 vertex/pixel shader sets/frame | 367.7 / 367.7 | 367.1 / 367.1 | 175.6 / 175.6 | 183.6 / 183.6 |

The exact 1,664-chunk repeat changed stock to both fixes as follows:

| Metric | Stock | Both | Change |
|---|---:|---:|---:|
| FPS | 76.98 | 84.21 | +9.4% |
| Mean frame | 14.76 ms | 13.61 ms | -7.8% |
| p95 | 16.13 ms | 15.47 ms | -4.1% |
| p99 | 17.12 ms | 16.68 ms | -2.5% |
| Ogre submissions/frame | 2,347.0 | 2,007.2 | -14.5% |
| DynamicGeometry batches/call | 155.6 | 64.2 | -58.8% |
| chunk render-queue calls/frame | 266.0 | 165.7 | -37.7% |
| chunk Entities retaining shadow state | 117.7 | 15.3 | -87.0% |
| D3D9 indexed draws/frame | 2,343.0 | 2,003.2 | -14.5% |
| D3D9 texture sets/frame | 445.4 | 290.3 | -34.8% |
| D3D9 vertex/pixel shader sets/frame | 365.8 / 365.8 | 183.6 / 183.6 | -49.8% |

Two lighter repetitions per configuration showed the same counter direction
but sizeable unlocked-FPS and random-fragment variance. The stable conclusion
is the reduction in batch, traversal, submission, draw, texture, and shader-set
work; the exact-count pair supplies the cleanest DX9 frame-time comparison.

### Prior controlled DX11 comparison

The original 28-object DX11 investigation used the same one-burst/no-scripted-
tail design and produced this matched stock/corrected result:

| Metric | Stock | Both | Change |
|---|---:|---:|---:|
| FPS | 57.22 | 62.15 | +8.6% |
| Mean frame | 17.66 ms | 16.30 ms | -7.7% |
| p95 | 19.40 ms | 19.83 ms | noise |
| p99 | 22.95 ms | 22.75 ms | -0.9% |
| Ogre submissions/frame | 2,723.4 | 1,949.8 | -28.4% |
| DynamicGeometry batches/call | 372.7 | 115.7 | -69.0% |
| chunk render-queue calls/frame | 369.3 | 184.5 | -50.0% |
| chunk Entities retaining shadow state | 177.4 | 1.0 | -99.4% |

A final 56-object corrected DX11 smoke at the original 3840x2160 configuration
completed with 1,632 created chunks and a +3s..+18s mean of 13.55 ms. That run
is a stability/visual cross-check, not a new stock-versus-corrected DX11 pair.

## Shared native destruction architecture

Validated current GOG executable observations:

- `ChunkEffect` singleton: `0x00950190`;
- `ChunkEffect::Simulate`: `0x004917F0`;
- active entries/count: singleton `+0x28` / `+0x8028`;
- `PartialFragmentObject`: `0x00492460`;
- `FullFragmentObject`: `0x00492640`;
- `CreateChunklet`: `0x004927D0`;
- `CreateChunk`: `0x00492AA0`.

```text
vehicle destruction
  -> ChunkEffect Partial/FullFragmentObject
  -> CreateChunklet / CreateChunk
  -> CLASS_ID_CHUNK native object and rigid simulation
  -> Ogre Entity using chunk1/chunk1.mesh or chunk2/chunk2.mesh
  -> Entity::_updateRenderQueue
  -> main view plus shadow-camera visits while castShadows is set
  -> Ogre RenderSystem::_render
       DX9  -> IDirect3DDevice9::DrawIndexedPrimitive and state/material binds
       DX11 -> ID3D11DeviceContext::DrawIndexed and related calls
  -> manager expiry and Ogre object removal
```

Exact chunk Entities record zero meaningful animation and software skinning.
In the heavy DX9 matrix `ChunkEffect::Simulate` remained approximately
0.056–0.069 ms/frame. It is not the source of the 12–15 ms sustained frames.

The executable-side destruction effects share `DynamicGeometry` before either
renderer. `prepareForSubmit` at `0x00678CD0` sorts and merges batches;
`setSquaredViewDepth` at `0x0067A780` stores true squared depth at `+0xB0` and
derives the logarithmic sort key at `+0x34`. The merge predicate cannot merge
otherwise compatible blended pieces whose depth keys differ. DX9 observes the
same batching reduction when those blended keys are coarsened, confirming that
the mechanism is renderer-independent on this build.

## DX9-specific findings

DX9 telemetry is attached to the validated retail
`D3D9RenderSystem::_render` export and the active `IDirect3DDevice9`/swap-chain
vtables. It counts primitive draws plus bounded render, blend, texture,
texture-stage, sampler, and shader setters without per-call logging.

For this workload, indexed D3D9 draws track Ogre submissions almost one for
one. The alpha correction also halves shader setter traffic and removes about
35% of texture sets in the exact-count pair. Although Ogre.cfg permits the
fixed pipeline, the relevant passes continue to bind vertex and pixel shaders;
texture-stage calls are present but do not show an additional independent
amplifier. The evidence therefore points to upstream pass/material submission,
not a separate measured D3D9 driver synchronization or fixed-function problem.

This telemetry does not measure time inside the vendor driver. A distinct
driver stall remains possible, but it is not required to explain the observed
draw/state scaling and was not optimized speculatively.

## Correction details and scope

### Blended DynamicGeometry batching

On the validated GOG executable only, an exact-prologue entry detour calls
stock `setSquaredViewDepth` first, then coarsens `+0x34` in groups of eight for
blended world batches (`+0x31 != 0`, queue group `<100`). True squared depth,
opaque batches, overlays, materials, shaders, geometry, and main-view order are
unchanged. Set `OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING=1` for stock behavior.

### Native transient chunk shadows

The renderer-neutral Ogre policy patches only the inherited
`Entity::getCastShadows` vtable slot. It requires stock to return true and an
exact case-insensitive mesh match to `chunk1/chunk1.mesh` or
`chunk2/chunk2.mesh`, then calls Ogre's real `setCastShadows(false)` once. All
other Entities retain stock behavior. Set
`OPENSHIM_DISABLE_NATIVE_CHUNK_SHADOW_FIX=1` for stock behavior.

The lightweight policy now requires the exact validated GOG 2.2.301 executable
and Ogre PE identities before any vtable write, followed by the existing export
and exact target-pointer checks. This supports GOG DX9 and DX11 and fails closed
on unsupported builds. Steam was not runtime-validated and is not claimed.

## Profiler repair and extension

The existing profiler repair follows at most two validated in-module
`JMP rel32` thunks, checks complete instruction-aligned prologues, suspends
other threads around entry overwrites, refuses an overwrite when any EIP is in
range, and uses RX trampolines.

DX9 support adds a prologue-gated `D3D9RenderSystem::_render` observer, active
device/swap-chain discovery, `Present` frame timing, primitive counts, and
bounded state/material counters. Active renderer selection is read from
`Ogre.cfg` before renderer-specific observers are installed. This prevents the
inactive renderer's temporary enumeration device from being patched and keeps
DX9/DX11 collection independent. Diagnostics remain separable from both
lightweight corrections.

## Regression validation and uncertainty

- DX9 and DX11 startup, mission load, destruction, and sustained tails passed.
- Profiling explicitly disabled still produced 1,568 chunks with the lightweight
  policy active and no renderer telemetry hooks.
- All four DX9 configurations ran independently through their environment
  opt-outs.
- Screenshots show native chunks, stock meshes/materials, smoke, explosions,
  alpha effects, main-view debris, opaque vehicle geometry, terrain, and HUD.
- Captured logs contain no matching renderer/material/shader failure or
  unhandled-exception signatures in the final matrix and smoke runs.
- Native chunk count/lifetime/physics code is untouched; normal Entity shadows
  are untouched by the exact mesh classifier.

Remaining uncertainty is primarily statistical and platform-specific. Chunk
fragment count and unlocked FPS vary between runs; a longer externally sampled
series would be needed for a release-level percentile guarantee. D3D9 vendor-
driver time is not directly measured. Only GOG 2.2.301 with the validated Ogre
and renderer binaries was exercised; Steam and other builds remain unsupported
until separately validated.
