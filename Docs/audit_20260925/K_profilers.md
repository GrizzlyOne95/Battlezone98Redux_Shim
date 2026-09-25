<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Profilers, samplers, and trace instrumentation

Scope read end to end: `src/patches/ogre_animation_profiler.cpp` + all ten `ogre_animation_profiler/*.inl`,
`include/ogre_animation_profiler.h`, `include/ogre_profiler_algorithms.h`, `tests/ogre_profiler_algorithms_tests.cpp`,
`src/patches/walker_cockpit_trace.cpp`, `src/patches/pilot_fp_animation_trace.cpp`, `src/patches/native_cpu_sampler.cpp`,
`src/patches/render_queue_trace.cpp`, `include/player_kill_trace.h`, `tests/player_kill_trace_tests.cpp`, plus the matching
headers, `src/plugin/openshim_plugin.cpp` (init/shutdown order), `src/engine/shim_log_client.cpp` / `shim_log_sink.cpp`
(what `LogShimA` does), `openshim.ini(.example)`, and the investigation docs that own each instrument.

## Summary

Overall these five subsystems are in better shape than typical diagnostics: every hook fails closed on prologue/export
mismatch, C++-object functions are kept out of `__try` frames, tables are fixed-size with drop counters, and the CPU sampler
follows a written suspend-window discipline. The three issues that matter:

1. **The Ogre profiler's entry-detour installer calls `LogShimA` while every other thread in the process is suspended**
   (`patch_scopes.inl:195-238`). `LogShimA` allocates a `std::string`, takes the log SRW lock and the CRT `FILE` lock. This
   path runs on every GOG DX11 launch because the shipped DX11 skin-source-shadow policy installs the `softwareVertexBlend`
   detour through it, so a heap-lock/log-lock holder among the ~100 suspended threads hangs the game with the main thread
   frozen. Fix is a two-line scope change.
2. **The profiler defaults ON when the INI key is absent** (`config_state.inl:73`, `profiling_helpers.inl:165-166`) while
   the INI template, `OGRE_ANIMATION_PROFILER.md`, and the roadmap all call it opt-in. Any install whose `openshim.ini`
   predates the key gets seven detours, D3D vtable hooks, ~20-200 log lines per second and a CSV beside the exe.
3. **The pilot-FP tracker is only half diagnostic now**: its `ResolveLocalFirstPersonEntity` is a production SDK export
   (EXU `TargetLocalFirstPerson`) that performs a full, allocating scene enumeration on every call, and it keeps a worker
   thread polling at 40 Hz for the whole process even with the trace off. The trace/manipulation half (about 1,200 lines) is
   a concluded investigation (2026-08-27/28) and belongs in a diagnostics-only build; the resolver does not.

Answers to the five scope questions are collected at the end of the Findings section ("Scope questions").

## Findings

### [HIGH][HIGH] Logging (heap + SRW lock + CRT FILE lock) inside the all-threads-suspended window — src/patches/ogre_animation_profiler/patch_scopes.inl:195-238

```cpp
SuspendedThreadSet suspended(static_cast<uint8_t*>(target), patchLength);   // :195 suspends every other thread
...
LogShimA(LogLevel::Info, kComponent,
    "[OgreProfile] installed %s entry observer implementation=0x%p ...", ...);  // :231-238, threads still suspended
return true;                                                                    // :239, ~suspended runs at :240
```
`SuspendedThreadSet` resumes its threads only in its destructor at end of scope (`:102-116`). Both `LogShimA` calls at
`:200-210` (the `ready && bytes mismatch` branch) and `:231-238` (success) execute before that. `LogShimA` →
`WriteFormattedMessage` does `std::string line = formatted;` (`src/engine/shim_log_client.cpp:71`, process-heap lock), then
the sink does `AcquireSRWLockExclusive(&g_LogLock)` and `fprintf`/`fflush` on a `FILE*` (`src/engine/shim_log_sink.cpp:206-208,
129-138`, CRT per-stream lock). If any suspended thread holds the process heap lock (any thread inside `HeapAlloc` during
mission load), the log SRW lock, or the log `FILE` lock, the profiler worker blocks forever with the main and render threads
suspended: a hard hang, not a crash. The CPU sampler's own header (`native_cpu_sampler.cpp:25-33`) states exactly this rule and
obeys it; the profiler does not.

Exposure is not limited to profiling: `InstallOgreObservers` installs the `Mesh::softwareVertexBlend` detour for the
shipped DX11 skin-source-shadow policy (`observer_install.inl:284-312`, policy default on per `worker_api.inl:169-178`) via this
same function, so every GOG DX11 launch passes through the window once per detour (up to six detours when profiling).

