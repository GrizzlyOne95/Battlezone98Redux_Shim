# BZLoader architecture and Phase 1 extraction plan

## Scope and status

BZLoader separates Battlezone's injection entry point from native module hosting
and, eventually, from OpenShim itself:

```text
Battlezone98Redux.exe
  -> winmm.dll                 proxy and pre-main compatibility seams
     -> bzloader.dll           native plugin host
        -> plugins/openshim.dll
```

This change is an extraction, not a rewrite. Phase 1 establishes and validates
the host boundary before moving the current OpenShim runtime. The foundation
keeps OpenShim in `winmm.dll` temporarily and loads BZLoader from the existing
patch worker. This preserves all current pre-main behavior while discovery and
ABI failure cases become independently testable.

The following are explicitly later work: hot reload, recursive discovery, a
dependency solver, an IFEO or suspended-process launcher, Windows 2000 support,
and centralized patch arbitration.

## Current startup sequence

The current implementation is concentrated in `src/dllmain.cpp`.

### Under loader lock (`DLL_PROCESS_ATTACH`)

1. `RenderProfiles::CaptureCommandLineSnapshot()` copies the pristine command
   line before the game mutates its buffer.
2. `BZROpenShim::Initialize()` initializes `openshim.log` and SDK v2, obtains
   `GetModuleHandleA("winmm.dll")`, and calls the process-wide
   `SetDllDirectoryA` with that module's directory.
3. `LoadRealWinmm()` builds an absolute System32 path, loads the real WinMM, and
   resolves legacy naked-forwarder targets.
4. The proxy pins itself for process lifetime.
5. `ApplyEarlyGameLogHooks()` installs logging hooks needed before game logs are
   created.
6. `RenderProfiles::InstallStartupBackendSeam()` validates and swaps one IAT
   entry. Its actual renderer transport runs later on the game thread.
7. `ApplyEditorOverheadPlacementOrderFix()` patches constructor-time behavior.
8. `ApplyCliMultiParameterOptionFix()` writes the command parser delimiter.
9. `_beginthreadex` starts `PatchThreadProc`.

The first four fix/seam calls intentionally run before the executable's CRT
constructors or `main`. Static inspection of the supported GOG executable found
that the only candidate early WinMM call, `timeBeginPeriod`, is reached from
normal game code through `0x00822EF0`, not before CRT initialization. Therefore
"first proxied WinMM call" is not an equivalent bootstrap boundary.

### Existing worker (`PatchThreadProc`)

The worker initializes UI performance state; renderer diagnostics and FXAA;
crash logging; the network optimizer and BZRNet instrumentation; then calls
`RunPatcher`. The patcher loads configuration, detects Steam/GOG and executable
version, waits for SteamStub settlement when required, parses and resolves
`scripts/patches.json`, installs patches, and publishes compatibility state.

After the patcher, the worker installs multiplayer faction/readiness diagnostics,
UI performance and file-scan hooks, renderer profiles, terrain proxy phase 2,
compatible-build autosave, and the native CPU sampler.

### Shutdown

`BZROpenShim::Shutdown()` is the only joined shutdown path. It signals and joins
the patch thread, shuts subsystems down in dependency order, frees real WinMM,
and closes the logger. `DLL_PROCESS_DETACH` never joins: process termination does
no cleanup, while explicit unload only signals the patcher and relies on the
module's process-lifetime pin.

## Selected deferred bootstrap boundary

BZLoader is loaded at the beginning of `PatchThreadProc`, not from `DllMain`.
The worker is an existing normal execution context. If it reaches
`LoadLibraryExW` before process attach has returned, the Windows loader
serializes that call until the loader lock becomes available; the attaching
thread does not wait for the worker. Plugin enumeration, queries, loads, logging,
and filesystem work therefore occur outside the proxy's `DllMain`.

This is the smallest practical boundary that retains the proven pre-main fixes.
It also avoids depending on the process current directory or on whether the game
happens to call a particular multimedia API early enough.

The long-term proxy should replace the current thread creation with an equally
early, explicitly verified process-startup seam if one is found. That
is not required to keep plugin discovery itself outside loader lock.

## Module ownership

### `winmm.dll`

- Export and forward the required WinMM API to the absolute System32 DLL.
- Capture immutable pre-main inputs.
- Retain only pre-main patches that cannot yet be expressed safely through a
  loaded plugin.
- Start the already-established deferred bootstrap and report loader failure.
- Do no plugin enumeration or plugin initialization in `DllMain`.

### `bzloader.dll`

