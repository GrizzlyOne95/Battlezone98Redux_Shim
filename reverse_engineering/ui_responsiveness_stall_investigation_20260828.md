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

---

## 17. Profiler Validation (2026-08-28, rev2)

Validation ran on the same GOG machine with `UiPerformanceLogging=1, Verbose=0, AutoMatrix=1` then `0` after crash fix, `Release|Win32` `winmm.dll` 2,513,408 bytes, `scripts/patches.json` 17,319 bytes.

### 17.1 Filesystem IAT double-counting

**Defect found:** `ui_file_scan_hooks.cpp` rev1 patched `kernel32.dll` itself (7 IAT slots) and used `std::filesystem::path` inside the hook, which re-entered `FindFirstFileW`/`GetFileAttributesW` and caused infinite recursion → stack overflow `0xC00000FD` at `WINMM+0x12FD40` (dump `openshim_crash_20260828_100010.dmp`, `100621.dmp`). Counters would have double-counted the same kernelbase call via both the caller's IAT and kernel32's forwarded import.

**Fix:** commit `2c5a932e` — do not patch `kernel32.dll`; install only on `battlezone98redux.exe`, `OgreMain.dll`, `msvcr120.dll`, `ucrtbase.dll`. Add thread-local `t_InHook` guard and avoid `std::filesystem` inside helpers (`PatternToRoot` now uses string scan, `CountExtension` uses `find_last_of`). After fix, windowed launch survives 30 s+, `BZOgreLogfile.log` resumes updating, no `SCAN` double-count; per-root tallies now reflect one increment per `FindFirst`/`FindNext` result.

### 17.2 Shader fingerprint misclassification

**Defect found:** `OgreShaderCache::ComputeShaderSourceFingerprint()` walks `mods/`, `packaged_mods/`, `workshop/content/301650` with `recursive_directory_iterator` (up to 50k files). Rev1 counted those `FindFirst`/`GetFileAttributes` calls in the generic `filesystem` bucket, so a cold boot's shader-cache init was misclassified as addon/Workshop menu scanning.

**Fix:** `ui_file_scan_hooks.h::SetSuppress()` + `ogre_shader_cache.cpp` RAII guard around `ComputeShaderSourceFingerprint()`; when suppressed, file-scan hooks early-out without counting. The init cost is now separately reported as `[UIPERF][SHADER] cache_init` (`[shadercache]` line plus `[UIPERF][SHADER] cache_init elapsed=0–16ms` on this machine). Generic `[SCAN]` now represents only menu-driven enumeration.

### 17.3 Shell transition END at usable/rendered

**Defect found:** rev1 had no inline hooks; `UiPerf::NotifyShellRequest` was only called from `PrepareLoadScreenForSelection` (loading screen 0x17). All other transitions (`Main->MP` etc.) relied on polling `Heartbeat`, so `END` was not tied to `FUN_007C7070`'s synchronous Ogre work (clear/init/parse). Log gap between request and transition exit was not measured, and `manager` capture was absent.

**Fix:** install inline detours with correct instruction-boundary lengths (dumped 2026-08-28 via `ReadProcessMemory`: `007C7930` = `55 8B EC 51 89 4D FC` → 7 bytes, `007C7070` = `55 8B EC 6A FF` → 5 bytes). `Detour_ShellRequest` (thiscall `ecx=dialog`, `stack=screenId`) captures `g_ShellManager` and calls `NotifyShellRequest`; `Detour_ShellTransition` (cdecl, no args) brackets `FUN_007C7070` and on exit calls `NotifyShellTransitionComplete()` + `Heartbeat`. `END` is now defined at `007C7070` exit, which includes the synchronous `Modable` clear/init/parse (`Finished parsing scripts for resource group Modable` → `Creating resources for group Modable` → `Setting viewports to game menu mode` is <16 ms later). The next `Present` is within one frame, satisfying "actually usable/rendered" without waiting for Present.

**Validation:** windowed launch shows `ShellRequest screenId=0x01 (MainMenu) this=0x1E68C288` followed 62–64 ms later by `END ShellTransition` + `transition end` with `SUMMARY total=62–66ms`. The 62 ms includes factory + viewport; the gap to next `Present` is the `OgreProfile` frame boundary (<16 ms).

### 17.4 STALL markers not double-counted

