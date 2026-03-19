# Agent RE Tooling

This file is the local reverse-engineering and agent-tooling inventory for the
Battlezone workspace on this machine.

Use this together with [AGENTS.md](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/AGENTS.md).

## Default Targets

- Configured local game install: `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux`
- Configured game executable via `BZR_GAME_EXE`:
  `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\battlezone98redux.exe`
- If this machine later gains a second runtime install, prefer the configured
  `BZR_GAME_DIR` / `BZR_GAME_EXE` environment variables over stale hardcoded
  assumptions.

## Command Surface

Prefer the stable wrappers in `%USERPROFILE%\bin`. The installer adds that
directory to the user `PATH`.

## Agent Autonomy

Use this split before choosing a tool.

- Independent or mostly independent:
  - `ghidra` MCP
  - `redux_debug`
  - Frida CLIs
  - `angr`
  - `ghidriff`
  - `diec`
  - Rizin CLIs
  - Qiling wrapper
- Partial / mixed:
  - `Process Monitor`
    - good for scripted capture, backing-file collection, and export
    - still benefits from a human when interactively refining filters
  - `Process Explorer`
    - callable, but mainly a human inspection surface
- Human-driven:
  - `x32dbg`
  - `Cutter`
  - `ReClass.NET`
  - `API Monitor`
  - `Ghidrathon` inside the Ghidra GUI

### Ghidra / MCP

