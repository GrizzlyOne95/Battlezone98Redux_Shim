> **Status: first repair experiment, superseded but retained.**
>
> This document records the pass that *found* the missing-culling defect and the
> private frustum test built to work around it. Its measurements stand and are
> not restated elsewhere. Two of its conclusions were later overturned:
>
> * its stated reason for not restoring finite bounds -- that Redux might depend
>   on infinite craft bounds for targeting or picking -- is wrong. The executable
>   creates no Ogre scene query at all; Ogre is the renderer and the legacy
>   Battlezone engine owns physics, collision, AI, targeting and weapons.
> * the `Mesh::_setBounds(infinite)` call site it could not locate was located.
>   It is the first-person view entity builder writing an "always visible" policy
>   onto a shared craft mesh.
>
> The shipped architecture is now the restored-bounds repair in
> `craft_bounds_architecture_20260822.md`, which reaches identical main-view
> decisions and additionally fixes shadow-cascade traversal. The private cull in
> `ogre_entity_frustum_cull.inl` is retained as an opt-in fallback.

# Craft frustum culling: a missing-culling defect and its repair (2026-08-22)

Starting commit: `8cf4e2ee` (`main`, immediately after PR #46 merged).
Branch: `agent/distant-unit-submissions`, reconciled onto that main at `bd4589ac`.
Runtime: GOG Battlezone 98 Redux 2.2.301, `lcbench`, `avtank`, DX11 and DX9.

Everything below is labelled **measured fact**, **inference** or **hypothesis**.
Numbers from earlier passes are labelled OLD where they appear.

## Summary

The previous triage recommended attacking distant-unit render submissions and
listed glow participation as the first experiment. Re-measuring on the post-#46
baseline **falsified the premise of that recommendation** and replaced it with a
better one.

Battlezone 98 Redux gives every craft mesh an **infinite Ogre bounding box** at
runtime. Ogre's frustum test short-circuits on an infinite box, so no craft is
ever culled, by any camera, at any distance. Twenty tanks fifty metres *behind*
the camera cost exactly as many main-view submissions as twenty tanks in front
of it. That is not a distance problem to be tuned; it is culling that never runs.

Restoring a per-object frustum test for the main camera, using Ogre's own
frustum planes and the asset's own bounds, removes **25.3% of all Ogre
submissions per frame** on both DX11 and DX9 when craft are off-screen, and is
neutral to slightly positive when they are not.

## Measured facts

### 1. Craft are never frustum-culled

DX11, static camera, profiler enabled, 20 tanks, contributor rows per material:

| Row | `orientation=facing` (all 20 in view) | `orientation=away` (all 20 behind) |
|---|---:|---:|
| `avtank00` `high-pssm` | 20.6 /f | 20.6 /f |
| `avtank01` `high-pssm` | 20.6 /f | 20.6 /f |
| `avheadlight00` `high-pssm` | 20.6 /f | 20.6 /f |
| all three `glow` rows | 20.6 /f each | 20.6 /f each |
| each of 3 PSSM shadow cascades | 61.9 /f | 61.8 /f |

Identical. Reproduced on the legacy chunk-proxy build as well, so this is stock
Redux behaviour and not something PR #46 introduced.

The dispersed scenario says the same thing more strongly: 41 craft in four
clusters on a 300 m ring, only ~10 inside the frustum, and `avtank01 high-pssm`
still reports **40.9 submissions/frame** — every craft in the mission.

### 2. The cause is an infinite bounding box on the mesh

An opt-in per-type census (`OPENSHIM_FRUSTUM_CULL_CENSUS=1`) keyed on vtable and
`AxisAlignedBox::Extent`:

```text
type=Ogre::Entity extent=1 meshExtent=1 sampleMesh=RenderableTileCluster_0x4_0x2 seen=19421
type=Ogre::Entity extent=2 meshExtent=2 sampleMesh=avtank.mesh                   seen=25837
type=Ogre::Light  extent=0 sampleMesh=<none>                                     seen=24664
```

`extent=2` is `EXTENT_INFINITE`. `meshExtent=2` places it on `Mesh::getBounds()`
itself, not on an attachment merged in by `Entity::getBoundingBox()`. Terrain
entities keep finite bounds, so this is specific to craft.

**The shipped assets are fine.** Parsing the `M_MESH_BOUNDS` chunk directly out
of the `.mesh` files:

| Mesh | min | max | radius |
|---|---|---|---:|
| `avtank.mesh` | (-3.16, -0.06, -3.74) | (3.16, 2.76, 2.96) | 4.27 |
| `svtank.mesh` | (-4.28, -0.09, -3.58) | (4.27, 3.70, 4.82) | 5.05 |
| `avfigh.mesh` | (-2.23, 0.04, -2.98) | (2.23, 2.78, 3.03) | 3.19 |
| `gatst00.mesh` | (-0.13, -0.11, -0.29) | (0.13, 0.11, 0.29) | 0.34 |

**Inference:** something in Redux calls `Mesh::_setBounds` with an infinite box
after the serializer has set the asset's box. The exact call site was not
located; it was not needed, because the repair below does not depend on it.

### 3. Ogre's own code explains why that disables culling completely

Verified against the Ogre 1.10.0 source tree, not from recollection:

- `RenderQueue::processVisibleObject` performs **no frustum test at all** — only
  `mo->isVisible()` and the rendering-distance cutoff.
- `SceneNode::_findVisibleObjects` performs the *only* frustum test, at node
  granularity: `if (!cam->isVisible(mWorldAABB)) return;`.
- `SceneNode::_updateBounds` merges every attached object's world box **and every
  child node's box** into the node's own, so one infinitely bounded object makes
  its whole node chain infinite.
- Redux registers only `DefaultSceneManager` (confirmed in `BZOgreLogfile.log`:
  `SceneManagerFactory for type 'DefaultSceneManager' registered`) and installs no
  Octree plugin, so there is no spatial structure to cull with either.

Together those give exactly the observed behaviour.

### 4. Re-measured contributor ranking, post-#46, 80 tanks firing, DX11

Ranked by measured CPU rather than submission count, as the previous triage
established.

| Group | Submissions/f | % of frame submissions | CPU ms/f |
|---|---:|---:|---:|
| Vehicle shadow (3 PSSM cascades x 3 submeshes) | 711.3 | 44.5% | 0.638 |
| Vehicle main `high-pssm` (3 materials) | 237.0 | 14.8% | **1.098** |
| Vehicle `glow` (3 materials) | 236.7 | 14.8% | 0.319 |
| Ordnance main + glow | 40.5 | 2.5% | 0.160 |
| DynamicGeometry effects | ~110 | ~7% | ~0.20 |

Vehicles alone are **63.5% of all submissions**.

Two things in that table falsify OLD assumptions:

- **OLD claim: "the three glow rows are roughly 1.1 ms at 80 tanks".** Measured:
  glow is **0.319 ms/f**, and `high-pssm` is 1.098 ms/f. Per submission that is
  1.35 us for glow against 4.63 us for `high-pssm`. The glow half was
  over-estimated by roughly 3.4x, which materially changes its ranking.
- `avheadlight00` costs **0.575 ms/f** against 0.269 and 0.254 for the hull and
  cockpit materials at an identical 79.0 submissions/frame. *Hypothesis, not
  established:* it is submesh 0 of `avtank.mesh` and may be absorbing the
  entity's first-touch per-frame work. Not investigated further.

### 5. Glow participation cannot be removed on material evidence

The previous triage proposed proving vehicle materials non-emissive and skipping
their glow pass. That was tested and **rejected**.

Every vehicle material derives from `BZBase`, whose `glow` technique binds
`EmissiveMap` and defaults it to `black.png`. If a material's emissive map were
black the glow pass would provably contribute nothing. Decoding all 98 shipped
`*_E.dds` emissive textures (DXT1/DXT5 endpoint scan, threshold 16/255):

- **97 of 98 are non-black.** Only `Chrome_e.dds` is fully black.
- Median non-black coverage is 1.95% of the texture, but non-zero: `avtank_E`
  1.58%, `avapc_cockpit_E` (used by `avtank01`) 1.12%, `avheadlight00_e` 14.96%.

So no stock vehicle material can be declared non-emissive, and a material-level
glow filter would visibly remove running lights and headlight bloom. Combined
with the corrected 0.319 ms/f measurement, the realistic ceiling for this family
is well under half a millisecond at 80 tanks and it cannot be taken safely.
**Family A is closed.**

## Candidate ranking

| Candidate | Current measured cost (80 tanks) | Theoretical ceiling | Realistic saving | Risk | Fidelity impact | Complexity |
|---|---:|---:|---:|---|---|---|
| **Main-view craft frustum culling** | 63.5% of submissions never culled | all off-screen craft | **-25.3% submissions** measured | low — Ogre's own test, fail-safe | none intended; bounds recovered from the asset | medium |
| Shadow-cascade culling | 711 sub/f, 0.638 ms/f | per-cascade rejection | unquantified | medium — cascade fitting and caster/receiver bounds | shadow pop if wrong | medium |
| Chunk-batch rebuild dedupe (~3x/frame) | ~4,500 verts rebuilt 3x/frame | 2/3 of rebuild cost | small but certain | very low | none | low |
| Batch material-LOD restoration | GPU only | distant chunk fragment cost | GPU-side only | low | restores stock LOD | medium |
| Glow participation | 0.319 ms/f | < 0.32 ms | **rejected** — 97/98 emissive maps non-black | high | visible | — |
| Main-view mesh LOD | 1.098 ms/f | large | not attempted | high | changes silhouettes | high |
| DX9 backend overhead | DX9 only | unknown | not isolated | high | none | unknown |

Selected: **main-view craft frustum culling**. It is the only candidate that is
supported by measured attribution, semantically provable (it is Ogre's own
frustum test against the asset's own bounds), fail-safe, narrow, independently
reversible, and worth more in real missions than in the benchmark.

## Implementation

`src/patches/ogre_entity_frustum_cull.inl`.

**It modifies no Ogre state.** `Mesh::_setBounds` is observed, not altered: the
last *finite* box each mesh is given — the box the serializer set from the
asset — is remembered in a fixed-capacity open-addressed table. When an entity's
world box turns out to be infinite, that remembered local box is inflated by a
safety margin, transformed by the entity's own node transform, and tested with
Ogre's `Camera::isVisible`.

Globally restoring the finite bounds was considered and **rejected**: Redux may
depend on infinite craft bounds for scene queries such as targeting or picking,
and this optimization must not change gameplay behaviour to buy frame time.
Keeping the recovered box private to the cull decision means the only observable
delta is which renderables reach the render queue.

Suppression works by making `Entity::_updateRenderQueue` a no-op for the one
object being processed while the original `processVisibleObject` runs in full.
The `visibleBounds->merge()` bookkeeping that feeds PSSM cascade fitting is
therefore **bit-identical by construction**, not replicated.

Deliberate scope limits:

- **Main-camera traversals only** (`onlyShadowCasters == false`). Shadow passes
  are counted and never culled, so every cascade, caster and cascade transition
  is untouched.
- **`Ogre::Entity` only**, matched on the exact decorated RTTI name and cached
  per vtable. Particle systems, billboard sets and manual objects are untouched.
- Skipping `_updateRenderQueue` also skips its trailing `updateAnimation()`.
  That is correct: shadow passes never cull, so anything casting a shadow still
  animates.

Fail-safe on every path: unresolved exports or a byte-guard mismatch stand the
feature down permanently; a null box, an infinite box with no remembered asset
bounds, a missing node transform, or a fault anywhere in the decision all submit
the object.

Controls:

| Variable | Effect |
|---|---|
| `OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING=1` | disable entirely (also `BZR_` prefix) |
| `OPENSHIM_FRUSTUM_CULL_MARGIN=<float>` | half-extent safety margin, default `0.25` |
| `OPENSHIM_FRUSTUM_CULL_CENSUS=1` | 1 Hz per-type bounds census |

### Two performance defects found and fixed during implementation

Both were caught because the idle and all-visible controls were measured, not
assumed.

1. **Linear scan of remembered bounds.** The first version scanned up to 487
   entries per infinitely-bounded entity per traversal. Measured cost: 20-tank
   idle went from 3.521 ms to 3.596 ms (+2.1%) with nothing culled. Replaced
   with an open-addressed hash; idle returned to parity.
2. **Testing objects that can never be culled.** Lights (~105 visits/frame, all
   null-boxed) and other non-Entity movables were being bounds-tested for
   nothing. 80-tank firing was +2.2% with 3% culled. Gated on a cached
   per-vtable RTTI classification; the regression disappeared.

## Performance, final head

Profiler enabled, GOG 2.2.301. Submission counts are the robust figures; frame
times are single runs on a machine with a browser and Steam resident and vary
about 1% run to run, so they are reported but not leaned on.

### DX11 and DX9, 20 tanks firing

| Workload | Submissions off -> on | Change | Frame off -> on | Change |
|---|---:|---:|---:|---:|
| DX11, all 20 in view | 486.8 -> 465.4 | -4.4% | 4.451 -> 4.503 ms | +1.2% |
| **DX11, all 20 behind camera** | **473.3 -> 353.4** | **-25.3%** | 4.475 -> 3.924 ms | **-12.3%** |
| DX9, all 20 in view | 487.3 -> 465.6 | -4.5% | 4.898 -> 4.719 ms | -3.7% |
| **DX9, all 20 behind camera** | **473.0 -> 353.3** | **-25.3%** | 4.688 -> 4.370 ms | -6.8% |

DX9 and DX11 give the same submission reduction to one decimal place, which is
what a renderer-independent change should do.

### DX11, dispersed and controls

| Workload | Submissions off -> on | Change | Frame off -> on | Change |
|---|---:|---:|---:|---:|
| Dispersed 40, 3 of 4 clusters off-screen | 750.1 -> 569.8 | **-24.0%** | 4.640 -> 4.515 ms | -2.7% |
| 80 firing, everything visible | 1,608.5 -> 1,581.7 | -1.7% | 11.932 -> 11.819 ms | -0.9% |
| **20 idle (control)** | **391.7 -> 391.7** | **0.0%** | 3.521 -> 3.526 ms | +0.1% |

The controls are the point: with nothing off-screen the change costs nothing
measurable, and with the camera turned away it removes a quarter of the frame's
submissions.

The `-4.4%` in the "all in view" rows is real and expected — terrain tiles and
effects behind the camera are culled even when every craft is visible.

## Validation performed

Static, on the final head:

- Release Win32 MSBuild — clean, no new warnings beyond the pre-existing
  `C4505`/`STL4038` set already on `main`;
- Ogre profiler algorithm tests — passed;
- INI/config tests — 23 checks, 0 failures;
- network-safety baseline — passed;
- `git diff --check` — clean.

Runtime: 39 harness runs across DX11 and DX9, culling enabled and
`OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING=1`, covering firing at 20 and 80,
dispersed at 40, idle controls, and both camera orientations.

Log scan across all 39 `openshim.log` files: **0** occurrences of `[ERROR]`,
unhandled access violations, `Ogre::Exception`, shader failures, material
failures, `culling stood down`, `guard mismatch`, `exports unavailable`, or
census table overflow.

## Known limitations

1. **Visual verification is outstanding.** Screen capture during this pass
   repeatedly caught the desktop instead of the game — the session locked during
   one attempt, and the machine was in interactive use during the others.
   `PrintWindow` against the game's HWND returns a black frame because the
   content lives in a DXGI swap chain. **No visual claim is made.** The specific
   risks a human should look for are pop-out at the screen edge on animated
   craft (walkers especially) and anything vanishing in the satellite view.
2. **Satellite and alternate camera modes were not exercised.** The cull tests
   against whatever camera Ogre passes, which is correct in principle for any
   camera, but no satellite-view run was made.
3. **The 0.25 safety margin is a judgement, not a measurement.** It exists
   because skeletal animation can carry geometry outside the bind-pose bounds
   the exporter recorded. It is tunable and can only cause under-culling.
4. **The `Mesh::_setBounds(infinite)` call site in Redux was not located.** The
   repair does not need it, but a future pass may want to know whether the
   infinite bounds were deliberate.
5. **Shadow cascades are untouched.** They remain 44.5% of submissions and
   0.638 ms/f at 80 tanks. That is the obvious next target and it is not
   attempted here.
6. **Frame timings are single runs on a machine in interactive use.** Submission
   counts are the load-independent evidence and should be quoted in preference.

## Next recommended target

**Per-cascade shadow-caster culling.** It is now the largest remaining block
(44.5% of submissions, 0.638 ms/f at 80 tanks), the recovered-bounds machinery
built here already supplies a testable box for craft, and the `onlyShadowCasters`
discriminator is already wired. It needs its own fidelity work: cascade fitting
uses `VisibleObjectsBoundsInfo`, so culling a caster changes what the cascade is
fitted to, which is exactly the risk this pass avoided by leaving shadows alone.

Second: the chunk-batch rebuild runs about three times per rendered frame (see
`live_render_optimization_20260822.md`). Small, certain, and very low risk.
