## Jump Sniping, Satellite FOW, PerceivedTeam

Date: March 18, 2026

Scope:

- item 23: jump sniping back to 1.5 behavior
- item 24: restore 1.5 satellite fog of war
- item 25: perceivedTeam not updating when the unit reveals itself by firing

### 1. Legacy BZ1 baseline

The exact legacy corpus is available at:

- `reverse_engineering/workshop/global_decompile/legacy_bz1_exact_full`

The best legacy hooks and function names for these systems are already exposed by the exact PDB-backed decompile.

#### 1.1 Satellite view and visibility

Legacy satellite view is not just a camera toggle.

Relevant legacy functions:

- `Set_Satellite_View` at `0047B221`
- `Apply_Satellite_View` at `0047B27F`
- `Toggle_Satellite_View` at `0047B337`
- `GameObject_ComputeVisibility` at `004980AC`
- `Scanner::BasicVisibility` at `004AE19D`
- `Scanner::SweepVisibility` at `004ADC08`
- `GameObject::SetVisibility` at `004ADBBD`
- `GameObject::ClearVisibility` at `004ADBD7`
- `GameObject::FullVisibility` at `00495079`

What the legacy code shows:

- `Apply_Satellite_View` switches to `OVER_VIEW`, sets `View_Record.Update_Camera = Set_Satellite_View`, and uses `OverView_*` camera state.
- `Scanner::BasicVisibility` clears `isVisible` for normal objects, then sets visibility for the owning team and friendly teams, and updates `seen`.
- `Scanner::SweepVisibility` does the radar/range search and marks objects as both `isVisible` and `seen`.
- `GameObject_ComputeVisibility` drives illumination from the per-team `isVisible` bits after scanner sweeps complete.
- `GameObject_IsVisibleToUser` is just an illumination gate for the user team view.
- `Submit_Overview_Entities` uses `GameObject_IsVisibleToUser` before overview entity submission.
- `BuildTerrainOverview` is the terrain pass for overview rendering.
- legacy `MapRadar::FillTerrainMap` does not consult `isVisible`, `seen`, or illumination; it only samples terrain tile and normal data to build the map texture.

Important legacy symbols:

- `SateliteView.Fog_Start`
- `SateliteView.Fog_End`
- `TerrainView.Fog_Start`
- `TerrainView.Fog_End`
- `visibilityScale`
- `TerrainVisibilityRange`
- `SATELLITE_ITEM`
- `mapRadar`
- `cockpitRadar`

Read:

- 1.5 satellite fog of war is tied to the normal legacy visibility pipeline.
- legacy overview object submission definitely honors visibility through `GameObject_IsVisibleToUser` and illumination.
- `MapRadar::FillTerrainMap` is probably not the primary owner of full satellite fog of war in 1.5.
- if Redux satellite shows everything, the first regression suspect should move toward the `OverView` render path, overview entity submission, or terrain-overview fog handling, with `MapRadar` kept as a secondary suspect for map-panel behavior.

#### 1.2 perceivedTeam

Relevant legacy functions:

- `GameObject::GetPerceivedTeam` at `00405B45`
- `GameObject::SetPerceivedTeam` at `00495314`
- global `GetPerceivedTeam(int)` at `0045EECF`
- global `SetPerceivedTeam(int,int)` at `0045EEE5`

What the legacy code shows:

- `GetPerceivedTeam` is a direct field read.
- `SetPerceivedTeam` is a direct field write.
- There is no recompute logic in the accessor itself.

Read:

- the bug is almost certainly not inside the accessor
- the real failure site is some caller path that should update `perceivedTeam` when a unit transitions from hidden/disguised perception into an overt hostile state
- attack, retaliation, target-acquire, or damage-response code is the likely owner, not the getter or setter

#### 1.3 Jump sniping / person landing state

Relevant legacy sniper UI functions:

- `SniperInterface::Init` at `004DA9CC`
- `SniperInterface::Simulate` at `004DAA78`
- `SniperInterface::Render` at `004DAB57`

What the legacy sniper UI code shows:

- `SniperInterface::Simulate` only checks:
  - `GameObject::userObject`
  - craft-like class id
  - a user-object virtual at `+100`
  - selected weapon bits on the carrier
  - `weaponClass->sig == 0x534E4950` for sniper
