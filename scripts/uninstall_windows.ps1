# One-line Windows uninstaller. Paste into PowerShell:
#   irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_windows.ps1 | iex
#
# Removes everything install_windows.ps1 deploys, from every detected Steam/GOG
# install (or the one named by OPENSHIM_GAME_PATH): the three-binary load chain
# (winmm.dll, bzloader.dll, plugins\openshim.dll), scripts\patches.json, the
# Enhanced renderer resources and asset manifest under openshim\, the four UI
# widget tiles, openshim.ini.canonical, the .bak-<stamp> copies the installer
# made of those files on each run, and what the Workshop updater leaves behind
# (winmm.dll.previous, scripts\patches.json.previous, openshim_update.status).
#
# A binary is removed only when it identifies as OpenShim; a foreign winmm.dll
# (another proxy) is kept and reported. openshim.ini and its backups, net.ini
# and its backups, and logs\ are left in place so a reinstall finds the
# player's settings; net.ini in particular is a game file OpenShim replaced,
# and the stock bytes are not known here.
#
#   OPENSHIM_PURGE_CONFIG=1   also remove openshim.ini and its backups
#   OPENSHIM_DRY_RUN=1        print what would be removed, remove nothing
#
# Keep this file pure ASCII: Windows PowerShell 5.1 reads a BOM-less UTF-8
# script as ANSI, and one non-ASCII character breaks it for anyone who saves
# it and runs powershell -File.

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$steamAppId = "301650"
$defaultInstallDir = "Battlezone 98 Redux"
$requestedGamePath = if ($env:OPENSHIM_GAME_PATH) { $env:OPENSHIM_GAME_PATH } else { "" }

# UI tiles the installer writes into the game's custom-widget resource tree.
# Everything else in that folder belongs to the game or to the player.
$uiTiles = @("uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png")

function Get-Switch {
    param([string]$Name)
    $value = [Environment]::GetEnvironmentVariable($Name)
    if (-not $value) { return $false }
    switch ($value.Trim().ToLowerInvariant()) {
        "1" { return $true }
        "true" { return $true }
        "yes" { return $true }
        "on" { return $true }
        "0" { return $false }
        "false" { return $false }
        "no" { return $false }
        "off" { return $false }
        default { throw "$Name must be 1/0, true/false, yes/no, or on/off." }
    }
}

$purgeConfig = Get-Switch "OPENSHIM_PURGE_CONFIG"
$dryRun = Get-Switch "OPENSHIM_DRY_RUN"

# --- discovery: identical to install_windows.ps1 so both scripts find the ---
# --- same folders, including a Steam install whose folder was renamed.    ---

function Test-BzrGameDir {
    param([string]$Dir)
    if (-not $Dir) { return $false }
    (Test-Path -LiteralPath (Join-Path $Dir "battlezone98redux.exe")) -or
        (Test-Path -LiteralPath (Join-Path $Dir "BZR.exe"))
}

function Add-UniquePath {
    param(
        [System.Collections.Generic.List[string]]$List,
        [string]$Path
    )
    if (-not $Path -or -not (Test-Path -LiteralPath $Path)) { return }
    $full = [System.IO.Path]::GetFullPath($Path)
    if ($List -notcontains $full) { $List.Add($full) }
}

# ${env:ProgramFiles(x86)} is undefined on 32-bit Windows, and Join-Path
# refuses an empty root, so filter the roots before joining.
function Get-ProgramFilesRoots {
    @(${env:ProgramFiles(x86)}, $env:PROGRAMFILES) | Where-Object { $_ } | Select-Object -Unique
}

function Get-SteamRoots {
    $roots = New-Object System.Collections.Generic.List[string]
    foreach ($location in @(
        @{ Path = "HKCU:\Software\Valve\Steam"; Names = @("SteamPath", "Path") },
        @{ Path = "HKLM:\SOFTWARE\WOW6432Node\Valve\Steam"; Names = @("InstallPath") },
        @{ Path = "HKLM:\SOFTWARE\Valve\Steam"; Names = @("InstallPath") }
    )) {
        try {
            $item = Get-ItemProperty -Path $location.Path -ErrorAction Stop
            foreach ($name in $location.Names) {
                $value = [string]$item.$name
                if ($value) { $roots.Add($value) }
            }
        } catch { }
    }
    foreach ($programFiles in Get-ProgramFilesRoots) {
        $roots.Add((Join-Path $programFiles "Steam"))
    }
    $roots | Where-Object { $_ } | Select-Object -Unique
}

