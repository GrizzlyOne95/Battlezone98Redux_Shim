# Daywrecker AI defence and reaction: research (queue item 14a)

Research only, no code. Status: static analysis; nothing here is live-tested.

## Decisions (user, 2026-11-19)

1. v1 includes AI reaction, not only the player-order fix.
2. The Daywrecker is collidable (powerup VDF); players already kill it in flight. Collision is
   settled by observation, no gating probe. The open risk is AI aim and lead against a falling target.
3. AI reaction first = shoot the bomb: units in a radius target the enemy falling DW, reusing the
   order fix. Scatter is later.
4. Switch: new `[SinglePlayer]` ini option, default off, working with stock DW ODFs.
5. Only open question: reproduce "Defend", and with which unit.
Single player only for any v1 (balance-changing AI behaviour).

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

## 1. Why the menu gives Go To (or Defend)

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
  `1.5/004aa384_PowerUpClass_PowerUpClass.c:12`; GOG `FUN_005ab2c0-005ab2c0.c`: `param_1[7] = 3`). The
  `DayWreckerClass` ctor (1.5 0x0052D3A9; GOG `FUN_004b0a00-004b0a00.c`) sets only the signature
  'WRCK' and name "daywrecker" and calls the PowerUp ctor, so a Daywrecker inherits 3.
- The same test is in the other paths: `ActionMode::GetCommand` (`1.5/004be002...c:48`,
  with no unit selected / mode 1; it returns ATTACK only for non-PowerUp enemies at `:57`),
  `TurretTank::GetCommand` (1.5 0x004B519A, GO at its first class test), `GOG FUN_00470d10-00470d10.c`.
- Order menu "Attack" mode (ModeList mode 0xE, `Docs/TURRET_ATTACK_ORDERS.md`) only picks the
  mode; the reticle target still resolves through the same GetCommand. UNVERIFIED that no
  other path in the Targets mode bypasses it.
- "Defend": no Craft or ActionMode path returns DEFEND for category 3 (GO is first), so the
  reported Defend likely comes from another class's GetCommand (Armory/APC/Scavenger family,
  not read) or an object whose DW state differs. UNVERIFIED; reproduce live per unit type.
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

## 4. v1 build plan (single player only, `[SinglePlayer] DaywreckerDefence`, default 0)

Stock DW ODFs work: the bomb test is RTTI `.?AVDayWrecker@@` (as `daywrecker_spawn_fall.cpp` does)
plus airborne bit 0x4 at `[obj+0x228]+0x114`, no ODF key. Gate every hook on the option,
`ReadLocalPlayerNetIdValue() == 0`, and a kill switch `OPENSHIM_DISABLE_DAYWRECKER_DEFENCE=1`.

**New files**
- `include/daywrecker_defence_policy.h` (pure logic) and `tests/daywrecker_defence_policy_tests.cpp`
  (pattern: `tests/daywrecker_spawn_policy_tests.cpp`).
- `src/patches/daywrecker_defence.cpp`, added to `Plugin_OpenShim.vcxproj`, the feature table
  (`global_feature_config.cpp:679-719` pattern), `Docs/ACTIVE_PATCHES.md`, and `scripts/patches.json`
  rows for each new address (reuse `GameObjectSetCommandWhere` 0x004DBE70).

**Policy header (unit-tested)**
- `ShouldOfferAttack(isDaywrecker, airborne, enemy, hasWeapon, optionOn, singlePlayer)`: turns the
  stock CMD_GO (3) into CMD_ATTACK (4).
- `ShouldTargetBomb(...)`: unit is an enemy of the bomb, armed, not cargo, idle/WAIT/DEFEND (never
  overrides a player order or an active attack), not already on it.
- `InRadius(dx, dz, R)` on XZ distance squared (as GetClosestEnemyPersonWithin); R constant to
  start at 150 m, tuned live.
- `ScanDue(now, last, 0.5 s)`, a per-bomb cap (start 4 units), a per-unit cooldown (3 s).

**Hooks**
1. GetCommand overrides, vtable slot 13, RTTI-checked, all-or-nothing install, same shape as
   `turret_attack_orders.cpp:28-35,200-210`: `Craft::GetCommand` 0x004AE110 (HoverCraft vtable
   0x0087ABE4) and `TurretTank::GetCommand` 0x005F5D10 (vtable 0x00889498). Call stock; if it returns
   GO and the policy agrees, return 4. `ActionMode::GetCommand` (1.5 0x004BE002): GOG address
   UNVERIFIED (GOG FUN_004d9da0 has the PRCS test but is void(void), so probably not it). It
   forwards to the selected unit's slot 13 (`1.5/004be002_ActionMode_GetCommand.c:22-26`), so the
   Craft/TurretTank hooks cover selected units; find the ActionMode tail only for the no-selection case.
2. Radius scan in the existing DayWrecker Simulate wrapper (`daywrecker_spawn_fall.cpp:264-271`,
   slot 15): add before forwarding, no second hook. Airborne only, throttled. Iterate
   `GameObject::objectList` (`1.5/004096bf_GetClosestEnemyPersonWithin.c:38-60`; GOG
   `FUN_00463d90-00463d90.c`), keep AI-team enemy craft in radius that pass `ShouldTargetBomb`.
3. Order: the bound SetCommand (`producer_rally_points.cpp:74,123,364-370`) is the (what, where,
   param) form used for GO. ATTACK needs the target form: script `Attack()` builds
   `AiCmdInfo{what=CMD_ATTACK, who}` and calls the object overload (`1.5/0045fc85_Attack.c`).
   Locate and bind that overload in the GOG corpus before coding (address UNVERIFIED).

**Does the lead solve need gravity?** Probably yes, but ship phase A without it. `GOG
FUN_0048f5e0-0048f5e0.c` assumes constant target velocity, so a bomb under 9.8 m/s^2 is missed by about
0.5*9.8*t^2 (about 36 m at t = 2.7 s; the t is an estimate). Where it would go: the existing
`CannonLeadVelocitySite` detour (0x0048F658, `ordnance_velocity.cpp:50-80,506`) already rewrites the
target velocity before the solve. For a DayWrecker target subtract `9.8 * t_est / 2` from `v.y`, with
`t_est = dist / muzzleSpeed`, to use the mean velocity over the flight. That site needs ordnance velocity
inheritance and the 0.1 m/s tolerance NOP active, so it would be forced on for this case. Drag, PowerUp
steering and `dropRate` bend the real path, so it is approximate. UNVERIFIED; add it only if the live hit
rate is poor.

Risks: balance (option off by default); AIP reissuing orders and cancelling the attack; pitch limits
on a steep dive (2b); the whole army turning at once (cap); a stale attack handle (DoAttack clears it on
kill, `1.5/004691b7_UnitProcess_DoAttack.c:12-20`).

**Live checklist (shared harness, lock first, 2 retries)**
1. Option off: stock behaviour, no `[DWDEF]` log lines (check the old build behaves the same).
2. Confirmation only: shells kill a falling bomb (user reports yes).
3. Option on, player: select a tank, reticle an enemy falling DW: menu shows Attack, order sticks, unit fires.
4. Option on, AI: enemy Armory drops on player-side units; units in radius log `[DWDEF] target`, fire, and
   the bomb dies or lands. Count kills over 5 drops at default and at `dropRate = 2`.
5. Cap and cooldown logs show no order spam; AIP does not cancel the order within 3 s.
6. Multiplayer: hooks pass through, no log lines.
7. Kill rate under 30%: add the gravity phase and re-run step 4.

## Open question for the user

1. Can you reproduce "Defend", and with which selected unit type? (Not blocking v1.)
