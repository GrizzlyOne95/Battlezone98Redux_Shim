# Live render optimization report (2026-08-22)

## Scope and answer

This investigation continued from exact head `6ff74dd9` on
`agent/live-render-optimization`. It reused the deterministic `lcbench` Instant
Action workload and targeted the remaining weapon/effect submission cost after
the DX11 software-skin readback correction.

The largest unnecessary ordinary-fire cost was not animation, skinning, or
DynamicGeometry preparation. It was the restored visual bridge for stock
generic impact debris: every native `chunk1/chunk1.mesh` or
`chunk2/chunk2.mesh` simulation object created a separate Ogre Entity. Each
tiny 12- or 24-vertex mesh was then submitted once through `high-pssm` and once
through `glow`. In a 20-tank firing sample this bridge alone accounted for
approximately 176 Ogre submissions/frame and continued accumulating toward the
proxy capacity. OpenShim now preserves every native chunk transform and
lifetime but emits exact stock generic chunklet geometry through one dynamic
ManualObject section. The result retains the material and both visible schemes
while collapsing roughly 100 independent renderables to one compatible batch.

In the controlled 20-tank DX11 workload, submissions fell from 816.02 to
488.42/frame and profiler frame time from 8.194 to 4.904 ms. Profiler-disabled
PresentMon measured 8.171 to 4.980 ms (-39.0%) and 122.4 to 200.8 FPS (+64.1%).
At 80 tanks the improvement was 2,551 to 1,597.98 submissions/frame and 19.61
to 12.13 ms (-38.1%). No projectile, impact, smoke, chunk, shadow, or gameplay
object was removed.

## Bounded render-contributor attribution

The profiler now hooks the exact retail
`Ogre::SceneManager::renderSingleObject` export and records contributors in a
fixed-capacity table. The semantic key is renderable vtable, Pass, camera, and
mesh; it never allocates an unbounded hot-path map or formats per-call logs.
One-second top rows include representative owner, RTTI type, mesh, material,
technique, scheme, LOD, pass index/name, camera, main/shadow entries,
RenderOperation vertices/indices, Ogre submission CPU, D3D draws, and DX9
state traffic. The analyzer writes aggregated `render_contributors.csv` and
also exposes interval DX9 and DX11 skin-source counters.

Legacy-proxy 20-tank firing ranking (`20260822_085553`; the then-top-20 output
does not contain all low-ranked compositor rows):

| Rank/group | Submissions/frame | Why |
|---|---:|---|
| `chunk1/chunk1.mesh`, `scarpmat2` | 95.35 | distinct tiny Entities, normal/glow |
| `chunk2/chunk2.mesh`, `scarpmat2` | 80.88 | distinct tiny Entities, normal/glow |
| `avtank.mesh` shadow caster, submesh 1 | 63.03 | one of three PSSM shadow traversals |
| `avtank.mesh` shadow caster, submesh 2 | 63.03 | second vehicle submesh |
| `avtank.mesh` shadow caster, submesh 3 | 63.03 | third vehicle submesh |
| `avheadlight00`, `avtank00`, `avtank01` | 21 each captured row | legitimate vehicle material passes |
| `dirt.tga` DynamicGeometry | 6.34 | compatible effect batch, also glow |
| `smoke.tga` DynamicGeometry | 5.44 | compatible effect batch, also glow |
| `grndchar.tga` | 5.09 | ground impact mark, also glow |
| `ground.tga` | 4.90 | ground effect, also glow |
| `vsmoke.tga` | 4.30 | vehicle/effect smoke, also glow |

Technique metadata proved that repeated PlayerCam rows are different
`high-pssm` and `glow` schemes, not duplicate calls to one pass. Shadow rows
use the `Default` scheme and the three shadow cameras. The chunk meshes did not
cast shadows under the existing exact chunk policy, so their multiplication
was entirely object count times the two main-view schemes.

At 80 tanks after batching, the largest contributors are legitimate vehicle
work: three shadow-caster submeshes at 243.02 submissions/frame each; six
vehicle high-pssm/glow rows at 81/frame; then visible ordnance and compatible
DynamicGeometry groups. The generic chunk batch costs only two submissions
when active (one per material scheme).

## Weapon/effect isolation

`lcbench` now accepts additional stock/common ODFs and a `flight` phase. The
flight phase places opposing units 400 m farther along the sight line to retain
muzzle/projectile activity while minimizing impacts during its short window.
Ten-unit DX11 results (`20260822_092655`) were:

| Unit/category | Idle ms / submits | Flight ms / submits | Firing+impact ms / submits | Interpretation |
|---|---:|---:|---:|---|
| `avtank`, cannon | 3.345 / 241.0 | 3.567 / 316.27 | 3.793 / 309.13 | impacts add dirt/smoke/ground/flame/vsmoke; batching contains chunklets |
| `svfigh`, machine-gun | 3.203 / 241.8 | 3.017 / 276.3 | 3.283 / 278.43 | trail, dirt, smoke and ground groups; no chunk explosion |
| `avrckt`, guided weapons | 3.213 / 241.13 | 3.053 / 241.17 | 3.237 / 241.1 | this forced setup did not sustain stock rocket fire; not used to claim a rocket cost |
| `avartl`, mortar/howitzer | 2.857 / 180.83 | 2.883 / 165.97 | 2.863 / 157.0 | packed howitzers did not sustain fire; result is a harness limitation, not an optimized category |

The successful cannon and machine-gun cases show high-constant-factor O(n)
effect growth, not O(n²). DynamicGeometry already batches each compatible
texture/material, but most effect materials still intentionally participate in
both Default and glow schemes. Projectile meshes can also use high-pssm, glow,
and shadow-caster passes. Removing those effects or passes without a visual
case was rejected. Rocket/howitzer deployment and weapon-mask control should be
added before those categories are used as quantitative evidence.

## Implemented optimization and safety gates

The shared Ogre optimization is deliberately narrow:

- only exact names `chunk1/chunk1.mesh` and `chunk2/chunk2.mesh` are candidates;
- embedded positions, normals, tangents and UVs are generated from the tracked
  974-byte and 1,718-byte stock payload meshes;
- every discovered campaign/stock override must match the expected byte count
  and FNV-1a (`0x0A5E675C05F6592A` and `0xEFA2B5E79112A3BF`);
- any missing, custom, or changed payload falls back to the existing per-Entity
  fidelity path;
- authored craft fragments and all other chunk meshes remain per-Entity;
- native simulation, transform, rotation, lifetime, count, and gameplay are
  unchanged;
