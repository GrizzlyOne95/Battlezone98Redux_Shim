# Shadow cutoff root cause — PSSM / headlight interaction RE

Date: 2026-08-25
Target: Battlezone 98 Redux GOG 2.2.301, DX11 and DX9 tested independently
Runtime fixture: `lcbench` + new `shadowline` scenario (28 stations, 25-700 m,
three idle avtank per station)
Branch: `agent/shadow-cutoff-re` (worktree `BZR-OpenShim-shadowcut-wt`)
Raw captures: `reverse_engineering/snapshots/shadow_cutoff_20260825/`

Evidence labels follow the repo convention: **CONFIRMED** (decompilation,
shipped asset, or runtime observation), **HIGH** (multiple direct facts, one
link not observed live), **MEDIUM** (bounded inference).

---

## 1. Executive verdict

The abrupt shadow cutoff is **receiver-side and has two stages, neither of
which is a PSSM split-distance problem**:

1. **The dominant visible termination sits at ~128 m, not at the 256 m outer
   split.** The executable calls `SceneManager::setShadowFarDistance(128.0)`
   (decompiled constant `0x43000000` in `FUN_00680fe0`). In Ogre's
   Focused/LiSPSM fit used by PSSM, that value clips the cascade intersection
   body at 128 m along the view direction
   (`FocusedShadowCameraSetup::calculateB`, local Ogre 1.10 source lines
   256-264). Cascade 3 is nominally responsible for view depths 64-256 m and
   the receiver shader selects it up to 256 m, but its fitted projection only
   covers receivers out to ~128 m. Beyond that, samples land outside the shadow
   map's border-clamped UV range, return the white border colour, and the
   pixel is lit. The result is a hard, unsupported shadow terminator at
   ~128 m — exactly the "shadow distance/cutoff" reported.

2. **A second, total receiver switch exists at 250 m (objects) / 256 m
   (terrain)** via material LOD: `BZBase.material` `lod_values 250 300` and
   `BZTerrainBase.material` `lod_values 256 512` (`lod_strategy Distance`)
   switch the `high-pssm` scheme to `MediumNoShadow`/`LowNoShadow` techniques.
   In stock content this is masked by fog (`FogEnd=250` on stock campaign
   terrains; lcbench ships 175-250), which is why the 128 m terminator is the
   one that shows.

**The headlight changes no shadow state whatsoever.** Runtime proof: the stock
headlight is an Ogre spotlight with `castShadows=no` (probe below), so it can
never enter the shadow-texture assignment; the four-arm matrix
(DX9/DX11 × headlight off/on) produced identical caster populations and
identical receiver technique/LOD distributions in every arm. What the headlight
changes is *visibility of the cutoff*: it is a non-shadow-casting spotlight
with range 600 m that illuminates terrain far beyond the 128 m terminator, so
the terminator becomes visible inside a lit pool. On DX11 there is an
additional amplifier: the stock DX11 receiver shader multiplies **every**
light's attenuation — including the headlight's — by the sun's PSSM factor
(`base-sm4.hlsl` line 356), so shadow-map structure, cascade seams, and the
128 m termination are stamped directly into the headlight pool. The DX9 shader
resets the shadow factor to 1.0 after the first light iteration
(`base.hlsl` lines 351-354) and therefore hides all of this from its pool.

Narrowest safe correction: raise the shadow far distance to match the outer
split (≥ 256 m) via the game's own setter seam. See section 8.

---

## 2. Reproduction matrix

Fixture: `lcbench.bzn` + new `shadowline` scenario in
`reverse_engineering/test_missions/live_combat_scaling/lcbench.lua` — one trio
of idle, same-team avtank at stations 25, 50, 75 … 700 m along the sight line
(spacing 25 m, lateral −10/0/+10 m), spawned after an eight-heading terrain
probe that re-faces the player down the flattest corridor. Station distances
are traced (`shadowline-station=N distance=X`) so captures score against exact
ranges. Runner: `run_shadow_cutoff_matrix.ps1` (windowed, topmost, logs and
frames captured per arm; `analyze_shadow_cutoff_matrix.py` aggregates
contributor rows; `enhance_shadow_frames.py` / `diff_headlight_frames.py`
process frames).

