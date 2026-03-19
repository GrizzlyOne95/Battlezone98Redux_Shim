# AI Process Uniqueness Feasibility

Date: 2026-03-19

Question:

- How much unique AI behavior already exists in the legacy 1.5 process family for
  `TankProcess`, `ScoutProcess`, `RocketTankProcess`, `BomberProcess`, and
  related bases?
- Is it feasible to add more unique behaviors by patching Redux rather than
  rewriting the whole AI stack?
- Concrete example: make bombers stop near max weapon range and attack instead of
  driving into the same close-range flow as the generic wingman family.

## Corpus Used

- Legacy exact-match corpus:
  `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full`
- Current Redux best-effort corpus:
  `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort`

## Executive Conclusion

Yes, adding more unique AI behavior is feasible, but the process family splits
into two different cases:

- `ScoutProcess` and `RocketTankProcess` already have real legacy specialization.
  Those are good candidates for direct Redux patching because the old behavior
  gives concrete ownership points.
- `TankProcess` and `BomberProcess` do not have meaningful legacy-specialized
  combat logic. In 1.5 they mostly inherit `WingmanProcess` behavior. That means
  "more unique bomber/tank behavior" is not a straight legacy port. It is new
  behavior that should be injected into shared `WingmanProcess` or `AttackTask`
  flow with bomber-only or tank-only gating.

The bomber standoff example fits the second category. The best patch surface is
not `BomberProcess` itself, because there is no native bomber-specific attack
routine to port. The best likely surfaces are:

- shared `AttackTask` state selection and movement logic
- shared `WingmanProcess` attack-task creation if we want bomber-only task
  substitution
- process-type-gated behavior using the current Redux process vtable values

## What Legacy 1.5 Actually Specializes

### `ScoutProcess`

Legacy `ScoutProcess` has one real specialization:

- `ScoutProcess::ChooseAttackTarget`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/ChooseAttackTarget-0047032d.c`
  - behavior:
    `GetClosestEnemyOrMineWithin(...)`

This is genuinely different from the generic offensive selection path:

- `OffensiveProcess::ChooseAttackTarget`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/ChooseAttackTarget-0044dca0.c`
  - behavior:
    `GetClosestEnemyWithin(...)`

Practical takeaway:

- scouts already have a legacy semantic difference
- adding more scout-specific behavior in Redux is structurally plausible because
  there is already a process-local override family

### `RocketTankProcess`

Legacy `RocketTankProcess` has real specialization through a custom attack-task
type:

- `RocketTankProcess::InitAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/InitAttack-00470a8a.c`
  - allocates `RocketTankAttack`
- `RocketTankProcess::InitSubAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/InitSubAttack-00470abe.c`
  - uses `WingmanBlastAttack` only for the special state `8`, otherwise
    allocates `RocketTankAttack`
- `RocketTankProcess::CleanAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/CleanAttack-0047049a.c`

The custom task also has its own state machine:

- `RocketTankAttack::DoState`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/DoState-00470b90.c`

Practical takeaway:

- rocket tanks are the strongest proof that "shared process family plus
  per-class attack-task override" is a real legacy pattern
- if we want a future bomber-only attack task, the rocket tank path is the best
  structural model

### `TankProcess`

Legacy `TankProcess` does not expose unique combat behavior in the exact corpus.
The visible class-local file is just the constructor:

- `TankProcess::TankProcess`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/TankProcess-004702dd.c`

The exact-match public function inventory shows constructors and destructors, but
no `TankProcess::DoAttack`, `TankProcess::ShouldAttack`, `TankProcess::InitAttack`,
or task-specialized attack routines.

Practical takeaway:

- tank uniqueness would need to be added from scratch in shared paths
- there is no obvious "port this old tank AI routine" target

### `BomberProcess`

Legacy `BomberProcess` is the same story as tank:

- `BomberProcess::BomberProcess`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/BomberProcess-0047039a.c`

The exact-match public function inventory exposes constructors and destructors,
but no bomber-local attack or decision overrides.

Also important:

- no `BomberAttack` class showed up in either corpus
- there is `RocketTankAttack`
- there is `WingmanBlastAttack`
- there is generic `AttackTask`
- there is not a bomber-specific attack-task family to recover

Practical takeaway:

- bomber-specific standoff behavior is feasible, but it is new behavior layered
  onto shared logic, not a latent 1.5 bomber routine waiting to be rehooked

## Shared Legacy Ownership For Tank/Bomber-Like Units

The shared family is:

- `OffensiveProcess`
  - constructor:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/OffensiveProcess-0044daa2.c`
  - note:
    initializes `engageRange`, `followRange`, `weaponRange`, `attackUser`,
    friend/enemy state, etc.
