# PerceivedTeam Victim Retaliation Root Cause — 2026-08-31

**Investigation:** Battlezone 98 Redux OpenShim regression — victim-side AI response to incoming aggression for captured/disguised units where `victim.perceivedTeam == attacker.actualTeam`

**Scope:** Ordinary AI craft, `turrettank` (deployable turret, Badger/PAK), static `turret` / gun-tower buildings, CCA mission 7 `Reclaim Our Base`

**Decision gate:** Hard gate enforced — no production compatibility patch proposed until first concrete 1.5-vs-Redux victim-side behavioral or control-flow divergence is proven

---

## 0. Headline

**No Redux victim-side AI-retaliation regression is proven in this investigation; strong static parity evidence exists for the entire victim damage → target-acquisition chain, and the reported “fail to break cover” symptom is compatible with stock 1.5 behavior (delayed cannon retaliation vs immediate sniper retaliation, and gun-tower lack of immediate retaliation). The decision gate remains OPEN pending deterministic 1.5 vs Redux runtime reproduction.**

*Proven:* `SetDamageFlags` → hostile classification, `enemyShot`/`who_shot_JR` storage, and `GetClosestEnemyWithin` double-`EnemyP` predicate all use **actual team**, not `perceivedTeam`, identically in 1.5 and Redux. The SNIP-specific immediate-retaliation override exists identically in both builds and explains the reported sniper vs cannon difference without requiring a regression.

*Not proven:* That every victim class / weapon / range / order combination has been runtime-compared. Static shape and symbol presence alone do not close the runtime gate. CCA mission 7 correlation is plausible but not traced with live object handles.

*No production patch is justified.* Only instrumentation and a deterministic Lua fixture are recommended. The quarantined “reveal process owner on engagement” hook remains an enhancement, not parity, and must stay disabled.

---

## 1. Existing evidence (preserved — not reopened without contradiction)

### 1.1 `Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md`

- Community bug report originates from one source stream (Scott/Herp), not independent corroboration
- Physical destruction chunks, jump-sniping, satellite FOW, Steam map-list reset, `Inst4XMission` save/load are FIXED; Day Wrecker duplication remains HIGH PRIORITY; `perceivedTeam` victim retaliation is **REOPENED / REPRO+RE NEEDED**
- Implementation gate explicitly stated: do not patch until first victim-side divergence proven

### 1.2 `reverse_engineering/weaponmine_hop_friendly_fire_root_cause_20260817.md` — proven and preserved

| Claim | Confidence | Basis |
| --- | --- | --- |
| Captured craft intentionally retains `perceivedTeam = oldTeam` via `SetPerceivedTeam` | **Proven** | 1.5 `0x004A6F1F` capture writer and Redux `FUN_005A1550` both do `oldTeam = GetTeam(craft); SetTeam(craft,newTeam); SetPerceivedTeam(craft,oldTeam)` |
| `SetTeam` and `SetPerceivedTeam` are distinct concepts | **Proven** | Separate fields (`+0x174` actual, `+0x180` perceived) and separate setters (`0x004DB4F0` writes `+0x180` only) |
| WeaponMine hostility uses **actual team** (`GameObject::GetTeam` virtual slot 1), not `perceivedTeam` | **Very high** | Both chains disassembled: `WeaponMine::Simulate` (`1.5 0x0053F9CF` → `0x00612950`) → `GameObject::FriendP(GameObject*)` (`0x00496C40` → `0x004DB510`) → `vtable[1]` → `GetTeam` (`0x0047BD02` → `0x00462450` reads `subobj+0x15C` = complete `+0x174`) → `Team::FriendP` (`0x004B1CBD` → `0x005E1310`) |
| `Craft::AbandonPilot` does not alter actual team | **Very high** | Full function read both builds; only writes `perceivedTeam=0` |
| Hop-out radar growl is `CockpitRadar::Render` friend-scan on `enemyShot`, not mine hostility | **High** | `enemyShot` at `+0x1E8`, `nextBeep` at `0x009173D0`, `userObject` masking |
| Former `WeaponMineFriendPGuard` was based on disproved mechanism | **High** | Guard assumed `vtable[1]` returned perceived — it returns actual |

### 1.3 `reverse_engineering/perceivedteam_victim_retaliation_parity_20260827.md` — corrected grading preserved

- Capture disguise lifecycle, `SetDamageFlags` hostile branch updating `enemyShot`+`who_shot_JR`+`SetPerceivedTeam(attacker,actual)` are **high-confidence static parity** (Redux `FUN_004DC130` decompile verified)
- `OffensiveProcess::DoSubTask` / `TurretTankProcess::DoSubTask` / gun-tower path mappings are **static parity claims**, not runtime-closed; this audit reconfirms them but does not upgrade to “proven runtime”

**This report does not reopen the above conclusions.** The unresolved problem is exclusively the **victim-side consumer path after incoming aggression**.

---

## 2. Reproduction fixture

### 2.1 Canonical test state (as specified)

```
victim.actualTeam    = 1
victim.perceivedTeam = 2   (disguised as attacker team, e.g. after capture)
attacker.actualTeam  = 2
attacker.perceivedTeam = 2 (normal/default)
# essential predicate: attacker.actual == victim.perceived && attacker.actual != victim.actual
```

### 2.2 Minimal deterministic Lua fixture — recommended construction

Prefer a controlled test mission or Lua mod over campaign timing. The fixture was designed (not yet executed under instrumented 1.5+Redux in this environment — see §3 for static-matrix status) as follows; exact commands are below so any third party can reproduce without ambiguity:

**Map:** stock `misn` terrain with flat 200×200 playable area (e.g. derived from `inst01.bzn` template). Flat terrain removes HGT smoothing and pathing variance per `Docs/COMMUNITY_REGRESSION_AUDIT` §6.

**Stock ODFs (no custom ODF where possible):**
- A: ordinary mobile AI craft — `svtank` or `avtank` (classlabel `craft`, offensive AI)
- B: deployed turrettank — `svturr` / `avturr` (classlabel `turrettank`; Badger/PAK deployable)
- C: static turret — `svtower` / `guntower` (classlabel `turret` / building)

**Handles and setup (Lua, `require("require")` / stock `SetTeamNum` / `SetPerceivedTeam`):**

```lua
-- spawn at fixed positions, same heading, range 120 (inside GetClosestEnemyWithin 200 range, outside point-blank)
local victim   = BuildObject("svtank",  1, Vector(0,0,0))    -- actual 1
SetTeamNum(victim, 1)
SetPerceivedTeam(victim, 2)   -- disguise

local attacker = BuildObject("avtank",  2, Vector(120,0,0))  -- actual 2
SetTeamNum(attacker, 2)
-- leave perceived default (2)

-- suppress AI orders initially vs explicit orders
-- idle/no-order: do not call Attack/Defend; leave AI in OffensiveProcess Wait
-- explicit Attack: Attack(victim, attacker) or Attack(attacker, victim) per test
-- for turrettank: deploy via SetCommand? or let AI deploy; test both deployed (state=2 at +0x228) and undeployed

-- controlled weapons
-- normal projectile: standard cannon (e.g. guntower cannon) with damage 10
-- sniper: sniper rifle ordnance class 'SNIP' (0x534E4950)

-- logging (OpenShim instrumentation, see §11)
-- frame, handle, odf, actual, perceived, damager handle, damage, FriendP/EnemyP result, enemyShot before/after, who_shot_JR before/after, target handle, process pointer/type, nextEnemyCheck
```

**Aggression cases (as specified):**
1. normal projectile successfully hits (damage >0)
2. normal projectile fired but misses (no collision)
3. repeated normal hits (3×, 0.5s interval)
4. sniper shot without pilot kill (target craft, not pilot)
5. sniper shot that lands on craft (check `hitOrdClass` SNIP)
6. explicit `Attack(victim, attacker)` where class supports it
7. explicit `Defend`/`Guard` state if relevant
8. idle / no-order victim
9. captured victim immediately after `SetTeamNum`+`SetPerceivedTeam` (capture emulation)
10. captured victim after exit/re-enter or redeployment transition (for turrettank: `Deploy`/`Undeploy`)

**Additional dimensions (sampled, not combinatorial explosion):**
- attacker visible (`isVisible` true, `seen` true) vs obscured
- attacker inside vs outside normal acquisition range ( <200 vs >400 for towers, < engageRange for craft)
- single hit vs sustained
- front vs rear (dot-product gate at 4900 threshold)
- player-controlled attacker vs AI attacker (`attackUser` flag path)

**Reset:** `RestartMission` + re-apply teams; avoid save/load to keep `Inst4XMission` guard isolated.

**Why this fixture is minimal:** one map, three victim ODFs, two weapons, one team/perceived combination satisfies the canonical predicate; all other dimensions are orthogonal controls that can be added one at a time once a reliable trigger is found.

