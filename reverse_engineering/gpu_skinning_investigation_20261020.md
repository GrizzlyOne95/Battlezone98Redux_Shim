# GPU skinning investigation (2026-10-20)

Question: should OpenShim move craft vertex skinning from Ogre's CPU path
(`Mesh::softwareVertexBlend`) to hardware skinning, given a hard requirement
that animation and presentation stay exactly stock?

## Verdict

- **Phase 1 gate: the gain is material.** On DX11, CPU skinning costs about
  0.033–0.042 ms per animated craft per frame. In groups that are mostly idle,
  it is 24–41% of the whole frame. It alone exceeds a 240 Hz budget share at about
  40 craft, and at 80 craft it is 2.3–3.0 ms of a 7 ms frame.
- **GPU skinning cannot meet the "exactly stock" bar as stated.** GPU
  blending changes float operation order and matrix association. That gives
  ULP-level position differences and occasional edge-pixel flips, so a strict
  pixel-identical A/B cannot pass. Nothing was prototyped; see *Recommendation*.
- **Recommended next step:** an exact optimisation (skip re-skinning when an
  entity's bone matrices are unchanged), gated on a pose-change-rate
  measurement. GPU skinning stays an option only if the user accepts
  sub-pixel, non-bit-exact output.
- **Update (same day): the measurement says no.** Only 4–27% of skinned
  vertices have an unchanged palette, about 5% with 80 craft moving or
  fighting. See *Pose-change rate*.

## Phase 1 measurements

Setup:
- `run_live_combat_benchmark.ps1`, DX11, windowed (`BZR_FORCE_WINDOWED=1`),
  `misn` live-combat scenario, units at 50 m facing the camera.
- `[Diagnostics] ProfileOgreAnimation = 1`: the INI key overrides
  `OPENSHIM_PROFILE_OGRE_ANIMATION`.
- RenderProfile=Enhanced, SkinnedGibs=1, FSAA 8, RTX 5080, over RDP.
- winmm.dll `00A7D611…2C64AD`, bzloader.dll `B6F24B56…3BB17699`. This build
  includes the DX11 skin-source shadow fix.
- `idle` = units stationary. `firing` = units firing; their weapon effects
  cost far more than the skinning does.

### Uncapped (VSync off, profiler on)

| unit | scenario | craft | fps | mean ms | skin ms | skin % of frame | anim ms (incl. skin) |
|---|---|---:|---:|---:|---:|---:|---:|
| svfigh | idle | 20 | 388 | 2.58 | 0.63 | 24% | 0.69 |
| svfigh | idle | 40 | 236 | 4.24 | 1.27 | 30% | 1.42 |
| svfigh | idle | 80 | 140 | 7.13 | 2.70 | 38% | 3.02 |
| svfigh | firing | 20 | 294 | 3.40 | 0.36 | 10.5% | 0.40 |
| svfigh | firing | 40 | 197 | 5.09 | 0.77 | 15% | 0.86 |
| svfigh | firing | 80 | 76 | 13.13 | 2.26 | 17% | 2.54 |
| avtank | idle | 20 | 371 | 2.70 | 0.65 | 24% | 0.73 |
| avtank | idle | 40 | 234 | 4.26 | 1.45 | 34% | 1.62 |
| avtank | idle | 80 | 137 | 7.32 | 2.99 | 41% | 3.37 |
| avtank | firing | 20 | 231 | 4.33 | 0.36 | 8% | 0.40 |
| avtank | firing | 40 | 137 | 7.38 | 0.88 | 12% | 1.00 |
| avtank | firing | 80 | 76 | 13.21 | 2.54 | 19% | 2.88 |

Profiler overhead was not measured.
- A matching profiler-off sweep ran cleanly, but with the profiler off this
  benchmark's only frame-time source is PresentMon, which was not used, so it
  produced no timings.
- The skin ms column times `softwareVertexBlend` directly, so it does not
  depend on the profiler's overhead. The fps and mean-ms columns may carry a
  small profiler cost, from hooks on about 250 calls per frame.
- To quantify that cost, rerun with PresentMon and the profiler off.

### Capped sweep (VSync on, ~58 fps), skin ms per frame

| unit | scenario | 20 | 40 | 80 |
|---|---|---:|---:|---:|
| svfigh | idle | 0.64 | 1.38 | 2.96 |
| svfigh | firing | 0.38 | 0.84 | 2.45 |
| avtank | idle | 0.71 | 1.59 | 3.37 |
| avtank | firing | 0.39 | 0.91 | 2.65 |

The per-frame skin cost does not depend on frame rate. It scales linearly with
skinned craft.

### Workload shape

- Every visible skinned entity is skinned once per frame, about 3 submesh
  sources each, with no duplicate skins. At 80 svfigh that is about 243 skin
  calls and 525k vertices per frame.
- Rigs are rigid-part. The average is 2.3 (svfigh) to 3.0 (avtank) bone
  matrices per mesh.
- Shadow-pass skin calls are 0 in this configuration. The shadow caster reuses
  the main-pass blended buffer through the DX11 skin-source fix, so there is
  no second skinning cost to remove.
- Under `firing`, fewer entities are visible or animated per frame (frustum and
  effects), so the absolute skin cost is lower and the effects dominate.

## Phase 2 findings (design only; not built)

### Materials that would need a skinned vertex program

These come from the loose material scripts in the GOG install.

- **Craft:** 2562 per-craft materials in `BZ_ASSETS\pc\materials` are thin
  `: BZBase` children. BZBase (`BZ_ASSETS_CORE\common\BZ_MATERIALS\BZBase.material`)
  has these techniques:
  - Schemes `high`, `medium`, `low` and `lowest`, each in `-pssm`, plain and
    `-noshadow` variants. These are 12 `Base*_vertexHLSL4` programs, all
    compiled from `pc\programs\dx11\base-sm4.hlsl` entry `base_vertex`
    (vs_4_0). They differ only in `preprocessor_defines`.
  - A `glow` scheme using `Textured_vertex` (`textured-sm4.hlsl`).
- **Shadow caster:** `Ogre/DepthShadowmap/CasterVP_HLSL4`
  (`DepthShadowmap-sm4.hlsl`, POSITION + worldViewProj). Texture shadows
  with PSSM (3 splits) render casters with this program, so a hardware-skinned
  entity needs a skinned caster too. Otherwise its shadow stays in bind pose.
- **Total:** 14 vertex programs from 3 HLSL sources. There is no existing
  skinned shader; terrain `BLENDINDICES` are packed data, not bones. RTSS is
  not used.
- **Mods:**
  - ISDF Chronicles ships its own `isdfc_*` programs, which would need their
    own skinned variants or must stay on CPU.
  - The CR mod ships only effect shaders.
- **Implication:** skinning cannot be added to the shared BZBase programs,
  because non-skeletal BZBase users (props, buildings) share them. The shim
  would clone materials at runtime, only for entities with a skeleton. The
  clones would get skinned variants (`includes_skeletal_animation true`,
  BLENDINDICES/BLENDWEIGHT inputs, a bone-matrix array) and
  `setShadowCasterVertexProgram` on each pass.

### How Ogre 1.10 would enable it per entity

- `Entity::isHardwareAnimationEnabled()` is true only when every technique in
  use has a vertex program with `includes_skeletal_animation`. Entities
  whose material is not cloned (unknown mods, failures) automatically stay on
  software skinning. That is a natural fail-closed path.
- `src/patches/diag_vehicle_skinning.cpp` already probes
  `isHardwareAnimationEnabled` and `getSkeleton`, so the identification side
  exists.
- Mesh vertex declarations must carry blend indices and weights in a GPU
  readable form. Ogre 1.x keeps them in the mesh's blend buffer for software
  skinning, so this needs verifying per mesh before any prototype.

### CPU-pose consumers

- `src/patches/skinned_gibs.cpp` reads skeleton bone derived transforms
  (`getBone`, derived position/orientation, bind-inverse). It does not read
  blended vertices, so it keeps working under hardware skinning.
- Anything that reads CPU-blended vertices would see bind-pose data. In `src/`
  only `ogre_animation_profiler/` touches skin-source state; it also hosts the
  DX11 shadow skin-source fix. That fix would become a no-op for
  hardware-skinned entities, and its counters would read zero.

### Exactness

- GPU skinning computes `sum(w_i * (M_i * p))` in shader float math.
- Ogre's CPU path uses SSE or general code with a different operation order.
  It also renormalises normals differently.
- The output differs at the ULP level, which moves rasterised edges by
  sub-pixel amounts and flips some edge and AA samples.
- A pixel-diff A/B (the `capture_craft_bounds_visuals.ps1` pattern) would show
  small non-zero diffs on craft silhouettes even when the result looks
  identical. "Animate exactly as on CPU" therefore cannot be proven by pixel
  identity. The honest acceptance bar would be "max per-pixel delta ≤ N on
  craft edges only".

## Recommendation

1. **Measure the pose-change rate first.** Count skin calls whose bone-matrix
   palette is byte-identical to that entity's previous frame. Idle craft,
   distant craft and craft between animation keys are likely to repeat.
2. **If the rate is high,** build an exact skip cache. It reuses the previous
   blended vertices when the palette is unchanged, so output is bit-identical by
   construction.
   - Ogre's `TempBlendedBufferInfo` checks temp buffers out with
     automatic release every frame. The cache therefore needs persistent
     per-entity blended buffers, about 156 KB per fighter.
   - It would sit behind a default-off `[Experimental]` key, fail closed, and
     pass a strict pixel-identical A/B.
3. **Only if the user accepts sub-pixel differences,** prototype hardware
   skinning. Scope:
   - Runtime BZBase material clones for skeletal entities.
   - Skinned variants of `base-sm4`, `textured-sm4` and the DepthShadowmap
     caster.
   - CPU fallback for anything else.
   - Expected win: up to the skin ms in the tables above, minus GPU cost and
     the per-entity bone upload, so roughly 2–3 ms at 80 craft.

## Pose-change rate (palette reuse probe, 2026-10-20)

Recommendation step 1, measured. **Verdict: do not build the whole-palette
skip cache.** An unchanged palette is common by call count, but those calls
are the small submeshes. The big body mesh changes almost every frame, so
the skips would cover only 4–27% of skinned vertices, and about 5% with 80
craft moving or fighting.

### Method

- `HookSoftwareVertexBlend` (`ogre_animation_profiler/ogre_hooks.inl`) now
  copies the bone matrices it is passed, up to 8 per call.
  - It keys them by the target vertex data. That is the entity's own
    `mSkelAnimVertexData`; the source data is shared per mesh.
  - It compares them byte-for-byte with that target's previous skin.
  - It reports a `[OgreProfile][Palette]` line every interval, and
    `analyze_live_combat_benchmark.ps1` adds `palette_*` columns for it.
  - It runs only under `ProfileOgreAnimation`, outside the timed region.
- `same` = palette byte-identical to the previous skin of that target. Every
  such skin was exactly one frame after the last one, and there were no
  same-frame repeats.
- `sameVert%` = the vertices those skins cover, as a share of all compared
  vertices. A skip cache saves roughly this share of the skin ms, minus
  its own compare cost.
- Setup is as in Phase 1: DX11, windowed, VSync off, `lcbench`, units at
  50 m facing the camera, 8 one-second samples (7 where noted), same
  winmm build plus the probe.
- `movement`, `combat` and `flight` were added after review, because mission
  craft move and fight. `idle` is the best case for a cache, not the
  typical one.

### Results

| unit | scenario | craft | skin calls/f | skin ms | same % (calls) | **same % (verts)** | ≤1e-5 noise / changed |
|---|---|---:|---:|---:|---:|---:|---:|
| svfigh | idle | 20 | 63.0 | 0.61 | 44.5 | **19.4** | 20.4 / 35.0 |
| svfigh | idle | 40 | 123.0 | 1.29 | 39.0 | **11.2** | 26.6 / 75.0 |
| svfigh | idle | 80 | 243.0 | 2.73 | 36.6 | **7.6** | 32.8 / 153.9 |
| svfigh | firing | 20 | 39.0 | 0.36 | 53.8 | **33.2** | 9.6 / 18.0 |
| svfigh | firing | 40 | 82.1 | 0.78 | 43.3 | **17.5** | 14.3 / 46.5 |
| svfigh | firing | 80 | 193.0 | 2.28 | 37.6 | **9.0** | 12.9 / 120.5 |
| svfigh | movement | 20 | 41.6 | 0.41 | 38.2 | **10.6** | 1.4 / 25.7 |
| svfigh | movement | 40 | 98.6 | 1.03 | 35.4 | **6.0** | 3.1 / 63.7 |
| svfigh | movement | 80 (7) | 197.9 | 2.24 | 34.6 | **4.3** | 3.0 / 129.5 |
| svfigh | combat | 20 | 36.3 | 0.33 | 38.9 | **11.7** | 0.2 / 22.2 |
| svfigh | combat | 40 | 60.7 | 0.56 | 37.0 | **8.6** | 0.3 / 38.4 |
| svfigh | combat | 80 | 138.1 | 1.51 | 34.8 | **5.0** | 0.7 / 90.1 |
| svfigh | flight | 20 | 33.0 | 0.30 | 48.1 | **25.1** | 8.5 / 17.1 |
| svfigh | flight | 40 | 63.0 | 0.63 | 41.1 | **14.5** | 10.4 / 37.1 |
| svfigh | flight | 80 (7) | 123.2 | 1.33 | 37.6 | **9.2** | 11.3 / 76.8 |
| avtank | idle | 20 | — | — | ~74.6 | **~26.6** | run incomplete; last interval only |
| avtank | idle | 40 | 123.0 | 1.58 | 70.4 | **14.4** | 6.9 / 36.4 |
| avtank | idle | 80 | 242.8 | 2.97 | 68.5 | **9.0** | 8.4 / 76.5 |
| avtank | firing | 20 | 33.2 | 0.35 | 73.4 | **23.2** | 0.7 / 8.8 |
| avtank | firing | 40 | 73.7 | 0.81 | 69.6 | **12.1** | 1.2 / 22.1 |
| avtank | firing | 80 | 188.9 | 2.46 | 67.9 | **7.0** | 2.2 / 59.3 |
| avtank | movement | 20 | 40.1 | 0.41 | 69.2 | **10.9** | 1.2 / 12.4 |
| avtank | movement | 40 | 88.1 | 0.97 | 67.8 | **7.0** | 1.1 / 28.4 |
| avtank | movement | 80 | 169.0 | 2.12 | 67.3 | **5.6** | 0.8 / 55.3 |
| avtank | combat | 20 | 40.3 | 0.42 | 69.2 | **10.9** | 0.0 / 12.4 |
| avtank | combat | 40 | 65.7 | 0.71 | 68.3 | **8.3** | 0.0 / 20.9 |
| avtank | combat | 80 | 149.3 | 1.92 | 67.3 | **5.7** | 0.0 / 48.6 |

The last column lists changed skins per frame whose every element moved by at
most 1e-5, out of all changed skins per frame. The avtank firing-80 run also
had 57 skins per interval it could not track (probe table contention). That
is too few to matter.

### Which bones change

The probe has no bone names, so the part names below are inferred, not
measured.
- **avtank:** the unchanged skins are the 3-matrix submeshes. The changing
  skin is the large submesh with 6–7 matrices.
  - In it, matrix slots 0–2 never changed in any scenario.
  - Slots 3–5 changed together on 76–95% of skins. Every change touched
    rotation, never translation alone.
  - So about half the bones of the body mesh animate every frame and the
    other half are static. Turret or hover parts would fit, unconfirmed.
- **svfigh:** changed skins split exactly 50/50.
  - In half, one matrix changes (slot 0 of a ~2-matrix submesh, ~30% of the
    time).
  - In the other half, all three matrices of a 3-matrix submesh change,
    with slot 2 changing on 83–98% of skins.
  - At idle and in flight, many changes are ≤1e-5 float noise, consistent
    with a damped wing or hover settle. That noise disappears under
    movement and combat, where the changes are real motion.
- **Both units:** the share of unchanged vertices falls as craft count rises
  (about 20–30% at 20 craft, 4–9% at 80). It also falls when craft move. A
  per-entity whole-palette check therefore helps least in exactly the
  case that costs most.

### Recommendation

- **Do not build the whole-palette skip cache.** At 80 craft it would save
  about 0.1–0.27 ms of 1.5–3.0 ms skin time. It would cost:
  - persistent per-entity blended buffers, about 156 KB per fighter, about
    12 MB at 80;
  - a palette compare on every skin;
  - a new fail-closed lifetime surface around Ogre's temp-buffer checkout.
  A tolerance-based check (treating the ≤1e-5 noise as unchanged) would not
  be exact, so it is out under the stock-identical rule.
- **Possible exact follow-up, not measured:** per-bone partial re-skinning.
  Rigs are rigid-part, and in avtank half the body's bones never move.
  Re-blending only the vertices that reference changed matrix slots, and
  keeping the rest from last frame, could save far more than whole-palette
  skips.
  - It still needs the persistent buffers above.
  - Its payoff depends on the vertex share per bone, which this probe does
    not measure.
  - Exactness depends on Ogre's SSE path producing per-vertex results
    independent of batch membership, which is plausible but unverified.
  - Measure that vertex share before designing it.
- Hardware skinning remains the only route to removing most of the cost,
  under the sub-pixel caveat above.

## Tooling changes in this workstream

`run_live_combat_benchmark.ps1` no longer force-kills
`battlezone98redux`.
- It takes the machine-wide launch lock from `BZRHarness.ps1`.
- It stops runs with `Stop-BZRGame -Id`.
- It refuses to continue if the game ignores WM_CLOSE.
- It restores `ogre.cfg` via the harness.

Notes for reruns:
- `-KillExisting` now means "close gracefully".
- The INI key `[Diagnostics] ProfileOgreAnimation` must be set for profiler
  samples. The env var alone is overridden by an INI value of 0.
- `ogre.cfg` VSync=Yes caps the sweep at ~58 fps.
