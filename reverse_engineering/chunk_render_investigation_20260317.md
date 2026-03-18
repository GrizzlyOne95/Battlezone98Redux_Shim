# Legacy Chunk Render Investigation

Date: March 17, 2026

## Current Working Read

The invisible chunk problem still looks like a native legacy-chunk-to-Redux-bridge failure, not a legacy simulation failure.

What we know:

- `winmm_shim.log` shows many `[CHUNK] stock ... reason=post-stock` entries with non-null geometry lookup tables and non-null handles.
- The March 17 Steam run had `Chunk Render Resolve Hook` installed, but `Force-first-geo fallback: disabled`, so that run only proves the stock resolver can see chunk GEO tables.
- The user confirmed the Ogre `*ck*.mesh` loads seen in `BZOgreLogfile.log` came from a custom mod that spawns fake chunks, so those loads are not evidence of the native chunk path.

## Legacy Engine Evidence

The best-effort badlands corpus points strongly at native chunks being built from existing legacy GEO child objects, not from separate pre-authored "chunk mesh" assets:

- [`CreateChunk-004be555.c`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\badlands\legacy_bz1_exact_full\ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\CreateChunk-004be555.c) changes the existing object to `CLASS_ID_CHUNK`, recomputes its transform, removes it from the old tree, and adds it under the `ChunkEffect` entity.
- [`PartialFragmentObject-004bef90.c`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\badlands\legacy_bz1_exact_full\ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\PartialFragmentObject-004bef90.c) recursively walks child GEO nodes and hands them to `CreateChunk`.
- [`FullFragmentObject-004bf08b.c`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\badlands\legacy_bz1_exact_full\ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\FullFragmentObject-004bf08b.c) does the same for the full hierarchy.
- [`Render_Chunk_Object-004e8ede.c`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\badlands\legacy_bz1_exact_full\ghidrecomp\results\bins\bzone.exe-aa1ee4\decomps\Render_Chunk_Object-004e8ede.c) renders through the old child/BSP display-list path.

Taken together, the legacy game is not spawning a separate modern chunk representation. It is reparenting real legacy GEO child objects and expecting the renderer to display them.

## Most Likely Failure Point

Most likely chain:

1. native chunk objects are still created and simulated
2. native chunk GEO lookup/selection often still works
3. Redux never creates or preserves the OBJ76/GameObject -> Ogre bridge for those chunk children
4. collision and damage continue because the legacy object still exists, but nothing reaches the Ogre renderer

This matches the existing OpenShim README note that, if forced geometry still does not render, the next failure point is probably "render-class handling or Ogre proxy creation."

## Instrumentation Added On March 17

OpenShim chunk tracing now logs two candidate Redux/Ogre bridge paths for each traced chunk object:

- direct object `+0xF0` bridge root
- direct bridge `+0x94` Ogre entity pointer
- direct bridge `+0xA8` Ogre light pointer
- legacy-style owner probe at object `+0x8C`, then owner `+0xF0/+0xF4/+0xF8`
- owner bridge `+0x94` Ogre entity pointer
- owner bridge `+0xA8` Ogre light pointer
- probe status for both paths

This was added in [`src/bzr_hooks.cpp`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\src\bzr_hooks.cpp) and built successfully into:

- `C:\Users\iestu\Documents\GIT\BZR-OpenShim\bin\Release\winmm.dll`

The rebuilt DLL was copied to:

- `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\winmm.dll`

## March 17 Follow-Up Result

The owner-aware Steam repro materially narrowed the problem:

- Many native chunk traces still show valid stock lookup tables and valid selected GEO handles for `type=0x3D`.
- The direct `+0xF0` probe continues to return inconsistent garbage-like values on many chunk objects, confirming that the resolve hook target is not a plain `GameObject` layout.
- The owner-aware probe is consistently `owner=0x00000000 ownerBridge=0x00000000 ownerOgre=0x00000000` on the native chunk objects observed so far.

This is important because it strongly suggests the real native chunk objects do not carry a normal Redux `GameObject -> Ogre` bridge at all by the time the render resolve hook sees them.

That fits the legacy `CreateChunk` behavior:

- chunk creation reparents existing legacy GEO child objects under the `ChunkEffect` entity
- chunk rendering walks the legacy child tree directly
- no separate modern render object is established in that path

