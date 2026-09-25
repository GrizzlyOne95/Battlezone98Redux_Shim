<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Scripts, installers, tests, CI, and repository hygiene

## Summary

Overall the supported install path (`install_windows.ps1`, `install_linux.sh`, release.yml, Test-PackageShape.ps1) is in good shape: one versioned bundle, SHA-256 verified before extraction, refuse-before-touch on foreign `winmm.dll`, per-file re-check after Defender's quarantine window, and the three-binary load chain treated as a set. The problems are at the edges: a fail-open bug in the Linux installer's chain check, two stale pre-split deploy scripts that still copy `winmm.dll` alone, an uninstaller that never learned about the split, and unverified/unpinned wrapper downloads. Repository hygiene is the weakest area: a 38 MB leaked PDB, a compiled `.exe`/`.obj`, and Ghidra lock files are tracked.

Top 3:
1. `install_linux.sh` "does this bootstrap need a loader?" check returns *no* whenever `grep -q` SIGPIPEs `tr` under `pipefail` -- reproduced on Linux. A post-split `winmm.dll` with a missing `bzloader.dll`/plugin then installs as "OpenShim" with no OpenShim in it, the exact fail-open the comment says it prevents.
2. `scripts/deploy_linux_proton.sh` and `launch_steam_chunk_force_geo.cmd` still deploy `winmm.dll` by itself (pre-split), and `uninstall_windows.ps1` removes only `winmm.dll` + `patches.json`, leaving `bzloader.dll`, `plugins\openshim.dll`, `openshim\`, UI tiles and every `.bak-*`.
3. `install_windows.ps1` deletes the tester's working upload wrapper *before* downloading its replacement from `main` (unpinned, unhashed); a failed download leaves a Steam launch option pointing at a `.bat` that no longer exists, so the game stops launching.

## Findings

### [High][High] Linux installer chain-required check fails open under `pipefail` (SIGPIPE) — scripts/install_linux.sh:225

```bash
if tr -d '\000' < "$DLL" | LC_ALL=C grep -qa 'bzloader\.dll'; then
    NEEDS_CHAIN=1
