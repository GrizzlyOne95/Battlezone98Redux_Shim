<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Render profiles, Ogre runtime, DX11 effects, lighting, fog wakes

Scope read end to end: `src/patches/ogre_render_profile.cpp`, `src/engine/render_profile*.cpp`,
`src/engine/render_effect_intent.cpp`, `src/patches/render_effect_intent_exports.cpp`,
`src/engine/ogre_runtime.cpp`, `src/patches/ogre_shader_cache.cpp`, `src/patches/dx11_enhanced_fxaa.cpp`,
`src/patches/dx11_scene_depth.cpp`, `src/engine/scene_depth_facts.cpp`,
`src/engine/dx11_legacy_material_compat.cpp`, `src/patches/d3d_startup_hooks.cpp`,
`src/engine/enhanced_light_selection.cpp`, `src/patches/ogre_enhanced_light_selection.cpp`,
`src/engine/enhanced_resource_bootstrap.cpp`, `src/engine/fog_wake*.cpp`, `src/patches/fog_wake_feature.cpp`,
`src/patches/sun_flash.cpp`, and the matching headers (`render_profile*.h`, `render_effect_intent.h`,
`ogre_runtime.h`, `dx11_*.h`, `scene_depth_facts.h`, `enhanced_*.h`, `fog_wake*.h`, `sun_flash.h`,
`headlight_falloff.h`, `shadow_far_distance.h`, `weapon_convergence.h`), plus the tests listed in the
brief and `Docs/OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md`. Call-site threading was cross-checked in
`src/patches/bzr_hooks.cpp` and `src/plugin/openshim_plugin.cpp`.

## Summary

Overall health is good. COM reference counting in the FXAA and scene-depth paths balances on every
path I traced (including early-outs and the RAII context-state restore), SEH cores are consistently
POD-only/noinline and separated from C++ wrappers, every executable/OgreMain write is byte-verified
first, and the DX9/DX11 gating fails closed (atomic DX11 flag, module presence, OgreMain multi-anchor
identity, IAT displacement checks on all three scheme call sites before any write). No use-after-free,
calling-convention, or fail-open defect was found.

Top three issues:
1. `handleSchemeNotFound` is a per-draw Ogre callback and the DX11 legacy-compat probe does all of its
   expensive work (string copies, vector of candidates, three SEH-guarded calls, cache-key build,
   mutex + set lookups, log-line construction) *before* consulting its own negative cache, so every
   declined/failed material pays that cost per renderable per frame.
2. The Enhanced light-selection hook calls `GetModuleHandleA` (loader lock + module-list walk) on
   every `_populateLightList` call, i.e. per renderable per light-dirty frame.
3. The deferred `ReapplyEffectiveProfileToViewports` path rewrites *foreign/custom* viewport schemes
   to the default modern base, contradicting the fail-open contract that the live hook honours; and
   the FXAA path retries a full D3DCompile plus an Error log every frame after a non-permanent
   resource-creation failure.

## Findings

### [Medium][High] DX11 compat probe does per-draw work before its negative-cache check — src/patches/ogre_render_profile.cpp:2044-2117

```
std::string materialName(kUnknownMaterial);            // 2044
...
std::vector<Dx11Compat::TechniqueCandidate> candidates; // 2055
...
const bool cached = NoteCompatCacheKey(cacheKey);      // 2109
if (cached && path != Dx11Compat::CompatPath::KeepNative) return nullptr; // 2114
```

Why it is wrong: Ogre 1.10's `Material::getBestTechnique` consults
`MaterialManager::_arbitrateMissingTechniqueForActiveScheme` (this listener,
`EnhancedSchemeFallbackListener::handleSchemeNotFound`, line 2237) every time a renderable using a
material without a technique for the active scheme is queued; a null answer is never cached by Ogre.
For any material that was declined or failed once (excluded class, `program-absent` on installs
without the payload, unsupported-after-reload, multi-pass, `SkipShaderless`), every subsequent draw
re-runs `GuardedCopyResourceName` (string copy, 2047), a `std::vector` of `TechniqueCandidate` with a
`std::string` per technique (2055-2071), `DescribeFirstPass` (three SEH-guarded exported calls plus two
string copies, 1430-1472), `snprintf`, `BuildCompatCacheKey` (which allocates a `std::string` per
character via `SanitizeKeyChar`, dx11_legacy_material_compat.cpp:149-157 / 708-713), then the mutex +
`unordered_set` lookup in `NoteCompatCacheKey`, and finally `LogCompatOnce` (string concatenation +
mutex + set lookup) even though the line was already logged. The live log in the comments records 81
declined materials in one run; each of those is a per-frame allocation burst on the render thread.

