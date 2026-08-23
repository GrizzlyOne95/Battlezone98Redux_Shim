# Phase 1: four-team distant-combat render attribution (2026-08-23)

The question this phase had to answer:

> What specifically owns the ~1,475 submissions in a large four-team battle, how
> does that ownership differ from actual DX9/DX11 API draw behavior, and which
> measured category gives us the best next optimization target?

The short answer, and it is not the expected one:

1. **The submissions are owned by vehicle shadow casters (43%), vehicle
   main-view passes (29%) and projectile meshes (21%).**
2. **DX11 and DX9 issue exactly the same number of API draws per Ogre
   submission — 1.00.** The previously reported "988 draws for 1,478
   submissions" on DX11 was an instrumentation defect and is retracted below.
3. **One Ogre submission costs about 0.7-1.0 us of frame time**, measured by
   removing whole categories and re-measuring with the profiler detached. The
   entire submission budget is therefore ~1.3 ms of a 9.2 ms large-battle
   frame. **Submission count is not the large-battle bottleneck.** About 86% of
   that frame is neither Ogre submission nor GPU work.

No optimization is shipped in this phase. Section 11 explains why that is the
conclusion the measurement supports rather than an omission.

---

## 1. Exact test setup

| Item | Value |
|---|---|
| Game | Battlezone 98 Redux, GOG 2.2.301, `battlezone98redux.exe` 5,425,152 bytes |
| Install | `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux` |
| CPU | AMD Ryzen 9 9900X, 12C/24T |
| GPU | NVIDIA GeForce RTX 5080, driver 32.0.16.1088 |
| Resolution | 3840x2160, FSAA 0, VSync forced off by the harness |
| Backends | `Direct3D11 Rendering Subsystem`, `Direct3D9 Rendering Subsystem` |
| Mission | `lcbench.bzn` + `lcbench.lua`, deployed to `addon\lcbench` |
| Scenario | `fourteam`, `fourteam_fire`, `fourteam_ai` |
| Population | 80 spawned craft (`avtank`) + the player = 81 |
| Distance | 400 m baseline; sweep at 100 / 200 / 400 / 800 m |
| Warmup / measure | 5 s / 10 s per run |
| Frame timing | PresentMon v1 metrics, ETW, `--process_id`, started at the mission's own `measure-begin` marker, profiler disabled |
| Attribution | OpenShim Ogre profiler, `OPENSHIM_PROFILE_OGRE_ANIMATION=1` |

### The four-team layout

Two opposing fronts side by side ahead of the player at the configured
distance. Each front is a pair of teams facing each other across a 60 m gap, so
teams 2/3 and 4/5 all fight inside one frustum. Lateral extents are chosen to
keep the whole battle within the frustum, which matters because craft outside
it are culled and a formation that spilled off screen would quietly measure a
smaller battle than it claims. All 81 craft are confirmed submitted every frame
(243.0 shadow submissions per cascade = 81 x 3 submeshes).

Three variants share that one layout, so a capture differs only in what is
driven:

| Scenario | What runs | Why it exists |
|---|---|---|
| `fourteam` | stopped, no firing | very nearly pure render work |
| `fourteam_fire` | deterministic `FireAt` maintenance, population held constant | repeatable battle without deaths |
| `fourteam_ai` | the same engagement started once through the native AI, no per-frame Lua | separates the harness's own scripting cost from the battle's |

### Reproduction

```bash
pwsh ./reverse_engineering/run_fourteam_phase1.ps1
```

```bash
pwsh ./reverse_engineering/run_fourteam_phase1.ps1 -Part repeats -Repeats 3
```

```bash
python reverse_engineering/analyze_fourteam_phase1.py reverse_engineering/snapshots/fourteam_phase1/<session>/render_contributors.csv --detail
```

## 2. Exact branch/head tested

Branch `agent/render-submission-attribution`, off `agent/generic-chunk-batch-rebuild`
at `a1134b66`.

| Commit | Content |
|---|---|
| `fd075e8a` | profiler: per-submission draw attribution, DX11 observer repair, isolation arm |
| `30f94664` | benchmark: four-team scenario, Phase 1 drivers, family classifier |
| `aa852046` | fix: make an isolation arm actually suppress with collection off |

All measurements in this document were taken with the shim built from
`aa852046` unless a section says otherwise. Build: MSVC 14.44.35207, Release,
Win32.

## 3. Baseline four-team results

Profiler-disabled PresentMon, DX11, 80 units, 400 m, 3 repeats of a 10 s
capture each (~1,100-3,000 present samples per capture). `sd` is the standard
deviation of the three per-capture means.