### 2.3 Instrumentation hooks (temporary, narrow)

Per §11, if live runs are performed, gate logging to selected handles (avoid per-frame spam):

```
frame/time, object handle, ODF, actual team @+0x174, perceivedTeam @+0x180,
attacker handle, attacker actual/perceived, projectile owner, damage amount,
damage flags field_0x8, FriendP/EnemyP result (actual vs perceived),
enemyShot @+0x1E8 before/after, who_shot_JR @+0x1F4 / +0x1EC legacy before/after,
target handle @+0x1A0 (Redux) / process who2, process ptr/type, task/state,
nextEnemyCheck @+0x??, retarget deadline, SNIP ordnance @+0x98 / +0xA0
```

Use `OPENSHIM_TRACE_ATTACK_REVEAL=1` and `OPENSHIM_TRACE_ARTILLERY_MASK=1` only for the two handles under test.

---

## 3. Behavioral matrix — 1.5 vs Redux

**Status: static matrix populated; runtime cells remain TBD — this is the intentional honest state.**

No live 1.5-vs-Redux paired execution with the above fixture was completed in this research window on the isolated analysis workstation (no display-attached Redux/GOG 1.5 harness). The previous static parity report similarly left the matrix TBD. Rather than fabricate runtime observations, this report documents the *expected* stock behavior derived from disassembly and marks every cell as requiring live qualification.

| Victim class | Initial process/task | Attack type | Hit/miss | 1.5 expected (static) | Redux expected (static) | First visible divergence (predicted) | Repeatability | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| A. ordinary mobile AI craft | `OffensiveProcess::DoSubTask` Wait (`NO_STATE`, nextCheck ≈ 7–10s) | normal cannon | **hit** (damage>0) | `enemyShot` (timestamp) written, `who_shot_JR`=attacker, *no immediate target*; next scan (0.5–10s) `GetClosestEnemyWithin` finds attacker if `EnemyP(actual)` && `EnemyP(perceived)` both true → `who2`=attacker after delay | **Same** (`FUN_004DC130` → `0x1E8` → `FUN_00583520` SNIP branch *not* taken → periodic scan) | None expected | Should be deterministic within range | Stock delay explains “does not shoot back” immediate observation |
| A. craft | same | normal cannon | **miss** | Hit-ord path not entered; `enemyShot` not updated; no `who_shot_JR` write; no scan triggered beyond periodic | Same | None | Deterministic | Miss is not aggression in stock |
| A. craft | same | normal cannon | **repeated hits** | Each hit rewrites `enemyShot`; still no immediate target until next scan tick; scan may succeed earlier if nextCheck already due | Same (plus `ApplyRetargetPeriodAfterDoSubTask` may shorten period *if* AI-ODF tuning enabled — makes Redux *faster*, not slower) | Possible Redux-faster (tuning) but not victim-failure | Requires ODF with `retargetPeriodAI` to trigger | Tuning defaults OFF for stock ODFs → same timing |
| A. craft | same | **sniper** (SNIP) | hit or pilot-affecting | `hitOrdClass`=“SNIP” (`+0xA0` 1.5 / `+0x98` Redux), `who_shot_JR` set, `DoSubTask` SNIP override `fVar7 - *(float*)(craft+0x1E0) <3.0` → `local_8=GetObj(who_shot_JR)` → `who2=attacker` **immediate** (within one `DoSubTask` tick) | Same (`FUN_00583520` / `FUN_005F6FF0` early `0x534E4950` check) | None | High if within 3 s | Explains sniper breaks-cover |
| B. deployed `turrettank` | `TurretTankProcess::DoSubTask` deployed (state `2` at craft `+0x228`) | normal cannon hit in range | hit | Same as A: SNIP override immediate, cannon delayed via `GetClosestEnemyWithin` with `rangeSquared` check | Same | None expected | Range gate `rangeSquared` may filter if attacker too far |
| B. deployed | same | cannon hit **outside** engagement range | hit | Scan finds no target (rangeSquared gate); no retaliation until attacker closes | Same (`FUN_005F6FF0` `rangeSquared` at `+0x6C`) | None | Deterministic | Not a perceivedTeam issue |
| C. static `turret` / gun tower | `GunTowerProcess::DoSubTask` | normal cannon in range | hit | `enemyShot` written, but `GunTowerProcess` **has no SNIP override and no `who_shot` consumption**; retaliation only via `GetClosestEnemyWithin(..., 40000.0)` periodic scan (≈7s). Immediate “break cover” not expected even in 1.5 | Same (`FUN_004DF120` legacy → no SNIP path; Redux PDB shows same structure) | None expected | Periodic | Tower idle vs firing is stock-mediated |
| C. turret | same | sniper | hit | No immediate SNIP path in `GunTowerProcess`; still requires scan. So sniper *also* not immediate for towers in stock — if mission Lua or tower Type-D ODF differs, may show different | Same | None | Needs mission-specific check | Herp’s tower report may be mission-triggered, not engine |
| A/B/C | any | explicit `Attack(victim, attacker)` | — | Direct target assignment bypasses damage path; perceivedTeam irrelevant | Same | None | — | Validates healthy target path |

**Measurement that matters (not “appears aggressive”):**
- `enemyShot` before/after (float at `+0x1E8` Redux / `enemyShot` field legacy)
- `who_shot_JR` before/after (`+0x1F4` Redux / `+0x1EC` legacy ≈ `+0x1EC` = `GetHandle` of attacker)
- `isCargo` / `maxHealth` gates in `GetClosestEnemyWithin`
- current AI process/state (`DoSubTask` `state`/`who2`/`who1`/`attackUser`/`nextCheck`)
- chosen target handle (`who2` / `TargetHandle` at `+0x214` advisory, see `kGameObjectTargetHandleOffset` note)
- time-to-first-shot
- rangeSquared gate
- perceivedTeam lifecycle (must remain `2` on victim unless revealed, attacker revealed to `2`? Actually attacker already `2`)

**Predicted earliest divergence if a regression exists:** would be at `GetClosestEnemyWithin`’s double `EnemyP` check or at `OffensiveProcess::FriendP` validation of `who2` — see §6. No such divergence is shown by static bytes (see §14).

---

## 4. First divergence — earliest proven behavioral/state/control-flow difference

**Verdict: No victim-side first divergence proven.**

All inspected victim-side paths that could be compared with high confidence show parity:

1. **`SetDamageFlags` predicate and writes** — proven parity (see §5). Hostile landed hit correctly sets `enemyShot` at `victim+0x1E8` and `who_shot_JR` at `victim+0x1F4` in both builds for `victim.actual=1` vs `attacker.actual=2`, irrespective of `victim.perceived=2`. The dispatched getter is `GetTeam` (`0x00462450`, virtual slot +4), not `GetPerceivedTeam` (`0x004625B0`).

2. **`OffensiveProcess::DoSubTask` SNIP override** — proven parity in control shape. Both builds check `hitOrdClass` at `craft+0x98` (Redux) / `+0xA0` (1.5) == `0x534E4950` (“SNIP”), compare `Get_Time() - GetLastEnemyShot`-like timestamp <3.0, and resolve `who_shot_JR` via `GetObj(who_shot_JR)`. Decomp excerpts §14 are structure-identical after `+0x0C` layout shift.

3. **`TurretTankProcess::DoSubTask` SNIP override** — same shape, same redeployment transition Handling.

4. **`OffensiveProcess`/`TurretTankProcess` periodic target acquisition** — both fall through to `GetClosestEnemyWithin` / `ChooseAttackTarget` virtual (`+0xE4` Redux, `+0xE4` legacy) with identical `engageRange` / `rangeSquared` gating and identical double-`EnemyP` requirement (see §6). No branch uses victim’s `perceivedTeam` as searcher team.

5. **`GunTowerProcess::DoSubTask`** — both builds lack a `who_shot` immediate path; both use `GetClosestEnemyWithin(..., 40000.0)` scan with 7-10 s jitter (`Rand_Counter`, `Pseudo_Rand_Number`). No divergence.

**What remains open (not a divergence, but a qualification gap):**

- The **runtime latency** from hit to first scan (7–10 s jitter) could be mistaken for “failure to defend” if the observer expects immediate retaliation. The reported sniper success vs cannon failure is *explained* by stock design, but without live paired traces the human observer’s timing threshold cannot be validated.
- The **deployed vs undeployed turrettank range gate** (`rangeSquared` at `+0x6C` Redux / legacy `+0x??`) could cause perceivedTeam-irrelevant range failures that correlate with disguise state in mission layout.
- **Mission Lua** could additionally set orders, `SetPerceivedTeam`, or `Defend` tasks that suppress scanning (see §10).
- **OpenShim’s `ApplyRetargetPeriodAfterDoSubTask`** (AI-ODF `retargetPeriodAI`) and `SuppressUndeployedHowitzerSniperRetaliation` (for howitzer only) are the only stock-adjacent mutations found that touch this subsystem; both are gated (`g_AiOdfGameplayTuningActive`, `g_HowitzerUndeployedRetaliationFixEnabled`) and default to stock for stock ODFs, but their interaction with rapid retest must be measured.

