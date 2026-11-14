# AI DoSubTask hooks missed the stock Friend/Enemy subclasses (2026-11-03)

Symptom: with `OPENSHIM_TRACE_AI_RANGE=1`, the lcbench turret runs
(`turret_charge_range_cache_20261103.md`) logged no `[AIODF] Retarget probe`
lines at all, although the retarget hooks reported installed.

## Cause

`ai_odf_tuning.cpp` replaced slot 11 (DoSubTask) only in the base process
vtables (TankProcess, GunTowerProcess, ArtilleryProcess, ...). Each
`*Friend`/`*Enemy` AI subclass has its own vtable copy, and stock ODFs name
those subclasses in `aiName`/`aiName2`:

| Evidence | Source |
|---|---|
| Stock howitzer uses the subclasses | CR `avartl.odf` lines 9-10 (`ArtilleryFriend` / `ArtilleryEnemy`) |
| Stock turret uses the subclasses | stock `bzone.zfs` `avturr.odf` (`TurretTankFriend` / `TurretTankEnemy`) |
| Other stock units (tanks, scouts, soldiers, walkers, bombers, gun towers) | UNVERIFIED per ODF; the class pattern and the zero probe lines are consistent with it |

So four things never ran for stock units:
- the global 0.75 s retarget;
- ODF `retargetPeriodAI`;
- the AttackReveal post-subtask reveal (called from the same hooks);
- the undeployed-howitzer SNIP retaliation fix. Its vtable check compared only against the ArtilleryProcess base.

## Subclass vtables (GOG exe, bzr-ghidra `read_bytes` at vtable + 0x2C)

The RTTI type descriptor names are `.?AV<Class>@@`. Slot 11 holds:

| Class | Friend vtable | Enemy vtable | Slot 11 (both) |
|---|---|---|---|
| GunTower | 0x0087A794 | 0x0087A9A0 | `80 87 4E 00` = 0x004E8780 GunTowerProcess::DoSubTask |
| Tank | 0x0088B088 | 0x0088AEA8 | `20 35 58 00` = 0x00583520 OffensiveProcess::DoSubTask |
| RocketTank | 0x0088AC8C | 0x0088A7DC | 0x00583520 |
| Scout | 0x0088AD7C | 0x0088AAAC | 0x00583520 |
| Person | 0x00885BE4 | 0x00885A74 | 0x00583520 |
| Soldier | 0x00887E08 | 0x00887EF8 | 0x00583520 |
| Artillery | 0x00876204 | 0x00876114 | 0x00583520 |
| Gech | 0x0087A04C | 0x0087A268 | 0x00583520 |
| Bomber | 0x0088A9BC | 0x0088A8CC | 0x00583520 |

The TurretTank subclasses are in the turret note. Wingman has no subclasses,
and no `OffensiveFriend` symbol exists. The inline detours (AttackTask
DoState, RecycleTask GotoScrap, CalcRange(Craft)) already cover every subclass.

## Fix

- Rows `<Class>FriendVtable` / `<Class>EnemyVtable` are in `scripts/patches.json`.
- The retarget installer hooks slot 11 of each one after the same RTTI-name and current-slot checks as the base vtables.
- The turret Friend/Enemy slots now use the full TurretTankProcess hook: range refresh, reveal, then retarget.
- `IsArtilleryProcessVtable` accepts ArtilleryFriend/Enemy for the howitzer fix.
- The global 0.75 s retarget is now single player only. It was not gated before, but it was also inert for stock units.

## Live check (GOG, windowed, `run_lcturret.ps1 -RunSeconds 75`, 170 m)

- `openshim.log` shows `Global retarget upgrade active period=0.75 classes=30` and one `Installed <Class>::DoSubTask vtable hook` line per subclass, at the slots in the table above.
- 24 `Retarget probe` lines for avturr/svturr (TurretTankFriend/Enemy); the earlier runs logged none.
- The turret range refresh still fires (`range=155.00->299.00`). First hit at T+12.82; the svturr is destroyed at T+18.14 (earlier: T+12.9 / T+18.1).
- lcbench has no other AI units, so the tank, scout and other subclass hooks are confirmed installed but not seen running. Re-acquire time was not measured (UNVERIFIED).
