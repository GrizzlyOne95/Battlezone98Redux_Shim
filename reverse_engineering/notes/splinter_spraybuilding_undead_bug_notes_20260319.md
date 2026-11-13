# Splinter Undead Bug Notes

Date: 2026-03-19

Issue:
- deployed splinter objects (`classLabel = "spraybomb"`) can be damaged below `0` health and still remain active until they finish firing their remaining payload shots

## Legacy 1.5 Findings

The exact-match legacy decompile shows that `spraybomb` is split across two native classes:

- `SprayBomb`
  - thrown/bouncing ordnance shell
  - legacy exact PDB/decomp:
    - `?Hit@SprayBomb@@UAEXPAVGameObject@@ABUVECTOR_3D@@@Z`
    - VA `0x0053ABBF`
- `SprayBuilding`
  - deployed stationary firing object that actually emits the splinter payload
  - legacy exact PDB/decomp:
    - `?Simulate@SprayBuilding@@UAEXM@Z`
    - VA `0x0053A779`

The important chain is:

1. `SprayBomb::Hit` converts the slow-moving bomb into a spawned `SprayBuilding`.
2. `SprayBuilding::Simulate` runs the spin / bob / shot-timer loop and keeps spawning payload ordnance while:
   - `shotTimer > 0`
   - enough ammo remains
3. `SprayBuilding::Simulate` never checks destroyed state, current health, or the standard building removal flags before continuing that loop.

Meanwhile the inherited building damage path still marks the object as dead:

- `Building::DamageAlloc`
  - legacy exact VA `0x00482E4A`
  - when health drops below `0`, it calls `obj_set_flag(obj, 0x1000200)`
- `Building::Simulate`
  - legacy exact VA `0x0048342D`
  - standard behavior is:
    - if `flags & 0x1000000`: call virtual `+0x14` and return
    - else if `flags & 0x200`: call virtual `+0x10` and return

So the bug is structural:

- `SprayBuilding` overrides `Building::Simulate`
- but does not preserve the base-class dead/remove handling at the top
- therefore a dead deployed splinter keeps running its custom fire loop until ammo depletion triggers its own self-removal path

This appears to be stock legacy behavior, not something introduced by Redux.

## Redux Mapping

The current Redux GOG advisory PDB still exposes the same symbols:

- `?Simulate@SprayBuilding@@UAEXM@Z`
  - RVA `0x001242F0`
  - VA `0x005242F0`
- `?DamageAlloc@Building@@UAE_NPAUDAMAGE@@PAUVECTOR_3D@@@Z`
  - RVA `0x000349A0`
  - VA `0x004349A0`
- `?Explode@Building@@UAEXXZ`
  - RVA `0x00034D20`
  - VA `0x00434D20`
- `?Simulate@Building@@UAEXM@Z`
  - RVA `0x00035490`
  - VA `0x00435490`

Per the current workspace notes, Steam has matched GOG byte-for-byte after settle for the builds checked so far, so this is a strong current patch target. Still verify the live entry bytes before shipping a detour.

## Patch Direction

Most likely safe fix in OpenShim:

- detour `SprayBuilding::Simulate`
- preserve stock behavior for normal live splinters
- but before entering the stock spray fire loop, reproduce the missing base-class destroyed handling:
  - if object flags contain `0x1000000`, trigger the same virtual explode path and return
  - else if object flags contain `0x200`, trigger the same virtual cleanup path and return

Equivalent higher-level version:

- call the missing `Building::Simulate` destruction gate first
- only continue into stock `SprayBuilding::Simulate` if the object is still alive and not marked for removal

## Practical Notes

- This should be implemented as a targeted native shim fix, not an ODF workaround.
- The deployed object is the problem, not the thrown `SprayBomb::Hit` half.
- A direct entry detour on `SprayBuilding::Simulate` is the cleanest first attempt.
- Because the Redux corpus is best-effort rather than exact-match, use expected-bytes validation or a small signature around the current entry before enabling the hook by default.

## Implementation (OpenShim, 2026-07-06)

Implemented in `src/patches/bzr_hooks.cpp` as a vtable-slot swap (same mechanism
as the ShieldTower team-filter fix), NOT an inline entry detour.

**Address re-derivation (the advisory-PDB VA was stale on the live exe):** the
2026-03-19 advisory VA `0x005242F0` for `SprayBuilding::Simulate` lands
mid-instruction on the current GOG build (Jan 29 2026 exe) — it is inside
`mov [edx+0x270], eax` at `0x005242EE`. The known-good constructor hook
(`AI_UnitRemove` @ `0x0068FC60`, bytes `55 8B EC 51 83 3D 08 0F 93 00 00`)
still matches this exe byte-for-byte, so the exe is the mapped build; only the
spraybomb VA had drifted. Re-derived via RTTI:

- `.?AVSprayBuilding@@` TypeDescriptor @ `0x00901E3C`
- complete-object COL (offset==0) @ `0x008ABDDC`, referenced by vtable-4 ptr @ `0x008881E8`
- **SprayBuilding primary vtable = `0x008881EC`** (24 slots; second sub-object COL at `0x0088824C`)
- diff vs **Building primary vtable `0x00876630`** (RTTI: TD `0x008FF9C8`, COL `0x008A6210`): SprayBuilding overrides exactly two slots — slot 0 (deleting dtor, `0x005DA680`) and **slot 15 = SprayBuilding::Simulate = `0x005DA6E0`** (Building's is `0x0047FCB0` = `Building::Simulate`).
- **Simulate vtable slot address = `0x00888228`** (`0x008881EC + 15*4`).
- Entry prologue @ `0x005DA6E0`: `55 8B EC 81 EC E8 02 00 00 …` (validated at install).

**Fix logic:** hook the vtable slot with a `__fastcall(this, edx, float)` thunk.
Read the destroyed/remove flags at `[[this+0xF4]+0x14]` (this is exactly what
stock `Building::Simulate @ 0x0047FCB0` reads: `mov edx,[this+0xF4];
mov eax,[edx+0x14]; and eax,0x1000000` … `and edx,0x200`). If
`flags & 0x01000200` (destroyed | marked-for-remove) is set, route the frame
through stock `Building::Simulate` (which dispatches the base explode/remove
virtual on the `this+0x18` sub-object and returns) instead of the spray payload
fire loop; otherwise call the original `SprayBuilding::Simulate`. No recursion:
`Building::Simulate` dispatches the remove/explode virtuals (second-base vtable
slots +0x10/+0x14), never Simulate.

Cross-validation bonus: the ShieldTower fix already resolves
`kGogBuildingSimulateAddr = 0x0047FCB0`, independently matching the RTTI diff.

Safety: install is gated by `ExpectedBytesMatchAt` on the prologue plus a vtable
slot value check (must be the hook or `0x005DA6E0`), so a future build drift
fails safe (fix disables itself, stock behavior preserved). All flag reads are
SEH-guarded and fall back to stock on fault. Toggle off with
`OPENSHIM_DISABLE_SPLINTER_UNDEAD_FIX=1`; trace with
`OPENSHIM_TRACE_SPLINTER_UNDEAD=1` (`[SPLINTER]` tag in `winmm_shim.log`,
budgeted via `OPENSHIM_TRACE_SPLINTER_UNDEAD_BUDGET`). Builds clean
Release|Win32. Runtime in-game repro validation still pending.
