# Player pilot flashlight investigation — 2026-09-05

## Decision

**Superseded — see "Runtime qualification and implementation" at the end of
this file.** The feature is implemented and validated on Windows/GOG. The
original decision, and the two bone recommendations below, are kept as the
pre-runtime record; live measurement contradicted both.

<details><summary>Original decision, 2026-09-05 (pre-runtime)</summary>

Feasible in principle; **not yet qualified for production implementation**.
No flashlight runtime code or configuration changes were made. This task did
not create or switch branches. The checkout started on
`agent/nickname-lounge-reauth` and changed externally to `main` during the
investigation; this report is left uncommitted.

The initial helmet candidate was `Bip01_Head` on the player's world Ogre
entity. The subsequent first-person weapon investigation below supersedes
that recommendation for a **gun-following** flashlight: use the FP entity's
`*21mg1` bone. Production light ownership and live aiming remain unqualified.

</details>

## Verified construction and integration evidence

- `src/patches/bzr_hooks.cpp`, stock headlight section: visibility, colour,
  beam shape, rainbow cycling, and attenuation repair already exist. These
  operate on an engine-owned light at render bridge `+0xA8`; they do not create
  a light for a pilot lacking one. `RefreshHeadlightState` runs from the world
  render callback and throttles policy updates to 200 ms.
- Ghidra decompilation of released GOG `0x0067F599` independently shows the
  construction path enumerating skeleton bones and recognizing the `hlgt`
  prefix. It creates a spotlight, stores it at bridge `+0xA8`, sets diffuse and
  specular colour, attenuation `(600, 1, 0.007, 0.0002)`, type 2, position and
  direction derived from the source bone, a 10/20 degree cone, and disables
  shadow casting. The light is attached to the entity's scene node, rather
  than an animated bone TagPoint. Ghidra treats this address as a split
  function fragment with an inherited frame; it is **not** a callable entry
  point or proposed hook site.
- The existing policy stands down in multiplayer and with EXU loaded. A
  pilot feature should deliberately preserve that ownership boundary unless
  coordinated EXU integration is separately designed.
- `reverse_engineering/player_pilot_animation_management_20260827.md` records
  the released runtime entity chain: local `Person +0xF0` to render bridge,
  then bridge `+0x94` to the world Ogre entity. World and first-person entities
  are distinct. The same chain is used by `pilot_fp_animation_trace.cpp`.
- Independent stock skeleton inspection found `Bip01_Head` and
  `Bip01_HeadNub` in American, Soviet, and Black Dog pilot world and FP assets
  (`aspilo`, `sspilo`, `bspilo`). Faction-specific `*11POV` / `*11GC1` names
  were found in FP assets, not the world assets in that inspection.

## Attachment ownership evidence

Local sibling `ogre-1.10.0/OgreMain/src` provides the API design evidence:

- `OgreEntity.cpp:1553`, `attachObjectToBone`: creates a TagPoint, registers
  the movable child, and notifies its attachment.
- `OgreEntity.cpp:1621`: pointer-based detach overload is available.
- `OgreEntity.cpp:276,1659`: entity teardown detaches children and frees
  TagPoints; it does not destroy those movable children.
- `OgreMovableObject.cpp:102`: movable destruction detaches from the parent
  entity if still attached.
- `OgreSceneManager.cpp:405`: `destroyLight(Light*)` uses the owning manager's
  movable-object destruction.

This suggests a separately owned SceneManager light attached to `Bip01_Head`.
Destroy it through the still-live owning manager without dereferencing an old
pilot entity. Scene clear/manager teardown needs its own verified ownership
boundary; do not retain and later destroy a pointer the scene has already
freed. Do not insert a new light into bridge `+0xA8` without establishing the
engine's cleanup contract for that field.

These are upstream source semantics, not a claim of released DLL ABI/runtime
qualification. Verify the exact released export decorations and string ABI
before implementing `attachObjectToBone`.

## Live probes and limitations

Executable: GOG `battlezone98redux.exe`, SHA-256
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.

Tool: `bzr-frida.cmd -p <PID> -l reverse_engineering/probe_pilot_flashlight.js
-q -t <seconds> -o <temporary log>`, after launch through a PowerShell session
dot-sourcing `reverse_engineering/BZRHarness.ps1` with `BZR_FORCE_WINDOWED=1`.
All sessions used `Stop-BZRGame -Id` for cleanup when still running.

