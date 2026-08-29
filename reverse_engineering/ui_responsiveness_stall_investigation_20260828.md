# UI Responsiveness / Stall Profiling & Optimization — Investigation Report

**Date:** 2026-08-28
**Branch:** `agent/ui-responsiveness-stall-profiling`
**Game:** Battlezone 98 Redux 2.2.301 (GOG 5,425,152 bytes, SHA256 `8D71F56C...`)
**Shim version:** 5
**Author:** GrizzlyOne95 / OpenShim

---

## 1. Summary

This report began as the **Phase 1 — Establish Reproducible Baselines + Phase 2 — Hierarchical Instrumentation** handoff. Sections 1–20 preserve that chronology; **§21 is the current evidence checkpoint** and supersedes earlier statements that the real frontend routes had not yet been reached. No optimization has been implemented or selected.

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

- All instrumentation is read-only; it never skips or replaces game logic, changes addon precedence, or touches Lua/network/D3D backends. Rev4 adds one opt-in, low-frequency trigger-detection helper thread; it never accesses Battlezone UI objects and only posts a private window message to the main thread (see §21.1).
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

**Fix:** install inline detours with correct instruction-boundary lengths (dumped 2026-08-28 via `ReadProcessMemory`: `007C7930` = `55 8B EC 51 89 4D FC` → 7 bytes, `007C7070` = `55 8B EC 6A FF` → 5 bytes). `Detour_ShellRequest` (thiscall `ecx=dialog`, `stack=screenId`) captures `g_ShellManager` and calls `NotifyShellRequest`; `Detour_ShellTransition` brackets `FUN_007C7070` and on exit calls `NotifyShellTransitionComplete()` + `Heartbeat`. Later static/runtime qualification corrected the transition ABI to `int __cdecl(int* dialog, int mode)`; callers clean eight stack bytes and EAX must be preserved. `END` is now defined at `007C7070` exit, which includes the synchronous `Modable` clear/init/parse (`Finished parsing scripts for resource group Modable` → `Creating resources for group Modable` → `Setting viewports to game menu mode` is <16 ms later). The next `Present` is within one frame, satisfying "actually usable/rendered" without waiting for Present.

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

The implemented harness posts a private window message to the game's window (`Battlezone 98 Redux (2.2.301) DX11`). The subclassed `WndProc`, on the game/main thread, locates the named button and invokes its stored callback. Runtime RE corrected the callback receiver: the `OnClick` slot contains a member thunk that expects the **live owning screen** in ECX, not the button. Back callbacks read `owner+0x138` to reach the shell manager. Passing the button is therefore not behaviorally equivalent and is rejected. A direct `ShellRequest` with a forced ID remains rejected for forward routes because it can bypass screen-specific content/resource preparation.

**Validation plan for harness equivalence** (per forward transition): 1) log button pointer/OnClick, 2) invoke handler, 3) confirm `ShellRequest` ID (hook), 4) confirm destination screen (factory `007C7AD0` ID), 5) confirm `BZOgreLogfile.log` shows `Parsing scripts for Modable` / `Creating resources` when expected, 6) compare one automated vs one manually clicked transition for wall/`SCAN`/`OGRE` parity. If automated skips work manual does, reject harness.

**Status:** button-table logging deployed (`winmm.dll` 2,513,408 b, `Button` helper in `ui_performance_hooks.cpp`). Full six-transition first/repeat capture and `minimal vs content-heavy` (base `addon` 6 dirs vs normal Workshop/CR) comparison remain to be run on unlocked interactive desktop before any optimization is selected. No merge to `main`.

---

## 21. Harness completion and real-route evidence checkpoint (2026-08-28 rev4)

This section records the current state through commit `f89182d4`. It supersedes the provisional harness and timing conclusions above. The code is pushed on `agent/ui-responsiveness-stall-profiling`; it has not been merged to `main`, and no menu-performance optimization has been implemented.

### 21.1 Idle trigger delivery: implemented and runtime-qualified

When `UiPerformanceLogging=1`, a low-frequency helper checks `uiperf_trigger.txt` approximately every 200 ms. The helper only checks for presence and posts a private window message; it never dereferences Battlezone UI objects. The existing OpenShim game-window subclass receives the message on the main/UI thread and performs file read/delete, UI traversal, and callback invocation there. Both helper and main-thread trigger-file operations are wrapped in `UiFileScan::SetSuppress`, so they do not appear in `[UIPERF][SCAN]` and do not contribute to a transition category.

An idle GOG MainScreen run, with no keyboard/mouse input or pre-existing transition, produced the required sequence:

```
[UIPERF][HARNESS] trigger file detected; posted main-thread event
[UIPERF][HARNESS] custom main-thread event delivered ... tid=<UI thread>
[UIPERF][HARNESS] trigger=SinglePlayer_MainScreen detected
[UIPERF][HARNESS] MainScreen ... vt=0x0089E178
[UIPERF][HARNESS] MainScreen_Overlay ... vt=0x008A0B94
[UIPERF][HARNESS] button=SinglePlayer_MainScreen ... vt=0x008A0470 onclick=0x0078C520
[UIPERF][HARNESS] invoking OnClick on main thread
[UIPERF] ShellRequest screenId=0x02 (SinglePlayer)
[UIPERF] transition end ShellRequest->SinglePlayer(0x02)
```

The transition completed at the real Single Player destination. Over 150 poll samples, helper active time averaged 108.5 microseconds per 200 ms sample (approximately 0.054% duty), with a 231.7 microsecond maximum. Earlier qualifying runs measured 100–120 microseconds average and at most 342 microseconds. Polling does not occur every rendered frame.

### 21.2 Reusable frontend RE findings

All addresses below are for the settled GOG 2.2.301 executable used by this investigation. Steam/GOG static parity remains subject to the normal settled-byte verification policy.

#### Shell state and hook boundaries

| Function/state | Address/offset | Qualified behavior |
|---|---:|---|
| Shell request | `0x007C7930` | `void __thiscall(manager, int screenId)`; prologue `55 8B EC 51 89 4D FC`, therefore a 7-byte trampoline boundary. Sets manager request byte and appends the destination to history. |
| Shell transition | `0x007C7070` | `int __cdecl(int* dialog, int mode)`; 5-byte prologue boundary. Destroys/reconstructs the active screen and clears the request byte only after destination construction. Callers clean eight stack bytes; preserve EAX. |
| Shell Back | `0x007C79A0` | `void __thiscall(manager)`; prologue `55 8B EC 51 89 4D FC`, therefore 7 bytes, not 5. Pops `manager+0x2C` history when nonempty and sets request byte `manager+0x27`. |
| Screen-to-manager Back thunk | `0x00788060` | Reads `this+0x138`, then calls Shell Back. This proves screen context is the receiver expected by stored Back callbacks. |
| Global active-screen wrapper | `0x00918320` | Wrapper pointer; active screen is wrapper `+0x14`. |
| Shell request byte | manager `+0x27` | Reliable completion signal. Pointer inequality is unreliable because the allocator can reuse the old screen address with a new vtable. |
| Shell history | manager `+0x2C` | History vector used by Shell Back. |

