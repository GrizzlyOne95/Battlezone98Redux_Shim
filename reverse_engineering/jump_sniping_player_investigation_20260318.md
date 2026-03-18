## Item 23: Player Jump Sniping / Landing Regression

Date: 2026-03-18

Scope:
- player-controlled `Person`
- legacy 1.5 exact decompile
- Redux stock pilot skeleton assets
- local Blender toolkit / porter metadata

## Main Finding

The old crouch-on-sniper-select behavior is owned by legacy `Person::Simulate`, not by `SniperInterface` and not by the AI `PersonProcess` task layer.

That matters because the reported regression:

- hold jump with sniper selected
- touch ground
- 1.5 would go back into the crouch/sniping pose
- Redux stays effectively in the jump/standing path

fits a missing transition in the Redux player `Person` animation-state path much better than a HUD or overlay issue.

## Legacy Player Animation State Machine

Legacy exact function:

- `Person::Simulate`
- [Simulate-004a56ba.c](c:\Users\istuart\Documents\GIT\Battlezone98Redux_Shim\reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full\ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\Simulate-004a56ba.c)

Important observations from the legacy body:

- It explicitly scans selected weapons and sets a local flag when the selected weapon signature is `0x534E4950` (`SNIP`).
- That sniper-selected flag directly drives the person animation state machine.
- The relevant state block is around lines 445-567 in the decomp.

Key behavior:

- Standing state `0`:
  - if sniper selected, choose animation index `0` and advance to state `1`
- Transition state `1`:
  - keep animation `0` until it finishes
  - then choose animation index `3` and advance to state `2`
- Sniping/crouched state `2`:
  - if still sniper-selected, remain on animation index `3`
  - if not sniper-selected, choose animation index `1` and advance to state `3`
- Uncrouch transition state `3`:
  - keep animation `1` until it finishes
  - then return to state `0` and standing animation index `2`

This is the clearest exact-legacy proof that crouch/sniping is a player-side person animation state machine, not just a scope overlay.

## Animation Index Meaning

The local Blender toolkit has a person animation reference and exporter mapping:

- [__init__.py](c:\Users\istuart\Documents\GIT\BZ98RBlenderToolKit\bz98tools\__init__.py)
- [bzportmodels.py](c:\Users\istuart\Documents\GIT\BZ98RBlenderToolKit\bz98tools\bzrmodelporter\bzportmodels.py)

Useful mapping:

- index `0` = `stand2Kneel`
- index `1` = `kneel2stand`
- index `2` = standing idle
- index `3` = crouched/sniping idle path
- index `11` = `jump`
- index `10` = `landParachute`

The toolkit’s person popup says:

- `0`: Stand -> Snipe
- `1`: Snipe -> Stand
- `2`: Standing / Idle
- `3`: Sniping / Idle
- `10`: `landParachute`
- `11`: `Jump`

The porter currently maps index `3` to the stock clip name `fireRecoilSniper`, which is notable because the shipped skeletons do not appear to contain a separately named `crouch_idle` clip.

## Stock Asset Evidence

Stock pilot skeletons are present at:

- [aspilo.skeleton](c:\Users\istuart\Documents\Battlezone 98 Redux\BZ_ASSETS\common\models\aspilo.skeleton)
- [bspilo.skeleton](c:\Users\istuart\Documents\Battlezone 98 Redux\BZ_ASSETS\common\models\bspilo.skeleton)
- [sspilo.skeleton](c:\Users\istuart\Documents\Battlezone 98 Redux\BZ_ASSETS\common\models\sspilo.skeleton)
- [cspilo.skeleton](c:\Users\istuart\Documents\Battlezone 98 Redux\BZ_ASSETS\common\models\TRO\cspilo.skeleton)

Binary string hits in those skeletons confirm the clips exist in stock assets:

- `fireRecoilSniper`
- `idle`
- `idleParachute`
- `jump`
- `kneel2stand`
- `landParachute`
- `runBackward`
- `runForward`
- `runLeft`
- `runRight`
- `stand2Kneel`

So item 23 is not blocked by missing stock animation assets.

## Ground / Landing Signals In Legacy

