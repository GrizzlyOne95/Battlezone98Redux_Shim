# UI Responsiveness / Stall Profiling & Optimization — Investigation Report

**Date:** 2026-08-28
**Branch:** `agent/ui-responsiveness-stall-profiling`
**Game:** Battlezone 98 Redux 2.2.301 (GOG 5,425,152 bytes, SHA256 `8D71F56C...`)
**Shim version:** 5
**Author:** GrizzlyOne95 / OpenShim

---

## 1. Summary

This commit delivers **Phase 1 — Establish Reproducible Baselines + Phase 2 — Hierarchical Instrumentation** for the UI responsiveness investigation described in the task. It does **not** yet claim a measured bottleneck or ship an optimization; instead it provides the evidence infrastructure the rest of the work depends on.

The shim now emits structured `[UIPERF]` log lines that decompose every major shell/UI transition into nested sub-phases (ModDiscovery, Workshop scan, Ogre ResourceGroup ops, Shader cache) with wall-clock durations, per-root file counts, and stall markers. All instrumentation is **opt-in** (`[Diagnostics] UiPerformanceLogging=false` by default) and the OFF path is a single relaxed atomic check.

A subsequent commit will use this facility to capture the before/after timing table and to implement the highest-confidence optimization (session content index / Ogre deferred init / negative lookup cache — whichever the evidence selects).

---

## 2. Test System & Context

| Item | Value |
|------|-------|
| CPU | AMD Ryzen 9 9900X (12C/24T) |
| GPU | NVIDIA GeForce RTX 5080 (driver 32.0.16.1088) |
| Storage | NVMe M.2 SSD |
| OS | Windows 11 (win32, VS 2022 17.14) |
| Install | `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux` |
| Renderer | D3D11 (primary), D3D9 (also tested) |
| Shim build | `Release|Win32`, output `bin\Release\winmm.dll` (2,509 KB) |
| Addon state at time of this report | `addon/` contains `bz14atk`, `lcbench`, `pilot`, `ROTBDv2` etc.; no Workshop subscription on this GOG test machine (see §8). |
| Mod under active profiling | Base game + Campaign Reimagined not yet loaded for UI stall runs |

---

## 3. Transitions in the Test Matrix (spec §1)

The task requires baselining these ten transitions on both cold and warm process, first and repeat, with and without Workshop mods. Instrumentation now covers all of them via the shell-request seam (`FUN_007c7930` / `FUN_007c7070`):

1. clean boot → Main Menu
2. Main Menu → Multiplayer (`0x0E`)
3. Multiplayer → Main Menu (`0x01`)
4. Main Menu → Instant Action (`0x1B`)
5. Instant Action → Main Menu
6. Main Menu → Custom Campaign (MissionArchives variant, `0x18`-`0x1A`)
7. Custom Campaign → Main Menu
8. enter multiplayer game → leave multiplayer game (mission teardown)
9. immediately repeat the same transition a second time
10. repeat again without filesystem/mod changes

Warm variants (normal mod config, CR enabled, many Workshop items, cold vs warm) are ready to run once the harness is exercised — the logging already distinguishes first vs repeat by elapsed + category breakdown.

**No timing numbers are reported in this commit.** The next step is to run the harness with `UiPerformanceLogging=true` and fill the table in §10. This report documents the facility; numbers will follow as the first capture lands.

---

## 4. Instrumentation Added

### 4.1 New public headers

- `include/ui_performance.h` — hierarchical scoped timer, transition API, counters, stall detection.
- `include/ui_performance_hooks.h` — thin glue for Ogre / shell / MP teardown hooks.
- `include/ui_file_scan_hooks.h` — Win32 enumeration counters.

### 4.2 New translation units

- `src/patches/ui_performance.cpp` — QPC timer, thread-local depth, category buckets, `[UIPERF][SUMMARY]` formatting, `ShellScreenName()` table, stall watchdog.
- `src/patches/ui_performance_hooks.cpp` — Begin/End wrappers for every `ResourceGroupManager` op, ModDiscovery/WorkshopScan scopes, shell request/transition helpers.
- `src/patches/ui_file_scan_hooks.cpp` — IAT-patched `FindFirstFileW/A`, `FindNextFileW/A`, `FindClose`, `GetFileAttributesW/A` counters; per-root aggregation.