The earlier 5-byte Shell Back trampoline split `89 4D FC` and was repaired. The earlier pointer-change completion test was also removed: destination construction can reuse the same allocation, whereas request-byte clear reliably denotes completion.

#### Live UI object layout and routes

Common UI fields: object name at `+0x20`; child vector at `+0x12C/+0x130`; button callback at `+0x154`. Generic buttons use vtable `0x008A0470`, overlays use `0x008A0B94`.

| Screen | Screen vtable | Live hierarchy / callback |
|---|---:|---|
| Main | `0x0089E178` | `MainScreen_Overlay` contains `SinglePlayer_MainScreen` (`OnClick 0x0078C520`, requests `0x02`) and `MultiPlayer_MainScreen`. |
| Single Player | `0x008A0350` | `Middle_Overlay` contains `Instant` (`0x007BEE10`, requests `0x1B`), `CampaignLaunch` (`0x007BEE80`, requests `0x20`), `Back_SinglePlayer` (`0x007BED10`), plus stock mission buttons. |
| Instant Action | `0x0089DA3C` | `Middle_Overlay` contains `Back` (`0x007898E0`), `Launch` (`0x00789900`), and `Mission_List`. |
| Campaign | `0x0089D8D8` | `Middle_Overlay` contains `Back` (`0x00788030`), `Launch` (`0x00788050`), `Options` (`0x00788020`), and `Mission_List`. |

`Instant` and `CampaignLaunch` are the actual nested Single Player button names; no forced shell IDs or assumed names are needed. Raw Back callback decompilation corroborates the owner rule: IA `0x007898E0` loads global screen `0x009454F4`, while Single Player `0x007BED10` loads `0x009455E0`; both reach `0x00788060`. Harness callbacks are therefore invoked as `__thiscall` with the live active screen in ECX.

### 21.3 Filesystem accounting repair

The first real-route capture had no `[SCAN]` lines because scan aggregation flushed only from exported `Shutdown()`. Normal game termination does not call that export, and process detach intentionally does no cleanup/log flushing. Commit `f89182d4` now starts a scan generation at ShellRequest/ShellBack and flushes it before `NotifyShellTransitionComplete()`.

Two times are deliberately separate:

- `elapsed`: inclusive FindFirst-to-FindClose enumeration lifetime, for diagnostic comparison only;
- `exclusive`: QPC time spent inside hooked `FindFirst`/`FindNext`/`FindClose`/`GetFileAttributes` APIs, which alone contributes to the exclusive `filesystem` category.

This prevents enumeration lifetime from double-counting Ogre work nested between FindFirst and FindClose. Transition accounting now satisfies `filesystem_exclusive + ogre_self + shader_self + unattributed = wall` within printed-timer rounding.

### 21.4 Same-process first-versus-repeat matrix (GOG content-heavy state)

Capture: `%TEMP%\BZR-OpenShim-uiperf-matrix-20260828-231654\openshim-run.log`. It used a fresh, windowed GOG process and the normal local content state, with `UiPerformanceLogging=1`, `UiPerformanceVerbose=0`. Each logical Main route includes the fast Main-to-Single-Player or Single-Player-to-Main navigation around the measured nested destination.

| Transition | First | Repeat | Delta | Repeat/First |
|---|---:|---:|---:|---:|
| Main -> Multiplayer | not measured (GOG lobby path is not runtime-qualified) | — | — | — |
| Multiplayer -> Main | not measured | — | — | — |
| Main -> Instant Action | 1183.28 ms | 1126.27 ms | -57.01 ms | 0.952 |
| Instant Action -> Main | 2119.07 ms | 2130.78 ms | +11.71 ms | 1.006 |
| Main -> Campaign | 1209.02 ms | 1114.10 ms | -94.92 ms | 0.921 |
| Campaign -> Main | 2156.74 ms | 2150.98 ms | -5.76 ms | 0.997 |

Exclusive breakdown (milliseconds):

| Logical transition | Pass | filesystem | ogre_self | shader_self | unattributed | wall |
|---|---|---:|---:|---:|---:|---:|
| Main -> IA | first | 4.36 | 864.62 | 0.00 | 314.30 | 1183.28 |
| Main -> IA | repeat | 4.47 | 868.37 | 0.00 | 253.43 | 1126.27 |
| IA -> Main | first | 17.50 | 1815.95 | 0.00 | 285.63 | 2119.07 |
| IA -> Main | repeat | 17.36 | 1827.53 | 0.00 | 285.88 | 2130.78 |
| Main -> Campaign | first | 3.87 | 949.46 | 0.00 | 255.68 | 1209.02 |
| Main -> Campaign | repeat | 3.59 | 871.52 | 0.00 | 238.99 | 1114.10 |
| Campaign -> Main | first | 17.46 | 1850.36 | 0.00 | 288.93 | 2156.74 |
| Campaign -> Main | repeat | 18.21 | 1834.96 | 0.00 | 297.81 | 2150.98 |

The largest atomic-transition unattributed aggregate in this matrix was 235.31 ms, below the 250 ms drilldown threshold. All continuous >=250 ms stall markers were already bounded by `OgreInitialise_Begin -> OgreInitialise_End`; the largest route marker was 1820.25 ms. Startup also contained a 2006.26 ms Modable initialise marker, outside the measured navigation routes. No continuous unattributed interval >=1 second remains hidden in this capture.

### 21.5 Repeated content and Ogre work

The forward repeat scans are identical in root and count:

| Route/pass | Primary root | dirs | files | ODF | BZN | TRN | inclusive | filesystem self |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| IA first | `addon` | 41 | 3661 | 420 | 90 | 90 | 60.11 ms | 3.98 ms for root; 4.36 ms all roots |
| IA repeat | `addon` | 41 | 3661 | 420 | 90 | 90 | 63.48 ms | 4.11 ms for root; 4.47 ms all roots |
| Campaign first | `addon` | 13 | 3487 | 368 | 78 | 78 | 58.38 ms | 3.39 ms for root; 3.87 ms all roots |
| Campaign repeat | `addon` | 13 | 3487 | 368 | 78 | 78 | 57.72 ms | 3.23 ms for root; 3.59 ms all roots |

Every destination-to-Single-Player return also repeats the same heavy tree: `mods` = 739 directories, 5136 files, 932 ODF, 8 BZN, 2 TRN; `addon` = 9 directories and 5 files. Inclusive enumeration lifetime is 108.62–113.27 ms and filesystem API self is 17.36–18.21 ms. The same metadata inventory is therefore rediscovered on repeat even though content did not change, but raw filesystem API self is a small fraction of wall time.

Ogre repeats the same `Modable` clear/init operations:

| Route operation | First | Repeat |
|---|---:|---:|
| IA: clear / initialise `Modable` | 72.46 / 792.16 ms | 71.27 / 797.11 ms |
| Campaign: clear / initialise `Modable` | 70.19 / 879.27 ms | 68.39 / 803.13 ms |
| IA return: clear / initialise `Modable` | 30.44 / 1785.50 ms | 29.52 / 1798.01 ms |
| Campaign return: clear / initialise `Modable` | 30.12 / 1820.24 ms | 29.23 / 1805.73 ms |

No load/unload/destroy or separately exported `parseResourceGroupScripts` operation appeared in this run. Material/script parsing occurs inclusively under `initialiseResourceGroup`; this capture does not yet provide a separate `*mod.material` parse count/time, so material-level conclusions must wait for narrower instrumentation or Ogre-log correlation. Shader markers were already warm: startup `cache_init=16 ms`; navigation markers report zero hits, zero misses, and zero elapsed. These are lookups/markers, not evidence of compilation.

### 21.6 Gates still open — do not overclaim

- **Manual-versus-harness equivalence passed for Main -> Instant Action** after this section's initial checkpoint; see §21.8. The remaining automated IA/Campaign timings may be treated as representative of normal UI navigation for the qualified GOG routes.
- **Multiplayer is not measured.** The GOG process does not provide a qualified live Steam lobby/Workshop context. Run the MP pair on Steam and verify the `MultiPlayer_MainScreen` callback, ShellRequest path, scan roots, and destination.
- **Minimal-versus-content-heavy scaling is not measured.** This section is the representative local content-heavy side only. A known minimal configuration must be captured with identical code before attributing scaling to entry count, metadata count, materials, or resource rebuilding.
- **No first optimization is selected.** Measured `Modable` initialise time is currently the dominant recoverable-looking repeat work (approximately 0.8 seconds forward and 1.8 seconds on returns), while raw filesystem API self is only 3.6–18.2 ms. That observation is not authorization to retain/cache resources: the physical-click and scaling gates, material-level attribution, invalidation design, and compatibility review remain outstanding.

### 21.7 Validation at this checkpoint

- `Release|Win32`: passed (existing warnings only).
- Host tests: 16/16 passed.
- `git diff --check`: passed.
- Safe runtime lifecycle: all launches dot-sourced `BZRHarness.ps1`, forced windowed mode for correctness, and closed through `Stop-BZRGame -Id`; original GOG `winmm.dll`, `scripts/patches.json`, and Ogre configuration were restored after each capture.

### 21.8 Manual-versus-harness equivalence result

A fresh manual capture used real mouse clicks on the rendered `Single Player` and `Instant Action` controls. Capture: `%TEMP%\BZR-OpenShim-uiperf-manual-20260828-232237\openshim-run.log`. It was compared with the first harness IA route from §21.4 in a comparable fresh-process/content state.

| Property | Manual physical click | Harness OnClick |
|---|---|---|
| Main -> Single Player | `0x02`, 94.69 ms | `0x02`, 91.49 ms |
| ShellRequest ID/path | `0x1B`, caller `0x007BEFC7` | `0x1B`, caller `0x007BEFC7` |
| Destination | `InstantAction(0x1B)` | `InstantAction(0x1B)` |
| Primary scan root | `addon` | `addon` |
| dirs/files/ODF/BZN/TRN | 41 / 3661 / 420 / 90 / 90 | 41 / 3661 / 420 / 90 / 90 |
| All-root FindFirst/FindNext/GetAttributes | 23 / 3730 / 17 | 23 / 3730 / 17 |
| clear `Modable` | 68.65 ms | 72.46 ms |
| initialise `Modable` | 799.67 ms | 792.16 ms |
| `buildIAResources` | 1005.08 ms | 984.73 ms |
| `InstantActionCtor` | 16.98 ms | 18.24 ms |
| shader markers | 0 hits / 0 misses / 0 ms | 0 hits / 0 misses / 0 ms |
| total SP -> IA | 1099.86 ms | 1091.79 ms |
| exclusive categories | filesystem 4.42; Ogre 868.32; unattributed 227.12 ms | filesystem 4.36; Ogre 864.62; unattributed 222.81 ms |

The engine work is structurally equivalent and no operation appears only on the physical-click route. Timing variation is small and expected. This passes the requested equivalence gate for a representative expensive transition and validates the harness's live-screen receiver convention.

## 22. Steam runtime qualification and the user-priority routes (2026-08-29)

The GOG matrix in §21 measured Instant Action and Campaign because those were
reachable. The user then identified the actually painful routes: **Multiplayer
open, Multiplayer leave, and Abort Mission from a single-player level**. Those
live on the Steam install, so the Steam process had to be made profilable
first. This section records that work, the resulting measurements, and the
correction it forces on the §21.6 ranking.

### 22.1 Steam startup was dying inside partially decrypted shell code

Profiler-enabled Steam launches died about five seconds into startup, before
MainScreen. Seven full dumps were captured in `C:\BZDumps` between 23:27 and
23:41 on 2026-08-28 (`battlezone98redux.exe.{32040,7904,30608,2776,39740,41644,17604}.dmp`).

All seven agree: the process dies inside the body of `ShellRequest`
(`0x007C7930`), in the range `0x007C7947`–`0x007C7976`. The exception code
varies between runs (`0xC000001D` illegal instruction, `0xC0000005` access
violation) only because different ciphertext bytes decode as different invalid
operations. In the dump, `ShellRequest` begins with correct plaintext for its
first 14 bytes and is SteamStub ciphertext immediately after.

Root cause: the profiler installed its three shell detours during `DllMain`
-time initialisation, before SteamStub had finished decrypting and settling
that code page. The inline write landed on a page that was subsequently
rewritten, so stock execution fell through into encrypted bytes. GOG is
unaffected because its executable is not packed.

Fixes, all already committed:

| Commit | Change |
|---|---|
| `fb7450ce` | Steam never publishes the GOG-only scroll-state getter `0x007D3360`, so every scroll-state caller fails closed instead of touching a UI context. |
| `3568da29` | The GOG map-frame probe is bypassed on Steam. |
| `58f503a4` | On Steam the three shell detours are deferred: they install on the UI thread only once a **live MainScreen exists** and full-function byte sentinels match. Startup keeps only read-only/IAT instrumentation. |

`AreSteamShellFunctionsSettled()` deliberately checks bytes **beyond** each
overwritten prologue (`ShellRequest+0x0E` and `+0x1D`, `ShellTransition+0x05`,
`ShellBack+0x07`). The dumps showed SteamStub exposing a correct 7-byte entry
while the rest of the function was still ciphertext, so a prologue match alone
is not authority to install a detour. The two Instant-Action drilldown hooks
remain GOG-only.

After this change, every Steam run reached a live MainScreen, installed all
three detours on the UI thread, and produced no new dump.

The first-chance `GetScrollState` access violation seen in earlier logs was
caught and handled; it was never the process-ending failure.

