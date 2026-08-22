# DX11 Enhanced dynamic-light audit

Date: 2026-08-20

Target: Battlezone 98 Redux 2.2.301, Campaign Reimagined, DX11 Enhanced

Status: **implemented and automatically validated; interactive visual validation pending**

Evidence labels:

- **CONFIRMED**: directly observed in source, a shipped binary, shader bytecode,
  a runtime trace, or an automated test.
- **HIGH confidence**: supported by multiple direct observations, but the exact
  modern BZCC CPU implementation was unavailable.
- **MEDIUM confidence**: consistent but incomplete evidence.
- **SPECULATIVE**: retained only as a later test hypothesis.

## Executive result

The widely reported eight-light behavior is **not a hard limit in Campaign
Reimagined Enhanced High**. Ogre initializes `Pass::mMaxSimultaneousLights` to
eight, but `SceneManager::renderSingleObject` treats the default value as a
sentinel for an ordinary non-iterated, unmasked pass and forwards the complete
per-renderable light list. CR's High SM4 programs then cap evaluation at 24.
An unattended mission trace observed nine candidates on the stock deployed
`en-high-noshadow` path, directly proving that more than eight reach it.

The actual High saturation boundary is therefore 24/25 (normally the sun plus
23 locals), not 8/9. Medium is shader-limited to eight and Low/Lowest to one.
The apparent eight-light symptom may come from Medium, older/non-Enhanced paths,
or ordinary light birth/death and distance-order replacement; no single visual
cause is claimed without an interactive A/B.

The confirmed weakness is selection quality. Ogre range- and mask-filters per
renderable, then stable-sorts only by squared center distance. It ignores light
energy, attenuation magnitude, spotlight cone, and selection history. The
implemented experiment preserves the existing 24-light High budget and replaces
only the ordering for CR `en-*` schemes with:

- contribution-based local-light relevance;
- deterministic identity tie-breaking;
- five-percent cutoff retention;
- directional-light producer order, preserving the sun/PSSM contract;
- exact-build and DX11 gating with fail-closed behavior;
- bounded opt-in diagnostics and an exact stock-order A/B switch.

No CR shader/material change, Ogre binary modification, DX9 change, Classic
change, gameplay-state change, light-lifetime change, or local-light shadow map
was required.

## 1. Exact current BZR/Ogre/CR path

### Gameplay light creation — CONFIRMED

Released GOG executable code at VA `0x0044C840` constructs the BZR `LightRender`
Ogre light and supplies:

- type from the render definition at `+0x17C`;
- world position and direction;
- range from `+0x16C`;
- attenuation `(constant=1, linear=0, quadratic=15/range^2)`;
- spotlight inner/outer angles from `+0x180/+0x184`, falloff 1;
- diffuse/specular color.

The update path at VA `0x0044CB70` refreshes position, direction, attenuation,
and animated color. Weapon, explosion, projectile, map, and vehicle lights thus
become normal Ogre `Light` objects before render selection.

### Scene query and per-renderable list — CONFIRMED

The matching local Ogre 1.10 source establishes this path:

1. The scene manager maintains visible/frustum light candidates.
2. `MovableObject::queryLights` caches a list per movable object and refreshes it
   when the scene light-dirty counter changes
   (`OgreMain/src/OgreMovableObject.cpp`, `MovableObject::queryLights`).
3. `SceneManager::_populateLightList` applies light masks and range tests
   (`OgreMain/src/OgreSceneManager.cpp`).
4. Directional lights are admitted; point/spot lights must intersect the
   object's world bounding sphere through `Light::isInLightRange`.
5. `Light::_calcTempSquareDist` assigns zero to directional lights and exact
   squared object-center distance to local lights.
6. `SceneManager::lightLess` stable-sorts only that temporary distance.

`_populateLightList` itself does **not** truncate the list. Selection is per
renderable/object, not one global scene set. Different objects can receive
different candidates and ordering.

### The Ogre value 8 and why it is not the High cap — CONFIRMED

- `OgreMain/include/OgreConfig.h`: `OGRE_MAX_SIMULTANEOUS_LIGHTS` is 8.
- `OgreMain/src/OgrePass.cpp`: a new pass initializes
  `mMaxSimultaneousLights` to 8.
