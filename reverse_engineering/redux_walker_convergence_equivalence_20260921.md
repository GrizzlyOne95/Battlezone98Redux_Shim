# Redux Walker convergence equivalence audit — 2026-09-21

## Scope

Work Order 1 only: compare the shipped GOG Redux `FUN_0060F320` against Battlezone 1.5
`Walker::UpdateWeaponAim @ 0x004B865D` and determine whether Redux changed the
target-convergence algorithm.

No production code is changed by this work order.

## Sources

- Redux GOG v2.2.301 best-effort decompile:
  `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_0060f320-0060f320.c`
- BZ1 1.5 imported-PDB decompile:
  `BZ1_Source/1.5/functions/004b/004b865d_Walker_UpdateWeaponAim.c`
- Redux helper bodies:
  - `GameObject::GetTarget @ 0x00462610`
  - `GameObject::GetObj @ 0x004DA060`
  - `obj_rel_parent_matrix @ 0x0062E070`
  - `Matrix_Inverse @ 0x008203F0`
  - `Build_Pitch_Matrix @ 0x0081EC40`
  - `Build_Directinal_Matrix @ 0x0081FA10`
  - `Matrix_Multiply @ 0x0081FE60`
  - `Dist3D @ 0x004976F0`
  - weapon transform refresh `0x00681A00`
- Existing Redux layout proof:
  `GameObject::targetHandle = +0x21C`, from SetTarget/GetTarget.
- Existing interface/vtable proof:
  DistributedObject/GameObject vtable slot 3 (`+0x0C`) is `GetPosition()`.

## Conclusion

**Redux `0x0060F320` preserves the BZ1 1.5 Walker convergence algorithm.**

There is no evidence of a changed convergence equation. The same five-slot loop,
baseline pitch/hardpoint transform construction, target-distance calculation, X/Z
hardpoint correction, zero vertical correction, directional-matrix construction,
and correction-matrix composition are present in the same order.

Redux differences are implementation/layout details:

1. shifted Redux GameObject field layout, notably `targetHandle +0x21C` rather
   than BZ1 1.5 `+0x214`;
2. compiler/decompiler prototype loss around thiscall helpers;
3. helper calls used to copy/restore MAT_3D translation rather than the cleaner
   field assignments visible in the 1.5 decompile;
4. an explicit Redux object/scene transform refresh at `0x00681A00` after each
   weapon update.

These do not alter the convergence geometry.

## Operation-by-operation equivalence

| Stage | BZ1 1.5 | Redux GOG | Result |
|---|---|---|---|
| Baseline pitch matrix | `Build_Pitch_Matrix(..., -craftPitch)` | `FUN_0081EC40(..., [this+0x280] ^ signbit)` | Equivalent |
| Weapon iteration | slots `0..4` | slots `0..4` | Exact |
| Weapon lookup | `Carrier::GetWeapon` | `0x00417F60` | Equivalent |
| Hardpoint-relative matrix | `obj_rel_parent_matrix(weapon->hard, craft->obj)` | `0x0062E070(weapon+0x14, this+0xF4)` | Exact semantics |
| Relative matrix inverse | `Matrix_Inverse` | `0x008203F0` | Exact |
| Preserve weapon local translation | save/restore `weapon->obj->transform.posit_*` | `0x00447F60` + `0x0044B7D0` around the matrix write | Equivalent |
| Baseline weapon orientation | relative inverse × pitch | same `0x0081FE60` composition | Equivalent |
| Target lookup | `GameObject::GetObj(craft->targetHandle)` | `GameObject::GetTarget @ 0x00462610` → `GetObj @ 0x004DA060` | Equivalent, Redux field shifted |
| Position source | target and shooter virtual `GetPosition()` | both dispatch through vtable `+0x0C` | Exact semantics |
| Range | `Dist3D(shooterPos,targetPos)` | `0x004976F0` | Exact |
| Correction X | `-hardpointRelative.posit_x` | `-(float)local_b4` | Exact |
| Correction Y | `0` | `0.0` | Exact |
| Correction Z | `range - hardpointRelative.posit_z` | `local_2f0 - (float)local_a4` | Exact |
| Correction matrix | `Build_Directinal_Matrix(origin=0, correction)` | `0x0081FA10(origin=0, local_38)` | Exact |
| Apply correction | correction × current weapon transform | `0x0081FE60(local_25c, weaponObj+0x20)` | Exact matrix order |
| Scene/object refresh | not explicit in 1.5 body | `0x00681A00(weaponObj, weaponObj+0x20)` | Redux integration detail |

