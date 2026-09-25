<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Options UI, native UI, UI performance, INI/config/env, preset migration, CLI parser

Scope read end-to-end: `src/patches/bzr_options_ui.cpp` (7007 lines), `src/engine/native_ui.cpp`,
`src/engine/native_ui_validation.h`, `include/native_ui.h`, `src/engine/ui_decor.cpp` + `include/ui_decor.h`,
`src/patches/ui_performance.cpp` + `include/ui_performance.h`, `src/patches/ui_performance_hooks.cpp` + header,
`src/patches/ui_file_scan_hooks.cpp` + header, `src/patches/editor_view_order.cpp` + header,
`include/scroll_helper.h`, `src/patches/openshim_ini.cpp` + header, `src/patches/openshim_env_config.cpp` + header,
`src/patches/openshim_preset_migration.cpp` + header, `src/patches/cli_multiparam_parser.cpp` + header,
`include/bzr_options_ui.h`, the five listed tests, `openshim.ini`, `openshim.ini.example`, `scripts/run_ini_tests.ps1`,
plus the config accessors in `src/patches/bzr_hooks.cpp:33757-33826` and the callers in `src/engine/patcher.cpp`,
`src/plugin/openshim_plugin.cpp`, `src/dllmain.cpp` that these files depend on.

## Summary

Overall the UI/config layer is in good shape: every inline detour is byte-guarded and fails closed, cached engine widget
pointers are invalidated by dtor hooks or generation/fingerprint checks, file writes go through temp+backup+atomic
replace, and the INI document editor is lossless and unit-tested. The three issues most worth fixing:

1. Preset migration runs on the patch thread with no exception guard and can throw (`std::stoi` on a hand-edited
   `; OpenShimPresetRevision = <huge number>` line, throwing `std::filesystem::exists`), which terminates the game at
   launch on a malformed but user-editable file.
2. `TryMigratePlayerPresetOnStartup` passes the *existing* (bad) file as its own canonical when no payload is found, so
   the "full replacement" path re-writes the bad values and stamps the file as revision 3, permanently skipping the
   surgical fix it was meant to apply (and its last-resort candidate would replace the player file with the 1895-line
   `openshim.ini.example`).
3. The Career-page hooks on `cUI_View::SetActive` / `SetText` / `SetLabel` are process-wide and decide "this is one of
   our widgets" by raw pointer equality against cached pointers that are only cleared from the MainScreen *constructor*
   hook, so after title-screen teardown a recycled heap address can have its activation vetoed or its text blanked.

Secondary themes: engine addresses hard-coded in feature code (with a `ResolveNamedAddress` lookup that can never
succeed because `scripts/patches.json` has no such entries), a per-frame reassert loop on the main menu that is
redundant once the SetActive hook is installed, filesystem probes repeated per widget, and a fair amount of dead
diagnostic API surface in `ui_performance*`.

## Findings

### [Medium][High] Preset migration can throw an unhandled C++ exception on the patch thread — src/patches/openshim_preset_migration.cpp:243

```cpp
            // Ignore trailing spaces / comments after number.
            out = std::stoi(num);
```
`num` is an unbounded digit run taken from a comment line in the user-editable `openshim.ini`. A value that does not
fit an `int` (e.g. `; OpenShimPresetRevision = 99999999999`) makes `std::stoi` throw `std::out_of_range`. The same
function also calls the throwing overloads of `std::filesystem::exists` at :619, :1079, :181, :745 and :991 (only
`remove`/`copy_file` use `error_code`). The caller chain is `RunPatcher` (`src/engine/patcher.cpp:1145`) on
`PatchThreadProc` (`src/plugin/openshim_plugin.cpp:65-90`), which has no `try`/`catch`, so the exception unwinds to
`std::terminate` and the game dies at launch. The header (:135) promises "never truncates or corrupts the source file on
failure", but an abort here is worse than a skipped migration.

Fix: replace `std::stoi` with a bounded parse (reject `num.size() > 9`, or `strtoul` + range check), use the
`error_code` overloads of `exists`, and wrap the body of `TryMigratePlayerPresetOnStartup` in `try { } catch (...) {
log; return Failed; }` so any remaining library exception cannot cross into the patcher.
Verifiable: Windows only (the migration test binary links bcrypt and is built by `scripts/run_ini_tests.ps1`); a test
feeding `; OpenShimPresetRevision = 99999999999999` through `TryParsePresetRevisionFromLines` would cover it.