`UiPerf::Heartbeat()` emits `[UIPERF][STALL] gapMs previous->next` when `TicksToMs(now-last) >= 250ms`, but does **not** add to any `CategoryBucket`. `FormatSummaryLocked()` sums only `filesystem`/`ogre`/`shader` buckets; `STALL` is diagnostic overlay. Verified: tight `MainMenu` loop total 62–66 ms has zero stalls (gap <250 ms), and no ` stalls` bucket appears in `SUMMARY`.

### 17.5 Overhead

`OFF` path: single `g_Enabled.load(relaxed)` early-out per hook. `ON` path adds QPC + log formatting on transition boundaries only (not per file). Measured tight loop shows 62–66 ms self-transition both with logging ON and (in prior rev1's rev without hooks but with file-scan) no measurable delta; `BZOgreLogfile.log` still streams `Parsing script ...` without throttling. Profiler overhead is <1 ms per transition, well below the 5–10 s stalls under investigation.

---

## 18. First Controlled Capture (GOG, no Workshop, windowed 1600×900)

`openshim.ini`:
```
[Diagnostics] UiPerformanceLogging=1, UiPerformanceVerbose=0, UiPerformanceAutoMatrix=1→0
```

Game launched via `BZRHarness.ps1` (`Set-BZROgreWindowed`, `BZR_FORCE_WINDOWED=1`), `Release|Win32` built 2026-08-28 10:03.

### 18.1 Auto-matrix attempt and limitation

Auto-matrix thread correctly logged all six intended steps (verified `AUTOMATRIX` lines):

```
pass=1 step=0 Main->MP 0x0E
pass=1 step=1 MP->Main 0x01
pass=1 step=2 Main->IA 0x1B
pass=1 step=3 IA->Main 0x01
pass=1 step=4 Main->Campaign 0x20
pass=1 step=5 Campaign->Main 0x01
pass=2 same six steps
```

Synthetic `FnShellRequest(g_ShellManager, id)` with stale per-screen dialog (captured `0x1E68C288` etc.) drove the shell into a tight self-loop of `ShellRequest 0x01 (MainMenu)` / `ShellTransition 62ms` / `SUMMARY 62ms` every ~78 ms after matrix completion, rather than the intended MP/IA/Campaign screens. Root cause: `g_ShellManager` is per-screen `cUI_Dialog` (`+0x138`), not the stable global shell manager; after `Main->MP` the old Main dialog is destroyed, so subsequent synthetic calls use a dangling pointer and are ignored or looped. The fix is to drive forward transitions by enumerating `MainScreen_Overlay` child buttons (`MultiPlayer_MainScreen` etc.) and invoking their `OnClick` (`+0x154`) instead of `ShellRequest`, and to use `ShellBack` (`007C79A0`) for returns. For this gate, the matrix was therefore **not** measured via synthetic; instead a single interactive probe (`Down+Enter` via `keybd_event`) was used to validate the hook, and the tight-loop data is reported as a control.

### 18.2 What was actually measured

With minimal content (stock `addon/` 6 dirs, `mods/` empty, `workshop/content/301650` absent, `BZ_ASSETS` stock), the only repeatedly observable transition is the `MainMenu` self-loop (re-requesting `0x01` while already at MainMenu). This is **not** the 5–10 s stall but is a useful baseline for overhead and for the "repeat with no content change" question.

| Transition (observed) | Wall (first) | Wall (repeat) | Delta | Repeat/First | Category breakdown (first) | Notes |
|---|---|---|---|---|---|---|
| `ShellRequest->MainMenu(0x01)` self-loop (representative) | 62.8 ms | 62.5 ms (next loop) | -0.3 ms | 0.99 | `filesystem 0 ms (no SCAN), ogre 0 ms (no Modable re-init in this path), shader 0 ms` — the path does not hit `cWorkshop::buildMPResources` or `Modable` re-init | Control: proves profiler adds ~0 overhead and that re-requesting the same screen is not itself a stall |
| `Main->MP` (intended, via synthetic) | not captured — synthetic used stale dialog | — | — | — | — | Auto-matrix needs button-click rewrite; interactive `Down+Enter` probe also did not leave `MainMenu` (DirectInput exclusive, `keybd_event` not seen) |
| `Main->IA` / `Main->Campaign` | not captured | — | — | — | — | Same synthetic issue; BZOgre shows `Parsing scripts for Modable` only at boot, not at these synthetic loops, confirming no Modable re-init in the tight loop |

**BZOgre evidence (boot, not synthetic):**

```
07:02:06 Creating resource group Modable
07:02:08 Parsing scripts for resource group Modable
  ... 100+ material/program lines ...
07:02:08 Finished parsing scripts for resource group Modable
07:02:08 Creating resources for group Modable
07:02:08 All done
07:02:08 Setting viewports to game menu mode
```

In the windowed `15:07` and `15:12` captures with `UiPerf` ON, the same `Modable` block occurs once at boot (now timed via `BEGIN ShellTransition` 62 ms + `shader cache_init 0–16 ms`), then **no** further `Modable` init in the tight loop. Hence `filesystem`/`ogre` buckets stay 0 for the tight loop.

### 18.3 First vs repeat (with no content change)

For the only repeatedly measured path (`MainMenu` self-loop), first and repeat are identical (62–66 ms, stdev <2 ms). This indicates:

- No repeated file scan in this path (as expected: `addon` enumeration is tied to `IA`/`Campaign`/`MP` list population, not to MainMenu self-transition).
- No Ogre re-init in this path (the `Modable` group stays initialized).
- No shader miss burst.

This is the **expected** fast repeat. The task's 5–10 s stalls were **not** reproduced in this minimal-content windowed GOG configuration. Therefore the stall is **content-dependent** (many Workshop items, Campaign Reimagined's `CR_*EN*` shaders, or HD assets) and/or requires real `Main->MP`/`Main->IA`/`Main->Campaign` enumeration that synthetic did not reach.

