<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Updater, update manifest, assets, SDK v2/bridge/thunks, events, misc gameplay patches

## Summary

Overall this slice is in good shape: the manifest parser is a strict shape parser with fixed
source/destination names (no path traversal possible), payload hashes are streamed, SEH frames
are POD-only, the event ring is allocation-free, `bzn_analysis.h` is carefully bounded on
untrusted input, and the export surface has a single source of truth plus a drift test.
Top three issues: (1) `OpenShimImpl_SetMusicTrack` calls a hardcoded engine address
`0x00406670` with no identity/build gate at all -- a fail-open violation of the project rule;
(2) the updater's trust chain is "whatever Steam delivers for Workshop item 3686673790": the
manifest hashes are self-attesting, the replacement helper `.exe` is executed with no hash or
signature check, and the downgrade guard trusts an unverified manifest version string; (3) two
per-frame costs on the game thread -- autosave stats `Save\auto.sav` twice every frame during a
mission, and `IsAssetFeatureAvailable` copies ten `std::string`s per chunk-proxy slot creation.
Note: there is no HTTP(S) code in the updater at all; download is delegated to Steam's UGC.

## Findings

### [High][High] Hardcoded engine address called with no build/identity gate — src/patches/openshim_sdk_provider.cpp:377
```cpp
static StartMusicFn pStartMusic = reinterpret_cast<StartMusicFn>(0x00406670);
...
__try { pStartMusic(0, index); return TRUE; }
```
An exported SDK entry (`OpenShimSetMusicTrack`, callable by any companion DLL) jumps to a raw
absolute address that is not in `scripts/patches.json` (grep for `406670` finds only this line),
is not checked with `IsCompatibleGameVersion()`/`IsPatchingComplete()`, and is not validated as
executable. On any other build the call lands on arbitrary bytes; `__except` only helps if that
happens to fault. This fails open, contrary to AGENTS.md ("Native hooks must fail closed").
Fix: add a named resolve (e.g. `"Music::StartMusic"`) to `scripts/patches.json`, resolve it via
`HookEngine::ResolveNamedAddress` once, require `IsCompatibleGameVersion() && IsPatchingComplete()`
and an executable-page check, and return `FALSE` otherwise. The catalog entry can be covered by
`patch_registration_tests`/`resolve_table_tests` on Linux; the call itself is Windows-only.

### [Medium][High] Updater trust chain: unsigned payloads, unverified helper executable — src/patches/openshim_updater.cpp:563-570, 627
```cpp
const std::filesystem::path helper = itemDirectory / L"bzfile_replace_helper.exe";
...
if (!LaunchHiddenProcess(helper, arguments, error))
```
The manifest, `winmm.dll`, `net.ini`, `patches.json` payload and the helper `.exe` all come from
the same Workshop item, so the SHA-256 values in the manifest only detect transfer corruption;
they do not establish authenticity. Worse, the helper is launched from the Workshop directory
with no hash at all (it is not in the manifest) and no Authenticode check, and it is the process
that replaces `winmm.dll`. Anyone who can publish to item 3686673790 (compromised uploader
account, Steam-side tampering) gets arbitrary code execution in every Steam install with a
single click on "Check for updates". Fix (minimal): add `helper = { source, sha256, size }` to
the format-2 manifest and validate it like the other payloads; (proper) verify an Authenticode
signature with `WinVerifyTrust` on `winmm.dll` and the helper, or embed an Ed25519 public key in
the shim and require a detached signature over the manifest text. Windows-only to verify.

### [Medium][High] Downgrade guard is bypassable and not fail-closed — src/patches/openshim_updater.cpp:685-692, 433-448
```cpp
if (ReadFileVersion(payloads[0].destination, installedVersion) &&
    CompareVersions(installedVersion, manifest.version) > 0)
```
`CompareVersions` returns 0 when either string fails to parse, and a failed `ReadFileVersion`
skips the check entirely; both paths fall through to staging. `manifest.version` is a free-form
string that is never compared with the version resource of the actual `winmm.dll` payload, so a
manifest that says `"99.0.0.0"` stages an arbitrarily old DLL. Fix: after `ValidateX86Dll`,
call `ReadFileVersion(payloads[0].source, payloadVersion)` and require it to equal
`manifest.version`; treat any parse failure in `CompareVersions` as "refuse to stage" and
surface it in the status message. `CompareVersions`/`ParseVersion` could move to a header and be
covered on Linux; the resource read is Windows-only.