Because the workstation's stored graphics config had vehicle shadows disabled
(see §5), the PSSM path was enabled for the measured arms by writing the
game's own settings bytes and invoking the game's own apply function via Frida
(`set_shadow_quality.js`, quality 3 = PSSM/2048, detail 0 = high). The final
matrix ran with PSSM active in all four arms:

| Arm | Renderer | Headlight | Shadow scheme active | Cascade cameras observed | Caster population per cascade | Receiver lod0/1/2 populations |
|---|---|---|---|---|---|---|
| matrix_pssm/dx11_off | DX11 | off | high-pssm | 3 | identical | lod0 + lod1 + lod2 |
| matrix_pssm/dx11_on | DX11 | on | high-pssm | 3 | identical | lod0 + lod1 + lod2 |
| matrix_pssm/dx9_off | DX9 | off | high-pssm | 3 | identical | lod0 + lod1 + lod2 |
| matrix_pssm/dx9_on | DX9 | on | high-pssm | 3 | identical | lod0 + lod1 + lod2 |

Measured observations:

- **Casters:** `Ogre/ShadowTexture2Cam/3Cam/4Cam` each received the full
  vehicle caster set (~255-256 avtank submissions/f for the 84-tank line in
  `pipeline_check6`; ~4.8 k/f aggregated per cascade in `matrix_pssm` — same
  population as the main camera). Tanks at 600-700 m are still submitted to
  all three cascades. **The cutoff is not caster culling.** This replicates
  the earlier distance-sweep finding
  (`distant_unit_submission_triage_20260822.md`: identical shadow submissions
  at 50/250/1000 m).
- **Receivers:** `PlayerCam` rows show `scheme=high-pssm` with `lod=0`
  (PSSM-receiving technique), `lod=1`, and `lod=2` (the material-LOD switch to
  NoShadow techniques) simultaneously — the populations predicted by
  `lod_values 250 300` / `256 512`. Distribution identical across all four
  arms.
- **Headlight delta:** none. Caster counts and LOD distributions are equal
  within noise across headlight off/on on both renderers.
- **Visual:** the moon fixture (Time=0300, Ambient=0, TerrainShadowLuma=40) is
  too low-contrast to read the terminator directly in RGB; the headlight
  contribution diff (`diff_headlight_frames.py`) isolates the pool and shows a
  hard-edged pool ending near the first stations, with the DX11 pool carrying
  shadow-map structure the DX9 pool lacks (peak contribution 22.9 vs 17.0).
  The 128 m terminator itself is confirmed by the CPU-side evidence chain in
  §3-§4 rather than by RGB measurement (see §10 Unknowns).

---

## 3. Native/Ogre call chain

Executable (GOG 2.2.301, image base 0x400000; decompilation corpus
`reverse_engineering/decompilation_from_1.5_exe-pdb/`):

| Address (VA) | Role | Evidence |
|---|---|---|
| `0x00680fe0` | Shadow/viewport apply: reads settings, configures shadow textures, PSSM camera setup, per-viewport material scheme | decompiled `FUN_00680fe0-00680fe0.c`; runtime-invoked via Frida (RVA 0x280fe0) |
| `0x0094672c` | Settings struct pointer (`DAT_0094672c`); `+0x25` shadow quality (sbyte, −1 = off, 2-4 = PSSM 1024/2048/4096), `+0x27` scheme detail (0=high…3=lowest) | decompiled; runtime read/write confirmed (`quality=-1 detail=0` before mutation) |
| `0x007af310` / `0x007af3e0` | The game's own quality/detail setters: write `+0x25` / `+0x27` then call `0x00680fe0` | decompiled callers |
| `0x007a9590` | Mission-load path that calls `0x00680fe0` (after `Viewport::setVisibilityMask`) | decompiled caller |
| `0x0067F599` | Stock headlight creation: `setAttenuation(600, 1, 0.007, 0.0002)` | shim comment + runtime probe |

Inside `FUN_00680fe0` (PSSM branch, quality ≥ 2):

- `setShadowTextureSettings(size, 3, PF_FLOAT32_R=33, 0, 1)` — three textures.
- **`setShadowFarDistance(128.0)`** (vtable slot `+0x394`, constant
  `0x43000000`).
- `setShadowDirLightTextureOffset(0.8)` (`0x3f4ccccd`), directional light
  extrusion `192.0` (`0x43400000`).
