# Daywrecker AI defence and reaction: research (queue item 14a)

Research only, no code. Status: static analysis; nothing here is live-tested.
Single player only for any v1 (balance-changing AI behaviour).

## Decisions (user, 2026-11-19)

1. v1 includes AI reaction, not only the player-order fix.
2. The Daywrecker is collidable (powerup VDF); players already kill it in flight. Collision is
   settled by observation, no gating probe. The open risk is AI aim and lead against a falling target.
3. AI reaction first = shoot the bomb: units in a radius target the enemy falling DW, reusing the
   order fix. Scatter is later.
4. Switch: new `[SinglePlayer]` ini option, default off, working with stock DW ODFs.
5. The order should be Attack. The bomb shows yellow (PowerUp) instead of enemy red; fix that too.
   This resolves the old "Defend" question: the user sees a powerup, so Attack is the target.
6. Same treatment for the Comet (the Torpedo class, section 3b): Attack order, enemy colour, AI
   targeting.
7. A unit that cannot attack it (no suitable weapon, or not ordered to) and has it in vision should
   dodge it with the stock incoming-ordnance avoidance checks.
8. (Supersedes the colour half of 5 and 6, user 2026-11-19.) Keep the yellow PowerUp colour: dropping
   a DW as a distraction is a valid tactic. No AssignColor hook. The player must still be able to order
   Attack on it.
9. AI detection: AI does not get the bomb instantly on radar contact. Detect it like a Person: in the
   unit's view cone (peripheral vision) and within proximity range, using the stock Person detection
   rule (locate it in the decompile and cite it). The radius scan, targeting and evasion only consider
   bombs a unit has detected this way.

Citations: `1.5/<name>.c` is `Battlezone_Source/BZ1/1.5/functions/<dir>/<addr>_<name>.c` (the
PDB-named BZ 1.5 decompile). `GOG FUN_xxxxxxxx-xxxxxxxx.c` is
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.
Unchecked claims are marked UNVERIFIED.

## Status & findings in one table

| Question | Answer |
| --- | --- |
| 1. Why Go To, not Attack? | Every GetCommand tests "target class category == 3" before it tests enemy. `PowerUpClass` sets category 3 and `DayWreckerClass` never overrides it, so a Daywrecker always returns CMD_GO. Proven. |
| 2a. Target filters | Menu: same cause as 1. Auto-acquire: `GetClosestEnemyWithin` only accepts IsCraft or PERSON classes. A PowerUp is excluded in both. Proven. |
| 2b. Pitch / lead | Linear-intercept lead with no gravity term, so a free-falling bomb is mis-led. Pitch limit is a weak point for hover craft; effect on AI aim UNVERIFIED. |
| 2c. Can it be destroyed in flight? | Yes (user observation, plus the code path): generic damage path reaches `PowerUp::DamageAlloc`, health < 0 flags it dead, `DayWrecker::Explode` makes a small building explosion. Collision confirmed by the user. |
| 3. Reaction hook | `GetClosestEnemyPersonWithin` is the in-engine "threat in radius" pattern. Best hook: the existing DayWrecker Simulate wrapper (vtable slot 15). |
| 4. Yellow colour | `AssignColor` paints a class-POWERUP object with `teamSlot < 0` yellow; DW and Comet qualify (3b). Proven in 1.5; GOG unverified. **Kept yellow by decision 8: no AssignColor hook.** |
| 5. Comet | Comet = `radarmsl`, classLabel "torpedo", a PowerUp subclass: same GO, yellow and target-filter problems (3b). Proven in 1.5; GOG unverified. |
| 6. Avoidance | `EvadeOrdnanceForce` only walks `Ordnance::ordnanceList` (200 m, forward cone), so bombs are never dodged; detour it to add them (3b). Proven in 1.5 (GOG `FUN_005fd5f0` read for the list walk); GOG unverified for the rest. |

## 1. Why the menu gives Go To

- A selected unit's reticle command comes from its own virtual `GetCommand`:
  `ActionMode::GetCommand` forwards to `selectList[0]`'s vtable +0x34 when anything is
  selected (`1.5/004be002_ActionMode_GetCommand.c:22-26`).