- `OgreMain/src/OgreSceneManager.cpp`, `renderSingleObject`: a temporary capped
  list is built only when the pass maximum differs from the default, the light
  start is nonzero, or the light mask is restricted. With default 8, start 0,
  and the ordinary mask, Ogre forwards the original complete list.
- `OgreMain/src/OgreAutoParamDataSource.cpp`: `getLight(index)` checks the
  current list size, and `getLightCount()` returns the complete list size.
- The compile-time eight-element arrays in `AutoParamDataSource` cache light
  projector/shadow matrices; they are not the ordinary direct-light upload cap.

Released `OgreMain.dll` confirms the same behavior:

| Function/behavior | Released RVA / instruction evidence |
|---|---|
| `Pass` constructor body | `0x002D9A30`; writes 8 at `0x002D9B89` |
| `Pass::setMaxSimultaneousLights` | export RVA `0x0001389A`; stores the supplied value without an 8 clamp |
| `SceneManager::_populateLightList` | body RVA `0x003B3930` |
| `Light::_calcTempSquareDist` | body RVA `0x0021BAE0` |
| `SceneManager::renderSingleObject` | body VA `0x103D1590`; compare-to-8 at `0x103D1C2D`, default path forwards the original list |
| `AutoParamDataSource::getLight` | body VA `0x100C60E0`; bounds against list size only |
| `AutoParamDataSource::getLightCount` | body VA `0x100C6230`; returns vector size |

### CR material/program/shader contract — CONFIRMED

`Shaders/CR_base.program`, `CR_terrain.program`, and `CR_static_ibl.program`
bind six 24-entry High arrays: diffuse, specular, view-space position,
attenuation, spotlight parameters, and view-space direction, plus
`light_count`. `CR_base-sm4.hlsl` and `CR_terrain-sm4.hlsl` use a compile-time
`MAX_LIGHTS=24` loop with a runtime active-count exit. Medium equivalents bind
eight; Low/Lowest bind one.

DXBC inspection found a 2,496-byte primary constant buffer with the six packed
24-entry arrays and `lightCount` at byte offset 2,432. The loop is dynamically
indexed, so scenes with three active lights do not execute 24 complete lighting
iterations. Representative existing High pixel shaders were approximately:

| Variant | Instruction slots | Texture samples |
|---|---:|---:|
| Base PSSM | 597 | 52 |
| Terrain PSSM | 600 | 54 |
| Base no-shadow | 278 | 4 |
| Terrain no-shadow | 281 | 6 |

The PSSM factor applies to the primary/sun iteration and is reset for later
iterations. Local point/spot lights remain unshadowed direct illumination.

### Exact current count matrix — CONFIRMED

| Path | Effective ordinary direct-light budget |
|---|---:|
| DX11 Enhanced High | 24 total, shader limit |
| DX11 Enhanced Medium | 8 total, shader limit |
| DX11 Enhanced Low/Lowest | 1 total, shader limit |
| DX11 Classic | unchanged stock behavior |
| DX9 | unchanged stock behavior |

The sun shares the ordinary High list and normally occupies element zero.

## 2. Current ordering and instability

| Question | Result | Evidence |
|---|---|---|
| Global or per object? | Per renderable/object cached list | **CONFIRMED** |
| Range/mask filtering? | Yes, before ordering | **CONFIRMED** |
| Primary order? | Directional first, locals by squared center distance | **CONFIRMED** |
| Intensity/attenuation magnitude? | Not considered by ordering | **CONFIRMED** |
| Spotlight cone? | Not considered by ordering | **CONFIRMED** |
| Stable tie-break by identity? | No | **CONFIRMED** |
| Cutoff hysteresis? | No | **CONFIRMED** |
| Hard global count of 8? | No | **CONFIRMED** |
| Enhanced High limit of 8? | No; runtime observed 9 | **CONFIRMED** |

At 24/25, tiny object/light movement can reverse distance order and swap two
nearly equal cutoff candidates. A closer but weak or off-axis light can also
displace a stronger contributor. This produces mathematically confirmed set
churn. Its exact share of the reported visible flicker remains **HIGH
confidence**, pending interactive comparison. Abrupt creation/expiration can
cause legitimate lighting changes independently and was not altered.

