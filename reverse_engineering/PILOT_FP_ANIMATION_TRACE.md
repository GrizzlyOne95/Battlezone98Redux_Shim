# Pilot first-person Ogre animation trace

This diagnostic records the Ogre animation-state activity associated with the local on-foot `Person`. It is observation-only by default and is intended to establish the exact stock first-person animation behavior before OpenShim attempts any viewmodel animation override.

The trace deliberately does **not** identify the target by mesh/resource name. Redux already has a verified local-player/render-object chain, so the observer follows the player object directly and ignores every other Ogre entity.

## Configuration

The trace ships **disabled**. It was enabled by default while this path was
being characterised; that default was reverted on 2026-08-30, after the
scene-graph walk it drives was found to kill the process on scene teardown
by calling through a destroyed `Ogre::SceneManager`. The walk is now guarded,
and it no longer runs at all unless this key is set.

```ini
[Diagnostics]
TracePilotFPAnimations = 1
```

Set the key to `1` to enable it. The process-environment compatibility override is:

```text
OPENSHIM_TRACE_PILOT_FP_ANIMATIONS=0|1
```

A process environment value takes precedence over the INI key.

This setting is independent of `ProfileOgreAnimation`. Enabling the pilot trace does **not** enable the general Ogre animation/render overhead profiler or its DX11 counters.

## Target ownership

On a version-qualified Redux executable, OpenShim resolves the target as:

```text
GameObject::userObject
        |
        +-- require MSVC RTTI containing "Person"
        |
        +-- Person + 0x0F0 -> render bridge
                              |
                              +-- +0x094 -> Ogre::Entity
```

The `userObject` is the current local player-controlled object. While the player is in a vehicle it is not a `Person`, so the target is cleared and no vehicle animation states are tracked. On foot, only the Ogre entity belonging to that local `Person` is accepted.

The `Person + 0x0F0 -> +0x094` render chain is already used by OpenShim/EXU diagnostics to reach a GameObject's Ogre entity. This trace adds the local-userObject and Person-RTTI requirements so unrelated units, AI pilots, vehicles, and world objects cannot enter the binding table.

This first capture also validates an important remaining assumption: that the established local Person Ogre entity is the entity receiving the visible first-person animation-state operations. If visible first-person animation changes occur but no corresponding `[FPAnim]` state activity is captured, that is a useful negative result indicating Redux owns a separate first-person Ogre entity that must be traced from the Person renderer.

## What is traced (v1 baseline)

OpenShim waits for the retail `OgreMain.dll`, resolves the relevant Ogre exports by semantic decorated-name matching, and observes only exact executable call/IAT sites for:

- `Ogre::Entity::getAnimationState`
- `Ogre::AnimationState::setEnabled`
- `Ogre::AnimationState::setLoop`
- `Ogre::AnimationState::setTimePosition`
- `Ogre::AnimationState::setWeight`
- `Ogre::AnimationState::addTime`

When `Entity::getAnimationState(name)` is called with `self` equal to the current local Person's target Ogre entity, OpenShim binds the returned `AnimationState*` to that animation name. Mutation hooks log only already-bound states.

The target is refreshed continuously. If the local Person/entity changes, all state bindings are cleared before the new target is published.

## v2 enhancements (2026-08-27)

v2 retains v1's read-only-by-default, fail-closed semantics and adds gated diagnostic extensions needed for the controlled pilot experiment:

### Call-site attribution

Each bound-state mutation now logs:

- `_ReturnAddress()` of the caller
- RVA (`caller - mainModuleBase`) and `inMain` flag

```text
[FPAnim] entity=0x... anim=stand2Kneel state=0x... enabled=1 caller=0x... rva=0x00ABCDEF inMain=1
```

An `rva` inside the executable and adjacent to known `Person::Simulate` addresses (`0x0059D340`, grounded branch `0x0059DEA5`, sniper signature check `sig==0x534E4950` at `0x59D7D7`) proves that the pilot FSM drives the clip. A caller outside the main module or at an unrelated RVA points to a separate controller or overlay.

### Transition filtering & throttling

- `enabled`/`loop` are logged only on transition (no duplicate spam).
- `weight` is logged only when delta > 0.001.
- `dt` (`addTime`) is throttled to at most one log per 500 ms per state; suppressed frames are summarized:

```text
[FPAnim] entity=0x... anim=idle state=0x... dt suppressed=29 since last
[FPAnim] entity=0x... anim=idle state=0x... dt=0.016667 caller=... rva=... inMain=...
```

This yields event-level logs rather than a per-frame storm.

### Periodic inventory poll

Every 1500 ms while a pilot target exists, the worker logs:

- bound-state count and per-binding `enabled/loop/weight` snapshot
- whether `Entity::getAllAnimationStates` is resolvable and whether the entity's `AnimationStateSet*` is non-null

```text
[FPAnim] inventory entity=0x... boundStates=3
[FPAnim] inv-bound anim=idle state=0x... enabled=1 loop=1 weight=1.000
[FPAnim] inventory entity=0x... animSet=0x... HAS_ANIM_SET
```