Fix: build the log strings into locals, put `SuspendedThreadSet` and the byte write in an inner `{}` block, and log after the
block (or call `suspended.Release()` explicitly before any `LogShimA`). Verifiable only on Windows.

### [HIGH][MED] Profiler enables itself when the INI key is missing — src/patches/ogre_animation_profiler/config_state.inl:73, profiling_helpers.inl:137-167

```cpp
constexpr int kDefaultProfilerEnabled = 1;                       // config_state.inl:73
...
g_ProfilerRequestSource = "build-default";
return kDefaultProfilerEnabled != 0;                             // profiling_helpers.inl:165-166
```
`openshim.ini.example:1030-1035` ("Default: OFF"), `reverse_engineering/OGRE_ANIMATION_PROFILER.md:3,12` ("opt-in"), and the
header comment (`ogre_animation_profiler.h:27-29`, "the diagnostic build defaults it on") disagree with each other, and there
is no diagnostic-vs-release build distinction: the same constant compiles into the shipped `Plugin_OpenShim`. The only thing
keeping the profiler off for players is the presence of `ProfileOgreAnimation = 0` in their `openshim.ini`. An INI written
before the key existed, a hand-trimmed INI, or an INI that `GetModuleFileNameA`-relative lookup cannot find (the profiler reads
the INI itself at `profiling_helpers.inl:150-158` instead of using `TryGetUserConfigBool`) turns on seven entry detours, DX9/DX11
vtable hooks, the 1-second report (`interval_report.inl`, ~20 fixed lines plus up to 160 `RenderContributorTop` lines and up to
5+5+16 top-entity lines per second) and the CSV writer.

Fix: `kDefaultProfilerEnabled = 0`, and read the key through the shared `TryGetUserConfigBool` so it follows the same INI
discovery as every other `[Diagnostics]` key. Verifiable on Linux only indirectly (`ResolveRequest` in the tests takes the
default as a parameter; a `static_assert(kDefaultProfilerEnabled == 0)` would be Windows-compiled).

### [MEDIUM][MED] D3D9 draw-observer "repair" re-runs a 9-slot vtable install (with a Warn log each) on every submission when a foreign hook owns the slot — src/patches/ogre_animation_profiler/d3d9_hooks.inl:72-97, :36-66

```cpp
if (!observerInstalled)
{
    InstallD3D9DeviceHooks(observedDevice);          // :91  GetSwapChain + 9x PatchComVtableEntry
    g_ContextVtableRefreshes.fetch_add(1, ...);
    observerInstalled = true;                        // :94  set even if nothing was installed
}
```
`PatchComVtableEntry` (`patch_scopes.inl:357-365`) logs `"... already wrapped by another observer; leaving it untouched"` at
Warn and returns false whenever the slot holds neither our hook nor the original. If ReShade, an overlay, or any other injector
wraps `IDirect3DDevice9::DrawIndexedPrimitive` after the profiler did, `vtable[82]` never equals `&HookD3D9DrawIndexedPrimitive`,
so every `D3D9RenderSystem::_render` call (about 1,500 per frame in the four-team benchmark) does `GetSwapChain`/`Release`, takes
`g_PatchMutex` nine times and writes one Warn line: tens of thousands of log lines per second and a collapsed frame time. The
per-frame branch at `:50-52` (`identity != previous || drawObserverMissing`) re-runs the same install every frame in the same
situation. `observerInstalled = true` also mis-classifies those submissions as observed, which is precisely the
"instrumentation defect" retraction in `render_submission_attribution_phase1_20260823.md`. The DX11 twin
(`d3d11_hooks.inl:63-83`) does this correctly: `RefreshContextHooks` returns false silently and `observerInstalled` stays false.

Fix: add a silent `RefreshD3D9DeviceHooks` mirroring `RefreshContextHooks` (compare each slot to hook/original, bail without
logging on a foreign pointer), set `observerInstalled` from its return value, and latch a "foreign hook present" flag so the
per-frame/per-submission checks stop retrying. Only reachable with profiling enabled. Windows only.

### [MEDIUM][MED] CPU sampler frame walk is bounded by `Esp + 4 MB`, not the thread's stack limit — src/patches/native_cpu_sampler.cpp:376-377, :383, header comment :30-33

