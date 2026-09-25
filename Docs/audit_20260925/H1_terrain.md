<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Terrain, TRN codec, colorspace diagnostic

Scope read end to end: `src/patches/terrain_proxy.cpp` (5304 lines), `terrain_semantic.cpp`,
`terrain_tile_blend.cpp`, `terrain_atlas_rect_repair.cpp`, `trn_codec.cpp`,
`dx11_colorspace_diagnostic.cpp` (2272 lines), the matching headers in `include/`
(`terrain_proxy.h`, `terrain_semantic.h`, `terrain_tile_blend.h`, `terrain_atlas_rect_repair.h`,
`trn_codec.h`, `chunk_batch_invalidation.h`, `dx11_colorspace_diagnostic.h`), the four tests, and the
relevant parts of `Docs/terrain-render-path.md`. Call sites in `bzr_hooks.cpp`, `file_io_hooks.cpp`,
`redux_compatibility.cpp`, `openshim_plugin.cpp` and `scripts/patches.json` were checked where a finding
depended on them. Two findings were confirmed with a Linux repro
(a small throwaway Linux program, not committed, built against the real `trn_codec.cpp` / `terrain_atlas_rect_repair.cpp`).

## Summary

Overall this area is in good shape: every opt-in path is dormant by default and installs nothing
unless configured (the DX11 diagnostic does two env reads and two INI reads at startup and then
returns; the terrain proxy verifies SHA-256 of both the exe and OgreMain before resolving a single
address). Ogre calls are consistently wrapped in try/catch, raw memory reads in SEH, and per-frame
hooks have cheap early-outs. The engine-independent codecs are small, allocation-bounded and tested.

Top three issues:
1. **TRN codec whole-file semantics are applied per `fwrite` chunk** by the Redux producer hook.
   The codec forces "strip trailing LFs, append one LF" and treats a leading `\n` as a record; if
   the game's writer ever emits a TRN in more than one `fwrite` (its buffer is a stack block of
   ~8 KB), chunk boundaries produce blank records or split lines. Reproduced on Linux.
2. **`TerrainAtlas::FormatWithDecimals` overflows `long long`** for a token with 19+ decimal
   places and writes a wrong value into the "repaired" CSV (reproduced: `0.8250000000000000000000`
   is rewritten as `1.0000000000000000000000`; on MSVC the UB cast yields `LLONG_MIN`).
3. **`ApplyTerrainTileBlendForCurrentMission` keys its "unchanged, skip" early-out on shim state**
   (`g_currentEdgeAlpha`) rather than on the live COLOR0 bytes, and reads the current TRN name from a
   raw absolute address that is not in `patches.json` and has no identity check of its own.

## Findings

### [Medium][Med] TRN canonicalizer is not chunk-safe but is applied per fwrite — src/patches/trn_codec.cpp:163-168, src/patches/redux_compatibility.cpp:248
```cpp
if (!output.empty())
{
    while (!output.empty() && output.back() == '\n')
        output.pop_back();
    output.push_back('\n');
}
```
`CanonicalizeTrnBytes` is documented as a whole-file normalizer (it also runs the UTF-16 heuristic
and BOM detection per call), but `ReduxTrnCanonicalFwrite` calls it on every `fwrite` payload.
The hooked call site (`Redux TRN Canonical Fwrite Hook`, `fwrite(buf,1,n,stream)` with `buf` at
`[ebp-0x20BC]`, i.e. a stack buffer) does not prove the writer flushes exactly once per file.
Repro (Linux, real codec): splitting `"[A]\r\nX=1\r\nY=2\r\n"` at byte 4 (inside the CRLF) yields
`[A]\r\n\r\nX=1\r\nY=2\r\n` (a blank record); splitting at byte 7 (mid-line) yields
`[A]\r\nX=\r\n1\r\nY=2\r\n` (a corrupt key). Both are silent data corruption of a saved TRN.
Fix (pick one): (a) in the fwrite hook, accumulate bytes per `FILE*` and canonicalize on
`fclose`/`fflush` (or when the stream changes); or (b) give the codec a streaming mode that does not
force a trailing LF, carries a pending `\r` across calls, and only decides encoding once. Add a test
that `canon(a)+canon(b) == canon(a+b)` for all split points of a sample. Verifiable on Linux
(tests/trn_codec_tests.cpp). If the writer is proven to emit exactly one fwrite per file, record that
in the patch identity text and downgrade this to a comment.

