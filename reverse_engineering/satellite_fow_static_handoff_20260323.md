# Satellite FOW Static Handoff

Date: March 23, 2026

Scope:

- Feature list item 24: restore Battlezone 1.5-style satellite fog of war
- Constraint for this pass: static-only analysis, no live process validation

## 1. What this pass was trying to answer

The earlier note already established the broad theory:

- legacy 1.5 satellite FOW depends on normal scanner and visibility state
- Redux probably still computes that state
- the likely regression is somewhere in the overview or Ogre render bridge

This follow-up pass was meant to tighten that theory and answer a narrower question:

- is `OverView::Render` itself still the best first render-side suspect?
- or is the stronger target actually the overview submission path around terrain and object visibility gating?

## 2. Reliable static evidence gathered in this pass

### 2.1 Legacy exact decomp still confirms the old ownership split

Relevant exact legacy files in:

- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full/ghidrecomp/results/bins/bzone.exe-aa1ee4/decomps`

Important bodies re-checked:

- `Apply_Satellite_View-0047b27f.c`
- `Set_Satellite_View-0047b221.c`
- `BasicVisibility-004ae19d.c`
- `SweepVisibility-004adc08.c`
- `GameObject_ComputeVisibility-004980ac.c`
- `GameObject_IsVisibleToUser-00496888.c`
- `Submit_Overview_Entities-004ea805.c`
- `BuildTerrainOverview-00520d2a.c`
- `FillTerrainMap-004d15ae.c`
- `Render-004d37b2.c` (`OverView::Render`)

What those bodies show:

- `Apply_Satellite_View` is mainly mode setup:
  - switches to `OVER_VIEW`
  - installs `Set_Satellite_View` as the camera update callback
  - sets the overview object and zoom
- `Set_Satellite_View` is mainly camera-matrix and zoom maintenance
- `Scanner::BasicVisibility` resets `isVisible` for normal objects, then sets owner/friendly-team bits and updates `seen`
- `Scanner::SweepVisibility` performs the scanner/range pass and marks matching objects as both `isVisible` and `seen`
- `GameObject_ComputeVisibility` converts per-team `isVisible` state into `illumination`
- `GameObject_IsVisibleToUser` is just an illumination gate:
  - visible if `gameObj->illumination > 0.0f`
- `Submit_Overview_Entities` explicitly checks `GameObject_IsVisibleToUser` before overview object submission
- `BuildTerrainOverview` is a separate terrain-overview rendering pass
- `MapRadar::FillTerrainMap` samples tile and normal data for the map texture and is not itself a full object-visibility gate

The most important refinement from this pass:

- legacy `OverView::Render` is mostly satellite input, selection, command, and camera-control logic
- it is not the main owner of the actual visibility gate for overview object drawing

That matters because it lowers the priority of patching `OverView::Render` directly as the first render-side fix target.

### 2.2 Redux still exposes the right function surface in the advisory PDB dump

Relevant Redux source ownership from:

- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/source_path_hits.txt`

Confirmed Redux modules:

- `fun3d/overview.c`
- `fun3d/mapradar.c`
- `fun3d/cockpitradar.c`
- `fun3d/scanner.c`
- `fun3d/gameobject.c`

Relevant Redux LLVM PDB entries from:

- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/llvm/pretty_funcs.txt`

Confirmed Redux functions and sizes:

- `Apply_Satellite_View` at `0x00154970`, size `342`
- `Set_Satellite_View` at `0x00154820`, size `322`
- `Toggle_Satellite_View` at `0x00154AD0`, size `25`
- `ControlPanel_SatelliteEnabled` at `0x00044230`, size `46`
- `GameObject_ComputeVisibility` at `0x0006EF00`, size `190`
- `Scanner::BasicVisibility` at `0x0010F420`, size `286`
- `Scanner::SweepVisibility` at `0x0010F540`, size `530`
- `BuildTerrainOverview` at `0x001BF500`, size `800`
- `OverView::Render` at `0x000E4170`, size `1471`
- `MapRadar::FillTerrainMap` at `0x00093DA0`, size `576`
- `MapRadar::Render` at `0x00092750`, size `5700`
- `CockpitRadar::Render` at `0x0003BA60`, size `7140`

Compared with legacy:

- `OverView::Render`: `1199` -> `1471`
- `BuildTerrainOverview`: `664` -> `800`
- `MapRadar::FillTerrainMap`: `529` -> `576`
- `MapRadar::Render`: `2955` -> `5700`
- `CockpitRadar::Render`: `4000` -> `7140`

Read:

- the scanner and visibility pipeline still exists in Redux as first-class code, not just dead leftovers
- `MapRadar` and `CockpitRadar` grew substantially, consistent with Redux/Ogre glue
- `OverView::Render` also changed, but not enough by itself to override the stronger legacy ownership clue that the actual visibility gate sat in overview submission, not in the UI/control body

### 2.3 Best-effort Redux ghidrecomp output is not reliable enough around `OverView`

The local best-effort decomp corpus under:

- `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps`

was useful for some symbol discovery, but not trustworthy for the actual `OverView` render body in this area.

Examples:

- nearby files such as `FUN_004e3990-004e3990.c` and `FUN_004e4730-004e4730.c` decompile to unrelated code paths
- the neighborhood around the advisory `OverView::Render` address did not line up cleanly with the named function surface

Read:

- use the Redux LLVM PDB dump as the reliable static source for ownership and addresses
- do not treat the local best-effort `FUN_004e41xx` decomp files as authoritative for overview render behavior

## 3. What changed in the working theory

The earlier note said the strongest first Redux-side suspects were:

- `OverView::Render`
- overview entity submission
- `BuildTerrainOverview`

After this static pass, that should be tightened to:

1. overview entity submission equivalent to legacy `Submit_Overview_Entities`
2. visibility gate equivalent to legacy `GameObject_IsVisibleToUser`
3. terrain overview render path around `BuildTerrainOverview`
4. only then `OverView::Render` itself, mainly as a control-flow owner or caller path
5. `MapRadar::Render` and `MapRadar::FillTerrainMap` as secondary suspects for panel behavior, not primary owners of full 1.5 satellite FOW

Reason:

- legacy `OverView::Render` is mostly command/input logic
- the legacy object-visibility gate is clearly in `Submit_Overview_Entities`
- the legacy terrain pass is separate in `BuildTerrainOverview`
- therefore the closest Redux regression candidate is no longer "overview UI code forgot visibility"
- it is more specifically "Redux overview terrain/object submission no longer honors the old visibility gate"

## 4. Static conclusions that are safe to carry forward

### 4.1 High-confidence conclusions

- Redux still contains the scanner and visibility functions needed for classic satellite FOW:
  - `GameObject_ComputeVisibility`
  - `Scanner::BasicVisibility`
  - `Scanner::SweepVisibility`
- Legacy full satellite FOW was not owned by `MapRadar::FillTerrainMap` alone
- Legacy overview object rendering definitely gated on `illumination` through `GameObject_IsVisibleToUser`
- Legacy overview terrain rendering was a separate pass in `BuildTerrainOverview`
- The first render-side Redux target should be the overview submission path, not just `OverView::Render`

### 4.2 Medium-confidence conclusions

- Redux `OverView::Render` is probably still mostly control/input logic, as in legacy, rather than the main place where hidden objects become visible
- The likely regression is either:
  - the legacy `GameObject_IsVisibleToUser` equivalent is gone/bypassed
  - the overview object submission equivalent no longer consults illumination
  - the Ogre-side overview bridge now submits all overview entities regardless of legacy visibility

### 4.3 Things static analysis could not prove here

- whether live Redux missions still compute correct `isVisible`, `seen`, and `illumination` values every frame
- whether the live overview submission path ignores those values
- whether the terrain pass itself also needs a fog/shroud-style treatment beyond object visibility

## 5. Useful supporting evidence already in this repo

OpenShim already has a satellite visibility probe scaffold in:

- `src/bzr_hooks.cpp`

Relevant offsets and logging:

- `kGameObjectIlluminationOffset = 0xDC`
- `kGameObjectIsVisibleOffset = 0x184`
- `kGameObjectSeenOffset = 0x188`
- `MaybeLogSatelliteVisibilitySample()`
- env flags:
  - `OPENSHIM_TRACE_SAT_VIS`
  - `OPENSHIM_TRACE_SATELLITE_VISIBILITY`

This is useful later because once live testing is available, it can answer the final unresolved question:

- are legacy-style visibility values correct and only the render bridge is wrong?

## 6. Recommended next RE steps when resuming

### 6.1 Best static next step

In Ghidra/Cutter/objdump terms, do this in order:

1. Locate the Redux caller chain around `BuildTerrainOverview` at `0x001BF500`
2. Locate the Redux equivalent of legacy `Submit_Overview_Entities`
3. Locate the Redux equivalent of legacy `GameObject_IsVisibleToUser`
4. Confirm whether any overview object-submission path still checks `illumination > 0`

Practical search hints:

- look for overview/world iteration code that walks world objects or object lists during overview rendering
- look for reads of the GameObject illumination field around overview submission code
- look for callers near the `Apply_Satellite_View` / `Set_Satellite_View` / `OverView::Render` cluster that branch into separate terrain/object overview rendering

### 6.2 Best live-assisted next step later

When live process work is available again:

1. enable the existing SATVIS logging
2. enter satellite view with known hidden and visible enemy units
3. verify whether hidden units still show:
   - `illumination == 0`
   - `isVisible` bit clear for user team
   - `seen` either clear or only historical
4. if those values are correct but units still render, patch the overview submission gate

### 6.3 Best first patch candidates after that

If the live data confirms the state is right but rendering is wrong, the best first native patch target is probably:

- the Redux equivalent of legacy `Submit_Overview_Entities`

If the state itself is wrong before rendering:

- start at the Redux equivalents of `Scanner::BasicVisibility`, `Scanner::SweepVisibility`, and `GameObject_ComputeVisibility`

## 7. Bottom line for handoff

This static pass did not solve item 24, but it did improve the target selection materially.

Updated handoff summary:

- The earlier broad "overview or Ogre bridge" theory still holds.
- The best first Redux-side suspect is now more specific:
  - overview object submission / illumination gating
  - not merely `OverView::Render` as a generic overview function
- `MapRadar::FillTerrainMap` remains secondary and is still unlikely to be the main owner of full 1.5 satellite FOW.
- The current best path is:
  - find the Redux `Submit_Overview_Entities` equivalent
  - verify whether it still honors illumination
  - then use the existing SATVIS runtime probe later to confirm the patch direction