## 3. BZ2/BZCC comparison

### Installed modern BZCC — CONFIRMED shader/config evidence

Installation inspected: `C:\Program Files (x86)\Steam\steamapps\common\BZ2R`.

- `battlezone2.exe` version 2.0.185, SHA-256
  `2319FB1CBB3A1D35E8D3FFDDB501F8B9518DB1C9EBAB893D34D7024D8535F426`.
- `render.cfg` sets `MaxHWLights=16`.
- `bz2r_res/config/GamePrefs.ini` sets `LitObjectMinimumSize=40` and contains
  adaptive `LightsNone`, `LightsOne`, `LightsNoHeadlights`, and `LightsAll`
  quality stages.
- Reflected DX11 bytecode contains 16 packed five-float4 light entries and a
  runtime active count. Light zero receives sunlight/PSSM; later locals do not.
- The shader distinguishes directional, point, and spot inputs and evaluates a
  smooth spot cone.

Recovered BZCC shading combines:

```text
radial = max(1 - (distance / range)^2, 0)
denominator = constant + linear*distance + quadratic*distance^2
distanceTerm = radial / denominator
spotTerm = smooth inner/outer-cosine cone raised by falloff
```

The installed release has no modern CPU LightManager source. A claim that BZCC
uses a specific identity tie-break or hysteresis rule would therefore be
**SPECULATIVE** and is not an implementation premise.

### BZ2 source/decompilation corpus — CONFIRMED legacy behavior

The local BZ2 corpus exposes `LightManager::GetActiveList`,
`ApplyPrioritizedLights`, `CheckPrioritizedLightListSpace`, `LightSorter`, and
`PrecalculatedLights::SortLightPointers`. It uses spatial candidates,
object-size/range/type filters, a prioritized list, `qsort`, and a configured
hardware-light cap. `PrecalculatedLights` stores 32 pointers. Recovered priority
is primarily spatial/distance based, not a confirmed complete physical
contribution estimate; equal `qsort` priorities do not prove deterministic ties.

### Feature comparison

| Feature | CR/BZR current | BZCC/BZ2 evidence | Backport decision |
|---|---|---|---|
| High capacity | 24 already | Modern BZCC 16; legacy storage 32 | Keep 24; no count increase |
| Candidate scope | Per renderable | Object/spatial relevance | Preserve |
| Ordering | Center distance only | Spatial priority/filtering | Improve with actual CR inputs |
| Active loop | Runtime count, upper 24 | Runtime count, upper 16 | Preserve |
| Attenuation | Ogre denominator; hard range admission | Denominator plus radial range fade | Rank with current CR contract; do not silently change shading |
| Spotlights | Position/direction/cone/falloff present | Explicit smooth cone | Already supported |
| Stability | No identity tie/hysteresis | Modern policy unknown | Add bounded deterministic retention |
| Sun/local shadows | Sun first/PSSM, locals unshadowed | Same conceptual separation | Preserve |

No directly applicable Ken-derived note about light selection, budgets, or
headlights was found in the available OpenShim/CR discussion-derived reports.
Actual BZR, Ogre, BZ2, and BZCC artifacts remain the evidence base.

## 4. Implemented relevance and stability policy

For each local light and object bounding sphere:

```text
surfaceDistance = max(length(lightPosition - objectCenter) - objectRadius, 0)
intensity = max(luminance(diffuse), luminance(specular)) * max(powerScale, 0)
distanceTerm = saturate(1 / max(c + l*d + q*d^2, epsilon))
spotTerm = 1 for point lights
spotTerm = pow(saturate((cone - outerCos) /
                       max(innerCos - outerCos, epsilon)), falloff)
influence = intensity * distanceTerm * spotTerm
```

Ogre's existing range test remains authoritative. This is intentionally cheap:
it approximates the direct contribution from values CR already consumes without
trying to reproduce per-pixel normal/BRDF response on the CPU.

Directional lights remain first in producer order. Locals sort by effective
influence, raw influence, stable 64-bit FNV-1a name ID, then original order only
for an unexpected duplicate identity. A previously selected light receives a
five-percent effective-influence bonus. A challenger therefore replaces a
cutoff incumbent only when meaningfully stronger, while removed/expired lights
leave immediately because history can select only current candidates.

