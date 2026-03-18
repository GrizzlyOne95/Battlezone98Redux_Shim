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

## March 18 Native Hook Result

The next step was moving this runtime proof into OpenShim itself so the shim could observe the real native chunk manager without an attached debugger.

OpenShim now hooks the `ChunkEffect::Simulate` vtable slot directly:

- vtable slot: `0x0087708C`
- original function: `0x004917F0`
- shim hook: `ChunkEffectSimulateHook`

That hook samples the active `ChunkEffect` array before calling the original virtual. Sampling before the original mattered: post-call tracing often only saw `count=0`, but pre-call tracing immediately matched the external sampler and the user's `misn03` repro.

With `OPENSHIM_CHUNK_EFFECT_TRACE=1`, the shim now logs live entries like:

- `count=2 gate=0x025D0608 templateCount=2`
- `entry[0] obj=0x3096CF70 classId=53 owner=0 pos=(...) vel=(...)`
- `entry[1] obj=0x2D39D948 classId=53 owner=0 pos=(...) vel=(...)`

This closes the loop on several earlier hypotheses:

- the real fragmentation path is not exposed through the old `ChunkRenderResolveHook`
- Redux still creates and simulates real native `CLASS_ID_CHUNK` objects
- those live chunk objects still have no normal `owner` bridge to Ogre
- the active manager already exposes object pointer, position, and velocity per chunk

So the best hook point for restoration is now clear: `ChunkEffect`, not the stock chunk render resolve path.

## March 18 Placeholder Proxy Result

After switching the placeholder prototype to consume only true live `ChunkEffect` entries, the old "everything exploded" failure mode went away.

The new proxy debug path now:

- initializes only from real `ChunkEffect` active entries
- filters to `class_id == 53`
- uses the entry position directly instead of trying to infer transform from every live GEO object
- updates from the existing render heartbeat rather than from the old broad GEO resolve path

The automated `misn03` proxy-debug run at:

- [`chunk_effect_probe_20260318_000140`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260318_000140)

showed:

- `Placeholder proxy debug: enabled`
- `Initialized billboard debug set=...`
- stable nonzero `CHUNKEFFECT` entries during live chunk simulation
- no new crash dump during the automated capture window

That is not yet full visual confirmation of restored debris, but it is the first stable run where Ogre billboard debug resources were created from the true native chunk list instead of from generic live GEO objects.

## March 18 Automation Tightening

The `misn03` harness is now more useful as an unattended regression tool instead of just a one-off probe:

- [`run_misn03_chunk_probe.ps1`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\run_misn03_chunk_probe.ps1) can now set chunk log budget, trace entry limits, chunk-effect tracing, proxy debug, and post-capture wait time for a single automated run
- [`run_misn03_chunk_probe_series.ps1`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\run_misn03_chunk_probe_series.ps1) can repeat the `misn03` repro multiple times and summarize proxy lifecycle events per run

OpenShim's proxy debug logging was also tightened to emit low-noise lifecycle markers:

- `tracking obj=...`
- `assigned obj=... billboard=...`
- `release obj=... reason=expired`

That matters because it lets the shim answer "did a real native chunk reach the Ogre-side placeholder path?" entirely from archived logs, without requiring a debugger or a manual screenshot for every pass.

The automated series runs on March 18 consistently showed:

- proxy initialization succeeded
- real `CLASS_ID_CHUNK` entries were tracked into proxy slots
- billboard assignment happened for those same native chunk objects

Representative unattended runs:

- [`chunk_effect_probe_20260318_071733`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260318_071733)
- [`chunk_effect_probe_20260318_071826`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260318_071826)

In both cases the first proxy lifecycle lines looked like:

- `tracking obj=...`
- `assigned obj=... billboard=...`

## March 18 Long-Wait Lifecycle Result

A longer single automated run with a larger log budget and a longer post-capture wait:

- [`chunk_effect_probe_20260318_072541`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260318_072541)

finally captured not just tracking and assignment, but expiry and billboard-slot reuse:

- `tracking obj=0x29C042B8 ...`
- `assigned obj=0x29C042B8 billboard=0x298F45A0 ...`
- `tracking obj=0x2CEDD708 ...`
- `assigned obj=0x2CEDD708 billboard=0x298D9270 ...`
- `release obj=0x2CEDD708 billboard=0x298D9270 reason=expired`
- later reuse of that same billboard slot for a different chunk object

So the proxy manager is now doing the full expected placeholder lifecycle on unattended runs:

1. observe real native chunk entries from `ChunkEffect`
2. allocate or reuse a proxy slot
3. assign an Ogre billboard
4. expire the proxy once the native chunk stops appearing

