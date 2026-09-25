<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# bzr_hooks.cpp lines 11000-22000

Scope: `/home/user/Battlezone98Redux_Shim/src/patches/bzr_hooks.cpp` lines 11000-22000 (read end to end in ~400-line chunks), with `include/bzr_hooks.h` and `include/bzr_object_layout.h` for context. Helpers defined outside the range were looked up where the range calls them (`EnvFlagEnabled` 33757, `ReadLocalPlayerNetIdValue` 9755, `GameObjectFromHandleGog` 363, `ResolveMainModulePtr` 3517, `LooksLikeOgreObject` 3319, `CollectLiveGameObjectsFromArena` 31492, `LoadCareerStatsFile` 9932, `ResolveLocalPlayerLookupForVerifiedGogBuild` 42805, the per-tick drivers `ChunkEffectSimulateHook` 40403 and `LegacyWorldUpdateRenderQueueHook` ~39446, `RetryDeferredRuntimeHooks` 36017, `ResolveBzrHooks` 34446). Build flags: `ExceptionHandling=Sync` (/EHs) in `BZROpenShim.vcxproj:74` and `Plugin_OpenShim.vcxproj:74`.

## Summary

The range is ~11,000 lines holding roughly 35 unrelated feature blocks (lobby flags/bans/mutes, career statistics, satellite visibility, weapon convergence, HUD/radar layout, turbo, unit VO, headlights, pilot flashlight, pilot team restore, BZRNet settings) plus five research probes. Code quality is generally high: nearly every engine read is under SEH in a POD-only leaf, GameObject identity is proven by an exact vtable-slot compare rather than a heuristic, most detours are byte-guarded with roll-back, and multiplayer gating is consistent. The top issues are:

1. `InstallJumpSnipingProbeIfRequested` (17721) writes the GOG-only `GetPlayerHandle` address into the shared `g_BzrFn_GetPlayerHandle` *before* the build/byte check, so on a non-GOG image with the trace env var set every later consumer (career stats damage probe, player-kill trace, `TryGetLocalPlayerWorldPosition`) calls into an unverified address: a fail-open.
2. `HandleUnitTurboBoundary` (18842) runs on every unit's simulate boundary and calls `GetModuleHandleA` twice per call whenever EXU is absent (18794-18797): loader-lock syscalls, two per unit per tick, for a feature whose overrides map is usually empty.
3. Several inline detours at fixed absolute addresses are "identified" by a 3-5 byte generic prologue (`55 8B EC`, `55 8B EC 6A FF`, `55 8B EC 83 EC 10`) with no image-base or Steam gate (13577, 17256, 16005), and every absolute address in the range is missing from `scripts/patches.json` (project rule). One of them (`UiEnsureManualObjectDedupeHook`) then replays a `ret 8` call through the trampoline, so a wrong-function match corrupts the stack rather than failing closed.

Secondary: career statistics do a synchronous read+rewrite of `career_stats.cfg` on the render callback for every derived kill/death; the satellite fix walks all 4096 arena slots with two `VirtualQuery` calls per object on every sim tick while in satellite view; two convergence log helpers and their guard flags are dead; the scene-teardown Ogre detours are installed although the file itself documents that they never fire.

## Findings

### [Medium][High] GOG-only player-handle address published before the build check — src/patches/bzr_hooks.cpp:17721
```cpp
g_BzrFn_GetPlayerHandle = reinterpret_cast<FnGetPlayerHandle>(kGogGetPlayerHandleAddr);
g_BzrFn_GameObjectGetObjByHandle = &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)
```
This runs as soon as `OPENSHIM_TRACE_JUMP_SNIPING` is set (16654), unconditionally on Steam/relocated builds, and *before* the `ExpectedBytesMatchAt(kGogPersonSimulateEntryAddr, ...)` guard at 17735. The probe itself fails closed when the bytes mismatch, but the two globals it already wrote are consumed elsewhere with no further identity check: `PublishDamageForCareerStatsFromProbe` 13139 (`g_BzrFn_GetPlayerHandle()` on every damage event), `TryReadDistributedTraceInfoForHandle` 13355, `TryCaptureLocalPlayerSnapshot` 16733, and the exported `TryGetLocalPlayerWorldPosition` (42822). The comment block at 42797-42804 explicitly states the address is a GOG constant and "callers must have already established they are on that exact build"; this site does not. Fix: move the two assignments below the byte check (or replace them with a call to `ResolveLocalPlayerLookupForVerifiedGogBuild()` guarded by `!g_IsSteamExe && GetModuleHandleW(nullptr) == 0x00400000` as `InstallMissionTransitionSeamIfPossible` does at 17612). Windows-only to verify.

### [Medium][High] Two loader-lock syscalls per unit per sim tick in the turbo boundary hook — src/patches/bzr_hooks.cpp:18792-18806, 18842-18846
```cpp
HMODULE module = GetModuleHandleA("exu.dll");
if (!module)
    module = GetModuleHandleA("ExtraUtilities.dll");
```
`HandleUnitTurboBoundary` is entered from the naked `UnitTurboBeginHook` (18861) at the per-unit simulate boundary (the hooks are installed by `InitializeGlobalTurboConfig`/`SetUnitTurboFromBridge` whenever the bytes match, regardless of whether any override exists). With `boundary == 0` it calls `ResolveExuCullingCallback()` first, which performs the `GetModuleHandleA` pair on every call when EXU is not loaded (the cache only short-circuits the `GetProcAddress`, not the module lookups). `GetModuleHandleA` takes the loader lock; two per unit per tick on an 80-unit map is ~10k lock acquisitions per second of sim. Fix: resolve the callback once (or on a 1-second re-check tick) into `g_ExuFn_UpdateCullingForUnit`, and early-out of `HandleUnitTurboBoundary` when both `g_UnitTurboOverrides.empty()` and the callback is null. Windows-only.

