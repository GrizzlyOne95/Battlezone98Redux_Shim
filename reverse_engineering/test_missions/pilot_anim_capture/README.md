# Pilot Animation Harness — `pilot_anim_capture`

Purpose-specific runtime laboratory for **PLAYER PILOT ANIMATION MANAGEMENT** as specified in the 2026-08-27 investigation.

## What it does

Forces the local player through a deterministic 0–32 s timeline while emitting precise `[PILOTTEST]` markers that correlate 1:1 with OpenShim's `[FPAnim]` animation-state log. It requires minimal manual input; where automation is incomplete it pauses and prints a single instructional marker.

Timeline:

| Elapsed | Event | Marker | Expected animation / note |
|---------|-------|--------|---------------------------|
| 0.0 | mission init | `[PILOTTEST] INIT` | player in vehicle |
| 2.0 | HopOut | `[PILOTTEST] HOP_OUT` | `HopOut(GetPlayerHandle())` |
| ~3.0 | pilot exists | `[PILOTTEST] PILOT_DETECTED` | `IsPerson(GetPlayerHandle())==true`, captures handle/ODF/class/pilotClass/team/pos/weapon |
| 2–6 | idle baseline | `[PILOTTEST] IDLE_WINDOW` | should be `idle` looping |
| 8.0 | sniper equip | `[PILOTTEST] SET_SNIPER` | `GiveWeapon(pilot, "gsnipe")`; expect `stand2Kneel` → crouch |
| 10.0 | crouch observation | `[PILOTTEST] CROUCH_EXPECTED` | expect `fireRecoilSniper` / `stand2Kneel` completion |
| 13.0 | fire | `[PILOTTEST] FIRE_WINDOW` | `FireAt` or `exu.animation.Play("fireRecoilSniper")` |
| 16.0 | move/strafe | `[PILOTTEST] MOVE_WINDOW` | `Goto` + `exu.animation.Play("runForward")` vs manual WASD |
| 19.5 | jump | `[PILOTTEST] JUMP_WINDOW` | manual Space + `exu.animation.Play("jump")` feasibility probe |
| 24.0 | final idle | `[PILOTTEST] FINAL_IDLE` | weapon back to `handgun`, expect `kneel2stand` → `idle` |
| 32.0 | complete/lifetime transition | `[PILOTTEST] LIFETIME_DESTROY` then `[PILOTTEST] TEST_COMPLETE` | Attempts `DeleteObject(GetPlayerHandle())`, then schedules `FailMission`; validates release through a supported mission transition without relying on unsupported player `GetIn` |

## Deployment

### Option A — overwrite lcbench (recommended for lcbench-trained workflows)

```
addon/lcbench/lcbench.bzn
addon/lcbench/lcbench.mat / .hg2 / .lgt / .trn / .ini   (stock lcbench copies)
addon/lcbench/lcbench.lua   ← replace with pilot_anim_capture/pilot_test.lua
addon/lcbench/pitcfg.odf    ← copy from pilot_anim_capture/pitcfg.odf (optional, 6-char name)
```

Launch Instant Action → **lcbench**. The harness auto-runs; follow any `[PILOTTEST] MANUAL ACTION:` line that appears.

### Option B — standalone Instant Action `pilot`

```
addon/pilot/pilot.bzn/.mat/.hg2/.lgt/.trn/.ini   (copies in this folder)
addon/pilot/pilot.lua   ← copy of pilot_test.lua renamed to pilot.lua (basename must match .bzn)
addon/pilot/pitcfg.odf
```

Launch Instant Action → **pilot**.

Both options use the same BZN (player-only, flat `earthgood` terrain); only the Lua basename matters to the engine.

## ODF constraint

All ODF basenames here are ≤8 chars (`pitcfg`, `gsnipe`, `handgun`, `pilot`). Do not introduce longer names; the engine truncates them.

## Lua constraints

- Lua 5.1, no `goto`/`::cont::`, no `io`/`os`/`debug`.
- Uses `print()` for markers; never `DisplayMessage`/`Command`.
- Handles null-padded getters (`GetOdf`, `GetPilotClass`, `GetWeaponClass`, etc.) via `TrimNullPad`.
- Validates `IsValid` before every dereference; does not cache `GetPlayerHandle()` across HopOut/death without revalidation.

## Correlation with native trace

1. Enable the enhanced trace (default-on):

```
[Diagnostics]
TracePilotFPAnimations=1
```

Environment override: `OPENSHIM_TRACE_PILOT_FP_ANIMATIONS=1`.

2. Optional manipulation experiment (isolated, lcbench-only, dormant by default):

```
[Diagnostics]
PilotFPAnimManip=1
PilotFPAnimManipAnim=stand2Kneel
PilotFPAnimManipMode=freeze   # or forceWeight
```
Or `OPENSHIM_PILOT_FP_MANIP=1`.

3. Run the harness and collect `openshim.log`. Correlate:

```
[PILOTTEST] T+2.000 HOP_OUT
[FPAnim] target person=0x... entity=0x...    ← should appear ~25 ms after PILOTTEST
[FPAnim] entity=0x... anim=stand2Kneel state=0x... bound=1 caller=... rva=0x...
[FPAnim] entity=0x... anim=stand2Kneel state=0x... enabled=1 caller=... rva=...
```

`caller` is `_ReturnAddress()` and `rva` is its offset in `battlezone98redux.exe`. A caller inside `Person::Simulate` (expected `0x59D340` family, grounded branch `0x59DEA5`) proves the game's pilot FSM drives the animation; a caller outside that region points to a separate system.

## Automation limits & manual steps

| Action | Automatable? | Harness behavior if not |
|--------|--------------|--------------------------|
| HopOut | YES (`HopOut`) | retries, then prints manual HopOut key |
| Weapon equip | YES (`GiveWeapon`) | logs mismatch, retries |
| Sniper crouch pose | SEMI (selection drives FSM) | waits 3 s, logs manual sniper-select reminder |
| Firing | SEMI (needs enemy or anim) | tries `exu.animation.Play` + `FireAt(nearestEnemy)`, else manual fire hold |
| Walking/strafe | SEMI (`Goto` + `exu.animation.Play`) | manual WASD |
| Jumping | MANUAL (no stable Lua Jump API) | prints tap-Space instruction + plays `jump` via EXU for feasibility only |
| Pilot lifetime release | YES (`DeleteObject`) | a fresh harness launch validates subsequent acquisition |

If a manual step is required, the harness prints:

```
[PILOTTEST] MANUAL ACTION: hold sniper zoom now
[PILOTTEST] CAPTURE WINDOW: 5 seconds
```

and automatically continues after the window.

## EXU probing

When `exu.animation` is present, each `DumpPlayerInfo` also enumerates:

```
idle, runForward/Backward/Left/Right, stand2Kneel, kneel2stand, fireRecoilSniper, jump, landParachute, idleParachute
```

with `enabled/loop/weight/timePosition/length/normalizedTime/atEnd`. This inventory supplements the native `[FPAnim] inventory` poll (every 1500 ms) that logs bound states plus `hasAnimSet` existence.

## Expected log volume

- Binding and transition events: a few dozen lines per phase (not per frame).
- `dt` (addTime) throttled to ≤2 logs/sec with suppression count.
- Inventory: one poll per 1.5 s, not per frame.

## Validation

After deploying, run:

```
.\scripts\run_ogre_profiler_tests.ps1
.\scripts\run_ini_tests.ps1
# then in-game:
# Instant Action → lcbench (or pilot) → idle 32 s → quit → inspect openshim.log for [PILOTTEST] + [FPAnim] correlation
```
