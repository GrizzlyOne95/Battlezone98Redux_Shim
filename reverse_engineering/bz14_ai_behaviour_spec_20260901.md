# BZ 1.4 AI — behavioural specification

**Date:** 2026-09-01
**Purpose:** implementable specification of 1.4 AI behaviour for an opt-in legacy mode in Redux
**Method:** hand semantic RE, 1.4 ↔ symbolised 1.5, anchored on the RtimeClass vtable chain
**Companions:** `bz14_ai_reconstruction_kit_20260901.md` (substrate),
`bz14_evasive_ai_investigation_20260823.md` (F1–F4)

Queue status: **`DoSlide` closed (no work needed)**, **`DoFlee` specified**,
**`IsStuck` specified (gating only)**, **`DoStuck` identified but structurally rewritten —
needs a per-state spec**. `AbleToHit`/`UpdateWeapon` outstanding.

---

## 0. SCOPE — this is the Tank/Scout AI family, not "the 1.4 AI"

**Everything in this document reconstructs the 1.4 `TankFriend`/`TankEnemy` behavioural family.
It must not be applied to combat units generally.** The engine's own class registry settles which
units are in scope, and it does so precisely.

All six relevant AI classes are 59-slot `AiProcess` vtables over a shared base. Diffing their slots
against `TankEnemy` (1.4 vtables; names taken from the 1.5 `TankEnemy` vtable at `0x005DB810`):

| Class | 1.4 vtable | Slots differing from `TankEnemy` | What differs |
|---|---|---|---|
| `TankEnemy` | `0x005EA708` | — | (reference) |
| `TankFriend` | `0x005EA618` | 0, 4 | **identity only** — destructor and `GetRtimeClass` |
| `ScoutFriend` | `0x005EA7F8` | 0, 4, **57** | identity + `ChooseAttackTarget` |
| `ScoutEnemy` | `0x005EA8E8` | 0, 4, **57** | identity + `ChooseAttackTarget` |
| `RocketTankFriend` | `0x005EABF0` | 0, 4, **24, 25, 48** | identity + `InitAttack`, `CleanAttack`, `InitSubAttack` |
| `RocketTankEnemy` | `0x005EACE0` | 0, 4, **24, 25, 48** | identity + `InitAttack`, `CleanAttack`, `InitSubAttack` |

Three consequences, all load-bearing:

1. **Scout is in scope, and inherits rather than aliases.** `ScoutFriend`/`ScoutEnemy` override
   *only* `OffensiveProcess::ChooseAttackTarget` (both to the same 1.4 address `0x004714C0`). Every
   movement and combat slot is `TankEnemy`'s. So Scouts flank exactly like Tanks because they are a
   subclass that changes only *who* to attack — not because their ODF points at `TankFriend`. The
   legacy reconstruction covers them automatically; no `ScoutLegacy*` implementation is needed.
2. **RocketTank is out of scope, and now we know why.** It overrides `InitAttack`, `CleanAttack`
   and `InitSubAttack` — the attack construction/teardown path — while keeping Tank's movement
   slots. That is the mechanism behind its more direct combat style: it builds a different attack
   task, so it does not enter the flank/flee cycle the same way. **Do not enable the legacy state
   machine for `rockettank`**, nor for `howitzer`, `walker`, `turret` or any other family, on the
   grounds that they are ground combat units.
3. **Friend and Enemy share all behaviour.** `TankFriend` differs from `TankEnemy` in slots 0 and 4
   only — pure identity. Whatever distinguishes friendly from enemy conduct is not in the vtable, so
   `TankLegacyFriend` and `TankLegacyEnemy` will share one implementation and differ only in
   registration.

Accordingly the opt-in surface should be family-specific — `aiName = "TankLegacyFriend"` /
`aiName2 = "TankLegacyEnemy"` — and never a global `if (legacyAI)`.

---

## 0.1 How the 1.4 functions were identified

