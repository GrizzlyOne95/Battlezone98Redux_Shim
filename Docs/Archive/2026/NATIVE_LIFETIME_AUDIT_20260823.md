# Native Lifetime / Memory-Safety Audit — 2026-08-23

Targeted crash, stale-reference, and object-lifetime audit of OpenShim and its
interaction with Redux/Ogre internals. Branch `agent/native-lifetime-audit`.

Method: static lifecycle tracing of every pointer-keyed static container in
`src/`, every worker-thread shutdown path, and the mission/save/load seams;
then Release Win32 builds plus dynamic stress runs (`lcbench` combat +
four-team fire, 80 objects, DX11 and DX9) and graceful `WM_CLOSE` shutdowns,
with final log scans.

## Confirmed and repaired (this workstream)

### 1. HUD panel fallback: restore path wrote through unvalidated cached addresses

`SetStockScrapPilotPanelsVisibleByUv` (bzr_hooks.cpp). The hide path re-reads
each cached record address under SEH and requires the stock scrap/pilot UV
block before writing, because "the engine can free and rebuild the HUD rect
heap block (mission restart, resolution change)". The matching show path
performed no such validation: it `VirtualProtect`ed each still-hidden address
to `PAGE_EXECUTE_READWRITE` and wrote the captured original into it.

A hide followed by a heap rebuild followed by the addon's show request
(the Campaign Reimagined driver reasserts on roughly a one-second cadence, so
show requests routinely land after transitions) therefore wrote an 24-byte
record into freed or reused memory inside a committed heap segment. The hide
path's own comment documents exactly this failure window; only the restore
direction was unprotected.

Repair: mirror the hide-path identity evidence in the restore path — re-read
the live record, require the stock UV match (UVs survive hiding; only w/h are
zeroed), and drop-and-rediscover on mismatch instead of writing. Validation:
structural (same guard pattern as the proven hide path), clean build, four
lcbench stress scenarios plus two graceful shutdown cycles with no new log
noise.

### 2. Net optimizer shutdown closed the wake socket before joining its owner

`ShutdownNetworkOptimizer` (net_optimizer.cpp). The reorder-wake worker reads
and recreates `g_WakeSender` without a lock. Shutdown closed that socket and
nulled the global *before* waiting for the worker, so the worker's final
iteration could send through a closed (potentially recycled) SOCKET value or
leak a sender it had just created. This violated the same join-before-free
contract the shutdown already applies to shared buffers.

Repair: close `g_WakeSender` only after `g_WakeThread` joins successfully;
if the join window lapses, leak both together rather than free under a live
thread. Validation: graceful-shutdown runs show all five workers joining with
no "workers exceeded join window" line and exit code 0.

### 3. CPU sampler shutdown freed handles after a timed-out join

`ShutdownNativeCpuSampler` (native_cpu_sampler.cpp) waited up to five seconds
for the sampler thread, then unconditionally closed the thread handle and the
wake event even when the wait timed out, handing a running worker an invalid
event and freeing state it could still touch.

Repair: refuse-to-free policy mirroring the net optimizer contract — bounded
wait, warn, and leave thread/event alone if the window lapses. Validation:
clean build and normal shutdown runs.

## Confirmed and repaired earlier on this branch (commit 4647e373)

Documented here because they bound the same audit scope:

- **Terrain proxy render-tick staleness** — the render tick had no liveness
  probe on the stored proxy entity (the sim-dispatch probe never runs there);
  now probed by name before use, and retry-path creation verifies the zone
  table still advertises the recorded source objects (`source_mismatch`
  forget).
- **TRN handle reuse** — leaked tracked HANDLE values could be reused by
  Windows and rewrite unrelated files at close; identity is now re-verified
  against the still-open handle before normalization, and the map is capped.
- **Net worker joins** — worker threads are joined before flushing/freeing
  shared buffers, refusing to free under live workers.

## Headlight world generation: authoritative mission lifecycle oracle

Review finding against the first repair: deriving
`s_HeadlightWorldGeneration` from raw local-player pointer inequality is not
proof that a world ended. A destroyed player object can be replaced by the
next mission's object at the *same address* while no refresh observes the
intermediate null, so the generation would not advance and a recycled
`Ogre::Light` address could inherit the previous world's baseline and receive
stale writes through it.

Final model (bzr_hooks.cpp):