- Derive all paths from its own absolute module path.
- Enumerate only immediate `plugins/*.dll` entries.
- Query and validate metadata before calling a plugin load function.
- Reject malformed plugins, ABI mismatches, unsupported games/builds, duplicate
  IDs, missing exports, and structured exceptions with diagnostics.
- Load in stable order: ascending priority, case-insensitive plugin ID, then
  case-insensitive absolute path.
- Provide the small versioned host API and reverse-order shutdown calls.

### `plugins/openshim.dll` (next extraction stage)

- Own the current patch worker and almost all present OpenShim sources unchanged.
- Preserve the current executable/version gates and `patches.json` behavior.
- Store its own `HMODULE` in a minimal plugin `DllMain` and initialize only
  from `BZPlugin_Load`.
- Retain its current process-lifetime/no-hot-unload safety policy.

Before this move, the command-line snapshot, renderer startup seam, editor
constructor fix, and CLI delimiter fix need an explicit proxy-to-plugin bridge or
must be documented as bootstrap-owned compatibility services. Moving them to a
later plugin load would silently change behavior.

## ABI v1

`include/bzloader_plugin.h` is the normative ABI. It uses `extern "C"`, fixed
width scalars, caller-supplied `structSize`, explicit ABI versions, and host- or
plugin-owned immutable strings. No STL or C++ object ABI crosses the boundary.

Required exports are:

```text
BZPlugin_Query(host ABI, metadata out)
BZPlugin_Load(host API)
BZPlugin_Shutdown()
```

### Append-only structures

Both shared structures are genuinely append-only, not append-only by promise.
Each has a **mandatory v1 prefix** that every participant must provide, and a
tail of optional fields a participant may omit because it was compiled against
an older header:

| Structure | Mandatory prefix ends at | Optional tail |
| --- | --- | --- |
| `BZHostApi` | `log` (`BZLOADER_HOST_API_V1_SIZE`) | `executableTimeDateStamp`, `executableSizeOfImage`, `getExecutableSha256` |
| `BZPluginInfo` | `supportedGameMask` (`BZLOADER_PLUGIN_INFO_V1_SIZE`) | `supportedBuildHint`, `dependencies`, `conflicts`, `loadPriority`, `flags`, `supportedExecutableSha256` |

`structSize` means two different things by direction, and this is the part
plugin authors get wrong:

- `BZHostApi::structSize` is **what the host filled**. A plugin must not read a
  field `BZLOADER_HAS_FIELD` does not cover.
- `BZPluginInfo::structSize` is the buffer **capacity** on the way in and the
  count of bytes **written** on the way out. A plugin compiled against a newer
  header clamps itself to the capacity it was handed rather than refusing an
  older host, and reports what it wrote. `src/loader/test_plugin.cpp` is the
  worked example.

The host reads the `BZPluginInfo` tail only through the guarded accessors in
`bzloader_catalog.h`, never by touching the field. A plugin that reports more
than the host's buffer holds is rejected outright (`PluginTooLarge`) rather
than read off the end of that buffer.

Dependency/conflict strings remain diagnostic-only in v1; no load-order promise
is inferred from them.

### Executable identity: a hint and an authority

There are deliberately two, because the cheap one is not trustworthy:

- `BZHostApi::executableBuildHint` is `pe-<TimeDateStamp>-<SizeOfImage>`, plus
  the same two values exposed as raw fields. It is cheap, always present, and
  **weak**: builds can collide on it and a relinked but behaviourally identical
  build can differ on it. It is a filter and a log token. `supportedBuildHint`
  matches against it and means "probably the right build".
- `BZHostApi::getExecutableSha256` computes the real digest of the running
  image, lazily and at most once per process, so only a plugin that actually
  pins an image pays the file read. `supportedExecutableSha256` is matched
  against it and is authoritative. It fails closed on every way of not
  knowing: host too old to offer the callback, digest uncomputable, or digest
  different.

Neither replaces OpenShim's own exact-build, hash, and expected-byte guards,
which stay authoritative for anything that writes into the game image.

### Game gating is fail-closed

A recognised host requires its own bit in `supportedGameMask`. An
**unrecognised** host admits only a plugin that declares exactly
`BZ_GAME_MASK_ANY`: a plugin that enumerated the games it supports has already
said this is not one of them, so enumerating both known games is not a
wildcard. This is why the standalone lifecycle test still works -- its plugin
patches nothing and legitimately claims `BZ_GAME_MASK_ANY`.

## The OpenShim SDK export boundary

`docs/OPENSHIM_SDK_V2.md` tells companion DLLs to find OpenShim with
`GetModuleHandleA("winmm.dll")` + `GetProcAddress`. That makes the *module
name* part of the published ABI, not just the symbol names, so `winmm.dll` has
to keep exporting all 71 `OpenShim*` names even once the implementations live
in `plugins/openshim.dll`.