So the current evidence now favors "missing Redux/Ogre proxy creation for chunk-class legacy children" over "chunk GEO lookup failure."

## Next Test Pass

Recommended environment for the next Steam reproduction:

```powershell
$env:OPENSHIM_CHUNK_LOG_BUDGET='1000'
$env:OPENSHIM_CHUNK_TRACE_ENTRY_LIMIT='32'
Remove-Item Env:OPENSHIM_CHUNK_FORCE_FIRST_GEO -ErrorAction SilentlyContinue
```

Then:

1. launch Steam Redux
2. destroy a craft/structure that should produce native legacy chunks
3. inspect `winmm_shim.log` for `[CHUNK]` blocks

Important signals:

- `owner=0x00000000 ownerBridge=0x00000000 ownerOgre=0x00000000`
  This suggests the native chunk object has no normal Redux owner/bridge path available at that probe point.
- `direct ...` values that look unstable or fault
  This means the hook target is not a plain `GameObject`, so direct EXU-style bridge reads should not be trusted as semantic state.
- `resolved=1` with a stable non-null `after=` handle and non-empty entries
  This means the stock/native GEO selection path is still functioning for that chunk object.

After that, run a second pass with:

```powershell
$env:OPENSHIM_CHUNK_FORCE_FIRST_GEO='1'
```

If forced-handle selection changes `before/after` but bridge/entity still stay null, the geometry lookup problem is secondary and the real missing piece is bridge/proxy creation.

## Preferred Fix Direction

Most feasible final solution, in order:

1. Native chunk-proxy bridge inside OpenShim or adjacent native runtime hooks.
   Goal: detect chunk-class legacy objects that already have valid GEO handles and create a transient Ogre-side proxy/render entity for them.
   Why this is now best: current logs suggest those objects do not retain a normal `GameObject -> Ogre` bridge to "unhide," so a small compatibility proxy is more realistic than trying to recover a missing owner path.

2. Native fallback that explicitly promotes chunk GEO handles into the active render path when stock selection fails.
   This is what the current `OPENSHIM_CHUNK_FORCE_FIRST_GEO` experiment is for.
   Useful, but by itself not enough if there is no downstream Ogre proxy at all.

3. Full synthetic Ogre chunk replacement.
   Spawn new Ogre entities or manually explode meshes using ExtraUtilities/toolkit data instead of reading native chunk GEO state.
   This is the heaviest option and should be treated as fallback only if the native bridge path proves impossible.
   It would require recreating chunk transforms, velocities, cleanup, material routing, collision expectations, and likely save/load edge cases.

## Practical Implication

The investigation has shifted from:

- "find the hidden native bridge"

to:

- "use the real native chunk object and GEO handle as simulation truth, then attach a lightweight Ogre proxy that mirrors that object's transform until cleanup"

That approach preserves native physics and damage while avoiding a full custom debris simulation stack.

## Why Synthetic Ogre Chunks Are Not First Choice

- Legacy chunk behavior already exists and still interacts physically.
- The badlands decomp shows fragmentation is hierarchy-based and uses real legacy geometry nodes.
- Replacing that with synthetic Ogre-only debris would duplicate logic that the engine is still already doing correctly on the simulation side.

So the best ROI remains: restore rendering of the native chunk objects instead of replacing them.

## Live Runtime Pivot

The old `ChunkRenderResolveHook` path has now effectively been ruled out as the right hook for actual fragmentation. A live runtime probe against the running Steam process found that Redux still has dedicated native chunk systems:

- `ChunkEffect` singleton at `0x00950190`
- `ChunkSimulateClass` singleton at `0x00946DD8`
- `ChunkEffect` vtable at `0x00877070`
- `ChunkEffect::Simulate`-like virtual at `0x004917F0`

The `0x004917F0` body is a much better fit for the real native chunk manager than the old render resolve hook:

- checks `this+0x802C` before doing chunk work
- reads active count from `this+0x8028`
- walks inline entries at `this+0x28 + index * 0x20`
- treats entry `[0]` as an `_OBJ76*`
- reads per-object state from at least `obj+0x14`, `obj+0x20`, and `obj+0xAC`
- removes expired entries by compacting the same inline array

