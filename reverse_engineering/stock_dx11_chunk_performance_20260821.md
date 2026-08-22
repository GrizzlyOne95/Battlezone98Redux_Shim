# Stock DX11 Destruction Performance Investigation — 2026-08-21

## Scope and status

The target is the persistent slowdown while stock Redux destruction debris is
alive and visible. OpenShim proxy overhead is tracked separately and is not a
valid explanation for the stock symptom.

The profiler defect is repaired and the relevant CPU/D3D11 telemetry is now
working. The current automated `misn06` scene does **not** reproduce the user's
heavy visible-debris minimum: its cinematic shows roughly six or seven vehicles
fighting far from the player, with additional units elsewhere on the map, then
relocates the camera and player away from the old debris. It therefore cannot
establish the
dominant stock rendering pathology or justify a behavior-changing fix yet.

## Native destruction architecture established so far

Validated GOG executable observations:

- `ChunkEffect` singleton: `0x00950190`;
- `ChunkEffect` vtable: `0x00877070`;
- `ChunkEffect::Simulate` slot: `0x0087708C`, target `0x004917F0`;
- active array base: `ChunkEffect + 0x28`, entry size `0x20`;
- active count: `ChunkEffect + 0x8028`;
- template list/count: `ChunkEffect + 0x8050/+0x8054`;
- `PartialFragmentObject`: `0x00492460`;
- `FullFragmentObject`: `0x00492640`;
- `CreateChunklet`: `0x004927D0`;
- `CreateChunk`: `0x00492AA0`.

Runtime samples prove that active entries point to real class-id 53
(`CLASS_ID_CHUNK`) objects with owner zero. The manager owns their transform,
velocity, collision/lifetime integration, and removal. OpenShim's mesh proxies
consume this list only as a separate enhanced visual bridge.

Legacy 1.5 `ChunkEffect::Submit` is empty. Legacy chunks enter a zone/sorting
list and reach `Render_Chunk_Object`; Redux's normal game-object-to-Ogre owner
bridge is absent for these owner-zero chunk objects. Generic native `chunk1` /
`chunk2` pieces and OpenShim-restored full fragment meshes must therefore remain
distinct in analysis. The exact stock Redux render association for every
visible native piece remains an open part of the investigation.

## Profiler defect and repair

The old observer searched loaded images for direct `E8 rel32` callers of
`Entity::_updateAnimation`. Retail Redux calls the protected
`Entity::updateAnimation` implementation from the render path and has no direct
callers matching the public wrapper export, so the required count was zero and
the profiler failed closed.

The repaired profiler follows the retail export's validated in-module
`JMP rel32` thunk and detours the verified implementation entry. It also detours
the protected core actually used by retail and `Mesh::softwareVertexBlend`.
The GOG implementations observed are:

- public `_updateAnimation`: `OgreMain.dll + 0x179CB0`;
- protected `updateAnimation`: `OgreMain.dll + 0x181840`;
- `softwareVertexBlend`: `OgreMain.dll + 0x28AFE0`;
- `_updateRenderQueue`: `OgreMain.dll + 0x179CE0` via Entity vtable.

The first public-wrapper install can encounter a transient access-denied thread
open during startup. The worker now reports the reason and retries for a bounded
window. A later retry reaches all three hooks and `FullyActive` once the real
DX11 context and first `Present` are observed.

## D3D11 observation defect and repair

Patching renderer imports captured probe/temporary contexts, not the renderer's
already-created real immediate context. That produced valid `Present` timing but
zero draw/upload counts. `D3D11RenderSystem::_render` proved submission was
active while those counters were zero.

The profiler now resolves the real context through exported Ogre renderer/device
accessors. Redux restores that context vtable at frame boundaries, so the
observer validates and refreshes the public COM slots once per frame. The fixed
capture records approximately 450–625 `DrawIndexed` calls per frame in the
`misn06` scene instead of zero.

## Current measurements

Stock-like configuration disables OpenShim chunk mesh proxies, manual proxy
submission, partial-fragment bone collapse, vehicle-skinning diagnostics, and
faction jet flames while leaving native `ChunkEffect` intact.

Capture:
`reverse_engineering/snapshots/misn06_auto_20260821_200002/delay_0250ms`

| Active chunks avg/max | FPS | Mean / p95 ms | Ogre submits/frame | DrawIndexed/frame | Ogre submit CPU/frame | Native sim CPU/frame |
|---:|---:|---:|---:|---:|---:|---:|
| 41.4 / 56 | 297 | 3.37 / 4.00 | 698.7 | 571.2 | 0.455 ms | 0.010 ms |
| 65.8 / 71 | 295 | 3.38 / 4.00 | 745.3 | 598.8 | 0.487 ms | 0.010 ms |
| 71.8 / 76 | 188 | 5.32 / 5.75 | 779.6 | 623.0 | 0.537 ms | 0.010 ms |
| 24.8 / 35 | 353 | 2.83 / 4.00 | 524.2 | 452.8 | 0.333 ms | 0.004 ms |

Interpretation is deliberately limited:

- native chunk simulation is decisively too small to explain the measured
  multi-millisecond frame changes in this scene;
- software blend is normally below roughly 0.3 ms/frame and does not scale with
  native active count strongly enough to be the dominant cost here;
- hundreds of same-frame animation entries mostly hit Ogre's clean/temporary-
  buffer guards; duplicate entries are not equivalent to duplicate deformation;
- visible workload changes by roughly 100–170 indexed draws/frame across these
  camera phases, but the cinematic transition and changing visible scene prevent
  attributing that delta specifically to debris;
- the 188–225 FPS interval is not the reported 45 FPS pathology and is not a
  valid before measurement for a stock fix.

Earlier low-FPS captures taken while the game lost foreground focus are excluded
from root-cause evidence; the apparent 50 ms software blends were a scheduling
artifact and fell to about 1 ms when repeated in the foreground.

## Hypothesis status

- Unnecessary software skinning: not dominant in the current stock-like scene;
  not globally disproved for the user's heavy visible case.
- Same-frame animation calls: present, but most are cheap and do not reblend.
- Native simulation/physics: rejected for the observed 0–86 chunk range.
- Draw/pass or shadow amplification: still plausible for the sustained visible
  case; the current mission changes camera/location too soon.
- Dynamic upload pressure: instrumentation is active; current scene has not
  shown a dominant animation-correlated upload cost.
- Resource churn: creation bursts remain distinct from the persistent symptom
  and require a sustained visible capture.

## Regression guard

Every DX11 capture searches both OpenShim and BZR logs for
`RenderingAPIException`, `without both vertex and fragment shaders`, missing
shader/material errors, unsupported techniques, and null GPU programs. The
captures listed above contain zero shaderless exceptions and zero matching
shader/material failures.

## Next proof needed

The remaining blocking measurement is a 10–20 second interval with many native
pieces simultaneously alive **and in the camera view**, plus a matched look-away
interval. The instrumented DLL and aggregate logs are ready; no debugger or
per-call trace is required. A stock-path behavior change must wait for that
measurement so a proxy-only or camera-transition correlation is not mistaken
for the root cause.
