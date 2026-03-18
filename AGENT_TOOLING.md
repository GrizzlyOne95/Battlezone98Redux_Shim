# Agent RE Tooling

This file is the local reverse-engineering and agent-tooling inventory for the
Battlezone workspace on this machine.

Use this together with [AGENTS.md](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/AGENTS.md).

## Default Targets

- Primary local game install: `%USERPROFILE%\Documents\Battlezone 98 Redux`
- Baseline/reference install also available on some tasks: `C:\GOG Games\Battlezone 98 Redux`
- For current work in this repo, do not assume a Steam-specific runtime path is
  needed unless the task explicitly says so.

## Command Surface

Prefer the stable wrappers in `C:\Users\istuart\bin`. They are already on
`PATH` in this environment.

### Ghidra / MCP

- `bzr-ghidra-mcp.cmd`
  - Wrapper around `pyghidra_mcp`.
  - Default project path: [pyghidra_mcp_projects](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/pyghidra_mcp_projects)
  - Default project name: `BZ98_Redux`
  - Default binary resolution order:
    1. `%USERPROFILE%\Documents\Battlezone 98 Redux\battlezone98redux.exe`
    2. `%USERPROFILE%\Downloads\Battlezone 98 Redux\battlezone98redux.exe`
    3. `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
  - Use for: entry bytes, disassembly, function lookup, symbols, xrefs, Ghidra project-backed binary queries.
  - Help: `bzr-ghidra-mcp.cmd --help`

### Debugger Bridge

- `bzr-redux-debug.cmd`
  - Wrapper around [redux_debug_bridge.py](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/scripts/redux_debug_bridge.py)
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
  - Current caveat:
    - the WinDbg `cdb` backend is installed and can launch Redux, but the
      Python-side `OpenProcess` read path still needs hardening for that child
      process shape on this machine. Treat the bridge as installed and useful,
      but validate memory-read results before relying on it for patch-safe byte
      capture.

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
    - `bzr-frida.cmd -f "C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe"`
    - `bzr-frida-trace.cmd -f "C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe" -i MessageBoxA`

### angr

- `bzr-angr.cmd`
  - Wrapper to the installed angr CLI
  - Use for:
    - decompile/disassemble from the command line
    - scripted CFG/path exploration
    - symbolic-execution experiments
  - Example:
    - `bzr-angr.cmd --help`

### Qiling

- `bzr-qiling.cmd`
  - Wrapper to [qiling_cli.py](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/scripts/qiling_cli.py)
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
    - `bzr-rz-bin.cmd -I "C:\Users\istuart\Documents\Battlezone 98 Redux\battlezone98redux.exe"`

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

These are installed and usable from the local Python 3.13 environment.

- `pyghidra-mcp`
  - Ghidra-backed MCP/CLI analysis server
- `pyghidra`
  - Python bridge into Ghidra
- `ghidrecomp`
  - Best-effort decompilation helpers
- `angr`
  - Static + symbolic binary analysis
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
  - `C:\ghidra_12.0.4_PUBLIC`

## Repo Scripts Worth Reusing

Prefer these before inventing a one-off script if they already cover the task.

- [ghidra_mcp_bz98.py](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/scripts/ghidra_mcp_bz98.py)
  - Battlezone-specific wrapper for `pyghidra_mcp`
- [redux_debug_bridge.py](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/scripts/redux_debug_bridge.py)
  - launch/read/terminate bridge, also exposes MCP mode
- [qiling_cli.py](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/scripts/qiling_cli.py)
  - small Qiling CLI bridge
- [capture_runtime_layout.ps1](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/capture_runtime_layout.ps1)
- [run_misn03_chunk_probe.ps1](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/run_misn03_chunk_probe.ps1)
- [run_best_effort_pipeline.py](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/reverse_engineering/run_best_effort_pipeline.py)

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
- Use angr or Qiling when the question is:
  - path exploration
  - symbolic constraints
  - emulated execution
  - offline behavior experiments
- Use Rizin / `rz-bin` for fast shell-side triage before opening a heavier GUI.
- Prefer the `bzr-*` wrappers over raw install paths so future package updates
  only need one wrapper fix.
