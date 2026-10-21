# DX11 frame-time breakdown, craft-heavy scenes (2026-10-20)

Goal: find where a Battlezone 98 Redux DX11 frame goes in craft-heavy scenes, so
the next FPS lever is chosen from data. Measurement only; nothing here changes
shipping behaviour.

## Bottom line

- The game is **CPU-bound on the main thread** in every scene measured. GPU
  active time is 0.6-3.2 ms against 2.3-8.3 ms frames. The main thread is
  busy for 97% of samples, and Present/GPU wait is about 1-3% of the frame.
- **Software skinning is the largest single cost.** With `GpuSkinning = 0`,
  `Entity::updateAnimation` takes 26% of the frame at 20 craft and 37% at 80.
  Most of it is charged to the shadow pass that first enqueues each entity.
  Turning GPU skinning on takes idle-80 from 8.27 to 4.81 ms (+72% fps).
- **Once skinning is on, the frame is spread across many buckets.** Shadows
  cost 0.5-1.3 ms. The pairwise collision loop costs 0.7 ms at 80 craft and
  grows roughly with n². The glow re-submit pass costs 0.3-0.9 ms. OpenShim's
  own GPU-skin per-frame scan costs 0.1-0.4 ms. No single lever beyond GPU
  skinning is worth more than about 20%.
- **The same-frame repeat counters are not real waste.** Duplicate animation
  updates cost at most 0.06 ms a frame, and duplicate render-queue entries at
  most 0.17 ms.

## Method

- **Scene:** `run_live_combat_benchmark.ps1` (lcbench) avtank scenarios.
  - `idle_020_50_facing` and `idle_080_50_facing`: 20 or 80 idle craft, facing
    the camera.
  - `combat_040_50_facing`: 40 craft fighting.
  - Settings: `BZR_FORCE_WINDOWED=1`, GOG build, DX11, flip-model
    "Composed: Flip".
  - Shadows: PSSM 2048 (`BZPLYR.DEF` byte 0x2D = 3), shadow far 256.
  - `[Fixes] RestoreCraftBounds = 1` (the default).
  - Measured window: 10 s after a 12 s settle.
- **Arms** (each run once per `GpuSkinning` 0/1):
  1. **clean** (`-PerfTelemetry` + PresentMon): frame time from `frames.bin`,
     and GPU active time from PresentMon. PresentMon ran unelevated and drops
     about 20% of presents, so its between-present times are not used.
  2. **profile**: the `ProfileOgreAnimation` probe plus two narrow additions
     from this workstream, listed below. Probe overhead inflates frames by
     7-15%, so read these numbers as relative per-pass shares and draw counts.
  3. **sample**: the `-SampleCpu` 1 kHz main-thread sampler. Each sample's
     symbolized stack goes into one exclusive bucket. Shares are converted to
     ms with the clean-arm frame time.
  4. **profile, shadows off** (byte 0x2D = 0xFF): the control arm for the
     shadow cost.
- **Probe additions** (`src/patches/ogre_animation_profiler/`, gated by the
  existing `ProfileOgreAnimation` switch, off by default):
  - `[OgreProfile][PassTime]`: per-viewport `_renderScene` time, inclusive and
    exclusive of nested passes. It also gives draw calls, render-queue entries
    and render-queue CPU per pass.
  - `[OgreProfile][Repeats]`: duplicate animation updates and render-queue
    entries split by the pass that caused them (main/shadow/external), with
    their CPU cost.
- **Caveat:** frame-pointer stack walks truncate in most samples, so deep
  inclusive shares are lower bounds. The exclusive buckets below are assigned
  from the outermost recognizable frame (sim tick, `renderOneFrame`, and so
  on). Those frames are present in almost every sample, so the top-level split
  is reliable. The split inside Ogre is good to about ±3 points.

## Clean frame times