- material remains `scarpmat2`, shadows remain off exactly as before, and Ogre
  still renders its high-pssm and glow techniques;
- missing Ogre exports or a batch construction failure fail back to the Entity
  bridge; unsupported executable/Ogre identities remain governed by the
  existing fail-closed chunk-proxy gates;
- `OPENSHIM_DISABLE_GENERIC_CHUNK_BATCH=1` (or the BZR-prefixed equivalent)
  independently restores the legacy Entity path.

No global material combination, transparency reorder, lifetime shortening,
shadow disable, projectile change, or gameplay count reduction was made.

## A/B and scaling

### Continuous fire

| DX11 workload | Legacy Entity proxy | Generic batch | Change |
|---|---:|---:|---:|
| 20 tanks, profiler mean | 8.194 ms, 816.02 submits | 4.904 ms, 488.42 submits | -40.2% ms, -40.1% submits |
| 20 tanks, PresentMon/profiler off | 8.171 ms, 122.4 FPS | 4.980 ms, 200.8 FPS | -39.0% ms, +64.1% FPS |
| 80 tanks, profiler | 19.61 ms, 2,551 submits | 12.13 ms, 1,597.98 submits | -38.1% ms, -37.4% submits |

The batch-enabled scaling session `20260822_093103` measured:

| Tanks | Mean ms | p95 ms | Ogre submissions/frame |
|---:|---:|---:|---:|
| 10 | 3.796 | 4.90 | 310.24 |
| 20 | 4.816 | 5.95 | 488.58 |
| 40 | 6.846 | 8.15 | 856.72 |
| 80 | 12.130 | 15.15 | 1,597.98 |

The remaining curve is broadly linear. It is now dominated by visible vehicle
submeshes across three shadow cameras plus high-pssm/glow, projectile meshes,
and separate compatible DynamicGeometry material groups.

### Real AI combat

The less deterministic 20-tank combat A/B used the same build and opt-out:

| Path | Mean ms | p95 ms | Submissions/frame | Rendered entities~ |
|---|---:|---:|---:|---:|
| batch (`20260822_094542`) | 4.476 | 5.50 | 548.98 | 69.0 |
| legacy (`20260822_094613`) | 5.122 | 6.15 | 635.74 | 99.4 |

This is a 12.6% mean-frame improvement and 13.6% fewer submissions despite
normal AI variation. Continuous fire is the stronger controlled result.

## Distant LOD and traversal

Forty idle tanks at fixed distances (`20260822_093248`) show the existing
deformation threshold clearly:

| Distance | Mean ms | Anim ms | Skin ms | Submissions/frame |
|---:|---:|---:|---:|---:|
| 50 m | 5.647 | 1.178 | 1.012 | 692.97 |
| 100 m | 5.380 | 1.181 | 1.002 | 695.47 |
| 250 m | 2.973 | 0.091 | 0.047 | 690.97 |
| 500 m | 2.867 | 0.091 | 0.048 | 690.93 |
| 1000 m | 2.957 | 0.093 | 0.048 | 691.63 |

The vehicle contributor rows remain LOD 0 and essentially constant: each
distance still has three shadow submesh groups and high-pssm/glow main groups.
Turning the formation away at 250/1000 m likewise left approximately 691
submissions/frame (`20260822_093426`). Thus Battlezone stops most distant
animation/skinning but keeps submitting the last pose and attachments. A
future safe render-LOD/culling policy would require proof of zero visible
contribution per attachment/pass; this patch does not guess at that boundary.

## DX9 baseline

The exact same quiet/idle/firing matrix (`20260822_093541`) completed on both
renderers:

| Workload | DX11 ms / submits | DX9 ms / submits |
|---|---:|---:|
| quiet | 2.777 / 91.0 | 4.970 / 91.0 |
| 20 idle | 4.117 / 392.5 | 6.667 / 392.27 |
| 20 firing | 4.760 / 487.87 | 5.587 / 488.35 |

Ogre content and submission counts are the same, and the generic batch works
unchanged on DX9. The DX9 firing backend records 124.6 render-state, 40.7
blend-state, 246.5 texture, 48.0 texture-stage, 65.8 sampler, and 131.0 each
vertex/pixel shader sets per frame. Quiet still performs 94 render-state, 129
texture, 44 sampler, and 37 each shader sets/frame. The low-load gap is
consistent with renderer/backend/driver and state-management overhead rather
than extra Battlezone objects or different shadow behaviour: Ogre content and
submission counts are identical on both renderers. No timing experiment in this
investigation isolated the cost of D3D9 state validation specifically, so the
state-traffic counts above are a plausible mechanism, not a measured
attribution. No state cache was changed
without proof that Ogre's setter calls are redundant at the actual device.

## Stock animated-mesh source survey

Five copies each of `avfigh`, `svfigh`, `avtank`, `avrckt`, `avartl`, `avapc`,
`avwalk`, `avmine`, `avturr`, and `aspilo` were loaded and animated on DX11
(`20260822_093849`, with the one artillery startup miss repeated successfully
in `20260822_094127`). The common repaired layout is interleaved position and
normal in a 24-byte source stride, with weights/indices in an 8-byte stream,
one weight, and CPU-shadowed weight data.

| Asset | Position/normal before | Repair | Bytes | After / animation |
|---|---|---:|---:|---|
| `avmine` | GPU-only source encountered | 3 buffers | 93,384 | `posShadow=yes`, normal motion, 0 failures |
| `avturr` | GPU-only source encountered | 3 buffers | 134,208 | `posShadow=yes`, normal motion, 0 failures |
| other eight sampled ODFs | no unshadowed source queried in sampled motion | none | 0 | normal motion, 0 failures |

The generic correction handled both newly exposed assets without a special
case. Final steady intervals required no additional repairs. Visual inspection
also retained vehicle geometry, animation, thrusters, terrain, shadows, HUD,
and radar.

## Regression validation

Passed:

- Release Win32 build, zero warnings/errors;
- Ogre profiler algorithm tests;
- INI/config writer tests (23 checks, 0 failures);
- modified Lua syntax check (no Lua 5.4-only syntax; source remains Lua 5.1
  compatible);
- `git diff --check` apart from configured CRLF notices;
- DX11 and DX9 quiet, idle, flight, firing, and runtime startup;
- batch enabled and independent environment opt-out;
- profiler enabled and profiler-disabled PresentMon operation;
- 10/20/40/80 firing scaling;
- fixed-camera visual comparison of batch versus per-Entity path: projectiles,
  impacts, smoke, fire, ground marks, debris field, vehicle lighting, terrain,
  shadows, HUD, and radar remained present with no obvious difference;