### [Medium][High] Case A "full replacement" uses the bad file as its own canonical and stamps it current — src/patches/openshim_preset_migration.cpp:1066-1099

```cpp
        std::filesystem::path canonicalPath = existingPath;
        ...
        if (!foundCanonical)
        {
            ...
            canonicalPath = existingPath;
        }
        MigrationResult r = MigratePresetFileIfNeeded(existingPath, canonicalPath);
```
When no `openshim.ini.canonical` / `.new` / `.example` sibling exists (the normal shipped layout), `canonicalPath ==
existingPath`. In `MigratePresetFileIfNeeded` the Case A branch (:668) then calls `LoadCanonicalPresetLines(existingPath)`
which returns the bad file's own 151 lines, so the `canonicalLines.empty()` fallback at :675 (the surgical repair the
comment says will happen) never runs. The code proceeds to :775-842: it re-emits the *bad* values, inserts
`; OpenShimPresetRevision = 3`, backs up and atomically replaces the file, and returns `FullReplaced` without setting
`g_MigrationRequiresSafeAttackReveal`. On the next boot `existingRev == kCurrentPresetRevision` (:654) returns early, so
`AttackRevealPerceivedTeam = 1` / `ScrapPilotHud = Legacy` are frozen in forever. Separately, the third candidate
`modDir / "openshim.ini.example"` (:1075) would, when present, overwrite the player's file with the 1895-line reference
whose defaults the run_ini_tests policy explicitly says differ from the player preset.

Impact is bounded today because Case A only fires on the exact SHA-256 of the never-shipped e81d8b0a payload, but the
framework is documented as the safety net for future bad presets, and this is exactly the branch that would be relied on.

Fix: pass an empty `canonicalPath` when nothing was found (so `LoadCanonicalPresetLines` returns `{}` and the surgical
fallback runs), and drop `openshim.ini.example` from the candidate list (or gate it behind an explicit revision marker
check). Verifiable on Windows with the existing test scaffold: `MigratePresetFileIfNeeded(bad, bad)` currently returns
`FullReplaced` with the values unchanged.

### [Medium][Med-High] Career-page hooks act on stale widget pointers after title-screen teardown — src/patches/bzr_options_ui.cpp:6867-6872, 5925-5933, 6329-6349

```cpp
    void __fastcall CareerUiSetActiveHook(void* thisPtr, void* /*edx*/, uint8_t value)
    {
        const bool isCareerPageWidget = IsCareerUiPageWidget(thisPtr);
        uint8_t out = value;
        if (out && !g_CareerUiPageActive && isCareerPageWidget)
            out = 0;
```
`IsCareerUiPageWidget` (:5742) is pointer equality against `g_CareerUiPlate`, `g_CareerUiTitleLabel`,
`g_CareerUiBackButton` and the 40 row labels. Those pointers are cleared only by `ResetCareerUiState`, whose callers are
`TickCareerUi` (:6445, :6489) and two fault handlers; `TickCareerUi` runs only from `MainScreenCtorHook` (:6938). When
Redux destroys `cUI_MainScreen` (the singleton is nulled by the dtor, per the comment at :5254-5256), 43 dangling
pointers survive for the whole mission and `CareerUiSetActiveHook` remains installed process-wide (0x007D3310). Any
cUI widget later allocated at one of those recycled addresses (in-mission screens, the pause/esc menu, the lobby) has
every `SetActive(1)` silently rewritten to `SetActive(0)`. If the page was open when the screen was torn down,
`g_CareerUiPageActive` stays `true` and `IsCareerUiBlankedView` (:5925) makes `CareerUiSetTooltipHook` /
`CareerUiSetButtonLabelHook` (:6905-6918) write `""` over the requested text for any view at a recycled address in
`g_CareerUiBlankedText`. `ReassertCareerUiHiddenState` already recognises the hazard for its own path (:6168-6192) but the
veto in the SetActive hook runs *before* any liveness check. The file's own rule at :6329-6332 ("a retained pointer into a
destroyed tree is the documented way to turn this kind of injection into a crash") is not honoured for the dtor.