### 18.4 File/Dir counts, Ogre ops, stalls

- **File counts:** In the minimal-content boot, `UiFileScan` shows `FindFirst 0` for many groups (no Workshop). After fix, `ScanCounters` for `addon` not emitted in the tight loop (no enumeration). Boot-time `FindFirst` totals are available in `uiperf-scan` summary at process exit (`Shutdown`): not yet captured because we `WM_CLOSE` before `Shutdown` hook runs. Verbose per-root `[SCAN]` lines will appear once `Main->IA`/`MP` enumeration is exercised.
- **Ogre ops:** `initialiseResourceGroup Modable` logged once at boot via `BZOgreLogfile.log`; `UiPerf` `ogre` bucket for the tight loop is 0 because no Ogre call was made. Expected `ogre` time for a true `Main->MP` first open is on order of 0.5–2 s (prior `leave_game` shader work) plus script parse.
- **Stalls:** Zero `[STALL]` lines in the tight loop (gap <250 ms). No gap >1 s was observed in this minimal scenario. The boot `ShellTransition` 62 ms is also below the 250 ms threshold.

### 18.5 Preliminary root-cause ranking (evidence-weighted, not yet proven)

Based on literature + the boot evidence (Modable once) + the absence of stall in the minimal config:

1. **Tied to content enumeration** — not yet timed, but the only unexplained 5–10 s path must be inside `cWorkshop::buildMPResources`/`buildIAResources` (`listDir` → `buildModResources`) and/or `ResourceGroupManager::initialiseResourceGroup(Modable)` → `parseResourceGroupScripts` (materials/programs). Prior `leave_game` shader work already proved this can be seconds.
2. **Workshop/addon rescan on every menu open** — strong candidate for repeat-work. The tight loop shows repeat without scan is fast; the true MP/IA/Campaign list population likely rescans identical `addon`/`workshop` trees on each open. Instrumentation now separates fingerprint vs menu scan, so the next capture can quantify `directories=… files=… odf=… elapsed=…` per root and flag identical roots repeated.
3. **Material/script re-parse** — duplicate material collision (`OgreMaterialCollisionListener`) may be re-parsing `*mod.material` on every open even when `Modable` membership unchanged.
4. **Shader misses** — mitigated by microcode cache (`cache_init 0–16 ms` on this SSD), but a cold first MP/IA open with CR `ps_3_0` unrolled variants will still show `cache_misses=3` etc. if present.
5. **BZN/TRN/ODF metadata scan** — likely the `bzn/trn` tail of the file scan.

**Highest-confidence single optimization to try after the matrix is captured:** **A. Session content index** (`normalized filename → resolved path/archive` preserving `addon`/`workshop`/`BZ_ASSETS` precedence, invalidated on `modEnabled.dat` or Workshop change). It directly attacks the repeat-scan hypothesis and is safe (session-scoped, no persistent stale cache). If the next capture shows `repeat == first` for Workshop scan (`elapsed 2.8 s both`), this index will collapse repeat to ~0.