| Scenario | mean ms | sd | p95 ms | p99 ms | fps | GPU active ms | submissions/f |
|---|---:|---:|---:|---:|---:|---:|---:|
| `fourteam` (idle) | 3.444 | 0.077 | 3.83 | 4.39 | 290 | 1.81 | 1,290.8 |
| `fourteam_fire` | 9.229 | 0.091 | 11.41 | 12.17 | 108 | 1.94 | 1,690.3 |
| `fourteam_ai` | 8.664 | 0.105 | 10.96 | 11.58 | 115 | 1.98 | not captured |

Three facts fall straight out of this table.

**The GPU is not the constraint.** GPU-active time is 1.8-2.0 ms against a
3.4-9.2 ms frame, and it barely moves between idle and a full battle even
though 4.6 M triangles are submitted every frame. This is a CPU-bound
workload, consistent with the previous phase's finding.

**Firing costs 5.8 ms and only ~400 of that is submissions.** Going from idle
to firing adds 400 submissions (worth ~0.36 ms at the measured marginal rate,
section 10) and 0.13 ms of GPU. The other ~5.3 ms is game-side work that never
reaches the renderer.

**That 5.3 ms is not the harness.** `fourteam_ai` starts the same engagement
once through the native AI and runs no per-frame Lua at all. It costs 8.66 ms
against `fourteam_fire`'s 9.23 ms, so the harness's 240 Lua calls per frame are
worth ~0.57 ms and the remaining ~4.7 ms is real engine cost.

## 4. DX9 versus DX11

Profiler-attached attribution runs, 80 units, 400 m.

| Backend | Scenario | submissions/f | API draws/f | draws / submission | contributor CPU ms/f |
|---|---|---:|---:|---:|---:|
| DX11 | idle | 1,290.8 | 1,290.3 | **1.000** | 1.730 |
| DX9 | idle | 1,291.4 | 1,291.4 | **1.000** | 1.675 |
| DX11 | firing | 1,690.3 | 1,689.7 | **1.000** | 2.791 |
| DX9 | firing | 1,691.0 | 1,691.0 | **1.000** | 2.596 |

Profiler-disabled PresentMon, single 10 s captures:

| Backend | Scenario | mean ms | p95 | p99 | GPU active ms |
|---|---|---:|---:|---:|---:|
| DX11 | idle | 3.41 | 3.76 | 4.19 | 1.80 |
| DX9 | idle | 3.66 | 4.12 | 4.51 | 2.25 |
| DX11 | firing | 9.01 | 11.17 | 11.70 | 1.92 |
| DX9 | firing | 9.43 | 11.52 | 12.70 | 2.64 |

DX9 is consistently ~5% slower on frame time and 25-38% higher on GPU-active
time at identical submission and draw counts. That gap is a backend/driver
property, not a scene-management difference, and it is small enough that it
does not change any Phase 1 or Phase 2 priority.

## 5. Submission ownership breakdown

DX11, 80 units, four teams, 400 m. Submissions, draws, triangles and CPU are
from the profiler-attached run; the frame-time column is derived from the
measured marginal submission cost in section 10 except where an isolation arm
measured it directly.

### Firing (`fourteam_fire`)

| Family | sub/f | % sub | API draws/f | draws/sub | triangles/f | contributor CPU ms/f |
|---|---:|---:|---:|---:|---:|---:|
| vehicle shadow casters | 729.1 | 43.1% | 728.9 | 1.00 | 2,305,414 | 0.607 |
| vehicle main view | 485.6 | 28.7% | 485.4 | 1.00 | 1,535,312 | 0.996 |
| ordnance / projectile meshes | 357.8 | 21.2% | 357.8 | 1.00 | **2,147** | 0.861 |
| terrain main view | 58.0 | 3.4% | 58.0 | 1.00 | 741,794 | 0.193 |
| effects (`DynamicGeometryBatch`) | 53.0 | 3.1% | 53.0 | 1.00 | 61,922 | 0.091 |
| post-process quads (`Rectangle2D`) | 4.0 | 0.2% | 4.0 | 1.00 | 0 | 0.012 |
| sky | 3.0 | 0.2% | 3.0 | 1.00 | 72 | 0.032 |
| **Total** | **1,690.6** | 100% | **1,690.1** | **1.00** | **4,646,661** | **2.791** |

Nothing is unclassified. Contributor coverage was 100.0% of render-system
submissions in every run, and the logged rank cap was raised from 48 to 160 so
the tail is enumerated rather than truncated.

### Idle (`fourteam`)

