# play01 live AI scan notes

Live scan target:
- Game: Battlezone 98 Redux 2.2.301, launched with `play01.bzn`.
- Map purpose: production units, buildings, and allied scavengers.
- Process used for scan: `battlezone98redux.exe`, PID `12192`.
- Backlog focus: high-priority AI ODF behavior work, especially scavenger recycle task behavior and AI retarget/reaction tuning.

## Key conclusion

The useful live Redux/Steam anchors for scavenger recycle behavior are the
`0x005Bxxxx` RecycleTask functions, not the older `0x0050xxxx` public-symbol
addresses. Live vtables and runtime heap instances both support this mapping.

## Live hooks already observed

| Site | Address | Live bytes | Note |
| --- | ---: | --- | --- |
| `OffensiveProcess::DoSubTask` | `0x004DFE70` | `E9 BB 55 53 6D 90 90 90 ...` | Already detoured by OpenShim. |
| `GunTowerProcess::DoSubTask` | `0x004741A0` | `E9 3B 06 59 6D 90 ...` | Already detoured by OpenShim. |
| `CalcRange(Craft)` advisory site | `0x0041F240` | `45 D8 89 45 C8 68 B4 2C ...` | Does not match the expected prologue or a detour in this live run. Resolved later as `FUN_00466BE0`; see `backlog_address_audit_20260708.md`. |

Post-run `winmm_shim.log` confirmation:
- `[AIODF] CalcRange(Craft) entry bytes mismatch at 0x0041F240; AI ODF range tuning disabled`
- `[SHIELDODF] ShieldTower::Simulate vtable mismatch slot=0x00887728 current=0x004178A0 expected=0x005D0D80`
- `[PROXODF] ProximityMine::Simulate vtable mismatch slot=0x00886234 current=0x0047F330 expected=0x005B0E40`

## RecycleTask anchors

| Function | Address | Stable entry bytes / pattern seed |
| --- | ---: | --- |
| `RecycleTask::InitState` | `0x005B6340` | State dispatcher. |
| `RecycleTask::CleanState` | `0x005B63E0` | State cleanup dispatcher. |
| `RecycleTask::DoState` | `0x005B6470` | State execution dispatcher. |
| `RecycleTask::InitLookingForScrap` | `0x005B6580` | `55 8B EC 83 EC 74 A1 ?? ?? ?? ?? 33 C5 89 45 FC` |
| `RecycleTask::InitGotoScrap` | `0x005B69E0` | `55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1` |
| `RecycleTask::DoGotoScrap` | `0x005B6AE0` | `55 8B EC 51 89 4D FC 8B 45 FC 83 78 30 00 75 02` |
| `RecycleTask::IsStuck` | `0x005B6FA0` | `55 8B EC 83 EC 14 89 4D F8 8B 45 F8 8B 48 2C` |
| `RecycleTask::InitStuck` | `0x005B7060` | `55 8B EC 51 89 4D FC 8B 45 FC C7 40 28 00 00 00` |
| `RecycleTask::CleanStuck` | `0x005B7080` | `55 8B EC 83 EC 08 89 4D FC E8 ?? ?? ?? ?? D9 5D` |
| `RecycleTask::DoStuck` | `0x005B70E0` | `55 8B EC 81 EC 7C 03 00 00 A1 ?? ?? ?? ?? 33 C5` |

Live `RecycleTask` vtable: `0x008868BC`.

Example live instance from `play01.bzn`:
- `RecycleTask*`: `0x42B0EB38`
- Owner `me`: `0x02A02B20`, first dword `0x00886FE8`
- Active subtask: `0x4628EAF0`, first dword `0x00886878`
- State sample: `curState=3`, `nextState=8`, `stuckState=0`

Useful field offsets:

| Field | Offset |
| --- | ---: |
| `nextStuck` | `+0x18` |
| `lastStuck.x/y/z` | `+0x1C/+0x20/+0x24` |
| `stuckState` | `+0x28` |
| `me` | `+0x2C` |
| `subtask` | `+0x30` |
| `scrapHandle` | `+0x40` |
| `dropHandle` | `+0x44` |
| `curState` | `+0x48` |
| `nextState` | `+0x4C` |
| `nextCheck` | `+0x5C` |

## UnitTask anchors

Live `UnitTask` vtable: `0x00889F14`.

Important entries observed:
- `UnitTask::Save`: `0x005FFA70`
- `UnitTask::Execute`: `0x006002A0`
- `UnitTask::DrawStateA`: `0x006004A0`

Useful field offsets:

