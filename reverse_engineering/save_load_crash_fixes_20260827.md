# Save-Load Crash Fixes — 2026-08-27

Two separate save-load crash signatures were identified and fixed. One was a
stock `Inst4XMission`/`PathSpawn` handle-validation defect; the other was an
OpenShim destruction-chunk proxy lifetime defect exposed during mission resource
unload.

## Inst4XMission / PathSpawn stale handle

### Crash signature

- Dump: `battlezone98redux.exe.16444.dmp`
- Fault: read access violation at `battlezone98redux.exe+0x5C4C0`
  (`0x0045C4C0`), reading the nested object state through a null pointer.
- Caller chain: `GameObjectHandle::GetObj` (`0x00462630`) from
  `PathSpawn::Execute` (`0x0059C500`).
- RTTI identified the process as `PathSpawn`, owned by `Inst4XMission`.
- The failing handle was `0xBF800000`. It selected object-pool slot `0xBF8`,
  but that slot was empty: both its generation and nested object-state pointer
  were zero.

### Root cause

This is a load-side reconstruction defect, not evidence of save-file corruption.

Redux `PathSpawn::CreateObject` at `0x0059C140` allocates `0x1150` bytes and
calls the no-argument load constructor at `0x0059C1D0`. That constructor calls
only the `AiProcess` base constructor and installs the `PathSpawn` vtable. It
does not initialize `PathSpawn::state`, the path item array, the item count, or
the cached powerup handles. The inherited `AiProcess::Load` restores only base
fields, so a reconstructed `PathSpawn` can retain stale derived-state values.

The stale cache alone should have been recoverable. `PathSpawn::Execute` already
treats a missing powerup as a normal condition and schedules a replacement.
However, stock `GameObject::GetObj` validates only the handle's low 20-bit
generation against the selected pool slot. Empty slots also have generation
zero, so this zero-generation stale handle passed the comparison. The wrapper
then treated the empty slot as a live object and dereferenced its null nested
state while checking the dead flag.

### Fix

OpenShim replaces the stock GOG `GameObjectHandle::GetObj` wrapper with a
guarded equivalent. It resolves the handle through the already-verified pool
lookup, round-trips the result through `GameObject::GetHandle`, rejects empty or
stale slots, checks the nested state before reading flags, and preserves the
stock dead-object filter. Returning null sends `PathSpawn` through its existing
missing-object recovery path.

The patch site is found by a unique full-function signature with a known-build
fallback of `0x00462630`. Startup validation reported one signature match and a
successful five-byte jump patch.

## Chunk proxy resource-unload lifetime

### Crash signature

- Dump: `battlezone98redux.exe.16476.dmp`
- Fault: read access violation at `OgreMain.dll+0x4669A3` in
  `Ogre::SubMesh::_getRenderOperation`.
- The `SubEntity` belonged to `Ogre/MO656`, mesh
  `avfigh/ara11nrr.mesh`, material `avfigh00`.
- The full dump placed the entity in OpenShim chunk-proxy slot 9 for geometry
  `ARA11NRR`.

### Root cause and fix

On a save/mission transition, Redux unloaded the outgoing `Modable` resource
group while the OpenShim proxy entity remained attached and visible. Ogre's
loading-screen scene traversal reached the entity after its mesh/submesh data
had been destroyed, leaving `SubMesh::indexData` null.

OpenShim now deactivates every chunk-proxy scene resource when leaving the
simulation, while its Ogre objects are still valid and before Redux unloads the
resource group. The generic chunk batch is hidden in the same transition.

## Validation

- Isolated Release build completed with zero errors.
- All 11 available native test targets passed.
- Startup signature scan found the Inst4X guard exactly once and installed it.
- The same save that produced the Inst4X dump was loaded repeatedly with the
  patched DLL; no crash and no new dump occurred.
- The game was then stopped through the safe harness path, and its temporary
  windowed-mode configuration was restored.
