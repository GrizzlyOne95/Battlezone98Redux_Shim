# Backlog address audit, 2026-07-08

Source docs:
- `C:\Users\iestu\Documents\ExtraUtilities\FeaturesToLookInto.txt`
- `C:\Users\iestu\Documents\ExtraUtilities\BZR_End_User_Experience_Priority_Backlog_FULL.md`
- `C:\Users\iestu\Documents\ExtraUtilities\BZR_Shim_EXU_Ownership_and_Config_Strategy.md`
- `C:\Users\iestu\Documents\ExtraUtilities\BZR_Stock_Normal_Player_Priority_Backlog.md`

Live target:
- `battlezone98redux.exe play01.bzn`
- Runtime title: Battlezone 98 Redux 2.2.301
- Live PID used for this pass: `35252`

## Corrections applied

### Original #14 / Priority 25: team filters for shield towers and mines

`winmm_shim.log` showed that the shield tower and proxmine team-filter hooks
were failing safe because the vtable slot constants pointed at neighboring
base-class virtuals, not the class `Simulate` entries.

Corrected in `src/patches/bzr_hooks.cpp`:

| Hook | Old slot | Live slot | Expected target |
| --- | ---: | ---: | ---: |
| `ShieldTower::Simulate` | `0x00887728` | `0x00887724` | `0x005D0D80` |
| `ProximityMine::Simulate` | `0x00886234` | `0x008862B4` | `0x005B0E40` |

Live evidence:

```text
0x00887720: 80 BC 4D 00 80 0D 5D 00 A0 78 41 00 ...
                         ^ 0x00887724 -> 0x005D0D80

0x008862B0: 80 BC 4D 00 40 0E 5B 00 A0 78 41 00 ...
                         ^ 0x008862B4 -> 0x005B0E40
```

The magnet mine slot was already installed in the live run:

```text
0x0087D574 -> OpenShim hook 0x6EFB1940
```

After rebuilding and deploying the corrected Release `winmm.dll`, the
validation launch confirmed all three hooks install:

```text
[SHIELDODF] Installed ShieldTower team filter hook slot=0x00887724 original=0x005D0D80
[MAGNETODF] Installed MagnetMine team filter hook slot=0x0087D574 original=0x0050C650
[PROXODF] Installed ProximityMine team filter hook slot=0x008862B4 original=0x005B0E40
```

## Revalidated addresses

### Original #46A / Priority 11/25: splinter undead spraybuilding fix

Status: address OK, hook installed in live run.

| Item | Address / slot | Live evidence |
| --- | ---: | --- |
| `SprayBuilding::Simulate` | `0x005DA6E0` | Entry bytes match `55 8B EC 81 EC E8 02 00 00 ...` |
| SprayBuilding simulate vtable slot | `0x00888228` | Slot points to OpenShim hook `0x6EFC7F70` |

### Original #47 / Priority 12/26: constructor remote-build-after-death cleanup

Status: address OK, hook installed in live run.

| Item | Address | Live evidence |
| --- | ---: | --- |
| `AI_UnitRemove` | `0x0068FC60` | Entry starts with OpenShim detour `E9 2B 73 8F 6E ...` |

### Original #18 / Stock priority 52: turret aim pitch range

Status: configured bytes still match live Steam.

| Item | Address | Live bytes |
| --- | ---: | --- |
| `TurretCraft Aim Pitch Multiplier` | `0x005F1838` | `F3 0F 10 05 84 25 8A 00 ...` |
| `TurretTank Aim Pitch Multiplier` | `0x005F561A` | `F3 0F 10 05 84 25 8A 00 ...` |

## Corrected after initial audit

### Original #43/#44 / Priority 22/23: AI ODF range tuning

Status: corrected after mapping the current Redux caller in `UnitTask::Execute`.

Old OpenShim advisory:

```text
0x0041F240
```

Old live bytes:

```text
45 D8 89 45 C8 68 B4 2C CC 02 8B 4D C8 51 8B 4D
```

That address is inside an existing function body, not a callable function entry,
and the startup log confirmed the hook disabled itself:

```text
[AIODF] CalcRange(Craft) entry bytes mismatch at 0x0041F240; AI ODF range tuning disabled
```

Current mapping:

| Function | Address | Live entry bytes |
| --- | ---: | --- |
| `CalcRange(Craft*)` / `FUN_00466BE0` | `0x00466BE0` | `55 8B EC 83 EC 1C 8B 45 ...` |
| `CalcRange(Weapon*)` / `FUN_00466890` | `0x00466890` | `55 8B EC 83 EC 20 8B 45 ...` |

Evidence:
- Legacy exact decompile maps `UnitTask::Execute` calling
  `CalcRange(Craft*, &close, &range, &time, &weapon)`.
- Current Redux `UnitTask::Execute @ 0x006002A0` calls
  `FUN_00466BE0(local_8[4], &local_c, &local_10, local_8 + 0x29, local_8 + 0x2d)`.
- `FUN_00466BE0` loops weapon slots, calls `FUN_00466890` for weapon range,
  writes close/range/time/weapon, and subtracts `1.0` from final range, matching
  the legacy `CalcRange(Craft*)` shape.
- The detour length must be `9` bytes, not `8`: the first whole-instruction
  sequence is `55 8B EC 83 EC 1C 8B 45 0C`. A crash dump from
  `C:\BZDumps\battlezone98redux.exe.22332.dmp` confirmed that the 8-byte test
  split `8B 45 0C`, causing execution to fall into invalid trampoline bytes at
  `0x0392000D`.

Validation after the 9-byte fix:

```text
0x00466BE0: E9 ... 90 90 90 90
[AIODF] Installed CalcRange(Craft) hook entry=0x00466BE0 trampoline=0x03AF0000
```

Remaining work for this hook is gameplay validation with ODFs that exercise
`engageRangeAI`, `weaponRangeMinAI`, and derived bomber stand-off values.

### Original #43/#44 / Priority 22/23: AI retarget timing

Status: active and installed in live runs.

| Hook | Address | Live evidence |
| --- | ---: | --- |
| `OffensiveProcess::DoSubTask` | `0x004DFE70` | Entry starts with OpenShim detour `E9 ...` |
| `GunTowerProcess::DoSubTask` | `0x004741A0` | Entry starts with OpenShim detour `E9 ...` |

These are good anchors for `retargetPeriodAI`; range/weapon-min now routes
through `CalcRange(Craft*) @ 0x00466BE0`.

## Address-ready next targets

These are high-priority backlog items with live or near-live anchors ready for
implementation work:

1. Original #14: shield/prox/magnet team filters.
   - Shield and prox slot corrections are now in code.
   - Rebuilt, deployed, and launch-confirmed installed.
2. Original #43/#44: AI ODF tuning.
   - Retarget hooks and `CalcRange(Craft*)` are installed.
   - Scavenger live anchors are in `play01_live_ai_scan_notes_20260708.md`.
   - Next unresolved hook work is scavenger scrap scoring and stuck timing.
3. Original #46A: splinter undead fix.
   - Hook is installed; gameplay repro validation remains.
4. Original #47: constructor death cleanup.
   - Hook is installed; gameplay repro validation remains.
5. Original #18: turret aim pitch.
   - Address bytes match; needs gameplay verification and ODF/config policy.
