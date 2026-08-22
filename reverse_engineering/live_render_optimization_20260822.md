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
therefore renderer/backend/driver overhead and repeated D3D9 state validation,
not extra Battlezone objects or shadow behavior. No state cache was changed
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

The branch is `agent/live-render-optimization` and is pushed to `origin`. It
has not been merged and no PR was opened. Manually dispatched GitHub
`Build Win32` run
[`32580118488`](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/actions/runs/32580118488)
passed on `123d60ec`, including the network baseline, pinned Ogre setup,
profiler/INI tests, FXAA shader validation, Release Win32 build, output
verification, and artifact upload.
