## Howitzer / Minelayer Weapon Mask RE Notes

Date: 2026-03-16

Goal: determine why `Howitzer` and `Minelayer` classlabel units appear to use
weapon mask `00001` regardless of Lua or ODF configuration, and identify the
correct native patch layer and likely hook sites.

### Current Status

Best patch home: Shim.

An experimental GOG-side behavior patch is now checked in.

The legacy exact-match corpus now proves the root cause semantically:

- artillery AI ignores `weaponMask` and uses the first non-null carrier weapon
- minelayer AI hardcodes slot `0` and selected mask `1` in the lay-mines task

Current implementation shape:

- a carrier-bias helper reorders `Carrier::weapon[0]` toward the decoded
  `weaponMask` target for `Howitzer` and `Minelayer`
- the existing artillery AI hook now applies that bias before the native helper
  continues
- exact decoded and raw `weaponMask` getter hooks also apply the bias
- the existing hovercraft flame hook applies the same bias for hovercraft-side
  minelayer refreshes

This is intended to make the stock native "first slot" behavior resolve to the
desired weapon without rewriting the full AI state machines.

Current limitation:

- this is build-validated only so far
- it is not yet gameplay-validated in a live Redux session
- Steam is still unimplemented for this feature

### Repos / Inputs Used

- `C:\Users\istuart\Documents\GIT\ExtraUtilities-G1\FeaturesToLookInto.txt`
- `C:\Users\istuart\Documents\GIT\Battlezone98Redux_CampaignReimagined-1\_Source\ODF\svartl.odf`
- `C:\Users\istuart\Documents\GIT\Battlezone98Redux_CampaignReimagined-1\_Source\ODF\svmine.odf`
- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb`
- `C:\Users\istuart\Documents\GIT\Battlezone98Redux_Shim\reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full`
- local `llvm-pdbutil`, `llvm-objdump`, `dumpbin`, `pyghidra`

### High-Confidence Findings

#### Legacy BZ1 exact-match corpus

The legacy exact corpus is the cleanest semantic source currently available for
this feature family, even though it is not the Redux executable we patch:

- corpus root:
  `C:\Users\istuart\Documents\GIT\Battlezone98Redux_Shim\reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full`
- source tree roots in the PDB:
  `c:\Users\Ken\Documents\Projects\BZ1\source\Internal\...`
- confirmed legacy source modules:
  - `ArtilleryProcess.obj`
  - `MineLayerProcess.obj`
  - `Howitzer.obj`
  - `MineLayer.obj`
  - `TurretTank.obj`
  - `ActionMode.obj`
  - `GameObject.obj`

Important exact legacy function exports:

- `ArtilleryProcess::DoAttack()` at RVA `0x0000C498`, size `1966`
- `MineLayerProcess::DoUState1()` at RVA `0x0001D04C`, size `65`
- `MineLayerProcess::InitUState1()` at RVA `0x0001D406`
- `MineLayerProcess::ChangesState()` at RVA `0x0001CFD5`
- `Howitzer::GetCommand(GameObject*)` at RVA `0x0009F64D`, size `262`
- `Howitzer::UpdateModeList()` at RVA `0x0009F753`, size `427`
- `Minelayer::SetActiveMode(int)` at RVA `0x0009FA41`, size `24`
- `TurretTank::SetActiveMode(int)` at RVA `0x000B4C07`, size `24`
- `GameObject::SetWeaponMask(long)` at RVA `0x0005E596`, size `13`
- global `SetWeaponMask(int me, long mask)` at RVA `0x0005F862`, size `25`

This matters for the Redux bug because it confirms the legacy engine already
had:

- explicit `ArtilleryFriend` and `MineLayerFriend` runtime classes
- tiny per-class `SetActiveMode` wrappers for `Minelayer` and `TurretTank`
- both object-member and global weapon-mask writer entry points

That is strong evidence that the hard-forced slot behavior is part of an old
native command or AI path inherited from legacy BZ code, not a Lua-era Redux
policy artifact.

Current limitation:

- the exact corpus now has usable `ghidrecomp` C output, so the legacy
  conclusions below are based on exact decompiled bodies rather than just
  symbol exports
- root cause of missing `ghidrecomp` C output is now known:
  `ghidrecomp` crashed after Ghidra finished analysis with
  `UnboundLocalError: cannot access local variable 'symbol_path'` in
  `ghidrecomp.utility.set_pdb`

#### Exact legacy root cause

The following legacy bodies are the key proof points.

`GameObject::SetWeaponMask(long)` and global `SetWeaponMask(int,long)` are both
plain raw writes to the object field. They do not contain any class-specific
artillery or minelayer behavior by themselves.

`FireAt(int me, int him)` does honor the object mask:

- resolves `GameObject* me`
- reads `me->carrier`
- calls `Carrier::SetSelected(carrier, me->weaponMask)`
- calls `Carrier::TriggerSelected(carrier)`

That matters because it separates normal "fire using current mask" behavior
from the specialized AI paths below.

`Craft::SetActiveMode(int)` also does not force a weapon mask. It only maps a
few modes into commands such as follow, reload, repair, rescue, and recycle.

`Minelayer::SetActiveMode(int)` and `TurretTank::SetActiveMode(int)` are both
tiny wrappers:

- `Minelayer::SetActiveMode(int)` maps mode `0xF` to `CMD_LAY_MINES`, else
  falls back to `Craft::SetActiveMode`
- `TurretTank::SetActiveMode(int)` maps mode `4` to `CMD_DROPOFF`, else falls
  back to `Craft::SetActiveMode`

So the class activation path is not the source of the forced slot.

The artillery AI root cause is exact in `ArtilleryProcess::DoAttack()`:

- it resolves the attacking craft's carrier
- it starts at weapon slot `0`
- it repeatedly calls `Carrier::GetWeapon(carrier, i)`
- it stops at the first non-null weapon
- it solves lead and directly fires that weapon object

There is no `weaponMask` consult in that selection path. For artillery-class
AI, "first available weapon on the carrier" is the hardcoded behavior.

The minelayer AI root cause is exact in `LayMinesTask::DoArrived()`:

- it resolves the controlled craft's carrier
- it explicitly calls `Carrier::GetWeapon(carrier, 0)`
- if that weapon exists and reports not-ready, the task waits
- otherwise it calls `Carrier::SetSelected(carrier, 1)`
- then it calls `Carrier::TriggerSelected(carrier)`

So the lay-mines task hardcodes both the slot check and the selected mask to
the first weapon.

This matches the user-observed symptom exactly:

- howitzers use the first carrier weapon because artillery AI walks weapons
  from slot `0` and fires the first non-null entry
- minelayers use the first carrier weapon because the lay-mines task checks
  slot `0` and selects mask `1`

#### Object layout

Recovered from PDB type data:

- `GameObject` size: `544`
- `GameObject::modeList` offset: `412` (`0x19C`)
- `GameObject::weaponMask` offset: `528` (`0x210`)
- `ModeList` size: `52`
- `ModeList::enabledMask` offset: `44`
- `ModeList::activeSlot` offset: `48`
- `Craft` size: `648`
- `HoverCraft` size: `736`
- `Minelayer` size: `752`
- `TurretTank` size: `856`
- `Howitzer` size: `856`
- `UnitProcess::me` offset: `44`
- `OffensiveProcess` size: `120`
- `ArtilleryProcess` size: `124`
- `MineLayerProcess` size: `88`

Implication:

- the active command-slot state for any `GameObject` lives at
  `this + 0x19C + 0x30`, which is `this + 0x1CC`
- AI process instances can reach their controlled craft through
  `process + 44`

#### Inheritance relevant to the bug

- `Howitzer` inherits `TurretTank`
- `Howitzer` overrides `GetCommand` and `UpdateModeList`
- `Howitzer` does not expose its own `SetActiveMode` in the recovered type
  data, so `TurretTank::SetActiveMode` is the relevant activation path
- `Minelayer` inherits `HoverCraft`
- `Minelayer` overrides both `UpdateModeList` and `SetActiveMode`

This means the likely native behavior split is:

- howitzer: `Howitzer::UpdateModeList` + `TurretTank::SetActiveMode`
- minelayer: `Minelayer::UpdateModeList` + `Minelayer::SetActiveMode`

#### Weapon mask access is not a plain raw field everywhere

The recovered `GameObject::weaponMask` field is at `+0x210`, but at least one
native getter decodes it:

- `0x00417C80`
  - `mov eax, [eax+0x210]`
  - `xor eax, 0x33333333`

There is also a separate raw field reader candidate:

- `0x0046DD70`
  - `mov eax, [eax+0x210]`
  - no xor

That means a patch must not assume that the backing field is always consumed in
decoded form. Any direct read or write of `weaponMask` has to account for the
encoded storage convention.

#### Weapon mask serialization / save-side helper exists

`0x00470F40` contains a compact helper that reads `this + 0x210` and emits
byte values `0..3` based on the stored mask value.

This is evidence that the engine already has native mask-to-slot translation
logic, but it does not prove the AI combat path uses that helper.

### Symbol / Address Notes

The GOG PDB is useful semantically, but some reported starts land in hot blocks
or split code and do not always line up with a clean function prologue when
linear-disassembled with `objdump`.

Treat these as semantic anchors, not patch-ready addresses, unless the bytes are
revalidated directly:

- `Howitzer::GetCommand`
- `Howitzer::UpdateModeList`
- `Minelayer::UpdateModeList`
- `Minelayer::SetActiveMode`
- `TurretTank::UpdateModeList`
- `TurretTank::SetActiveMode`

This caveat does not apply equally to everything. Some AI-side routines do have
clean exact starts.

### Exact AI-Side Anchors

These starts were revalidated directly in the executable:

- `ArtilleryProcess::DoAttack` at `0x0042AF10`
- `ArtilleryProcess::DoWait` at `0x0042B350`
- `ArtilleryProcess::ShouldAttack` at `0x0042C1E0`
- command-list helpers around `0x0042F020` and `0x0042F840`

`ArtilleryProcess::DoAttack` and a sibling routine around `0x0042BC50` are the
best verified AI-side anchors so far.

There is now a temporary runtime trace hook at the first internal call inside
`ArtilleryProcess::DoAttack`:

- patch site: `0x0042BB1A`
- overwritten bytes: `E8 01 AD FE FF`
- original call target: dynamically resolved from the patched call site
- return address: `patch site + 5`

The trace helper reads:

- `process + 44` as the controlled `Craft*`
- raw `weaponMask` at `craft + 0x210`
- decoded `weaponMask` as `raw ^ 0x33333333`
- `modeList.enabledMask` at `craft + 0x1C8`
- `modeList.activeSlot` at `craft + 0x1CC`

Enable it with:

- `OPENSHIM_TRACE_ARTILLERY_MASK=1`

Current implementation notes:

- GOG-validated only for now
- budget-limited to the first `400` `[ARTYMASK]` log lines
- instrumentation only, no behavior change

The equivalent minelayer AI family is known semantically:

- `MineLayerProcess::ChangesState`
- `MineLayerProcess::InitUState1`
- `MineLayerProcess::DoUState1`

but the current linear disassembly still lands inside a larger containing
function region, so the exact minelayer hook site needs one more validation pass
before patch bytes should be committed.

### What The TurretTank Mode Code Tells Us

The large `TurretTank` mode-update region around `0x00538120` through
`0x0053855F` is real executable code and uses several class-local flags and
three object fields:

- `this + 0x12C`
- `this + 0x130`
- `this + 0x134`

It repeatedly:

- checks byte flags in the `0x61..0x74` range
- calls helper code through common menu or mode functions
- toggles state bytes rather than directly touching `weaponMask`

This strongly suggests:

- `TurretTank::UpdateModeList` is building internal mode availability state
- the actual weapon-mask application is elsewhere
- patching only the menu-construction side is unlikely to fix AI-controlled
  howitzers

### What Is Not Yet Proven

The following are still unproven and still block a safe shipped patch:

1. The exact Redux byte-accurate equivalents of the legacy consume sites:
   - artillery "first non-null weapon" selection inside
     `ArtilleryProcess::DoAttack`
   - minelayer slot `0` plus `SetSelected(..., 1)` inside
     `LayMinesTask::DoArrived`
2. The cleanest Redux-side override rule:
   - choose by decoded `weaponMask`
   - choose by `modeList.activeSlot`
   - choose by a translation between the two
3. Whether the safest patch point is:
   - the class-local AI routine
   - a lower-level carrier weapon selector with caller filtering
   - a fire-dispatch helper immediately before weapon activation

### Best Current Interpretation

The bug is native AI behavior, not Lua policy:

- howitzers route through artillery AI, which selects the first non-null weapon
  instead of consulting `weaponMask`
- minelayers route through `LayMinesTask`, which explicitly checks slot `0` and
  selects mask `1`
- `FireAt` shows the engine does have a normal mask-honoring path, but these
  two AI paths bypass it
- the class `SetActiveMode` wrappers are not the forcing point
- both behaviors survive Lua or ODF-side mask configuration

That keeps the Shim as the correct long-term patch home.

### Recommended Next Steps

1. Run an in-game validation pass with:
   - howitzer using non-slot-0 masks
   - minelayer using non-slot-0 masks
   - both ODF and Lua-driven mask changes
2. Confirm that swapping `Carrier` slot `0` plus bitfields is sufficient for:
   - artillery fire selection
   - minelayer lay-mine triggering
3. If minelayer still misses in gameplay, revalidate the exact Redux
   `LayMinesTask::DoArrived` consume site and patch that path directly.
4. If player-controlled howitzer or minelayer UX regresses, narrow the helper
   to AI-only call paths rather than class-wide carrier biasing.

### Patch Recommendation

Do not patch this in EXU.

Do not patch this in EXU.

Do not ship a blind raw-field write to `weaponMask` as the only fix.

The current Shim patch instead biases the native first-slot behavior toward the
decoded `weaponMask` target by reordering the owning `Carrier`.