Fix (smallest): in `CareerUiSetActiveHook`, `IsCareerUiBlankedView` and `RecordCareerUiText`, require
`ReadMainScreenSingleton() == g_CareerUiMainScreen && g_CareerUiMainScreen != nullptr` before a pointer match counts, and
call `ResetCareerUiState()` when that test fails. Better: detour the MainScreen inner dtor at 0x0078ECA0 (the bytes are
already verified by `native_ui.cpp:1328-1332`) and reset there. Windows only.

### [Medium][High] Engine addresses hard-coded in feature code; `ResolveNamedAddress` fallbacks can never resolve — src/patches/ui_performance_hooks.cpp:2007-2012

```cpp
        uint32_t reqAddr = HookEngine::ResolveNamedAddress("ShellRequest");
        if (!reqAddr) reqAddr = 0x007C7930;
```
`scripts/patches.json` has no `ShellRequest`, `ShellTransition` or `ShellBack` entry (its `resolves` list contains
`GameObjectClass::Build`, `BuildingClass::BuildClass`, ... only), so every enabled run logs three
`[RESOLVE] name="..." has no entry in scripts/patches.json` warnings (`src/engine/hook_engine.cpp:387-391`) and uses the
literals. The same file also embeds `0x0076A030/0x0076A240/0x0078E670/0x0079EA90/0x0078E8C0/0x007A0F80` (:1181-1216),
`0x0076A430/0x00789C20` (:1845-1850), the Modable setter table (:1586-1591), `0x0094551C/0x0089E178/0x008A0B94/0x008A0470/
0x00918320` (:781-795, :859, :912-913), and literal fallbacks `0x007C79A0` (:891) and `0x007C7930` (:1928).
`bzr_options_ui.cpp:120-188, 2054-2057, 5257, 5375-5376, 5400`, `native_ui.cpp:32-37`, `editor_view_order.cpp:72-83` and
`cli_multiparam_parser.cpp:108-147` do the same. AGENTS.md: "Put build-specific sites and addresses in
`scripts/patches.json`; do not scatter raw addresses through feature code." All of these are behind exact byte guards so
they fail closed, and the two DllMain-time fixes document why they cannot use the catalog; the rest could.

Fix: add named entries (with patterns) for at least the three shell functions so the lookup is real, remove the literal
fallbacks (a missing entry should disable the profiler, not silently use a literal), and move the options/main-screen
constructor and dtor sites into the catalog. Windows only (needs the exe to validate patterns).

### [Low][High] Placeholder path `"<GAME_ROOT>"` left in production code — src/patches/bzr_options_ui.cpp:833

```cpp
            const std::filesystem::path gogInstall("<GAME_ROOT>");
            if (hasInputMap(gogInstall))
                return gogInstall;
```
`<` and `>` are invalid path characters on Windows, so `exists("<GAME_ROOT>/input.map", ec)` always fails; the branch
is dead and reads like a redacted hard-coded install path. Remove it (the module directory and the Documents install are
the two real candidates). Linux-verifiable only as a grep.

### [Low][High] UTF-8 em dashes in engine-rendered strings — src/patches/bzr_options_ui.cpp:3407, 3689-3695, 3912-3921

```cpp
                        reason = "Unavailable — Enhanced renderer resources not detected";
```
Ten occurrences. The cUI text path is byte-per-glyph (`ReadUiViewName` at :5020 already treats bytes outside
0x20..0x7E as `?`), so these render as three garbage glyphs. Replace with `-`. Windows only to see it.

### [Low][Med] Section-name whitespace handled differently by the lossless writer and the migration reader — src/patches/openshim_ini.cpp:118

```cpp
            if (_stricmp(headerName.c_str(), section) == 0)
```
`IniLineIsSectionHeader` returns the raw text between the brackets (the test at `tests/ini_writer_tests.cpp:434` pins
`" Spaced "`), and the writer compares it untrimmed, while the migration code trims before comparing
(`openshim_preset_migration.cpp:701, :907`). A player file with `[ General ]` is therefore recognised by migration's value
extraction but the settings page appends a second `[General]` section at EOF, and from then on the Win32 profile reader
and the writer disagree about which line is live. Fix: trim inside `IniLineIsSectionHeader` (or in the compare) and add a
test. Linux: `openshim_ini.cpp` is not in `tests/CMakeLists.txt` and uses `_stricmp/_strnicmp`; swapping those for a
portable helper would let `ini_writer_tests` join the Linux CTest lane.

### [Low][High] String INI values silently truncated at 127 bytes — src/patches/bzr_hooks.cpp:33790-33792

