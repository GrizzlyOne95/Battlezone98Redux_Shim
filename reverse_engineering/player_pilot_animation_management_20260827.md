# Player Pilot Animation Management — Controlled Investigation (2026-08-27)

**Branch:** `agent/pilot-animation-management` (worktree: `BZR-OpenShim`)  
**Stock-control follow-up:** `agent/pilot-fp-stock-control` (isolated worktrees: `BZR-OpenShim-fpcontrol` and `ExtraUtilities-fpcontrol`)
**Scope:** Determine how Battlezone 98 Redux manages the local player's pilot animation state on foot, prove observability/controllability via OpenShim/EXU, and recommend an architecture for custom first-person animations.  
**Test lab:** `lcbench` + purpose-specific harness `reverse_engineering/test_missions/pilot_anim_capture/`  
**Instrumentation:** `src/patches/pilot_fp_animation_trace.cpp` (v3 dual-target), `include/pilot_fp_animation_trace.h`, `reverse_engineering/PILOT_FP_ANIMATION_TRACE.md`
**Build:** GOG Redux 2.2.301, `battlezone98redux.exe` VA 0x401000, Ogre 1.10 `OgreMain.dll` SHA-256 `E5E6939…`
**Runtime Capture:** **EXECUTED — QUALIFIED**. The 32 s observational capture, independent FP-only/WORLD-only manipulation captures, and marker-synchronized visual capture completed on 2026-08-27. A distinct live `aspilo_fp.mesh` entity, its stock animation traffic, its shared `Person::Simulate` controller, and independent control of the visible first-person presentation are **PROVEN-RUNTIME**. The public stock-animation API follow-up completed on 2026-08-28: safe FP tracking plus EXU `TargetLocalFirstPerson` and stock `Play`/`Stop`/`Seek` are **PROVEN-RUNTIME**. Custom clip loading remains out of scope.

## 0. Runtime Qualification Result (2026-08-27)

This section is the authoritative captured result. Later sections retain pre-run design and static-analysis context; examples there are not evidence unless repeated here.

### 0.1 Environment and captures

- Branch: `agent/pilot-animation-management`, base commit `8d695d3e38d276f8717df8369b01bc1fe1a9b4db`, with the narrow instrumentation corrections described in §0.10 applied in the worktree. `main` was not merged.
- Game: GOG Battlezone 98 Redux 2.2.301, `battlezone98redux.exe` SHA-256 `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
- OpenShim: `Release|Win32`, `winmm.dll` SHA-256 `9456D64DCBE8ED49C0EA0DB5F30892DDE7B46393D8CEB0C34CEA0AB7EFD2A7F2`; build and deployed copies matched.
- Mission: the documented `addon/lcbench/lcbench.lua` overwrite, because the bundled standalone `pilot.bzn` still identifies `lcbench` internally and did not enter simulation. Engine-visible names (`lcbench`, `pitcfg`) remain at most eight characters.
- Windowing/shutdown: `BZR_FORCE_WINDOWED=1`; every launch dot-sourced `BZRHarness.ps1` and stopped via `Stop-BZRGame -Id`.
- Observational evidence: `tmp/pilot_anim_qualification_20260827/run1_observational/{openshim.log,BZLogger.txt,BZOgreLogfile.log}`.
- Manipulation evidence: `tmp/pilot_anim_qualification_20260827/run2_manip_fp/` and `tmp/pilot_anim_qualification_20260827/run2_manip_world/`.
- Visual evidence: screenshots captured in the qualification task, correlated with logs in `run3_visual_fp_thirdperson/` and `run3_visual_world/`; operator observation confirmed the external pilot kneeling while the FP-only-frozen view remained standing.
- Lifetime evidence: the manipulation captures used the corrected full 32 s Lua timeline, then `FailMission(GetTime()+1)`; the earlier unsupported local-player `GetIn` step was removed.

Configuration:

| Capture | `TracePilotFPAnimations` | `PilotFPAnimManip` | Scope | Target/mode |
|---------|--------------------------|--------------------|-------|-------------|
| Observational | 1 | 0 | n/a | n/a |
| FP manipulation | 1 | 1 | `fp` | `stand2Kneel` / `freeze` |
| WORLD manipulation | 1 | 1 | `world` | `stand2Kneel` / `freeze` |

### 0.2 World acquisition — PROVEN-RUNTIME

At `2026-08-27T17:17:22.860Z`, immediately after Lua `HOP_OUT` at `17:17:22.843Z`, the trace acquired:

```text
[FPAnim] target person=0x02A0D320 class=.?AVPerson@@
         entity=0x2D7A83E0 renderBridge=Person+0x0F0/Ogre+0x094 gen=1
```

Scene enumeration identified that entity as `name=Ogre/MO7`, `mesh=aspilo.mesh`, `skeleton=present`, `worldPilot=1`. Its observed bound inventory was `idle`, `idleParachute`, `landParachute`, `runForward`, `stand2Kneel`, `fireRecoilSniper`, and `kneel2stand`.

### 0.3 FP discovery and promotion — PROVEN-RUNTIME

Every plausible skeletal candidate in the first post-HopOut enumeration was recorded:

| Entity | Name | Mesh | Skeleton | Strict | `worldPilot` | Result |
|--------|------|------|----------|--------|--------------|--------|
| `0x27B7CE90` | `Ogre/MO1` | `avtank.mesh` | present | 0 | 0 | rejected |
| `0x27B6EEC8` | `Ogre/MO3` | `avtank.mesh` | present | 0 | 0 | rejected |
| `0x2D7A83E0` | `Ogre/MO7` | `aspilo.mesh` | present | 0 | 1 | excluded as known WORLD target |
| `0x2D7A9E58` | `Ogre/MO8` | `aspilo_fp.mesh` | present | 1 | 0 | promoted |

Promotion occurred at `17:17:22.912Z`:

```text
[FPAnim][FP] target acquired entity=0x2D7A9E58 mesh=aspilo_fp.mesh
  skeleton=present name=Ogre/MO8 gen=1 caller=0x69EF33E5
  rva=0x00000000 inMain=0 strict=1 worldPilot=0
