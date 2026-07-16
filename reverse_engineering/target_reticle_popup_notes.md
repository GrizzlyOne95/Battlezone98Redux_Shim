# Target Reticle Popup Notes

Date: 2026-03-17

Updates: 2026-03-18, 2026-07-13

The `NEUTRAL ONLY` option was revisited on 2026-07-13. The crash cause was not
the recent-hit call site itself: the hook received the complete Redux
`GameObject*`, but the old team lookup treated offset `+0x00` as the inherited
GameObject interface. Redux places that interface at `+0x18`. The old code
therefore loaded the wrong vtable and called slot `+0x04` with the wrong
`this` pointer.

The team lookup now uses `[object + 0x18]`, calls its `GetTeam` slot at `+0x04`,
and passes `object + 0x18` as `this`, matching stock Redux call sites. The
experimental downgrade/force guard has been removed, so the normal user-facing
scope is again:

- `DEFAULT`
- `NEUTRAL ONLY`
- `EXPLICIT ONLY`

## Scope

Goal: determine where Battlezone 98 Redux automatically shows the target
reticle sprite and health bar when player ordnance hits an object, and map out
the safest implementation path for a persistent PDA setting. The original
investigation covered these modes:

- `DEFAULT`
- `EXPLICIT ONLY`

The current intended shipping behavior is:

- `DEFAULT`: keep stock behavior
- `NEUTRAL ONLY`: suppress auto-popup reticles on team `0` neutral objects
- `EXPLICIT ONLY`: only show the target reticle when the player explicitly
  targets something, such as with the `T` target action

## Primary Inputs

- Legacy exact-match global decompile:
  `reverse_engineering\workshop\global_decompile\legacy_bz1_exact_full\ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps`
- Redux GOG best-effort PDB export:
  `reverse_engineering\workshop\global_decompile\bzr_gog_best_effort\pdb_reference\public_functions.csv`
- Existing OpenShim config bridge pattern:
  `src\bzr_hooks.cpp`
  `src\winmm_proxy.cpp`
  `src\winmm.def`
- Existing Extra Utilities bridge pattern:
  `<USER_HOME>\Documents\GIT\ExtraUtilities-G1\src\UnitVo.cpp`
  `<USER_HOME>\Documents\GIT\ExtraUtilities-G1\src\luaexport.cpp`
- Campaign persistent config:
  `<USER_HOME>\Documents\GIT\Battlezone98Redux_CampaignReimagined-1\_Source\Scripts\PersistentConfig.lua`

## Result

The target reticle popup is controlled by `SelectionDisplay::Render`, and the
stock game uses two separate reasons to draw the same target sprite:

- explicit target selected by the player
- recent-hit timer after the player damages an object

That second path is what causes UI spam when neutral props, pylons, geysers,
and similar team `0` objects get hit.

## Legacy Behavioral Findings

### `SelectionDisplay::Render`

Legacy exact decompile:

- `Render-004c1db7.c`

Relevant control flow:

- explicit target path:
  `local_19 = pGVar1 == local_a0;`
- recent-hit popup path:
  `local_1c = Get_TimeLocal() < pGVar1->playerShot + 2.0;`

Both feed the same sprite draw:

- target sprite draw when `local_19` or `local_1c` is true
- health bar path also keys off the same popup/target conditions

This is the core finding: the stock reticle/health popup is not only tied to
manual target selection.

### `GameObject::SetDamageFlags`

Legacy exact decompile:

- `SetDamageFlags-00496da9.c`

Relevant behavior:

- when the incoming `DAMAGE` flags include the player-shot bit (`0x10`)
- and the damage source is not the same object as the damaged object
- the game writes:
  `this->playerShot = Get_TimeLocal();`

That timestamp is later consumed by `SelectionDisplay::Render`.

### `Targeting::Simulate`

Legacy exact decompile:

- `Simulate-004dc119.c`

Relevant behavior:

- the player's current explicit target is stored in
  `GameObject::userObject->targetHandle`
- that is the path used for the stock `T`-style targeting behavior

## Redux GOG Symbol Mapping

The best-effort PDB export originally suggested:

- `SelectionDisplay::Render`:
  `?Render@SelectionDisplay@@UAEXXZ` -> `0x0043E0E0`
- `GameObject::SetDamageFlags`:
  `?SetDamageFlags@GameObject@@IAEXPAUDAMAGE@@@Z` -> `0x0046C860`
- `Targeting::Simulate`:
  `?Simulate@Targeting@@UAEXM@Z` -> `0x00527550`