```cpp
        char buf[128] = {};
        GetPrivateProfileStringA(section, key, kUnsetSentinel, buf,
            static_cast<DWORD>(sizeof(buf)), path.string().c_str());
```
`TryGetUserConfigString` is the accessor behind every `[Network] Nickname`, `StockFactionSet`, colour/enum and path-like
key, while the lossless writer accepts any length. `GetPrivateProfileStringA` truncates without error, so a long value is
read back as a different (truncated) value. `openshim_env_config.cpp:34` uses 1024 for the same file. Fix: use a 1024-byte
buffer (or loop on `len == size-1`). Windows only.

### [Low][High] `version.dll` delay-load resolved inside DllMain — src/patches/cli_multiparam_parser.cpp:202-211

```cpp
            const DWORD size = GetFileVersionInfoSizeA(path, &handle);
            ...
            if (!GetFileVersionInfoA(path, 0, size, s_versionBuffer))
```
`ApplyCliMultiParameterOptionFix` is called from `DLL_PROCESS_ATTACH` (`src/dllmain.cpp:171`) and `version.dll` is in
`DelayLoadDLLs` (`Plugin_OpenShim.vcxproj:83,112`, `BZROpenShim.vcxproj:84,114`), so the first call runs `LoadLibrary`
under the loader lock. It works today (same-thread re-entrancy), but it is the pattern the loader documentation forbids
and the file's own comment (:154-157) shows the author was already avoiding heap work here. Fix: take `version.dll` out of
the delay-load list for the winmm shim (it is tiny and imports only kernel32/ntdll), or read `VS_FIXEDFILEINFO` from the
already-mapped resource directory with `FindResource`/`LoadResource`. Windows only.

### [Low][Med] `g_TransitionActive` read without the mutex — src/patches/ui_performance.cpp:627, 648, 681

```cpp
        if (g_TransitionActive)
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
```
Written under `g_Mutex` at :520, :568, :795, :830 and read unlocked from the Ogre/scan record paths, which the file's own
comments say can run on a loader thread. Formally a data race; make it `std::atomic<bool>` (the file already uses atomics
for the enable flags). Windows only.

### [Low][High] `ScopedTransition` dtor resets the thread's phase depth — src/patches/ui_performance.cpp:580

```cpp
        t_state.depth = 0;
```
Any `ScopedPhase` still alive on that thread would then log at the wrong depth and its own dtor's `--depth` would be
skipped by the `> 0` guard. Harmless only because `ScopedTransition` has no users (see dead code). Either delete the
class or drop this line.

### [Low][Med] `IsOnForegroundGameUiThread` refuses the native UI API whenever the game is not the foreground window — src/engine/native_ui.cpp:133-143

```cpp
        HWND foreground = GetForegroundWindow();
        if (!foreground)
            return false;
```
Every API entry (`ApiCreateSurface`, `ApiAddLabel`, `ApiSetText`, ...) requires the foreground window to belong to this
process *and* the calling thread. An SDK consumer calling from the correct UI thread while alt-tabbed, or under a Wine/
Proton window manager that reports a different foreground window, gets `OPENSHIM_UI_INVALID_HANDLE`/0 with no log. The
records already carry `ownerThreadId` and `g_UiThreadId`; compare against the thread that owns the game HWND
(`GetWindowThreadProcessId` on the captured window) instead. Windows only.

### [Low][High] `OPENSHIM_CAREER_TRACE` bypasses the INI redirect and is probed on every SetText — src/patches/bzr_options_ui.cpp:5841-5842

```cpp
            if (s_traceBudget > 0 &&
                ::GetEnvironmentVariableW(L"OPENSHIM_CAREER_TRACE", nullptr, 0) != 0)
```
Only `GetEnvironmentVariableA` is redirected by `openshim_env_config.h`, so this flag cannot be set under
`[Environment]` like every other diagnostic, and because the budget only decrements when the variable is set, the PEB
environment scan runs on every `cUI_Text::SetText` call for the life of the process. Use `EnvFlagEnabled` and cache
the answer once. Also undocumented (see INI cross-check below).

### [Low][High] INI documentation gaps (code reads keys the example never mentions)

Cross-checked every `TryGetUserConfig*`, `GetPrivateProfile*`, `TryReadIniValue`/`TryReadMapped*` call and the settings
registry against `openshim.ini.example` (live and commented keys) and `openshim.ini`.