```cpp
const uintptr_t stackLow = context.Esp;
const uintptr_t stackHigh = stackLow + kStackWindowBytes;   // 4 MB above ESP
```
The file header says "Module ranges and stack bounds used by the walk are computed outside the window and cached"; module
ranges are, stack bounds are not. A 32-bit Redux process packs one-hundred-plus 1 MB stack reservations into the address space,
so `[Esp, Esp+4 MB)` routinely spans the reservations of two or three *other* threads. A garbage frame-pointer value (the walk
follows raw `[ebp]` and only requires monotonic increase, `:381-405`) can land on another thread's `PAGE_GUARD` page.
`ReadStackSlot` catches the `STATUS_GUARD_PAGE_VIOLATION`, but the guard bit is consumed by the fault, so that other thread
later runs off its stack without the guard and fail-fasts far from the sampler. The same header explains this hazard for pages
below ESP (`:34-37`) and then leaves it open above ESP.

Fix: when a thread is first tracked (`RefreshThreads`, outside any suspend window) read its TEB via
`NtQueryInformationThread(ThreadBasicInformation)` → `TebBaseAddress` → `NT_TIB::StackBase`, store it in `ThreadEntry`, and
clamp `stackHigh` to it (fall back to the 4 MB window only when the query fails). Windows only.

### [MEDIUM][HIGH] Pilot-FP worker thread runs at 40 Hz for the process lifetime even with the trace off — src/patches/pilot_fp_animation_trace.cpp:1679-1693, :1642-1668

```cpp
g_Enabled.store(TraceRequested(), std::memory_order_release);
...
g_WorkerThread = _beginthreadex(nullptr, 0, TraceThreadProc, nullptr, 0, nullptr);   // :1687 unconditional
```
`TraceThreadProc` resolves exports once (`:1644-1651`) and then, with `g_Enabled == false`, does nothing but
`Sleep(kPollSleepMs /*25*/)` (`:1658-1667`) until shutdown. The header's justification ("Tracking is always active because
companion APIs depend on its lifetime checks", `pilot_fp_animation_trace.h:32-33`) is not borne out by the code:
`ResolveLocalFirstPersonEntity` (`:1695-1712`) calls `ResolveTrackerExports()` itself and reads no state the thread maintains
when the trace is off (`RefreshWorldTarget`/`RefreshFpTargetViaEnumeration` only run under `g_Enabled`). Every player pays a
thread and 40 timer wakeups per second for nothing. Fix: `if (!g_Enabled) return 0;` after the export resolve (or do not start
the thread), and replace the `Sleep` poll with an event wait. Windows only.

### [MEDIUM][MED] `ResolveLocalFirstPersonEntity` (production SDK export) runs a forced, allocating full-scene enumeration on every call — src/patches/pilot_fp_animation_trace.cpp:1695-1712, :783-994

```cpp
std::lock_guard<std::mutex> trackerLock(g_TrackerMutex);
if (!ResolveTrackerExports()) return false;
RefreshWorldTarget();
RefreshFpTargetViaEnumeration(true);        // :1708  force => bypasses the 1.5 s throttle at :786
```
Per call: a 16 KB `std::vector<void*> sceneObjects(4096)` (`:816`), then for every skinned entity in the scene two
`std::string` constructions for `hasAnimationState("idle"/"stand2Kneel")` (`:850-851` via `:541-554`), `getMesh()->getName()`
string copies, `NormalizeMeshBase` lowercasing, `SafeEntitySkeletonName`, and pushes into four vectors of strings
(`:807-864`). This is exported as `OpenShimResolveLocalFirstPersonEntity` (`openshim_sdk_provider.cpp:548`) and the header
tells callers not to cache the result beyond one operation (`pilot_fp_animation_trace.h:41-44`), so a Lua script that plays
FP animations each frame drives a per-frame O(skinned entities) walk with dozens of allocations on the sim thread under
`g_TrackerMutex`. Fix: keep the forced path only when the current FP entity is no longer present or the world entity changed;
otherwise reuse the last result within a short TTL (100 ms) and defer all string work behind `g_Enabled`. Windows only.

### [LOW][HIGH] Sampler tracks threads by TID only; a reused TID pins the dead thread's handle and hides the new thread — src/patches/native_cpu_sampler.cpp:460-467, :495-508