```

The promotion caller is in the Ogre enumeration path rather than `battlezone98redux.exe`, so a main-module RVA is intentionally zero. Candidate discovery alone was not used as proof; the promoted target and its subsequent bound state traffic are the proof.

### 0.4 FP animation inventory — PROVEN-RUNTIME

The promoted FP entity exposed the same observed bound set as WORLD, with distinct `AnimationState*` values:

| Requested state | WORLD | FP | Result |
|-----------------|-------|----|--------|
| `idle` | observed | observed | same name, distinct states |
| `stand2Kneel` | observed | observed | same name, distinct states |
| `kneel2stand` | observed | observed | same name, distinct states |
| `fireRecoilSniper` | observed | observed | same name, distinct states |
| `jump` | not exercised | not exercised | **UNKNOWN**, not evidence of absence |
| `run*` | `runForward` observed | `runForward` observed | other directions not exercised |
| `landParachute` | observed | observed | same name, distinct states |

`idleParachute` was also observed on both. The Lua-only run had no supported jump action; `Goto` did not drive the local player during the scripted movement phase. Expected but unexercised states are not reported as captured.

### 0.5 Script correlation — PROVEN-RUNTIME

Log timestamps below are UTC and are actual captured transitions. The caller column records the state-selection/bind RVA; disabling uses the corresponding `...6F3/...7F3` site.

| Script event | Time | World animation | World caller RVA | FP animation | FP caller RVA |
|--------------|------|-----------------|------------------|--------------|---------------|
| `HOP_OUT` | `17:17:22.843` | `idleParachute` bound at `.861` | `0x0019DA40` | `idleParachute` bound at `.913` | `0x0019DC08` |
| `IDLE_WINDOW` | `17:17:23.844` | `landParachute` at `24.199`, `runForward` at `24.822`, `idle` at `24.941` | `0x0028070C` | same sequence at identical transition times | `0x0028080C` |
| `SET_SNIPER` | `17:17:28.844` | `idle` off; `stand2Kneel` on | `0x0028070C` | `idle` off; `stand2Kneel` on | `0x0028080C` |
| crouch/sniper phase | marker `17:17:30.845`; transition `30.778` | `stand2Kneel` off; `fireRecoilSniper` on | `0x0028070C` | same transition | `0x0028080C` |
| firing phase | `17:17:33.843` | no new transition observed | — | no new transition observed | — |
| movement phase | `17:17:36.844` | no new transition observed | — | no new transition observed | — |
| jump phase | `17:17:40.344` | no `jump` transition observed | — | no `jump` transition observed | — |
| `FINAL_IDLE` | `17:17:44.843` | `fireRecoilSniper` off; `kneel2stand` on | `0x0028070C` | same transition | `0x0028080C` |
| `TEST_COMPLETE` | `17:17:52.844` | `idle` active; no new transition | — | `idle` active; no new transition | — |

The fire/move/jump rows are negative observations about this Lua execution, not claims that those paths or clips do not exist.

### 0.6 Shared-controller classification — PROVEN-NATIVE + PROVEN-RUNTIME

Equivalent WORLD and FP transitions do **not** have equal immediate helper RVAs:

| Operation | WORLD RVA | FP RVA | Delta |
|-----------|-----------|--------|-------|
| disable prior state | `0x002806F3` | `0x002807F3` | `+0x100` |
| get/bind new state | `0x0028070C` | `0x0028080C` | `+0x100` |
| enable | `0x00280722` | `0x00280822` | `+0x100` |
| loop | `0x00280740` | `0x00280840` | `+0x100` |
| time position | `0x0028075D` | `0x0028085D` | `+0x100` |

This is evidence of separate per-entity apply helpers, not independent gameplay controllers. Bounded Rizin analysis found two 251-byte structural clones, `fcn.00680670` and `fcn.00680770`. Their only controller call sites are `0x0059E1CB -> 0x00680670` and `0x0059E245 -> 0x00680770`, sequentially in the established `Person::Simulate` function (`0x0059D340`), WORLD first and FP second. Runtime transitions occur WORLD then FP on the same timestamp.

**Classification:** one native `Person::Simulate` FSM drives two distinct Ogre entities through parallel WORLD and FP animation-application helpers. This is stronger and more precise than an `X == Y` call-site result.

### 0.7 Targeted manipulation and visual result — PROVEN-RUNTIME

The scope correction allowed attribution without adding a public API:

- FP-only run: `21,590` `[MANIP][FP]` records and `0` `[MANIP][WORLD]` records. `stand2Kneel` was sought to time `0` and its FP `addTime` was suppressed from `17:36:50.962Z` until mission transition at `17:37:15.962Z`.
- WORLD-only run: `1,704` `[MANIP][WORLD]` records and `0` `[MANIP][FP]` records. The separately addressed WORLD state was suppressed; the fresh run also reacquired `aspilo.mesh` and `aspilo_fp.mesh` with new process-local pointers.
- No second manipulation target was frozen, so attribution is specific to `stand2Kneel`.
- The FP-only state remained selected much longer than in the WORLD-only/control progression, proving that the FP `AnimationState` is live and participates in the animation-control path.

After the workstation was unlocked, the visual comparison was repeated. The FP-only capture was synchronized to the actual Lua `CROUCH_EXPECTED stage=3` marker at `2026-08-27T13:04:45.962-05:00`, not estimated from process launch time.

- FP-only freeze, first-person camera: the weapon/pilot presentation remained in the default standing/low pose even though Lua had selected `gsnipe` and the WORLD state was free to advance.
- Same FP-only run, third-person observation using Shift+F3: the world pilot was kneeling while first-person remained at the default standing pose.
- WORLD-only control: the first-person sniper viewmodel raised normally while only `[MANIP][WORLD]` was active.

This is outcome **B**: WORLD affects the external pilot while FP affects first person independently. The distinct FP `AnimationState` is the visible local first-person presentation driver.

### 0.8 Lifetime — partial PROVEN-RUNTIME

The unsupported local-player `GetIn` path was removed. At T+32 the Lua harness attempted `DeleteObject` and immediately scheduled `FailMission(GetTime()+1)`. Captured behavior:

1. Lua `DeleteObject` callback fired and cleared its script binding, but `GetPlayerHandle()` remained the same valid `Person`; deleting the local player this way does not remove the native/render object.
2. At `17:37:15.962Z`, the engine logged `Mission left simulation: ... RUN_WAS_FAILURE`.
3. No manipulation entries occurred after that mission transition.
4. On graceful teardown at `17:37:22.438Z`, WORLD cleared `gen=2` and FP logged `target released reason=world-pilot-cleared ... gen=2`.
5. The next fresh scripted launch acquired distinct WORLD and `aspilo_fp` pointers at `17:39:18.291Z` and resumed clean manipulation with no stale pointer.

Binding clear/release and fresh-launch reacquisition are **PROVEN-RUNTIME**. Same-process mission restart/reacquisition is **UNKNOWN** because Lua exposes mission completion but no direct local-player `GetIn` or restart primitive; no manual menu driving was substituted.

### 0.9 Final architecture and decision gate

- **PROVEN-RUNTIME:** a distinct live `aspilo_fp.mesh` Ogre entity exists while the local player is on foot.
- **PROVEN-RUNTIME:** WORLD and FP own distinct `Entity*` and distinct `AnimationState*` objects with matching observed stock animation names.
- **PROVEN-RUNTIME:** their transitions correlate frame-for-frame with the scripted player FSM timeline.
- **PROVEN-NATIVE:** one `Person::Simulate` controller invokes WORLD then FP through separate structural-clone helpers.
- **PROVEN-RUNTIME:** the manipulation gate can independently alter the FP or WORLD state stream.
- **PROVEN-RUNTIME:** FP-only manipulation changes the visible first-person pose independently of the WORLD pilot; WORLD-only manipulation does not block the first-person sniper pose.

The decision gate is **open** for the minimum stock-animation API: OpenShim should safely qualify/track the local FP entity, and EXU may add `TargetLocalFirstPerson` while reusing existing `Play`/`Stop`/`Seek`. Do not load custom clips yet; first prove stock animations through that public API.

### 0.10 Minimal corrections required for valid evidence

- Excluded the already-known WORLD entity from FP strict promotion; the original branch build incorrectly promoted `aspilo.mesh` before reaching `aspilo_fp.mesh`.
- Resolved/logged actual mesh names and skeleton presence.
- Propagated `_ReturnAddress()` from the hook wrapper so caller RVAs identify the game call site rather than the shim helper.
- Added test-only `OPENSHIM_PILOT_FP_MANIP_SCOPE=world|fp|both`, defaulting to `both`.
- Removed the project-local `register` preprocessor macro that prevented the branch from compiling with current MSVC STL headers.
- Replaced the invalid Lua local-player `GetIn` lifetime step with the full-timeline `DeleteObject` observation followed by supported `FailMission` transition.

No feature API, custom clip, or ExtraUtilities change was made in the 2026-08-27 qualification work; the separately authorized stock-control follow-up is documented next.

### 0.11 Public stock-animation control follow-up (2026-08-28)

This is the implementation and runtime qualification authorized by the §0.9 decision gate. It does not add custom clips, resource loading, a managed animation clock, or a parallel animation system.

#### Environment, build, and configuration

- OpenShim branch/base: `agent/pilot-fp-stock-control` from `87feae84`; `main` was not merged. Release Win32 `winmm.dll` SHA-256 `00B6D8AE7CDBE735DD99B8C7A20D0292568C38B0267E5074EE9ED764055CF6BF`.
- EXU branch/base: `agent/pilot-fp-stock-control` from `6d8cfd3`; runtime-qualified Release x86 `exu.dll` SHA-256 `36615786680C96423C3001673A481958340BB171CE9ACF2266D08562D968AE0D`. The final rebuild after changing only the capability-status text is `4E4E0A6B642A994CB90E20665B27BE054D6322AE4775CF1993F1C89AD103EE4A`.
- Deployed DLL hashes matched the isolated build outputs before launch.
- Game/process: GOG Redux 2.2.301, PID `43672`, windowed through `BZRHarness.ps1`; shutdown used `Stop-BZRGame -Id 43672`.
- Configuration: `TracePilotFPAnimations=1`, `PilotFPAnimManip=0`. All state changes below came from the public EXU API, not the OpenShim test manipulation gate.
- Lua: `reverse_engineering/test_missions/pilot_anim_capture/fpstock.lua`, deployed through the documented `lcbench.lua` overwrite. The engine-visible name remains `lcbench` (seven characters).
- Preserved evidence: `tmp/fp_stock_control_20260828/run1_public_api/` and `tmp/fp_stock_control_20260828/run2_lifetime_visual/`.

OpenShim now owns strict, process-lifetime FP qualification and exposes a narrow snapshot resolver. The resolver rechecks the current local world `Person`, SceneManager membership, the `_fp` pilot mesh allowlist, skeleton, `idle`, and `stand2Kneel`. EXU resolves this export afresh for each operation and never caches the returned Ogre pointer.

#### Public API matrix — PROVEN-RUNTIME

The first run began at local log time `07:19:45.371`. While the player was still in the vehicle, the target failed closed: `Has=false`, `Play=false`, and `GetInfo=nil`. `HopOut` occurred at T+2.001, the local pilot appeared at T+2.019, and OpenShim promoted `entity=0x2DCB6390`, `mesh=aspilo_fp.mesh`, `name=Ogre/MO8`, `gen=1`, `strict=1`, `worldPilot=0`.

At T+4.002, both WORLD and FP reported stock states `idle`, `stand2Kneel`, `kneel2stand`, `fireRecoilSniper`, `jump`, `runForward`, and `landParachute`. This is a direct public `Has` inventory and expands the earlier traffic-only inventory: `jump` is present even though gameplay did not select it in the original observational timeline.

| API event | Time | WORLD state | FP state | Result |
|-----------|------|-------------|----------|--------|
| FP `Play` + `Seek(0.5)` | T+5.004 | `stand2Kneel`: disabled, t=0.000 | enabled, t=0.500 | both calls `true`; FP changed only |
| FP hold | T+12.002 | disabled, t=0.000 | enabled, t=0.500 | WORLD remained untouched |
| FP `Stop(reset=true)` | T+12.002 | disabled, t=0.000 | disabled, t=0.000 | `true`; FP reset only |
| WORLD `Play` + `Seek(0.5)` | T+13.004 | enabled, t=0.500 | disabled, t=0.000 | both calls `true`; WORLD changed only |
| WORLD hold | T+17.000 | enabled, t=0.500 | disabled, t=0.000 | FP remained untouched |
| WORLD `Stop(reset=true)` | T+17.000 | disabled, t=0.000 | disabled, t=0.000 | `true`; WORLD reset only |
| FP recoil `Play` + `Seek(0.5)` | T+18.002 | disabled, t=0.000, len=0.033 | enabled, t=0.033, len=0.067 | `true`; FP clip selected independently |
| FP recoil `Stop(reset=true)` | T+19.000 | unchanged | disabled, t=0.000 | `true` |
| gameplay regain | T+21.002 | `idle` enabled, t=0.967, len=1.500 | `idle` enabled, t=0.967, len=1.000 | stock controller reclaimed both; no persistent override |

`Play`, `Stop`, and `Seek` are therefore **PROVEN-RUNTIME** for the qualified FP stock target. The half-time hold intentionally does not claim autonomous advancement; `nativeAdvancement` remains `unvalidated` and `managedClock=false`.

#### Visual independence — PROVEN-RUNTIME

The public API FP-only half-kneel was captured in first person during the `FP_VISIBLE_WINDOW_BEGIN` interval. In a separate replay of the same script, Shift+F3 was pressed during the identical FP-only hold: the external WORLD pilot remained visibly standing while the FP entity was held at normalized time 0.5. Together with the logged state snapshots, this repeats outcome **B** through the public API rather than the old instrumentation gate:

- FP targeting changes the visible first-person presentation without changing WORLD.
- WORLD targeting changes its own `AnimationState` without changing FP.
- The two target descriptors address dedicated render entities with independent states.

#### Same-process lifetime — PROVEN-RUNTIME

The replay button was exercised without ending PID `43672`, closing the previously unknown same-process case:

```text
gen=1 target acquired entity=0x2DCB6390 name=Ogre/MO8
gen=2 target released reason=world-pilot-cleared prevEntity=0x2DCB6390
gen=3 target acquired entity=0x312628E8 name=Ogre/MO16
gen=4 target released reason=world-pilot-cleared prevEntity=0x312628E8
gen=5 target acquired entity=0x27391608 name=Ogre/MO24
```

Each replay created a distinct FP pointer and advanced the generation. The Lua pre-HopOut checks continued to return safe false/nil results, subsequent operations resolved the new entity, and four complete runs ended without a stale-pointer manipulation or crash. Bindings were cleared on release and stock gameplay regained control before each mission transition.

#### Final classification and next boundary

- **PROVEN-RUNTIME:** strict local FP entity tracking survives destruction/recreation and same-process mission replay.
- **PROVEN-RUNTIME:** EXU `TargetLocalFirstPerson` resolves to the dedicated FP entity and fails closed when it does not exist.
- **PROVEN-RUNTIME:** stock `Play`, `Stop`, and `Seek` independently control FP without perturbing WORLD; WORLD behavior remains compatible.
- **PROVEN-NATIVE:** the underlying gameplay controller remains the shared `Person::Simulate` path documented in §0.6; the new API does not replace it.
- **UNKNOWN:** autonomous native advancement of an externally selected state without repeated `Seek` or gameplay ownership.

The stock-control implementation gate is complete. Custom clip/resource registration remains a separate future problem and is not authorized by this result.

---

## 1. Executive Summary

**PROVEN-RUNTIME** (from existing probe + art assets)  
- The local pilot's *logical* controller is `Person::Simulate` at GOG `0x0059D340` (fixed 2026-07-13; previously hooked wrong `0x004F4370` version-string builder). It owns a 4-state FSM (`Person+0x228` = 0..3) that selects among indices 0..11, driven by sniper-selected flag (`sig==0x534E4950`) and grounded flag (`*(Person+0x230)+0x114 &0x80`).

**STRONGLY SUPPORTED** (static + asset evidence)  
- Stock pilot skeletons contain the clips this FSM names: `stand2Kneel` (0), `kneel2stand` (1), standing `idle` (2), `fireRecoilSniper`/crouch idle (3), `runForward/Backward/Left/Right`, `jump` (11), `landParachute` (10), `idleParachute`, etc. verified by string hits in `aspilo.skeleton`, `bspilo.skeleton`, `sspilo.skeleton`, `cspilo.skeleton`.
- The Ogre presentation side is an `Ogre::Entity` reachable via the verified chain `main+0x00517AFC (userObject)` → RTTI `Person` → `Person+0x0F0` render bridge → `bridge+0x094` → Ogre `Entity` (`src/patches/pilot_fp_animation_trace.cpp:41-43`). This chain is shared with headlight/satellite/jump-snipe diagnostics and EXU's `GetRenderableEntity`.

**PROVEN-RUNTIME / PROVEN-NATIVE by §0 capture**
- A distinct live `aspilo_fp.mesh` entity (`Ogre/MO8`) exists beside the world `aspilo.mesh` entity (`Ogre/MO7`), with separate `AnimationState*` objects and matching observed stock state names.
- `Person::Simulate` drives WORLD and FP sequentially through separate helper functions. The remaining unknown is visual presentation control, not entity ownership or animation traffic.

**What this investigation delivered**  
- Enhanced the existing read-only trace to v2: caller RVA via `_ReturnAddress()`, transition filtering, `dt` throttling (≤2 Hz), 1.5 s inventory poll (`boundStates` + `hasAnimSet` existence), and a fail-closed manipulation gate (`freeze`/`forceWeight` behind `OPENSHIM_PILOT_FP_MANIP`). Code never alters stock behavior unless explicitly opted-in for isolated `lcbench` testing.
- **FP qualification pass (v3, this commit):** generalized the binding machinery to `TargetState` (`WORLD`/`FP`) sharing the same transition/throttling code (per §3 of the follow-up spec, no duplicated `RegisterBinding`/`LogBound*`). Added FP discovery via **verified enumeration seam** `SceneManager::getMovableObjectIterator("Entity")` (`OgreSceneManager.h:3316`, `OgreMain.dll` export `?getMovableObjectIterator@SceneManager@Ogre@@...` 5296) with `SceneManager` retrieval via global `0x00920EA0+0x08` (`bzr_hooks.cpp:2042`). `SceneManager::createEntity` is **not** used because the exe does not import any `createEntity`/`destroyEntity` overload (`dumpbin /imports` verified). Strict promotion requires `hasSkeleton` + `hasAnimationState("idle")` + `hasAnimationState("stand2Kneel")` (pilot vocabulary) + `worldIsPilot`, with `generation`-based lifetime and explicit `target acquired / released / reacquired` logging. Broad: `hasSkeleton`; strict: pilot anim set. Logs split `[FPAnim]` (WORLD, compat) vs `[FPAnim][FP]` + `[MANIP][WORLD]`/`[MANIP][FP]`.
- Built a deterministic Lua harness `pilot_anim_capture/pilot_test.lua` (32 s, 12 stages) emitting `[PILOTTEST] T+…` markers. The runtime correction removes unsupported local-player `GetIn`; after the complete marker it attempts deletion, then uses `FailMission` for the lifetime transition.
- Audited EXU's high-level `exu.animation` API (`ExtraUtilities/src/Game/AnimationApi.h`) and confirmed it already exposes sufficient primitives for GameObject-targeted control; `localFirstPerson` target remains intentionally fail-closed pending FP ownership validation (now gated on `g_Fp.entity` promotion).
- Provides a concrete reproduction procedure and a feasibility matrix (Options A–D) with a recommendation for a split OpenShim (low-level ownership) + EXU (Lua-facing) architecture behind a validated `aspilo_fp` resolver.

**Confidence key used below:** `PROVEN-RUNTIME`, `PROVEN-NATIVE` (disassembly/symbols), `STRONGLY SUPPORTED` (multiple independent static sources), `INFERRED`, `UNKNOWN`.

---

## 2. Previous Animation Instrumentation Reviewed

### 2.1 First-person pilot Ogre animation trace (PR #25)

- **Files:** `include/pilot_fp_animation_trace.h:1-19`, `src/patches/pilot_fp_animation_trace.cpp:1-905` (v1), `reverse_engineering/PILOT_FP_ANIMATION_TRACE.md:1-100`.
- **Design:** Worker thread (25 ms poll) waits for `OgreMain.dll`, resolves 6 retail Ogre exports by semantic decorated-name match (`getAnimationState@Entity`, `setEnabled@AnimationState`, `setLoop`, `setTimePosition`, `setWeight`, `addTime`), patches *exact* executable `E8 rel32` direct-call sites + IAT entries in `battlezone98redux.exe` only. Binds `AnimationState* → name` only when `Entity* self == g_TargetEntity` (current local `Person` entity). Logs only already-bound states. Fail-closed if no call/IAT site found.
- **Ownership model:** `GameObject::userObject` at `0x00517AFC`, RTTI `Person`, `Person+0x0F0 → bridge → +0x094 → Ogre::Entity`. Clears bindings on target change.
- **Logging:** `[FPAnim] target person=… entity=…`, `[FPAnim] entity=… anim=idle state=… bound=1`, `enabled/loop/time/weight/dt`.
- **What it proved:** That a trace scoped to the *world* `Person` entity can be installed safely without global noise, and that the binding-table size (64) and polling cadence are sufficient. It established the `Person+RTTI` gate that prevents AI/vehicle/world noise.

**Gap analysis (why v1 was insufficient):**

| Requirement (spec) | v1 coverage | Gap |
|---------------------|-------------|-----|
| Enumerate all AnimationStates on entity/skeleton | ❌ only logs states touched via `getAnimationState` | unknown clip inventory, lengths, loop defaults |
| Entity/Skeleton/SceneNode identity for FP vs TP | ❌ only entity pointer | cannot prove separate `_fp` entity |
| Weight/time/loop/blend ownership | ⚠️ logs but per-frame unfiltered | `addTime` storm, no transition vs steady-state distinction |
| Call site above Ogre | ❌ no `_ReturnAddress`/RVA | cannot prove `Person::Simulate` drives it |
| FP vs TP architecture | ❌ assumes same entity; notes negative-result test but no separate trace | `_fp.mesh` existence discovered but not traced |
| Manipulation experiment | ❌ read-only only | no controllability proof |
| Filtering | ✅ Person-only | ok, but no inventory throttling |

### 2.2 Ogre animation profiler v2

- **File:** `src/patches/ogre_animation_profiler.cpp` + `src/patches/ogre_animation_profiler/ogre_hooks.inl` etc., `reverse_engineering/OGRE_ANIMATION_PROFILER.md`.
- **Scope:** Observes `Entity::_updateAnimation` (public + protected `updateAnimation`), `Mesh::softwareVertexBlend`, `SceneManager::_renderScene`, and DX11/DX9 render subsystems. Reports aggregate FPS, animation calls, blends, top contributors — not pilot-AnimationState identity. Independent of pilot trace (`ProfileOgreAnimation` vs `TracePilotFPAnimations`).
- **Relevance:** Proves Ogre detour infrastructure is safe and that EXU-scale per-frame work can be bounded (atomic tables, bloom sets, fixed histograms). Pilot trace v2 reuses the same address-containment checks and fail-closed install pattern.

### 2.3 SDK v2 / read-only developer inspector

- **Files:** `include/BZROpenShim.h`, `src/engine/openshim_sdk_v2.cpp`, `include/openshim_sdk_v2.h`.
- **Capability:** `OpenShimGetApi` v2, `OpenShimDeveloperSnapshot`, `PollEvent` queue, `NativeUi` for OptionsParent overlay. Read-only, no pilot animation fields yet. Proves the event-queue pattern for exposing pilot animation snapshots without unsafe cross-boundary pointers.

### 2.4 High-level Ogre animation APIs in ExtraUtilities

- **File:** `ExtraUtilities/src/Game/GameObject.cpp` (`GetRenderableEntity`, `GetNamedAnimationState`, `TryGetAnimation*`), Lua surface `HasEntityAnimation`, `GetEntityAnimationInfo`, `SetEntityAnimationEnabled/Loop/Weight/Time`, and the newer `ExtraUtilities/src/Game/AnimationApi.h` (`exu.animation`).
- **Assessment:** See §14–15. Sufficient for GameObject-targeted experiments; FP path pending validation.

### 2.5 Declarative resolver & native UI

- `scripts/patches.json` + `src/engine/resolve_table.cpp` carry `identity` notes for each signature; `src/engine/native_ui.cpp` validates OptionsParent overlay. Pattern adopted for any new pilot-related signature.

**Conclusion:** Earlier instrumentation established the world target. The §0 runtime captures now prove FP ownership, observed inventory, native caller attribution, and independent visible first-person control.

---

## 3. lcbench Automation Harness

### 3.1 Design rationale

`lcbench` (`reverse_engineering/test_missions/live_combat_scaling/lcbench.*`, flat `earthgood` terrain, player-only `lcbench.bzn`) is the repo's controllable runtime lab. Rather than forking a new BZN (risking stale nav/terrain), the investigation reuses the same BZN and provides a **purpose-specific Lua** that can either overwrite `lcbench.lua` or deploy as a standalone `pilot.*` Instant Action.

### 3.2 Files

```
reverse_engineering/test_missions/pilot_anim_capture/
  pilot_test.lua   (26 kB, 600 lines, timeline state machine)
  pilot.bzn / .hg2 / .lgt / .mat / .trn / .ini  (copies of lcbench baseline, ini renamed to pilot)
  pitcfg.odf       (6-char ODF, timeline tuning, respects 8-char limit)
  README.md        (deployment + correlation guide)