### [Medium][Med] Validation worker has no C++ exception barrier — src/patches/openshim_updater.cpp:640-720
```cpp
unsigned __stdcall ValidationThreadProc(void*)
{
    std::filesystem::path itemDirectory;
```
The worker runs `std::regex` over a 64 KB untrusted manifest, builds `std::filesystem::path`s,
concatenates strings and copies files. Any `std::bad_alloc`, `std::regex_error`
(MSVC's regex is recursive and can throw `error_stack`/`error_complexity` on long inputs), or
`filesystem_error` (`operator/`, `path(std::wstring)`) escapes the thread and terminates the
game. Fix: wrap the body in `try { ... } catch (...) { SetState(Failed, "Update check failed:
internal error."); }`. Windows-only; `ParseOpenShimUpdateManifest` itself could get a
long-input/fuzz case in `tests/openshim_update_manifest_tests.cpp` on Linux.

### [Medium][High] Autosave stats the save file twice every frame — src/patches/autosave.cpp:1058
```cpp
if (ObserveExternalAutoSave(now) || now < g_nextSaveTick)
    return;
```
`ObserveExternalAutoSave` is evaluated first, so on every `updateRenderQueue` call during a live
mission it performs `std::filesystem::exists` and `last_write_time` on `Save\auto.sav` (two
path-resolving NTFS syscalls per frame, ~10-50 us each). The result is only needed when the
deadline is reached. Fix: `if (now < g_nextSaveTick || ObserveExternalAutoSave(now)) return;`
(identical semantics because the write time is compared against the last observation, not
against "now"), or throttle the observation to once per second. Windows-only (main-thread hook).

### [Medium][High] SDK writes full struct into caller buffer regardless of caller's structSize — src/engine/openshim_sdk_v2.cpp:73, 382
```cpp
*outEvent = g_EventQueue[g_EventQueueHead];
...
*outSnapshot = snapshot;
```
`OpenShimEvent` and `OpenShimDeveloperSnapshot` carry `structSize`, and the header/doc promise
that "future SDK revisions can append fields" to the snapshot. Appending anything while
keeping this copy would overflow the buffer of every companion built against the older header,
because `pollEvent`/`captureDeveloperSnapshot` never read the caller's `structSize`. There is
also no `static_assert` pinning the ABI sizes (expected 120 and 96 bytes on x86). Fix: read
`outEvent->structSize`, refuse (`return 0`) if it is smaller than the v2 minimum, and
`memcpy(out, &src, min(structSize, sizeof(src)))`; add
`static_assert(sizeof(OpenShimEvent) == 120)` / `== 96` beside the structs. The static_asserts
are verifiable on Linux (the header compiles in `openshim_sdk_thunk_tests`).

### [Medium][Med] ODF item hooks unbalance the engine's Use/Unlock pairs — src/patches/odf_item_hooks.cpp:316-320, 408-428
```cpp
if (it != g_OdfItems.end() && it->second.refcount > 0)
{
    ++it->second.refcount;
    return it->second.changed ? it->second.patchedBuf : it->second.originalPtr;
}
```
A second `UseItem(name)` while our record is live is answered from the cache without calling
the engine's `UseItem`, but every `UnlockItem(name)` (line 413) is forwarded to the engine. The
engine therefore sees one Use and N Unlocks. If the item store is lock-counted (the Use/Unlock
naming strongly suggests it is), its count underflows and it may release the buffer while our
record still hands out `originalPtr` for unchanged files (use-after-free) or the following
Unlock corrupts a count. Fix: forward every `UseItem` to the engine (it keeps its own count) and
only cache the patched buffer; keep our refcount for the buffer lifetime. Windows-only.

### [Medium][Med] File-I/O provider callbacks can throw C++ exceptions into game CreateFile callers — src/patches/file_io_hooks.cpp:887-954; src/engine/bootstrap_file_io.cpp:150-168
```cpp
static const wchar_t* __cdecl ProviderRoutePathW(...)
{
    std::wstring routed = RouteTerrainAtlasPath(path, desiredAccess, creationDisposition);
```
The bootstrap seam calls `provider->routePathW` / `provider->onOpenedW` with no `try`/`__try`.
`RouteTerrainAtlasPath` builds `std::filesystem::path`, `std::wstring`, an `unordered_map`
entry and an `ifstream`; `ProviderOnOpenedW` builds paths and calls `IsEditorSourcePath`
(`lexically_normal` + transform). A `bad_alloc` (or, on a code-page-incompatible path,
`filesystem_error` from `path::string()`-style conversions) unwinds straight into the engine's
`CreateFileW` call. In addition `g_InAtlasRepair` (file_io_hooks.cpp:193/248) is set and
cleared by hand, so an exception leaves that thread with atlas repair permanently disabled.
Fix: wrap the four provider bodies and `Hooked_CloseHandle`'s normalization in
`try { } catch (...) { return nullptr; }`, and make `g_InAtlasRepair` a scoped guard like
`ScopedNormalizationGuard`. Windows-only.

### [Medium][High] Absolute engine addresses hardcoded in feature code — several files
- src/patches/autosave.cpp:72-81 (`kIsNetGameAddr = 0x00917F7B`, `kUserObjectAddr`,
  `kEditModeAddr`, `kQueuedLoadNameBufferAddr`, `kWorldUpdateRenderQueueVtableSlot = 0x00892728`)
  plus a private 54-byte signature scan for `SaveGame` (lines 97-102, 407-467).
- src/patches/game_state.cpp:10-16 (`0x00945549`, `0x0094557C`, `0x009454EC`, `0x00918320..28`).
- src/patches/redux_compatibility.cpp:163-164, 348-349, 359 (`moduleBase + 0x00218E38`,
  `+0x00386E5F`, IAT slots `+0x00469544`/`+0x00469484`, `+0x0041DF00`).
- src/patches/pond_class_label.cpp:29-31 (`0x0047B6C0`, `0x0047E9C0`, `0x005896C0`); the
  identity check for `ParameterDB::GetInt` is only the three bytes `55 8B EC` (lines 253-264),
  which matches almost every function in the image.
```cpp
constexpr uintptr_t kParameterDbGetIntAddress = 0x005896C0u;
static const uint8_t parameterDbPrologue[] = { 0x55, 0x8B, 0xEC };
```
AGENTS.md: "Put build-specific sites and addresses in scripts/patches.json; do not scatter raw
addresses through feature code." `scripts/patches.json` only carries `0x00892728` as a fallback.
Autosave and game_state are gated by `IsCompatibleGameVersion()` (openshim_plugin.cpp:129) and
redux_compatibility by an executable SHA-256, so these are rule violations rather than
fail-open bugs; the pond `tuggable` trio is the weakest (prologue-only check, on the deferred
retry path). Fix: add named resolves (`Game::IsNetGame`, `Game::UserObject`, `Ui::WrapperActive`,
`ParameterDB::GetInt`, `BuildingClass::String16`, `Building::Building`, ...) with proper
signatures to `scripts/patches.json` and resolve through `HookEngine::ResolveNamedAddress`.
Catalog entries are verifiable on Linux via `patch_registration_tests`.

### [Low][High] `IsAssetFeatureAvailable` copies ten strings per call on a burst path — src/engine/openshim_assets.cpp:917-919; src/patches/bzr_hooks.cpp:6219
```cpp
const AssetCapabilities caps = GetAssetCapabilities();
```
`EnsureChunkMeshProxySlot` calls this for every chunk-proxy slot creation (vehicle destruction
bursts on the game thread). Each call copies the whole `AssetCapabilities` (ten `std::string`s,
`problem` text) under the shared lock. Fix: add a lock-scoped bool reader
(`ReadFeatureFlagsLocked`) that copies only `state`, `manifestDetected`, the two compat bools
and the four feature bools. Verifiable on Linux (`openshim_assets_tests`).

### [Low][High] Assets: wasted probes and always-true condition — src/engine/openshim_assets.cpp:684-687, 459-463
```cpp
std::string chunkP, enhP, terrainP;
ProbeDestructionChunksAt(gameDir, chunkP);
ProbeEnhancedResourcesAt(gameDir, enhP);
ProbeTerrainHdAt(gameDir, configuredTerrainHdManifest, terrainP);
```
In the malformed-manifest branch all three directory scans run and every output is discarded.
At 459-463 `FileExistsNonEmpty(p1) || FileExistsNonEmpty(p2) || std::filesystem::exists(manifest, ec)`
is always true because `is_regular_file(manifest)` was just checked, making the two
`FileExistsNonEmpty` calls dead. Fix: delete the three probes (or log their problems) and
reduce 459-463 to `return true;`. Linux-verifiable.

### [Low][High] SDK document drifted from the header — Docs/OPENSHIM_SDK_V2.md:24-25, 47-51, 61-67, 73-81
```cpp
api->structSize < sizeof(BZROpenShim::OpenShimApiV2))      // line 25
offsetof(BZROpenShim::OpenShimApiV2, getDeveloperSnapshot) // line 48
```
Line 25 tells consumers to reject a table smaller than `sizeof`, which lines 41-44 then say
not to do; `getDeveloperSnapshot` does not exist (`captureDeveloperSnapshot` does);
`OPENSHIM_CAP_NATIVE_UI`, `getNativeUiApi`, `NativeUiAction` and the five `Sim*` events are
missing. Since companions are written from this document, the wrong field name and the
contradictory size check are worth fixing. Docs-only.

### [Low][High] Stale ownership comments in the provider — src/patches/openshim_sdk_provider.cpp:9, 509-511, 601-604
```cpp
// Transitional: the provider is still linked into winmm.dll, so the
// bootstrap installs it directly. Once this file ships in plugins/openshim.dll, delete this
```
The file is compiled only into `Plugin_OpenShim.vcxproj:174` (not `BZROpenShim.vcxproj`), and
`InstallBuiltIn` is called from the plugin (`openshim_plugin.cpp:320`) through the bootstrap
API. "52 bodies" is also no longer accurate. Misleading for anyone reasoning about which module
runs this code. Fix: rewrite the three comments.

### [Low][High] hudbridge logs at Info on every export call — src/patches/openshim_sdk_provider.cpp:299-372
```cpp
LogHudBridgeCall("OpenShimGetHudSpriteRect", name);
```
`Get/Set/Restore*HudSprite*` each emit one or two Info lines per call. A companion that
queries a sprite rect per frame writes ~120 log lines/s. Fix: log at Debug, or once per
(function, sprite) until the result changes.

### [Low][Med] Updater launches the helper with `CREATE_BREAKAWAY_FROM_JOB` — src/patches/openshim_updater.cpp:495-497
```cpp
CREATE_NO_WINDOW | DETACHED_PROCESS | CREATE_BREAKAWAY_FROM_JOB,
```
If the game runs inside a job object without `JOB_OBJECT_LIMIT_BREAKAWAY_OK` (some launchers,
Proton/Wine wrappers, test harnesses), `CreateProcessW` fails with `ERROR_ACCESS_DENIED` and the
update is reported as failed. Fix: on `ERROR_ACCESS_DENIED`, retry once without the flag.
Windows-only.

### [Low][Med] Staged payload copies are written into the Steam Workshop item directory — src/patches/openshim_updater.cpp:578-583
```cpp
payloads[index].staged = itemDirectory / (L"openshim_suite_" + ... + L".pending." + prefix);
```
Steam owns `steamapps\workshop\content\301650\<id>` and may validate, overwrite or delete it at
any time; staged files that survive a helper failure also pollute the item. Fix: stage under
`gameRoot\openshim\_update\` (created with `create_directories`) and pass those paths to the
helper. Windows-only.

### [Low][High] Autosave shutdown can drop the original world update if another hook chained after it — src/patches/autosave.cpp:868-879
```cpp
InterlockedCompareExchangePointer(slot, g_previousWorldUpdateRenderQueue, hook);
...
g_previousWorldUpdateRenderQueue = nullptr;
```
The CAS result is ignored; if the slot no longer holds our hook (someone hooked after us and
chains to us), our hook stays reachable but `previous` is now null, so
`AutoSaveWorldUpdateRenderQueueHook` (line 781-787) skips the engine's `updateRenderQueue`.
Fix: only clear `g_previousWorldUpdateRenderQueue`/`g_hookInstalled` when the CAS returned
`hook`; otherwise log and leave the chain intact. Windows-only.

### [Low][Med] `ReadRegistryString` mis-sizes odd byte counts — src/patches/openshim_updater.cpp:203-218
```cpp
std::wstring value(bytes / sizeof(wchar_t), L'\0');
```
If `RegGetValueW` reports an odd `bytes`, the buffer is one byte short and the second call
returns `ERROR_MORE_DATA`, so the Steam path is silently dropped. Fix: allocate
`(bytes + 1) / sizeof(wchar_t)`. Windows-only.

### [Low][Med] Per-open path construction before the feature gate — src/patches/file_io_hooks.cpp:920-922, 943-945
```cpp
const std::wstring routedPath = routed ? routed : L"";
if (IsEditorSourcePath(routedPath))
    RememberOpenedBznSource(handle, desiredAccess, creationDisposition);
```
`IsEditorSourcePath` builds a `std::filesystem::path`, `extension()`, `lexically_normal()` and a
lower-cased `wstring` for every file the game opens, even though `RememberOpenedBznSource`
immediately returns unless `BZR_BZN_SAVE_SOURCE=1`. Fix: test `BznSourceSaveEnabled()` first,
and use a suffix test like `PathEndsWithBzn` before constructing paths. Windows-only.

### [Low][High] `Hooked_CloseHandle` locks a mutex on every handle close in the process — src/patches/file_io_hooks.cpp:808-835, 688-696
```cpp
const bool tracked = !g_InTrnNormalization && PopTrackedTrnWriteHandle(object, record);
```
Every `CloseHandle` from the exe and both CRTs (files, events, threads, mutexes) takes
`g_TrnWriteMutex` to look up an almost always empty map. Fix: keep an
`std::atomic<size_t> g_TrackedCount` and return early when it is zero.

### [Low][Low] Minor benign races
- src/engine/openshim_sdk_thunks.cpp:24 `static bool s_logged` is written from any thread
  without synchronization (worst case a duplicate warning).
- src/patches/openshim_events.cpp:109 reads `g_Dropped` for the log line after the lock is
  released (a torn/stale count in a diagnostic line).
Fix: `std::atomic<bool>` / capture `g_Dropped` inside the lock. Low value; listed for completeness.

## Dead or unused code (list with evidence)

- `FormatAssetStatusForLog` (src/engine/openshim_assets.cpp:1060) -- no callers in `src/`,
  `include/` or `tests/` (grep `FormatAssetStatusForLog`).
- `ShouldEnableAssetFeature` (src/engine/openshim_assets.cpp:958) -- only referenced by
  `tests/openshim_assets_tests.cpp`; no runtime caller.
- `ParseAssetManifestContent` (src/engine/openshim_assets.cpp:360-364): the empty
  `if (!haveCompat && haveVersionAlias) { }` block and the `!haveFormat ||` half of the next
  condition are dead (`haveFormat` is forced true at 356).
- src/engine/openshim_assets.cpp:461: the two `FileExistsNonEmpty` calls are dead (see finding).
- `AssetCapabilities::expectedVersion` / `kAssetPackExpectedVersionAlt` exist only to feed the
  legacy `"1"`/`"1.0"` alias comparisons; harmless, but the four "version" fields
  (`installedVersion`, `versionCompatible`, `expectedVersion` + Format/Compatibility pairs) are
  three ways of saying the same thing and should collapse once the UI stops reading the alias.
- `OdfCompat::ProcessOdfText` `flushPayloadCheck(int endLine)` (src/patches/odf_compat.cpp:246)
  takes a parameter it immediately `(void)`s.
- `RuntimePayload::backup` is filled (openshim_updater.cpp:663-671) and forwarded to the helper,
  but never used by the shim itself; fine, just noting the helper owns that contract.

## Performance notes

- First `GetAssetCapabilities()` performs the full addon/mods/packaged_mods/Workshop directory
  enumeration under the unique lock on whichever thread asks first; `RefreshAssetCapabilities`
  is called at hook install (bzr_hooks.cpp:35049) so this normally happens off the frame, but
  any earlier caller would pay it inline.
- `openshim_updater.cpp` `FindSteamLibraries` re-reads every `libraryfolders.vdf` on each
  validation run; cheap and off-thread, acceptable.
- `bzn_analysis.h` allocates a `std::string` copy per numeric field (`ParseDecimalLong`,
  `IsNonFiniteNumber`); a 16 MB mission produces hundreds of thousands of small allocations on
  the thread that opened the file. It is a one-shot diagnostic capped at 64 reports, so
  acceptable, but `strtol`/`strtod` on a `std::string_view` via a stack buffer would remove it.
- `WaitForSettledCompatibilityBytes` spins up to 30 s (3000 x 10 ms) on the patch thread for
  Steam; intended.
- `ApplyTrnSaveNormalizeHooks` waits up to 5 s per CRT module (200 x 25 ms); intended.
- `redux_compatibility.cpp` `ComputeSha256` (BCrypt, uppercase hex) duplicates
  `openshim_updater.cpp` `ComputeSha256` (CryptoAPI, lowercase hex); one shared helper would
  remove ~100 lines and one of two hex conventions.

## Positive notes (things done well that later work should keep doing)

- `ParseOpenShimUpdateManifest` is a non-evaluating shape parser that pins `source`/`destination`
  to three literal names, so a manifest cannot direct a write outside `winmm.dll`, `net.ini`,
  `scripts\patches.json`; it also cross-checks the top-level hash/size/version against the
  winmm payload.
- Updater SEH frames (`ResolveWorkshopMethods`, `InvokeWorkshopEnsure`) hold only PODs, validate
  the manager vtable slots with `VirtualQuery` before calling, and the helper receives the
  expected SHA-256 per payload so it can re-verify after the copy.
- `Workshop::GetManager` is a named resolve, and `BeginOpenShimUpdateCheck` refuses on
  unsupported builds and non-Steam distributions.
- `openshim_sdk_bridge`/`openshim_sdk_thunks`: append-only provider table guarded by
  `structSize`, one-time GetProcAddress, no LoadLibrary on the export path, one-shot unavailable
  logging, and `openshim_sdk_exports.inc` as the single source of truth with a text drift test.
- `openshim_events.cpp`: fixed-capacity ring, single SRW lock scoped to a struct copy, drop-newest
  policy explained, sinks invoked with no lock held and batch copied out first, re-entrancy guard.
- `bzn_analysis.h`: every index is bounds-checked, counts are sanity-capped by line count,
  `long` overflow handled via `ERANGE`, pointers into `result.objects` are only used until the
  next push; `bzn_load_trace.cpp` caps file size (16 MB), reports (64) and rows (4096), keeps
  C++ objects out of the `__try` frame, and re-enters safely via `thread_local`.
- `odf_item_prologue.h` refuses to relocate anything but the exact known prologue and explains
  why five bytes would break the trampoline; `odf_compat.cpp` preserves bytes and line endings
  exactly and never throws.
- `autosave_gate.h` isolates the decision logic (host-tested), the fault budget stands the
  feature down instead of re-faulting every interval, and `InvokeNativeNormalSaveGame` restores
  the `missionSave` flag on both paths.
- `file_io_hooks.cpp`: `TrackedHandleMatchesRecord` re-verifies handle identity before
  rewriting a file, `WriteBinaryFileAtomic` uses temp + `MoveFileEx`, the tracked-handle map is
  capped, and the editor save dialog confirms every possible overwrite before any write.
- `render_queue_trace.cpp` builds the Ogre listener vtable by hand and documents the
  `__fastcall`-as-`__thiscall` convention rather than trusting header ABI.
