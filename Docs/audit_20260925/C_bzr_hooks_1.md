<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# bzr_hooks.cpp lines 1-11000

Scope: `/home/user/Battlezone98Redux_Shim/src/patches/bzr_hooks.cpp` lines 1-11000 (of 42,854), read end to end in ~400-line chunks, with `include/bzr_hooks.h` and `include/bzr_object_layout.h` for context. Helpers called from this range but defined later in the file were looked up (`ChunkRenderResolveHook` 38516, `ChunkEffectSimulateHook` ~40405, `EngineFlameSubmitHook` ~39371, `TryResolveChunkPayloadMeshResource` 28470, `InstallCareerStatsMpHookIfPossible` 16901, `ResolveBzrHooks` 34446+). Callers were verified with grep across `src/ include/ tests/`.

## Summary

This range is almost entirely *declarations and helpers*: the exported-global block, ~300 engine function-pointer typedefs/statics, ~1,150 lines of `constexpr` addresses/offsets (174 raw `0x00...` `uintptr_t` constants), feature state globals for ~40 unrelated features, and then the implementation of the chunk-proxy/generic-chunk-batch renderer, the HUD sprite rect table bridge, career stats persistence, and the lobby flag catalogue. Only one real hook entry point is defined here (`GameObjectHandleGetObjHardened`, `__cdecl`, correctly matched to the `__cdecl` stock `GameObjectHandle::GetObj` it replaces via a GOG-only registry entry). No calling-convention mismatches were found in-range.

Top 3 issues:
1. **Career stats MP worker ignores `[Career] StatsTracking=0`** (the shipped default): `StartCareerStatsMpSessionWorker` is started unconditionally and `PollMultiplayerCareerSession` never consults `g_CareerStatsEnabled`, so `career_stats.cfg` is still written at every multiplayer match start, from a background thread that also calls an engine function.
2. **SEH `__except(EXCEPTION_EXECUTE_HANDLER)` wrappers around Ogre C++ calls swallow C++ exceptions** (`createEntity`, `createBillboardSet`, `attachObject`, `setPosition`, ...). An `Ogre::Exception` is an SEH exception 0xE06D7363, so these handlers "catch" it without unwinding OgreMain frames (mutexes, partially constructed objects), unlike the thumbnail guard elsewhere in the file which correctly filters on that code.
3. **Per-tick chunk-proxy work is O(chunks x slots) with heap allocation per slot per tick**, driven twice per frame (sim hook + render hook); `std::unordered_set` is built per call in three transform-resolution helpers and the payload mesh is re-resolved for every live chunk every sim tick.

Overall the code is defensive (SEH around every engine read, log budgets everywhere, static_asserts pinning layout to `bzr_object_layout.h`), but the file has become a dumping ground: the same feature is spread across three or four non-adjacent regions (constants ~600-1700, state ~1860-3100, implementation 3200+), and dead constants/helpers accumulate because nothing removes them.

## Findings

### [High][High] MP career session worker runs and writes the stats file regardless of `[Career] StatsTracking` — src/patches/bzr_hooks.cpp:10096, :10159, :34952
```cpp
static void PollMultiplayerCareerSession()
{
    const ULONGLONG nowMs = GetTickCount64();
    const bool active = IsMultiplayerCareerSessionActive();
    ...
    LoadCareerStatsFile(data); ... SaveCareerStatsFile(data)
```
`StartCareerStatsMpSessionWorker()` is called unconditionally from `ResolveBzrHooks` (line 34952) and spawns `CareerStatsMpSessionThreadProc`, a never-exiting thread that polls every second. Neither `PollMultiplayerCareerSession` nor `RecordMultiplayerCareerStats` (10181) reads `g_CareerStatsEnabled` (declared much later, 12979); every other career path does (`CareerStatsEventSink` 13698, 13614, 13662). Grep confirms no reference to `g_CareerStatsEnabled` below line 12978. With `openshim.ini` shipping `StatsTracking = 0`, the worker still records `mpMatchesPlayed`/`mission.<key>.plays` into `career_stats.cfg` at every MP match start. Secondary problems in the same code: (a) `ResolveCareerStatsProfileKey` (9915) calls the engine function `g_BzrFn_GetLocalPlayerNetId()` from this worker thread, not the game thread; (b) synchronous `ReplaceFileW`/`CopyFileW` on a thread that is never joined, so it can be mid-write during process teardown; (c) `RecordMultiplayerCareerStats` (still reachable through the queue-full fallback at 16871) also writes without the gate.
Fix: hoist the `g_CareerStatsEnabled` declaration above this block; early-return in `PollMultiplayerCareerSession` and `RecordMultiplayerCareerStats` when it is false; only start the worker from `InitializeCareerStatsConfig` when enabled (and stop it / skip polling when disabled at runtime). Read the net id via `ReadLocalPlayerNetIdValue()` (a SEH-guarded global read, 9756) instead of calling the engine function off-thread. Verifiable on Windows only (behaviour), though the gate predicate could be unit-tested on Linux if extracted.

