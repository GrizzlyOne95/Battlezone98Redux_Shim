# LockAllies(true) in Start() is lost -- 2026-11-23

GOG 2.2.301 (`battlezone98redux.exe`, base 0x00400000). Patch
`src/patches/ally_lock_keep.cpp`, `[Network] AllyLockSurvivesStart` (default on).
Addresses verified by byte scan of the GOG exe and by Ghidra decompile
(`/battlezone98redux.exe-007c64`), cited per finding. Where Start() runs inside
sim startup (mission load or post load) is not pinned in the decompile; the live
Stock arm shows the lock is gone after it.

## Bug
A co-op mission calls `LockAllies(true)` in `Start()`, yet Y/U still ally/unally.
Calling it later works. 1.5 honoured it from Start().

## Findings
- Lua "LockAllies" (string 0x0087C7B4), table 0x00871E38, handler 0x00501CB0 ->
  0x005C9450 -> setter 0x0046CE10: `DAT_0260D5EC = arg`.
- Readers: getter 0x0046CE40; Y/U handler 0x0046CD10 (nothing happens when nonzero).
- 0x0046CC80 (void cdecl, no args) creates the ally editor in DAT_0260D184 and writes
  the gate to 0 (0x0046CCED). Decompile `FUN_0046cc80`: `DAT_0260d184 = FUN_008231c0(&local_50);`
  then `DAT_0260d5ec = 0;`.
- Network startup 0x0056FD20 calls it at 0x00570170 (intended per-game reset; kept).
  Its only caller is 0x00572380, whose only caller is post load `FUN_00617110` (call at
  0x006171AB, after "Sim Startup: Initializing Game Simulation Network Part 1"). So every
  net-game sim startup clears the gate before the rebuild, and keeping the gate across the
  rebuild cannot carry one mission's lock into the next.
- UI rebuild 0x00681DF0, for `state != 9 && state != 2 && FUN_00572A70()` (net game),
  calls 0x006246D0, 0x0046CE20, 0x00624210, then 0x0046CC80 (E8 at 0x00681E2A).
  Decompile `FUN_00681df0`: `if ((iVar1 != 9) && (iVar1 != 2)) { iVar1 = FUN_00572a70();`
  `if (iVar1 != 0) { FUN_006246d0(); FUN_0046ce20(); FUN_00624210(); FUN_0046cc80(); }`.
  Callers include sim startup 0x006185F0 (call at 0x00618955, after mission load and
  Start()), so the Start() lock is zeroed. Decompile `FUN_006185f0`: mission load
  `FUN_00616fc0()` / `FUN_006170a0()`, post load `FUN_00617110()`, first frame, then at the
  end `DAT_009183dc = 1; FUN_00681df0();`.

## Fix
REL32 patch "Ally Lock Survives UI Rebuild" on 0x00681E2A. Wrapper saves the gate,
runs 0x0046CC80, restores the gate. Resolves `AllyEditor::Init` 0x0046CC80 and
`AllyLock::Gate` 0x0260D5EC (operand of the setter's `mov [gate],eax`). Fails closed
if the call target does not match. Log tag `[ALLYLOCK]`. Kill switches
`OPENSHIM_DISABLE_ALLY_LOCK_SURVIVES_START` / `BZR_DISABLE_ALLY_LOCK_SURVIVES_START`.

Signatures (all unique in the GOG exe): call-site 1 match at 0x00681E2B; gate 1 match
(operand 0x0260D5EC at 0x0046CE17); init 1 match at 0x0046CC80.

Live test (2026-11-23, GOG, 2-client CR co-op, `Run-BZRMpBugs.ps1 -Case LockAllies`):
- Stock arm (`AllyLockSurvivesStart=0`): on both clients, U and Y open the ally box
  despite `LockAllies(true)` in Start(), and no `[ALLYLOCK]` line is logged. This reproduces the report.
- Fixed arm: on both clients, U and Y stay shut. The log shows `[ALLYLOCK] ... redirected site=0x00681E2A` and
  `restored LockAllies gate=1`.
- Controls, both arms, both clients: unlocked, U and Y open the box; a later `LockAllies(true)`
  keeps them shut.
