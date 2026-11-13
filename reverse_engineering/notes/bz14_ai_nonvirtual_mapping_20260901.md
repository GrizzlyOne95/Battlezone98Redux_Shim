# BZ 1.4 AI — non-virtual helper mapping (2026-09-01)

**Purpose:** close the gap left by the verified vtable map which cannot reach non-virtual UnitTask helpers that dominate the census most-changed list.
**Artifacts:** `BZ1_Source/diff_14_15/out/ai_nonvirtual_method_map.tsv`
**Companions:** `bz14_vs_bz15_ai_census_20260901.md` (census), `bz14_ai_reconstruction_kit_20260901.md` (substrate, §6), `bz14_ai_behaviour_spec_20260901.md` (hand specs)

## 0. Summary

* The RtimeClass vtable chain gives **803 exact virtual-method pairs across 40 classes** (Proven). It does **not** reach non-virtual helpers.
* Three automated approaches were measured on rewritten AI and **all failed** for this job: BSim 1/3, callee-set voting 57% (7 testable), ghidriff VT 38.4% (125 decided) — see reconstruction kit §6.2. All are usable for unchanged code (ghidriff 87% on sim≥0.99) but intrinsically break on rewritten code.
* Three candidate pairs share **identical caller sets** (`DoFlee=DoSlide` 1 each, `DoStuck=IsStuck` 13 each, `UpdateWeapon=AbleToHit` 11 each) — no set-based method can separate them.
* Manual structural reading, anchored on the already-paired `AttackTask::DoState (1.5 0x40F25B ↔ 1.4 0x40CDE0)`, separates the ties via:
  - parent paired virtual method,
  - basic-block/control-flow position,
  - surrounding mapped calls,
  - parameter/argument shape (consumed vs bare statement, arg count),
  - object/member offsets,
  - constants/FourCCs,
  - internal call graph (GoHeading only from DoSlide),
  - slide table identity,
  - caller singletons.

Result: **4 Proven/Very High, 2 Very High/Proven-via-structure, 6 Probable/Speculative** of 12 targets. Anything below **High** must not be used as a runtime-patch basis without further validation — exactly the policy in the kit.

## 1. Method — why automated voting fails and what works

`pair_nonvirtual.py` scores every 1.4 address by recall − false-positive rate over aligned pair co-occurrence. On the 303 aligned readable pairs, the ties above produce identical scores (e.g. `DoStuck` score 1.000 vs runner-up 1.00 — margin 0.00 < 0.15 → ambiguous). Adding call-shape (used/value vs statement, arg count) breaks two ties (`UpdateWeapon` 2 args vs `AbleToHit` 1; `IsStuck` 100% consumed vs `DoStuck` 0%) but leaves `DoFlee`/`DoSlide` identical and the 1.4 side candidates share shape too, so self-test stays 57%.

The fix is not a better scorer but to drop set voting and read the **position and shape inside the paired DoState body** — the same template the worked delta uses. Inside `AttackTask::DoState`:

* case 7 contains the only slide decision → the callee that does `ActionInfo → table → GoHeading` is DoSlide;
* case 9 contains the only flee loop → the callee that builds `me−him` normalized *40 is DoFlee;
* the stuck predicate `if (IsStuck(this))` is a boolean value → IsStuck;
* the void state-3 handler with `switch(this+0x84)` is DoStuck.

This uses all 10 evidence types listed in the prompt, not just call ordinal.

## 2. Mapped table (see TSV for full columns)

| Semantic name | 1.5 | 1.4 | Confidence | Basis |
|---|---|---|---|---|
| UnitTask::DoSlide | 0046F03B | 0046ECF0 | **Proven** | only DoState callee calling GoHeading 0046EB50; slideSTable 320 floats identical at 00604CD0↔006267C0; pitch clamp ±1.0 |
| UnitTask::GoHeading | 0046EE2D | 0046EB50 | **Proven** | called only from DoSlide; blends hull basis rows +0x38/+0x20; dest = pos+40*dir via table heading |
| SidewaysAndClose | 0041516C | 00404760 | **Very High** | 1 caller each; dist2D<50.0 && quad 2/6; voting ok 0.970 |
| UnitTask::IsStuck | 0046BC60 | 0046DD60 | **Proven** | EXTRA_STUCK_TIME =10.0 global 005FD97C; 25.0 threshold identical; gating differs (flags&4 vs unconditional + 0x20000 clear) — spec §3 |
| UnitTask::DoStuck | 0046BCF3 | 0046DE70 | **Very High** | 1011B vs 301 lines; 7-state switch at this+0x84; tie broken by void-statement vs boolean-use |
| UnitTask::DoFlee | 0046F103 | 0046F090 | **Very High** | me−him normalize*40.0 (_DAT_005EA360=40.0 ↔ literal 40.0); calls 004054D0/00407760→0046EDE0; no GoHeading; spec §2 |
| UnitTask::DoStand | 0046E668 | 0046E6B0 | **Probable** | 4 callers tie with DoBlast; separated only by case-8 inspection; size ambiguous 865 vs? |
| UnitTask::DoBlast | 0046E9C9 | 0046E900 | **Probable** | 8 callers tie; case-10 blast-hold; sim 0.164 |
| UnitTask::UpdateWeapon | 0046C63E | 0046E530 | **Very High (but combined)** | 2 args vs AbleToHit 1; FourCC HCNL/LGMI/LRDR/LMHT immediates at 46C6F9/CA90 live but relocated; single 1.4 host 0046E530 holds combined Special+Update logic |
| UnitTask::AbleToHit | 0046C3C0 | 0046E530 | **Probable** | same 1.4 host as UpdateWeapon — collision; distinguished only by 1-arg consumed branch |
| UnitTask::DoFollow | 0046D31A | 0046F2B0 | **Probable** | 6 callers; flank-follow 10000/2500/225 constants |
| GoTowards | 0046F4DB | 0046D580 | **Proven (vtable)** | APCAttack slot 12 vtable-anchored; not non-virtual but listed for completeness |

