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
| 4. Yellow colour | `AssignColor` paints a class-POWERUP object with `teamSlot < 0` yellow; DW and Comet qualify. One AssignColor wrapper fixes HUD, reticle box and radars (3b). Proven in 1.5; GOG unverified. |
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

## 4. v1 build plan (single player only, `[SinglePlayer] DaywreckerDefence`, default 0)

"Bomb" means an enemy DayWrecker (airborne: flags bit 0x4 at `[obj+0x228]+0x114`) or an enemy Comet
(Torpedo, sig 'PROT', obj flag 0x200 clear). Stock ODFs work: detection is RTTI or class signature, no ODF
key. Gate every hook on the option, `IsSinglePlayerSession()` and a kill switch
`OPENSHIM_DISABLE_DAYWRECKER_DEFENCE=1`. `IsSinglePlayerSession()` is `ReadLocalPlayerNetIdValue() == 0`
(`src/patches/game_object_helpers.cpp:168-171`, declared `bzr_hooks_internal.h:464`) and is the named
predicate for SinglePlayer-tier gates. Its comment says the net id is non-zero in a network game and "the
host has an id too", and an unreadable id returns 0xFFFF (fails closed) (`game_object_helpers.cpp:145-149`).
So an MP host is not single player by the source comments. Not confirmed live: see checklist row 10.

**New files**
- `include/daywrecker_defence_policy.h` (pure logic) and `tests/daywrecker_defence_policy_tests.cpp`
  (pattern: `tests/daywrecker_spawn_policy_tests.cpp`).
- `src/patches/daywrecker_defence.cpp`, added to `Plugin_OpenShim.vcxproj`, the feature table
  (`global_feature_config.cpp:679-719` pattern), `Docs/ACTIVE_PATCHES.md`, and `scripts/patches.json`
  rows for each new address (reuse `GameObjectSetCommandWhere` 0x004DBE70).

**Policy header (unit-tested)**
- `ShouldOfferAttack(isBomb, enemy, hasWeapon, optionOn, singlePlayer)`: stock GO becomes ATTACK.
- `ColourAsTeam(isBomb, optionOn, singlePlayer)`: whether the AssignColor wrapper forces the team branch.
- `ShouldTargetBomb(...)`: unit armed (start: weapon pointer non-zero, as `Craft::GetCommand` uses
  `[this+0x1A0]`), enemy of the bomb, not cargo, idle/WAIT/DEFEND, never overriding a player order or an
  active attack, not already on it.
- `InRadius(dx, dz, R)` on XZ distance squared (R starts at 150 m); `ScanDue(now, last, 0.5 s)`; per-bomb
  cap (4 units); per-unit cooldown (3 s).
- `EvadeForce(selfPos, selfVel, selfRadius, bombPos, bombVel, bombRadius, weight)` mirroring stock: 200 m
  range, forward cone (`z >= |x|` and `z >= 1.5|y|`), closest-approach time, threat if `t > 0` and miss
  `< (r1 + r2) * 2.5`, weight `/(t + 1)` times the stock factor `Min(2.5 - miss/r1, 1)`
  (`0046dd9d_EvadeOrdnanceForce.c:181,193`); and `Combine(stockForce, bombForce)` with the stock
  normalise-to-20 rule, which runs only when a threat is recorded (`:209`).
- `ShouldEvade(isBomb, enemy, unitIsPlayer, targetsThisBomb, optionOn, singlePlayer)`: an AI unit, armed or
  not (stock evade has no weapon test), that is not currently attacking or targeting that bomb. That is, evade
  when `ShouldTargetBomb` is false for the unit, or the unit's current target is not that bomb. The player
  craft is never touched. This also removes the dodge-versus-aim conflict (a shooter does not dodge its own
  target); the dodge-versus-goto-force conflict stays (see risks).

**Hooks**
1. GetCommand overrides, vtable slot 13, RTTI-checked, all-or-nothing install, same shape as
   `turret_attack_orders.cpp:28-35,200-210`: `Craft::GetCommand` 0x004AE110 (HoverCraft vtable 0x0087ABE4)
   and `TurretTank::GetCommand` 0x005F5D10 (vtable 0x00889498). Call stock; if it returns GO and
   `ShouldOfferAttack`, return 4. `ActionMode::GetCommand` (1.5 0x004BE002): GOG address UNVERIFIED
   (`FUN_004d9da0` is not it); it forwards to the selected unit's slot 13
   (`1.5/004be002_ActionMode_GetCommand.c:22-26`), so the two hooks cover selected units.
2. Colour: wrapper on `GameObject::AssignColor` (GOG address UNVERIFIED, locate first): for a bomb set
   `teamSlot = 0` around the stock call, restore after. Covers HUD, target box, reticle and both radars.
3. Radius scan from the DayWrecker Simulate wrapper (slot 15, `daywrecker_spawn_fall.cpp:264-271`) and a
   new Torpedo Simulate wrapper (Torpedo vtable and slot UNVERIFIED). Both refresh a small bomb registry
   (handle, pos, vel, team, time) and run the throttled scan: iterate `GameObject::objectList`
   (`1.5/004096bf_GetClosestEnemyPersonWithin.c:38-60`; GOG `FUN_00463d90-00463d90.c`) for AI-team enemy
   craft passing `ShouldTargetBomb`.