- `bzr-ghidra-mcp.cmd`
  - Wrapper around `pyghidra_mcp`.
  - Default project path: [pyghidra_mcp_projects](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/pyghidra_mcp_projects)
  - Default project name: `BZ98_Redux`
  - Default binary resolution order:
    1. `BZR_GAME_EXE` / `BZR_REDUX_EXE` if set
    2. `%USERPROFILE%\Documents\Battlezone 98 Redux\battlezone98redux.exe`
    3. `%USERPROFILE%\Downloads\Battlezone 98 Redux\battlezone98redux.exe`
    4. `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
  - Use for: entry bytes, disassembly, function lookup, symbols, xrefs, Ghidra project-backed binary queries.
  - Help: `bzr-ghidra-mcp.cmd --help`

### Debugger Bridge

- `bzr-redux-debug.cmd`
  - Wrapper around [redux_debug_bridge.py](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/scripts/redux_debug_bridge.py)
  - Subcommands:
    - `doctor`
    - `launch`
    - `read`
    - `probe`
    - `status`
    - `terminate`
    - `mcp`
  - Use for:
    - launch Redux under a controlled backend
    - wait for settle
    - read process memory
    - tear down the session
  - Examples:
    - `bzr-redux-debug.cmd doctor`
    - `bzr-redux-debug.cmd probe 0x005E82B0 --backend cdb --wait-seconds 8 --length 16`
    - `bzr-redux-debug.cmd launch --backend cdb --wait-seconds 1`
    - `bzr-redux-debug.cmd read 0x005E82B0 --length 16`
  - Current behavior:
    - the WinDbg `cdb` backend is the preferred path for hook-byte capture on
      this machine.
    - `probe --backend cdb` captures bytes with in-debugger `db` output, and
      `read` against a saved `cdb` session relaunches through `cdb` instead of
      depending on Python `OpenProcess` against the child process.
    - use the `native` backend only when you explicitly want a persistent PID
      session and plain `ReadProcessMemory`.

### WinDbg / x64dbg

- `bzr-cdb32.cmd`
  - Stable wrapper to WinDbg package `x86\cdb.exe`
  - Verified: `bzr-cdb32.cmd -version`
- `bzr-x32dbg.cmd`
  - Stable wrapper to `x32dbg.exe`
  - Use for 32-bit GUI debugging of `battlezone98redux.exe`

### Frida

- `bzr-frida.cmd`
- `bzr-frida-ps.cmd`
- `bzr-frida-trace.cmd`
  - Stable wrappers to the Python-installed Frida CLIs
  - Use for:
    - live instrumentation
    - API tracing
    - quick user-mode probes
    - function attach/replace experiments without rebuilding the shim
  - Examples:
    - `bzr-frida-ps.cmd --help`
    - `bzr-frida.cmd -f $env:BZR_GAME_EXE`
    - `bzr-frida-trace.cmd -f $env:BZR_GAME_EXE -i MessageBoxA`

### angr

- `bzr-angr.cmd`
  - Wrapper to the installed angr CLI
  - Use for:
    - decompile/disassemble from the command line
    - scripted CFG/path exploration
    - symbolic-execution experiments
  - Example:
    - `bzr-angr.cmd --help`

### ghidriff

- `bzr-ghidriff.cmd`
  - Wrapper to the installed `ghidriff` CLI
  - Use for:
    - build-to-build binary diffing
    - verifying whether a subsystem really changed between executable revisions
    - producing markdown diff reports from Ghidra-backed analysis
  - Example:
    - `bzr-ghidriff.cmd --help`
  - Notes:
    - expects a working Ghidra install
    - best used against old/new binary pairs, not as a general disassembler

### Qiling

- `bzr-qiling.cmd`
  - Wrapper to [qiling_cli.py](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/scripts/qiling_cli.py)
  - Subcommands:
    - `version`
    - `run-python`
  - Use for:
    - Python-driven emulation work
    - running local Qiling scripts in the installed interpreter
  - Examples:
    - `bzr-qiling.cmd version`
    - `bzr-qiling.cmd run-python path\\to\\your_qiling_script.py -- arg1 arg2`
  - Note:
    - the installed Qiling package does not currently expose a standalone
      native CLI on this machine, so this wrapper is the supported entry point.

### Rizin / Cutter

- `bzr-rizin.cmd`
- `bzr-rz-bin.cmd`
- `bzr-rz-asm.cmd`
- `bzr-cutter.cmd`
  - Stable wrappers to the installed Rizin and Cutter binaries
  - Use for:
    - fast binary metadata inspection
    - section/import/export/string dumping
    - lightweight CLI reversing
    - GUI reversing in Cutter
  - Examples:
    - `bzr-rizin.cmd -v`
    - `bzr-rz-bin.cmd -I $env:BZR_GAME_EXE`

### Detect It Easy

- `bzr-diec.cmd`
- `bzr-die.cmd`
  - Stable wrappers to the installed Detect It Easy CLI and GUI
  - Use for:
    - fast PE triage
    - compiler/packer/signature checks
    - quick pre-analysis classification before heavier reversing
  - Example:
    - `bzr-diec.cmd $env:BZR_GAME_EXE`
  - Guidance:
    - prefer `bzr-diec.cmd` for agent work
    - use `bzr-die.cmd` only when a human wants the GUI

### Sysinternals

- `bzr-procmon.cmd`
  - Stable wrapper to `Procmon.exe`
  - Use for:
    - startup/load-path mysteries
    - file, registry, and DLL touch tracing
    - backing-file capture flows that can later be inspected or exported
  - Guidance:
    - useful to agents for scripted capture and export
    - a human still helps when interactively shaping filters
- `bzr-procexp.cmd`
  - Stable wrapper to `procexp.exe`
  - Use for:
    - loaded-module inspection
    - parent/child process confirmation
    - handle and thread inspection
  - Guidance:
    - primarily a human-operated inspection tool, not a first-choice autonomous surface

## Installed MCP Servers

Configured in `%USERPROFILE%\.codex\config.toml`:

- `ghidra`
  - Command: `python ...\scripts\ghidra_mcp_bz98.py`
  - Use this first for Ghidra-backed binary questions.
- `redux_debug`
  - Command: `python ...\scripts\redux_debug_bridge.py mcp`
  - Use this for launch/read/terminate style debugger-session automation.
- `linear`
  - Present globally, but not specific to this RE workflow.

## Python RE Packages Present

These are installed and usable from the local Python 3.12 environment.

- `pyghidra-mcp`
  - Ghidra-backed MCP/CLI analysis server
- `pyghidra`
  - Python bridge into Ghidra
- `ghidrecomp`
  - Best-effort decompilation helpers
- `angr`
  - Static + symbolic binary analysis
- `ghidriff`
  - Ghidra-backed binary diff engine
- `frida`
  - Dynamic instrumentation runtime
- `frida-tools`
  - Frida command-line tooling
- `qiling`
  - Emulation framework
- Supporting low-level packages already present through this stack include:
  - `capstone`
  - `keystone-engine`
  - `unicorn`
  - `pefile`
  - `pyelftools`
  - `minidump`

## Other Native Tooling Already Available

- LLVM tools in `C:\Program Files\LLVM\bin`
  - `llvm-pdbutil.exe`
  - `llvm-objdump.exe`
  - useful for PDB lookup and static disassembly from shell scripts
- Visual Studio / MSVC tools
  - `dumpbin.exe`
  - `link.exe`
  - `MSBuild.exe`
- Ghidra install
  - `C:\Users\iestu\Tools\ghidra_12.0.4_PUBLIC`
  - mirrored into `BZR_GHIDRA_INSTALL_DIR` and the Codex `ghidra` MCP entry
- Sysinternals
  - `Process Monitor`
  - `Process Explorer`
- Detect It Easy
  - portable WinGet install under `%LOCALAPPDATA%\Microsoft\WinGet\Packages`

## Optional Manual Extras

These are worth knowing about, but they are not currently part of the automated
installer flow in this repo.

- `Ghidrathon`
  - useful when you specifically want Python 3 scripting inside the Ghidra GUI
  - lower priority here because `pyghidra` and the Ghidra MCP cover most
    agent-first workflows already
- `ReClass.NET`
  - useful for rebuilding live native class layouts and vtables
  - human-assisted, not an unattended agent tool
- `API Monitor`
  - useful for fast manual Windows API and COM tracing
  - less attractive when Frida already covers the same question programmatically

## Repo Scripts Worth Reusing

Prefer these before inventing a one-off script if they already cover the task.

- [ghidra_mcp_bz98.py](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/scripts/ghidra_mcp_bz98.py)
  - Battlezone-specific wrapper for `pyghidra_mcp`
- [redux_debug_bridge.py](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/scripts/redux_debug_bridge.py)
  - launch/read/terminate bridge, also exposes MCP mode
- [qiling_cli.py](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/scripts/qiling_cli.py)
  - small Qiling CLI bridge
- [capture_runtime_layout.ps1](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/reverse_engineering/capture_runtime_layout.ps1)
- [run_misn03_chunk_probe.ps1](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/reverse_engineering/run_misn03_chunk_probe.ps1)
- [run_best_effort_pipeline.py](/c:/Users/iestu/Documents/GIT/BZR-OpenShim/reverse_engineering/run_best_effort_pipeline.py)

## Practical Guidance

- Use Ghidra MCP first when the question is:
  - function names
  - entry bytes
  - xrefs
  - disassembly
  - decompiler output
- Use `bzr-redux-debug` or `bzr-cdb32` when the question is:
  - runtime bytes
  - launch-time settle behavior
  - live addresses
  - process memory verification
- Use Frida when the question is:
  - hook viability
  - fast dynamic tracing
  - argument/value logging
  - live API interception without rebuilding `winmm.dll`
- Use `ghidriff` when the question is:
  - did this executable revision really change here
  - which functions moved or were rewritten between two builds
  - produce a reusable diff report for later review
- Use `diec` when the question is:
  - what compiler/packer/signature does this binary show
  - do quick triage before opening Ghidra
- Use `bzr-procmon` when the question is:
  - what files, registry keys, or DLLs did startup touch
  - what path or load-order issue happened at runtime
- Use angr or Qiling when the question is:
  - path exploration
  - symbolic constraints
  - emulated execution
  - offline behavior experiments
- Use Rizin / `rz-bin` for fast shell-side triage before opening a heavier GUI.
- Prefer the `bzr-*` wrappers over raw install paths so future package updates
  only need one wrapper fix.