### [Medium][High] Generic-prologue identity for fixed-address inline detours (fail-open risk) — src/patches/bzr_hooks.cpp:13577, 17256, 16005
```cpp
static const uint8_t kExpectedProlog[] = { 0x55, 0x8B, 0xEC };            // 13577 DistributedRecordDeathInt
static const uint8_t kExpectedBytes[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF }; // 17256 FUN_007D2B70
constexpr uint8_t kRadarLayoutExpectedBytes[6] = { 0x55,0x8B,0xEC,0x83,0xEC,0x10 }; // 15945 radar builder
```
These byte patterns match thousands of functions in the image; the code at 13581-13582 even says so ("Detailed delta check omitted"). None of the three installers checks `g_IsSteamExe` or the image base (contrast `InstallMissionTransitionSeamIfPossible` 17612-17620, which requires base 0x00400000, and `InstallCareerStatsMpHookIfPossible` 16930-16936, which adds a 16-byte body check). Consequence on a relocated or differently laid-out image: the detour lands on an unrelated function. For `UiEnsureManualObjectDedupeHook` (17160) that is worse than a no-op: the hook treats `this` as a widget, reads `widget+0x20` as a `std::string` (17173) and then calls the trampoline as `void(__thiscall*)(void*, UiOgreSharedPtr)` — a `ret 8` contract — so a wrong function with a different arity corrupts the caller's stack. Fix: add a body-byte cross-check at a fixed offset (as 16930 does) or an operand that names a known global, and gate on the pinned image base; longer term, register these as `resolves` in `scripts/patches.json` with identity notes so the `[RESOLVE]` line documents the evidence. Windows-only.

### [Medium][High] Absolute addresses hardcoded in feature code rather than `scripts/patches.json` — src/patches/bzr_hooks.cpp:12065, 12984, 15943-15953, 16135-16137, 17150-17153, 17458-17460, 18262-18272, 19137-19140, 21723-21745, 21851-21852
```cpp
constexpr uintptr_t kRadarLayoutBuilderAddr = 0x00492EC0;        // 15943
static constexpr uintptr_t kGlobalTurboComissOperandAddr = 0x00601CA3; // 18262
constexpr uintptr_t kBzrNetNicknameAddr = 0x009453E0;           // 21739
```
`grep` of `scripts/patches.json` finds none of 0x00492EC0, 0x00434170, 0x007D2B70, 0x00601CA3, 0x00601C92, 0x0044CBD0, 0x0059DEA5, 0x00577290, 0x006796D0, 0x0059D340, 0x005C7FB0, 0x008723F4, 0x009C91D0, 0x00946708, 0x00945704, 0x009453E0, 0x00764760, 0x0088A4FC, 0x00889418, 0x00681A00, 0x005C710E, 0x0068CA30 (only 0x00417F60 appears). AGENTS.md requires build-specific sites in `patches.json`. Also `0x00462380` (GameObject::GetHandle) is defined three times: `kGogGameObjectGetHandleAddr` 12984, `kGameObjectGetHandleAddr` 18272, and as a literal in `GameObjectFromHandleGog` 373; `kGogGameObjectGetTeamAddr` 12065 duplicates evidence already in `bzr_object_layout.h`. Fix: move to `resolves`/`globals` entries (many already have the identity evidence in comments), and collapse the GetHandle constant into one named resolve. Verifiable on Linux via `tests/patch_registration_tests.cpp` once registered.

### [Medium][High] Synchronous career-stats file rewrite on the render callback per kill/death — src/patches/bzr_hooks.cpp:13612-13658, 13660-13694
```cpp
AcquireSRWLockExclusive(&g_CareerStatsLock);
std::unordered_map<std::string, std::string> data;
LoadCareerStatsFile(data);      // std::ifstream read of career_stats.cfg (9932)
...
if (!SaveCareerStatsFile(data)) // full rewrite (9962)
ReleaseSRWLockExclusive(&g_CareerStatsLock);
```
`CareerRecordDerivedKill` runs from `CareerStatsEventSink` inside `TickOpenShimEventLayer`, which `LegacyWorldUpdateRenderQueueHook` (39469) calls every rendered frame. Each SimKill that involves the local player therefore parses and rewrites the stats file on the frame; in a firefight with several kills in one frame that is several full read/write cycles inside the Ogre render-queue callback. The `RecordDeathHook` comment at 16858-16863 explains this exact cost was just removed from the *detour* path, but the drain reintroduces it on the frame thread. The lock is also acquired/released manually with no RAII, so a `std::bad_alloc` from the map leaves it held forever. Fix: accumulate deltas in memory and flush on a timer / on `SimSessionEnded` (the MP path already has `CareerStatsMpSessionThreadProc`), and wrap the SRW lock in a small scope guard. The accounting logic is engine-independent, so a batching layer would be testable on Linux; the hook wiring is Windows-only.

