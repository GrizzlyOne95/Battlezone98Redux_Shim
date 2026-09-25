<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# bzr_hooks.cpp lines 33000-end, plus its two .inl includes

Scope read end to end: `src/patches/bzr_hooks.cpp` 33000-42854, `src/patches/ogre_entity_frustum_cull.inl` (1571 lines), `src/patches/chunk_proxy_generic_meshes.inl` (60 lines, pure constexpr data), plus `include/bzr_hooks.h`, `include/bzr_object_layout.h`, and the helpers referenced from the range (InstallInlineDetour32, ExpectedBytesMatchAt, InstallRadarLayoutHookIfPossible, ResolveEngineFlameRuntimeTargets, ShouldTraceJetFlames, patcher.cpp filter/retry logic, patches.json entries, trampolines.cpp stubs).

## Summary

Overall the range is careful code: every detour has a whole-instruction byte guard, engine reads sit in POD-only SEH frames, log output is budgeted, and the frustum-cull file is genuinely hot-path aware (fixed-capacity open-addressed tables, RTTI classified once per vtable, no allocation per visit). The problems are mostly at seams rather than in the hooks themselves.

Top three:
1. **Shadow-far override silently stops working after 16 stock applies** (`bzr_hooks.cpp:35836`): the telemetry line budget also gates the functional re-apply, so a long session (mission loads + quality changes) returns to the stock 128 m clip with no log line saying so.
2. **RetryDeferredRuntimeHooks runs concurrently on two threads on Steam** (`bzr_hooks.cpp:36017` vs `patcher.cpp:1288-1295` and four SDK bridge entry points): ~30 installers use plain `bool` latches and `InstallInlineDetour32` is not atomic, so a bridge call from Lua during the 25 s Steam settle loop can race a live code patch.
3. **Fail-open writes and a dead/misleading tail**: the radar-scale bridge writes `0x008E77B0` even when its byte guard failed (`36387-36406`); ~300 lines of retired weapon-mask code carrying wrong (BZ 1.5) offsets are still compiled, one of which is an empty function reached by two *live* code patches; and the map-filter port that AGENTS.md calls "disabled" has no runtime filter excluding it and frees engine-owned memory with the shim's CRT.

## Findings

### [Medium][High] Telemetry budget disables the shadow-far fix after 16 applies — src/patches/bzr_hooks.cpp:35836
```cpp
if (g_OverrideDistance <= 0.0f ||
    g_TelemetryLines >= kMaxTelemetryLines)
{
    return;
}
```
Every path inside `ApplyAfterStock()` increments `g_TelemetryLines` (35855, 35880, 35896, 35906, 35924, 35932), including the successful `action=applied` path and the "pssm-disabled" early applies that command-line mission launches produce. `kMaxTelemetryLines` is 16. `FUN_00680fe0` runs on every mission load (`reverse_engineering/shadow_cutoff_root_cause_20260825.md` lists the `0x007a9590` mission-load caller) and on every quality/detail change, each of which rewrites `setShadowFarDistance(128)`. After the 16th apply the shim returns before re-issuing the override, the stock 128 m clip is back, and nothing is logged — the exact "hard shadow terminator" the feature exists to fix reappears mid-session on a fix that is on by default.
Fix: keep the budget only around the `LogShimA` calls (e.g. `const bool canLog = g_TelemetryLines < kMaxTelemetryLines;`), never around the `setFar(...)` re-issue. Verifiable on Linux only if the budget logic is lifted into `include/shadow_far_distance.h` (already unit-tested there); the live re-apply needs Windows.

### [Medium][Med] Deferred-hook installers race between the patcher thread and the game thread — src/patches/bzr_hooks.cpp:36017, 36158, 36213-36216, 36452, 36531
```cpp
bool SetBomberAiRangeEnabledFromBridge(bool enabled)
{
    RetryDeferredRuntimeHooks();
```
`RetryDeferredRuntimeHooks()` is called from the patcher thread in a 250 x 100 ms loop on Steam (`src/engine/patcher.cpp:1288-1295`) and also from SDK bridges exported to Lua (`openshim_sdk_provider.cpp:96,111,119,133,156,187`), which run on the game thread as soon as a mission script starts. Every installer it fans out to uses a non-atomic `bool` latch (`g_RadarLayoutHookInstalled` 16002, `g_InstallAttempted` 35966, `g_EntityFrustumCullInstalled` inl:1381, etc.) and `InstallInlineDetour32` (34274) does `if (detour.trampoline) return true;` then `memcmp` / `VirtualProtect` / byte-wise writes with no lock. Two threads can both pass a latch; the loser either sees the already-written `E9` and logs a spurious "prologue mismatch" (leaving `*Installed=false` while the hook is live), or reads a torn prologue between `targetBytes[0] = 0xE9` (34316) and the rel32 `memcpy` (34320) and copies it into its trampoline.
Fix: a single `static std::mutex`/SRWLOCK held for the body of `RetryDeferredRuntimeHooks()` and `InstallInlineDetour32()`, or remove the `RetryDeferredRuntimeHooks()` calls from bridge entry points and rely on the patcher thread. Also write the rel32 before the opcode and store the opcode last. Windows only.

