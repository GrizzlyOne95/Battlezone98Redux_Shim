# Ogre Animation / Render Overhead Profiler

This opt-in diagnostic correlates Ogre animation, software deformation, native
chunk simulation, renderer submissions, DX9/DX11 work, and `Present` frame time.
The diagnostic observers do not change animation state, culling, materials,
shaders, or gameplay. The independently controlled validated-runtime
performance policies documented below can remain active when profiling is
disabled.

## Enable

Set `OPENSHIM_PROFILE_OGRE_ANIMATION=1`, or configure:

```ini
[Diagnostics]
ProfileOgreAnimation = 1
```

The environment value takes precedence over the INI value. Disable profiling
for normal play after collecting a capture.

## Observer architecture

The retail GOG `OgreMain.dll` used for validation has SHA-256
`E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45`.
The profiler enumerates semantic exports, follows at most two in-module
`JMP rel32` export thunks, verifies complete instruction-aligned prologues, and
installs process-lifetime x86 entry detours for:

- public `Ogre::Entity::_updateAnimation`;
- protected `Ogre::Entity::updateAnimation`, which the retail render path calls
  directly instead of passing through the public wrapper;
- `Ogre::Mesh::softwareVertexBlend`;
- `Ogre::SceneManager::_renderScene`, including re-entrant shadow-camera
  attribution.

The protected core detour is required for actual attribution; the public
wrapper is retained as a validated observer seam and compatibility check.
`Entity::_updateRenderQueue` remains observed through an exact-match Entity
vtable slot.

Entry installation suspends other process threads, refuses to patch while an
instruction pointer is in the overwrite span, constructs an RX trampoline, and
fails closed when a thunk, target, prologue, or thread state is unsupported.
Transient thread-open races are retried for a bounded five-second window.

For the validated GOG renderer (`RenderSystem_Direct3D11.dll` SHA-256
`78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0`),
the profiler also observes `D3D11RenderSystem::_render`. BZR creates its real
immediate context before the renderer IAT observer can see it, so the profiler
obtains that context through the renderer's exported `_getDevice` and
`D3D11Device::GetImmediateContext` accessors. The runtime restores the context
vtable at frame boundaries; one validated, batched vtable refresh per frame
keeps aggregate D3D11 counters attached without per-call logging.

For the validated GOG DX9 renderer (`RenderSystem_Direct3D9.dll` SHA-256
`822D26CA4B9CCE82DDD2FCA5E31E7D3A0CD8D05032130A987830143E3D0F95E1`),
the profiler observes `D3D9RenderSystem::_render`, obtains the renderer-owned
active device only after the first render operation, and attaches bounded
observers to the active device and primary swap chain. Renderer selection from
`Ogre.cfg` gates DX9 versus DX11 observer installation so the inactive
renderer's enumeration objects are never patched.

## State model

State transitions are explicit:

- `Disabled`: collection is off.
- `WaitingForOgre`: requested, but no Ogre install attempt has completed.
- `OgreReady`: all required Ogre observers are active and renderer capture has
  not begun.
- `WaitingForRenderer`: Ogre is active; a usable DX9/DX11 device and `Present`
  pair is not yet available.
- `FullyActive`: Ogre hooks, the selected DX9/DX11 device hooks, and `Present`
  correlation work.
- `PartialDiagnostics`: at least one useful observer works, but full attribution
  does not.
- `Failed`: installation was attempted and no useful observer remains active.

Installed detours and vtable observers are process-lifetime. Shutdown disables
collection first; hooks then become pass-through until process exit.

## Telemetry

Reports are aggregated approximately once per second. Diagnostic hot paths use
atomics, fixed tables, and bounded bloom sets; they do not format strings,
write files, allocate, or acquire heavyweight contributor maps. The independent
DX11 skin-source correction can allocate once per previously unshadowed shared
source, then returns to a pointer/flag fast path.

The reports include:

- `Present`-epoch FPS plus frame mean, p50, p95, p99, maximum, and slow-frame
  counts;
- animation calls, approximate unique entities, render-driven versus external
  provenance, CPU time, and same-entity/same-frame repeats;
- software blends, vertices, matrices, normals, CPU time, size/latency buckets,
  and blends per animation update;
- fixed-size per-Entity and per-source-`VertexData` top contributors;
- source position/normal/weight/index stride, weights-per-vertex, and buffer
  shadow/system-memory state;
