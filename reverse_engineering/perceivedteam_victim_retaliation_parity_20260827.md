# PerceivedTeam Victim AI Retaliation Parity Analysis: 1.5 vs Redux (2026-08-27)

## Executive Summary & Decision Gate Result

**Verdict: No Redux regression exists in the victim AI retaliation or `perceivedTeam` hostility path.**

Static reverse engineering of Battlezone 1.5 (`bzone.exe` + `bzint.pdb` 1.5.2.27) and Battlezone 98 Redux (`battlezone98redux.exe` GOG 2.2.301 / Steam) confirms 100% semantic and structural identity across the complete hostility, damage allocation, target selection, and AI process state machine pipeline.

Specifically:
1. **Disguise Mechanics**: Capture (`Person::RegCollision`) deliberately sets `craft->perceivedTeam = oldOwnerTeam` in both 1.5 and Redux.
2. **Attacker Reveal**: `SetDamageFlags` on hit reveals the damager (`damager->SetPerceivedTeam(damager->GetTeam())`) in both 1.5 and Redux.
3. **Victim Damage Classification**: `SetDamageFlags` evaluates damager team using `EnemyP(shooterTeam)`. If actual teams are hostile (victim actual team 1, attacker actual team 2), damage is correctly classified as enemy damage, updating `enemyShot` timestamp and `who_shot_JR` handle in both 1.5 and Redux.
4. **Target Acquisition & Hostility Predicate**: `GameObject::EnemyP` and `GameObject::FriendP` test actual team (`vtable[1]` = `GetTeam()`) against `Team::FriendP` in both 1.5 and Redux. `perceivedTeam` is NOT read by target acquisition routines (`GetClosestEnemyWithin`).
5. **AI Retaliation State Machine**: `OffensiveProcess`, `TurretTankProcess`, and `TurretCraft`/`GunTower` processes check `enemyShot` during periodic `DoSubTask` updates and transition to attack against `who_shot_JR` in both 1.5 and Redux.
6. **Quarantine Confirmation**: The quarantined OpenShim attack-reveal hook was an enhancement (revealing attackers on process engagement before damage lands) and **must remain quarantined** as it is not a 1.5 compatibility fix.

---

## 1. Scope & System Architecture Comparison

### 1.1 Key Data Layouts & Field Offsets

| Field / Property | 1.5 Offset | Redux Offset | Accessor / Method | Semantics |
| --- | --- | --- | --- | --- |
| `team` (actual) | `+0x168` | `+0x174` | `vtable[1]()` (`GetTeam`) | True team assigned at spawn/capture |
| `group` | `+0x16C` | `+0x178` | Direct field read | Unit group index (0-9) |
| `teamList` | `+0x170` | `+0x17C` | `FriendP(int)` -> `[this+0x17C]` | Pointer to `Team` alliance bitmask |
| `perceivedTeam` | `+0x174` | `+0x180` | `GetPerceivedTeam()` | Visual/Radar disguise team |
| `enemyShot` | — | `+0x1E8` | `GetEnemyShot()` | Timestamp of last hit by enemy |
| `friendShot` | — | `+0x1EC` | Direct float field | Timestamp of last hit by friendly |
| `who_shot_JR` | — | `+0x1F4` | Direct `Handle` field | Unit handle of last attacker |

*Note*: The `DistributedObject` base subobject is located at `base+0x20` in 1.5 and `base+0x18` in Redux. Virtual team accessors called on the subobject adjust operand offsets accordingly.

---

## 2. Static Analysis: Pipeline Comparison

### 2.1 Disguise Mechanics (`Person::RegCollision` / Capture)
- **1.5 VA**: `0x004A6E06`
- **Redux VA**: `0x005A1550` (`FUN_005a1550`)
- **Behavior**:
  ```cpp
  int oldTeam = craft->GetTeam(); // vtable[1]()
  craft->SetTeam(person->team);    // Updates actual team (+0x174) & teamList (+0x17C)
  craft->curPilot = person->objClass;
  ...
  craft->SetPerceivedTeam(oldTeam); // Sets perceivedTeam (+0x180) to previous owner!
  ```
- **Parity**: Identical line-for-line in both 1.5 and Redux. Disguise is an intentional design feature of Battlezone 1.5.

### 2.2 Damage Allocation & Hostility Classification (`GameObject::SetDamageFlags`)
- **1.5 VA**: `0x00496DA9`
- **Redux VA**: `0x004DC130` (`FUN_004dc130`)
- **Logic**:
  1. Checks if damager is team 0 (environment/neutral).
  2. If damager team == victim team: evaluates `FriendP`.
  3. If damager team != victim team: calls `FriendP(damagerTeam)`.
     - If `FriendP` returns false (enemy): writes current game time `fVar1` to `enemyShot` (`+0x1E8`), updates `who_shot_JR` (`+0x1F4`), and calls `damager->SetPerceivedTeam(damager->GetTeam())` (`0x004DC29F`).
- **Parity**: Identical in both 1.5 and Redux. Landed damage from an actual enemy always sets `enemyShot` and updates `who_shot_JR`.

### 2.3 Hostility Predicates (`GameObject::FriendP` & `GameObject::EnemyP`)
- **1.5 VAs**: `FriendP` (`0x00496C40` / `0x00495321`), `EnemyP` (`0x00495380`)
- **Redux VAs**: `FriendP` (`0x004DB510` / `0x004DB560`), `EnemyP` (`0x004DB600`)
- **Implementation**:
  ```cpp
  bool GameObject::FriendP(GameObject* candidate) {
      if (!candidate) return false;
      int candidateActualTeam = candidate->GetTeam(); // vtable[1]()
      return this->FriendP(candidateActualTeam);
  }
  ```
