# RTS build queue (`[Gameplay] RtsBuildQueue`)

Default **off**, single player only. Source: `src/patches/rts_build_queue.cpp`, rules in
`include/rts_build_queue_policy.h`, badge text in `src/patches/producer_badges.cpp`.

## Behaviour

Applies to the **Recycler and Factory** only (not the Construction Rig, not the Armory).

- Picking a build item while the producer is busy adds it to that producer's queue (no modifier).
  "Busy" is the producer's build class `*(obj+0x300) != 0`, **or** its queue is non-empty (so the
  order of picks is kept). Picking while idle with an empty queue is stock (builds at once).
- Caps: 10 entries per producer, 16 producers with a queue. A pick into a full queue (or with no
  free producer slot) plays the stock `mnu_buzz.wav` and does nothing else.
- Shift+pick (Shift held, the stock multi-select modifier `cmd_multi`, Ctrl by default, clear)
  removes the **last** queued entry of that same item. If that item is not queued, the pick runs
  stock.
- Drain: on the frame thread (`RunDeferredSceneMutations`; inline from the world render tick only
  while the scene-mutation drain is not installed), at most every 250 ms, for each producer with a
  queue: when `+0x300 == 0` and the team can pay the front entry (see below), pop it and call the
  **original** `Producer::SetActiveMode` (not the hook, so it does not queue again). At least 500
  ms between two issues for one producer. Otherwise the entry waits. Scrap is charged when each
  item starts, as stock does.
- Cleared on mission load/reset (feature registry revert), when the option turns off, in a network
  game (feature registry MP gate, refreshed every 250 ms), and when the producer dies, vanishes,
  changes team or is a network replica (checked by handle in the drain, as `producer_badges.cpp`).
- Not saved: a save/load drops the queues.

### Badges (only when `RtsProducerBadges` is on)

- A building producer's label gets ` +N` for N queued entries (`Tank 45% +2`).
- The badge scan includes an idle producer that holds a queue. If its next entry cannot be paid
  (scrap or pilots) the badge reads `<next item name> waiting for scrap` (localization key
  `openshim_ui:rts_build_queue_waiting`, 7 languages). It stays hidden while the next entry is
  affordable (the drain issues it within a quarter second). The query is
  `RtsBuildQueueBadgeQuery` (game thread).

## Engine facts

GOG Redux 2.2.301, verified in Ghidra (bytes read 2026-11-17).

- `Producer::SetActiveMode` 0x005AEAB0 (vtable slot 11 for Recycler and Factory): modes 0xb, 3 and
  0x17 are other commands; a mode below 0x1b goes to FUN_004a8560; a mode >= 0x1b is a build pick
  and calls `SetCommand` 0x004DBF90(this, 0x15 /*CMD_BUILD*/, mode, 0). So for a build pick `mode`
  **is** the `GameObjectClass*`.
