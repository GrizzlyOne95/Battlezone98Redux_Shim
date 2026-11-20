# Live tests owed

Native and gameplay changes merge only after a live test (see
`Docs/FEATURE_WORK_QUEUE.md`, "Standing"). This file is the one list of what
still owes one. Add a row when a PR that needs a live test opens. Delete the
row when its test passes, and note the result in the PR.

Run the tests through the shared live-test harness, under `bzr_livetest.lock`,
with deployed files hash-restored afterwards. Each checklist names its
preconditions; a failed precondition is a fixture failure, not a FAIL.

Updated 2026-11-19.

## Waiting for a live test

| Feature | PR / branch | Checklist | Fixture needed | Still UNVERIFIED |
|---|---|---|---|---|
| Satellite follow camera (`RtsFollowCamera`, Shift+C) | #900, `agent/follow-camera` (base main) | `Docs/RTS_COMMANDS.md` 11b | none | One-frame lag or tug against mouse pan; side effects of the per-frame vcall at `[obj+0x18]` slot 0x2C |
| Daywrecker fall-on-spawn ODF key | #901, `agent/daywrecker-fall-on-spawn` (base main) | `Docs/DAYWRECKER_FALL_ON_SPAWN.md` | Test ODF with the key | Flag restore on save/load; whether `BuildObject(vector)` snaps to ground |
| Daywrecker `dropRate` ODF key | #902, `agent/daywrecker-drop-rate` (base #901) | `Docs/DAYWRECKER_DROP_RATE.md` | Test ODF with the key | (see doc) |
| Radar order pings (`RtsRadarPings`) | #903, `agent/radar-order-pings` (base #900) | `Docs/RTS_MARKERS.md` 13 | none | Known cosmetic: rim-clamped ring spills a few pixels past the radar disc |
| FPS quick-commands (`RtsQuickCommands`, Numpad 1/2/3/5) | #907, `agent/fps-quick-commands` (base #903) | `Docs/RTS_COMMANDS.md` 11c | none | Tanks and turrets list ModeList 14 (Attack); `GameObject::EnemyP` matches the panel's ally rule |
| Tread texture scroll (`treadScrollU`, DX11 Enhanced) | #911, `agent/tread-texture-scroll` (base main) | `Docs/TRACKED_VEHICLES.md` (tread scroll steps) | **Blocked:** a tracked model with separate L/R tread materials. None exists yet | Tread pass whose instanced twin was built before the bind stays unscrolled |
| Walker free head M1 (`[WalkerClass] torsoName`) | #914, `agent/walker-free-head-m1` (base #910) | `Docs/WALKER_FREE_HEAD.md` | avwalk copy `avwalkfh` with `torsoName = "AGE11TY1"`; board it >=10 s after HopOut. **Needs an unlocked desktop** (input injection) | Done 2026-11-19 (locked session): install, ODF lines, no crash, stock walker unaffected. Open: twist gate, mouse = head, keys = legs, fire along head, slopes |
| MRU alias + menu probe (Nightingale steps 1-2) | #915, `agent/mru-menu-probe` (base #912) | `Docs/MRU_CLASS.md` live checklist | `svmruprb` / `svmruprn` test ODFs. **Needs an unlocked desktop** | Done 2026-11-19: install, class build, menu-probe decision log, absent-section copy, kill switch. Open: menu visuals, picks 7/8/9 consumed with order unchanged, stock Follow/Go To, other units' menus, mixed selection |
| Daywrecker AI defence v1 | #917, `agent/daywrecker-ai-defence-v1` (base #913) | `Docs/DAYWRECKER_AI_DEFENCE_RESEARCH.md` section 4 (9 rows) | `DaywreckerDefence=1`, SP; Armory DW drops near AI units; needs a Comet (`radarmsl`) source for row 7 | Not started. Open: all 9 rows, incl. kill rate under 30% deciding the gravity lead |
| MRU gameplay (Nightingale steps 3-6) | #918, `agent/mru-full` (base #915) | `Docs/MRU_CLASS.md` live checklist (23 steps) | `MruGameplay=1`, SP; `repamine`/`ammomine` pod ODFs loadable; damaged and low-ammo friendlies near a deployed MRU | Not started. Open: pod build inside Simulate, pod pickup, deploy hold, gauge drain, ammoPer*=0, AI re-order packing; non-combat steps 18-23: no Attack in menu, group attack skips MRU, no target picks, Hunt ignored |
| Unit loadouts M1 | #919, `agent/unit-loadouts` | `Docs/UNIT_LOADOUTS.md` live checklist (12 items) | `UnitLoadouts=1` and `[ProducerBuildMenus] Enabled=1`, SP; Armory built; Recycler or Factory selected | Not started. Open: Alt+pick reaches PRODMENU, greyed entries clickable, surcharge display/charge/refund, swap at FinishBuild, unfitted credit, reset on mission change without EXU |
| Lobby Briefing overlay | #921, `agent/lobby-briefing` | `Docs/LOBBY_BRIEFING.md` live checklist | MP lobby as host and as client; a mission with `.des` pages and one without | Not started. Open: button greyed with no `.des`, paging/Esc, lobby state untouched on close, "kick while open" (does a stock alert draw under the panel?) |

## Merge order once tests pass

#900, then #903, then #907 (each is stacked on the one before). #901, then #902.
