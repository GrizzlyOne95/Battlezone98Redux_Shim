# Fixture tests for OpenShimSetup's install/repair/update maintenance actions.
# Run only on Windows after the Release Win32 binaries have been built.
$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$repoRoot = Split-Path -Parent $PSScriptRoot
$installer = Join-Path $repoRoot "scripts\install_windows.ps1"
$sourceDll = Join-Path $repoRoot "bin\Release\winmm.dll"
$ps51 = Join-Path $env:SystemRoot "System32\WindowsPowerShell\v1.0\powershell.exe"
if (-not (Test-Path -LiteralPath $sourceDll -PathType Leaf)) {
    throw "Build winmm.dll before running setup_maintenance_tests.ps1"
}

$temp = Join-Path ([System.IO.Path]::GetTempPath()) ("openshim-maintenance-" + [guid]::NewGuid().ToString("N"))
$game = Join-Path $temp "game"
$emptyGame = Join-Path $temp "empty-game"
$variables = @("OPENSHIM_GAME_PATH", "OPENSHIM_TEST_GAME_PATHS", "OPENSHIM_DLL",
    "OPENSHIM_SUITE_ZIP", "OPENSHIM_SUITE_SHA256", "OPENSHIM_SETUP_ACTION",
    "OPENSHIM_RESET_INI", "OPENSHIM_WEBHOOK", "OPENSHIM_INTERACTIVE", "LOCALAPPDATA")
$previous = @{}
foreach ($name in $variables) { $previous[$name] = [Environment]::GetEnvironmentVariable($name) }

function Invoke-Setup {
    param([string]$Action, [bool]$ExpectSuccess)
    $env:OPENSHIM_SETUP_ACTION = $Action
    $output = & $ps51 -NoProfile -NonInteractive -ExecutionPolicy Bypass -File $installer 2>&1
    $status = $LASTEXITCODE
    if ($output) { $output | ForEach-Object { Write-Host $_ } }
    if ($ExpectSuccess -and $status -ne 0) { throw "$Action failed with exit code $status" }
    if (-not $ExpectSuccess -and $status -eq 0) { throw "$Action unexpectedly succeeded" }
}

try {
    New-Item -ItemType Directory -Path $game, $emptyGame -Force | Out-Null
    New-Item -ItemType File -Path (Join-Path $game "battlezone98redux.exe"),
        (Join-Path $emptyGame "battlezone98redux.exe") -Force | Out-Null

    # Existing OpenShim, but the loader, runtime plugin and resources are missing.
    # Repair must fill the holes without overwriting player/network settings.
    Copy-Item -LiteralPath $sourceDll -Destination (Join-Path $game "winmm.dll")
    Set-Content -LiteralPath (Join-Path $game "openshim.ini") -Value "player-setting=keep" -Encoding ASCII
    Set-Content -LiteralPath (Join-Path $game "net.ini") -Value "network-setting=keep" -Encoding ASCII

    $env:OPENSHIM_GAME_PATH = $game
    $env:OPENSHIM_TEST_GAME_PATHS = $null
    $env:OPENSHIM_DLL = $null
    $env:OPENSHIM_SUITE_ZIP = $null
    $env:OPENSHIM_SUITE_SHA256 = $null
    $env:OPENSHIM_RESET_INI = $null
    $env:OPENSHIM_WEBHOOK = $null
    $env:OPENSHIM_INTERACTIVE = $null
    $env:LOCALAPPDATA = Join-Path $temp "local-appdata"
    New-Item -ItemType Directory -Path $env:LOCALAPPDATA -Force | Out-Null

    Invoke-Setup -Action "repair" -ExpectSuccess $true

    foreach ($file in @("winmm.dll", "bzloader.dll", "plugins\openshim.dll",
                        "scripts\patches.json", "openshim.ini.canonical",
                        "openshim\OpenShimAssets.ini",
                        "openshim\renderer\enhanced\resources.version")) {
        if (-not (Test-Path -LiteralPath (Join-Path $game $file) -PathType Leaf)) {
            throw "Repair did not restore $file"
        }
    }
    if ((Get-Content -LiteralPath (Join-Path $game "openshim.ini") -Raw).Trim() -ne "player-setting=keep") {
        throw "Repair overwrote player settings"
    }
    if ((Get-Content -LiteralPath (Join-Path $game "net.ini") -Raw).Trim() -ne "network-setting=keep") {
        throw "Repair overwrote network settings"
    }
    if (Get-ChildItem -LiteralPath $game -Filter "winmm.dll.bak-*" -File) {
        throw "Repair backed up an already-correct winmm.dll"
    }

    # A second repair must be idempotent for the installed binary chain.
    Invoke-Setup -Action "repair" -ExpectSuccess $true
    if (Get-ChildItem -LiteralPath $game -Filter "winmm.dll.bak-*" -File) {
        throw "Repeat repair backed up an unchanged winmm.dll"
    }

    # Update to the same version must be a no-op, not a reinstall.
    $installedHash = (Get-FileHash -LiteralPath (Join-Path $game "winmm.dll") -Algorithm SHA256).Hash
    Invoke-Setup -Action "update" -ExpectSuccess $true
    if ((Get-FileHash -LiteralPath (Join-Path $game "winmm.dll") -Algorithm SHA256).Hash -ne $installedHash) {
        throw "Same-version update modified winmm.dll"
    }

    # Repair and Update are not aliases for a fresh installation.
    $env:OPENSHIM_GAME_PATH = $emptyGame
    Invoke-Setup -Action "repair" -ExpectSuccess $false
    Invoke-Setup -Action "update" -ExpectSuccess $false
    if (Test-Path -LiteralPath (Join-Path $emptyGame "winmm.dll")) {
        throw "Maintenance action installed into an empty game folder"
    }

    Write-Host "PASS: repair restores missing files, preserves settings and unchanged files; update no-op; empty-install guard"
}
finally {
    foreach ($name in $variables) { [Environment]::SetEnvironmentVariable($name, $previous[$name]) }
    Remove-Item -LiteralPath $temp -Recurse -Force -ErrorAction SilentlyContinue
}