function Get-SteamLibraryRoots {
    param([string]$SteamRoot)
    $libraryRoots = New-Object System.Collections.Generic.List[string]
    $libraryRoots.Add($SteamRoot)
    $libraryVdf = Join-Path $SteamRoot "steamapps\libraryfolders.vdf"
    if (Test-Path -LiteralPath $libraryVdf) {
        foreach ($line in Get-Content -Path $libraryVdf) {
            $match = [regex]::Match($line, '"path"\s+"([^"]+)"')
            if (-not $match.Success) {
                $match = [regex]::Match($line, '^\s*"\d+"\s+"([^"]+)"')
            }
            if ($match.Success) {
                $libraryRoots.Add($match.Groups[1].Value.Replace('\\', '\'))
            }
        }
    }
    $libraryRoots | Where-Object { $_ } | Select-Object -Unique
}

function Get-GamePaths {
    $paths = New-Object System.Collections.Generic.List[string]
    if ($requestedGamePath) {
        if (-not (Test-BzrGameDir $requestedGamePath)) {
            throw "OPENSHIM_GAME_PATH is not a Battlezone 98 Redux install: $requestedGamePath"
        }
        Add-UniquePath -List $paths -Path $requestedGamePath
        return $paths
    }

    foreach ($steamRoot in Get-SteamRoots) {
        foreach ($libraryRoot in Get-SteamLibraryRoots -SteamRoot $steamRoot) {
            $steamApps = Join-Path $libraryRoot "steamapps"
            $manifest = Join-Path $steamApps "appmanifest_$steamAppId.acf"
            $installDir = $defaultInstallDir
            if (Test-Path -LiteralPath $manifest) {
                foreach ($line in Get-Content -Path $manifest) {
                    $match = [regex]::Match($line, '"installdir"\s+"([^"]+)"')
                    if ($match.Success) {
                        $installDir = $match.Groups[1].Value
                        break
                    }
                }
            }
            $candidate = Join-Path $steamApps (Join-Path "common" $installDir)
            if (Test-BzrGameDir $candidate) { Add-UniquePath -List $paths -Path $candidate }
        }
    }

    foreach ($programFiles in Get-ProgramFilesRoots) {
        $candidate = Join-Path $programFiles "GOG Galaxy\Games\Battlezone 98 Redux"
        if (Test-BzrGameDir $candidate) { Add-UniquePath -List $paths -Path $candidate }
    }

    return $paths
}

# --- identity -----------------------------------------------------------------

# Every OpenShim binary (bootstrap, loader, plugin) carries the ASCII string
# "OpenShim" in its code and the UTF-16 product name "BZR Open Shim" in its
# version resource. A winmm.dll without either is somebody else's proxy.
function Test-OpenShimBinary {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) { return $false }
    $bytes = [System.IO.File]::ReadAllBytes($Path)
    if ([System.Text.Encoding]::ASCII.GetString($bytes).Contains("OpenShim")) { return $true }
    return [System.Text.Encoding]::Unicode.GetString($bytes).Contains("BZR Open Shim")
}

# --- removal ------------------------------------------------------------------

$script:removed = 0
$script:kept = 0
$script:failed = New-Object System.Collections.Generic.List[string]

function Remove-Planned {
    param([string]$Path, [switch]$Recurse)
    if ($dryRun) {
        Write-Host "  would remove $Path"
        $script:removed++
        return
    }
    try {
        Remove-Item -Force -LiteralPath $Path -Recurse:$Recurse
        Write-Host "  removed $Path"
        $script:removed++
    } catch {
        Write-Host "  FAILED  $Path : $($_.Exception.Message)"
        $script:failed.Add($Path)
    }
}

function Remove-IfPresent {
    param([string]$Path)
    if (Test-Path -LiteralPath $Path -PathType Leaf) { Remove-Planned -Path $Path }
}

# Binaries and their installer backups: only what identifies as OpenShim.
function Remove-OpenShimBinary {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) { return }
    if (Test-OpenShimBinary $Path) {
        Remove-Planned -Path $Path
    } else {
        Write-Host "  KEEPING $Path : it does not identify as OpenShim"
        $script:kept++
    }
}

function Remove-Backups {
    param([string]$Path, [switch]$IdentityChecked)
    $dir = Split-Path -Parent $Path
    $leaf = Split-Path -Leaf $Path
    if (-not (Test-Path -LiteralPath $dir)) { return }
    foreach ($backup in Get-ChildItem -LiteralPath $dir -File -Filter "$leaf.bak-*" -ErrorAction SilentlyContinue) {
        if ($IdentityChecked) { Remove-OpenShimBinary $backup.FullName } else { Remove-Planned -Path $backup.FullName }
    }
}

function Remove-DirectoryIfEmpty {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Container)) { return }
    if ($dryRun) { return }
    if (@(Get-ChildItem -LiteralPath $Path -Force).Count -eq 0) {
        Remove-Item -LiteralPath $Path -Force
        Write-Host "  removed empty folder $Path"
    }
}

