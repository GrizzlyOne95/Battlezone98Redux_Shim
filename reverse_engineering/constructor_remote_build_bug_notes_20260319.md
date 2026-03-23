# Constructor Remote Build Bug Notes 2026-03-19

## Summary

Bug:

- AI constructors can continue a scripted facility build from far away after the
  original constructor was killed and later rebuilt.
- Reported repro includes scripted build-order cases and strategy matches.

Most likely legacy source:

- `AI_UnitRemove-005083d9.c`
- specifically the constructor death branch for
  `cc_construct_type != 0 && cc_constructing != 0`

## Root Cause

The AI build-program system reserves a facility build before the constructor
actually finishes the job.

Relevant flow:

1. `AIBuild_BuildListWhatToMakeWith-0050c92c.c`
   - claims the build-program node
   - calls `AIBuild_ConstructionBegin`
   - spends AI credit against the chosen account
2. `AIBuild_ProcessFacilityConstruction-0050cbca.c`
   - selects an unassigned constructor
   - issues `Units_SOrderConstruct`
   - stores constructor-side AI state:
     - `cc_reserved_area`
     - `cc_construct_cost`
     - `cc_construct_type`
     - `cc_account`
3. `Units_SOrderConstruct-00517b24.c`
   - computes the world build position
   - writes that into the rig via `ConstructionRig::SetConstructionMatrix`
   - issues `GameObject::SetCommand(..., CMD_BUILD, ...)`

The intended failure-recovery path appears to be `AI_BuildingStalled-005084fc.c`.
That function:

- calls `AIBuild_ConstructionEnd`
- removes the reserved area
- refunds spent credit
- re-adds the constructor to the unassigned CC pool
- issues `Units_SOrderStop`
- clears the constructor `cc_*` tracking fields

However, `AI_UnitRemove-005083d9.c` does not do the same thing when an assigned
constructor dies while `cc_constructing != 0`.

That branch only:

- logs `"Removing assigned construction crew with bldg under construction"`
- calls `AIBuild_ReservedAreaRemove`

It does not:

- call `AIBuild_ConstructionEnd`
- refund spent credit
- stop the scripted order
- clear `cc_construct_type`, `cc_account`, `cc_construct_cost`, or
  `cc_constructing`
- requeue the constructor through the same cleanup path used by
  `AI_BuildingStalled`

## Why The Rebuilt Constructor Can Resume From Far Away

`AI_UnitAppeared-00507277.c` adds every newly appeared constructor back into the
unassigned constructor pool. `AI_UnitAdd-0050839c.c` also performs a generic
`AIBuild_ConstructionEnd` for the produced unit's prereq type before calling
`AI_UnitAppeared`.

Inference:

- the old constructor's active build-program/build-site state is not fully
  cleaned up on death
- the replacement constructor is reintroduced as an available construction crew
- the construction-program bookkeeping can now be in a partially stale state
  where the original world build target survives independently of the dead rig

That matches the observed symptom better than a simple pathing or placement
error: the issue is most likely stale build-program cleanup, not bad
distance-checking in the order assignment itself.

## Best Fix Direction

Best first fix target:

- patch the constructor-removal path equivalent to
  `AI_UnitRemove-005083d9.c`

Desired behavior when an assigned constructor dies:

- use the same cleanup semantics as `AI_BuildingStalled`
- end the outstanding construction claim
- refund/remove the reserved accounting consistently
- stop the outstanding scripted build order
- clear the constructor `cc_*` fields

## Redux 2.2.301 Mapping

Current Redux GOG best-effort corpus mapping from the March 23, 2026 live
OpenShim implementation pass:

- `AI_UnitRemove` -> `FUN_0068fc60`
- `AI_BuildingStalled` -> `FUN_0068fe40`
- `AI_SpentCreditRefund` -> `FUN_00690020`
- `AIBuild_ConstructionEnd` -> `FUN_006905d0`
- `AIBuild_UnassignedCCAdd` -> `FUN_00690770`
- `AIBuild_UnassignedCCRemove` -> `FUN_006907b0`
- `AIBuild_ReservedAreaRemove` -> `FUN_00690920`

Observed current-field offsets from those Redux functions:

- team: `unit + 0x10` as signed byte
- `cc_construct_type`: `unit + 0x30`
- `cc_construct_cost`: `unit + 0x34`
- `cc_constructing`: `unit + 0x38`
- `cc_reserved_area`: `unit + 0x3c`
- `cc_account`: `unit + 0x40`

`AI_BuildingStalled` still calls the stock stop-order helper at `0x00416280`,
but the current Redux corpus decompiles that site as a `RET` stub. In practice,
the meaningful recovery work in Redux is the construction-claim, refund, and
`cc_*` cleanup.

## OpenShim Status 2026-03-23

Implemented in [`src/bzr_hooks.cpp`](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/src/bzr_hooks.cpp):

- inline detour at `AI_UnitRemove` entry `0x0068FC60`
- interception only for AI constructor deaths where
  `cc_construct_type != 0 && cc_constructing != 0`
- cleanup now performs:
  - `AIBuild_ConstructionEnd`
  - `AIBuild_ReservedAreaRemove`
  - `AI_SpentCreditRefund`
  - best-effort stock stop-helper call
  - zeroing `cc_construct_type`, `cc_construct_cost`, `cc_constructing`,
    `cc_account`, and `cc_reserved_area`

Intentional difference from `AI_BuildingStalled`:

- OpenShim does not call `AIBuild_UnassignedCCAdd` on the death path, because a
  dead constructor should not be reintroduced into the unassigned-crew pool.

Runtime logging:

- install and event logs use the `[AICONSTRUCT]` tag
- the always-on success line is
  `Applied constructor death cleanup action=death_cleanup ...`
- trace mode adds budgeted `action=` / `reason=` lines:
  - `action=death_cleanup reason=applied` confirms the detour took ownership
  - `action=fallback` documents why stock `AI_UnitRemove` was left in place for
    that call, with reasons such as `team_not_ai`, `not_constructor`,
    `construct_type_zero`, or `constructing_zero`
- `OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD=1` enables extra trace lines
- `OPENSHIM_TRACE_CONSTRUCTOR_BUILD_CLEANUP=1` is accepted as a trace alias
- `OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD_BUDGET=<n>` adjusts trace volume
- `OPENSHIM_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX=1` disables the hook

## Key Legacy References

- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_UnitRemove-005083d9.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_BuildingStalled-005084fc.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AIBuild_BuildListWhatToMakeWith-0050c92c.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AIBuild_ProcessFacilityConstruction-0050cbca.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Units_SOrderConstruct-00517b24.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_UnitAppeared-00507277.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_UnitAdd-0050839c.c`