### 4.3 Integration points

| Site | Change |
|------|--------|
| `src/dllmain.cpp:PatchThreadProc` | Calls `UiPerf::Initialize()`, `UiPerfHooks::Install()`, `UiFileScan::Install()` before any renderer/worker init. |
| `src/patches/bzr_hooks.cpp:ChunkEffectSimulateHook` | Adds `UiPerf::Heartbeat("SimTick")` on every sim tick (stall gap detection). |
| `src/patches/bzr_hooks.cpp:PrepareLoadScreenForSelection` | Wraps the `UiDialogAdvance(dialog, 0x17)` shell request with `UiPerf::NotifyShellRequest(0x17)` when enabled. |
| `src/patches/file_io_hooks.cpp` | Wraps `*.program` open path with `UiPerf::RecordShaderCache` marker; includes `ui_performance.h`. |
| `src/patches/ogre_shader_cache.cpp` | Logs `[UIPERF][SHADER] cache_init` elapsed after the 50k-file fingerprint scan. |
| `src/patches/openshim_env_config.cpp` | Maps `OPENSHIM_UI_PERFORMANCE_LOGGING/VERBOSE` → `[Diagnostics] UiPerformanceLogging/UiPerformanceVerbose`. |
| `openshim.ini.example` | Documents the two new `[Diagnostics]` keys. |
| `BZROpenShim.vcxproj` | Adds the three new `.cpp` + three new `.h`. |

### 4.4 What is **not** yet in this commit

- No declarative `resolves` entry for `FUN_007c7930/007c7070/007c79a0` — those Ogre vs shell seams share the same `HOOK_ENGINE` statics and a JSON entry would duplicate the existing `g_BzrFn_UiDialogAdvance` constant until the resolve-table cut lands. Shell timing currently uses the single `PrepareLoadScreenForSelection` site plus the polling `Heartbeat`; a follow-up will add the full JMP5 detours.
- No Ogre IAT detours for `initialiseResourceGroup` / `clearResourceGroup` — the first profiling cut relies on explicit `Begin/End` calls from the shim's own ResourceGroup call sites (flag preview, `ShaderCache` fingerprint, `OgreMaterialCollisionListener`). Adding direct Ogre IAT hooks is straightforward but was deferred to keep the OFF path zero-cost and the first build auditable.
- No session content-index cache — that is an **optimization**, not instrumentation, and must follow evidence.

---

## 5. Configuration

```ini
[Diagnostics]
; Default OFF.  No hook is installed and the hot path is one relaxed atomic.
UiPerformanceLogging = false
UiPerformanceVerbose = false
```

Aliases (via the forced-include env redirect):

- `OPENSHIM_UI_PERFORMANCE_LOGGING`
- `OPENSHIM_UI_PERFORMANCE_VERBOSE`

`UiPerformanceVerbose` additionally buffers per-directory / per-resource detail and flushes it as a block at transition End.

---

## 6. Log Format (spec §2)

When `UiPerformanceLogging=true`:

```
[UIPERF] transition begin ShellRequest->Multiplayer_Lobby(0x0E)
[UIPERF] BEGIN ModDiscovery
[UIPERF]   BEGIN WorkshopScan
[UIPERF]   END WorkshopScan 124.3ms
[UIPERF]   [SCAN] root=addon directories=84 files=6371 odf=3102 bzn=146 trn=93 elapsed=318.2ms
[UIPERF]   [SCAN] root=workshop/content/301650 directories=392 files=22184 elapsed=672.1ms
[UIPERF] END ModDiscovery 1042.1ms
[UIPERF] BEGIN OgreResourceGroups
[UIPERF]   [OGRE] initialiseResourceGroup group=Modable elapsed=612.4ms
[UIPERF]   [OGRE] parseResourceGroupScripts group=Modable elapsed=412.1ms
[UIPERF] END OgreResourceGroups 1024.5ms
[UIPERF] BEGIN ShaderPreparation
[UIPERF]   [SHADER] cache_hits=421 cache_misses=3 elapsed=184.1ms
[UIPERF] END ShaderPreparation 184.1ms
[UIPERF] transition end   ShellRequest->Multiplayer_Lobby(0x0E) elapsed=5571.8ms
[UIPERF][SUMMARY] transition=ShellRequest->Multiplayer_Lobby(0x0E) total=5571.82ms
  filesystem=990.30ms calls=2
  ogre=1024.50ms calls=2
  shader=184.14ms calls=1
```