| Family | sub/f | % sub | API draws/f | triangles/f | contributor CPU ms/f |
|---|---:|---:|---:|---:|---:|
| vehicle shadow casters | 728.7 | 56.5% | 728.4 | 2,304,006 | 0.595 |
| vehicle main view | 486.0 | 37.7% | 486.0 | 1,536,583 | 0.907 |
| terrain main view | 58.0 | 4.5% | 58.0 | 742,409 | 0.166 |
| effects | 11.0 | 0.9% | 11.0 | 6,847 | 0.023 |
| post-process quads | 4.0 | 0.3% | 4.0 | 0 | 0.011 |
| sky | 3.0 | 0.2% | 3.0 | 72 | 0.027 |
| **Total** | **1,290.7** | 100% | **1,290.4** | **4,589,917** | **1.730** |

### Inside the vehicle families

`avtank.mesh` is one skeletal mesh with three submeshes and **no mesh LOD chunk
at all**:

| Submesh | Material | Triangles | Share of the mesh |
|---|---|---:|---:|
| 1 | `avtank00` (hull) | 9,225 | 97.3% |
| 2 | `avheadlight00` | 192 | 2.0% |
| 3 | `avtank01` (cockpit) | 68 | 0.7% |

Per craft that is 3 shadow submissions per cascade (x3 cascades) plus 3
main-view submissions per active scheme (`high-pssm` and `glow`) = 15
submissions per craft per frame. Measured per-group detail, idle at 400 m:

| Group | sub/f | CPU ms/f | us per submission |
|---|---:|---:|---:|
| shadow cascade 0 | 242.9 | 0.213 | 0.88 |
| shadow cascade 1 | 242.9 | 0.193 | 0.79 |
| shadow cascade 2 | 242.9 | 0.189 | 0.78 |
| `avheadlight00` `high-pssm` lod2 | 80.0 | 0.294 | **3.68** |
| `avtank01` `high-pssm` lod0 | 81.0 | 0.244 | **3.01** |
| `avtank00` `high-pssm` lod2 | 80.0 | 0.106 | 1.33 |
| `avheadlight00` `glow` lod0 | 81.0 | 0.084 | 1.04 |
| `avtank00` `glow` lod0 | 81.0 | 0.080 | 0.99 |
| `avtank01` `glow` lod0 | 81.0 | 0.079 | 0.98 |

**Submesh count, not triangle count, drives vehicle main-view CPU.** The two
smallest submeshes — 192 and 68 triangles — cost 2.8x and 2.3x more CPU per
submission than the 9,225-triangle hull, and together they own 0.538 ms of the
1.730 ms of contributor CPU (31%) while carrying 0.7% of the geometry.

### The projectiles

`gatst00.mesh` is a **6-triangle** single-submesh projectile with a skeleton
link, material `ordnanceRed : BZBase`. Every round in flight submits twice —
once through `high-pssm`, once through `glow`. With ~179 rounds airborne that
is 357.8 submissions per frame, 21% of all submissions and 31% of contributor
CPU, for 2,147 triangles — 0.046% of the frame's geometry. This is the worst
cost-per-triangle renderable in the scene by a wide margin.

## 6. API draw ownership

Identical to the submission table: every family measures 1.00 API draws per
Ogre submission on both backends (see the `draws/sub` column in section 5, and
the whole-run figures in section 4). There is no family where the two counts
diverge.

## 7. The DX11 submission/draw discrepancy — explained and retracted

**The previous phase's observation is withdrawn.** DX11 does not issue fewer
API draws than Ogre submissions. The deficit was an instrumentation defect in
the profiler.

### What was actually happening

The DX11 draw observers are vtable patches on `ID3D11DeviceContext`
(`DrawIndexed`, `Draw`, and the four instanced/indirect entry points). The
profiler verified that patch **once per frame**, at the first render-system
submission. Under load that vtable is repeatedly reverted mid-frame, so every
draw issued after the revert went uncounted.

The loss was positional rather than uniform, which is exactly why it looked
like a backend behavior. Counted fraction, from the old 80-unit DX11 capture:

| Rendered in the frame | submissions/f | counted draws/f | counted |
|---|---:|---:|---:|
| shadow cascade 0 | 243.0 | 231.8 | 95% |
| shadow cascade 1 | 243.0 | 210.5 | 87% |
| shadow cascade 2 | 243.0 | 187.8 | 77% |
| main view (`high-pssm` + `glow`) | 486.8 | 270.5 | 56% |
| post-process quads | 4.0 | 1.2 | 30% |

A monotone decline with position inside the frame is a signature of a hook that
dies partway through, not of a renderer that suppresses redundant work.