- `setShadowTextureCountPerLightType(LT_DIRECTIONAL, 3)`.
- `PSSMShadowCameraSetup`, aggressive focus, split points `0.1/16/64/256`,
  per-split optimal adjust factors all `0.0` (Ogre default split padding 1.0
  → camera coverage `[15,17]`, `[63,65]`).
- Per-viewport `setShadowsEnabled` + `setMaterialScheme("high-pssm")`
  (detail byte selects high/medium/low/lowest).

OgreMain.dll (shipped; semantics verified against local Ogre 1.10 sources):

| Item | Value | Evidence |
|---|---|---|
| `SceneManager::_populateLightList` body | RVA `0x003B3930` | audit-verified against released DLL; re-confirmed by Frida attach |
| `Light::getShadowFarDistance` export | `?getShadowFarDistance@Light@Ogre@@QBEMXZ` (non-virtual `Q`, a deviation from vanilla 1.10's virtual `U`) | export table dump |
| `SceneManager::setShadowFarDistance` export | `?setShadowFarDistance@SceneManager@Ogre@@UAEXM` | export table dump |
| Frustum light sort | casters first, then temp-square-dist (directional = 0) | `OgreSceneManager.cpp:4427-4440` |
| Texture-shadow caster collection | no far-distance per-caster cull (that test exists only in the stencil-volume listener, `OgreSceneManager.cpp:4560-4573`) | source |
| `prepareShadowTextures` | iterates sorted frustum lights; sun (directional caster, dist 0) always consumes textures 0-2 | `OgreSceneManager.cpp:6324-6457` |
| Focused/PSSM body-B clip | `mBodyB.clip(plane at light.getShadowFarDistance() along camera dir)` for directional lights | `OgreShadowCameraSetupFocused.cpp:256-264` |
| PSSM split padding | ±1.0 around each interior split; per-split LiSPSM fit with main-camera near/far temporarily set to the split slab | `OgreShadowCameraSetupPSSM.cpp:100-134` |

Runtime light-state probe (`[HEADLIGHT-PROBE]`, player headlight, per frame):

```text
type=2 (spotlight) range=600.0 attenuation=(c=1.0 l=0.007 q=0.0002)
inner=10.00deg outer=20.00deg falloff=1.000 visible=yes castShadows=no
```

`Headlights = 0` is implemented by the shim as `Light::setVisible(false)`
(`bzr_hooks.cpp:15628`), which removes the light from
`findLightsAffectingFrustum` entirely — it cannot affect shadow textures in
either state because it never cast shadows in either state.

---

## 4. PSSM runtime values

| Parameter | Value | Source |
|---|---|---|
| Technique | Texture-based, PSSM (3 cascades), additive-integrated receivers | decompiled + scheme table |
| Shadow texture count | 3, all `LT_DIRECTIONAL` | decompiled; runtime camera names `Ogre/ShadowTexture2Cam/3Cam/4Cam` |
| Texture size | 2048 at quality 3 (1024/2048/4096 at 2/3/4); format `PF_FLOAT32_R` | decompiled table |
| Split points | 0.1 / 16 / 64 / 256 | decompiled **and** static in every stock material (`base.program`: `pssmSplitPoints float4 0.1 16.0 64.0 256.0`) |
| Split padding | 1.0 (Ogre default; not overridden) → effective coverage `[15,17]`, `[63,65]` | Ogre source; decompile shows no padding call |
| Optimal adjust factors | 0.0, 0.0, 0.0 | decompiled |
| Shadow far distance | **128.0** | decompiled constant; the value `Light::getShadowFarDistance()` returns and the Focused fit clips against |
| Dir-light texture offset | 0.8 | decompiled |
| Dir-light extrusion | 192.0 | decompiled |
| Receiver cascade selection | `vDepth <= 16 → map1; <= 64 → map2; else map3` with `vDepth = clip-space z ≈ view distance` | `base-sm4.hlsl:264-277`, `terrain-sm4.hlsl:274-287`; identical in DX9 sources |
| Shadow remap | `shadow = shadow*0.7 + 0.3` (0.3 ambient floor) | `base-sm4.hlsl:279`, `terrain-sm4.hlsl:289`, `base.hlsl:261` |
| Effective cascade-3 ground coverage | **~64-128 m, not 64-256 m** | body-B clip at shadow far distance (Focused source) + 128 constant |

Consequence: receivers with view depth in (128, 256] select cascade 3 and
sample outside its fitted area → white border → fully lit. The shader's own
split constant (256) overstates the CPU-fitted coverage by 2×.

---

## 5. Headlight delta

**First diverging state value: none.** Every shadow-relevant state was
captured immediately around the headlight toggle across the four-arm matrix:

| State | Headlight off | Headlight on |
|---|---|---|
| Shadow-casting light set | sun only | sun only (`castShadows=no` on headlight, runtime probe) |
| `getLightsAffectingFrustum` ordering effect | headlight absent | headlight present as non-caster; cannot precede the sun (directional casters sort first, `lightsForShadowTextureLess`) |
| Shadow texture assignment | sun → textures 0-2 | identical |
| PSSM camera setup / far distance / near-far | unchanged | unchanged |
| Caster submissions per cascade | ~255/f × 3 | ~255/f × 3 (equal within noise) |
| Receiver scheme/technique/LOD distribution | high-pssm lod0/1/2 | identical |
| Visibility masks / render queues | unchanged | unchanged |

The only states that change are the light's own illumination parameters
(`setVisible`, and under shim overrides colour/beam/falloff). The stock
light's stored state at creation: range 600, attenuation (1, 0.007, 0.0002),
cone 10°/20°, falloff 1.0, diffuse/specular white ×1 (probe values above).

Why the symptom tracks headlight state anyway:

1. **Illumination exposure.** The pool reaches far beyond the 128 m
   terminator. With the headlight off, the fixture's ~0 ambient (and stock
   night/dusk missions generally) hides everything past a few tens of metres;
   with it on, terrain out to hundreds of metres is visible and the terminator
   at ~128 m becomes an obvious hard edge. The same applies to the 250/256 m
   material-LOD switch on brighter maps.