## Recovering `local_b4` and `local_a4`

The Redux decompile initially makes these look uninitialized. They are not.

The stack object beginning at `local_dc` is the copied 64-byte MAT_3D returned by
`obj_rel_parent_matrix`. The decompiler split its translation doubles into
separate locals. In that MAT_3D:

- `local_b4` is the relative matrix X translation;
- the middle Y double is unused by convergence;
- `local_a4` is the relative matrix Z translation.

That is why Redux constructs:

```text
correction.x = -hardpointRelativeX
correction.y = 0
correction.z = targetDistance - hardpointRelativeZ
```

This exactly matches BZ1 1.5.

## Target lookup decompiler trap

Redux decompiles this as:

```c
local_2ec = FUN_00462610();
```

which can look like a no-argument global query. The helper is already independently
proven as `GameObject::GetTarget`:

```text
[this + 0x21C] -> handle -> GameObject::GetObj(0x004DA060)
```

The missing `this` argument is a decompiler/prototype-recovery artifact from the
x86 thiscall register convention, not a behavior difference.

## Exact Walker geometry

The convergence stage is not "point each barrel at the target's world-space
center." The target supplies a scalar distance.

For a hardpoint whose relative craft-space position is `(hx, hy, hz)`, and a
target at center-to-center distance `d`, Walker constructs:

```text
v = (-hx, 0, d - hz)
```

then builds a directional matrix from `v` and composes that correction with the
already-established stock weapon aim.

Consequences:

- lateral hardpoint separation is corrected;
- hardpoint forward offset is included;
- hardpoint Y is deliberately ignored by the convergence correction;
- target world bearing/elevation is **not** used by this convergence stage;
- the stock aim/pitch stage remains authoritative.

This is the source of the characteristic Walker convergence feel.

## Important finding for OpenShim Work Order 2

The initial `SolveWalkerStyleRange()` implementation proposed in OpenShim PR #240
captures the intended range-based feel, but it is **not yet an exact translation
of the proven Redux algorithm**.

It currently derives lateral/forward offsets by projecting:

```text
worldMuzzle - shooterPosition
```

onto the current world barrel basis.

Stock Walker instead uses the X and Z translation directly from:

```text
obj_rel_parent_matrix(weapon->hard, craft->obj)
```

before the weapon object's own local transform is composed.

Those quantities can coincide in simple cases, but they are not the same contract.
A weapon object's local muzzle/transform offset, nested hardpoint hierarchy, or
nontrivial stock aim transform can make them differ.

Work Order 2 should therefore use the exact hardpoint-relative X/Z values (or an
independently proven equivalent) and reproduce the stock correction matrix order,
rather than treating the current projected-muzzle calculation as final.

## Confidence

| Claim | Confidence |
|---|---|
| Redux `0x0060F320` is the Walker-style target-convergence routine used by current OpenShim | High |
| Five-slot loop and baseline hardpoint/pitch setup match BZ1 | High |
| Target comes from `GameObject::GetTarget` / `targetHandle +0x21C` | High |
| Range is center-to-center `Dist3D(GetPosition(), GetPosition())` | High |
| Correction is exactly `(-hardpointX, 0, range-hardpointZ)` | High |
| Correction matrix is composed before the current weapon transform | High |
| Redux added an explicit transform refresh without changing convergence geometry | High |
| PR #240 projected-muzzle offsets are always equivalent to Walker hardpoint-relative X/Z | **False / not supported** |

## Work Order 1 disposition

**Complete.**

Work Order 2 has a concrete correction target: make OpenShim's pure Walker-style
solver consume the exact hardpoint-relative X/Z contract proven above, then pin
that behavior with deterministic tests before any further convergence refactor.
