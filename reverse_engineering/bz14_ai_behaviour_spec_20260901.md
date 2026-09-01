# BZ 1.4 AI — behavioural specification

**Date:** 2026-09-01
**Purpose:** implementable specification of 1.4 AI behaviour for an opt-in legacy mode in Redux
**Method:** hand semantic RE, 1.4 ↔ symbolised 1.5, anchored on the RtimeClass vtable chain
**Companions:** `bz14_ai_reconstruction_kit_20260901.md` (substrate),
`bz14_evasive_ai_investigation_20260823.md` (F1–F4)

Queue status: **`DoSlide` closed (no work needed)**, **`DoFlee` specified**.
`IsStuck`/`DoStuck` and `AbleToHit`/`UpdateWeapon` outstanding.

---

## 0. How the 1.4 functions were identified

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

## 3. Remaining queue

| Handler | 1.5 | 1.4 | Status |
|---|---|---|---|
| `DoSlide` | `0x0046F03B` | `0x0046ECF0` | **closed — identical** |
| `DoFlee` | `0x0046F103` | `0x0046F090` | **specified above** |
| `IsStuck` | `0x0046BC60` | candidate `0x0046DE70` | needs callee-evidence separation from `DoStuck` |
| `DoStuck` | `0x0046BCF3` | candidate `0x0046DE70` | same candidate as `IsStuck` — must be split |
| `AbleToHit` | `0x0046C3C0` | candidate `0x0046E530` | needs separation from `UpdateWeapon` |
| `UpdateWeapon` | `0x0046C63E` | candidate `0x0046E530` | same candidate — must be split |

The two remaining pairs collide the same way `DoFlee`/`DoSlide` did, and the same technique applies:
1.5 `IsStuck` is consumed as a value at every call site while `DoStuck` is a bare statement, and
`UpdateWeapon` passes two arguments to `AbleToHit`'s one — so the 1.4 call sites in
`AttackTask::DoState` (`0x0040CDE0`) distinguish them directly.

## 4. Architecture note

The opt-in design (`aiName = "TankLegacyFriend"` alongside stock `TankFriend`) suits these findings
well. Both specified behaviours reduce to **predicate and gating changes on Redux-native code
paths**, not new maths:

* `DoSlide` — no change at all; only the `DoState` case-7 entry/exit predicate (F1).
* `DoFlee` — suppress the skill-gated evade block and the lead/lag term.

That keeps a legacy unit inside Redux's own steering and control code, which is what makes per-ODF
opt-in safe: stock units are untouched because the difference is a branch taken per unit, not a
detour installed globally.
