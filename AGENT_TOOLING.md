# OpenShim RE Tool Selection

Read this only for reverse-engineering, binary-analysis, runtime-probing, signature, PDB, or native-hook work. Ordinary docs/API/build tasks do not need it.

Prefer the stable `bzr-*` wrappers on `PATH` instead of package-specific install paths. If a wrapper is missing/broken or the toolchain must be installed on another PC, use `AGENT_TOOLING_SETUP.md`.

## Choose the Smallest Useful Tool
- **Ghidra MCP (`ghidra`) / `bzr-ghidra-mcp.cmd`** — first choice for functions, symbols, xrefs, entry bytes, disassembly, decompiler output, and project-backed static analysis.
- **Redux debugger (`redux_debug`) / `bzr-redux-debug.cmd`** — launch/settle/read/terminate workflows and runtime-byte verification. Use `--backend native` for a persistent live target, then read from the saved PID (or pass `--pid` explicitly). The `cdb` backend is useful for an isolated startup probe, but an unsupplied-PID read intentionally relaunches the game and is not evidence from a previously launched live session.
- **`bzr-cdb32.cmd`** — direct 32-bit WinDbg CLI work when the debugger bridge is insufficient.
- **Frida (`bzr-frida*.cmd`)** — fast live instrumentation, argument/value logging, API tracing, and hook experiments without rebuilding OpenShim.
- **`bzr-ghidriff.cmd`** — build-to-build binary diffing; use when determining whether executable revisions actually changed a subsystem.
- **Rizin (`bzr-rizin.cmd`, `bzr-rz-bin.cmd`, `bzr-rz-asm.cmd`)** — fast shell-side PE/section/import/export/string/disassembly triage.
- **Detect It Easy (`bzr-diec.cmd`)** — compiler/packer/signature triage before heavier analysis.
- **Retoolkit triage (`bzr-capa.cmd`, `bzr-floss.cmd`, `bzr-yara.cmd`, `bzr-entropy.cmd`, `bzr-pe-sieve.cmd`, `bzr-goresym.cmd`, `bzr-redress.cmd`)** — use a bounded, relevant subset for capabilities, recovered strings, rule matches, entropy/packing, or process/in-memory inspection. Keep raw output on disk; summarize only decision-relevant evidence.
- **angr / Qiling (`bzr-angr.cmd`, `bzr-qiling.cmd`)** — symbolic/path exploration or offline/emulated execution when static/dynamic inspection is insufficient.
- **ProcMon (`bzr-procmon.cmd`)** — startup/load-path, file, registry, and DLL activity. Scripted capture/export is agent-friendly; interactive filter tuning may need human help.
- **x32dbg, Cutter, Process Explorer, ReClass.NET, API Monitor** — primarily human-assisted surfaces; use only when they add value beyond the autonomous tools above.

## Useful Repo Surfaces
The decompiler corpus (`reverse_engineering/repo_corpora/bzr_gog_best_effort/`), the PDB-derived corpus zips (`reverse_engineering/corpus_artifacts/`) and the 2016 prerelease executables are git-ignored here and never committed: this repository is public. They live in the private `Battlezone_Source` repository under `BZ1/Redux/openshim_re_corpus/`; run `reverse_engineering/Restore-ReCorpus.ps1` to copy them into a checkout.

Before writing one-off tooling, check whether these already cover the task:
- `scripts/ghidra_mcp_bz98.py` — Battlezone Ghidra/MCP wrapper.
- `scripts/redux_debug_bridge.py` — debugger launch/read/probe/terminate + MCP bridge.
- `scripts/qiling_cli.py` — Qiling CLI bridge.
- `reverse_engineering/capture_runtime_layout.ps1` — runtime-layout capture.
- `reverse_engineering/run_best_effort_pipeline.py` — reusable RE pipeline.
- Subsystem-specific `reverse_engineering/run_*_probe.*` scripts — prefer an existing probe when it matches the target.
- `reverse_engineering/tooling_smoke_pipeline.ps1` — bounded offline triage that writes a compact report plus raw artifacts under ignored `reverse_engineering/tooling_smoke/`.

