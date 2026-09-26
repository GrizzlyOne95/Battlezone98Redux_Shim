# OpenShim repository code audit (2026-09-25)

Repository-wide review of the native shim for safety, correctness, performance,
efficiency and unused code, taken at commit `17e40c0f` (main). This document is
the consolidated, prioritized view. The per-subsystem reviewer worksheets, with
code quotes and section maps, are in `Docs/audit_20260925/`. Line numbers in
those worksheets refer to `17e40c0f`; `src/patches/bzr_hooks.cpp` shrank by
about 530 lines in the same pull request, so its numbers shift accordingly.

## 1. Scope and method

- Every `.cpp`, `.h`, `.inl` and `.inc` under `src/`, `include/` and `tests/`
  was read end to end (about 125k lines excluding the vendored JSON header),
  plus the installers, deploy scripts, CI workflows, project files and the
  repository hygiene surface.
- The engine-independent CTest suite was built and run on Linux before and
  after the changes (40/40 pass, zero warnings under `-Wall -Wextra -Wshadow`).
- Two mechanical sweeps backed the reviewers: an unreferenced-symbol sweep
  (declared or defined once, never referenced, not exported through
  `winmm.def`) and a raw-address census (`0x00[4-9A-F]xxxxx` literals in code).
- Findings were kept only when the reviewer re-read the surrounding code and
  grepped the callers; the highest-rated ones were re-verified independently
  before being acted on.

## 2. Executive summary

The codebase is in good shape for what it is: a large, hook-heavy native shim.
The hook engine, loader ABI, network parsers, render hooks and updater all show
consistent discipline: byte-verified writes, POD-only SEH frames, fail-closed
platform gates, balanced COM reference counts, bounded tables and budgeted
logging. No use-after-free, calling-convention mismatch or exploitable packet
parser was found.

The real risks cluster in five places:

1. **Process-wide hazards in rarely exercised paths.** Logging while every
   other thread is suspended (profiler entry detours), a non-transactional
   plugin load that could leave the executable's IAT pointing into an unmapped
   module, and a delay-loaded `version.dll` resolved from inside `DllMain`.
   All three are fixed in this PR.
2. **Config-driven behaviour that ignored its switch.** The multiplayer
   career-stats worker ran regardless of `[Career] StatsTracking`; the Ogre
   profiler's build default was *on* while every document and ini said *off*;
   the shadow-far override silently stopped re-applying after sixteen mission
   loads. Fixed in this PR.
3. **Exceptions with no barrier on the patch thread.** `std::stoi`,
   `std::filesystem::exists` and JSON accessors could throw out of
   `PatchThreadProc` and abort the game at launch on a malformed ini or
   patches.json. The preset-migration and static-pointer sites are fixed
   here; the general barrier is backlog item P0-3.
4. **Raw engine addresses in feature code.** About 1,100 literal engine
   addresses live in `src/` (696 of them in `bzr_hooks.cpp`) against the
   project's own rule that build-specific sites belong in `scripts/patches.json`.
   Most are byte-guarded, but a handful are called with no identity check at
   all (the music bridge was one; fixed here). This is the largest structural
   item and is scheduled as P1-1.
5. **`bzr_hooks.cpp` is a 42k-line god file.** It mixes roughly forty
   unrelated features, several concluded research probes and a few empty
   placeholders. The reviewers produced a 170-row section map to plan the
   split (section 7).

## 3. Fixed in this pull request

