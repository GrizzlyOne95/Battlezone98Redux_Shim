# lcbench pilot/craft light scene-flip fixture — `lcbench_pilotlight`

Deterministic A/B laboratory for the whole-scene light step reported on
2026-09-13. Deployed as an overlay on the existing `addon/lcbench` world, the
same way as the pilot, neutral, wmask and aip harnesses: the runner installs the
`live_combat_scaling` world files plus `rmplight.lua` as `addon/lcbench/lcbench.lua`,
launches `battlezone98redux.exe lcbench.bzn` through `BZRHarness.ps1` with
`BZR_FORCE_WINDOWED=1`, captures window frames with `PrintWindow`, and restores
`openshim.ini` and `addon/lcbench` by hash in a `finally` block. If
`addon/lcbench` did not exist, the runner creates it and removes it again.

## What is being measured

A play01.bzn capture (no mission script, so engine plus shim only) showed the
entire 3D scene stepping between two light levels, co-timed to the frame with
boarding and leaving a craft:

| capture frame | player | terrain patch luma | headlight cone |
|---|---|---:|---|
| 0-85 | in craft | 70.0 | on |
| 86-707 | on foot | 70.0 | off from f98 |
| **708**-989 | in craft | **39.3** | **on** |
| 990-1512 | on foot | 39.3 | off from f1000 |
| 1513-1584 | on foot | 70.0 | off |
| **1585**-end | in craft | **39.3** | **on** |

Frames 707 and 708 are consecutive, same camera, both in the craft: one frame
apart the scene drops 2.4x and the cone appears.

It is a scene light level, not a post-process:

- sky-dome star pixels are **bit-identical** across the step (105 -> 105, region
  max 125.67 -> 125.67), so unlit geometry is untouched;
- relative contrast (sigma/mu 0.194 -> 0.221) and hue (B/R 1.360 -> 1.329) are
  preserved, so it is an intensity scale rather than a light being removed;
- pure black stays black, so nothing additive is involved;
- the HUD does not change, so it happens before HUD compositing.

## Scenarios

`run_lcplight.ps1 -Scenario flashlight` varies `[SinglePlayer] PilotFlashlight`.
`-Scenario headlight` varies `HeadlightFalloffRepair` and `Headlights` with the
pilot flashlight off throughout, so the craft light is the only variable.

Every arm writes every key the scenario varies, so no arm inherits a value by
omission, and each arm proves it engaged from its own log (`[PILOTLIGHT] created`
count for the flashlight scenario, the observed `range=` in `[HEADLIGHT-PROBE]`
for the headlight scenario). An arm that did not engage is reported as
**NOT ENGAGED** and excluded rather than averaged in — a dead arm otherwise reads
exactly like a null result.

Two rectangles are measured per frame, because a light that only changes its own
pool is a completely different finding from one that changes the whole map:

- `offbeam` — upper right hillside, which no player light points at;
- `beam` — lower centre right, where a torch or headlight pool lands.

## Result, 2026-09-13, `-Scenario flashlight`

GOG Redux 2.2.301, installed `winmm.dll` SHA-256 `55C4D20F…B9FA9BAB`, windowed.
Both arms engaged (`on`: one `[PILOTLIGHT] created`; `off`: none).

| region | PilotFlashlight=1 | PilotFlashlight=0 | ratio |
|---|---:|---:|---:|
| beam (its own pool) | 110.0 | 46.7 | **2.36** |
| offbeam (upper right hill) | 25.8 | 35.1 | **0.74** |
| far right edge | 36.7 | 44.3 | 0.83 |

The flashlight lights its cone **and darkens everything outside it by 17-26%**.

The live `[HEADLIGHT-PROBE]` line in the same runs shows what the craft light
looks like under the shipped preset (`HeadlightColor=White`, `HeadlightBeam=Wide`):

```text
type=2 diffuse=(4.000,4.000,4.000) range=2239.8
attenuation=(c=1.0000 l=0.00700 q=0.000200)
inner=63.03deg outer=85.94deg falloff=2.000 castShadows=no
```

Stock is 10/20 degrees, diffuse 1.0, range 600. `HeadlightFalloff::SolveInvisibleRange`
raised the range to 2239.8 m so the cone terminator falls below the 8-bit floor.
`include/headlight_falloff.h` names that exact hazard in its own comment on
`kMaxRange`: *"past a few kilometres the light is in every renderable's candidate
list for no visible gain."*

## Timeline the fixture drives

```text
T+0    START       in a craft
T+8    HOP_OUT     on foot; the shim creates the pilot flashlight ~200 ms later
T+26   BOARD       back into the craft via exu.SetAsUser when EXU is present
forever HEARTBEAT  never fails the mission, so the runner owns process lifetime
```

The board leg is a bonus, not a gate: plain BZ has no Lua API for entering a
craft. The hop-out leg alone changes the flashlight's existence, which is the
variable under test. The view is never driven — an A/B is only meaningful if
both arms photograph the same geometry.

## How to run

```powershell
pwsh -File reverse_engineering/run_lcplight.ps1 -Scenario flashlight
pwsh -File reverse_engineering/run_lcplight.ps1 -Scenario headlight
pwsh -File reverse_engineering/run_lcplight.ps1 -Scenario headlight -Arms repair,stock
```

Sample times are seconds after **process launch**, not mission time: the engine
spends roughly 13 s on the loading screen before `Start()` runs, and a frame
captured during the load is the same bitmap in every arm. The first attempt at
this fixture sampled at t+6 and t+13 and produced two byte-identical 1257577-byte
PNGs with identical luma, which is not a null result — it is not a measurement.

The runner refuses to launch while another `battlezone98redux.exe` is running.
This repository's working tree is shared with parallel agents and the game
install is a single shared resource; a second launch would fight over
`openshim.ini` and `addon/lcbench`.