```

ODF basename `pitcfg` is 6 chars — comfortably under the engine's 8-char limit cited in §5 of the spec and `BZR_LUA_AGENT_REFERENCE.md`.

### 3.3 Timeline & state machine

Implemented as an integer `stage` (0..13) advanced by `elapsed` vs `cfg.*At` plus pilot-existence gates. No `goto`/`::cont::`, no `io/os/debug`, `print()` only.

| Wall | Stage | Lua event | Prints | Instrumentation correlation |
|------|-------|-----------|--------|-----------------------------|
| 0.0 | 0 | `Start()` captures `GetPlayerHandle`, ODF, class, team, pos, weapon slots | `[PILOTTEST] START`, `INIT`, `PILOT_INFO` | baseline for `userObject` chain |
| 2.0 | 0→1 | `HopOut(GetPlayerHandle())` | `[PILOTTEST] HOP_OUT` | expect `[FPAnim] target person=… entity=…` within ~25 ms poll |
| ~3.0 |1→2| pilot detected (`IsPerson` true) | `PILOT_DETECTED`, `IDLE_WINDOW` | bindings appear, `idle` enabled/loop |
| 8.0 |2→3| `GiveWeapon(pilot,"gsnipe")` | `SET_SNIPER` | `stand2Kneel` enabled, `fsm 0→1` in jump-snipe probe |
|10.0|3→4| crouch observation window | `CROUCH_EXPECTED` | `fireRecoilSniper` steady, `stand2Kneel` completion → `fireRecoilSniper` |
|13.0|4→5| fire | `FIRE_WINDOW`, `FIRE_AT` / `exu.animation.Play("fireRecoilSniper")` | `time=0` reset, weight bump, `hasEnded` |
|16.0|6→7| move/strafe | `MOVE_WINDOW`, `Goto(dest)` + `Play("runForward")` | `runForward` vs manual WASD |
|19.5|8→9| jump | `JUMP_WINDOW`, manual Space + `Play("jump")` feasibility | `jump` (11), grounded flag clear, `landParachute` on touch |
|24.0|10→11| final idle, re-equip `handgun` | `FINAL_IDLE` | `kneel2stand` (1) → `idle` (2) |
|32.0|11→12| complete/lifetime transition | `LIFETIME_DESTROY`, `TEST_COMPLETE` | attempts `DeleteObject`, then schedules `FailMission` |

Each stage transition calls `DumpPlayerInfo()` which, when `exu.animation` is present, probes the anim list:

```lua
probeAnims = {"idle","runForward","runBackward","runLeft","runRight","stand2Kneel","kneel2stand","fireRecoilSniper","jump","landParachute","idleParachute"}
for _, n in ipairs(probeAnims) do
  if exu.animation.Has(h, n) then print(exu.animation.GetInfo(h, n)) end
