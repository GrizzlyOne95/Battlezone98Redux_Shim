# Hardware instancing for GPU-skinned craft (design, 2026-10-21)

Goal: cut draw submissions for craft in large fights on Direct3D 11. The
profiling in `frame_time_breakdown_20261020.md` (draft PR #540) shows the
frame is CPU-bound on the main thread. At idle 80 (avtank, GpuSkinning 1, PSSM
2048) the frame makes 912 draws: 295 main, 292 glow, about 309 across the three
shadow cascades. Draw submission costs about 2 µs a draw.

This document assumes `[Experimental] GpuSkinning = 1`, which another session
is making the default. Everything here builds on that path.

## 1. How a craft reaches Ogre today

- **Scene objects.** Each craft is one `Ogre::Entity` with about 3 sub-entities
  (body, turret, gun or similar). Each sub-entity is one `Renderable`. The game
  holds the `Entity*` itself, and other OpenShim features look at it (for
  example chunk meshes and enhanced light selection).
- **Queueing.** For each camera, `SceneManager::_renderScene` culls with the
  scene graph. Each visible entity then queues one entry per sub-entity per
  pass into `RenderPriorityGroup` solids, organised as `OM_PASS_GROUP`, which
  is a `map<Pass*, vector<Renderable*>>`.
- **Drawing.** `QueuedRenderableCollection::acceptVisitor` walks each
  `Pass*` group:
  - `SceneMgrQueuedRenderableVisitor::visit(const Pass*)` calls `_setPass`
    once per group;
  - `visit(Renderable*)` then calls `validateRenderableForRendering`, followed
    by `renderSingleObject` for each member.
- **What `renderSingleObject` does per object:**
  - reads `getNumWorldTransforms()` and `getWorldTransforms(mTempXform)` (at
    most 256 entries), applies the camera-relative offset, and calls
    `setWorldMatrices`;
  - sets up the object's light list, through `getLights()` and the
    `_populateLightList` hook in enhanced light selection;
  - calls `updateGpuProgramParameters`, then `_issueRenderOp`, which builds a
    local `RenderOperation` from `getRenderOperation()` and calls
    `D3D11RenderSystem::_render` for one draw.
- **Passes per frame.** The same queue walk runs for the main camera, for the
  `Glow` material-scheme render, and for each of the 3 PSSM cascades. In the
  cascades, `_setPass` derives the shadow-caster pass
  (`Ogre/DepthShadowmap/Caster/Float`, technique 0, pass 0) with the source
  pass's shadow-caster vertex program.
- **Result:** about 3.1 draws per craft in each of main, glow and shadow.

## 2. What GpuSkinning changes

`src/patches/gpu_skinning.cpp` makes these changes:

- It clones each craft material per blend-weight count, as
  `OpenShim/GpuSkin/<gen>/w<N>/<material>`.
- It replaces every pass's vertex program with a skinned twin. The twin has a
  `float4 osGpuSkinBones[64*3]` palette, filled by
  `world_matrix_array_3x4`, plus `BLENDINDICES`/`BLENDWEIGHT` inputs.
- It sets a matching skinned shadow-caster vertex program.
- It remaps every world-relative auto constant to its world-space equivalent.
  Constants that need the real world matrix are refused.

Two facts make instancing cheap to add on top of this:

1. **The vertex buffers are shared.** Under hardware animation,
   `SubEntity::getRenderOperation` binds the mesh's own `VertexData`. Every
   tank of a type therefore draws the same vertex and index buffers.
2. **The palette is the only per-object vertex input.** It holds K = 2-7
   rigid-part matrices per sub-mesh. Lights are per object, but they are equal
   between craft that are lit the same way.

Two draws of the same sub-mesh with the same pass and lights differ only in
the palette. Instancing is the act of concatenating those palettes.

## 3. Options

| Option | What it takes | Verdict |
|---|---|---|
| **A. Ogre `InstanceManager`**, HW basic (no skinning) | Replaces each `Entity` with an `InstancedEntity`. HW basic cannot animate, so it would only cover non-skeletal meshes. | **No.** Craft are skeletal, and the game owns its `Entity*` objects. Swapping them breaks every game and OpenShim consumer of the entity. Constructing those Ogre classes from OpenShim also crosses the VS2013 ABI of `OgreMain`. |
| **B. `InstanceManager` HW VTF** (bone palettes in a texture) | Same entity swap. Also needs new `vs_4_0` shaders that sample a VTF, plus Ogre's `InstanceBatchHW_VTF` material conventions (a `boneMatrices` sampler on unit 0). | **No.** It has the same ownership problem, and every stock and CR craft program would need a VTF rewrite. |
| **C. `InstanceManager` ShaderBased** (constant-buffer palette, one batch per material) | Same entity swap. Its own shader convention (`worldMatrix3x4Array` indexed by `blendIndices`) is close to ours. | **No,** for the same ownership reason. |
| **D. Our own per-pass batching layer (chosen)** | We leave entities and the queue alone. At draw time we replace N identical-key draws with one `DrawIndexedInstanced`. The palette holds N·K matrices; a per-instance stream adds `base = i·K` to every blend index. | **Yes.** It only touches render submission, needs no ownership change, and every refusal falls back to the stock per-object draw. |
| **E. Static or rigid parts only first** | Same layer as D, but only for non-skeletal entities, which would use `world_matrix_array_3x4` with K = 1. | Craft are all skeletal on the GpuSkin path, and in our scenes static props are few: lever 8 puts them at about 46 draws per pass. Option D covers rigid sub-meshes (K = 1) for free, so a separate rigid path adds nothing. |

## 4. Chosen design (option D)

### 4.1 Hooks

There are four hooks. None of them is in the game exe, so `patches.json` gets
no entry.

- **Three vtable slots of `SceneMgrQueuedRenderableVisitor`.** The class's
  exported vtable is `??_7SceneMgrQueuedRenderableVisitor@SceneManager@Ogre@@6B@`.
  - We patch slot 1, `visit(Renderable*)`; slot 2, `visit(const Pass*)`; and
    slot 3, `visit(RenderablePass*)`.
  - Each slot is matched by value against the exported function, before
    patching.
- **An inline detour on `QueuedRenderableCollection::acceptVisitor`** (the
  real body behind the ILT thunk). Its prologue is checked: `55 8B EC 6A FF`.
- **Why these and not `renderSingleObject`:** the animation profiler
  (`ProfileOgreAnimation`) already detours `renderSingleObject` with strict
  prologue checks. None of our hooks overlaps it, so both can run together.

### 4.2 Deferral and grouping

- **Recording the pass.** `visit(const Pass* p)` first flushes anything still
  pending, then runs the original, then records `p` as the group's
  **source pass**. In shadow cascades, `mUsedPass` is the derived caster
  pass, but `p` is still the material's own pass, so lookups are keyed on `p`.
- **Deferring members.** `visit(Renderable* r)` defers `r` when all of the
  following hold:
  - the feature is active;
  - the source pass has an instanced twin;
  - `r` is exactly an `Ogre::SubEntity` (its vptr equals
    `??_7SubEntity@Ogre@@6B@`);
  - its world-transform count K is between 1 and the twin's palette capacity.
  Anything else renders at once through the original slot.
- **Group key.** Pending members are grouped by:
  - source pass;
  - the `VertexData*` and `IndexData*` from `getRenderOperation`, plus index
    start and count, operation type and `useIndexes`;
  - K;
  - `getCastsShadows()`, because `validateRenderableForRendering` reads it;
  - the light list. We compare the contents of the `HashedVector<Light*>`
    returned by `getLights()`.
- **When pending groups flush:**
  - at the next `visit(const Pass*)`;
  - at the next `visit(RenderablePass*)`, which is the sorted and transparent
    path, never deferred;
  - when `acceptVisitor` returns.
  At each of these points the group's pass is still the bound one.
- **A group of one** is drawn by calling the original `visit(Renderable*)`,
  exactly as stock does.

### 4.3 The instanced draw

For a group of n ≥ 2, in chunks of at most ⌊capacity / K⌋:

1. Fetch every member's world transforms into a scratch array, chunk-major,
   and check that all first matrices agree on negative scale. Ogre flips the
   cull mode from `mTempXform[0]`.
2. Call `SceneManager::_setPass(twinPass)` and store the returned (possibly
   derived caster) pass in the visitor's `mUsedPass`.
3. Swap the leader's vptr for a copy of the `SubEntity` vtable with three
   slots overridden:
   - slot 7, `getNumWorldTransforms` → n·K;
   - slot 6, `getWorldTransforms` → copy the scratch array;
   - slot 3, `getRenderOperation` → the stock operation, but with
     `vertexData` replaced by our copy and `numberOfInstances = n`. The copy's
     declaration and binding add the instance stream.
4. Call the original `visit(Renderable*)` for the leader. Ogre then runs the
   whole stock per-object path once: lights, camera-relative offset, auto
   parameters, `_issueRenderOp`. `D3D11RenderSystem::_render` sees
   `getHasInstanceData()` and issues `DrawIndexedInstanced`.
5. Restore the vptr and `mUsedPass`.

The draw needs no closing `_setPass`. Every flush point is followed by a
`_setPass` of the next group, or by the end of the collection.

### 4.4 Instance stream

- **Buffers.** For each K there is one `HardwareVertexBuffer` of 256 `float`
  values, holding `i·K`. It is created dynamic write-only and filled once
  through a discard lock. It has `setIsInstanceData(true)` and step rate 1, so
  D3D11 uses `D3D11_INPUT_PER_INSTANCE_DATA`.
- **Why not `SV_InstanceID`:** Ogre's D3D11 input layout
  (`D3D11VertexDeclaration::getD3DVertexDeclaration`) requires every shader
  input to match a declaration element. Otherwise it throws "Unable to set
  D3D11 vertex declaration", so a system-value input cannot be used.
- **Declaration.** For each source `VertexDeclaration` we build a copy with one
  more element, `TEXCOORD15` / `VET_FLOAT1`, on the next free source. It is
  built once and re-validated element by element on every use.
- **Why a copy:** `D3D11VertexDeclaration` caches one input layout per
  program, so the declaration object must stay stable.
- **Binding.** A single scratch `VertexBufferBinding` is refilled for each
  draw (the source's buffers plus the instance buffer) and emptied afterwards,
  so no buffer reference outlives the draw.

### 4.5 Instanced twin material and programs

- **Material.** When gpu_skinning builds a clone, the instancing layer clones
  that clone again, as `OpenShim/GpuInst/<gen>/w<N>/<material>`. Each pass gets:
  - a vertex program built from the skinned twin's source by
    `MakeInstancedSkinnedVertexSource`;
  - a matching instanced caster program.
- **The source transform:**
  - it widens the palette to `osGpuSkinBones[256*3]`;
  - it adds `in float osGpuInstBase : TEXCOORD15`;
  - it rewrites each `osGpuSkinIndices.<lane> * 3` to
    `(osGpuSkinIndices.<lane> + (uint)osGpuInstBase) * 3`.
  Because it only edits the skinned twin's generated text, it is independent of
  how that twin was made (see PR #538).
- **The twin is never bound to an entity.** It is reached only through
  `_setPass` and a map from clone `Pass*` to twin `Pass*`.

### 4.6 Fail-closed rules

- **No twin is built for a pass when:**
  - the pass iterates per light, or is transparent;
  - the source already mentions `TEXCOORD15`;
  - the vertex, fragment or caster program parameters hold any auto constant
    that depends on the renderable. The palette entry itself is exempt. The
    refused types are:
    - the world family (0-7) and worldview / worldviewproj (20-27);
    - `custom` (88) and `animation_parametric` (120);
    - camera position in object space (79, 131);
    - light values in object space (45, 48, 50, 60, 63, 65);
    - texture and spotlight worldviewproj (82, 83, 86, 87).
- **Mismatches at draw time:** a negative-scale mismatch, a changed
  declaration, or a `RenderOperation` that does not match the cached key
  renders that group the stock way.
- **Faults:** the draw runs under `__try`. A C++ exception from Ogre (for
  example "Unable to set D3D11 vertex declaration") or an access violation
  does three things:
  - restores the vptr and `mUsedPass`;
  - latches the feature off for the process;
  - redraws the group's members the stock way.
- **Switch:** `[Experimental] GpuInstancing = 1` (or
  `OPENSHIM_GPU_INSTANCING`). It defaults to off and also requires
  GpuSkinning. It is read at mission start, like GpuSkinning.

### 4.7 The required checklist

| Concern | How it is handled |
|---|---|
| Stock and CR materials and shaders | Twins are generated from whatever gpu_skinning produced, so CR's PBR programs are covered whenever they skin. Passes with object-dependent constants are refused per pass (section 4.6). |
| Team colour, damage, glow | These come from materials and textures, so different values mean different `Pass*` and never share a group. The glow scheme is just another pass with its own twin. Any value supplied per renderable (`ACT_CUSTOM`) refuses the twin. |
| Culling | Unchanged. Ogre culls per camera before queueing, so only visible members are ever grouped. |
| Shadow casters | Each cascade queues casters separately. The twin pass carries an instanced caster vertex program, and `_setPass` derives from the twin the same way it does from the source. |
| Selection and picking | Game-side ray and bounds queries never touch render submission, so they are unaffected. |
| LOD | Mesh LOD changes `IndexData*`, which is in the key. Material LOD changes the `Pass*`. |
| Lifetime (objects dying mid-fight) | Groups live only from one queue walk to the next flush, inside one `acceptVisitor` call, so nothing is kept per entity. Twins are released with the gpu_skinning clones at mission end. |
| Light lists | Part of the key. Craft lit differently (explosions, headlights) fall into separate groups, so combat gains less than idle. |

## 5. Expected gain, and how to measure it

- **Upper bound:** at idle 80, about 700 of the 912 draws are craft
  sub-entities. With identical lights they collapse to about 3 per pass, so
  about 690 submissions disappear. Each remaining instanced draw also uploads
  a bigger palette and does its own per-object work once.
- **Arithmetic:** 690 × 2 µs is about 1.4 ms. The working estimate is 0.6-1.2
  ms (+12-25%) at idle 80, and less in combat 40, where light lists split the
  groups.
- **Caution:** the glow and shadow trim study (section "Follow-up" of the
  frame-time doc) removed up to 57% of glow submissions with no measurable
  gain against ±0.4 ms of noise. Part of the 2 µs per draw may therefore not
  be recoverable.
- **The benchmark decides.** Use `run_live_combat_benchmark.ps1 -UnitOdf
  avtank` at idle 80 and combat 40 with GpuSkinning 1. Compare a clean arm
  (GpuInstancing 0 against 1) with at least 3 repeats each, then repeat with
  CPU sampling.
- **Logging:** the mission summary logs batches, members, singles and refusal
  counts, so draw reduction can be checked against the profiler's draw counts.

## 6. Results (prototype, 2026-10-21)

### 6.1 Status: every craft renders

The prototype installs, batches and fails closed:

- no faults;
- `decl_refused=0`;
- `max_batch=20` at 20 tanks;
- about 28,000 instanced draws per idle-20 mission.

With `GpuInstancing=1` all 20 tanks of the parity scene render. The tank region
of the screenshot differs from the `GpuInstancing=0` shot by 164-254 pixels
(animation noise); the broken build differed by about 5,600.

#### The bug: a non-virtual unlock left the instance stream at zero

The first build drew one tank per batch. Diagnostics (temporary env hooks,
since removed):

| Test | Result | Meaning |
|---|---|---|
| Batch cap 1 (`perDraw=1`) | Every tank renders | The twin program, the palette upload and the cloned declaration are correct for instance 0. |
| Twin VS scaled 3× (`osGpuSkinPos * 3`) | Every craft vanishes | The instanced twin is the program actually bound. |
| Per-instance base forced to 100000 for every instance | Same single tank as `i·K` | The value in the instance stream never reaches the shader. |

A RenderDoc 1.46 capture of an idle-20 frame then showed:

- six `DrawIndexedInstanced` calls, each with `InstanceCount` 20;
- the TEXCOORD15 element is `R32_FLOAT` at input slot 3, per-instance, step
  rate 1, and the VS reads it;
- slot 3 is bound, with stride 4 and offset 0;
- **the buffer's GPU contents are all zero**, so post-VS positions are
  identical for instances 0-3.

**Cause.** The instance buffer was unlocked through the exported
`HardwareBuffer::unlock`, called directly. `D3D11HardwareVertexBuffer`
overrides `unlock` to forward to its inner `D3D11HardwareBuffer`, which does
the `Unmap` (or the staging copy). The direct call ran only the base class
body, so the data written through the lock never reached the GPU. The 2-arg
`lock` wrapper was fine: it dispatches virtually to `lockImpl`.

**Fix.** At install, the shim finds `unlock`'s slot in the exported
`HardwareBuffer` vtable (fails closed if it is absent or not unique) and calls
it through the buffer's own vptr.

What was ruled out along the way:

- **`SV_InstanceID`.** Ogre's D3D11 layout throws for any shader input that
  has no declaration element (section 4.4). An earlier arm that "worked" had
  faulted, and the fault latched the feature off. Lesson: **a faulted arm
  reads as success.** Always check the mission summary's `batches` before
  trusting a screenshot.
- **Static instance buffer.** Switching it to dynamic write-only with a
  discard lock changed nothing; the dynamic buffer was kept.
- **Calling Ogre virtuals through their exports.** Any exported virtual whose
  derived class overrides it must be called through the vtable. Binding the
  export is only safe for non-virtual functions or classes with no override.

### 6.2 Benchmark (fixed build, every craft rendering)

Setup:

- `run_live_combat_benchmark.ps1 -UnitOdf avtank`, GpuSkinning 1, DX11,
  windowed;
- 3 repeats per arm, interleaved (0 and 1 alternate within each repeat);
- 8 s measure window; seconds above 100 fps averaged, weighted by frame count.

Every `GpuInstancing=1` run engaged: `decl_refused=0`, no faults,
`max_batch=80` at idle and 40 in combat.

| Scenario | Arm | GpuInstancing 0 | GpuInstancing 1 | Δ |
|---|---|---|---|---|
| idle 80 | clean | 4.13 ms (4.02-4.23), 601 draws/frame | 3.26 ms (3.23-3.31), 131 draws/frame | −0.87 ms (−21%) |
| idle 80 | `-SampleCpu` | 4.57 ms (4.44-4.77) | 3.50 ms (3.45-3.59) | −1.07 ms |
| combat 40 | clean | 5.07 ms (4.91-5.19), 502 draws/frame | 4.92 ms (4.71-5.13), 422 draws/frame | −0.15 ms (within noise) |
| combat 40 | `-SampleCpu` | 5.46 ms (5.40-5.52), 557 draws/frame | 4.75 ms (4.07-5.22), 353 draws/frame | −0.71 ms (one outlier at 4.07) |

Reading:

- **Idle.** Draws fall by 78%, and frame time by 0.87 ms with no overlap
  between the arms. That is inside the 0.6-1.2 ms estimate of section 5. The
  broken build measured almost the same (−0.78 ms), so pixel work from the
  extra instances is not a significant cost here.
- **Combat.** Explosion lights split the groups: about a third of deferred
  members still draw alone (`singles` ≈ 130-180k per mission), and draws fall
  by only 16-37%. The clean arm's gain is inside run-to-run noise; the
  sampled arm suggests up to 0.7 ms but rests on one fast run.
- **Next.** Combat would gain more if light-list differences did not split
  groups. That needs the light list moved out of the key, for example per
  instance lights, which is a larger change than this prototype.
