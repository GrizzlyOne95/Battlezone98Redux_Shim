# OpenShim installation and troubleshooting

This guide supplements the [quick start](../README.md). It covers the complete matched runtime suite, Windows maintenance actions, Linux/Proton installation, standalone installs, and uninstall/cleanup choices.

**Supported game version:** Battlezone 98 Redux **2.2.301**. Use the current [release](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/releases/latest) for normal play. A checkout of `main` may be newer than the latest release and is not automatically release-qualified.

## Before installing

- Close Battlezone 98 Redux completely before installing, repairing, updating, or uninstalling.
- Back up custom `openshim.ini` and `net.ini` if you have modified them. Normal Install/Update can deploy `net.ini` (backing up the previous file); Repair preserves an existing one.
- OpenShim requires the **matched** `winmm.dll`, `bzloader.dll`, `plugins/openshim.dll`, and `scripts/patches.json` set. Installing only the proxy DLL does not enable the runtime.
- The game executable is not rewritten. Supported game folders may contain `battlezone98redux.exe` (Steam) or `BZR.exe` (GOG); the Windows installer recognizes either filename.
- Windows may warn about the unsigned setup executable or hooking DLLs. Verify the published release and SHA-256 checksum before trusting the files. Do not disable antivirus globally.

## Windows: OpenShimSetup.exe (recommended)

1. Download [OpenShimSetup.exe](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/releases/latest/download/OpenShimSetup.exe).
2. Run it and choose a maintenance action. Detected Steam/GOG installations are listed; you can browse to another game folder or drag that folder onto the setup executable.
3. Confirm the target directory. No Windows game launch option is needed for a normal installation.

| Action | Behavior |
| --- | --- |
| **Install** | Installs the version embedded in the setup executable. A development build without an embedded release can fetch the latest published suite. |
| **Repair** | Restores missing/modified files from the **same version**; refuses to replace the installation with a different version. Preserves an existing `openshim.ini`, `net.ini`, and unrelated mod files. |
| **Update** | Downloads and verifies the **latest published release** rather than using the setup executable's embedded bundle. Refuses downgrades; does nothing if the same version is already installed. Use Repair for damage at the same version. |
| **Uninstall** | Removes OpenShim-owned deployed files and backups, preserving `openshim.ini`, `net.ini`, and logs by default. |

When uninstalling, an **unchecked** checkbox can additionally remove OpenShim settings, logs, crash dumps, and uploader data. This includes current-user `%LOCALAPPDATA%\openshim` and `%APPDATA%\openshim`, shared between all OpenShim installations for that Windows account. It does **not** delete `net.ini`, `BZLogger.txt`, unrelated game logs, or other mods. Remove a Steam upload-wrapper launch option yourself if previously configured.

### Windows automation

Choose a single action:

```powershell
OpenShimSetup.exe --install
OpenShimSetup.exe --repair
OpenShimSetup.exe --update
OpenShimSetup.exe --uninstall
```

For full cleanup in an unattended invocation:

```powershell
OpenShimSetup.exe --uninstall --purge-leftovers --quiet --no-pause
```

- `--quiet` skips the interactive action/folder menu (defaults to Install if no action was supplied).
- `--no-pause` avoids waiting for Enter and also makes the invocation non-interactive.
- Set `OPENSHIM_GAME_PATH` to operate on one game folder rather than all detected installs.
- `--purge-leftovers` is accepted **only** with `--uninstall`.

### Alternative PowerShell script installer

The one-liner below fetches the script from the **current `main` branch**, executes it locally, then downloads and verifies a matching published release ZIP. It is not an offline or no-download operation. Inspect the script if you prefer to review remote code before executing it.

```powershell
irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_windows.ps1 | iex
```

To download the script separately and see download/connection errors:

```powershell
$dst = Join-Path $env:TEMP 'openshim_install.ps1'
Invoke-WebRequest -UseBasicParsing -Uri 'https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_windows.ps1' -OutFile $dst
(Get-Item $dst).Length
powershell -NoProfile -ExecutionPolicy Bypass -File $dst
```

An error such as `Cannot bind argument to parameter 'Command'` from the piped one-liner usually means no script content reached `iex`. Corporate DNS, HTTPS inspection, filters, or blocking of `raw.githubusercontent.com` can cause this. The separate download reveals the underlying error.

The standalone script uninstaller is:

```powershell
irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_windows.ps1 | iex
```

To preview deletions or opt into cleanup, set environment variables **before** running the uninstaller script:

```powershell
$env:OPENSHIM_DRY_RUN = '1'          # Preview; do not delete
$env:OPENSHIM_PURGE_CONFIG = '1'     # Also remove openshim.ini and backups
$env:OPENSHIM_PURGE_LEFTOVERS = '1'  # Full OpenShim-only cleanup, including uploader data
```

Use only the setting(s) you intend. Remove the temporary environment settings afterward if you will run other installer actions from the same shell. `OPENSHIM_PURGE_LEFTOVERS` implies the config purge; neither removes shared `net.ini`.

### Defender and SmartScreen warnings

OpenShimSetup.exe is unsigned and native proxy DLLs can trigger security heuristics. A warning is **not proof** of a false positive. Compare hashes with the published `SHA256SUMS.txt`, review the release source/build information, and investigate detections before restoring a quarantined file or creating a narrow exclusion. Do not disable protection globally.

The **opt-in test-crew uploader** is separate from normal installation. When a webhook is configured, the Windows install script may attempt to add a Microsoft Defender folder exclusion for the current user's `%LOCALAPPDATA%\openshim` uploader directory, if the caller has sufficient privileges. Understand this change before opting in; it is not required for ordinary player installs.

## Linux: Steam with Proton

Use a host terminal, **not** a shell inside the Steam Snap sandbox.

For native Steam or Flatpak Steam:

```bash
curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --native
```

For Snap Steam:

```bash
curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --snap
```

Then, in **Steam → Battlezone 98 Redux → Properties → Launch Options**:

```text
WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%
```

The quotes are required: an unquoted `;` separates shell commands. If you are not using a separate `dsound` netcode proxy, use `WINEDLLOVERRIDES="winmm=n,b" %command%` instead.

If you maintain both native/Flatpak and Snap Steam installations, invoke the corresponding installer for each game installation you actually launch. The scripts download a verified matched Windows suite; Linux/Proton is not a native `.so` build.

To uninstall a native/Flatpak installation:

```bash
curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_linux.sh | bash -s -- --native
```

For Snap, substitute `--snap`. Add `--dry-run` to inspect the plan first or `--purge-config` if you also want to remove `openshim.ini`; `net.ini` and logs are retained. Clear the Steam launch option after uninstalling the proxy DLL.

### Linux/GOG under Wine or a compatible Proton prefix

The game and OpenShim still use **Win32** binaries. Point the Linux installer at the actual game directory using `--game-path` (an existing folder containing `BZR.exe` or `battlezone98redux.exe`):

```bash
curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --game-path '/path/to/Battlezone 98 Redux'
```

Configure the Wine/Proton prefix to load the native `winmm` proxy rather than its built-in equivalent. The precise launcher configuration depends on how GOG is run. Follow the [shared platform policy](BZR_PLATFORM_COMPATIBILITY.md) and validate the prefix before treating it as qualified.

## Standalone DLL-only installation and optional assets

A stock Redux 2.2.301 install can run OpenShim **without** the Campaign Reimagined/Workshop asset pack. The complete native loader chain and patch table are still required:

```text
<game directory>/winmm.dll
<game directory>/bzloader.dll
<game directory>/plugins/openshim.dll
<game directory>/scripts/patches.json
<game directory>/openshim.ini
```

Engine/gameplay/networking fixes do not require the Workshop pack. Native `ChunkMeshes` can generate fragments from source models without that pack, with external meshes retained as fallback for unsupported content. Enhanced renderer features need the compatible resource files; absent/partial/mismatched resources cause dependent options to become unavailable while independent features remain usable. See [Native chunk meshes](NATIVE_CHUNK_MESHES.md) and `include/openshim_assets.h` for the current implementation.

Avoid mixing DLLs, configuration presets, and `patches.json` from different tags. After replacing native DLLs, **fully exit and restart Redux**.

## Test-crew session uploading

Logging/uploading is **off for regular installs**. The optional uploader requires the private test-crew webhook configuration and an explicit wrapper launch command. It can bundle peer public IP addresses; do not post such bundles publicly.

The [uploader guide](../upload/README.md) contains Windows and Linux wrapper commands, Snap/Flatpak path differences, retry/outbox behavior, and privacy details. Removing the uploader files does **not** clear Steam launch options automatically: remove the wrapper command manually or the game may fail to launch.

## Release verification

The release download includes a suite SHA-256 sidecar and published checksums. The installer verifies the suite before deployment, but source-level tests alone cannot establish runtime compatibility across Steam/GOG, DX9/DX11, multiplayer, and Proton/Wine. See the [release qualification matrix](RELEASE_QUALIFICATION.md) for live-client checks and sign-off requirements.
