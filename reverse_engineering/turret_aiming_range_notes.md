# Turret Aiming Range Notes

## Question

Feature request:

> Add a way to adjust turret aiming range. Currently hardcoded to 0.5 radians so they can't aim straight up at threats for example. This seems to apply to both `turrettank` class and `turret` class.

Primary suspected AI label was `TurretTankFriend`, but the actual limit is not in the AI process layer.

## Conclusion

This is a native class-simulation issue in `TurretCraft` and `TurretTank`, not an EXU-side Lua/content issue.

`UpdateWeaponAim` is not where the clamp happens. The hard limit is upstream: both turret classes derive their applied pitch angle from vehicle control pitch multiplied by a hardcoded `0.5`.

## Legacy exact-match proof

Exact legacy match used:

- EXE: `C:\Program Files (x86)\Battlezone\bzone.exe`
- PDB: `C:\Program Files (x86)\Battlezone\bzint.pdb`
- Corpus: `reverse_engineering\workshop\global_decompile\legacy_bz1_exact`

Full legacy export corpus now also verified:

- Corpus: `reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full`

Important legacy symbols:

- `TurretCraft::UpdateWeaponAim(float)`
- `TurretCraft::Simulate(float)`
- `TurretTank::UpdateWeaponAim(float)`
- `TurretTank::Simulate(float)`

Legacy class/layout evidence:

- `Craft::pitchAng` at `+0x25c`
- `VEHICLE::control.pitch` at `+0xc8`

Observed in legacy disassembly:

- `TurretCraft::Simulate(float)` stores `vhcl->pitch * 0.5f` into `this->pitchAng`
- `TurretTank::Simulate(float)` stores `vhcl->pitch * 0.5f` into `this->pitchAng`

Observed in legacy `UpdateWeaponAim(float)`:

- It consumes `pitchAng`
- It does not apply the `0.5f` limit itself

Confirmed directly in the full-export ghidrecomp output:

- `ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\Simulate-004b445b.c`
  - shows `this->pitchAng = vhcl->control.pitch * 0.5f` equivalent at the end of `TurretCraft::Simulate`
- `ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\Simulate-004b5814.c`
  - shows `this->pitchAng = vhcl->control.pitch * 0.5f` equivalent at the end of `TurretTank::Simulate`
- `ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\UpdateWeaponAim-004b410b.c`
  - builds the pitch matrix from stored `pitchAng`
- `ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\UpdateWeaponAim-004b4da6.c`
  - also builds the pitch matrix from stored `pitchAng`, or falls back to `HoverCraft::UpdateWeaponAim`

That full-export corpus does not reveal a second hidden clamp site. It reinforces that the simulation-site multiplier is the correct hook target.

## Current Redux mapping

Redux binary used:

- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- Image base `0x00400000`

Because the shipped Redux PDB is not an exact GUID match, symbol names from that PDB are advisory only. The live code below is based on the current binary plus the legacy exact-match lineage.

### Likely current function mapping

- `FUN_005f0d90` is the current `TurretCraft::Simulate(float)` equivalent
- `FUN_005f0930` is the current `TurretCraft::UpdateWeaponAim(float)` equivalent
- `FUN_005f2a40` is the current `TurretTank::Simulate(float)` equivalent
- `FUN_005f27b0` is the current `TurretTank::UpdateWeaponAim(float)` equivalent

### Current consumer side

`UpdateWeaponAim` still consumes the derived pitch field and builds a pitch matrix from it:

- `FUN_005f0930`
- `FUN_005f27b0`

These functions both use the field at `this + 0x280` as the applied pitch angle.

### Current hardcoded multiplier sites

TurretCraft path:

- Function: `FUN_005f0d90`
- Live instructions:
  - `0x005f1838  movss  0x008a2584, %xmm0`
  - `0x005f1840  mulss  0xc8(%edx), %xmm0`
  - `0x005f184e  movss  %xmm0, 0x280(%eax)`

TurretTank path:

- Function: `FUN_005f2a40`
- Live instructions:
  - `0x005f561a  movss  0x008a2584, %xmm0`
  - `0x005f5622  mulss  0xc8(%eax), %xmm0`
  - `0x005f5630  movss  %xmm0, 0x280(%ecx)`

Current decomp also shows the same logic directly:

- `*(float *)(... + 0x280) = *(float *)(*(int *)(... + 0x230) + 200) * 0.5;`

This is the Redux equivalent of the legacy:

- `this->pitchAng = this->vhcl->control.pitch * 0.5f`

## What this means

The effective turret/barrel pitch is being halved before visual aim update runs.

If the underlying vehicle control pitch can reach about 1.0 radian, the turret/barrel only receives about 0.5 radian. That matches the reported behavior.

## Recommended shim strategy

This belongs in Shim.

Best native hook options:

1. Patch both simulation sites so the multiplier is configurable instead of fixed at `0.5f`.
2. Keep a default of `0.5f` for compatibility.
3. Add a per-class or per-instance override source if desired.

Reasonable implementation options:

- Simple global patch:
  - Replace the shared constant use with a shim-owned float, applied at both sites.
- Per-class patch:
  - In the hook, inspect the object/class and apply a class-specific multiplier for `TurretCraft` vs `TurretTank`.
- Content-facing extension:
  - After the native fix exists, EXU could optionally expose scripting or ODF control over the multiplier.

## Recommended first implementation

Implement a shim-owned configurable multiplier with two hook sites:

- `0x005f1840` / store at `0x005f184e`
- `0x005f5622` / store at `0x005f5630`

That is the narrowest patch with the clearest semantics and least risk.

## Implementation status

This is now implemented in Shim by replacing the hardcoded scalar load at both sites with a shim-owned float:

- `TurretCraft` hook at `0x005f1838`
- `TurretTank` hook at `0x005f561a`

Current behavior:

- Default multiplier: `0.95f`
- Environment overrides:
  - `OPENSHIM_TURRET_AIM_PITCH_MULTIPLIER`
  - `OPENSHIM_TURRET_PITCH_MULTIPLIER`

Reason for the `0.95f` default:

- It removes the obvious vanilla restriction.
- It stays slightly conservative relative to `1.0f`, which can look unnaturally vertical on some assets.

## Risk notes

- Best-effort Redux class layouts from the shipped PDB should not be trusted for exact offsets.
- The live instruction sites above are the exact evidence; the symbolic names around them are inferred from legacy exact-match lineage and vtable clustering.
- If a future build changes codegen, the two patch sites will need to be re-located by pattern, not by trusting the shipped PDB.