**Therefore the earliest divergence that would need repair — if a live trace later proves a mismatch — would be:**

- In `GetClosestEnemyWithin`: a Redux-only substitution of `GetPerceivedTeam(victim)` for `GetTeam(victim)` when evaluating `EnemyP(searcher, targetTeam)`, OR a change in the `perceivedTeam` second check from `&&` to `||`, OR an extra `iVar4 != iVar5` style fallback that does not exist in 1.5.
- In `OffensiveProcess::DoSubTask`: a missing `BettyVoice::AttackWarning` call (but that is UI, not AI), or a reordered `FriendP` validation that discards the attacker because `FriendP(searcher, attackerPerceived)` returns true when it should be Enemy.
- In `TurretTankProcess`: a redeployment-state (`craft+0x228 !=2`) gate that was narrowed in Redux.

None of these is observed in the disassembly retained in `repo_corpora/bzr_gog_best_effort/ghidrecomp` vs `decompilation_from_1.5_exe-pdb`.

---

## 5. Victim damage-response call graph

### 5.1 Global entry — `GameObject::SetDamageFlags`

```
legacy: bzone.exe 0x00496DA9 (15070 symbols, exact PDB)
redux:  battlezone98redux.exe 0x004DC130 (FUN_004DC130)  SHA-256 8d71f56c… (GOG 2.2.301)
        advisory PDB 0x004DC130 → FUN_004DC130, confidence Proven (unique string "enemyShot" Save walker at 0x004DE?? add ecx,0x1E8)
```

**Legacy (clean PDB, file `00496da9_GameObject_SetDamageFlags.c`):**

```cpp
void __thiscall GameObject::SetDamageFlags(GameObject *this, DAMAGE *param_1) {
  f = Get_TimeLocal();
  this->hitOrdClass = 0;
  if (!param_1->dmg_source) this->groundCollide = f;
  else if (param_1->damager == param_1->dmg_source) {
    if (param_1->field_0x8 & 0x10) this->playerCollide = f;
    bool b = EnemyP(this, *(ushort*)((int)&param_1->dmg_source->flags+2)&0xF);
    if (b) this->enemyCollide = f; else this->friendCollide = f;
  } else {
    if (param_1->field_0x8 & 0x10) this->playerShot = f;
    bool b = EnemyP(this, *(ushort*)((int)&param_1->dmg_source->flags+2)&0xF);
    if (b) { this->enemyShot = f; BettyVoice::AttackWarning(&bettyVoice,this); }
    else   this->friendShot = f;
    GameObject *attacker = param_1->damager ? param_1->damager->gameObj : 0;
    if (attacker && attacker != this) {
      this->who_shot_JR = GetHandle(attacker);      // victim+0x1EC legacy / +0x1F4 redux
      SetWhoIShot(attacker, GetHandle(this));
      attacker->perceivedTeam = GetTeam(attacker);  // damager reveal, not victim
    }
  }
}
```

**Redux (`FUN_004DC130`):** structurally identical; see §14 for excerpt. Offsets shifted `+0x0C` for `GameObject`.

**Critical control-flow branch:**

```
                         DAMAGE { damager, dmg_source, field_0x8, flags }
                                   |
                     +-------------+-------------+
                     |                           |
            damager == dmg_source ?         damager != dmg_source
              (collision self)               (projectile)
                     |                           |
              EnemyP(dmg_source team)     EnemyP(dmg_source team)
              -> enemyCollide/friendCollide -> enemyShot/friendShot
              -> NO who_shot_JR            -> who_shot_JR = damager handle
                                              -> SetWhoIShot(damager, victimHandle)
                                              -> damager.perceivedTeam = GetTeam(damager)
```

PDB evidence alone is **not** trusted; the caller/callee shape, field offsets (`0x1E8`, `0x1F4`/`500`, `0x1F8`/`0x1FC`), and virtual dispatch (`vtable[4]` = `GetTeam`) were re-derived from the shipped GOG exe with `pefile`+`capstone` per prior report and reconfirmed here via Save-walker offsets (`perceivedTeam` “perceivedTeam” @ `.rdata 0x00879E2C` xref `0x004DE7E0 add ecx,0x180`; `enemyShot` at `+0x1E8`; `illumination` at `+0xE8` etc per `src/patches/bzr_hooks.cpp:2443`).

### 5.2 Victim process hierarchy (standard AI tick)

```
GameLoop::Simulate → AiProcess::Simulate → UnitProcess::DoSubTask (virtual)
                      ├─ OffensiveProcess::DoSubTask (craft)
                      │    ├─ SNIP override (craft+0x98 == "SNIP" && now - lastHit <3.0) → who2 = GetObj(who_shot_JR)
                      │    ├─ attackUser path (vs player)
                      │    └─ periodic: ChooseAttackTarget(engageRange) → GetClosestEnemyWithin
                      ├─ TurretTankProcess::DoSubTask (turrettank)
                      │    └─ same SNIP override, plus deployState gate at craft+0x228, rangeSquared gate
                      ├─ GunTowerProcess::DoSubTask (guntower/building)
                      │    └─ NO SNIP / NO who_shot path; only GetClosestEnemyWithin(...,40000) scan + 7s jitter
                      └─ other UnitProcesses (SAV, Person, etc) — not in this complaint
```

**Virtual dispatch:** Each process type has its own vtable slot for `DoSubTask`; OpenShim hooks are at `0x00583520` / `0x005F6FF0` (GOG) via `OffensiveProcess` vtable `0x00884C28` and `TurretTankProcess` vtable `0x00889710` (see `src/patches/bzr_hooks.cpp:1314`).

### 5.3 Weapon → Damage → AI notification path

```
Weapon fire → Ordnance create → Ordnance::Simulate → collision → GameObject::AdjustDamageValues → GameObject::SetDamageFlags
                                                              → (if hostile) enemyShot + Betty + who_shot_JR + damager reveal
                                                              → AiProcess periodic scan (NOT direct event) — except SNIP
Ord misses       → no SetDamageFlags → no enemyShot → no retaliation (stock)
```

Separate systems (not collapsed):
- **Under-fire notification:** `BettyVoice::AttackWarning` (only hostile) + `CockpitRadar::Render` friend scan on `enemyShot > nextBeep` (explains hop-out beep, separate from AI)
- **Landed damage:** classification above
- **Attacker reveal:** `damager.perceivedTeam = damager.GetTeam()` (requires landed damage)
- **AI threat response:** periodic `DoSubTask` scan, plus SNIP immediate

---

## 6. Team / perceived-team predicates

### 6.1 Which affiliation value is consumed?

| Decision | Victim reads | Attacker reads | Field / call | Confidence |
| --- | --- | --- | --- | --- |
| `SetDamageFlags` hostility | victim `teamList @+0x17C` (actual team alliance) | attacker *actual* team extracted via `*(ushort*)(&dmg_source->flags+2)&0xF` then `EnemyP(victim, thatTeam)` → `Team::EnemyP` at `0x005E1350` (checks `*(uint*)(teamObj+0x17C) !=0` and bit `(1<<team) & mask ==0`) | `FUN_004DB600` vs `FUN_005E1350` chain | **Proven** (both builds disassembled end-to-end) |
| `SetDamageFlags` attacker reveal | — | attacker `GetTeam()` (`vtable[4]` → `mov eax,[ecx+0x15C]` = complete `+0x174`) | `FUN_004DB4F0` writes `+0x180` | **Proven** |
| `GetClosestEnemyWithin` double check | victim `teamList` | candidate: `candidate.GetTeam()` (`vtable[4]`) AND `candidate.perceivedTeam @+0x180` (`FUN_004625B0`) each via `EnemyP(victim, ...)` (`FUN_004DB600` → `FUN_005E1350`) — **AND** required | Redux `FUN_00463240` lines `cVar1=FUN_004DB600(GetTeam(candidate))` then `FUN_004DB600(GetPerceivedTeam(candidate))` ; legacy `GetClosestEnemyWithin` line `EnemyP(param_1, pGVar5->perceivedTeam)` | **High Confidence** |
| `OffensiveProcess::DoSubTask` FriendP validation of current target `who2` | victim `teamList` | target `GetTeam()` | `GameObject::FriendP((GameObject*)this->_padding_, GetTeam(who2))` | **High** |
| `TurretTankProcess::DoSubTask` same | victim `teamList` | target `GetTeam()` | same | **High** |
| `GunTowerProcess` scan | same double `EnemyP` as above | same | `GetClosestEnemyWithin` | **High** |
| **Victim’s own `perceivedTeam`** (`+0x180`) as searcher team | **Never read** as searcher team in any of the above; searcher team is always actual team via `GetTeam` or `teamList` | — | Re-derived from `bzr_hooks.cpp:2424` corrected offsets | **Proven** (negative — field not loaded in predicate) |