### [Medium][High] Atlas repair writes a wrong value when a token has 19+ decimal places — src/patches/terrain_atlas_rect_repair.cpp:112-115
```cpp
const double scaled = magnitude * scale;
const long long rounded = static_cast<long long>(scaled + 0.5);
const long long whole = decimals > 0 ? rounded / static_cast<long long>(scale) : rounded;
```
`ParseDotDecimal` (line 81-88) counts an unbounded number of fractional digits from an untrusted
mod CSV. With `decimals >= 19`, `scale >= 1e19` and both casts are UB (out of `long long` range).
Repro: a uniform-grid file whose off-grid row is `G.MAP,0.8250000000000000000000,0,0.125,0.125`
is reported `Repaired` and rewritten as `G.MAP,1.0000000000000000000000,...` (GCC); MSVC gives
`LLONG_MIN`, i.e. `-9223372036854775808.…`. The "repair" then corrupts the atlas mapping.
Fix: in `ParseDotDecimal`, treat `places > 15` (or any value the double cannot round-trip) as
invalid so the row makes the file `Unparsable`, or clamp `decimals` in `FormatWithDecimals` and
verify `snapped` round-trips through `ParseDotDecimal` before emitting an edit. Verifiable on Linux
(tests/terrain_atlas_rect_repair_tests.cpp).

### [Medium][Med] Tile-blend "unchanged" early-out is keyed on shim state, not on the buffer — src/patches/terrain_tile_blend.cpp:242-250
```cpp
const std::uint8_t edgeAlpha = TerrainTileBlendEdgeAlpha(blend);
if (edgeAlpha == g_currentEdgeAlpha)
{   ... "unchanged"; return; }
```
`g_currentEdgeAlpha` is process-lifetime; the COLOR0 bytes live in the terrain manager's CPU buffer
(`manager+0x80`). If Redux rebuilds that buffer (new manager instance, re-run of the shared stream
generator) between two missions that both request the same non-stock `TerrainTileBlend`, the second
mission's seams silently revert to stock while the log says "unchanged". `g_seamMaskCaptured` being
sticky is fine (the mask is deterministic) but the skip is not. The function is only reached once
per `RUN_STARTED`, and the CPU write loop is 9,409 bytes, so the early-out saves almost nothing.
Fix: decide from the buffer, e.g. read the alpha of a known seam vertex (index 0 is first row/first
column, so `vertices[0*16+12+3]`), and skip only when it already equals `edgeAlpha`; or drop the
early-out and always apply. Windows-only to verify (needs a live mission).