2. **DX11-only import of shadow structure into the pool.** The stock DX11
   shader applies the sun's PSSM factor to every light iteration
   (`base-sm4.hlsl:354-357`; same in `terrain-sm4.hlsl:365-367`), so the
   headlight pool is darkened by the shadow map — including its cascade seams
   (16/64 m), its 128 m termination, and any caster acne. The DX9 shader
   resets `shadow = 1.0` after the first (sun) iteration (`base.hlsl:351-354`)
   and its pool is clean. This is a real renderer divergence, confirmed from
   the shipped HLSL in `BZ_ASSETS_CORE/pc/programs/`, and it is why the
   symptom is *substantially worse on DX11 with the headlight on*.

Environmental finding: this workstation's stored config had
`settings+0x25 = -1` (vehicle shadows disabled). In that state the game builds
a 1×1 dummy shadow texture, disables viewport shadows, and selects the
`high-noshadow` scheme — no PSSM at all (`FUN_00680fe0` negative branch;
confirmed at runtime: contributor rows showed `high-noshadow` before the
setting was applied). Any cutoff report necessarily comes from a config with
quality ≥ 2. The setting was restored to −1 after the captures.

---

## 6. Caster/receiver disposition

For representative objects on both sides of the cutoff (84-tank shadowline):

| Object distance | Submitted as caster? | Rendered into a shadow texture? | Receiver technique | Receiver samples usable shadow? | Disposition |
|---|---|---|---|---|---|
| 25-64 m | yes (all 3 cascades) | yes | `high-pssm` lod0 (PSSM) | yes (cascade 1/2) | working |
| 64-128 m | yes | yes | `high-pssm` lod0 | yes (cascade 3, inside fit) | working |
| 128-250 m | yes | yes (casters still rendered) | `high-pssm` lod0 | **no — cascade 3 sampled outside fit → lit** | **SHADOW CAMERA RANGE (the reported cutoff)** |
| 250-300 m | yes | yes | lod1 technique (NoShadow) under `high-pssm` | no sampling at all | material-LOD receiver switch (masked by fog) |
| 300-700 m | yes | yes | lod2 technique (NoShadow) | no sampling at all | material-LOD receiver switch |

Diagnosis against the candidate list:

- **CASTER CULLING** — ruled out. Casters are submitted at every distance to
  every cascade (runtime; also `distant_unit_submission_triage_20260822.md`).
