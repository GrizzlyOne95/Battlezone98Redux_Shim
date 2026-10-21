# AttackTask: where the time goes, and what can be sped up exactly (2026-10-21)

**Goal:** speed up `AttackTask::DoState` (GOG 0x00478A50) without changing a single result.
**Scope:** GOG 2.2.301 exe, 80-craft `avtank` combat benchmark (`run_live_combat_benchmark.ps1 -Scenario combat`).

Confidence labels:
- **[C]** confirmed in the GOG bytes;
- **[1.5]** taken from the named 1.5 decompile only;
- **[I]** inferred.

No decompiler output is reproduced here. Addresses are GOG RVAs plus 0x400000.

## 1. Profile

The figures come from cpu-sampler captures of the 80-craft combat run, inclusive ms per frame, with stock code under `AttackTask::DoState`. The total is **0.752 ms/frame**.

| Callee | ms/frame | What it is |
|---|---|---|
| 0x463FC0 NearestVehicle | 0.265 | Scans the entire `GameObject::objectList` for the closest vehicle. Inside it: Dist3D_Squared 0.071, iterator ops ~0.04 |
| 0x605F70 DoBlast | 0.117 | FindPotentialField 0.065, EvadeLineOfFireForce 0.023, AddCliffForce 0.018 |
| 0x601250 DoGoto | 0.106 | GotoForce 0.088 (FindPotentialField, EvadeLOF, AddCliff), IsStraightPlan |
| 0x462B60 MayHitFriends | 0.104 | Grid range search along the firing lane; writes closeAdjust |
| 0x607520 DoFlee | 0.058 | The same force trio as DoBlast |
| 0x603AD0 AbleToHit | 0.045 | One terrain LOS ray (0x784620) at most, 0.033 |
| 0x606E20 DoSlide | 0.029 | The same force trio |
| self | ~0.02 | |

**Call frequency [C]:**
- `UnitTask::Execute` (0x6002A0) calls DoState every AI update, with no think interval.
- About 6,000 calls/s at 80 craft, ~70 per frame, ~10.6 µs per call.

**Scaling:** the cost is roughly quadratic in craft count.

| Craft | AttackTask ms/frame |
|---|---|
| 20 | 0.099 |
| 40 | 0.267 |
| 80 | 0.79 |

Each attacker's NearestVehicle walks every object, and the grid searches get denser as craft are added.

**Our hook** (`AttackTaskDoStateTuningHook`, `OPENSHIM_PROFILE_ATTACK_TASK=1`) adds about 2% on top of stock.

## 2. Does multiplayer require bit-identical AI?

The user's concern was that multiplayer depends on AttackTask results being exact. The code says the multiplayer model is **owner-authoritative replication, not lockstep**:

- **[C]** Each object has one owner (`DistributedObject::object_type`: 1 local, 2 remote).
- **[C]** `SetRemote` (Redux 0x4B7F20; 1.5 0x48E988) deletes the replica's AI process. A replica of an AI unit runs a do-nothing `NetProcess`.
- **[C]** Commands to a remote object are forwarded to its owner (a "CO" packet).
- **[C]** Owners send quantised transforms (`NetUtil_ReduceMatrix`, 14 bytes). Replicas can never be bit-identical to the owner.
- **[C]** No packet carries a per-tick input, a frame number or a state hash.
  - The exe crc32 is only a join/cheat check.
  - `Net_DoSyncStart` is a one-time start barrier.
- **[C]** The shared clock is a ping-estimated offset, used to timestamp packets.
- **[I]** "Dead reckoning" (replicas extrapolate between packets) is plausible from the fields involved (`net_dt`, `iter`, `true_transform`), but the code that consumes them has not been found.
- **[I]** AttackTask therefore runs only on the unit's owner. I did not read the per-process loop itself (`AiMission::Update`). The inference rests on the `SetRemote`/`NetProcess` evidence above.

The earlier note ("clock offset plus dead reckoning, not lockstep") is correct on lockstep and on the clock offset. Its dead-reckoning half is likely but unproven.

**What "exact" has to cover, then:**
- **Must match:** the owner's outputs for the same inputs. Those are the commands it issues, the weapon fire, the ordnance it spawns, the damage, and the transform it sends.
- **Cross-peer float equality:** not required, because peers already differ.

The prototype below meets the stricter bar anyway. It produces the same bits, in the same order, from the same inputs, so it is also exact for single-player replays and save/load.