### [Medium][High] SEH handlers swallow Ogre C++ exceptions without unwinding — src/patches/bzr_hooks.cpp:6124, :5993, :6020, :6052, :6205, :6893 (pattern)
```cpp
__try
{
    outSceneNode = createChildSceneNode(rootNode, zeroPos, identity);
    if (outSceneNode)
    {
        outEntity = CreateChunkMeshProxyEntity(sceneManager, createEntity, meshName);
```
`TryCreateChunkMeshProxyObjects`, `TryCreateChunkProxyBillboardSet`, `TrySetupChunkProxyBillboardSet`, `TryUpdateChunkMeshProxyTransform`, `TryNotifyChunkProxyCameraSafe`, `TryUpdateChunkProxyRenderQueueSafe`, `TryAddChunkProxyRenderableSafe`, etc. all use `__except(EXCEPTION_EXECUTE_HANDLER)`. That handler also catches MSVC C++ exceptions (code 0xE06D7363) that Ogre throws routinely (`Ogre::ItemIdentityException` when a mesh/material is missing, `Ogre::InvalidParametersException` from `createEntity`, `Ogre::InternalErrorException` from the codec). Executing the SEH handler for a C++ throw skips every destructor between the throw and this frame — Ogre's `OGRE_LOCK_AUTO_MUTEX` guards in `ResourceGroupManager`/`SceneManager`, half-constructed `Entity` objects registered in the movable-object map — and leaks the exception object. The file already knows this distinction: the thumbnail BMP guard (constants at 843-870) explicitly filters on 0xE06D7363. The comment on `EnsureChunkMeshProxySlot` (6237) argues the mesh is pre-verified, but `createEntity` can still throw for a resource group that is not initialised, a corrupt `.mesh`, or a name collision.
Fix: in each wrapper use `__except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)` and wrap the actual Ogre call in a separate `noexcept`-free function with `try { ... } catch (...) { return false; }` (the generic batch code at 8329-8520 already does this correctly with `try/catch`). Windows-only.

### [Medium][High] Chunk proxy tick allocates and rescans per slot, twice per frame — src/patches/bzr_hooks.cpp:5553, :5590, :5640, :7596, :8895, :9252
```cpp
std::unordered_set<uintptr_t> seen;
seen.reserve(std::size(candidates));
for (const void* candidate : candidates)
```
`TryResolveChunkProxyPositionFromCandidates` (5553), `TryResolveChunkProxyTransformForSlot` (5590) and `TryBuildChunkProxyAnchoredEntryTransform` (5640) each heap-allocate an `unordered_set` to dedupe 6-9 pointers. `UpdateChunkProxySlotPosition` calls two of them per active slot, and `TickChunkProxyDebug` is driven both from `ChunkEffectSimulateHook` (40448) and from `EngineFlameSubmitHook` (39371), i.e. twice per frame across up to `g_ChunkProxyCapacity` = 256 slots. In addition `TrackChunkEffectActiveEntries` (9252, per sim tick) runs, for every live chunk: `CaptureChunkBridgeSnapshot` (three SEH regions + string probes), `TryResolveChunkProxyPositionFromCandidates` (alloc), then `TrackChunkProxyDebugEntry` (8895) which linearly scans all 256 slots, captures the bridge snapshot *again*, and calls `TryResolveChunkPayloadMeshResource` (28470; walks `g_ChunkPayloadResourceDirectories`, cached only per name) on every tick even though the slot already has `proofMeshName`. All of this is gated on `g_EnableChunkMeshProxy` (default off; on when DestructionChunks assets are present), so stock users are unaffected, but with the asset pack a 40-craft battle (~400 chunks) makes this the dominant sim-tick cost.
Fix: dedupe with a fixed `uintptr_t[9]` and a linear compare (no allocation); keep a small `unordered_map<objectBytes, slotIndex>` alongside `g_ChunkProxySlots` so the per-chunk update is O(1); in `TrackChunkProxyDebugEntry`'s "already tracked" branch skip `CaptureChunkBridgeSnapshot`/`TryResolveChunkPayloadMeshResource` unless `geomName` or the binding's `bindTick` changed. The dedupe helper is Linux-testable if extracted; the rest is Windows-only.