```
The script runs under `set -euo pipefail` (line 21). `grep -q` exits on the first match and closes the pipe; `tr` is still writing the rest of a multi-MB DLL, takes SIGPIPE (status 141), and with `pipefail` the whole pipeline is 141 -> the `if` is false -> `NEEDS_CHAIN` stays 0. Reproduced on this host with a 2 MiB file carrying the UTF-16 string at 300 KiB: `status=141 PIPESTATUS=141 0` with pipefail, `status=0` without, and `status=0` only when the string sits in the last ~64 KiB (pipe buffer). In a real Win32 DLL the `L"bzloader.dll"` literal (src/engine/bzloader_bootstrap.cpp:53) lives in `.rdata`, followed by `.data`, `.rsrc`, `.reloc`, so the SIGPIPE case is the normal one. Consequence: line 271 (`if [[ "$NEEDS_CHAIN" == "1" && ( -z "$LOADER_DLL" || -z "$PLUGIN_DLL" ) ]]`) never fires, so `--dll` with a lone post-split bootstrap, or a bundle that lost its plugin, deploys a game that launches with no OpenShim and no error. The Windows twin (install_windows.ps1:198) reads the whole file and is not affected.
Fix (minimal): let grep consume the whole stream, e.g. `if tr -d '\000' < "$DLL" | LC_ALL=C grep -a 'bzloader\.dll' >/dev/null; then` (no `-q`), or `if LC_ALL=C grep -qa 'bzloader\.dll' <(tr -d '\000' < "$DLL")`. Verifiable on Linux (a 20-line bash test with a synthetic file; could join tests/openshim_wrap_coredump_tests.sh's lane).

### [High][High] `deploy_linux_proton.sh` is a pre-split deploy: bootstrap only, no loader, no plugin — scripts/deploy_linux_proton.sh:148-151

```bash
deploy_file "$DLL" "$game_dir/winmm.dll"
deploy_file "$PATCHES" "$game_dir/scripts/patches.json"
deploy_file "$OPENSHIM_INI" "$game_dir/openshim.ini"
```
It never copies `bin/Release/bzloader.dll` or `bin/Release/plugins/openshim.dll`, so on a current build it produces exactly the "boots with no OpenShim" install that Deploy-OpenShim.ps1 (lines 38-48) and Test-PackageShape.ps1 exist to prevent. It also overwrites the player's `openshim.ini` unconditionally (line 150; install_linux.sh preserves it), omits `openshim/OpenShimAssets.ini`, and uses GNU-only `stat -c %s` (line 108). Nothing references it (grep over README, Docs, CI, scripts: none; only its own `OPENSHIM_INSTALLER` env check at line 183 hints at a former caller). Fix: delete it and point people at `install_linux.sh --dll` / a local checkout, or make it call `find_artifact_set`/`deploy_matched` from install_linux.sh. Verifiable on Linux.

### [High][High] Windows installer deletes the live upload wrapper before fetching its replacement — scripts/install_windows.ps1:354-359

```powershell
Remove-Item -Force -ErrorAction SilentlyContinue $wfDest
...
Invoke-WebRequest -Uri $wu -UseBasicParsing -OutFile $wfDest
```
`Update-WrapperFiles` runs for every tester who already has `%LOCALAPPDATA%\openshim\openshim_wrap.ps1` (line 682), not only on `OPENSHIM_WEBHOOK` runs. If the raw.githubusercontent download fails (offline, AV, rate limit, fork without the file), the `.ps1` and/or `.bat` are already gone. The Steam launch option `cmd /c ""%LOCALAPPDATA%\openshim\openshim_wrap.bat" %command%"` then fails outright and the game will not start until the tester notices; the script's own text at line 707 acknowledges this failure mode. install_linux.sh gets this right (downloads to `$work` first, lines 573-579, then `install_wrapper_copy`). Fix: download to `$tempRoot`, verify non-empty, then `Move-Item -Force` over the destination. Windows-only to verify.

### [Medium][High] Uploader wrapper is fetched unpinned and unverified, and drifts from the release — scripts/install_windows.ps1:358, scripts/install_linux.sh:573-574

```bash
download_to "https://raw.githubusercontent.com/${REPO_SLUG}/${REF}/upload/openshim_wrap.sh"
```
The bundle is pinned to `releases/latest` and hash-checked; the wrapper (which runs on every launch with the tester's webhook) comes from `main` over HTTPS with no hash and no tie to the release the DLL came from. Both scripts already read `SHA256SUMS.txt` from the bundle; adding `upload/openshim_wrap.*` to the suite ZIP (release.yml:257-269) and copying from `$suiteRoot` instead of raw would pin and verify it for free. Related drift already visible: `upload/openshim_wrap.sh:59` is `OpenShim-upload-20260920-coredump` while `upload/openshim_wrap.ps1:52` is `OpenShim-upload-20260914` (the ps1 has none of the coredump/termination parity work), so Windows and Linux testers report different wrapper generations from the same install command. Verifiable on Linux (bundle contents), Windows (installer).

### [Medium][High] `uninstall_windows.ps1` predates the three-binary split and does not restore state — scripts/uninstall_windows.ps1:109-125

```powershell
Remove-Item -Force -LiteralPath $dllPath        # winmm.dll only
...
Remove-Item -Force -LiteralPath $patches        # scripts\patches.json only
```
Left behind: `bzloader.dll`, `plugins\openshim.dll`, `openshim\renderer\enhanced\*`, `openshim\OpenShimAssets.ini`, `openshim.ini.canonical`, the four tiles the installer writes into the game's own `BZ_ASSETS_CORE\common\ui\CustomWidgets\`, and every `*.bak-<stamp>` the installer accumulates on each run (Backup-ThenCopy, install_windows.ps1:411-421, never pruned). The header comment (line 4) still describes the single-DLL world. It also drifted from the installer's discovery: no `appmanifest_301650.acf` `installdir` parsing (install_windows.ps1:123-133) and no `Test-BzrGameDir` validation of `OPENSHIM_GAME_PATH` (line 76-79), so a typo in `OPENSHIM_GAME_PATH` silently uninstalls nothing. There is no Linux uninstaller at all; README.md:91 says "remove winmm.dll", which leaves the same residue. Fix: share the file list with the installer (loader, plugin, `openshim\`, tiles, canonical ini), delete `.bak-*` it created, and mirror Get-GamePaths. Windows-only to verify (Linux twin would be verifiable here).

### [Medium][High] `launch_steam_chunk_force_geo.cmd` copies `winmm.dll` alone and has an unfilled placeholder — launch_steam_chunk_force_geo.cmd:16,27

```bat
set "GAME_DIR=<GAME_ROOT>"
...
copy /y "%SOURCE_DLL%" "%TARGET_DLL%" >nul
```
Same pre-split hazard as deploy_linux_proton.sh (a fresh `winmm.dll` over an old loader/plugin, or no loader at all), plus a redacted `<GAME_ROOT>` that makes the default path unusable. Unreferenced anywhere. Fix: delete, or replace the copy with `powershell scripts\Deploy-OpenShim.ps1`. Windows-only.

### [Medium][High] Repository tracks a 38 MB leaked PDB, compiled test binaries and Ghidra lock files — battlezone98redux.pdb, tmp/load_test.exe, tmp/load_test.obj, battlezone98redux.exe-ghidra/**

`git ls-files` shows `battlezone98redux.pdb` (38,891,520 B) at the repo root, `tmp/load_test.exe` (112 KB) + `tmp/load_test.obj`, and `battlezone98redux.exe-ghidra/.../*.lock`, `*.lock~`, `~index.dat` (Ghidra runtime lock/index files that change on every open). AGENTS.md calls the PDB "private leaked-PDB" and reverse_engineering/*.md describe it as GUID-mismatched advisory material; `reverse_engineering/corpus_artifacts/*.zip` already goes through LFS (.gitattributes:1), and `sync_repo_best_effort_corpus.ps1:59` explicitly says the PDB is "not bundled". Only `tools/dump-main-ui-pdb.ps1` defaults to it (`-PdbPath "battlezone98redux.pdb"`). `.gitignore` covers `bin/`, `*.log`, `*.dmp` but not `tmp/*.exe|*.obj`, `*.lock`, `~index.dat`. Fix: `git rm --cached` the PDB, `tmp/load_test.exe`, `tmp/load_test.obj`, and the Ghidra lock/index files; add `tmp/*.exe`, `tmp/*.obj`, `*.lock`, `*.lock~`, `**/~index.dat` to `.gitignore`; move `tmp/load_test.cpp` to `tests/` or `reverse_engineering/` (its own header says it is a manual loader smoke test). History rewrite is a separate decision (do not do it without instruction). Verifiable on Linux.

### [Medium][Med] `dx11_enhanced_fxaa.rc`, `render_effect_intent.cpp`, `scene_depth_facts.cpp` are compiled into `winmm.dll` but only used from `openshim.dll` — BZROpenShim.vcxproj:129-130,232

```xml
<ClCompile Include="src\engine\render_effect_intent.cpp" />
<ClCompile Include="src\engine\scene_depth_facts.cpp" />
...
<ResourceCompile Include="dx11_enhanced_fxaa.rc" />
```
- The FXAA runtime (`src/patches/dx11_enhanced_fxaa.cpp`, plugin-only) loads its two RCDATA resources through `GetThisModule()` (line 127, `GetModuleHandleExA` from its own address, used at 146-157), i.e. from `openshim.dll`. The `.rc` comment (dx11_enhanced_fxaa.rc:5, "received ... entirely from winmm.dll") is stale and the winmm.dll copy of the HLSL + NVIDIA header is dead payload in the bootstrap.
- No bootstrap-only source (dllmain.cpp, winmm_proxy.cpp, openshim_sdk_bridge/thunks/legacy_thunks.cpp, openshim_bootstrap_api.cpp, startup_backend_seam.cpp, bzloader_bootstrap.cpp, bootstrap_file_io.cpp, cli_multiparam_parser.cpp, editor_view_order.cpp, src/winmm.def, include/openshim_sdk_exports.inc) references `BZROpenShim::RenderEffects::*` or `BZROpenShim::SceneDepth::*`; `include/openshim_sdk_bridge.h:19` includes `render_effect_intent.h` for types only. `scene_depth_facts.h` is included only by `src/patches/dx11_scene_depth.cpp` (plugin). Result: a second, never-used provider table + `std::mutex g_lock` (render_effect_intent.cpp:34) lives in winmm.dll, which is the kind of "two copies of state in two modules" that becomes a real bug the day the bootstrap starts calling it.
The other five shared sources (backend_selection, game_log_path, render_profile, shim_log_client, startup_seam_wire) are legitimately needed by the startup seam (tests/CMakeLists.txt:517-525 shows the same set). Fix: drop the two `.cpp` and the `.rc` from BZROpenShim.vcxproj, fix the `.rc` comment. Windows-only to verify (build + export parity step).

### [Low][High] `upload.conf` is written with unescaped single quotes and then `source`d — scripts/install_linux.sh:610, upload/openshim_wrap.sh:150,209

```bash
OPENSHIM_PLAYER='${OPENSHIM_PLAYER:-}'
...
source "$CONF_FILE"
```
`OPENSHIM_PLAYER` is free text (an in-game name); any `'` in it (`O'Neil`) produces a conf that fails to parse or, worse, executes the remainder on every launch and `--retry`. The webhook is prefix-validated only, so it can carry a `'` too. The PowerShell reader (`openshim_wrap.ps1:90`, `Trim("'")`) is tolerant, so the mismatch is Linux-specific. Fix: write `printf '%q'` (bash) or escape `'` as `'\''`, or switch the reader to a `KEY=VALUE` line parser like the ps1 one. Verifiable on Linux.