One invasive debugger pass accidentally broke on `0x004917F0`, which produced a dump at the injected `int 3`, but that was still useful because it confirmed the actual live layout:

- `ChunkEffect + 0x8028` is the active chunk count
- `ChunkEffect + 0x802C` is a nonzero gate/handle-like field used before the loop
- `ChunkEffect + 0x8038..0x8048` are tuning floats
- `ChunkEffect + 0x8050` is a template/object-list pointer
- `ChunkEffect + 0x8054` is a template/object count

That breakpoint fired even when `count == 0`, so the next probe path should be non-invasive sampling of the `ChunkEffect` singleton rather than more entry breakpoints. To support that, there is now a lightweight live sampler:

- [`probe_chunk_effect_runtime.py`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\probe_chunk_effect_runtime.py)
- [`probe_chunk_effect_runtime.ps1`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\probe_chunk_effect_runtime.ps1)

The intended next step is:

1. run the sampler against a live Redux process
2. destroy a unit that produces invisible native debris
3. capture one or more nonzero `ChunkEffect` samples
4. inspect the live `_OBJ76*` entries for class/state/owner/transform fields

If that capture shows real chunk-class objects in the active `ChunkEffect` array, the next implementation hook should move from `ChunkRenderResolveHook` to this manager path instead.

## Automated `misn03` Repro Result

The new launcher/probe harness:

- [`run_misn03_chunk_probe.ps1`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\run_misn03_chunk_probe.ps1)

was used to automate:

1. clear/archive `winmm_shim.log`
2. launch `battlezone98redux.exe misn03.bzn`
3. poll the live `ChunkEffect` singleton without breaking into the game
4. archive the captured runtime report and the resulting shim log

Two automated runs were captured:

- [`chunk_effect_probe_20260317_234117`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260317_234117)
- [`chunk_effect_probe_20260317_234342`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260317_234342)

The second run is the clearest one. It observed:

- first nonzero sample: `count=2 gate=0x025D0608 templateList=0x29BD64C8 templateCount=2`
- 100 live samples over the probe window
- active count range `1..3`
- five unique active `_OBJ76*` pointers across the capture
- every sampled object had `class_id == 53` (`CLASS_ID_CHUNK`)
- every sampled object had `owner == 0`
- every sampled object had `flags == 0`

Representative first burst from the report:

- `0x30BAB388 class=53 owner=0 timer=0.123778...`
- `0x2DDF4E50 class=53 owner=0 timer=0.123778...`
- later `0x2DDF3CD0 class=53 owner=0 timer=0.147347...`

That matters because it is direct live evidence that Redux's native `ChunkEffect` manager is already tracking real `CLASS_ID_CHUNK` legacy objects. This is no longer inference from decomp alone.

The entry layout now also looks substantially more understandable. For multiple consecutive samples:

- entry word `[0]` is the chunk `_OBJ76*`
- entry word `[1]` stays zero in the observed runs
- entry words `[2..4]` behave like position floats
- entry words `[5..7]` behave like velocity floats

Example for object `0x30BAB388` across the first 10 samples:

- position-like tuple moves from `(-0.5508, 4.3508, -3.7072)` to `(-0.5508, -0.0984, -3.7072)`
- velocity-like tuple stays stable near `(0.0707, -1.8111, -0.9526)`

That is exactly the kind of data a shim-side Ogre proxy needs.

## Updated Conclusion

The chunk-restore path is now much clearer:

- Redux still creates real native `CLASS_ID_CHUNK` objects and simulates them through `ChunkEffect`.
- Those objects are directly enumerable from the live `ChunkEffect` active-entry array.
- The active-entry array already appears to expose object pointer plus position/velocity-style state.
- The sampled chunk objects still have no owner bridge (`owner == 0`), which reinforces the earlier conclusion that there is no normal `GameObject -> Ogre` path to recover.

So the most feasible restoration path is now:

1. hook or mirror the `ChunkEffect` active-entry list, not `ChunkRenderResolveHook`
2. create a transient Ogre proxy per active `CLASS_ID_CHUNK` object
3. drive proxy transform/lifetime from the live `ChunkEffect` entry and/or the backing `_OBJ76*`
4. keep native chunk simulation untouched

At this point the missing piece is no longer "do chunks really exist?" They do. The remaining job is to render the already-simulating native chunk list.