### [Medium][High] Function pointers and pool addresses hard-wired in feature code instead of `scripts/patches.json` resolves — src/patches/bzr_hooks.cpp:363-380, :488-492, :2760-2761, :34761
```cpp
static FnResolveObj76GameObject g_BzrFn_ResolveObj76GameObject =
    reinterpret_cast<FnResolveObj76GameObject>(0x00479F30);
...
static FnPlayGlobalSound g_BzrFn_PlayGlobalSound =
    reinterpret_cast<FnPlayGlobalSound>(0x0043AA30);
```
and `GameObjectFromHandleGog` (363) reads the object pool at literal `0x0260DB20` and calls `GetHandle` at literal `0x00462380`. These are *called* addresses that never pass through `HookEngine::ResolveNamedAddress` and have no byte/identity check, in a file that elsewhere guards every detour with `ExpectedBytesMatchAt`. Counting only this range, 174 `constexpr uintptr_t k* = 0x00...` constants live at 557-1700, and the same value sometimes exists twice (`kGogResolveObj76GameObjectAddr` at 792 is declared but the pointer above uses the literal; `kGogGameObjectGetObjByHandleAddr` at 1095 is the address the comment at 358 says was wrong, still compiled in). `GameObjectFromHandleGog` is also reached from the player-kill trace (13229, 13264, 13350) with no `g_IsSteamExe`/platform gate, although its only registry-driven user (`GameObject Handle Stale Slot Guard`) is `"platforms": ["gog"]`. The project rule ("put build-specific sites and addresses in `scripts/patches.json`; native hooks must fail closed") is not met for these.
Fix (incremental, no address changes): add `resolves` entries for the four *called* targets (`GameObject::GetHandle`, obj76->GameObject accessor, `PlayGlobalSound`, `GetLocalPlayerNetId`) with the existing values as `fallback` and an `identity` note, resolve them in `ResolveBzrHooks`, and null them (fail closed) when the resolve disagrees; delete the two dead duplicates. Windows-only to verify at runtime; `tests/patch_registration_tests.cpp` covers the json/`patches.h` pairing on Linux.