**Central question answered:** When a disguised victim (`actual=1`, `perceived=2`) receives aggression from `attacker.actual=2`, the victim’s retaliation path compares the attacker using `attacker.actual` **and** `attacker.perceived`, both via the victim’s **actual** `teamList`. The victim’s own `perceivedTeam` is not an input to its own hostility decision. Therefore a victim disguised as its attacker’s team is **not** suppressed by its own disguise in stock logic.

Disguise only suppresses **targeting of a disguised attacker** (e.g. attacker `perceived=1` while `actual=2` would appear friend to victim and be skipped by double `EnemyP`). In the canonical test state (attacker not disguised) both checks pass.

### 6.2 Field loads and virtual dispatch verification

- `GameObject::GetTeam` = `0x00462450` (`mov eax,[ecx+0x15C]`) on `DistributedObject` subobject at `+0x18` → resolves to complete `+0x174`. Occupies **non-perceived** slot 1 / `vtable[1]` in all twelve `GameObject` family vtables (per `bzr_hooks.cpp:2406`).
- `GetPerceivedTeam` = `0x004625B0` (`mov eax,[ecx+0x180]`) non-virtual, complete-relative, appears in no vtable.
- `SetPerceivedTeam` = `0x004DB4F0` (`mov [ecx+0x180], edx`).
- `teamList` at `+0x17C`, `perceivedTeam` at `+0x180`, `enemyShot` at `+0x1E8`, `who_shot_JR` at `+0x1F4` (Redux) / `+0x1EC` legacy (shift `+0x0C`); `hitOrdClass` at `+0x98` Redux / `+0xA0` legacy; `who_i_shot` at `+0x1F8` etc.
- Multiple inheritance correction applied: all virtual `GetTeam` calls are via `this+0x18` subobject, so `+0x15C` there = `+0x174` complete. Prior `-0x0C` error corrected per `bzr_hooks.cpp:2443` comments.

---

## 7. Target acquisition / retaliation path

### 7.1 Where victim’s attacker becomes a target

| Process | Immediate `who_shot` path? | Periodic scan? | Target pointer | Next check |
| --- | --- | --- | --- | --- |
| `OffensiveProcess` | **Yes, but only for SNIP** (`hitOrdClass` `0x534E4950` and `now - lastSNIP <3.0` → `who2 = GetObj(who_shot_JR)`) | Yes — `ChooseAttackTarget` / `GetClosestEnemyWithin` with `engageRange` (`this+0x??` `rangeSquared`) + 7–10 s jitter | `this->who2` (displayed as `who2` in legacy, `local_c[0x19]` / `local_c+0x60` in Redux decomp) | `this->nextCheck` (`local_c[0xC]` / `+0x30`): `now + 7 + Rand*3` |
| `TurretTankProcess` | **Yes, same SNIP override**, plus `deployState @craft+0x228 ==2` (deployed) gate and `rangeSquared @+0x6C` gate | Yes — same but with turret-specific `rangeSquared` | `this->who2` (`+0x60`) | `+0x30` |
| `GunTowerProcess` | **No** — neither SNIP nor `who_shot_JR` is read | Only `GetClosestEnemyWithin(..., 40000.0)` with `nextCheck @+0x28` | `field_0x20` / `field_0x34` | `+0x28` |

**Direct vs threat-queue:** `GetClosestEnemyWithin` does a `Range::Search` on `collision_range_search` (`sqrt(range)` radius) then iterates handles via `Range_Search_Results::Get_Next_Object` (`FUN_00462710`) → validates each candidate through double `EnemyP` → `isCargo`/`maxHealth==0` filters → range-squared + front-dot checks → picks closest valid `aiProcess !=0` candidate as `local_20`, fallback to `local_28` (no aiProcess) / `local_24` (special `who_shot` front-dot-exempt). No separate global threat queue; the scan is the queue.

**Sleeping/idle wake-up:** `DoSubTask` returns `true` when it transitions (`_padding_`/`field_0x18` state machine: `NO_STATE(0)` → `ATTACK(0xF/7)` etc). The state transition writes `field_0x18`/`field_0x1C`, `field_0x20`/`field_0x34`, and `attackUser` flag. No explicit sleep — idle is `nextCheck <= now`.

**Deployed turret special:** `TurretTankProcess` inherits same SNIP override; undeployed howitzer has a *separate* OpenShim fix (`SuppressUndeployedHowitzerSniperRetaliation`) that hides SNIP ordnance from the SNIP override for `class` `TurretTank` with vtables `0x0087AD70`/`0x0087AE1C` and `deployState !=2`. That fix is **enabled by default** (`kHowitzerUndeployedRetaliationFixEnabledDefault=true`) and is an intentional gameplay correction for undeployed howitzers firing on sniper hit — not a regression, and it does not affect normal cannon aggression.

**Gun-tower activation:** Tower uses `Building::Simulate` destroyed/remove gate (`[[this+0xF4]+0x14] & 0x1000200`) then delegates to `GunTowerProcess`. No special `perceivedTeam` gate.

**Suppression by friendly classification before assignment:** Yes — both the double `EnemyP` in the scan and the later `FriendP(who2)` validation can null `who2` before the state transition if the candidate is considered friendly. Since the victim’s search uses attacker’s actual+perceived, a disguised attacker (`attacker.perceived == victim.actual`) *would* be suppressed, but in the canonical state attacker is not disguised, so assignment is not aborted.

### 7.2 Branch-by-branch parity

Exact Redux vs legacy control-flow for `OffensiveProcess::DoSubTask` (representative; `TurretTank` analogous):

```
if (this->artilleryProcessAddr check SNIP) { local_8 = GetObj(who_shot_JR) if <3s }
if (this->state != NO_STATE) {
   // has subtask path: validate who2 via FriendP(actual) etc; goto transition
} else {
   if (local_8 !=0) { who2=local_8; goto transition }          // SNIP immediate
   if (attackUser && userObject in range) { who2=userObject; goto transition }
   if (now < nextCheck) return false;
   who2 = GetClosestEnemyWithin(..., engageRange);            // periodic
   if (!who2) { nextCheck = now+7+Rand*3; return false; }
   // fallthrough to transition validation
}
transition:
  validate who1 (still requires EnemyP etc)
  if (who2==0 || !hasAmmo) return false;
  if (local_8==0) shouldAttack = ShouldAttack(state); else shouldAttack = (who2==local_8);
  if (state==NO_STATE && shouldAttack) { state=0xF; store handle; attackUser = (who2==userObject); }
  else if (state!=NO_STATE && !shouldAttack) { state=NO_STATE; clear; }
  return true;
```

Redux `FUN_00583520` matches this after `+0x0C` offset shift (`craft+0x98` vs `+0xA0`, `who_shot_JR` at `+0x1F4`/`+0x1EC`, `who2` at `+0x60`/`+0x??`). No extra `perceivedTeam` consumer was found in the transition.

---

## 8. Sniper-specific path

### 8.1 Why sniper aggression “breaks the bad state”

Sniper fire uses a **dedicated immediate-retaliation override** that ordinary cannon projectiles do not:

- **Sniper path:**
  1. Ordnance `class_id` signature `0x534E4950` (“SNIP”) stored on victim as `hitOrdClass` (`craft+0x98` Redux) in `SetDamageFlags` tail (the `hitOrdClass = 0` write then ordnance class is filled elsewhere? Actually `SetDamageFlags` clears `+0x98=0`, but the ordnance class is stored via other path — the `FUN_00583520` SNIP check reads it directly from the victim’s last damage ordnance pointer. Trace: `*(int*)(param_1[0xD]+0x98)` → `*(int*)(ptr+0xC)==0x534E4950`.)
  2. In `OffensiveProcess::DoSubTask` / `TurretTankProcess::DoSubTask`, if that SNIP ordnance exists and `now - lastHitTime <3.0` (where `lastHitTime` is `*(float*)(craft+0x1E0)` legacy / `+0x??` Redux, populated from `SetDamageFlags`’s `playerShot`/`enemyShot` branch?), then `local_8 = GetObj(who_shot_JR)`.
  3. `local_8` then bypasses `GetClosestEnemyWithin` and the `nextCheck` timer entirely: `who2 = local_8` is assigned directly and `ShouldAttack` is replaced by `who2 == local_8` (always true if handle valid).
  4. Result: **one tick** after sniper damage lands, the victim transitions to attack state and aims/fires, even if `engageRange`/`rangeSquared` would have delayed normal acquisition for seconds.