## March 18 Template Identity Result

The next question was whether a live native chunk entry carries any stable piece identity beyond just "some `CLASS_ID_CHUNK` object."

The richer runtime probe now captures:

- `obj + 0x64` as a likely chunk template reference
- `obj + 0x78/0x7C/0x80` as the live parent/sibling/child links
- a raw snapshot of the `ChunkEffect` template list
- one level of sub-structure snapshots beneath each unique template reference

That probe showed a very important result: the candidate template reference at `obj + 0x64` dereferences to a tiny named template block whose first field is an ASCII string pointer.

Representative unattended capture:

- [`chunk_effect_probe_20260318_074532`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\snapshots\chunk_effect_probe_20260318_074532)

Representative live sample:

- `entry[0] obj=... template=0x259A0C08 ...`
- `entry[1] obj=... template=0x2002FC40 ...`
- template ref `0x259A0C08` -> string `chunk1`
- template ref `0x2002FC40` -> string `chunk2`

This is the first direct proof that Redux's native chunk simulation preserves a stable per-piece name at runtime, not just anonymous physics state.

It also lines up with the asset side. The same Steam install already contains stock Ogre-era resources like:

- `iechunk1.geo`
- `iechunk1.mesh`
- `iechunk2.geo`
- `iechunk2.mesh`

and the Ogre/BZ logs show those assets being discovered and loaded during startup.

## Updated Restoration Read

This narrows the real rendering problem substantially:

1. native chunk simulation already preserves piece identity as `chunkN`
2. stock Redux already ships many corresponding Ogre chunk meshes for stock assets
3. the missing piece is therefore not "invent what chunk piece this is"
4. the missing piece is "bind the native chunk piece identity to an Ogre renderable at runtime"

That changes the practical fix design:

- for stock assets, the fastest path is likely to reuse existing Ogre chunk meshes by combining the source object's model family/prefix with the native `chunkN` template name
- for custom assets, the same native `chunkN` identity can drive an exported/generated mesh path when no stock Ogre chunk mesh exists

In other words, the comprehensive solution now looks less like "reverse the whole fragmentation system" and more like:

1. cache the dying object's source model identity before the bridge disappears
2. read the live native chunk template name (`chunk1`, `chunk2`, etc.) from `obj + 0x64`
3. resolve or synthesize the corresponding Ogre mesh for that `(source-prefix + chunkN)` pair
4. attach that render proxy to the existing native `ChunkEffect` lifecycle already proven in-shim

## Final Auto-Path Conclusion

At this point the automatic/runtime-only investigation is effectively exhausted on the key questions it can answer without building the full restoration feature:

- native chunk simulation exists and is stable
- `ChunkEffect` is the correct runtime manager hook
- live chunk entries are real `CLASS_ID_CHUNK` objects
- those chunk objects have no normal Redux owner bridge
- the native chunk objects preserve stable piece identity as `chunkN`
- stock Redux already ships many matching Ogre chunk meshes
- the placeholder proxy lifecycle works against the true native chunk list

What the automated probes did **not** fully recover yet is the stock source-family prefix at the exact moment of fragmentation. That is now the remaining engineering problem, not the remaining reverse-engineering mystery.

So the most feasible restoration implementation is:

1. hook earlier at the death/fragmentation boundary or another still-bridged source-object path
2. cache the source object's model/class identity while that information is still intact
3. combine that cached source-family prefix with the native `chunkN` template name
4. spawn or attach the matching Ogre chunk mesh to the existing native chunk lifecycle
5. fall back to generated/exported custom chunk meshes when no stock Ogre chunk asset exists

If that prefix cache proves awkward, the fallback remains viable:

- keep using `ChunkEffect` as the authoritative native simulation source
- render a shim-managed Ogre proxy from offline-exported chunk meshes keyed by mod asset data instead of stock Redux naming

But either way, the core direction is now settled: preserve native chunk simulation and repair only the rendering bridge.

## Updated Practical Read

At this point the problem is no longer "find where chunks exist." They exist, and Redux tracks them natively in a dedicated manager.

The remaining gap is specifically:

1. native `ChunkEffect` creates and simulates chunk-class `_OBJ76*` objects
2. those objects have valid class/state/position data
3. those objects do not carry a normal Redux `owner -> Ogre` bridge
4. therefore they stay physically active but visually absent unless OpenShim creates a render-side proxy

So the most feasible restoration path remains:

1. track active `ChunkEffect` entries in-shim
2. create transient Ogre proxy visuals for those live `CLASS_ID_CHUNK` objects
3. mirror their position/lifetime from the native manager
4. later replace placeholder billboards with reconstructed piece geometry once the render loop is proven

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