### [Medium][Med] `LookupHudSpriteId` caches hits only; every miss rescans the table and logs — src/patches/bzr_hooks.cpp:4030-4130
```cpp
// memoize successful hits so steady-state refreshes neither rescan ...
static std::unordered_map<std::string, int> s_HudSpriteIdCache;
```
A name that is not in the table (typo from a mod's Lua, or a sprite that only exists in some HUD variants) goes through `TryReadHudSpriteNameCount` + `SehScanHudSpriteTable` (900+ `memcpy`+`_stricmp`) + `SehCallHudSpriteLookupFn` and emits three `LogShimA` lines on **every** call. The bridge entry points `GetHudSpriteRectFromBridge`/`SetHudSpriteRectFromBridge`/`SetHudSpriteVisibleFromBridge` (36629, 36857, 36913) call it directly and are exposed to mission Lua, which can call them per frame.
Fix: memoize `0` too, keyed with the table count so a later registration invalidates it; log the miss once per name. Windows-only.

### [Low][High] `ReadInlineAsciiBufferRaw` writes one past `capacity` — src/patches/bzr_hooks.cpp:9787-9812
```cpp
for (size_t i = 0; i < capacity; ++i) { ... outBuffer[length++] = ch; }
...
outBuffer[length] = '\0';
```
If the engine buffer has no NUL within `capacity` bytes, `length == capacity` and the terminator lands at `outBuffer[capacity]`. The only caller (`ReadInlineAsciiBuffer`, 9814) passes `std::string(capacity, '\0').data()`, whose `[capacity]` slot is the string's own terminator, so writing `'\0'` there is benign today; any future raw-array caller (the file has many `char name[16]` buffers) overflows by one.
Fix: loop `i + 1 < capacity`, or reserve `capacity + 1` in the caller. Pure function — Linux-testable if lifted into a header.

### [Low][High] `written += _snprintf_s(..., _TRUNCATE, ...)` goes backwards on truncation — src/patches/bzr_hooks.cpp:4515-4560
`_snprintf_s` returns -1 when it truncates; `written` then decreases and the next piece is written over the tail of the previous one. The size argument shrinks in step so there is no overflow, only a garbled diagnostic line (budgeted to 6). Fix: `if (n < 0) break;`. Linux-testable if lifted.

### [Low][Med] `TryGetOgreModuleRange` latches failure if called before OgreMain is mapped — src/patches/bzr_hooks.cpp:3282-3316
`s_attempted = true` is set before `GetModuleHandleA("OgreMain.dll")` is checked, so a single early call permanently makes `LooksLikeOgreObject` return false, silently dropping `ownerOgreEntity` for every chunk (and the bone-collapse path at 12461+). OgreMain is a static import of the exe today, so the window is theoretical, but the same file treats `ResolveOgreProcRaw` misses before module load as "timing, not an answer" (3222 comment) — this helper should follow that rule. Fix: set `s_attempted` only after a non-null module handle. Windows-only.

### [Low][Med] `ResolveOgreProcByOffset` calls raw OgreMain image offsets with no validation — src/patches/bzr_hooks.cpp:3353-3365, :6895-6903, :8727-8729, :12405
Offsets `0x00026850`, `0x0002CCCD`, `0x0001584D`, `0x00005E70` into `OgreMain.dll` are cast to `__thiscall` procs and called on the render path. Nothing checks the DLL's version, size, or prologue bytes, unlike every exe-side detour in the file. A different OgreMain build (a future Redux patch, or a modded DLL) turns these into mid-instruction calls. Fix: pair each offset with an expected prologue and `ExpectedBytesMatchAt` (or the module's `SizeOfImage`/checksum) at first resolve, returning null on mismatch so the callers' existing null checks stand the feature down. Windows-only.

### [Low][High] Full-process memory scan with one SEH frame per 4-byte candidate — src/patches/bzr_hooks.cpp:4276-4360
`DiscoverStockScrapPilotPanelRecordAddresses` walks every `MEM_PRIVATE` region up to 128 MB at 4-byte stride and calls `TryReadHudSpriteRectRecord` (its own `__try`) for each offset. SEH frame setup on x86 is cheap but not free at ~30M iterations; the comment records multi-second freezes. It is only the fallback (`SetStockScrapPilotPanelsVisibleByUv`) behind the now-static table at `kHudSpriteRectTableAddr`, and is throttled by exponential backoff. Fix: one `__try` per region (read the region into a local span first) or delete the fallback now that the static table is proven. Windows-only.

## Section map (lines 1-11000)

