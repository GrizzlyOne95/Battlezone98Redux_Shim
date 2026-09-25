<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Load chain, lifecycle, logging, crash handling

Scope: `src/dllmain.cpp`, `src/engine/winmm_proxy.cpp` + `src/winmm.def` + `tests/winmm_export_baseline.txt`,
`src/loader/*` + `include/bzloader_*.h`, `src/engine/bzloader_bootstrap.cpp`, `src/plugin/*`,
`src/engine/openshim_bootstrap_api.cpp`, `src/engine/startup_backend_seam.cpp` + `startup_seam_wire.cpp`,
`src/engine/bootstrap_file_io.cpp`, `src/engine/crash_logger.cpp`, `src/engine/shim_log_sink.cpp` +
`shim_log_client.cpp`, `src/engine/game_log_path.cpp`, `include/BZROpenShim.h`, the three vcxproj files and
`Docs/BZLOADER_ARCHITECTURE.md`. Every file was read end to end; every finding below was re-checked against
callers with grep.

## Summary

Overall the load chain is in good shape: the module split is clean, the ABI tables are genuinely append-only
with guarded reads, SEH boundaries wrap every plugin entry point and every raw memory probe, the file-I/O
provider is loaded once per call through an acquire/release atomic, the logger is a single-owner sink behind
an SRW lock, and the crash logger is allocation-free with an interlocked reentrancy guard. The three issues
worth fixing first are:

1. **`DllMain` calls into delay-loaded `version.dll`** (`ApplyCliMultiParameterOptionFix` ->
   `GetFileVersionInfoSizeA`), i.e. a `LoadLibrary` under the loader lock, in direct contradiction of the
   project's own "DllMain must never LoadLibrary" rule.
2. **A failed `BZPlugin_Load` is not transactional**: the file-I/O and SDK provider tables are installed
   before the patch thread is created, and on `_beginthreadex` failure the plugin returns 0 while BZLoader
   then `FreeLibrary`s it, leaving the executable's `CreateFileA/W` IAT entries routing through an unmapped
   module.
3. **The bootstrap's `CreateFileA/W` wrappers can throw C++ exceptions into game code** (`std::filesystem`
   / `std::string` on every open, no `try`/`catch`), and they allocate on every file open the game makes.

## Findings

### [High][High] BZPlugin_Load leaves providers installed after failure; loader then unmaps the module — src/plugin/openshim_plugin.cpp:319-332, src/loader/bzloader.cpp:462-466

```cpp
    BZROpenShim::InstallFileIoProvider();          // pointer into openshim.dll stored in winmm.dll
    BZROpenShim::SdkProvider::InstallBuiltIn();    // same
    BZROpenShim::InitializeOpenShimSdkV2();
    g_PatchThread = _beginthreadex(...);
    if (!g_PatchThread) { ...; BZROpenShim::SetShimLogSink(nullptr); return 0; }
```
and in the host:
```cpp
            if (!loaded) { RejectPlugin(plugin, "BZPlugin_Load failed"); continue; }   // RejectPlugin -> FreeLibrary(plugin.module)
```
The header (`bzloader_plugin.h:186-188`) and the architecture doc both require a failed load to be
transactional because the host will `FreeLibrary` the module. Here only the log sink is undone. The
file-I/O provider (`file_io_hooks.cpp:961`, a static table inside `openshim.dll`) and the SDK provider table
stay installed in `winmm.dll`, `RejectPlugin` unmaps `openshim.dll`, and the very next `CreateFileW` the
game makes jumps through `provider->routePathW` into unmapped memory (`bootstrap_file_io.cpp:250-256`).
The same holds for the `loadRaised` (SEH) branch at `bzloader.cpp:457-461`: a plugin that faulted half-way
through `Load` is by definition not transactional, yet it is freed too.

Fix (two halves, both small):
- Plugin: create the worker with `CREATE_SUSPENDED` *first*, install the providers only after that
  succeeded, then `ResumeThread`. Then the only failure path (`_beginthreadex`) really has installed nothing.