Keys read by code but absent from `openshim.ini.example`:
- `[Diagnostics] ChunkBatchReuse`, `ChunkBatchReuseObserve` — `src/patches/bzr_hooks.cpp:35141-35143`
- `[Diagnostics] HeadlightLightTrace` — `bzr_hooks.cpp:20238`
- `[Diagnostics] PilotFlashlightTrace` — `bzr_hooks.cpp:21173`
- `[Diagnostics] TraceMpAuth`, `TraceMpAuthDW`, `TraceMpAuthSPL` — `bzr_hooks.cpp:26287-26291`
- `[Diagnostics] UiPerformanceAutoMatrix` — `src/patches/ui_performance_hooks.cpp:1982`
- `[NativeUiDiagnostics] MainMenuProbe` — `src/engine/native_ui.cpp:1402` (whole section undocumented)
- Env-only diagnostics not listed in the example's `[Environment]` block: `OPENSHIM_LOG_OPTIONS_TREE`
  (`bzr_options_ui.cpp:5190`), `OPENSHIM_CAREER_TRACE` (`:5842`), `OPENSHIM_UI_PERFORMANCE_AUTOMATRIX`
  (`ui_performance_hooks.cpp:1991`).

Keys in the example that no code reads: none found. Every candidate the first pass flagged (`AutoSave/InitialDelaySeconds`,
`RetrySeconds`, the `TerrainRenderProbe*` and `TerrainProxy*` keys, `TracePilotFPAnimations`, `WalkerCockpitTrace`,
`SceneDepthDiagnostic`, `OwnedObjectReveal`, `UdpPort`, `AiOdfGameplayTuning`, `PilotFlashlight{Bone,Offset,Pitch}`,
`PilotTeamRestore`, `TerrainSemanticFrameCaptureMinCoverage`) is read through a constant-name or multi-line call.

`openshim.ini` vs `openshim.ini.example`: in sync per the `run_ini_tests.ps1` rule (every live example key is present in
the player file; the player file's only extras are the `; OpenShimPresetRevision = 3` marker and a commented pseudo-key at
line 328). Neither file carries a BOM.

Fix: add the eight keys above to the example (all are diagnostics; the [NativeUiDiagnostics] section needs a header) and
route the three env-only flags through `EnvFlagEnabled` so the `[Environment]` escape hatch covers them. Linux-verifiable
with a grep-based test.

## Dead or unused code (list with evidence)

Verified with `grep -rn` across `src/ include/ tests/`; counts are total hits including the definition.
- `include/ui_performance.h` / `ui_performance.cpp`: class `ScopedTransition` (all 15 hits are its own definition),
  `ScopedPhase::Annotate` ×4 and `Dismiss` (0 call sites), `EmitSummary`, `SetStallThresholdMs`, `Flush`, `LogVerbose`,
  `TicksToUs` (each defined+declared only). `LogVerbose`/`BufferOrEmitVerbose`'s whole verbose-buffer mechanism
  (`t_state.verboseBuffer`, `kMaxBufferedLines`) is therefore unreachable except via `Annotate`, which is unused.
- `src/patches/ui_performance_hooks.cpp`: `g_OrigShellRequest/Transition/Back` (:477-479), `g_ShellRequestPatch/Orig`,
  `g_ShellTransitionPatch/Orig` (:482-485), `InstallJmp5` (:492, superseded by `InstallInlineHook`), forward decls
  `OnShellRequestDetour/OnShellTransitionDetour/OnShellBackDetour` (:511-513, never defined), `g_ShellRequestStart`
  (stored at :762/:1046, never read), `g_ModDiscoveryContext`+`OnModDiscovery_*`, and the header API
  `OnOgreLoad/Unload/Destroy/ParseScripts_*`, `OnWorkshopScan_*`, `OnShellRequest`, `OnShellTransitionUpdate`,
  `OnMultiplayerShutdown_*` (2 hits each = declaration + definition, no callers). The comment block at :515-522 describes
  a "polling observer" design that does not exist.
- `include/scroll_helper.h`: `ConsumeSavedScrollDelta` (:844), `SelectHopFix3DeltaFromFrame` (:877), `HopFix2_Helper`
  (:967, all 5 hits inside this header), `SelectHopFix2This` (:1018) — no callers in `trampolines.cpp`/`patcher.cpp`.
  These carry the stale "GetScrollState address appears wrong for Steam" comment (:846-848).
