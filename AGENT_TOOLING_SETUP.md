# OpenShim Agent RE Tooling Setup

Use this only to install, repair, or reproduce the Battlezone reverse-engineering toolchain on a Windows PC. For normal RE work after setup, use `AGENT_TOOLING.md`.

## Requirements
- Windows with `python` and `winget` on `PATH`.
- A clone of OpenShim.
- Ghidra is strongly recommended but may require separate/manual installation.

## Install / Refresh
From the repo root:

```powershell
.\scripts\install_agent_re_tooling.ps1
```

The installer is intended to be rerunnable. It installs/refreshes supported packages, writes stable `bzr-*` wrappers into `<USER_HOME>\bin`, updates the marked Battlezone entries in `<USER_HOME>\.codex\config.toml`, and configures the persistent local Ghidra MCP service.

Common optional parameters:

```powershell
.\scripts\install_agent_re_tooling.ps1 `
  -RepoRoot "<REPO_ROOT>" `
  -GameDir "<GAME_ROOT>" `
  -GhidraInstallDir "<GHIDRA_ROOT>" `
  -UnrealEngineDir "<UE_ROOT>" `
  -RetoolkitDir "<RETOOLKIT_ROOT>"
```

Supported environment overrides include `BZR_GAME_DIR`, `BZR_GAME_EXE`, `BZR_REDUX_GAME_DIR`, `BZR_REDUX_EXE`, `BZR_GHIDRA_INSTALL_DIR`, `BZR_CDB_PATH`, `BZR_WINDBG_ROOT`, `BZR_X32DBG_PATH`, `UE_ROOT`, and `UE_ENGINE_DIR`.

## What It Provides
The automated stack covers the agent-facing tools needed for most work:
- Ghidra/pyghidra MCP and persistent local service.
- Redux debugger bridge plus WinDbg `cdb` and x32dbg wrappers.
- Frida, angr, ghidriff, Qiling, Rizin/Cutter, Detect It Easy.
- Process Monitor / Process Explorer.
- CMake, Ninja, 7-Zip, Visual Studio compiler/linker/dumpbin/IDE wrappers.
- Retoolkit CLI surfaces such as capa/FLOSS/YARA/packer/PE triage helpers.
- Unreal editor/build automation wrappers when Unreal is installed.

After setup, prefer the `bzr-*` commands described in `AGENT_TOOLING.md` rather than raw package paths. Do not spend context enumerating every wrapper unless troubleshooting installation.

## Ghidra
If Ghidra is not installed automatically, install it separately and either pass `-GhidraInstallDir` or set `BZR_GHIDRA_INSTALL_DIR` / `GHIDRA_INSTALL_DIR`.

The preferred MCP model is a persistent local service:
- endpoint: `http://127.0.0.1:8765/mcp`
- startup wrapper: `bzr-ghidra-mcp-service.cmd`
- user startup entry: `BzrGhidraMcp`

This avoids per-session Ghidra startup/handshake cost. Restart an already-running agent session if it still caches an older MCP configuration.

## Human-Assisted Extras
These are optional and should not block normal agent work:
- Ghidrathon — Python inside the Ghidra GUI.
- ReClass.NET — live class/vtable reconstruction.
- API Monitor — manual Windows API/COM tracing.
- x32dbg/Cutter/Process Explorer — useful GUI inspection surfaces, but generally secondary to agent-friendly CLI/MCP tools.

## Validation
After setup, validate only the surfaces relevant to the machine/task. A practical smoke set is:

```powershell
bzr-ghidra-mcp.cmd --help
bzr-redux-debug.cmd doctor
bzr-frida-ps.cmd --help
bzr-ghidriff.cmd --help
bzr-qiling.cmd version
bzr-rizin.cmd -v
bzr-cdb32.cmd -version
bzr-diec.cmd $env:BZR_GAME_EXE
bzr-cmake.cmd --version
bzr-ninja.cmd --version
bzr-cl.cmd /Bv
```

If Ghidra and a valid Redux executable are configured, confirm the MCP endpoint is reachable and then use `AGENT_TOOLING.md` to choose the smallest tool for each RE question.