```cpp
const bool known = std::any_of(threads.begin(), threads.end(),
    [&](const ThreadEntry& tracked) { return tracked.tid == entry.th32ThreadID; });
if (known || threads.size() >= kMaxThreads) continue;
```
When a tracked thread exits and Windows hands its TID to a new thread, `live` still contains the TID, so the stale entry is
kept, its handle keeps the exited thread object alive for the rest of the capture, `GetThreadTimes` reports a frozen total
(delta 0), and the new thread is never sampled. `creationFileTime` is already captured (`:484`) but never compared. Fix: on a
TID match, re-read creation time and replace the entry when it differs. Windows only.

### [LOW][HIGH] `HookEntityUpdateAnimation` is a pure pass-through detour that the installer nevertheless requires — src/patches/ogre_animation_profiler/ogre_hooks.inl:1-9, observer_install.inl:356, :412-425, :497

```cpp
void __fastcall HookEntityUpdateAnimation(void* self, void*) { ... real(self); }   // collects nothing
...
if (!updateAnimation || !updateAnimationCore || !blendEntry) return false;         // observer_install.inl:356
const bool usable = animationEntry && animationCoreEntry && blendEntry;           // :497
```
Installing it costs a trampoline page, an exe-code write, and one full suspend-all-threads cycle (the window of the HIGH
finding above), and its absence makes the whole profiler report "unavailable". Remove the detour, the `animationEntry`
requirement, `g_EntityUpdateAnimationDetour` and `g_RealEntityUpdateAnimation`. Windows only.

### [LOW][HIGH] `RefreshContextHooks` writes the D3D11 context vtable without the guard the file says is mandatory — src/patches/ogre_animation_profiler/d3d11_hooks.inl:396-404 vs profiling_helpers.inl:1346-1362

```cpp
if (!VirtualProtect(begin, byteLength, PAGE_READWRITE, &oldProtection)) return false;
for (...) if (vtable[entry.index] == entry.original) vtable[entry.index] = entry.hook;   // raw store
```
`WritePointer`/`WritePointerGuarded` exist precisely because "the Windows loader can re-protect that page between the
VirtualProtect here and the store, which is exactly how the DX11 observer took the process down twice on 2026-08-22"
(`profiling_helpers.inl:1346-1350`). The refresh path (invoked from the render thread on every submission where the slot is
missing) bypasses it. Fix: route the writes through `WritePointer`. Windows only.

### [LOW][HIGH] Raw build-specific globals duplicated across three diagnostic TUs and not registered in `scripts/patches.json` — walker_cockpit_trace.cpp:89-90, pilot_fp_animation_trace.cpp:78,85 (and bzr_hooks.cpp:2706, 17128, 19096)

```cpp
constexpr uintptr_t kUserObjectRva = 0x00517AFC;
constexpr uintptr_t kSceneManagerStructureAddr = 0x00920EA0;
```
Five copies of the same two addresses, none in `patches.json` `globals` (grep for `517AFC`/`920EA0`/`userObject` in
`scripts/patches.json` is empty), which is the project rule in `AGENTS.md` and `Docs/AGENT_PATCH_WORKFLOW.md:7,19`. The walker
trace additionally reads `main+0x517AFC` and patches exe `E8` call sites and IAT slots (`:457-466`, `:1733-1822`) without
`IsCompatibleGameVersion()`; the pilot trace does check it (`:386`). Both are INI-gated and every read is SEH-guarded, so the
practical risk is a garbage object walk on a non-2.2.301 build rather than a crash. Fix: add `globals` entries and resolve
through them; gate the walker install on `IsCompatibleGameVersion()`. `patch_registration_tests` runs on Linux.

### [LOW][HIGH] Pilot/walker traces read `Ogre::Resource::getName()` through the pinned header layout, and the pilot one guards it with a `catch (...)` the file itself says cannot catch faults — pilot_fp_animation_trace.cpp:662-678 (vs :476-479), walker_cockpit_trace.cpp:627-630

```cpp
try { const Ogre::MeshPtr& mesh = g_FnEntityGetMesh(entity); if (!mesh.isNull()) return mesh->getName(); }
catch (...) {}
```
`getName()` is an inline member read of `Resource::mName`, so it depends on the retail object layout that
`config_state.inl:16-17` says is "not ABI-identical to pristine upstream 1.10.0". The profiler avoids this by resolving
`?getName@Resource@Ogre@@UBE...` (`observer_install.inl:146-148`). It works today (logged names are correct), so this is a
fragility note: use the export under `__try` in both traces. Windows only.

### [LOW][HIGH] Profiler worker never exits when profiling is off — src/patches/ogre_animation_profiler/worker_api.inl:54-148

