# AI turret weapon range is cached at Init/PostLoad only (2026-11-03)

Symptom: an AI turret (for example an avturr carrying a MAG / charge gun) does not
engage at the weapon's long charged-shot range until a pilot swap rebuilds its AI
process.

Corpus: `Battlezone_Source\BZ1\Redux\openshim_re_corpus\bzr_gog_best_effort\ghidrecomp\results\bins\battlezone98redux.exe-6777ca\decomps\`
(GOG Redux exe). The line numbers below are lines in `FUN_<addr>-<addr>.c` there. The
addresses were confirmed in the shipping GOG exe through the bzr-ghidra bridge (bytes
below). No decompiler output is reproduced here.

## Root cause

| Claim | Source |
|---|---|
| TurretTankProcess Init seeds the outputs: time +0x70 = 1.0, close +0x68 = 0, range +0x6C = 150.0 (0x43160000), weapon +0x74 = 0 | `FUN_005f6b50` lines 17, 19, 21, 23 |
| Init then calls CalcRange(Craft) `FUN_00466be0(craft = this+0x34, +0x68, +0x6C, +0x70, +0x74)` | `FUN_005f6b50` lines 25–27 |
| Init derives +0x78 = range/time and +0x7C = time/range, then squares +0x68 and +0x6C | `FUN_005f6b50` lines 29, 31, 33, 35 |
| PostLoad repeats the same seed, call and derivation | `FUN_005f6d90` lines 15–31 (call at 21) |
| The cached squared range +0x6C gates target keep and target search | `FUN_005f6ff0` line 189 (keep current target only while dist² < +0x6C), line 211 (+0x6C is passed to the target search `FUN_00463240` at 213) |
| Other turret states compare against the same cached +0x6C | `FUN_005f7470` line 35; `FUN_005f7500` line 45 |
| UnitTask::Execute instead recomputes on weapon change: it calls `FUN_005fed30(craft)`, compares it with its cached copy (`local_8[0x30]`, i.e. +0xC0), and on a difference stores the new value and re-runs `FUN_00466be0` | `FUN_006002a0` lines 55, 57, 59, 61 |
| `FUN_005fed30` is a weapon signature: for each of the 5 weapon slots in the craft's weapon mask it XORs the weapon pointer, the current ordnance class (+0x0C) and the weapon class sig | `FUN_005fed30` lines 29, 31, 33, 35, 39 |

TurretTankProcess has no such check, so its range stays whatever CalcRange returned at
Init/PostLoad. A pilot swap rebuilds the process and so runs Init again.

Ghidra (GOG exe), checked this session:
- `0x005FED30` begins `55 8B EC 83 EC 14 C7 45 FC 00 00 00 00 8B 4D 08`. The single
  argument is the craft, read from `[ebp+8]`; the function ends in a plain `ret`, so it is cdecl.
- Turret process vtables (RTTI type descriptor names; slot 11 = `0x005F6FF0` DoSubTask in each):

| Class | Vtable | Slot 11 address |
|---|---|---|
| `.?AVTurretTankFriend@@` | `0x008895EC` | `0x00889618` |
| `.?AVTurretTankProcess@@` | `0x00889710` | `0x0088973C` |
| `.?AVTurretTankEnemy@@` | `0x008897F8` | `0x00889824` |

Stock avturr/svturr ODFs use `aiName = "TurretTankFriend"`, `aiName2 = "TurretTankEnemy"`
(stock `bzone.zfs` avturr.odf), so the Friend/Enemy vtables must be hooked, not only
TurretTankProcess.

## Charge guns and the signature

The current ordnance class is part of the signature (`FUN_005fed30` line 39), and a
charge gun steps its current charge level while the trigger is held (1.5
`ChargeGun::Simulate`, `BZ1\1.5\functions\0052\0052c82b_ChargeGun_Simulate.c` line 55).
So the signature changes with every charge level, and UnitTask's range follows the
charge. gmaggun levels are `charge1`..`charge6` (stock gmaggun.odf). Range = shotSpeed ×
lifeSpan: charge1 = 100 × 3.0 = 300 m, charge6 = 75 × 2.5 = 187.5 m (stock charge1.odf,
charge6.odf). Levels 1–3 reach about 300 m.

The charge fires only when the trigger is released (`ChargeGun::Simulate` line 42 is the
not-firing branch; line 161 builds the ordnance; lines 170–172 reset to the empty level).

The AI does have a charge release, in UnitTask::UpdateWeapon (an earlier version of this
note said no AI code calls IsChargeFull; that was wrong):

| Claim | Source |
|---|---|
| 1.5: the CHRG branch triggers while the charge is empty, stops triggering (so the charge fires) at the full level, and otherwise keeps charging only while a later level has a better damage-rate estimate | `BZ1\1.5\functions\0046\0046c63e_UnitTask_UpdateWeapon.c` lines 250, 251, 254–316, 374 |
| Redux `FUN_00604130` (UpdateWeapon, entry `55 8B EC 81 EC 84 02 00 00`) has the same branch: IsFiring `FUN_005fce20`, hold on `!fire` (vfunc +8), IsChargeReady `FUN_005fcd90`, IsChargeFull at 595 (Ghidra labels it `ShouldReceiveNotifications`; `005fcdc0` compares +0xE4 with +0xEC), level loop in 0x2C steps up to and including the full level, trigger only if a later level scores higher | `FUN_00604130` lines 575, 579–581, 585–589, 595, 667–747, 749–751 |
| The estimate ignores reach: no ordnance speed or lifespan is read in the loop | `FUN_00604130` lines 667–747 |
| A failed fire cone also holds the charge (vfunc +8) | `FUN_00604130` lines 899–903 |
| Callers include TurretAttack::DoState `FUN_005f8880` (vtable `0x008895B0` slot 12) and TurretBlastAttack::DoState `FUN_005f7cf0` (vtable `0x008896D4` slot 12) | Ghidra xrefs 0x005f8f42, 0x005f8f67, 0x005f7def; vtable data refs 0x008895e0, 0x00889704 |

## Fix (OpenShim, `AiOdfGameplayTuning`, single player)

`src/patches/ai_odf_tuning.cpp` hooks slot 11 of the Friend/Enemy vtables (the existing
TurretTankProcess hook gets the same call). Before DoSubTask runs, it reads
`FUN_005fed30(craft)`. When that differs from the value last seen for this process, it
re-runs Init's sequence (seed 0/150/1/null, CalcRange(Craft) through the existing
detour, then +0x78, +0x7C and the two squares). Rows `CraftWeaponSignature`,
`TurretTankFriendVtable` and `TurretTankEnemyVtable` are in `scripts/patches.json`.

## Live test (GOG, windowed, `reverse_engineering/run_lcturret.ps1`)

The lcbench world: a friendly avturr, with an enemy svturr N m away. At T+3 the avturr
gets `gmaggun` in its empty GC2 hardpoint.

| Run | Result |
|---|---|
| 170 m, AiOdfGameplayTuning = 0 | no range refresh lines; the avturr never targets the svturr in 30 s |
| 170 m, tuning on | `range=155.00->299.00` at the GiveWeapon frame; targets the svturr from T+11 and holds it to the end |
| 190 m / 195 m, tuning on | same targeting; range cycles 299 → 290 → 263 → 186.5 → 299 as the MAG charges and fires |

None of these first runs damaged the svturr, which was out of sight: the overlay then placed the
turrets along the player's heading without checking terrain. The overlay now picks the
heading (every 15°) whose muzzle-to-muzzle line, 2.5 m above each turret and sampled every
2 m with `GetTerrainHeightAndNormal`, clears the terrain by the most, and logs each health
drop as a HIT.

| Run (line-of-sight checked) | Result |
|---|---|
| `-EnemyGap 170` (170.0 m), tuning on | clearance 3.4 m; 7 hits from T+12.9, then the killing shot; svturr destroyed at T+18.1 |
| `-EnemyGap 210` (216.8 m in 3D; beyond the 187.5 m full-charge reach), tuning on | clearance 4.0 m; 8 hits from T+13.9, then the killing shot; destroyed at T+19.3 |

(These runs logged only the health drops before the kill; the overlay now also counts the killing shot.)

## Early release at the reaching level: tried, not needed

A test hook on `FUN_00604130` lowered the ChargeGun's full level (+0xEC), for one call
from a TurretAttack/TurretBlastAttack, to the highest level that reached the target
(range = ordnance +0x50 lifespan × +0x54 speed − 1, as `FUN_00466890` lines 165–167 and
CalcRange). At 216.8 m it ran only on `fire = 0` calls (64 of 64 traced), where stock
holds the charge anyway. A build with the hook off gave the same hits at the same times
(first hit T+13.87 vs T+13.88, destroyed T+19.26 in both). With a clear line of sight the
stock damage-rate estimate already lets the charge go at a level that reaches, so the
hook was dropped. The earlier "charges to full and falls short" reading came from the
runs without line of sight, where the fire-cone hold kept charging.
