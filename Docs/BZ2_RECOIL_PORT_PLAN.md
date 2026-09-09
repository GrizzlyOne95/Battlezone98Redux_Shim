# BZ2-Style Weapon Recoil Port Plan for OpenShim

## Goal

Add Battlezone 2-style per-weapon mesh recoil to Battlezone 98 Redux through OpenShim with the smallest practical native surface.

The target behavior is the classic BZ2 vehicle recoil system:

```text
successful weapon shot
    -> identify recoil controller for weapon slot
    -> instantly move configured submesh backward along its local axis
    -> return submesh to its captured rest transform over time
```

This document is a design/research artifact only. It does not implement hooks or change runtime behavior.

## BZ2 behavior to preserve

Research against the BZ2 a130 executable/PDB recovers the following primary recoil semantics:

- Per-weapon configuration key: `recoilName%d`
- Controlled object: named model `MeshObj` / submesh
- Ownership: carrier/vehicle creates and owns `RecoilControl`
- Weapon construction receives the relevant `RecoilControl*`
- Kick displacement: approximately `-0.6` units
- Recovery rate: approximately `+3.0` units/second
- Stock return duration: approximately `0.2` seconds
- Motion: translation along the controlled piece's authored local axis
- Transform application: recomputed from captured rest position plus axis times recoil displacement
- Trigger intent: successful/committed shot, not raw trigger-button input

The BZ2 source research is documented separately in `GrizzlyOne95/BZ2_Source`.

## Proposed authoring compatibility

OpenShim should accept the BZ2 naming convention directly rather than invent a new required key:

```ini
recoilName1 = "recoil_1"
recoilName2 = "recoil_2"
```

This gives content authors a familiar and portable convention.

Optional OpenShim extensions may be supported later:

```ini
recoilDistance1 = 0.6
recoilReturn1   = 3.0
```

Recommended defaults when omitted:

```text
recoilDistanceN = 0.6
recoilReturnN   = 3.0
```

The first implementation should not require these extension keys.

## Minimum runtime architecture

A compact runtime representation is sufficient:

```cpp
struct RecoilController
{
    MeshNode* node;          // actual BZ1 type TBD
    Vec3      restPosition;  // actual BZ1 vector type TBD
    Vec3      localAxis;     // or derive from live node transform
    float     distance;
    float     kickDistance;
    float     returnSpeed;
};
```

The exact BZ1 model/vector types must be taken from the real engine structures discovered during implementation. The names above are intentionally schematic.

### Fire

```cpp
void Fire(RecoilController& recoil)
{
    recoil.distance = -recoil.kickDistance;
    Apply(recoil);
}
```

### Update

```cpp
void Update(RecoilController& recoil, float dt)
{
    if (recoil.distance >= 0.0f)
        return;

    recoil.distance += recoil.returnSpeed * dt;

    if (recoil.distance > 0.0f)
        recoil.distance = 0.0f;

    Apply(recoil);
}
```

### Apply

Conceptually:

```cpp
node.localPosition = restPosition + localAxis * distance;
mark_transform_dirty(node);
```

The implementation must use the existing BZ1 model hierarchy/transform machinery and must not introduce a parallel renderer-side transform system.

## Required integration points

### 1. ODF/config parse

At vehicle/class initialization, inspect indexed weapon slots for `recoilNameN`.

Requirements:

- absence of the key must preserve stock behavior exactly;
- invalid/missing mesh names must fail closed and leave that slot without recoil;
- diagnostics should identify the ODF, slot, and missing recoil node when useful;
- parsing must respect whatever locale-safe ODF path OpenShim currently uses.

### 2. Mesh-node resolution

Once the vehicle/model hierarchy exists:

```text
recoilNameN
    -> resolve named model piece
    -> capture original local transform
    -> obtain/create RecoilController
    -> associate weapon slot N with controller
```

Do not search the hierarchy by name every simulation frame.

### 3. Successful-shot hook

This is the most important correctness requirement.

Do not trigger recoil on:

```text
fire key/button down
```