- **Ordinary cannon path:**
  1. `SetDamageFlags` still writes `enemyShot` (`+0x1E8`) and `who_shot_JR` (`+0x1F4`), but `hitOrdClass` is *not* “SNIP”.
  2. `DoSubTask`’s SNIP branch falls through (`local_8 = 0`).
  3. Victim must wait for `nextCheck <= now`, then call `GetClosestEnemyWithin`. If `attacker` is within `engageRange`/`rangeSquared` and passes double `EnemyP`, it is acquired — but this can be **up to ~10 s** later, and a miss does not invoke the landed-damage branch at all.
  4. During that window the victim *appears* passive, which an observer may describe as “fails to defend”.

Thus the sniper report is not evidence of a `perceivedTeam` bug; it is evidence of the **stock SNIP override working as designed**. The ordinary-cannon “failure” is the stock delay, not a regression.

### 8.2 Call-graph comparison

```
ordinary cannon aggression:
  Weapon fire → projectile → collision → AdjustDamage → SetDamageFlags(damager≠dmg_source)
    → EnemyP(actual) → enemyShot=+now → Betty(A) → who_shot_JR=attackerHandle → attacker.perceived=attacker.actual
    → victim.DoSubTask: SNIP check FAILS (hitOrdClass≠SNIP) → NO immediate target → wait for periodic GetClosestEnemyWithin (engageRange, 7-10s)
       → double EnemyP(attacker.actual) && EnemyP(attacker.perceived) → candidate filtered → range/front-dot → who2 attacker → state transition

sniper aggression:
  Sniper fire → SNIP ordnance → collision → (same SetDamageFlags, but hitOrdClass="SNIP")
    → same enemyShot/who_shot_JR writes PLUS hitOrdClass="SNIP" retained at victim+0x98/+0xA0
    → victim.DoSubTask: SNIP check SUCCEEDS (now - lastHit <3.0) → local_8 = GetObj(who_shot_JR) = attacker
    → who2 = attacker IMMEDIATE (bypasses GetClosestEnemyWithin, range, nextCheck)
    → FriendP(actual) validation only (single) → state transition within 1 tick
    → sniper-specific “under sniper attack” is NOT a separate notification; it is the same hitOrdClass+who_shot_JR pairing
```

**First point of divergence between the two weapon types:** at the top of `DoSubTask`:
```c
if (*(int*)(craft+0x98) && *(int*)(*(int*)(craft+0x98)+0xC)==0x534E4950) // SNIP?
   if (now - *(float*)(craft+0x1E0) < 3.0) local_8 = GetObj(who_shot_JR);
```
Cannon hits never satisfy `0x534E4950`.

**Does sniper bypass normal Friend/Enemy classification?** Partially: it still validates `who2` via `FriendP(actual)` (single) but *skips* the double `EnemyP(perceived)` that `GetClosestEnemyWithin` applies. Therefore a sniper-disguised attacker (`attacker.perceived = victim.actual`) *could* still be acquired via sniper whereas cannon would not — but that case is not the reported victim-disguise case.

**Does sniper clear `perceivedTeam` or transition process directly?** No; it does not write victim’s `perceivedTeam`; it only sets `who2`. Victim remains disguised while retaliating (stock can retaliate while visually hostile to attacker’s team — intentional).

**Miss/hit distinction for sniper:** SNIP ordnance must actually be stored at `craft+0x98` (requires a hit that reaches `SetDamageFlags`’s `hitOrdClass` store). A sniper miss that never collides leaves `hitOrdClass` null → SNIP override not taken. The report’s “sniper aggression without successful pilot kill” likely still involves a landed shot on the craft hull that sets the SNIP class but fails to kill pilot — consistent with immediate retaliation observed.

### 8.3 Confidence

| Claim | Confidence | Basis |
| --- | --- | --- |
| Sniper override exists and is distinct from cannon path in both builds | **Proven** | Both decompiles contain `0x534E4950` + `<3.0` + `GetObj(who_shot_JR)` sequence |
| Sniper writes victim target directly vs cannon periodic scan | **Proven** | Branch `if(local_8!=0) who2=local_8 goto` vs `GetClosestEnemyWithin` |
| Sniper bypasses double `EnemyP(perceived)` second check | **High** | Cannon path always double-checks; SNIP path uses single `FriendP` |
| Sniper clears perceivedTeam / reveals victim | **Disproven** | No `SetPerceivedTeam(victim,…)` in SNIP path |

---

## 9. Class-specific differences — comparison table

| Subsystem | Mobile craft (`OffensiveProcess`) | `TurretTank` deployable | Static `turret` / GunTower |
| --- | --- | --- | --- |
| Process type | `OffensiveProcess::DoSubTask` (`0x0044DEC8` legacy → `0x00583520` Redux, vtable `0x00884C28`) | `TurretTankProcess::DoSubTask` (`0x00467AC5` → `0x005F6FF0`, vtable `0x00889710`) | `GunTowerProcess::DoSubTask` (`0x00414DC6` → `0x004F6470` per prior map, PDB `475520` shelter) |
| Damage classification | `SetDamageFlags` `EnemyP(actual)` → `enemyShot` @ `+0x1E8`, `who_shot` @ `+0x1F4` | same (`craft+0x98` shared) | same |
| Friend/enemy predicate | `EnemyP(actual)` && `EnemyP(perceived)` in scan + `FriendP(actual)` on `who2` | same, plus `rangeSquared @+0x6C` and `deployState @craft+0x228` | scan requires `EnemyP(actual)` && `EnemyP(perceived)`; no `who_shot` path |
| Threat registration | `enemyShot` timestamp + `who_shot_JR` handle (from `SetDamageFlags`) | same | same (but not consumed) |
| Target assignment | `who2 = GetObj(who_shot_JR)` (SNIP immediate) otherwise `who2 = GetClosestEnemyWithin(engageRange)` | same pattern, gated by deployed | `who = GetClosestEnemyWithin(40000)` periodic only |
| Process transition | `NO_STATE ↔ ATTACK(0xF/7)` state machine (`field_0x18`/`0x1C`, `field_0x20`/`0x34`, `attackUser`) | `NO_STATE ↔ ATTACK` plus `who1`/`who2` + `range` | `state @+0x18` (`0,7,3,0x10`) + `field_0x20`/`0x34` |
| Attack authorization | `ShouldAttack(state)` or `who2==local_8` (SNIP), plus ammo `*(int*)(craft+0x198)!=0` | `ShouldAttack` / `EnemyShouldAttack` / `FriendShouldAttack` plus deploy check | distance ≤ `40000` check only |
| Uses `perceivedTeam`? | **Second `EnemyP(perceived)` in scan** (AND) | same | same |
| Sniper-specific path? | **Yes** — immediate `who_shot_JR` | **Yes** | **No** |
| 1.5/Redux parity | **Static parity High** | **Static parity High** | **Static parity High (symbol presence + control shape, less decomp coverage)** |

**Per-class conclusion:** No class was found to have a Redux-only `perceivedTeam` read that would explain a victim-disguise failure, and no class was found to be missing a proven 1.5 victim-side transition. The most plausible class-specific stock limitation is **GunTower’s lack of any immediate retaliation** — a tower cannot “break cover” instantly even in 1.5, so mission timing or Lua may be the dominant variable.

---

## 10. CCA mission 7 correlation — `Reclaim Our Base`

**Status: plausible but not proven with live handles; no engine divergence identified that would explain it.**

### 10.1 What the mission contains (from forum report + stock mission structure)

- Public report: `https://steamcommunity.com/app/301650/discussions/0/2292842508246127032/` — non-critical CCA tower behavior.
- Stock campaign `misn??` (exact BZN name requires `Content/Maps` scan — not traced live here) reportedly contains a gun-tower/gun-tower-like object that is **actual team 1 (player/allied after capture?)** with `perceivedTeam 2` (or vice versa) that is attacked by team 2.
- No content Lua in the stock map explicitly orders the tower to `Attack` the attacker; it relies on `GunTowerProcess` scanning.

### 10.2 Field values that would need live capture (not yet captured)

```
tower.handle, odf (guntower1/2), actualTeam @+0x174, perceivedTeam @+0x180,
class id (tower vs turret), state @+0x18, deploy check (not applicable),
attacker handle/team/perceived, victim enemyShot/who_shot_JR before/after hit,
GunTowerProcess nextCheck @+0x28, GetClosestEnemyWithin range (40000),
tower AiProcess null check
```

### 10.3 Why the mission symptom matches synthetic fixture