- log scan found no shader/material/renderer failure, exception, or access
  violation in final sessions.

The known rare full-profiler pre-mission startup miss occurred once in the
stock sweep; the exact case passed on immediate repeat. The runtime optimization
does not depend on the full profiler.

Not claimed: Steam binaries, multiplayer, every stock animated mesh, every
weapon family, or a pixel-difference proof of every transient effect. The
GOG 2.2.301 runtime is the supported identity for this evidence.

## Remaining costs and deliberate non-changes

1. Vehicle geometry is still multiplied across three PSSM shadow cameras and
   high-pssm/glow. These passes are visibly meaningful and were retained.
2. Compatible DynamicGeometry is batched per material, but many smoke/fire/
   impact materials still render in Default and glow. Reordering or globally
   combining transparent materials risks alpha errors and was rejected.
3. Distant units keep LOD-0 render submissions after deformation work stops.
   A visibility/attachment proof is required before changing silhouettes.
4. DX9 has measurable backend/state overhead with identical Ogre work. A
   device-state cache needs correctness evidence before implementation.
5. Authored/custom debris remains exact per-Entity. Fidelity and mod
   compatibility outweigh batching unknown geometry.
6. GPU skinning remains poor ROI: corrected software skinning is sub-millisecond
   in ordinary sampled populations and is not a top-two remaining cost.
7. Rocket/howitzer forced-fire coverage is incomplete; the harness must deploy
   artillery and explicitly establish a valid selected weapon/mask first.

## Reproduction artifacts and repository status

Raw captures are under the ignored
`reverse_engineering/snapshots/live_combat` tree. Principal sessions:

- `20260822_085553`: legacy contributor attribution;
- `20260822_090342` / `20260822_090421`: chunk proxy off/on diagnosis;
- `20260822_091621`, `20260822_091734`, `20260822_091931`: first batch and
  visual/legacy comparisons;
- `20260822_092655`: weapon/flight matrix;
- `20260822_093103`: batch-enabled 10/20/40/80 scaling;
- `20260822_093248` / `20260822_093426`: distance/facing-away;
- `20260822_093541`: matched DX11/DX9 baseline;
- `20260822_093849` / `20260822_094127`: stock skin-source survey;
- `20260822_094300` / `20260822_094331`: profiler-disabled PresentMon A/B;
- `20260822_094542` / `20260822_094613`: normal combat A/B.

Investigation commits so far:

- `a828130c` — bounded render-contributor profiling and backend attribution;
- `f666045b` — technique/pass metadata, analyzer output, and weapon/flight test
  matrix extensions;
- `4957d318` — hash-gated canonical generic chunklet batch.
- `123d60ec` — technical report, profiler documentation, and roadmap status.

The branch is `agent/live-render-optimization` and is pushed to `origin`. Manually dispatched GitHub
`Build Win32` run
[`32580118488`](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/actions/runs/32580118488)
passed on `123d60ec`, including the network baseline, pinned Ogre setup,
profiler/INI tests, FXAA shader validation, Release Win32 build, output
verification, and artifact upload.

---

# Post-reconciliation addendum (2026-08-22)

Everything above this line is the **OLD** capture set, taken on branch head
`5638bce3` before the repository was reconciled. Everything below is the
**FINAL** state. Where the two disagree, the FINAL numbers govern.

## Repository reconciliation baseline

The branch was rebuilt on a deliberately re-established baseline.

