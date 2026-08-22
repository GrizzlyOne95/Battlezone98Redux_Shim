# Stock DX11 Destruction Performance Investigation — 2026-08-21

## Result

The stock-equivalent slowdown was reproduced with a controlled mission that
spawns 28 stock `svtank` objects, destroys all of them once, and then performs
no scripted work during the debris tail. The sustained cost is a stock render
submission/pass explosion, not OpenShim proxy work, native chunk simulation,
or continuous software skinning.

Two stock behaviors amplify the same render bottleneck:

1. blended destruction effects are split by `DynamicGeometry` into hundreds of
   depth-keyed batches even when material and render state otherwise match;
2. rigid `chunk1/chunk2` Ogre Entities retain `castShadows=true`, causing the
   same transient debris to be visited by the main view and shadow cameras.

The GOG correction coarsens only the logarithmic depth key for blended world
effects and clears Ogre's real shadow state only for exact
`chunk1/chunk1.mesh` and `chunk2/chunk2.mesh` Entities. Piece count, mesh,
lifetime, native physics, main-pass rendering, opaque geometry, and material
selection are unchanged.

## Controlled reproduction

`reverse_engineering/test_missions/stock_chunk_tail.lua` uses an existing stock
map as terrain/player donor, creates four rows of seven `svtank`, waits three
seconds, applies one lethal damage burst, then emits fixed tail markers. This
avoids the earlier `misn06` ambiguity: that mission shows roughly six or seven
vehicles fighting far from the player, has other units elsewhere, and moves the
camera/player to another location when its cinematic ends. It remains a useful
smoke test, but not a persistent visible-debris benchmark.

Matched final captures (profiler enabled, optional OpenShim proxy behavior not
used):

- stock policy: `snapshots/misn06_auto_20260821_212636/delay_0250ms`;
- corrected policy: `snapshots/misn06_auto_20260821_212535/delay_0250ms`.

The comparison window begins in the first complete interval after the single
destruction marker and covers the heavy visible tail.

| Metric | Stock policy | Corrected | Change |
|---|---:|---:|---:|
| FPS | 57.22 | 62.15 | +8.6% |
| Mean frame time | 17.66 ms | 16.30 ms | -7.7% |
| p95 frame time | 19.40 ms | 19.83 ms | noise / no improvement |
| p99 frame time | 22.95 ms | 22.75 ms | -0.9% |
| Ogre submissions/frame | 2723.4 | 1949.8 | -28.4% |
| DynamicGeometry batches/call | 372.7 | 115.7 | -69.0% |
| Indexed draws/frame | 1245.7 | 1193.2 | -4.2% |
| chunk Entity render-queue calls/frame | 369.3 | 184.5 | -50.0% |
| chunk Entities retaining shadow state | 177.4 | 1.0 | -99.4% |

The tail percentiles are dominated by the synchronized creation/explosion
burst and run-to-run effect randomness; the sustained mean and submission
counts are the stable signal. A stride-32 experiment reduced batches further
but added little frame benefit and was not selected. Disabling shadows on the
entire `DynamicGeometry` object also had no effect and was discarded.

## Native destruction architecture

Validated current GOG executable observations:

- `ChunkEffect` singleton: `0x00950190`;
- `ChunkEffect::Simulate`: `0x004917F0`;
- active entries: singleton `+0x28`, entry size `0x20`;
- active count: singleton `+0x8028`;
- template list/count: `+0x8050/+0x8054`;
- `PartialFragmentObject`: `0x00492460`;
- `FullFragmentObject`: `0x00492640`;
- `CreateChunklet`: `0x004927D0`;
- `CreateChunk`: `0x00492AA0`.

Runtime flow established by native hooks and Ogre metadata:

```text
vehicle destruction
  -> ChunkEffect Partial/FullFragmentObject
  -> CreateChunklet / CreateChunk
  -> CLASS_ID_CHUNK object in ChunkEffect's fixed active array
  -> per-frame transform/velocity/collision/lifetime in ChunkEffect::Simulate
  -> retail Ogre Entity named Ogre/MO... using chunk1/chunk1.mesh or
     chunk2/chunk2.mesh
  -> Entity::_updateRenderQueue
  -> main view plus shadow-camera visits while castShadows is set
  -> Ogre render submission / D3D11 DrawIndexed
  -> manager expiry and Ogre object removal
```