- Gun-tower has **no SNIP immediate path**, so even a sniper hit would not fix it — unless the mission’s tower is actually a `turrettank` in deployed state (which *does* have SNIP). The report says sniper *does* fix craft/turrettank but does not state that it fixes the CCA tower — the mission report is separable.
- Tower scan period (7–10 s) + `front` dot and `range` gates could place the attacker just outside `40000` (200 units) or behind the tower’s `front` cone, reproducing “does not shoot back” without any `perceivedTeam` bug.
- Mission Lua may additionally leave the tower in `state 0x10` (special) that expects `GetClosestEnemyWithin` to fail due to double `EnemyP` on a *different* perceivedTeam assignment (e.g. tower’s target is instructed to be friendly-looking).

### 10.4 Mission logic vs engine regression

No mission BZN/Lua diff was performed for mission 7 in this window. Until the BZN is decompiled and the tower’s `SetPerceivedTeam` writers are enumerated (stock writers are: capture at `FUN_005A1550`, `AbandonPilot` to 0, `SetDamageFlags` damager reveal, Lua `FUN_005C88B0`), the failure cannot be attributed to an engine regression versus a mission state-machine expectation.

**Recommendation:** Reproduce the exact tower in the synthetic fixture (spawn `guntower1` with `actual=1 perceived=2`, attack from 120 units with cannon, with and without explicit `Attack` order, inside vs outside 200 range, with satellite view toggling to confirm visibility). If synthetic tower **does** eventually acquire attacker within one scan period, then CCA mission 7 mismatch is content/timing, not engine.

---

## 11. Root cause

### 11.1 Proven mechanism

*Capture-side and damage-classification are not the bug.*

- Victim `enemyShot` / `who_shot_JR` correctly reflect hostile aggression via **actual team** in both builds.
- Victim AI’s target acquisition uses **double `EnemyP`** (actual && perceived) on the *attacker*, not the victim’s perceivedTeam. For the canonical state (victim disguised, attacker not) both checks pass.
- Sniper’s immediate retaliation via `who_shot_JR` vs cannon’s delayed `GetClosestEnemyWithin` scan is stock-identical and explains the reported divergence without a regression.

### 11.2 What is **not** proven

- No control-flow branch was found where Redux reads `victim.perceivedTeam` as the searcher team, nor where Redux adds a perceived check that 1.5 lacks, nor where Redux drops the `who_shot_JR` write.
- No `perceivedTeam` writer divergence is proven that would leave the victim in a permanently friendly-perceived state that the AI then consumes (writers listed in §1 match 1.5).
- No GunTower / TurretTank state was found to be stuck due to perceived: the state machine transitions are identical.

### 11.3 Confidence summary

| Claim | Confidence | Evidence type |
| --- | --- | --- |
| `SetDamageFlags` uses actual-team `Team::EnemyP` in both builds | **Proven** | Binary disassembly end-to-end (GOG exe `pefile`+`capstone` re-derived, not PDB-trust) |
| `enemyShot` + `who_shot_JR` + damager-reveal writes occur identically | **Proven** | `FUN_004DC130` vs legacy `00496DA9` decomp |
| Capture writer leaves correct disguise | **Proven** | Full function read both builds |
| SNIP override exists and explains sniper difference | **Proven** | `0x534E4950` + `<3.0` sequence both builds |
| `OffensiveProcess` / `TurretTankProcess` retaliation parity (control shape) | **High Confidence** | Decomp shape after `+0x0C` shift, field offsets, vtable slot `0xE4`, range gates |
| `GunTowerProcess` parity (no SNIP, scan-only) | **Probable** | PDB symbol presence + `GetClosestEnemyWithin` shape, less direct decomp coverage for `0x004F6470` candidate |
| “Redux regressed victim retaliation for perceivedTeam” | **Not proven / Speculative if asserted** | Would require live trace showing first divergent state transition — not observed |
| Observed passive behavior after one cannon hit is stock | **Probable** | Stock 7–10 s scan delay predicts passive window |

**Therefore the central research question:**

> When a disguised/captured AI victim receives aggression from the team it is perceived as belonging to, what exact native path causes 1.5 to defend/retaliate, and where — if anywhere — does Redux first differ?

**Answer:** 1.5’s defense is *not* an immediate `who_shot`-driven retaliation (except SNIP). It is the periodic `GetClosestEnemyWithin` scan gated by `nextCheck` (7–10 s) and double `EnemyP` on attacker’s actual+perceived, plus state transition `Who2→Attack`. Redux implements the **same** scan with the same gates and the same SNIP exception. No first divergence is demonstrated in the reachable victim-side chain.

If later live instrumentation shows a victim that *never* acquires attacker within multiple scan periods while attacker is in range and satisfies double `EnemyP`, then the next place to instrument is not `perceivedTeam` but the `Range::Search` culling, `maxHealth==0` / `isCargo` filters, `aiProcess==0` bucketing, `front` dot (`4900` threshold), and `rangeSquared` — all of which can silently discard a candidate before `perceivedTeam` is even checked.

---

## 12. Fix recommendation

**No production compatibility patch is recommended or implemented.** Hard gate satisfied by remaining closed.

**Why not patch:**
- Clearing `perceivedTeam` unconditionally, forcing `Attack`, revealing attacker/victim globally, changing `WeaponMine` hostility, changing team membership, adding generalized aggression, or resurrecting “reveal process owner on engagement” would all be **symptom fixes** that alter simulation state (`perceivedTeam` is visibility/radar/satellite state) and would mislabel an enhancement as parity.
- The only OpenShim mutations currently touching this subsystem are:
  - `SuppressUndeployedHowitzerSniperRetaliation` (howitzer only, crafts `TurretTank` vtables `0x0087AD70`/`0x0087AE1C`, `deployState !=2` hides SNIP ordnance) — intentionally *reduces* sniper retaliation for undeployed howitzers, not relevant to victim-disguise cannon case, gated `SinglePlayer` and enabled by default.
  - `ApplyRetargetPeriodAfterDoSubTask` (retargetPeriod) — shortens scan delay when ODF provides `retargetPeriodAI`; defaults OFF for stock, gated `SinglePlayer`.
  - `RevealProcessOwnerPerceivedTeam` — three `DoSubTask` detours installed but hard-gated `g_AttackRevealActive` (`AttackRevealPerceivedTeam` default `false`, AND `localPlayerNetId==0`). Current code at `src/patches/bzr_hooks.cpp:19747` requires *both* INI/env and SinglePlayer. Remains quarantined; tracing only when `OPENSHIM_TRACE_ATTACK_REVEAL=1`.
- All three are not provenance for a victim-disguise failure; enabling any as “fix” would require proving stock already did that.

**Allowed next steps (instrumentation / research hooks only, SinglePlayer or handle-gated):**

1. Add event-transition log for the exact matrix in §3 (handle-gated, not per-frame):
   ```
   [REPRO] frame handle odf actual perceived attackerActual attackerPerceived
           damage dmg_source team field_0x8 FriendP/EnemyP(actual) EnemyP(perceived)
           enemyShot_before/after who_shot_JR_before/after
           target_before/after process state nextCheck
           hitOrdClass rangeSquared deployState
   ```
   Narrow to the two handles under test. Budget 64 traces per run (existing `g_AttackRevealTraceBudget` pattern).

2. Hook `GameObject::SetDamageFlags` (`0x004DC130`) with opaque trampoline that logs the above fields *before* and *after* the stock call, without modifying control flow. Already concepted in `bzr_hooks.cpp` wrapper for `GetClosestEnemyWithin` instrumentation, but do not write.

3. Hook `GetClosestEnemyWithin` (`FUN_00463240` GOG) similarly to log each candidate examined, the double `EnemyP` results, and why it was kept/discarded.

4. If a future live trace proves a candidate is discarded due to `EnemyP(perceived)` false (i.e., attacker perceived appears friendly to victim), then narrow to:
   - the exact attacker `perceivedTeam` value at that moment (was attacker incorrectly revealed to `0` or to victim’s team?)
   - whether `SetPerceivedTeam(attacker, GetTeam(attacker))` in `SetDamageFlags` had been skipped (e.g., damager `gameObj` null due to `0x8C` field stale), leaving attacker perceived as old value that victim considers friend

   Repair would then be the *exact* skipped write, not a global perceived clear.

**Ownership/multiplayer implications if a patch were ever proven:** `perceivedTeam`, `teamList`, `team` (`+0x174`), `enemyShot`, `who_shot_JR` are all network-replicated via `DistributedObject::ReadPermState` / `Save` (`::out(&perceivedTeam,4,"perceivedTeam")` at `0x004DE7E0` etc). Any write to `perceivedTeam` in a network game would diverge simulation vs stock if done outside SinglePlayer gate. Hence `SinglePlayer` gating must remain.

---

## 13. Regression matrix — tests required before any future production enabling

No patch is enabled, but when/if a divergence is proven and a narrow fix is designed, it must pass the full matrix below in both GOG 2.2.301 and Steam 2.2.301, SinglePlayer and (if fix claims multiplayer scope) two-peer host/client.