- if a selected sniper weapon is found, it updates the sniper camera matrix and enables the overlay
- there is no landing, crouch, grounded, or state-transition logic in `SniperInterface::Simulate`

Relevant legacy person-state classes:

- `PersonGlide`
- `PersonStraight`
- `PersonGetIn`
- `PersonRetreat`
- `PersonAttack`
- `SoldierAttack`
- `SoldierRetreat`
- `SoldierReturn`

Relevant legacy methods:

- `PersonGlide::DoState`
- `PersonStraight::DoState`
- `PersonAttack::InitState`
- `PersonAttack::DoState`
- `PersonRetreat::DoStateProlog`
- `SoldierAttack::InitState`
- `SoldierAttack::DoState`

Read:

- the old crouch-on-touchdown behavior is very unlikely to live in `SniperInterface`
- the first real candidates are `Person`, `PersonProcess`, `SoldierProcess`, and person animation/state transition code
- the user suspicion about person-class animation ownership is consistent with the corpus

### 2. Redux / GOG evidence

The best-effort Redux corpus is available at:

- `reverse_engineering/workshop/global_decompile/bzr_gog_best_effort`

The GOG PE/PDB pair is not an exact match, but the PDB metadata is still very useful for source ownership.

#### 2.1 Redux source/module hits

GOG PDB metadata still points at the same major ownership areas:

- `MapRadar.obj` -> `fun3d/mapradar.cpp`
- `CockpitRadar.obj` -> `fun3d/cockpitradar.cpp`
- `Scanner.obj` -> `fun3d/scanner.cpp`
- `GameObject.obj` -> `fun3d/gameobject.cpp`
- `SniperInterface.obj` -> `fun3d/sniperinterface.cpp`
- `Person.obj` -> `fun3d/person.cpp`
- `PersonProcess.obj` -> `fun3d/personprocess.cpp`
- `SoldierProcess.obj` -> `fun3d/soldierprocess.cpp`

Important GOG module/include hints:

- `MapRadar.obj` includes `overview.h`, `terramap.h`, `controlpanel.h`, `aicommand.h`, `gameobject.h`
- `CockpitRadar.obj` includes `scanner.h`, `terramap.h`, `gameobject.h`, plus Ogre render glue headers
- `SniperInterface.obj` includes `craft.h`, `carrier.h`, `rangex.h`, `gameobject.h`, plus Ogre render glue headers
- `Person.obj` includes `animobj.h`, `animsprite.h`, `ogre76handler.h`, `chunkeffect.h`

#### 2.2 Redux public-function names still present in the GOG PDB metadata

The advisory GOG PDB still exposes these names:

- `_GameObject_ComputeVisibility`
- `?SweepVisibility@Scanner@@QAEXXZ`
- `?BasicVisibility@Scanner@@SAXXZ`
- `?SetPerceivedTeam@@YAXHH@Z`
- `?Init@SniperInterface@@UAEXXZ`
- `?Simulate@SniperInterface@@UAEXM@Z`
- `?Render@SniperInterface@@UAEXXZ`
- `?Init@MapRadar@@UAEXXZ`
- `?Render@MapRadar@@UAEXXZ`
- `?FillTerrainMap@MapRadar@@IAEXABVPixelBox@Ogre@@MMMM@Z`
- `?Init@CockpitRadar@@UAEXXZ`
- `?Update@CockpitRadar@@QAEXM@Z`
- `?Render@CockpitRadar@@UAEXXZ`
- `_ControlPanel_SatelliteEnabled`
- `_UserPref_unlimitedRadar`

Read:

- Redux still appears to carry the same logical systems, even if the exact binary layout moved
- the advisory PDB keeps the same major ownership surfaces, but for item 24 the better first pass is now `OverView` plus overview terrain or object submission, not just `MapRadar`

#### 2.2.1 Redux LLVM PDB dump hits that refine item 24

The LLVM PDB dump is especially helpful here because it still names the exact Redux functions even when the best-effort Ghidra export does not.

Relevant Redux functions still present in the LLVM dump:

- `BuildTerrainOverview(CAMERA*)`
- `GameObject_ComputeVisibility()`
- `MapRadar::FillTerrainMap(Ogre::PixelBox&, float, float, float, float)`
- `MapRadar::Render()`
- `OverView::Render()`
- `Scanner::BasicVisibility()`
- `Scanner::SweepVisibility()`

Read:

- Redux still has both the old visibility computation path and a distinct `OverView` render path.
- that is a better structural match for the 1.5 satellite behavior than treating `MapRadar::FillTerrainMap` as the sole owner.

#### 2.3 Redux animation/state hints for jump sniping

Important Redux strings/symbols:

- `kneel2stand`
- `stand2Kneel`
- `STAND`
- RTTI for `Person`
- RTTI for `PersonProcess`
- RTTI for `PersonGlide`
- RTTI for `PersonStraight`
- RTTI for `PersonAttack`
- RTTI for `PersonRetreat`
- RTTI for `SoldierProcess`

Read:

- Redux still has explicit person-state types and explicit kneel/stand transition strings
- that makes a person-state or Ogre-skeletal animation bridge regression much more plausible than a sniper-overlay regression

### 3. Existing workspace hooks that may help

#### 3.1 ExtraUtilities scanner exposure

EXU already exposes scanner data through the live game object:

- `GameObject::GetScanner()` uses offset `0x198`
- `Scanner` layout currently used by EXU:
  - `range`
  - `period`
  - `active`
  - `sweep`
  - `owner`

Existing EXU Lua-facing helpers already touch:

- radar period
- radar range
- Ogre scene visibility mask
- Ogre movable visibility flags
- satellite state/camera/cursor/zoom

Read:

- if Redux map view no longer respects legacy visibility bits, there is enough existing workspace plumbing to build a diagnostic or temporary workaround
- a practical first probe would be to force scanner range/period updates and compare that to actual satellite rendering
- a second practical probe would be to compare legacy visibility state against Ogre visibility-mask behavior while in satellite mode

#### 3.2 OpenShim chunk visibility work is a useful analogy

The existing chunk-render investigation strongly suggests a broader pattern in Redux:

- legacy simulation state can still exist and update correctly
- the Ogre render bridge can silently stop honoring that state

That does not prove the satellite issue is the same bug, but it makes this explanation plausible:

- legacy visibility/scanner state is still being computed
- the Ogre-side map/satellite render path is bypassing or ignoring it

### 4. First hook targets by issue

#### 4.1 Item 23: jump sniping

Best first targets:

1. `Person.obj`
2. `PersonProcess.obj`
3. `SoldierProcess.obj`
4. person-state transitions around `PersonGlide` <-> `PersonStraight`
5. any Redux code that binds the strings `kneel2stand` and `stand2Kneel`

Less likely first target:

- `SniperInterface` itself

Reason:

- legacy `SniperInterface::Simulate` is just weapon-selection/camera enable logic
- the landing/crouch behavior looks like a person-state or animation transition issue

#### 4.2 Item 24: satellite fog of war

Best first targets:

1. `OverView::Render`
2. `BuildTerrainOverview`
3. overview entity submission equivalent to legacy `Submit_Overview_Entities`
4. `GameObject_ComputeVisibility`
5. `Scanner::BasicVisibility`
6. `Scanner::SweepVisibility`
7. `MapRadar::Render`
8. `MapRadar::FillTerrainMap`
9. Ogre-side visibility-mask or proxy submission in overview/map view

Reason:

- legacy satellite FOW clearly depends on scanner-driven visibility bits plus overview render behavior
- legacy `MapRadar::FillTerrainMap` itself is not visibility-aware, so it is probably not the main 1.5 ownership point for full satellite fog of war
- Redux almost certainly still has the same logical components, but the Ogre overview bridge may no longer honor them

#### 4.3 Item 25: perceivedTeam

Best first targets:

1. attack-state entry for hidden/sniped units
2. retaliation / target-acquire paths
3. damage-response paths
4. any callsites that should invoke `SetPerceivedTeam` when a unit becomes overtly hostile

Not the right first target:

- the accessor itself

Reason:

- the legacy getter/setter are only field accessors
- the bug is a missing or late caller, not broken accessor logic

### 5. Practical next RE steps

If this investigation turns into implementation work, the next most efficient passes look like:

1. Locate the live Redux functions that reference `kneel2stand` and `stand2Kneel`.
2. Locate the live Redux function(s) that reference `SetPerceivedTeam` and the `" Perceived Team (%d)"` debug string.
3. Trace `MapRadar::FillTerrainMap` or `MapRadar::Render` in the GOG/Steam binary and compare what it uses instead of the old `isVisible/seen` gates.
4. Trace Redux `OverView::Render` and the terrain-overview submission path first, then compare object submission against the legacy `Submit_Overview_Entities` visibility gate.
5. Add temporary logging/hooks in OpenShim or EXU for:
   - per-object legacy visibility bits
   - per-object scanner ownership/range hits
   - per-object illumination values during satellite view
   - perceived-team writes
   - person state changes for the user avatar while sniper is selected

### 5.1 Item 25 caller narrowing from the exact legacy corpus

A direct caller search against the exact 1.5 decompile changes the first-pass target list substantially.

Relevant legacy `SetPerceivedTeam` callers:

- `GameObject::SetDamageFlags` at `00496DA9`
- `OffensiveProcess::DoSubTask` at `0044DEC8`
- `TurretTankProcess::DoSubTask` at `00467AC5`
- `Person::RegCollision` at `004A6E06`
- `Craft::AbandonPilot` at `00488DB8`
- `Craft::ExplodePilot` at `00488A98`

What those callers do:

- `GameObject::SetDamageFlags` is the important reveal path for live combat.
  - When a non-self `damager` exists during a shot event, legacy records `who_shot_JR`, calls `SetWhoIShot(damager, victimHandle)`, and then sets the `damager` object's `perceivedTeam` to its real team.
  - That means an overt attacker is globally "revealed" by damage bookkeeping, not by `PersonAttack::InitState` or `SoldierAttack::DoState`.
- `OffensiveProcess::DoSubTask` and `TurretTankProcess::DoSubTask` are secondary reveal paths for `attackUser` retarget logic.
  - If the process decides it should keep attacking the user after losing the current handle, legacy calls `GameObject::SetPerceivedTeam(GameObject::userObject, actualTeam)`.
  - This makes them plausible secondary suspects for sniper-specific reacquire edge cases.
- `Person::RegCollision` sets the entered craft's perceived team to the pilot's real team when the pilot boards it.
  - This is not the best match for the "opens fire and does not draw aggro" report.
- `Craft::AbandonPilot` and `Craft::ExplodePilot` reset the craft's perceived team to `0`.
  - These are lifecycle cleanup paths, not the hostile-reveal path.

Updated read for item 25:

- the original "attack-state entry / retaliation / target-acquire / damage-response" framing was directionally correct
- but the exact legacy corpus says the primary owner is `GameObject::SetDamageFlags`
- `OffensiveProcess::DoSubTask` and `TurretTankProcess::DoSubTask` are the next-best suspects, especially for sniper or user-target reacquire behavior
- `PersonAttack` / `SoldierAttack` state code is not where legacy performs the core perceived-team reveal write

Implication for Redux:

- if Redux units can openly fire, deal damage, and still fail to draw aggro, the most likely regression is that the legacy `damager->perceivedTeam = realTeam` write is missing or bypassed in the Redux equivalent of `GameObject::SetDamageFlags`
- if the bug is narrower and mostly appears around user-sniper or reacquire transitions, then the Redux equivalents of `OffensiveProcess::DoSubTask` / `TurretTankProcess::DoSubTask` move up in priority
- either way, the accessor itself remains the wrong place to patch

### 6. Current bottom line

Item 23:

- likely a person-state or skeletal-animation transition regression
- probably not a `SniperInterface` regression

Item 24:

- likely a legacy-visibility-to-Ogre regression in the Redux overview or satellite render bridge
- the strongest first Redux-side suspects are now `OverView::Render`, overview entity submission, and `BuildTerrainOverview`
- `MapRadar::FillTerrainMap` remains worth checking, but the legacy code suggests it is not the primary owner of full satellite fog of war

Item 25:

- likely a missing or bypassed reveal write in the Redux equivalent of `GameObject::SetDamageFlags`
- secondary suspects are the `attackUser` retarget paths in Redux equivalents of `OffensiveProcess::DoSubTask` and `TurretTankProcess::DoSubTask`
- not a broken getter/setter implementation