`winmm.dll` therefore exports thunks. `include/openshim_sdk_exports.inc` is the
single source of truth: the same list expands into the thunk bodies, into the
`OpenShimSdkProviderTable` struct, and into the drift test. No signature is
written twice, so none can disagree.

A thunk reads the installed provider table and calls through. It never loads
anything -- an export can be called on any thread at any time, including while
someone else holds the loader lock, so a thunk that hit `LoadLibrary` would be
a deadlock waiting to happen. With no provider installed it returns the
documented unavailable value (`FALSE`, `0`, `0.0f`, `nullptr`) and counts the
call. Resolution costs one `GetProcAddress` for the whole table, not one per
export: the bootstrap calls `SdkBridge::InstallProviderFromModule` once against
the already-loaded plugin, which fetches `OpenShimSdkProvider_GetTable`.

The table follows the same append-only rules as the plugin ABI -- `structSize`
says what is really there, fields are only added at the end, every read is
guarded -- so an older provider paired with a newer bootstrap reports its
shorter table and the newer exports read as unavailable instead of jumping
through uninitialised memory. The table itself is built with C++20 designated
initializers, which makes a mis-ordered slot a compile error rather than a
silently swapped function.

While the runtime still ships inside `winmm.dll`, the provider is installed
directly from `DllMain` (a pointer store into a static table -- no allocation,
no loader work), which keeps behaviour identical to calling the implementation
directly. When the provider moves into the plugin that call is replaced by
`InstallProviderFromModule`, and the window before the plugin loads becomes
real -- which is exactly why the thunks fail safely and count.

This is also what removed the `winmm_proxy.cpp -> bzr_hooks.cpp` dependency:
the marshalling that needed `bzr_hooks` moved to
`src/patches/openshim_sdk_provider.cpp` on the runtime side. Measured with the
closure script, `winmm_proxy.cpp` went from reaching 52 translation units to
reaching 2 (itself and `shim_log.cpp`).

## The bootstrap file-I/O seam

The executable's `CreateFileA/W` import entries point at wrappers in
`src/engine/bootstrap_file_io.cpp` for the whole life of the process. They are
patched once, before the CRT runs, and nothing ever re-points them. What
changes over the process lifetime is not the hook but the *policy* behind it.

This is the shape the split needed, and it is not "early code versus runtime
code". `ApplyEarlyGameLogHooks` was one function doing two unrelated jobs:
rewriting five immediate log-path operands (self-contained, genuinely
pre-main) and installing `CreateFile` handlers that carried the BZN, editor,
TRN, shader-cache and UI-perf runtime. Only the second dragged
`patcher`/`hook_engine`/`resolve_table` into the proxy.

So the bootstrap keeps the hook, the original function pointers, the import
patcher, the operand patches, and the early log routing -- and nothing else.
With no provider installed a wrapper routes the stock logs, calls the real
Win32 function, preserves `GetLastError`, and returns. That path has to work,
because the game creates `BZLogger.txt` and its Ogre log almost immediately.

OpenShim supplies the rest by installing a `Provider`: two optional path
rewrites and two post-open notifications. It is a pointer store, never a
`LoadLibrary` or a `GetProcAddress`, and the executable's import table is
never rewritten again. The table is **internal**, deliberately not part of
`BZPluginHostApi` v1: it is an implementation seam between the bootstrap and
OpenShim, not something third-party plugins should bind to yet.

Two details that are easy to get wrong:

- **Both names are reported.** `onOpened` receives the caller's original name
  *and* the path actually opened. They are not interchangeable: the `*.program`
  shader-cache trigger and TRN write tracking key off what the caller asked
  for, while editor-source detection and BZN load tracing follow what was
  really opened. Collapsing them silently breaks one side or the other.
- **The provider pointer is loaded once per call.** It is `std::atomic` with
  release/acquire, and a wrapper that read it twice could route a path through
  one provider and report the open to another.

`GetGameLogPath`/`SanitizeLogFilename` moved to their own translation unit
(`game_log_path.cpp`) rather than the bootstrap taking a dependency on
`shim_log.cpp`. They are pure and stateless, so a module can compile them
safely; the logging subsystem, which owns a file handle, an init-once and a
lock, must exist exactly once and stays on the runtime side.

Measured effect. `bootstrap_file_io.cpp` reaches **2** translation units
(itself and `game_log_path.cpp`); the `file_io_hooks.cpp` it replaced in the
bootstrap graph reached 58. Every remaining route from the bootstrap to the
patch engine now runs through the renderer:

```text
patcher.cpp <- bzr_options_ui.cpp <- ogre_render_profile.cpp
```

The whole bootstrap minus the renderer seam is 10 of 78 translation units, so
the renderer is the only major cut left.

## The bootstrap startup renderer seam

Deliberately not built like the file-I/O seam, because the timing contract is
different. There, a missing provider can mean "stock for now, the plugin
catches up later". Here it cannot: the intercepted `Ogre::ConfigFile::load`
*is* the game's read of `Ogre.cfg`, and the graphics bootstrap reads
`getSetting("Render System")` immediately afterwards. If the decision is not
made by the time that call returns, the decision point is gone for this boot,
and a warm-cache Steam start reaches the load in about a second -- long before
any plugin could be hosted.

So the bootstrap owns the whole startup decision and runs it self-
sufficiently, with no plugin loaded at all. It owns the command-line snapshot,
the arm, the executable/IAT/call-site validation, the original
`ConfigFile::load` pointer, the one-shot latch, minimal parsing of
`[Graphics] Renderer` and `[Startup] BackendTransport`, CLI `/renderer:`
resolution, the renderer-DLL presence check, and the atomic `Ogre.cfg`
transport. Then it calls the original `ConfigFile::load` exactly as before.

`backend_selection.cpp` is reused as the decision core rather than duplicated
in spirit: it is already pure and free of Win32 and Ogre, and so is
`render_profile.cpp`. Compiling those two into the bootstrap is fine. What the
boundary keeps out is `hook_engine`, the patch registry, resolve tables and
mutable renderer runtime state.

The bootstrap publishes a POD `StartupRendererResult` -- no `std::string`, no
locks, no patch-engine objects, nothing with a destructor. OpenShim reads it
during its own initialisation and seeds `s_bootRequest` and
`s_transportWrittenThisBoot` from it instead of re-deriving a decision that
was made before it existed. Everything below the startup transport stays with
OpenShim: active-backend observation, outcome classification, scheme takeover,
Enhanced resources, DX11 compatibility, options UI, viewport work, profile
requests.

Like the file-I/O provider, this is OpenShim-bootstrap plumbing and is **not**
part of the BZLoader plugin ABI.

The call-site proof moved intact and should stay that way: the return-address
gate, the six-byte post-SteamStub validation, the `Ogre.cfg` argument check,
the one-shot latch and the SEH fail-to-stock behaviour are all load-bearing.

Measured effect. The seam reaches **5** translation units; the whole bootstrap
(excluding `dllmain.cpp`, which is still the monolith's entry point and gets
split with the plugin) is **13 of 79**, down from 58 before the SDK, file-I/O
and renderer cuts. `ogre_render_profile.cpp` moved from the bootstrap graph to
the plugin side.

## The module split, as built

```text
Battlezone98Redux.exe
  -> winmm.dll                 18 TUs   bootstrap
     -> bzloader.dll                    plugin host
        -> plugins/openshim.dll  74 TUs  runtime
```

`winmm.dll` is 213 KB where the monolith was 3.0 MB. It compiles twelve
translation units of its own plus six that are pure enough to share
(`backend_selection`, `render_profile`, `render_effect_intent`,
`game_log_path`, `shim_log_client`, `startup_seam_wire`) -- stateless mappings
where a second copy cannot disagree with the first.

### What the plugin may and may not do

The loader owns the plugin's lifecycle. It called `BZPlugin_Load` to start the
runtime and it calls `BZPlugin_Shutdown` to stop it, so the plugin never shuts
down BZLoader, never frees the real WinMM, and never closes `openshim.log`. A
plugin tearing down its own host would invert the dependency graph. That
ordering is also what lets the runtime log its entire shutdown: BZLoader
returns first, and only then does the bootstrap release WinMM and close the
log.

`BZPlugin_Load` resolves the bootstrap table, installs the log bridge, installs
the file-I/O and SDK providers, and starts the patch worker. A failure before
the worker starts is transactional -- nothing is installed, so returning 0
leaves the process as it was.

### Two directions, two tables

- **plugin -> bootstrap** is `OpenShimBootstrapApi`, one versioned table behind
  one export (`OpenShimBootstrap_GetApi`): logging, the startup renderer
  result, the pending marker, provider installation, the import patcher, and
  the deferred CLI verification. Private, and deliberately not
  `BZPluginHostApi` -- third-party plugins have no business in it.
- **bootstrap -> plugin** is `OpenShimSdkProviderTable`, which the export
  thunks already used. The split appended the legacy v1 C++ API to it, so the
  seven mangled symbols winmm.dll has always exported keep working while the
  values come from the runtime.

### The export surface