### The fix and the evidence

Checking the one vtable slot on every submission costs two loads and a compare;
the repair itself still only runs when the entry is missing. After that change:

| Run | submissions/f | API draws/f | draws/sub | noDraw/f | zeroPrim/f | unobserved/f | vtable repairs per report interval |
|---|---:|---:|---:|---:|---:|---:|---:|
| DX11 idle | 1,290.8 | 1,290.3 | 1.000 | 0.20 | 0.00 | 0.30 | 406.9 |
| DX11 firing | 1,690.3 | 1,689.7 | 1.000 | 0.27 | 0.00 | 0.41 | 176.8 |
| DX11 firing @100 m | 1,516.3 | 1,515.7 | 1.000 | 0.27 | 0.00 | 0.35 | 120.6 |
| DX11 firing @800 m | 1,521.4 | 1,520.8 | 1.000 | 0.26 | 0.00 | 0.35 | 125.4 |
| DX9 idle | 1,291.4 | 1,291.4 | 1.000 | 0.00 | 0.00 | 0.00 | **0.0** |
| DX9 firing | 1,691.0 | 1,691.0 | 1.000 | 0.00 | 0.00 | 0.00 | **0.0** |

DX9 needs zero repairs across every run; the D3D9 device vtable is never
reverted. DX11 needs 120-410 per report interval. That asymmetry between the
two backends' *hooking* is what produced an apparent asymmetry in their
*drawing*.

The residual 0.2-0.3 no-draw submissions per frame on DX11 match the
`unobserved` count one-for-one: they are the single submission in flight when a
revert is detected, and they are reported separately precisely so draw loss is
bounded instead of silently inflating a "backend suppresses draws" claim.

### The one real backend asymmetry, and why it does not bite

There *is* a genuine difference in the two render systems, from Ogre 1.10
source:

* `D3D11RenderSystem::_render` wraps its draw in `if (primCount)` — a
  submission whose primitive count computes to zero issues no API draw.
* `D3D9RenderSystem::_render` has no such guard and calls
  `DrawIndexedPrimitive`/`DrawPrimitive` regardless.

Both return early on an empty vertex buffer. The profiler now classifies every
no-draw submission by which of those applies. **`zeroPrim` measured 0.00 per
frame in every run**, so this asymmetry is real in the source and inert in this
workload. It is instrumented now, so if a future asset does trip it the counter
will say so rather than the difference being re-derived from a source reading.

Ruled out with evidence, not assumption: instancing (`DrawInstanced` and
`DrawIndexedInstanced` measured exactly 0.0/f — an earlier hypothesis that the
analyzer was ignoring instanced draws is therefore also retracted), indirect
draws (0.0/f), multiple queue entries feeding one draw (`multiDraw` 0.0/f),
attribution coverage (100.0% in every run), and contributor-slot drops (0).

## 8. Idle versus firing

| | idle | firing | delta |
|---|---:|---:|---:|
| frame mean | 3.444 ms | 9.229 ms | +5.785 ms |
| submissions/f | 1,290.8 | 1,690.3 | +399.5 |
| API draws/f | 1,290.3 | 1,689.7 | +399.4 |
| triangles/f | 4,589,917 | 4,646,661 | +56,744 |
| GPU active | 1.81 ms | 1.94 ms | +0.13 ms |
| submission cost at 0.9 us | ~1.16 ms | ~1.52 ms | +0.36 ms |
| **unexplained by render or GPU** | — | — | **~5.3 ms** |

Every extra submission a battle produces is a projectile or an effect batch,
and all of them together are worth about 6% of the cost of firing. The other
94% is simulation, ordnance, collision and effect spawning that never reaches
`SceneManager::renderSingleObject`. Removing the harness's per-frame Lua
(`fourteam_ai`) accounts for 0.57 ms of it; the remaining ~4.7 ms is unattributed
by this phase's instrumentation and is the correct Phase 2 target.

## 9. Shadow / glow / attachment / LOD isolation

Isolation suppresses a category inside `SceneManager::renderSingleObject`,
which removes the material, technique and scheme setup as well as the
submission. Captured with the profiler **disabled** and PresentMon attached, 3
repeats each. Engagement is proved per run by the profiler's own suppression
counter (~250k suppressed renderables per second on the idle workload), not
assumed.

### Idle (`fourteam`), baseline 3.444 ms

