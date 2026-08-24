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
- **Headlight baselines across worlds** — captured light baselines were keyed
  by raw pointer only; recycled light addresses inherited dead baselines and
  write-back hit freed memory. Baselines now carry a world generation derived
  from tracked player identity; stale entries discard instead of restore.
- **TRN handle reuse** — leaked tracked HANDLE values could be reused by
  Windows and rewrite unrelated files at close; identity is now re-verified
  against the still-open handle before normalization, and the map is capped.
- **Net worker joins** — worker threads are joined before flushing/freeing
  shared buffers, refusing to free under live workers.

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
  colorspace observer, instrumentation before optimizer); patch-thread join
  is bounded.

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