Not by any matcher — all three failed (see the kit, §6.2). By callee evidence against the
vtable-anchored `AttackTask::DoState` pair (1.5 `0x0040F25B` ↔ 1.4 `0x0040CDE0`):

| Function | 1.5 | 1.4 | Corroboration |
|---|---|---|---|
| `DoSlide` | `0x0046F03B` | **`0x0046ECF0`** | only `DoState` callee that calls GoHeading (1.4 `0x0046EB50`); same `ActionInfo` → table-lookup → `skipObj = him` → `GoHeading` shape |
| `DoFlee` | `0x0046F103` | **`0x0046F090`** | computes `me−him`, normalises, scales by **40.0** — 1.4 `_DAT_005EA360 = 40.0`, matching 1.5's literal `40.0`; calls no GoHeading |

Both were previously reported *ambiguous* by callee-set voting, which resolved `DoFlee`, `DoSlide`
and `SidewaysAndClose` all to the same address. The callee-evidence reading separates them cleanly.

---

## 1. `UnitTask::DoSlide` — **unchanged; do not reimplement**

The interesting result is a negative one.

**Code.** 1.4 `0x0046ECF0` and 1.5 `0x0046F03B` have the same structure:

```
ActionInfo(me_pos, him_pos)            -> ring, my_quad, his_quad
heading = slideTable[ring][my_quad][his_quad]
skipObj = him
GoHeading(heading)
if (braccel > 0.2) braccel = 1.0
pitch = clamp(pitch + delta, -1.0, +1.0)
```

**Data.** The table is **5 rings × 8 × 8 = 320 floats** (an earlier 8×8×8 read was running off the
end into adjacent data). 1.4 `0x00604CD0`, 1.5 `0x006267C0`:

> **All 320 entries are identical between the two builds.**

Values are only `{-0.52, 0.0, +0.52}` — ±0.52 rad ≈ **±29.8°**, or straight on. Ring 0:

```
my_quad 0:   0.520 -0.520  0.520  0.520 -0.520 -0.520 -0.520  0.520
my_quad 1:   0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
my_quad 2:   0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
my_quad 3:   0.520  0.520  0.520  0.520  0.520  0.520  0.520  0.520
my_quad 4:   0.520  0.520  0.520  0.520  0.520 -0.520 -0.520 -0.520
my_quad 5:  -0.520 -0.520 -0.520 -0.520 -0.520 -0.520 -0.520 -0.520
my_quad 6:   0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
my_quad 7:   0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
```

The pitch clamp is `-1.0 / +1.0` in both (1.4 `_DAT_005EA320` / `_DAT_005EA324`).

**Consequence.** The visible 1.4-vs-1.5 sliding difference is **not in `DoSlide`**. It is in *when
the slide is entered and left* — the `AttackTask::DoState` case-7 predicate, which is exactly F1 in
the 20260823 investigation. A legacy mode should change the predicate, not the slide.

---

## 2. `UnitTask::DoFlee`