- **SHADOW CAMERA RANGE** — **the cause.** Cascade 3's fitted coverage ends at
  the 128 m shadow-far-distance clip while the receiver shader believes it
  extends to 256 m.
- **CASCADE SELECTION** — correct per the shader constant; the constant is
  what lies about the coverage.
- **RECEIVER FADE** — none exists in stock (no fade term in the shaders; the
  Ogre receiver-pass fog fade applies only to the fixed-function modulative
  path, unused here).
- **WRONG LIGHT / WRONG SHADOW TEXTURE** — ruled out. The sun is always the
  first caster (directional temp-square-dist = 0, stable sort); the headlight
  never casts and cannot displace textures. Runtime matrices identical across
  headlight states.
- **MATERIAL/SCHEME PROBLEM** — a second, independent cutoff at 250/256 m
  (material LOD technique switch), by design; masked by fog in stock content.

---

## 7. DX9 versus DX11

| Property | DX9 | DX11 |
|---|---|---|
| Shadow technique | PSSM, 3 cascades (identical CPU setup) | identical |
| Cascade count | 3 | 3 |
| Shadow far distance | 128 (same executable code) | 128 |
| Headlight changes active light/shadow state | no | no |
| Caster cutoff | none (all distances submitted) | none |
| Receiver cutoff (sun shadows) | ~128 m (cascade-3 fit) | ~128 m (cascade-3 fit) |
| Receiver technique switch | 250/300 m objects, 256/512 m terrain | same |
| Headlight pool multiplied by sun PSSM factor | **no** (`base.hlsl:351-354` resets `shadow=1.0` after light 0) | **yes** (`base-sm4.hlsl:354-357`, no reset; same in `terrain-sm4.hlsl`) |
| Pool shows cascade seams / 128 m termination | no | yes |
| Root cause of the reported cutoff | shared: shadow-far-distance clip on cascade 3 | shared, plus pool-visible shadow structure amplifying it |

**The bug is shared.** The 128 m termination and the material-LOD switch
behave identically (same CPU code, same materials, same split constants).
The DX11 shader's missing `shadow = 1.0` reset is a separate, DX11-only
divergence that makes the headlight pool display shadow-map structure — the
reason the symptom reads as "headlight makes the cutoff worse" on DX11.

---

## 8. Recommended intervention seam

**A — preferred: raise the shadow far distance to match the outer split
(`setShadowFarDistance` 128 → ≥ 256).**

- One CPU-side value; the game's own setter (`SceneManager::setShadowFarDistance`,
  called from `FUN_00680fe0`) is the seam. A shim implementation would re-issue
  the setter after `FUN_00680fe0` runs (or intercept the `+0x394` vtable call),
  quarantined behind an environment variable, stock-exact when disabled.
- Fixes the premature 128 m termination without touching split distances,
  shaders, materials, or the headlight. Cascade 3's nominal contract (64-256 m)
  becomes true.
- Must be validated on DX9 and DX11 with the shadowline fixture, and benchmarked
  (submissions/frame will not change — casters are already all submitted; the
  cascade-3 fit covers 2× the ground at the same texel budget, so effective
  resolution there halves; measure visual quality at 64-128 m before/after).
- Do not couple it to shadow quality (the 128 constant is written for every
  PSSM quality; the fix should track the outer split, not the quality byte).

**B — alternate (content-side, already shipped for CR Enhanced only):** the CR
Enhanced V2 receiver fade (last 24 units fade to lit; samples stop at 256)
hides the unsupported region for `en-*` schemes. It does not help stock
schemes and does not address the 128 m clip; acceptable as a mitigation, not
as the fix.

**C — rejected:**

- Raising the split distances themselves — the splits are not the cause; doing
  so changes near-field resolution for no benefit and must be kept in lockstep
  between CPU and four material copies.
- Editing `pssmSplitPoints` shader constants blindly — desynchronises
  receiver selection from the CPU fit.
- Per-cascade distant caster culling *as a fix for the cutoff* — casters are
  not the cause; culling is a performance policy (§9), not a correctness
  change.
- Any headlight-side change — the headlight is provably not involved in the
  shadow pipeline; altering its illumination to hide the cutoff would degrade
  unrelated lighting.

---

