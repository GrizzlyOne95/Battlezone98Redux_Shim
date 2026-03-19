# Agent Tooling Setup

This file is the portable setup guide for the Battlezone reverse-engineering
toolchain on a different Windows PC.

Use this when you want the same agent-capable tooling stack on another machine
without copying machine-specific absolute paths from the current workstation.

## What This Sets Up

- Ghidra MCP wrapper for Battlezone binaries
- Debugger bridge wrapper and MCP server
- WinDbg `cdb` 32-bit CLI
- x32dbg wrapper
- Frida CLI wrappers
- angr CLI wrapper
- ghidriff CLI wrapper
- Qiling wrapper
- Rizin CLI wrappers
- Cutter GUI wrapper
- Detect It Easy CLI and GUI wrappers
- Process Monitor wrapper
- Process Explorer wrapper
- Codex MCP config entries for:
  - `ghidra`
  - `redux_debug`

## Requirements

- Windows
- `python` on `PATH`
- `winget` on `PATH`
- a clone of this repo
- optional but strongly recommended: a Ghidra install

## One-Command Install

From a PowerShell prompt in the repo:

```powershell
.\scripts\install_agent_re_tooling.ps1
```

That script installs the free packages it can acquire automatically:

- `Microsoft.WinDbg`
- `x64dbg.x64dbg`
- `Rizin.Rizin`
- `Rizin.Cutter`
- `horsicq.DIE-engine`
- `Microsoft.Sysinternals.ProcessMonitor`
- `Microsoft.Sysinternals.ProcessExplorer`
- Python packages:
  - `pyghidra-mcp`
  - `angr`
  - `frida`
  - `frida-tools`
  - `qiling`
  - `ghidriff`

It also writes stable `bzr-*` wrappers into `%USERPROFILE%\bin`, adds that
directory to the user `PATH`, and updates `%USERPROFILE%\.codex\config.toml`.

## Paths That Commonly Vary By PC

These are intentionally configurable:

- repo clone root
- game install directory
- explicit game executable path
- Ghidra install directory
- user bin directory
- Codex config path

The installer supports parameters:

```powershell
.\scripts\install_agent_re_tooling.ps1 `
  -RepoRoot "D:\src\Battlezone98Redux_Shim" `
  -GameDir "D:\Games\Battlezone 98 Redux" `
  -GhidraInstallDir "D:\tools\ghidra_12.0.4_PUBLIC"
```

## Environment Variable Overrides

The repo tooling also honors these user or process environment variables:

- `BZR_GAME_DIR`
- `BZR_GAME_EXE`
- `BZR_REDUX_GAME_DIR`
- `BZR_REDUX_EXE`
- `BZR_GHIDRA_INSTALL_DIR`
- `BZR_CDB_PATH`
- `BZR_WINDBG_ROOT`
- `BZR_X32DBG_PATH`

These are useful when:

- the game is not under `%USERPROFILE%\Documents\Battlezone 98 Redux`
- you want to force a specific executable
- Ghidra is installed somewhere other than `C:\ghidra_12.0.4_PUBLIC`
- you want to pin the debugger backend to a specific install

## Ghidra Note

`winget` does not currently expose a good Ghidra package on this machine, so
the installer does not auto-download Ghidra.

Install Ghidra separately, then either:

- pass `-GhidraInstallDir ...` to the installer, or
- set `BZR_GHIDRA_INSTALL_DIR`, or
- set `GHIDRA_INSTALL_DIR`

## What Agents Should Use After Setup

Once installed, agents should prefer these stable wrappers from `%USERPROFILE%\bin`:

- `bzr-ghidra-mcp.cmd`
- `bzr-redux-debug.cmd`
- `bzr-frida.cmd`
- `bzr-frida-ps.cmd`
- `bzr-frida-trace.cmd`
- `bzr-angr.cmd`
- `bzr-ghidriff.cmd`
- `bzr-qiling.cmd`
- `bzr-rizin.cmd`
- `bzr-rz-bin.cmd`
- `bzr-rz-asm.cmd`
- `bzr-cutter.cmd`
- `bzr-cdb32.cmd`
- `bzr-x32dbg.cmd`
- `bzr-die.cmd`
- `bzr-diec.cmd`
- `bzr-procmon.cmd`
- `bzr-procexp.cmd`

The detailed local usage guide for agents lives in `AGENT_TOOLING.md` in the
repo root after setup.

## Tooling Categories

Use this split when deciding what to automate on another PC.

- Autonomous or mostly autonomous:
  - `ghidra` MCP
  - `redux_debug` bridge
  - Frida CLIs
  - `angr`
  - `ghidriff`
  - `diec`
  - Rizin CLIs
  - Qiling wrapper
- Partially agent-usable:
  - `Process Monitor`
    - usable for scripted capture, backing-file collection, and export flows
    - still benefits from a human when refining filters interactively
  - `Process Explorer`
    - callable, but mainly useful as a human inspection surface
- Human-driven or manual-install extras:
  - `Ghidrathon`
    - useful inside Ghidra, but not the first agent interface in this repo
  - `ReClass.NET`
    - useful for live class-layout reconstruction, but not unattended
  - `API Monitor`
    - strong manual tracing tool, weak autonomous-agent surface

## Manual Extras Not Automated By This Script

These are worth documenting for another PC, but they are not currently installed
by `install_agent_re_tooling.ps1`.

- `Ghidrathon`
  - install as a Ghidra extension if you specifically want Python 3 inside the
    Ghidra GUI
- `ReClass.NET`
  - install manually if the task is live class/vtable reconstruction
- `API Monitor`
  - install manually if the task is targeted Win32 or COM tracing without
    writing Frida scripts first

## Re-Running Safely

The installer is intended to be re-runnable.

- already-installed winget packages are skipped
- Python packages are refreshed idempotently
- wrapper files are regenerated
- Codex config entries are replaced inside a marked block

## Recommended Validation

After install, open a fresh shell and run:

```powershell
bzr-ghidra-mcp.cmd --help
bzr-redux-debug.cmd doctor
bzr-frida-ps.cmd --help
bzr-angr.cmd --help
bzr-ghidriff.cmd --help
bzr-qiling.cmd version
bzr-rizin.cmd -v
bzr-rz-bin.cmd -h
bzr-cdb32.cmd -version
bzr-diec.cmd $env:BZR_GAME_EXE
Get-Command bzr-procmon.cmd
```

If `Ghidra` is installed and `BZR_GAME_EXE` points at a valid executable, the
MCP wrapper should be ready for Codex and CLI use immediately.