A non-null `animSet` proves the pilot mesh is skeleton-animated (has a skeleton). An enumeration of the binding table gives the actually-touched clips; a future `AnimationStateSet::getAnimationStateIterator` hook can enumerate the full mesh inventory without relying on bindings.

No extra per-frame work is introduced: the inventory poll runs on the existing 25 ms worker thread but fires at most every 1.5 s and is SEH-guarded.

### Optional mesh/skeleton resolution

Best-effort resolution of `Entity::getMesh` / `Entity::hasSkeleton` is attempted as optional exports. Failure does not fail the trace; success is informational.

### Dormant manipulation gate (lcbench-only)

A fail-closed, dormant-unless-enabled manipulation path is present for the controlled feasibility experiment described in the investigation. It is **not** active during normal play.

```ini
[Diagnostics]
PilotFPAnimManip=0
PilotFPAnimManipAnim=stand2Kneel
PilotFPAnimManipMode=freeze   ; freeze | forceWeight
```

Environment override: `OPENSHIM_PILOT_FP_MANIP=1`.

When enabled, the `addTime` or `setWeight` hook for the named animation on the bound pilot entity is diverted:

- `freeze`: `addTime` is suppressed and logged as `[MANIP] Freeze addTime suppressed`
- `forceWeight`: `setWeight` is forced to `1.0` regardless of the game's request

The gate is checked only for already-bound states, is re-read after Ogre resolves, and is logged once at activation:

```text
[FPAnim] manipulation gate ACTIVE mode=0 targetAnim=stand2Kneel (isolated lcbench-only experiment)
```

Stock behavior is never altered when the gate is `0`.

## v3 enhancements (2026-08-27) — dual-target FP qualification

v3 retains v2's semantics and generalizes the binding machinery so WORLD (`Person+0x0F0` world pilot) and FP (`aspilo_fp` family) share the same transition/throttling code. No duplicated `RegisterBinding`/`LogBound*` implementations — both targets go through `TargetState` + `TargetKind`.

### FP target

FP discovery uses the **verified enumeration seam** `SceneManager::getMovableObjectIterator("Entity")` (`OgreSceneManager.h:3316`, `OgreMain.dll` export `?getMovableObjectIterator@SceneManager@Ogre@@...`, 5296). Creation interception via `SceneManager::createEntity` is **not** used because the executable does not import any `createEntity` overload (`dumpbin /imports` shows zero `createEntity`/`destroyEntity`/`getMovableObject` imports; only `getAnimationState` etc. are imported). Enumeration is therefore the primary resolver per the spec's preferred order A→C.

SceneManager retrieval uses the **verified global structure** `0x00920EA0 +0x08` (`bzr_hooks.cpp:2042` `kOgreSceneManagerStructureAddr`/`kOgreSceneManagerOffset`), the same seam used by `terrain_proxy.cpp` and `ogre_entity_frustum_cull.inl`. Both addresses are build-constant for GOG 2.2.301 and are checked with SEH.

**Candidate discovery is broad, promotion is strict** (`src/patches/pilot_fp_animation_trace.cpp:402-411`):

- Broad: `hasSkeleton` true (resolves `hasSkeleton@Entity@Ogre@@` `0x1D5E8` via export, SEH-guarded via `SafeEntityHasSkeleton`). Every animated `Entity` (≈20–40 per scene) appears as `[FPAnim][FP] candidate ... hasSkeleton=1`.
- Strict (pilot FP): `hasSkeleton` + `hasAnimationState("idle")` + `hasAnimationState("stand2Kneel")` (resolves `hasAnimationState@Entity@Ogre@@` `0x3B2F5` via `SafeEntityHasAnimationState`). Only pilot skeletons (`aspilo_fp`, `bspilo_fp`, `sspilo_fp`, `cspilo_fp`, `bsheav_fp` per `craft_bounds_architecture_20260822.md:122` table) carry that vocabulary; world `avtank` does not. The strict set is therefore typically 0–1 entities.

Promotion requires **strict + `worldIsPilot`** (`ResolveCurrentLocalPersonOgreEntity` true, i.e., local `Person` exists). Creation time is recorded but not required — the log records `caller` RVA and `worldPilot` flag as qualification evidence, per the spec's "record caller RVA/module" rather than hard-require `inMain`.

### FP lifetime

`g_Fp` has its own `generation` (`atomic<uint64_t>`), `bindings[64]`, `mutex`, `meshName`/`skeletonName`/`entityName`, and `lastInventoryTick`. It is **not** a raw `g_TargetFpEntity = entity` assignment.

- `RefreshWorldTarget: RefreshWorldTarget()` clears `g_Fp` (logs `[FPAnim][FP] target released reason=world-pilot-cleared`) when the world pilot disappears — FP presentation should not outlive the pilot.
- `RefreshFpTargetViaEnumeration:564` polls every `kFpEnumerateIntervalMs = 1500` via `SafeGetSceneManagerViaGlobal` + `getMovableObjectIterator("Entity")`; it builds `broadCandidates`/`strictCandidates` under SEH/`try/catch` and logs each `[FPAnim][FP] candidate ... strict=... worldPilot=...` with `caller` RVA.
- If `currentFp` is not in `broadCandidates`, it is **released** (`[FPAnim][FP] target released reason=not-in-enumeration`) and `generation` is bumped; if a new strict candidate exists it is **reacquired** (`[FPAnim][FP] target reacquired ...`). Bindings are cleared on both transitions and `lastInventoryTick` reset.
- SEH alone is not trusted for lifetime — pointer reuse is handled by generation + enumeration-membership check.