## 9. Performance implications

(Recorded only; no optimization was made during this investigation.)

- Vehicle shadow-caster submissions are **distance-invariant** and submitted to
  **all three cascades** (re-confirmed: ~255/f per cascade for the 84-tank
  line; prior triage measured identical counts at 50/250/1000 m). The largest
  remaining legitimate win is per-cascade distant caster culling
  (`distant_unit_submission_triage_20260822.md` second experiment) — it is a
  policy change and must be measured separately from this fix.
- Raising the shadow far distance to 256 does **not** increase caster
  submissions (they are already unbounded) and does not add passes; its cost
  is halved texel density in cascade 3 and a larger fitted area. If that
  proves visually costly, the honest alternative is raising the texture size
  at quality 4, or accepting B's fade for stock as a separate, explicit
  change.
- The material-LOD NoShadow switch at 250/256 m already bounds receiver cost;
  it also means any fix that extends usable coverage past 250 m is partially
  masked on objects (250 m) and terrain (256 m) — the *useful* correction
  window for seam A is exactly 128-250 m.

---

## 10. Unknowns

- **The 128 m terminator was not measured in RGB.** The moon fixture's ambient
  and `TerrainShadowLuma=40` make ground shadows too low-contrast for a
  reliable pixel measurement; the 128 m value is CONFIRMED as the CPU-side
  clip constant (decompilation) and the clip behaviour is source-verified in
  Ogre 1.10, but the shipped `OgreMain.dll`'s
  `FocusedShadowCameraSetup::calculateB` / LiSPSM / PSSM bodies were not
  byte-diffed against vanilla 1.10 (the earlier audit byte-verified
  `_populateLightList`, `renderSingleObject`, `Pass`, and
  `AutoParamDataSource` paths only). Confidence: HIGH, not CONFIRMED-end-to-end.
- `Light::getShadowFarDistance` runtime return values were not captured (the
  Frida interpose used a stale mangled name — the shipped export is
  non-virtual `QBEM`; corrected in the script but not re-run).
- The stock headlight pool's own hard edge at ~35-40 m on the night fixture
  (spot cone/attenuation interplay) is not explained by the shadow state and
  predates this investigation (see the headlight-falloff work and
  `HeadlightFalloffRepair`); it is recorded as a headlight-side behaviour,
  not a shadow finding.
- Whether the 128 constant was deliberately tuned to hide under stock fog
  (stock campaign terrains ship `FogEnd=250`, lcbench 175-250) is unknowable
  from the binary; the fix's visual acceptance should account for content
  that sets fog farther out.
- DX9 arm renderer identity was verified via the shim profiler
  (`configured renderer=Direct3D9`), not via `BZOgreLogfile.log` (the copied
  root-level log was stale).

---

## Appendix — artifacts

- Harness/fixture (task-owned, on branch):
  - `reverse_engineering/test_missions/live_combat_scaling/lcbench.lua`
    (adds the `shadowline` scenario; existing scenarios unchanged)
  - `reverse_engineering/run_shadow_cutoff_matrix.ps1`
  - `reverse_engineering/analyze_shadow_cutoff_matrix.py`
  - `reverse_engineering/enhance_shadow_frames.py`
  - `reverse_engineering/diff_headlight_frames.py`
  - `reverse_engineering/set_shadow_quality.js` (Frida: apply quality 3 via
    the game's own code path; also interposes `get/setShadowFarDistance`)
  - `reverse_engineering/restore_shadow_quality.js` (Frida: restore −1)
  - `reverse_engineering/trace_light_lists.js` (Frida: `_populateLightList`
    observer; not needed for the verdict, kept for reuse)
- Raw captures: `reverse_engineering/snapshots/shadow_cutoff_20260825/`
  (`matrix_pssm/` is the authoritative four-arm set;
  `matrix_v1/` is the shadows-disabled control that surfaced the config
  finding; `pipeline_check*/`, `pool_probe/`, `lightlist_trace*/`,
  `shadowfar_probe*/` are intermediate; `restore_run/` documents the setting
  restore).
- Workstation state: `BZPLYR.DEF` byte 0x25 restored to `0xFF` (quality −1)
  after captures; `Ogre.cfg`/`openshim.ini`/`lcbcfg.odf` restored by the
  runner's `finally`.