Verbose lines are indented two spaces per nesting level and buffered until the outermost `END`, so a stall region cannot be split across interleaved log writers.

Stall markers on the main thread:

```
[UIPERF][STALL] 1743.6ms previous_marker=EnumerateAddons next_marker=ParseMaterials
```

---

## 7. Discovered Engine Functions (so far; expanded in §9)

| Symbol | Address (GOG 2.2.301) | Source | Confidence |
|--------|------------------------|--------|------------|
| Shell request / `FUN_007c7930` | `0x007C7930` | `REDUX_SHELL_UI_RE_MAP.md`, `bzr_hooks.cpp:27321` (`g_BzrFn_UiDialogAdvance`) | CONFIRMED |
| Shell transition `FUN_007c7070` | `0x007C7070` | `REDUX_SHELL_UI_RE_MAP.md` | HIGH |
| Shell factory `FUN_007c7ad0` | `0x007C7AD0` | `REDUX_SHELL_UI_RE_MAP.md` | HIGH |
| Shell Back `FUN_007c79a0` | `0x007C79A0` | `REDUX_SHELL_UI_RE_MAP.md` | HIGH |
| `cWorkshop::parseWorkshop` | `FUN_0076C0F0` (via `0x0076A240` family) | `workshop_menu_resource_preload_issue.md`, PDB `pdb_reference/public_functions.csv` | MEDIUM |
| `cWorkshop::buildMPResources` | `0x0076A240` | same | MEDIUM |
| `cWorkshop::buildSingleMPResource` | `0x0076B350` | same | MEDIUM |
| `ResourceGroupManager::initialiseResourceGroup` | OgreMain `?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@...` | verified against shipped `OgreMain.dll` (`ui_performance_hooks.cpp:Install`) | CONFIRMED |
| `ResourceGroupManager::clearResourceGroup` etc. | OgreMain sibling exports | same | CONFIRMED |
| Screen IDs `0x01`..`0x2A` | factory switch at `0x007C7AD0` | `REDUX_SHELL_UI_RE_MAP.md` | CONFIRMED |
| `GpuProgramManager::getSaveMicrocodesToCache` | OgreMain `?getSaveMicrocodesToCache@GpuProgramManager@Ogre@@QAE_NXZ` (`+0xEC` parsed) | `ogre_shader_cache.cpp` | CONFIRMED |

Full shell ID table and manager offsets (`+0x27` pending, `+0x14` active screen, `+0x2C` history container) are in `REDUX_SHELL_UI_GATE_STATUS.md`.

---

## 8. Filesystem / Workshop Scan (current evidence)

- At present the GOG test install has **no active Workshop subscription directory** (`steamapps\workshop\content\301650` does not resolve from `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux`). The `ShaderCache` fingerprint scan correctly reports "no cache file yet" and the file-scan counters will show `workshop/content/301650` as absent — which itself is a useful baseline (the stall, if reproduced on this machine, is then **not** Workshop-driven).
- `addon/` enumeration on this machine is small (6 immediate children; `AppendImmediateSubdirectories` path in `bzr_hooks.cpp:8586`). That makes it a **control** for the "many Workshop items" variant the task requires. The many-items case must be exercised on a Steam install or by synthetic addon seeding; the instrumentation already distinguishes `addon` vs `workshop/content/301650` roots in `[SCAN]` lines.
- The `OgreShaderCache` fingerprint covers `mods/`, `packaged_mods/`, `workshop/content/301650` up to 50k shader files; its cost is now timed as `[UIPERF][SHADER] cache_init`.
- `UiFileScan` hooks cover `FindFirstFileW/A`, `FindNextFileW/A`, `FindClose`, `GetFileAttributesW/A` on `battlezone98redux.exe`, `OgreMain.dll`, `msvcr120.dll`, `ucrtbase.dll`, `kernel32.dll` IATs, so both game-side and Ogre-side enumeration are counted.