The same legacy `Person::Simulate` function also owns important ground-contact flags:

- it reads and writes bits in the per-person flag word at `+0x10c`
- it clears bit `0x80` on one ground-contact path around lines 1265-1279
- it clears bit `0x4` on another landing/contact path around lines 1309-1315
- it sets bit `0x80` again later around lines 1441-1443

That is strong evidence that player jump/landing and crouch/sniping are both coordinated inside the same simulate function, even though this pass did not yet fully recover the exact legacy caller that chooses animation indices `10` and `11`.

## Best Current Hypothesis

The most likely Redux regression is:

- Redux still has the stock skeletal clips
- Redux likely still enters jump / landing movement correctly enough to animate or move
- but Redux no longer re-enters the legacy sniper-selected crouch state machine on touchdown for the player `Person`

In practical terms, the missing behavior is probably one of:

1. the landing path no longer clears the same grounded/landing flags that legacy `Person::Simulate` expected
2. the player `Person` animation-state variable no longer transitions back through `0 -> 1 -> 2`
3. the skeletal animation bridge no longer starts the `stand2Kneel` / crouched anim sequence after landing
4. Redux’s scope implementation replaced the old fixed crouch-tied scope behavior with an always-on attached/geometry scope path and lost the old crouch trigger

The toolkit explicitly describes Redux-style attached/geometry scopes as "always on", while the classic fixed scope turns on and off with crouch/uncrouch. That lines up with the symptom.

## Best First Redux Targets

Given the evidence, the best first native targets are:

- `Person::Simulate`
- `Person::PostSimulate`
- the Redux `Person.obj` path in `fun3d/person.cpp`
- the skeletal bridge in code paths touching `animobj.h`, `animsprite.h`, and `ogre76handler.h`

The best first question to answer in Redux is:

- when the player `Person` lands with a sniper selected, does Redux ever request animation index `0` / `stand2Kneel` again?

If not, that is probably the exact regression.

## Things This Pass Ruled Out

- not primarily `SniperInterface`
- not primarily `PersonAttack` / `SoldierAttack`
- not missing stock pilot animation clips

## Next Useful Probe

If this gets instrumented in OpenShim, the highest-signal probe would be:

- hook the Redux player `Person` animation start path
- log object ODF, selected sniper yes/no, airborne/grounded flag transitions, and requested animation index
- verify whether touchdown while sniper-selected ever requests:
  - `10` -> landing
  - then `0` -> `stand2Kneel`
  - then `3` -> crouched/sniping idle

## Current Redux GOG PDB Confirmation

The live GOG install at:

- [battlezone98redux.exe](c:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe)
- [battlezone98redux.pdb](c:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb)

confirms that the current Redux build still has the exact `Person` and `AnimObj` symbols needed to probe this cleanly.

Useful current GOG RVAs from the structured PDB export:

- `Person::Simulate` = `0x000F43E0`
- `Person::PostSimulate` = `0x000F6300`
- `Person::UpdateWeaponAim` = `0x00077290`
- `AnimObj_Start` = `0x001617A0`
- `AnimObj_Stop` = `0x001618E0`
- `GetPlayerHandle` = `0x00114610`
- `GameObject::GetObj` = `0x0006B160`
- `GameObjectHandle::GetObj` = `0x00023F70`

With the normal `0x00400000` image base, the corresponding current GOG VAs are:

- `Person::Simulate` = `0x004F43E0`
- `Person::PostSimulate` = `0x004F6300`
- `Person::UpdateWeaponAim` = `0x00477290`
- `AnimObj_Start` = `0x005617A0`
- `AnimObj_Stop` = `0x005618E0`
- `GetPlayerHandle` = `0x00514610`
- `GameObject::GetObj` = `0x0046B160`
- `GameObjectHandle::GetObj` = `0x00423F70`

This materially tightens item 23 because it means there is no need to guess at the current Redux function locations.

## Current Redux Layout Details That Matter

The current GOG PDB class layout also exposes the exact runtime fields needed for a probe.

Current `Person` layout highlights:

- `sizeof(Person)` = `664`
- `Person + 0x0E8` = `_OBJ76* obj`
- `Person + 0x198` = `Carrier* carrier`
- `Person + 0x210` = `long weaponMask`
- `Person + 0x288` = `long curAnim`
- `Person + 0x28C` = `int animHandle`
- `Person + 0x290` = `bool cycleState`

Current `Carrier` layout highlights:

- `Carrier + 0x00` = `GameObject* owner`
- `Carrier + 0x18` = `Weapon* weapon[5]`
- `Carrier + 0x30` = `unsigned long selected`
- `Carrier + 0x38` = `int special`

Current `Weapon` / `WeaponClass` layout highlights:

- `Weapon + 0x08` = `WeaponClass* weaponClass`
- `WeaponClass + 0x0C` = `unsigned long sig`
- `WeaponClass + 0x20` = `char odf[16]`

That gives a direct way to answer "sniper selected?" on the live player object:

1. call `GetPlayerHandle()`
2. resolve the object with `GameObject::GetObj(handle)`
3. cast to `Person*`
4. read `person->carrier`
5. inspect `carrier->selected`
6. for any selected slot, inspect `carrier->weapon[i]->weaponClass->sig`
7. compare the signature against legacy sniper signature `0x534E4950` (`SNIP`)

So a clean probe does not need to infer selection from input state or HUD state.

## What The Current Build Confirms

The current Redux GOG PDB strongly reinforces the earlier conclusion:

- the active player animation owner is still `Person::Simulate`, not `SniperInterface`
- the old person task classes still exist, but they remain a different layer:
  - `PersonGlide::DoState`
  - `PersonStraight::DoState`
  - `PersonAttack::DoState`
  - `PersonRetreat::DoStateProlog`
- Redux still exposes the exact `AnimObj_Start` bridge that should receive:
  - `jump`
  - `landParachute`
  - `stand2Kneel`
  - crouched/sniping idle

So the best current working theory is still:

- touchdown with sniper selected is not re-driving the player `Person::Simulate` crouch/sniper transition in Redux
- or `Person::Simulate` does request it, but the request is getting lost before or inside `AnimObj_Start`

## Best Probe Recipe Now

Given the exact current GOG symbols, the cleanest high-signal probe path is now:

1. hook `Person::Simulate` at `0x004F43E0`
2. resolve the local player via `GetPlayerHandle()` + `GameObject::GetObj()`
3. when `this == playerPerson`, log:
   - `curAnim`
   - `animHandle`
   - `carrier->selected`
   - selected weapon sig / ODF
4. optionally hook `AnimObj_Start` at `0x005617A0`
5. when `obj == person->obj`, log requested animation index

That should answer the core question very quickly:

- after landing with sniper still selected, does Redux request `0` / `stand2Kneel` at all?

If the answer is "no", item 23 is almost certainly a missing player `Person::Simulate` state transition in Redux rather than an asset problem.

## OpenShim Probe Added

There is now a temporary GOG-only OpenShim probe in [src/bzr_hooks.cpp](c:\Users\istuart\Documents\GIT\Battlezone98Redux_Shim\src\bzr_hooks.cpp) gated behind:

- `OPENSHIM_TRACE_JUMP_SNIPING=1`

What it does:

- installs an inline detour on the player `Person::Simulate` path
- resolves the local player with `GetPlayerHandle()` + `GameObject::GetObj()`
- logs only when the local player `Person` changes in a jump-sniping-relevant way:
  - `Craft::state`
  - `curAnim`
  - `animHandle`
  - vertical velocity band (`up` / `flat` / `down`)
  - selected weapon mask / slot
  - selected weapon signature / ODF
  - sniper selected yes/no

Important correction from live disassembly:

- the safe callable entry for current GOG `Person::Simulate` is `0x004F4370`
- the earlier `0x004F43E0` number still appears in the PDB-derived range dump, but it lands inside the function body rather than at the actual prologue

So the current runtime probe is intentionally using `0x004F4370`.

Steam follow-up:

- the probe no longer hard-disables on Steam
- it now installs when the settled bytes at `0x004F4370` match the expected prologue
- it retries:
  - during initial hook resolution
  - once again after the patcher’s Steam settle wait
  - later from the chunk-effect runtime hook if Steam finishes settling even later