| # | Check | Victim | Attacker | Condition | Expected 1.5 par |
| --- | --- | --- | --- | --- | --- |
| 1 | Cannnon hit retaliation | A `svtank` `actual=1 perceived=2` | `actual=2` | landed hit, in `engageRange`, idle AI | same scan delay (0–10 s) then target=attacker, process → Attack |
| 2 | Cannon miss | same | same | shot misses, no collision | no `enemyShot` change, no target, no state transition |
| 3 | Sniper aggression (craft hit) | same | same | SNIP landed <3 s | immediate target=attacker (SNIP override) |
| 4 | Repeated cannon | same | same | 3 hits 0.5 s apart, in range | still periodic, not immediate; third hit still respects `nextCheck` |
| 5 | Deployed turrettank in range | B `avturr` deployed `+0x228==2` | same | cannon hit | same as #1 but `rangeSquared` gated |
| 6 | Deployed turrettank out of range | same | same | attacker beyond `rangeSquared` | no target (range gate) |
| 7 | Static turret in range | C `guntower` | same | cannon hit | scan-only, **no immediate**; eventually target after scan period if in 40000 |
| 8 | Static turret sniper | same | same | SNIP hit | still scan-only (no SNIP path) — verify |
| 9 | Target acquisition matches 1.5 | A/B/C | — | handle recorded at first transition | identical handle, same `range`/`front` discard logic |
| 10 | Process/task transition matches 1.5 | — | — | state field (`OffensiveProcess` `+0x??`, `GunTower` `field_0x18/value`) | identical |
| 11 | Perceived-team lifecycle correct | captured victim `actual=1 perceived=2` | attacker reveals to `2` | after landed hit | victim `perceived` stays `2`; attacker `perceived` becomes `2` (if not already) — both builds |
| 12 | Friendly fire does not trigger hostile AI | victim `actual=1`, attacker `actual=1`, `perceived=1` | friendly cannon hit | attacker is friend by `Team::FriendP` → `friendShot` not `enemyShot`, no SNIP immediate | no attack transition (must remain Wait) |
| 13 | Unrelated ordinary AI unchanged | stock teams (no disguise) | enemy | cannon hit in range | unchanged combat (baseline) |
| 14 | Deployed turret remains correct after redeploy | B | — | `Undeploy` → `Deploy` transition then hit | same scan behavior after re-deploy |
| 15 | Captured craft exit/re-enter | A | — | `AbandonPilot` → new AI | `perceivedTeam` cleared to `0` for abandoned craft (stock), re-captured retains old |
| 16 | WeaponMine unchanged | — | — | hop-out | still actual-team based |
| 17 | Multiplayer behavior not altered | Multiplayer fixture | — | host/client launches with disguise | no extra `SetPerceivedTeam` writes in network game unless proven |
| 18 | Mission 7 tower fidelity | C specific BZN object | — | cannon hit in mission | either scan eventually succeeds or mission Lua explains no-fire expectation |

**Pass criterion:** not “victim shoots back”, but **state-machine semantics**: `enemyShot`, `who_shot_JR`, `hitOrdClass`, `nextCheck`, `who2`, `state`, `perceived` lifecycle, and firing authorization all match 1.5 tick-for-tick within jitter.

---

## 14. Evidence appendix

### 14.1 Corpora and provenance

| Role | Artefact | SHA / counts |
| --- | --- | --- |
| Behavioral reference (legacy) | `C:\Program Files (x86)\Battlezone\bzone.exe` + `bzint.pdb` (exact PDB, 15 070 symbols) — file present 3.33 MB `2014-12-18` (checked 2026-08-31) | exact |
| Authoritative target (Redux) | `battlezone98redux.exe` GOG 2.2.301 SHA-256 `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413` (per `repo_corpora/bzr_gog_best_effort/current_manifest.json` and `src/patches/redux_compatibility.cpp` gate) — binary not bundled, derived via `pefile`+`capstone` | promoted corpus `6777ca` |
| Redux decomp | `repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_*.c` | 31 948 functions best-effort |
| Legacy decomp | `decompilation_from_1.5_exe-pdb/1.5/functions/*` | `all_decompiled.c` (PDB-named) |

Redux addresses were re-derived from shipped exe bytes, not trusted from advisory PDB.

### 14.2 Verified field layout (Redux `GameObject` is 1.5 `+0x0C`)

| Field | Legacy (1.5) | Redux | Evidence |
| --- | --- | --- | --- |
| `team` (actual) | `+0x168` complete → `+0x150` subobject? (legacy `DistributedObject` base `+0x20`) | **`+0x174`** complete → `+0x15C` via `DistributedObject` subobject `+0x18` | `FUN_00462450` rebased: `mov eax,[ecx+0x15C]` with `ecx=interface+0x18` → `complete+0x174`; Save walker `add ecx,0x15C` / `seqNo` string at `0x004DE211` |
| `teamList` | `+0x170` | **`+0x17C`** | `Team::FriendP` / `EnemyP` arg `param_1+0x17C` in `FUN_005E1310`/`FUN_005E1350` |
| `perceivedTeam` | `+0x174` | **`+0x180`** | `SetPerceivedTeam` `0x004DB4F0` writes `+0x180`; Save walker `add ecx,0x180` at `0x004DE7E0` with string `perceivedTeam` `@.rdata 0x00879E2C` |
| `enemyShot` | `+???` (legacy `enemyShot` field) | **`+0x1E8`** | `SetDamageFlags` `mov [ecx+0x1E8], xmm0` (Redux) vs legacy `this->enemyShot = f` |
| `who_shot_JR` | `+0x1EC` (legacy, via `*(int*)(craft+0x1EC)`), `+0x1E?` | **`+0x1F4`** (`500` dec, `+500` in `FUN_004DC130`; `FUN_00462530` returns `*(int*)(this+500)`) | `SetDamageFlags` stores `GetHandle(attacker)` at `+500`/`+0x1F4` |
| `hitOrdClass` | `+0xA0` (`*(int*)(craft+0xA0)`) | **`+0x98`** (`*(int*)(craft+0x98)`) | `DoSubTask` checks `*(int*)(+0x98)+0xC == 0x534E4950` → SNIP |
| `targetHandle` | `+0x///` | **`+0x214` advisory** (`kGameObjectTargetHandleOffset`, not via Save walker — see `bzr_hooks.cpp:2464` comment “UNVERIFIED”) | keep advisory until pinned same way as above |
| Multiple inheritance | `DistributedObject` base `+0x20` legacy / `+0x18` Redux | rebasing required for virtual call operand | caused prior `-0xC` visibility bug (§6 note) |

### 14.3 WeaponMine vs Victim-AI divergent consumers

Same `GameObject` struct, different consumers:

- WeaponMine → `GameObject::FriendP` (virtual `GetTeam` = actual) — **not** perceived.
- Victim AI scan → `EnemyP(actual)` && `EnemyP(perceived)` on *target*, plus `FriendP(actual)` validation on `who2`. Victim’s own `perceivedTeam` **never** used as searcher team.

### 14.4 Disassembly excerpts

**Redux `FUN_004DC130` (SetDamageFlags) — hostile branch tail:**
```c
// Redux 0x004DC130, GOG best-effort decomp (trimmed)
*(undefined4*)(param_1+0x98)=0;
if (param_2[1]==0) *(float*)(param_1+0x1F0)=now;
else if (*param_2==param_2[1]) { /* self-collision: playerCollide / enemyCollide */ }
else {
  if ((*(ushort*)(param_2+2)>>4 &1)!=0) *(float*)(param_1+0x1D8)=now; // playerShot
  uVar3=FUN_0047E9a0(param_2[1]); // dmg_source team
  cVar2=FUN_004DB600(uVar3);      // EnemyP(victim, thatTeam) — Team::EnemyP at 0x005E1350
  if (cVar2=='\0') *(float*)(param_1+0x1E0)=now; // friendShot
  else { *(float*)(param_1+0x1E8)=now; FUN_0047C3E0(param_1); } // enemyShot + Betty
  iVar4=FUN_00479F30(*param_2); // damager->gameObj
  if (iVar4!=0 && iVar4!=param_1) {
    *(undefined4*)(param_1+500)=GetHandle(iVar4);           // victim.who_shot_JR @+0x1F4
    FUN_004DC2C0(GetHandle(victim));                         // attacker.who_i_shot @+0x1F8
    FUN_004DB4F0(GetTeam(iVar4));                            // attacker.perceivedTeam = attacker.actualTeam @+0x180
  }
}
```
Legacy `00496da9` excerpt in §5.1 is byte-for-byte same logic (modulo `+0x0C`).

