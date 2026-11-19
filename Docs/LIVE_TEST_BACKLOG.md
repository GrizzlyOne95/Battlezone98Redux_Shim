# Live tests owed

Native and gameplay changes merge only after a live test (see
`Docs/FEATURE_WORK_QUEUE.md`, "Standing"). This file is the one list of what
still owes one. Add a row when a PR that needs a live test opens. Delete the
row when its test passes, and note the result in the PR.

Run the tests through the shared live-test harness, under `bzr_livetest.lock`,
with deployed files hash-restored afterwards. Each checklist names its
preconditions; a failed precondition is a fixture failure, not a FAIL.

Updated 2026-11-18.

## Waiting for a live test

| Feature | PR / branch | Checklist | Fixture needed | Still UNVERIFIED |
|---|---|---|---|---|
| Satellite follow camera (`RtsFollowCamera`, Shift+C) | #900, `agent/follow-camera` (base main) | `Docs/RTS_COMMANDS.md` 11b | none | One-frame lag or tug against mouse pan; side effects of the per-frame vcall at `[obj+0x18]` slot 0x2C |
| Daywrecker fall-on-spawn ODF key | #901, `agent/daywrecker-fall-on-spawn` (base main) | `Docs/DAYWRECKER_FALL_ON_SPAWN.md` | Test ODF with the key | Flag restore on save/load; whether `BuildObject(vector)` snaps to ground |
| Daywrecker `dropRate` ODF key | #902, `agent/daywrecker-drop-rate` (base #901) | `Docs/DAYWRECKER_DROP_RATE.md` | Test ODF with the key | (see doc) |
| Radar order pings (`RtsRadarPings`) | #903, `agent/radar-order-pings` (base #900) | `Docs/RTS_MARKERS.md` 13 | none | Known cosmetic: rim-clamped ring spills a few pixels past the radar disc |
| FPS quick-commands (`RtsQuickCommands`, Numpad 1/2/3/5) | #907, `agent/fps-quick-commands` (base #903) | `Docs/RTS_COMMANDS.md` 11c | none | Tanks and turrets list ModeList 14 (Attack); `GameObject::EnemyP` matches the panel's ally rule |
| Tread texture scroll (`treadScrollU`, DX11 Enhanced) | PR pending, `agent/tread-texture-scroll` | `Docs/TRACKED_VEHICLES.md` (tread scroll steps) | **Blocked:** a tracked model with separate L/R tread materials. None exists yet | Tread pass whose instanced twin was built before the bind stays unscrolled |

## Merge order once tests pass

#900, then #903, then #907 (each is stacked on the one before). #901, then #902.