### 22.2 Driving real input into Redux from the harness

Two harness defects had previously been mistaken for engine behaviour, and the
conclusion "automated SendInput cannot reliably drive this UI" was wrong. Both
are host-side:

1. **`INPUT` must be the full 40-byte x64 layout.** A C# union declaring only
   `KEYBDINPUT` measures 32, and `SendInput` rejects the whole call with
   `ERROR_INVALID_PARAMETER`, returning 0. Declare `MOUSEINPUT` in the union
   too, and check the return value.
2. **Redux reads the keyboard through OIS/DirectInput, which works in scan
   codes.** A virtual-key-only send is accepted by Windows and never reaches
   the game. Use `KEYEVENTF_SCANCODE` with `wVk = 0` and
   `wScan = MapVirtualKey(vk, MAPVK_VK_TO_VSC)`, held ~90 ms so it spans
   several frames.

Two more were found during this session:

3. **`SetForegroundWindow` is refused outright** for a process that does not
   already own the foreground. Attach to the *current foreground* window's
   thread input queue — not just the target's — for the duration of the call,
   then **verify** `GetForegroundWindow() == hwnd` before sending anything.
   `Process.MainWindowHandle` is unreliable; enumerate the process's visible
   `OgreD3D*` window instead.
4. **The harness host must call `SetProcessDPIAware()`.** The display is
   scaled, so a DPI-virtualised host reads a 1600x900 client area as 1066x600
   and its window rect, desktop capture and absolute mouse coordinates all
   disagree with the game's real pixels.

With those four corrected, a real scan-code `Escape` opens the stock pause
screen from inside a running mission, and real absolute-coordinate mouse clicks
select rows in a mission list. The earlier `__PAUSE__` trigger, which marshalled
`ShellRequest(0x0B)` directly, was removed: it never opened the pause screen
(the request byte is not what the in-mission Escape path drives), and it is
unnecessary now that real input works.

### 22.3 Single-player routes go through the full main menu

Launching a `.bzn` on the command line is not the route to measure. It also
never visits MainScreen, so on Steam the deferred shell detours never install.
Every single-player measurement below therefore uses the stock navigation:

`MainScreen -> SinglePlayer_MainScreen -> <campaign or Instant Action> -> Launch
-> mission -> Escape -> pause screen -> Abort`.

Live pause screen (`Top Screen`, vtable `0x0089D9FC`), enumerated from a
running mission:

| Button | OnClick |
|---|---|
| `Back` | `0x00788EA0` |
| `Options_EscScreen` | `0x00788EB0` |
| `Load` | `0x00788EC0` |
| `Save` | `0x00788ED0` |
| `Abort` | `0x00788EE0` |
| `Restart` | `0x00788EF0` |

Red Brigade campaign screen (`Screen0x22`, vtable `0x0089E2A8`), reached from
`CHMission_SinglePlayer` (`0x007BEDC0`): `Back` `0x0078ED70`, `Options`
`0x0078ED80`, `Launch` `0x0078ED90`, `Archive` `0x0078EDA0`, `MainMenu`
`0x0078EDB0`, and a `Mission` list with `MissionpageUp` `0x0078ED20` /
`MissionpageDn` `0x0078ED30`. Mission 1 is preselected, so this screen needs no
list selection and is the deterministic way to reach a stock mission.

Instant Action is not deterministic for a harness: `Mission_List` exposes only
`Mission_ListpageUp`/`pageDn` as UI children — the rows are internal to the list
widget — so `Launch` is inert until a row is selected by a real click, and on
this install every listed map is Workshop content requiring EXU, which is not
installed in the Steam copy. Those launches stop on a modal
`no file '...\exu.dll' / NO ASSET 'exu.lua'` dialog on the loading screen.

### 22.4 Measurements — Multiplayer

Capture: `%TEMP%\BZR-OpenShim-uiperf-steam-mp-20260829-054953\openshim-run.log`,
Steam, windowed, `/nointro`, normal local content, first and repeat in one
unchanged process.

| Transition | First | Repeat |
|---|---:|---:|
| Main -> Multiplayer lobby (`0x0E`) | 8158.07 ms | 3503.47 ms |
| Multiplayer lobby -> Main (`Back`) | 2188.19 ms | 2210.49 ms |

Where the time goes:

| Phase | MP open first | MP open repeat | MP leave first | MP leave repeat |
|---|---:|---:|---:|---:|
| `buildMPResources` | 7709.70 ms | 3426.89 ms | — | — |
| `buildMainResources` | — | — | 2105.64 ms | 2127.29 ms |
| nested `clear Modable` | 71.58 ms | 71.85 ms | 156.11 ms | 165.17 ms |
| nested `initialise Modable` | 6988.57 ms | 2872.16 ms | 1763.04 ms | 1763–1800 ms |
| destination ctor | 371.04 ms | 3.14 ms | 3.04–3.37 ms (MainScreenCtor) | same |
| old-screen dtor | <1 ms | <1 ms | 0.89 ms | 0.93 ms |
| filesystem API self | 23.64 ms | 22.62 ms | 18.18 ms | ~18 ms |

Scan roots are re-enumerated in full on every visit, with identical counts:

| Route | Primary root | dirs | files | ODF | BZN | TRN | inclusive | filesystem self |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| MP open first | `addon` | 8 | 24682 | 3355 | 62 | 62 | 551.61 ms | 23.21 ms |
| MP open repeat | `addon` | 8 | 24683 | 3355 | 62 | 62 | 398.55 ms | 22.17 ms |
| MP leave | `workshop/content/301650` | 743 | 5236 | 932 | 8 | 2 | 114.61 ms | 17.59 ms |

So both Multiplayer routes are dominated by stock `Ogre::initialiseResourceGroup`
on the `Modable` group, nested inside `buildMPResources` / `buildMainResources`.
Lobby construction and screen destruction are negligible after the first visit,
and raw filesystem API self time is 18–24 ms against 2.2–8.2 s of wall time.
The first-visit outlier (6989 ms vs 2872 ms) is cold OS cache, not extra work.

### 22.5 Measurement — Abort Mission is *not* a slow transition

Captures:
`%TEMP%\BZR-OpenShim-uiperf-steam-spabort-20260829-094242\openshim-run.log` and
`...-094434\openshim-run.log`. Both used the full menu route, the Red Brigade
campaign mission 1, a real scan-code `Escape` to open the pause screen, and the
live `Abort` button's own OnClick with the live screen in ECX. The second run
stayed in the mission for 150 s before aborting, to test whether teardown cost
scales with simulation build-up.

| Transition | Run A (8 s in mission) | Run B (150 s in mission) |
|---|---:|---:|
| `SinglePlayer` (`0x02`) | 272.04 ms | 272.39 ms |
| Red Brigade screen (`0x22`) | 195.94 ms | 191.91 ms |
| `Launch` -> `Loading` (`0x17`) | 195.57 ms | 198.67 ms |
| mission load (`BuildMainResources_End -> SimTick`) | 3054.15 ms | 1780.18 ms |
| `Escape` -> pause (`0x0B`) | 190.43 ms | 190.35 ms |
| **`Abort` -> `MainMenu` (`0x01`)** | **61.50 ms** | **60.22 ms** |

