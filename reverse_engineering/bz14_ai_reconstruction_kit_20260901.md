# BZ 1.4 AI — reconstruction kit

**Date:** 2026-09-01
**Purpose:** everything needed to reimplement 1.4-era AI behaviour as an alternative mode in Redux
**Artifacts:** `BZ1_Source/diff_14_15/`
**Companions:** `bz14_vs_bz15_ai_census_20260901.md` (which behaviours changed),
`bz14_evasive_ai_investigation_20260823.md` (the evasive system, read by hand)

---

## 0. What this is, and what it is not

**It is the substrate.** Four things that did not exist before and that any 1.4-AI restoration needs:

1. A **complete, readable 1.4 corpus** for the AI class hierarchy — the previous corpus was missing
   half of it.
2. A **validated 1.5↔1.4 method map**, exact rather than heuristic, so any 1.5 function named in the
   PDB can be read against its 1.4 original.
3. A **comparison harness** that puts both sides on the same footing and refuses to compare things
   it cannot compare fairly.
4. One **fully worked delta** (`AttackTask::DoState` case 7) as the template.

**It is not a finished behavioural specification for every AI behaviour.** Turning the map into
implementable pseudocode is still a per-function reading job. This kit makes each of those readings
cheap and reliable; it does not do them. The census's top-20 list is the queue.

---

## 1. The 1.4 corpus gap is closed

Ghidra does not create functions from vtable slot targets, and 1.4 has no RTTI to help it. Measured
against the RtimeClass-derived vtable map: **156 of the 314 virtual-method addresses had no function
in the 1.4 corpus at all** — including `AttackTask::DoState` (`0x0040CDE0`), the most-studied AI
function in the build.

`bsim/ghidra_scripts/SeedAndDecompile.java` forces a function at each mapped address and decompiles
it. Result: **created 156, already present 158, failed 0; 314 of 314 decompiled, 0 failures**, into
`out/bz14_seeded/`.

Anyone using `BZ1_Source/1.4/ghidra/decomps` for coverage claims should use the seeded set alongside
it. The raw corpus has holes exactly where the class hierarchy points.

## 2. The method map, and how it is validated

Built by `build_vtable_map.py` from the engine's own `RtimeClass` registry — see §7 of the census
doc for the chain. **803 virtual-method pairs across 40 classes.**

Two independent checks, both of which caught real errors:

* **Self-check:** `AttackTask` → 1.5 `0x005CF8F8`, 1.4 `0x005E6E58`, slot 11 = `0x0040CDE0`, matching
  the address the 20260823 investigation derived by hand.
* **Inherited-method consistency:** an inherited 1.5 method must resolve to the *same* 1.4 address
  from every class that inherits it. 85 methods appear in more than one class; **39 were
  inconsistent, and all 39 traced to a single class, `SoldierRetreat`** — its vtable alignment is
  wrong. 39 of 40 classes are clean. `SoldierRetreat` is dropped, and the gate is permanent in
  `compare_pairs.py`.

Without that gate, `SoldierRetreat`'s bad pairs produced "deltas" comparing a 244-line function
against an 8-line one.

## 3. Two comparison traps, both measured

**Thunks.** Some vtable slots point at a jump trampoline, not the body — `SitTask::DoState` in 1.4 is
`thunk_FUN_0046dba0`. Unfollowed, that compares 9 lines of trampoline against a 94-line function.
The harness follows them.

**Decompiler-configuration bias — this one nearly produced a bogus headline.** 1.5's corpus was
decompiled with `bzint.pdb` types applied, so float constants print as literals; the seeded 1.4
functions were decompiled without type info, leaving them as `_DAT_` references. A naive comparison
reported **100 "1.5-only" constants against 1**, and 37 pairs differing only on the 1.5 side against
**zero** differing only on the 1.4 side. That is not a property of the code — it is an artifact.

Resolving each `_DAT_` address to its stored float from the image puts both sides on the same
footing. Corrected: **17 pairs vs 11, and 61 constants vs 43** — a plausible balance.

**Consequence for reconstruction:** with the bias removed, the two builds turn out to **share almost
all their numeric tunables.** The surviving constant deltas are mostly sign variants of the same
value. So a 1.4-AI restoration is **not** a matter of restoring different numbers — the divergence is
in control flow. Do not go looking for a table of changed constants; there isn't one.

## 4. Where the behaviour actually differs