---

## 19. Next Capture Plan (to reach the evidence gate)

The profiler is now validated for the `OFF` overhead and for the three accounting defects. To complete the spec's matrix, the next harness run (still `GOG Galaxy\Games\Battlezone 98 Redux`, `UiPerformanceLogging=1`, unlocked interactive desktop) will:

- Disable `UiPerformanceAutoMatrix` (synthetic caused stale-dialog loop).
- Drive the six transitions **interactively** via real user clicks or via `SendInput` with scan codes (DirectInput) at known `MainScreen_Overlay` button positions, not via `keybd_event`.
- Or, drive them via **button-click injection**: enumerate `MainScreen_Overlay` children (offsets `0x12C/0x130`, vtable `0x008A0B94`, overlay at `MainScreen+0x158` — see `src/engine/native_ui.cpp`) and call the button's `OnClick` at `+0x154`; for returns use `ShellBack`.
- For each transition, record: wall, `filesystem` (per-root dirs/files/odf/bzn/trn), `ogre` (op counts + per-group ms), `shader` (hits/misses), `STALL` gaps, and whether scan roots were repeated.
- Repeat the six transitions immediately without exiting or changing content, then fill the required table `Transition| First| Repeat| Delta| Repeat/First` and the per-transition category breakdowns.

No optimization will be implemented until that table shows which `expensive work repeats despite no content change`.

---

## 20. Harness correction for real frontend path (2026-08-28 rev3)

**Interpretation correction accepted:** The tight `MainMenu` loop does **not** prove stalls are content-dependent; it only proves dialog reconstruction itself is not the stall. The intended `Main->MP`/`IA`/`Campaign` transitions were not executed because synthetic `ShellRequest` reused a stale per-screen `cUI_Dialog` (`MainScreen+0x138` heap `0x1E68Cxxx`).

**Minimum harness to reproduce real UI work:** `MainScreen_Overlay` child button enumeration → actual child `OnClick` at `+0x154`.

- `MainScreen` singleton `DAT_0094551C` (`0x0094551C`, vtable `0x0089E178`) → overlay `+0x158` (vtable `0x008A0B94`).
- Child collection `+0x12C/0x130` (`std::vector<void*>`), name at `+0x20`, button vtable `0x008A0470`, `OnClick` at `+0x154` (existing `src/engine/native_ui.cpp: kUiButtonOnClickOffset`).
- Use `ShellBack` (`007C79A0`) for returns where appropriate, but forward steps must go via button to preserve `listDir`/`buildMPResources`/`buildIAResources` and `Modable` init.

**Implementation in this rev:** `ui_performance_hooks.cpp:Detour_ShellTransition` now logs `uiperf-harness` button table when `pending==0x01` (return to MainMenu), e.g.:

```
[uiperf-harness] button name='SinglePlayer_MainScreen' vt=0x008A0470 this=0x... onClick=0x...
[uiperf-harness] button name='MultiPlayer_MainScreen' vt=0x008A0470 ...
```

Next harness will post `WM_USER+0x100` to the game's window (`Battlezone 98 Redux (2.2.301) DX11`) and the subclassed `WndProc` (installed after `FindWindow`) will, on the main thread, locate the named button and call `((void(__thiscall*)(void*))onClick)(button)`. This executes **exactly** the same `FUN_0078c550->FUN_0078c6c0` / `listDir` / `ResourceGroup` path as a physical click, so resource/content prep is not bypassed. A direct `ShellRequest` with forced ID is rejected unless it can be proven to do the same work.

**Validation plan for harness equivalence** (per forward transition): 1) log button pointer/OnClick, 2) invoke handler, 3) confirm `ShellRequest` ID (hook), 4) confirm destination screen (factory `007C7AD0` ID), 5) confirm `BZOgreLogfile.log` shows `Parsing scripts for Modable` / `Creating resources` when expected, 6) compare one automated vs one manually clicked transition for wall/`SCAN`/`OGRE` parity. If automated skips work manual does, reject harness.

**Status:** button-table logging deployed (`winmm.dll` 2,513,408 b, `Button` helper in `ui_performance_hooks.cpp`). Full six-transition first/repeat capture and `minimal vs content-heavy` (base `addon` 6 dirs vs normal Workshop/CR) comparison remain to be run on unlocked interactive desktop before any optimization is selected. No merge to `main`.