Abort breakdown (both runs):

| Component | Run A | Run B |
|---|---:|---:|
| `buildMainResources` | 0.09 ms | 0.07 ms |
| `MainScreenCtor` | 3.04 ms | 3.37 ms |
| filesystem: roots / FindFirst / FindNext / GetFileAttributes | 0 / 0 / 0 / 0 | 0 / 0 / 0 / 0 |
| Ogre `clear`/`initialise Modable` | none | none |
| wall clock, `Abort` OnClick to MainScreen buttons live | ~150 ms | ~270 ms |

This is a real result and it contradicts the working assumption. Aborting a
stock single-player mission does **not** rebuild the `Modable` resource group
and does **not** re-enumerate any content root; `buildMainResources` returns in
under a tenth of a millisecond because the group is still valid. Dwelling
150 s in the mission changed nothing, so mission teardown does not scale with
simulation build-up either.

Two caveats, stated rather than papered over:

- The mission was stock Red Brigade content on an install whose addon tree is
  large but whose *mission* was not addon-backed. An abort out of a
  Workshop/Campaign Reimagined mission — which may leave the resource group
  dirty the way Multiplayer does — has not been measured, and is the obvious
  candidate for the slowness the user reports.
- `Abort` was invoked through the button's own OnClick, not a physical click on
  the pause screen. §21.8 established manual/harness equivalence for a
  representative expensive transition on MainScreen; that equivalence has not
  been re-verified for the pause screen.

### 22.6 Revised ranking

Measured on Steam with the user's normal content:

| Route | Wall | Dominant cost |
|---|---:|---|
| Main -> Multiplayer lobby (first) | 8158 ms | `initialise Modable` 6989 ms |
| Main -> Instant Action (first) | 3964–8450 ms | `initialise Modable` ~3.1 s + 24.7k-file `addon` scan |
| Main -> Multiplayer lobby (repeat) | 3503 ms | `initialise Modable` 2872 ms |
| Multiplayer -> Main | 2188–2210 ms | `initialise Modable` ~1763 ms |
| mission load | 1780–3054 ms | stock mission load |
| Single Player screen | ~272 ms | — |
| campaign screen, pause, Loading | ~190–199 ms | — |
| **Abort -> MainMenu** | **60–62 ms** | **nothing recoverable** |

The one recoverable-looking behaviour remains repeated
`Ogre::initialiseResourceGroup` on `Modable` for content that has not changed.
It is worth 1.8–7.0 s per affected transition. Abort Mission should be dropped
from the optimisation list unless a content configuration is found where it is
actually slow.

### 22.7 Gates still open

- **Abort under addon content is unmeasured.** Repeat §22.5 with a
  Workshop/Campaign Reimagined mission before concluding Abort is fast in
  general.
- **Physical-click equivalence for the pause screen** is unverified.
- **Minimal-versus-content-heavy scaling** is still unmeasured (§21.6), so
  `initialise Modable` cost has not been attributed to entry count, metadata
  count, or material parsing.
- **Material-level attribution inside `initialiseResourceGroup`** still
  requires narrower instrumentation; no separate `*mod.material` parse
  count/time exists yet.
- **No optimisation is selected or authorised.** Retaining or caching the
  `Modable` group needs an invalidation design and a compatibility review.

### 22.8 Incidental finding — autosave faults when a mission fails to load

Not part of this investigation, recorded because it produced evidence during
it. When a launch stops on the modal `exu.dll` missing dialog on the loading
screen, OpenShim's autosave still fires on its interval and calls the native
`SaveGame`, which raises `0xC0000005` every time:

```
[ERROR] [autosave] Native SaveGame raised exception 0xC0000005 for ...\Save\auto.sav
```

Each fault is caught by the crash logger, which writes a ~500 MB full dump.
Three such dumps were produced in 5 minutes on 2026-08-29
(`battlezone98redux.exe.{23992,1604,34420}.dmp`). Autosave should not attempt
`SaveGame` when no mission is actually running. `C:\BZDumps` is currently
~6 GB.

### 22.9 Validation at this checkpoint

- `Release|Win32`: passed (existing warnings only).
- Host tests: 16/16 passed.
- `git diff --check`: passed.
- Working tree matches `HEAD` for `src/`; the `__PAUSE__` trigger and the
  pause-menu variant of the deferred-install gate were removed rather than
  committed, because neither was ever observed to work.
- Safe runtime lifecycle: every launch dot-sourced `BZRHarness.ps1`, forced
  windowed mode, and shut down through `Stop-BZRGame -Id`; the user's original
  Steam `winmm.dll`, `scripts/patches.json` and `openshim.ini` were restored
  after each capture and verified identical by hash.

## 23. Abort is content-dependent, and every slow route is one Ogre phase (2026-08-29)

§22.5 measured Abort at 60–62 ms and flagged addon content as the untested
case. Manual qualification then confirmed the missing case: aborting a custom
campaign mission takes ~3–4 s, opening Custom Campaigns ~4 s, and returning
from it ~3 s. This section reproduces all three with the same instrumentation,
identifies the dominant cost, and profiles inside it.

### 23.1 The custom-content route

`Custom Campaigns` is the stock Campaign screen (`0x20`, vtable `0x0089D8D8`),
reached from `CampaignLaunch` (`0x007BEE80`) on the Single Player screen. Its
children are `Back` `0x00788030`, `Launch` `0x00788050`, `Options` `0x00788020`
and a `Mission_List` whose rows are internal to the list widget.

The install under test has two custom campaigns — `Battlezone: A Chronology`
(Campaign Reimagined, Workshop item `3686673790`) and
`Battlezone: ISDF Chronicles` (`addon\ISDF Chronicles`). Selecting a campaign
needs a real click on its row; `Launch` then opens that campaign's own mission
screen (`Screen0x25`), and `Launch` there starts the mission. So the full route
is:

`MainScreen -> SinglePlayer -> CampaignLaunch -> [click campaign row] -> Launch
-> Screen0x25 -> Launch -> Loading -> mission -> Escape -> pause -> Abort`.

### 23.2 Measurements

Capture: `%TEMP%\BZR-OpenShim-uiperf-steam-spabort-20260829-101138\openshim-run.log`
(abort route) and `...-100444\openshim-run.log` (open/leave cycle). Steam,
windowed, `/nointro`, real scan-code Escape, live `Abort` OnClick.