end
```

### 3.4 Controllability vs manual input

| Action | Lua API | Automatable? | Harness behavior if not |
|--------|---------|--------------|--------------------------|
| HopOut | `HopOut(h)` `PROVEN` | YES | retry, then `MANUAL ACTION: press HopOut (E)` |
| Weapon equip | `GiveWeapon(h, weap, slot)` `PROVEN` | YES | logs mismatch, retries `GiveWeapon` without slot |
| Sniper crouch | FSM-driven via weapon selection `PROVEN` | SEMI | 3 s `CAPTURE WINDOW`, manual sniper-select reminder |
| Firing | `FireAt` needs enemy; `exu.animation.Play` `PROVEN` | SEMI | `Play("fireRecoilSniper")` + `FireAt(nearestEnemy)` else manual hold fire |
| Strafe/run | `Goto` + `Play("runForward")` `INFERRED` | SEMI | manual WASD |
| Jump | no stable `Jump` API `UNKNOWN` | MANUAL | `MANUAL ACTION: TAP JUMP (Space)` + `Play("jump")` for feasibility only |
| Lifetime transition | `DeleteObject` observation + `FailMission` | YES | documents that local-player deletion is retained, then exits the mission through supported Lua |

All stages are **reproducible**: re-running the mission with the same `pitcfg.odf` yields markers at the same wall times (±1 tick), so `[FPAnim]` logs can be diffed run-to-run.

### 3.5 Null-padded string handling

`GetOdf`, `GetPilotClass`, `GetWeaponClass`, `GetClassSig`, `GetBase` return fixed-width null-padded strings per `BZR_LUA_AGENT_REFERENCE.md`. Harness uses `TrimNullPad(s)` (`string.find(s,"\0")`) before every comparison — e.g., `TrimNullPad(GetOdf(h)) == "aspilo"`.

### 3.6 EXU mode

If `exu.animation` is absent, harness degrades gracefully (logs `EXU NOT present`). If present, it enriches each `DumpPlayerInfo` with `Has/GetInfo` inventory supplementing the native `[FPAnim] inventory` poll.

---

## 4. Pilot Object / Entity Lifecycle

**PROVEN-NATIVE (addresses) + STRONGLY SUPPORTED (chain):**

- **While in vehicle:** `GameObject::userObject` (`main+0x00517AFC`) → some `Craft`/`Vehicle` (RTTI ≠ `Person`). `PilotFP trace` reports no target. `GetPlayerHandle()` returns the craft handle. `HopOut` creates a new `Person` GameObject on foot (often `aspilo` family) adjacent to the craft. Pre-destruction vehicle properties must be cached before `DeleteObject` — after flagging destroyed only handle/objective name remains per `BZR_LUA_AGENT_REFERENCE.md`.
- **After HopOut:** `userObject` becomes a `Person` (validated via `vtable[-1] → TypeDescriptor+8` contains `"Person"` `src/patches/pilot_fp_animation_trace.cpp:181-230`). `Person+0x0F0` dereferences to a render bridge; `bridge+0x094` to an `Ogre::Entity*` whose vtable lies inside `OgreMain.dll` (verified via `OgreRuntime::ContainsAddress` + `ReadPointer` SEH). This is the **world pilot entity**.
- **Handle change:** `GetPlayerHandle()` now returns the new `Person` handle (different integer). The vehicle handle remains valid until recycled. The harness tracks `lastPilotHandle` vs `GetPlayerHandle()` and logs `PLAYER_HANDLE_CHANGED`.
- **Mission end:** Lua `FailMission` moves the mission out of simulation. The result screen retained the `Person`; graceful teardown then cleared WORLD and released FP at generation 2.

**What the trace now proves about lifecycle:**

- Pointer identity (`person=0x… entity=0x…` line) is logged on every target change. `g_LastInventoryEntity` resets on target change so inventory for the new entity is re-polled.
- The `Person` object's `Carrier` subset (`Person+0x1A0` per GOG correction) is *not* dereferenced by the pilot trace — that belongs to `ExtraUtilities/src/Game/GameObject.cpp` weapon-selection logic and `bzr_hooks.cpp` jump-snipe probe — but the harness's `GiveWeapon`/`GetWeaponClass` probes indirectly confirm the Carrier's `selectedMask` via visible ODF changes.

**Runtime result:** FP release on teardown and fresh-launch acquisition are proven. Whether the engine pools the FP entity across a same-process mission restart remains **UNKNOWN**.

---

## 5. Skeleton / Entity Architecture

### 5.1 Known meshes

Directory `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\BZ_ASSETS\common\models\`:

| Mesh | Size | Skeleton | Size |
|------|------|----------|------|
| `aspilo.mesh` | 883 kB | `aspilo.skeleton` | 2 091 392 B |
| `aspilo_fp.mesh` | 146 kB | `aspilo_fp.skeleton` | 2 082 251 B |
| `bspilo_fp.mesh` | 146 kB | `bspilo_fp.skeleton` | 2 082 061 B |
| `sspilo_fp.mesh` | 114 kB | `sspilo_fp.skeleton` | 1 259 484 B |
| `sspilo.mesh` | 873 kB | `sspilo.skeleton` | 1 261 039 B |

**STRONGLY SUPPORTED:** Dedicated `*_fp` first-person meshes exist, each paired with its own `_fp.skeleton`. Their sizes differ materially from world meshes (world 883 kB vs FP 146 kB), indicating distinct LOD/topology — not just a view flag.

**INFERRED:** The craft first-person cockpit is already known to use a dedicated FP entity with its own `setCastShadows(false)` and bounds policy (`reverse_engineering/craft_bounds_architecture_20260822.md` — `0x0067E5A0` = FP view entity builder). By analogy, the pilot FP view likely also owns a separate entity built from `aspilo_fp.mesh`.

**v2 handling:** The trace's optional `Entity::getMesh` / `hasSkeleton` resolver is best-effort (`FindOptionalExport`) — its existence is logged but not required for binding. The 1.5 s inventory poll additionally logs `hasAnimSet != null` which proves the target entity *is* skeleton-animated without needing the mesh name. A future step can hook `EntityFactory::createEntity` to capture the FP mesh name at creation time.

### 5.2 Skeleton sharing

`Ogre::Entity::mSkeletonInstance` may be shared (`mSharedSkeletonEntities`, `shareSkeletonInstanceWith`). The trace's `looksLikeOgreObject(ReadPointer(object)+offset)` checks guard against stale pointers, but does not assume sharing. EXU's `GetRenderableEntity` similarly re-resolves per call rather than caching `Entity*`.

### 5.3 SceneNode

Ogre's `Entity` is a `MovableObject` attached to a `SceneNode`. The trace does not log the node pointer — not needed for animation identity — but the node lifetime follows the entity (cleared on target change). A dedicated FP entity would be attached to a hidden/overlay scene node, which explains why world-entity animation might not be visible in FP.

---

## 6. Animation-State Inventory

### 6.1 Baseline from asset strings

Binary string scan of `aspilo.skeleton` etc. (per `jump_sniping_player_investigation_20260318.md`):

```
fireRecoilSniper, idle, idleParachute, jump, kneel2stand, landParachute,
runBackward, runForward, runLeft, runRight, stand2Kneel
```

Indices per toolkit/legacy decomp:

| Index | Clip | State | Loop |
|-------|------|-------|------|
| 0 | `stand2Kneel` | stand → snipe | false (one-shot) |
| 1 | `kneel2stand` | snipe → stand | false |
| 2 | `idle` (standing) | idle | true |
| 3 | `fireRecoilSniper` (crouch/snipe idle) | snipe idle | true¹ |
| 10 | `landParachute` | landing | false |
| 11 | `jump` | jump | false |
| — | `runForward/Backward/Left/Right` | locomotion | true |
| — | `idleParachute` | parachute idle | true |

¹ Porter maps index 3 to `fireRecoilSniper` because no distinct `crouch_idle` clip exists in shipped skeletons.

### 6.2 v2 runtime inventory

v2 logs two complementary inventories:

1. **Binding-table inventory** (always): every 1.5 s while pilot exists, logs each bound state's last `enabled/loop/weight` snapshot:

```
[FPAnim] inventory entity=0x... boundStates=3
[FPAnim] inv-bound anim=idle state=0x... enabled=1 loop=1 weight=1.000
[FPAnim] inv-bound anim=runForward state=0x... enabled=0 ...
```

2. **Ogre `AnimationStateSet` existence** (best-effort): calls `Entity::getAllAnimationStates` via resolved export under SEH; logs `animSet=0x… HAS_ANIM_SET` vs `null`. A non-null set proves the mesh *is* skeleton-animated. Full iteration via `AnimationStateSet::getAnimationStateIterator` is left as a follow-up — the binding table already enumerates the *actually-touched* clips, and iterating the full set without a stable iterator export risks false layout assumptions.

**UNKNOWN pending capture:** Per-clip `length`, `timePosition`, per-clip blend mode, and whether the `_fp` skeleton's clip list differs from the world skeleton's.

---

## 7. Gameplay-Event → Animation Correlation

### 7.1 Methodology

For each `[PILOTTEST] T+… EVENT`, the trace's `[FPAnim] entity=… anim=… enabled/weight/time caller=… rva=…` lines within ±100 ms are attributed to that event. `caller` RVA distinguishes `Person::Simulate`-driven changes from other subsystems.

### 7.2 Expected table (to be filled with live capture)

Below is the *strongly supported* hypothesis to be confirmed by running the harness; `PROVEN` vs `INFERRED` columns are explicit.

| Gameplay event (`[PILOTTEST]`) | Entity (`[FPAnim] entity=`) | Animation (`anim=`) | Enabled | Weight | Loop | Notes / Confidence |
|--------------------------------|-----------------------------|----------------------|---------|--------|------|---------------------|
| HopOut (2.0 s) | new Person `0x…` | `idle` | 1→1 | 1.0 | 1 | `PROVEN` logical; Ogre timing = `INFERRED` until capture |
| Idle stationary | world Person | `idle` | 1 | 1.0 | 1 | `PROVEN-NATIVE` FSM state 0 idle path |
| Walk forward (`moveAt`) | world Person | `runForward` | 1 | 1.0 | 1 | `PROVEN-NATIVE` FSM state 0 run branch |
| Walk backward | world Person | `runBackward` | 1 | 1.0 | 1 | `STRONGLY SUPPORTED` |
| Strafe left/right | world Person | `runLeft`/`runRight` | 1 | 1.0 | 1 | `STRONGLY SUPPORTED` |
| Turning if anim-driven | world Person | `run*` weight cross-fade or none | ? | ? | ? | `UNKNOWN` — may be root-motion vs skeleton |
| Sniper equip (8.0 s) | world Person | `stand2Kneel` (0) | 1→1 (`curAnim` 0) | 1.0 | 0 | `PROVEN-NATIVE` `Person+0x228` state 0→1 |
| Sniper crouch hold | world Person | `fireRecoilSniper` (3) | 1 | 1.0 | 1 | `PROVEN-NATIVE` state 2 |
| Uncrouch (sniper→handgun) | world Person | `kneel2stand` (1) | 1 | 1.0 | 0 then `idle` | `PROVEN-NATIVE` state 2→3→0 |
| Fire (normal) | world Person | `idle` or `run*` overlay? | ? | ? | ? | `INFERRED` — handgun fire may not have dedicated clip |
| Fire (sniper) | world Person | `fireRecoilSniper` weight pulse | ? | ? | ? | `INFERRED` — clip name suggests recoil |
| Jump (Space held) | world Person | `jump` (11) | 1 | 1.0 | 0 | `PROVEN-NATIVE` grounded=0 path |
| Parachute/airborne | world Person | `idleParachute` / `landParachute` (10) | 1 | 1.0 | ? | `STRONGLY SUPPORTED` |
| Landing (grounded=1) | world Person | `landParachute` then `stand2Kneel` if sniper | see §8 | — | — | `PROVEN-NATIVE` with fix at `0x59DEA5` |
| Enter vehicle | — | target cleared | — | — | — | `PROVEN-RUNTIME` probe logging |
| Weapon change (handgun↔sniper) | world Person | `stand2Kneel`/`kneel2stand` toggle | — | — | — | `PROVEN-NATIVE` |

**Distinguishing PROVEN from INFERRED:** Rows marked `PROVEN-NATIVE` are directly observed in the GOG disassembly (`0x0059D340` switch on `+0x228` at `0x59DDC0`, sniper `cmp [eax+0xC],0x534E4950` at `0x59D7D7`, `movzbl [ebp-0x352]` at `0x59DEA5`). Rows marked `INFERRED` for Ogre timing/weight will become `PROVEN-RUNTIME` after a single `pilot` run where each `[PILOTTEST]` marker is followed by the expected `[FPAnim] enabled/weight/time` line with caller RVA inside `Person::Simulate`.

### 7.3 Negative-result criterion

If during sniper crouch the world entity shows *no* `[FPAnim]` enabled transition for `stand2Kneel`/`fireRecoilSniper` yet the first-person view *is* visibly crouched, that is `PROVEN-RUNTIME` evidence of a separate FP entity. The harness is explicitly designed to make that outcome unambiguous by holding sniper for 3 s with no locomotion.

---

## 8. Sniper / Crouch Findings

**PROVEN-NATIVE (GOG `0x0059D340`):**

- Sniper detection: iterates `Carrier` slots (`Person+0x1A0 → Carrier`), for each `weapon[i] → weaponClass → sig` at `weaponClass+0x0C`; sniper iff `sig==0x534E4950` (`"SNIP"`). See `0x59D7BD` (`mov ecx,[ecx+0x1A0]`), `0x59D7D7` (`cmp dword [eax+0xC],0x534E4950`).
- Grounded test: `*(Person+0x230)+0x114 &0x80` — bit **set** = grounded, clear = airborne (`0x59DDF8` `and ecx,0x80; jne grounded`). Offset per `jump_sniping_crouch_fix_20260713.md:38-41`.
- FSM (`Person+0x228` switch, jump table `0x5A0A98`):
  - **State 0 (standing, `0x59DDE6`):** if airborne → jump/land anims (9/10/11); else if grounded:
    1. `if (jumpHeld)` → anim `0xB` (11, jump) ← *the 2026 regression*
    2. `else if (sniperSelected)` → anim `0` (`stand2Kneel`), `state=1`
    3. else → `idle`/`run*` (2/4/5/6/7)
  - **State 1 (`0x59E073`):** wait `animHandle==-1` → anim `3` (`fireRecoilSniper` crouch), `state=2`
  - **State 2 (`0x59E0AA`):** `if (!sniper)` → anim `1` (`kneel2stand`), `state=3`; else stay `3`
  - **State 3 (`0x59E0DD`):** wait → anim `2` (`idle`), `state=0`

**Regression & fix (PROVEN-NATIVE + PROVEN-RUNTIME once patched):**

Redux's grounded branch tested `jumpHeld` *before* `sniperSelected`, so holding jump (1) prevented the sniper-crouch path even after landing — legacy 1.5 tested sniper first. The patch at `0x59DEA5` (`66 8B 85 AE FC FF FF 38 E0 76 26` — `cmp al,ah; jbe 0x59DED6`) implements `jumpHeld <= sniperSelected` (both 0/1), fixing only the `jump&&sniper` case. Gated by `[SinglePlayer] JumpSnipeCrouch` + live net-id check (`0x009180D4==0`), verified by `ExpectedBytesMatchAt(0x59DEA5,…)`.

**Sniper/category nuance (STRONGLY SUPPORTED):**

The `weaponMask` / hardpoint system (`SetWeaponMask`, `GiveWeapon` mask bits 1,2,4,8,16) and the hardpoint-selection bias (`carrierExistingMask & selectedMask & enabledMask`) is exercised by howitzer/minelayer paths, but for `Person` the selection is the `Carrier.selected` bitfield. The toolkit's port mapping (`index 3 → fireRecoilSniper`) confirms no distinct `crouch_idle` asset — sniper idle *is* the crouched pose. Camera-position change is not a separate system; crouch *is* the `stand2Kneel` → `fireRecoilSniper` transition.

**Harness validation for §8:**

- `SET_SNIPER` (8.0 s) should be followed within 1–2 ticks by `stand2Kneel enabled=1 time=0` then `fireRecoilSniper enabled=1` once `animHandle==-1`.
- `FINAL_IDLE` after re-equipping `handgun` (24 s) should show `kneel2stand enabled=1` then `idle`.
- Landing with sniper (post-`JUMP`) should re-enter `stand2Kneel` if the `0x59DEA5` fix is active — the harness's jump-at-19.5 s + finalIdle at 24 s specifically brackets this regression.

---

## 9. Weapon / Firing Findings

**STRONGLY SUPPORTED / INFERRED:**

- `Person` ODF (`aspilo.odf:9-14`) defaults `weaponName1="handgun"` (`CANN` `shotDelay 0.3`, `ordName tracer`). `gsnipe.odf` (`CANN` `shotDelay 1.0`, `snipe.odf` ordnance `shotSpeed 1000`, `damageBallistic 25`) is the sniper weapon to equip via `GiveWeapon`.
- Firing while standing likely does **not** swap to a separate full-body clip; `idle`/`run*` continue while the muzzle/ordnance spawns. Sniper firing may pulse `fireRecoilSniper` weight or restart it — the harness's `FIRE_WINDOW` + `exu.animation.Play("fireRecoilSniper", restart=true)` isolates the clip's visibility independent of `Person+0x228`.
- Weapon change (`handgun` ↔ `gsnipe`) toggles the crouch state machine, not just an overlay: `GetWeaponClass(h,slot)` after `GiveWeapon` should change `sig` → sniper flag → FSM transition.

**Pending capture:** Whether `FireAt` on a `Person` injects a distinct `fire*` animation or merely spawns ordnance. The `dt` throttling (≤2 Hz) plus `weight` transition log will distinguish a one-shot weight pulse from a persistent enabled change.

---

## 10. Movement / Jump Findings

**PROVEN-NATIVE for FSM gating, STRONGLY SUPPORTED for Ogre:**

- Movement (`Go`/`Goto`/`Follow`) for `Person` is AI-task-driven (`PersonStraight`, `PersonGlide`, `PersonAttack` etc.) but the *animation* selection remains in `Person::Simulate` state 0's `idle` vs `run*` branch, keyed on locomotion velocity vs sniper/jump flags.
- Jump input is read into `[ebp-0x352]` (`jumpHeld`) and compared against sniper at `0x59DEA5`. Airborne path chooses jump/land anims (9/10/11). No stable Lua `Jump(pilot)` exists — harness treats jump as manual + `Play("jump")` feasibility probe.
- `Turn`/strafe if animation-driven would appear as `runLeft`/`runRight` weight cross-fade; may instead be root-motion yaw with no clip change (`UNKNOWN` until `MOVE_WINDOW` capture shows weight deltas).

**Lifecycle during jump/landing:** The `grounded` bit (`*(Person+0x230)+0x114 &0x80`) flips on contact; with the fix, sniper-selected landing correctly re-enters `stand2Kneel` rather than staying in jump. The harness's `JUMP_WINDOW` (19.5–23.5 s) deliberately spans airborne → landing → 2 s snipe-recovery.

---

## 11. First-Person vs Third-Person Architecture

**Question:** Do world-body and FP arms/weapon share the same `Ogre::Entity`/`SkeletonInstance`/`AnimationState`/`SceneNode` or are they separate?

**Evidence for separate `_fp` entity (STRONGLY SUPPORTED):**

- Art: `aspilo_fp.mesh` (146 kB) and `aspilo_fp.skeleton` (2 082 251 B) shipped alongside `aspilo.mesh` (883 kB) / `.skeleton` (2 091 392 B). Same for `bspilo_fp`/`sspilo_fp`. The naming convention mirrors craft FP meshes (`avtank` vs `avtank_fp`-style) which are known to use a **dedicated** FP entity built by `0x0067E5A0` (first-person view entity builder) with `setCastShadows(false)` and bounds `finite box` (`craft_bounds_architecture_20260822.md:122-231`).
- If the world entity were hidden in FP and its animation still drove the FP arms, the trace would continue to log `[FPAnim]` on the world entity while the FP view moves — the v2 “negative result” test would then be positive for shared ownership. If instead FP movement occurs with *no* world-entity `[FPAnim]` activity, that is proof of a separate FP entity.

**Evidence for shared state (INFERRED):**

- The `Person+0x0F0 → Ogre Entity` chain discovered for the world pilot is the *only* chain currently traced. The jump-snipe probe's `Person::Simulate` logging shows anim indices and FSM state without distinguishing FP vs TP — suggesting the FSM is singular. The FP view may therefore mirror the world entity's animation states, or the FP entity may copy/clone the world skeleton and receive the same `setEnabled` calls.

**What v2 now proves:**

- The inventory poll's `hasAnimSet` and binding logs are *exclusively* for the world entity. A capture where the tester visibly fires `gsnipe` in FP yet no `[FPAnim] enabled=1` appears for `fireRecoilSniper` on the world entity would **disprove** the shared-entity hypothesis and mandate a second resolver that finds the FP entity via the FP renderer (analogous to `craft_bounds_architecture`'s `0x0067E5A0`).
- Conversely, if manipulating the world entity's `stand2Kneel` weight via `exu.animation.SetWeight` visibly moves the FP arms, that is `PROVEN-RUNTIME` for shared presentation.

**Status:** **PROVEN-RUNTIME:** a separate `aspilo_fp.mesh` entity is instantiated and drives visible first-person presentation. **PROVEN-NATIVE:** `Person::Simulate` drives it after the WORLD entity through the parallel FP helper.

---

## 12. Native Call Chain / Controlling Game Subsystem

**PROVEN-NATIVE:** Redux animation selection *is* driven by `Person::Simulate` (`0x0059D340`, `case 0` etc.) → branch on sniper/grounded/jumpHeld → write `Person+0x228` (FSM), `Person+0x2A8` (`curAnim`), `Person+0x2AC` (`animHandle`), `Person+0x290` (`cycleState`) → ultimately call the Ogre `AnimationState` setters.

**How v2 proves the caller:**

- Each hook captures `void* retAddr = _ReturnAddress(); uintptr_t rva = retAddr - mainBase; bool inMain = MainModuleContains(retAddr)` and logs it. A `rva` in the `0x0059Dxxx` range (or more precisely `0x0019Dxxx` from image base `0x401000`) that falls inside the 22-byte prologue `55 8B EC 6A FF 68 D6 C1 84 00 64 A1 00 00 00 00 50 81 EC E8 06 00 00` is `Person::Simulate`. A `rva` near `0x0046B160` (`GameObject::GetObj`) etc. would implicate a different path.
- The existing jump-snipe probe already logs `fsm=%u→%u grounded=%s→%s anim=%ld→%ld animH=%d→%d … sniper=%s→%s` at `ChunkEffectSimulateHook` cadence, correlating FSM/grounded/anim to wall time; v2's caller RVA will align those logs with the exact Ogre setter call.
- Generic Ogre fall-through (e.g., `SniperInterface` or `PersonAttack::DoState`) would appear as a caller outside `0x0059D340`'s span.

**Who *doesn't* drive it (PROVEN-NATIVE):** `SniperInterface` and `SoldierAttack` were ruled out in `jump_sniping_player_investigation_20260318.md:151` — the sniper flag scan and FSM live in `Person::Simulate`, not in those task classes.

**Blend mode / weight:** The legacy `Person::Simulate` writes `curAnim` and lets `AnimObj_Start` (Redux VA `0x005617A0`, PDB `0x001617A0`) start the clip. Whether Redux uses `setWeight` for blending vs hard `setEnabled` toggle, and whether it calls `setLoop`/`setTimePosition`/`addTime` directly or via a `SkeletonInstance` wrapper, will be visible in the `[FPAnim] weight/time/loop` logs and their caller RVAs.

---

## 13. OpenShim Observability

**What is observable now (PROVEN-RUNTIME once enabled):**

- Binding (`getAnimationState` with `self==target`) — logged with caller RVA.
- `setEnabled`, `setLoop`, `setTimePosition`, `setWeight` — transition-filtered, with caller RVA.
- `addTime` — throttled (≤2 Hz, suppressed count summarized) with caller RVA.
- Entity/skeleton existence (`hasAnimSet` non-null) and bound-state inventory every 1.5 s.
- Lifecycle (`target person=… entity=…` / `target cleared`) at 25 ms poll.

**What is *not* observable yet (and why):**

- Full clip list (13+ names) without iterating `AnimationStateSet` — requires hooking `AnimationStateSet::getAnimationStateIterator` or calling it via resolved export and iterating under SEH. Left as follow-up; binding table already covers the *touched* set.
- Per-clip `length` / blend-mode flag — requires `AnimationState::getLength` or reading `AnimationSet` metadata; can be added via the same export-resolution pattern.
- Skeleton resource name (`aspilo_fp.skeleton`) — requires optional `getMesh` → `Mesh::getSkeletonName` round-trip; v2 resolves `getMesh`/`hasSkeleton` optionally but does not yet call `Mesh::getSkeletonName` (added as best-effort, never fail-closed).

**Noise / safety:**

- Filtered to relevant skeleton resource indirectly via the `Person+RTTI+Entity` gate — global Ogre noise is never entered.
- `dt` throttling prevents log storms; `enabled/loop` duplicated writes are suppressed.
- No object layout is guessed: `LooksLikeOgreObject(ReadPointer(entity))` ensures the vtable pointer falls in `OgreMain.dll` before any dereference; all `ReadPointer`/`GetModuleHandle` paths are SEH- or null-guarded.
- All hooks fail closed: if no exact `E8` call/IAT site exists for any export, that export's observer is not installed and the trace logs `observer unavailable`.

**Verification:** After enabling `TracePilotFPAnimations=1` and launching any pilot session, `openshim.log` should contain:

```
[FPAnim] enabled; read-only trace v2 waiting for OgreMain.dll…
[FPAnim] resolved Entity::getAnimationState … address=0x…
[FPAnim] observers active getState=… enabled=… loop=… time=… weight=… addTime=…; ownership=local Person Ogre entity
[FPAnim] enhanced trace v2: caller RVA, transition filtering…
[FPAnim] target person=0x… class=.?AVPerson@@ entity=0x… renderBridge=…
[FPAnim] entity=0x… anim=idle state=0x… bound=1 caller=… rva=… inMain=1
```

Absence of the target line while on foot would indicate the `Person+RTTI` gate failed — but that gate has already been validated in `bzr_hooks.cpp` jump-snipe probe.

---

## 14. Successful / Failed Manipulation Experiments

**Status: runtime state-manipulation captures complete; visual presentation proof remains unavailable.**

### 14.1 What the gate does

Behind `PilotFPAnimManip=1` (INI) or `OPENSHIM_PILOT_FP_MANIP=1` (env), the `addTime` / `setWeight` hooks for the named `AnimationState` on the *bound* pilot entity are diverted:

- `mode=freeze` (`g_ManipMode==Freeze`): `AnimationState::addTime` is **not** forwarded; a log line `[MANIP] Freeze addTime suppressed anim=… state=… dt=…` is emitted. The pose freezes at its current `timePosition`.
- `mode=forceWeight` (`ForceWeight`): `setWeight` is forced to `1.0`.

The diversion is checked only for already-bound states, logs with `[FPAnim][MANIP]`, and is dormant otherwise (`g_ManipMode==Disabled`). Restoration is implicit: disabling the env/INI and restarting the game restores stock behavior; the hook itself remains pass-through until process exit (matching the profiler's lifetime policy).

### 14.2 Candidate experiments (only one needs to succeed)

| # | Experiment | Hook | Expected visible effect | Proves |
|---|------------|------|--------------------------|--------|
| 1 | Freeze `stand2Kneel` `addTime` | `addTime` suppressed | crouch transition halts mid-blend | OpenShim can block time advancement |
| 2 | Force `idle` weight 1.0 | `setWeight` forced | prevents weight fade during run | OpenShim can override weight |
| 3 | `setTimePosition` to 0 | forward modified time | rewinds clip | OpenShim can seek |
| 4 | `setEnabled(false)` via `exu.animation.Stop` | tomorrow via EXU | disables clip | EXU can control enabled |
| 5 | `exu.animation.Play("stand2Kneel", restart=true)` stock clip | `GetNamedAnimationState` path | FP arms move independent of weapon | presentation decoupled from FSM |

Experiment 1 is implemented as `freeze` on `stand2Kneel` (default `PilotFPAnimManipAnim`). It is the narrowest proof: “OpenShim can control the local player's relevant animation state.” If that freeze affects **first-person visual** (arms/weapon frozen) it is `PROVEN-RUNTIME` for FP controllability; if it affects only third-person world view, it proves world-entity control and implies FP needs the separate `_fp` resolver; if it affects *neither*, either the wrong entity is being frozen or the clip is driven elsewhere.

### 14.3 Captured result

FP-only and WORLD-only `stand2Kneel` freeze runs completed; see §0.7. The marker-synchronized first-person capture and Shift+F3 third-person observation prove independently visible state streams.

### 14.4 Restoration & safety

- The gate is checked with `std::memory_order_acquire` and is only read inside the hook — no extra thread or timer.
- Manipulation suppression currently logs each diverted `addTime`; this intentionally produced large test-only logs and remains dormant outside the opt-in gate.
- Lifecycle: target change clears bindings, so a frozen state's suppression disappears on target release.

---

## 15. ExtraUtilities Applicability

### 15.1 Current surface (PROVEN from `ExtraUtilities/src/Game/GameObject.cpp` + `src/Game/AnimationApi.h`)

Low-level (`HasEntityAnimation`, `GetEntityAnimationInfo`, `SetEntityAnimationEnabled/Loop/Weight/Time`): each call re-resolves `GetRenderableEntity(handle)` under SEH, then `GetNamedAnimationState(entity, name)`, then the corresponding Ogre setter — never caching `Entity*`/`AnimationState*` between calls, never installing a frame hook.

High-level `exu.animation` (`Game/AnimationApi.h:1-290`):

```lua
exu.animation.Target(handle)        -- → {kind="gameObject", handle=lightuserdata}
exu.animation.GetCapabilities()     -- → {gameObjectTarget=true, localFirstPersonTarget=false, managedClock=false, nativeAdvancement="unvalidated", firstPersonStatus="aspilo_fp resolver requires live ownership validation"}
exu.animation.Has(target, name)
exu.animation.GetInfo(target, name) -- → enabled/loop/weight/timePosition/length + derived normalizedTime/atEnd
exu.animation.Play(target, name, {restart=true, loop=false, weight=1.0})
exu.animation.Stop(target, name, reset=false)
exu.animation.Restart(target, name)
exu.animation.SetEnabled/SetLoop/SetWeight(target, name, v)
exu.animation.Seek(target, name, timePosition)
```

`TargetKind::LocalFirstPerson` is **intentionally fail-closed** (`IsTargetSupported` returns false for `LocalFirstPerson`) until the `_fp` ownership experiment validates a stable resolver — the doc string says exactly this at `AnimationApi.h:35-40, 66-74`.

### 15.2 Is it enough for pilot control?

- **For the world pilot entity:** YES, the existing primitives already expose enough: `Has/GetInfo/SetEnabled/SetLoop/SetWeight/SetTime` plus `Play/Stop/Restart/Seek` cover every `AnimationState` method the trace observes. The `exu.animation.Play` restart/loop/weight sequence (`RawSetTime(0) → RawSetLoop → RawSetWeight → RawSetEnabled(true)`) matches the game's typical `setEnabled`/`setLoop`/`setWeight`/`setTimePosition` pattern.
- **For a dedicated FP viewmodel/body (Option C/D):** ALMOST. The API needs one additional *target resolver* — not a new animation primitive — that returns the FP `Entity*` for `LocalFirstPerson`. The playback primitives (`Play` etc.) then work unchanged. The resolver itself belongs in OpenShim (owns the `Ogre::Entity`/render-bridge chain and the `_fp` creation path); the Lua-facing verb belongs in EXU. This split is already the expected ownership per the spec's `My expectation is that low-level Ogre ownership belongs in OpenShim and optional Lua-facing control may belong in ExtraUtilities` — proven against the current code.

### 15.3 Minimum missing primitive

- **If FP is shared entity:** nothing — pilot is already controllable via `exu.animation` with a `GameObject` target for `GetPlayerHandle()` once the pilot is on foot.
- **If FP is separate `_fp` entity:** one new resolver `exu.animation.TargetLocalFirstPerson()` (or `Target{kind="localFirstPerson"}`) that internally calls the OpenShim-exposed `ResolveLocalFpEntity()` (to be added once the FP `SceneNode`/`Entity` path is validated). No new per-clip method is needed; speed control was deliberately deferred (see below).

### 15.4 Why no speed control yet

`ANIMATION_API.md` documents the deliberate omission: speed would require either a proven native Ogre time-scale (no such export is known stable) or an EXU-owned clock. Adding a second clock before confirming how Redux advances time (`addTime` per frame vs `setTimePosition` explicit) risks double-advancement. Once the live ownership/advancement experiment (§14) completes, a `SetSpeed` or `SetTimeScale` can be added behind the same `Target` without breaking `Play`.

### 15.5 Where Lua-driven custom FPS anim belongs

| Layer | Owns | Why |
|-------|------|-----|
| **OpenShim** | `Ogre::Entity`/`SkeletonInstance` resolution, lifetime (target refresh, binding table, `hasAnimSet`), optional `PilotFPAnimManip` diversion, future `aspilo_fp` creation capture | Already owns the `Person+0x0F0` chain, the `OgreMain.dll` export enumeration, and the fail-closed `E8`/`IAT` patcher. EXU must never dereference raw `Entity*` without OpenShim's verified chain. |
| **ExtraUtilities** | Lua verbs `Play/Stop/Seek/Set*`, `Target` abstraction, `GetCapabilities` probe, future `SetSpeed` + `LoadAdditionalSkeletonClip` | Already owns the SEH-guarded resolver and the `exu.animation` table that mission scripts import. |
| **Campaign Reimagined** | Mission timeline, weapon-loadout scripting, per-mission `PitFPAnimState` config | Consumes the API; does not own pointers. |

**Verdict:** Split architecture — **OpenShim owns the Ogre ownership/resolver and the low-level diversion; ExtraUtilities owns the Lua-facing control**. No parallel animation API is warranted — the existing `exu.animation` is fundamentally suitable, needing only the FP resolver once validated.

---

## 16. Custom FPS Animation Feasibility

### 16.1 Option matrix

|  | Description | Pros | Cons | Requires | Status |
|---|-------------|------|------|----------|--------|
| **A** | Override names/timing of existing `AnimationStates` (e.g., drive `stand2Kneel` at 2× speed, change `loop`/`weight`) | Small intervention, reuses stock skeleton | Limited to clips already in `aspilo_fp.skeleton` | Proves FP entity is the world entity or that the world entity drives FP | Feasible now for world entity |
| **B** | Load additional Ogre animations into the existing pilot skeleton (`Skeleton::addAnimation`, `SkeletonManager::load`) | Keeps single entity, adds e.g., `fpsReloadShotgun` | Needs toolchain: `.skeleton` binary format, resource group, skeleton compatibility (bone count/mask), safe runtime insertion | Ogre `Skeleton` resource APIs; validation that the `_fp` skeleton can be reloaded/relinked | Research needed; pilot harness can test `getAnimationState("fpsTest")` miss → loader path |
| **C** | Dedicated FP pilot/viewmodel entity (separate `aspilo_fp` mesh, its own skeleton, its own `AnimationStateSet`) | Complete freedom, independent weapon presentation, no risk to TP | More rendering/camera integration, weapon alignment, visibility/culling (`_fp` already `setCastShadows(false)` per craft precedent) | FP entity creation hook (like `0x0067E5A0` for craft) + material scheme handling | Strongest if FP is already separate; aligns with art assets |
| **D** | EXU/OpenShim animation-control API driven by Lua (`exu.animation.Play("sniper")` etc.) | Scriptable, data-driven, no native skeleton edit | Still needs A/B/C underneath; needs a managed clock if speed control required | `exu.animation` + resolver (A/C) + optional `SetSpeed` | Recommended as the *Lua surface* regardless of A/B/C underneath |

### 16.2 Evidence per option

- **A** is already implementable for the world entity via `exu.animation.SetWeight/SetLoop/Seek/Stop`. The pilot trace proves weight/time/enabled are observable; the dormant `freeze` gate proves `addTime` can be suppressed. A live run that freezes `stand2Kneel` and retains FP freeze would confirm A for FP if FP is shared.

- **B** is plausible but has open questions: Can `OgreMain.dll`'s retail `Skeleton` load an external `.skeleton` that was not in the initial `General` resource group? Does `Mesh::getSkeletonName` allow rebinding? The toolchain exists (`BZ98RBlenderToolKit` `bzportmodels.py` maps indices to clip names) but the runtime insertion path needs validation via `SkeletonManager::getByName` + `load` test. The pilot trace's `HAS_ANIM_SET` log would confirm whether the FP skeleton is shared or per-entity.

- **C** is the best fit *if* FP is already separate (asset evidence + craft precedent). The craft FP entity is built by `0x0067E5A0` with infinite bounds + `setCastShadows(false)` and `DynamicGeometry` stride-8 batching — the same pattern would apply to `aspilo_fp`. The one-time cost is camera-relative attachment and material visibility flags; the win is complete animation freedom and no risk of breaking TP.

- **D** is not an alternative to A/B/C but the intended *surface* for whichever is chosen. The spec's `exu.FPSAnimationPlay("sniper")` sketch maps directly onto `exu.animation.Play(LocalFPTarget, "sniper", {loop=false})` once the resolver exists. The high-level API intentionally avoids a frame hook; Redux/Ogre remains the clock unless a validated `SetSpeed` is added later.

### 16.3 Load-path and toolchain notes

- Asset format: Ogre 1.10 `Skeleton` binary (`.skeleton`) — already produced by `BZ98RBlenderToolKit`. Resource group for pilot is `General` (same as terrain) per `lcbench` observation; `TryResolveMaterial` patterns show `ResourceGroupManager` usage.
- Compatibility: Skeleton compatibility is bone-count/parent/hierarchy dependent. A `_fp` skeleton that differs from the world skeleton cannot be swapped without re-creating the entity.
- Safe insertion: Must occur while the target `Entity` is valid (between `target person=…` and `target cleared`), under SEH, without caching `AnimationState*` between calls — exactly the pattern `ExtraUtilities/GameObject.cpp` already follows.

### 16.4 Recommendation after runtime qualification

**Provisional recommendation:**

1. **Short term:** Add only the safe OpenShim FP target qualification/tracking needed for a production resolver, then expose EXU `TargetLocalFirstPerson` using the existing `Play`/`Stop`/`Seek` verbs. Prove stock animations through that surface.

2. **Medium term:** If FP-only manipulation visibly changes first-person presentation, add a safe OpenShim resolver for the now-proven `aspilo_fp` entity, expose it as `exu.animation.TargetLocalFirstPerson()`, and keep the existing playback verbs unchanged.

3. **Long term:** If new clips are needed beyond the 11 stock names, pursue **Option B** on the FP skeleton specifically — load additional `.skeleton` clips into the `_fp` skeleton via the resource-group path that the FP entity already uses, keeping TP untouched.

Visible FP control is now proven, so the minimum stock-animation targeting API is justified. Do **not** load or import custom clips until stock control succeeds through the intended public surface.

---

## 17. Recommended Implementation Architecture

```
                +------------------+        +-------------------+        +--------------------+
