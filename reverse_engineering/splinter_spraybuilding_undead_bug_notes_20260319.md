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