4. Attack order: the bound SetCommand (`producer_rally_points.cpp:74,123,364-370`) is the (what, where,
   param) form used for GO. ATTACK needs the target form: script `Attack()` builds
   `AiCmdInfo{what=CMD_ATTACK, who}` and calls the object overload (`1.5/0045fc85_Attack.c`). Locate and bind
   that overload in the GOG corpus first (address UNVERIFIED).
5. Avoidance: detour `EvadeOrdnanceForce` GOG 0x005FD5F0. Call stock, then add `EvadeForce` for each
   registry bomb that passes `ShouldEvade`. A unit evades only when it is not currently attacking or
   targeting that bomb (`ShouldTargetBomb` false, or its current target is not that bomb). Registry: store
   handles, not pointers, and re-resolve them on each use (skip if it no longer resolves). Remove an entry on
   explode or death as well as on a 0.25 s refresh timeout. Death point: the grounded tick in
   `DayWrecker::Simulate` detonates when flag 0x4 is clear (`1.5/0052d029_DayWrecker_Simulate.c:21-37`), which
   the existing Simulate wrapper already sees; `DayWrecker::Explode` is 1.5 0x0052D234 and `Torpedo::Explode`
   1.5 0x0053D56E (GOG addresses UNVERIFIED). Whether a shot-down bomb reaches Explode is UNVERIFIED (section
   2c), so the timeout stays as the fallback.

**Shoot first, dodge second.** Units that `ShouldTargetBomb` rejects (no weapon, player order, cap reached)
rely on the evade wrapper (decisions 3 and 7). Units that do target the bomb do not dodge it.

**Does the lead solve need gravity?** Probably yes for a DW, but ship without it. `GOG
FUN_0048f5e0-0048f5e0.c` assumes constant target velocity, so a bomb under 9.8 m/s^2 is missed by about
0.5*9.8*t^2 (about 36 m at t = 2.7 s; the t is an estimate). It would go in the existing
`CannonLeadVelocitySite` detour (0x0048F658, `ordnance_velocity.cpp:50-80,506`), which already rewrites the
target velocity before the solve: for a DayWrecker target subtract `9.8 * t_est / 2` from `v.y` with
`t_est = dist / muzzleSpeed`. That needs ordnance velocity inheritance and the 0.1 m/s tolerance NOP forced
on. A Comet is powered flight, so no gravity term. UNVERIFIED; add it only if the live hit rate is poor.

**Tests (host, no engine)**: each policy function above. Boundaries: cone edge, range 40000, `t <= 0`, miss at
exactly 2.5 radii, the `Min(2.5 - miss/r1, 1)` factor (0 at 2.5 radii, 1 at or below 1.5), normalise only when
a threat is recorded and `|F|^2 > 400` (no threat with a large force: no normalise); a unit targeting the bomb
does not evade it; option off or multiplayer returns stock; cap and
cooldown; a player order is never overridden; stale registry entries dropped.

Risks: balance (option off by default); AIP reissuing orders and cancelling the attack; pitch limits on a
steep dive (2b); the whole army turning at once (cap); AssignColor and Torpedo addresses unlocated; the added
force fighting the unit's goto force (the dodge-versus-aim conflict is removed by not evading a bomb the unit
targets); a Comet's homing defeating a dodge; a 600 HP Comet being hard to shoot
down.

**Live checklist (shared harness, lock first, 2 retries)**
1. Option off: stock behaviour, no `[DWDEF]` log lines (check the old build behaves the same).
2. Confirmation only: shells kill a falling bomb (user reports yes).
3. Colour: enemy DW and enemy Comet red in the target box, reticle, cockpit radar and map radar; own-team
   bomb green; option off yellow. Record which team owns the DW and the Comet: a team-0 bomb shows white.
4. Player order: select a tank, reticle the enemy bomb: Attack (not Go To), the order sticks, the unit fires.
5. AI shoot: enemy Armory drops on player-side units; units in radius log `[DWDEF] target` and fire. Count kills
   over 5 drops at default and at `dropRate = 2`.
6. Avoidance: an unarmed unit (scavenger or tug), and an armed unit with the shoot path disabled, with the bomb
   in front within 200 m: log `[DWDEF] evade` and the unit leaves the landing point; a unit behind or outside
   the cone does not react.
7. Comet: an enemy radarmsl at the player's units shows red, Attack is offered, an unarmed unit avoids it.
8. Cap and cooldown logs show no order spam; AIP does not cancel within 3 s; multiplayer passes through.
10. Host in MP: host a match (alone, then with a client): the option does nothing, no `[DWDEF]` lines, bombs
    stay yellow, no order or evade changes. Confirms `IsSinglePlayerSession()` is false for a host.
9. Kill rate under 30%: add the gravity phase and re-run step 5.

## Open questions for the user

None.