function Test-GameRunningFrom {
    param([string]$GameDir)
    $prefix = [System.IO.Path]::GetFullPath($GameDir).TrimEnd('\') + '\'
    foreach ($process in Get-Process -Name "battlezone98redux", "BZR" -ErrorAction SilentlyContinue) {
        try {
            $path = $process.Path
            if ($path -and $path.StartsWith($prefix, [System.StringComparison]::OrdinalIgnoreCase)) {
                return $true
            }
        } catch { }
    }
    return $false
}

$gamePaths = @(Get-GamePaths)
if ($gamePaths.Count -eq 0) {
    throw "Could not find Battlezone 98 Redux. Set OPENSHIM_GAME_PATH and run again."
}

# Refuse before touching anything: a running game holds the DLLs open, and a
# half-removed load chain is the one state neither installer nor game handles.
foreach ($gameDir in $gamePaths) {
    if (Test-GameRunningFrom $gameDir) {
        throw "Battlezone 98 Redux is running from $gameDir. Close the game, then run the uninstaller again. Nothing was removed."
    }
}

if ($dryRun) { Write-Host "Dry run: nothing will be removed." }

foreach ($gameDir in $gamePaths) {
    Write-Host ""
    Write-Host "Game folder: $gameDir"

    # Load chain, plus the previous-version copies the Workshop updater keeps.
    foreach ($relative in @("winmm.dll", "winmm.dll.previous", "bzloader.dll", "plugins\openshim.dll")) {
        Remove-OpenShimBinary (Join-Path $gameDir $relative)
    }
    foreach ($relative in @("winmm.dll", "bzloader.dll", "plugins\openshim.dll")) {
        Remove-Backups -Path (Join-Path $gameDir $relative) -IdentityChecked
    }
    Remove-DirectoryIfEmpty (Join-Path $gameDir "plugins")

    # patches.json travels with the DLL and nothing else writes that name.
    $patches = Join-Path $gameDir "scripts\patches.json"
    Remove-IfPresent $patches
    Remove-IfPresent "$patches.previous"
    Remove-Backups -Path $patches

    # Enhanced renderer resources and the asset manifest. openshim\ is created
    # by the installer, but only its own entries are removed; anything else a
    # player put there is reported and left.
    $openshimDir = Join-Path $gameDir "openshim"
    $renderDir = Join-Path $openshimDir "renderer\enhanced"
    if (Test-Path -LiteralPath $renderDir -PathType Container) {
        Remove-Planned -Path $renderDir -Recurse
    }
    Remove-IfPresent (Join-Path $openshimDir "OpenShimAssets.ini")
    Remove-DirectoryIfEmpty (Join-Path $openshimDir "renderer")
    Remove-DirectoryIfEmpty $openshimDir
    if (-not $dryRun -and (Test-Path -LiteralPath $openshimDir -PathType Container)) {
        Write-Host "  KEEPING $openshimDir : it still holds files the installer did not put there"
        $script:kept++
    }

    # The four widget tiles; the folder may hold the game's or the player's own
    # widgets, so it goes only when those four were all it contained.
    $uiDir = Join-Path $gameDir "BZ_ASSETS_CORE\common\ui\CustomWidgets"
    foreach ($tile in $uiTiles) { Remove-IfPresent (Join-Path $uiDir $tile) }
    Remove-DirectoryIfEmpty $uiDir

    # Installer-owned copy of the shipped preset, and the updater's status file.
    Remove-IfPresent (Join-Path $gameDir "openshim.ini.canonical")
    Remove-IfPresent (Join-Path $gameDir "openshim_update.status")

    if ($purgeConfig) {
        $ini = Join-Path $gameDir "openshim.ini"
        Remove-IfPresent $ini
        Remove-Backups -Path $ini
        foreach ($reset in Get-ChildItem -LiteralPath $gameDir -File -Filter "openshim.ini.pre-reset-*.bak" -ErrorAction SilentlyContinue) {
            Remove-Planned -Path $reset.FullName
        }
    }
}

Write-Host ""
if ($dryRun) {
    Write-Host "Dry run complete: $($script:removed) item(s) would be removed, $($script:kept) kept."
} else {
    Write-Host "Uninstall complete: $($script:removed) item(s) removed, $($script:kept) kept."
}
if ($purgeConfig) {
    Write-Host "openshim.ini and its backups were removed (OPENSHIM_PURGE_CONFIG). net.ini and logs were left in place."
} else {
    Write-Host "openshim.ini, net.ini, their backups, and logs were left in place."
    Write-Host "Set OPENSHIM_PURGE_CONFIG=1 and run again to remove openshim.ini as well."
}
$wrapDir = if ($env:LOCALAPPDATA) { Join-Path $env:LOCALAPPDATA "openshim" } else { "" }
if ($wrapDir -and (Test-Path -LiteralPath $wrapDir)) {
    Write-Host "The optional log-upload wrapper is still installed at $wrapDir;"
    Write-Host "delete that folder and clear the Steam launch option that names it if you set one."
}
if ($script:failed.Count -gt 0) {
    throw "$($script:failed.Count) item(s) could not be removed (listed above as FAILED). Close anything using them and run again."
}