### [Low][High] Linux installer copies Enhanced resources non-recursively while Windows uses `-Recurse` — scripts/install_linux.sh:400, scripts/deploy_linux_proton.sh:156

```bash
cp -f "$RENDER_SRC"/* "$render_target/"
```
Today `resources/renderer/enhanced/` is flat, so this works. The first subdirectory added there makes `cp` fail ("omitting directory") and, under `set -e`, aborts `deploy_matched` *after* `winmm.dll`, the loader, the plugin and `patches.json` have already been replaced (lines 385-395), i.e. a partial deploy with a half-copied resource tree that the runtime validator will then reject. Windows (`Copy-Item ... -Recurse`, install_windows.ps1:298) and release.yml (`-Recurse`, line 267) already assume a tree. Fix: `cp -Rf "$RENDER_SRC"/. "$render_target/"`. Verifiable on Linux.

### [Low][High] Install/update file set disagreement: suite shape check does not require the UI tiles that Deploy-OpenShim.ps1 treats as mandatory — scripts/Test-PackageShape.ps1:184-193

```powershell
$companions = [ordered]@{
    'scripts\patches.json' ...
    'resources\openshim\OpenShimAssets.ini' = 'the asset manifest'
```
`resources\ui\custom_widgets\{uiline,uiplate,uibtn,uibtnhv}.png` is absent from the list, so a suite ZIP without the tiles passes `-Layout Suite`; `Deploy-OpenShim.ps1:142-143` throws on the same omission, and both installers silently skip (`if (Test-Path ...)` / `[[ -f ... ]]`) and still print "deployed UI widget tiles". Pick one policy; adding the four tiles (and `resources\renderer\enhanced\*.program`) to `$companions` matches the installers' stated intent that a bundle without resources is refused. Also, `SHA256SUMS.txt` (release.yml:286-290) covers only the flat assets, not the resource trees; the bundle hash covers those, which is fine, but the per-file post-quarantine re-check in install_windows.ps1 therefore cannot notice a quarantined shader. Windows-only to verify.

