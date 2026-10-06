# Opt-in vehicle geometry contact experiment

The local ISDFC `isdftest` COLLISION page selects one Fury Warrior (`fvtankf`).
EXU exposes `exu.collision`; the optional winmm SDK bridge delegates to OpenShim.
Nothing is enabled automatically in the permanent mission or other campaigns.

## Contact path and scope

- Preserve entity type 1, COLP source body and the normal broadphase. Changing
  both hovercraft to type 3 would bypass CheckPair's hovercraft dispatch.
- CarEntityCheck sends an eligible pair to CarHierarchyCheck with the selected
  vehicle as the geometry **target**. Reverse the entity and output arguments
  together when the selected vehicle was the source.
- Build native Cgeom caches for physical exterior LOD0 parts (name digits `11`,
  classes 60/65/66/67/68, more than 8 vertices). Exclude helpers and cockpit LOD.
- Temporarily attach caches/0x3000 collision flags and tight local bounds during
  this synchronous calculation. Restore exact flags, cache pointers and bounds
  in `__finally`. Every other contact path sees the original state.
- Preserve polygon time, point and normal. Replace the 72-byte counterpart
  properties block with the corresponding **root craft** properties. CheckPair
  already replaces counterpart object pointers with the entity roots. Leaving
  leaf properties in place incorrectly gives a moving vehicle scenery defaults.
- Terrain, shots, pilots and unsupported entity pairs remain stock. This tests
  source COLP versus target legacy GEO, not polygon versus polygon, and does not
  extract Ogre render/skinning triangles.

## Ownership and failure behavior

Only one handle is selected. Round-trip its generation through the live object
arena and verify its GameObject and root before walking the remembered tree.
Changed trees/geometry pointers fall back to stock and increment `fallbacks`.
Recreate the target to qualify its new hierarchy. Cache limits: 256 nodes,
16384 vertices per physical part; allocation/validation failures reject selection.
The generated Spitter, Spearhead and Leviathan hulls contain 9469, 9619 and
11146 vertices respectively. Cgeom_Create uses 14 bytes of temporary stack
storage per source vertex and ushort remap indices; the bounded 16384 limit
allows these hulls while staying below the index format's capacity.

Caches are detached outside contact. Free them via native Cgeom_Delete on a
temporary object containing only the owned +0x9C pointer; never dereference a
destroyed part to free memory. EXU clears selection on mission reset/close.
The process-owned hook keeps no EXU function pointers. Lua/native APIs must be
called on the mission simulation thread, as the EXU bindings do.

## Evidence and provenance (2026-10-06)

**PROVEN:** installed Windows GOG 2.2.301 executable SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`
matches the private Ghidra corpus. Fresh Rizin disassembly and settled live entry
reads qualified each of the six named resolves. All patterns have a single match
and zero fallback. The hook copies six whole prologue bytes without relative
operands. Steam explicitly stands down; other distribution/platform lanes are
unverified.

| Native function | GOG VA | Calling convention/evidence |
|---|---|---|
| CarEntityCheck | 0x004405E0 | cdecl(entity, entity, float, out, out), caller cleans 20 bytes |
| CarHierarchyCheck | 0x00440870 | same five arguments; recursion returns integer contact result |
| Cgeom_Create | 0x00444220 | cdecl(obj, matrix), EAX pointer; existing SetObjCollision caller |
| Cgeom_Delete | 0x00444540 | cdecl(obj), only frees/nulls +0x9C through engine CRT |
| SelectLOD | 0x004E3620 | cdecl(obj, lod), existing setup uses 0 |
| GetProperties | 0x0062BF70 | cdecl(hidden result buffer, obj), writes 72 bytes, returns buffer in EAX |

CLSN_INFO wire layout is 120 bytes: collided +0, counterpart object +4,
properties +8..+79, time +80, contact point +84, relative velocity +96,
normal +108. BoxGeom fills the target leaf properties; CheckPair replaces its
object pointer with the root before the response. GetProperties caller at
0x00441D36 pushes object then buffer and cleans 8 bytes; the callee copies
18 words and returns the buffer with plain RET. No leaked-build ABI is assumed.

**PROVEN:** a normal mission-loop A/B run selects 8 Fury parts/3158 faces and
executes real geometry contacts without stock fallback. An initial run exposed
excessive impulses from leaf scenery properties; root-property adaptation fixes
that mismatch. Final measurements and session logs belong in the local
qualification report, not in the private decompile corpus.

Final functional checks cover centre/left/right passes in both modes and two
centre passes with reversed craft creation order (eight passes total). All
survive with zero stock fallbacks. Creation order was varied; native dispatch
argument order was not separately instrumented. Local `QUALIFICATION.md` and
`qualification.json` retain counters/travel and exact deployed hashes.

The five-new-Scion matrix accepted all targets: Spitter 3 parts/14080 faces,
Spearhead 3/15992, Leviathan 7/18412, Healer 5/1356 and Fury 8/3158. Its saved
record contains 44 of 150 planned pair/mode/lane passes with zero stock fallbacks
or flagged excessive speeds. Remaining combinations are unqualified. Several
GEO passes produce no contact while BOX does; one-impulse coast distance, recessed
surfaces and vertical alignment must be distinguished in follow-up testing.
ISDFC retains curated partial measurements and explicit provenance; this is not
full five-craft collision acceptance.

Stock `avtank`/`svtank` controls complete all 48 pair/mode/lane/speed passes at
12 and 24 m/s. Both survive every pass; all 24 GEO passes produce contact, with
zero stock fallbacks and no sampled speed above 24 m/s. Each target selects six
physical parts (164 and 159 collision polygons). These are positive controls
for the installed runtime module recorded in ISDFC's stock-control provenance,
not proof of exact normals or a substitute for resolving the Scion misses.

**UNKNOWN:** production suitability on all craft, animated extreme poses,
save/load gameplay contact, multiplayer determinism, and Steam/Wine/Proton.
This is a one-craft contact experiment, not a global collision mode.

## SDK and Lua

Append-only SDK exports: GetGeometryContactCapabilities (bit 0),
SetGeometryContact(handle, enabled), ClearGeometryContact,
GetGeometryContactStats(handle, enabled*, parts*, faces*, checks*, hits*, fallbacks*).
Old/missing providers fail closed. EXU methods live under `exu.collision`:
GetCapabilities, SetGeometry, GetStats, Clear. Stats report actual native mode;
counters reset when the mode is selected. `hits` counts successful narrowphase
checks, not unique impacts. Positive `fallbacks` means some pairs ran stock.

Windows checks: Release Win32 build, 78 CTests, appended SDK argument/order and
older-provider checks, network/INI/profiler gates, 208 Enhanced shader compilations
and PSSM math/isolation checks. EXU Release x86 builds and Windows hardening/
address-generation checks pass. WSL host validation reaches Python checks then
stops because that environment has no `node`; Linux qualification is incomplete.

Local deployment uses Deploy-OpenShim.ps1 for the complete winmm/bzloader/plugin/
patches/resources set, plus the rebuilt EXU and ISDFC scripts, with backups.
No release, Workshop publication or global ODF collision rewrite is performed.