| # | Fix | Files | Verified |
|---|-----|-------|----------|
| F1 | Profiler entry-detour installer no longer logs while all other threads are suspended; outcome is captured to locals and logged after resume. Previously any suspended thread holding the heap, log or CRT FILE lock would hang the process. Reached on every GOG DX11 launch via the skin-source-shadow policy. | `src/patches/ogre_animation_profiler/patch_scopes.inl` | Windows (CI build); logic re-read |
| F2 | Ogre animation profiler build default changed from on to off, matching `openshim.ini`, the example ini and the profiler docs. | `src/patches/ogre_animation_profiler/config_state.inl` | Windows |
| F3 | `BZPlugin_Load` creates the patch thread `CREATE_SUSPENDED` first, installs the file-I/O and SDK provider tables into `winmm.dll` only once nothing can fail, then resumes. BZLoader no longer `FreeLibrary`s a plugin whose `Load` failed or raised, since such a plugin may already own process-wide state. | `src/plugin/openshim_plugin.cpp`, `src/loader/bzloader.cpp` | Windows (BZLoader host lifecycle test in CI) |
| F4 | `version.dll` is a static import of `winmm.dll` instead of a delay-load, because `ApplyCliMultiParameterOptionFix` reads the exe version resource from `DllMain`; a delay-load there is a `LoadLibrary` under the loader lock. The plugin keeps it delay-loaded. | `BZROpenShim.vcxproj` | Windows |
| F5 | Multiplayer career-stats session poll and kill/death recorder honour `[Career] StatsTracking`; with tracking off the worker no longer writes `career_stats.cfg` or calls engine accessors off the game thread. | `src/patches/bzr_hooks.cpp` | Windows |
| F6 | Shadow-far override: the 16-line telemetry budget now gates only the log lines, not the functional `setShadowFarDistance` re-apply. | `src/patches/bzr_hooks.cpp` | Windows |
| F7 | `OpenShimSetMusicTrack` fails closed on an unsupported build instead of calling a fixed address unconditionally. | `src/patches/openshim_sdk_provider.cpp` | Windows |
| F8 | `Hook_WSASendTo` and `Hook_sendto` restore the real socket error before returning; the logging helpers' `getpeername` call had been overwriting it with `WSAENOTCONN`. | `src/patches/net_optimizer.cpp` | Windows |
| F9 | Relay control log (`bz_relay_control.jsonl`, on with `RelayLogging=1`) is passed through `SanitizeBzrNetJson` so Steam/GOG app tickets and lobby passwords no longer land on disk verbatim. | `src/patches/net_optimizer.cpp` | Linux (sanitizer tests) + Windows |
| F10 | `patches.json` static-pointer accessor tolerates non-string or non-hex addresses instead of throwing out of the patch thread. | `src/engine/patcher.cpp` | Windows |
| F11 | Preset migration uses the `error_code` overload of `filesystem::exists` and rejects over-long revision digit runs instead of letting `std::stoi` throw at launch. | `src/patches/openshim_preset_migration.cpp` | Linux (preset migration tests) |
| F12 | Autosave evaluates the cheap deadline compare before the `Save\auto.sav` stat, removing a filesystem call per frame during missions. | `src/patches/autosave.cpp` | Windows |
| F13 | Linux installer: the "does this winmm.dll need bzloader.dll" probe used `grep -q` under `pipefail`; a quiet grep can close the pipe before `tr` finishes, `tr` then dies with SIGPIPE (status 141) and the fail-closed loader/plugin check is skipped. Now grep consumes the whole stream. | `scripts/install_linux.sh` | Linux: the reviewer reproduced status 141 on this host; the race is timing-dependent (a later 20-run re-check did not trigger it), and the new form cannot race |
| F14 | Windows installer downloads each uploader wrapper to a staging file and swaps it in only on success; it used to delete the live wrapper first, leaving the Steam launch option pointing at a missing `.bat` on a failed download. | `scripts/install_windows.ps1` | Windows |
| F15 | Dead code removed (section 6): 26 functions, 2 structs, 22 constants/flags, 3 stale declarations, the `netcode_hooks.cpp` forwarder, `ParseHexPattern`, one unused test helper and a duplicate include. | various | Linux tests + Windows CI |
| F16 | Hygiene: `tmp/load_test.exe`, `tmp/load_test.obj` and five Ghidra lock/index files untracked and ignored; two pre-split deploy scripts that still copied `winmm.dll` alone (`scripts/deploy_linux_proton.sh`, `launch_steam_chunk_force_geo.cmd`) removed. | `.gitignore`, `tmp/`, `battlezone98redux.exe-ghidra/` | n/a |

Everything marked "Windows" compiles through the Win32 CI lane but has not been
run in the game from this branch; F1, F3, F5 and F6 deserve one GOG launch with
`[Diagnostics] ProfileOgreAnimation = 1`, a multiplayer lobby and a shadow
quality change respectively before release.

## 4. Prioritized backlog

Severity/confidence as rated by the reviewer and re-checked where noted.
"Worksheet" points at the file in `Docs/audit_20260925/`.

### P0: safety and correctness, schedule next