Lua mission     | Campaign Reimag|        | ExtraUtilities    |        | OpenShim            |
  pilot_test.lua|   (timeline)   |  exu   | exu.animation     |  C ABI | PilotFP trace        |
  ────────────► |  GiveWeapon    |──────► | Play/Stop/Seek    |──────► | ResolveLocalFpEntity |
                |  GetWeaponClass|        | Has/GetInfo       |        | Binding table        |
                |                |        | Target(FP) (new)  |        | hasAnimSet poll      |
                +------------------+        +-------------------+        | Caller RVA capture   |
                                                              | |       | Manipulation gate    |
                                                              | |       | (freeze/forceWeight)|
                                                              | |       +--------------------+
                                                              | |               |
                                                              | |   OgreMain.dll |  Entity.getAnimationState
                                                              | |   battlezone98redux.exe | Person::Simulate (0x0059D340)
                                                              | |
                                                              v v
                                                        Ogre::Entity  (world aspilo or aspilo_fp)
                                                        Ogre::SkeletonInstance
                                                        Ogre::AnimationState  (idle, runForward, stand2Kneel, fireRecoilSniper, jump, landParachute …)
                                                        SceneNode (world vs overlay)
```

**Ownership:**

- **OpenShim** (native): `userObject@0x00517AFC`, RTTI `Person`, `Person+0x0F0→+0x094` entity, target refresh (25 ms), binding table, export resolution (`getAnimationState`, `getAllAnimationStates` optional), caller RVA, inventory poll, manipulation diversion. Exports a stable `ResolveLocalFpEntity()` for EXU.

- **ExtraUtilities** (Lua bridge): `GetRenderableEntity` (SEH-guarded), `GetNamedAnimationState`, `exu.animation.*`, `TargetKind::LocalFirstPerson` once OpenShim resolver is validated. Never caches `Entity*` between calls. Future `SetSpeed` gated behind `nativeAdvancement` proof.

- **Campaign Reimagined** (content): `pilot_test.lua` timeline, `pitcfg.odf` tuning, per-mission weapon/mode selection, user-facing `PilotFPAnimManip` INI documentation.

**Data flow for custom FPS anim (after validation):**

1. Mission calls `local fp = exu.animation.TargetLocalFirstPerson()` (EXU asks OpenShim for FP entity).
2. `exu.animation.Play(fp, "fpsReload", {restart=true, loop=false})` → `RawSetTime(0) → RawSetLoop(false) → RawSetWeight(1) → RawSetEnabled(true)` on the FP entity.
3. Ogre advances the FP skeleton via `AnimationState::addTime` each frame; OpenShim's `addTime` hook observes but does not advance (unless frozen for debug).

No second clock, no parallel API, no asset duplication until a run proves the FP skeleton needs new clips (Option B).

---

## 18. Remaining Unknowns

| # | Unknown | Why it matters | How to resolve (one run) |
|---|---------|----------------|---------------------------|
| U1 | FP SceneNode / creation site (entity itself is now proven as `aspilo_fp.mesh`) | Needed for a production-safe resolver | Implement only the minimum qualification/tracking required by `TargetLocalFirstPerson` |
| U2 | Full clip list + per-clip `length` / `loop` default / blend mode | Custom anim must know naming and timing | Add `AnimationStateSet::getAnimationStateIterator` hook or call `getLength` per bound state; log via inventory |
| U3 | Weight vs enabled vs layering for locomotion (`idle` + `runForward` simultaneous?) | Movement blending | `Has` probe already enumerates simultaneous enabled states; `caller` RVA shows who sets weight |
| U4 | Turning anim-driven vs root-motion yaw | Determines whether custom strafe needs new clip | `MOVE_WINDOW` manual WASD + `runLeft`/`runRight` weight delta |
| U5 | **RESOLVED:** FP skeleton transition controls visible first-person pose independently | Opens stock-animation target API | Marker-synchronized FP-only capture + Shift+F3 external observation |
| U6 | Firing while moving: layering or hard switch | Reload anim layering design | `FIRE_WINDOW` while `runForward` enabled — log simultaneous `enabled` set |
| U7 | Jumping Lua automation (any `SetPosition`/`SetVelocity` that triggers `jump` clip) | Full automation vs one manual tap | Try `SetVelocity(y=+)` after `Play("jump")`; if no `Person::Simulate` jump path, document as manual-only |
| U8 | Same-process restart/return lifecycle (destroyed vs pooled FP entity) | Lifetime for a production resolver | Observe a real restart or player return; Lua `GetIn` is not a valid local-player transition |
| U9 | Weapon-change animation (is `GiveWeapon` sufficient to retrigger FSV or does `SetWeaponMask` needed?) | Reliable sniper toggle | Harness already tries both `GiveWeapon(...,0)` and `GiveWeapon(...)` without slot; log which triggers `stand2Kneel` |
| U10 | Can `Ogre::SkeletonManager::load` inject a new clip (`fpsTest`) at runtime without restart? | Option B viability | After `HAS_ANIM_SET` proof, attempt `Entity::getAnimationState("fpsTest")` — if null, try `SkeletonManager::getByName("aspilo_fp.skeleton")` load path |

U5 is resolved. U1 remains production-resolver work; U8 remains a same-process lifetime hardening case and does not invalidate the observed FP target/control result.

---

## 19. Exact Reproduction Procedure

### 19.1 Prerequisites

- GOG Redux installed at `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux` (verified `battlezone98redux.exe` + `OgreMain.dll` SHA-256 `E5E6939…`).
- Branch `agent/pilot-animation-management` built **Release | Win32** (`BZROpenShim.sln` → `bin/Release/winmm.dll`), deployed as `winmm.dll` + `winmm.ini` is not needed — `openshim.ini`.
- `ExtraUtilities` built with `Game/AnimationApi.h` (ships `exu.animation`; no extra build step if already deployed).
- World assets `pilot.bzn/.hg2/.lgt/.mat/.trn/.ini` present in either `addon/lcbench` (overwriting) or `addon/pilot` (standalone) per `pilot_anim_capture/README.md`.

### 19.2 Deploy the harness

**Option A (overwrite lcbench):**

```powershell
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot_test.lua   "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\lcbench\lcbench.lua" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pitcfg.odf       "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\lcbench\pitcfg.odf" -Force
# lcbench.bzn/.hg2/.lgt/.mat/.trn/.ini already present in addon/lcbench from a prior lcbench setup
```

**Option B (standalone pilot):**

```powershell
New-Item -ItemType Directory -Force -Path "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot" | Out-Null
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot.bzn        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.bzn" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot.hg2        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.hg2" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot.lgt        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.lgt" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot.mat        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.mat" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot.trn        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.trn" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot.ini        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.ini" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pilot_test.lua   "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pilot.lua" -Force
Copy-Item reverse_engineering/test_missions/pilot_anim_capture/pitcfg.odf       "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\addon\pilot\pitcfg.odf" -Force
```

The completed qualification used Option A. The bundled standalone `pilot.bzn` retained internal `lcbench` mission metadata and did not enter simulation, so Option B is not currently a valid runtime route without rebuilding that BZN.

### 19.3 Configure OpenShim

`openshim.ini` (adjacent to `battlezone98redux.exe`):

```ini
[Diagnostics]
TracePilotFPAnimations=1
; PilotFPAnimManip is dormant by default and only needed for the single manipulation run:
; PilotFPAnimManip=0
; PilotFPAnimManipAnim=stand2Kneel
; PilotFPAnimManipMode=freeze
```

Environment overrides (take precedence over INI):

```powershell
$env:OPENSHIM_TRACE_PILOT_FP_ANIMATIONS=1
# $env:OPENSHIM_PILOT_FP_MANIP=1   # only for the isolated manipulation run
```

### 19.4 Run

1. Launch the game (Instant Action → `lcbench` or `pilot`). Use windowed for stability (`$env:BZR_FORCE_WINDOWED=1`) unless timing is being measured.
2. If the harness is on `lcbench`, the map title still reads “OpenShim Live Combat Benchmark” (the BZN name) — the Lua is `pilot_test.lua`.
3. Observe the on-screen log? No — markers go to the game log via `print()` and appear in `openshim.log` (and potentially `exu.log`).
4. For the Lua-only qualification, do not supply manual movement, fire, or jump input. Unexercised phases remain explicit negative observations.
5. Remain in the mission for 32 s until `[PILOTTEST] TEST_COMPLETE`; the lifetime build then schedules mission failure one second later.

### 19.5 Collect evidence

`openshim.log` (adjacent to exe or in `logs/`) must contain correlated pairs:

```
[PILOTTEST] T+2.000 HOP_OUT
[FPAnim] target person=0x… class=.?AVPerson@@ entity=0x… renderBridge=…
[PILOTTEST] T+8.000 SET_SNIPER
[FPAnim] entity=0x… anim=stand2Kneel state=0x… bound=1 caller=0x… rva=0x… inMain=1
[FPAnim] entity=0x… anim=stand2Kneel state=0x… enabled=1 caller=… rva=… inMain=1
[FPAnim] inventory entity=0x… boundStates=…
```

`exu.log` (if ExtraUtilities installed) may duplicate the `[PILOTTEST] ANIM has=…` probes.

### 19.6 Manipulation run (only after baseline capture)

1. Set `PilotFPAnimManip=1` + `PilotFPAnimManipAnim=stand2Kneel` + `PilotFPAnimManipMode=freeze` (or `OPENSHIM_PILOT_FP_MANIP=1`). Use `OPENSHIM_PILOT_FP_MANIP_SCOPE=fp` and `world` in separate runs.
2. Repeat §19.4. During `CROUCH_EXPECTED`, the crouch blend should visibly freeze mid-transition and `openshim.log` should contain `[MANIP] Freeze addTime suppressed …`.
3. Observe whether the freeze appears in **first-person** (arms/weapon frozen) vs **third-person** (external cam) vs both/neither — that outcome determines FP vs TP §11.
4. Restore `PilotFPAnimManip=0` before any non-lcbench play.

### 19.7 Validation steps

From repo root:

```powershell
.\scripts\run_ogre_profiler_tests.ps1
.\scripts\run_ini_tests.ps1
# Release | Win32 build:
msbuild BZROpenShim.sln /p:Configuration=Release /p:Platform=Win32
git diff --check
```

---

## 20. Files Changed

| Path | Action | Why |
|------|--------|-----|
| `src/patches/pilot_fp_animation_trace.cpp` | MODIFY | Correct FP promotion, mesh/skeleton identity, caller attribution, and independent test-only WORLD/FP manipulation scopes |
| `BZROpenShim.vcxproj` | MODIFY | Remove the project-local `register` macro that breaks current MSVC STL compilation |
| `include/pilot_fp_animation_trace.h` | MODIFY | Document v2 extensions, manipulation gate |
| `reverse_engineering/PILOT_FP_ANIMATION_TRACE.md` | MODIFY (v2 doc) | Caller RVA, filtering, inventory, manipulation gate, harness correlation |
| `reverse_engineering/test_missions/pilot_anim_capture/pilot_test.lua` | MODIFY | Purpose-specific 32 s harness; corrected unsupported local-player `GetIn` to deletion observation + mission-failure lifetime transition |
| `reverse_engineering/test_missions/pilot_anim_capture/pitcfg.odf` | MODIFY (6 chars) | Move lifetime transition to the completed 32 s boundary |
| `reverse_engineering/test_missions/pilot_anim_capture/pilot.bzn/.hg2/.lgt/.mat/.trn/.ini` | CREATE (copies of lcbench baseline) | Flat `earthgood` lab for standalone Instant Action `pilot`; `pilot.ini` retitled |
| `reverse_engineering/test_missions/pilot_anim_capture/README.md` | MODIFY | Correct lifetime behavior and remove unsupported local-player re-entry claim |
| `reverse_engineering/player_pilot_animation_management_20260827.md` | MODIFY | Add the captured runtime result, evidence tables, limitations, and decision gate |

**Not changed (intentionally):**
- `src/patches/ogre_animation_profiler.cpp` — left untouched; pilot trace is independent of `ProfileOgreAnimation`.
- `ExtraUtilities/src/Game/AnimationApi.h` — not modified; audit (§15) shows it is already sufficient pending the FP resolver.
- `reverse_engineering/test_missions/live_combat_scaling/lcbench.lua` — left untouched to preserve the benchmark; pilot harness is provided as a drop-in copy rather than a forced merge.

**Branch hygiene:**

- Work is on `agent/pilot-animation-management`, not `main`. No commit to `main` was made per the task's source-hygiene rule.
- No logs/dumps/binaries/game files were committed; only source/harness/docs.
- `git diff --check` passes (no whitespace errors) after the edits (validated in §19.7).

---

## Confidence Summary

| Claim | Confidence | Evidence |
|-------|------------|----------|
| Pilot FSM is `Person::Simulate` at `0x0059D340` family, `+0x228` state 0..3 | PROVEN-NATIVE | Disassembly bytes, jump table `0x5A0A98`, sniper `0x59D7D7` |
| Grounded flag `*(Person+0x230)+0x114 &0x80`, jumpHeld at `[ebp-0x352]` | PROVEN-NATIVE | `0x59DDF8`, `0x59DEA5` |
| Stock clips `stand2Kneel`/`kneel2stand`/`idle`/`fireRecoilSniper`/`jump` exist | PROVEN-RUNTIME (asset strings) | `aspilo.skeleton` hits |
| World pilot entity via `userObject@0x00517AFC → Person+0x0F0→+0x094 → Ogre::Entity` | PROVEN-RUNTIME (shared with other probes) | `pilot_fp_animation_trace.cpp:41-43`, `bzr_hooks.cpp` jump-snipe probe |
| Dedicated FP meshes `*_fp.mesh/.skeleton` exist | PROVEN-RUNTIME (art) | `BZ_ASSETS/common/models/` dir listing |
| Distinct live `aspilo_fp.mesh` entity and matching stock state traffic | PROVEN-RUNTIME | §0 observational capture |
| Ogre `AnimationState` mutations for sniper crouch are `stand2Kneel`/`fireRecoilSniper`, driven by WORLD/FP helpers called sequentially from `Person::Simulate` | PROVEN-RUNTIME + PROVEN-NATIVE | §0.5–0.6 capture and bounded Rizin analysis |
| `exu.animation` sufficient for GameObject pilot control | STRONGLY SUPPORTED | `GameObject.cpp` SEH resolver + `AnimationApi.h` `IsTargetSupported` |
| Custom FPS architecture should be split OpenShim (resolver) + EXU (Lua verbs) with dormant manipulation gate | STRONGLY SUPPORTED | Ownership already split; no parallel API needed |

---

## References

- `reverse_engineering/jump_sniping_crouch_fix_20260713.md` — GOG `Person::Simulate` `0x0059D340` fix at `0x59DEA5`.
- `reverse_engineering/jump_sniping_player_investigation_20260318.md` — legacy `Person::Simulate` decomp, clip index mapping, carrier/weaponMask layout.
- `reverse_engineering/craft_bounds_architecture_20260822.md` — craft FP entity builder `0x0067E5A0`, `setCastShadows(false)`, bounds policy precedent for `_fp`.
- `reverse_engineering/OGRE_ANIMATION_PROFILER.md` — Ogre hook lifetime/bounded-alloc pattern.
- `ExtraUtilities/docs/ANIMATION_API.md` — `exu.animation` design rules, `localFirstPerson` deferred status.
- `ExtraUtilities/docs/BZR_LUA_AGENT_REFERENCE.md` — Lua 5.1 constraints, `HopOut`/`GiveWeapon`/`FireAt`/`GetIn`/`Goto`, null-padded getters, `DeleteObject` lifetime.
- `include/BZROpenShim.h` / `src/engine/openshim_sdk_v2.cpp` — SDK v2 event queue, `OpenShimGetApi`.

---
*End of report. Runtime qualification is complete. Next step: minimum safe OpenShim FP tracking plus EXU `TargetLocalFirstPerson`, proving stock animation control before any custom clip work.*