For AttackTask's chain specifically:
- **RNG [1.5 + C grep]:** AttackTask's chain calls none of `Random_Sync`, `Pseudo_Rand`/`Rand_Counter` or libc `rand`. Its "random" evasion is `Noise1D` (0x822970), a pure function of sim time. Skipping or deferring a pure callee therefore cannot shift any RNG stream.
- **Float order [C]:** SSE scalar float32 throughout, stored to float locals, with no FMA. `Dist3D_Squared` is ((dx·dx + dy·dy) + dz·dz). Reimplementing any of it would have to use the same operations in the same order. The prototype reimplements nothing: it calls the stock function with the stock arguments.
- **Tie-breaks [C]:** NearestVehicle uses strict `<` from a best of 1e30, so the first minimum in list order wins. Any replacement scan has to visit candidates in list order.
- **Iteration order:** the order in which units are processed does not cross the wire. Within one unit, the order of calls in DoState is kept.

## 3. Candidates

| # | Candidate | Expected saving at 80 craft | Exact? | Status |
|---|---|---|---|---|
| A | **Lazy NearestVehicle**: run the scan only when DoGoto, DoFollow or UpdateSpecial will read it | Up to 0.265 ms/frame, minus the calls that do read it (measured below) | Yes, same call with the same arguments, before any input can change (§4) | **Prototyped** |
| B | Per-AI-update candidate array for NearestVehicle: filter the object list once, then scan pointers and positions | Most of the remaining scan cost | Only if no object moves, is created or is destroyed during the AI pass; needs proof that AI and physics are not interleaved per object | Not done: that proof is missing |
| C | Spatial broadphase for NearestVehicle | Large at high counts | Only if the first-in-list-order tie-break is kept, e.g. by gathering candidates and taking the min by list index | Not done; B first |
| D | Terrain LOS cache (0x784620) keyed on exact endpoints | ≤0.033 ms | Yes, if keyed on bit-equal endpoints with a terrain-dirty flag, but endpoints rarely repeat | Not worth it |
| E | IsStraightPlan keyed on plan point + craft xz | Small | Yes with an exact key | Not measured |
| — | MayHitFriends | — | **No.** It writes closeAdjust every call, so it cannot be skipped | Rejected |
| — | FindPotentialField / GotoForce caching | — | **No.** They depend on live positions of moving objects | Rejected |

There are no ODF lookups, no allocations and no RNG in the DoState chain, so no saving was found there.

## 4. Why lazy NearestVehicle is exact

The prolog does `task+0x7C (avoidObj) = NearestVehicle(craft, craft->GetPosition())` at 0x478BB1 on every call. The prototype has two parts:

1. **At the prolog:** store null and remember `(task, craft, position pointer)`.
2. **Before each reader:** if the reader's `this` is the pending task, call stock NearestVehicle with those same arguments, store the result, and clear the pending record.

The reader call sites are:
- DoGoto at 0x47912E, 0x4792BF and 0x479401;
- DoFollow at 0x4791F4;
- UpdateSpecial at 0x4795A7.

The result is identical to stock if every reader that runs sees the same value stock would have stored, and no unresolved null is ever read. The supporting facts:

1. **Every path to a reader passes the prolog [C].** Every early exit before 0x478BB1 jumps to the DoState return (0x4795AC). That return skips UpdateSpecial too. No code outside DoState jumps into it.
2. **avoidObj has exactly three readers [1.5 + C].**
   - In 1.5, `avoidObj` is read only by `UnitTask::DoGoto`, `DoFollow` and `UpdateSpecial`. Only the constructors write it, and it is not saved.
   - In the GOG exe, the five calls of those methods inside AttackTask::DoState are the only calls with an AttackTask `this`. The other call sites are in other task classes' own methods, which act on their own objects.
   - So an AttackTask's avoidObj is read only inside its own DoState, after the prolog of that same call.
3. **No inputs change before a resolve [I, tested live by verify mode].** NearestVehicle reads only the object list, each object's class, label, cargo flag and position, and the craft's position.
   - Between the prolog and DoGoto/DoFollow, DoState runs only state predicates and steering helpers: AbleToHit, IsStuck, the CheckX helpers and distance tests. None of them creates, destroys or moves an object.
   - Weapon fire (UpdateWeapon 0x604130) comes after the state switch, in the epilog.
4. **UpdateSpecial is handled by keeping the eager path [C].**
   - UpdateSpecial runs after UpdateWeapon, and firing can create objects (a dispensed mine is a GameObject).
   - UpdateSpecial reads avoidObj only when the task has a special weapon (`+0xB8` non-null; 0x60556C) and the weapon signature is `PMDR`.
   - So a call whose task has a special weapon at the prolog keeps the stock eager scan.
   - The UpdateSpecial thunk resolves only when +0xB8 has become non-null during the call. It counts those resolves, and none has been seen.
5. **NearestVehicle is pure [C].** It makes no writes, no RNG calls and no allocations. Calling it later with the same inputs gives the same bits. Calling it zero times has no side effect to miss.

**Not covered:** the prototype does not prove that nothing in the state switch ever edits the object list. Fact 3 rests on reading the callees. **Verify mode** is the live test of it.

## 5. Verification design