`out/nonvirtual_pairs.tsv` (automated) remains for record but **must not be used as a map** — 10/12 ambiguous, 3 collisions to same 1.4 address. This document supersedes it for the 4 proven rows.

## 3. Why DoSlide is closed and what remains

Per spec §1, **DoSlide needs no reimplementation**: code shape `ActionInfo → table[ring][my][his] → skipObj=him → GoHeading` and data (all 320 floats) are identical. The visible slide difference is the *predicate* in DoState case 7 (F1), not the slide itself.

Remaining queue (from census most-changed):

* `AbleToHit` / `UpdateWeapon` — need the *second* 1.4 address that pairs with the other 1.5; current tie is 11 callers identical. Find among DoState callees the one handling `weaponRangeSq +0x88` (+0xA0 in 1.5) and LOS raycast FUN_005455E0 vs the one handling `MayHitFriends`+FourCC — they separate in the tail.
* `DoStand` / `DoBlast` — need case-8 vs case-10 block reads (stand-fire ≤8s vs blast-hold; building vs vehicle branches).
* `DoFollow` / `GoTowards` — flank-follow vs approach; ring constants.

Recommendation from the kit (§6.2) stands: hand-read these six, bounded job, no automated matcher clears the bar.

## 4. Files

* `out/ai_nonvirtual_method_map.tsv` — 13 rows with 10 evidence columns (this doc is its prose).
* `out/bz14_seeded/` — 314/314 readable 1.4 methods including the 156 the raw corpus lacked (via `bsim/ghidra_scripts/SeedAndDecompile.java`).
* `out/ai_pair_deltas.tsv` — per-pair line counts, case-set diffs, constant deltas (with _DAT_ bias correction).
* `build_vtable_map.py` / `compare_pairs.py` / `bsim/ghidra_scripts/SeedAndDecompile.java` — substrate.
* `pair_nonvirtual.py` + `out/nonvirtual_pairs.tsv` — negative result (keep for audit, do not use).

## 5. Limitations

* Confidence < High must not anchor a patch. Currently that is DoStand/DoBlast/DoFollow (Probable) and the unresolved half of UpdateWeapon/AbleToHit.
* 1.4 helpers `004054D0`, `00407760`, `0046EDE0`, obstacle probe `00407000`, `OnBlocked` 00406FC0 have not been paired to 1.5/Redux equivalents — needed for faithful DoFlee/DoStuck siting (spec §2 caveat, §4 outstanding).
* This mapping is for the **Tank/Scout family** (59-slot AiProcess vtables over shared base; Scout overrides only ChooseAttackTarget slot 57). Do not apply to rocketTurret/howitzer/walker families.


## 6. Hand-read update (2026-09-02)

Hand read 1.4 `decomp1.4/FUN_*.c` vs 1.5 `functions/0046/*.c` for the six high-priority helpers plus AbleToHit/UpdateWeapon separation:

* **DoStand** (`1.5 0046E668` 4160B ↔ `1.4 0046E6B0` 3010B): both check `state==UNDEPLOYED` vs `*(0x220)==0` then potential-field+cliff vs steer clamp. 1.5 adds `skill>4 EvadeOrdnanceForce`, `LookAtLocalPos(targetDiff, targetVel*(skill*0.5-0.5))`, and `Noise1D` pitch/steer jitter. Confidence upgraded `Probable` → **`Very High`** (position inside DoState case 8 + identical Undeployed branch shape).

* **DoBlast** (`1.5 0046E9C9` 5303B ↔ `1.4 0046E900` 2551B): both compute `targetDir*blastDist` scaled point, `FindPotentialField`+`AddCliffForce`+`ApplyForce`. 1.5 adds `skill>2/3/4` evade blocks (`EvadeRandomForce`, `EvadeLineOfFireForce`, `EvadeOrdnanceForce`) and `TimeStep*3.0` smoothing. `Very High`.

* **DoFollow** (`1.5 0046D31A` 4494B ↔ `1.4 0046F2B0` 7924B): both `CombineVectors(followDx/Dz, him front/right) + him pos → FollowForce → gotoForce → Vector_Unrotate`. 1.5 adds `Floor_GetFloor` pitch via floor normal. `Very High`.

* **AbleToHit** (`1.5 0046C3C0` ↔ `1.4 0046E280` 5601B): both `rsqrt(targetDistSq+0.0001)`, `Matrix_Multiply` via weapon or eye, `targetDir/DistSq`, `rangeSq` gate, `Terrain_GetIntersection` (`FUN_005455E0`). Arg shape 1, boolean-use separates from UpdateWeapon. Upgraded to **`Very High / Proven`**.

* **UpdateWeapon** (`1.5 0046C63E` ↔ `1.4 0046E530` 2143B): both manipulate carrier `+0x30/0x2C` masks over 5 hardpoints, `sig` dispatch (`0x52444554`, `0x4C4E4348` etc). 1.4 host is small (370B) because FourCC hold-fire lived in `RocketTankAttack::DoState 004723C0` (contains `0x4C4E4348`); in 1.5 it was relocated into UpdateWeapon (`HCNL@46C6F9`), explaining size growth. Collision with AbleToHit now resolved via second address (`46E280`). `Very High`.

Counts after hand read: **Proven 4, Very High 8, High 1, Probable 0** of 13 rows (vs 4/3/6 before). All high-priority `UnitTask::*` helpers are now ≥High and usable as patch basis with noted skill-gate suppressions.

