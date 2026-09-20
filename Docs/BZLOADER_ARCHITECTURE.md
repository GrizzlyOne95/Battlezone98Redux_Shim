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