- Host: for `loadRaised` (and arguably any `Load` that returned 0) do not `FreeLibrary`; leak the module,
  exactly as the shutdown path already does for loaded plugins ("workers or trampolines may still reference
  their code"). Alternatively make `BootstrapFileIo::InstallProvider(nullptr)` / `SdkBridge::InstallProvider(nullptr)`
  legal uninstalls (both currently refuse null) and call them on the failure path.

Verifiable: Windows only (needs the real host/plugin lifecycle). The host half is testable in
`BZLoaderHostTest` with a plugin whose `Load` returns 0.

### [High][High] DllMain calls delay-loaded version.dll under the loader lock — src/dllmain.cpp:171, src/patches/cli_multiparam_parser.cpp:202-211, BZROpenShim.vcxproj:84,114

```cpp
        BZROpenShim::ApplyCliMultiParameterOptionFix();      // dllmain.cpp:171, DLL_PROCESS_ATTACH
```
```cpp
            const DWORD size = GetFileVersionInfoSizeA(path, &handle);   // cli_multiparam_parser.cpp:202
            if (!GetFileVersionInfoA(path, 0, size, s_versionBuffer))   // :206
            if (!VerQueryValueA(...))                                    // :211
```
```xml
      <DelayLoadDLLs>version.dll;gdiplus.dll;ws2_32.dll;%(DelayLoadDLLs)</DelayLoadDLLs>   <!-- BZROpenShim.vcxproj:84 -->
```
`version.dll` is delay-loaded in the winmm project, so the first `GetFileVersionInfoSizeA` call goes through
`__delayLoadHelper2` -> `LoadLibraryExA("version.dll")` -> `GetProcAddress`, all inside `DLL_PROCESS_ATTACH`.
This is the exact hazard `Docs/BZLOADER_ARCHITECTURE.md` and the comment at `dllmain.cpp:76` forbid
("DllMain must never LoadLibrary"). It works today because the loader lock is re-entrant on the attaching
thread and `version.dll` has no dependencies of its own, but it is undefined by contract, it runs
`version.dll`'s `DllMain` nested inside ours, and it is the kind of thing Proton/Wine loader changes break.
`ApplyEditorOverheadPlacementOrderFix` (the other pre-main fix) is clean; only the CLI fix does this.

Fix: remove `version.dll` from `DelayLoadDLLs` in **BZROpenShim.vcxproj only** (it is a tiny system DLL,
present on every target incl. Wine; keeping `ws2_32`/`gdiplus` delay-loaded as AGENTS.md requires is
unaffected), or replace the version lookup with the PE `TimeDateStamp`/`SizeOfImage` identity that
`InstallStartupBackendSeamImpl` already reads without any library call, or read `VS_FIXEDFILEINFO` straight
from the mapped resource directory. Verifiable: Windows only (a `dumpbin /imports winmm.dll` check that
`version.dll` is a static import could be added to the Windows lane).

### [Medium][High] CreateFileA/W wrappers can throw C++ exceptions into the game — src/engine/bootstrap_file_io.cpp:158-191, 244, 288

```cpp
            const std::wstring logRouted = RouteGameLogPath(fileName);   // :244, every CreateFileW
            ...
            if (!fileName || !*fileName || !ShouldRouteGameLog(std::filesystem::path(fileName)))   // :160 (A variant)
```
The wrappers sit in the executable's IAT and are entered from arbitrary game code with no C++ handler
between them and the caller. `std::filesystem::path(const char*)` converts through the ANSI code page and
MSVC's implementation throws `std::system_error` on an unconvertible sequence; `std::wstring`/`std::string`
construction, `filename()`, `extension()` and `WideCharToMultiByte` buffers can throw `std::bad_alloc`.
Any of those unwinds straight into `battlezone98redux.exe` frames that never expected an exception from
`CreateFileA`, i.e. a crash with the shim on the stack. The hook engine elsewhere in the repo is careful
about this; this seam is not.

Fix: wrap the routing decision in `try { ... } catch (...) { path = fileName; }` (falling back to the
caller's own name, provider not consulted), or better, drop `std::filesystem` here entirely: "no separator
in the name and ends with `.log` / equals `bzlogger.txt` case-insensitively" is a 20-line scan over the
input with no allocation (see the performance note below, which the same rewrite fixes). Verifiable:
Windows only for the wrapper itself; the pure predicate could be moved into `game_log_path.cpp` and unit
tested on Linux.

### [Medium][High] StartupRendererResult is copied without the lock that writes it — src/engine/startup_backend_seam.cpp:932-940, 212-221, 843-852

```cpp
    bool CopyStartupRendererResult(void* out, uint32_t capacity)
    {   ...
        std::memcpy(out, &src, sizeof(StartupRendererResult));   // :938, no lock
```
`PublishResultLocked` (`:212-221`) writes the seven fields under `s_stateLock` on the game thread inside
`ConfigFile::load`; the plugin's patch thread copies them via the bootstrap table at an unrelated time
(`ogre_render_profile.cpp:2877`). A copy that overlaps the publish can read the old `requestedBackend`/
`transportWritten` with the new `selectionRan = 1`, and the plugin then seeds `s_bootRequest` from a torn
record and classifies the boot as "requested=Auto, transport untouched" while the bootstrap actually wrote
DX11 into `Ogre.cfg`. Diagnostics-only impact, but the whole point of the record is that the runtime does
not re-derive this.

Fix: take `s_stateLock` shared inside `CopyStartupRendererResult` (same TU, lock already exists;
`AcquireSRWLockShared`/`ReleaseSRWLockShared` around the `memcpy`). Verifiable: the copy path is covered by
`startup_backend_seam_tests` (Windows only); the change is mechanical.

### [Medium][Med] The plugin copies the startup record exactly once and assumes the seam already fired — src/patches/ogre_render_profile.cpp:2877-2899 (consumer of the scope's API), src/engine/startup_backend_seam.cpp:833-852

```cpp
        // ... it has already run by the time this executes. Read its published result
        const bool haveStartup = StartupSeam::CopyStartupRendererResult(&startup, sizeof(startup));
        ...
        if (haveStartup && startup.selectionRan != 0) { s_bootRequest.backend = ...; }
```
Nothing orders `InitializeOgreRenderProfiles` (patch thread, after `RunPatcher`) after the game's first
`Ogre.cfg` read (game thread, ~1 s on warm Steam, likely earlier on GOG where the patcher has no SteamStub
wait). `s_bootRequest` is only ever assigned from this copy (`ogre_render_profile.cpp:2897-2898`), so if the
copy happens first the plugin permanently reports `requested=Auto`, `transportWritten=false` and the
outcome classification in `ReportSelectionOutcome` (`:416`) is wrong for that boot. The record already
carries `selectionRan`, so the fix is cheap: have the observation worker (which runs after the renderer is
established, so strictly after `ConfigFile::load`) re-copy when the init-time copy had `selectionRan == 0`.
Verifiable: Windows only (timing).

### [Medium][High] Shutdown paths proceed after a timed-out join — src/dllmain.cpp:113-121, src/plugin/openshim_plugin.cpp:195-201

```cpp
        WaitForSingleObject(reinterpret_cast<HANDLE>(g_LoaderThread), 5000);
        CloseHandle(...); g_LoaderThread = 0;
        ShutdownBZLoader();   // -> BZLoader_Shutdown, then FreeLibrary(bzloader.dll)
```
```cpp
            BZROpenShim::SignalPatcherShutdown();
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_PatchThread), 2000);
            ...
        BZROpenShim::UiPerfHooks::Shutdown();  ... ShutdownNetworkOptimizer();
```
Neither wait checks its result. If the loader thread is still inside `BZLoader_Initialize` (holding
`g_StateLock`) after 5 s, `ShutdownBZLoader` blocks on the lock (fine) but then `FreeLibrary(bzloader.dll)`
runs while that thread may still be returning through `bzloader.dll` code. If the patch thread is still in
`RunPatcher` after 2 s (the SteamStub settle wait alone can be longer), `RuntimeShutdown` tears down the
subsystems it is about to initialise. Every patcher loop already polls `g_ShutdownRequested`
(`patcher.cpp:621,727,1121,1290`), so `INFINITE` is safe here; at minimum, on `WAIT_TIMEOUT` log and skip
the teardown that follows. `Shutdown()` is host-only today (the game never calls it), which keeps this at
Medium. Verifiable: Windows only.

### [Low][High] Bootstrap log routing derives paths two different ways — src/engine/bootstrap_file_io.cpp:136-139,419-423 vs src/engine/game_log_path.cpp:122-139

```cpp
        char g_BzLoggerPath[] = "logs\\BZLogger.txt";        // CWD-relative, pushed into the exe's CRT fopen
```
The rewritten `push` operands are current-directory-relative, while `GetGameLogPath` (used by the IAT
wrapper for the same files and by the shim's own log) creates and uses `<exe dir>\logs`. With CWD != exe dir
(shortcut "Start in", some launchers) the CRT path opens `<cwd>\logs\BZLogger.txt`, which does not exist
and is never created, so the stock log is silently lost while stock would have written to CWD. The two
routes should agree: fill a static `char[MAX_PATH]` from `GetModuleFileNameA` in `ApplyEarlyGameLogHooks`
before patching the operands (the operand only needs a stable address, not a literal). Verifiable: Windows
only.

### [Low][High] Typed forwarders call a null pointer when a real export is missing — src/engine/winmm_proxy.cpp:93-97, 101-108

```cpp
#define FORWARD(name) \
    static decltype(&::name) _fn_##name = nullptr; \
    if (!_fn_##name) _fn_##name = reinterpret_cast<decltype(&::name)>(ResolveRealWinmmProc(#name)); \
    return _fn_##name
```
`ResolveRealWinmmProc` logs and returns null on failure; the macro then calls it. The naked legacy
forwarders `jmp dword ptr [g_fp_x]` through a null slot in the same case (Wine's `winmm` lacks some of the
`*32Message`/`mmTask*` thunks). Since these are legacy names the game never calls it is Low, but the typed
ones could fail closed with `MMSYSERR_NOTSUPPORTED`/`0`/`FALSE` for one extra line per thunk; the naked ones
can point their slot at a `ret` stub at resolve time. Verifiable: Windows only.

### [Low][High] `Initialize()` still performs the process-wide search-path mutation the doc marks for removal, and looks itself up by name — src/dllmain.cpp:41-53, 99-100

```cpp
        HMODULE hMod = GetModuleHandleA("winmm.dll");
        if (hMod) SetupLibrarySearchPath(hMod);   // SetDllDirectoryA(<winmm dir>)
```
`Docs/BZLOADER_ARCHITECTURE.md:404-405` and phase 4 say this belongs on the removal list; BZLoader and the
plugin already use absolute paths with `LOAD_WITH_ALTERED_SEARCH_PATH`, and nothing in scope depends on it.
It also changes the game's own `LoadLibrary` search order for the whole process. Separately, `DllMain`
already has `hModule`; resolving by base name is what the SDK doc tells *companions* to do, the proxy itself
should use its own handle. Fix: pass `hModule` into `Initialize`, drop `SetupLibrarySearchPath`, log the
directory only. Verifiable: Windows only.

### [Low][High] Crash-time work that can be hoisted or is unsafe on the faulting thread — src/engine/crash_logger.cpp:305, 320-345, 381

- `:305` `EnvDisabled("OPENSHIM_DISABLE_CRASH_DUMP")` is evaluated inside the unhandled filter.
  `GetEnvironmentVariableA` takes the PEB lock; a thread that faulted while holding it deadlocks the
  report. Read it once in `InstallCrashLogger` into a static bool like the other two opt-outs.
- `:323-343` the VEH writes a full report (CreateFile, 512-slot `VirtualQuery` scan) for a first-chance
  `EXCEPTION_STACK_OVERFLOW` on the overflowed stack; that reliably double-faults and loses the unhandled
  report and minidump that would otherwise follow. Return `EXCEPTION_CONTINUE_SEARCH` for that code in
  the VEH.
- `:381` `LoadLibraryA("dbghelp.dll")` by bare name while `SetDllDirectoryA(<game dir>)` is in effect
  puts the game directory ahead of System32; `LoadRealWinmm` already builds a `GetSystemDirectoryA` path,
  do the same here.
Verifiable: Windows only.

### [Low][High] Startup-seam call-site gate mixes relocation-aware and absolute addresses — src/engine/startup_backend_seam.cpp:524-531, 713-716, 736-737, 782-792, 797

```cpp
        constexpr uintptr_t kImageBaseAssumption = 0x00400000u;
        ...  imageBase + (kConfigFileLoadIatVa - kImageBaseAssumption)     // slot: rebased
        ...  if (returnAddress != kStartupCfgLoadRetVa) return;             // gate: absolute
        ...  bytes[2] == 0x08 && bytes[3] == 0x9D && bytes[4] == 0x86        // operand: absolute
```
The arm rebases the IAT slot and marker but the gate compares an absolute return address and absolute
`call [0x00869D08]` operand bytes. On a relocated image the seam arms, the gate never matches, and the boot
silently falls to stock; that is fail-closed (good) but the arm status says "armed" and the log says
nothing. Either drop the rebasing (the executable is not `/DYNAMICBASE` and every other site here is
absolute) or rebase the gate too; and note in the report at `:2877` of the consumer that "armed" does not
imply "gate reachable". These are also raw addresses in feature code; they are byte-checked and the
bootstrap cannot parse `patches.json` under the loader lock, so a comment pointing at the corresponding
`patches.json` entries (or a static_assert-style test that the two agree) is the realistic mitigation.
Same applies to `bootstrap_file_io.cpp:419-423` and the two pre-main patch TUs. Verifiable: Linux (a
test comparing the constants with `scripts/patches.json` is pure text).

### [Low][Med] Command-line snapshot truncates at 1200 bytes — src/engine/startup_backend_seam.cpp:53,60

```cpp
    char s_commandLineSnapshot[1200] = {};
    strncpy_s(s_commandLineSnapshot, raw, _TRUNCATE);
```
Steam launch options plus a long quoted exe path can exceed this; a `/renderer:` token past the cut is
lost and the seam silently falls back to the persistent preference. The buffer is static, so 4096 or
`32767` costs nothing at run time; alternatively scan for the `/renderer:` token at capture time and store
only that. Verifiable: Linux, if `FindCommandLineRendererOverride` is exercised with a long input.

## Dead or unused code (list with evidence)

- `src/engine/scene_depth_facts.cpp` is compiled into **winmm.dll** (`BZROpenShim.vcxproj`) but no
  winmm-side TU includes `scene_depth_facts.h` — only `src/patches/dx11_scene_depth.cpp` (plugin) and the
  test do (`grep -rl scene_depth_facts.h src include tests`). The doc lists six shared TUs; the project has
  seven. Remove it from `BZROpenShim.vcxproj`.
- `src/plugin/bootstrap_service_client.cpp:43` `BootstrapFileIo::GetProvider() { return nullptr; }` has no
  caller in the plugin (`grep -rn 'GetProvider()' src` -> only the winmm implementation and the Windows
  test). The comment says the runtime never reads it; the stub exists only to satisfy a declaration nobody
  references. Drop it, or declare `GetProvider` bootstrap-only in the header.
- `include/startup_backend_seam.h:119-125` `RenderProfiles::SeamResultForPublication`,
  `ClearPendingMarkerFromRuntime`, `RunStartupSelectionForTestImpl` are declared in the shared header but
  used only inside `startup_backend_seam.cpp` (`:905-922` -> `:929,937,944`). They can be TU-local
  (anonymous namespace) and leave the header; the plugin compiles the header and could call them by
  mistake, which would be a link error against the wrong module.
- `include/winmm_proxy.h:4` comment "The DllMain in dllmain.cpp bootstraps the standalone OpenShim patcher"
  is stale; it starts BZLoader now.
- `src/plugin/openshim_plugin.cpp:135,147` log with component `"dllmain"` from the plugin's patch thread;
  the lines are attributed to the wrong module in `openshim.log`.
- `Docs/BZLOADER_ARCHITECTURE.md:348` "winmm.dll 18 TUs" vs 19 in the vcxproj; `:353-356` six shared TUs
  vs seven. Doc drift caused by the `scene_depth_facts` entry above.
- `BZLoader::PluginFlags` (`bzloader_catalog.cpp:93`) is only called from tests; harmless as a v1 ABI
  accessor, but nothing in the host reads `flags` yet.

Everything else was checked and is used: `LogShimW`/`LogShimVW` (one caller each), `BZLoader_GetSessionId`
(host test), `RunStartupSelectionForTest` (seam test), `GetShimLogSink` (bootstrap API test),
`RequestedBackendName` (both modules).

## Performance notes

- `bootstrap_file_io.cpp:148-191, 244, 288`: every `CreateFileA/W` the game makes builds two
  `std::filesystem::path`s, four `std::(w)string`s (`filename()`, `extension()`, two lower-cased copies) and
  returns a full-length copy of the file name even when nothing is routed (the common case). During a
  mission load that is thousands of opens; the whole predicate is "no `\\`/`/`, ends in `.log` or equals
  `bzlogger.txt`" and needs no allocation. Same rewrite removes the exception hazard above.
- `shim_log_client.cpp:304-337`: each `LogShimA` formats into a 4 KiB stack buffer, copies to a
  `std::string`, copies *again* in `WriteFormattedMessage` (`std::string line = formatted;`) for the trim.
  Take `formatted` by value and move, or trim in place before constructing the string. Only matters on
  chatty paths in other scopes, but this is the shared floor for all of them.
- `shim_log_sink.cpp:141-152, 210`: `OutputDebugStringA` on *every* line, always. Without a debugger it
  is still a `RaiseException(DBG_PRINTEXCEPTION_C)` round trip through the VEH chain (which now includes
  `FirstChanceLogger`), on top of the `fflush` per line. Consider a one-time `IsDebuggerPresent()` gate or
  a config switch; Wine also handles this exception slowly.
- `bzloader.cpp:98-103`: `_wfopen_s`/`fclose` per log line under `g_LogLock`. Fine for the dozen lines the
  host writes; do not route plugin bulk logging through `BZHostApi::log`.
- `crash_logger.cpp:229-253`: the first-chance path (budget 64, one per EIP) does up to 512 `VirtualQuery`
  calls plus `GetModuleHandleExA`+`GetModuleFileNameA` per hit on the faulting thread before the game's
  own `__try` gets to see the exception. Acceptable given the budget, but note it is why healthy sessions
  can show a few-ms hiccup on the shim's own guarded probes.

## Positive notes (things done well that later work should keep doing)

- `DllMain` does exactly what the doc says it does and no more; every heavy step is on a worker, the worker
  is started with `_beginthreadex`, `DisableThreadLibraryCalls` is called, and the detach path refuses to
  join. The one violation (version.dll) is a build setting, not a design choice.
- Both cross-module tables (`BZHostApi`, `BZPluginInfo`, `OpenShimBootstrapApiV1`, `StartupRendererResult`,
  `BootstrapFileIo::Provider`) are real append-only structs with `structSize`, guarded accessors, fixed-width
  integers, and `static_assert`ed layouts; `PluginTooLarge` is rejected instead of read off the end.
- Every plugin entry point (`Query`/`Load`/`Shutdown`/`LoadLibraryExW`) and every raw memory probe
  (`GuardedReadSlotValue`, `GuardedMarkerEquals`, `PatchPushStringOperand`, `BuildExecutableHint`,
  `GuardedTransportGate`) is behind `__try` in a function with no unwindable C++ objects.
- The startup seam fails closed at every step with a numbered arm status, and the one-shot latch is taken
  *before* the heavy work so a fault cannot cause a second transport attempt.
- `bootstrap_file_io.cpp` loads the provider pointer once per call and reports both the requested and the
  routed name; `GetLastError` is preserved across the notification.
- Path derivation is module-relative everywhere that matters (`GetProxyDirectory`, `ModulePath(g_Module)`,
  `GetMainModuleDirectory`, `GetGameLogPath`), the real WinMM is loaded by absolute System32 path, and every
  dependent module is loaded with `LOAD_WITH_ALTERED_SEARCH_PATH`.
- The export surface is pinned twice: `winmm.def` (263 names) against `winmm_export_baseline.txt` (271 =
  263 + 7 mangled v1 symbols + `OpenShimBootstrap_GetApi`, all accounted for) with `@N` stack sizes so a
  wrong `WINAPI` signature would fail the Windows lane, and the three intentionally-absent names are listed
  in both the baseline and the test.
- `bzloader.log` carries a per-run session id so the host integration test cannot be fooled by a previous
  run's success.
- The crash logger is written for crash time: static buffers, `WriteFile` only, interlocked guard, per-EIP
  dedupe and a budget for the first-chance path.
