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
- **Update (Phase 3):**
  - The pose probe ruled out the skip cache.
  - The user accepted sub-pixel differences, provided GPU skinning is a
    toggle.
  - It is now built as `[Experimental] GpuSkinning` (default off), with a
    Video menu row "GPU Skinning".
  - At 80 idle craft on DX11 it raises fps by about 75% (98 → 175).
  - See *Phase 3*.

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

## Phase 2 findings (design; built in Phase 3)

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

## Phase 3: hardware skinning, built behind a toggle

The design follows Phase 2. Code is in `src/patches/gpu_skinning.cpp`, and the
HLSL transform is in `gpu_skinning_hlsl.cpp` with host tests.

### What it does

- **Setting:**
  - `[Experimental] GpuSkinning = 0|1`, default 0; env var
    `OPENSHIM_GPU_SKINNING`.
  - Video menu row "GPU Skinning".
  - It is read when a mission starts, so a change applies on the next mission
    load.
  - A command-line launch gives no run-state transition, so the first world
    render evaluates the setting instead.
  - DX11 only. There is no multiplayer gate: each client's skinning is local
    presentation.
- **Programs:**
  - Every installed HLSL4 vertex program a craft pass uses gets a skinned
    twin, generated at runtime from the program's own source.
  - Nothing is shipped.
  - World-dependent auto constants are remapped, because under hardware
    skinning Ogre's "world" is bone 0.
  - A skinned `Ogre/DepthShadowmap/CasterVP_HLSL4` replaces the caster vertex
    program, so shadows follow the pose.
- **Materials:**
  - A clone is made per (source material, weights per vertex).
  - It is named `OpenShim/GpuSkin/<gen>/w<N>/<material>`.
  - Non-skeletal users of BZBase keep the stock material.
- **Per-entity fail-closed:**
  - An entity switches only if every sub-entity converts and Ogre then
    reports `isHardwareAnimationEnabled`. Otherwise its stock materials
    return.
  - Converted entities are re-verified every frame before rendering.
  - A 64-bone cap applies.
  - A new candidate must pass an RTTI check for `Ogre::Entity`.
  - Any SEH or C++ fault latches the feature off for the process.
- **Logging:**
  - Each mission ends with `[GPUSKIN] mission summary: converted=…
    rejects={…}`.

### Results (DX11, windowed, VSync off, profiler on, same session for both arms)

All 12 GPU runs converted every craft (count + 1, which includes the player),
with zero rejects, reverts, faults or crashes.

- **Interleaved check:**
  - The 80-craft idle runs used the arm order stock, GPU, stock, GPU, to rule
    out drift.
  - avtank: 98 / 175 / 95 / 174 fps.
  - svfigh: 102 / 176 / 101 / 175 fps.
- **Sweep:**
  - The table below has one run per cell.
  - The stock fps is below Phase 1 because the machine was more loaded this
    session. Compare the arms with each other, not with Phase 1.

| unit | scenario | craft | stock fps | GPU fps | stock skin ms | GPU skin ms |
|---|---|---:|---:|---:|---:|---:|
| avtank | idle | 20 | 269 | 346 | 0.49 | 0.02 |
| avtank | idle | 40 | 167 | 267 | 1.04 | 0.08 |
| avtank | idle | 80 | 97 | 178 | 2.11 | 0.03 |
| avtank | firing | 20 | 170 | 181 | 0.25 | 0.03 |
| avtank | firing | 40 | 107 | 122 | 0.60 | 0.03 |
| avtank | firing | 80 | 56 | 71 | 1.72 | 0.06 |
| svfigh | idle | 20 | 278 | 343 | 0.40 | 0.02 |
| svfigh | idle | 40 | 176 | 261 | 0.89 | 0.03 |
| svfigh | idle | 80 | 102 | 177 | 1.87 | 0.03 |
| svfigh | firing | 20 | 217 | 233 | 0.25 | 0.02 |
| svfigh | firing | 40 | 141 | 165 | 0.53 | 0.03 |
| svfigh | firing | 80 | 56 | 67 | 1.54 | 0.04 |

- **Frame time:**
  - The saving is larger than the skin ms alone. At 80 idle craft, frame time
    drops by about 4.6 ms, while skinning plus its buffer `Map` accounted for
    about 2.3 ms.
  - The remainder is most likely driver-side work for about 240 dynamic
    vertex-buffer uploads per frame (inferred, not measured).
  - The GPU arm still makes about 3 CPU skin calls per frame. That entity has
    not been identified.
- **Visual parity (method):**
  - 20 craft per run, arm order stock, GPU, stock, GPU, for avtank and svfigh.
  - Each run captured 6 frames via `PrintWindow(PW_RENDERFULLCONTENT)`, so
    there was no foreground change and no input.
  - Frames were compared at matched indices.
  - Runs are not frame-locked, so stock against stock is the noise floor.

| unit | pair | mean abs diff | pixels > 8 |
|---|---|---:|---:|
| avtank | stock vs stock | 2.09 | 3.8% |
| avtank | GPU vs GPU | 1.39 | 3.2% |
| avtank | stock vs GPU | 1.10 | 2.5% |
| svfigh | stock vs stock | 1.22 | 3.3% |
| svfigh | GPU vs GPU | 0.14 | 0.4% |
| svfigh | stock vs GPU | 0.70 | 1.9% |

- **Visual parity (findings):**
  - Stock-vs-GPU differences are within run-to-run noise.
  - A zoomed side-by-side shows the same poses (svfigh wings deployed),
    lighting, engine glow and silhouettes.
  - No craft rendered in bind pose.
- **Limits of this check:**
  - The craft are small, about 30 px at 50 m in a 584x900 window, and partly
    behind the HUD.
  - It rules out gross errors: wrong pose, double transform, lost shadow or
    lost texture.
  - It cannot see sub-pixel edge flips, or specular and normal detail on a
    close-up craft.
  - Close-range and shadow-heavy views still need a look in play.

### Pitfalls hit while building it

- **Non-virtual exports:**
  - Calling an exported virtual such as `GpuProgram::getLanguage` through its
    export runs the base implementation and skips the override.
  - Every HLSL4 program then reported `asm`.
  - The fix identifies `D3D11HLSLProgram` by RTTI instead.
- **Mangled names:**
  - In the hand-written mangled names, the `std::string` fragment is followed
    directly by the next token, with no extra `@`.
  - All required exports are checked at resolve time, and the feature stays
    off if any is missing.
- **DX11COMPAT warning:** the `[DX11COMPAT] unsupported custom programs …
  action=skip` warning is logged for the clones exactly as it is for stock
  `avtank00`, so it is pre-existing.

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