| Transition | First | Repeat | `initialise Modable` | `clear Modable` | filesystem self |
|---|---:|---:|---:|---:|---:|
| `SinglePlayer` (`0x02`) | 267–278 ms | — | none | none | 0–0.10 ms |
| **Custom Campaigns (`0x20`) open** | **4226–4673 ms** | **4086 ms** | 3234–3670 ms | 72–78 ms | 24–27 ms |
| **Custom Campaigns `Back` -> SP** | **2549 ms** | **2539 ms** | 1998 ms | 174 ms | 18 ms |
| Campaign missions (`0x25`) | 2497 ms | — | 1910 ms | 167 ms | 21 ms |
| `Loading` (`0x17`) | 159 ms | — | none | none | 0 |
| `Escape` -> pause (`0x0B`) | 183 ms | — | none | none | 0 |
| **Abort -> MainMenu, custom mission** | **2484 ms wall** | — | 1832 ms | 82 ms | 0 |
| Abort -> MainMenu, stock mission (§22.5) | 60–62 ms | 60 ms | none | none | 0 |
| `Back_SinglePlayer` -> Main | 56 ms | — | none | none | 0 |

The Abort breakdown is the clearest statement of the whole investigation:

| Component | Stock Red Brigade mission | Campaign Reimagined mission |
|---|---:|---:|
| `buildMainResources` before the transition | 0.09 ms | **2205.24 ms** |
| ├─ `clear Modable` | — | 82.20 ms |
| └─ `initialise Modable` | — | 1831.93 ms |
| `ShellRequest->MainMenu(0x01)` transition | 61.50 ms | 87.07 ms |
| `MainScreenCtor` | 3.04 ms | 2.45 ms |
| filesystem roots scanned | 0 | 0 |
| wall, `Abort` OnClick to MainScreen live | ~150 ms | **~2484 ms** |

Same code path, same `buildMainResources`, same shell transition. The only
difference is whether the `Modable` resource group has to be rebuilt. Abort is
therefore content-dependent exactly as reported, and it is **the same
`Ogre::initialiseResourceGroup("Modable")` path already measured for
Multiplayer** — not a separate problem.

### 23.3 Inside `initialiseResourceGroup`

New instrumentation hooks the two stock phases and the script loaders. Both
phases and both loaders are exported by `OgreMain.dll`, but each export address
is an incremental-link thunk (`E9 rel32`), so the thunk is followed to the real
body before hooking — a relative jump cannot be relocated into a trampoline.
Each body is refused unless its first five bytes are exactly the MSVC SEH
prologue `55 8B EC 6A FF`, which is also where the fifth byte lands on an
instruction boundary, so a different OgreMain build fails closed.

Capture: `%TEMP%\BZR-OpenShim-uiperf-steam-spabort-20260829-101753\openshim-run.log`.

| Route | `initialise` | `parseResourceGroupScripts` | scripts | script parse | slowest one | residual | `createDeclaredResources` |
|---|---:|---:|---:|---:|---:|---:|---:|
| startup (base set) | 2188.70 ms | 2188.58 ms | 275 | 2125.70 ms | 40.86 ms | 62.88 ms | 0.00 ms |
| Campaign open, first | 3620.97 ms | 3620.84 ms | 1114 | 3415.44 ms | 30.01 ms | 205.40 ms | 0.00 ms |
| Campaign open, repeat | 3540.37 ms | 3540.24 ms | 1114 | 3349.92 ms | 22.98 ms | 190.32 ms | 0.00 ms |
| `Back` -> SP, first | 2662.67 ms | 2662.56 ms | 275 | 2580.64 ms | 43.04 ms | 81.92 ms | 0.00 ms |
| `Back` -> SP, repeat | 2366.96 ms | 2366.87 ms | 275 | 2300.53 ms | 38.97 ms | 66.34 ms | 0.00 ms |

So, of `initialiseResourceGroup`:

- `parseResourceGroupScripts` is **100.0%** of it;
- handing script bytes to a `ScriptLoader` is **94–97%** of that;
- the residual — matching patterns against every archive, building the file
  list, opening each stream — is 63–205 ms, i.e. **2–6%**;
- `createDeclaredResources` is **0.00 ms** every time.

Per-script-type attribution (composition from
`...-102142\openshim-run.log`; that run's absolute times are inflated by a
concurrent workload and are not quoted here):

| Group set | `.material` | `.program` | `.particle` | total |
|---|---|---|---|---|
| base / Main / Single Player | 259 scripts, 93–97% of parse time | 15 scripts, 64–137 ms | 1 script, 3–6 ms | 275 |
| custom content mounted (Campaign) | 1114 scripts, 100% of parse time | 0 | 0 | 1114 |

`MaterialSerializer::parseScript` never fires: everything goes through
`ScriptCompilerManager`, as expected for this Ogre version. The Ogre log agrees
on the sets — six `Parsing scripts for resource group Modable` blocks in one
session, of 244 / 275 / 1114 / 275 / 1114 / 275 scripts, over 1137 distinct
`.material` files.

No single script dominates: the slowest is 23–71 ms
(`cr_pda_overlay.material`, `ibcmmd_port.material`, `CR_terrain.program`,
`pc/materials/BZ2Render.material`) against totals of 2.3–5.3 s. The cost is the
aggregate of ~1114 material scripts at ~3 ms each, so nothing can be fixed by
special-casing a few files.

The counts are identical between first and repeat visits: **the same 275 or
1114 scripts are recompiled from source on every menu transition**, with no
content change in between.

### 23.4 The pivot: which site decides to rebuild

`initialiseResourceGroup` now logs its return address. Two stock call sites
drive every rebuild seen on these routes:

| Caller | Set | Where it fires |
|---|---|---|
| `0x0076A1C8` | 275 scripts (base) | startup, and nested inside `buildMainResources` — so on Multiplayer leave, Custom Campaigns `Back`, and Abort out of a custom mission |
| `0x0076AE17` | 1114 scripts (custom content mounted) | entering the Custom Campaigns screen (`0x20`) and its mission screen (`0x25`) |

Both are unconditional in every observation so far: each is preceded by a
`clearResourceGroup("Modable")`, which discards the group's script state and
forces the full re-parse. Neither appears to consult any notion of whether the
mounted content actually changed.

The open question for the next step is therefore narrow and static: read
`0x0076A1C8` and `0x0076AE17` and their enclosing functions, and establish
whether the engine has any existing dirty/generation signal that could gate the
clear+initialise pair, or whether one would have to be introduced.

### 23.5 Gates still open

- **No optimisation is selected or authorised.** The measurement says a cache
  or bypass would have to cover an entire script set, keyed on something that
  genuinely captures mounted-content identity, and it would have to be correct
  across mod switching, Workshop updates and in-place edits.
- **Physical-click equivalence for the pause screen** is still unverified
  (§22.5); Abort is invoked through the button's own OnClick.
- **Minimal-versus-content-heavy scaling** is still unmeasured, though §23.3
  now attributes the difference between the 275- and 1114-script sets directly
  to mounted content rather than to entry counts.
- **Measurements are load-sensitive.** Two runs in this section were taken
  while a second agent session was building and are visibly inflated
  (`buildMainResources` 5453 ms, parse residual 5629 ms). Only the quiet
  captures are quoted for absolute time; the contaminated ones are used for
  composition only.