- `WingmanProcess`
  - constructor:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/WingmanProcess-00470196.c`
  - note:
    derives from `OffensiveProcess`
- `WingmanProcess::ShouldAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/ShouldAttack-00470653.c`
- `WingmanProcess::AttackWaitVsAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AttackWaitVsAttack-004705ea.c`
- `WingmanProcess::InitAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/InitAttack-004706a1.c`
  - note:
    allocates generic `AttackTask`
- `WingmanProcess::InitSubAttack`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/InitSubAttack-004706d5.c`
  - note:
    allocates `WingmanBlastAttack` only when state field `0x20 == 8`, otherwise
    generic `AttackTask`

That means generic tank/bomber behavior is really owned by:

- `OffensiveProcess` target acquisition / subtask logic
- `WingmanProcess` attack-state gating and attack-task creation
- `AttackTask` movement and fire-state transitions

## Why The Bomber Range Example Points To `AttackTask`

The generic attack-task state machine is where the "close distance, wait, blast,
flee, or resume goto" decisions live.

Relevant legacy files:

- `AttackTask::ChooseState`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/ChooseState-0040ee98.c`
  - key behavior:
    compares target distance against `attackRangeSq`
    chooses between state `2` and waiting/following states
- `AttackTask::CheckWaiting`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/CheckWaiting-0040f008.c`
- `AttackTask::DoState`
  - decomp:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/DoState-0040f25b.c`
  - key behavior:
    runs the actual state machine for goto, blast, sit, slide, flee, and fire
    decisions

This is the strongest evidence for the bomber request:

- the "drive up close before firing" behavior is primarily task-level
- bomber-only standoff logic can likely be implemented by changing the range
  thresholds or state transitions for bombers inside shared attack-task flow

By contrast, `BomberProcess` itself does not contain a unique fire or spacing
policy to patch.

## Existing Specialized Comparison Points

Two useful reference families already prove that narrow AI-side changes are
viable without rewriting everything:

- artillery
  - current shim already hooks `ArtilleryProcess::DoAttack`
  - legacy anchor:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/DoAttack-0040d498.c`
- turret tank
  - legacy `TurretTankProcess` has a full specialized branch family:
    `DoAttack`, `DoSubTask`, `ShouldAttack`, `FriendShouldAttack`,
    `EnemyShouldAttack`
  - example files:
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/DoAttack-00467461.c`
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/DoSubTask-00467ac5.c`
    `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/ShouldAttack-004677fb.c`

These confirm that process-local and AI-only patching can work when the native
ownership point is concrete.

## Current Redux Anchors

These current Redux addresses are useful starting points from the promoted
best-effort corpus.

### Shared Process / Task Logic

- `AttackTask::ChooseState` at `0x0042C0D0`
- `AttackTask::CheckWaiting` at `0x0042C280`
- `AttackTask::AssignFollowOffset` at `0x0042C300`
- `AttackTask::CheckFollowing` at `0x0042C450`
- `AttackTask::DoState` at `0x0042C680`
- `OffensiveProcess::DoSubTask` at `0x004DFE70`
- `WingmanProcess::AttackWaitVsAttack` at `0x0054C340`
- `WingmanProcess::ShouldAttack` at `0x0054C3B0`
- `ScoutProcess::ChooseAttackTarget` at `0x0054C780`
- `RocketTankProcess::InitAttack` at `0x0054CD70`
- `RocketTankProcess::InitSubAttack` at `0x0054CE60`

Important caveat:

- only `OffensiveProcess::DoSubTask` was directly observed in the Redux decomp
  output during this pass
- the rest come from the current advisory PDB / symbol join, not from a fresh
  Ghidra validation pass
- they are still good first-pass hook candidates, but not yet "fully validated
  disassembly truth" in the same way as the legacy exact corpus

### Current Redux Type Gates

Current Redux imported vtables give direct runtime type checks for process-local
branching:

- `WingmanProcess` vftable `0x0088A6EC`
- `RocketTankProcess` vftable `0x0088A5C0`
- `TankProcess` vftable `0x0088AB9C`
- `ScoutProcess` vftable `0x0088AF98`
- `BomberProcess` vftable `0x0088B178`
- `AttackTask` vftable `0x00876358`
- `WingmanBlastAttack` vftable `0x0088A6B0`
- `RocketTankAttack` vftable `0x0088AE6C`