| Arm | submissions removed | mean ms | sd | delta | per submission |
|---|---:|---:|---:|---:|---:|
| baseline | — | 3.444 | 0.077 | — | — |
| `glow` | 272 (21%) | 3.253 | 0.016 | **-0.191 ms (-5.5%)** | 0.70 us |
| `shadow` | 729 (56%) | 2.924 | 0.015 | **-0.520 ms (-15.1%)** | 0.71 us |
| `glow+shadow` | 1,001 (78%) | 2.697 | 0.015 | **-0.746 ms (-21.7%)** | 0.75 us |

### Firing (`fourteam_fire`), baseline 9.229 ms

| Arm | submissions removed | mean ms | sd | delta | per submission |
|---|---:|---:|---:|---:|---:|
| baseline | — | 9.229 | 0.091 | — | — |
| `glow` | 467 (28%) | 8.765 | 0.088 | **-0.465 ms (-5.0%)** | 0.99 us |
| `shadow` | 729 (43%) | 8.690 | 0.065 | **-0.539 ms (-5.8%)** | 0.74 us |
| `glow+shadow` | 1,196 (71%) | 8.326 | 0.109 | **-0.904 ms (-9.8%)** | 0.76 us |

The arms are additive to within 5% and the per-submission cost is stable at
**0.70-0.99 us across both workloads and every arm**. That number is the single
most useful output of this phase: it converts any proposed submission
reduction into an expected frame-time saving without another experiment.

### Attachments and LOD

* **There are no attachment entities.** A BZR craft is one skeletal mesh with
  three submeshes. "Attachment" cost is submesh cost and is already broken out
  in section 5.
* **There is no mesh LOD to switch to.** `avtank.mesh`, `avfigh.mesh` and
  `svtank.mesh` contain no `M_MESH_LOD_LEVEL` chunk — one LOD level each.
  Forcing a lower vehicle LOD at distance is not a policy toggle; it would
  require generating LODs at runtime (`OgreMeshLodGenerator.dll` does ship).
* **Material LOD does work, and it now engages.** `BZBase` declares
  `lod_values 250 300` with `lod_index 0/1/2` on `high-pssm`. At 400 m the 80
  distant craft are measured at `lod=2` on `avtank00` and `avheadlight00`,
  while the player's own craft stays at `lod=0`. This is a change from the
  pre-`91476138` state recorded in the previous triage, and it is consistent
  with finite craft bounds having been restored — an entity with an infinite
  bounding radius can never leave LOD 0.
* **Material LOD reduces shader cost, not submissions or geometry.** Vehicle
  main-view submissions are 486.0 and triangles 1.54 M at 200 m, 400 m and
  800 m alike; only CPU falls, from 1.198 ms to 0.997 ms. `avtank01` never
  LODs at all because `BZBaseCockpit` declares one technique per scheme, and
  the `glow` technique has no `lod_index` so glow never LODs either.
* **Shadow casters ignore distance completely.** 728-730 submissions and
  2.30 M triangles at 100 m, 200 m, 400 m and 800 m — the same numbers, not
  approximately. Casters use `Ogre/DepthShadowmap/Caster/Float`, so the
  vehicle material's LOD (whose lower techniques are `NoShadow`) does not
  reach them.

### Distance sweep, DX11 firing, 80 units

| Distance | vehicle shadow sub/f | vehicle main sub/f | total sub/f | frame mean ms (PresentMon) | GPU ms |
|---:|---:|---:|---:|---:|---:|
| 100 m | 730.2 | 426.3 | 1,518.0 | 13.94 | 3.20 |
| 200 m | 728.2 | 485.8 | 1,604.4 | 12.98 | 1.94 |
| 400 m | 729.1 | 485.6 | 1,690.6 | 9.01 | 1.92 |
| 800 m | 728.1 | 486.0 | 1,521.1 | 13.35 | 1.90 |

Frame time does not track submissions here at all — 800 m has the *fewest*
submissions and is 48% slower than 400 m. The variation across distances is
driven by projectile population and time-of-flight, not by rendering. The
100 m column is the only one where the render side genuinely changes: GPU
active rises to 3.20 ms from overdraw, main-view submissions fall to 426
because some craft leave the frustum at that angular spread, and animation CPU
rises from 0.13 to 0.76 ms because software skinning is still active inside the
~150 m animation LOD threshold.

## 10. CPU versus GPU interpretation

| Term | Idle (3.44 ms frame) | Firing (9.23 ms frame) |
|---|---:|---:|
| GPU active | 1.81 ms | 1.94 ms |
| Ogre submissions (measured marginal) | ~0.93 ms (27%) | ~1.28 ms (14%) |
| everything else (CPU) | ~2.5 ms | ~7.9 ms |