- `src/patches/bzr_options_ui.cpp`: `TrySetUiTexture` (:93, defined, never called — its fallback logic is duplicated
  inline at :1815-1823, :1860, :1885); `kOptionsInputScreenFactoryCallerAddr` (:122) only ever printed in a log (:1486).
- `src/patches/openshim_preset_migration.cpp`: the empty-file hash comparison at :632-640 is a no-op (`if` with an empty
  body); `anyChanged` in the Case A fallback (:691-725) is set but never read; the `if/else` at :145-148 emits `"\r\n"`
  in both arms.
- `src/patches/openshim_env_config.cpp:15` `kUnsetValue` is duplicated as `kUnsetSentinel` in `bzr_hooks.cpp:33789`,
  `cli_multiparam_parser.cpp:242`, `editor_view_order.cpp:137`, `startup_backend_seam.cpp:120`, and the bool-token
  parser (`1/true/on/yes/enabled`) is copy-pasted in at least six places (`env_config.cpp:49-78`, `bzr_hooks.cpp:33806-
  33826`, `ui_performance.cpp:288-296, 313-330`, `ui_performance_hooks.cpp:1984-1992`, `editor_view_order.cpp:144-149`,
  `cli_multiparam_parser.cpp:249-254`, `bzr_options_ui.cpp:3250-3267`). One shared `ParseIniBool` would remove the
  risk of the sets drifting (they already differ: `ui_performance_hooks.cpp:1992` omits `enabled`, `EnvFlagEnabled`
  accepts anything not starting with `0`).

## Performance notes

- **Per-frame reassert on the main menu** — `bzr_options_ui.cpp:6926` calls `ReassertCareerUiHiddenState` from the
  process-wide `cUI_Text::SetText` hook; the comment confirms the shell hits this every frame (MPStatus tooltip). Each call
  does two name compares, a ≤256-entry child scan (:6138-6162) and then 43 engine `SetActive` calls (:6194-6200), each
  of which re-enters `CareerUiSetActiveHook` and its 43-pointer `IsCareerUiPageWidget` scan before reaching Ogre. Once the
  SetActive detour is installed the shell can no longer re-activate these widgets (the hook vetoes it at :6871-6872), so
  the reassert is redundant; gate it on `g_CareerUiSetActiveOriginal == nullptr` or on a "hidden state dirty" flag that
  the SetActive hook sets when it observes an activation attempt.
- **`RecordCareerUiText` per SetText/SetLabel** (:5831-5905): parent read, name compare, 43-pointer scan, 64-record
  linear search, `ReadUiViewName` (≤200-byte copy) and two `_snprintf_s` on every text set process-wide while
  `g_CareerUiTextRecordingArmed` is true — it is armed at :6753 and never disarmed. Add the singleton-liveness early-out
  suggested in the stale-pointer finding; that also removes the string work when no title screen exists.
- **Filesystem probes per widget** — `IsUiTextureFileAvailable` (`bzr_options_ui.cpp:55-91`) does `GetModuleFileNameA`,
  four `std::filesystem::path` constructions and up to four `exists()` calls, and is invoked once or twice per injected
  button/plate/decor piece (:1815, :1821, :1860, :1885). The settings page builds ~45 such widgets, the keybind page
  ~50, so a page construction costs 200-400 stat calls. Cache the answer per texture name (a static array of four
  bools is enough; the loose-file deployment does not change at runtime, and `RefreshAssetCapabilities` is the
  designated refresh point).
- **INI re-reads per refresh** — `RefreshShimSettingsUiControls` calls `GetShimSettingCurrentIndex` (:3500) for each of
  16 rows, each a `GetPrivateProfileStringA` parse of the whole file (:3219), plus `Assets::GetAssetCapabilities()`
  copies (:3392, :3476) per row. `OnShimSettingsRowHovered` triggers a full refresh on every hover-leave (:3878) and the
  file documents that the shell fires every hover slot in bulk when a screen opens (:611-613), so page open can cost
  16 refreshes × 16 file parses. Read the file once into a map per refresh (`ReadTextFileLines` + `IniLineMatchesKey`,
  both already available) or invalidate a cache only on `WriteUserConfigValueLossless`.