1. **Per-call side by side (`OPENSHIM_AI_LAZY_NEAREST=verify`).**
   - The prolog runs stock (eager) and remembers its arguments.
   - At every reader it re-runs stock NearestVehicle with those arguments and compares the answer with what stock stored. Each mismatch is counted by reader.
   - A clean run shows that a deferred scan returns exactly the eager answer in every reader the run reached.
2. **Deterministic replay (designed, not run).**
   - Load a fixed single-player save with `PreciseTimestep` off and a fixed frame step.
   - Run N frames each way (off, then on).
   - Log per frame, for every AI craft: its position bits, its command and target handle, and the weapon-fire events. Diff the two logs.
   - Redux has no replay system, so this needs a deterministic frame clock harness that does not exist yet.
   - Verify mode is the cheaper equivalent for this change, because the change touches nothing but the timing of one pure call.
3. **Performance A/B.** Interleave off/lazy runs, 3 of each, 60 s each, at 80 craft. The metric is the `[AIKITE] profile` "stock" time (the inclusive cost of AttackTask::DoState with the lazy thunks inside it) per call and per second.

## 6. Prototype

`src/patches/ai_nearest_vehicle_lazy.cpp`.

**Switch:** `OPENSHIM_AI_LAZY_NEAREST` = `1` (lazy) or `verify`. It is off by default.

**Hooks:**
- six `call rel32` retargets, all inside AttackTask::DoState: the prolog plus five readers;
- the `patches.json` rows `AttackTaskNearestVehicleCall`, `AttackTaskDoGotoCallA/B/C`, `AttackTaskDoFollowCall` and `AttackTaskUpdateSpecialCall`, plus the four target functions `UnitTask*`.
- Other task classes, and other callers of NearestVehicle, DoGoto, DoFollow and UpdateSpecial, are untouched.

**Fail-closed behaviour:**
- Any row mismatch leaves stock in place.
- A partial install is rolled back.

**Gate:** laziness is SinglePlayer-tier (`AttackTaskLazyNearest` in the MP-gate registry). It stands down while the local net id is non-zero.

**Status:** an experiment, not a default.

### Results

**Setup:**
- 80-craft `avtank` combat, 60 s per run, telemetry capture, `OPENSHIM_PROFILE_ATTACK_TASK=1`.
- Arms interleaved off/lazy ×3, then one verify run. Run 2026-10-21 on GOG.
- "Stock" is the inclusive time of AttackTask::DoState, measured by the existing profile hook. It includes the lazy thunks.

| Run | Mode | DoState calls | µs/call | ms per wall second | Deferred scans resolved |
|---|---|---|---|---|---|
| 1 | off | 435,352 | 10.78 | 78.2 | — |
| 2 | lazy | 450,713 | 8.04 | 60.4 | 34% |
| 3 | off | 446,219 | 10.37 | 77.1 | — |
| 4 | lazy | 415,106 | 8.16 | 56.5 | 29% |
| 5 | off | 425,677 | 10.29 | 73.0 | — |
| 6 | lazy | 418,438 | 8.05 | 56.2 | 33% |
| 7 | verify | 394,115 | 15.18 (scans 2–3×) | 119.6 | **505,571 checks, 0 mismatches** |

**Cost:**
- Mean cost per call: off 10.48 µs, lazy 8.08 µs, a **−23%** cut in AttackTask's total cost.
- Per wall second: 76.1 → 57.7 ms, so about **0.18 ms/frame** at the ~100 fps of this run.
- About two thirds of calls never needed the scan. Every resolve came from DoGoto. DoFollow and UpdateSpecial never resolved, and no task had a special weapon (`eager=0` in every window).

**Frame time:**
- Mean: off 10.22 ms, lazy 10.20 ms.
- The run-to-run spread (9.6–10.8 ms mean, 17–31 ms 1% low) is far larger than a 0.18 ms saving. **No frame-time change is resolvable at this sample size.**
- The saving is real in the AI cost and scales about quadratically with craft count, but on its own it is not a visible fps change at 80 craft.

**Exactness:**
- Verify mode re-ran the scan at every reader with the prolog's arguments: 505,571 checks, 0 mismatches.
- That is the live test of fact 3 in §4, for the states this benchmark reaches.
- It does not cover:
  - special-weapon tasks (they keep the eager path anyway);
  - DoFollow (never reached here);
  - mission scripts that create or destroy objects from inside an AI callback.

### Recommendation

- **Keep it opt-in for now.** It is exact by construction and by measurement in the states covered.
- **Before making it a [Fixes]-style default (single-player only):** run verify mode on a campaign mission with follow orders and scripted spawns.
- **The larger remaining win is candidate B** (a prefiltered candidate array for the 34% of calls that still scan). It needs one more proof first: that the AI pass never interleaves with physics or object creation. Read `AiMission::Update` and the sim loop to confirm.
