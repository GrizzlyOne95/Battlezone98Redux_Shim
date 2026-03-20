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

## Key Legacy References

- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_UnitRemove-005083d9.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_BuildingStalled-005084fc.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AIBuild_BuildListWhatToMakeWith-0050c92c.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AIBuild_ProcessFacilityConstruction-0050cbca.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/Units_SOrderConstruct-00517b24.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_UnitAppeared-00507277.c`
- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps/AI_UnitAdd-0050839c.c`
