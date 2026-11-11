# UnitTask::NearestVehicle: exact fast path (2026-11-11)

**Goal:** make `UnitTask::NearestVehicle` (GOG 0x00463FC0) cheaper without changing any result, in every session including co-op.
**Code:** `include/nearest_vehicle_scan.h` (the scan), `src/patches/ai_nearest_vehicle_fast.cpp` (the hook), `tests/nearest_vehicle_scan_tests.cpp`.
**Switch:** `OPENSHIM_AI_FAST_NEAREST=1|on|true` (fast) or `verify`; default off.

Confidence labels:
- **[C]** read in the GOG 2.2.301 bytes (rizin, `pd`), at the address given;
- **[1.5]** read in the named BZ 1.5 decompile file and line, `Battlezone_Source\BZ1\1.5\functions\`;
- **UNVERIFIED** not checked either way.

No decompiler output is reproduced here.

## 1. Why

`attacktask_exact_optimisation_20261021.md` §1 profiles NearestVehicle at 0.265 ms/frame inclusive at 80 combat craft. Of that, Dist3D_Squared is 0.071 and the iterator helpers about 0.04. Most of the remainder is call overhead around trivial helpers.

## 2. What stock does [C]

The signature is `GameObject* __cdecl (GameObject* craft, const Vector* position)`, with the args at `[ebp+8]` and `[ebp+0xC]`.

1. **Initial state.**
   - `best` starts at the float at 0x008A2EB0, which is 0x7149F2CA = 1e30.
   - `result` starts at 0 (0x00463FD3).
2. **The list.**
   - The list pointer `[0x00917A74]` is read once (0x00463FDA, `A1` imm32, so the operand is at +0x1B).
   - `begin` is called once (0x00463FE9 → 0x0041FBD0, which returns `[this+0]`).
   - `end` is called again on every loop test (0x00464005 → 0x0041FC30, which returns `[this+4]`).
3. **The iterator helpers are plain pointer operations:**
   - construct: 0x004230C0 → 0x00423970, which stores the pointer; 0x004178A0 is a no-op container check;
   - dereference: 0x00421EC0 → 0x00416400, `mov eax,[eax]`;
   - `!=`: 0x00421F00 → 0x004237F0, a pointer compare;
   - post-increment: 0x0046B260 → 0x00421EE0 → 0x00421F70, `+4`.
4. **Per object, in this order:**
   1. skip `obj == craft` (0x0046402E);
   2. skip cargo: 0x0045BBC0 is `mov al,[ecx+0x9C]` (0x0045BBCA);
   3. `sig = (obj+0x18)->vtbl[0]()` then `+0x14` (0x00464054);
   4. if `sig == 0x54554700` (tug), call `(craft+0x18)->vtbl[0]()` and skip when its `+0x14 == 0x52435943` (recycler) (0x0046405C..0x0046407C);
   5. a second `(obj+0x18)->vtbl[0]()` call, then `+0x1C` = label (0x00464091);
   6. skip labels 5, 7, 2 and 10 (0x00464099..0x004640AF);
   7. skip `label == 3 && sig != 0x544F5250` (torpedo) (0x004640B1..0x004640BE);
   8. `p = (obj+0x18)->vtbl[3]()` (0x004640D4);
   9. `d = Dist3D_Squared(*position, *p)`: `*position` is copied again on every pass (0x004640EB) and the call is at 0x00464103;
   10. `comiss best, d; jbe skip` (0x00464113), so `d` is taken only when `best > d` and the compare is ordered.
5. **Return value:** `[ebp-0x20]` is returned (0x0046412E).

**Dist3D_Squared** (0x004620B0..0x00462156) calls Vector subtract (0x004401A0), which computes `a - b` with one `subss` per axis (0x004401B0..0x004401D3). It then computes `(dx*dx + dy*dy) + dz*dz` with SSE single ops (0x0046211B..0x0046213D). The result is stored as a float and reloaded with `fld` (0x00462141, 0x00462146), so it is exactly float precision.

## 3. Design

`NearestVehicleScan::Scan` repeats step 4 in the same order and makes the same virtual calls on the same objects.
- **Class reads.** It reads the object's class twice (signature, then label) and the craft's class only for a tug.
- **List reads.** It reads `begin` once and `end` on every test, straight from the vector's first two words.
- **Distance.** `DistSquared` uses `_mm_sub_ss`, `_mm_mul_ss` and `_mm_add_ss` in the stock order. This is needed because the shim builds with `/arch:IA32`, where plain float code would run on x87 at a different precision.
- **Compare.** `Closer` is `_mm_comigt_ss(best, d)`, the same ordered compare, so:
  - the first minimum in list order wins;
  - a NaN distance never wins;
  - a distance of 1e30 or more never wins.

**What is dropped:**
- the iterator calls;
- the cargo getter call (its one byte read is kept);
- the by-value `Vector` copies;
- the two stack-cookie frames.

None of these does observable work (§2). Nothing is cached between calls, so the result cannot depend on when objects move, spawn or die.

**The hook.** An inline detour sits on the function entry, replacing 6 bytes `55 8B EC 83 EC 28`. Its trampoline is the stock function, which verify mode uses.

## 4. The "nothing moves during the AI pass" question

The design does not need that proof: each call reads the live list and live positions, exactly as stock does.

For the record, the proof would probably fail if a cache were ever tried, so a per-pass cache is not safe:
- [1.5] `0047\004789c5_Simulate.c` lines 33-38 run `GameObject_CallAI` then `GameObject_Simulate` for each object in turn, on the arcade path.
- [1.5] On the normal path:
  - lines 18-31 call `ClassSimulateAll`;
  - `004e9e1d_ClassSimulateAll.c` lines 19-33 walk the object list and call each object's per-class simulate;
  - `00496710_GameObject_CallAI.c` line 24 calls the AI process at vtbl+0x1C;
  - `004964d3_GameObject_Simulate.c` lines 52 and 87 call the object's vtbl+0x3C.
- So object i's AI and object i's movement are interleaved before object j's AI runs.
- Whether the GOG build keeps that interleaving: **UNVERIFIED**.

## 5. Fail-closed checks

The install keeps stock unless all of these hold:
1. The `UnitTaskNearestVehicle` row in `scripts/patches.json` binds, and its identity bytes match.
2. The bound address is 0x00463FC0. The fingerprints below are absolute GOG addresses.
3. FNV-1a 64 of 16 stock ranges match: NearestVehicle itself (0x175 bytes) and every helper in §2. The table is in `ai_nearest_vehicle_fast.cpp`.
   - Because NearestVehicle reaches the helpers through rel32 calls, a matching body also pins their addresses and the list global `0x00917A74`.
4. The entry still holds `55 8B EC 83 EC 28` when the detour is written.

## 6. Network games and the lazy patch

**No MP gate.**
- The patch returns the same object as stock for every input. A peer running it is therefore indistinguishable from one that is not.
- It is not registered in the MP-gate registry (`src/patches/global_feature_config.cpp`, the `AttackTaskLazyNearest` entry at line ~730 is the SinglePlayer-tier precedent). Registration is opt-in and exists for behaviour that may diverge.
- A possible second reason, not needed by the argument above: AI may run only on the owning machine, so a co-op peer would never re-run another machine's NearestVehicle (**UNVERIFIED**).

**With `OPENSHIM_AI_LAZY_NEAREST`.**
- The lazy patch calls 0x00463FC0 through its bound address (`ai_nearest_vehicle_lazy.cpp` lines 131 and 151), so every scan it still makes goes through this detour.
- It rewrites call sites inside AttackTask::DoState, not the NearestVehicle entry. Its `RedirectCallTarget` still finds the stock target 0x00463FC0 at those sites, so install order does not matter.
- Its own SP gate stays: laziness depends on timing, which this patch does not change.

## 7. Expected saving and live test

**Estimate.** About 0.08-0.15 ms/frame at 80 combat craft: part of the 0.265 ms inclusive, mainly the iterator, getter and Dist3D frames. This is not measured yet. The virtual calls remain and are likely the bulk of what is left.

**Live test plan.** Not run: a benchmark owned the GOG install on 2026-11-11.
1. **Verify run.** Set `OPENSHIM_AI_FAST_NEAREST=verify` and run the 80-craft combat benchmark.
   - Expect `[AINEAREST] verify ... mismatches=0` in every window, and the install line in openshim.log.
2. **Perf A/B.** Interleave arms `OPENSHIM_AI_FAST_NEAREST=0` and `=1` with `run_live_combat_benchmark.ps1 -Scenario combat` at `-Count 80` and `-Count 120`, at least 3 runs per arm.
   - Compare AI ms and frame time, alternating arms so drift cancels.

## 8. Not done (out of scope)

**Testing the distance first** and skipping the class calls for objects already farther than `best` would save more. It needs `vtbl[0]` and `vtbl[3]` on every object class to be free of side effects, and that is **UNVERIFIED**. `ai_nearest_vehicle_lazy.cpp` line 26 asserts NearestVehicle is pure, but not per-class getter purity.

## 9. Pairwise collision loop (scoping only)

**Identity [C].**
- 0x00442E70, the only caller of which is 0x00618130 (per `frame_time_breakdown_20261020.md`).
- It walks the dynamic-entity list `[0x0260CAC4]` and builds each entity's swept AABB (0x00442E95 → 0x00442A90).
- For each dynamic entity i, it then calls the pair function 0x00443060:
  - on every later dynamic entity (0x00442EEA);
  - then on every static entity in `[0x0260D0F0]` (0x00442F20).
- Next pointers are read before each pair call (0x00442ED7, 0x00442F0D).
- 0x00443060 first calls the AABB overlap test 0x00442F40 (0x00443085), which uses six `comiss` on +0x50/+0x58/+0x54 (x, z, y) at 0x00442F4E..0x00442FBB. It returns early when there is no overlap (0x00443093).
- [1.5] This is the BZ 1.5 shape:
  - `004749d0_CheckEntityCollisions.c` lines 18-38;
  - `00473452_CreateMovingBBoxe.c` lines 26-59: sphere plus velocity×timestep, padded by radius;
  - `00474679_CheckPair.c` lines 46-53: the AABB reject.
- `MightCollide` (`00408b6a_MightCollide.c`) is an AI avoidance predicate, not this loop.

**The current broadphase.** There is none beyond the per-pair AABB reject: O(D²/2 + D·S) calls, all in list order.

**Cost.** The 0.68 ms at idle 80 in the 2026-10-20 breakdown was mostly OpenShim's experimental `VehicleGeometryContact` hook (the same note's correction section).
- With it off, stock is about 0.03 ms at idle 80 (0.7% of samples).
- It is at most 0.13 ms in the 80-craft combat runs (`combat_hitch_and_sim_breakdown_20261021.md`).
- Both figures include the narrow phase a grid would not remove.

**Exact replacement: feasible, but not worth building.**
- A sort-and-sweep or grid must call the narrow phase for exactly the overlapping pairs in the stock (i, j) order. Pair responses change entity state, so order matters.
- **The cheapest exact form** inlines the six-compare reject inside a copy of the same nested loop and calls 0x00443060 only for overlaps. Order and live reads stay identical, and no proof is needed. NaN boxes fall through all six compares and reach the narrow phase, as in stock.
- **A true sweep or grid** would need proof that no `bBox` (+0x50..) changes and no entity joins or leaves the lists during the pair loop, because collision handlers run inside it (**UNVERIFIED**). It would also need the stock ordering restored afterwards.
- **Estimated saving:** the rejected-pair call overhead only. That is about D²/2 ≈ 3,200 calls at 80 dynamic entities, roughly 0.02-0.05 ms/frame (**UNVERIFIED**, not profiled at that granularity).
- **Recommendation:** do not build. Revisit only if `VehicleGeometryContact` ships on by default, and then fix that hook's cost first.