History is keyed per destination Ogre light-list, bounded to 4,096 entries, and
oldest-entry evicted. It resets after a suspicious object-center/radius jump to
limit pointer-reuse contamination.

## 5. Implementation, isolation, and applicability

### OpenShim ownership

- `include/enhanced_light_selection.h`
- `src/engine/enhanced_light_selection.cpp`
- `include/ogre_enhanced_light_selection.h`
- `src/patches/ogre_enhanced_light_selection.cpp`
- installation from `RetryDeferredRuntimeHooks` in `src/patches/bzr_hooks.cpp`

The detour calls Ogre `_populateLightList` first, preserving queries, masks,
range tests, and normal caching. It may then reorder the completed vector. It
does not truncate it. The list's hash-dirty flag is set after reordering.

The hook installs only when DX11's render-system module is present, the feature
or diagnostics request it, and exact released Ogre identity/signature anchors
match. Runtime mutation additionally requires a scheme beginning `en-`. Classic
and stock schemes return untouched; DX9 never installs the hook. Invalid pointers,
missing exports, or unexpected bytes preserve the completed stock list.

### GOG/Steam

| Item | GOG | Steam |
|---|---|---|
| BZR executable SHA-256 | `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` | `D298782FC9A13EDB0665DB934110440C45461031DB5F7FE1A76C8784B61CC90D` |
| Relevant code module | `OgreMain.dll` | `OgreMain.dll` |
| Ogre SHA-256 | `E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45` | same, byte-identical |
| PE timestamp/image size | `0x5866BF6A` / `0x00A65000` | same |
| Separate hook/signature | no | no |

The hook verifies the `_populateLightList` prologue, released `HashedVector`
layout writes, and `_calcTempSquareDist` type-dispatch bytes. Unknown builds fail
closed. No storefront-specific executable patch is attempted.

### Campaign Reimagined ownership

No functional CR file changed. Existing materials, constant bindings, and HLSL
already carry the necessary 24-light High path and true spotlight inputs. CR
only documents the paired experiment.

### Headlight result — CONFIRMED

BZR headlights already use genuine Ogre spotlight semantics. Position,
direction, range, attenuation, inner/outer cone, and falloff are created and
updated by BZR; CR's Enhanced SM4 path receives and evaluates them with a smooth
cone. No spotlight rewrite or new headlight shadowing was justified.

## 6. Configuration and diagnostics

```ini
[DX11Enhanced]
EnhancedLightSelectionV2 = 1

[Diagnostics]
EnhancedLightSelectionTrace = 0
```

V2 off plus trace off means the hook is not installed: the A/B baseline is exact
stock distance ordering. Trace can run in observer mode without mutation.
Configuration is read at install time, so restart after changing it.

`[LIGHTSEL]` output is capped at 64 summaries per process, normally sampled
every 120 populated lists and additionally when oversubscribed or materially
churning. It reports candidates, selected budget, cutoff, replacements,
stock/V2 set difference, running max/average, scheme/mode, and up to four ranked
lights. It does not log every object every frame indefinitely.

## 7. Automated validation and cost

### Native selector tests — PASS

Tests cover scheme isolation, under-budget preservation, contribution ranking,
spot-cone rejection, finite zero-denominator handling, cutoff retention, prompt
major replacement, immediate light removal, deterministic ordering under
reversed container order, and a moving 30-local-light combat simulation.

The simulation compares stock distance ordering at both an illustrative 8-slot
cutoff and the actual High 24-slot cutoff against V2. Its purpose is to measure
unnecessary churn, not to assert a real combat scene never changes selection.

```text
stock8=675 replacements; stock24=546; enhanced24=0; frames=180
```

Separate cases prove that a materially stronger arrival replaces an incumbent
promptly and that an expired light is removed immediately.

### CPU microbenchmark — PASS

Release build, 20,000 selections/case on the development workstation:

| Candidates | Budget | Approximate time/selection |
|---:|---:|---:|
| 8 | 8 | 0.86 microseconds |
| 16 | 16 | 1.61 microseconds |
| 32 | 24 | 3.01 microseconds |
| 64 | 24 | 5.23 microseconds |
| 128 | 24 | 9.80 microseconds |