The FP path therefore never dereferences a stale `Entity*` blindly, manipulation is disabled when `g_Fp.entity==nullptr`, and the capture shows `target acquired / released / reacquired` lifecycle explicitly.

### Generalized binding

`RegisterBindingForTarget`, `FindBindingForTarget`, `LogBoundBoolForTarget`, `LogBoundFloatForTarget`, `TryLogInventoryForTarget` all take `TargetState&` + `TargetKind`. World behavior is byte-for-byte preserved; FP reuses the same transition filtering (`enabled`/`loop` only on change, `weight` ε=0.001, `dt` throttled 500 ms with `suppressed` count) and inventory poll (1.5 s, `boundStates` + `HAS_ANIM_SET` via `SafeGetAllAnimationStates`).

Logging distinguishes ` [FPAnim]` (WORLD, backward compatible) vs ` [FPAnim][FP]` (FP). Manipulation logs split `[MANIP][WORLD]` vs `[MANIP][FP]` so attribution is unambiguous.

### Verified seams documented at install

`InstallObservers:1317` now logs:

- `verified enumeration seam: SceneManager::getMovableObjectIterator export=...`
- `verified: exe does NOT import SceneManager::createEntity (dumpbin /imports) — creation hook not used; enumeration is primary resolver`
- `SceneManager retrieval: global structure 0x00920EA0 +0x08 (same as bzr_hooks.cpp:2042)`
- `verified enumeration seam ...` vs `enumeration seam NOT found — FP discovery via enumeration will fail closed`

If enumeration cannot be established, FP discovery fails closed and the world trace remains functional.

## Log format

Lines are emitted through the normal OpenShim logger with an `[FPAnim]` prefix. Typical v2 output:

```text
[FPAnim] target person=0x12345678 class=.?AVPerson@@ entity=0x23456789 renderBridge=Person+0x0F0/Ogre+0x094
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A bound=1 caller=0x... rva=0x... inMain=1
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A enabled=1 caller=0x... rva=0x... inMain=1
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A loop=1 caller=... rva=... inMain=...
[FPAnim] entity=0x23456789 anim=stand2Kneel state=0x456789AB time=0.000000 caller=... rva=... inMain=...
[FPAnim] inventory entity=0x23456789 boundStates=3
[FPAnim] inv-bound anim=idle state=0x3456789A enabled=1 loop=1 weight=1.000
[FPAnim] inventory entity=0x23456789 animSet=0x... HAS_ANIM_SET
```

When entering a vehicle, the trace should report that the local user object is no longer a Person and clear the target.

## Controlled harness correlation

Use the purpose-specific harness at `reverse_engineering/test_missions/pilot_anim_capture/pilot_test.lua` (deployed as `lcbench.lua` or `pilot.lua` alongside the `pilot.bzn` world). It emits precise `[PILOTTEST] T+<sec> <EVENT>` markers; each `[FPAnim]` line's caller RVA and timestamp can be correlated to the immediately-preceding `[PILOTTEST]` event.

Example correlation:

```text
[PILOTTEST] T+8.000 SET_SNIPER
[FPAnim] entity=0x... anim=stand2Kneel state=0x... bound=1 caller=... rva=0x59DE... inMain=1
[FPAnim] entity=0x... anim=stand2Kneel state=0x... enabled=1 caller=... rva=0x59DE... inMain=1
```

## First validation capture

Use an ordinary pilot session and perform this sequence deliberately, leaving roughly a second between actions:

1. Stand still.
2. Walk forward.
3. Walk backward.
4. Strafe left and right.
5. Fire a normal weapon.
6. Equip the sniper weapon and remain crouched briefly.
7. Unequip the sniper weapon.
8. Jump.
9. Land.
10. Enter a vehicle, then hop back out.

The capture should establish which states are enabled/disabled, which clips loop, when time is reset, whether weight is changed, how Redux advances each state per frame, and whether the known local Person Ogre entity is in fact the first-person animation owner.

## Decisive follow-up experiment

After this trace is validated, the next experiment should use the gated manipulation path in `lcbench` only:

1. While standing normally, request an existing clip such as `stand2Kneel` directly on the observed local Person Ogre entity without changing the selected weapon or `Person::curAnim`.
2. If the visible first-person model moves independently, add a deliberately new skeleton clip such as `fpsTest` and request it through `Entity::getAnimationState("fpsTest")`.

That determines whether OpenShim can decouple first-person presentation from the hardcoded `Person::Simulate` 0-11 animation FSM before any shotgun/reload state machine is implemented. The dormant manipulation gate is the minimal mechanism for step 1 (freeze/weight override) without shipping a general asset override.