| Start | End | Feature / hook group | ~lines | openshim.ini keys / patch names / env | Status |
|---|---|---|---|---|---|
| 1 | 60 | Includes (note `native_ui_validation.h` included twice, lines 21 and 37) | 60 | — | active |
| 62 | 129 | Exported globals: lobby ban/flag/nickname/net-route widgets, autosave-load button, map-filter flags, vehicle-fix targets, BZRNET labels | 68 | patches "Ban Button Hook 1/2, 2/2", "Lobby BZRNET Integration HOST/CLIENT", "Map Filters 1-8", "Vehicle List Mod Fix 1/4, 4/4", "AutoSave Load Button Hook" | active |
| 131 | 315 | Engine function-pointer typedefs (`Fn*`) for every feature in the file | 185 | — | active (several typedefs unused in-range, see dead list) |
| 316 | 345 | `g_BzrPtr_*` / UI ctor & setter pointer statics (GOG addresses in trailing comments) | 30 | resolved in `ResolveBzrHooks` (34446+) by literal | active |
| 347 | 440 | `GameObjectFromHandleGog` + `GameObjectHandleGetObjHardened` (stale handle guard) | 94 | patch "GameObject Handle Stale Slot Guard" (`platforms: ["gog"]`, fallback 0x00462630) | active; the only hook entry point in range |
| 441 | 527 | Static fn pointers: person/carrier guards, PREREQ probe, AI multi-producer makers, shield tower / mines / spray building / tug / rig, friend/enemy, matrix, range search, key config, recycle/scrap, AI unit remove, chunk effect | 87 | `[Fixes]` AiMultiProducerMakers, `[Diagnostics]` AipResolveTrace | active |
| 529 | 556 | Forward decls: `ChunkEffect*Hook` (`__fastcall`, this+edx idiom, correct for `__thiscall` targets), `InstallArtilleryDoAttackHookIfPossible`, nickname helpers | 28 | — | active |
| 557 | 660 | Anonymous-namespace constants: shell/load states, queued-load buffers, bans/flags file names, flag preview + nickname panel geometry, producer build-menu INI, producer vtables, engine flame layout | 104 | `openshim_producer_build_menus.ini`, `bans.cfg`, `flags.cfg` | active |
| 661 | 710 | HUD sprite name/rect table addresses and record layout | 50 | (bridge) `Get/SetHudSpriteRectFromBridge` | active |
| 711 | 800 | GameObject/obj76/ordnance/shield-tower/mine offsets, GOG simulate addresses, Friend/EnemyP, SetDamageFlags, vtable slots | 90 | `[Fixes]` shield/mine team filters (implemented later) | active |
| 801 | 1000 | Constants for: ScriptUtils CanBuild/IsBusy, briefing scroll, MultiRender count clamp (#65), thumbnail BMP guard, splinter undead (#46), MPAUTH probes, Tug PostLoad, constructor recycle stale target, quake replay fade (#57), target-cam satellite (#56/#78), cinematic satellite zoom (#58), APC allied target, Building state flags | 200 | `[Fixes]` ProducerScriptPredicates, BriefingScroll, MultiRenderCountClamp, ThumbnailBmpGuard, SplinterUndead, TugCargoPostLoad, ConstructorRecycleStaleTarget, QuakeReplayFade, TargetCamSatellite, CinematicSatelliteZoom, ApcAlliedTargetDeploy; env `OPENSHIM_TRACE_MPAUTH_*` | active; MPAUTH block (873-905) is diagnostic-only/experimental |
| 1001 | 1140 | Flag display / net player / flag object constants, Person::Simulate & GetPlayerHandle & RecordDeath addresses, Steam64/net-id/UI-wrapper globals, artillery DoAttack, career-stats timing, jump-snipe Person offsets and crouch byte patch | 140 | `[SinglePlayer]` JumpSnipeCrouch, `[Career]` StatsTracking, `[Display]` MultiplayerFlags | active; `kGogGameObjectGetObjByHandleAddr` (1095) and `kGogDistributedRecordDeathIntAddr` "advisory" (1106) are stale |
| 1141 | 1300 | Ordnance velocity inheritance: three patch sites, expected bytes, frame offsets, runtime verdict states | 160 | `[SinglePlayer]` OrdnanceVelocityInheritance | active (default off) |
| 1301 | 1400 | Scrap retarget/pathing constants, weapon convergence vtable slots, smart reticle range redirect sites | 100 | `[SinglePlayer]` WeaponConvergence, PlayerReticleConvergence, SmartReticleRange; ODF `scrapPathingAI` etc. | active |
| 1401 | 1660 | Scrap/pilot HUD legacy layout: engine layout points, BZ1.5 plate run tables, text colour/align sites, submit call sites | 260 | `[Display]` ScrapPilotHud (Stock/Legacy) | active |
| 1661 | 1700 | AttackTask/DoSubTask vtables, GetGameTime, chunk effect create/fragment addresses, world render origin, AI unit remove/build helpers, key config, AI team table | 40 | `[Fixes]` ConstructorRemoteBuild; chunk hooks | active |
| 1701 | 1860 | State structs (retarget, scrap, jump snipe, constructor cleanup) and forward decls of chunk/HUD helpers | 160 | — | active |
| 1861 | 1975 | Feature state globals: jump snipe, ordnance velocity, convergence, smart reticle, scrap/pilot HUD, HUD sprite discovery | 115 | as above | active |
| 1976 | 2130 | Structs: ban/flag records, producer build-menu config, `AiTuningConfig`/cache, unit tuning override, kite state, team filter, shield tower runtime | 155 | ODF `engageRangeAI`, `weaponRangeMinAI`, `retargetPeriodAI`, `affectAllies/Enemies` | active |
| 2131 | 2330 | Ban/flag/GDI+ globals, vehicle-asset exception cache, geo lookup structs, chunk bridge snapshot, LegacyMat3/Ogre PODs, `#include chunk_proxy_generic_meshes.inl`, `ogre_entity_frustum_cull.inl`, `ChunkProxySlot` | 200 | — | active |
| 2331 | 2470 | Chunk proxy / satellite visibility trace globals, VDF caches, vehicle skinning trace | 140 | env `OPENSHIM_CHUNK_*`, `[Diagnostics]` TraceSatelliteVisibility, TraceVehicleSkinning | active; `g_TraceSatelliteVisibility` defaults on per comment |
| 2471 | 2660 | Detour records + installed/enabled flags for ~30 hooks; `[Fixes]` Enabled vs Active (MP gate) flags; MPAUTH state | 190 | `[Fixes]` many; MP gate | active |
| 2661 | 2770 | Engine flame variant buffers (10 x 0x1250 B statics), JetFlames, under-attack alert, chunk effect offsets, View_Record RVA, chunk proxy tuning | 110 | `[Display]` JetFlames, UnderAttackAlert | active |
| 2771 | 2900 | Feature defaults/enabled/active flags: bomber AI range, howitzer volley, owned-object reveal, weapon mask (artillery/minelayer), ODF AI tuning, turret pitch, attack reveal, hop-out alert | 130 | `[SinglePlayer]` BomberAiRange, HowitzerVolley, AiWeaponMask*, AiOdfGameplayTuning, AttackRevealPerceivedTeam, TurretAimPitch | active |
| 2901 | 3060 | GameObject visibility/team/target/owner offsets with static_asserts against `bzr_object_layout.h`; chunk proxy runtime globals; generic chunk batch state + telemetry | 160 | env `OPENSHIM_FORCE_GENERIC_CHUNK_BATCH_FAILURE` etc. (test seams) | active; two globals are explicitly TEST/DIAGNOSTIC seams |
| 3061 | 3215 | Ogre function typedefs, MP flag render set struct/globals | 155 | — | active |
| 3216 | 3365 | `ResolveOgreProcRaw` (cached, negative-cached), `TryGetOgreModuleRange`, `LooksLikeOgreObject`, `ResolveOgreProcByOffset` | 150 | — | active |
| 3366 | 3400 | `ShouldEnableMultiplayerFlagUi` | 35 | `[Display]` MultiplayerFlags; env `OPENSHIM_DISABLE_MP_FLAG*` | active |
| 3401 | 3520 | Env parsers, clamps, `LogChunkDiagnostic` (8 KB stack, double sink), `GetMainModuleBase`/`ResolveMainModulePtr` | 120 | — | active |
| 3521 | 3970 | ASCII probe helpers for geo names / obj ids / owner entity names | 450 | — | active (chunk proxy only) |
| 3971 | 4770 | HUD sprite rect table: lookup, sample validation, memory-scan fallback, hide/restore, discovery with backoff, entry read/write | 800 | `[Display]` ScrapPilotHud; bridge `HudSprite*FromBridge` | active; scan fallback (4276) is legacy |
| 4771 | 5130 | Chunk identity/binding caches, link-probe capture, source-tree probe | 360 | — | active (chunk proxy) |
| 5131 | 5330 | `LogChunkCreateLifecycle` and classification helpers | 200 | env `OPENSHIM_TRACE_CHUNK_RENDER` | diagnostic |
| 5331 | 5900 | Geo lookup search, legacy-matrix -> quaternion, transform/position candidate resolution, local->anchored promotion | 570 | — | active (chunk proxy) |
| 5901 | 6650 | Ogre scene manager access, billboard/mesh entity creation, resource-location registration, slot release/forget | 750 | DestructionChunks asset pack | active |
| 6651 | 7590 | "Safe" SEH wrappers around Ogre calls, manual render-queue submission, geom bounds, sim->render space conversion, canonical payload hash, `UpdateChunkProxySlotPosition` | 940 | env `OPENSHIM_DISABLE_CHUNK_MANUAL_SUBMIT` | active |
| 7591 | 7860 | `TickChunkProxyDebug`, generic chunk batch geometry append, rehydrate-to-entities, QPC cost | 270 | — | active |
| 7861 | 8130 | Ogre material scheme reader; DX11 enhanced lighting diagnostic (`MaybeLogDx11EnhancedLightingState`) | 270 | `[Diagnostics]` TraceDX11EnhancedLighting; env `OPENSHIM_TRACE_DX11_ENHANCED_LIGHTING` | diagnostic (off by default) |
| 8131 | 8670 | Generic chunk batch telemetry, hide, deactivate-on-transition, `RebuildAndSubmitGenericChunkBatch` (state-version reuse) | 540 | — | active |
| 8671 | 8880 | `SubmitChunkProxiesToRenderQueue` (called from `LegacyWorldUpdateRenderQueueHook`) | 210 | — | active |
| 8881 | 9110 | Suppressed chunk pieces table, `TrackChunkProxyDebugEntry`, `TrackCreateChunkTargetForProxy` (no callers), `TrackChunkProxyDebugObject` (empty stub) | 230 | — | partly dead |
| 9111 | 9390 | Chunk effect entry reader, `LogChunkEffectRuntimeSample`, `TrackChunkEffectActiveEntries` (per sim tick), `CaptureChunkBridgeSnapshot` | 280 | env `OPENSHIM_TRACE_CHUNK_EFFECT` | active |
| 9391 | 9575 | Chunk class probes / transition log, `LogChunkResolveSnapshot` (used by `ChunkRenderResolveHook`, 38516) | 185 | patch "Chunk Render Resolve" (via `ChunkRenderResolveHook`) | diagnostic |
| 9576 | 9700 | Misc clamps, module dir, workshop content root discovery, `TrimAsciiInPlace`, user-config section names | 125 | — | active (shared helpers) |
| 9701 | 9830 | Ban id normalisation, `BzrString` conversion, SEH readers for Steam64 / local net id (`IsSinglePlayerSession`) / UI wrapper, inline ASCII buffer readers | 130 | MP gate for every `[SinglePlayer]` feature | active, load-bearing |
| 9831 | 10230 | Career stats: paths, key sanitising, mission/profile key, load/save (atomic replace), MP session worker thread, `RecordMultiplayerCareerStats` | 400 | `[Career]` StatsTracking (NOT honoured here, see finding 1) | active |
| 10231 | 11000+ | Lobby flags: config/dir paths, catalogue scan, GDI+ conversion to 1-bit 64x32 payload, BMP/BIN writers, `MarkFlagDisplayDirty` (writes 0x009B60CC+0x2C), flag config save/load, engine flag path apply (continues past 11000) | 770 | `[Display]` MultiplayerFlags, `flags.cfg` | active (feature default off) |

Reads/writes of fixed engine VAs in this range that rely only on SEH (no build-identity check of their own): `kHudSpriteNameCountAddr` 0x00920F00 (3960), `kOgreSceneManagerStructureAddr` 0x00920EA0 (5851), `kGogWorldRenderOriginAddr` 0x025F8E4C (7258), `kSteam64GlobalAddr` 0x0260B1D0 (9735), `kLocalPlayerNetIdAddr` 0x009180D4 (9756), `kUiWrapperActiveAddr` 0x00918324 (9776), `kQueuedLoadNameBufferAddr`/`kQueuedLoadPathBufferAddr` (9870/9893), and the **write** to `kFlagDisplayAddr` 0x009B60CC (10704). The HUD rect table (0x025F8F40) is the one that validates its base against known UV samples before use (4600-4640) — that pattern is the one to copy.

## Dead or unused code (list with evidence)

Verified with `grep -rnw` across `src/ include/ tests/` (count = definition only unless noted):
- `TrackCreateChunkTargetForProxy` (9042-9108): defined, zero callers.
- `TrackChunkProxyDebugObject` (9111-9121): body is four `(void)` casts; called at 38567 and 38648 — a stub that does nothing.
- `TryGetChunkProxyNumAttachedObjectsSafe` (6690), `TryGetChunkProxyAttachedObjectSafe` (6705), `TryProcessQueuedUpdatesSafe` (6622): no callers.
- `HudSpriteUvBlockMatches` (4237): no callers (superseded by `HudSpriteRecordMatches`).
- `kGogGameObjectGetObjByHandleAddr` (1095): only other mention is the comment at 358 explaining it was the wrong address.
- `kGogResolveObj76GameObjectAddr` (792): unused; `g_BzrFn_ResolveObj76GameObject` (492) repeats the literal.
- `kSteamDistributedRecordDeathIntAddr` (1109) == `kGogDistributedRecordDeathIntAddr`; both "advisory" per their own comment, still selected at 13577.
- `kLoadQueuedState` (571), `kMagnetMineClassSoundNameOffset` (761), `kMineOwnerOffset` (760), `kObjectClassOdfOffset` (703), `kObjectClassOdfLen` (704): declared, never read.
- `JumpSnipeProbeLogState`/`g_JumpSnipeProbeLogState` are used (16892) — not dead; listed only because the range grep suggested otherwise.
- Function-pointer typedefs with no use in the file: none found dead; all `Fn*` aliases resolve to at least one static.
- Duplicate `#include "../engine/native_ui_validation.h"` (lines 21 and 37).
- `ResolveFlagSourceDirectoryPath` 10362-10367: `if (DirectoryContainsSupportedFlagSources(dir)) return dir; return dir;` — both branches identical.
- `EnsureFlagCatalogLoaded` 10874-10878: `if (!g_ConfigRequestedFlagsDirectory.empty()) status = "No images in flags folder."; else status = "No images in flags folder.";` — identical branches.
- Test-only seams compiled into release: `g_ForceGenericChunkBatchFailure` (3084), `g_ForceGenericChunkNonUnitScale` (3092), `g_UiManualObjectDedupeTestInjected` (2482) — used, but only reachable via env vars; candidates for `#ifdef` if the file is split.

## Performance notes

- `TickChunkProxyDebug` is invoked twice per frame (sim hook 40448 with `allowManualSubmit=false`, render hook 39371 with the camera). The sim-side call only needs expiry + transform mirroring; the second full `UpdateChunkProxySlotPosition` pass, including `FindChunkResolvedBindingEntryForGeom` and `GetGenericChunkBatchKind` per slot, is redundant when the render hook is installed.
- `LogChunkDiagnostic` (3474) formats into an 8 KB stack buffer and then formats *again* through both `Log` and `LogShimW`. It is behind `AcquireChunkLogSlot` budgets in most call sites, but several diagnostic-only sites (`TryConvertChunkSimTransformToRenderSpace` origin log, `IsCanonicalGenericChunkPayload`) are once-only and fine. Keep budgets on every new call.
- `RebuildAndSubmitGenericChunkBatch` (8329) is well engineered: version-hash reuse, `try/catch` around Ogre, QPC cost sampling. The `g_GenericChunkBatchBuiltMaterial == g_GenericChunkBatchMaterialName` `std::string` compare per traversal is negligible but could be a bool.
- `MaybeLogDx11EnhancedLightingState` (7961) constructs a `std::string scheme` every 250 ms when enabled — acceptable for a diagnostic.
- `RecordMultiplayerCareerStats` (10181) loads, rewrites, and atomically replaces `career_stats.cfg` under an SRW lock; the later code (16860) moved the hot path to an event sink, but the queue-full fallback still does this from the RecordDeath detour.
- `SetStockScrapPilotPanelsVisibleByUv` (4374) allocates two `std::vector`s and re-verifies every cached address per call; it is called from the 200 ms refresh tick path (15842) only on state transitions, so acceptable.
- `IsLikelyLiveOgreObject` (6784) does `GetModuleHandleA` + `VirtualQuery` per sub-entity per frame when the manual submit path is active; cache the module handle like `ResolveOgreProcByOffset` does.

## Positive notes

- Every engine-memory read in this range is wrapped in `__try`, and the POD-only rule for `__try` frames is stated and followed (`SehScanHudSpriteTable` comment at 3985, `TryReadViewportSchemeName` at 7842).
- Layout offsets shared with `bzr_object_layout.h` are pinned with `static_assert`s (698-703, 2947-2960, 3005-3010) and by `tests/object_layout_tests.cpp`; the comments record the exact instruction that proves each offset and explicitly warn about the 1.5-to-Redux shift trap. This is the model for any new offset.
- `ResolveOgreProcRaw` caches negative lookups and documents the 45 %-CPU incident that motivated it — a good example of turning a perf regression into a structural guard.
- The HUD rect table base is validated against known atlas UVs before any write, and both hide and restore paths re-verify the live record before touching memory (4400-4470).
- `SaveCareerStatsFile` writes through a temp file and `ReplaceFileW`, with fallbacks, instead of truncating in place.
- The `[Fixes]` Enabled-vs-Active split (2596-2612) and `IsSinglePlayerSession` fail-closed sentinel (`kLocalPlayerNetIdUnreadable = 0xFFFF`, 1121) make the multiplayer gate hard to get wrong for new features.
- The generic chunk batch path uses C++ `try/catch` around Ogre calls and stands the feature down permanently on failure (`g_GenericChunkBatchRuntimeAvailable`), with a same-frame rehydrate to the entity path — the right shape for a renderer-side fallback.