## Model Formats (SDF/VDF/GEO/ANIM, Ogre mesh/skeleton)
Never hand-roll a reader or writer for these formats. Use the sibling libraries:
- **Read:** Battlezone98_Modding_Toolbox `battlezone/meshes/legacy.py` (`read_sdf`, `read_vdf`, `read_geo`, `AnimSequence`, `AnimTrack`). Its `legacy_port.py` handles cockpit and person animation.
- **Read and write:** BZ98RBlenderToolKit `bz98tools/bzrmodelporter/` (`bzbwd2.py` + `bzbwd2_serializer.py` for SDF/VDF, `bzgeo*`, `ogremesh*`, `ogreskeleton*`). To import it without Blender, put `bz98tools/` on `sys.path` and import `bzrmodelporter.*`, because the package root imports `bpy`.

If one of them is missing something, fix it in that repository, or report the gap. Campaign Reimagined imports both through `Tools/bzmodellibs.py`.

## Practical Workflows

- **Before a new patch/signature:** qualify the PE with static triage, locate semantics with Ghidra, then run a native live launch and capture the target bytes from its PID. Compare expected bytes/build facts before writing a patch.
- **For a one-shot startup/base-image check:** use `bzr-redux-debug.cmd probe --backend cdb ...`. It terminates after the dump; do not describe it as a settled live-runtime capture.
- **For a behavior/argument question:** begin with a small Frida trace or existing subsystem probe; graduate to cdb/x32dbg only when a breakpoint or exception context is necessary.
- **For executable-version drift:** first compare PE identity, then use ghidriff; confirm any candidate correlation with bytes and runtime behavior before reusing it.
- **For a screenshot of a live run:** set `OPENSHIM_FRAME_CAPTURE=1500,4000,8000` before launch. OpenShim writes those rendered world frames as `openshim_frame_NNNNN.png` next to the exe and logs `[FRAME-CAPTURE]`. It reads the Ogre render window back, so it works headless (session locked or disconnected) where `PrintWindow`/`CopyFromScreen` return black. Requires the DX11 renderer with the terrain-proxy Ogre exports resolved.
- **For a fixed headless capture size:** also set `OPENSHIM_FRAME_CAPTURE_SIZE=2560x1440` (strict `widthxheight`, bounds 320..7680 by 200..4320). The capture listener resizes its own window once before rendering, with no activation, movement, camera writes or saved-config changes. Windowed DX11 only; missing exports, fullscreen and foreign windows are declined. `OPENSHIM_UNCLAMP_WINDOW=1` can help initial creation, but alone may still leave a disconnected desktop's width clamp. Check `[FRAME-CAPTURE] client-size ... actual=...` and the PNG dimensions.
- **Before any live launch, check the foreground process and input idle time.** `Assert-BZRSafeToLaunch` only looks for another BZR process; if the user is in another game, don't launch. Tell them what's waiting instead.
- **Live capture checklist:** reuse an existing capture script first. `capture_grizzly_reference.ps1 -CRMission` fails when the terrain name differs from the mission name. Runtime logs are in `<game>\logs\`. Some missions (`bdmisn02cr`) wait at the menu for Space on a CLI launch. `powershell -File` doesn't split array arguments.
- **Coordinates:** `CameraObject` offsets are centimetres. World coordinates come from `.trn [Size]`; pack `boundsMeters` are native render coordinates.
- **Judging frames:** motion checks compare same-camera frames as a timeline with PNG mtimes, with no per-tick teleport. Before calling a frame dark, read CR's `Environment.Init` lighting and take a real control: `TerrainHdEnabled = 0` is the stock control (a bogus manifest doesn't disable HD), and the log must show no `TERRAIN` lines. A shader or parameter change gets stills from every planet, not only the one it targets.
- **Odd render result or no captured frames:** read `<game>\logs\BZOgreLogfile.log` first. An Ogre exception thrown every frame (for example `InvalidParametersException`) stops frame listeners, and `openshim.log` won't show it.
- **Tests:** `cmake -S tests -B <dir> -G "Visual Studio 17 2022" -A x64`, then `cmake --build <dir> --target <test> --config Debug`, then `ctest --test-dir <dir> -C Debug -R <test> --output-on-failure`. A shader-text change touches `terrain_paint_tests` as well as `terrain_paint_gpu_tests`, so run both before pushing.
- **Building:** the shim builds with MSBuild on `Plugin_OpenShim.vcxproj` (there is no root CMake). Read current code from a worktree at `origin/main`, because the canonical checkout may be stale.
  - The window size under `BZR_FORCE_WINDOWED=1` is not fixed. A short landscape window lets cockpit overlays such as the radar map cover the ground, so look at a frame before scoring it, and rerun if the view you need is hidden.
  - Prefer `OPENSHIM_FRAME_CAPTURE_SIZE=1920x1080` for fixed-size captures. It uses `SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSENDCHANGING` with the window's measured borders. On a small virtual desktop, `WM_GETMINMAXINFO` can clamp a regular resize to the desktop size. Confirm the resulting PNG dimensions instead of relying on Ogre.cfg's requested mode.
  - To get a frame with no HUD, take it from a cinematic camera (`CameraReady()`, then `CameraObject(...)` every frame) in a capture-only copy of the mission Lua.
  - Launch a Campaign Reimagined mission through the mod's crsetup slot: copy the mission's `.bzn` and its terrain's `.trn/.hg2/.mat/.lgt` (the `TerrainName` stem in the bzn, for example `bdmisn07` for `bdmisn07cr.bzn`) over `mods\3686673790\crsetup.*`, launch `crsetup.bzn /nointro /renderer:dx11`, and restore the slot afterwards (`capture_grizzly_reference.ps1 -CRMission` does the copy). Redux runs the Lua named by the bzn's embedded `msn_filename`, so also rewrite `msn_filename = <mission>.bzn` to `crsetup.bzn` in the copy and put the mission Lua (plus any capture driver) in `crsetup.lua`. A command-line launch has no mod `require` path, so start that file with the stock crsetup's `require("RequireFix").Initialize({"campaignReimagined","3686673790"})`. Otherwise there is no CR runtime, so stock skies and weather show:
    - A bare `<mission>.bzn` loads `<first 8 chars>.lua` (BZLogger: `No Lua script "bdmisn01.lua"` for `bdmisn01cr.bzn`), and `require` of mod modules fails.
    - The mod-relative path `mods/3686673790/<mission>.bzn` fails with `Could not load "mods/3686673790": Permission denied`.
    - Confirm `exu.log` was written by the run before you trust a frame.
  - Lua `print()` lines go to `logs\BZLogger.txt` with no line break, so each is glued to the next timestamp. Strip `\d{4}-\d\d-\d\d \d\d:\d\d:\d\d\.\d{6} ?` before you grep.
- **Runtime logs** (`openshim.log` and the other logs) are in `<game>\logs\`, not next to the exe.
- **Terrain pack builds** (`scripts/terrain-packs/build-world-packs.sh`) need `TRO_DIR` set to the extracted TRO campaign maps (normally `%USERPROFILE%\Documents\TerrainPaintOut\zfsmaps\tro_cam`). Without it, the build fails with "<map> has no CR, stock or TRO_DIR". Python steps that use PIL must run without `-I`, which hides user site-packages.
- **For loading/filesystem/environment issues:** use ProcMon. Do not use static disassembly to infer a load path when a filtered capture can answer it directly.
- **For unattended cdb crash capture (repeated harness runs):**
  - The game is 32-bit: use the x86 cdb (`bzr-cdb32.cmd`), or dumps and stacks come out wrong.
  - Put the handlers in a script file (`-cf <file>` or `$$><file`). In PowerShell, pass any inline `-c` string in single quotes so `$`, `;` and backticks reach cdb intact.
  - Every command path must end in `g` (init script, exception handlers), `gc` (breakpoint hit scripts) or `qd`. A path with none of these leaves the game frozen at the break. The init script must end in `g`, because a launched target stops at the initial breakpoint.
  - Handle every break type the run can raise: `sxe -c "..." -c2 "..." av` (first and second chance), `sxe bpe` (break instruction, 0x80000003) and `sxe c0000374` (heap corruption). Each handler prints its own distinct marker line, then dumps and quits with `qd`. The game raises handled first-chance AVs, so a first-chance AV is a crash only once its stack has been classified.
  - If cdb was killed rather than exiting via `qd`, the game can be left suspended. For a game this task launched, resume it with `cdb -pv -p <pid> -c '~*m;~*;qd'` and repeat while `~*` still shows a non-zero suspend count. Then stop it with `Stop-BZRGame -Id <pid>` (dot-source `reverse_engineering/BZRHarness.ps1` first). This recovery path has only been used once; verify the game actually resumed.
- **For scoring crash logs:** match the handlers' markers anchored to the start of a line (for example `^=== (FIRST CHANCE AV|SECOND CHANCE|BREAK)`). Classify each event from the lines that follow it, not from the whole log. Unanchored matches hit cdb's own echo of the `sxe`/script text. Before trusting any rate, validate the detector on one known-clean log and one known-crash log.
- **Before arming a hook on a game state** (for example a run state from `SetRunning`): confirm in a real run log that every exit path you care about reaches that state. In harness runs on 2026-10-28, quitting to desktop after a completed mission left the run state at `RUN_WAS_SUCCESS` and never reached `RUN_WAS_EXITED`, so a hook armed on `RUN_WAS_EXITED` never ran. For exit-time work, prefer a seam that every exit passes through, such as the exe's IAT import of `Ogre::Root::~Root` (`??1Root@Ogre@@QAE@XZ` from `OgreMain.dll`; see `RootDestructorExitSeam` in `src/patches/lifecycle_seams.cpp`).
- **For A/B crash-rate comparisons:** run at least 8 runs per arm (more for rare crashes) and interleave the arms. Report runs that crashed early separately from runs that reached the measured phase (for example exit). An early crash hides any later crash, so small or unsplit samples give false dependence verdicts.

## Runtime / Safety Rules
- Static addresses, decompiler output, leaked-PDB hints, and runtime bytes are different evidence classes; corroborate them rather than treating one as authoritative for all builds.
- For leaked/private PDB work, follow `reverse_engineering/private_pdb_semantic_ranking.md`; same-RVA equality alone is not identity evidence.
- For Steam runtime bytes, allow SteamStub/runtime settling before comparing against the GOG/static baseline.
- A native patch must fail closed when the expected build, signature, bytes, or object lifetime cannot be validated.
- Record the command, executable hash/build identity, process PID (for live work), addresses read, and tool/backend in the task evidence. Never promote a one-shot probe, static address, or unvalidated PDB hint to live-runtime proof.
- Prefer existing catalog/pattern infrastructure over scattering raw addresses through feature code.
- Never start a harness run while any other `battlezone98redux` process is running, including the user's own game. Never attach to, suspend, or stop a game process this task did not launch.

## Tool Availability
The installed toolchain normally includes Ghidra/pyghidra, the Redux debugger bridge, WinDbg/cdb, Frida, angr, ghidriff, Qiling, Rizin/Cutter, Detect It Easy, Sysinternals, LLVM/MSVC utilities, and `bzr-*` build/archive/triage wrappers. Do not load or enumerate the full installation inventory unless a setup/repair task requires it; `AGENT_TOOLING_SETUP.md` is authoritative for installation and environment overrides.