| Field | Offset |
| --- | ---: |
| `curState` | `+0x08` |
| `nextState` | `+0x0C` |
| `me` | `+0x10` |
| `himHandle` | `+0x14` |
| `braccelFactor` | `+0x64` |
| `strafeFactor` | `+0x68` |
| `steerFactor` | `+0x6C` |
| `avoidSkip` | `+0x78` |
| `nextStuck` | `+0x84` |
| `lastStuck.x/y/z` | `+0x88/+0x8C/+0x90` |
| `stuckState` | `+0x94` |
| `pitch` | `+0xB0` |
| `blastDist` | `+0xF0` |

## Recommended next hook targets

1. `RecycleTask::InitLookingForScrap @ 0x005B6580`
   - Best first target for AI ODF scavenger knobs. This is where scrap candidates are evaluated, rejected, and converted into the active scrap handle.
2. `RecycleTask::IsStuck @ 0x005B6FA0` and `RecycleTask::CleanStuck @ 0x005B7080`
   - Best target for scavenger stuck timing and movement threshold tuning. `CleanStuck` refreshes `nextStuck` with the hardcoded follow-up delay.
3. `RecycleTask::DoStuck @ 0x005B70E0`
   - More invasive target for advanced unstuck behavior. Prefer collecting one more trace before detouring this whole function.
4. `CalcRange(Craft) @ 0x00466BE0`
   - Follow-up audit resolved the stale advisory address and confirmed the corrected detour installs. Use this site for gameplay validation of `engageRangeAI`, `weaponRangeMinAI`, and bomber stand-off tuning.

## Scavenger path-scoring implementation, 2026-07-13

The first scavenger hook is now implemented at the narrow distance-score call
inside `RecycleTask::InitLookingForScrap`, rather than detouring the whole task.

Validated Redux sites:

| Item | Address | Validation |
| --- | ---: | --- |
| Candidate distance call | `0x005B680E` | `E8 9D B8 EA FF`, calls `Dist3D_Squared @ 0x004620B0` |
| `FindPlan(GameObject*, float, float)` | `0x004666C0` | Same overload used by the stock final candidate validation |
| `AiPath::GetLength` | `0x00461110` | Sums the length of consecutive points at `AiPath+0x08` |
| `AiPath` scalar deleting destructor | `0x00460640` | Called with flag `1`, matching stock path cleanup |

As of 2026-07-14 the replacement call uses pathing mode by default in
single-player through `[SinglePlayer] SmartScavengerPathing=1`. An enabled AI
ODF tuning layer can still set `scrapPathingAI = false` for a specific scavenger
ODF; multiplayer always returns to the stock squared-distance behavior. In
pathing mode it:

1. preserves the stock team, ownership, region, and `GoodScrapPosition` filters;
2. applies `scrapSearchRadiusAI` when positive;
3. calls `FindPlan` for each surviving candidate;
4. scores a good path as `pathLength * scrapPathLengthWeightAI + straightDistance * scrapStraightDistanceWeightAI`;
5. scores a bad path with `scrapPathFailPenaltyAI` plus the secondary straight-distance term, allowing the unchanged stock final validation/retry loop to reject it;
6. keeps a Shim-side failure cooldown keyed by scrap pointer and position so the
   stock first-pass clearing of `HardToGetTo` does not defeat
   `scrapHardToGetCooldownAI` across scans.

Every address and helper prologue is byte-checked before the call is patched.
On a mismatch, invalid pointer, missing ODF setting, or disabled master toggle,
the path scorer fails back to the stock distance behavior. Trace output is
available with `OPENSHIM_TRACE_SCAVENGER_PATH=1` or
`OPENSHIM_TRACE_AI_SCAVENGER=1`.

### En-route retargeting, 2026-07-13

Redux `RecycleTask::DoGotoScrap @ 0x005B6AE0` only executes the existing
`ScavGotoScrap` subtask until it finishes; it never re-enters candidate
selection when new scrap appears. OpenShim now detours its seven-byte prologue
(`55 8B EC 51 89 4D FC`), calls the stock routine first, and periodically asks
the unchanged state machine to transition back to `LookingForScrap` when the
subtask is still active.

This behavior is part of `scrapPathingAI = true`. Its additional ODF controls
are:

- `scrapRetargetPeriodAI`: seconds between en-route rescoring passes; defaults
  to `2.0`, and a non-positive value disables en-route retargeting.
- `scrapRetargetMinImprovementAI`: score advantage a new target must have over
  the incumbent; defaults to `25.0` path-score units.

The current target receives the improvement margin as a temporary score bonus,
which prevents comparable candidates from causing target oscillation. A fixed
20 m pickup guard suppresses rescoring when the scavenger is already close to
its current scrap. The stock subtask cleanup and `InitLookingForScrap` /
`InitGotoScrap` transitions remain responsible for safely deleting and
rebuilding the actual movement task.

## Probe helper

Read-only helper used during this scan:

`reverse_engineering/live_ai_address_probe.py`

Example:

```powershell
python reverse_engineering\live_ai_address_probe.py --pid 12192 --max-hits-per-type 24 --max-region-mb 64
```
