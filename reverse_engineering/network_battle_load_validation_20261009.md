# Multiplayer battle-load qualification — 2026-10-09

Status: implemented; four-client live qualification in progress. This extends
the objective/services impairment suite with natural AI combat and object churn.
It does not change client retry timers, packet ordering, or server defaults.

## Reproducible scenario

`Run-BZRBattleLoad.ps1 -Units 40 -Seconds 60` stages `nbattle.bzn` over the
repository's authored `lcbench` terrain. Requires the four prepared private
`C:\BZRCoop\instances` clients, EXU/CRCoop content, windowed rendering and the
existing private network control setup. It is a separate multiplayer test map,
not a campaign mission with objectives skipped. The normal game install and CR
source/content remain unchanged.

- Humans on teams 1–4 observe two host-owned AI armies on reserved teams 5–6.
- Tanks/fighters use native `Attack` AI, ordinary health/ammo and natural deaths.
- Four units spawn per quarter-second into distinct vacant army slots; retarget
  only when the victim dies. Requested duration starts after the full population
  first assembles; ramp has a separate 30-second limit.
- Replacements sustain the requested load; maximum 160 active and 640 cumulative
  spawns prevent an unbounded test. Scrap is left to native gameplay.
- No scripted damage, kills, health/ammo refill, or removal during measurement.
  Removal is a separate post-measurement host cleanup/convergence check.
- Each client samples AI/scrap counts. Scrap uses exact `classLabel == "scrap"`
  over `AllObjects`, including zero-health pieces. `scrapObserved` is unique
  census-observed handles within 600 m of the arena, not an exact native creation
  total. Baseline handles are excluded. Measured peaks freeze at workload end.
- Host evidence must include ammo consumption, damage, deaths and natural scrap.
  Requested load must reach 75%; at least 75% of steady host samples must retain
  that load. Guests must observe both armies, at least 50% load and new scrap.

Evidence: `battle-samples.jsonl`, `battle-summary.json`, `flow-summary.json/.md`,
four-client screenshots, archived native captures/logs, relay/protocol traces,
native-network-health report and hashed source/content/display provenance.
CPU totals, working set, simulation clocks/update counts and probe command
latency are diagnostics, not renderer FPS. Four processes share one machine;
no WAN, multi-PC, or independent GPU performance acceptance is implied.

## Progress and runs

| Run/control | Result | Meaning |
|---|---|---|
| `battle-control-20261009-100420` / `battle-load-20261009-100420-smoke20` | preflight stopped | Harness only accepted missions already in campaign content. No game launched; 128 backed-up targets restored/verified. Preflight now accepts a mission Lua supplied by a valid override. |
| `battle-control-20261009-100650` / `battle-load-20261009-100650-smoke20` | lobby selection failed | All four authenticated. Display name placed the new map below the visible searched rows. No combat started. Display name now sorts first. Restored/verified. |
| `battle-control-20261009-101002` / `battle-load-20261009-101002-smoke20` | native map load failed | All four selected/launched the map; native loader rejected craft-state fields inherited by generated start markers (`battle_spawn1 skipped pilot class`, failed to load game files). Replaced the marker with the validated authored co-op `pspwn_1` template. No combat started; restored/verified. |
| `battle-control-20261009-101530` / `battle-load-20261009-101530-smoke20` | lobby selection failed | New map was already selected; harness required a changed settings version and then walked away from it. Missing/comma-only vehicle descriptions also appeared. No combat. Independent review found marker-coordinate regexes also overwrote orientation/velocity; fixed before the next launch. Restored/verified. |
| `battle-control-20261009-102214` / `battle-load-20261009-102214-smoke20` | running | Four clients, clean network, 20 requested AI, 45 sustained seconds after ramp. Validated marker structure/basis/velocity, proper pilot VXT, description, terrain filenames matching map name. Harness accepts an already-selected matching map. Source/scenario snapshotted. |

The Lua fixture passed authority restrictions, bounded frame spawning,
native damage/ammo/death accounting, exact zero-health scrap classification,
and prohibition of cleanup during the measured phase. Additional checks passed
160 distinct initial positions and the 640-creation cap under rapid attrition.
PowerShell syntax and map staging passed. Python map regression verifies all
four native marker bases, translations, zero motion, team/sequence/mission
references, and byte-identical copies of the existing authored terrain.

## Next qualification gates

First qualify real destruction/scrap and clean host/guest cleanup at 20 units.
Then measure 40/80-unit clean runs and matched 80-unit fix ON/OFF runs with 3%
loss. Preserve the clean reference alongside loss runs. Add equal-population
idle/moving-only controls before attributing packet growth specifically to
combat instead of object count. Natural combat is repeatable configuration,
not bit-deterministic native simulation; repeated seeds/passes remain required.
Scrap collection/scavengers, artillery/projectile-heavy armies, sustained soak,
bandwidth caps and real WAN remain additional lanes. Do not claim these passed
from a tank/fighter run.
