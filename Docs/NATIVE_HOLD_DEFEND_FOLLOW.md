# Native Hold, Defend refresh and Follow-as-Formation (single-player AI)

Status: implemented behind opt-in toggles. Single-player only. Every one of them is reset at mission end.
Evidence: shipping GOG `battlezone98redux.exe` (Ghidra project binary `battlezone98redux.exe-007c64`,
read with Ghidra decompile, Ghidra read_bytes and capstone), plus the BZ1 1.5 decompile in
`Battlezone_Source/BZ1/1.5/functions/`. Addresses are shipping GOG addresses unless marked "1.5".

## Why the stock orders misbehave

| Order | Stock behaviour | Evidence |
|---|---|---|
| Defend (target) | While in DEFEND, `OffensiveProcess::DoSubTask` asks `ShouldAttack(DEFEND)`, which is `WaitVsAttack`, an engageRange distance test. Passing it switches the unit to SUBATTACK, so it chases. A recent attacker ('PINS' within 3 s) forces SUBATTACK without any test. | 1.5 `0044e334_OffensiveProcess_ShouldAttack.c:31-35`, 1.5 `0044e153_OffensiveProcess_WaitVsAttack.c:18`; GOG `0x583520` DoSubTask |
| Defend (moving target) | Two things make units lag. The DefendTask wander point is fixed for 10 s (`+0x120 = now + 10`). In state 2 the goto follows a path built once to a snapshot of the target's position (`+0x28`). | GOG `0x4b0ff0` InitState (state 6), `0x4b1250` DoState, `0x601070` InitGoto (the path at `+0x40` is built only when it is null) |
| Follow | `OffensiveProcess::ChangesState` sets followRange `+0x6c = [0x8A2E20]` (15625 = 125²) for CMD_FOLLOW. FriendFollowVsAttack then fires, and the unit chases and leaves. Formation leaves followRange at 0, so the unit stays in FollowTask state 4 and runs FollowTask's fire block at the closest enemy. | GOG `0x5833a0` movss at `0x5833CA` (`f3 0f 10 05 20 2e 8a 00`, then `f3 0f 11 41 6c` = store to `+0x6c`); 1.5 `0044e1d9` FriendFollowVsAttack |
| Hold | Does not exist in BZR. CMD_DEFEND with `who == 0` already builds a `SitTask` (stands still), but DoSubTask still switches it to SUBATTACK. | GOG `0x5fbb80` InitDefend; 1.5 `00469d44_UnitProcess_InitDefend.c`; 1.5 `0045fed5_Defend.c` (script `Defend(h, prio)` issues CMD_DEFEND with who = 0) |

Script `Defend()` only writes `GameObject::nextCmd` (1.5 `0049550f_GameObject_SetCommand.c`). The task changes on a later process tick.

CMD_DEFEND = 0xF. It maps to process state 9: `UnitProcess::ChangesState` `0x5fad00`, case 0xF sets `+0x20 = 9`.

## 1. Follow uses Formation rules

Patch the 4-byte constant address at `0x5833CE` from `20 2E 8A 00` (→ 15625.0) to `98 24 8A 00`.
`[0x8A2498]` is 0.0 (read_bytes). Check the expected bytes before writing.
Write it while the toggle is active and restore it otherwise.

The site is shared by every process vtable whose slot 9 resolves to `0x5833a0`:
- directly: Artillery, Gech, Person, Offensive;
- through `0x613a40`: Bomber, RocketTank, Scout, Tank, Wingman.

Soldier (`0x5d7800`) and GunTower/TurretTank (`0x5fad00`) are unaffected.

## 2. Defend refresh

Wrap DefendTask::DoState. That is vtable `0x8785F4` slot 12 (`0x4b1250`), RTTI `.?AVDefendTask@@`, thiscall with no args.
Call stock first, then work on the task `t`:

| Field | Offset |
|---|---|
| state | `t+8` |
| next state | `t+0xc` |
| me | `t+0x10` |
| target handle | `t+0x14` |
| target object | `t+0x18` (refreshed by stock) |
| goal | `t+0x28` |

- **State 6 (wander).** Shift `+0x28` by the target's xz movement since the last tick. The wander point then stays relative to a moving target. DoWander steers toward `+0x28`.
- **State 2 (goto).** This runs at most once per second per task. If the live target is more than 15 m (2D) from `+0x28` and `next == 2`, set `next = 6`.
  - This is a transition stock already makes (2→6 on arrival).
  - CleanState `0x4b1210` calls CleanGoto `0x601200` for state 2, freeing the old path.
  - InitState 6 then picks a point around the live target, and the next state-6 tick re-snapshots and re-paths.
- A side table keyed by task pointer stores the last target position and the last repath time. It is cleared at mission end, and an entry is reset when the target handle changes.

## 3. Hold (BZ2 SitAttack equivalent)

1. The caller issues `Defend(h, 0)` (CMD_DEFEND, who = 0 → SitTask). It then calls `OpenShimSetAiHold(h, TRUE)`, which records the handle.
2. **Held test.** A craft is held when all of these are true:
   - the handle is in the table;
   - `GetObj(h)` is the craft;
   - its process state `+0x20 == 9` (DEFEND);
   - process who `+0x3c == 0`.

   Entry lifetime:
   - An entry stays pending for up to 3 s while the queued command is applied.
   - Once seen held, the entry is dropped as soon as the test fails (a new order was given).
3. **SitTask::DoState hook.** Vtable `0x889F50` slot 12 (`0x608630`, which is `DoSit 0x602420` only), RTTI `.?AVSitTask@@`.
   - Run stock.
   - For held craft (`t+0x10`), also run the FollowTask fire block copied from FollowTask::DoState `0x4d3b80` at `0x4d3e49..0x4d3fd4`.
   - SitTask is a `UnitTask`, so the fields are shared. SitTask has no InitState override (slot 10 = base `0x417c60`).
   - SitTask is built by about 11 other call sites, so the hook acts only on held craft.
4. **No chasing.** `OffensiveProcessDoSubTaskHook` returns false before calling stock when the process's craft (`process+0x34`) is held. This also blocks the 'PINS' attacker path.

### FollowTask fire block (GOG `0x4d3e49`–`0x4d3fd4`)

```
c = thiscall 0x417ca0(me); if !c → skip                      // me = [t+0x10]
if !thiscall 0x417fb0(thiscall 0x417ca0(me)) → skip
if [[[t+0xb4]+8]+0xc] == 'DISP' (0x44495350) → skip
range = [t+0xa0]
enemy = cdecl 0x463240(me, &range); if !enemy → skip          // add esp,8
saved = [t+0x18]; [t+0x18] = enemy
able = thiscall 0x603ad0(t)                                  // bool
v = cdecl 0x4462d0(&out, [t+0x98]*0.5 - 0.5, vec3 by value [t+0xe4..0xec])   // add esp,0x14
thiscall 0x607110(t, t+0xc8, &v)                             // LookAtLocalPos
if !thiscall 0x608460(t):
    fire = able && !cdecl 0x462b60(me, range, 0.3f, 1.0f)    // MayHitFriends, add esp,0x10
    thiscall 0x604130(t, fire)                               // UpdateWeapon (1 stack arg)
else if thiscall 0x608490(t): thiscall 0x6084c0(t)           // UNVERIFIED meaning
[t+0x18] = saved
```

The constants are `[0x8A2584]` = 0.5, `[0x8A2558]` = 0.3 and `[0x8A2604]` = 1.0 (read from the exe).

### Known limits

- The Hold table is not saved. After a load, a held unit becomes a plain SitTask idle (stands still, chases). The mission can re-arm it.
- These features are inactive in multiplayer.