```text
UnitTask::DoFlee
  1.4: 0x0046F090 (537 bytes)      1.5: 0x0046F103 (940 bytes)

Entry:
  - called from AttackTask::DoState in the flee/evade state
  - requires a valid `him` (target) and `me` (own craft)

Inputs:
  - him->GetPosition()      (virtual, vtable +0x0C)
  - me->GetPosition()
  - me->vhcl->control       (braccel at +0xD0, flag at +0xD4)
  - this->skipObj           (this+0x70)
  - 1.5 only: this->skill, this->targetVel, this->targetDiff,
              this->threatOrd, this->evadeForce

Behavior (1.4):
  - diff  = me_pos - him_pos                    ; directly away from the enemy
  - dir   = diff / |diff|                       ; normalise
  - goal  = me_pos + dir * 40.0                 ; _DAT_005EA360 = 40.0
  - steer toward `goal` with radius 40.0 via the two 1.4 goal-seek helpers
    (0x004054D0 taking me/skipObj/radius/goal, then 0x00407760), converted to
    controls by 0x0046EDE0
  - if braccel saturated at 1.0, set vhcl+0xD4 = 1

Exit:
  - no internal termination; the state is left by AttackTask::DoState

1.5 difference:  PURELY ADDITIVE, and skill-gated.
  1.5 keeps the identical base (me-him, normalise, scale by the same 40.0) and layers on:
    - unconditional lead/lag aim:
        LookAtLocalPos(targetDiff, targetVel * (skill * 0.5 - 0.5))
    - if skill > 2.0 :  EvadeRandomForce
                        EvadeLineOfFireForce(me, ((skill - 2.0) + 1.0) * 5.0)
    - if skill > 4.0 :  EvadeOrdnanceForce(me, threatOrd)
    - accumulate into this->evadeForce, smoothed:
        evadeForce += TimeStep() * 5.0 * (new_force - evadeForce)
    - then normalise and scale by 40.0 as 1.4 does
  So at skill <= 2.0 the whole evade-force block is skipped and 1.5 reduces almost
  exactly to 1.4 -- the residual being the LookAtLocalPos lead/lag term, which 1.4
  does not have at all.

Redux implementation point:
  Redux carries the 1.5 rewrite structurally (20260823), so the legacy behaviour is
  reachable two ways:
    (a) cheap and low-risk -- for legacy-AI units, force the evade path off (behave as
        skill <= 2.0) and suppress the LookAtLocalPos lead/lag term. This reuses
        Redux-native code and touches no maths.
    (b) faithful -- reimplement the 1.4 body verbatim: goal = me + normalise(me-him)*40,
        steer with radius 40.
  (a) is recommended first; it is a predicate change, testable against (b) later.
  Exact Redux addresses pending the 1.5 -> Redux siting pass.
```

**Caveat.** 1.4's two goal-seek helpers (`0x004054D0`, `0x00407760`) and the control conversion
(`0x0046EDE0`) have not themselves been compared against their 1.5/Redux equivalents. Option (a)
sidesteps them; option (b) requires that comparison first.

---

## 3. `UnitTask::IsStuck` — gating change only

Identified without any matcher, via the config-key chain: the string `EXTRA_STUCK_TIME`
(1.4 `0x005FD980`) is consumed by the AI config loader at `0x0040D961`, which stores the parsed
float to **`0x005FD97C`**. Exactly one AI function reads that global with the `Get_Time()` comparison
shape — `0x0046DD60`, which is also a `DoState` callee. The two remaining readers (`0x00459308`,
`0x00459CED`) are the same pattern in other task classes.

```text
UnitTask::IsStuck
  1.4: 0x0046DD60 (185 bytes, returns bool)   1.5: 0x0046BC60

Entry:
  - called as a predicate from AttackTask::DoState and peers

Inputs:
  - me->GetPosition()                     (virtual, vtable +0x0C)
  - this->nextStuck   (1.4 this+0x74)
  - this->lastStuck   (1.4 this+0x78 .x / +0x7C .y / +0x80 .z)
  - EXTRA_STUCK_TIME  (config-loaded global; 1.4 0x005FD97C = 10.0)
  - 1.5 only: me->vhcl->flags

Behavior (1.4):
  - if OnBlocked(me_pos)                       -> return true        (1.4 0x00406FC0)
  - if Get_Time() < nextStuck + EXTRA_STUCK_TIME -> return false     (timer gate)
  - dx = pos.x - lastStuck.x ; dz = pos.z - lastStuck.z
  - stuck = (dx*dx + dz*dz) < 25.0             (1.4 _DAT_005EA344 = 25.0, i.e. 5 units)
  - CleanStuck (inlined in 1.4):
        nextStuck = Get_Time() + 5.0           (1.4 stores Get_Time() - (-5.0))
        lastStuck = me_pos
  - return stuck

Exit:
  - pure predicate; no steering side effects

1.5 difference:  GATING ONLY -- every threshold is identical.
  - 25.0 distance threshold: identical
  - EXTRA_STUCK_TIME 10.0:   identical
  - CleanStuck +5.0 re-arm:  identical
  Two additions:
    1. 1.5 guards the blocked test:  if ((me->vhcl->flags & 4) == 0) { if (OnBlocked(pos)) ... }
       1.4 calls OnBlocked unconditionally. So a craft with flag bit 2 set is exempt from
       the blocked check in 1.5 and is NOT exempt in 1.4.
    2. 1.5's CleanStuck additionally clears me->vhcl->flags & 0x20000; 1.4 does not.

Redux implementation point:
  For legacy units, bypass the flags&4 exemption (always run the blocked test) and skip
  the 0x20000 clear. No maths changes, no new state. This is the smallest legacy delta
  found so far.
```

