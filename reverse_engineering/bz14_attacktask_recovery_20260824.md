# Battlezone 1.4 AttackTask Policy — Reconstruction and Redux Port Feasibility

Date: 2026-08-24
Branch: `agent/bz14-attack-policy-port` (OpenShim)
Supersedes portions of `bz14_evasive_ai_investigation_20260823.md` §9–§10: the
runtime-anchor claims are corrected by today's live-execution probes (§6).

Claim tags: **PROVEN** (decompile/disassembly/runtime bytes read directly),
**RUNTIME-PROVEN** (live-process instrumentation this session),
**HIGH CONFIDENCE**, **PLAUSIBLE**, **UNKNOWN**.

## 1. Executive summary

1. The full Battlezone 1.4 `AttackTask` tactical policy has been reconstructed
   (state machine, thresholds, predicates, movement-primitive wiring) from the
   1.4 runtime-unpacked corpus and cross-checked line-by-line against the
   PDB-named 1.5 source tree (`BZ1_Source\1.5`). See §3.
2. The prior report's claim that Redux executes this machine at
   `AttackTask::DoState = 0x00478A50` is correct statically but wrong
   dynamically: in live GOG build 2.2.301 gameplay that function **never
   executes** during tank attack engagements. Multiple independent
   instrumentation methods agree (§6). Byte-presence validation
   ("hook-validated") does not establish execution.
3. Live tank combat in 2.2.301 runs through per-family **blast-skeleton task**
   bodies — states `{2,3,5,D}`; e.g. body `0x00614DD0` in RocketTankAttack
   (RTTI vftable `0x0088AE6C`), observed ~35k ticks during one
   avtank-vs-svtank engagement — plus the process layer
   (`OffensiveProcess::DoSubTask` @`0x583520`, `WingmanProcess::ShouldAttack`
   @`0x613B70`; both confirmed executing tens of thousands of times). The
   generic AttackTask object is constructed by the live process layer (ctor
   `0x00477E60`, called from `0x00583CF0` and `0x00613C10`) but its `DoState`
   was never observed on the executed path.
4. The planned seam — post-decision override of recorded transitions inside
   `AttackTask::DoState` — is therefore **not viable on this build**. Per the
   task's decision gate, implementation stops here. A validated, fail-closed,
   default-off OpenShim implementation of the recovered policy plus unit tests
   ships for the future (§8), together with candidate future strategies (§7).

## 2. Conventions and evidence sources