| Scene | GpuSkinning 0 | GpuSkinning 1 | GPU active (0 / 1) |
|---|---:|---:|---:|
| idle 20 | 3.29 ms (304 fps) | 2.33 ms (430 fps) | 1.15 / 0.57 ms |
| idle 80 | 8.27 ms (121 fps) | 4.81 ms (208 fps) | 3.24 / 0.72 ms |
| combat 40 | 7.74 ms (129 fps) | 5.97 ms (167 fps) | 1.83 / 0.65 ms |

## Where the frame goes (ms per frame, sampler share × clean frame)

Each sample is counted once, in the first bucket that matches, top to bottom.

### GpuSkinning = 1

| Bucket | idle 20 | idle 80 | combat 40 |
|---|---:|---:|---:|
| **Simulation total** | **0.94** | **1.85** | **2.51** |
| · world tick: objects, AI, physics (`0x6175C0`/`0x6176A0`) | 0.61 | 0.65 | 1.16 |
| · pairwise object loop / collision (`0x442E70`) | 0.15 | 0.68 | 0.11 |
| · object-class step (`0x618060`) | 0.11 | 0.33 | 0.52 |
| · weapons + audio | 0.05 | 0.13 | 0.23 |
| · other frame-loop work (net, input, Lua) | 0.03 | 0.05 | 0.48 |
| **Render total** | **1.38** | **2.95** | **3.46** |
| · game render prep outside Ogre (camera, effects, lists) | 0.05 | 0.08 | 0.32 |
| · Ogre scene-graph update | 0.03 | 0.04 | 0.04 |
| · culling + queueing (main, glow, UI) | 0.19 | 0.31 | 0.53 |
| · draw submission (main, glow, UI) | 0.53 | 1.19 | 1.49 |
| · shadow cascades (all 3, cull + draw) | 0.35 | 0.83 | 0.73 |
| · frame listeners (OpenShim GPU-skin scan) | 0.12 | 0.40 | 0.21 |
| · compositor / other Ogre | 0.04 | 0.05 | 0.06 |
| · Present / GPU wait | 0.06 | 0.06 | 0.07 |
| Skeletal animation (`Entity::updateAnimation`, across buckets) | 0.04 | 0.05 | 0.04 |

### GpuSkinning = 0

| Bucket | idle 20 | idle 80 | combat 40 |
|---|---:|---:|---:|
| **Simulation total** | **1.02** | **2.11** | **2.76** |
| · world tick | 0.63 | 0.65 | 1.21 |
| · pairwise object loop / collision | 0.16 | 0.77 | 0.13 |
| · object-class step | 0.15 | 0.45 | 0.59 |
| · weapons + audio, other loop | 0.08 | 0.24 | 0.82 |
| **Render total** | **2.27** | **6.16** | **4.98** |
| · culling + queueing (main, glow, UI) | 0.25 | 0.40 | 0.55 |
| · draw submission (main, glow, UI) | 0.55 | 1.26 | 1.58 |
| · shadow cascades, **including the CPU skinning they trigger** | 1.20 | 4.16 | 2.30 |
| · render prep, scene graph, present, other | 0.27 | 0.34 | 0.55 |
| Software skinning + animation (`Entity::updateAnimation`, across buckets) | 0.86 | 3.10 | 1.55 |

### Buckets the brief asked for that are small

- **Particles and effects:** no `Ogre::ParticleSystem` samples in any scene.
  BZ effects are game-side sprites. In combat they show up as the rise in game
  render prep (0.05 → 0.32 ms) and in draw submission. Confidence: low; there
  is no dedicated probe.
- **UI / overlay pass:** 0.07-0.18 ms (14-17 draws). Post-process quads:
  0.04 ms (3 draws).
- **Present / GPU wait:** under 0.1 ms. The GPU is idle most of the frame.

## Per-pass detail (profile arm, GpuSkinning = 1, shadows on)

Times are inclusive `_renderScene` ms per frame with the probe running.
Draws are D3D11 draw calls per frame for that pass.