With `collectProfilerData == false` (the shipped INI), after `ogreInstallFinished` the loop body is only
`Sleep(kPollSleepMs /*25*/)` until process exit, i.e. 40 wakeups per second on every GOG install because the shadow policies
start the worker (`:199-223`). Fix: `if (!collectProfilerData && ogreInstallFinished) break;` after the install block.
Windows only.

### [LOW][MED] CSV output goes beside the executable, append-only across sessions, never rotated — src/patches/ogre_animation_profiler/csv_top.inl:33-41

```cpp
const std::string csvPath = ... iniPath.substr(0, slash + 1) + "openshim_ogre_profile.csv";
if (fopen_s(&file, csvPath.c_str(), "a+") != 0 || !file) return;
```
In Program Files / Steam directories the open fails silently and the CSV never appears; where it succeeds the file grows one
row per second forever across runs. The sampler already does this correctly (`GetGameLogPath`, per-PID name,
`native_cpu_sampler.cpp:711-723`). Fix: `GetGameLogPath("openshim_ogre_profile_<pid>.csv")`, `CREATE_ALWAYS`.

### [LOW][MED] Render-queue trace budget is never reset on re-attach, while the group suppression stays active — src/patches/render_queue_trace.cpp:73, :189-196, :255-266

`RenderQueueTraceShutdown` clears `g_AttachedTo` on mission end; the next mission re-attaches (`:218-253`) with `g_FramesLeft`
still 0, so nothing is logged, yet `g_SkipGroup` (a visible render change) keeps applying. Either reset `g_FramesLeft` and
`g_Frame` in `RenderQueueTraceShutdown`, or do not re-attach. Windows only.

### [LOW][HIGH] Engine-independent profiler test is not in the CTest suite, and half of what it tests is code the shim never runs — tests/ogre_profiler_algorithms_tests.cpp, include/ogre_profiler_algorithms.h

`tests/CMakeLists.txt` has no `ogre_profiler_algorithms_tests` target (only `scripts/run_ogre_profiler_tests.ps1`, MSVC x86),
so the Linux lane never builds it although it includes nothing Windows-specific. Of the helpers it exercises,
`UpdateAndCheckDuplicate` (`:214-224`), `ContributorRank`/`RanksBefore`/`InsertContributor` (`:226-260`), `ResolveRel32Thunks`
(`:269-296`) and `ResolveRequest`/`RequestDecision`/`RequestSource` (`:29-40`, `:116-128`) have no caller under `src/`
(verified by grep); the runtime uses its own implementations (`FindOrClaim*` + `exchange` for duplicates, `std::sort` for
ranking, `ResolveModuleExportImplementation` for thunks, `ProfilerRequested` for the request decision). The tests therefore
pass regardless of the shipped logic. Fix: add the target to `tests/CMakeLists.txt` and either make the runtime call these
helpers or delete them. Verifiable on Linux.

## Dead or unused code (list with evidence)

- `IsOgreAnimationProfilerRequested()` — defined `worker_api.inl:158-161`, declared in the header, no caller anywhere
  (`grep -rl` hits only the definition and declaration). `IsPilotFpAnimationTraceRequested()` (`pilot_fp_animation_trace.cpp:1674`)
  likewise.
- `g_PointerPatches` (`config_state.inl:477`) is write-only: pushed at `patch_scopes.inl:266, 330, 371`, never read.
  `EntryDetour32::original` (`config_state.inl:233`, filled at `patch_scopes.inl:221`) is never restored either; both exist for
  an unpatch path that does not exist (hooks are documented as process-lifetime).
- `HookEntityUpdateAnimation` no-op detour (finding above).
- `OgreProfilerAlgorithms::UpdateAndCheckDuplicate`, `ContributorRank`, `RanksBefore`, `InsertContributor`, `ResolveRel32Thunks`,
  `ResolveRequest`, `RequestDecision`, `RequestSource` — test-only (finding above). `EqualsAsciiCaseInsensitive` is used only by
  `IsNativeTransientChunkMeshName` in the same header (fine).
- Pilot trace: `_ReturnAddress()` captured inside the enumeration loop and on promotion (`:869-871`, `:918-920`, `:979-981`) is
  always the tracer's own worker/SDK frame, so the logged `caller=/rva=/inMain=` fields on `[FPAnim][FP] candidate/acquired`
  lines are meaningless noise; `g_EntityHasSkeletonExport` (`:172`) is stored but only ever cast into `g_FnEntityHasSkeleton`.
- Pilot trace `SafeEntitySkeletonName` (`:680-685`) returns only `"present"/"none"`; it is logged as `skeleton=%s` and copied
  into `TargetState::skeletonName[64]` as if it were a name.