### 23.6 Validation at this checkpoint

- `Release|Win32`: passed (existing warnings only).
- Host tests: 16/16 passed.
- `git diff --check`: passed.
- Safe runtime lifecycle: every launch dot-sourced `BZRHarness.ps1`, forced
  windowed mode, and shut down through `Stop-BZRGame -Id`. One run was killed
  by its host before its restore step; the Steam install was restored manually
  and verified by hash, and the harness now emits a heartbeat during long waits
  so an idle-output kill cannot recur.
- Measurements are taken only with the game window verifiably foreground. An
  inactive Redux window throttles its main loop; one `SinglePlayer` transition
  measured 66 s that way against a true 272 ms.

## 24. Modable mount lifecycle: the redundancy guard already exists (2026-08-29)

§23 established that every slow route is dominated by
`Ogre::initialiseResourceGroup("Modable")` and pinned two callers,
`0x0076A1C8` and `0x0076AE17`. The task then was to recover the surrounding
resource lifecycle, find the smallest reliable "Modable content changed"
signal, and suppress redundant rebuilds if the evidence supported it.

**Headline result: the engine already implements that guard, and it already
fires. No redundant whole-set rebuild was found to suppress on any measured
route.** What remains is genuine state change, so the multi-second cost cannot
be removed by "not clearing unchanged state".

### 24.1 The mount-mode state machine — PROVEN STATIC

Static analysis of the unencrypted GOG `battlezone98redux.exe` (2.2.301,
image base `0x00400000`; addresses verified identical to the settled Steam
image by successful prologue-guarded hook installation at runtime).

The resource manager object carries two fields:

| Field | Type | Purpose | Confidence |
|---|---|---|---|
| `+0x8C` | `int` | Mount mode | PROVEN STATIC + PROVEN RUNTIME |
| `+0x90` | `std::string` | Identity of the currently mounted content | PROVEN STATIC + PROVEN RUNTIME |
| `+0x38`, `+0x40`, `+0x54` | containers | Per-mode location/content lists | INFERRED (read by the setters) |
| `+0x5C` | ptr | Written by the mount wrapper | UNKNOWN |

`0x00915568` is a global enable flag; every setter returns immediately when it
is zero.

Seven stock setters drive the field. Five share one shape:

```
void __thiscall SetModable<Mode>(this)          // 0x0076A600 takes an argument
{
    if (g_ModableEnabled /*0x00915568*/ == 0) return;
    if (this->mode /*+0x8C*/ == <target>) return;      // <-- the stock guard
    this->mode = <target>;
    ...  mutate the mounted location set via 0x006679C0 ...
    ResourceGroupManager::getSingleton().clearResourceGroup("Modable");
    ResourceGroupManager::getSingleton().initialiseResourceGroup("Modable");
}
```

and two carry a *second* identity term:

```
void __thiscall SetModableCampaign(this, content)      // 0x0076AE60, 0x0076B350
{
    if (g_ModableEnabled == 0) return;
    if (this->mode == 0 && StringEquals(this->identity /*+0x90*/,
                                        content->identity /*+0x7C*/))
        return;                                        // <-- same content, no rebuild
    this->mode = 0;
    this->identity = content->identity;
    ...  mount, clear, initialise  ...
}
```

The setter catalogue:

| Address | Mode | Also known as | Guard | Epilogue |
|---|---:|---|---|---|
| `0x0076A030` | 4 | `buildMainResources` (already hooked here) | mode only | `ret` |
| `0x0076A240` | 2 | `buildMPResources` (already hooked here) | mode only | `ret` |
| `0x0076A430` | 1 | `buildIAResources` (already hooked here) | mode only | `ret` |
| `0x0076A600` | 0 | content setter | mode only | `ret 4` |
| `0x0076AB20` | 3 | custom-campaign list mount | mode only | `ret` |
| `0x0076AE60` | 0 | campaign/mod mount | **mode + identity** | `ret 4` |
| `0x0076B350` | 0 | second content mount | **mode + identity** | `ret 4` |

Argument counts are taken from each epilogue, not assumed: `0x0076AB20` ends in
`ret`, the other content setters in `ret 4`. Getting this wrong unbalances the
stack — an early revision of this instrumentation passed a stack argument to
the zero-argument setter and crashed the process (see §24.6).

So the previously-named `build*Resources` functions are not resource builders
with incidental mode bookkeeping; they *are* the mount-mode setters. That
resolves the two call sites from §23.4: `0x0076A1C8` is the
`initialiseResourceGroup` return address inside the mode-4 setter, and
`0x0076AE17` the one inside the mode-3 setter.

Mounting does **not** go through Ogre's exported `addResourceLocation` /
`removeResourceLocation`. Redux registers its own `Ogre::Archive` subclass
through the wrapper at `0x006679C0` (it allocates a 16-byte object via
`Ogre::StdAllocPolicy::allocateBytes` and installs it directly). Hooks on both
exported functions were installed and fired exactly once across a full session,
for `group=General type=FileSystem name=...\flags\_generated` — never for
`Modable`. PROVEN RUNTIME.

### 24.2 The guard fires in practice — PROVEN RUNTIME

Capture: `%TEMP%\BZR-OpenShim-uiperf-steam-spabort-20260829-104231\openshim-run.log`
(Multiplayer and Custom Campaigns cycles) and `...-104357\openshim-run.log`
(custom-campaign launch and Abort). Every mount-mode transition in both:

| Setter | mode before -> after | Identity before -> after | Skipped | Elapsed |
|---|---|---|---:|---:|
| `buildMPResources` | 4 -> 2 | — | no | (see §22.4) |
| `buildMainResources` | 2 -> 4 | — | no | |
| `buildMPResources` | 4 -> 2 | — | no | |
| `buildMainResources` | 2 -> 4 | — | no | |
| **`buildMainResources`** | **4 -> 4** | — | **yes** | **~0.01 ms** |
| `setModableCustomCampaignList` | 4 -> 3 | — | no | 3736.84 ms |
| `buildMainResources` | 3 -> 4 | — | no | |
| `setModableCustomCampaignList` | 4 -> 3 | — | no | 3755.35 ms |
| `buildMainResources` | 3 -> 4 | — | no | |
| **`buildMainResources`** | **4 -> 4** | — | **yes** | **~0.01 ms** |
| `setModableCustomCampaignList` | 4 -> 3 | `<none>` | no | 3974.45 ms |
| `setModableCampaign` | 3 -> 0 | `<none>` -> `...\packaged_mods\819834262` | no | 2319.62 ms |
| **`setModableCampaign`** | **0 -> 0** | **same path -> same path** | **yes** | **0.00 ms** |
| `buildMainResources` | 0 -> 4 | (identity retained) | no | 2200.72 ms |
| **`buildMainResources`** | **4 -> 4** | — | **yes** | **~0.01 ms** |