The probe file was already untracked when this task began and was not modified.
It observes `Person::Simulate` at main+`0x19D340` (`0x0059D340` in these runs),
reads the local-player pointer at main+`0x517AFC`, and enumerates relevant bones
through Ogre exports. Its READY marker confirms initialization, not a pilot
sample or a validation of bone attachment APIs.

| PID | Fixture / observation | Result |
| --- | --- | --- |
| 38048 | `lcbench.bzn`, temporary Lua HopOut overlay | Game reached simulation, but no HopOut marker or pilot samples were captured; no conclusion about pilot bones. |
| 32172 | Existing `pilot.bzn` | `BZLogger.txt`: could not load terrain `lcbench.trn`; fixture retained the original terrain reference. |
| 19892 | Temporary textual `lcbench` → `pilot` reference correction in `pilot.bzn` | Reached first-frame setup, then exited due to complete render failure. Ogre reported missing objects in `pc/materials/TestGround.material` and a DX11 draw without vertex/fragment shaders. No pilot samples. |

Temporary Lua and BZN overlays were restored byte-for-byte in `finally` blocks.
Raw probe output was kept under the host temporary directory
`bzr-pilot-light-20260905`. Game evidence was read from the user-designated
GOG `logs` directory (`BZLogger.txt`, `BZOgreLogfile.log`, `openshim.log`).
The tests did not create a flashlight or mutate Ogre light state.

## Qualification needed before implementation

1. Repair/qualify a pilot fixture, including its terrain resource references,
   shader resources, and actual Lua execution. Capture a real player Person.
2. Observe world head transforms while standing, crouching, looking up/down,
   turning, walking and switching first/third person. Establish whether the
   world head is animated when hidden and whether its direction follows aim.
3. Validate released `createLight`, `attachObjectToBone`, and `destroyLight`
   ABI/export signatures. Prototype a head attachment with measured local
   direction/offset; compare its beam visually against player aim.
4. Prove cleanup across boarding, death, restart, load, mission exit, scene
   destruction, configuration changes, EXU handoff, and multiplayer entry.
   Do not rely solely on cached pointer equality or on Lua DeleteObject of the
   local player (previous pilot investigation found that inconclusive).
5. Reuse existing headlight colour/beam/falloff policy for the new light,
   with an explicit pilot enable setting, and allow Ogre to update a true bone
   attachment each render frame rather than tracking aim at 5 Hz.

Windows/GOG live pilot behavior remains unverified. Windows/Steam,
Linux/Steam/Proton and Linux/GOG/Wine are also unverified. No build was needed
for this documentation-only result; no release or deployment was performed.

## Follow-up: first-person gun hierarchy and animation

The user specifically requested verification of the first-person weapon's
attachment hierarchy. This follow-up inspected installed skeleton animation
tracks, independently inspected mesh vertex assignments, and decompiled the
released FP entity setup. No game launch was needed for these static findings.

### Actual visible mesh controller

| FP asset | Main vertices | Scope vertices | Sole assigned bone | Bone handle |
| --- | ---: | ---: | --- | ---: |
| `aspilo_fp.mesh` | 1843 | 8 | `asp21mg1` | 70 |
| `bspilo_fp.mesh` | 1843 | 8 | `bsp21mg1` | 70 |
| `sspilo_fp.mesh` | 1538 | 30 | `ssp21mg1` | 29 |

Every inspected vertex assignment has weight 1.0 to that one bone. There are
no head or hand assignments in these meshes. Thus a head attachment does not
follow the same animated transform as the visible first-person weapon.

Serialized hierarchy:

```text
asp21mg1 (root, gun controller)
  asp11GC1 (child, local position 0.10, 0.20, 0.00)
bsp21mg1 (root, gun controller)
  bsp11GC1 (child, local position 0.10, 0.20, 0.00)
ssp21mg1 (root, gun controller)
  ssp11GC1 (child, local position 0.15, 0.10, -0.05)
csp21mg1 (root, skeleton-only inspection)
  csp11GC1 (child, local position 0.21, 0.25, 0.00)
```

The `Bip01_Head` chain is separate, descending from neck/spine/pelvis.
The `*11POV` bone is another root, not a gun child. Matching bone names in
world and FP skeletons does not make them the same live bone instance.