### [Medium][Med] Radar-scale bridge writes an absolute engine address even when its byte guard failed — src/patches/bzr_hooks.cpp:36394-36402
```cpp
InstallRadarLayoutHookIfPossible();
__try
{
    *reinterpret_cast<float*>(kRadarSizeScaleAddr) = clamped;
}
```
`InstallRadarLayoutHookIfPossible()` (16000) verifies the layout-builder prologue at `kRadarLayoutBuilderAddr` and stands down on mismatch, but neither `SetRadarSizeScaleFromBridge` nor `RefreshRadarSizeScaleState` (16077-16098, same pattern outside this range) checks `g_RadarLayoutHookInstalled` before storing to `0x008E77B0`. On a build where the guard fails, the write still lands on whatever lives at that address (SEH only catches an unmapped page). This is a fail-open write on a project that documents fail-closed as the rule. `GetRadarSizeScaleFromBridge` (36372) has the same unguarded read, which is harmless.
Fix: `if (!g_RadarLayoutHookInstalled) return false;` before the store in both places (the byte-guarded builder is the identity proof for the neighbouring globals). Windows only.

### [Medium][Low] Map-filter port frees engine-owned containers with the shim CRT, and is not actually disabled — src/patches/bzr_hooks.cpp:38879-38892, 38984-38996, 39112-39115, 39207-39212
```cpp
static void BzrVectorClear(BzrVector* v)
{ ...  BzrStringFree(cur);  ...  std::free(v->begin);
```
`MapFilters1Rebuild` and `MapFilters2Filter` receive the engine's own `MapFilterList`/`MapRing` (`listPtr` from the engine frame, trampolines.cpp:790-835) and immediately `std::free` the vector storage and `operator delete` every ring entry. OpenShim is v143 and the game is MSVC120 (the code itself says so at ~41090), so those are different CRT heaps; freeing a block the engine allocated is heap corruption. Whether the engine has already emptied those containers before the trampoline sites (`0x007A31D9`, `0x00752A82`) is not visible from the shim, so confidence is low. What is verifiable: AGENTS.md calls this "the disabled clean-room filter/sort port", but `FilterPatchesForRuntime` (patcher.cpp:481-500) filters `Map Sorting`/hop-fix/vehicle/chunk/prodmenu/BZRNet names and has **no** entry for `Map Filters 1/8 .. 8/8` (patches.json:672-711), so the eight patches are applied whenever their `expected_original` bytes match.
Fix: either add the eight names to a runtime filter defaulting to off (matching the documented status), or make the port never free storage it did not allocate (track shim-allocated blocks, or resolve the engine's `free`/`operator delete` and use those). Windows only.

### [Medium][Med] Remembered-bounds table is keyed by raw `Mesh*` and never invalidated — src/patches/ogre_entity_frustum_cull.inl:281-317, 1063-1075
```cpp
if (!candidate.haveAsset)
{
    std::memcpy(candidate.assetMinimum, box, ...);
    candidate.haveAsset = true;
}
```
Entries are inserted on the first finite `_setBounds` and never removed. Ogre unloads and reloads meshes between missions/resource-group changes, and the allocator reuses addresses, so a new mesh can land on a slot whose `assetMinimum/assetMaximum`, `haveAsset`, `sawInfinite`, `restoreClassified/restoreExcluded` all describe a *different* mesh. The private cull is safe on reuse (it reads `minimum/maximum`, which every finite write refreshes), but the restore path (`OPENSHIM_RESTORE_CRAFT_BOUNDS`) derives its substitute box from the stale asset box, which can be *smaller* than the new mesh — the one outcome the file's header says the design cannot produce (a visible craft culled). Separately, the table never shrinks: after ~768 distinct meshes over a session, `g_RememberedMeshBoundsDropped` grows and newly loaded craft silently get no recovery.
Fix: `MeshSetBoundsHook` already captures `callSite`; when a finite write comes from inside `OgreMain.dll` (the serializer's `readBoundsInfo`), treat it as a fresh load and reset the entry (`assetMin/Max` = box, `sawInfinite=false`, `restoreClassified=false`). Alternatively detour `Mesh::unload`/dtor to erase the slot. Windows only.

### [Low][High] `InstallEntityFrustumCullingIfEnabled()` is called before its enable flags exist — src/patches/bzr_hooks.cpp:34947 vs 35080-35103
```cpp
InstallEntityFrustumCullingIfEnabled();   // 34947
...
g_EntityFrustumCullEnabled = !(EnvFlagEnabled(...));   // 35080
```
On the first `ResolveBzrHooks` pass both `g_EntityFrustumCullEnabled` and `g_RestoreCraftBoundsEnabled` are still `false`, so the 34947 call returns at inl:1383 without doing anything; the real install happens later from `RetryDeferredRuntimeHooks` (36031). The call is dead and misleading about ordering. Fix: delete line 34947 or move the env parsing block (35076-35103) above the install sequence. Linux: n/a (trivial).

### [Low][High] Two live code patches call an empty function; retired helpers with BZ 1.5 offsets still compiled — src/patches/bzr_hooks.cpp:37563, 37375-37561, 38007-38177
```cpp
void __cdecl ApplyWeaponMaskCarrierBiasForCraft(void* /*craft*/)
{
}
```
`ApplyWeaponMaskCarrierBiasForCraft` is a no-op, yet patches.json:597-606 ("Decoded/Raw Weapon Mask Carrier Bias Hook") still patch two engine sites whose trampolines (`trampolines.cpp:1513,1526`) exist only to call it, and `EngineFlameHoverCraftEmitHook` (39305) calls it per flame emit. Each is a patched call site plus a full `pushad/popad` round-trip for nothing. The retirement comment (37540-37561) is excellent; the code it retires is not removed (see dead-code list). `TraceArtilleryMaskFromProcess` (38007) has no callers and reads craft `+0x210/+0x1C8/+0x1CC`, the 1.5 offsets the same comment says are wrong for Redux, so if anyone wires it up it prints wrong fields with confidence.
Fix: drop the two patch entries + trampolines, the call at 39305, and the dead helpers; keep the exported symbol only if an external DLL resolves it (nothing in this repo does). Linux: build + `grep` verifiable.

### [Low][Med] Per-frame [FRUSTUMCULL] Info line for the whole process lifetime — src/patches/ogre_entity_frustum_cull.inl:1232-1288, 1339
```cpp
ReportFrustumCullIntervalIfDue();   // called from ProcessVisibleObjectHook
```
The private cull is on by default, and `ReportFrustumCullIntervalIfDue` emits one `LogShimA(Info)` line every 1000 ms unconditionally while a scene is being traversed — ~3600 log lines per hour in every normal session, plus a `GetTickCount()` per visited object (cheap, but it is the only work in the hook that runs after the original for non-entities). Fix: only log when a counter changed since the last window or when `g_FrustumCullCensusEnabled`/a trace env is set; keep the counters. Windows only (log volume), trivially reviewable.

### [Low][Med] Raw addresses hardcoded in feature code rather than scripts/patches.json — src/patches/bzr_hooks.cpp:33461-33465, 34681-34790, 35699-35703, 37619-37620, 37270
```cpp
constexpr uintptr_t kRawMouseInputEnabledAddr = 0x00918424;
...
g_BzrFn_VehicleListSet = reinterpret_cast<FnVehicleListSet>(0x0076B7A0);
```
The raw-input block (four absolute addresses, guarded by a base==0x00400000 check and whole-instruction signatures, so it fails closed), the ShadowFarOverride RVAs (35699-35703, guarded by PE timestamp/size), `kReduxCarrierGetWeaponAddr`/`kReduxCarrierSetSelectedAddr` (called unguarded from three hooks, but only reachable through patches.json-registered sites), `kGogSetDamageFlagsAddr` (37270, called from the four "Damage Reveal Probe" sites) and the ~90-line literal table inside `ResolveBzrHooks` (34681-34790, assigned identically for GOG and Steam with no guard) all violate the "sites and addresses live in scripts/patches.json" rule. None is a correctness bug on 2.2.301; they are the reason the next build change will be found by a crash rather than a `[SKIP]` line. Fix: move them to the `static_pointers`/`resolves` arrays with `expected_original` and resolve through `HookEngine::ResolveNamedAddress`, as `EngineFlame::AddFlame` already does (34779). Linux: n/a.

### [Low][High] Duplicate if/else branches and a tautology — src/patches/bzr_hooks.cpp:35266-35273, 35441-35462, 39072
```cpp
if (MapEntryIsStock(entry) || !MapEntryIsStock(entry))
    flags |= 0x1;
```
Three places compute the same value in both arms (`g_ChunkTraceEntryLimit`, `g_SatelliteVisibilityObjectLimit`, `g_SatelliteVisibilityLogIntervalMs`) and 39072 is always true. Harmless, but each hides whether a specified/unspecified distinction was intended. Fix: collapse to one statement each. Linux: n/a.

### [Low][Med] Env-variable reads on UI/input paths — src/patches/bzr_hooks.cpp:38670-38671, 38684-38685, 39120-39121, 39216-39217, 33587-33588
```cpp
if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
    EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
```
`EnvFlagEnabled` is a `GetEnvironmentVariableA` (process-environment lock + scan). The map-filter scroll hooks, rebuild/filter hooks and `ShouldTraceRawMouseInput` (per raw packet while the 256-packet budget lasts) re-read it every call. `ShouldTraceJetFlames` (27695) and `ShouldRunUiWidgetProbe` (40803) already show the cached pattern. Fix: cache once in a `static int`. Linux: n/a.

## Dead or unused code (list with evidence)

All verified with `grep -rn -w` over `src/ include/ tests/ scripts/`:

| Symbol | Location | Evidence |
|---|---|---|
| `TryPrepareArtilleryVolley` | bzr_hooks.cpp:38072-38108 | only its definition; the only caller of `IsHowitzerCraft` (37405), `CollectCarrierVolleyIndices` (37521), `SnapshotCarrierState` (37485) |
| `IsWeaponMaskCarrierBiasCraft`, `FindPreferredWeaponSlot`, `FindWeaponArrayIndexForSlot`, `SwapCarrierBits`, `RestoreCarrierState`, `MoveCarrierWeaponIndexToFront`, `CarrierSnapshot`, `kHowitzerVft*`, `kMinelayerVft*`, `kGameObjectCarrierOffset(0x198)`, `kGameObjectWeaponMaskOffset(0x210)` | bzr_hooks.cpp:37375-37561 | no references outside this block; block is documented as retired at 37540 |
| `ArtilleryDoAttackHook` + `InstallArtilleryDoAttackHookIfPossible` + forward decl at 550 + `g_ArtilleryDoAttackDetour` bookkeeping in `ResolveBzrHooks` (34553-34558) | bzr_hooks.cpp:38110-38177 | installer has no callers; the hook is a pure pass-through, so even if installed it would only add a detour with no effect |
| `TraceArtilleryMaskFromProcess` | bzr_hooks.cpp:38007-38070 (decl bzr_hooks.h:203) | no callers in src/ or trampolines; reads 1.5 offsets |
| `ApplyWeaponMaskCarrierBiasForCraft` (empty body) | bzr_hooks.cpp:37563 | still reached from trampolines.cpp:1513,1526 and 39305 — live patches doing nothing |
| `InstallEntityFrustumCullingIfEnabled()` call at 34947 | bzr_hooks.cpp:34947 | always a no-op (flags set at 35080-35103) |
| `g_WeaponMaskCarrierBiasEnabled` (write-only global) | bzr_hooks.cpp:2844, 34648, 36182, 36544 | grep over the whole file shows four writes and zero reads; `SetWeaponMaskCarrierBiasEnabledFromBridge` (36180) therefore toggles nothing — the WMASK hooks read `g_AiWeaponMask*Active` instead |
| `FlushChunkFragmentEventsForShutdown` | bzr_hooks.cpp:42844 | empty stub, called by the host; fine to keep but should say so in the header |
| `kBz15UiScale` | bzr_hooks.cpp:41516 | defined, never used (grep: 1 hit) |
| Identical if/else arms | 35266-35273, 35441-35462 | see finding above |

## Performance notes

- **ProcessVisibleObjectHook** (inl:1290-1342) is the hottest code in scope: per visible MovableObject per camera pass (main + PSSM cascades). The path for a non-entity is one vtable-hash probe; for an entity it is `getWorldBoundingBox(true)` (which re-derives the world AABB that stock `processVisibleObject` then derives again for `visibleBounds->merge`) plus `Camera::isVisible`. Infinite-box entities add `Entity::getMesh` + a hash probe + a 3x4 affine transform. No allocation, no string work, no logging on the per-object path other than the 1 Hz report above. Good.
- `EntityUpdateRenderQueueHook` (inl:1220) is a single TLS load; `MeshSetBoundsHook` (inl:1160) only runs on spawn.
- Shadow-caster traversals are counted but not culled (documented), so with the default private cull the PSSM passes still submit every craft; the restore path is what fixes that and it is opt-in. Worth revisiting the default once the stale-slot issue above is closed.
- `LegacyWorldUpdateRenderQueueHook` (39403) fans out to 12 tick functions every rendered frame (per camera). Each claims internal throttling; the aggregate is still a dozen calls + `GetOgreSceneManagerRuntime()` per frame. If this file is split, the render-tick dispatcher deserves to own a single `frameId` gate.
- `ChunkEffectSimulateHook` (40403) re-checks eight `*Installed` latches and runs ~10 sampler/reconcile calls per sim tick; same comment.
- `AiFindObjectClassCollectHook` (34120) does an `std::any_of` over up to 4096 pairs per call (O(n^2) over the class list) — load-time only, acceptable.
- `KickBannedPlayers`/`ReapplyPersistentMutes` (38381-38495) loop 64 sessions x `BanLookup` per membership event — event-driven, fine.
- `InstallInlineDetour32` allocates one RWX page per detour and never frees it (process-lifetime pin, intentional); trampolines copy prologue bytes verbatim with no relocation, so every caller must keep passing position-independent prologues (all callers in scope do).

## Positive notes (things done well that later work should keep doing)

- Every detour in scope anchors on whole instructions with an `expected` byte guard and stands the feature down on mismatch (`InstallInlineDetour32`, raw input 33520-33541, ShadowFar 35994-36003, frustum inl:1479-1535).
- SEH is confined to POD-only helpers with the reason stated (`TryCollapseOwnerBoneSeh` 39676, `DecideFrustumCull` inl:734, `TryUpdateAutoSaveLoadButton` 42447), and C++ exceptions from Ogre are caught at the toolset boundary (41100-41110).
- The frustum file classifies by exact MSVC RTTI name (`.?AVEntity@Ogre@@`), keeps every table fixed-capacity and power-of-two, uses `thread_local` for the suppression flag, and runs the original `processVisibleObject` unconditionally so PSSM bookkeeping stays bit-identical. Its header comment is a model of recording what was measured and what was withdrawn.
- Offsets are derived from the shipped Redux image and cross-checked against 1.5 with the shift table (`bzr_object_layout.h`), and the retired 1.5-offset code carries an explicit "must not be revived as written" note.
- `PreserveSprayEmitterOwner` refuses to write when the field it is about to overwrite is non-zero and traces the refusal, so a wrong offset is visible rather than silent.
- Log budgets are `volatile long` + `InterlockedDecrement` throughout; the raw-input packet trace, chunk fragment walk and WMASK hooks all cap themselves.
- Lobby widget caches are validated by containment in the live parent's child vector before any engine call (`IsWidgetLiveChildOfParent` 40775), which is the right liveness proof for recycled screen addresses.

## SECTION MAP (lines 33000-42854 + includes)

Status key: **active** = compiled and reachable in a default session; **opt-in** = reachable only behind an ini/env flag; **experimental** = gated by a patch-list filter or diagnostic flag; **dead** = no callers.

| Start | End | Feature / hook group | ~Lines | Related openshim.ini keys / patch names / env | Status |
|---|---|---|---|---|---|
| 33000 | 33164 | Producer build menu config (tail of PRODMENU section) | 165 | `producer_build_menu.ini`; patch "Producer Build Menu Root Hook" (filtered by `IsProducerBuildMenuExperimentPatchName`, GOG only) | experimental |
| 33166 | 33364 | AutoSave load path + restart-mission state helpers | 200 | patches "AutoSave Load Button Hook", "Restart Mission Hook Pause/Failure"; `kQueuedLoadPathBufferAddr` etc. (574-580) | active |
| 33366 | 33426 | Vehicle asset debug-exception cache (`CallVehicleListLoadSafely`) | 60 | patches "Vehicle List Mod Fix 1-4/4" | active |
| 33428 | 33751 | Raw mouse input (RAWINPUT) | 325 | `[General] RawMouseInput`; env `OPENSHIM_DISABLE_RAW_MOUSE_INPUT`, `OPENSHIM_TRACE_RAW_INPUT`; stock `rawinput`/`norawinput` tokens; absolute addrs 33461-33465 | active (default off) |
| 33753 | 33827 | Config helpers: `EnvFlagEnabled`, `GetUserConfigPath`, `TryGetUserConfigString/Bool` | 75 | `openshim.ini` reader (all sections) | active (shared infra) |
| 33828 | 33847 | `Set*Original` setters for registry-installed guards | 20 | patch registry glue | active |
| 33849 | 34003 | AIP prereq resolve probe + universe census (AIPRES) | 155 | `[Diagnostics] AipResolveTrace`; patches "AIP Prereq Name Resolve Probe (x3)", "PREREQ_WhatIs" | opt-in diagnostics |
| 34005 | 34151 | AI multi-producer makers (AIMAKER) | 147 | `[Fixes] AiMultiProducerMakers`; patches "AI Multi Producer Maker Collect/Apply", "AI FindObjectClass", "AI Units_Init", "AI GetPrereq" | active |
| 34153 | 34237 | Pilot null-carrier guards (PILOTSAFE) | 85 | exact-call-site guards for Carrier::GetSelected/GetWeapon; `LcbenchSafetyPolicy` | active |
| 34239 | 34272 | Neutral attack orders (NEUTORDER) | 34 | `[Gameplay] AllowNeutralAttackOrders`; resolve "Team::EnemyP(int)" | active |
| 34274 | 34389 | Inline detour engine, `ExpectedBytesMatchAt`, `GetMainModuleDirectory`, `TrimAsciiCopy` | 116 | shared infra (also used by native_ui, pond_class_label, terrain_proxy, light selection) | active |
| 34391 | 34443 | `ApplyShimSettingLive` (settings-UI live re-apply dispatch) | 53 | every `ShimSettingApplyGroup` | active |
| 34446 | 34680 | `ResolveBzrHooks` part 1: global reset block | 235 | all features (state reset on re-resolve) | active |
| 34681 | 34790 | `ResolveBzrHooks` part 2: literal address table (UI ctors, BZRNet, vehicle list, load screen, map filter, localize) | 110 | raw addresses, no guard, same for GOG/Steam | active |
| 34791 | 34936 | `ResolveBzrHooks` part 3: dynamic alpha batching detour (GOG), DynamicGeometry profiler detours + IAT swap | 146 | env `OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING`, `OPENSHIM_DYNAMIC_ALPHA_DEPTH_BUCKET_STRIDE`; `[Diagnostics] OgreProfile` | active / opt-in |
| 34937 | 35672 | `ResolveBzrHooks` part 4: install sequence, env/ini parsing for ~40 features, status log block | 736 | `OPENSHIM_DISABLE_*` family, `[Diagnostics] Trace*`, `[Fixes] OwnedObjectReveal`, `[SinglePlayer] AttackRevealPerceivedTeam`, chunk/mesh/frustum env, `[Network]`, bans | active |
| 35674 | 36015 | Shadow far distance override (SHADOWFAR) | 342 | env `OPENSHIM_SHADOW_FAR_DISTANCE`; RVAs 35699-35703; PE identity check | active (default on) |
| 36017 | 36073 | `RetryDeferredRuntimeHooks`, `AreRequiredDeferredRuntimeHooksInstalled`, `InitBzrHookStrings` | 57 | patcher.cpp entry points | active |
| 36075 | 36574 | SDK bridge getters/setters (UnitVo, bomber AI, howitzer, AI tuning, turbo, convergence, smart reticle, radar, raw input, career reset, mission reset) | 500 | `openshim_sdk_provider.cpp` exports for EXU/Lua | active |
| 36576 | 36962 | HUD sprite rect / scrap-pilot panel bridge (HUD) | 387 | bridge; `[Display]` scrap/pilot layout keys via `BuildScrapPilotHudIniLayout` | active |
| 36964 | 36995 | Target reticle popup getter hook | 32 | `[SinglePlayer] TargetReticlePopupMode`; patch "Target Reticle Popup Recent-Hit Getter Hook" | active |
| 36997 | 37356 | Owned-object reveal chain, spray-emitter owner propagation (naked asm), damage reveal probe (OWNREVEAL/DMGREVEAL) | 360 | `[Fixes] OwnedObjectReveal`, `[Diagnostics] TraceDamageReveal`; patches "Damage Reveal Probe 1-4/4", "Splinter Emitter Owner Propagation" | active |
| 37358 | 37373 | Under-attack alert | 16 | `[SinglePlayer] UnderAttackAlert*`; patches "Under Attack Alert Hook 1/2, 2/2" | active |
| 37375 | 37565 | RETIRED carrier-bias helpers + empty `ApplyWeaponMaskCarrierBiasForCraft` | 190 | patches "Decoded/Raw Weapon Mask Carrier Bias Hook" (live, call a no-op) | dead |
| 37567 | 38006 | AI weapon-mask hardpoint selection + synchronized volley (WMASK) | 440 | `g_AiWeaponMaskArtilleryActive/MinelayerActive` (bridge/ini); patches "Artillery Weapon Mask Select Hook", "LayMines Weapon Mask Select/Trigger Hook", "Artillery Volley Trigger Hook 1-4/4"; raw addrs 37619-37620 | active code, feature off by default |
| 38007 | 38177 | `TraceArtilleryMaskFromProcess`, `TryPrepareArtilleryVolley`, `ArtilleryDoAttackHook` + installer | 171 | none reachable | dead |
| 38179 | 38300 | Producer-menu original setter; Vehicle list mod fix (`VehicleListModFix2`, `VehicleListModFix4Helper`) | 122 | patches "Vehicle List Mod Fix 1-4/4" (asset-scoping filter) | active |
| 38302 | 38495 | Ban identity lookup, `KickBannedPlayers`, `ReapplyPersistentMutes` | 194 | `bans.cfg`/`mutes.cfg`; `[Network] PersistentPlayerMute`; patch "Joiner Event Hook" | active |
| 38497 | 38515 | `ProducerBuildMenuCallHook`, `MapFilters6Rel32` | 19 | patches "Producer Build Menu Root Hook", "Map Filters 6/8" | active |
| 38516 | 38665 | `ChunkRenderResolveHook` (CHUNK) | 150 | `[General] ChunkMeshes`; env `OPENSHIM_CHUNK_*`; patch "Chunk Render Resolve Hook" (filtered) | experimental |
| 38667 | 38695 | Map filter scroll hooks | 29 | patches "Map Filters 7/8, 8/8"; env `OPENSHIM_TRACE_MAP_REFRESH` | active |
| 38697 | 39279 | Clean-room map filter/sort port (`MapFilters1Rebuild`, `MapFilters2Filter`, BzrVector/MapRing/MapEntry helpers) | 583 | patches "Map Filters 1/8 .. 5/8"; documented as disabled but no runtime filter | experimental (see finding) |
| 39281 | 39401 | Engine flame hooks (FLAME) | 121 | `[Display] JetFlames`; patches "HoverCraft Engine Flame Emit Hook 1/2, 2/2", "Engine Flame Control/Submit VTable Hook"; resolves "EngineFlame::AddFlame/ResolveTexture" | active |
| 39403 | 39508 | `LegacyWorldUpdateRenderQueueHook` — per-frame render dispatcher | 106 | patch "Legacy World Update RenderQueue VTable Hook"; drives headlights, flashlight, MP gate, event layer, skinning diag, RQ trace, MP preview fix, chunk proxies, terrain proxy, fog wake | active |
| 39510 | 39825 | Chunk geom dump + partial-fragment bone collapse (CHUNKSPAWN) | 316 | env `OPENSHIM_DISABLE_PARTIAL_FRAGMENT_BONE_COLLAPSE`, chunk trace env; `ChunkMeshes` | experimental |
| 39827 | 40260 | ChunkEffect create/chunklet/partial/full fragment hooks | 434 | inline detours at `kGogChunkEffectCreateChunk*Addr`; env `OPENSHIM_UNSAFE_CHUNK_CREATE_HOOKS` (Steam) | experimental |
| 40262 | 40401 | DynamicGeometry profiler + alpha-depth batching hooks | 140 | `[Diagnostics] OgreProfile`; `OPENSHIM_DISABLE_DYNAMIC_ALPHA_BATCHING` | active (batching) / opt-in (profiler) |
| 40403 | 40469 | `ChunkEffectSimulateHook` — per-sim-tick dispatcher | 67 | patch "Chunk Effect Simulate VTable Hook"; drives jump-snipe probe, MP gate, flag fallback, shader cache, UiPerf, career MP, mpauth, radar, chunk hooks, sat-vis | active |
| 40471 | 40684 | `/help`, `/nickname`, `/ban`, `/mute`, `/unmute` command handler + joiner event | 214 | patches "Custom Command /help Handler", "Joiner Event Hook"; `[Network] PersistentPlayerMute` | active |
| 40686 | 41229 | Lobby UI cache/liveness, cUI widget ABI probe, flag preview PNG (GDI+), invalid-thumbnail plate | 544 | env `OPENSHIM_UI_WIDGET_PROBE`; `[Network]` flags; BMPFIX placeholder | active / opt-in probe |
| 41230 | 42223 | Flag arrow buttons, nickname panel + route readout widgets, nickname edit/apply | 994 | `[Network] LobbyReadouts`, `LobbyBanButton`; env `OPENSHIM_DISABLE_LOBBY_READOUTS`; patches "Lobby BZRNET Integration HOST/CLIENT" | active |
| 42225 | 42400 | Ban/flag/nickname/route button callbacks (`__cdecl` engine callbacks) | 176 | patches "Ban Button Hook 1/2, 2/2" | active |
| 42402 | 42548 | AutoSave load button create/click, restart-mission hooks | 147 | patches "AutoSave Load Button Hook", "Restart Mission Hook Pause/Failure" | active |
| 42550 | 42775 | `BanButtonCreateHost/Client` (lobby injection entry points) | 226 | `[Network] LobbyBanButton`, flags, readouts | active |
| 42777 | 42803 | `SetBzrNetNicknameFromBridge` | 27 | exported `OpenShimImpl_SetBZRNetNickname` | active |
| 42805 | 42842 | GOG-verified local-player lookup (`ResolveLocalPlayerLookupForVerifiedGogBuild`, `TryGetLocalPlayerWorldPosition`) | 38 | used by terrain proxy after SHA-256 gate; `kGogGetPlayerHandleAddr` | active (GOG) |
| 42844 | 42854 | `FlushChunkFragmentEventsForShutdown` stub, C export | 11 | host shutdown | stub |
| inl 1 | inl 1571 | `ogre_entity_frustum_cull.inl`: restored craft bounds + private frustum cull + census | 1571 | env `OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING`, `OPENSHIM_RESTORE_CRAFT_BOUNDS[_SCALE/_SCOPE/_MODE]`, `OPENSHIM_FRUSTUM_CULL_WITH_RESTORE`, `OPENSHIM_FRUSTUM_CULL_MARGIN`, `OPENSHIM_FRUSTUM_CULL_CENSUS`, `OPENSHIM_BOUNDS_TRACE`; OgreMain exports | active (cull on by default; restore opt-in) |
| inl2 1 | inl2 60 | `chunk_proxy_generic_meshes.inl`: constexpr chunk1/chunk2 vertex data + FNV/size pins | 60 | `ChunkMeshes` generic batch | active data |

### Split suggestions derived from the map
- The two per-frame dispatchers (39403, 40403) are the natural spine of a `render_tick.cpp`/`sim_tick.cpp`; every feature they call should register a tick rather than be named there.
- `ResolveBzrHooks` (34446-35672, 1.2k lines) is three things: global reset, address table, feature init/logging. The address table belongs in patches.json; the init block is a per-feature `Init*` call list and could be table-driven.
- Lobby UI (40686-42775, ~2.1k lines including GDI+ PNG generation) is self-contained and touches nothing else in the file except `TrimAsciiCopy`, `ReadBzrNetNickname`, `ApplyBzrNetNicknameAuthoritative`.
- WMASK (37567-38006) and the dead block on either side of it (37375-37565, 38007-38177) should move together, dropping the dead parts.
- The frustum .inl is already a clean unit; it only needs `InlineDetour32`, `LogShimA` and the three enable flags from the host, so it can become a `.cpp` with a 4-function header.

### Calling-convention audit of hooks in range
Checked each hook against how it is installed (inline detour on a `__thiscall` body -> `__fastcall(this, edx, ...)`; call-site rel32 replacement -> `__cdecl` with the trampoline supplying stack args; naked stubs for register-passing sites). All consistent: `ProcessVisibleObjectHook`/`EntityUpdateRenderQueueHook`/`MeshSetBoundsHook` (inl), `ProcessMouseRawInputHook` (`__cdecl`, prologue reads `[ebp+8]`), `ShadowFarOverride::ApplyHook` (`__cdecl` void(void) — matches `void FUN_00680fe0(void)` in the decomp), `DamageRevealProbeHook`/`PersonCarrier*Guard`/`ControlPanelEnemyPAttackOrderHook`/`ChunkEffect*Hook`/`DynamicGeometry*Hook`/`ArtilleryDoAttackHook` (`__fastcall` over `__thiscall`), `OpenShimArtillery*`/`OpenShimLayMines*` (`__cdecl` fed by trampolines.cpp), `SprayEmitterBuildOwnerHook` (naked, `ret 0x14` for the 5-arg thiscall). No mismatches found.
