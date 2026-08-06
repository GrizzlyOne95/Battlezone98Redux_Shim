# Workshop Download + RE Setup

This workflow is for analyzing the Steam Workshop payloads. The clean-room
shim implementation in `src/` is currently targeted at the GOG `v2.2.301`
executable, while these Workshop artifacts remain the primary source for
reconstructing `_bzcp.dll` and `winmm.bin`.

For the Workshop item:

- URL: `https://steamcommunity.com/sharedfiles/filedetails/?id=3362534335`
- Workshop item id: `3362534335`
- Steam app id: `301650`

## Prereqs

- Repo checked out on `master`
- SteamCMD installed at `C:\steamcmd\steamcmd.exe`

## Download and Snapshot

From repo root:

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\Download-WorkshopItem.ps1
```

This does all of the following:

1. Downloads/updates the mod in SteamCMD cache (`steamapps\workshop\content\301650\3362534335`).
2. Copies files to `reverse_engineering\workshop\3362534335\snapshots\<timestamp>`.
3. Refreshes `reverse_engineering\workshop\3362534335\latest`.
4. Writes `manifest.sha256.txt` for binary diffing.

## Steam Account Login (if needed)

Anonymous worked for this item during setup. If Steam later requires account auth:

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\Download-WorkshopItem.ps1 `
  -SteamUser "<your_steam_user>" `
  -SteamPassword "<your_password>" `
  -SteamGuardCode "<code_if_prompted>"
```

## Initial RE Targets

Start in the latest snapshot directory:

```powershell
cd .\reverse_engineering\workshop\3362534335\latest
```

Primary files for analysis:

1. `_bzcp.dll` (main binary patch DLL)
2. `winmm.bin` (binary payload)
3. `shimmsn.lua`, `_requirefix.lua`, `_table_show.lua` (script behavior)

Useful quick triage:

```powershell
Get-FileHash .\_bzcp.dll -Algorithm SHA256
Get-FileHash .\winmm.bin -Algorithm SHA256
Format-Hex .\winmm.bin -Count 128
```

## Compare Two Snapshots

```powershell
$a = ".\reverse_engineering\workshop\3362534335\snapshots\YYYYMMDD-HHMMSS\manifest.sha256.txt"
$b = ".\reverse_engineering\workshop\3362534335\snapshots\YYYYMMDD-HHMMSS\manifest.sha256.txt"
Compare-Object (Get-Content $a) (Get-Content $b)
```