- `Craft::GetCommand` (1.5 0x00488EC4): the order is (a) target class `+0x28 == 3` returns
  CMD_GO (`1.5/00488ec4_Craft_GetCommand.c:28`), (b) only then `EnemyP` returns CMD_ATTACK
  (`:30-32`), (c) FOLLOW, (d) DEFEND (`:41`). The GO test precedes the enemy test.
- GOG confirms: `GOG FUN_004ae110-004ae110.c` (0x004AE110, `Craft::GetCommand`): `*(class+0x1c) == 3`
  returns 3 before the enemy helper `FUN_004db5b0` is called (returns 4 for attack, 5 follow).
  Class `+0x1c` in GOG is `+0x28` in 1.5 (the same field).
- Category 3 is set by `PowerUpClass::PowerUpClass` (1.5 0x004AA384,
  `1.5/004aa384_PowerUpClass_PowerUpClass.c:17`; GOG `FUN_005ab2c0-005ab2c0.c`: `param_1[7] = 3`). The
  `DayWreckerClass` ctor (1.5 0x0052D3A9; GOG `FUN_004b0a00-004b0a00.c`) sets only the signature
  'WRCK' and name "daywrecker" and calls the PowerUp ctor, so a Daywrecker inherits 3.
- The same test is in the other paths: `ActionMode::GetCommand` (`1.5/004be002...c:48`,
  with no unit selected / mode 1; it returns ATTACK only for non-PowerUp enemies at `:57`),
  `TurretTank::GetCommand` (1.5 0x004B519A, GO at its first class test), `GOG FUN_00470d10-00470d10.c`.
- Order menu "Attack" mode (ModeList mode 0xE, `Docs/TURRET_ATTACK_ORDERS.md`) only picks the
  mode; the reticle target still resolves through the same GetCommand. UNVERIFIED that no
  other path in the Targets mode bypasses it.
