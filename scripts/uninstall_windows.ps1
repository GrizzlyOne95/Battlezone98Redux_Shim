# One-line Windows uninstaller. Paste into PowerShell:
#   irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_windows.ps1 | iex
#
# Removes OpenShim's winmm.dll (and the co-deployed patches.json) from every
# detected Steam/GOG install. Leaves openshim.ini, net.ini, and logs alone.

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$steamAppId = "301650"
$defaultInstallDir = "Battlezone 98 Redux"
$requestedGamePath = if ($env:OPENSHIM_GAME_PATH) { $env:OPENSHIM_GAME_PATH } else { "" }

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
    foreach ($fallback in @(
        (Join-Path ${env:ProgramFiles(x86)} "Steam"),
        (Join-Path $env:PROGRAMFILES "Steam")
    )) {
        if ($fallback) { $roots.Add($fallback) }
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
        Add-UniquePath -List $paths -Path $requestedGamePath
        return $paths
    }
    foreach ($steamRoot in Get-SteamRoots) {
        foreach ($libraryRoot in Get-SteamLibraryRoots -SteamRoot $steamRoot) {
            $candidate = Join-Path $libraryRoot "steamapps\common\$defaultInstallDir"
            if (Test-BzrGameDir $candidate) { Add-UniquePath -List $paths -Path $candidate }
        }
    }
    foreach ($candidate in @(
        (Join-Path ${env:ProgramFiles(x86)} "GOG Galaxy\Games\Battlezone 98 Redux"),
        (Join-Path $env:PROGRAMFILES "GOG Galaxy\Games\Battlezone 98 Redux")
    )) {
        if (Test-BzrGameDir $candidate) { Add-UniquePath -List $paths -Path $candidate }
    }
    return $paths
}

function Test-OpenShimDll {
    param([string]$DllPath)
    if (-not (Test-Path -LiteralPath $DllPath)) { return $false }
    $raw = [System.Text.Encoding]::ASCII.GetString([System.IO.File]::ReadAllBytes($DllPath))
    return $raw.Contains("OpenShim")
}

$gamePaths = @(Get-GamePaths)
if ($gamePaths.Count -eq 0) {
    throw "Could not find Battlezone 98 Redux. Set OPENSHIM_GAME_PATH and run again."
}

foreach ($gameDir in $gamePaths) {
    Write-Host "Game folder: $gameDir"
    $dllPath = Join-Path $gameDir "winmm.dll"
    if (Test-Path -LiteralPath $dllPath) {
        if (Test-OpenShimDll $dllPath) {
            Remove-Item -Force -LiteralPath $dllPath
            Write-Host "  removed $dllPath"
        } else {
            Write-Host "  KEEPING $dllPath : it does not look like OpenShim"
        }
    } else {
        Write-Host "  (absent) $dllPath"
    }

    $patches = Join-Path $gameDir "scripts\patches.json"
    if (Test-Path -LiteralPath $patches) {
        Remove-Item -Force -LiteralPath $patches
        Write-Host "  removed $patches"
    }
}

Write-Host ""
Write-Host "Uninstall complete. openshim.ini, net.ini, and logs were left in place."
Write-Host "Clear any leftover Steam launch options by hand if you set them."
