# Live combat scaling investigation — GOG 2.2.301

Date: 2026-08-22  
Branch: `agent/live-combat-scaling` (based on PR #41 head `2c984923`)  
Scope: stock GOG Battlezone 98 Redux 2.2.301, DX9 and DX11

## Outcome

The investigation found two different live-combat costs.

1. Ordinary visible-unit work scales approximately linearly: each nearby animated vehicle adds render-queue visits, submissions, animation evaluation, and software-skinned vertices. This is real work, not an O(n²) simulation defect.
2. Some animated meshes, demonstrated by `svfigh`, had an additional DX11-only pathology. Their position/normal source buffers were GPU-only, so every software-skinning call performed a synchronous GPU staging readback. `avtank` used CPU-shadowed source buffers and did not exhibit this cost.

OpenShim now detects an unshadowed position/normal source at the validated `Mesh::softwareVertexBlend` boundary, copies its exact interleaved contents once, and replaces it with a normal Ogre CPU-shadowed buffer. It preserves the source layout, usage, vertex count, rendering, and animation behavior. The policy is DX11-only, gated to the exact GOG 2.2.301 executable/Ogre identities, validates the entry prologue, retries deferred thread-safe installation, fails back to stock behavior on any repair failure, and has this opt-out:

```text
OPENSHIM_DISABLE_DX11_SKIN_SOURCE_SHADOW_FIX=1
```

The clean profiler-disabled 20-fighter A/B improved from 7.405 ms/frame (135 FPS) to 3.575 ms/frame (280 FPS), saving 3.83 ms/frame. A full-AI 20-fighter combat A/B improved from 10.064 to 5.368 ms/frame, saving 4.70 ms/frame, although normal damage/destruction makes that comparison noisier than the no-destruction test.

This does not eliminate the larger weapon/effect submission burden seen with continuously firing tanks. At 80 continuously firing `avtank` units, the measured scene still reaches 19.61 ms/frame. That remaining workload is mainly broad weapon/effect/render submission amplification, not animation or `DynamicGeometry` CPU time.

## Reproduction package

The Instant Action mission is in `reverse_engineering/test_missions/live_combat_scaling` and is deployed by the harness as `addon/lcbench`.

It follows the stock IA layout:

- `lcbench.ini` exposes the map under Instant Action.
- `lcbench.bzn` uses `TerrainName=lcbench`, `msn_filename=lcbench.bzn`, and contains the named `LuaMission` object.
- `lcbench.trn`, `.hg2`, `.lgt`, `.mat`, terrain texture, and material names match the terrain name.
- `lcbench.lua` is Lua 5.1-compatible and supports `quiet`, `idle`, `movement`, `firing`, `ai_idle`, and `combat` phases.
- Selectable units are `svtank`, `avtank`, and `svfigh`. `svtank` remains useful only as a non-skinned control; `avtank` and `svfigh` exercise moving/skinned parts.

Direct launch was validated with:

```text
battlezone98redux.exe lcbench.bzn
```

The harness `reverse_engineering/run_live_combat_benchmark.ps1` deploys the addon, switches/restores DX9 or DX11 and VSync, writes the requested mission configuration, launches that exact mission argument, aligns Lua phase markers with profiler output, takes timestamped snapshots, and can run with the internal profiler disabled plus AMD PresentMon. `reverse_engineering/analyze_live_combat_benchmark.ps1` emits both profiler and PresentMon summaries.

## Baseline phase scaling

These are 4K DX11, VSync-off, five-second profiler windows using `avtank` at 50 m. The population excludes the player.

| Phase | Units | FPS | Mean ms | p95 ms | Animation ms/f | Skin ms/f | Ogre submits/f |
|---|---:|---:|---:|---:|---:|---:|---:|
| quiet | 0 | 386.4 | 2.59 | 3.00 | 0.09 | 0.08 | 91 |
| idle | 10 | 322.0 | 3.10 | 3.60 | 0.37 | 0.34 | 241 |
| idle | 20 | 271.2 | 3.69 | 4.25 | 0.60 | 0.54 | 392 |
| idle | 40 | 201.2 | 4.99 | 5.85 | 1.23 | 1.08 | 697 |
| idle | 80 | 123.0 | 8.27 | 10.55 | 2.23 | 1.87 | 1,296 |
| movement | 10 | 343.4 | 2.93 | 3.60 | 0.37 | 0.34 | 266 |
| movement | 20 | 279.0 | 3.59 | 4.45 | 0.61 | 0.54 | 408 |
| movement | 40 | 194.4 | 5.16 | 6.00 | 1.04 | 0.91 | 791 |
| movement | 80 | 108.6 | 9.20 | 10.15 | 2.12 | 1.77 | 1,408 |
| firing | 10 | 293.3 | 3.41 | 4.00 | 0.39 | 0.36 | 310 |
| firing | 20 | 122.6 | 8.21 | 10.70 | 0.79 | 0.67 | 818 |
| firing | 40 | 84.4 | 11.94 | 13.75 | 1.08 | 0.89 | 1,406 |
| firing | 80 | 51.0 | 19.61 | 23.10 | 2.10 | 1.72 | 2,551 |
| combat | 10 | 279.2 | 3.59 | 4.25 | 0.39 | 0.35 | 419 |
| combat | 20 | 215.0 | 4.68 | 5.35 | 0.60 | 0.53 | 635 |
| combat | 40 | 135.1 | 7.46 | 8.35 | 1.11 | 0.96 | 1,040 |
| combat | 80 | 83.9 | 11.97 | 13.00 | 1.91 | 1.59 | 1,711 |

Idle and scripted movement are close. Native allied AI with no enemy was also close to idle (20 units: 3.63 ms; 40: 4.69 ms), so autonomous AI alone was not the dominant cost. The largest transition is continuous firing: projectiles, muzzle/engine effects, smoke, audio, and associated render work increase submissions much faster than animation time.

The measured counters are broadly O(n). No O(n²) animation, skinning, render-queue, `DynamicGeometry`, or AI-idle counter was found. The firing curve is phase/effect-lifetime sensitive, but the observed work does not show a clear quadratic counter.

## Animation, shadow passes, and duplicate work

For 40 nearby `avtank` units, the profiler measured about 205 animation entries/frame. Camera attribution identified `PlayerCam` plus three nested shadow texture cameras (`Ogre/ShadowTexture0Cam`, `1Cam`, and `2Cam`). The representative pass split was:

| Counter | Main/non-shadow | Nested shadow |
|---|---:|---:|
| render-queue calls/f | 141.9 | 122.9 |
| animation entries/f | 82.0 | 122.9 |
| software blends/f | 3.0 | 122.9 |

The repeated Entity animation entries are not repeated skeleton computation. Ogre's dirty-state cache makes the later traversal entries return cheaply. The actual software blends occur once for the current frame, during the first shadow preparation, and are reused by subsequent main/shadow rendering. Removing the repeated entries would therefore be unsafe and would save little; no duplicate-skeleton optimization was implemented.

Normal vehicle shadows remain enabled. The fix changes only where immutable source vertex bytes are read from; it does not remove a camera, shadow pass, Entity visit, or draw.

## Visibility and distance/LOD

At 40 `avtank` units, facing toward versus directly away produced essentially the same near-field animation and skinning workload (4.77 versus 4.85 ms/frame at 50 m). This map/formation does not prove fine-grained occlusion behavior, but it does show that simply turning away did not eliminate the nearby render-driven workload.

Distance produced a clear LOD cutoff between 100 and 250 m:

| Distance | Facing mean ms | Skin calls/f | Skin ms/f | Ogre submits/f |
|---:|---:|---:|---:|---:|
| 50 m | 4.77 | 125.9 | 1.04 | 697 |
| 100 m | 4.76 | 126.2 | 1.04 | 759 |
| 250 m | 2.81 | 6.0 | 0.07 | 691 |
| 500 m | 2.74 | 6.0 | 0.07 | 691 |
| 1000 m | 2.78 | 6.0 | 0.08 | 691 |

The spawned tanks stop being software-skinned at the distant LOD; only the player sources remain. Submission/queue counts remain comparatively high, so distant objects are geometrically cheaper without disappearing from all traversal work. No animation-distance policy was changed because the expensive part already falls away and a more aggressive cutoff would be a fidelity change.

## DX11 skin-source defect and correction

Runtime layout attribution showed the crucial difference:

```text
svfigh: pos=24 norm=24 weight=8 index=8 weights=1 posShadow=no  weightShadow=yes
avtank: pos=24 norm=24 weight=8 index=8 weights=1 posShadow=yes weightShadow=yes
```

The vertex counts and skinning fast-path layout were comparable, so the approximately eightfold CPU difference was not bone math. Ogre's D3D11 read lock for a static non-shadowed buffer creates a staging resource, copies the GPU resource, maps it synchronously, and releases it. That happened for each fighter source, each visible Entity, each frame.

The correction repaired three shared fighter sources once (155,304 bytes total). All Entity instances then reused those source buffers. Profiler attribution changed from roughly 4.5–4.7 ms/frame of software skinning for 20 fighters to about 0.48 ms/frame while blending the same approximately 144,000 vertices/frame.

### Individual optimization A/B

Profiler disabled, PresentMon, DX11, 20 idle `svfigh`, six-second windows:

| Policy | FPS | Mean ms | p95 ms | p99 ms | GPU active ms |
|---|---:|---:|---:|---:|---:|
| opt-out / stock | 135.0 | 7.405 | 13.444 | 19.413 | 5.036 |
| enabled | 279.7 | 3.575 | 3.973 | 4.262 | 3.492 |

Result: -3.830 ms/frame (-51.7%), +107% FPS. The maximum-frame values contain launch/driver outliers (138.9 ms in one combat capture and 34.2 ms in the idle fixed capture), so p95/p99 are more representative.

### Scaling after correction

Internal-profiler DX11 results:

| Workload | Before mean ms | After mean ms | Before skin ms | After skin ms |
|---|---:|---:|---:|---:|
| 20 fighter idle | 6.65 | 3.57 | 4.53 | 0.48 |
| 40 fighter idle | 10.22 | 4.60 | 7.11 | 0.93 |
| 20 fighter firing/no destruction | 8.46 | 4.98 | 4.05 | 0.49 |

The corrected DX11 20-fighter skin time (0.48 ms/frame) now matches DX9 (0.51 ms/frame). DX9 never enables the policy. `avtank` already has shadowed sources and performs zero repairs.

### Full-AI combat A/B

Profiler disabled, PresentMon, 20 `svfigh`, normal hostile AI:

| Policy | FPS | Mean ms | p95 ms | p99 ms | GPU active ms |
|---|---:|---:|---:|---:|---:|
| opt-out / stock | 99.4 | 10.064 | 16.991 | 27.336 | 5.794 |
| enabled | 186.3 | 5.368 | 8.740 | 13.664 | 3.711 |

Result: -4.696 ms/frame (-46.7%), +87.5% FPS. This is the best direct answer for a modest battle built from affected moving/skinned units, but it is naturally noisier because units fire, collide, take damage, and can be destroyed.

## Renderer comparison

Baseline `avtank` results show DX9 is slower in quiet/idle rendering but converges with DX11 under heavy firing:

| Workload | DX11 mean ms | DX9 mean ms |
|---|---:|---:|
| quiet | 2.59 | 3.66 |
| idle 20 | 3.69 | 4.53 |
| idle 40 | 4.99 | 5.30 |
| firing 20 | 8.21 | 8.27 |
| firing 40 | 11.94 | 12.44 |
| combat 20 | 4.68 | 6.15 |
| combat 40 | 7.46 | 8.03 |

The ordinary weapon/effect burden is therefore mostly shared engine/Ogre work. The fighter readback pathology is DX11-specific.

## Weapon effects and PR #41 batching

Continuous `avtank` firing at 20 units increases Ogre submissions from 392/frame idle to 818/frame and indexed DX11 draws from 357 to 681. At 80 units it reaches 2,551 submissions and 1,307 indexed draws/frame. Animation is only 2.10 ms and skinning 1.72 ms of the 19.61 ms frame; attributed `DynamicGeometry` preparation is approximately 0.28 ms/frame.

The inherited PR #41 compatible-alpha batching correction was A/B tested with the profiler disabled for 20 firing tanks:

- enabled: 7.248 ms mean, 8.270 ms p95, 8.804 ms p99;
- disabled: 7.333 ms mean, 8.543 ms p95, 9.560 ms p99.

It helps ordinary firing by about 1.2% mean, 3.2% p95, and 7.9% p99 on this capture, but it is not the main explanation for live-combat scaling. No additional alpha reordering was attempted because preserving blend order is required.

## Regression and safety validation

Passed:

- Release Win32 build.
- Ogre profiler algorithm tests.
- INI/config writer tests.
- Lua 5.1 syntax check.
- `git diff --check` (only configured CRLF conversion notices).
- Exact `battlezone98redux.exe lcbench.bzn` launch.
- DX11 profiler enabled and disabled.
- DX11 optimization enabled and explicit opt-out.
- DX9, where the policy stays disabled.
- Idle, movement, firing-without-destruction, and full AI combat.
- Runtime source repair: 3 repairs, 155,304 bytes, 0 failures; subsequent intervals do no repair work.
- Log scan: no shader/material failures, renderer errors, exceptions, or access violations in final validation sessions.
- Visual captures: fighter geometry/deformation remained intact; units changed position and orientation; thruster effects, shadows, terrain, HUD, and radar rendered normally across frames.

One pre-mission process exited during a profiler-enabled matrix before Lua loaded. This matches the rare startup observer-install race seen during the investigation and was not tied to a unit or repaired buffer. All subsequent final runs completed, but hardening the profiler's multi-detour startup remains worthwhile. The default runtime policy installs only the required blend boundary, not the full diagnostic observer set.

Not exhaustively validated in this synthetic pass: every stock vehicle mesh, long campaign cinematics, multiplayer, save/load during a repair, every building shadow, and Steam binaries. Steam remains unsupported/unclaimed. Unknown executable/Ogre identities are not patched.

## Remaining bottlenecks

1. Weapon/projectile/effect submission amplification is now the largest reproducible general-combat cost. The next useful step is per-weapon/effect isolation with renderable/material contributor attribution, not another animation change.
2. Nearby live units still produce many legitimate queue visits and submissions. Distant LOD removes skinning but not most queue/submission activity; finer visibility attribution may reveal a safe opportunity.
3. DX9 has a higher quiet/idle baseline than corrected DX11.
4. The full diagnostic profiler has a rare startup hook-install failure that should be isolated independently from gameplay performance.
5. Hardware skinning remains a larger architectural experiment and is not justified while the corrected CPU skin path is sub-millisecond for 20 fighters.

## Answer to the primary question

The reported approximately 20 ms/frame battle penalty is not one universal defect. In the deterministic 80-tank continuous-firing reproduction, most of it is weapon/effect-driven render and submission work; animation and skinning together account for under 4 ms. In a modest battle made from affected fighter meshes, however, DX11 was wasting approximately 4–6 ms/frame on repeated GPU readback of immutable software-skin source data. OpenShim safely eliminates that redundant portion without changing animation, AI, shadows, effects, or mesh fidelity.

Raw timestamped captures are under the ignored `reverse_engineering/snapshots/live_combat` tree. Principal sessions are `20260822_004329` (baseline phase sweep), `20260822_005045` (camera/distance/passes), `20260822_010922` (DX9), `20260822_011516` (fighter defect confirmation), `20260822_013635`/`20260822_013714` (idle profiler-disabled A/B), `20260822_013801` and `20260822_014027` (post-fix scaling and renderer validation), and `20260822_014520`/`20260822_014544` (full combat A/B).

Investigation commits:

- `6b38d016` — deterministic Instant Action mission, runner, and analyzer;
- `9d0fb5ca` — pass/source diagnostics and the DX11 skin-source correction;
- `adf484e0` — technical report and roadmap status.

The branch is `agent/live-combat-scaling`. It is intentionally separate from
PR #41 and does not merge that PR. The branch is pushed to `origin`; no pull
request was opened. The manually dispatched GitHub `Build Win32` workflow
passed on `adf484e0`, including the network baseline check, pinned Ogre setup,
profiler/INI tests, FXAA validation, Release Win32 build, output verification,
and artifact upload:

https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/actions/runs/32558118526
