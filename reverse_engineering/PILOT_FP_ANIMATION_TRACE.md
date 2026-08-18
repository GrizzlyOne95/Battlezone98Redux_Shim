# Pilot first-person Ogre animation trace

This diagnostic records the Ogre animation-state activity associated with the local on-foot `Person`. It is observation-only and is intended to establish the exact stock first-person animation behavior before OpenShim attempts any viewmodel animation override.

The trace deliberately does **not** identify the target by mesh/resource name. Redux already has a verified local-player/render-object chain, so the observer follows the player object directly and ignores every other Ogre entity.

## Configuration

The trace is enabled by default while this path is being characterised:

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

## What is traced

OpenShim waits for the retail `OgreMain.dll`, resolves the relevant Ogre exports by semantic decorated-name matching, and observes only exact executable call/IAT sites for:

- `Ogre::Entity::getAnimationState`
- `Ogre::AnimationState::setEnabled`
- `Ogre::AnimationState::setLoop`
- `Ogre::AnimationState::setTimePosition`
- `Ogre::AnimationState::setWeight`
- `Ogre::AnimationState::addTime`

When `Entity::getAnimationState(name)` is called with `self` equal to the current local Person's target Ogre entity, OpenShim binds the returned `AnimationState*` to that animation name. Mutation hooks log only already-bound states.

The target is refreshed continuously. If the local Person/entity changes, all state bindings are cleared before the new target is published.

## Log format

Lines are emitted through the normal OpenShim logger with an `[FPAnim]` prefix. Typical output should resemble:

```text
[FPAnim] target person=0x12345678 class=.?AVPerson@@ entity=0x23456789 renderBridge=Person+0x0F0/Ogre+0x094
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A bound=1
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A enabled=1
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A loop=1
[FPAnim] entity=0x23456789 anim=idle state=0x3456789A dt=0.016667
[FPAnim] entity=0x23456789 anim=stand2Kneel state=0x456789AB time=0.000000
```

When entering a vehicle, the trace should report that the local user object is no longer a Person and clear the target.

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

After this trace is validated, the next experiment should remain separate from this read-only patch:

1. While standing normally, request an existing clip such as `stand2Kneel` directly on the observed local Person Ogre entity without changing the selected weapon or `Person::curAnim`.
2. If the visible first-person model moves independently, add a deliberately new skeleton clip such as `fpsTest` and request it through `Entity::getAnimationState("fpsTest")`.

That determines whether OpenShim can decouple first-person presentation from the hardcoded `Person::Simulate` 0-11 animation FSM before any shotgun/reload state machine is implemented.
