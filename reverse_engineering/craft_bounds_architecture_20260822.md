# Craft bounds: where the infinite box comes from, and repairing it at the
# renderer layer (2026-08-22)

Baseline: `main` at `8cf4e2ee` (immediately after PR #46).
Branch: `agent/distant-unit-submissions`.
First repair experiment (PR #47) head, preserved: `eaa87b05513dc85cbff596f7403242499bafe3f2`.
Runtime: GOG Battlezone 98 Redux 2.2.301, `lcbench`, DX11 and DX9.

Every claim below is labelled **measured**, **binary evidence**, **inference**
or **hypothesis**. Numbers carried over from PR #47 are labelled as such and are
not overwritten.

---

## 1. Why PR #47's architecture was reconsidered

PR #47 established, and this pass re-confirms, that Redux gives craft meshes an
infinite Ogre bounding box, that Ogre's frustum test short-circuits on one, and
that a private per-object frustum test recovers about a quarter of the frame's
submissions when craft are off-screen.

Its implementation deliberately did **not** restore the finite bounds. The
stated reason was:

> Redux may depend on infinite craft bounds for scene queries such as targeting
> or picking, and this optimization must not change gameplay behaviour to buy
> frame time.

**That reason does not apply to Battlezone 98 Redux, and the PR was wrong to
rely on it.** Ogre is the renderer. The legacy Battlezone engine retains
ownership of physics, collision, object simulation, AI, targeting, weapon logic,
unit state, object interaction and every gameplay spatial relationship. An Ogre
`Mesh`/`Entity`/`SceneNode` bounding box is consumed by the render traversal and
by Ogre-side scene queries; it is not the source of truth for anything the
simulation does.

**Binary evidence for that boundary in this build.** Every Ogre bounds symbol the
executable imports is renderer-facing: `Mesh::_setBounds`,
`Mesh::_setBoundingSphereRadius`, `MovableObject::getWorldBoundingBox`,
`MovableObject::getWorldBoundingSphere`, `MovableObject::getLightCapBounds`,
`MovableObject::getDarkCapBounds`, `ShadowCaster::extrudeBounds` and
`ManualObject::getBoundingBox`/`getBoundingRadius`.

More decisively, the executable imports **no Ogre scene-query factory at all** --
no `SceneManager::createRayQuery`, `createSphereQuery`,
`createAxisAlignedBoxQuery`, `createIntersectionQuery` or
`createPlaneBoundedVolumeQuery`, and no `SceneQuery::execute`. It does import the
`MovableObject` query-*flag* accessors (`setQueryFlags`, `addQueryFlags`,
`removeQueryFlags`, `getQueryFlags`), but those flags are only ever consulted by
a query object, and this binary never creates one. So no Redux code path can
reach a bounds-driven Ogre spatial query even in principle, and changing an Ogre
bounding box cannot change Battlezone simulation semantics.

The remaining reasons to be careful with finite bounds are purely visual, and
they are the ones this pass actually investigated:

* animated geometry can leave the serialized bind-pose box;
* walkers have the largest pose excursions;
* attachment and parent/child bounds propagate in ways worth checking;
* Redux might have chosen infinite bounds deliberately.

The last of those turned out to be answerable directly.

---

## 2. Where the infinite bounds come from

### 2.1 Static evidence

`battlezone98redux.exe` 2.2.301 (GOG, unencrypted, ImageBase `0x00400000`).

`Ogre::Mesh::_setBounds` is imported once, at IAT `0x0086979C`, and is called
from exactly four places in `.text`:

| Call site | What it passes |
|---|---|
| **`0x0067E76F`** | **`AxisAlignedBox(EXTENT_INFINITE)`** |
| `0x0067F860` | `Entity::getBoundingBox()` scaled by 2 |
| `0x0077945F` | finite `AxisAlignedBox(min,max)`, procedural terrain geometry |
| `0x00779B05` | finite `AxisAlignedBox(min,max)`, procedural terrain geometry |

`??0AxisAlignedBox@Ogre@@QAE@W4Extent@01@@Z` -- the extent-kind constructor, the
only way this binary can name `EXTENT_NULL`/`EXTENT_FINITE`/`EXTENT_INFINITE`
directly -- is called from exactly one address, `0x0067E744`, with `push 2`
(`EXTENT_INFINITE`), and its result flows straight into the `_setBounds` six
instructions later. **There is one infinite-bounds assignment in the whole
executable.**

Its function, `0x0067E5A0`, is the **first-person view entity builder**:

```
0x0067E618  sprintf(name, "%.*s.mesh", 26, requestedName)
0x0067E66C  entity = sceneManager->createEntity(...)        ; vtable +0x17C
0x0067E6DB  entity->setCastShadows(false)
0x0067E705  skeleton = entity->getSkeleton()
0x0067E71A  view->entity   = entity                          ; [arg0+0xC0]
0x0067E723  view->flags    = 0                               ; [arg0+0xC8]
0x0067E736  view->skeleton = skeleton                        ; [arg0+0xCC]
0x0067E744  AxisAlignedBox box(EXTENT_INFINITE)
0x0067E76F  entity->getMesh()->_setBounds(box, /*pad=*/true)
```

`setCastShadows(false)` plus an unconditional never-cull box is a coherent
"always draw the cockpit I am sitting in, and do not let it cast a shadow"
policy. **Inference:** for a mesh that is only ever a first-person model this is
intentional and harmless.

The defect is *which* mesh it lands on. `0x0067E5A0` has exactly one caller,
`0x0067F480` (the per-craft Ogre setup function), which resolves the
first-person mesh name three ways:

1. a 15-entry table at `0x008ED2E8` -> `0x008ED308`:

   | craft | first-person mesh | | craft | first-person mesh |
   |---|---|---|---|---|
   | `avartl` | `avartl_c` | | `avwalk` | `avwalk_c` |
   | `bvartl` | `bvartl_c` | | `svwalk` | `svwalk_c` |
   | `svartl` | `svartl_c` | | `cvwalk` | `cvwalk_c` |
   | `avturr` | `avturr_c` | | `bvwalk` | `bvwalk_c` |
   | `svturr` | `svturr_c` | | `aspilo` | `aspilo_fp` |
   | `bvturr` | `bvturr_c` | | `sspilo` | `sspilo_fp` |
   | | | | `bspilo` | `bspilo_fp` |
   | | | | `bsheav` | `bsheav_fp` |
   | | | | `cspilo` | `cspilo_fp` |

2. `"%.16s_cockpit"`, when `ResourceGroupManager::resourceExistsInAnyGroup` says
   that resource exists;
3. otherwise, at `0x0067FDE8`, **the craft's own mesh name** -- taken when the
   skeleton carries a bone whose fourth character is `'2'`, i.e. the `AGR2*`
   group. (`avtank.skeleton` contains `AGR21bga` and `agr21bda` alongside
   `AGR11POV`, `AGR11GC1`, `AGR11TUR`, `HLGT0_ffffff`.)

`Ogre::Mesh` is a shared resource. On path 3 the never-cull policy is written
onto the very Mesh that every world instance of that craft renders from.

### 2.2 Runtime confirmation

`OPENSHIM_BOUNDS_TRACE=1` with `OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE=observe`
records the return address of every `Mesh::_setBounds` call it classifies.
Measured, DX11, `lcbench`:

```
[BOUNDSTRACE] #1 mesh=avtank.mesh action=observed incoming=INFINITE
  assetMin=(-3.16,-0.06,-3.74) assetMax=(3.16,2.76,2.96)
  callSite=battlezone98redux.exe+0x27E775 tid=20644
```

`0x00400000 + 0x27E775 = 0x0067E775`, the instruction immediately after the
`call` at `0x0067E76F`. The static and runtime answers agree exactly. The asset
box quoted also matches `avtank.mesh`'s `M_MESH_BOUNDS` chunk parsed straight
out of the file in PR #47.

Terrain writes trace to `battlezone98redux.exe+0x379465` = `0x0077945F`, and
load-time writes to `OgreMain.dll+0x29A757`
(`MeshSerializerImpl::readBoundsInfo`), so call-site attribution is exact for
every path.

**Timing and frequency, measured:** the infinite write happens once per craft
spawn, on the render thread, after the serializer has set the asset box and
after `0x0067F860` has written its scaled box. It is not periodic and never
recurs per frame.

### 2.3 Which object classes actually receive infinite bounds

Measured, one run per craft ODF, `OPENSHIM_RESTORE_CRAFT_BOUNDS_SCOPE=all` so
nothing is filtered out (`lcbench` always has an `avtank` player craft, which is
why `avtank.mesh` appears in every row):

| Spawned craft | meshes given `EXTENT_INFINITE` |
|---|---|
| `avtank` | `avtank.mesh` |
| `avfigh` | `avfigh.mesh`, `avtank.mesh` |
| `avmine` | `avmine.mesh`, `avtank.mesh` |
| `avwalk` | `avwalk_c.mesh`, `avtank.mesh` |
| `avturr` | `avturr_c.mesh`, `avtank.mesh` |
| `avartl` | `avartl_c.mesh`, `avtank.mesh` |
| `aspilo` | `aspilo_fp.mesh`, `avtank.mesh` |

So:

* **craft with no dedicated first-person mesh** (`avtank`, `avfigh`, `avmine`,
  ... -- resolved by path 3) have their **world mesh** made infinite. This is
  the defect.
* **craft listed in the table** (walkers, turret tanks, artillery, pilots) put
  the infinite box on their dedicated `*_c` / `*_fp` model instead; their world
  meshes are never made infinite.
* **terrain, buildings, ordnance, effects, attachments, weapons** never reach
  the call site at all, and are untouched. No non-craft class receives infinite
  bounds anywhere in this executable.

**Measured, and not previously known:** the first-person entity is built for
*every* craft, not only the player's -- five AI walkers were enough to make
`avwalk_c.mesh` infinite in a mission whose player flies an `avtank`.

### 2.4 Is it deliberate?

**Inference, supported by binary evidence, not proven intent.** The infinite box
is paired with `setCastShadows(false)` and is written only on the first-person
view path, which is exactly the shape of a deliberate "the cockpit is always
visible" policy. Nothing in the binary suggests the author intended it to reach
shared world meshes; path 3 reuses the craft's own mesh name as a *fallback*
for craft that ship no separate cockpit model, and the shared-resource
consequence looks unconsidered rather than chosen. It is **not** an animation
workaround, a debug leftover or an Ogre compatibility shim: no such guard,
version check or comment-shaped constant exists near the call site, and the
behaviour is unconditional within its function.

### 2.5 A second, separate stock defect found on the way

**Measured.** `0x0067F860` sets craft bounds to
`Entity::getBoundingBox() * Vector3(2,2,2)` -- and `Entity::getBoundingBox()`
re-reads the mesh's *current* bounds. Nothing resets it between spawns, so on
any craft mesh that is not subsequently made infinite the box doubles once per
spawned craft.

Two consequences:

* On path-3 craft the infinite write immediately follows and masks it.
* On table craft (walkers, turret tanks, artillery, pilots) it does not: their
  world mesh grows by 2x per spawn without limit, so whatever culling Ogre could
  have done for them decays away as a mission fills up.

Also **measured**, and the reason the restored-bounds policy below does *not*
copy Redux's transform: `AxisAlignedBox::scale()` multiplies both corners about
the **origin**, which does not preserve containment. `apammo.mesh` has
`assetMin.y = 0.29`; scaling by 2 lifts the floor of its box to `0.58` and
leaves real geometry outside the box it just computed.

---

## 3. The repair

`src/patches/ogre_entity_frustum_cull.inl`, opt-in behind
`OPENSHIM_RESTORE_CRAFT_BOUNDS=1`.

`Mesh::_setBounds` is already hooked by PR #47 to *observe* bounds. The same
hook now, when restoration is enabled:

1. remembers the **first** finite box each mesh is given -- the one
   `MeshSerializerImpl::readBoundsInfo` set from `M_MESH_BOUNDS`. The *first*,
   not the last, because the last inherits section 2.5's compounding;
2. when Ogre is handed `EXTENT_INFINITE` for a mesh whose asset box is known and
   which is not a first-person-only model, substitutes a finite box built with
   Ogre's own `AxisAlignedBox(Real,Real,Real,Real,Real,Real)` constructor;
3. leaves everything else exactly as Redux wrote it.

Ogre's native `SceneNode::_findVisibleObjects` frustum test then works normally.
No submission is suppressed by OpenShim in this mode, and
`Entity::_updateRenderQueue` and `RenderQueue::processVisibleObject` are not
patched at all -- with restoration alone the render traversal keeps its stock
instruction stream.

### Scope, and why it is this narrow

* **Only meshes that were actually handed an infinite box are touched.** A mesh
  that never receives one is never repaired, never pinned and never inspected
  again. Terrain clusters, buildings, ordnance, effects and attachments are
  therefore bit-identical to stock by construction, which matters because
  terrain tile meshes legitimately rewrite their own finite bounds.
* **`*_c`, `*_fp` and `*_cockpit` meshes keep their infinite box.** Those are the
  models the policy was written for, they are drawn from inside the cockpit, and
  leaving them alone means the first-person view cannot regress.
  `OPENSHIM_RESTORE_CRAFT_BOUNDS_SCOPE=all` removes this filter for A/B work.
* **The policy box is derived from the asset box, inflated about its centre**,
  never about the origin, for the `apammo` reason in 2.5.

### Controls

| Variable | Effect |
|---|---|
| `OPENSHIM_RESTORE_CRAFT_BOUNDS=1` | enable; also stands the PR #47 private cull down |
| `OPENSHIM_FRUSTUM_CULL_WITH_RESTORE=1` | run both mechanisms deliberately |
| `OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE=<k>` | centre inflation factor, default `2.0` |
| `OPENSHIM_RESTORE_CRAFT_BOUNDS_SCOPE=all` | do not exempt `*_c`/`*_fp`/`*_cockpit` |
| `OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE=observe` | decide and trace, change nothing |
| `OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE=infinite` | substitute the infinite write only, never pin |
| `OPENSHIM_BOUNDS_TRACE=1` | bounded per-mesh call-site trace |
| `OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING=1` | PR #47's opt-out, unchanged |

Fail-safe on every path, as before: unresolved exports or a byte-guard mismatch
stand both features down; a mesh with no recorded asset box, a fault building
the replacement box, or a fault anywhere in the decision all fall through to
exactly the call Redux made.

---

## 4. Results

All three architectures ran the identical workload list in the identical order,
one mode after another, on the same mission state:

* **stock** -- `OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING=1`, nothing installed;
* **private** -- PR #47 defaults: infinite bounds kept, OpenShim suppresses
  `Entity::_updateRenderQueue` for craft it finds outside the main frustum;
* **restore** -- `OPENSHIM_RESTORE_CRAFT_BOUNDS=1` (scale 2.0), which also stands
  the private cull down. No submission is suppressed by OpenShim at all;
  `processVisibleObject` and `Entity::_updateRenderQueue` are not even patched.

21 runs, 21 completed, no launch failures and no crashes.

### 4.1 Ogre submissions per frame

| Workload | stock | private | restore | private | restore |
|---|---:|---:|---:|---:|---:|
| DX11 dispersed 40 facing | 748.6 | 570.2 | **204.1** | -23.8% | **-72.7%** |
| DX11 firing 20 away | 472.5 | 350.1 | **165.1** | -25.9% | **-65.1%** |
| DX11 firing 20 facing | 488.2 | 465.9 | **374.0** | -4.6% | **-23.4%** |
| DX11 firing 80 facing | 1606.7 | 1583.0 | **1170.8** | -1.5% | **-27.1%** |
| DX11 idle 20 facing (control) | 391.7 | 392.0 | **280.2** | +0.1% | **-28.5%** |
| DX9 firing 20 away | 470.2 | 350.2 | **165.4** | -25.5% | **-64.8%** |
| DX9 firing 20 facing | 488.2 | 466.8 | **373.2** | -4.4% | **-23.6%** |

DX9 and DX11 agree to within 0.3 percentage points in every mode, which is what
a renderer-independent change should do.

### 4.2 Where the saving comes from: main view vs shadows

Main-camera render-queue calls per frame (`rqMain`) and shadow-camera calls
(`rqShadow`), measured:

| Workload | rqMain stock / private / restore | rqShadow stock / private / restore |
|---|---|---|
| DX11 dispersed 40 facing | 164.8 / 164.8 / 104.8 | 124.5 / 124.5 / **2.5** |
| DX11 firing 20 away | 107.3 / 107.3 / 67.3 | 68.7 / 68.7 / **6.7** |
| DX11 firing 20 facing | 106.2 / 106.3 / 102.2 | 66.3 / 66.4 / **32.3** |
| DX11 firing 80 facing | 267.0 / 265.7 / 262.0 | 257.7 / 257.2 / **115.4** |
| DX11 idle 20 facing | 102.0 / 102.0 / 102.0 | 63.0 / 63.0 / **25.8** |

**The two repairs remove exactly the same craft from the main view.** Craft
submissions on `PlayerCam`, per frame, for the 21 craft present (20 spawned plus
the player):

| Workload | material | stock | private | restore |
|---|---|---:|---:|---:|
| idle 20 facing | `avtank00 high-pssm` | 21.0 | 21.0 | **21.0** |
| idle 20 facing | `avtank01 high-pssm` | 21.0 | 21.0 | **21.0** |
| idle 20 facing | `avheadlight00 high-pssm` | 21.0 | 21.0 | **21.0** |
| firing 20 away | `avtank00 high-pssm` | 21.0 | 1.0 | **1.0** |
| firing 20 away | `avheadlight00 high-pssm` | 21.0 | 1.0 | **1.0** |
| dispersed 40 | `avtank01 high-pssm` | 41.0 | 11.0 | **11.0** |
| dispersed 40 | `avheadlight00 glow` | 41.0 | 11.0 | **11.0** |

With everything on screen, restored bounds submit **every** craft -- the control
is exact, not approximately exact. With the camera turned away, they remove
exactly the same 20 craft the private cull removes, leaving the player's own
craft, which is at the camera. Ogre's native test and PR #47's private test
reach identical decisions.

**All of restore's additional saving is shadow-caster traversal**, which PR #47
deliberately never touched. Per-cascade craft submissions, `idle 20 facing`
(3 submeshes x 21 craft = 63 per cascade):

| Cascade | stock | private | restore |
|---|---:|---:|---:|
| 1 (nearest) | 63.0 | 63.0 | **3.0** |
| 2 | 63.0 | 63.0 | **60.0** |
| 3 (farthest) | 63.0 | 63.0 | **14.3** |
| total | 189.0 | 189.0 | **77.3** (-59%) |

Stock puts every craft in every cascade because an infinite box intersects every
cascade volume. With real bounds each craft lands in the cascade or cascades
that actually cover its depth. Nothing here is an OpenShim policy: the cascade
volumes and the intersection test are Ogre's, unchanged.

### 4.3 Frame time

Single runs on a machine in interactive use; submission counts above are the
load-independent evidence and should be quoted in preference.

| Workload | stock | private | restore | restore vs stock |
|---|---:|---:|---:|---:|
| DX11 dispersed 40 facing | 4.818 ms | 4.425 | **3.966** | -17.7% |
| DX11 firing 20 away | 4.299 ms | 3.875 | **3.136** | -27.0% |
| DX11 firing 20 facing | 4.315 ms | 4.271 | **4.251** | -1.5% |
| DX11 firing 80 facing | 11.535 ms | 11.343 | **10.870** | -5.8% |
| DX11 idle 20 facing | 3.522 ms | 3.550 | **3.305** | -6.2% |
| DX9 firing 20 away | 4.921 ms | 4.411 | **4.066** | -17.4% |
| DX9 firing 20 facing | 4.851 ms | 4.751 | **4.560** | -6.0% |

Submission CPU alone falls from 0.774 to 0.619 ms/f at 80 craft firing (-20.0%)
and from 0.349 to 0.157 ms/f dispersed (-55.0%).

### 4.4 Bounds policy

Only one policy was carried into the benchmark matrix, `scale = 2.0` about the
box centre, chosen for these reasons rather than by sweeping arbitrary margins:

* **it is not arbitrary.** Redux itself already inflates craft bounds by a factor
  of 2 at `0x0067F860`. Matching the magnitude keeps the repaired box no tighter
  than the box the game computes for itself on every spawn;
* **`scale = 1.0` (exact serialized bounds) was rejected without testing it in
  the matrix**, because the asset box is a bind-pose box and the animation
  excursion argument against it is real;
* the axis of the change that mattered was **centre versus origin**, not the
  factor. Redux scales about the origin, which is not containment-preserving --
  `apammo.mesh` (`assetMin.y = 0.29`) loses the bottom of its own box under
  Redux's own transform. Centre inflation always contains the asset box.

`OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE` remains tunable, and under-inflation can
only cause visible clipping, never a crash or a gameplay change.

**Not done:** a 1.0 / 1.25 / 1.5 / 2.0 sweep with visual scoring per craft class.
The chosen value is defensible but it is not demonstrated to be the *smallest*
safe value, and that remains open.

### 4.5 Visual results

Exclusive-fullscreen DXGI cannot be captured with `CopyFromScreen` or
`PrintWindow`, which is why PR #47 produced no visual evidence at all.
`capture_craft_bounds_visuals.ps1` forces a window for the duration and restores
`Ogre.cfg` afterwards, which made real frames available for the first time.

| Case | Result |
|---|---|
| First-person cockpit (`avtank`, whose FP entity uses the repaired mesh) | **renders normally**; the cockpit frame is present in every captured frame |
| Craft clipped by the left screen edge, 50 m | **renders**, no pop-out |
| Craft clipped by the right screen edge, near camera (a few metres) | **renders**, no pop-out |
| 20 craft moving at 50 m, 26 frames | every frame shows a normal scene; no craft vanished |
| 40 craft dispersed on a 300 m ring, camera re-pointing every 1.5 s, 24 frames | no pop, no missing craft |
| Static A/B, `idle` 20 craft, stock vs restore | see below |

The static A/B is the sharpest instrument, because `idle` holds the camera and
the unit positions fixed so the two runs are directly comparable:

* **0.92%** of pixels differ by more than 32/255, and every one of them is inside
  the horizontal band the craft occupy (`y 406..554`);
* those differences are hover-bob phase -- the two runs are not frame
  synchronised and idle craft oscillate vertically. Craft count and placement
  match cluster for cluster;
* the ground beneath and around the craft is **bit-identical**: mean luminance
  delta `-0.000`, and the count of pixels darker than 60, 80, 100 and 120 is
  identical to within one pixel in every bucket. No ground shading, and
  therefore no cast shadow, changed.

The operator also watched the full benchmark campaign live at native resolution
and reported no visual artefacts.

**Not done, and it is the main gap:** the satellite view was not exercised, and
neither were mission cinematics, alternate camera modes, save/load, or a walker
under restored bounds. Walkers are the specific class most likely to exceed a
bind-pose box, *and* the class whose world mesh this repair does not touch (see
2.3), so the risk there is low but it is untested. Driving the satellite view
needs scripted scan-code input which was not built in this pass.

### 4.6 Hierarchy propagation

`Entity::getBoundingBox()` recomputes from `Mesh::getBounds()` on every call and
`SceneNode::_updateBounds` re-merges every frame, so restored mesh bounds
propagate to existing entities and their nodes without any invalidation step --
confirmed by the fact that culling starts working on craft that were already
spawned before the repair applied.

No ancestor was observed to stay infinite. The measured proof is indirect but
strong: if any craft's node chain were still infinite, that craft could not be
culled, and `firing 20 away` would not have fallen from 21.0 to 1.0 craft
submissions. Lights attached to craft report a null box, which merges as a no-op.

The census now reports `nodeExtents=` and `parentNodeExtents=` per object type
for direct inspection, but that instrument was added after the matrix ran and
has not been exercised on a full mission.

---

## 5. Architecture selected

**Restore finite Ogre bounds. Retain the PR #47 private cull as an opt-in
fallback, not as the shipped mechanism.**

| | main-view culling | shadow culling | mechanism |
|---|---|---|---|
| stock | none | none | -- |
| private (#47) | -4.6% to -25.9% submissions | none | OpenShim suppresses `Entity::_updateRenderQueue` |
| **restore** | **identical to private** | **-51% to -98%** | Ogre's own traversal, on correct bounds |

Restoration wins on every axis that matters:

* it reaches the *same* main-view decisions as the private cull, so it gives up
  nothing;
* it additionally fixes shadow-cascade traversal, which the private approach
  could not touch without reimplementing cascade fitting;
* it patches **one** function (`Mesh::_setBounds`) instead of three, and leaves
  the per-frame render traversal completely unpatched -- no per-object hook, no
  per-traversal decision, no thread-local suppression flag;
* it repairs incorrect renderer state at the layer that owns it rather than
  compensating for it one layer up.

### Rejected, and why

* **Keeping infinite bounds out of concern for gameplay queries** -- the premise
  was wrong. See section 1: the executable creates no Ogre scene query at all.
* **Repairing every mesh** (`SCOPE=all`) -- it would also strip the
  always-visible policy from `*_c`/`*_fp` cockpit models, where that policy is
  correct and deliberate. Retained as an A/B switch only.
* **Reproducing Redux's own `scale(2,2,2)`** -- scales about the origin and is
  not containment-preserving.
* **Deriving the policy from the last finite box** -- inherits the per-spawn
  doubling at `0x0067F860`.
* **A custom per-cascade shadow policy** -- unnecessary. Ogre does it correctly
  once the bounds are correct, which is exactly the outcome Phase 7 was written
  to look for.