### [Medium][High] Raw absolute data address in feature code with no local identity gate — src/patches/terrain_tile_blend.cpp:29, 124-133
```cpp
constexpr uintptr_t kReleasedCurrentTrnName = 0x02CC40C0;
...
const auto* source = reinterpret_cast<const char*>(kReleasedCurrentTrnName);
if (!MemoryRangeHasAccess(source, MAX_PATH, false)) return false;
```
`Terrain::GetManager` and `Terrain::GetFloat` go through `HookEngine::ResolveNamedAddress`
(pattern-scanned, fail closed), but the TRN filename is read from a hard-coded VA whose only
check is "readable". The function itself would run on a Steam or relocated image if any caller
other than the GOG/fixed-base-gated mission seam (`bzr_hooks.cpp:17604-17612`) invoked it, and
would then hand `GetFloat` whatever bytes are there as a file path. This violates the project rule
that build-specific addresses belong in `scripts/patches.json` and that hooks fail closed on their
own. Fix: add a named data resolve (e.g. `Terrain::CurrentTrnName`, `mode: "address"` with an
identity note tied to `GetFloat`'s callers) and resolve it next to the other two; return early with a
warning when unresolved. Windows-only (patch workflow).

### [Low][High] Executable VAs hard-coded in terrain_proxy instead of patches.json — src/patches/terrain_proxy.cpp:44-66, 1395
```cpp
constexpr uintptr_t kZoneConstructVa = 0x007778B0;
...
void* structure = *reinterpret_cast<void**>(Rebase(0x00920EA0));   // SafeGetSceneManager
```
Fourteen release VAs plus one inline literal. This is mitigated in practice: the worker refuses to
touch any of them unless the exe SHA-256 matches `kExpectedExeSha256` and both detour sites match
their entry bytes, so it fails closed. It is still a rule deviation, and `0x00920EA0` is not even a
named constant. Minimal fix: hoist `0x00920EA0` to `kSceneManagerHolderVa` beside the others and add
a comment that the SHA pin is the identity gate; fuller fix is named resolves. Windows-only.

### [Low][High] Required Ogre exports that are never called gate Phase 2 — src/patches/terrain_proxy.cpp:1090-1092, 1250
```cpp
g_ogre.lockBuffer = Resolve<FnLockBuffer>(module, "?lock@HardwareBuffer@...");
g_ogre.unlockBuffer = Resolve<FnUnlockBuffer>(module, "?unlock@HardwareBuffer@Ogre@@UAEXXZ");
... reinterpret_cast<void*>(g_ogre.lockBuffer), reinterpret_cast<void*>(g_ogre.unlockBuffer),   // in required[]
```
`grep 'g_ogre\.lockBuffer('` / `unlockBuffer(` find no callers (writes go through
`WriteD3D11VertexBuffer`). `destroySceneNode` (pointer form, deliberately unused per the comment),
`getElementType` and `getElementOffset` are also resolved and never invoked. Two of these are in
the `required[]` array, so an unrelated export rename would disable Phase 2 for nothing.
Fix: delete the five resolves and their `OgreApi` members. Windows-only build.

### [Low][High] Deferred-context path breaks the "read-only" contract and logs a false success — src/patches/dx11_colorspace_diagnostic.cpp:1557-1575, 539-585
```cpp
InstallContextHooks(*deferredContext);
LogShimA(LogLevel::Info, kComponent,
    "[TERRAIN-PROBE] installed observers on newly-created deferred context=0x%p flags=0x%X", ...);
```
`PatchComVtableEntry` refuses when `current != original` (a deferred context is a different class
with its own vtable, so this is the normal outcome), yet the log claims observers were installed.
If the patch did apply, `ObserveTerrainState` would call `ReadBufferSnapshot` on the deferred
context: `context->CopyResource(staging, source)` is *recorded into the game's command list*
(a state change) and `Map(D3D11_MAP_READ)` then fails, since deferred contexts only allow
write-discard maps. Redux/Ogre 1.10 does not appear to use deferred contexts, so the impact is
low. Fix: in `ObserveTerrainState`, return early when
`context->GetType() == D3D11_DEVICE_CONTEXT_DEFERRED`, and make the log conditional on the two
`PatchComVtableEntry` results. Windows-only.

### [Low][Med] `QuerySemanticBinding` reports "query failed" instead of "slot 3 absent" — src/patches/terrain_proxy.cpp:1851-1885, 1492-1502
```cpp
if (GetVertexBuffer(operation, 3, buffer) && buffer)
```
`GetVertexBuffer` calls `VertexBufferBinding::getBuffer(3)`, which in Ogre 1.10 throws
`ITEM_NOT_FOUND` when slot 3 is unbound. The surrounding `try` turns that into `return false`, so
the full-rebuild path (`ZoneProcessHook`, lines 4956-4964) logs a Warn "binding query failed /
retainedOwner=0" whenever the semantic renderer is on but the stream has not been installed yet,
rather than the intended `slot3=0` record. Fix: call `isBufferBound(3)` (export
`?isBufferBound@VertexBufferBinding@Ogre@@QBE_NG@Z`) before `getBuffer`, or catch around just that
call. Windows-only.

### [Low][Med] One SharedPtr reference leaked per pass when the parameter re-attach fails — src/patches/terrain_proxy.cpp:3255-3266, 3287-3297
```cpp
OgreSharedPtr oldParameters;
g_ogre.getVertexProgramParameters(pass, &oldParameters);      // +1 ref held here
g_ogre.setVertexProgram(pass, programName, false);
if (oldParameters.rep && oldParameters.info && AddSharedReference(oldParameters))
{   g_ogre.setVertexProgramParameters(pass, oldParameters); ReleaseCloneHandoff(oldParameters); }
```
If `AddSharedReference` fails (or `info` is null), the reference obtained from the getter is never
released. Bounded (13 passes per material install, at most a handful of installs per mission), so
this is accounting drift rather than growth. Fix: `else ReleaseCloneHandoff(oldParameters);`.
Windows-only.

### [Low][Med] C++ exceptions can escape COM/engine hook boundaries — src/patches/dx11_colorspace_diagnostic.cpp:1493-1516, 1579-1607; src/patches/terrain_proxy.cpp:4796-4806
`HookPSSetShaderResources`/`HookOMSetRenderTargets`/`HookCreateTexture2D` call `LogSrvRecord`,
`LogRenderTargetView`, `LogTextureCreated`, which allocate (`GetDebugName` builds a
`std::vector`/`std::string`, `std::to_string`) with no try/catch; a `bad_alloc` would unwind
through d3d11/Ogre frames. `ZoneConstructHook` similarly runs `ObserveZone` (which does
`g_zoneOrdinals.emplace` and copies `candidate.meshName`) outside any catch. Realistically only
OOM triggers it. Fix: wrap the post-call bodies of the COM hooks and the `ObserveZone` call in
`try { } catch (...) {}` (the rest of terrain_proxy already follows that pattern). Windows-only.

### [Low][Low] Process-shutdown forget still calls into Ogre resource managers — src/patches/terrain_proxy.cpp:5221-5223, 2660-2684
```cpp
// Process shutdown can run after OGRE has already gone away, so this
// path forgets by name only and never touches a scene object.
ForgetTerrainProxy(TerrainForgetReason::ProcessShutdown, false, false);
```
`ForgetTerrainProxy` -> `RemoveSemanticResources` / `RemoveProxyMeshResource` call
`getMaterialManager()`, `getHighLevelProgramManager()`, `getMeshManager()` and `removeResource()`.
They are null-checked and try/catch-wrapped, and Ogre nulls its singleton pointers in the
destructors, so this is probably safe in practice, but the comment overstates it and a torn-down
`ResourceManager` reached through a still-non-null singleton is not a C++ exception. Fix: for
`ProcessShutdown`, skip the resource-manager calls entirely (there is nothing to reclaim from a
process that is exiting) and only reset shim state. Windows-only.

## Dead or unused code (list with evidence)

- `src/patches/terrain_proxy.cpp` `OgreApi::lockBuffer`, `unlockBuffer`, `destroySceneNode`,
  `getElementType`, `getElementOffset` and their `Resolve<>` lines (1090-1092, 1105, 1185-1187):
  resolved, never invoked (`grep -c 'g_ogre\.<name>('` = 0 for each). Two of them are in `required[]`.
- `include/terrain_semantic.h` `Cell::cellX/cellZ/terrainX/terrainZ` (written in
  `ProvideSemanticCell`, terrain_proxy.cpp:4119-4124) and `Vertex::mix/variant` (written in
  terrain_semantic.cpp:160-161): never read anywhere (`grep '\.mix\b\|\.variant\b'` finds only the
  writes; the JSON dump uses its own local `Cell` struct). Keep `Cell::terrainX/Z` only if a later
  phase needs them; otherwise drop the fields.
- `src/patches/terrain_proxy.cpp:5245` `g_lastRunState = currentState;` in
  `TerrainProxyMissionRunStateChanged`: the variable is only read inside `InstallHooks` (line 5080),
  which runs once before any transition is delivered, so the per-transition write is dead state.
- `src/patches/terrain_proxy.cpp:62` `kSetRunningVa`: used only to print an address in the
  "hooks installed" log; the real seam lives in `bzr_hooks.cpp`. Harmless, but the constant invites
  the reader to think this module hooks `SetRunning`.
- `src/patches/terrain_tile_blend.cpp:45-98` `MemoryRangeHasAccess` / `IsExecutableAddress` are
  near-verbatim copies of the same helpers in `autosave.cpp` and `openshim_updater.cpp`
  (`grep -rln 'bool MemoryRangeHasAccess'`). Candidate for one shared header.
- `src/patches/dx11_colorspace_diagnostic.cpp`: no dead code found; every `kMax*`/helper is used.
- `include/chunk_batch_invalidation.h`: fully exercised by `tests/chunk_batch_invalidation_tests.cpp`
  and `bzr_hooks.cpp` (`#include` at line 28); no dead members.

## Performance notes

- **When disabled, both subsystems are inert.** `InitializeDx11ColorSpaceDiagnostic` reads two env
  vars and two INI keys, then returns before any thread or vtable patch; no per-frame cost exists.
  `TerrainProxyRenderFrameTick` costs one plain-int compare and one atomic load per world frame when
  no capture is configured; `InitializeTerrainProxyPhase2` returns before creating its worker unless
  a feature is opted in, so the two inline detours are never written.
- `terrain_proxy.cpp` `ZoneProcessHook` (4809-4990): once a proxy exists it does
  `ProxyEntityStillRegistered()` (a `std::map<std::string,...>` lookup inside Ogre) on every zone
  dispatch; on the retry path (`selected && !proxyCreated`) `ResolveClusterCandidate` copies the mesh
  name into a `std::string` per dispatch. Both are bounded and opt-in; fine as is.
- `CaptureClusterHeightSignature` makes 4,225 `g_heightAt` calls per dirty event (documented as
  never per frame). During continuous deformation this runs every tick for the selected cluster;
  acceptable for a diagnostic, but consider hashing only on `fullDirty` if it shows up.
- `dx11_colorspace_diagnostic.cpp:902-912` `LogCurrentViewports` allocates a `std::vector` on every
  `OMSetRenderTargets` while the color-space observer is on; a
  `std::array<D3D11_VIEWPORT, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE>` removes the
  allocation. `LogSrvRecord` does `GetDesc`+`GetResource`+`QueryInterface`+mutex per bound SRV for the
  process lifetime even after the 768-record cap is hit; an early `if (set.size() >= limit) return;`
  before the COM calls would make the steady state nearly free.
- `ObserveTerrainState` (probe) is cheap after its capture budget is spent (two atomic loads), but
  when `TerrainRenderProbeCluster` names an ordinal that never appears it keeps doing
  `IAGetVertexBuffers`/`IAGetIndexBuffer`/`ComIdentity` on every 38,400-index triangle-list draw. Bounded
  by the 4,096-cluster cap.
- `terrain_proxy.cpp` `InstallSemanticMaterial` compiles up to 13 HLSL programs inside the zone
  dispatch hook under `g_mutex`, on the game thread. Expected for this diagnostic, but it means a
  stall of hundreds of ms at selection time; nothing to fix, just worth knowing when reading traces.
- `ComputeSha256` streams the exe and OgreMain once on the worker thread (64 KB reads); one-time.

## Positive notes (things done well that later work should keep doing)

- Fail-closed identity: the terrain proxy pins both module hashes and re-checks entry bytes before
  each detour; the DX11 observer waits for the loader, retries a bounded number of times, and refuses
  to re-hook a vtable slot that someone else already changed.
- Ownership discipline in terrain_proxy: scene objects are destroyed by *name* with a
  process-lifetime serial, stored pointers are re-verified against the live zone table before use,
  and every forget path funnels through one idempotent `ForgetTerrainProxy`. The crash-dump-backed
  comments explain why.
- Raw-memory reads use SEH helpers with no C++ objects in the same frame; Ogre calls sit in
  try/catch; D3D11 readbacks go through staging buffers and release every COM reference on all paths.
- Bounded logging everywhere (`InsertBounded`, `typeCount <= 8`, `waits % 600`), so a misbehaving
  diagnostic cannot flood the log.
- The atlas repair deliberately hand-parses dot-decimal numbers and formats without `%f`, documenting
  the locale hazard; the TRN codec preserves scalar-single-precision semantics in
  `terrain_semantic.cpp` with explicit SSE intrinsics and a comment tying each step to the released
  function.
- `chunk_batch_invalidation.h` keeps the whole reuse policy in a header that builds without Ogre, and
  its tests assert every render-affecting field moves the version and every uncertain input rebuilds.
- Config clamping in `ReadConfig` (capture count, stride, coverage, aim distance) rejects NaN and
  out-of-range values rather than trusting the INI.