GPU-active time is not additive with frame time — the two overlap — but its
near-constancy across a 2.7x frame-time change settles the question: this is
CPU-bound, and it stays CPU-bound when 4.6 M triangles per frame are in flight.

The distinction that matters for Phase 2:

* **Ogre submission cost** (scene traversal + pass setup + render-system call +
  API draw) is 0.7-1.0 us each, so ~1.3 ms in a large battle.
* **Backend cost** is a small part of that: DX9 and DX11 differ by ~5% of frame
  time at identical draw counts.
* **Actual API draw overhead** cannot be separated further with this harness —
  the isolation arm removes the submission and its draw together. Bounding it
  would need an arm that submits without drawing, which is not worth building
  given the size of the whole term.
* **GPU geometry/pixel cost** is ~1.9 ms and flat.
* **Everything else** — ~7.9 ms of a firing frame — is unattributed. It is
  larger than every render term combined.

## 11. Optimization implemented

**None.** The phase's own gates were: the target must be quantitatively
identified, the expected payoff must be substantial, semantics must be
preserved, and the change must be independently disableable. The measurement
satisfies the first gate and fails the second for every candidate.

The entire Ogre submission budget is ~1.3 ms of a 9.2 ms large-battle frame.
The best-supported single change available (section 17, rank 1) has a measured
ceiling of ~0.19 ms on that frame — 2%. Shipping it now would mean optimizing a
14% term while an 86% term sits unmeasured, which is the exact failure mode the
brief asks to avoid.

Two things were nevertheless fixed, and both are instrumentation rather than
rendering:

* the DX11 draw observer now survives a mid-frame vtable revert (section 7);
* a measurement-only isolation arm exists and is proven to engage.

Neither changes what the game draws. With `OPENSHIM_PROFILE_OGRE_ANIMATION`
unset the profiler's render-system and scene-manager observers are not
installed at all, so normal gameplay carries none of this.

## 12. Before/after measurements

There is no rendering before/after because nothing about rendering changed. The
instrumentation before/after is in section 7: draws per submission went from an
apparent ~0.67 on DX11 to a measured 1.000, matching DX9 exactly, on the
same workload and the same build of the game.

## 13. Opt-out results

| Control | Default | Effect when set |
|---|---|---|
| `OPENSHIM_PROFILE_OGRE_ANIMATION` | unset (off) | 0 = no profiler observers installed at all; 1 = full collection |
| `OPENSHIM_PROFILE_ISOLATE` | unset (off) | `glow`, `shadow`, or `glow+shadow` suppresses that category; logs a warning on every report interval and every 2 s of gameplay |

With both unset the shim installs only the pre-existing chunk-shadow and DX11
skin-source policies, exactly as before this branch. Verified by capturing
`fourteam_fire` with the profiler disabled and no isolation: shadows, bloom,
vehicles, effects and HUD all render normally (section 14).

## 14. Visual and regression validation

Windowed DX11, `fourteam_fire`, 40 units at 80 m, profiler disabled. 80 m is
used here rather than the 400 m benchmark distance because the `lcbench` terrain
ridge hides the formation beyond ~100 m (limitation 1). Downscaled frames are
committed next to this report as `phase1_fourteam/visual_isolate_*.jpg`; the
full-resolution captures are local under the ignored `snapshots/` tree and are
regenerated with:

```bash
pwsh ./reverse_engineering/capture_fourteam_visuals.ps1 -Scenario fourteam_fire -Isolate none -Distance 80 -Count 40 -Frames 3
```

| Arm | Result |
|---|---|
| `none` | Vehicles, ground shadows, muzzle-flash bloom, terrain, HUD all correct. No corruption, no missing geometry. |
| `shadow` | Ground shadows under the craft are gone. Everything else, including bloom, is unchanged. |
| `glow` | Ground shadows present. Muzzle flashes lose their bloom halo and read as flat sprites. Everything else unchanged. |

Each arm removes exactly the category it names and nothing else, which is the
visual counterpart of the submission arithmetic in section 9.

Log review across all 10 profiler-attached attribution runs, 10 single
profiler-disabled captures and the 27 profiler-disabled repeat captures:

* no shader errors, no renderer errors, no exceptions, no access violations;
* no invalid Ogre object lifetime or stale `ManualObject` / scene-node
  diagnostics;
* mission transitions clean — every run reached its own `benchmark-end` marker
  and exited without a crash dump;
* one pre-existing stock-content warning in `BZOgreLogfile.log`:
  `Compiler error: reference to a non existing object in pc/materials/TestGround.material`.
  That material is a stock asset referencing a program name that does not
  exist, is not used by the benchmark, and no shim code touches material
  parsing.