Four skips in two sessions, including the exact case the task singled out:
selecting the same campaign twice in a row (`Campaign A -> Campaign A`) returns
in **0.00 ms** because both the mode and the identity string match. The
identity is a real filesystem path — for Campaign Reimagined,
`C:\...\Battlezone 98 Redux\packaged_mods\819834262`.

Every other transition changed `(mode, identity)` for real. There is no
observed case of "desired state == active state" that still rebuilds.

### 24.3 What this means for the proposed optimization

The task's critical hypothesis was:

> desired Modable state = BASE, active Modable state = BASE, resource locations
> unchanged -> recompiling 275 scripts appears redundant.

That case exists and is **already free**: `buildMainResources` returns in
0.01 ms whenever the mode is already 4. It is exactly why Abort out of a stock
Red Brigade mission costs 60 ms (§22.5) while Abort out of a custom campaign
costs 2484 ms — in the stock case the mode never left 4.

Implementing an OpenShim-side `desiredState == activeState` suppression would
therefore be dead code: the condition it tests is already short-circuited
inside the stock function, before our detour's inner call returns. It was not
implemented, and adding it is not recommended.

Correspondingly, the invalidation cases the task listed are already correct in
stock code:

| Case | Stock behaviour | Correct? |
|---|---|---|
| Base -> Base | skipped | yes |
| Campaign A -> Campaign A | skipped (mode 0 + identity match) | yes |
| Campaign A -> Campaign B | rebuild (identity differs) | yes |
| Base -> Multiplayer / Campaign list | rebuild (mode differs) | yes |
| Any mode change | rebuild | yes |
| **Loose-file edit inside the same mod** | **not detected** | **no — see §24.5** |
| **Workshop update of the same item** | **not detected** | **no — see §24.5** |

### 24.4 What is actually left, and what it would cost

Every remaining multi-second stall is a genuine `(mode, identity)` change:

| Route | Transition | initialise Modable |
|---|---|---:|
| Main -> Multiplayer | 4 -> 2 | 2872–6989 ms |
| Multiplayer -> Main | 2 -> 4 | ~1763 ms |
| Main/SP -> Custom Campaigns | 4 -> 3 | 3233–3670 ms |
| Custom Campaigns -> Back | 3 -> 4 | ~1998 ms |
| Custom Campaigns -> campaign screen | 3 -> 0 | ~1858 ms |
| Abort out of a custom mission | 0 -> 4 | ~1820 ms |

Each of those genuinely swaps the mounted content, and §23.3 showed the cost is
~95% `ScriptCompilerManager` recompiling 275 or 1114 `.material`/`.program`
scripts from source. Removing it means not re-parsing scripts across a *real*
state change, which is the parsed-script cache the task wanted to avoid unless
necessary — or reducing what each screen mounts, which changes stock content
behaviour.

Two observations that matter if a cache is ever pursued:

- The state space is small and the identities are stable: modes 1–4 have no
  identity, mode 0 is keyed by a mod path. A cache would be keyed on
  `(mode, identity)` and would need at most a handful of entries.
- The sets alternate rather than accumulate. A session that goes
  `Main -> Custom Campaigns -> campaign -> mission -> Abort -> Main` performs
  three full rebuilds (~7 s of script compilation) over three distinct states,
  each of which is re-entered later in the same session unchanged.

### 24.5 Invalidation gap in the stock identity — PROVEN STATIC

The stock identity is a path string only. It carries no timestamp, size, hash
or generation counter, and the comparison at `0x00427310` is a plain string
equality. Consequently:

- editing a `.material` in place inside the currently mounted mod, or
- a Workshop update that replaces files under the same item id,

does **not** invalidate the identity. Today this is harmless because any change
of screen also changes the mode and forces a rebuild anyway. It would stop
being harmless the moment anything reused parsed state across a mode change:
such a cache could not rely on the stock identity alone and would need its own
content signature (mtime/size sweep of the mounted roots at minimum). This is
recorded as a hard prerequisite, not a detail.

UNKNOWN: whether any other engine subsystem maintains a content generation
counter that could serve this purpose. Nothing of the sort was found around
these call sites.

### 24.6 Instrumentation added

All of it is diagnostic-only and gated on `UiPerformanceLogging`:

- The three existing `build*Resources` detours now report
  `modeBefore`/`modeAfter`/`skipped` plus the identity string, at no extra cost
  and without hooking those functions twice.
- New prologue-guarded hooks on `0x0076A600`, `0x0076AB20`, `0x0076AE60` and
  `0x0076B350` report the same, plus the requested content identity.
- Ogre's `addResourceLocation` / `removeResourceLocation` are hooked to log
  every location mutation with group, type and path.
- A shared, fully validated `TryReadStdString` probe replaced the ad-hoc
  DataStream-name reader, so both the identity fields and script names use one
  guarded reader that fails closed on an unexpected layout.

Every hook validates the exact five-byte MSVC SEH prologue before patching and
fails closed otherwise, and all of them install behind the existing Steam
settle gate.

One correctness incident during development, recorded because it produced a
dump: an early revision called the zero-argument setter at `0x0076AB20` through
a signature with one stack argument. The stack imbalance corrupted the process
and it exited mid-sequence (`battlezone98redux.exe.8772.dmp`, 2026-08-29
10:41). The fix was to take each setter's argument count from its own epilogue
(`ret` versus `ret 4`) and keep the two shapes strictly separate. No user data
was affected and the Steam install was restored and hash-verified afterwards.

### 24.7 Recommendation

1. **Do not implement desired-vs-active suppression.** It is already in stock
   code, it demonstrably fires, and a shim-side copy would be unreachable.
2. **Treat the remaining cost as a script-compilation problem, not a lifecycle
   problem.** The next honest option is reuse of parsed state across a genuine
   `(mode, identity)` change, with its own content signature for invalidation —
   explicitly the higher-risk path the task deferred.
3. **Before any such work, decide whether the mounted set itself is
   justified.** The Custom Campaigns list screen mounts a 24,697-file addon
   tree and compiles 1,114 material scripts to show a two-row list with a map
   preview. That is where the biggest single win would be, and it is a content
   /UI design question rather than a caching one.

### 24.8 Validation at this checkpoint

- `Release|Win32`: passed (existing warnings only).
- Host tests: 16/16 passed.
- `git diff --check`: passed.
- Runtime: Multiplayer open/leave x2, Custom Campaigns open/leave x2,
  Single Player -> Custom Campaigns -> Campaign Reimagined -> real mission ->
  Escape -> Abort -> Main, all through the real main-menu route with a real
  scan-code Escape and the game window verifiably foreground.
- No behaviour change was made to any engine path; only logging was added, so
  no A/B enable/disable comparison was required.
- Steam install restored and hash-verified after every cycle: `winmm.dll` and
  `scripts/patches.json` match the pre-run copies, no `openshim.ini` or trigger
  file left behind, no orphan process, `Ogre.cfg` recovered.