The stock chunk Entities are rigid: their contributor rows contain zero
`Entity::updateAnimation` and zero `softwareVertexBlend` calls. Native
simulation remains approximately 0.03–0.10 ms/frame under the heavy load.
Neither can explain a 16–20 ms frame.

The same destruction burst also creates stock smoke/explosion geometry through
the executable's `DynamicGeometry` container. `prepareForSubmit` at
`0x00678CD0` sorts and merges its batches; `_updateRenderQueue` at `0x00679570`
submits the prepared batches. `setSquaredViewDepth` at `0x0067A780` stores the
true depth at `+0xB0`, derives a logarithmic key at `+0x34`, and uses that key in
the comparator at `0x00678950`. The merge predicate at `0x00677A80` cannot
merge otherwise compatible blended pieces whose keys differ. During the
controlled burst, `smoke` and `smoke2.tga` are the largest blended contributors.

## Profiler defect and repair

The previous implementation required direct `E8 rel32` callers of the public
`Entity::_updateAnimation` export. Retail Redux calls the protected core
implementation directly, so no required public-wrapper caller existed and the
profiler failed closed even though some observers remained installed.

The repair follows at most two validated in-module `JMP rel32` export thunks,
checks complete GOG prologues, suspends other threads around the overwrite, and
installs x86 entry detours with RX trampolines for:

- public `_updateAnimation`: `OgreMain.dll + 0x179CB0`;
- protected `updateAnimation`: `+0x181840`;
- `Mesh::softwareVertexBlend`: `+0x28AFE0`.

`Entity::_updateRenderQueue` remains an exact vtable observer. Profiler state is
now explicit (`Disabled`, waiting states, `FullyActive`,
`PartialDiagnostics`, `Failed`), and the already-created real D3D11 immediate
context is recovered through Ogre's renderer/device exports. This restored
real draw, upload, and `Present` correlation instead of reporting zeros from a
temporary context.

## Correction details and safety

### Blended DynamicGeometry batching

On the validated GOG executable only, a prologue-gated detour calls stock
`setSquaredViewDepth` first, then coarsens `+0x34` in groups of eight for
blended world batches (`+0x31 != 0`, queue group `<100`). The true squared depth
at `+0xB0`, opaque batches, overlays, materials, shaders, and geometry are
untouched. Set `OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING=1` to restore stock
behavior; the bucket stride is diagnostically adjustable with
`OPENSHIM_DYNAMIC_ALPHA_DEPTH_BUCKET_STRIDE` (1–32).

### Native transient chunk shadows

The Ogre policy patches only the inherited `Entity::getCastShadows` vtable slot.
When stock returns true, it resolves the Entity mesh and requires an exact,
case-insensitive match to one of the two native transient mesh names. It then
calls Ogre's real `setCastShadows(false)` once. Later checks return false without
string work. All other Entities retain the stock result. The policy installs
even when the diagnostic profiler is disabled and can be opted out with
`OPENSHIM_DISABLE_NATIVE_CHUNK_SHADOW_FIX=1` (legacy alias
`BZR_DISABLE_NATIVE_CHUNK_SHADOW_FIX`).

Unsupported Ogre exports/vtables or GOG prologues fail closed. The alpha patch
is not claimed for Steam; runtime settlement/support needs separate validation.

## Hypothesis disposition

- unnecessary chunk software skinning: rejected; exact chunk Entities have
  zero animation and blend work;
- duplicate animation: present elsewhere, but not the rigid chunk path;
- native physics/simulation: rejected as dominant by measured CPU time;
- dynamic upload pressure: large aggregate Map counts exist, but measured CPU
  and animation correlation do not explain the tail;
- resource churn: limited to the burst, not the persistent tail;
- draw/pass explosion: confirmed; it scales with visible stock destruction and
  is reduced directly by the two corrections above;
- shadow amplification: confirmed for exact stock chunk Entities, but only one
  component of the broader submission explosion.

## Regression and remaining uncertainty

All controlled DX11 captures contain zero `RenderingAPIException`, zero
`without both vertex and fragment shaders`, and zero matching missing-shader,
material-compile, unsupported-technique, or null-GPU-program errors. Screenshots
show the stock debris pieces, smoke, explosion sprites, and materials still
rendering through the heavy tail.

The corrected run materially improves sustained mean frame time and removes the
measured pathological submissions, but p95 is statistically flat in this
single matched pair. A longer multi-run sample is still desirable before
assigning a release-level percentile guarantee. OpenShim proxy optimizations
remain separate and are not used as root-cause evidence here.