### [Low][High] CI duplication and drift between build-win32.yml and release.yml — .github/workflows/release.yml

- `Test-EnhancedPssmV2.ps1` runs in build-win32.yml:97 but not in release.yml, so a tag can ship a PSSM regression a PR would have caught.
- The FXAA `fxc` step (~28 lines) and the export-parity step (~40 lines) are copy-pasted verbatim between the two files (build-win32.yml:54-82,190-230 vs release.yml:54-82,136-170). Move both into `scripts/` (there is already `Test-EnhancedShaderCompile.ps1` for the sibling check) and call them from both workflows.
- release.yml has `workflow_dispatch` (line 7) but `softprops/action-gh-release` needs a tag; a manual run on a branch does all the work and fails at Create Release. Either drop the trigger or gate the release step on `startsWith(github.ref, 'refs/tags/')`.
- bzrnet-instrumentation.yml:6 triggers on push to `agent/bzrnet-native-instrumentation`, which no longer exists on origin; harmless, but dead.
Verifiable only by running Actions.

### [Low][Med] `Join-Path` on an undefined `${env:ProgramFiles(x86)}` throws under `$ErrorActionPreference = "Stop"` — scripts/install_windows.ps1:92,143, scripts/uninstall_windows.ps1:47,87

```powershell
(Join-Path ${env:ProgramFiles(x86)} "Steam"),
```
On 32-bit Windows the variable is undefined and `Join-Path` refuses an empty `-Path`, so discovery throws before any candidate is tested (the `if ($fallback)` guard runs too late). Rare host, but the game itself is 32-bit. Fix: build the list with `Where-Object { $_ }` on the env values before `Join-Path`. Windows-only.