- **Authoritative oracle — mission lifecycle seam.** `BzrSetRunningHook`
  (the proven `SetRunning` detour at `0x00434170`, byte-guarded, GOG-pinned)
  advances `s_HeadlightWorldGeneration` on *both* edges of `RUN_STARTED`:
  leaving simulation invalidates every captured baseline, entering
  simulation starts the next world's numbering. The seam fires before any
  headlight refresh reads or writes baseline state.
- **Baseline stamps.** Every entry in `g_HeadlightOriginalStates` carries the
  generation it was captured under. All restore paths
  (`RefreshHeadlightState`'s erase loop, `RestoreAllHeadlightStates`
  stand-down, and the falloff plan's idempotent-baseline reuse) treat a
  non-current stamp as discard-only: the stored light pointer is never
  dereferenced. `CaptureHeadlightState` resets an entry whose stamp does not
  match, so an address recycled by a new world's light captures fresh stock
  values instead of inheriting another object's baseline.
- **Fallback sanity signal only, gated on seam availability.** While the
  mission lifecycle seam is installed it is the *sole* generation authority:
  `RefreshHeadlightState` advances the generation from player-pointer
  changes only when `g_MissionSeamInstalled` is false. Rationale: the player
  object can legitimately change during a live world (ejection, vehicle
  transition, engine-side recreation), so treating pointer change as world
  death would discard current-world baselines and recapture already-modified
  values as stock. On installs without the seam (Steam/relocated
  executables), a changed pointer remains the only available evidence that
  the previous world ended; an unchanged pointer proves nothing there,
  which is why it is never the primary oracle.
- **Discard accounting.** Stale-world discards are counted and the first few
  per transition are logged (`[HEADLIGHT] stale-world baseline discarded`),
  so session logs show invalidation working without allowing a pathological
  map to flood the log.

Acceptance properties: no stale-world baseline can be restored into a later
world; pointer reuse cannot defeat invalidation (the seam advances regardless
of allocator behavior); same-world refreshes remain idempotent (baselines are
reused only under a matching generation); disabling the headlight feature
still restores current-generation baselines and silently drops stale ones;
and mission transitions never dereference old Ogre light pointers because the
seam callback only bumps a counter.

## Shutdown ownership model: loader-lock-safe detach

Review finding: `DllMain(DLL_PROCESS_DETACH)` called `BZROpenShim::Shutdown`,
which performs bounded joins (patch thread up to 2 s, CPU sampler up to 5 s,
each network worker up to 1.5 s). Waiting for arbitrary worker threads while
holding the Windows loader lock is unsafe — a worker needing loader service
during teardown deadlocks against the detach thread — and "leak the worker
after timeout" does not protect an explicit-unload path whose module then
unmaps under the surviving thread.

Final architecture (dllmain.cpp):

1. **Process-lifetime module pin.** At attach the module pins itself with
   `GetModuleHandleExW(PIN | FROM_ADDRESS)`. From that point an explicit
   `FreeLibrary` becomes reference-count noise: the loader will not unmap
   this DLL while the process runs. Unmapping executable code under a live
   OpenShim worker is therefore structurally impossible, not merely unlikely.
   This extends the shutdown paths' existing leak-rather-than-free policy to
   the module itself.
2. **Process termination (`lpvReserved != NULL`).** Per the DllMain contract,
   every other thread has already been terminated (e.g. by `ExitProcess`)
   before detach notifications run, and the whole address space is about to
   disappear. The detach handler logs to the debugger trace and does nothing
   else: no joins, no frees, no logger or heap work that could touch a lock a
   dying thread held. The shim relies on OS process teardown deliberately.
   (The structured log already flushes each line as it is written, so no
   end-of-session flush is lost.)
3. **Explicit unload (`lpvReserved == NULL`, FreeLibrary/load-failure).**
   Documented contract: a host that intends to unload must call the public
   `BZROpenShim::Shutdown()` export first, from one of its own normal
   threads — that is the orderly, joined, child-before-parent teardown, and
   it remains the supported path. If the module is freed without that call,
   the detach handler only stores the patcher stop flag (a plain atomic
   write) and returns; it performs no waits and no cleanup, relying on the
   process-lifetime pin to keep mapped whatever code workers still execute.
4. **No TerminateThread anywhere; no new synchronization dependencies.** The
   subsystem-level bounded joins and refuse-to-free guards reviewed on this
   branch are unchanged — they live inside `Shutdown()` and its callees,
   which now only run from normal execution contexts.

Ownership summary: worker threads own their run loops and stop on atomic
flags; `Shutdown()` owns joined, ordered teardown and may only be called from
a normal context; the detach handler owns nothing except the decision between
"OS will reclaim everything" and "signal-only wind-down"; and the module pin
guarantees that whichever path runs, OpenShim code pages outlive every
OpenShim thread.

## False positives (audited, protected by construction)

- **Satellite visibility state** (`g_SatelliteVisibilityState`): entries store
  GameObject + entity pointers, but teardown is gated on world liveness
  (clear-without-deref), exit restoration re-resolves the entity from the
  live arena, requires entity-pointer equality, `LooksLikeOgreObject`, a
  successful `getVisible`, and applied-state agreement; in-satellite sweeps
  erase unvisited entries. Hardened correctly.
- **Enhanced light-selection history** (`g_History`): keyed by list pointer,
  but stores stable light-ID hashes, never dereferenced; LRU-capped and
  distance/radius-reset, so key reuse degrades to harmless hysteresis bias.
- **Chunk identity/resolved-binding caches**: bounded sweep/erase logic and
  version-gated rebuild (`chunk_batch_invalidation.h`) with byte-exact source
  hashing; covered by unit tests.
- **Combat kite / scrap retarget / AI tuning maps**: cleared at hook resolve,
  feature disable, and bridge clear; values are scalars compared or applied
  through freshly read task endpoints, never dereferenced. Residual risk is
  behavioral only (a recycled object address inheriting Lua tuning floats
  until the next bridge call); accepted as best-effort semantics, not a
  safety defect.
- **AutoSave** (`autosave.cpp`): config/tick state only, no raw caches;
  save/load hooks re-resolve per use.
- **dllmain shutdown order**: layered child-before-parent (FXAA before
  colorspace observer, instrumentation before optimizer); the joined
  `Shutdown()` path runs only from normal execution contexts — detach no
  longer waits (see the shutdown ownership model above).

## High-confidence hazard, not repaired today

The process-wide first-chance exception log shows recurring wild transfers
with stable signatures across independent sessions and independent builds
(including pre-change ones): `eip` landing in `int3` padding of our own
winmm.dll export region (e.g. RVA `0xF6E27`, adjacent to `auxOutMessage`),
and repeated garbage-pointer faults around `OgreMain.dll+0x17FB25`. Every
process survived — something above the faulting frame swallows these — and
the identical recurrence across builds predates all changes on this branch.

Per the repair gate this is documented rather than patched: the required next
experiment is a cdb second-chance session breaking on first-chance
`0xC0000005` with our vectored logger detached, to capture the unguarded call
sites and identify which outer handler masks them, before deciding whether
the defect lives in stock engine code or in a shim trampoline.

## Validation summary

- Release Win32 build clean after each repair (only pre-existing warnings).
- Stress matrix: `lcbench` combat + four-team fire, count 80, DX11 and DX9,
  warmup 4 s / measure 8 s per arm — all arms completed, no new diagnostics,
  no terrain-proxy/headlight/HUD fallback violations logged.
- Graceful `WM_CLOSE` shutdown twice on the final binary: exit code 0 both
  times; net worker joins all succeeded within budget; sampler shutdown
  silent; final session log contains zero `[ERROR]` lines.

### Post-review revalidation (2026-08-24)

After the lifecycle-oracle and detach-architecture corrections, with current
`main` merged into the branch:

- Release|Win32 rebuild clean; all 10 ctest suites pass.
- `fourteam_fire`, 80 units, DX11 and DX9 arms: seam installed, headlight
  policy active, falloff repair applied, zero `[ERROR]`/join-window/violation
  lines. Arms end in a hard kill, so no transition edges are expected there.
- Graceful `WM_CLOSE`: exit code 0;
  `[MISSION] Mission left simulation ... transitions=1` followed by
  `[HEADLIGHT] world generation advanced to 2` — the lifecycle oracle fired
  on the real leaving edge; zero error/warning lines in the final session log.
  The entering edge shares the same counter path and was exercised in prior
  sessions where the shell started before the mission; a scripted
  shell→mission→shell→mission cycle remains manual-validation work.
- Explicit `FreeLibrary` unload of the shim itself is not exercisable by the
  game (the module is a statically imported proxy); its safety claim is the
  structural pin guarantee (code pages cannot unmap under live workers), not
  a dynamically tested unload.