The implementation uses a deterministic stable sort. These costs are small for
representative counts but are not a substitute for in-game CPU/GPU profiling.

### HLSL/DXBC — PASS, unchanged

All 208 CR DX11 SM4 permutations compile. No shader instruction, sample,
constant-buffer, or loop change was introduced. DX9 files were not touched.

### Non-interactive runtime — PASS for hook/integration, not visual quality

The built shim was temporarily deployed to the GOG install and BZR was launched
hidden with `misn03.bzn`; no mouse, keyboard, or scripted UI was used. Logs
confirmed VO completion, first frame, and game simulation initialization. The
hook installed, identified `en-high-noshadow`, and emitted bounded records with
up to nine candidates in the quiet mission. V2 preserved all nine because the
scene was under budget. The original game `winmm.dll` was restored byte-for-byte
after the probe (SHA-256
`4258C2418E99EFA053C31005CDBC0E11ECC13DB1D64EBC01781B1056DA976DF3`).

This proves ABI integration, scheme gating, diagnostics, and >8 High candidates.
It does not validate appearance, high-combat churn, or frame-time impact.

## 8. Before/after values

| Setting | Stock | Experiment |
|---|---:|---:|
| Enhanced High budget | 24 | 24 |
| Enhanced Medium budget | 8 | 8 |
| Enhanced Low/Lowest budget | 1 | 1 |
| Local ordering | squared center distance | estimated contribution + deterministic ID |
| Cutoff retention | 0% | 5% |
| Directional order | producer order | producer order |
| CR shader/material constants | existing | unchanged |
| DX11 Classic / DX9 | stock | unchanged |

A 32-light increase is not recommended now. The evidence supports improving the
existing 24 slots first; visual benefit and cost must be measured before raising
the established shader layout.

## 9. Exact later visual acceptance

1. Launch BZR in DX11 Enhanced High and enable bounded `[LIGHTSEL]` tracing.
2. Load a repeatable 5-friendly-versus-5-enemy tank battle with headlights,
   continuous cannon/machine-gun fire, projectiles, and repeated explosions.
3. Use a stationary view first. Confirm at least one observed renderable exceeds
   24 candidates; an >8 scene alone does not saturate Enhanced High.
4. Record a short fixed save/view run with V2 on: candidate maximum, churn,
   headlight/projectile/explosion popping, nearby-light loss, FPS, and frame time.
5. Set V2 off, restart, repeat from the same save/view and duration.
6. Repeat while moving through the battle.
7. Check strong transient replacement, expired-light removal, rear headlight
   rejection, and absence of stale illumination.
8. Briefly verify DX11 Classic and DX9 remain visually equivalent to baseline.

Acceptance requires less arbitrary popping/churn without stale lights or a
material frame-time regression. Tune retention only after this A/B.

## 10. Known limitations and status

- The reported visual symptom is not yet reproduced interactively; visual cause
  attribution remains **HIGH confidence**, not confirmed.
- The quiet unattended mission did not exceed 24 candidates, so runtime cutoff
  behavior is validated by native simulation rather than a live combat draw.
- Modern BZCC's exact CPU ordering/hysteresis remains unavailable; no unsupported
  claim was copied into the implementation.
- The metric estimates object-level relevance and cannot know each pixel normal,
  occlusion, or BRDF response. This is intentional.
- V2 configuration requires restart because the detour installation is static.
- No local-light shadows or transient lifetime fades are added.

| Component | Static audit | Automated validation | Runtime non-interactive | Visual validation |
|---|---|---|---|---|
| Actual budget/path | PASS | shader/DXBC PASS | >8 High candidates CONFIRMED | PENDING |
| Contribution ranking | PASS | native tests PASS | hook exercised | PENDING |
| Determinism/hysteresis | PASS | churn/replacement/removal PASS | diagnostics exercised | PENDING |
| Count increase | rejected: existing High is 24 | not applicable | not applicable | not applicable |
| True spotlights | already present | cone tests PASS | spot candidates observed | PENDING |
| Classic/DX9 isolation | PASS | scheme guards/build PASS | DX11-only install CONFIRMED | PENDING |

The architecture and implementation are ready for human visual/performance
tuning; the experiment is not yet visually accepted or release-complete.