### [Low][Med] `json_escape` does not escape control characters — upload/openshim_wrap.sh:673-680

The Discord `content` string embeds the map name scraped from BZLogger (`session_summary`, line 655-663). A `\r` or other control byte in that line yields invalid JSON, Discord returns 400, `--fail` makes `post_file` fail, and the bundle parks and is retried forever ("parked bundle still not uploadable"). Escape `\r` and strip other `[[:cntrl:]]`. Verifiable on Linux.

### [Low][High] `.gitattributes` LFS rule and `.gitignore` gaps

`reverse_engineering/corpus_artifacts/*.zip` is an LFS pointer (133 B) and `git lfs` is absent on this host, which is fine for a pointer but means `setup-dev.sh` should mention LFS if anything reads it. `.gitignore` lists `bin/` (so `tmp/load_test.exe` must have been force-added), `WORKSTATION.local.md`, `upload.conf`, but nothing for Ghidra project state or `tmp/`. See the hygiene finding above.

## Dead or unused code (list with evidence)

### Test executables / registration

| Item | Evidence | Note |
|---|---|---|
| `enhanced_light_selection_bench` | `add_executable` at tests/CMakeLists.txt:95, no `add_test` | Intentional benchmark (prints CSV, `return 0`, no checks). Fine, but say so in a comment. |
| `tests/backend_selection_tests.cpp` | not in CMakeLists; built only by `scripts/run_backend_selection_tests.ps1`, which no workflow calls | Engine-independent (`backend_selection.cpp` already links in the CTest seam tests). Never runs in CI. Add to CMake. |
| `tests/ui_decor_tests.cpp` | not in CMakeLists; only `scripts/run_ui_decor_tests.ps1`, not in any workflow | `src/engine/ui_decor.cpp` has no Win32 includes. Never runs in CI. Add to CMake. |
| `tests/ini_writer_tests.cpp`, `tests/openshim_preset_migration_tests.cpp` | built only by `scripts/run_ini_tests.ps1` (Windows CI lane) | `ini_writer_tests` is portable and could join the Linux lane; preset_migration uses `WIN32_LEAN_AND_MEAN` (line 32). |
| `tests/ogre_profiler_algorithms_tests.cpp` | `scripts/run_ogre_profiler_tests.ps1` (in CI) | OK; header-only test, could also be CMake. |
| `tests/bzloader_host_tests.cpp` | BZLoaderHostTest.vcxproj, run by CI as a separate step | OK (needs real DLL loading). |
| Tests that always pass | none found | Every CTest target keeps a failure counter and returns non-zero; `native_ui_validation_tests` exits on first failure. |

### Engine-independent sources under `src/` with no test coverage (no Win32/D3D/Ogre include in the file; heuristic, verify before relying on it)

`src/patches/openshim_sdk_provider.cpp` (609 lines), `src/patches/openshim_env_config.cpp` (552), `src/patches/terrain_semantic.cpp` (238), `src/engine/ui_decor.cpp` (219, only via run_ui_decor_tests.ps1 off-CI), `src/patches/fog_wake_feature.cpp` (144), `src/patches/openshim_ini.cpp` (126, Windows-lane only), `src/engine/openshim_sdk_legacy_thunks.cpp` (84), `src/plugin/bootstrap_service_client.cpp` (64), `src/plugin/startup_seam_client.cpp` (43), `src/patches/netcode_hooks.cpp` (18). The first two are the largest untested pure-logic files in the tree.

### Duplicated test helpers