| ID | Finding | Where | Worksheet |
|----|---------|-------|-----------|
| P0-1 | **MPAUTH diagnostic detours steal 5 bytes after verifying only a 3-byte prologue.** The ordinary-state-reader site declares its own 4th byte as `0x83` (`sub esp, imm8`, a 3-byte instruction), so the 5-byte steal provably splits it and the trampoline executes garbage whenever `[Diagnostics] TraceMpauth` is on. `GameObject::Remove` hook has the same shape. Fix: verify the full stolen length against known bytes (6 bytes here) or add a length decoder to `InstallInlineDetour32`. [High/Med] **Resolved 2026-09-25** (`agent/detour-steal-guards`): all nine MPAUTH sites now verify and steal the full prologue read from GOG 2.2.301 (6 bytes for the `83 EC` sites, 9 for the three `81 EC` sites; `Ordnance_Receive` and the ordinary reader had never matched), and `InstallInlineDetour32` runs every steal through `src/engine/x86_length.cpp`, refusing a range that is not on an instruction boundary or contains a rel8/rel16 branch, re-basing rel32 branches, and logging `[DETOUR] refused` once per site. The decoder is diffed against capstone over the whole GOG `.text` (10 mismatches, all SALC) and pinned by `tests/x86_length_tests.cpp`; a live run showed 0 refusals and 9/9 MPAUTH installs. | `bzr_hooks.cpp` 26331-26484 | E |
| P0-2 | **`ApplyPatch` guards only `expected_original.size()` bytes but writes `payload.size()`**; the two "Under Attack Alert Hook" entries write 52 bytes behind a 5-byte guard. Add `expected.size() >= payload.size()` (or an explicit `guard_len`) and extend those two guards in `patches.json`. Behaviour change: a mismatch will then fail closed, which is the intent. [Med/High] **Resolved 2026-09-25** (`agent/detour-steal-guards`): `ApplyPatch` refuses and logs `[PATCH] ... guard covers N of M payload bytes` when the guard is shorter than the payload; both Under Attack entries carry the full 52-byte block from GOG 2.2.301 (the JMP5 resumes at +0x34, which is the `jbe` target and an instruction boundary). A stale deployed `patches.json` with the old 5-byte guards now leaves those two hooks unapplied instead of writing 47 unverified bytes. | `hook_engine.cpp` 65-72, `patcher.cpp` 922, `patches.json` | B |
| P0-3 | **No exception barrier on the patch thread.** `RunPatcher`, `PatchThreadProc` and the JSON accessors (`std::stoul`, `get<std::string>`, ~40 sites) let a malformed `patches.json` or ini abort the game. Wrap `PatchThreadProc` body and `RunPatcher` config parsing in `try/catch`, log, and continue with defaults. [Med/High] **Resolved 2026-09-25** (`agent/patch-thread-exception-barrier`): every patches.json read goes through the non-throwing readers in `src/engine/patch_config_parse.cpp` (host-tested on both lanes, including a pass over the shipped file), so a malformed `static_pointers`/`patches`/`globals`/`audio_gas_pattern`/`features` node is logged as `[CONFIG] ... ignored` and only that entry is lost; `RunPatcher` and the preset-migration call carry their own `try/catch`, and each stage of `PatchThreadProc` runs under `RunPatchStage`, so a throwing stage is logged by name and the later stages still run. | `patcher.cpp` 54-61, 573; `openshim_plugin.cpp` 64-90 | B, I |
| P0-4 | **Signature-miss fallback builds its byte guard from pattern index 0 instead of `offset` and maps `??` to `0x00`**; the two HoverCraft REL32 fallbacks can never apply, and a coincidental match would write over unverified bytes. [Med/High] **Resolved 2026-09-25** (`agent/signature-miss-fallback-guard`): a signature miss takes the fallback only when `PatchConfig::VerifyFallbackSite` finds the entry's own pattern at `fallback - offset`, and the guard is then the `expected_size` bytes observed at the fallback address, as the scan path records them (host-tested on both lanes, including every non-`require_unique` shipped entry); a site that does not carry the pattern is logged as `[FALLBACK] ... rejected` and left unresolved, so the Steam settle loop retries it and the tail report names it under `[SIGNATURE]`. | `patcher.cpp` 883-891 | B |
| P0-5 | **Fail-open bridges when a guard fails.** Radar-scale bridge writes `0x008E77B0` even when its byte guard failed (36394-36402, 16077-16098); jump-snipe probe publishes GOG-only function pointers into shared globals before its build check (17721); `mp_faction_restrict` nulls `g_OrigLoad` when the second site fails while the first still calls the interceptor (407-414). [Med/High each] **Resolved 2026-09-25** (`agent/fail-closed-bridges`): the radar size scale is written (and read) only while the byte-guarded layout hook is installed, with a one-time `[RADAR] ... not written` line otherwise; the jump-snipe probe publishes `g_BzrFn_GetPlayerHandle`/`g_BzrFn_GameObjectGetObjByHandle` only after the `Person::Simulate` entry bytes match, and logs the mismatch once; a faction-restrict install whose second site fails restores the first site's stock call bytes (logging the call target it now reaches) before clearing the original, and keeps the original if the restore itself fails so the interceptor still delegates. | `bzr_hooks.cpp`, `mp_faction_restrict.cpp` | D, F, G |
| P0-6 | **Hooks written non-atomically from the patch thread while the game thread may execute the bytes.** `WriteProcessMemory` JMP5 writes in `hook_engine.cpp` and `InstallInlineDetour32` (opcode before rel32) have no suspend/interlocked write; `RetryDeferredRuntimeHooks` races between the patcher's 250x100 ms loop and game-thread SDK bridges over ~30 plain-bool latches. Fix: single mutex around retry + detour install, and an 8-byte interlocked write or thread suspension for the patch. [Med/Med] **Resolved 2026-09-25** (`agent/atomic-hook-writes`): `HookEngine::WriteMemory` commits a write to an executable page with every other thread suspended and none of them inside the site (retrying up to 20 ms for one that is, then refusing with a `[PATCH] ... not written` line) and flushes the instruction cache; `InstallInlineDetour32` writes its whole jump through that path instead of byte-by-byte; and `HookEngine::CodePatchLock`, a recursive mutex, is held by `WriteMemory`, `InstallInlineDetour32` (from the installed check through the write) and the body of `RetryDeferredRuntimeHooks`. | `hook_engine.cpp` 45-59, `bzr_hooks.cpp` 34274-34330, `patcher.cpp` 1288-1295 | B, F |
| P0-7 | **SEH `__except(EXCEPTION_EXECUTE_HANDLER)` around Ogre C++ calls swallows Ogre exceptions (0xE06D7363) without unwinding OgreMain frames** (chunk proxy 5993-6235, 6893+). Filter to access violations and use `try/catch` for the C++ side as the generic batch code already does. [Med/High] **Resolved for the chunk proxy 2026-09-25** (`agent/seh-filter-ogre-exceptions`): all 18 chunk-proxy guards now run their Ogre call through `CatchOgreThrow` (a `try/catch` lambda, so the throw unwinds OgreMain's frames before it is caught and logged) under `__except(OgreCallSehFilter(...))`, which keeps only hardware faults and passes the MSVC C++ exception code back to the unwinder. **Follow-up:** 25 other `__try` regions in `bzr_hooks.cpp` still wrap Ogre calls with the swallowing handler (DX11 lighting snapshot and scheme read, entity visibility calls, headlight state, pilot flashlight and bone samples, vehicle skinning probe, multiplayer flag billboards, owner-bone collapse, chunk owner visibility); they can adopt the same two helpers one subsystem at a time. | `bzr_hooks.cpp` | C |
| P0-8 | **Updater trust chain.** Manifest hashes are self-attesting and `bzfile_replace_helper.exe` is launched unverified; downgrade guard falls through on unparsable versions; `ValidationThreadProc` has no `try/catch`. Minimum: hash the helper in the manifest and verify it, compare the payload DLL's version resource against `manifest.version`, and add the barrier. [Med/High] | `openshim_updater.cpp` 433-448, 563-570, 627, 640-720, 685-692 | J |
| P0-9 | **TRN codec applies whole-file semantics per `fwrite` chunk.** A writer that emits more than one `fwrite` per file gets blank records or broken keys at chunk boundaries (reproduced on Linux). Accumulate per `FILE*` until close, and add a `canon(a)+canon(b)==canon(a+b)` test. [Med/Med] **Resolved 2026-09-25** (`agent/trn-writer-single-fwrite`) by the proof the audit allowed for: disassembly of the writer `FUN_00786C80` (0x00786E38-0x00786EF1, GOG 8D71F56C) shows the raw loader returning the whole existing TRN in one buffer, `fopen`, exactly one `fwrite(buffer, 1, size, FILE*)`, a return check against the size, `fclose`, free; no loop and no second write, so per-call canonicalization is whole-file canonicalization on this build and the exact-hash gate keeps it so. The proof is recorded in both TRN entries' `identity` text in `scripts/patches.json`, above the hook, on the codec declaration, and as an addendum to Finding 3B of the 2026-08-20 investigation; `trn_codec_tests` pins that the codec is not chunk-safe at the audit's two split points, so a writer that splits a file is never paired with it unchanged. | `redux_compatibility.cpp`, `scripts/patches.json` | H1 |
| P0-10 | **Windows uninstaller removes only `winmm.dll` and `patches.json`**, leaving `bzloader.dll`, `plugins\openshim.dll`, assets, ini backups and UI tiles; its discovery drifted from the installer. No Linux uninstaller. [Med/High] | `scripts/uninstall_windows.ps1` 109-125 | L |

### P1: correctness and performance worth scheduling

| ID | Finding | Where | Worksheet |
|----|---------|-------|-----------|
| P1-1 | **Move raw engine addresses into `patches.json`.** Census: 1,112 literals in 25 files; `bzr_hooks.cpp` 696, `trampolines.cpp` 54, `bzr_options_ui.cpp` 44, `mp_ready_diagnostic.cpp` 42, `ui_performance_hooks.cpp` 41. Start with the ones that are *called* rather than byte-compared: `ResolveObj76GameObject` 0x00479F30, `PlayGlobalSound` 0x0043AA30, `GetLocalPlayerNetId` 0x00572D90, `GameObjectFromHandleGog` pool 0x0260DB20, the ten `[Net]` globals, `ui_performance_hooks` shell addresses (whose `ResolveNamedAddress` names have no JSON entry and always fall back), `terrain_tile_blend` 0x02CC40C0, `pond_class_label` ParameterDB with a `55 8B EC`-only identity. `0x00462380` is defined three times, `0x00517AFC`/`0x00920EA0` five times. | many | B, C, D, E, F, G, H1, I, J, K |
| P1-2 | **Legacy-1.4 AI branch ships a `suppress = true` placeholder**: legacy craft never leave flee state 9 by timeout; also team-filtered ProximityMine "detonates" by OR-ing removal flags without spawning ordnance, and the magnet twin skips base `Mine::Simulate` when class is null. Either finish or gate off. | `bzr_hooks.cpp` 22931-22951, 32887-32900, 32679 | E |
| P1-3 | **Frustum-cull remembered-bounds table keyed by raw `Mesh*` is never invalidated on unload**; address reuse can restore a too-small box (the one failure mode the design forbids). Also `InstallEntityFrustumCullingIfEnabled()` at 34947 runs before its enable flags are computed (35080-35103) and is a no-op there. | `ogre_entity_frustum_cull.inl` 281-317, 1063-1075; `bzr_hooks.cpp` 34947 | F |
| P1-4 | **Options UI Career-page hooks match cached widget pointers process-wide** and are cleared only from the MainScreen ctor hook; a recycled heap address after title-screen teardown can be vetoed or blanked. Add a liveness check against the MainScreen singleton or hook the dtor at 0x0078ECA0 (bytes already verified in `native_ui.cpp`). | `bzr_options_ui.cpp` 5925-5933, 6867-6872 | I |
| P1-5 | **Preset migration Case A re-emits a bad file as its own canonical** when no payload is found, stamping revision 3 and never setting the safe-fallback flag. | `openshim_preset_migration.cpp` 1066-1099 | I |
| P1-6 | **`ReapplyEffectiveProfileToViewports` rewrites foreign/custom viewport schemes to high-pssm** (unknown scheme normalizes to default) and forces Glow on, contradicting the hook's own fail-open guard; runs on boot, ini reload and EXU request even on Redux. Linux-testable. | `ogre_render_profile.cpp` 2780-2791 vs 2380-2384 | H2 |
| P1-7 | **Cached `UseItem` skips the engine call but every `UnlockItem` forwards**, so the engine lock count can underflow. | `odf_item_hooks.cpp` 316-320 vs 408-428 | J |
| P1-8 | **SDK v2 `pollEvent`/`captureDeveloperSnapshot` copy `sizeof(struct)` into the caller's buffer ignoring `structSize`**, contradicting the append-only promise; add `static_assert`s on the ABI sizes (120/96) and honour the caller's size. | `openshim_sdk_v2.cpp` 73, 382 | J |
| P1-9 | **`FormatWithDecimals` casts to `long long`**; a mod CSV token with 19+ decimals is UB and is written back as a wrong value (reproduced). Reject rows with more than 15 decimals or verify round-trip before emitting. | `terrain_atlas_rect_repair.cpp` 112-115 | H1 |
| P1-10 | **Per-frame / per-object hot-path waste** (each independently measured by the reviewers): `handleSchemeNotFound` does string copies, a vector, three SEH calls and a log line before its negative-cache check (per renderable per frame); `_populateLightList` calls `GetModuleHandleA` per renderable; `ResolveExuCullingCallback` two `GetModuleHandleA` per unit per tick; AI `DoSubTask` path does ~3 `GetEnvironmentVariableA` per unit per tick; `SelectEngineFlameManager` `GetModuleHandleA` per craft per frame; `SyncSatelliteVisibility` 2-3 `VirtualQuery` per object per tick; `LookupHudSpriteId` rescans ~900 entries and logs on every miss; net `LogPacketActivity`/`LogRouteEvent` do ~4 syscalls and ~10 allocations per datagram before the sampling check even with logging off; FXAA retries a full `D3DCompile` x2 per Present on non-permanent failures; `ScanForPatterns`/`ResolveNamedAddress` copy every executable region per target (22 targets x up to 11 passes, 28 names). | see worksheets | B, C, D, E, G, H2 |
| P1-11 | **Worker threads that never idle**: pilot first-person trace polls at 25 ms for process lifetime even when the trace is off (its stated justification is false); profiler worker likewise at 40 Hz; `ResolveLocalFirstPersonEntity` (a production SDK export) enumerates the whole scene under a mutex per call. | `pilot_fp_animation_trace.cpp` 783-994, 1642-1693; `worker_api.inl` 54-148 | K |
| P1-12 | **CPU sampler walks frames bounded by `Esp+4MB` instead of the thread's TEB `StackBase`** (the header claims stack bounds are cached); a garbage EBP can consume another thread's guard page. Cache `NT_TIB::StackBase` per thread outside the suspend window. | `native_cpu_sampler.cpp` 376-383 | K |
| P1-13 | **D3D9 profiler hook re-runs `InstallD3D9DeviceHooks` (~1,500x per frame, each logging a Warn) when a foreign hook owns vtable[82]**; the DX11 twin handles this correctly. | `d3d9_hooks.inl` 50-97 | K |
| P1-14 | **`CopyStartupRendererResult` memcpy's `s_result` without `s_stateLock`** while the game thread publishes it; the plugin copies it exactly once at init assuming the seam already fired. | `startup_backend_seam.cpp` 212-221, 932-940; `ogre_render_profile.cpp` 2877-2899 | A |
| P1-15 | **Bootstrap `CreateFileA/W` wrappers build `std::filesystem::path` with no `try/catch`** and allocate 4-6 times per open; one allocation-free predicate fixes both. Same class: provider callbacks in `file_io_hooks.cpp` 887-954 invoked with no barrier; COM vtable hooks in `dx11_colorspace_diagnostic.cpp` and `ZoneConstructHook` can leak `bad_alloc` into the game. | `bootstrap_file_io.cpp` 158-191 | A, H1, J |
| P1-16 | **Shutdown joins ignore `WAIT_TIMEOUT`** (5 s in `dllmain.cpp`, 2 s in the plugin) then tear down while the thread may run; the loops already poll `g_ShutdownRequested`, so `INFINITE` is safe. | `dllmain.cpp` 113-121, `openshim_plugin.cpp` 195-201 | A |
| P1-17 | **`patch_registration_tests` scans only `patcher.cpp` and `bzr_hooks.cpp` for `ResolveNamedAddress`**, missing the three unresolvable names in `ui_performance_hooks.cpp`, and does not check the globals-to-`patches.h` direction (11 orphaned globals: Map Filters 1-8/8, Version Notice 1-3). Extend the test to all of `src/`. Linux-verifiable. | `tests/patch_registration_tests.cpp` 234-262 | B |
| P1-18 | **Uploader wrapper is fetched unpinned from `main` and unhashed** while the bundle itself is hash-verified; the `.ps1` wrapper (20260914) also lags the `.sh` one (20260920, coredump work). Ship `upload/openshim_wrap.*` inside the suite zip. | `scripts/install_windows.ps1`, `scripts/install_linux.sh` | L |
| P1-19 | **`Plugin_OpenShim.vcxproj` pins three files to C++14** (`ogre_animation_profiler.cpp`, `pilot_fp_animation_trace.cpp`, `walker_cockpit_trace.cpp`) inside a C++20 project; document why (Ogre header compatibility) or lift it. | `Plugin_OpenShim.vcxproj` 165-195 | (this doc) |

### P2: cleanup and maintainability

| ID | Item | Worksheet |
|----|------|-----------|
| P2-1 | Split `bzr_hooks.cpp` (section 7). | C, D, E, F |
| P2-2 | Concluded diagnostics to move to a diagnostics-only build or remove: `render_queue_trace.cpp` (question answered in `FOG_COMPOSITOR_QUALIFICATION_20260908.md`), the trace/manipulation half of `pilot_fp_animation_trace.cpp` (only the ~500-line resolver is production), the Ogre profiler proper once the chunk-shadow and DX11 skin-source-shadow policies move out of its TU, the scene-teardown Ogre detours the file itself documents never fire (17310-17433), the parked map-filter port (12 trampolines + `MapFilters6Rel32`, `Trampoline_VersionNotice`), `Prime*`/carrier-bias/artillery remnants (partly removed here; `ApplyWeaponMaskCarrierBiasForCraft` remains an empty function reached by two live patches and `g_ArtilleryDoAttackDetour` is reset in `ResolveBzrHooks` for a detour that is never installed). | D, F, K |
| P2-3 | Duplicated helpers to consolidate: WebSocket parser and ~8 helpers between `net_optimizer.cpp` and `bzrnet_instrumentation.cpp` (with divergent JSON escaping); `PatchComVtableEntry`/IAT walkers across 11 files; `MemoryRangeHasAccess`/`IsExecutableAddress` in three files; six copy-pasted bool-token parsers; `FindExportsContaining` x3, `TryGetRttiClassName` x2, four `IsTruthy` variants in the profiler TUs; duplicated headlight preset tables and ban/mute config loaders. | G, H1, H2, I, K |
| P2-4 | Diagnostics-framework API with no callers: `UiPerf::ScopedTransition`, `ScopedPhase::Annotate/Dismiss`, `EmitSummary`, `SetStallThresholdMs`, `Flush`, `LogVerbose`, `TicksToUs`, the `OnOgre*/OnModDiscovery/OnWorkshopScan/OnShellRequest/OnMultiplayerShutdown` header API and shell detour scaffolding in `ui_performance_hooks`; `scroll_helper.h` `ConsumeSavedScrollDelta`, `SelectHopFix3DeltaFromFrame`, `HopFix2_Helper`, `SelectHopFix2This`; `BzrNetTraceSocketGeneration`, `GetBzrNetCaptureId`, `IsBzrNetPrivateForensicTrace`; `FormatAssetStatusForLog`; `InstallProviderFromModule`; `DescribeEventType`, `GetInProcessEventStats`, `ResetInProcessEventQueue`; `TriggerAutoSaveNow`; `LegacyPassKindName`; sun-flash counters. Decide keep-as-API or delete; left in place here because several read as intentional surface. | G, I, J, K |
| P2-5 | INI keys read by code but undocumented in `openshim.ini.example`: `[Diagnostics] ChunkBatchReuse`, `ChunkBatchReuseObserve`, `HeadlightLightTrace`, `PilotFlashlightTrace`, `TraceMpAuth`/`TraceMpAuthDW`/`TraceMpAuthSPL`, `UiPerformanceAutoMatrix`; whole `[NativeUiDiagnostics]` section; env-only `OPENSHIM_LOG_OPTIONS_TREE`, `OPENSHIM_CAREER_TRACE`, `OPENSHIM_UI_PERFORMANCE_AUTOMATRIX`. | I |
| P2-6 | `winmm.dll` compiles `render_effect_intent.cpp`, `scene_depth_facts.cpp` and `dx11_enhanced_fxaa.rc` although no bootstrap source uses them (the FXAA code loads its RCDATA from `openshim.dll`); the architecture doc says 18 TUs / 6 shared, the project has 19 / 7. | A, L |
| P2-7 | Tests: `backend_selection_tests` and `ui_decor_tests` run in no CI lane; `ogre_profiler_algorithms_tests` is MSVC-script-only; 47 of 55 test files hand-roll the same `Check`/`Require` macros; `CMakeLists.txt` repeats the include/feature/warning triple ~45 times. Largest untested engine-independent sources: `openshim_sdk_provider.cpp`, `openshim_env_config.cpp`, `terrain_semantic.cpp`. | L |
| P2-8 | CI: `release.yml` skips `Test-EnhancedPssmV2` and duplicates ~70 lines of `build-win32.yml`; `bzrnet-instrumentation.yml` triggers on a branch that no longer exists; `README.md` line 181 still calls the DLL-only layout a supported install. | L |
| P2-9 | Hygiene left for a decision: `battlezone98redux.pdb` (38 MB) is tracked at the repository root and `AGENTS.md` describes it as a private leaked PDB; it should not be in a public repository. Not removed here because tooling scripts may reference it. | L |
| P2-10 | Low-severity items recorded in the worksheets and not repeated here: bare-name `LoadLibraryA("dbghelp.dll")` in the crash logger, `FORWARD` macro calling a null pointer when a real WinMM export is missing, 1200-byte command-line snapshot, `ReadInlineAsciiBufferRaw` writing `outBuffer[capacity]`, `_snprintf_s` -1 accumulation, `TryGetOgreModuleRange` latching failure before OgreMain loads, reorder path dropping >1500-byte datagrams, stale WSABUF pointers in pending-IO maps, `ShutdownBzrNetTrace` INFINITE wait, D3D11 deferred-context observers, `QuerySemanticBinding` spurious Warn, SharedPtr leak on `AddSharedReference` failure, sampler TID-reuse pin, unbounded CSV/sampler files, non-recursive shadow-script scan, `Join-Path` on undefined `ProgramFiles(x86)`. | A, C, G, H1, H2, K, L |

## 5. Hardening and build notes

- All three projects build at `/W4` with `/sdl`; none treat warnings as errors
  and none set `ControlFlowGuard` (correct for a shim that writes trampolines).
  `/DYNAMICBASE`, `/NXCOMPAT` and `/SAFESEH` rely on toolset defaults; pin them
  explicitly in the Release `Link` group so a toolset change cannot drop them.
- `ws2_32.dll` and `gdiplus.dll` stay delay-loaded in both DLLs, as
  `AGENTS.md` requires; all hooked Winsock exports resolve through
  `GetProcAddress`. Only `version.dll` changed (F4).
- The Linux test tree is warning-free under `-Wall -Wextra -Wshadow`; consider
  adding `-Wshadow` to the CMake targets that already use `-Werror`.

## 6. Dead code inventory

Removed in this PR (each verified as defined once, referenced nowhere, not
exported through `winmm.def`, not named in `patches.json`):

- `bzr_hooks.cpp`: `HudSpriteUvBlockMatches`, `TryProcessQueuedUpdatesSafe`,
  `TryGetChunkProxyNumAttachedObjectsSafe`, `TryGetChunkProxyAttachedObjectSafe`,
  `TrackCreateChunkTargetForProxy`, `LogPlayerConvergenceMountFault`,
  `LogPlayerConvergenceLayoutCrossCheck`, `IsBuildingStub`,
  `PrimeUnderAttackAlertConfig`, `PrimeTargetReticlePopupConfig`,
  `IsWeaponMaskCarrierBiasCraft`, `FindPreferredWeaponSlot`,
  `FindWeaponArrayIndexForSlot`, `RestoreCarrierState`,
  `MoveCarrierWeaponIndexToFront`, `SnapshotCarrierState`, `SwapCarrierBits`,
  `IsHowitzerCraft`, `CollectCarrierVolleyIndices`,
  `TraceArtilleryMaskFromProcess`, `TryPrepareArtilleryVolley`,
  `ArtilleryDoAttackHook`, `InstallArtilleryDoAttackHookIfPossible`,
  `ShouldTraceArtilleryMask`; structs `CarrierView`, `CarrierSnapshot`;
  constants `kLoadQueuedState`, `kMagnetMineClassSoundNameOffset`,
  `kMineOwnerOffset`, `kObjectClassOdfOffset`, `kObjectClassOdfLen`,
  `kGogGameObjectGetObjByHandleAddr` (two copies),
  `kGogResolveObj76GameObjectAddr`, `kBz15UiScale`,
  `kGogArtilleryDoAttackEntryAddr`, `kArtilleryDoAttackDetourLen`,
  `kWeaponMountWorldMatrixOffset`, `kWeaponMountInverseMatrixOffset`,
  `kGameObjectCarrierOffset`, `kGameObjectWeaponMaskOffset`,
  `kUnitProcessMeOffset`, `kWeaponIndexOffset`; flags
  `g_PlayerReticleConvergenceMountFaultLogged`,
  `g_PlayerReticleConvergenceLayoutCheckLogged`; a duplicate include of
  `native_ui_validation.h`.
- `bzr_hooks.h`: declarations for the three removed public functions.
- `patcher.cpp`: `ShouldEnableArtilleryMaskTracePatch`.
- `hook_engine.cpp/.h`: `ParseHexPattern`.
- `netcode_hooks.cpp` and `ApplyNetcodeHooks` (the header keeps the two buffer
  constants `net_optimizer.cpp` reads).
- `pilot_fp_animation_trace`: `IsPilotFpAnimationTraceRequested`;
  `ogre_animation_profiler`: `IsOgreAnimationProfilerRequested`.
- `bzr_options_ui.cpp`: `TrySetUiTexture`.
- `tests/openshim_preset_migration_tests.cpp`: `MakeBadR1LinesNoMarkerButBadValues`.

Remaining candidates (deliberately not removed here, see P2-2 and P2-4):
the reviewers' worksheets list them per subsystem. Pre-existing dead
constants in `bzr_hooks.cpp` that document reverse-engineered offsets
(`kGogDayWrecker*`, `kGogDistributed*`, `kGogOrdnance*`, `kCraftDeployState*`,
`kMinelayerVft*`, `kSatelliteMinZoomAddr`, `kFlagDisplayFlagIndexOffset`,
`kMultiplayerFlagMaxObjects`, `g_JumpSnipeProbeInstallAttempted`) should move
into `patches.json` `globals` or `bzr_object_layout.h` with provenance rather
than be deleted.

## 7. `bzr_hooks.cpp` split plan

The four section maps (worksheets C, D, E, F; about 170 rows in total) agree on
the shape. Extraction order that minimizes cross-references, each step a
separate PR with the Win32 build and `patch_registration_tests` as the gate:

1. **Spine first.** Keep `ResolveBzrHooks`, `RetryDeferredRuntimeHooks` and
   the render/sim tick dispatchers (39403, 40403) in `bzr_hooks.cpp`; split
   `ResolveBzrHooks` (1.2k lines) into reset / address table (to
   `patches.json`) / table-driven `Init*`.
2. **Chunk proxy and generic chunk batch renderer** (3521-9575, ~6,000 lines)
   plus the HUD sprite rect bridge, into `chunk_proxy_*.cpp` and
   `hud_sprite_rects.cpp`. The HUD rect table's UV-sample validation is the
   pattern every other fixed-VA read should copy.
3. **Lobby UI and GDI+ PNG generation** (40686-42775, ~2.1k lines), self-contained.
4. **Career stats** (9831-10230 and 12978-13760), **satellite fix**,
   **convergence**, **HUD/radar**, **turbo**, **unit VO**, **headlights**,
   **pilot flashlight**, **pilot team restore**, **BZRNet** (each a clean cut
   point per worksheet D).
5. **MPAUTH, chunk-create detours, vehicle skinning** (diagnostic) and the
   **legacy-1.4 AI / proximity-mine** experiments (incomplete) into
   `diagnostics/` and `experimental/` TUs so their status is visible from the
   tree.
6. **Frustum cull** `.inl` becomes a `.cpp` with a four-function header;
   **WMASK** and its retired neighbours move together.

All 18 non-static hooks in the 22000-33000 range are referenced only from this
file's installers and should become `static` as they move.

## 8. Scripts, tools and tests

Worksheet L carries a keep/remove/move table for every file under `scripts/`,
`tools/` and the repository root. Summary: the installers and `Deploy-OpenShim.ps1`
are the maintained surface; `deploy_linux_proton.sh` and
`launch_steam_chunk_force_geo.cmd` were pre-split leftovers (removed here);
several one-off capture scripts at the root (`buffer_logger_windows.ps1`,
`bzrnet_capture_windows.ps1`, `tester_diag_windows.ps1`) are referenced only by
closed investigations and are candidates to move under `reverse_engineering/`.

## 9. Patterns worth keeping

The reviewers independently called out the same practices; new code should
follow them:

- Whole-instruction byte guards before every detour, REL32 identity checks on
  call-site replacements, `[RESOLVE]` lines that echo the identity note.
- SEH frames that contain only POD and `noinline` cores; `try/catch` for the
  C++ side.
- Fail-closed platform gates (SHA-256 of exe + OgreMain for the terrain proxy,
  fixed-base GOG checks, `IsCompatibleGameVersion`).
- Fixed-capacity power-of-two tables with drop counters instead of hot-path
  allocation; budgeted logging; `thread_local` suppression flags.
- Module-relative paths with `LOAD_WITH_ALTERED_SEARCH_PATH`; append-only,
  `structSize`-guarded provider tables with an export drift test.
- Atomic temp-plus-rename file writes with backups; the lossless tested INI
  editor; the allocation-free crash logger and event ring.