Fix: keep a small negative cache keyed by `(material pointer, schemeName, lodIndex)` (or by
`materialName` after one cheap `GuardedCopyResourceName`) and test it at the top of
`ProbeDx11LegacyCompat` before any candidate collection; only a miss proceeds to the full ladder.
Clear it when the mutation cache is cleared. The `ResolveBaseSchemeTechnique` walk (1038-1068) is
cheap and can stay as is.

Verifiable: Windows only (needs Ogre). The pure policy pieces are already Linux-tested.

### [Medium][High] `GetModuleHandleA` on every `_populateLightList` call — src/patches/ogre_enhanced_light_selection.cpp:287-294

```
if (!sceneManager || !schemeBuffer || schemeBufferSize == 0 || !outBudget
    || !GetModuleHandleA("RenderSystem_Direct3D11.dll"))
```

Why it is wrong: `PopulateLightListHook` (502) runs once per movable object whenever the scene's
light-dirty counter changed, which in this game is essentially every frame (headlights, projectiles,
explosions move every tick). `GetModuleHandleA` takes the loader lock and walks the module list with a
case-insensitive string compare on every call. The install path already refused to install without
that module (567) and Ogre render-system plugins are never unloaded, so the check can never change
its answer after install. The same call also allocates `stockOrder`, `candidates`, the `previous`
vector copy (383-404, under `g_HistoryMutex`), and inside `RankCandidates` an `unordered_set` and the
`ranked` vector (enhanced_light_selection.cpp:127-131) on every invocation.

Fix: drop the module check from `GetEnhancedScheme` (or latch a `static bool` at install). Optionally
reuse thread-local scratch vectors for `stockOrder`/`candidates`/`ranked` and pass `previous` by const
reference under the lock instead of copying.

Verifiable: Windows only for the hook; the ranking allocation change is measurable with
`tests/enhanced_light_selection_bench.cpp` on Linux.

### [Medium][High] Deferred reapply rewrites foreign/custom viewport schemes (fail-open contract broken) — src/patches/ogre_render_profile.cpp:2780-2791

```
const std::string_view modernBase = NormalizeModernMaterialScheme(current, {});
char buffer[48] = {};
if (BuildMaterialSchemeForProfile(effective, modernBase, buffer, sizeof(buffer)))
{
    const std::string target(buffer);
    if (target != current) { WriteViewportScheme(viewports[i], target); ...
```

