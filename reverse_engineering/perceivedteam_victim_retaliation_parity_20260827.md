# PerceivedTeam Victim AI Retaliation Parity Analysis: 1.5 vs Redux (2026-08-27)

## Executive Summary & Decision Gate Result

**Verdict: strong static parity evidence; runtime victim-side parity is still required before closing the regression.**

The original version of this report stated that no Redux regression exists and described the compared path as "100%" / "byte-for-byte" identical. That conclusion exceeded the evidence retained in the repository. An independent 2026-08-27 audit confirms important Redux-side pieces of the proposed chain and agrees that the old OpenShim reveal-on-engagement hook is not established as a 1.5 compatibility fix, but it does **not** independently close the full victim-side behavior matrix.

The correct evidence grade is therefore:

- **PROVEN / HIGH CONFIDENCE:** capture intentionally preserves a disguise through `perceivedTeam`; the inspected Redux hostility and damage-classification path uses actual-team relations; hostile landed damage updates the enemy-shot state and attacker handle; the old OpenShim reveal-on-engagement behavior remains an enhancement and must stay quarantined.
- **STATIC PARITY REPORTED, NOT RUNTIME-CLOSED:** the 1.5-vs-Redux `OffensiveProcess`, `TurretTankProcess`, gun-tower/turret response, target acquisition, and sniper-response comparisons documented below.
- **OPEN DECISION GATE:** reproduce the victim-side response in both 1.5 and Redux for captured craft, `turrettank`, and `turret` before declaring that Scott ("Herp")'s reported behavior is native parity rather than a Redux regression.

This grading is consistent with the earlier repository report `weaponmine_hop_friendly_fire_root_cause_20260817.md`, which explicitly left victim AI retaliation while disguised **not established**.

---

## 1. Scope

The specific complaint under test is separate from the already-closed WeaponMine hop-out theory. The open question is whether an AI-controlled captured/disguised victim in Redux responds to incoming fire the same way as Battlezone 1.5.

Relevant classes/paths:

- ordinary offensive craft;
- deployable turret (`classlabel = turrettank`);
- gun tower building (`classlabel = turret`);
- capture/disguise state (`perceivedTeam`);
- hostile landed damage (`SetDamageFlags`);
- target selection / hostility predicates;
- victim process transition to attack;
- sniper-specific behavior reported to break the passive state.

---

## 2. Data Layout and Disguise State

The existing repo investigation established the following relevant layout relationship:

| Field / Property | 1.5 Offset | Redux Offset | Semantics |
| --- | ---: | ---: | --- |
| actual `team` | `+0x168` | `+0x174` | true gameplay team |
| `group` | `+0x16C` | `+0x178` | unit group |
| `teamList` | `+0x170` | `+0x17C` | alliance/hostility relation |
| `perceivedTeam` | `+0x174` | `+0x180` | disguise / perceived allegiance |
| `enemyShot` | — | `+0x1E8` | timestamp of recent hostile hit |
| `who_shot_JR` | — | `+0x1F4` | handle of last relevant attacker |

`DistributedObject` is at a different base-subobject offset in the two builds, so virtual team accessors must be rebased before comparing field operands. This multiple-inheritance detail caused an earlier incorrect WeaponMine interpretation and remains important here.

### Capture behavior

The existing 1.5/Redux comparison reports the same intentional capture sequence:

```cpp
oldTeam = craft->GetTeam();
craft->SetTeam(person->team);
// pilot / AI ownership work
craft->SetPerceivedTeam(oldTeam);
```

This means a captured craft can be **actual team A** while continuing to appear as **perceived team B**. That disguise mechanism is legacy behavior, not itself a Redux defect.

---

## 3. Redux Damage Classification — Independently Rechecked

The repo-tracked GOG best-effort corpus contains `FUN_004dc130` for Redux `GameObject::SetDamageFlags`.

The important hostile-damage branch is visible directly in that decompile:

```text
actual attacker/team relation
    -> FUN_004db600(...)
    -> hostile branch
       -> write current time to victim +0x1E8
       -> FUN_0047c3e0(victim)
       -> resolve attacker object
       -> write attacker handle at victim +0x1F4
       -> reveal attacker through the inspected perceived-team writer path
```

This independently confirms that **a landed hit classified as hostile updates victim retaliation state in Redux**. It does not, by itself, prove that every victim process later consumes that state identically to 1.5.

The repo-tracked `FUN_004db600` / `FUN_005e1350` chain also supports the existing conclusion that the inspected hostility relation is based on the actual team/alliance mask rather than `perceivedTeam`.

### Evidence grade

**Redux side: high confidence.**

**1.5 parity: reported by the original static comparison, but not independently re-derived from a repo-tracked portable 1.5 decompile during this audit.** The exact 1.5 executable/PDB comparison used in earlier work was local-machine evidence.

---

## 4. Target Acquisition and Retaliation Process Claims

The original investigation maps the following pairs:

| Path | 1.5 | Redux | Current grade |
| --- | --- | --- | --- |
| `FriendP` / `EnemyP` actual-team relation | `0x00496C40`, `0x00495321`, `0x00495380` | `0x004DB510`, `0x004DB560`, `0x004DB600` | **High static confidence** |
| `OffensiveProcess::DoSubTask` | `0x0044DFA1` | `0x00583690` | **Static parity claim; runtime open** |
| `OffensiveProcess::WaitVsAttack` | `0x0044E150` | `0x00583950` | **Static parity claim; runtime open** |
| `TurretTankProcess::DoSubTask` | `0x00467B88` | `0x005F7143` | **Static parity claim; runtime open** |
| gun-tower / turret process | `0x004DF120` | `0x004F6470` | **Static parity claim; runtime open** |
| sniper response path | `0x004A8B10` and capture/pilot paths | `0x005A3210` and corresponding Redux paths | **Static parity claim; runtime open** |

The Redux advisory PDB retained in the repo does contain the expected `OffensiveProcess` symbols (`DoSubTask`, `WaitVsAttack`, `ChooseAttackTarget`, etc.), which supports the function identity work. However, symbol presence and static similarity are not a substitute for the requested behavioral matrix.

Do **not** describe these paths as "byte-for-byte identical" unless an exact binary comparison is actually recorded. Semantic similarity is the appropriate term where decompilation/control-flow comparison is the evidence.

---

## 5. What the Static Evidence Suggests About Scott ("Herp")'s Observation

The static model can plausibly explain some apparently passive behavior without requiring a regression:

1. Near misses do not necessarily invoke the landed-damage path that updates `enemyShot`.
2. Capture deliberately leaves `perceivedTeam = oldTeam` until stock reveal rules change it.
3. Retaliation is process/tick driven rather than necessarily frame-immediate.
4. Turret classes can apply range and target-validity gates after damage state is recorded.

Those are **candidate explanations**, not proof that Scott's observed captured-craft/turret behavior is native 1.5 behavior. The original wording "Static analysis proves this is native 1.5 behavior" is withdrawn pending runtime comparison.

---

## 6. Required Runtime Decision Matrix

Use a deterministic scenario where the same geometry, ranges, teams, and orders can be reproduced in both builds.

Minimum matrix:

| Victim | Stimulus | 1.5 result | Redux result | Gate |
| --- | --- | --- | --- | --- |
| captured offensive craft | normal cannon landed hit | TBD | TBD | OPEN |
| captured offensive craft | repeated cannon hits | TBD | TBD | OPEN |
| captured offensive craft | near miss only | TBD | TBD | OPEN |
| captured offensive craft | sniper aggression | TBD | TBD | OPEN |
| captured `turrettank` | normal landed hit in range | TBD | TBD | OPEN |
| captured `turrettank` | landed hit outside engagement range | TBD | TBD | OPEN |
| captured `turret` | normal landed hit in range | TBD | TBD | OPEN |
| captured `turret` | sniper / pilot-affecting stimulus where applicable | TBD | TBD | OPEN |

For each run record at minimum:

- actual team;
- `perceivedTeam`;
- attacker actual/perceived team;
- whether damage landed;
- `enemyShot` before/after;
- `who_shot_JR` before/after;
- current AI process/state;
- chosen target handle;
- time from hit to first retaliation shot;
- range to attacker.

### Decision rule

- If the first victim-side state transition differs between 1.5 and Redux, reopen as a confirmed compatibility regression at that transition.
- If all relevant classes/stimuli match, then the report may be upgraded to **PROVEN-RUNTIME PARITY / NO REDUX REGRESSION**.

---

## 7. OpenShim Guidance

1. **Keep the attack-reveal-on-engagement hook quarantined.** Existing evidence does not establish it as 1.5 behavior.
2. **Do not add a new perceived-team compatibility patch yet.** The runtime decision gate remains open.
3. **Do not conflate the closed WeaponMine hop-out investigation with this victim-side complaint.** They share data structures but are different consumers.
4. If runtime establishes parity, close this regression as expected legacy behavior and document the reproduction.
5. If runtime establishes divergence, patch the **first divergent consumer/state transition**, not `perceivedTeam` globally.

---

## 8. Final Evidence Classification

| Claim | Classification |
| --- | --- |
| Capture deliberately sets `perceivedTeam` to the previous owner team | **Established static parity** |
| Redux hostile landed damage updates `enemyShot` and attacker handle | **Independently verified in repo corpus** |
| Inspected hostility relation uses actual team/alliance state | **High static confidence** |
| Old reveal-on-engagement OpenShim hook is a proven 1.5 restoration | **False / not established; remain quarantined** |
| Victim `OffensiveProcess` retaliation is behaviorally identical in 1.5 and Redux | **Not yet runtime-proven** |
| `turrettank` retaliation is behaviorally identical | **Not yet runtime-proven** |
| gun-tower `turret` retaliation is behaviorally identical | **Not yet runtime-proven** |
| Sniper behavior is behaviorally identical | **Not yet runtime-proven** |
| No Redux regression exists anywhere in this victim-side path | **Premature conclusion; decision gate open** |