- `.inl` fragment split: `GetOpenShimIniPath` is cut between `config_state.inl:708-714` and `profiling_helpers.inl:1-7`; no
  `.inl` has a guard or a header comment saying it is a fragment, and they compile only in the order listed in
  `ogre_animation_profiler.cpp`. Maintainability hazard rather than dead code, but it belongs on this list.
- Duplicated helpers that should be shared (each verified by reading both copies): `FindExportsContaining`
  (`profiling_helpers.inl:1481`, `walker_cockpit_trace.cpp:486`, `pilot_fp_animation_trace.cpp:996` — three near-identical
  export-directory scanners although `OgreRuntime::ResolveExport` exists), `TryGetRttiClassName` (walker `:404`, pilot `:331`,
  and `CopyRttiTypeName` in `profiling_helpers.inl:590`), `MainModuleContains`/`CallerRva`/`CopyText` (walker + pilot),
  `GetOpenShimIniPath` (profiler + pilot, walker inlines a third), `PatchDirectCalls`/`PatchIatEntries`/`WriteRel32`/`WritePointer`
  (walker `:1719-1822`, pilot `:1104-1218`), and four `IsTruthy`/`StringIsTruthy` variants with different accepted spellings
  (sampler `:208-219` rejects only `0/false/FALSE/off`; walker `:267-273`; pilot `:182-190` also `disabled`; profiler uses the
  shared header one).
- Concluded investigations still carrying runtime code (see Scope questions, item 5): `render_queue_trace.cpp` (its one question
  is answered in `Docs/FOG_COMPOSITOR_QUALIFICATION_20260908.md`, verdict "No"), and the trace/manipulation half of
  `pilot_fp_animation_trace.cpp` (qualification complete 2026-08-27/28 per
  `reverse_engineering/player_pilot_animation_management_20260827.md`).

## Performance notes

- **Zero-cost when disabled?**
  - Ogre profiler: no. With the shipped INI (`ProfileOgreAnimation = 0`) the worker thread still starts for the two
    default-on policies, polls every 25 ms forever, installs the `softwareVertexBlend` detour (DX11) and the Entity
    `getCastShadows` vtable hook (both DX9/DX11) — those two are intended production behaviour, the polling is not. The
    hooks' disabled paths are one relaxed atomic load plus the policy work (`ogre_hooks.inl:291-313`, `:178-212`). About 4 MB of
    zero-initialised slot tables live in `.bss` (`g_RenderContributorSlots` 2048 x ~1 KB, `g_EntityProfileSlots` 4096 x ~300 B,
    etc.); they are demand-paged and only touched when profiling, so the cost is address space, not RSS.
  - Pilot-FP trace: no; permanent 40 Hz worker (finding above). Hooks are installed only when enabled.
  - Walker trace: yes; `Requested()` false returns before any thread or resolve (`:1891-1895`).
  - CPU sampler: yes; env check only (`:969-974`).
  - Render-queue trace: one latched atomic load per world frame (`bzr_hooks.cpp:39478` → `render_queue_trace.cpp:102-110`).