- New `main` baseline SHA: **`c0bcf0ab`** — `f23b7cc3` (PR #45) plus PR #43.
- PR #43 (`agent/live-combat-scaling`) was landed first as a prerequisite. It
  was a strict ancestor of this branch, so leaving it open would have shown the
  same four commits in two open PRs. Landing it reduces this branch's own
  history from nine commits to five render-optimization commits.
- Baseline verification on `c0bcf0ab`: network-safety baseline (10 checks),
  Ogre profiler algorithm tests, INI/config tests (23 checks, 0 failures),
  DX11 Enhanced FXAA `vs_5_0`/`ps_5_0` compilation, and a clean Release Win32
  MSBuild producing `winmm.dll` (2,182,656 bytes, SHA-256
  `5D2685E1A02224496573FAF1DB7597CE73E38A45759A3CF77D324055E0EFD497`).

## Final branch ancestry

```text
c0bcf0ab  main baseline
  6b38d016  test: add deterministic live combat benchmark   -+
  9d0fb5ca  perf: avoid DX11 software skin readbacks         | landed via PR #43,
  adf484e0  docs: report live combat scaling results         | now in main
  6ff74dd9  docs: record branch validation status           -+
  a828130c  WIP: epitaxy pre-switch                         -+
  f666045b  profile: attribute live render submissions       | this PR
  4957d318  perf: batch canonical generic impact chunks      |
  123d60ec  docs: report live render optimization results    |
  5638bce3  docs: record live render validation status       |
  265c7026  Merge main (c0bcf0ab)                            |
  0ad135fd  fix: guarantee the batch always falls back       |
  <docs>    this addendum                                   -+
```

History was merged, not rebased: the investigation commits and their evidence
are preserved exactly as they were pushed. `265c7026` is a merge commit, not a
replayed history, and no commit on this branch was rewritten onto `c0bcf0ab`.
Any earlier wording describing this branch as *rebased* onto the new baseline
was wrong and has been corrected.

The subject line of `0ad135fd` says "guarantee". Read that as the batch
*ownership* guarantee, which is real; the same-frame Entity restoration it also
performs is demonstrated rather than guaranteed. See "What is guaranteed, and
what is only demonstrated" below.

## Unit-scale safety change

`AppendGenericChunkBatchGeometry()` applies orientation and translation to the
baked positions. Once a chunklet is inside the shared ManualObject section
there is no per-chunk scene node left to carry a scale, so a scaled chunk would
be batched at the wrong size with nothing to detect it.

`IsUnitScaleForGenericChunkBatch()` now gates classification: a tracked
transform whose scale is not `(1, 1, 1)` within `1e-3` per component (or is
non-finite) falls back to the per-Entity fidelity path.

**This is a latent-defect barrier, not a fix for observable breakage, and the
report should not be read as claiming otherwise.** `ChunkProxyTransform::scale`
is structurally unit today: `TryBuildOgreQuaternionFromLegacyTransform()`
normalises the legacy basis vectors — which is where a `LegacyMat3` would carry
scale — and `TryGetChunkProxyTransform()` never writes the field. Every
assignment to `.scale` in `bzr_hooks.cpp` writes `(1, 1, 1)` or copies another
default. The gate converts that from an assumption into an enforced invariant.

One honest qualification: the per-Entity fallback calls
`TryUpdateChunkMeshProxyTransform()`, which sets node position and orientation
only. It does **not** apply scale either. So the fallback does not render a
scaled chunk correctly — what the gate guarantees is that a scale is never
silently baked away into shared geometry, and that the chunk keeps rendering
through the fidelity path. Since no path populates scale, neither behaviour is
observable today.

Arbitrary scale in the batch is deliberately not implemented: it would need
inverse-transpose handling for normals and tangents, and no evidence shows
stock or modded generic chunklets require it.

Rejections are counted and logged with a 5-second throttle. In the forced test
below, **152,618 rejections produced 3 log lines**.

## Batch-failure fallback: a real defect, found and repaired

This was not a hardening pass. The pre-existing code had a genuine
missing-debris bug.

`UpdateChunkProxySlotPosition()` hides the per-Entity mesh proxy — and for a
slot born batch-eligible, never creates one — the moment a slot is classified
batch-ready. If `RebuildAndSubmitGenericChunkBatch()` then returned `false`,
`SubmitChunkProxiesToRenderQueue()` fell through to the per-Entity loop, which
skips every slot failing its `!slot.entity` check. That is precisely the set of
slots that had just been classified. The debris disappeared.

The `!sceneManager` early return makes this worse than a one-frame glitch: it
returns `false` *without* clearing `g_GenericChunkBatchRuntimeAvailable`, so the
slots stayed batch-classified and kept vanishing on subsequent frames.

`RehydrateGenericChunkBatchSlotsToEntities()` now demotes every
batch-classified slot back to the Entity path before the per-Entity loop reads
the slots, using the transform the batch would have baked. Recovering a
partially constructed ManualObject is deliberately not attempted; the Entity
path is the known-good fidelity path and is cheap to rehydrate.

### What is guaranteed, and what is only demonstrated

This distinction matters, because the function does two different things with
two different strengths of assurance.

**Guaranteed by construction — batch ownership is always released.**
`slot.genericBatchTransformReady` and `slot.genericBatchKind` are cleared
*before* any Ogre call and on every path, including the two `continue` paths.
No slot can remain stranded claiming the batch owns it, so the pathological
pre-fix state — a slot permanently classified batch-ready while nothing draws
it — is structurally unreachable. This one is a real invariant.

**Attempted, not guaranteed — same-frame Entity restoration.** Restoration
calls `EnsureChunkMeshProxySlot()` and then `TryUpdateChunkMeshProxyTransform()`.
Both can return `false` (Ogre `SceneManager` unavailable, entity creation
failing, a missing resolved Ogre export). Either failure `continue`s, and the
slot is counted in `demoted` but not in `restored`. Such a slot is invisible
for that frame and is retried on subsequent frames through the ordinary
per-Entity path, because its batch flags are already cleared. So the code does
**not** mathematically guarantee that every demoted slot is restored in the
same frame, and this report does not claim that it does.

**What the evidence shows.** In the forced-failure test below, every logged
rehydrate line reported `demoted == restored`, and `world-rq-submit` entries
for the chunk meshes appeared in the same millisecond. Across 39,688 counted
rehydrations there was no observed instance of `demoted > restored`. The
correct reading is therefore: *on the tested workload, same-frame restoration
was complete*. Ogre-side Entity creation failure remains theoretically
possible; it simply never occurred in the measured runs, and if it did, the
consequence is bounded to a one-frame gap for the affected chunklets rather
than the permanent disappearance the pre-fix code produced.

## Forced-failure regression test and its result

`OPENSHIM_FORCE_GENERIC_CHUNK_BATCH_FAILURE=1` makes
`RebuildAndSubmitGenericChunkBatch()` report failure **after** the eligible
slots have been counted — the same window a real Ogre construction failure
would land in. `OPENSHIM_FORCE_GENERIC_CHUNK_NON_UNIT_SCALE=1` forces a
`(1.25, 0.75, 1.0)` scale so the scale gate, which has no natural trigger, can
be exercised. Both are environment-gated, log that they are active, and are
unreachable from gameplay.

The A/B is the proof. Same build, same 20-tank DX11 firing workload, same
forced-failure flag; the only difference is whether the rehydration call is
compiled in:

| | Rehydration removed (pre-fix behaviour) | Rehydration present (final) |
|---|---:|---:|
| Forced failures injected | 8 | 8 |
| Rehydrate events | 0 | 24 logged (39,688 counted) |
| Per-Entity `chunk1`/`chunk2` submissions | **0** | 24 logged |
| Unhandled exceptions | 0 | 0 |

Zero submissions through **any** path confirms the debris was entirely dropped
before the fix. Afterwards every rehydrate line reported `demoted == restored`,
and `world-rq-submit` entries for `chunk1/chunk1.mesh` and `chunk2/chunk2.mesh`
appear in the same millisecond as the rehydrate line — so on this workload the
restoration was complete and no missing-debris interval was observed. Sustained for the whole run with `runtimeAvailable=1`
and no stale ManualObject, duplicate rendering, or crash.

Checklist requested for this test:

1. canonical `chunk1`/`chunk2` detected — yes (`batching=enabled`, correct byte
   counts and FNV-1a hashes);
2. slots classified for batching — yes (`eligible=12`, rising to 37);
3. forced failure occurs after batch setup — yes, by construction;
4. per-Entity fallback renders the same frame — yes on this workload,
   same-millisecond `world-rq-submit` and `demoted == restored` on every
   logged line; not a construction-level guarantee (see above);
5. subsequent frames stable — yes, 39,688 rehydrations over the run;
6. no stale ManualObject — the object is never begun on the forced path;
7. no duplicate rendering — `demoted == restored` and the batch submitted
   nothing;
8. policy after failure — a *forced* failure deliberately leaves
   `runtimeAvailable=1`; a real construction failure still clears it and
   permanently stands the batch down;
9. mission teardown — scene-teardown forget hooks (`clearScene`,
   `destroyAllMovableObjects`) install and clear the batch flags. **Save/load
   and interactive menu-driven mission exit were not exercised in this pass.**

## FINAL performance

All FINAL runs are GOG 2.2.301, `lcbench`, `avtank`, 50 m, facing, on branch
head `0ad135fd`.

### Profiler-disabled PresentMon, 20 tanks firing, DX11 — the headline result

Columns read baseline first, so left-to-right is the direction of the change:
**legacy opt-out is the before, batch is the after.**

| Metric | Legacy opt-out (before) | Batch (after) | Change |
|---|---:|---:|---:|
| Frame mean | 7.215 ms | 4.204 ms | **-41.7%** |
| Frame p95 | 8.071 ms | 4.908 ms | -39.2% |
| Frame p99 | 8.480 ms | 5.366 ms | -36.7% |
| Frame max | 9.530 ms | 13.150 ms | +38.0% |
| FPS | 138.60 | 237.84 | **+71.6%** |
| GPU active | 3.606 ms | 3.789 ms | +5.1% |
| Samples | 1,399 | 2,401 | |

Stated as prose so the direction cannot be misread: frame mean fell from
**7.215 ms legacy to 4.204 ms batched (-41.7%)**, and FPS rose from **138.60
legacy to 237.84 batched (+71.6%)**.

GPU-active time is essentially unchanged while CPU frame time drops by 42%,
which is the expected signature of a render-*submission* saving rather than a
GPU saving. The single worse number is frame max: the batched run's 13.150 ms
outlier exceeds the legacy run's 9.530 ms. With one sample each this is not
evidence of a systematic hitch, but it is not evidence against one either, and
it is recorded rather than averaged away.

### Profiler-enabled DX11

| Workload | Legacy opt-out (before) | Batch (after) | Submissions change |
|---|---|---|---|
| 20 firing | 29.640 ms / p95 46.94 / p99 61.56 / **866.69** submits | 6.526 ms / p95 9.594 / p99 10.50 / **488.57** submits | -43.6% |
| 80 firing | 32.965 ms / p95 41.47 / p99 55.72 / **2,565.87** submits | 19.626 ms / p95 25.03 / p99 27.13 / **1,598.42** submits | -37.7% |
| 20 idle | 5.199 ms / **391.84** submits | 5.279 ms / **391.64** submits | none |
| 80 idle | 14.914 ms / **1,307.67** submits | 10.880 ms / **1,304.14** submits | none |

**The frame-time column in this table is not trustworthy** and should not be
quoted. These captures ran while the machine was also compiling; the 20-tank
legacy figure (29.64 ms mean, 61.56 ms p99) is slower than the same run's
80-tank figure, which is incoherent. Use the PresentMon table above for timing.

The **submission** counts are load-independent and are the robust result. They
reproduce the OLD capture almost exactly (OLD: 488.42 and 1,597.98 batched),
which is itself useful evidence that the scale gate and rehydration changed
nothing on the normal path.

The idle rows are the control: with no impacts there is no debris, and the
batch changes nothing (391.64 vs 391.84). The optimization only touches impact
chunklets.

### DX9

| Workload | Legacy opt-out (before) | Batch (after) | Change |
|---|---|---|---|
| 20 firing | 7.961 ms / p95 8.88 / **849.38** submits | 4.869 ms / p95 5.75 / **487.66** submits | **-38.8% ms, -42.6% submits** |
| 20 idle | 4.436 ms / **391.73** submits | 4.474 ms / **391.70** submits | none |

The batch is confirmed active on DX9 (`active=112 vertices=2016 sections=1`).
DX9 frame times were captured in a quieter interval than the DX11
profiler-enabled set and are internally consistent.

## FINAL — aggregate-batch culling, ordering and LOD investigation

This section was added after the corrections above. It exists because collapsing
roughly a hundred independent Ogre `Entity` renderables into one `ManualObject`
can change renderable-level culling, render-queue granularity, depth sorting and
pass selection even when geometry, material and transforms are preserved
exactly. Each of those was investigated separately and measured.

### The `dispersed` benchmark scenario

`lcbench` gained a `dispersed` scenario for this. It places firing pairs in
clusters on a ring around the player, evenly spaced in bearing and measured from
the player's own front vector:

- `clusterCount` clusters (default 4) at `clusterRadius` metres (default 300);
- cluster 0 straight ahead, so exactly one cluster is inside the frustum and the
  other three are roughly 90, 180 and 270 degrees off the sight line — two
  lateral, one directly behind the camera;
- pairs straddle their cluster centre on the radial axis 40 m apart and shoot
  each other, so impacts and the chunklets they spawn stay local to their own
  cluster;
- `spinSeconds` re-points the player craft at the next cluster on a fixed
  cadence, which is what moves debris clusters in and out of the frustum without
  any synthetic input;
- the layout was verified offline against a stubbed BZ Lua API before it was ever
  run in the game.

Measured field geometry at `count=40`, 4 clusters, 300 m radius: cluster
centroids at bearings 0.0/90.0/180.0/270.0 degrees, each 300.0 m out, total
debris field span **640 m** on both horizontal axes. At runtime the live chunk
set spanned **659–687 m**.

### Ogre's aggregate bounds grow monotonically — measured

`ManualObject::getBoundingBox()` and `getBoundingRadius()` are now read back once
per second and logged beside the tight bounds of the live chunk set.

| Time into run | Ogre AABB span (x, y, z) | Tight span (x, y, z) |
|---|---|---|
| +0 s | 640.4, 24.4, 28.9 | 640.1, 24.3, 28.6 |
| +1 s | 648.4, 31.7, 37.1 | 648.2, 31.5, 36.5 |
| +3 s | 664.8, 35.2, 57.2 | 664.1, 35.2, 56.8 |
| +5 s | 671.4, 35.9, 74.0 | 665.9, 30.2, 63.7 |
| +11 s | 674.9, 36.5, 74.5 | 667.4, 34.9, 70.8 |
| +12 s | 692.2, 36.5, 110.1 | 659.0, 32.8, 63.9 |
| +14 s | 692.9, 36.5, 111.2 | 664.0, 31.3, 54.0 |

The Ogre box only ever moves outward. The tight box oscillates as debris expires
and respawns; the Ogre box does not follow it back down. `extentEnum` stayed `1`
(`EXTENT_FINITE`) throughout.

**Measured fact:** the aggregate AABB is a monotone union of every chunk position
the batch has ever contained, not the bounds of the currently live set. This is
consistent with Ogre resetting `mAABB` only in `ManualObject::clear()` and not in
`beginUpdate()`; OpenShim never calls `clear()`. Over a long mission the box would
keep growing toward the map extents.

### …and it does not matter, because neither path is frustum-culled

**Measured fact:** the batch does not go through `SceneManager::_findVisibleObjects`
for its submission. `RebuildAndSubmitGenericChunkBatch()` calls
`ManualObject::_updateRenderQueue()` directly, from inside the game's own
`_updateRenderQueue` override at `0x00679570`. Nothing tests the aggregate AABB
against the frustum on that path.

**The legacy path has exactly the same property.** `SubmitChunkProxiesToRenderQueue()`
calls `RenderQueue::addRenderable` per sub-entity, also directly. Both the
per-Entity path and the batch submit every live chunklet every frame regardless of
where the camera is pointing.

So the aggregate AABB **causes no excess submission**, because there was no culling
to lose. This was the specific risk the dispersed test was built to detect, and the
answer is that batching does not introduce a culling regression — it inherits an
existing no-culling property and reduces the number of unculled renderables from
roughly a hundred to one.

Dispersed workload, DX11, 40 units, 4 clusters, 300 m radius, camera rotating
between clusters every 3 s:

| | Legacy opt-out (before) | Batch (after) | Change |
|---|---:|---:|---:|
| Ogre submissions/frame | 1,266.9 | 745.4 | **-41.2%** |
| Ogre render CPU | 0.458 ms/f | 0.330 ms/f | -27.9% |

The reduction with three quarters of the debris field off-screen is the same size
as the reduction with everything in front of the camera, which is what the
no-culling finding predicts.

**Not implemented:** spatial subdivision of the batch. The measurement gives no
reason for it. Excess submission caused by aggregate bounds is the problem it would
solve, and that problem does not exist here.

### Material and pass semantics: opaque, therefore order-independent

This is settled from the shipped material scripts rather than inferred from the
geometry being identical.

`scarpmat2` is declared in `BZ_ASSETS/pc/materials/npscr1.material` as
`material scarpmat2 : BZBase`. It sets four texture aliases and four scalar
parameters and adds no pass state of its own. Every technique it therefore has
comes from `BZ_ASSETS_CORE/common/BZ_MATERIALS/BZBase.material`.

**Measured fact:** `BZBase.material` contains no `scene_blend`,
`separate_scene_blend`, `depth_write`, `depth_check`, `alpha_rejection` or
`transparent_sorting` directive anywhere in the file — not in the `high-pssm`
family, not in the `high`/`medium`/`low`/`lowest` families, and not in the `glow`
technique. Every pass runs with Ogre's defaults: `scene_blend one zero`, depth
write on, depth check on.

**Inference from that fact:** all of these techniques are fully opaque. Ogre places
opaque renderables in the solid group of `RENDER_QUEUE_MAIN`, where the visible
result is resolved by the depth buffer and is independent of submission order.
Combining chunklets into one renderable therefore cannot produce a transparency or
ordering artefact, because there is no blending and no back-to-front dependency to
disturb. Submission order still affects early-Z efficiency, which is a performance
question, not a correctness one.

The `glow` technique is included in that statement: it binds only `EmissiveMap` with
`Textured_vertex`/`Textured_fragment` and declares no blend state either, so the glow
pass is opaque within its own scheme as well.

### A real semantic deviation the batch does introduce: material LOD

The dispersed run surfaced something the 50 m firing benchmark could not.

**Measured fact, legacy path**, chunk contributor rows across the measurement
window:

| Scheme | LOD indices observed |
|---|---|
| `high-pssm` | 1 and 2 |
| `glow` | 0 only |

**Measured fact, batch path**: `high-pssm` lod=0 and `glow` lod=0, always.

`BZBase` declares `lod_values 250 300`, and supplies `high-pssm` techniques at
`lod_index` 0, 1 and 2 — `BZPassSchemeHighPSSM`, then `BZPassSchemeMediumNoShadow`,
then `BZPassSchemeLowNoShadow`. A per-Entity chunklet beyond 250 m therefore drops
to the cheaper medium pass and beyond 300 m to the low pass, and both of those drop
the three shadow-map texture units. The dispersed clusters sit at 300 m, so the
legacy rows land on LOD 1 and LOD 2 exactly as the material intends.

The batch never does. The cause is not the scene node position: `ManualObjectSection`
does not override `getTechnique()`, and the base implementation is

```cpp
virtual Technique* getTechnique(void) const { return getMaterial()->getBestTechnique(0, this); }
```

with the LOD index hardcoded to `0`. Verified against the pinned Ogre 1.10 reference
headers (`OgreRenderable.h:89`, `OgreManualObject.h`) and independently confirmed by
the measured `lod=0` rows.

**Consequence, stated honestly.** Batched chunklets are always shaded with the full
`BZPassSchemeHighPSSM` pass, including shadow-map sampling, at every distance. Stock
per-Entity chunklets drop to cheaper unshadowed passes past 250 m. The deviation is
one-directional — batched distant debris is shaded to a *higher* standard than stock,
never a lower one — and it is a fragment-cost deviation, not a CPU one, which is
consistent with the +5.1% GPU-active time measured in the PresentMon A/B. It is a
departure from stock pass selection and is recorded as such rather than described as
"material preserved, therefore identical".

The `glow` technique carries no `lod_index` at all, so it defaults to 0 and every
chunklet participates in glow at full quality at any distance — on **both** paths.
That part is stock behaviour, not something batching changed.

Restoring stock LOD semantics would mean partitioning the batch by the 250 m and
300 m thresholds into three renderables whose nodes carry representative distances.
That is a candidate for follow-up work, ranked below, and is deliberately not part of
this PR.

### The batch is rebuilt three times per rendered frame

An opt-in counter (`OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS`, off by default, and when
off not even the counters are touched) recorded how often
`SubmitChunkProxiesToRenderQueue()` runs.

| Run | Submit calls/s | Rebuilds/s | FPS | Rebuilds per frame |
|---|---:|---:|---:|---:|
| dispersed, static camera | 663 | 663 | 219 | **3.03** |
| dispersed, rotating camera | 552 | 552 | 183 | **3.02** |

**Measured fact:** the game drives its `_updateRenderQueue` override about three
times per rendered frame — one traversal per active scheme — and OpenShim tears down
and rebuilds the entire `ManualObject` on every one of them. At ~250 live chunks that
is roughly 4,500 vertices re-transformed and re-emitted three times per frame instead
of once.

The profiler's contributor table independently shows the batch renderable being
submitted `2.0/f` under `high-pssm` and `2.0/f` under `glow`.

This is redundant work that this PR introduced and did not notice, and it is the
highest-confidence next optimization: build the geometry once per frame and let later
calls in the same frame re-submit the object that is already current. It is **not**
fixed here, because it is a separate optimization and belongs on its own branch with
its own opt-out and its own A/B.

### Visual verification: not completed in this pass

Side-by-side dispersed captures with the batch enabled and disabled were attempted
with camera rotation between clusters. **The Windows session locked partway through
the capture set, so every screenshot recorded the lock screen rather than the game.**
The captures are discarded and no visual claim is made from them.

What can be said: the game continued rendering throughout, and the submission and
frame telemetry from those runs matches the unlocked runs closely (batch 739–764
submits/f, legacy 1,002–1,102 submits/f), so the numeric results are usable and are
reported. The visual comparison itself is outstanding and is listed under known
limitations.

## FINAL validation performed

18 harness runs plus 3 manual capture launches, all on `0ad135fd`.

Build and static:

- Release Win32 MSBuild — clean, no new warnings;
- Ogre profiler algorithm tests — passed;
- INI/config tests — 23 checks, 0 failures;
- network-safety baseline — 10 checks passed;
- DX11 Enhanced FXAA `vs_5_0` and `ps_5_0` — compiled;
- `git diff --check` — clean;
- no Lua was modified in this change, so no Lua re-validation was required.

Runtime DX11: idle and firing at 20 and 80, batch enabled and
`OPENSHIM_DISABLE_GENERIC_CHUNK_BATCH=1` opt-out; profiler-disabled PresentMon
A/B; forced batch-failure; forced non-unit scale.

Runtime DX9: idle and firing at 20, batch enabled and opt-out.

Log scan across all 18 harness runs: **0** `[ERROR]`, unhandled access
violations, shader failures, material failures, `Ogre::Exception`, stale
scene-object errors, or renderer failures.

Visual: side-by-side firing-phase captures with the batch enabled and disabled.
Both render terrain, vehicle geometry, impact fire, smoke plumes, ground scorch
marks, HUD and radar, with no missing or duplicated geometry apparent. These
frames were **not** time-synchronized, so effect shapes differ between them;
this is a sanity check, not a pixel-difference proof. The fixed-camera
comparison in the OLD section remains the stronger visual evidence, and the
normal-path rendering code is unchanged by this addendum's commits.

## FINAL — re-validation on the corrected head

The matrix below was re-run after the corrections and the new diagnostics, on
the exact head this PR proposes to merge. It supersedes the earlier `0ad135fd`
matrix for the runs it repeats; the earlier one is retained above.

Twelve harness runs plus one re-run of the DX11 idle control. Every run is GOG
2.2.301, `lcbench`, `avtank`, profiler enabled, DX11 unless stated.

### Submissions — the robust result

| Workload | Legacy opt-out (before) | Batch (after) | Change |
|---|---:|---:|---:|
| DX11 20 firing | 797.6 | 486.5 | **-39.0%** |
| DX11 80 firing | 2,527.7 | 1,599.7 | **-36.7%** |
| DX11 40 dispersed, rotating | 1,266.9 | 745.4 | **-41.2%** |
| DX9 20 firing | 817.2 | 487.7 | **-40.3%** |
| DX11 20 **idle** (control) | 391.7 | 391.0 | none |

The idle control is unchanged, as it must be: with no impacts there is no debris
and the batch has nothing to collapse.

### Ogre render CPU, from the profiler's own accounting

| Workload | Legacy opt-out | Batch | Change |
|---|---:|---:|---:|
| DX11 20 firing | 0.355 ms/f | 0.261 ms/f | -26.5% |
| DX11 80 firing | 0.967 ms/f | 0.758 ms/f | -21.6% |
| DX11 40 dispersed | 0.458 ms/f | 0.330 ms/f | -27.9% |
| DX9 20 firing | 0.341 ms/f | 0.236 ms/f | -30.8% |
| DX11 20 idle | 0.189 ms/f | 0.183 ms/f | none |

### Frame times — captured under a locked session, labelled accordingly

**These samples are contaminated and are reported, not relied on.** The Windows
session locked partway through this pass. The game kept rendering — submission
counts from the locked runs match the unlocked ones closely — but frame pacing
under a locked session is not a trustworthy measurement of user-visible
performance.

| Workload | Legacy opt-out | Batch | Change |
|---|---:|---:|---:|
| DX11 20 firing | 7.668 ms / 130.6 FPS | 4.247 ms / 235.8 FPS | -44.6% ms |
| DX11 80 firing | 20.238 ms / 49.4 FPS | 11.399 ms / 87.5 FPS | -43.7% ms |
| DX11 40 dispersed | 10.104 ms / 100.9 FPS | 4.925 ms / 206.0 FPS | -51.3% ms |
| DX9 20 firing | 7.943 ms / 126.1 FPS | 4.895 ms / 204.2 FPS | -38.4% ms |

They are in the same direction and roughly the same magnitude as the clean
profiler-disabled PresentMon A/B reported above (7.215 ms legacy to 4.204 ms
batched, -41.7%), which is the number that should be quoted.

**The profiler-disabled PresentMon A/B was not repeated on this head.** The
commits added since `0ad135fd` change no rendering behaviour: they add a
once-per-second bounds readback inside an existing log throttle, an opt-in
counter that is not even incremented when its environment flag is absent, a new
benchmark scenario in Lua, and documentation. The render path is byte-for-byte
the same, and the measured submission counts on this head reproduce the earlier
ones (486.5 vs 488.57 at 20 firing, 1,599.7 vs 1,598.42 at 80 firing), which is
the evidence that nothing on the normal path moved.

### Diagnostic seams, re-exercised on this head

`OPENSHIM_FORCE_GENERIC_CHUNK_BATCH_FAILURE=1`, DX11 20 firing:

- every logged rehydrate line reported `demoted == restored` — 109/109, 115/115,
  107/107, 118/118 — across **165,996** counted rehydrations;
- per-Entity `chunk1`/`chunk2` submissions present at 55.6 and 57.6 per frame,
  so the debris is drawn through the fallback;
- 742.6 total submissions/frame, between the batch (486.5) and the legacy
  (797.6) figures, consistent with the chunklets having been demoted to
  individual Entities;
- no unhandled exception.

`OPENSHIM_FORCE_GENERIC_CHUNK_NON_UNIT_SCALE=1`, DX11 20 firing:

- the `(1.2500, 0.7500, 1.0000)` rejection fires and falls back per Entity;
- **253,567 rejections produced 3 log lines** — the throttle works;
- 807.4 submissions/frame, i.e. indistinguishable from the legacy path, which is
  the correct outcome when every chunklet is rejected.

`OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS=1` announced itself in the log and
produced the rate rows quoted above; with the flag absent, no rate row appears.

### Build and static, on this head

- Release Win32 MSBuild — clean, no new warnings beyond the pre-existing
  `C4505`/`STL4038` set already present on `main`;
- Ogre profiler algorithm tests — passed;
- INI/config tests — 23 checks, 0 failures;
- network-safety baseline — passed;
- `git diff --check` — clean;
- `lcbench.lua` re-validated: `luac -p` clean, and the dispersed layout was
  exercised against a stubbed BZ Lua API before any game run.

### Log scan

21 `openshim.log` files across every run in this pass were scanned for
`[ERROR]`, unhandled access violations, `Ogre::Exception`, shader failures,
material failures, `batch update threw`, `procs-missing` and
`exports unavailable`. **All eight patterns: 0 occurrences.**

### Two unhandled crashes — pre-existing, not from this branch

Two launches out of 22 died with an unhandled access violation about 100 ms into
startup, before any mission loaded:

```text
[CRASH] 2026-08-22 12:25:36 unhandled code=0xC0000005 eip=0x6DFDA917 (WINMM.dll+0x0007A917)
[CRASH] 2026-08-22 15:09:12 unhandled code=0xC0000005 eip=0x6DFDA9F7 (WINMM.dll+0x0007A9F7)
```

Symbolized against the matching `winmm.pdb`:

- `0x7A9F7` and `0x7A917` -> `PatchIatFunction`,
  `src/patches/dx11_colorspace_diagnostic.cpp`
- callers -> `DiscoveryThreadProc`, same file

The faulting address is a page-boundary offset reached from the IAT store that
immediately follows a `VirtualProtect(PAGE_READWRITE)` which returned success —
the same class of defect already recorded for `PatchIATByFuncName` in
`file_io_hooks.cpp:236`, but a different site, and this one runs on a background
discovery thread that races the loader while `RenderSystem_Direct3D11.dll` is
being mapped.

`src/patches/dx11_colorspace_diagnostic.cpp` is **byte-identical to `main`**
(verified by content hash with line endings normalised) and is touched by no
commit in this PR. It is tracked as separate work.

Note again that *first-chance* `0xC0000005` records appear in every run of this
codebase and are expected: the chunk-proxy and Ogre probes are deliberately
wrapped in `__try`/`__except`. Only the `unhandled` record is a real crash.

## A pre-existing crash found during validation (not this branch)

One of the 21 launches died with an unhandled access violation about 100 ms
into startup, before any mission loaded:

```text
[CRASH] 2026-08-22 11:35:20 unhandled code=0xC0000005 eip=0x6DFF70C2
        (WINMM.dll+0x000970C2) write=0x00869140 tid=37464
```

Symbolized against the matching `winmm.pdb`:

- `0x970C2` -> `PatchIATByFuncName`, `src/patches/file_io_hooks.cpp:236`
- `0x98B93` -> `ApplyTrnSaveNormalizeHooks`, `src/patches/file_io_hooks.cpp:759`
- `0xF24CE` -> `RunPatcher`, `src/engine/patcher.cpp:700`

Line 236 is `*iatEntry = newFunc;`, immediately after a
`VirtualProtect(PAGE_READWRITE)` that returned success — so the page protection
was changed by another thread between the call and the store. `0x00869140` is
in the game's import address table.

`src/patches/file_io_hooks.cpp` is **byte-identical to `main`** on this branch
and is not touched by any commit in this PR. Two further unhandled access
violations were recorded in this environment earlier the same day, before this
branch's changes were ever built. It is tracked as separate work, and PR #42
rewrites this file, so a fix belongs there or alongside it.

Note that *first-chance* `0xC0000005` records appear in every run of this
codebase and are expected: the chunk-proxy and Ogre probes are deliberately
wrapped in `__try`/`__except`. Only the `unhandled` record is a real crash.

## Known limitations, restated for the final state

1. The unit-scale gate is a barrier against a future defect, not a fix for one
   observed. The per-Entity fallback does not render scale either.
2. A *forced* batch failure intentionally leaves the batch runtime available,
   so the same run keeps re-failing and re-rehydrating. Only a real failure
   stands the batch down permanently. Do not read the forced test as proving
   the stand-down policy.
3. Save/load and interactive menu-driven mission exit were not exercised in
   this pass. The teardown forget hooks are installed and the OLD capture set
   covers mission startup and shutdown, but no save/load cycle was run.
3a. **Visual verification was not completed on the corrected head.** The Windows
   session locked during the dispersed capture set and every screenshot recorded
   the lock screen. The captures were discarded. The prior fixed-camera
   comparison stands, and the render path is unchanged by the commits added
   since, but a fresh side-by-side dispersed comparison is outstanding.
3b. **Batched chunklets always render at material LOD 0.** `ManualObjectSection`
   inherits `Renderable::getTechnique()`, which hardcodes the LOD index to 0, so
   the batch never drops to the `lod_index` 1 and 2 techniques that `BZBase`
   declares at 250 m and 300 m. Legacy per-Entity chunklets do. The deviation is
   one-directional (higher shading quality than stock, never lower) and costs
   fragment work rather than CPU, but it is a departure from stock pass
   selection and is not claimed otherwise.
3c. **The batch is rebuilt about three times per rendered frame**, because the
   game drives its `_updateRenderQueue` override once per active scheme and the
   rebuild is unconditional. This is redundant work introduced by this PR. It is
   measured, documented, and deliberately left for a separate branch rather than
   fixed here.
3d. **The profiler-disabled PresentMon A/B was not repeated** on the final head.
   The added commits change no rendering behaviour and the submission counts
   reproduce, but the headline timing number is inherited from `0ad135fd`
   rather than re-measured.
4. Frame max regressed in the single PresentMon batched sample (13.150 ms vs
   9.530 ms). One sample each; unexplained.
5. Profiler-enabled DX11 frame times in this pass are contaminated by
   concurrent machine load and are reported only so they are not hidden.
6. DX9's remaining low-load gap is consistent with backend/driver and
   state-management overhead; no experiment isolated state-validation cost.
7. Not claimed: Steam binaries, multiplayer, every stock animated mesh, every
   weapon family, or a pixel-difference proof of every transient effect.

## FINAL commit SHAs

- `265c7026` — merge of baseline `c0bcf0ab` into the branch;
- `0ad135fd` — unit-scale gate, same-frame rehydration fallback, and the two
  diagnostic test seams.

Raw FINAL captures are under the ignored
`reverse_engineering/snapshots/live_combat` tree plus the out-of-tree
`C:\bzrwt-final` session directories (`dx11_batch_on`, `dx11_batch_off`,
`dx9_batch_on`, `dx9_batch_off`, `pm2_batch_on`, `pm2_batch_off`,
`forced_failure`, `scale_fallback`, `visual`).