### Animation evidence

In all four inspected FP skeletons (`aspilo`, `bspilo`, `sspilo`, TRO `cspilo`):

- `*21mg1` has 30 distinct local poses in each of `stand2Kneel` and
  `kneel2stand`, with both translation and rotation changing.
- `runForward` changes the gun transform: 30 distinct local poses for
  American/Black Dog, 26 for Soviet/Chinese (rounded to 5 decimals).
- `idle` contains a constant gun-local pose.
- `fireRecoilSniper` contains a constant gun-local pose: four identical keys
  for American/Black Dog, one key for Soviet/Chinese. Do **not** claim this
  particular clip proves visible gun recoil. Other engine/entity motion may
  contribute; this inspection did not establish that behavior.
- `*11GC1` has no animation track of its own and inherits its authored gun
  parent's transform unless the runtime changes the hierarchy.
- No separate reload clip was present in these skeleton animation inventories.
  Weapon-switch/reload coverage cannot be inferred from these clip names.

Skeleton parsing followed `OgreSkeletonSerializer.cpp:473–649` and
`OgreSkeletonFileFormat.h`. It accounts for the legacy bone chunk length
excluding the bone-name string, reads quaternion storage as x/y/z/w per
`OgreSerializer.cpp:386`, and consumed each file exactly to EOF. Mesh parsing
independently read submesh `0x4100` bone-assignment records.

### Released engine corroboration and recommendation

Ghidra GOG `0x0067E5A0` and its split continuation `0x0067E6A8` create the FP /
cockpit mesh entity and store it at bridge `+0xC0`, with skeleton `+0xCC`.
Both setup branches explicitly set bones whose fourth character is `2`
(`*21mg1`) to **not manually controlled**, with scale `(1,1,1)`. This
corroborates the authored gun animation rather than merely its bone name.

The two setup branches differ for `*11GC1`: the same-model branch detaches
and zero-scales bones whose fourth character is `1`, whereas the separate
cockpit-mesh branch recognizes `GC1` and stores it at bridge `+0xAC` for
object class 4. Therefore prefer attachment directly to the active FP
`*21mg1` with a measured local flashlight offset. Use GC1 only after verifying
the active runtime hierarchy; do not assume its on-disk parent survives all
model-loading paths. These decompilation fragments are evidence, not new
callable signatures or patch sites.

Confidence is high in **which bone controls the inspected first-person gun**.
This does not yet qualify creation/destruction of a persistent light, the
world-space lighting transform of the FP entity, first/third-person switches,
custom pilot assets, or visual aim alignment. Resolve the active FP entity
and bone by verified identity/name, not a hard-coded handle across factions.

### Asset identities (SHA-256)

```text
aspilo_fp.mesh      1a0abd09507957d6628f70aeb6115a02ec1b28fa4e64c32f054a749d998a3b30
bspilo_fp.mesh      87d585d2abe4636c9a4e6b7be53d1b712e652f035bbacd4db8cfa293f2ce6f8d
sspilo_fp.mesh      3945dafa6ba9def8b8ad6b3f554b494699e0b36574e728ccca2a568f78c351a5
aspilo_fp.skeleton  07a37c103f5cc16e5ae045a70d77bf0ecd44fea6a32b748730526770fd5d5cba
bspilo_fp.skeleton  a43206049c247eed0afffd226418156e1281cf964cdb6767dd5139b5f58b60cc
sspilo_fp.skeleton  e19d0a196fee77aa44c5b68c3b9b7a4e09992e7083659ee743228a8572482103
cspilo_fp.skeleton  0763580031a7525d8a3f647f30a28af1dcb5b1d623e86b8b04abf050dabe5006
```

---

## Runtime qualification and implementation — 2026-09-05 (later session)

The sections above are the pre-runtime static case. Everything below was
measured on a live pilot and supersedes the static recommendation where the two
disagree. The feature is **implemented and validated**.

### Fixture