| Pass | idle 20 | idle 80 | combat 40 |
|---|---|---|---|
| Main camera | 0.61 ms excl. / 108 draws | 1.22 ms / 295 draws | 1.56 ms / 281 draws |
| Cascade 0 (near) | 0.08 ms / 3 draws | 0.09 ms / 3 draws | 0.17 ms / 15 draws |
| Cascade 1 | 0.18 ms / 60 draws | 0.35 ms / 114 draws | 0.34 ms / 101 draws |
| Cascade 2 (far) | 0.06 ms / 13 draws | 0.50 ms / 192 draws | 0.21 ms / 68 draws |
| Glow scheme pass | 0.30 ms / 105 draws | 0.70 ms / 292 draws | 0.86 ms / 278 draws |
| UI / overlay | 0.07 ms / 14 draws | 0.08 ms / 14 draws | 0.15 ms / 17 draws |
| Post quads (×3 renders) | 0.04 ms / 3 draws | 0.04 ms / 3 draws | 0.04 ms / 3 draws |
| **Total draws / frame** | **307** | **912** | **762** |

- With `RestoreCraftBounds = 1`, shadow casters are culled per cascade: the near
  cascade draws 3-15 casters, and the far cascade carries most craft once they
  spread out (192 draws at 80 idle craft).
- With `GpuSkinning = 0`, draw counts are the same. Cascade 1/2 time rises to
  1.0-2.4 ms because the first pass to enqueue a skinned entity pays its
  software skinning.
- **Shadows-off control** (profile arm, frame mean):

  | Scene | Shadows on | Shadows off | Shadow cost |
  |---|---:|---:|---:|
  | skin 1, idle 20 | 2.60 ms | 2.14 ms | 0.46 ms |
  | skin 1, idle 80 | 5.54 ms | 4.74 ms | 0.80 ms |
  | skin 1, combat 40 | 6.65 ms | 5.39 ms | 1.26 ms |
  | skin 0, idle 20 | 3.52 ms | 2.85 ms | 0.67 ms |
  | skin 0, idle 80 | 9.31 ms | 8.15 ms | 1.16 ms |
  | skin 0, combat 40 | 8.65 ms | 7.93 ms | 0.72 ms |

  With skin 0 the skinning moves into the main pass when shadows are off, so
  the skin-0 delta understates the shadow cost.
- **Glow scheme pass:** it re-runs a second full scene pass that submits about
  as many draws as the main camera. This makes it the largest single render
  pass after main.

## Same-frame repeat counters

The probe classifies each repeated `Entity::updateAnimation` and render-queue
entry within one frame.

- **Duplicate animation updates:** 45 a frame at 20 craft and 181 at 80.
  - Almost all come from the main/glow re-queue; a few come from shadow passes.
  - Each costs 0.3 µs: Ogre's per-frame animation cache short-circuits it,
    with 0 extra blends.
  - Skinning is never duplicated.
  - Total: 0.013-0.058 ms a frame.
- **Duplicate render-queue entries:** 88-224 a frame, costing 0.04-0.17 ms.
- **Verdict:** not material. Removing all of them buys about 1-3%. Earlier
  per-second readings (1,200 anim and 2,300 rq per second) are the same
  counters at high fps. The real cost behind the duplicates is the glow pass
  itself. Confidence: high.

## Ranked levers

The gain is for GpuSkinning = 1 at idle 80 / combat 40, unless noted.

