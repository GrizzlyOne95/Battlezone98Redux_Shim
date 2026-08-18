# Pilot first-person Ogre animation trace

This diagnostic records the Ogre animation policy Battlezone 98 Redux applies to the dedicated first-person pilot viewmodel (`aspilo_fp.mesh`). It is observation-only and is intended to establish the exact stock first-person animation behavior before OpenShim attempts any viewmodel animation override.

## Configuration

The trace is enabled by default:

```ini
[Diagnostics]
TracePilotFPAnimations = 1
```

Set the key to `0` to disable it. The process-environment compatibility override is:

```text
OPENSHIM_TRACE_PILOT_FP_ANIMATIONS=0|1
```

A process environment value takes precedence over the INI key.

This setting is independent of `ProfileOgreAnimation`. Enabling the pilot trace does **not** enable the general Ogre animation/render overhead profiler or its DX11 counters.

## What is traced

OpenShim waits for the retail `OgreMain.dll`, resolves the relevant Ogre exports by semantic decorated-name matching, and observes only exact executable call/IAT sites for:

- `Ogre::Entity::getAnimationState`
- `Ogre::AnimationState::setEnabled`
- `Ogre::AnimationState::setLoop`
- `Ogre::AnimationState::setTimePosition`
- `Ogre::AnimationState::setWeight`
- `Ogre::AnimationState::addTime`

The trace does not assume every animated `Ogre::Entity` is the pilot. When `getAnimationState` returns a state, OpenShim resolves that entity's mesh through `Entity::getMesh()` and the retail `Resource::getName()` export. A state is registered only when the resource basename is exactly `aspilo_fp.mesh` (or `aspilo_fp`).

The only small representation check is extracting the raw `Mesh*` from the `const MeshPtr&` returned by `Entity::getMesh()`. That pointer is accepted only when its vtable is inside the loaded retail `OgreMain.dll`; otherwise the entity is ignored. This keeps a mismatched retail SharedPtr layout fail-closed rather than treating an arbitrary object as the first-person mesh.

## Log format

Lines are emitted through the normal OpenShim logger with an `[FPAnim]` prefix. Typical output should resemble:

```text
[FPAnim] entity=0x12345678 mesh=aspilo_fp.mesh anim=idle state=0x23456789 bound=1
[FPAnim] entity=0x12345678 mesh=aspilo_fp.mesh anim=idle state=0x23456789 enabled=1
[FPAnim] entity=0x12345678 mesh=aspilo_fp.mesh anim=idle state=0x23456789 loop=1
[FPAnim] entity=0x12345678 mesh=aspilo_fp.mesh anim=idle state=0x23456789 dt=0.016667
[FPAnim] entity=0x12345678 mesh=aspilo_fp.mesh anim=stand2Kneel state=0x3456789A time=0.000000
```

`bound=1` means OpenShim observed `Entity::getAnimationState(name)` return that `AnimationState*` for the first-person entity. Subsequent mutation lines are keyed by the state pointer and therefore remain scoped to that entity without repeatedly inspecting the Ogre mesh in the hot `addTime` path.

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

The capture should establish which first-person states are enabled/disabled, which clips loop, when time is reset, whether weight is changed, and how Redux advances each state per frame.

## Decisive follow-up experiment

After this trace is validated, the next experiment should remain separate from this read-only patch:

1. While standing normally, request an existing clip such as `stand2Kneel` directly on the observed `aspilo_fp` entity without changing the selected weapon or `Person::curAnim`.
2. If the viewmodel moves independently, add a deliberately new skeleton clip such as `fpsTest` and request it through `Entity::getAnimationState("fpsTest")`.

That determines whether OpenShim can decouple first-person presentation from the hardcoded `Person::Simulate` 0-11 animation FSM before any shotgun/reload state machine is implemented.