- "Defend": assumed, not a finding. We assume the user saw a powerup-looking (yellow) bomb and wants Attack
  (decision 5). No Craft or ActionMode path read here returns DEFEND for category 3 (GO is first); where a
  Defend order could come from is UNVERIFIED (other classes' GetCommand not read). Not pursued.
- A script already can order it: the Lua `Attack(h, target)` builds `CMD_ATTACK` and calls
  `GameObject::SetCommand` directly (`1.5/0045fc85_Attack.c`), skipping GetCommand. That is the
  cheapest way to test items 2b/2c live with no native work.

## 2. Why a direct attack does not hit it

### 2a. Target filters (proven)

- Auto-acquire for offensive units: `OffensiveProcess::ChooseAttackTarget` (1.5 0x0044DCA0)
  just calls `GetClosestEnemyWithin` (`1.5/0044dca0_...ChooseAttackTarget.c:12`).
- `GetClosestEnemyWithin` (1.5 0x00406302) requires `EnemyP`, perceived-team enemy,
  `maxHealth != 0`, not cargo, and `IsCraft(obj) || class_id == CLASS_ID_PERSON`
  (`1.5/00406302_GetClosestEnemyWithin.c:68-72`). `IsCraft` is HELICOPTER or VEHICLE only
  (`1.5/00405df2_IsCraft.c`). A PowerUp is rejected, so AI never picks a Daywrecker itself.
  GOG address of this function: UNVERIFIED (not located by name).
- Explicit orders do not use that filter, so once an ATTACK command is issued the target
  stays (`UnitProcess::DoAttack`, `1.5/004691b7_UnitProcess_DoAttack.c`). Whether the attack
  task then keeps a PowerUp target is UNVERIFIED.
- Weapon trigger: `UnitTask::UpdateWeapon` branches on `IsCraft(target)` and on a ray test
  (`1.5/0046c63e_UnitTask_UpdateWeapon.c:337-366`). A Daywrecker is dynamic but not a craft;
  the exact fire/hold outcome is UNVERIFIED.
- Craft vs PowerUp collision is skipped: `Craft::RegCollision` returns false for
  `CLASS_ID_POWERUP` (`1.5/00486c3f_Craft_RegCollision.c:34`). That is only craft-body contact,
  not shells.

### 2b. Pitch and lead

- Pitch: hover craft store `0.5 * control pitch` at `this+0x280` (`scripts/patches.json:2333`,
  HoverCraft::AimPitchGlobalGate identity). Stock turrets use the same 0.5 constant at
  0x005F1838 / 0x005F561A (`scripts/patches.json:7490-7498`); the repo's `TurretAimPitch`
  (`[SinglePlayer]`, default on) swaps it for 0.95 (`src/patches/bzr_hooks.cpp:99-100`,
  `src/patches/trampolines.cpp:1020-1043`). Only the two Turret classes are patched, so a
  hover tank stays at 0.5. The unit of the 0.5 (rad or fraction) and whether AI craft pitch
  is clamped to it: UNVERIFIED.
- Lead: `GOG FUN_0048f5e0-0048f5e0.c` (`CannonLeadVelocitySite`, `src/patches/ordnance_velocity.cpp:50-80`)
  solves `|p + v t| = s t` with a constant target velocity and a skip when the target speed
  is <= 0.1 (`FUN_0048f5e0:~25-48`). No gravity or acceleration term. The bomb falls at
  `9.8` m/s^2 with drag (`Docs/DAYWRECKER_DROP_RATE.md`, the PowerUp::Simulate row), and
  `dropRate` shortens the flight, so the linear lead overshoots or undershoots. Direct-fire
  cannons will miss often; only the geometry of a final steep dive is easy to hit.
  Ordnance velocity inheritance already exists (same file) and helps nothing here.
- PowerUpProcess steers the bomb toward its target while descending (bit 0x1;
  `1.5/004585ef_PowerUpProcess_Execute.c:~56-85`), so its path is not a pure parabola.

### 2c. Can it take damage or be destroyed in flight?

- Generic path: `Damage_Resolve` ends in `ClassAllocateDamage(victim)`
  (`1.5/00525248_Damage_Resolve.c:60`) with no class filter.
- `PowerUp::DamageAlloc` (1.5 0x004A94A4): skips if obj flag 0x200 (already detonated), else
  subtracts health and, if health < 0, ORs 0x1000000 (`1.5/004a94a4_PowerUp_DamageAlloc.c:32,80-82`).
  It even has an ordnance-hit chunklet branch (`:42-68`), so shells hitting powerups is an
  anticipated case.
- Death calls `DayWrecker::Explode` (1.5 0x0052D234): builds the **building** explosion
  (`xplBuilding`), not the ODF `xplBlast`, and no crater (`1.5/0052d234_DayWrecker_Explode.c:27-39`).
  So shooting it down yields a small blast, not the bomb's. The 1.5 ODF sample has
  `maxHealth = 300` (`Battlezone_Install/addon/.../ianreck.ODF`); the Redux apdwrck value is
  UNVERIFIED. That "flags 0x1000000 routes to Explode" is UNVERIFIED (not traced).
- The DW has a car-sphere collider (`1.5/0047487b_InitCollisionType.c:17`), and
  `DayWrecker::RegCollision` (0x0052D12B) damages what it hits then clears 0x4.
  Collision is settled by user observation: players already kill it in flight.

## 3. Enemy reaction in a radius

- Pattern: `GetClosestEnemyPersonWithin` (1.5 0x004096BF; GOG `FUN_00463d90-00463d90.c`): loop
  `GameObject::objectList`, `EnemyP`, class test, XZ distance squared against the radius,
  keep the closest (`1.5/004096bf_...c:38-60`). Used by `SAVProcess::DoSubTask`
  (`1.5/0045bbc8_SAVProcess_DoSubTask.c:30`). `GetClosestThreatWithin` (1.5 0x004097C5) is the
  craft-only version. A Daywrecker-centred scan (units near the bomb) is the inverse and reuses
  the same loop.
- Hook points that already exist in the repo:
  - DayWrecker vtable slot 15 (Simulate, `src/patches/daywrecker_spawn_fall.cpp:70,264-271`).
    It is called every tick for each airborne bomb with the bomb as `self`; a scan can run
    there (throttled to ~2 Hz). No new hook needed.
  - `GameObject::SetCommand(what, where, param)` at 0x004DBE70
    (`scripts/patches.json:3150`) already bound by `src/patches/producer_rally_points.cpp:74,123,364-370`
    to send CMD_GO; reuse it to scatter (move off the landing point).
  - `GameObject::SetTarget` (1.5 0x0045A033) for "shoot it"; GOG address UNVERIFIED.
  - Vtable GetCommand slot 13 hook precedent: `src/patches/turret_attack_orders.cpp:28-35`.
- Hazard: AI teams reissue orders from the strategic layer (AIP). Whether a SetCommand
  survives the next AIP pass, and whether SetCommand on an enemy AI unit mid-attack is
  honoured, is UNVERIFIED; needs live tuning.

## 3b. Colour, Comet and avoidance (added 2026-11-19)

**Colour (proven in 1.5; GOG unverified).** `GameObject::AssignColor` (1.5 0x004953BA): if `teamSlot < 0` and `class_id ==
CLASS_ID_POWERUP` the live colour is yellow (dead: dark yellow); otherwise by team: 0 white, user team
green, friend blue, else red (`1.5/004953ba_GameObject_AssignColor.c:17-45`).
- A DW or Comet has `teamSlot == -1`: `GameObject::Init` sets -1 when the class has no category range
  (`1.5/00496c94_GameObject_Init.c:21-32`), so it takes the yellow branch. The base class ctor sets
  `categoryMin/Max = -1` (`1.5/00499d37_GameObjectClass_GameObjectClass.c:108-109`); the PowerUpClass ctor
  (`1.5/004aa384_PowerUpClass_PowerUpClass.c:13-17`) and, by grep, the DayWreckerClass and TorpedoClass ctors
  do not change it. Whether the ODF load sets a range (`GameObjectClass.c:205` copies one) is UNVERIFIED.
- Init sets `teamSlot = 0` instead when `this == userObject` or an unnamed byte field is non-zero
  (`00496c94_GameObject_Init.c:21-22`, the `_padding_ != 0` test). What that field is, and whether a DW or
  Comet has it set, is UNVERIFIED. If it is set, the bomb is already not yellow, so check live first.
- AssignColor runs at Init/Load and every visibility pass for objects with a team >= 0
  (`1.5/004980ac_GameObject_ComputeVisibility.c:73`), so a one-off write to `liveColor` is overwritten.
  It must be hooked at AssignColor.
- Every consumer reads `GameObject::GetColor` (live colour, or dead colour when flag 0x200 is set,
  `1.5/004bf774_GameObject_GetColor.c`): target box (`004c2ab9_BoundingBox_Render.c:61`), selection
  (`004c1db7_SelectionDisplay_Render.c:142`), target camera (`004db7e6_TargetCam_Render.c:239,246`),
  cockpit radar (`004c05b7_CockpitRadar_Render.c:348`), map radar (`004d2395_MapRadar_Render.c:274`).
  One hook fixes HUD, reticle box and radar colour. Radars also pick blip style by category 3/4
  (`CockpitRadar_Render.c:310-317`, `MapRadar_Render.c:252`); the shape stays as is.
- Cheapest fix: a wrapper on AssignColor that, for a bomb only, sets `teamSlot = 0` around the stock
  call and restores it; the stock team branch then gives red, blue, green or white. The colour follows
  `teamNumber`, so a team-0 bomb would be white; which team owns a DW (and a Comet) is UNVERIFIED (live
  checklist row 3). The restore must be exception-safe (`__try/__finally`): this is a per-frame path and a
  throw between set and restore would leave `teamSlot = 0` and corrupt the team slot. The GOG address
  of AssignColor and the GOG `teamSlot` offset are UNVERIFIED (a static search for them failed; find
  them through the caller in GOG `GameObject::Init`).

**Comet = Torpedo, a PowerUp subclass (proven in 1.5; GOG unverified).**
- Stock `gcomet.odf` is `classLabel = "radarlauncher"` and fires `radarmsl`: `classLabel = "torpedo"`,
  `aiName = "TorpedoProcess"`, `maxHealth = 600`, unitName "Comet", `lifeSpan = 20`, `velocForward = 15`
  (`C:/Users/iestu/Documents/BZR_moved_out_20261112/StockODFFiles/gcomet.odf` and `radarmsl.odf` in the same folder; classLabel, maxHealth, aiName, lifeSpan re-read 2026-11-19; unitName and velocForward not re-checked). The `apcmet`/`spcmet` pickup is a `wpnpower`
  that only grants the weapon, a different object.
- `TorpedoClass::TorpedoClass` (1.5 0x0053D625) calls `PowerUpClass::PowerUpClass`, signature 'PROT'
  (`1.5/0053d625_TorpedoClass_TorpedoClass.c:6-20`); `Torpedo::Torpedo` calls `PowerUp::PowerUp`
  (`1.5/0053c664_Torpedo_Torpedo.c:6`). It inherits category 3, so it gets: GO instead of Attack (same
  GetCommand tests), yellow colour, rejection by `GetClosestEnemyWithin` (not IsCraft), and it is not in
  `Ordnance::ordnanceList`, so stock evasion never sees it (below).
- Damage is the generic `PowerUp::DamageAlloc`, so it is shootable. GOG addresses of the Torpedo class
  and vtable are UNVERIFIED (`FUN_005e5080` holds the "torpedo" string). Its team (the launcher's?) and
  the in-flight test (sig 'PROT', obj flag 0x200 clear) are UNVERIFIED.
- Aside: obstacle avoidance `AvoidObject` exempts category 3 only for sig 'PROT'
  (`1.5/00406a85_AvoidObject.c:49`), so a Comet is already avoided as an obstacle and a Daywrecker
  (sig 'WRCK') is ignored.

**Stock avoidance (proven in 1.5; GOG partly read).** `EvadeOrdnanceForce` (1.5 0x0046DD9D; GOG `FUN_005fd5f0-005fd5f0.c`, cdecl,
hidden vec3 return, args: unit, current threat, out threat):
- It walks `Ordnance::ordnanceList` only and skips class sig 0x534e4950
  (`1.5/0046dd9d_EvadeOrdnanceForce.c:98`; GOG `FUN_005fd5f0:128`). A DW or Comet is not in the list.
- Vision test: within 200 m (`dist^2 <= 40000`, `:113`; GOG `:149`) and, unless it is the known threat,
  inside a forward cone in the unit's frame; dropped if `z < |x|` or `z < 1.5|y|` (`:124`). No line of
  sight or scanner check.
- Closest approach from relative velocity: time `t = -(rel.d)/|rel|^2`; threat if `t > 0` and the miss
  distance is under `(unit radius + ordnance radius at +0xd4) * 2.5`; missiles of sig 0x494d474d, 0x54484d4d or
  0x4d53534c whose `Missile::GetTarget` is the unit use a 3 s window instead (threat if `t < 3`, factor
  `Min(3 - t, 1)`, `:156-161`, verified). A Comet (sig 'PROT') is not one of those, so the 3 s window does not
  apply to it; it would take the plain branch (`:180-181`) if fed in. Force = away from the miss point, weight `GetOrdnanceDamage / (t + 1)` times the factor
  `Min(2.5 - miss/r1, 1)` where `r1 = unit radius + ordnance radius` (`:181,193`; `:184-197` in total). The
  normalise-to-20 step runs only when a threat was recorded (`local_10 != 0`) and `|F|^2 > 400`
  (`:209-219`).
- Callers add the force to steering: GOG 0x00601CF0 and six more; 1.5 `UnitTask::GotoForce:100`,
  `DoFlee:79`, `DoSit`, `DoStand`, `DoBlast`, `GoHeading`, `SitTask::DoState`. The current threat is
  cached as an `Ordnance*` (`threatOrd`), so a bomb cannot be fed in as an ordnance.
- Feed-in route: detour `EvadeOrdnanceForce` (0x005FD5F0): call stock, then add a bomb force, computed with
  the same maths, for each bomb in a registry that the Simulate wrappers refresh; re-apply the
  normalise-to-20 rule. Weight and blast radius: ODF damage (class +0x170 as read in
  `DayWrecker::RegCollision`) and the xplBlast radius; offsets UNVERIFIED, so start with constants.
- A Comet homes (TorpedoProcess), so a sideways dodge may not shake it; a DW drifts toward its target
  (PowerUpProcess), so dodge away from the landing point. Both UNVERIFIED.

## 4. v1 build (single player only, `[SinglePlayer] DaywreckerDefence`, default 0)

Built on branch `agent/daywrecker-ai-defence-v1`. The addresses below were located in the GOG corpus and
checked against the shipping exe bytes. "Bomb" means a DayWrecker with the airborne bit (flags 0x4 at
`[obj+0x228]+0x114`) or a live Comet (Torpedo, obj76 flag 0x200 clear), identified by primary vtable. The
enemy test is `GameObject::EnemyP` (`GameObjectEnemyP` 0x004DB5B0). Stock ODFs work. Every hook is gated on
the option, `IsSinglePlayerSession()` and the kill switch `OPENSHIM_DISABLE_DAYWRECKER_DEFENCE=1`.
`IsSinglePlayerSession()` is `ReadLocalPlayerNetIdValue() == 0` (`src/patches/game_object_helpers.cpp:168-171`);
its comment says a host has a non-zero id too (`:145-149`). Not confirmed live: checklist row 9. With the
option off or the kill switch set, nothing is installed. Decision 8: no AssignColor hook; the bomb stays
yellow.

**Files**: `include/daywrecker_defence_policy.h` (pure rules), `tests/daywrecker_defence_policy_tests.cpp`,
`src/patches/daywrecker_defence.cpp` (installed from `InstallAiTuningCoreHooksIfPossible`, after
TurretAttackOrders), feature-table row `DaywreckerDefence`, `scripts/patches.json` rows, the vtable audit,
`Docs/ACTIVE_PATCHES.md` and both ini files.

**Detection like a Person (decision 9).** Stock AI picks a non-craft target (a pilot) in
`GetClosestEnemyWithin` (GOG `FUN_00463240`, row `AiFireBlockHelperGetEnemyWithin`; 1.5
`00406302_GetClosestEnemyWithin.c`). The rule has two parts:
- XZ distance squared `<= 4900` (70 m). GOG line 196; 1.5 line 72.
- The target is in the front half-space: `front . (target - self) >= 0`, where `front` is the obj76 matrix
  front row at obj76+0x38. GOG lines 200-201, via `FUN_00462490`; 1.5 lines 95-99.

Persons are not radar-detected: `Scanner::SweepVisibility` skips category 4. The check is stateless.
`Detects()` runs it on every scan and every evade call, so a unit only reacts to a bomb it currently sees.

**Hooks and addresses**
1. **GetCommand**, vtable slot 13, RTTI-checked, all or nothing.
   - `Craft::GetCommand` 0x004AE110 (row `CraftGetCommand`) sits in slot 13 of 7 vtables, not only
     HoverCraft: Craft 0x008781EC, HoverCraft 0x0087ABE4, Minelayer 0x0087D790, Person 0x0088562C, SAV
     0x00886BFC, Walker 0x0088A0BC and Wingman 0x0088A464. Found by an .rdata scan;
     `scripts/audit_vtable_hooks.py` finds no other copy. All 7 are hooked.
   - Stock answers GO for the PowerUp category (`*(class+0x1C)==3`) before its enemy test. The hook turns
     GO into ATTACK when the bomb is an enemy and the unit is armed (`[this+0x1A0] != 0`).
   - TurretTank slot 13 (vtable 0x00889498, `TurretTank::GetCommand` 0x005F5D10) is already wrapped by
     TurretAttackOrders. This hook installs after it and chains to it.
   - `ActionMode::GetCommand` forwards to the selected unit's slot 13
     (`1.5/004be002_ActionMode_GetCommand.c:22-26`), so it needs no hook.
2. **Registry and scan**: two Simulate wrappers, both on slot 15.
   - DayWrecker: vtable 0x00878508, `DayWrecker::Simulate` 0x004B0460. Chains with the spawn-fall and MP
     Armory wrappers.
   - Torpedo: RTTI `.?AVTorpedo@@` vtable 0x00888778, `Torpedo::Simulate` 0x005E2D90, found in no other
     vtable. New rows `TorpedoVtable` and `TorpedoSimulate`.
   - Before stock runs, each bomb refreshes its handle entry (32 slots). An entry is dropped after 0.25 s
     unseen, when the bomb lands or dies, or when its handle no longer resolves.
   - Every 0.5 s the bomb walks `GameObject::objectList` for craft that pass all of these:
     - obj76+0x84 is 1 or 6 (`FUN_00417e20`), and alive (obj76 flag 0x200 clear);
     - within 150 m XZ, and detecting the bomb;
     - AI, an enemy of the bomb, armed, and not cargo (`[obj+0x9C]`);
     - idle or defending: `curCmd.what` at +0xAC is NONE or DEFEND, and `nextCmd.what` at +0xCC is NONE;
     - not already on the bomb: no current or pending ATTACK on it (who at +0xB0/+0xD0) and target handle
       +0x21C not the bomb.
   - Those units get `SetCommand(ATTACK, bomb)` through `GameObjectSetCommandObj` 0x004DBD60. At most 4
     per bomb, with a 3 s per-unit cooldown.
   - The command offsets come from the Lua `GetCurrentCommand`/`GetCurrentWho` bindings (`FUN_005cb5c0`,
     `FUN_005cb5f0`).
3. **Evasion**: inline detour on `EvadeOrdnanceForce` 0x005FD5F0.
   - cdecl `(ret, unit, currentThreat, outThreat)`; 6 callers, each followed by `add esp,0x10`. New row
     `EvadeOrdnanceForce`; 9-byte patch `55 8B EC 81 EC 98 01 00 00`.
   - Stock runs first. Then, for each registry bomb the AI unit detects, is an enemy of, and is not
     attacking or aiming at, the hook adds the stock force (`0046dd9d_EvadeOrdnanceForce.c:113-197`; GOG
     `FUN_005fd5f0` lines 149-255) with weight 1000.
   - It then applies the stock normalise-to-20 rule when any threat was recorded (`:209-224`).
   - Explode hooks were not needed: the grounded tick, the handle re-resolve and the timeout remove entries.

No gravity lead, as planned. The cannon lead solve (`GOG FUN_0048f5e0`) assumes constant target velocity,
so it misses a falling DW by about 0.5*9.8*t^2. Add it in `CannonLeadVelocitySite` only if the live kill
rate is poor (checklist row 8).

**Decision log lines** (change-only, budget 400 per mission):
- `[DWDEF] Baseline`, `Active` / `Stood down`, and the install results.
- `offer <kind>: enemy armed -> cmd`.
- `bomb tracked` / `bomb left`.
- `scan bomb= inRadius detected ordered busy unarmed capOrCooldown`.
- `target unit= bomb=`.
- `evade on/off unit= bomb= force=`.

Risks:
- Balance (off by default).
- AIP reissuing orders.
- Pitch limits on a steep dive (2b).
- The added force fighting the unit's goto force.
- A Comet's homing defeating a dodge.
- A 600 HP Comet being hard to shoot down.

**Live checklist (shared harness, lock first, 2 retries)**
1. Option off: stock behaviour. The log shows `[DWDEF] Disabled` and no other `[DWDEF]` lines.
2. Option on, kill switch set: the log shows `Disabled by OPENSHIM_DISABLE_DAYWRECKER_DEFENCE` and behaviour
   is stock.
3. Install: the log shows GetCommand installed (7 slots + TurretTank), both Simulate wrappers, the evade
   detour, then `Active (SP-only)`. DW drop rate and spawn-fall still work, since they share slot 15.
4. Player order: select a tank, then a turret, and put the reticle on an enemy falling DW.
   - Attack is offered (not Go To), the order sticks and the unit fires.
   - The bomb stays yellow.
   - An unarmed unit (a tug) still gets Go To.
5. AI shoot: the player's Armory drops a DW on AI units.
   - AI units within 150 m that face the bomb log `[DWDEF] target` and fire.
   - Units facing away count in `inRadius` but not in `detected`.
   - At most 4 units per bomb, no re-order within 3 s, and a unit on a GO order is left alone.
   - Units on the player's team are never ordered, so their Defend or Follow orders survive. They still dodge.
   - Limit: the Howitzer has its own GetCommand (0x004F0DD0), so the player gets no Attack on a bomb for it, but the scan can still order an AI Howitzer to attack.
6. Avoidance: an AI scavenger or tug facing the falling bomb within 70 m logs `[DWDEF] evade on` and moves
   off the landing line. One facing away does not react.
7. Comet: fire an enemy radarmsl at the player's units; Attack is offered. AI units target and dodge a
   player-fired Comet the same way as a DW.
8. Kill rate over 5 drops, at default and at `dropRate = 2`. Under 30% means add the gravity phase.
9. Host in MP, alone and then with a client: the log shows `Stood down`, with no order or evade changes.

## Open questions for the user

None.