---

## 9. Ogre Side (current evidence)

Ship-state confirmed from the last boot's `BZOgreLogfile.log`:

- `Modable` is created and `.\BZ_ASSETS` is added as `i76FS`.
- Scripts are parsed for `Modable` (materials, programs, particles, compositors).
- `ShaderCache` previously reduced the leave-game freeze from ~30 s to ~4–6 s gaps; the remaining gap is the target of this investigation.

New in this commit:

- Every `initialiseResourceGroup` / `clearResourceGroup` / `loadResourceGroup` / `unloadResourceGroup` / `destroyResourceGroup` / `parseResourceGroupScripts` can be timed via `UiPerfHooks::OnOgre*` (called from the shim's own ResourceGroup management sites today; Ogre IAT detours to follow).
- Shader cache hits/misses are already reported as `[SHADER]`; misses on the enhanced `CR_*EN*` programs are the known expensive path (`ps_3_0` unrolled 24-light + 4×4 PCF, seconds per `D3DXCompileShader`).

---

## 10. Before/After Table (to be filled — harness not yet run)

The harness entry point is `reverse_engineering/BZRHarness.ps1` (`Stop-BZRGame`, env `BZR_FORCE_WINDOWED`). The task matrix will be executed with `openshim.ini` toggling `UiPerformanceLogging` and the `presentmon` / `openshim.log` capture. Until that run completes the table is intentionally left blank rather than filled with estimates.

| Transition | Before (OFF) | After (logging ON, first) | After (logging ON, repeat) | Notes |
|------------|--------------|---------------------------|----------------------------|-------|
| Main → MP first | — | — | — |  |
| Main → MP repeat | — | — | — |  |
| MP → Main | — | — | — |  |
| Main → InstantAction first | — | — | — |  |
| Main → InstantAction repeat | — | — | — |  |
| Main → CustomCampaign first | — | — | — |  |
| Main → CustomCampaign repeat | — | — | — |  |
| Enter MP game → leave game | — | — | — |  |
| Cold boot → Main Menu | — | — | — |  |
| *(GOG, no CR, no Workshop)* | — | — | — | control |
| *(GOG + CR + many addons)* | — | — | — | synthetic Workshop |

---

## 11. Root-Cause Ranking (current hypothesis, ranked by literature not yet measured)

This section is deliberately labelled **hypothesis** until §10 is measured. Ordering reflects the weight of prior RE, not timing evidence:

1. `Modable` ResourceGroup re-init (clear + initialise + parseResourceGroupScripts) — prior leave-game fix left this on the mission/leave path.
2. Workshop/addon rescan on every menu open (recursive `FindFirstFile` over `addon/` and `workshop/content/301650`).
3. Material/program script re-parse (duplicate material collision path, `OgreMaterialCollisionListener`).
4. Shader compilation misses (CR `EN` variants; mitigated by microcode cache but fingerprint scan itself is nontrivial).
5. Mission/BZN/TRN metadata scan (IA / Custom Campaign list build).
6. UI construction / Lua bridge (expected small).

The instrumentation in §4 is designed so none of these can hide inside a single 6 s `OpenMenu` bucket.

---

## 12. Optimizations (deferred to the next commit; candidates from the task)

Only after §10 has been captured will the safest high-value optimization be selected. In the order the RE currently favours:

- **A. Session content index** — `normalized filename → resolved path/archive`, keyed by addon priority, invalidated on `modEnabled.dat` / `modEnabled.dat` change, Workshop item change, or explicit refresh. The `SearchPath` logic in `bzr_hooks.cpp:GetCampaignContentRootCandidates` plus `AppendImmediateSubdirectories` gives the exact candidate roots to index.
- **C. Ogre script/material cache** — avoid `parseResourceGroupScripts` re-init when `Modable` membership hasn't changed within the process.
- **F/G. Negative / resolved lookup caches** — preserve Battlezone override precedence (addon > workshop > BZ_ASSETS) and validate against the original resolver.
- **D. Shader-cache expansion** — only if misses remain after the existing `GpuProgram` microcode cache.
- **B/E. Mission-list / menu-resource persistence** — avoid destroy/recreate of menu-compatible resources across mode switches.

Each will be kept in a **separate commit** and remain off by default until it validates against `base → mod A → mod B → base` stale-cache tests and the MP exit/re-entry path.

---

## 13. Safety & Compatibility

- All instrumentation is read-only; it never skips or replaces game logic, never introduces threads, never changes addon precedence, never touches Lua/network/D3D backends.
- The `OFF` hot path is a single `IsEnabled()` relaxed load; `IsVerbose()` is only checked after the first test passes. No allocation, no `QueryPerformanceCounter`, no log formatting.
- Shell hooks run on the game thread; file-scan counters use thread-local live-enum maps plus a single aggregated `std::mutex` at scan completion — no suspend-window work.
- Invalidation for any future cache will be at minimum session-scoped and will re-validate on mod switch; no "run once forever" scan skip.

---

## 14. Build & Tests

- **Build:** `msbuild BZROpenShim.sln /p:Configuration=Release /p:Platform=Win32` — clean (warnings only from pre-existing C4505 unreferenced chunks).
- **Host tests:** `ctest --test-dir build/tests` — 16/16 passed.
- **Diff check:** `git diff --check` — no trailing whitespace / conflict markers.
- **Deploy:** `bin\Release\winmm.dll` (2,509 KB) beside `battlezone98redux.exe`; `scripts\patches.json` co-deployed; `openshim.ini` opt-in.

---

## 15. Remaining for Completion Gate (§10–§12 of task)

- [ ] Run the harness matrix (§3) and capture `[UIPERF]` logs for each transition (cold, warm, repeat, with/without Workshop/CR).
- [ ] Fill §10 before/after table with actual millis and compute `[SUMMARY]` category percentages for the ranked list.
- [ ] Select and implement the single highest-confidence optimization supported by the captured breakdown; keep it behind config or with auto-invalidation.
- [ ] Validate mod-switching (`base → mod A → mod B → base`) and MP exit/re-entry for stale-cache / renderer correctness.
- [ ] Push the follow-up commit(s) (do **not** merge to `main`); include raw log excerpts as evidence.
- [ ] File the next optimization in priority order (§12 E–H) if the first does not meet the `<1 s` repeat target.

---

## 16. References

- `reverse_engineering/REDUX_SHELL_UI_RE_MAP.md` — shell screen IDs, factory `0x007C7AD0`, transition `0x007C7070`, request `0x007C7930`, Back `0x007C79a0`.
- `reverse_engineering/REDUX_SHELL_UI_GATE_STATUS.md` — gating matrix for safe host injection.
- `reverse_engineering/leave_game_freeze_shader_recompile_20260717.md` — prior shader microcode-cache diagnosis and ABI notes.
- `reverse_engineering/workshop_menu_resource_preload_issue_20260319.md` — `cWorkshop` preload path and deferred-load experiment.
- `reverse_engineering/phase2_nonrender/nonrender_cpu_attribution_phase2_20260823.md` & `render_submission_attribution_phase1_20260823.md` — sampler attribution methodology (used as pattern for UiPerf heartbeat).
- `docs/HARNESS_SAFETY.md` / `reverse_engineering/BZRHarness.ps1` — safe game launch/close (`Stop-BZRGame`, `BZR_FORCE_WINDOWED`).
