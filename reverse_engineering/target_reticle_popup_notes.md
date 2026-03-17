# Target Reticle Popup Notes

Date: 2026-03-17

## Scope

Goal: determine where Battlezone 98 Redux automatically shows the target
reticle sprite and health bar when player ordnance hits an object, and map out
the safest implementation path for a persistent PDA setting with these modes:

- `DEFAULT`
- `NEUTRAL ONLY`
- `EXPLICIT ONLY`

The intended user-facing behavior is:

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
  `C:\Users\istuart\Documents\GIT\ExtraUtilities-G1\src\UnitVo.cpp`
  `C:\Users\istuart\Documents\GIT\ExtraUtilities-G1\src\luaexport.cpp`
- Campaign persistent config:
  `C:\Users\istuart\Documents\GIT\Battlezone98Redux_CampaignReimagined-1\_Source\Scripts\PersistentConfig.lua`

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

From `public_functions.csv`:

- `SelectionDisplay::Render`:
  `?Render@SelectionDisplay@@UAEXXZ` -> `0x0043E0E0`
- `GameObject::SetDamageFlags`:
  `?SetDamageFlags@GameObject@@IAEXPAUDAMAGE@@@Z` -> `0x0046C860`
- `Targeting::Simulate`:
  `?Simulate@Targeting@@UAEXM@Z` -> `0x00527550`

These are the main Redux native targets for implementation.

## Recommended Patch Shape

The safest behavioral design is still to patch the render-side decision rather
than alter damage state globally.

Preferred native logic:

1. keep the explicit target path untouched
2. gate or suppress only the recent-hit popup path
3. leave `playerShot` available for any other system that may use it

That gives the three requested modes cleanly:

- `DEFAULT`: stock explicit-target and recent-hit popup paths remain active
- `NEUTRAL ONLY`: keep recent-hit popups except when the target object is team
  `0`
- `EXPLICIT ONLY`: disable the recent-hit popup path entirely, but keep the
  explicit target path

## Config Integration Plan

The persistent-config plumbing already exists in a very similar shape for
under-attack alerts.

Planned chain:

1. Campaign PDA setting in `PersistentConfig.lua`
2. EXU Lua export, similar to `SetUnderAttackAlertMode`
3. EXU bridge into `winmm.dll` via `GetProcAddress`
4. OpenShim exported setter, similar to `OpenShimSetUnderAttackAlertMode`
5. OpenShim render-side native hook consults the selected mode

## Current Blocker

This environment is not launchable for the target runtime, so the exact Redux
instruction bytes at the live hook site were not revalidated yet.

What is known:

- semantic behavior from the legacy exact-match decompile
- matching Redux GOG function names and addresses from the PDB export
- the campaign/EXU/OpenShim config bridge pattern already used elsewhere

What is still needed before shipping native code:

- validate the live Redux hook site in a runnable session
- recover the exact instruction sequence around the chosen render-side branch
- verify Steam separately if this is intended to ship there too

## Resume Checklist

When a runnable build is available again:

1. validate `SelectionDisplay::Render` at `0x0043E0E0`
2. locate the exact branch that corresponds to the `playerShot` popup path
3. confirm where team number can be read cheaply for the rendered object
4. add OpenShim mode enum and bridge export
5. add EXU setter bridge and Lua export
6. add persistent PDA menu entry in Campaign Reimagined
7. test all three modes on:
   - neutral props and buildings
   - enemy units and buildings
   - friendly selected targets
   - explicit `T` targeting

## Short Conclusion

The investigation is complete enough to resume quickly later.

The stock popup reticle is confirmed to be driven by:

- explicit target selection, and
- a two-second `playerShot` timer

So the requested feature is feasible and the likely final solution is a
render-side mode gate, but the final native patch should wait until the live
Redux hook bytes can be revalidated in a launchable environment.