- **`FitUiTextToWidth`** (:2149-2173) pops one character per iteration and re-measures through the native routine, so a
  long label costs O(n) engine measure calls; a binary search on length, or measuring the ellipsis once and subtracting
  per-char advances, would make it O(log n). Not per-frame.
- **Env-var redirect has no cache** — `OpenShimGetEnvironmentVariableA` (`openshim_env_config.cpp:508-552`) performs
  `GetModuleFileNameA`, two `std::filesystem::path` allocations and one or two `GetPrivateProfileStringA` file parses per
  call. Almost every caller memoises (`patcher.cpp:180-260`, `scroll_helper.h:68-89`, `bzr_hooks.cpp:16656`,
  `file_io_hooks.cpp:448`), but `EnvFlagEnabled` (`bzr_hooks.cpp:33757`) does not, and the redirect is force-included
  into every TU, so any future uncached call in a hot path silently becomes a disk read. Consider a small
  name→value cache with a generation bump on `WriteShimUserConfigValue`.
- **UiPerf when enabled**: `Hooked_PeekMessageA` (`ui_performance_hooks.cpp:176-183`) runs
  `TryInstallDeferredSteamShellHooksOnMainThread` on every PeekMessage; on Steam, until the main screen is live, each
  call is one SEH read plus four `ReadProcessMemory` syscalls (:1147-1154). Rate-limit by tick. `Hooked_FindNextFileW/A`
  copy `it->second.pattern` (`std::wstring`) and rebuild the root string on every enumerated file (`ui_file_scan_hooks.cpp:
  286-287, 321-322`); store the root once in `EnumRecord` at FindFirst time instead. `ScopedPhase` constructs
  `m_category` as a `std::string` and takes a QPC sample before checking `m_active` (:383-391); reorder so the disabled
  path allocates nothing.
- **UiPerf when disabled** is genuinely zero-cost: hooks are not installed (`ui_file_scan_hooks.cpp:445-449`,
  `ui_performance_hooks.cpp:2001-2005`) and the public entry points early-out on one relaxed atomic load.

## Positive notes (things done well that later work should keep doing)

- Every inline detour in scope checks an exact byte prefix (and, for the Steam-deferred profiler hooks, body sentinels
  beyond the overwritten prologue) before writing, and refuses rather than guesses: `bzr_options_ui.cpp:4846-4858,
  6536-6616, 6779-6807`, `native_ui.cpp:1328-1350`, `ui_performance_hooks.cpp:1129-1187`, `editor_view_order.cpp:158-171`,
  `cli_multiparam_parser.cpp:274-283`. The editor fix writes both sites or neither and reverts the first on a second
  failure (:181-190).
- Widget lifetime is treated as untrusted: the options/input screens get inner-dtor hooks that drop every cached child
  pointer (`bzr_options_ui.cpp:4807-4830`), fast restyle paths require `IsLive` *and* the dtor hook (:4090-4095), and the
  native UI SDK proves host identity with baseline child counts, a hierarchy fingerprint and a generation counter
  (`native_ui.cpp:444-529`, `native_ui_validation.h`) with the rules unit-tested on Linux.
- Engine heap reads are SEH-wrapped and bounded (`ReadUiChildCount`, `FindStockOptionsInputButtonByClick`,
  `LogUiTree`, `TryReadStdString`), and the Ogre `std::string` probe validates size/capacity/printable bytes before
  dereferencing.
- File writes are careful: temp sibling + `.openshim.bak` + `ReplaceFileW` → `MoveFileExW` → guarded copy fallback,
  with read-only attributes cleared and restored (`bzr_options_ui.cpp:1067-1178`); migration never truncates the source
  and removes its temp file on every failure path.
- The INI document editor is lossless, section-scoped, alias-aware and covered by focused tests
  (`tests/ini_writer_tests.cpp`); the env-var → INI redirect centralises the legacy flag zoo in one table with clear
  inversion semantics and an `[Environment]` escape hatch.
- Layout geometry is derived from one builder and asserted by `ui_decor_tests` (no overlap, plates never under value
  buttons, masks cover panels), and the hover-slot resolver was fixed to derive from that same builder rather than a
  hand copy (:3818-3826).
- Fail-closed policy carries through configuration: `MigrationRequiresSafeFallbackForAttackReveal` forces the safe value
  for the current boot when the file cannot be repaired, and the DllMain-time fixes read only `.data`/resource bytes
  that SteamStub does not encrypt, logging `.text` corroboration instead of requiring it.