The `pilot` addon still cannot be used: its terrain material set fails DX11
shader binding and the process closes on the first frame ("Attempted to render
to a D3D11 device without both vertex and fragment shaders"). The working
recipe is the README's Option A — deploy a fixture Lua as
`addon/lcbench/lcbench.lua` — plus two things that were not previously recorded:

- The mission can be selected from the command line, with **no shell
  navigation at all**: `battlezone98redux.exe lcbench.bzn`.
- The mission argument must be the **bare basename**. The engine copies it into
  a 16-byte buffer, so `addon/lcbench/lcbench.bzn` arrives as
  `addon/lcbench/l` (exactly 15 characters) and the load fails with
  `Could not load "addon/lcbench/l"`. `run_lcwalk_drive.ps1` already used the
  bare form; `launch_mission_live.ps1`'s default `mods/.../misn03.bzn` is 26
  characters and cannot ever have worked.

New harness files:

- `reverse_engineering/test_missions/pilot_anim_capture/pilot_flashlight_fixture.lua`
  — endless on-foot fixture: HopOut at T+3 s, then heartbeats forever. Unlike
  `pilot_test.lua` it never fails the mission, so there is time to attach a
  probe and to drive the view by hand.
- `reverse_engineering/run_pilot_flashlight_probe.ps1` — deploys the fixture,
  launches, attaches the Frida probe, restores `lcbench.lua` and `ogre.cfg`.
- `reverse_engineering/run_pilot_flashlight_validation.ps1` — deploys the built
  `winmm.dll`, enables the feature in the installed `openshim.ini`, launches,
  captures frames, restores both files by hash.

### Live probe result — the gun bone carries no aim

`reverse_engineering/probe_pilot_flashlight.js`, 40 samples at 1 Hz on a live
`Person` (`.?AVPerson@@`, local-player slot `0x00517AFC`), walking and looking
around. Bridge fields read as decompiled from `FUN_0067f599` / `FUN_0067e6a8`.

| Thing | Measured |
|---|---|
| bridge `+0xA8` (stock headlight) | **null for the entire time on foot** — no pilot skeleton has an `hlgt*` bone, so the engine never builds one |
| bridge `+0x94` world entity / `+0x98` node | `Ogre/MO7` (`aspilo.mesh`) on `Unnamed_404`, a child of `Ogre/SceneRoot` |
| bridge `+0xC0` FP entity | `Ogre/MO8` (`aspilo_fp.mesh`), attached to `Unnamed_405` — a **sibling** node, also under SceneRoot, holding a near-identical transform |
| FP bone `asp21mg1` (the gun) | derived position `(0, 0, 0)`, derived forward fixed at `(1, 0, 0)`; total movement across the whole capture `(0.057, 0.139, 0.082)` |
| FP bone `asp11GC1` | `(0, 0.2, 0.1)`, no track of its own |
| FP bone `asp11POV` | `(-0.185, 1.685, -0.06)`, orientation **identity in every sample** (quaternion spread exactly 0) |
| pilot node `Unnamed_404` orientation | full yaw range; pitch swept -2.96° to -14.10° **while the pilot stood still**; its -Z axis matched the walking direction exactly |

This overturns the static recommendation. The first-person gun bone is
essentially static in skeleton space — it sits at the skeleton origin (ankle
height in world terms) with a fixed axis-aligned rotation, and the ~14 cm it
does move is weapon bob. **The aim lives in the pilot's SceneNode, not in any
bone.** `asp11POV` does not carry it either.

So a TagPoint on `*21mg1` would have put the light at the pilot's feet, pointed
along a fixed axis, and would additionally go stale whenever the first-person
entity stops being animated. A node-attached light with a bone-derived local
offset — which is exactly what stock does for craft headlights at
`FUN_0067f599` — is both the correct aim frame and the ownership the engine
already uses.

### What was implemented

`src/patches/bzr_hooks.cpp`, "Player pilot flashlight (SinglePlayer tier)",
placed next to the stock headlight section and reusing its Ogre API table,
colour palette, rainbow cycling and `HeadlightFalloff` attenuation solver.

- Creates an `Ogre::Light` through `SceneManager::createLight()`, sets
  `LT_SPOTLIGHT`, the stock craft attenuation curve `(600, 1, 0.007, 0.0002)`
  re-solved for the configured peak brightness, `setCastShadows(false)`, a
  node-local position taken from the first bone whose name ends in the
  configured suffix (default `11POV`, searched in the FP skeleton then the
  world one), a node-local direction of `-Z` with an optional pitch, and
  attaches it to the pilot's own scene node.
- Destroyed through the **same** SceneManager that created it, and only while
  that manager is still the live one; otherwise the reference is dropped.
- Dropped without touching Ogre from `SceneManager::clearScene`,
  `destroyAllMovableObjects`, and the mission run-state seam — the scene frees
  the light with itself, so calling `destroyLight` there would run through
  freed memory.
- Destroyed on boarding (the local player object stops being a `Person`), on a
  pilot-object or node change, and if a modded pilot mesh ever carries an
  `hlgt*` bone and gets a stock engine light of its own.
- Registered in `g_FeatureRegistry` as a `SinglePlayer`-tier feature, so it
  stands down for the duration of a network game.
- Deliberately **not** gated on EXU. The stock headlight EXU stand-down exists
  because both write the same engine-owned light; this light is created by the
  shim and no script or ODF can address it.

Settings: `[SinglePlayer] PilotFlashlight`, `PilotFlashlightColor`,
`PilotFlashlightBeam`, `PilotFlashlightOffset`, `PilotFlashlightPitch`,
`PilotFlashlightBone`; the first three also appear on the in-game settings page
(`ShimSettingApplyGroup::PilotFlashlight`, which clears the config latch so the
row re-applies live). Diagnostics: `[Diagnostics] PilotFlashlightTrace` /
`OPENSHIM_TRACE_PILOT_FLASHLIGHT`.

### Blocker found on the way: the shim's per-frame world driver was gated off

The first three validation runs created no light and logged nothing, because
`RefreshPilotFlashlightState` never ran. Neither did `RefreshHeadlightState`.

`LegacyWorldUpdateRenderQueueHook` is the shim's only per-frame world driver —
it calls `RefreshHeadlightState`, `TickMpGateReconcile`,
`TickOpenShimEventLayer` and `RefreshVehicleSkinningDiagnosticsIfNeeded`. Its
vtable patch, "Legacy World Update RenderQueue VTable Hook", was listed in
`IsChunkExperimentPatchName` in `src/engine/patcher.cpp`, so
`ShouldEnableChunkExperiments()` gated it. That flag is bridged by
`openshim_env_config.cpp` to `[General] ChunkMeshes`, **which ships as 0**.

Consequence, on the shipped default configuration:

- the stock headlight feature never ran at all — no `[HEADLIGHT] refresh`, no
  colour/beam/visibility application, and no EXU stand-down;
- `TickMpGateReconcile` never ran, so every `SinglePlayer`-tier feature's
  periodic multiplayer reconcile was dead (each feature's own gate still
  checked the net id at its own call sites; only the periodic reconcile was
  missing);
- the native event-layer tick never ran from this path.

There is no `[SKIP]` line for a filtered patch, which is why this was invisible:
the entry is erased from the vector before the apply loop, so the log simply
never mentions it.

Fixed by removing that one patch from `IsChunkExperimentPatchName`. The other
two chunk entries stay gated. The hook body is safe with chunk features off —
only its chunk-batching branch is experimental, and every other path calls the
original through.

### Lifetime fixture, and two bugs it found

`reverse_engineering/test_missions/pilot_anim_capture/pilot_flashlight_lifetime.lua`
HopOuts at T+3, removes the pilot object at T+15, and fails the mission at
T+22. The middle step is the only route that reaches
`SceneManager::destroyLight`; a mission exit only reaches the forget path, so
without this fixture the destroy branch would have shipped unexecuted. It found
two real defects.

**A Lua-API trap worth recording separately.** `DeleteObject` is a *mission
callback* name, not a removal API. Defining `function DeleteObject(h)` at the
bottom of a mission script — which every harness in this folder does — assigns a
global that replaces whatever `DeleteObject` was, and the chunk executes top to
bottom, so by the time `Update` runs the name refers to the script's own no-op.
`pilot_test.lua` calls `DeleteObject(h)` in `TryDestroyPilot` after defining
that callback, so its `LIFETIME_DESTROY` step has always called itself. The
removal API is `RemoveObject`. This fixture captures both globals at the top of
the chunk and prefers `RemoveObject`; with `DeleteObject` it logged
`DELETE_PILOT ok=false`, with `RemoveObject` the pilot is actually removed.

**Bug 1 — the light was rebuilt into a world already being torn down.**
Leaving `RUN_STARTED` does not clear the scene immediately: the local player
object and its scene node stay readable for several seconds until `clearScene`
runs. The first lifetime run logged

```text
21:54:40.528  forgot  light=0x1EEF1C40 ... (left simulation)
21:54:40.757  created light=0x1EEF1E08 ... total=2
21:54:47.132  forgot  light=0x1EEF1E08 ... (clearScene)
```

— a second light built 229 ms after the world stopped running. Fixed with
`g_PilotFlashlightWorldRunning`, driven by
`PilotFlashlightNotifyMissionRunStateChanged` on both edges of the mission seam;
the refresh now forgets and returns while the world is not running. It defaults
to true so an install where the seam could not be hooked behaves as before.

**Bug 2 — `destroy FAILED`.** With the pilot object removed, destroying the
light threw. The usual reason this path runs is that the pilot GameObject went
away (boarding, death, a script removing it), and the engine destroys that
object's scene node with it — so the recorded node pointer is already freed. Two
corrections:

- The explicit `SceneNode::detachObject` before `destroyLight` was removed. It
  is unnecessary — `~SceneNode` calls `detachAllObjects`, which clears the
  light's parent pointer before the node dies, and `~MovableObject` detaches
  from the parent if there still is one — and it is the one call that
  dereferences a node the shim does not own.
- `PilotFlashlightLightLooksLive` now gates the destroy: a freed allocation
  stays readable for a while, so a null check proves nothing, but a live
  `Ogre::Light`'s vptr points inside `OgreMain.dll`'s image and a freed or
  recycled one's does not. If it fails the reference is dropped instead.

Removing the detach alone did **not** fix it; the failure stopped once the
liveness guard was added as well, and which of the two was decisive was not
isolated. Both are correct on their own merits, so the pair was kept. The
destroy now succeeds, reproducibly across two runs:

```text
[PILOTLIGHT] created   light=0x1D97ECF8 node=0x1D98E918 bone=asp11POV
             local=(-0.185,1.685,-0.060) dir=(0.000,0.000,-1.000) total=1
[PILOTLIGHT] destroyed light=0x1D97ECF8 (player is not on foot)
```

The `destroy FAILED` line now carries the SEH exception code, so a future
recurrence names the fault rather than just reporting failure.

### Validation

GOG Redux 2.2.301, `battlezone98redux.exe` SHA-256
`8D71F56C…3377413`; `winmm.dll` built `Release|Win32`, VC 14.44.35207.
Windowed (`BZR_FORCE_WINDOWED=1`). Frames captured with `PrintWindow`
(`PW_RENDERFULLCONTENT`) rather than `CopyFromScreen`: the game window cannot be
forced to the foreground while the operator is using the machine, and a screen
grab taken behind it captures the desktop wallpaper — which reads exactly like
"the feature does nothing". `SetForegroundWindow`, `BringWindowToTop` and an
`AttachThreadInput` borrow all failed; `PrintWindow` worked first try.

Observed:

```text
[PILOTLIGHT] Baseline enabled=yes colour=fixed(5.00,1.00,1.00) beam=focused
             bone=*11pov offset=(0.000,0.000,0.000) pitch=0.0 (SP-only)
[PILOTLIGHT] Pilot flashlight active (SP-only)
[PILOTLIGHT] eval not-on-foot player=0x02A0D720 class=.?AVWingman@@ ...
[PILOTLIGHT] eval eligible-creating player=0x02A0D320 class=.?AVPerson@@ node=0x1E946138 ...
[PILOTLIGHT] created light=0x1E2FF250 node=0x1E946138 bone=asp11POV
             local=(-0.185,1.685,-0.060) dir=(0.000,0.000,-1.000) total=1
[PILOTLIGHT] forgot light=0x1E2FF250 node=0x1E946138 (left simulation)
```

The captured frames show a red spotlight pool on the terrain **centred on the
player's reticle**, appearing only after the pilot is on foot.

`scripts/run_ini_tests.ps1` (132 settings, 23 + 50 checks) and
`scripts/run_ui_decor_tests.ps1` pass.

### Still unqualified

- Windows/Steam, Linux/Steam/Proton and Linux/GOG/Wine.
- Behaviour with a mod that gives a pilot mesh its own `hlgt*` bone — the code
  stands down for that case, but the case has not been built and run.
- Save/load across a mission save while on foot.