47 of 55 test sources define their own `Check`/`Require`/`Expect*` + `g_Failures` counter (42 with a global counter), and six define the identical macro `#define CHECK(c) Check((c), #c, __LINE__)` (bootstrap_file_io_tests.cpp:34, bzloader_catalog_tests.cpp:26, odf_compat_tests.cpp:22, openshim_bootstrap_api_tests.cpp:37, openshim_sdk_thunk_tests.cpp:29, startup_backend_seam_tests.cpp:46). Three files hand-roll a temp directory under `std::filesystem::temp_directory_path()` (openshim_assets_tests.cpp:62, openshim_preset_migration_tests.cpp:167, render_profile_resources_tests.cpp:41). A 30-line `tests/test_support.h` (counter, `CHECK`, `CHECK_EQ`, scoped temp dir) would delete ~40 copies and also remove the six per-target `if(MSVC) /W4 /WX else -Wall -Wextra -Werror` blocks if paired with a CMake helper function. tests/CMakeLists.txt itself repeats the `target_include_directories`/`target_compile_features`/warning triple ~45 times (lines 202-296, 324-347); a `bzr_add_test(name sources...)` function would cut the file by two thirds.

### Scripts and tools reference table

| Script | Purpose (1 line) | Referenced by | Verdict |
|---|---|---|---|
| scripts/install_windows.ps1 | One-line Windows installer (bundle + verify + deploy) | README, release.yml, uninstall, Test-PackageShape | keep |
| scripts/uninstall_windows.ps1 | One-line Windows uninstaller | README, CHUNK_RENDERING_EXPLAINED | keep, fix (see finding) |
| scripts/install_linux.sh | One-line Linux/Proton installer | README, release.yml, upload/README, wrapper | keep, fix (see finding) |
| scripts/steam_game_paths.sh | Steam library discovery (sourced) | install_linux.sh, deploy_linux_proton.sh | keep |
| scripts/deploy_linux_proton.sh | Pre-split dev deploy of winmm.dll only | NONE | candidate to remove |
| scripts/Deploy-OpenShim.ps1 | Dev deploy of full chain + resources to GOG | Docs/AGENT_PATCH_WORKFLOW, render docs, custom_widgets README | keep (note: does not deploy openshim.ini/net.ini; document that) |
| scripts/Test-PackageShape.ps1 | Load-chain/suite shape validator | build-win32.yml, release.yml | keep |
| scripts/Test-EnhancedShaderCompile.ps1 | Compile every Enhanced HLSL variant | both workflows | keep |
| scripts/Test-EnhancedPssmV2.ps1 | PSSM v2 guard | build-win32.yml, RE doc | keep; add to release.yml |
| scripts/Test-EnhancedLodPermutations.ps1 | LOD permutation compile + DXBC baseline diff | NONE | keep only if wired into CI or documented in Docs/DX11 roadmap; otherwise move to reverse_engineering |
| scripts/Compare-EnhancedShaderParity.ps1 | OpenShim vs CR shader parity | Docs render docs | keep |
| scripts/Apply-StockDx11ShaderHardening.ps1 | Edits stock `BZ_ASSETS_CORE\pc\programs\dx11` shaders in a game install (`-Restore`) | NONE | move to reverse_engineering (mutates game files, undocumented) |
| scripts/run_ini_tests.ps1 | MSVC build+run of ini/preset tests + preset parity | both workflows, Docs | keep |
| scripts/run_ogre_profiler_tests.ps1 | MSVC build+run of profiler algorithm tests | both workflows | keep |
| scripts/run_backend_selection_tests.ps1 | MSVC build+run of backend_selection_tests | Docs, include/backend_selection.h (not CI) | candidate to remove once the test is in CMake |
| scripts/run_ui_decor_tests.ps1 | MSVC build+run of ui_decor_tests | one RE doc (not CI) | candidate to remove once the test is in CMake |
| scripts/run_render_profile_tests.ps1 | MSVC build+run of 5 render tests that CMake already runs | Docs, headers, tests | candidate to remove (fully duplicated by CTest) |
| scripts/render_profile_matrix.ps1 | Runtime qualification matrix driver; header says "not tracked" and cites `tmp\render_profile_matrix.ps1` | Docs qualification reports | keep, fix header |
| scripts/Get-RenderEvidence.ps1 | Harvest renderer evidence from logs | Docs, render_worlds README | keep |
| scripts/Install-RenderWorldMaps.ps1 / Test-RenderWorldMaps.ps1 | Benchmark maps install/check | Docs, RE READMEs | keep |
| scripts/Install-VegetationBench.ps1 | Vegetation bench install | lcbveg README | keep |
| scripts/BznIdentity.ps1 | Set-BznIdentity helper | Install-*.ps1 | keep |
| scripts/Compare-TerrainCaptures.ps1, Test-TerrainSemanticParity.ps1, New-TerrainHdSmokeTiles.ps1, terrain_hd_tiles.example.json | Terrain Phase 3 capture/parity tooling | Docs/terrain-render-path.md (json: NONE) | keep; json unreferenced but is the example the manifest loader documents -- reference it from terrain doc or remove |
| scripts/Invoke-SunFlashTrace.ps1 | [SUNFLASH] two-arm trace driver | NONE (include/sun_flash.h is cited in it, not vice versa) | move to reverse_engineering or reference from Docs |
| scripts/install_agent_re_tooling.ps1 | Installs Ghidra MCP / debugger bridge / frida wrappers | AGENT_TOOLING_SETUP, TODO | keep (RE toolchain) |
| scripts/ghidra_mcp_bz98.py, qiling_cli.py, redux_debug_bridge.py | RE toolchain CLIs | AGENT_TOOLING.md, installer | move to reverse_engineering/tools (they are RE, not build/deploy) |
| scripts/ghidra_extract_gog_exe_summary.py | pyghidra summary extractor | Docs/GHIDRA_GOG_EXE_RE.md | move to reverse_engineering |
| scripts/export_chunk_mesh_payloads.py, match_legacy_chunk_pieces.py | Chunk mesh payload pipeline (Blender) | each other only | move to reverse_engineering (or Docs pointer) |
| scripts/audit_chunk_payload_coverage.py | Offline chunk payload coverage report | NONE | move to reverse_engineering |
| scripts/pre-commit-secret-guard.sh | Blocks Discord webhook commits | setup-dev.ps1/.sh | keep |
| scripts/patches.json | Patch address table | everywhere | keep |
| tools/validate-network-baseline.ps1 | net_optimizer/net.ini safety baseline | both workflows, Docs | keep |
| tools/dump-main-ui-pdb.ps1 | llvm-pdbutil dump of the root PDB | NONE (defaults to tracked PDB) | move to reverse_engineering; decouple from tracked PDB |
| tools/export-bz15-ui.py, find-redux-ui-ctors.py | BZ1.5 UI export / Redux ctor finder | Docs/bz15-multiplayer-ui-port.md | move to reverse_engineering |
| tools/probe-redux-shell.js | Frida runtime probe (hardcoded GOG addresses) | NONE | move to reverse_engineering |
| buffer_logger_windows.ps1 | Start/Stop/Mark buffer capture harness | bzrnet_capture, tester_diag, RE report | keep; move to scripts/ |
| bzrnet_capture_windows.ps1 | BZRNet capture harness | bzrnet-instrumentation.yml (parse check), RE docs | keep; move to scripts/ |
| tester_diag_windows.ps1 | Tester diagnostics (ping, procdump arming) | NONE (mentioned in wrapper text only) | keep; move to scripts/ and reference from upload/README |
| verify_windows.ps1 | Verifies deployed patches.json / [STALE-CONFIG] | Docs/AGENT_PATCH_WORKFLOW, tester_diag | keep; move to scripts/; add load-chain check (it has none) |
| install_lldb_shim.ps1 | LLDB shim installer with `<LLVM_ROOT>`/`<ANDROID_SDK>`/`<BLENDER_ROOT>` placeholders | NONE | candidate to remove (cannot run as committed) |
| launch_steam_chunk_force_geo.cmd | Copies winmm.dll only + launches with chunk env | NONE | candidate to remove (pre-split, `<GAME_ROOT>` placeholder) |
| dx11_enhanced_fxaa.rc | RCDATA for FXAA HLSL + NVIDIA header | both vcxproj | keep; drop from BZROpenShim.vcxproj (see finding) |
| net.ini | Shipped network preset | installers, CI, docs | keep |
| netcode_manifest.json | Optional socket-buffer patch manifest read from game dir (net_optimizer.cpp:1216,4798) | include/netcode_hooks.h, net_optimizer.cpp | keep but document: no installer deploys it, so it is dev-only; consider moving under resources/ or Docs |
| openshim_producer_build_menus.ini.example | Producer build-menu example config | Docs/producer-build-menu-test.md | keep |
| AGENT_TOOLING_TODO.md | RE tooling backlog | NONE (AGENTS.md does not list it) | keep or fold into AGENT_TOOLING_SETUP.md |
| CHUNK_RENDERING_EXPLAINED.md | Plain-English chunk writeup | one RE work-pass note | move to Docs/ |
| WORKSTATION.md | Template for WORKSTATION.local.md | NONE (gitignore names the .local) | keep |
| tmp/load_test.cpp (+ .exe/.obj) | Manual LoadLibrary smoke test for winmm.dll | NONE | untrack binaries; move .cpp to tests/manual or reverse_engineering |
| experiments/ogre_plugin_probe/* | OGRE plugin-load probe DLL, in .sln but not in default build set | README inside; .sln | keep as experiment or move to reverse_engineering; it is not built by CI |
| battlezone98redux.exe-ghidra/** | Ghidra project skeleton with lock files | NONE | untrack lock/index files (`.lock`, `.lock~`, `~index.dat`) |
| BZR64_RESEARCH/** | x64/macOS recon reports + 2 python tools | own README | keep (research) |

### README drift relevant to installers (prose, noted only because it contradicts the installers)

README.md:181 still says "Placing only `winmm.dll` (and `openshim.ini`) into a stock install is a deliberately supported degraded configuration" -- after the split that is exactly the configuration every script now refuses (release.yml body, lines 404-414). README.md:91's Linux uninstall instruction leaves the loader/plugin behind.

## Performance notes

- install_windows.ps1:198-199 and Test-OpenShimDll (line 149) decode each candidate DLL twice (`ASCII.GetString` + `Unicode.GetString` of the whole file); with 2-3 game dirs that is a few MB of transient strings. Not worth changing on its own; Test-PackageShape already does the read-once/both-encodings pattern (Get-BinaryText) that could be shared.
- install_linux.sh:225 `tr | grep` streams the whole DLL through a pipe per artifact set; fine once the `-q` fix lands (it reads the whole file anyway then).
- tests/CMakeLists.txt compiles `shim_log_sink.cpp`/`shim_log_client.cpp`/`game_log_path.cpp` into five separate targets and `render_profile.cpp` into three; a small `bzr_test_support` STATIC library would cut Linux CI build time and the repetition.
- openshim_wrap.ps1:559 loads the entire ZIP into memory (`ReadAllBytes`) to split a >9 MB bundle; harmless at these sizes.

## Positive notes

- Bundle-first install: one `OpenShim-Suite.zip` + `.sha256`, regex-validated digest, verified before extraction, `release_metadata.json` tag/commit asserted in CI (Test-PackageShape `-ExpectedTag/-ExpectedCommit`), and version/identity of all three binaries checked against the tag (release.yml:184-195). Keep this.
- Refuse-before-touch: both installers validate every game dir for a foreign `winmm.dll` before writing anything (install_windows.ps1:540-546, install_linux.sh:544-551), and both re-check for Defender quarantine after a 3 s delay with per-file hashes.
- Player `openshim.ini` preserved by default with an explicit `OPENSHIM_RESET_INI` backup-and-reset; `openshim.ini.canonical` always refreshed for runtime migration.
- Secret hygiene: webhook validated by prefix, written mode 600 on Linux, `upload.conf` gitignored twice, pre-commit guard installed by both setup scripts with CRLF normalisation, and `.gitattributes` forcing LF on `*.sh`.
- The Windows wrapper (`openshim_wrap.ps1`) fences every pre-launch step in try/catch and always launches the game; the `.bat` falls back to a plain launch when the `.ps1` is quarantined. The Linux wrapper's `clean_env` (strip Steam's LD_PRELOAD/LD_LIBRARY_PATH for helpers) and outbox/park/retry design are solid and are exercised by `tests/openshim_wrap_coredump_tests.sh` in the Linux lane.
- CI proves the ABI, not just the compile: export-parity against `tests/winmm_export_baseline.txt`, the BZLoader host lifecycle test with session-id-stamped log validation, and `patch_registration_tests` cross-checking patches.json/patches.h/patcher.cpp/bzr_hooks.cpp as text.
- tests/CMakeLists.txt keeps Windows-only targets behind `if(WIN32 AND MSVC)` with a stated reason each time, so the Linux lane stays honest about what it covers.