- **Bounded memory when enabled?** Profiler: all tables fixed-size, open-addressed with probe caps and a drop counter
  (`FindOrClaimRenderContributorSlot`, `profiling_helpers.inl:536-588`); the per-second report builds vectors bounded by table
  size (`csv_top.inl:188-189` reserves 256 but can reach 2048 x ~800 B = 1.6 MB transiently, fine). CSV unbounded across
  sessions (finding). Pilot: 64 bindings per target (`kMaxBindings`), 4096-object enumeration cap; but `LogBoundFloatForTarget`
  throttles only `dt` and `weight` (`:1296-1337`), so `setTimePosition` on a bound state logs every call — one line per frame
  per state when an FP clip is scrubbed. Walker: fixed arrays; one `[WALKF]` line per `_renderScene` call, which includes
  shadow-camera re-entries, so several lines per frame. Sampler: 512 KB flush threshold, `sampleScratch` per tick, output
  unbounded unless `OPENSHIM_PROFILE_NATIVE_CPU_DURATION` is set (documented, `logs\`-relative, per-PID name).
- **Shutdown**: sampler is the model (5 s join, on timeout it deliberately leaks the thread and event and says so,
  `:1007-1036`). Profiler and pilot trace wait 2 s then `CloseHandle` and zero the handle regardless (`worker_api.inl:245-250`,
  pilot `:1720-1725`); the profiler's worker can still be inside `InstallEntryDetour32` under `g_PatchMutex` at that point,
  which is harmless only because this runs at process exit. Walker never joins its arm worker; that thread checks
  `g_Enabled` every 500 ms for up to 300 s and exits (`:1874-1888`), acceptable. Render-queue trace removes its listener on
  mission end and at shutdown.
- Hot-path notes worth keeping in mind when profiling *is* on: `HookSceneManagerRenderSingleObject` does an RTTI walk and up to
  eight Ogre string reads on first sight of each contributor (metadata capture is CAS-latched, `profiling_helpers.inl:632-703`),
  then only atomics; `HookD3D11RenderSystemRender` does two loads + one compare per submission (`d3d11_hooks.inl:66-83`) plus a
  once-per-frame `_getDevice`/`GetImmediateContext` pair; `HookSoftwareVertexBlend` calls `findElementBySemantic` twice per blend
  for the policy even with profiling off (`profiling_helpers.inl:1110-1146`), linear in the element list, acceptable.
- Walker trace's `Node::setPosition` IAT hooks take `g_Mutex` (and `g_WriterMutex` on a match) on every node write in the exe
  while the trace is on (`:338-356`); diagnostic-only, but it means the walker capture perturbs the frame it measures.

## Scope questions

1. **Zero-cost when disabled** — see Performance notes. Two thread pollers (profiler worker, pilot worker) are the concrete
   non-zero costs on every player's machine; both are one-line fixes.
2. **Bounded memory / output / safe shutdown when enabled** — memory yes everywhere (fixed tables, caps with drop/truncation
   counters); output is unbounded for the profiler CSV (across sessions), the sampler file (by design, DURATION-capped), and
   the traces' log volume; shutdown is sound for the sampler and render-queue trace, "best effort with a timeout" for the
   profiler/pilot, and join-less for the walker.
3. **CPU sampler suspend discipline** — `SuspendThread`/`ResumeThread` are balanced on every path including
   `GetThreadContext` failure (`:553-576`); nothing inside the window allocates, logs, takes a lock, or calls the loader
   (`RefreshModules`/`RefreshThreads`/`FlushBuffer` all run outside it); the walk reads only at or above ESP through
   SEH-guarded volatile loads. No loader-lock or heap-lock deadlock path found in the sampler. The two real gaps are the
   stack upper bound (guard pages of other threads) and TID reuse, both filed above. Note the irony that the *profiler's*
   `SuspendedThreadSet` is where the suspend-window rule is broken.
4. **D3D9/D3D11 COM and vtable safety** — refcounts are balanced: `QueryInterface(IDXGIDevice)`/`GetAdapter`/`GetParent` each
   paired with `Release` (`d3d11_hooks.inl:444-475`), `GetImmediateContext` released (`:497-503`), `GetSwapChain` released
   (`d3d9_hooks.inl:308-317`); the creation hooks add no references. vtable patching goes through `PatchComVtableEntry`, which
   refuses to overwrite a slot it does not recognise and records the original once, and `WritePointer` guards the store against
   loader re-protection. The two defects are the D3D9 re-install storm/misclassification and the unguarded `RefreshContextHooks`
   store, both filed above. Hooks are process-lifetime and become pass-through after shutdown, which is the right choice for
   shared class vtables.
5. **What is still used**:
   - *Ogre profiler* (`ProfileOgreAnimation`, `OPENSHIM_PROFILE_OGRE_ANIMATION`, `OPENSHIM_PROFILE_ISOLATE`): driven by
     `reverse_engineering/run_live_combat_benchmark.ps1` and `capture_fourteam_visuals.ps1`; Phase 1/2 attribution
     (2026-08-23) concluded that submission count is not the bottleneck. It cannot simply be removed because the same TU hosts
     two shipped, default-on policies (native chunk shadow suppression; DX11 skin-source shadow retrofit,
     `OGRE_ANIMATION_PROFILER.md:154-190`). Recommendation: move `HookEntityGetCastShadows`, `RetrofitVertexSourceShadow`/
     `EnsureDx11SoftwareSkinSourceShadows` and the `softwareVertexBlend` detour into a small production TU (they need
     `InstallEntryDetour32`, `PatchEntityVtables`, `IsValidatedGogChunkShadowRuntime`), then compile the remaining ~5,000
     profiler lines only in a diagnostics configuration.
   - *CPU sampler* (`OPENSHIM_PROFILE_NATIVE_CPU*`): Phase 2 (2026-08-23) found and fixed its target (the per-frame
     `GetProcAddress` in `GetHeadlightOgreApi`); `analyze_cpu_samples.py` and the benchmark script still reference it. It is
     env-only and truly dormant, so it is the cheapest to keep; a diagnostics-only build is still the right home.
   - *Walker cockpit trace* (`WalkerCockpitTrace`, `OPENSHIM_WALKER_TRACE`): `walker_cockpit_jitter_native_result_20260902.md`
     is "ONE NARROW BLOCKER" and `Docs/STEAM_ROADMAP_BBCODE.txt:262` still lists the visual confirmation as pending — open,
     keep. It does add two `winmm.dll` exports (`OpenShimSetWalkerCase`, `OpenShimWalkerTraceSummary`, in
     `tests/winmm_export_baseline.txt`) for a diagnostic, which a diagnostics build would drop from the public surface.
   - *Pilot FP trace* (`TracePilotFPAnimations`, `OPENSHIM_TRACE_PILOT_FP_ANIMATIONS`, `PilotFPAnimManip*`,
     `OPENSHIM_PILOT_FP_MANIP*`): the investigation is closed ("EXECUTED — QUALIFIED", "PROVEN-RUNTIME", public API shipped
     in EXU on 2026-08-28). What remains production is `ResolveLocalFirstPersonEntity` + `RefreshWorldTarget` +
     `RefreshFpTargetViaEnumeration` + the liveness checks (about 500 lines). The E8/IAT observers, the five
     `HookAnimation*` functions, the manipulation gate and the inventory poll are the concluded experiment. Split the resolver
     into its own TU and move the rest to the diagnostics build.
   - *Render-queue trace* (`TraceRenderQueues`, `SkipRenderQueueGroup`, `OPENSHIM_TRACE_RENDER_QUEUES`): its single question
     is answered in `Docs/FOG_COMPOSITOR_QUALIFICATION_20260908.md` (row 2, verdict "No"; the doc records the experiment). It
     is 278 lines, cheap when off, and a clean removal candidate (or diagnostics-only) now that the fog design has moved on.
   - *Player-kill trace* (`TracePlayerKills`): the header is pure classification used by `bzr_hooks.cpp:13410-13557` and the
     tests; the INI text still calls the activnet rule "a hypothesis under test" — keep as is (runtime side is outside this
     scope).

## Positive notes (things done well that later work should keep doing)

- Fail-closed detour installation: exact prologue bytes, bounded thunk following, module/executable-page checks, and a
  per-thread EIP-in-patch-range check before writing (`patch_scopes.inl:119-240`, `profiling_helpers.inl:1418-1473`).
- PE identity gate before any production vtable write (`IsValidatedGogChunkShadowRuntime`, `profiling_helpers.inl:108-119`) and
  a policy that disables itself for the process on the first failed repair (`RetrofitVertexSourceShadow`).
- Consistent isolation of SEH from C++ objects, with the reasoning written next to it (walker `:295`, `:618-620`; pilot
  `:471-479` including the note that `catch (...)` does not catch AVs under `/EHsc`; sampler `:343-361`).
- The CPU sampler's design notes (`:7-37`): explicit suspend-window rules, health counters reported with every capture so a
  capture that observed nothing cannot pass as one that observed nothing happening, jittered sampling interval, bounded join
  with a deliberate leak on timeout.
- SceneManager liveness verified by checking that its vptr lives in `OgreMain.dll` via `GetModuleHandleExA(FROM_ADDRESS)`
  after a real crash dump (`pilot_fp_animation_trace.cpp:436-469`), and the enumeration walk kept under SEH even after that
  check.
- `PatchComVtableEntry` refusing to stack on a foreign wrapper, plus `WritePointerGuarded` documenting the loader race that
  motivated it; `IatPatch::WaitForModuleLoadToFinish` used before touching the renderer's IAT (`worker_api.inl:78-92`).
- The hand-built `RenderQueueListener` vtable with each slot's index logged, so an ABI mismatch shows as a wrong-looking trace
  instead of a silent crash (`render_queue_trace.cpp:27-54`).
- Fixed-size, lock-free contributor tables keyed by semantic identity rather than transient object address, with drop and
  "unobserved" counters so instrumentation loss is measured instead of assumed (`config_state.inl:94-105`, `:332-344`).
- INI/documentation discipline for the traces that ship off: walker and pilot both read their key with default 0 and say why
  (`walker :288-290`, `pilot :214-216`), and every instrument has an owning document under `reverse_engineering/` or `Docs/`.
