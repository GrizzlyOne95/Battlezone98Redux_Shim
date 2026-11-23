# Howitzer attack approach

`[SinglePlayer] HowitzerAttackApproach` (default OFF, read at startup).
Source: `src/patches/howitzer_attack_approach.cpp`. Log tag `[HOWAPPR]`.
Options row: RTS Commands > "Howitzer Approach" (restart required; the
Gameplay screen is full at 16 rows).

Addresses are from the shipping GOG 2.2.301 exe. Each behaviour claim cites
the private ghidrecomp corpus (`bzr_gog_best_effort/.../decomps`), file
`FUN_<addr>-<addr>.c`, by line number. Function entry bytes are pinned in
`scripts/patches.json`; vtable slot contents were dumped from the exe.

## Problem

Order a stock howitzer (class Howitzer, e.g. avartl/svartl) to attack a target
beyond its shell arc and it says "out of range" and goes idle. It never moves:

- `ArtilleryProcess::InitAttack` 0x00475AF0 deploys at once and sets the
  30 s attack timeout (`FUN_00475af0` lines 13-17).
- `ArtilleryProcess::DoAttack` 0x00475B30 takes the first mounted weapon
  (lines 489-497), and for a `MORT` weapon (line 561) runs the reach test
  0x0056B1C0 (line 573); on a miss it says 0x13 and sets state 3 (idle)
  (lines 575-581, again at 809-819). It never writes throttle or reads the
  task at +0x38.

## Addresses (GOG 2.2.301)

| Item | Address | Notes |
|---|---|---|
| ArtilleryFriend vtable | 0x00876204 | slot 11 DoSubTask 0x00583520, 15 InitGoto 0x00475A30, 16 EndGoto 0x005FB720, 17 DoGoto 0x005FB770, 24 InitAttack 0x00475AF0, 25 EndAttack 0x00417C60, 26 DoAttack 0x00475B30 |
| ArtilleryProcess::DoAttack | 0x00475B30 | hooked on the ArtilleryFriend vtable only (row `ArtilleryProcessDoAttack`) |
| EndAttack (shared empty fn) | 0x00417C60 | row `GameObjectDeselect`; hooked on the ArtilleryFriend vtable only |
| UnitProcess::InitGoto | 0x005FB500 | row `UnitProcessInitGoto` |
| GotoTask vtable | 0x0087A61C | row `GotoTaskVtable`; RTTI `.?AVGotoTask@@` checked at install; slot 6 done 0x004714B0, slot 7 execute 0x006002A0 |
| Weapon ballistic reach | 0x0056AF20 | row `WeaponBallisticReach`; thiscall(ECX = weapon)(float* outTime, const VECTOR3* target, char highArc), ret 0xC, AL = reachable |
| Howitzer craft vtable | 0x0087AD70 | slot 24 Craft::Deploy 0x004AE2B0, slot 25 Craft::Packup 0x004AE330 |
| ArtilleryFriend ShouldSwitch | 0x00476F90 | vt+0xE8; not hooked, cited below |

Slot mapping (state machine 0x005FA6E0): state n uses Init 3n+3, End 3n+4,
Do 3n+5, so attack (7) is 24/25/26 and goto (4) is 15/16/17. Note: slot 16
is EndGoto, not DoGoto: `FUN_005fb720` deletes the task and zeroes +0x38
and +0x10 (lines 9-17); DoGoto is slot 17, `FUN_005fb770`: if task vt[6]
(done) it clears +0x10 and goes idle, else calls task vt[7] (lines 13-31).

Fields: process +0x20 pending state, +0x34 craft, +0x38 task, +0x3C target
handle, +0x68 engage range, +0x7C attack timeout. Craft +0xAC current command
(4 = ATTACK; `FUN_00475b30` line 393), +0x1A0 weapon carrier, +0x228 deploy
state (0 packed, 1 deploying, 2 deployed, 3 packing), +0x230 controls.
Carrier: +0x18 + 4i weapon i, +0x2C mount mask. Weapon: +0x08 class
(+0x0C signature, `FUN_00475b30` line 561), +0x0C ordnance class (+0x54 shot
speed, `FUN_0056af20` line 73), +0x28 muzzle matrix (line 77).

Reach test maths (`FUN_0056af20` lines 95-111, 147): d = target - muzzle,
h2 = dx2 + dz2, a = dy2/h2 + 1, b = v2 - 9.8 dy, c = 24.01 h2; reachable when
b2 - 4ac >= 0. The decompiler shows `void`; the return in AL was read from
the disassembly. `0x0056B1C0` (what DoAttack calls) wraps it with a led
target position from target+0x18 vt+0xC (`FUN_0056b1c0` lines 43-45).

## Behaviour

Both hooks are vtable-slot replacements on the ArtilleryFriend vtable,
RTTI-checked (`.?AVArtilleryFriend@@`) and installed all or nothing. They are
installed only when the ini key is on, and pass straight through to stock in
network games (`IsSinglePlayerSession()`).