### 4.1 Methods whose state set itself differs (14)

Structural change, not just a rewritten handler:

`DefendTask::InitState` · `SAVAttackVehicleTask::InitState` · `SAVAttackVehicleTask::DoState` ·
`FollowTask::DoState` · `FollowTask::InitState` · `RescueTask::DoState` · `AttackTask::InitState` ·
`AttackTask::CleanState` · `WingmanProcess::ChangeState` · `UnitProcess::ChangeState` ·
`PersonProcess::ShouldAttack` · `SAVAttackPersonTask::InitState` · `ScavengerProcess::Execute` ·
`TugProcess::Execute`

### 4.2 Methods where 1.4 carries substantially more code

1.5 removed logic in these; the removed logic is what a restoration puts back:

| Method | 1.5 lines | 1.4 lines |
|---|---|---|
| `ScavengerProcess::Execute` | 36 | **81** |
| `TugProcess::Execute` | 31 | **56** |
| `WingmanProcess::ChangeState` | 20 | **51** |
| `SitSpinTask::DoState` | 20 | **45** |
| `AttackTask::DoState` | 289 | **399** |
| `SAVAttackVehicleTask::DoState` | 155 | **200** |
| `OffensiveProcess::DoSubTask` | 155 | **188** |

Full table: `out/ai_pair_deltas.tsv`.

## 5. The worked delta — the template for the rest

`AttackTask::DoState` case 7. Both builds handle the identical state set (2–0xC), so the machine was
not restructured; the rewrite is inside the handler.

**1.4** — slide-exit keyed on the *enemy's own task state*, no time cap:

```c
iVar8 = (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + 0x30))();
iVar8 = *(int *)(iVar8 + 0xac);            /* the ENEMY's task state */
if ((iVar8 != 2) && (iVar8 != 5)) {
    if (iVar8 == 7) { *(undefined4 *)(param_1 + 0x10) = 10; }   /* -> slide */
    else { ... SidewaysAndClose ... }
}
```

**1.5 / Redux** — that predicate is gone, replaced by a self-contained one:

```c
if (IsBuilding(target)) goto done;
if (Get_Time() <= startTime + 10.0) {          /* 10s cap, absent in 1.4 */
    if (!UnitTask::IsStuck(this)) {
        UnitTask::DoSlide(this);
        ... SidewaysAndClose(...)
    }
}
```

**To restore 1.4 behaviour** the change is: read the target's task state (object `+0xAC`), branch on
`{2, 5, 7}`, and drop the elapsed-time cap. The helpers 1.5 introduced (`IsStuck`, `DoSlide`,
`SidewaysAndClose`, `AbleToHit`) survive and are reusable — the 20260823 doc establishes that the
missile FourCC fire gate was relocated into `UnitTask::UpdateWeapon` rather than deleted.

## 6. The remaining hop

The functions dominating the census's most-changed list — `DoFlee`, `DoStand`, `DoStuck`, `DoBlast`,
`UpdateWeapon`, `DoFollow` — are **non-virtual** and therefore in no vtable, so §2's map does not
reach them. They are called from the now-paired `DoState`/`Execute` bodies, so call-site position
inside an aligned pair identifies them. That is the one piece of tooling still missing, and it is
the natural next step.

## 7. Redux

The 20260823 investigation established that **Redux carries the 1.5 rewrite structurally unchanged**,
so every 1.4→1.5 delta in this kit is also a 1.4→Redux delta. A restoration targets the Redux
equivalents of the 1.5 addresses here; that doc already maps several (e.g. Redux `0x00478A50`).
Mapping the rest of the 1.5→Redux side is a separate pass and has not been done here.

## 8. Files

| Path | What |
|---|---|
| `out/virtual_method_map.tsv` | 803 verified 1.5↔1.4 virtual-method pairs |
| `out/class_vtable_map.tsv` | 40 classes with both vtables and object sizes |
| `out/bz14_seeded/` | 314 decompiled 1.4 methods, including the 156 the corpus lacked |
| `out/ai_pair_deltas.tsv` | per-pair line counts, state-set differences, constant deltas |
| `build_vtable_map.py` | the RtimeClass chain |
| `compare_pairs.py` | comparison harness with the consistency gate, thunk following, and bias correction |
| `bsim/ghidra_scripts/SeedAndDecompile.java` | fills the corpus holes |