- **1.4** = runtime-unpacked image `bz14_unpacked.exe` (identity map:
  file offset = VA − 0x400000), corpus `%TEMP%\opencode\bz14_diff\decomp14\`.
- **1.5** = `BZ1_Source\1.5\all_decompiled.c` (PDB-named) + `functions\`.
- **Redux** = GOG `battlezone98redux.exe` 2.2.301 (file dated 2026-01-29,
  5,425,152 bytes, packed: SizeOfImage ≈ 43 MB; execution observed from
  private RWX arenas at randomized per-boot bases). Static analysis used the
  Ghidra project program `/battlezone98redux.exe-007c64`; corpus VAs were
  re-validated against live memory this session (§6).
- Live instrumentation: Frida 17.7.3 (attach/spawn), external
  ReadProcessMemory cross-check, OpenShim's own detour telemetry.
- Validation mission: `reverse_engineering/test_missions/bz14atk/`
  (deploys as `addon\bz14atk`; issues native `Attack()`/`Hunt()`; prints
  `[BZ14ATK]` telemetry every second).

## 3. Recovered 1.4 AttackTask policy

### 3.1 Task layout and dispatcher mechanics

| Field | 1.4 offset | Meaning | Confidence |
|---|---|---|---|
| curState | +0x0C | current state id | PROVEN |
| nextState | +0x10 | transition record | PROVEN |
| craft | +0x14 | owner OBJ76 | PROVEN |
| himHandle / him | +0x18 / +0x1C | target handle / resolved object | PROVEN |
| slideRef | +0x2C..34 | target-position anchor refreshed on entry of {2,B,C} | PROVEN |
| forceVec | +0x44..4C | steering snapshot cleared by CleanState | PROVEN |
| rangeSq | +0x88 | weapon/slide ring (CalcRange) | PROVEN |
| ableToHit latch | +0xA4 | per-tick AbleToHit result | PROVEN |
| aimDir | +0xB4..C0 | emitted aim direction | PROVEN |
| stateEntryTime | +0xD4 | Get_Time() snapshot on entering {8,A} | PROVEN |
| groupPtr | +0xD8 | attack-group list | PROVEN |
| waitSq | +0xF4 | ctor 100000.0 (~316²) direct-assault radius | PROVEN |
| arriveSq | +0xF8 | ctor 136900.0 (370²) travel→wait radius | PROVEN |
| fleeFrom | +0xFC | flee anchor (cleared when leaving 9) | PROVEN |

Craft damage fields: lastDamageTime +0x1DC, newest attacker handle +0x1E8
(PROVEN).

Dispatcher (1.5 `UnitProcess::Execute` @0x4697D9, PDB-named):

```c
if (nextState != NO_STATE) {
    CleanState(); curState = nextState; nextState = NO_STATE; InitState();
}
if (ChangesState(command)) { /* re-init */ }
if (!skipGate()) DoState();
```

Consequences used by the port design: any nonzero `nextState` write triggers a
full Clean/Init cycle next dispatch (equal-value writes are re-entry requests);
leaving `nextState == 0` is a clean "stay".

### 3.2 State machine (`DoState` @0x40CDE0)

States {2,3,4,5,6,7,8,9,A(10),B(11),C(12),D(13)}; state 1 runs ChooseState on
entry (@0x40C7F0). Constants read from the dump:

| Constant | Value | Use |
|---|---|---|
| `_DAT_005E6E94` | 22500 (150²) | ChooseState buddy scan radius |
| `_DAT_005E6EA8` | 10000 (100²) | target drifted >100 u from anchor |
| `_DAT_005E6EAC` | 100 (10²) | self within 10 u of stale anchor |
| `_DAT_005E6EB0` | 2500 (50²) | follow-close threshold |
| `_DAT_005E6EB4` | 225 (15²) | follow-travel goto gate |
| `_DAT_005E6EB8` | 25 (5²) | tail neighbor de-clump radius |
| `_DAT_005E6EA4` | 5625 (75²) | flee exit distance |
| `_DAT_005E6EA0` | −8.0 | stand window (now ≤ entry+8 s) |
| `_DAT_005E6E9C` | 5.0 | slide-force arrival length |

All distances horizontal (x/z distance²).

Per-state behavior (PROVEN unless tagged):

- **1 INIT** → ChooseState: cmdTarget dead/null → **D**;
  dist²(self,cmdTarget) < waitSq → him:=cmdTarget, **2 APPROACH**;
  else nearest group member whose task state == B within 150² → follow them
  (**4 FOLLOW**); none → **B TRAVEL**.
- **2 APPROACH**: AbleToHit → **7 SLIDE** [site 0x40D190] (delta D1);
  stuck → 3; target drifted >100² from anchor → re-enter 2 (re-anchor);
  self within 10² of stale anchor → re-enter 2; else DoGoto (0x46D350).
- **3 UNSTUCK**: DoStuck 0x46DE70 (enter helper 0x46DE20).
- **4 FOLLOW**: leader = him+0xF4 container → +0x30 task object;
  leader invalid → 1; leader fighting {5,7,8,9,A} → him:=cmdTarget,
  **2 APPROACH**; dist² ≤ 100² → DoFollow-hold (FUN_0046F2B0) or stuck→3;
  far → refresh anchor, **C FOLLOW-TRAVEL**.
- **5 BLAST**: AbleToHit ? DoBlast(0x46E900) : **2 APPROACH**.
- **6 WAIT/SIT**: inline group-list scan (member task nextState==C referencing
  me → DoSit 0x46DBA0); nobody waits → **2**.
- **7 SLIDE** (strafe duel): AbleToHit latch;
  dist² > rangeSq(+0x88) → **2 APPROACH** [pursuit];
  enemy activity state via vtbl slot-12 field (+0xAC): engaged set
  **{2,5,7}** → **A BLAST-HOLD** [site 0x40CF97; delta D2 core];
  stuck → 3; SidewaysAndClose (dist<50 ∧ quad(my_head, bearing→him) ∈ {2,6};
  buildings forced quad 4) → **8 STAND+FIRE** regardless of firing solution
  [delta D2c]; else DoSlide (0x46ECF0); force length < 5 → **A BLAST-HOLD**.
  No time cap exists in 1.4.
- **8 STAND+FIRE**: fresh hit (craft.lastDamageTime > entryTime) →
  **9 FLEE**, fleeFrom := newest attacker (+0x1E8) [LAB_0040D08C];
  lost shot → **7 SLIDE**; stood > 8 s → **7 SLIDE** [delta D4];
  else DoStand (0x46E6B0).
- **9 FLEE**: attacker gone → **7**; dist² > 5625 → **7**; stuck → **A**;
  else DoFlee (0x46F090). No time bound in 1.4 [delta D3].
- **A BLAST-HOLD**: fresh hit → **9 FLEE**; lost shot → **7 SLIDE**
  (no building special case — corrects the prior report's diagram);
  else DoBlast.
- **B TRAVEL**: craft within arriveSq (370²) of anchor → **6 WAIT**;
  stuck → 3; target moved >100² → re-enter B; else DoGoto anchor.
- **C FOLLOW-TRAVEL**: leader invalid → 1; leader fighting → him:=cmdTarget,
  **2**; close (≤50²) → **2**; else travel to anchor (re-anchor when leader
  moves >100²; goto gate 15²), stuck → 3.
- **D DONE**: terminal early-out at function head.

Common tail (only when ableToHit latched): neighbor query FUN_0040C400 →
friend within 5 u ⇒ power := 1.0, else power := MayHitFriends(craft, aimDir,
0.3) ? 0 : 0.25 (ctrl block craft+0x228, power +0xCC); UpdateWeapon (0x46E530)
only when no friendly in cone. States that never latch ableToHit
({3,4,6,9,B,C}) skip weapon updates entirely that tick — authentic 1.4 fire
discipline.

ChooseState (@0x40C7F0) is an entry-time selector only (its sole caller is
OnEnterState @0x40CC40, xref-proven); the tactical policy lives in DoState.

### 3.3 Pseudocode of the divergent decisions (1.4 reference)

```c
// state 2 APPROACH
if (AbleToHit())              next = 7;   // D1: strafe-duel first
// state 7 SLIDE
else if (dist2 > rangeSq)     next = 2;   // pursue
else if (enemyStateIn{2,5,7}) next = 10;  // D2: engaged -> blast-hold
else if (SidewaysAndClose())  next = 8;   // abeam & close (any firing solution)
else { DoSlide(); if (forceLen < 5) next = 10; } // uncapped in 1.4
// state 8 STAND+FIRE
if (freshHit)                 next = 9;   // flee from newest attacker
else if (!aTH)                next = 7;
else if (now > entry + 8.0)   next = 7;   // D4: rotate back to slide
else DoStand();
// state 9 FLEE
if (attackerGone || dist2 > 5625) next = 7; // D3: no time bound
else if (stuck) next = 10; else DoFlee();
// state A BLAST-HOLD
if (freshHit) next = 9;
else if (!aTH) next = 7;                    // D5: always back to slide
else DoBlast();
```

Anti-thrash properties: transitions persist until a condition flips; the only
timers are the 8 s stand window and damage freshness; sliding/fleeing are
unbounded in 1.4. The stun-lock cycle documented previously
(9 -> 7 -> {8,A} -> 9 under sustained fire) is authentic and reproduced by
these rules with no added smoothing.

## 4. Redux static architecture (GOG corpus)

| Item | Address | Notes |
|---|---|---|
| AttackTask vftable | 0x00876358 | RTTI-named; slots read this session: +0x28 InitState(0x478770), +0x2C CleanState(0x478930), **+0x30 DoState(0x478A50)** |
| AttackTask ctor / dtor | 0x00477E60 / 0x00477FB0 | ctor called from FUN_00583CF0 and FUN_00613C10 (live process layer); task object size 0x140 |
| ChooseState | 0x004782D0 | structurally identical to 1.4/1.5; outer threshold task+0x134 initialized to 100000.0 by ctor (FUN_00477E60 writes dword[0x4D]) — resolves the prior report's open question |
| DoState body | 0x00478A50 | full machine present statically; **not executed in live engagements** (§6) |
| RocketTankAttack vftable / DoState body | 0x0088AE6C / 0x00614DD0 | RTTI-named; states {2,3,5,D}; mad floor 0xBE99999A at ctrl+0xD0, ring decay x5.0 clamp 20.0 at task+0xF0; slot layout matches AttackTask (+0x30 DoState) |
| OffensiveProcess::DoSubTask | 0x00583520 | live (RUNTIME-PROVEN executing) |
| WingmanProcess::ShouldAttack | 0x00613B70 | live (RUNTIME-PROVEN executing) |
| UnitTask primitives | DoGoto 0x601250, DoStuck 0x6029B0, DoSlide 0x606E20, DoStand 0x6057E0, DoBlast 0x605F70, DoFlee 0x607520 | zero-extra-arg __thiscall on task (verified from stock call sites in decompile+asm) |
| Helpers | DistanceSq 0x462010 (horizontal), SidewaysAndClose 0x4788D0 (cdecl, two interface results), enemy activity field +0x84 of vtbl-slot-12 result, MayHitFriends 0x462B60(craft,dir,0.3,1.0), GetTime 0x822D80, craft lastDamageTime +0x1E8 (getter FUN_0046D040), newest attacker +0x1F4 (FUN_00462530), GetHandle 0x462380, resolve 0x462630 | PROVEN from decompiles |

Corrections to the prior report (all PROVEN this session):

- The slide-exit engagement predicate was NOT replaced by IsBuilding.
  1.4 tests enemy activity state {2,5,7} (+0xAC of slot-12 result);
  Redux FUN_00477D70 tests the same field (+0x84) with set {2,5,7,**10**}.
  1.5 genuinely calls a real IsBuilding there (PDB-named @0x40ED47) — the
  predicate changed twice across builds. Redux is *closer* to 1.4 here than
  1.5 was, differing only by the extra {10} arm.
- SaC->STAND gating on ableToHit exists in both 1.5 and Redux (D2c is
  1.5-inherited, not Redux-only).
- State-A lost-shot routing: 1.4 always -> 7; 1.5 IsBuilding ? 2 : 7;
  Redux engaged{2,5,7,10} ? 2 : 7.

## 5. 1.4 -> Redux mapping and adapter strategy

| 1.4 concept | Redux equivalent | Confidence |
|---|---|---|
| curState/nextState | task+0x08 / +0x0C (same semantics; Execute applies nonzero, clears after) | PROVEN |
| craft/him handles | +0x10 / +0x14(handle) +0x18(obj); cmdTarget +0x24 | PROVEN |
| rangeSq / ableToHit latch / entry time | +0xA0 / +0xC4(u8) / +0x100 | PROVEN |
| fleeFrom | +0x13C | PROVEN |
| forceVec snapshot | +0x4C..54 | PROVEN |
| craft lastDamageTime / attacker | +0x1E8 / +0x1F4 | PROVEN |
| enemy activity field | slot12(him)+0x84 (values share AttackTask state ids) | HIGH CONFIDENCE on semantics, container identity UNKNOWN |
| AbleToHit | FUN_00603AD0 writes +0xC4 latch per tick | PROVEN |
| movement/weapons | same primitive addresses as table above; all authoritative engine code | PROVEN |

Adapter strategy that was implemented (and why it is currently inert):
wrap DoState with a trampoline detour; let stock run; then re-evaluate only
the four provably divergent recorded-transition sites using the recovered 1.4
predicates and rewrite task+0x0C where they differ (0 = stay). Stock timer
windows in states 7/9 are neutralized per-tick by temporarily freshening
task+0x100 so their false branches cannot skip movement primitives; original
values restored before return. When stock's gating skipped its own DoSlide
while 1.4 would keep sliding, the game primitive FUN_00606E20 is invoked
directly (zero-extra-arg __thiscall, exact stock call shape) so suppressed
transitions cannot stall the duel cycle. No 1.4 memory layouts, no movement,
steering, navigation or weapon replacements.

## 6. Runtime findings on live GOG 2.2.301 (RUNTIME-PROVEN)

All observations below were collected this session against
`battlezone98redux.exe` PID-verified sessions using the bz14atk validation
mission, with the OpenShim legacy-policy hook (shadow mode) installed and byte-
validated, and cross-checked with Frida 17.7.3 and external ReadProcessMemory.

### 6.1 AttackTask::DoState does not execute

Evidence lines:

1. OpenShim detour telemetry: hook installed and byte-validated at 0x478A50
   (e.g. `[BZ14] ... SHADOW at DoState=0x00478A50 trampoline=0x...`), then a
   complete engagement ran (telemetry `cmd=4` = ATTACK per the AiCommand enum,
   first hit at t+1.3 s, target killed) producing **zero** hook-body entries
   (`[BZ14h]` budgeted entry log stayed empty across multiple runs; counters
   otherwise verified working).
2. Frida Interceptor at module VA 0x878A50: zero calls during confirmed-live
   combat windows in repeated sessions.
3. Frida spawn-mode attach from process start: same zero result across an
   entire mission lifetime.
4. Pattern scan of all r-x ranges for the exact prologue
   `55 8B EC 83 EC 7C 89 4D FC` finds exactly one copy (the private RWX arena
   copy at a randomized base); hooking that copy also yields zero calls during
   live engagements.
5. Control probes in the same sessions prove the instrumentation stack:
   Stalker call-summary shows hundreds of distinct module-range functions
   executing per second; FUN_00583520 / FUN_00613B70 / FUN_00614DD0 hooks
   counted tens of thousands of calls during the same windows in which the
   DoState probes counted zero.

Conclusion (HIGH CONFIDENCE, approaching certain): the corpus body at
0x00478A50 is not on the executed path of these engagements. The prior
report's "hook-validated runtime anchor" established byte presence only.

### 6.2 What actually executes

Subtask vtable identification via live DoSubTask (0x583520) hook reading
process+0x38 during a Hunt/Attack engagement:

| subtask vtable | RTTI name (Ghidra) | ticks observed | notes |
|---|---|---|---|
| 0x88AE6C | RocketTankAttack | ~35k | states {5,...}; the attacker's active brain |
| 0x88590C | (unnamed region) | ~13k | curState=1; defender-side task |
| 0x889F50 / 0x889ED8 | (unnamed) | transient | briefly constructed |

Plus process layer: OffensiveProcess::DoSubTask and WingmanProcess::
ShouldAttack executing continuously. The 0x614DD0 body decompiles to the
blast skeleton `{2,3,5,D}` with AbleToHit -> BLAST routing — i.e. the
"D1-inverted stop-and-shoot" behavior is delivered by THIS family, not by
AttackTask.

Unit->process routing therefore differs from the prior model in this build
(an avtank attacker ran a RocketTankFriend process + RocketTankAttack task;
the svtank defender ran an unnamed TankFriend-side family). Whether generic
AttackTask serves any live path (e.g. specific orders such as player-commanded
ATTACK vs autonomous engagement) remains UNKNOWN and needs its own RE pass.

### 6.3 Memory layout caveats discovered

- The shipped exe is packed: file 5.4 MB but SizeOfImage ~43 MB; static Ghidra
  analysis must use the unpacked corpus, whose VAs match live *module* memory
  for the functions tested (0x583520/0x613B70/0x614DD0 executed at exactly
  those VAs).
- Module pages at the AttackTask cluster were observed holding non-code data
  ("abstor"/"abshld" patterns) at various times, while other module code kept
  executing; private RWX arena copies of code exist at randomized bases.
  Any address-pinned hooking scheme in this environment must re-validate
  execution assumptions at runtime rather than trusting install-time bytes.
  This caveat applies to the whole constant-address inline-hook layer, not
  just this feature.

## 7. Decision gate verdict and future strategy

Verdict: **stop** — the planned narrow seam cannot influence live behavior on
this build because its target function is execution-dead there. This is a
precise incompatibility, not a general one: the recovered policy, the Redux
primitive set, and the dispatcher mechanics are all fully compatible; only the
anchor's liveness fails.

Best candidate future strategies (in order):

1. **Identify the live attack-task families' decision bodies** (the unnamed
   vtable regions around 0x88590C and their DoState equivalents) and map the
   1.4 decisions onto them. The blast-skeleton lacks the entire
   slide/stand/flee surface, so this likely becomes strategy 2 anyway.
2. **Full replacement DoState for the live attack-task class(es)**: OpenShim
   already owns every required primitive signature (DoGoto/DoSlide/DoStand/
   DoBlast/DoFlee/DoStuck/SidewaysAndClose/DistanceSq/GetTime — PROVEN above)
   plus the recorded-transition protocol; a replacement virtual dispatched
   through the same vtable slot would restore the complete 1.4 machine while
   keeping movement/weapons authoritative. Higher risk than the abandoned
   seam (reimplements the tail too), so gate behind the same default-off
   configuration and shadow mode.
3. **Process-layer route**: ShouldAttack/DoSubTask are proven-live narrower
   surfaces for commitment/retarget behavior, complementing either of the
   above.

Additional RE needed before resuming:

- Enumerate which orders/unit classes actually construct and tick which attack
  task classes in 2.2.301 (the ctor callers 0x583CF0/0x613C10 contexts).
- Name the unnamed vtable families (RTTI walk around 0x885xxx/0x889xxx) and
  recover their DoState bodies.
- Confirm whether the module-page mutation observed at the AttackTask cluster
  affects long-lived hooks generally (relevant repo-wide).

## 8. Shipped implementation (validated, inert by default)

Files: `include/bz14_attack_policy.h` (pure decision core),
`include/bz14_attack_redux.h` + `src/patches/bz14_attack_redux.cpp`
(SEH-guarded accessors), `src/patches/bz14_attack_policy.cpp`
(config/detour/hook), `tests/bz14_attack_policy_tests.cpp`.

- Config `[AI] Legacy14AttackBehavior` (default OFF), env aliases
  `OPENSHIM_LEGACY_ATTACK`-style documented in `openshim.ini.example`;
  shadow mode `Legacy14AttackShadow` evaluates both policies and logs
  divergences under `OPENSHIM_TRACE_AI_BZ14=<budget>` without applying them;
  single-player-only gate (net id 0) like other sim-affecting settings;
  arbitration with the AIKITE kite hook (legacy wins the shared detour site
  when enabled; kite unavailable simultaneously, logged).
- Decision core unit-tested (11/11 suite green): D1/D2/D2c/D3/D4/D5 outcomes,
  engaged-set differences, ring boundaries (no invented smoothing),
  quad math replication of get_weapon_quad.
- Build: Release Win32 DLL links clean; tests pass under ctest.
- Runtime status on current build: installs fail-closed, never fires (target
  function execution-dead; §6), i.e. stock behavior is untouched whether the
  option is off or on. When a live seam lands (§7), the same binary surface
  becomes functional without redesign.

## 9. Performance, multiplayer, safety notes (design-level)

- Hot-path cost when armed is O(1) arithmetic + up to two interface calls and
  one SidewaysAndClose per sliding tick; no allocations, no string work unless
  trace budgets are explicitly enabled; counters are plain integers (sim is
  single-threaded). With the option disabled the only cost is one config read
  at startup.
- Determinism: the restored policy is a pure function of simulation state
  (positions, times, state ids); no RNG is introduced (1.4 DoState/ChooseState
  contain none; process-layer rand stays out of scope). Sessions are gated to
  single-player regardless, matching the repo convention for
  simulation-affecting settings.
- Safety: SEH guards on every game-memory touch; byte validation before
  install; trampoline passthrough on any failure; no broad AI patches; no
  weapon-accuracy or aggression changes; stun-lock weakness reproduced
  deliberately as historical behavior.

## 10. Artifact index

- Implementation: files listed in section 8 (this branch).
- Validation mission: `reverse_engineering/test_missions/bz14atk/`.
- Session evidence: `%TEMP%\opencode\frida_spawn_out.txt`, `stack_out.txt`,
  harness snapshots under `reverse_engineering/snapshots/live_combat/20260824_*`.
- Prior context: `bz14_evasive_ai_investigation_20260823.md` (sections 9-10
  corrected here), scratch corpora under `%TEMP%\opencode\bz14_diff\`.