**DoAttack** (slot 26). Gates, all required, else stock runs unchanged:
craft vtable is the Howitzer primary vtable; craft team is the local
player's team; craft command is ATTACK; the target handle resolves; the craft
carries a `MORT` weapon with a shot speed. Then the reach test runs twice on
that weapon with the target pushed out horizontally from the craft: x1.05
("deploy") and x1.02 ("hold"). Stock aims at a led position, so the margins
keep stock's own test from failing after we commit.

- Deploying or deployed, hold passes: stock DoAttack runs (fire).
- Deploying or deployed, hold fails: refresh the timeout, skip stock. If the
  target was never in reach this attack (stock InitAttack deployed at once),
  Packup now; otherwise after 1 s out of reach. A refused Packup hands the
  tick to stock (out of range, idle).
- Packed, deploy passes: zero the drive controls (as artillery idle does,
  `FUN_00475970` lines 37-45), Deploy, skip stock this tick.
- Packing (3), deploy passes: wait.
- Out of reach and packed or packing: Packup (cancels a pending deploy), then
  `UnitProcess::InitGoto` builds a GotoTask to the live target at +0x3C and
  stores it at +0x38 (`FUN_005fb500` lines 101-143). Each tick, tick it the
  way DoGoto does (vt[6] done, else vt[7]) and refresh the 30 s timeout so
  stock does not give up (`FUN_00475b30` lines 475-481). Re-path when the
  target has moved 25 m from the snapshot, at most every 2 s. If the task
  reports done while still out of reach, it is deleted and stock decides
  (out of range, idle).
- Target gone, or the order changed: our task is deleted and stock runs,
  which says 0x18, clears ATTACK and goes idle (`FUN_00475b30` lines 385-401).

Our task is deleted only while +0x38 still holds it, with vt[0](1) and
+0x38 = 0, as EndGoto does.

**EndAttack** (slot 25, stock is the empty 0x00417C60): leaving the attack
state deletes our task, since the next InitGoto overwrites +0x38 without a
delete (`FUN_005fb500` line 143).

**Save and load.** The process save writes +0x38 as an object pointer named
"task" (`FUN_005f9ab0`, the ArtilleryFriend slot-3 chain via `FUN_00582ea0`
line 81, writes it at lines 205-207; the string at 0x00875DCC is `task`),
and the load reads it back as "UnitProcess::task" (`FUN_005f9490` lines
213-215, chained from `FUN_00582ca0` line 79). The process state at +0x1C
comes back too (lines 81-105), and ArtilleryFriend's post-load
(`FUN_004758a0` lines 13-17) re-arms the 30 s timeout for state 7. So a game
saved mid-approach loads with the GotoTask at +0x38 and no track. Live run
2026-11-23 (save during `drive`, then load): `foreign task 0x360DACD0
vt=0x0087A61C at +0x38 state=7 next=0 deploy=0`.

A loaded attack runs DoAttack on the first sim ticks after the mission
reset. So only a process's first attack tick since the reset, and only within
1 s (game time) of the first attack tick any process made, may adopt; a task
stock leaves at +0x38 later in a mission is never taken. On that tick, with a
new track, a task at +0x38 whose vtable is `GotoTaskVtable` is adopted: it becomes the track's task, with the live
target as the re-path snapshot, and the approach carries on; every later
delete (in reach, deployed, re-path, arrived, gate, EndAttack) goes through
the same owned-task path and logs `deleted adopted task ... (<why>)`. Any
other task type is left to stock as before (`foreign task ... ; stock
attack`). `InitGoto` builds a `GoGet` instead of a GotoTask when the target
is a building other than a 'CPOD' (`FUN_005fb500` lines 101-121); such a
restored task is not adopted.

**Keeping the ordered target.** In the attack state stock does not pick a new
target by ordinary acquisition: `OffensiveProcess::DoSubTask` asks
ShouldSwitch (vt+0xE8, `FUN_00583520` line 295), and ArtilleryFriend's
0x00476F90 returns 0 for state 7 (`FUN_00476f90` lines 25-27). The one
remaining path is the recent-SNIP override (`FUN_00583520` lines 67-87,
179-183, 299-301), sourced from craft+0x98. While an approach is driving
(drive, packup, hold or deploy phases), `OffensiveProcessDoSubTaskHook` in
`ai_odf_tuning.cpp` hides that input for the one call, the same way the
HowitzerUndeployedRetaliation fix does, whatever the deploy state and whether
or not that fix is on. Logged once per approach.

Decision log: a change-only `[HOWAPPR] <old> -> <new>` line per phase change
(fire, hold, packup, drive, deploy, arrived) with distance, both reach
results and the deploy state; a `gate=` line when a player howitzer's gate
result changes for a reason other than team/class (tracked per process).
Budget 96 lines per mission.

Tracks are cleared only at mission exit (the feature table's revert), not
by `exu.ResetMissionHookOverrides()`: the feature is ini-only, and a live
track owns the GotoTask at +0x38.

## Open questions (UNVERIFIED)

- A save made mid-approach against a building target restores a `GoGet`,
  which is not adopted: it is left to stock and leaks as before. Not tested.
- The muzzle matrix of a packed howitzer may sit lower than when deployed;
  the 5% margin is meant to absorb that. Not measured.
- Enemy howitzers and the ArtilleryProcess base vtable stay stock by design.