| # | Lever | Est. gain | Confidence |
|---|---|---|---|
| 1 | **GPU skinning on by default** | skin 0 → 1: −3.5 ms at idle 80 (+72% fps), −1.8 ms in combat (+30%), −1.0 ms at idle 20 (+41%) | **High** (measured). Visual parity and mod-craft coverage are outside this doc; see PRs #536/#538. |
| 2 | **Shadow cost: caster limits / far-cascade rate** | Ceiling is all shadow work, 0.8 / 1.3 ms (+17% / +23%). Cascade 2 at half rate saves about 0.25 ms at idle 80 (+5%). A caster cap on cascades 1-2 saves 0.2-0.5 ms. | Medium (shadows-off delta measured; per-technique splits estimated from per-cascade time) |
| 3 | **Pairwise object loop (`0x442E70`): spatial broadphase** | 0.68 ms at idle 80, growing about n² (0.15 ms at 20). It nearly vanishes in combat, where craft spread out. A grid could save about 0.5 ms at 80 (+11%). | Medium on cost, low on achievable savings (the loop's exact role is still to be confirmed) |
| 4 | **OpenShim GPU-skin `ScanFrame` per-frame snapshot** | 0.12 / 0.40 / 0.21 ms (5 / 8 / 3.5%). The snapshot runs every frame through `ZwQueryVirtualMemory`, though conversion only runs every 15 frames. Throttling or caching it recovers most of this: about +8% at idle 80. | High on cost, medium-high on recovery. It is the cheapest change on this list. |
| 5 | **Glow scheme pass: re-submits all of main** | 0.30 / 0.70 / 0.86 ms of CPU. Limiting it to glow-bearing renderables could save 0.4-0.7 ms (+10-13%). | Medium-low (depends on which materials truly need the glow scheme) |
| 6 | **Fixed simulation tick + render interpolation** | See the next section: about +43% at idle 80 and +47% in combat at 60 Hz; little or none for skin 0 at 120 Hz | **Low** (model-based, with large blockers) |
| 7 | **Hardware instancing for craft** | Each craft adds about 3.1 draws to each of main, glow and shadow. Draw submission is about 2 µs a draw. Realistically 0.5-1.0 ms at idle 80 (+10-25%); per-draw parameter updates and culling remain. | Low. Animated instances need bone palettes per instance on top of GPU skinning, so this is a large change. |
| 8 | **Static-prop batching (EXU StaticGeometry)** | The base scene without craft is about 46 draws per pass (extrapolated from 108 → 294 draws for 20 → 80 craft). Ceiling about 0.2 ms (+4%). This bench map has few props; prop-dense maps would gain more. | Low-medium |
| 9 | **Remove duplicate anim updates / rq entries** | 0.05-0.2 ms (1-3%) | High (measured directly) |

## Lever 6 in detail: fixed simulation tick with interpolated rendering

### Split

Simulation = frame-loop work outside `renderOneFrame` and game render prep:
the world tick, collision, object-class step, weapons, audio, net and input.
Render = everything from game render prep through Present.

| GpuSkinning 1 | Sim S (ms/frame) | Render R (ms/frame) | Now |
|---|---:|---:|---:|
| idle 20 | 0.94 | 1.38 | 430 fps |
| idle 80 | 1.85 | 2.95 | 208 fps |
| combat 40 | 2.51 | 3.46 | 167 fps |
| GpuSkinning 0, idle 20 | 1.02 | 2.27 | 304 fps |
| GpuSkinning 0, idle 80 | 2.11 | 6.16 | 121 fps |

### Model

Assume a fixed sim at H Hz with unchanged per-step cost and uncapped
rendering. Then the render rate is F = (1000 − S·H) / R.

| Scene | 60 Hz sim | 120 Hz sim |
|---|---:|---:|
| skin 1 idle 20 | 684 fps (+59%) | 643 fps (+50%) |
| skin 1 idle 80 | 301 fps (+45%) | 264 fps (+27%) |
| skin 1 combat 40 | 245 fps (+47%) | 202 fps (+21%) |
| skin 0 idle 20 | 413 fps (+36%) | 387 fps (+27%) |
| skin 0 idle 80 | 142 fps (+17%) | 121 fps (0%) |

**Confidence: low.**

- The model ignores the interpolation cost: every frame would need to blend and
  write a transform for every object, and those writes happen inside the world
  tick today.
- It assumes sim cost per step is independent of dt.
- It uses lower-bound sampler shares.
- When fps is already at or below the sim rate (skin 0 at 120 Hz) there is no
  gain, only added latency.
- Much of the headline gain is at frame rates above 240 fps, where it matters
  least.

### Feasibility blockers (from the decompile corpus; GOG addresses)

- **Render reads live sim state.** Per-object scene-node writes happen inside
  the sim tick (`0x6176A0` → `0x4D4610` → `0x451F80` → renderer lists
  `0x44E7F0`/`0x44E880`). The camera is set in render prep from object state.
  Interpolation needs a previous/current transform snapshot for every
  renderable, plus the camera, plus effects that sample sim positions.
- **Variable dt everywhere.**
  - SetLoopTimes (`0x822AE0`) computes an integer-ms dt, clamped to 200 ms,
    with no accumulator.
  - The float step (`0x946790`) has a getter (`0x822D60`) with about 65-80
    callers.
  - Physics is explicit Euler (`pos += vel*dt`), so a fixed step changes
    numeric behaviour.
- **Input is sampled in the sim step.** Mouse aim is bucketed at 1/60 s in
  `NextInputs` (`0x623B20`). Decoupling either keeps input on the sim tick
  (latency up to one tick) or needs a separate render-rate aim path.
- **Multiplayer.**
  - It is not lockstep: it uses a clock offset (`0x946798`/`0x94678C`) plus
    dead reckoning for remote craft (`GameObject::Simulate`, `0x4964D3`), so a
    fixed tick is not ruled out by protocol.
  - Net send cadence appears to follow frame rate (see
    `nav_beacon_contact_netcode_storm_20261001.md`), so its behaviour changes.
  - Every peer must agree, so this would need an MP gate like `PreciseTimestep`
    (PR #525).
- **Lua.** `Update(dt)` and `GetTimeStep` assume one call per rendered frame.
  Mission scripts would see a different call rate.
- **Cheaper partial step:** a fixed step without interpolation, rendering every
  frame at the latest state. It fixes determinism and physics-rate issues, but
  buys no fps.

## Recommended order

1. Ship GPU skinning on by default (lever 1). It is the dominant cost and
   already exists.
2. Throttle or cache the GPU-skin `ScanFrame` snapshot (lever 4). It is small,
   contained and pure OpenShim overhead that grows with craft count.
3. Shadow far-cascade rate / caster cap (lever 2) and a glow-pass narrowing
   study (lever 5). Each is worth 10-20% in heavy scenes.
4. Identify `0x442E70` precisely before planning a broadphase (lever 3).
5. Defer the fixed tick, instancing and StaticGeometry (levers 6-8) until the
   above have landed; re-measure first.

## Reproducing

```powershell
. .\reverse_engineering\BZRHarness.ps1
# under Enter-BZRLaunchLock; set BZPLYR.DEF byte 0x2D (3 = PSSM 2048, 0xFF = off)
$env:BZR_FORCE_WINDOWED = '1'; $env:OPENSHIM_GPU_SKINNING = '1'   # or '0'
$b = '.\reverse_engineering\run_live_combat_benchmark.ps1'
# per scene: -Scenario idle -Count 20|80, or -Scenario combat -Count 40
& $b -UnitOdf avtank -MeasureSeconds 10 -Scenario idle -Count 80                                          # profile arm
& $b -UnitOdf avtank -MeasureSeconds 10 -Scenario idle -Count 80 -ProfilerDisabled -SampleCpu             # sample arm
& $b -UnitOdf avtank -MeasureSeconds 10 -Scenario idle -Count 80 -ProfilerDisabled -ExternalPresentMon -PerfTelemetry  # clean arm
# then analyze_frame_hitches.py <frames.bin> --skip-seconds 12, and analyze_cpu_samples.py with the private functions.csv
```

Concurrency note: another session edited `openshim.ini` (TerrainHd keys) during
this run. The changed keys do not affect these scenes, so the arms remain
comparable.