## 4. `UnitTask::DoStuck` — **structurally rewritten; not a gating change**

Identified as `0x0046DE70` (1011 bytes, void) — the other `DoState` callee in the pair, with side
effects and no return value, matching the call-shape evidence (1.5's `DoStuck` is a bare statement
while `IsStuck` is consumed as a value).

**This one is different in kind from everything above.**

| | 1.4 `0x0046DE70` | 1.5 `0x0046BCF3` |
|---|---|---|
| shape | `switch (this[+0x84])`, **states 0–6** | **no switch at all** |
| size | 1011 bytes | 301 decompiled lines |

1.4 implements stuck-recovery as an explicit **7-state machine** on a dedicated state field
(`this+0x84`). 1.5 has no such dispatch — the recovery was restructured into straight-line logic
with a `Range_Search_Results` query.

So the pattern that held for `DoSlide`, `DoFlee` and `IsStuck` — same machinery, different
predicates — **does not hold here.** Reconstructing 1.4's stuck recovery means implementing its
7-state machine, not toggling a gate.

### 4.1 The state graph — recovered

**It is both selection and escalation, not one or the other.** States 1–4 are four *directional
recovery manoeuvres* chosen by obstacle probing; 0 → (1–4 | 5) → 5 → 6 is a *temporal escalation*
with a fixed window per phase.

Field map (established from `DoSlide`/`DoFlee`/`IsStuck` plus this function):

| Field | Meaning |
|---|---|
| `this+0x10` | owning task state (writing 1 hands control back) |
| `this+0x14` / `+0x1C` | `me` / `him` |
| `this+0x74` | recovery-window deadline (shares the `nextStuck` slot) |
| `this+0x84` | **stuck substate, 0–6** |
| `vhcl+0xC4` | throttle |
| `vhcl+0xC8` | pitch |
| `vhcl+0xCC` | steer |
| `vhcl+0xD0` | braccel |
| `vhcl+0xD4` | boolean flag (also written by `DoFlee`) |

Constants: window `= Get_Time() + 2.0` (`_DAT_005EA348 = -2.0`, stored as a subtraction);
obstacle-distance threshold `10.0` (`_DAT_005EA310`); speed test `> 0.7` (`_DAT_005EA328`).

| State | Purpose | Movement | Transition |
|---|---|---|---|
| **0** | detect and select | `braccel = -0.1`, throttle 0 | not blocked → **6**; else probe 4 directions (`0x00407000` on `renderObj+0x20`, i = 0..3) for the nearest obstacle. If one found **and** (speed > 0.7 or nearest ≤ 10.0) → **best+1** (1–4); else → **5** |
| **1** | recover: drive out | `braccel = +1.0`, steer 0, flag 1 | unblocked → exit; window expired → **5** |
| **2** | recover: turn right | `steer = +1.0`, braccel 0 | unblocked → exit; window expired → **5** |
| **3** | recover: reverse | `braccel = -1.0`, steer 0 | unblocked → exit; window expired → **5** |
| **4** | recover: turn left | `steer = -1.0`, braccel 0 | unblocked → exit; window expired → **5** |
| **5** | fallback push | if \|throttle\| ≥ `_DAT_005EA350` → coast, else `braccel = +1.0` | window expired **or** unblocked → exit; speed > 0.7 → **6** |
| **6** | reverse out | `braccel = -1.0`, throttle 0, steer 0 | window expired → exit |