- `producer_build_menu.cpp` already replaces slot 11 with `ProducerSetActiveModeHook`. The queue
  sits after `TryHandleProducerMenuMode` (PRODMENU's nested-page modes) and before the original:
  `if (mode >= 0x1b && RtsBuildQueueOnPick(self, mode)) return true;`. The Construction Rig hook is
  untouched.
- `Producer::StartBuild` 0x005AECB0 (affordability): team number `*(int*)(obj+0x174)`, `Team*`
  `*(void**)(obj+0x17C)`, scrap cost `FUN_004E1B90(teamNum, cls)` (cdecl, difficulty-adjusted),
  pilot cost `FUN_004E1C10(teamNum, cls)` (cdecl); team scrap `*(uint32_t*)(team+0x16C) ^
  0x33333333`, team pilots `*(int*)(team+0x174)`. It builds only if `scrapCost <= scrap` and
  `pilotCost <= pilots`. The queue repeats exactly that test before issuing.
- Liveness (as `producer_badges.cpp`): vtable is `RecyclerVtable`/`FactoryVtable`, team equals the
  user's team, byte `+0x80 != 2` (not a replica), obj76 (`+0xF4`) flags `+0x14` lack `0x200`. Raw
  reads are SEH-guarded.
- `Producer::UpdateModeList` 0x005AE660 (slot 23), deployed state 2: each build entry is enabled only if the producer is not building (`FUN_004723d0`, `+0x300 != 0`), scrap and pilots cover it and `TeamFirstEmptySlot` 0x005E0F90 finds a unit slot (FUN_005ae660.c lines 59-77). So stock greys every build entry while building and the pick never reaches `SetActiveMode`. After PRODMENU's `ProducerUpdateModeListHook`, `RtsBuildQueueAfterUpdateModeList` sets the enabled bit (ModeList `+0x2C`, one bit per slot, `ModeList::SetMode` 0x0046FA60) again for slots 1-9 holding a class while the producer builds, unless the class has no free unit slot (`OffenseOverflowBuildGate`: the same gate the stock call site sees, so `ExtendedUnitCap` opens a full offense range that can auto-group). Menu stubs keep PRODMENU's own state.
- Item names: `KillTicker::LookupUnitName` on the class ODF (`char[8]` at class `+0x30`), cached in
  the badge module.

## Hook sites (`scripts/patches.json`, `engine_addresses`)

| Row | Address | Verified bytes |
|---|---|---|
| `BuildScrapCost` | 0x004E1B90 | `55 8B EC 83 EC 0C 8B 45 0C 8B 48 48 89 4D FC E8` |
| `BuildPilotCost` | 0x004E1C10 | `55 8B EC 83 EC 08 8B 45 0C 8B 48 50 89 4D FC E8` |
| `TeamFirstEmptySlot` (existing row) | 0x005E0F90 | bound by `OffenseOverflow` too |

Plus the existing `GameObjectHandleGetObj`, `InputHeldModifierKeys`, `CommandMenuUnitBranchInput`,
`RecyclerVtable`, `FactoryVtable` and the stock `ProducerSetActiveMode` bound by PRODMENU
(`PlayGlobalSound` is optional: without it the refuse buzz is silent). If any fails to bind the
feature stays inert, the option is marked unavailable (`MarkOptionHookFailed`) and the log says so.

**Needs `[ProducerBuildMenus] Enabled = 1`**: the pick hook is PRODMENU's `SetActiveMode` vtable
hook, which is only installed with that option. The queue checks on every refresh that vtable slot
11 (+0x2C) of both the Recycler and Factory vtables holds that hook; if not the option shows
"Unavailable: needs [ProducerBuildMenus] Enabled = 1" and the queue stays off.

## Limits

- No unit-cap wait: the stock `StartBuild` may refuse for reasons other than scrap and pilots
  (e.g. a unit cap); a queued entry is popped when it is affordable and handed to the stock pick,
  and what happens after that is stock's.
- Not saved.
- A second pick before the first pending `CMD_BUILD` is processed (`+0x300` still 0) follows stock:
  it is not queued and replaces the pending command. The drain keeps 500 ms between issues for
  the same reason.
- A stale badge name for up to ~200 ms right after an item finishes (the badge scan is 5 Hz); the
  waiting badge hides itself when the name no longer matches the queue's next entry.
- Mission scripts that call `SetCommand`/`Build` directly bypass the queue.
- A plain order for the producer (Stop, Go and the other `SetActiveMode` modes 0x17, 0xB, 3) drops
  its queue (`cleared ... (plain order)`). The drain only issues when the producer's command
  (`+0xCC`, nextCmd.what) is 0 or 0x15 (build).
- The drain skips a whole pass while the player object or its team cannot be read (load or
  transition); queues are cleared only when the producer itself is gone, dead, a replica or on
  another team.
- After the last queued entry is issued the producer counts as busy for 500 ms (`+0x300` is set a
  few frames later), so a pick in that window is queued, not stock.

## Log lines (`[BUILDQ]`, budgeted, reset on mission reset)

`rows bound`, `engine rows did not bind; build queue inert`, `install complete|gave up`,
`active=<0|1> (option, hooks, single player)` (change-only), `queued handle= class= depth=`,
`removed handle= class= left=`, `refused (full) handle= class= depth=`, `refused (no free producer
slot)`, `issued handle= class= left=`, `cleared handle= entries= (<reason>)` / `cleared all`.

## Live test checklist (not yet run)

1. Option on, SP mission: start a unit in a Factory, pick two more: the log shows `queued`, the
   build continues; each starts when the previous finishes and the scrap drops then.
2. Pick an 11th: buzz, no change. Shift+pick an item queued twice: the last copy goes.
3. With `RtsProducerBadges` on: the badge reads `... +2`; with too little scrap, the idle Factory
   reads `<item> waiting for scrap` until scrap arrives.
4. Kill the Factory, reload the mission, or turn the option off: the queue is gone.
5. Construction Rig and Armory picks stay stock.