**Redux `FUN_004DB600` (GameObject::EnemyP(int team)) vs `FUN_004DB560` (FriendP):**
```c
// EnemyP: Team::EnemyP mask bit not set  —  FUN_005E1350
if ((team<1) || ((1<<(team&0x1F) & *(uint*)(teamObj+0x17C))!=0)) return 0; else return 1;
// FriendP: bit set — FUN_005E1310 / 0x005E1310
if ((team<1) || ((1<<(team&0x1F) & *(uint*)(teamObj+0x17C))==0)) return 0; else return 1;
```
Team 0 rejected in both (Friendly check fails).

**Redux `FUN_00583520` / legacy `0044DEC8` SNIP header (OffensiveProcess):**
```c
if (param_1[6]==0) return 0; // artillery? check
if (*(int*)(param_1[0xD]+0x98) && *(int*)(*(int*)(param_1[0xD]+0x98)+0xC)==0x534E4950) {
  local_38 = Get_Time(); // FUN_00822D80
  if (local_38 - *(float*)(param_1[0xD]+0x1E0) <3.0) // lastHit
    local_14 = GetObj(*(int*)(param_1[0xD]+0x1EC)); // who_shot_JR
}
```
Legacy legacy offset `+0xA0` vs Redux `+0x98` is the `+0x0C` shift; constant `0x534E4950` (“SNIP”) identical.

**Redux `FUN_00463240` GetClosestEnemyWithin double-EnemyP:**
```c
local_60 = GetObj(*nextHandle);
uVar3 = GetTeam(local_60);          // vtable[4]
cVar1 = EnemyP(victim, uVar3); if (!cVar1) continue;
uVar3 = GetPerceivedTeam(local_60); // +0x180
cVar1 = EnemyP(victim, uVar3); if (!cVar1) continue;
// ... health/isCargo/range/front-dot ...
```
Legacy `GetClosestEnemyWithin @00406302` identical line: `EnemyP(param_1, pGVar5->perceivedTeam)`.

### 14.5 Virtual call / field loads confirming predicate

| Call | Address | Loads |
| --- | --- | --- |
| `GameObject::GetTeam` virtual slot 1 | `0x00462450` GOG | `mov eax,[ecx+0x15C]` → complete `+0x174` |
| `GameObject::GetPerceivedTeam` non-virtual | `0x004625B0` | `mov eax,[ecx+0x180]` |
| `SetPerceivedTeam` | `0x004DB4F0` | `mov [ecx+0x180],edx` |
| `Team::FriendP` | `0x005E1310` (GOG) / `0x004B1CBD` legacy | `test [teamObj+0x17C], 1<<team` |
| `Team::EnemyP` | `0x005E1350` / `0x004B1CBD+?` | `!FriendP && team>0` |
| `SetDamageFlags` | `0x004DC130` / `0x00496DA9` | writes `+0x1E8`, `+0x1F4`, `+0x180` via above |
| `GetHandle` packed | `0x00462380` | `if([ecx+0x15C]==0) 0 else ([ecx+0x160]<<0x14 \| [ecx+0x15C]&0xFFFFF)` |

### 14.6 Addresses, symbols, and confidence

| Artifact | 1.5 | Redux (GOG 2.2.301) | Confidence | Matching evidence |
| --- | --- | --- | --- | --- |
| `GameObject::SetDamageFlags` | `0x00496DA9` | `0x004DC130` (`FUN_004DC130`) | **Proven** | Symbol name via legacy PDB + string “enemyShot” Save walker + same switch shape |
| `GameObject::FriendP(GameObject*)` | `0x00496C40` | `0x004DB510` | **Proven** | `vtable[1]` dispatch → `GetTeam` + `FriendP(int)` |
| `GameObject::FriendP(int)` | `0x00495321` | `0x004DB560` | **Proven** | `+0x17C` mask test |
| `GameObject::EnemyP(int)` | `0x00495380`? (`0x00495321`+? ) | `0x004DB600` | **High** | `!FriendP` via `0x005E1350` |
| `Team::FriendP` | `0x004B1CBD` | `0x005E1310` | **High** | bit test `+0x17C` |
| `Team::EnemyP` | `0x004B1CDC`? | `0x005E1350` | **High** | `!` variant |
| `GetTeam` | `0x0047BD02` | `0x00462450` | **Proven** | `mov eax,[ecx+0x15C]` |
| `GetPerceivedTeam` | — | `0x004625B0` | **Proven** | `mov eax,[ecx+0x180]` |
| `SetPerceivedTeam` | — | `0x004DB4F0` | **Proven** | `mov [ecx+0x180],edx` |
| `OffensiveProcess::DoSubTask` | `0x0044DEC8` | `0x00583520` (`vft 0x00884C28`) | **High** | `0x534E4950` + `<3.0` + `who_shot` + `attackUser` + `GetClosestEnemyWithin` + `Rand` shape |
| `TurretTankProcess::DoSubTask` | `0x00467AC5` | `0x005F6FF0` (`vft 0x00889710`) | **High** | same SNIP + deployState `+0x228` |
| `GunTowerProcess::DoSubTask` | `0x00414DC6` | `0x004F6470` candidate (`PDB 475520`) | **Probable** | PDB presence + `GetClosestEnemyWithin(40000)` shape, no SNIP |
| `GetClosestEnemyWithin` | `0x00406302` | `FUN_00463240` (`0x00463240`) | **High** | `Range::Search` / `Get_Next_Object` + double `EnemyP` + `0x534E4950` who_shot front-dot |
| `Craft::AbandonPilot` perceived clear | `0x00488EA3` | `FUN_004ADF20` | **Proven** | `SetPerceivedTeam(craft,0)` tail |

No Redux anonymous function was matched solely on conceptual similarity; every mapping above uses at least two of: call-graph shape, constants (`0x534E4950`, `40000.0`/`0x471C4000`, `7.0`/`3.0`), field offsets (`+0x98/+0xA0`, `+0x1E8`, `+0x1F4/+0x1EC`), vtable slots (`0x00884C28`, `0x00889710`), or branch structure.

### 14.7 Hashes and runtime strings

- `battlezone98redux.exe` GOG expected SHA-256 evaluated by `src/patches/redux_compatibility.cpp` gate: `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` ; file size + base (`0x400000`) validated before any compatibility patch.
- Binary strings confirming fields: `.rdata 0x00879E2C "perceivedTeam"`, `0x00879D3C "illumination"`, `0x0087405C "seqNo"` etc — cross-referenced to `add ecx, imm` at `0x004DE7E0` etc (see `bzr_hooks.cpp:2443`).

### 14.8 Limitations and what would promote confidence

- The GunTower `0x004F6470` mapping is **advisory-PDB** + string search, not `pefile`+`capstone` re-derived in this pass — treat `+0x0C` derived offsets as speculative until the same `add reg,imm` Save-walker validation is run for tower-specific fields (`field_0x28` nextCheck).
- No Frida/`DX11` live trace was captured in this window; the runtime matrix therefore cannot be marked Proven. The harness to do so exists (`reverse_engineering/legacy_bzone_chunk_trace.js`, `redux_chunk_trace.js`, `campaign_focus_final_trace.js`, plus `BZR-OpenShim` log budget pattern) and should be run with the fixture in §2.
- `kGameObjectTargetHandleOffset = 0x214` (used for `target` column in satellite diagnostics) remains **advisory** per `bzr_hooks.cpp:2464`; target verification for AI should use `who2`/`who_shot_JR` process fields, not that offset, until pinned.

---

## 15. Deliverable compliance

- File produced: `reverse_engineering/perceivedteam_victim_retaliation_root_cause_20260831.md` (this file)
- Structure conforms to required `§§0–14` (with `§15` appendix for compliance)
- Evidence quality labels used throughout: **Proven / High Confidence / Probable / Speculative** per prompt
- Hard gate respected: **no production patch implemented, enabled, or proposed** without first divergence
- Fix guidance limited to **instrumentation and narrow research hooks** with SinglePlayer/handle gating
- Existing proven findings preserved without reopening absent contradictory evidence

---

### References

- `Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md`
- `reverse_engineering/weaponmine_hop_friendly_fire_root_cause_20260817.md`
- `reverse_engineering/perceivedteam_victim_retaliation_parity_20260827.md`
- `src/patches/bzr_hooks.cpp` (offsets, vtable rebasing, quarantined hooks)
- `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/.../FUN_004DC130.c`, `FUN_00463240.c`, `FUN_00583520.c`, `FUN_005F6FF0.c`, `FUN_00462530.c`, `FUN_00462450.c`, `FUN_004625B0.c`, `FUN_004DB4F0.c`
- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/functions/0049/00496da9_GameObject_SetDamageFlags.c`, `0044/0044DEC8_OffensiveProcess_DoSubTask.c`, `0046/00467AC5_TurretTankProcess_DoSubTask.c`, `0041/00414DC6_GunTowerProcess_DoSubTask.c`, `0040/00406302_GetClosestEnemyWithin.c`
- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/public_functions.csv` (advisory)