Later semantic recovery showed that the `SelectionDisplay` PDB mapping is stale
for this executable: `0x0043E100` is an audio-buffer routine, while the actual
Redux selection render loop is `FUN_00497AA0`. Its recent-hit getter call is at
`0x00497C26`. The `GameObject::SetDamageFlags` and `Targeting::Simulate`
mappings remain useful, but future work should prefer the recovered render body
over the old `0x0043E0E0` label.

## Live Redux Revalidation

Steam runtime revalidation was completed on March 17, 2026 against a live
`battlezone98redux.exe /nointro` session.

Verified results on the running Steam 2.2.301 process:

- the first `96` bytes at the then-PDB-labeled `0x0043E100` site matched the GOG
  executable exactly (this was later identified as an audio-buffer routine, not
  the selection render body)
- the first `96` bytes of `GameObject::SetDamageFlags` at `0x0046C860`
  matched the GOG executable exactly
- the first `96` bytes of `Targeting::Simulate` at `0x00527550`
  matched the GOG executable exactly

Practical takeaway:

- the current Steam build matched GOG at all three probed addresses
- the launchability blocker is gone for this feature
- the active reticle hook should be validated at the recovered
  `0x00497C26`/`0x00497C27` call site rather than the stale PDB render label

## Recommended Patch Shape

The safest behavioral design is still to patch the render-side decision rather
than alter damage state globally.

Preferred native logic:

1. keep the explicit target path untouched
2. gate or suppress only the recent-hit popup path
3. leave `playerShot` available for any other system that may use it

That originally gave the three requested modes cleanly:

- `DEFAULT`: stock explicit-target and recent-hit popup paths remain active
- `EXPLICIT ONLY`: disable the recent-hit popup path entirely, but keep the
  explicit target path

The 2026-03-18 shipping recommendation temporarily narrowed this to `DEFAULT`
and `EXPLICIT ONLY`. The corrected 2026-07-13 interface adjustment restores
`NEUTRAL ONLY` as a normal persistent mode.

## Config Integration Plan

The persistent-config plumbing already exists in a very similar shape for
under-attack alerts.

Planned chain:

1. Campaign PDA setting in `PersistentConfig.lua`
2. EXU Lua export, similar to `SetUnderAttackAlertMode`
3. EXU bridge into `winmm.dll` via `GetProcAddress`
4. OpenShim exported setter, similar to `OpenShimSetUnderAttackAlertMode`
5. OpenShim render-side native hook consults the selected mode

## 2026-07-13 Resolution

The render-side site is now recovered and implemented:

- `0x00497C26`: `call 0x00497890`
- `0x00497C27`: rel32 operand patched by OpenShim
- `0x00497890`: stock `playerShot` getter, reading `[ecx + 0x1D8]`
- immediately before the call, Redux loads the complete rendered object into
  `ECX`

The crash-prone part was the hook's team read. Stock Redux calls the relevant
GameObject virtuals through `[object + 0x18]`; the team slot is `+0x04`. The
fixed helper applies that same subobject adjustment and is protected by the
existing SEH fallback. If a team cannot be read, the object is treated as
non-neutral and stock popup behavior is preserved.

The end-to-end persistent path was restored at the same time:

- Extra Utilities now passes mode `2` through to OpenShim instead of rewriting
  it to mode `1`
- Campaign Reimagined again exposes `NEUTRAL ONLY` in its PDA preset list
- saved mode `2` values map back to that preset instead of being normalized to
  `DEFAULT`

Release/Win32 compilation completed successfully for both OpenShim and Extra
Utilities, and `luac -p` passed for the campaign `PersistentConfig.lua` change.
Manual in-mission behavioral validation is still recommended for neutral
props, explicit targets, and non-neutral hit popups.

## Resume Checklist

1. Deploy the corrected Release/Win32 `winmm.dll`.
2. Select `NeutralOnly` through the PDA/EXU bridge or set
   `[Display] TargetReticle = NeutralOnly` in `openshim.ini`.
3. Test all three modes on:
   - neutral props and buildings
   - enemy units and buildings
   - friendly selected targets
   - explicit `T` targeting

## Short Conclusion

The stock popup reticle is confirmed to be driven by:

- explicit target selection, and
- a two-second `playerShot` timer

The persistent render-side gate now supports all three requested modes. The
neutral-only crash was caused by a missing Redux `+0x18` base-subobject
adjustment in the hook, not by the selected rel32 call site.
