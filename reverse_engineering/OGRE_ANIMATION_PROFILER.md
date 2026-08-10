# Ogre Animation / Render Overhead Profiler

This diagnostic measures whether Battlezone 98 Redux is spending CPU time animating and software-skinning Ogre entities that never reach render submission.

It is **opt-in** and observation-only. It does not change animation state, VDF state, culling, materials, shader selection, or D3D11 render state.

## Developer setup

The profiler uses the pinned Ogre 1.10 reference headers added to OpenShim.

Run once after cloning/updating the branch:

```powershell
.\setup-dev.ps1
```

Then build `Release | Win32` normally.

The retail BZR `OgreMain.dll` is not assumed to be ABI-identical to pristine upstream Ogre 1.10. The profiler resolves the retail DLL's exports at runtime and only installs observers when the expected semantic exports/call sites can be identified.

## Enable

Either set the environment variable before starting BZR:

```powershell
$env:OPENSHIM_PROFILE_OGRE_ANIMATION = "1"
```

or add this to `openshim.ini`:

```ini
[Diagnostics]
ProfileOgreAnimation = 1
```

Remove/disable the setting for normal play.

## What is measured

Once per approximately one second, OpenShim reports:

- `frames` - DX11 `Present` calls observed during the interval.
- `animCalls` - calls into `Ogre::Entity::_updateAnimation`.
- `animUnique~` - approximate unique Entity pointers seen by animation during the interval.
- `animCPU` - measured wall-clock CPU time spent inside `_updateAnimation` (includes nested animation work).
- `swBlend` - calls to `Ogre::Mesh::softwareVertexBlend`.
- `verts` - source vertices submitted to software vertex blending.
- `swCPU` - measured wall-clock CPU time spent specifically inside `softwareVertexBlend`.
- `skinnedUnique~` - approximate unique Entities attributable to software skinning.
- `renderQueue` - calls to `Ogre::Entity::_updateRenderQueue` when the retail Entity vtable can be verified and patched.
- `renderUnique~` - approximate unique Entities reaching that render-submission path.
- `skinnedNotRendered~` - approximate software-skinned Entity set not seen in the render-submission set during the same interval.
- `Draw` / `DrawIndexed` - basic immediate-context D3D11 draw calls.
- `submittedVerts` / `submittedIndices` - vertex/index counts passed to those two D3D11 draw APIs.

The `~` metrics use a 65,536-bit pointer bloom set to avoid allocating or locking a hash table in the hot animation/render paths. At normal BZR entity counts the collision error should be small, but these values are intentionally labelled approximate.

`animCPU` contains `swCPU`; do not add them together.

## Recommended large-battle test

Use the same mission/save and avoid changing unit count between samples.

### A. Face the battle

Keep the camera aimed at the densest group of units for 10-20 seconds. Save several consecutive `[OgreProfile]` lines.

### B. Turn 180 degrees away

Do not move the player or change the battle. Point the camera away so the units are outside the view frustum. Record another 10-20 seconds.

### C. Move well outside rendering range

If practical, move far enough away that the battle should not be submitted for rendering, while allowing the simulation to continue. Record another sample.

## Interpreting the result

### Expected efficient behavior

When looking away, all or most of these should collapse together:

```text
animCalls
swBlend
verts
renderQueue
Draw / DrawIndexed
```

That indicates Ogre is avoiding most software animation work for invisible objects.

### Suspected Redux behavior

A strong confirmation of unnecessary software skinning would look like:

```text
Facing battle:
  skinnedUnique~=90
  renderUnique~=25

Looking away:
  skinnedUnique~=90
  renderUnique~=0-3
```

with `verts` and `swCPU` staying high while render submission/draw activity collapses.

That means the CPU is continuing to deform meshes that the renderer will not submit.

### Rendering is not the main bottleneck

If turning away materially reduces `renderQueue` and D3D11 draw activity but frame rate remains poor while `swCPU` is already small, large-battle cost is likely dominated elsewhere (simulation, collision, AI, pathing, etc.).

## Safety / fail-closed behavior

The profiler does not hardcode guessed retail Ogre addresses.

For Ogre it:

1. Enumerates exports in the already-loaded retail `OgreMain.dll`.
2. Resolves semantic export names for `_updateAnimation`, `softwareVertexBlend`, and `_updateRenderQueue`.
3. Rewrites only direct `CALL rel32` sites whose decoded destination exactly equals the resolved retail function.
4. Rewrites the Entity vtable only when a slot value exactly equals the resolved retail `_updateRenderQueue` function.
5. If any required match is missing or ambiguous, that observer stays disabled and a warning is logged.

For DX11 it observes the render system's imported D3D11 device creation calls, then wraps the public COM vtable entries for `DrawIndexed`, `Draw`, and `Present`.

The D3D11 counters currently cover the normal `Draw` and `DrawIndexed` paths only. If Redux is later found to use instanced or indirect draw APIs materially, those can be added separately.