`winmm.dll` still exports 271 symbols: every `OpenShim*` SDK name, the seven
mangled v1 C++ symbols, and the WinMM forwarders. Exactly three left, all
predicted and none of them published API -- `OpenShimSdkProvider_GetTable`
(the plugin's own getter, which the bootstrap now resolves *from* the plugin)
and the two `walker_cockpit_trace.cpp` debug hooks that were never in
`winmm.def`.

## Path and loading security

The proxy derives `bzloader.dll` from the proxy module address and calls
`LoadLibraryExW` with an absolute path and `LOAD_WITH_ALTERED_SEARCH_PATH`.
BZLoader derives `plugins` from its own module path, never the current directory,
does not recurse, and loads each discovered DLL by absolute path using the same
flag. This is compatible with the shipped Win32 payload under native Windows and
Wine/Proton without introducing registry or shell dependencies.

The existing `SetDllDirectoryA` in OpenShim initialization is process-wide and
belongs on the migration-removal list. It is not reused by BZLoader.

## Current patch and hook ownership

OpenShim currently has several independent mutation mechanisms:

- `scripts/patches.json`, `BuildPatchList`, `ScanForPatchAddresses`, and
  `HookEngine::ApplyPatch` for checked byte, JMP5, REL32, DWORD/vtable, and
  global-address patches;
- named read/call resolutions through `HookEngine::ResolveNamedAddress`;
- direct IAT swaps for Win32, Ogre, renderer, file, and network interception;
- subsystem-owned trampolines and detours, including dynamically chained
  network and UI hooks;
- exact-build/hash-gated renderer and terrain hooks.

Today, only OpenShim coordinates these writes. Multiple plugins could install
separate trampolines or overwrite the same IAT/byte region without detection.
ABI v1 intentionally exposes no raw patch-registration promise, leaving room to
append `ResolveSymbol`, `RegisterPatch`, `RegisterHook`, and ownership/query
services later. A broker must define region identity, expected bytes, callback
ordering, chaining, rollback, and plugin ownership before those functions are
standardized.

Plugin `DllMain` implementations must remain minimal. A failed
`BZPlugin_Load` must be transactional: it returns only after undoing any partial
initialization, because the host does not call `BZPlugin_Shutdown` for a plugin
that never became active.

## Failure and lifecycle policy

- Bad or incompatible candidate plugins are logged and skipped; independent
  plugins continue.
- Duplicate IDs are rejected deterministically.
- A plugin whose load fails is not considered active.
- Successfully loaded plugins receive shutdown in reverse load order.
- Runtime unload/reload is unsupported. Successfully loaded modules are not
  freed by BZLoader after shutdown because workers or trampolines may still
  reference their code.
- During the foundation stage only, missing BZLoader is logged and the existing
  monolithic OpenShim continues. After OpenShim moves behind the ABI, a missing
  loader or plugin must fail closed before OpenShim patching begins.
- `bzloader.log` is append-only across runs, so every line carries the id of
  the run that wrote it (`[s=...]`, also exported as `BZLoader_GetSessionId`).
  Without that, any reader -- including the host integration test -- can credit
  this run with a previous run's success.

## Phase plan and validation

1. **Audit:** this document and source-derived boundary.
2. **Foundation:** ABI header, deterministic loader, host logging, test plugin,
   catalog tests, and deferred proxy integration.
3. **OpenShim extraction:** split WinMM forwarding from OpenShim bridge exports,
   create `plugins/openshim.dll`, pass/store its module handle, and update
   resources/updater/package manifests.
4. **Thin proxy:** remove logger/SDK/runtime initialization and the process-wide
   DLL search mutation; retain only forwarding and proven bootstrap seams.
5. **Qualification:** unit tests plus native GOG, Steam, Proton/Steam, and
   Wine/Proton GOG launch/deployment lanes. Loading/path/layout changes require
   all four lanes or an explicit unverified-lane release block.

Foundation automation covers metadata sizing and the append-only prefix/tail
rules, ABI mismatch, IDs, fail-closed game gating (including an unrecognised
host), build hint and exact-SHA-256 constraints, duplicate IDs, stable
ordering, and plugin-directory derivation. The Win32 workflow runs
`BZLoaderHostTest.exe` after MSBuild and fails the job on a nonzero exit, so
the green check means Windows really loaded another DLL through the ABI and
completed the lifecycle. These tests are written with an explicit `CHECK`
macro rather than `assert`, because CI configures the suite as Release and
`NDEBUG` would compile every assertion away.
Native integration must additionally exercise missing directories, invalid DLLs,
missing exports, load failures/exceptions, shutdown order, and diagnostic paths.