Why it is wrong: the live hook (2373-2396) only prefixes engine-native modern bases and our own
`en-`/`og-` names and passes anything else through untouched ("Fail open: foreign/custom schemes pass
through"). The reapply path has no such guard: `NormalizeModernMaterialScheme` maps an unrecognised
scheme such as `mymod-scheme` to `high-pssm` (render_profile.cpp:150-157), so the viewport is
overwritten with `high-pssm` / `en-high-pssm` / `og-high-pssm`. The drain runs unconditionally at every
boot (`PublishReapplyPending()` at 872 after backend observation), on every ini reload (2846), every EXU
request (2820) and every mission reset with an override (2836), and it runs even when the effective
profile is Redux. The same block also asserts the Glow compositor ON for Redux/Enhanced on every reapply
(2796), regardless of what the viewport had.

Fix: mirror the hook's guard before computing `target`:
`if (!IsModernMaterialScheme(current) && !starts_with("en-") && !starts_with("og-")) continue;`
Better, hoist a single `ShouldRewriteMaterialScheme(std::string_view)` into `render_profile.cpp` used by
both paths so they cannot diverge again, and only touch Glow when the profile is Retro or when it was
previously suppressed by us.

Verifiable: the shared guard is Linux-testable in `tests/render_profile_tests.cpp`; the call site is
Windows only.

### [Medium][High] FXAA retries a full shader recompile and logs Error every frame after a non-permanent resource failure — src/patches/dx11_enhanced_fxaa.cpp:782-806, 704-728, 849-861

```
g_Runtime.Reset();
device->AddRef();
g_Runtime.device = device;
device->GetImmediateContext(&g_Runtime.context);
if (!g_Runtime.context || !CreateDeviceResources(device)) { g_Runtime.Reset(); return false; }
```

Why it is wrong: `CreateDeviceResources` sets `g_PermanentFault` only when `D3DCompile` fails (692,
700). If `CreateVertexShader`/`CreatePixelShader` (704-728) or any of the fixed-state creations
(730-777) fail, it returns false, `EnsureDeviceResources` calls `g_Runtime.Reset()` (801) which nulls
`g_Runtime.device`, and the next `Present` (1064 -> 888 -> 907) re-enters the same path: `AddRef`,
`GetImmediateContext`, two `D3DCompile` invocations of the embedded FXAA source (tens of milliseconds
each with `OPTIMIZATION_LEVEL3`), failure, and another `LogLevel::Error` line. `EnsureSourceResources`
has the same shape: a failed `CreateTexture2D`/`CreateShaderResourceView` (832-847) logs Error (851)
and returns false with no latch, so it is retried and logged on every frame at that resolution.

Fix: on any `CreateDeviceResources` failure set `g_PermanentFault` (or a per-device fault latch keyed by
the `ID3D11Device*`), and latch the source-resource error log the way `g_UnsupportedFormatLogged`
(928) already does.

Verifiable: Windows only.

### [Low][High] Orphaned seam code and dead state left behind by the startup-seam extraction — src/patches/ogre_render_profile.cpp:285-388, 67, 77

```
__declspec(noinline) static bool GuardedWriteSlotValue(void* slot, void* value)   // 376, unreferenced
bool s_backendTransportEnabled = true;   // 77; written at 241-247, never read
bool s_backendDetected = false;          // 67; written at 863, never read
```

`GuardedWriteSlotValue` now lives in `src/engine/startup_backend_seam.cpp:611` and the copy here has
no caller (grep of src/include/tests), which is a C4505 at the project's Level4 warning setting.
Lines 285-374 are 79 comment lines describing functions that no longer exist in this file (transport,
marker, IAT arm, call-site proof, SEH forwarder). `RequestContentRenderProfile` (2809) has external
linkage but no header declaration and no external caller; it belongs in the anonymous namespace.

Fix: delete the duplicate function, the two write-only statics and the orphaned comment blocks;
make `RequestContentRenderProfile` internal.

Verifiable: Linux (grep / build of the pure units is unaffected); the Windows build confirms no C4505.

### [Low][High] Raw executable addresses in feature code rather than `scripts/patches.json` named resolves — src/patches/ogre_render_profile.cpp:884-896, include/sun_flash.h:109-115

```
constexpr uintptr_t kViewportSetMaterialSchemeIat = 0x00869810;
constexpr SchemeCallSite kSchemeCallSites[] = { { 0x00681585, ... }, { 0x00682AA0, ... }, { 0x00682EA7, ... } };
```

and `kScreenFlashAddFlashAddr = 0x0049B4C0ul`, `kScreenFlashInstanceAddr = 0x0097838Cul` in
`sun_flash.h`. Only the operand site `0x004F9FD4` is in `scripts/patches.json` (line 543); the IAT
slot, the three call sites and the ScreenFlash callee/instance are not. All are byte-verified before
any write (2465-2491; `CallSiteMatchesStock` sun_flash.cpp:175-191), so they fail closed and this is
maintainability only. `ogre_enhanced_light_selection.cpp:32,189` carries OgreMain RVAs
(`0x003B3930`, `0x0021BAE0`) guarded by PE timestamp/size plus three byte anchors; those are OgreMain
rather than exe offsets and arguably outside the rule.

Fix: move the exe values to named resolves in `scripts/patches.json` and resolve them through
`HookEngine::ResolveNamedAddress`, keeping the existing byte checks. Do not change the values.

Verifiable: Windows only (patch loader).

### [Low][Med] Shadowing-script scan is non-recursive while the Ogre location is registered recursively — src/engine/render_profile_resources.cpp:141

```
for (std::filesystem::directory_iterator it(resourceDir, scanEc), end; ...
```

The comment at 124-139 explains that a stray `.program`/`.material` shadows the payload because Ogre
parses the whole location; the runtime registers that location with `recursive=true`
(ogre_render_profile.cpp:1607). A stale script in a subdirectory therefore still wins while validation
passes. Fix: use `recursive_directory_iterator` with `skip_permission_denied`.

Verifiable: Linux, via `tests/render_profile_resources_tests.cpp` (add a subdirectory case).

### [Low][High] D3D9 startup hooks are pass-through logging only, and the header claims otherwise — src/patches/d3d_startup_hooks.cpp:121-149, include/d3d_startup_hooks.h:11-13

```
// so addon DLLs can be loaded before the game creates its real D3D device.
```

`Hooked_Direct3DCreate9`/`Hooked_Direct3DCreate9Ex` only call the original and `Log`. In addition
`PatchIAT` (81-93) uses `FirstThunk` as the name table when `OriginalFirstThunk == 0` and then treats
bound function addresses as `IMAGE_IMPORT_BY_NAME` RVAs without an SEH guard, and
`ApplyD3DStartupHooks` (170-183) sleeps up to 5 s per watched module on the patch thread. Gated by
`ShouldEnableD3DStartupHooks()` (patcher.cpp:189) so normally inert.

Fix: either delete the feature or correct the comment and add the `OriginalFirstThunk == 0` guard used by
the other two IAT walkers.

Verifiable: Windows only.

### [Low][Med] Header declares a function inside an anonymous namespace — include/dx11_enhanced_fxaa.h:15-23

```
namespace { long __stdcall HookFactoryCreateSwapChain(IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**); }
```

Every TU that includes this header (`src/plugin/openshim_plugin.cpp`) gets its own internal-linkage,
never-defined declaration. Harmless today, but the declaration exists only to let the .cpp forward
declare the hook; it belongs in the .cpp.

Verifiable: Linux (compile of the header alone).

### [Low][Med] Scene-depth immediate-context pointer is stored with asymmetric ownership — src/patches/dx11_scene_depth.cpp:670-678, 656-668

```
if (!context) device->GetImmediateContext(&context);   // AddRef'd here...
g_ImmediateContext = context;                          // ...but not when the caller supplied it
```

`EnsureContextHook` dereferences `g_ImmediateContext` from the worker thread every 15 s (873) and from
every non-depth `CreateTexture2D` (492). When the caller-supplied pointer path is taken no reference
is held; when the `GetImmediateContext` path is taken the reference is never released. In this game
the immediate context lives for the process, so exposure is nil, but the two paths should agree: always
`AddRef` what is stored and `Release` it in `ShutdownDx11SceneDepth`.

Verifiable: Windows only.

### [Low][Med] Epoch-tracker contract comment and test model the opposite drain order from the runtime — include/render_profile_request_tracker.h:255-258, src/patches/ogre_render_profile.cpp:2439-2445, tests/request_apply_tracker_tests.cpp:40

```
if (s_reapplyPending.exchange(false, std::memory_order_acq_rel))
{
    const uint64_t coveredEpoch = s_applyTracker.SnapshotPublished();   // snapshot AFTER consuming
```

The header says the drain "snapshots the highest published epoch BEFORE consuming the pending flag".
The runtime consumes first. I checked the race: because `ResolveAndPublishLocked` stores
`s_effectiveProfileAtomic` before `Publish()` (release) and the drain's snapshot is an acquire load, any
epoch the snapshot observes has its state visible to the apply pass, so the runtime order cannot
over-report. It is not a bug, but the documented contract and the test do not describe the code.
Also `PublishReapplyPending` (126-130) discards the epoch that `Publish()` returns and
`RequestRenderProfile` re-snapshots (2990-2994), so a concurrent publisher makes it under-report
(transient StoredDeferred, documented).

Fix: correct the header/test comment (or return the epoch from `PublishReapplyPending` and use it).

Verifiable: Linux (`request_apply_tracker_tests`).

### [Low][Med] Mutual factory-vtable re-assert between the FXAA and colorspace observers can drop one from the chain — src/patches/dx11_enhanced_fxaa.cpp:1162-1166, 234-238

```
// Reassert our top-level wrapper before returning so later swapchains remain covered
InstallFactoryHooks(self);
```

Both observers (`dx11_colorspace_diagnostic.cpp:1771`) install with "keep the first predecessor"
semantics and both re-run `InstallFactoryHooks` from their device hooks. If the inner observer's device
hook re-asserts after the outer one installed, the outer wrapper is unlinked until the next
`CreateSwapChain` (where the outer one re-asserts last). Only reachable when both opt-in diagnostics
are on and more than one device/swapchain is created.

Fix: re-assert only when `vtable[index]` is neither our hook nor a known chain member, or share one
dispatcher between the two DX11 observers.

Verifiable: Windows only.

### [Low][High] Dead local in `ClassifyLegacyPass` — src/engine/dx11_legacy_material_compat.cpp:484, 496

```
std::string mapped;
...
(void)mapped;
```

Allocates nothing (SSO) but is noise. Delete. Verifiable: Linux (`dx11_legacy_material_compat_tests`).

### [Low][Med] `"0"` opts out of the shadow far-distance fix but `"0.0"` is Rejected — include/shadow_far_distance.h:158-160, 182-186

`EqualsIgnoreCase(configured, "0")` returns OptedOut, while any other spelling of zero parses to
`0.0f`, falls below `kMinFarDistance` and is logged as Rejected (still no override, so behaviour is the
same, but the log blames the user). Fix: treat a parsed value `<= 0` as OptedOut.

Verifiable: Linux (`shadow_far_distance_tests`).

## Dead or unused code (list with evidence)

- `src/patches/ogre_render_profile.cpp:376-388` `GuardedWriteSlotValue`: no reference in src/include/tests
  outside `startup_backend_seam.cpp`, which has its own copy.
- `src/patches/ogre_render_profile.cpp:77,241-247` `s_backendTransportEnabled`: written, never read.
- `src/patches/ogre_render_profile.cpp:67,863` `s_backendDetected`: written, never read.
- `src/patches/ogre_render_profile.cpp:285-374`: 79 lines of comments for functions that were moved
  to `src/engine/startup_backend_seam.cpp`.
- `src/patches/ogre_render_profile.cpp:2809` `RequestContentRenderProfile`: external linkage, no
  header declaration, no external caller.
- `src/engine/dx11_legacy_material_compat.cpp:484,496` `mapped`.
- `include/dx11_legacy_material_compat.h:52` `LegacyPassKindName`: defined at .cpp:160 and referenced
  nowhere else (not even tests).
- `include/dx11_legacy_material_compat.h:229-245` `CompatCounters`/`FormatCompatSummary` and
  `FormatRtssUnavailableLog`: only used by tests; the runtime keeps its own atomic counters in
  `CompatProbeState` (ogre_render_profile.cpp:1366-1379) and never emits the summary. Either wire the
  summary into shutdown logging or drop the duplicate counter struct.
- `include/scene_depth_facts.h:149` `Registry::NextSerial`: no caller anywhere.
- `include/ogre_runtime.h:313` `OgreRuntime::ResolveOffset`: defined, no caller (the other
  `OgreRuntime` helpers are used by the profiler/trace modules).
- `include/fog_wake.h:39` `Field::Clearance()`: only tests ("For future upload"); fine to keep but
  note it is the only accessor the eventual GPU path will need.
- `src/patches/d3d_startup_hooks.cpp` hooked functions: pass-through logging only (see finding).
- `include/render_effect_intent.h` `RegisterProvider`/`UnregisterProvider`: no provider exists in
  src/ (documented as intent plumbing only; not flagged as dead, but note that every export currently
  answers `NotImplemented`).
- Duplicated helpers that should be shared: `PatchComVtableEntry` (dx11_enhanced_fxaa.cpp:200,
  dx11_scene_depth.cpp:189, dx11_colorspace_diagnostic.cpp:1170), `PatchIatFunction`/`PatchIAT`
  (dx11_enhanced_fxaa.cpp:248, dx11_scene_depth.cpp:734, d3d_startup_hooks.cpp:58; 11 files in src/
  contain an `IMAGE_DIRECTORY_ENTRY_IMPORT` walker), `GetOpenShimIniPath`/`StringIsTruthy`
  (dx11_enhanced_fxaa.cpp:84-125, dx11_scene_depth.cpp:147-183) instead of `TryGetUserConfigString`,
  `ResolveOgreExport`/`ResolveOgreMainProc`/`Resolve` (ogre_render_profile.cpp:667,
  ogre_shader_cache.cpp:249, ogre_enhanced_light_selection.cpp:127) instead of
  `OgreRuntime::ResolveExport`.

## Performance notes

- `handleSchemeNotFound` and `_populateLightList` are the two genuinely hot Ogre callbacks in scope;
  see the first two findings. Everything else in `ogre_render_profile.cpp` runs at ~1 Hz (the
  settings-reassert loop) or once.
- `ApplyFxaa` (dx11_enhanced_fxaa.cpp:888-1043) per frame: `GetDevice` + `GetBuffer` + `GetDesc`,
  a fresh `CreateRenderTargetView` on the backbuffer (963), and `SavedContextState` which performs ~20
  `*Get*` calls (each AddRef) and restores them, with five 256-entry class-instance arrays (5 KB) on the
  stack. Caching the RTV per backbuffer pointer and releasing it on size/format change would remove one
  allocation per frame; the RAII save/restore is the correct price for coexisting with Ogre's state.
- `Field::Advance` (fog_wake.cpp:106-111) performs a full semi-Lagrangian resample (65 536 bilinear
  `Sample` calls in double precision) on every 30 Hz tick, but wind is hardwired to zero
  (fog_wake_feature.cpp:142). A `shiftX == 0 && shiftZ == 0` fast path that multiplies by `decay`
  would be roughly an order of magnitude cheaper; Linux-verifiable in `fog_wake_tests`.
- `ProbeEnhancedResourcesAt` (directory scans over the game root plus every content-root candidate)
  runs twice: at startup under `s_stateLock` (ogre_render_profile.cpp:514, 2901) and again on the render
  thread from the first `setMaterialScheme` call (1645). Caching the resolved directory from the first
  probe removes the render-thread filesystem walk; also consider validating outside the lock so EXU's
  bridge getters cannot block on disk I/O during startup.
- `ComputeShaderSourceFingerprint` (ogre_shader_cache.cpp:159-219) walks up to 50 000 files under
  `g_Mutex` inside the `.program` open hook; it is reported under `[UIPERF][SHADER]` and bounded, so
  this is informational.
- `SelectSourceTechniqueIndex` (dx11_legacy_material_compat.cpp:629,641,667) calls `ToLowerCopy` per
  candidate per pass (three passes), allocating; lowering once into the candidate would remove it.
- `HookOMSetRenderTargets` (dx11_scene_depth.cpp:620-654) takes `g_DataMutex` on every bind; it is
  opt-in diagnostic and bounded, acceptable.

## Positive notes (things done well that later work should keep doing)

- SEH discipline: every guarded core is `noinline`, holds only POD, and all `std::string`/export
  resolution happens in the wrapper (ogre_render_profile.cpp:660-665, 2618-2723; ogre_shader_cache.cpp:
  258-407; sun_flash.cpp:66-135, 175-191; ogre_enhanced_light_selection.cpp:153-315).
- Scheme takeover: all three sites verified for `FF 15 <exact IAT displacement>` before any write, all
  pages made writable before the first byte changes, and the IAT slot itself is left pristine so the
  original is always reachable (2456-2560).
- Truthful ABI: `RequestRenderProfile` never infers "applied" from viewport existence; the resolver and
  `SupportsRenderProfile` share `ProfileRequirementsMet` so they cannot disagree (render_profile.h:157).
- Fail-closed gating: `s_detectedDx11Atomic` + resources-valid atomics gate the compat ladder
  (1997-2025); light selection requires the D3D11 module, PE timestamp/size and three code anchors
  (153-196) and preserves Ogre's list on any candidate read failure (527-528); the sun-flash patch
  verifies opcode + rel32 target before the payload is built and only ever tail-jumps through a pointer
  set by that verification.
- COM hygiene in FXAA: `SavedContextState` releases every captured reference exactly once, the
  backbuffer RTV and texture are released before `Present` (DXGI `ResizeBuffers` requirement), and
  device/context pins are dropped on device change and at shutdown.
- Ogre `SharedPtr<DataStream>` ownership in the shader cache is passed by value exactly once and never
  touched again, with the ABI evidence (`ret 8`) written down (ogre_shader_cache.cpp:25-31).
- Enhanced resource bootstrap is a compare-exchange state machine that is final on failure, so it can
  never repeat per draw (1620-1702), and it proves the payload parsed by resolving one canonical
  program name rather than trusting `initialiseResourceGroup`.
- Pure policy split: resolver, resource validation, compat ladder, bootstrap state, light ranking,
  fog-wake field/runtime, scene-depth registry and sun-flash maths are all Win32/Ogre-free and covered
  by host tests (`tests/CMakeLists.txt`), which is what made most of this audit checkable without a
  game.