Trigger only when the game has actually committed a weapon shot/ordnance creation or equivalent accepted firing event.

This is needed so recoil naturally respects:

- cooldown;
- ammo availability;
- weapon enable/disable state;
- AI firing;
- burst/automatic fire cadence;
- linked weapons;
- weapons that refuse a trigger attempt.

The BZ1 implementation task should locate the narrowest common shot-commit path rather than patch every input path.

### 4. Simulation/update hook

Advance active recoil controllers using simulation delta time.

Preferred ownership:

- vehicle/weapon simulation path if a safe common hook exists;
- otherwise a bounded OpenShim per-object update registry keyed to live vehicle/model instances.

Avoid renderer-frame timing if possible. Recoil should be simulation-time behavior and should remain stable across variable render FPS.

### 5. Lifetime/destruction

Controllers must not outlive the associated vehicle or mesh hierarchy.

Required cleanup cases include:

- vehicle destruction;
- map unload;
- mission restart;
- object replacement/recycling;
- multiplayer object teardown;
- model reload/rebuild if BZ1 performs one dynamically.

## Shared recoil nodes / linked weapons

Multiple weapon slots may legally reference the same `recoilName`.

Incorrect design:

```text
slot 1 -> controller A -> barrel
slot 2 -> controller B -> barrel
```

where A and B independently rewrite the same node transform.

Preferred design:

```text
slot 1 --+
         +--> one controller for "barrel"
slot 2 --+
```

Implementation pattern:

```cpp
RecoilController* GetOrCreateRecoilController(MeshNode* node);
```

Each slot stores a reference/handle to the shared controller. A valid shot from any associated slot resets that controller to full recoil.

This also protects against displacement accumulation bugs seen historically in implementations where linked weapons shared a recoil piece.

## Transform semantics

The safest port should mirror the important BZ2 property:

```text
current position = captured rest position + local axis * current distance
```

Do not implement:

```text
current position += recoil delta
```

Incremental mutation risks drift and shared-controller accumulation.

### Axis

BZ2 analysis indicates the primary controller uses a basis vector from the controlled mesh's local transform, structurally consistent with the mesh's local forward direction.

Before implementation, identify the exact equivalent BZ1 basis/member and prove its sign/orientation with a test mesh.

A good qualification asset should use a recoil node whose local forward axis is visually obvious and intentionally differs from world forward.

## Multiplayer/networking

The initial design should treat recoil as deterministic local presentation derived from an already-networked firing event.

Do **not** add a new recoil network packet unless testing demonstrates that one is necessary.

Expected model:

```text
existing authoritative/replicated shot event
    -> each peer triggers same local recoil controller
```

This keeps the feature visual and avoids changing game-state protocol semantics.

Qualification must verify:

- local player firing;
- remote player firing;
- AI firing on host;
- AI/vehicle visibility on clients;
- late object creation / object replication;
- linked weapon cadence.

If remote replicas do not execute the same successful-shot path, add a replica-side visual trigger at the existing ordnance/fire receive boundary rather than networking recoil state itself.

## Savegames

BZ2 serializes recoil displacement, but the stock primary return duration is only about 0.2 seconds.

Recommendation for Phase 1:

- do not patch BZ1 save format;
- restore all recoil controllers at rest after load.

This is effectively invisible in normal play and avoids introducing save compatibility risk for a transient cosmetic state.

Exact BZ2-compatible persistence can be considered later if there is a compelling reason.

## Safety / compatibility requirements

The feature should be inert unless an ODF explicitly declares `recoilNameN`.

Required failure behavior:

- unsupported executable/build: do not install unsafe hooks;
- missing configured node: skip recoil for that slot;
- destroyed/stale object: never dereference cached mesh pointers;
- duplicate/shared node: share controller or arbitrate explicitly;
- unknown weapon class: stock firing remains unaffected;
- configuration parse failure: no recoil rather than broken weapon operation.

The feature must not alter weapon damage, projectile direction, firing cadence, ammo use, hardpoint selection, or gameplay physics.

## Suggested implementation phases

### Phase 0 - BZ1 engine trace