"exit" means `this+0x10 = 1` — control returns to the owning task's state 1.

```
                    ┌──────────────┐
                    │      0       │ detect + probe
                    └──┬────┬───┬──┘
        not blocked    │    │   │  probe hit
              ┌────────┘    │   └──────────────┐
              v             │ no probe          v
         ┌────────┐         v            ┌─────────────┐
         │   6    │    ┌────────┐        │ 1 · 2 · 3 · 4│ fwd/right/rev/left
         │reverse │<───│   5    │        └──────┬──────┘
         └───┬────┘ spd│ push   │<──────timeout─┘
             │ >0.7    └───┬────┘
   timeout   │             │ timeout / unblocked
             └─────────────┴───────────> exit (task state := 1)
```

Every state re-tests `OnBlocked` (`0x00406FC0`) — the same predicate `IsStuck` uses — so recovery
ends the moment the craft is free, not when a timer says so.

### 4.2 What this means for the legacy layer

The seven states reduce to a compact, implementable machine: **one detection state, four directional
manoeuvres selected by a 4-way obstacle probe, and two escalating fallbacks**, all on a 2-second
per-phase window, driving only `throttle`/`steer`/`braccel`.

That is small enough to reimplement directly against Redux-native controls, and it needs no 1.4
helper beyond the obstacle probe (`0x00407000`) and `OnBlocked` — both of which have Redux
equivalents to be sited. So `DoStuck` is a genuine subsystem restoration, but a **bounded** one: a
7-case switch over three control outputs, not a port of 1011 bytes of arithmetic.

**Still outstanding for `DoStuck`:** the exact semantics of the 4-way probe (`0x00407000`, what the
four indices mean geometrically), `_DAT_005EA350`, and the `me` vtable call at `+0x84` used in state
5. None of those block writing the state machine; all three affect fidelity.

## 5. Remaining queue

| Handler | 1.5 | 1.4 | Status |
|---|---|---|---|
| `DoSlide` | `0x0046F03B` | `0x0046ECF0` | **closed — identical** |
| `DoFlee` | `0x0046F103` | `0x0046F090` | **specified above** |
| `IsStuck` | `0x0046BC60` | **`0x0046DD60`** | **specified (§3) — gating only** |
| `DoStuck` | `0x0046BCF3` | **`0x0046DE70`** | **identified (§4) — 7-state machine, needs per-state spec** |
| `AbleToHit` | `0x0046C3C0` | candidate `0x0046E530` | needs separation from `UpdateWeapon` |
| `UpdateWeapon` | `0x0046C63E` | candidate `0x0046E530` | same candidate — must be split |

`AbleToHit`/`UpdateWeapon` collide on `0x0046E530` the way `IsStuck`/`DoStuck` did, and the same
technique applies: `UpdateWeapon` passes two arguments to `AbleToHit`'s one, and `AbleToHit` is
consumed as a value while `UpdateWeapon` is a statement, so the 1.4 call sites in
`AttackTask::DoState` (`0x0040CDE0`) separate them. Note that `0x0046E530` is only one of the two
addresses; the second member of the pair still has to be found among the `DoState` callees, exactly
as `0x0046DD60` was found for `IsStuck`.

## 4. Architecture note

The opt-in design (`aiName = "TankLegacyFriend"` alongside stock `TankFriend`) suits these findings
well. Both specified behaviours reduce to **predicate and gating changes on Redux-native code
paths**, not new maths:

* `DoSlide` — no change at all; only the `DoState` case-7 entry/exit predicate (F1).
* `DoFlee` — suppress the skill-gated evade block and the lead/lag term.

That keeps a legacy unit inside Redux's own steering and control code, which is what makes per-ODF
opt-in safe: stock units are untouched because the difference is a branch taken per unit, not a
detour installed globally.