Practical takeaway:

- if a hook lands in shared `WingmanProcess` or `AttackTask` logic, it is still
  possible to apply bomber-only behavior by inspecting the owning process or task
  type at runtime

## Feasibility Assessment

### 1. More unique scout behavior

Feasible and relatively clean.

Reason:

- legacy already gives a scout-only override point
- Redux still exposes `ScoutProcess::ChooseAttackTarget`
- we can extend scout target selection or attack gating without inventing the
  whole specialization pattern from nothing

### 2. More unique rocket tank behavior

Feasible and structurally strongest.

Reason:

- legacy already uses `RocketTankAttack`
- Redux still exposes `RocketTankProcess::InitAttack`,
  `RocketTankProcess::InitSubAttack`, and `RocketTankAttack`
- this is the clearest candidate for process-local custom attack behavior

### 3. More unique bomber behavior

Feasible, but not as a direct legacy port.

Reason:

- no bomber-local attack routine in legacy
- no `BomberAttack` class in either corpus
- bomber uniqueness must be injected into shared `WingmanProcess` or
  `AttackTask` behavior with a bomber-only gate

Best likely implementation options:

- low-risk option:
  hook `AttackTask::ChooseState` and possibly `AttackTask::DoState`, detect
  bomber-owned tasks, and bias the stand-off thresholds toward max weapon range
- medium-risk option:
  hook `WingmanProcess::InitAttack` for bombers and substitute a custom shim-side
  task object with bomber-specific state behavior
- higher-risk option:
  patch the `BomberProcess` vtable to point selected inherited methods at custom
  shim code, then reimplement the needed parts of shared `WingmanProcess`
  behavior

The low-risk option is the best fit for the example request.

### 4. More unique tank behavior

Feasible, but same caveat as bomber.

Reason:

- no meaningful tank-local combat overrides in the legacy corpus
- tank uniqueness would also need to be added through shared path branching or a
  new custom attack-task policy

## Recommendation

If the next concrete experiment is the bomber stand-off request, the first pass
should be:

1. validate Redux `AttackTask::ChooseState` and `AttackTask::DoState` in Ghidra
   at `0x0042C0D0` and `0x0042C680`
2. recover enough task layout to identify the owning craft/process from the live
   task pointer
3. gate on `BomberProcess` vtable `0x0088B178` or on a bomber craft class test
4. change only the range-based transition logic so bombers stop at a larger
   preferred stand-off distance before `UnitTask::DoBlast` / weapon updates
5. leave `TankProcess`, `ScoutProcess`, and `RocketTankProcess` on their current
   paths unless explicitly opted in

Why this path first:

- smallest behavioral surface
- AI-only scope
- does not require inventing a native `BomberAttack` object model
- can be reverted or tuned with much less risk than a new task-class insertion

## Bottom Line

Adding more unique AI behavior in Redux is feasible.

- `ScoutProcess` and `RocketTankProcess` have real legacy uniqueness we can build
  on directly.
- `TankProcess` and `BomberProcess` mostly do not.
- your bomber "stop at range and fire" idea is still realistic, but the correct
  ownership point is probably shared `AttackTask` logic with bomber-only gating,
  not a direct `BomberProcess` function port from 1.5.

## Implementation Follow-Up

The current shim now takes a first practical step on the bomber request through
the existing AI ODF range hook instead of adding a new process detour.

- if a craft ODF uses `aiName = "BomberFriend"` or `aiName2 = "BomberEnemy"`
  and does not already define explicit `engageRangeAI` or `weaponRangeMinAI`
  tuning, OpenShim derives a fallback `weaponRangeMinAI`
- the derived fallback scans the craft ODF `weaponName1..5` entries, resolves
  each weapon ODF `ordName`, reads the ordnance `shotSpeed` and `lifeSpan`, and
  uses the maximum `(shotSpeed * lifeSpan - 1.0)` range it finds
- for stock bombers like `avhraz` / `svhraz` using `grktbomb` -> `rocket2`,
  that produces an AI range floor of `299.0`
- if a custom bomber ODF swaps in a shorter weapon, the fallback range drops to
  that weapon's computed range instead
- explicit AI ODF tuning still wins over the derived bomber fallback