### [Medium][Med] Naked thunks call C++ helpers that may clobber SSE state at mid-function sites — src/patches/bzr_hooks.cpp:18861-18897, 19478-19503
```cpp
pushad
pushfd
push dword ptr [ebp - 0x08]
push dword ptr [ebp - 0x04]
call HandleEmissionLightState   // uses std::cos + double math (19466-19470)
```
The ordnance thunks at 18066-18073 justify not saving XMM0-7 with a site-specific argument ("the nearest preceding instruction ... is a CALL"). The turbo (`UnitTurboBeginHook`/`UnitTurboEndHook`) and emission-light thunks make no such argument, yet both sit mid-function (0x00601C92 in the throttle comparison sequence; 0x0044CBD0 in `LightRenderClass::Simulate`'s per-light loop) and call helpers that do emit SSE: `HandleEmissionLightState` computes `std::cos(kPi * seconds * rate)` and stores a float; `HandleUnitTurboBoundary` can reach EXU's `EXU_UpdateCullingForUnit` (18830), whose contents the shim cannot audit. If the host has a live XMM register across those stolen bytes, it is silently corrupted. Additionally `UnitTurboBeginHook` replays `fstp dword ptr [eax+8]` *after* the C call, so x87 `st(0)` must survive `HandleUnitTurboBoundary` (balanced MSVC code preserves it, but nothing enforces it). Fix: either add the same site-specific proof comment (and cite the preceding CALL) or make the thunks self-sufficient by saving/restoring XMM0-7 (`sub esp,128; movdqu [esp+n],xmmN ...`) and, for the begin hook, spilling `st(0)` around the call. Windows-only; needs a disassembly check of the two sites.

### [Medium][Med] Satellite visibility sync does ~2 `VirtualQuery` per live object per sim tick while in satellite view — src/patches/bzr_hooks.cpp:13944-14180, 12071-12116
```cpp
static void* s_satObjects[kGameObjectArenaSlotCapacity];
const size_t totalObjects = CollectLiveGameObjectsFromArena(s_satObjects, ...);
for (size_t i = 0; i < totalObjects; ++i) {
    ...
    if (!TryReadObjectIlluminationAndEntity(obj, illumination, entity)) // -> TryGetGameObjectFieldBase -> 2x VirtualQuery
```
`SyncSatelliteVisibility` is called from `ChunkEffectSimulateHook` (40436) every sim tick. In satellite view it walks every live arena slot and, for each, `TryGetGameObjectFieldBase` issues two `VirtualQuery` syscalls (object page + vtable page) before the exact vtable compare, then `LooksLikeOgreObject` issues another for the entity, plus an `unordered_map` find/insert. On a 500-object map that is ~1500 syscalls per tick for the duration of the overview. The author's own note at 13049-13055 observes the arena is always mapped and the vtable compare alone is the identity proof. Fix: use a cheaper identity path for arena entries (skip the object-page `VirtualQuery`; the vtable pointer can be range-checked against the main image the way `IsExecutableMainImageAddress` does, or cached per slot per tick), and/or throttle the sync to ~100 ms since the visibility gate does not need per-tick fidelity. Windows-only.

### [Low][High] Retry loops that log forever after their window expires — src/patches/bzr_hooks.cpp:13590-13592, 16955-16962
```cpp
} else if ((now - g_DistributedRecordDeathIntFirstTick) >= kDistributedHookRetryWindowMs) {
    Log(L"[PKTRACE] Distributed hook still mismatched after %llums at 0x%08X - failing closed\n", ...);
}
return;
```
The message says "failing closed" but nothing latches; the function is re-entered every `kDistributedHookRetryMs` (500 ms, 2474) from `ChunkEffectSimulateHook` and logs at 2 Hz for the rest of the session. `InstallCareerStatsMpHookIfPossible` has the same shape at 16955-16962 (a line every 15 s forever, resetting `g_CareerStatsMpHookFirstAttemptTick` each time). Fix: set a terminal `...GaveUp` flag on window expiry and early-return on it. Windows-only.

### [Low][Med] C++ `try/catch` used as the memory guard under /EHs — src/patches/bzr_hooks.cpp:17164-17214
```cpp
try {
    auto* bytes = reinterpret_cast<uint8_t*>(widget);
    ...
    const std::string& name = *reinterpret_cast<const std::string*>(bytes + kUiWidgetNameOffset);
    void* sceneRoot = *reinterpret_cast<void**>(kBzrSceneRootPtrAddr);
} catch (...) {
```
Both projects compile with `ExceptionHandling=Sync`, so `catch (...)` only catches C++ exceptions (the Ogre `ItemIdentityException` it is meant for); an access violation from a bad widget/scene-root read propagates into the engine. Every other engine read in this range lives in an SEH leaf; this one does not. Also `*reinterpret_cast<const std::string*>` reads a msvcr120-built `std::basic_string` through the current toolset's layout; it works today because both use the 16-byte SSO layout, but it is an implicit ABI assumption that deserves a `static_assert(sizeof(std::string) == 24)` and a comment. Fix: move the raw reads into a POD `__try` leaf that returns the name pointer/length and the scene manager, keep `try/catch` only around the two Ogre calls. Windows-only.

### [Low][Med] Headlight enumeration passes weakly identified pointers into Ogre — src/patches/bzr_hooks.cpp:19565-19581, 19549-19562, 20142-20153
```cpp
return vtable >= mainBase && vtable < mainBase + 0x00600000;   // IsLiveHeadlightObjectSlot
...
auto* bridge = *reinterpret_cast<uint8_t**>(gameObject + 0xF0);
return bridge ? *reinterpret_cast<void**>(bridge + 0xA8) : nullptr;  // TryGetGameObjectHeadlight
```
`RefreshHeadlightState` walks all 4096 arena slots using only the range heuristic (any exe-resident vtable passes, including the abstract `_purecall` tables the satellite code documents at 12047-12058), then hands `bridge+0xA8` straight to `api.setDiffuse/setRange/setVisible` without the `LooksLikeOgreObject`/`PilotFlashlightLightLooksLive` vetting the satellite and pilot-flashlight blocks apply. A non-GameObject slot whose +0xF0/+0xA8 happen to be readable produces a virtual call through garbage inside OgreMain (a fastfail there bypasses the SEH at 19809). Fix: use `TryGetGameObjectFieldBase` (exact GetTeam tag) for arena entries and require `PilotFlashlightLightLooksLive(light)` before the first Ogre call. Windows-only.

### [Low][Med] Unbounded `g_HeadlightFalloffPlanLogged` set and stale-address suppression — src/patches/bzr_hooks.cpp:19123, 19738
```cpp
static std::unordered_set<void*> g_HeadlightFalloffPlanLogged;
if (!g_HeadlightFalloffPlanLogged.insert(light).second) return;
```
Never cleared. It grows one entry per distinct light address per process, and because Ogre recycles light allocations across missions, a new light at an old address is silently treated as already logged, defeating the "one line per light per session" intent. Fix: clear it in `HeadlightNotifyMissionRunStateChanged` next to the generation bump (20000-20010). Windows-only (trivial).

### [Low][Low] Threading model for shared POD tables is undocumented and internally inconsistent — src/patches/bzr_hooks.cpp:13024-13026, 13478-13486, 18848-18851, 36445
`g_CareerPendingVictims` is described as "touched only from the event drain ... main thread" (13024) but is read from `DistributedRecordDeathIntHook` and `TraceNetPlayerRecordDeath` inside the engine's death path (13478, 13539) and cleared from `ResetCareerStatsData` on the settings path (13879); `g_UnitTurboOverrides` (an `unordered_map`) is written by `SetUnitTurboFromBridge` (36445) and read in `HandleUnitTurboBoundary` (18848). Elsewhere the file uses `Interlocked*` between what it calls "the sim thread" and "the reconcile tick" (1893, 17918-17931). If simulation and the Ogre render-queue callback are the same thread these are all fine; if not, the research reads are benign races but the `unordered_map` read during a rehash is UB. Fix: one comment at the top of the file stating which hooks run on which thread, and either drop the `Interlocked` ceremony or protect the map. Not verifiable on Linux.

### [Low][High] Per-refresh allocations and env-var lookups on periodic/hot paths — src/patches/bzr_hooks.cpp:20101, 20197, 16361-16365 (used at 37006), 12808
```cpp
std::unordered_set<void*> touched;                       // 20101, every 200 ms
if (EnvFlagEnabled("OPENSHIM_TRACE_HEADLIGHTS"))         // 20197, every 200 ms
return EnvFlagEnabled("OPENSHIM_TRACE_OWNED_OBJECT_REVEAL") || EnvFlagEnabled("BZR_TRACE_OWNED_OBJECT_REVEAL"); // per reveal event
```
`EnvFlagEnabled` (33757) is an uncached `GetEnvironmentVariableA` each call. `ShouldTraceOwnedObjectReveal` is evaluated at the top of `TraceOwnedObjectReveal` (37006) for every owned-object reveal, even when tracing is off; `ShouldTraceUnitVo` (18491) shows the right pattern (function-local `static const bool`). Fix: cache both flags at init (they are already re-read in `InitializeGlobalImprovementConfig` for other keys) and make `touched` a function-static that is `clear()`ed. Windows-only.

### [Low][Low] Emission-light fix never destroys dormant renderers — src/patches/bzr_hooks.cpp:19497-19502
```cpp
emissionInactive:
    // Keep the renderer dormant instead of invoking its deleting destructor.
    jmp dword ptr [g_EmissionLightLoopResume]
```
Stock deletes a light renderer when its active flag clears; the fix keeps every such renderer (and its Ogre `Light`) alive so it can be re-activated. If the producer never re-activates (craft destroyed, effect retired), nothing in the range frees it; over a long session the light list grows. This may be reclaimed by the owning object's destructor (not visible here), so it is a question rather than a defect: confirm the owner frees dormant renderers, or add a "dormant for N seconds" reap. Windows-only.

## Dead or unused code (list with evidence)

- `LogPlayerConvergenceMountFault` (14455-14486) and `LogPlayerConvergenceLayoutCrossCheck` (14488-14533): grep of `src/ include/ tests/` finds only the definitions; their guard flags `g_PlayerReticleConvergenceMountFaultLogged` (1912) and `g_PlayerReticleConvergenceLayoutCheckLogged` (1914) are written only by these two functions. Remove both, or wire the layout cross-check into `ApplyWalkerConvergencePostPass` once per session (it is a useful assertion that was never connected).
- Scene-teardown forget hooks `SceneManagerClearSceneHook` / `SceneManagerDestroyAllMovablesHook` / `InstallSceneTeardownForgetHooksIfPossible` (17310-17433): the mission-seam comment at 17437-17451 states the executable "contains no call to Ogre::SceneManager::clearScene or destroyAllMovableObjects at all", so the two OgreMain detours are installed from `ResolveBzrHooks` (34946) and `RetryDeferredRuntimeHooks` (36030) for callbacks that never fire. Either remove them or keep one as a belt-and-braces guard with a comment saying so.
- Duplicate constants: `kGogGameObjectGetHandleAddr` (12984) and `kGameObjectGetHandleAddr` (18272) both equal 0x00462380, and `GameObjectFromHandleGog` (373) uses the literal; `kGogGameObjectGetTeamAddr` (12065) duplicates the evidence already pinned in `include/bzr_object_layout.h`.
- Copy-pasted config loaders: `EnsureBansConfigLoaded`/`SaveBansConfig`/`IsBanIdConfigured`/`AddBanConfigEntry` (11228-11397) and `EnsureMutesConfigLoaded`/`SaveMutesConfig`/`IsMuteIdPersisted`/`AddMuteConfigEntry` (11435-11599) are the same `<stable_id> [name]` file format with different globals; a single templated `IdentityListFile` would remove ~170 lines and make the parsing testable on Linux. Similarly `TryLoadUnderAttackAlertModeFromConfig` (11714) and `TryLoadTargetReticlePopupModeFromConfig` (11921) are byte-identical except for the key string, and both `TryGetEnv...Mode` wrappers (11751, 11958).
- `ParseHeadlightColour` (19908) and `ParsePilotFlashlightColour` (21081) carry identical 10-entry preset tables.
- `IsExuModuleLoaded` (18293) and `ResolveExuCullingCallback` (18792) both probe `exu.dll`/`ExtraUtilities.dll` by name; one resolver would do.
- Research-only code that ships in the release DLL and is dead unless an env var is set: jump-snipe probe (16654-16899, 17710-17761, `OPENSHIM_TRACE_JUMP_SNIPING`), player-kill trace (13326-13610, `OPENSHIM_TRACE_PLAYER_KILLS`), satellite pre-hide/validate fixtures (12347-12365, 13907-13942, 14195-14301, `OPENSHIM_SATVIS_*`), UI orphan injection (17155, `OPENSHIM_TEST_UI_MANUAL_OBJECT_ORPHAN`). Not defects, but they are the first candidates to move to a separate `bzr_research_probes.cpp` during the split.

## Performance notes

- `ApplyWalkerConvergencePostPass` (14784) and `TryGetWalkerGameObjectPosition` (14566): each convergence pass costs up to four `VirtualQuery` calls per weapon-aim call (`IsLikelyGameObjectEntry` two, the in-guard vtable query one, `IsExecutableMainImageAddress` one) and runs per craft per frame for every Wingman/Turret/TurretTank while either convergence feature is on. The vtable page is immutable image memory; its `VirtualQuery` result could be cached per vtable address.
- `RefreshHeadlightState` (20012) walks 4096 slots every 200 ms and allocates a `std::unordered_set` per pass (see finding); `RefreshPilotFlashlightState` (20945) and `RefreshPilotTeamRestoreState` (21466) each perform an RTTI walk (`TryGetRttiClassName` + `strstr`) per call, the latter every frame when the feature is enabled.
- `UnitVoQueueIntercept` (18497): builds a `std::string` per call and one per queued item in `InspectUnitVoQueueLocked` (18424-18426) under a `std::mutex`; per-VO-event rather than per-frame, so acceptable, but `IsLikelyUnitVoFilename` could run on a stack buffer.
- `HandleUnitTurboBoundary` (18842): when an override differs from the global state it rewrites the two patch sites (`VirtualProtect` x2 + `FlushInstructionCache` x2) at the begin *and* end of every overridden unit's simulate, i.e. eight page-protection transitions per overridden unit per tick. A per-unit override that is applied by swapping bytes on the shared site is inherently costly; if per-unit turbo stays, a cheaper design is a per-unit flag checked by a small replacement of the comparison rather than re-patching.
- `MaybeLogSatelliteVisibilitySample` (12674) is well budgeted (interval + budget) and its 16 KB static array avoids stack pressure; keep this pattern.
- `InstallRadarLayoutHookIfPossible` is polled every sim tick from `ChunkEffectSimulateHook` (40429) without the throttle its neighbours have; the memcmp is 6 bytes so this is negligible, but once it has failed it will never succeed on the same image and could latch.

## Positive notes (things done well that later work should keep doing)

- GameObject identity by exact vtable-slot compare against `GameObject::GetTeam`, never by calling through the vtable (12047-12116), with the `_purecall`/`__fastfail` rationale written down; `TryGetWalkerGameObjectPosition` re-validates inside the guard and checks the target slot is executable image code before calling (14580-14620).
- Every byte patch in the range is guarded on the exact expected bytes for *both* directions (apply and revert), refuses to touch a site someone else changed, and rolls back partial multi-site writes (`EnsureSmartReticleRangeRedirect` 15128-15197, `SetScrapPilotHudPlateHookActive` 15676-15741, `ReconcileGlobalTurboPatchState` 18744-18790).
- SEH is kept in POD-only leaves with the C2712 reason stated (12814, 18828, 20599), and the FAST_FAIL-bypasses-SEH caveat is acknowledged where it matters (14520-14533).
- Multiplayer gating is uniform (`IsSinglePlayerSession`/`ReadLocalPlayerNetIdValue() == 0`) and each SinglePlayer-tier feature has a `Refresh...State` reconciler plus a `Revert...ToBaseline` for mission end.
- `InstallCareerStatsMpHookIfPossible` (16930-16936) shows the right identity discipline: prologue plus a body byte string containing a known global's address. The ordnance thunks (18058-18073) document the XMM/x87 argument explicitly. `GetHeadlightOgreApi` (19181) resolves once and audits every unresolved name, with the 43%-CPU regression that motivated it recorded.
- Feature blocks carry the reverse-engineering evidence inline (addresses, xrefs, capture timestamps, dump names), e.g. pilot team restore 21251-21341 and BZRNet globals 21694-21745, which is exactly what makes a later patches.json migration possible.

## SECTION MAP (lines 11000-22000)

| Start | End | Feature / hook group | ~lines | openshim.ini keys / env / patch names | Status |
|---|---|---|---|---|---|
| 10914 | 11204 | Lobby flag catalogue: engine `SetMyFlag` upload path, cached legacy payload apply, `SelectFlagEntryByIndex` (tail of the flag block that starts before 11000) | 290 | flag selection config (`SaveSelectedFlagConfig`), `g_BzrFn_SetMyFlag`/`NetPlayerSetFlagBuffer` resolves | active |
| 11205 | 11398 | Ban list persistence (`bans.cfg`, legacy `banlist`) used by `/ban` and lobby ban button | 195 | none (file format), `[BAN]` log tag | active |
| 11399 | 11621 | Persistent per-player mute list (`mutes.cfg`) | 225 | `[Network] PersistentPlayerMute`, `OPENSHIM_DISABLE_PERSISTENT_PLAYER_MUTE` | active |
| 11623 | 11852 | Under-attack alert mode (config parse, env, baseline, bridge setter) | 230 | `[Display] UnderAttackAlert`, legacy per-mod cfg `UnderAttackAlertMode`, `OPENSHIM_UNDER_ATTACK_ALERT_MODE/COOLDOWN`; feeds `HandleUnderAttackAlert` | active |
| 11854 | 12033 | Target reticle popup mode (config parse, baseline, bridge setter) | 180 | `[Display] TargetPolicy`/`TargetReticle`, `OPENSHIM_TARGET_RETICLE_POPUP_MODE`; feeds `TargetReticlePopupRecentHitGetterHook` | active |
| 12035 | 12198 | Shared GameObject identity helpers (`TryGetGameObjectFieldBase`, `GetGameObjectActualTeam`, `IsNeutralTeamObject`, forward decls for arena enumeration) | 165 | none; hardcoded `kGogGameObjectGetTeamAddr` | active (infra) |
| 12200 | 12238 | View-id / satellite-overview predicate; damage-reveal and player-kill trace budgets | 40 | `OPENSHIM_TRACE_PLAYER_KILLS`, `[Diagnostics]` damage-reveal trace | active / diagnostic |
| 12240 | 12368 | Satellite visibility fix state + config; hop-out alert config | 130 | `[SinglePlayer] SatelliteVisibilityFix`, `[General] SuppressHopOutAttackAlert`, `OPENSHIM_DISABLE_SATELLITE_VISIBILITY_FIX`, `OPENSHIM_SATVIS_TEST_PREHIDE_TEAM`, `OPENSHIM_SATVIS_VALIDATE` | active (+ test fixtures) |
| 12370 | 12617 | SATVIS diagnostic capture: RTTI class name, Ogre `getVisible` by offset, per-object capture/log | 250 | `OPENSHIM_TRACE_SATELLITE_VISIBILITY` | diagnostic |
| 12619 | 12672 | Hop-out stale attack-alert suppression (`MaybeSuppressStaleHopOutAttackAlert`) | 55 | `[General] SuppressHopOutAttackAlert`; RVA `kRadarAttackAlertNextBeepRva` | active |
| 12674 | 12812 | `MaybeLogSatelliteVisibilitySample` sampler | 140 | `OPENSHIM_TRACE_SATELLITE_VISIBILITY` | diagnostic |
| 12814 | 12902 | SEH leaves for satellite fix (`TryReadObjectIlluminationAndEntity`, `TryCallEntitySetVisible`, `SatelliteWorldIsLive`) | 90 | none | active (infra) |
| 12904 | 13324 | Career statistics on the native event layer: rationale, pending-victim table, damage publish from `DamageRevealProbeHook`, drain, kill derivation | 420 | `[Career] StatsTracking`, `OPENSHIM_DISABLE_CAREER_STATS`; rides "Damage Reveal Probe 1..4/4" patches | active |
| 13326 | 13610 | Player-kill research trace (PKTRACE): `DistributedTraceInfo`, `DistributedRecordDeathIntHook` inline detour at 0x006796D0, `TraceNetPlayerRecordDeath` | 285 | `OPENSHIM_TRACE_PLAYER_KILLS` (+ budget); `tests/player_kill_trace_tests.cpp` covers the pure logic | experimental / research |
| 13612 | 13901 | Career stats sinks, subscription, session state, reset (`ResetCareerStatsData`), `TickOpenShimEventLayer` | 290 | `[Career] StatsTracking`; `career_stats.cfg` | active |
| 13903 | 14301 | Satellite visibility fix: test pre-hide, `SyncSatelliteVisibility` (enter/exit transitions, mark-and-sweep), `LogSatelliteVisibilityValidationSample` | 400 | as 12240 block; `OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX` | active (+ validation) |
| 14303 | 14413 | Engine flame runtime target resolution (`EngineFlame::AddFlame`, `GetTeamNum`, `EngineFlame::ResolveTexture` resolves), manager observation | 110 | `resolves` in patches.json; `[Display]` jet flame keys elsewhere | active |
| 14415 | 14439 | `WritePointerValue` (vtable slot writer) | 25 | none | active (infra) |
| 14441 | 15106 | Weapon convergence + player reticle convergence: Walker post-pass, range providers, three vtable dispatchers, `RefreshShotConvergencePatchState` | 665 | `[SinglePlayer] WeaponConvergence`, `PlayerReticleConvergence`/`SmartReticleConvergence`; `tests/weapon_convergence_tests.cpp`; hardcoded vtable slots 0x0088A4FC/0x00889418 | active; two dead log helpers |
| 15108 | 15286 | Smart reticle range redirect (five-site operand rewrite to a shim cell) | 180 | `[SinglePlayer] SmartReticleRange`/`ReticleRange`; EXU `SetReticleRange` bridge | active |
| 15288 | 15914 | Scrap/pilot HUD legacy layout: baseline capture, UI-scale inversion, command-menu anchor, plate draw hooks (`ScrapPanelSubmitHook`/`PilotPanelSubmitHook` call-site patches), text colour/alignment patches, `RefreshScrapPilotHudLayout` | 625 | `[Display] ScrapPilotHud`; bridge `Set/GetScrapPilotHudTopLeftsFromBridge` | active |
| 15916 | 16114 | Radar layout hook (inline detour at 0x00492EC0) + `RadarSizeScale` | 200 | `[Display] RadarSizeScale`; bridge `SetRadarSizeScaleFromBridge` | active |
| 16116 | 16250 | Satellite view limits (max zoom `.rdata` write, pan speed) | 135 | `[SinglePlayer] SatelliteZoomOut`, `SatellitePanSpeed` | active |
| 16252 | 16368 | Small reconcilers: turret aim pitch, AI weapon mask artillery/minelayer, ODF tuning, bomber AI range, attack reveal, `[Fixes]` MP gates | 115 | `[SinglePlayer] TurretAimPitch`, `AiWeaponMask*`, `AiOdfGameplayTuning`, `BomberAiRange`; `[Fixes]` keys | active |
| 16370 | 16620 | `InitializeGlobalImprovementConfig` (reads ~20 keys, runs every reconciler) | 250 | `[Display] ScrapPilotHud/RadarSizeScale`, `[SinglePlayer] WeaponConvergence/PlayerReticleConvergence/SmartReticleRange/SmartScavengerPathing/JumpSnipeCrouch/OrdnanceVelocityInheritance/SatelliteZoomOut/SatellitePanSpeed/TurretAimPitch(+Multiplier)/AiWeaponMask*/BomberAiRange/AiOdfGameplayTuning`, `[Gameplay] AllowNeutralAttackOrders`, `[Diagnostics] AipResolveTrace`, `[Fixes] AiMultiProducerMakers` | active |
| 16622 | 16674 | `VtableTypeNameMatches`, `ReadValueAtOffset`, `ShouldEnableJumpSnipingProbe` | 55 | `OPENSHIM_TRACE_JUMP_SNIPING` | infra / research |
| 16676 | 16899 | Jump-snipe probe snapshot/log; `RecordDeathHook` (NetPlayer::RecordDeath detour target); `PersonSimulateJumpSnipeProbeHook` | 225 | `OPENSHIM_TRACE_JUMP_SNIPING`; career MP path | `RecordDeathHook` active, probe experimental |
| 16900 | 16994 | `InstallCareerStatsMpHookIfPossible` (inline detour 0x00577290 with body check) | 95 | `[Career] StatsTracking` | active |
| 16996 | 17147 | Ogre `ParticleSystemManager::createTemplate` dedupe detour (crash fix) | 150 | none (export-resolved) | active |
| 17149 | 17308 | UI "Top Screen" ManualObject orphan dedupe detour at 0x007D2B70 (crash fix) | 160 | `OPENSHIM_DISABLE_UI_MANUAL_OBJECT_DEDUPE`, `OPENSHIM_TEST_UI_MANUAL_OBJECT_ORPHAN` | active |
| 17310 | 17433 | Ogre `clearScene`/`destroyAllMovableObjects` forget hooks | 125 | none | installed but documented never to fire (dead in practice) |
| 17435 | 17674 | Mission transition seam: `SetRunning` detour at 0x00434170, run-state name table, EXU lifecycle notify | 240 | none; drives headlight/pilot-light/fog-wake/terrain generation bumps | active (GOG-only, base-pinned) |
| 17676 | 17708 | D3D11/dxgi/RenderSystem module pin for shutdown ordering | 35 | none | active |
| 17710 | 17761 | `InstallJumpSnipingProbeIfRequested` (Person::Simulate detour 0x0059D340) | 50 | `OPENSHIM_TRACE_JUMP_SNIPING` | research |
| 17763 | 17845 | Jump-snipe crouch-on-landing fix (11-byte branch rewrite at 0x0059DEA5) | 85 | `[SinglePlayer] JumpSnipeCrouch`; bridge `SetJumpSnipeCrouchEnabledFromBridge` | active |
| 17847 | 18212 | Ordnance velocity inheritance: cannon-lead tolerance NOP, owner-chain validation, two naked thunks (0x004803D4, 0x0048F658), installer/reconciler | 365 | `[SinglePlayer] OrdnanceVelocityInheritance`/`OrdnanceVelocInheritance`, `OPENSHIM_DISABLE_ORDNANCE_VELOCITY_INHERITANCE` | active (default off) |
| 18214 | 18246 | Revert-to-baseline helpers (convergence, reticle range, scrap/pilot HUD, turret pitch) | 35 | as above | active |
| 18248 | 18312 | Global turbo constants, `IsExuModuleLoaded`, `WritePatchBytes` | 65 | `[SinglePlayer] Turbo` | active (infra) |
| 18314 | 18719 | Unit VO queue policy: filename classifier, queue inspection, `UnitVoQueueIntercept` call-site rewrite, `KillQueue` discovery, config | 405 | `[Display] UnitVoFeedback`; resolves `UnitVo::SayQueueCallSite`/`RecycleQueueCallSite`; `OPENSHIM_TRACE_UNIT_VO`; bridge `Set/GetUnitVo*FromBridge` | active |
| 18721 | 19017 | Global + per-unit turbo: comiss operand / gate patches (0x00601CA3/0x00601CB5), naked begin/end hooks (0x00601C92/0x00601CCD), EXU culling callback | 300 | `[SinglePlayer] Turbo`, `OPENSHIM_GLOBAL_TURBO(_TOLERANCE)`; bridge `Set/GetGlobalTurbo`, `Set/GetUnitTurbo` | active (default off) |
| 19019 | 19148 | Headlight enums, Ogre API struct, original-state record, constants, world-generation globals | 130 | `[SinglePlayer] Headlights*` | active (infra) |
| 19150 | 19362 | Headlight Ogre API resolution (once, audited), `VerifyExpectedOgreExportsIfPossible` | 215 | none | active |
| 19363 | 19440 | `LogHeadlightLightParameters` probe | 80 | `[Diagnostics] HeadlightLightTrace`, `OPENSHIM_TRACE_HEADLIGHT_LIGHT` | diagnostic |
| 19442 | 19547 | Emission (running) light fix: `HandleEmissionLightState` + naked thunk at 0x0044CBD0 | 105 | `OPENSHIM_DISABLE_EMISSION_LIGHT_FIX` | active |
| 19549 | 20353 | Stock headlight policy: capture/restore/apply with falloff repair plan, colour/beam parsing, `RefreshHeadlightState` (200 ms arena walk), config, live re-apply | 805 | `[SinglePlayer] Headlights`, `OtherHeadlights`, `HeadlightColor`, `HeadlightBeam`, `HeadlightBrightness`, `HeadlightFalloffRepair`, `OPENSHIM_DISABLE_HEADLIGHT_FALLOFF_REPAIR`, `OPENSHIM_TRACE_HEADLIGHTS`; `tests/headlight_falloff_tests.cpp` | active |
| 20355 | 21247 | Pilot flashlight: Ogre API, bridge field reads, bone-suffix lookup, create/retire/forget, `RefreshPilotFlashlightState`, config parsing | 890 | `[SinglePlayer] PilotFlashlight`, `PilotFlashlightColor/Beam/Offset/Pitch/Bone`, `[Diagnostics] PilotFlashlightTrace`, `OPENSHIM_PILOT_FLASHLIGHT`, `OPENSHIM_TRACE_PILOT_FLASHLIGHT` | active (default off) |
| 21249 | 21692 | Pilot team restore on boarding: packed/live team sample, layout self-check, boarding watch, repair writes | 445 | `[SinglePlayer] PilotTeamRestore`, `OPENSHIM_PILOT_TEAM_RESTORE` | experimental (ships off) |
| 21694 | 22000+ | BZRNet route preference / UDP port / nickname: global byte guards, nickname read/write, lobby validation, authoritative nickname apply with optional websocket recycle, route-preference parsing (continues past 22000) | 310+ | `[Network] Nickname`, `ReauthOnNicknameChange`, route/port keys (parsed after 22000), `OPENSHIM_DISABLE_BZRNET_REAUTH`; bridge `SetBzrNetNicknameFromBridge` | active (reauth experimental) |

Calling-convention audit for hooks defined in the range: `DistributedRecordDeathIntHook` (13457, `__fastcall` for a `__thiscall(int)` target), the three `...UpdateWeaponAimWithConvergence` dispatchers (14931-14990, `__fastcall(this, edx, float)` in `__thiscall(float)` vtable slots), `ScrapPanelSubmitHook`/`PilotPanelSubmitHook` (15646/15655, `__cdecl` replacing a `__cdecl` call), `RadarRefreshLayoutHook` (15993, `__cdecl(int)`), `RecordDeathHook` (16852, `__cdecl(int,int)`), `PersonSimulateJumpSnipeProbeHook` (16875), `ParticleCreateTemplateDedupeHook` (17005), `UiEnsureManualObjectDedupeHook` (17160, `__fastcall` with an 8-byte by-value arg matching `ret 8`), the two `SceneManager*Hook`s (17310/17321), `BzrSetRunningHook` (17552, `__cdecl(int)`), `UnitVoQueueIntercept` (18497, `__cdecl`), and the naked thunks (18075, 18090, 18861, 18880, 19478) with their `__cdecl` helpers and matching `add esp` — all consistent with how they are installed. No wrong-convention annotations were found in this range.

Hooks that read engine memory without validating the resolved base: `IsTeamHumanByNetPlayer`/`GetNetPlayerIdForTeam` (13326-13343) and `TryGetGameObjectHandleValue` (13028) use absolute GOG addresses under SEH only; `TryGetReticleConvergenceRange` (14726) reads `kLocalUserObjectPtrAddr`/`kSmartReticle*Addr` absolutely; `ApplyWalkerConvergencePostPass` (14784) calls `kCarrierGetWeaponAddr`/`kRefreshWeaponTransformAddr` absolutely (reachable only after the vtable-slot guard succeeded, which is an implicit build check); `TryGetHeadlightPlayerObject` (19584) relies on SEH for a null `ResolveMainModulePtr` result. The range's better pattern (`TryReadCurrentViewId` 12200, `MaybeSuppressStaleHopOutAttackAlert` 12646) resolves via `ResolveMainModulePtr` and checks for null first.