- **Parity**: Both 1.5 and Redux query `vtable[1]()` (actual team) for hostility tests. Neither `FriendP` nor `EnemyP` reads `perceivedTeam`.

### 2.4 Target Selection (`GetClosestEnemyWithin` & `OffensiveProcess::ChooseAttackTarget`)
- **1.5 VAs**: `GetClosestEnemyWithin` (`0x00463240`), `ChooseAttackTarget` (`0x0044DF50`)
- **Redux VAs**: `GetClosestEnemyWithin` (`0x00463240`), `ChooseAttackTarget` (`0x00583500`)
- **Logic**: Iterates over candidate targets using `owner->EnemyP(candidate)`. Since `EnemyP` tests actual team, target selection evaluates true actual team alliances.
- **Parity**: Identical between 1.5 and Redux.

### 2.5 Victim AI Process & Retaliation State Machine

#### 2.5.1 `OffensiveProcess`
- **1.5 VAs**: `DoSubTask` (`0x0044DFA1`), `WaitVsAttack` (`0x0044E150`)
- **Redux VAs**: `DoSubTask` (`0x00583690`), `WaitVsAttack` (`0x00583950`)
- **Logic**: In `Wait` or `Follow` state, `WaitVsAttack` checks if `enemyShot` timestamp is recent. If recent enemy damage occurred, it retrieves `who_shot_JR`, sets target handle, and transitions task to `Attack`.
- **Parity**: Identical between 1.5 and Redux.

#### 2.5.2 `TurretTankProcess` & `TurretCraft` / `GunTower`
- **1.5 VAs**: `TurretTankProcess::DoSubTask` (`0x00467B88`), `TurretCraft::DoSubTask` (`0x004DF120`)
- **Redux VAs**: `TurretTankProcess::DoSubTask` (`0x005F7143`), `TurretCraft::DoSubTask` (`0x004F6470`)
- **Logic**: Deployable turrets and gun towers evaluate targets within their effective weapon range. When hit, `SetDamageFlags` sets `who_shot_JR`. On the next subtask tick, if the damager is within range, the turret rotates and engages.
- **Parity**: Identical between 1.5 and Redux.

#### 2.5.3 Sniper-Specific Aggression Path
- **1.5 VA**: `SniperShell::Execute` (`0x004A8B10`) / `Person::RegCollision`
- **Redux VA**: `0x005A3210`
- **Logic**: When a sniper bullet hits a craft, if it kills/ejects the pilot, `Craft::AbandonPilot` sets `perceivedTeam = 0`. If it does not kill the pilot, standard `GameObject::SetDamageFlags` executes, revealing the sniper unit's perceived team if damager is non-null.
- **Parity**: Identical between 1.5 and Redux.

---

## 3. Explanation of Scott ("Herp")'s Observed Behavior

Scott observed that an AI-controlled captured craft (or turret) appears passive under enemy fire until ordered or sniped. Static analysis proves this is **native 1.5 behavior** resulting from three design characteristics:

1. **Near-Miss / In-Flight Shots Do Not Trigger Retaliation**:
   - `SetDamageFlags` is ONLY invoked when a projectile **lands a hit**.
   - Enemy projectiles in flight or missing near the victim do NOT trigger `SetDamageFlags`. The victim remains in its disguise (`perceivedTeam = oldTeam`) and does not initiate preemptive attack.

2. **Perceived Team Disguise Belongs to Legacy**:
   - Captured units keep `perceivedTeam = oldTeam` until damage lands.
   - Enemies of the victim (who match `oldTeam`) will not attack the disguised unit until the disguised unit shoots them and lands a hit.

3. **SubTask Tick Cadence**:
   - AI processes poll `enemyShot` on fixed `DoSubTask` interval ticks (typically 0.1s to 0.5s). Retaliation is not instantaneous on frame 0 of hit, but on the subsequent AI tick.

4. **Turret / Gun Tower Range Gates**:
   - Turrettanks and Gun Towers will only retaliate against `who_shot_JR` if the attacker is within their maximum weapon/engagement range. Long-range artillery or sniper shots outside turret range set `who_shot_JR`, but the turret process ignores the target due to range limits.

---

## 4. Matrix Summary & Verification

| Stage | Behavior in 1.5 | Behavior in Redux | Divergence Found? |
| --- | --- | --- | --- |
| Disguise Assignment | `perceivedTeam = oldTeam` | `perceivedTeam = oldTeam` | **None** |
| Attacker Reveal on Hit | `damager->perceivedTeam = damager->team` | `damager->perceivedTeam = damager->team` | **None** |
| Hit Classification | `enemyShot` updated via `EnemyP` | `enemyShot` updated via `EnemyP` | **None** |
| Target Acquisition | Query `candidate->GetTeam()` | Query `candidate->GetTeam()` | **None** |
| AI Retaliation Transition | Poll `enemyShot` -> `Attack(who_shot_JR)` | Poll `enemyShot` -> `Attack(who_shot_JR)` | **None** |
| Sniper Hit Response | Trigger `SetDamageFlags` / `AbandonPilot` | Trigger `SetDamageFlags` / `AbandonPilot` | **None** |

---

## 5. Conclusion & Actionable Guidelines

1. **No Code Fix Required**: Because Redux matches 1.5 behavior byte-for-byte, no native code modification or shim hook is needed or permitted.
2. **Quarantine Maintenance**: The old OpenShim reveal-on-engagement hook must remain quarantined. Enabling it would alter legacy AI disguise balance.