Before editing runtime behavior, identify and document:

1. BZ1 vehicle/weapon class structures used by Redux.
2. Per-weapon slot storage and weapon build path.
3. ODF parser path for vehicle weapon properties.
4. Model hierarchy/node lookup by string.
5. Mutable local node translation fields/helpers.
6. Transform-dirty/update mechanism.
7. Common successful-shot commit path.
8. Safe vehicle destruction/lifetime hook.
9. Simulation delta-time source.

Deliverable: address/symbol report with no behavior patch.

### Phase 1 - One-slot proof of concept

Hard-code or debug-configure one known test vehicle/node and prove:

- node can be moved safely;
- children follow;
- rest transform is preserved;
- update is stable at different frame rates;
- no renderer corruption occurs.

Do not ship hard-coded content behavior.

### Phase 2 - `recoilNameN` parser and slot mapping

Add BZ2-compatible indexed parsing and controller creation.

Test:

- one weapon / one recoil node;
- two weapons / two nodes;
- two weapons / one shared node;
- no recoil keys;
- invalid recoil node.

### Phase 3 - successful-shot trigger

Wire the controller to the confirmed shot-commit path.

Test:

- player single-shot;
- automatic weapon;
- AI weapon;
- empty ammo;
- held trigger during cooldown;
- linked weapons.

### Phase 4 - multiplayer qualification

Validate host/client visual agreement and object lifetime.

No recoil-specific networking should be added unless existing fire replication proves insufficient.

### Phase 5 - optional tuning keys

Only after stock-compatible behavior is proven, consider:

```ini
recoilDistanceN
recoilReturnN
```

Keep default behavior identical to the recovered BZ2 primary controller.

## Recommended test asset

Create a deliberately simple model with:

```text
vehicle root
    +-- recoil_test
          +-- barrel_tip / visual marker
```

Author `recoil_test` with a clearly rotated local axis so world-axis mistakes are obvious.

Test ODF:

```ini
recoilName1 = "recoil_test"
```

Expected stock-compatible trace:

```text
t = 0.000  shot commits, displacement = -0.600
...
t = 0.100  displacement ~= -0.300
...
t = 0.200  displacement = 0.000
```

The exact sampled values depend on simulation tick timing, but the fixed-speed return should converge at approximately 0.2 seconds.

## Instrumentation recommendations

For development builds, log only state transitions rather than every frame:

```text
[Recoil] bind object=<id> slot=1 node=recoil_test
[Recoil] fire object=<id> slot=1 node=recoil_test distance=-0.600
[Recoil] rest object=<id> node=recoil_test
[Recoil] missing object=<id> slot=2 node=missing_name
```

Optional verbose logging can include local rest position and axis for qualification builds.

## Explicit non-goals

Do not combine this work with:

- camera recoil;
- player view kick;
- physics impulse on the firing craft;
- procedural weapon sway;
- generic skeletal animation;
- renderer redesign;
- projectile/netcode changes;
- BZ2's secondary joint recoil controller unless a concrete BZ1 use case is identified.

## Remaining research gates

Before implementation is considered merge-ready, resolve:

1. Exact BZ1 successful-shot hook.
2. Exact BZ1 model-node lookup path.
3. Exact mutable local transform representation.
4. Correct local recoil axis/sign.
5. Object/model lifetime safety.
6. Replica behavior in multiplayer.
7. Whether any existing OpenShim model-transform hook can be reused instead of adding another patch site.

## Acceptance criteria

A first shipping implementation is successful when:

- stock content without `recoilNameN` is bit-for-behavior unaffected by the feature;
- a configured BZ1 vehicle visibly recoils the named mesh when its weapon actually fires;
- displacement is local-axis-relative, not world-axis-relative;
- default behavior is approximately `0.6` units kick with `3.0 units/sec` linear recovery;
- AI and player firing work;
- shared recoil meshes do not accumulate or fight;
- destroyed objects leave no stale controller pointers;
- multiplayer firing does not require or introduce a new protocol packet;
- no weapon gameplay values are altered.