Chunk/debris lifetime behavior, the generic chunk batch and its opt-out are
untouched by this branch.

## 15. Known limitations

1. **The battle is occluded by terrain at the tested distances.** All 81 craft
   are inside the frustum and submitted every frame — confirmed by the
   submission counts — but the `lcbench` terrain has a ridge ahead of the
   player start, so at 150 m and beyond most craft are hidden behind it. Pixel
   and overdraw cost is therefore understated relative to a real open-ground
   battle. Given GPU-active time is ~1.9 ms and flat, this does not affect the
   CPU conclusions, but it does mean the GPU numbers are a floor.
2. **One craft type.** Every measurement uses `avtank`. Craft with more
   submeshes or different materials will shift the vehicle families' shares.
3. **No buildings or turrets.** A real mission adds static structures with
   their own materials, several of which are in the black-emissive set that
   section 17 rank 1 targets. This benchmark therefore understates that
   candidate's real-gameplay value and cannot measure it.
4. **The isolation arms measure removal, not replacement.** They bound what a
   category costs; a real optimization that reduces rather than removes a
   category will realise less.
5. **API draw cost cannot be separated from submission cost** with this
   harness (section 10).
6. **The profiler's per-contributor `cpu ms/f` column is instrumented time.**
   It includes two QPC reads and several atomics per submission. Contributor
   CPU sums to 1.730 ms on an idle frame whose profiler-disabled cost is 3.444
   ms, and the isolation arms put the true marginal submission cost at ~0.72 us
   against the column's implied ~1.34 us. Use the column for *ranking within a
   run*; use isolation for absolute cost.
7. **Frame times are from one machine.** A slower CPU would raise the
   submission term's share; a slower GPU could make GPU-active binding.

## 16. Failed hypotheses and retractions

| Hypothesis | Verdict |
|---|---|
| DX11 suppresses redundant draws, so an Ogre submission is not an API draw there | **Retracted.** Instrumentation defect; both backends measure 1.00 draws per submission (section 7). |
| The DX11 deficit is instanced draws that the analyzer's `Draw`/`DrawIndexed` fields miss | **False.** `DrawInstanced` and `DrawIndexedInstanced` measure exactly 0.0/f. |
| The DX11 deficit is Ogre's `if (primCount)` guard firing on empty submissions | **False in this workload.** The guard is real in the source but `zeroPrim` measures 0.00/f. |
| The ~1,475 submissions are the large-battle bottleneck | **Retracted.** They are worth ~1.3 ms of a 9.2 ms frame. Removing 71% of them buys 9.8%. |
| Suppressing glow or shadows changes nothing (from the first isolation captures) | **Retracted — the arms were not running.** The scene-manager detours were only installed when the profiler was collecting, so the profiler-disabled arms suppressed nothing and returned a null result that looked like a real one. Fixed in `aa852046`; the corrected arms are in section 9. |
| Distant units stay at LOD 0 | **No longer true.** Material LOD 2 is measured at 400 m. The previous triage's finding was taken before finite craft bounds were restored. |
| Glow cannot be filtered by material because emissive maps are non-black | **Too strong.** 24 material definitions across 22 stock files set `EmissiveMap black.dds`, and they include all three ordnance materials and 5 of the 9 terrain detail atlases — i.e. the highest-count renderables in a battle. See rank 1 below. |

## 17. Ranked next optimization opportunities

Expected saving uses the measured 0.9 us per submission on the firing workload.

**1. Skip the `glow` submission for materials with a provably black emissive map.**
The `glow` technique in `BZBase` binds exactly one texture unit — `EmissiveMap`,
defaulting to `black.png` — and its fragment program samples only that. A
material that sets `EmissiveMap black.dds` therefore writes black into the glow
buffer, which the downsample/blur/combine chain adds as nothing. This is a
static, offline-provable property of the material, so skipping it is invisible
by construction rather than by tuning. 24 material definitions across 22 stock material files
qualify, of 252, including all three of `ordnanceRed`/`Blue`/`Green` and 5 of
the 9 `*_detail_atlas` terrain materials -- among them `mn_detail_atlas`, the
one this benchmark's terrain uses. In this benchmark that is
179 ordnance + 29 terrain = 208 submissions/f, ~0.19 ms (2% of a firing frame,
4.4% of an idle frame). Real gameplay adds turrets, scavengers, pilots and
towers to that set. **Risk: very low. Payoff: small but certain.**