- named main and shadow cameras plus main-versus-nested render-queue,
  animation, and software-blend attribution;
- render-queue calls and approximate visible-versus-skinned sets;
- Ogre render operations and CPU submission time;
- D3D11 `Draw`, `DrawIndexed`, instanced and indirect variants, normalized per
  frame;
- D3D9 `DrawPrimitive`/`DrawIndexedPrimitive` plus bounded render-state,
  blend-state, texture, texture-stage, sampler, and shader setter counts;
- `Map`, `Unmap`, and `UpdateSubresource`, including write-mode and animation
  TLS attribution;
- native `ChunkEffect::Simulate` active count and CPU time.
- native `DynamicGeometry` rebuild, queue, batch, material, vertex, and index
  attribution;
- exact `chunk1/chunk2` Entity names, meshes, stored shadow state, and
  render-queue calls;
- native chunk shadow-policy query/suppression counts.

A stable core subset is appended to `openshim_ogre_profile.csv`; the more
detailed chunk/renderer histograms remain in the one-second log rows. The CSV
schema is centralized in `include/ogre_profiler_algorithms.h` and protected by
unit tests.

`animCPU` contains nested blend work, so it must not be added to `swCPU`.
Approximate unique counts use a 65,536-bit pointer bloom set and are labelled
with `~` in logs.

## Duplicate semantics

Duplicate animation detection keys on `(Entity*, Present frame epoch)`. Multiple
`softwareVertexBlend` calls inside one Entity update are reported as
blends/update; they are not counted as duplicate Entity updates.

## Recommended visible-destruction capture

Use the same mission/save and keep the camera aimed at the debris for 10–20
seconds. Record a quiet interval, a creation burst, and a sustained interval
while the pieces remain both alive and visible. Then turn away without changing
the simulation to separate visible rendering work from native simulation.

Do not treat an interval after a cinematic camera relocates the player away
from the battle as a sustained visible-debris sample. It remains useful for
native `ChunkEffect` simulation scaling only.

For a deterministic visible tail, deploy
`reverse_engineering/test_missions/stock_chunk_tail.lua` beside a copied stock
`.bzn` with the same basename. It creates 56 `svtank`, destroys them once at
three seconds, and leaves the camera/load unchanged afterward.

## Validated runtime performance policies

These policies are separate from collection and default on in the validated GOG
2.2.301 build for both DX9 and DX11:

- exact `chunk1/chunk1.mesh` and `chunk2/chunk2.mesh` Entities have their real
  Ogre shadow flag cleared once; opt out with
  `OPENSHIM_DISABLE_NATIVE_CHUNK_SHADOW_FIX=1`;
- blended world-effect logarithmic depth keys use stride 8 to permit compatible
  `DynamicGeometry` batches to merge; opt out with
  `OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING=1`.

Neither policy changes piece count, native simulation/lifetime, main-pass mesh,
opaque geometry, material, or shader selection. See
`stock_destruction_render_submission_performance_20260821.md` for the RE and
A/B evidence. The chunk policy additionally checks the exact validated GOG
executable and Ogre PE identities before writing an Entity vtable; unsupported
builds fail closed. Steam is not claimed by this investigation.

DX11 additionally enables a software-skin source correction on the same exact
GOG executable/Ogre identities. If the position/normal stream read by
`Mesh::softwareVertexBlend` lacks an Ogre CPU shadow, OpenShim pays one staging
readback, creates an equivalent CPU-shadowed vertex buffer, copies the exact
interleaved bytes, and replaces that shared binding. This avoids a synchronous
GPU readback for every affected Entity every frame without changing the mesh,
animation, draw, or shadow policy. Any failed repair disables the correction
for the process and leaves stock behavior in place. Opt out with:

```text
OPENSHIM_DISABLE_DX11_SKIN_SOURCE_SHADOW_FIX=1
```

See `live_combat_scaling_20260822.md` for the deterministic IA mission, layout
evidence, and profiler-enabled/disabled DX9/DX11 A/B results.

## Tests

Run:

```powershell
.\scripts\run_ogre_profiler_tests.ps1
.\scripts\run_ini_tests.ps1
```

The pure profiler tests cover histogram percentiles, frame/vertex/matrix/latency
buckets, duplicate semantics, bounded top-contributor replacement, state
transitions, environment/INI/default precedence, CSV stability, bounded rel32
thunk resolution, detour prologue validation, exact native-chunk mesh
classification, and blended depth-key quantization.