**2. Per-cascade distant shadow-caster culling.**
729 submissions/f, 43% of the total, measured at 0.539 ms. Completely invariant
with distance. The boundary is bounded and testable — does this caster
contribute texels to this cascade at this range — and shadow participation is a
policy, not asset geometry, so an opt-out is straightforward. **Risk: medium
(missing shadows are visible). Ceiling: 0.54 ms.**

**3. Batch or instance projectiles.**
357.8 submissions/f for 2,147 triangles. Every round is an independent 6-triangle
skeletal entity submitted twice. Consolidating rounds sharing a material into
one buffer is the same shape as the generic chunk batch that already shipped.
**Risk: medium. Ceiling: ~0.32 ms, and it scales with battle size better than
anything else on this list.**

**4. Consolidate or distance-suppress the tiny vehicle submeshes.**
`avheadlight00` and `avtank01` are 260 of 9,485 triangles but 4 of every 6
main-view submissions and 31% of contributor CPU. **Risk: high — mods ship
their own meshes and materials, and the headlight submesh carries visible
detail. Ceiling: ~0.3 ms.**

**5. Generate runtime mesh LODs for craft.**
Would reduce triangles (currently 3.8 M/frame from craft) but not submissions,
and the GPU is not the constraint. **Low value until something makes the GPU
the constraint.**

Ranks 1-4 together have a ceiling of roughly 1.35 ms on a 9.2 ms frame, and
they overlap: 1 and 3 both target projectiles. A realistic combined outcome is
under 10%.

## 18. Recommendation for Phase 2

**Do not spend Phase 2 on render submissions.** They are measured, ranked, and
worth at most ~14% of a large-battle frame; the four candidates above are
documented well enough to be picked up cheaply whenever they become worth
doing.

**Phase 2 should attribute the ~7.9 ms of non-render CPU in a firing frame.**
It is the largest term by a factor of six and nothing currently measures it.
The specific evidence pointing there:

* idle → firing costs +5.79 ms while adding only ~0.36 ms of submissions and
  0.13 ms of GPU;
* removing the harness's per-frame Lua accounts for 0.57 ms of that, so ~4.7 ms
  is engine work;
* the distance sweep shows frame time tracking projectile population rather
  than anything the renderer does — 800 m has the fewest submissions and is
  48% slower than 400 m.

Concretely: instrument the game's own per-frame phases (simulation tick,
ordnance update, collision, effect spawning, audio) the way the render path is
instrumented now, on the same four-team workload, and produce the equivalent of
section 5 for the non-render frame. The four-team harness, the isolation
mechanism, the PresentMon arms and the family classifier all carry over
unchanged.

If a render change is wanted anyway before that work, take rank 1: it is the
only candidate whose visual equivalence can be proved offline rather than
argued from screenshots.

---

## Largest remaining render-cost owners

DX11, 80 units, four teams, 400 m, firing. Frame mean 9.229 ms. Frame-time
contribution is measured where an isolation arm covers the category exactly,
and derived at 0.9 us per submission otherwise.

| Category | Submissions/frame | API draws/frame | Est. frame-time contribution | Optimization opportunity | Risk |
|---|---:|---:|---:|---|---|
| Vehicle shadow casters (3 cascades x 3 submeshes x 81) | 729.1 | 728.9 | **0.539 ms (5.8%)** — measured | Per-cascade distance/texel-coverage culling | Medium — missing shadows are visible |
| Vehicle main view (`high-pssm` + `glow`, 3 submeshes) | 485.6 | 485.4 | ~0.44 ms (4.7%) | Consolidate or distance-suppress the 192- and 68-triangle submeshes | High — mod meshes and materials |
| Ordnance / projectile meshes (6 triangles each, x2 schemes) | 357.8 | 357.8 | ~0.32 ms (3.5%) | Batch rounds sharing a material; drop the provably-black glow pass | Medium (batching), very low (glow) |
| — of which the black-emissive `glow` pass | 178.9 | 178.9 | ~0.16 ms (1.7%) | Skip; provably writes nothing | **Very low** |
| Terrain main view (`MN_DETAIL_ATLAS`, both schemes) | 58.0 | 58.0 | ~0.05 ms (0.6%) | Drop the black-emissive glow pass (29 sub/f) | Very low |
| Effects (`DynamicGeometryBatch`) | 53.0 | 53.0 | ~0.05 ms (0.5%) | Already batched by material | — |
| Post-process quads + sky | 7.0 | 7.0 | ~0.01 ms | None | — |
| **All render submissions** | **1,690.6** | **1,690.1** | **~1.28 ms (14%)** | — | — |
| **Non-render CPU (unattributed)** | — | — | **~7.9 ms (86%)** | **Phase 2** | — |
