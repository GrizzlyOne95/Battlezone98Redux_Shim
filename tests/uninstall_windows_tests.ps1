# Fixture test for scripts/uninstall_windows.ps1. Builds a fake game folder
# holding everything install_windows.ps1 deploys (plus the residue the Workshop
# updater and the installer's backups leave), runs the uninstaller against it
# through OPENSHIM_GAME_PATH, and checks what is gone and what survived. No
# game install, network access, or elevation required.
#
#   powershell -ExecutionPolicy Bypass -File tests\uninstall_windows_tests.ps1

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$repo = Split-Path -Parent $PSScriptRoot
$uninstaller = Join-Path $repo "scripts\uninstall_windows.ps1"
$script:failures = 0

function Check {
    param([bool]$Condition, [string]$Message)
    if ($Condition) { return }
    Write-Host "FAIL: $Message" -ForegroundColor Red
    $script:failures++
}

function Write-Fixture {
    param([string]$Root, [string]$Relative, [string]$Content = "fixture")
    $path = Join-Path $Root $Relative
    $dir = Split-Path -Parent $path
    if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    [System.IO.File]::WriteAllText($path, $Content)
}

# A file that passes Test-OpenShimBinary: the ASCII marker every shipped
# OpenShim binary carries. The foreign proxy carries neither marker.
$openShimMarker = "MZ....OpenShimGetVersion....BZLoader...."
$foreignMarker = "MZ....SomeOtherProxy........................"

function New-GameFixture {
    param([string]$Root)
    if (Test-Path -LiteralPath $Root) { Remove-Item -Recurse -Force -LiteralPath $Root }
    New-Item -ItemType Directory -Force -Path $Root | Out-Null
    Write-Fixture $Root "battlezone98redux.exe" "MZ game"

    # Installed load chain, the updater's previous copy, and installer backups
    # of each (one backup is a foreign proxy that must survive).
    Write-Fixture $Root "winmm.dll" $openShimMarker
    Write-Fixture $Root "winmm.dll.previous" $openShimMarker
    Write-Fixture $Root "winmm.dll.bak-20260101-000000" $openShimMarker
    Write-Fixture $Root "winmm.dll.bak-20260102-000000" $foreignMarker
    Write-Fixture $Root "bzloader.dll" $openShimMarker
    Write-Fixture $Root "bzloader.dll.bak-20260101-000000" $openShimMarker
    Write-Fixture $Root "plugins\openshim.dll" $openShimMarker
    Write-Fixture $Root "plugins\openshim.dll.bak-20260101-000000" $openShimMarker

    # patches.json family.
    Write-Fixture $Root "scripts\patches.json" "{}"
    Write-Fixture $Root "scripts\patches.json.previous" "{}"
    Write-Fixture $Root "scripts\patches.json.bak-20260101-000000" "{}"
    Write-Fixture $Root "scripts\stock_mission.lua" "-- the game's own script"

    # Resource trees and the asset manifest.
    Write-Fixture $Root "openshim\renderer\enhanced\resources.version" "3"
    Write-Fixture $Root "openshim\renderer\enhanced\openshim_enhanced_base.program" "program"
    Write-Fixture $Root "openshim\OpenShimAssets.ini" "[Assets]"

    # Widget tiles beside a file that is not the installer's.
    foreach ($tile in @("uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png")) {
        Write-Fixture $Root "BZ_ASSETS_CORE\common\ui\CustomWidgets\$tile" "png"
    }
    Write-Fixture $Root "BZ_ASSETS_CORE\common\ui\CustomWidgets\player_widget.png" "png"

    # Player configuration, its backups, the installer's canonical copy, the
    # network config family, logs, and the updater status file.
    Write-Fixture $Root "openshim.ini" "[Player]"
    Write-Fixture $Root "openshim.ini.bak-20260101-000000" "[Player]"
    Write-Fixture $Root "openshim.ini.pre-reset-20260101-000000.bak" "[Player]"
    Write-Fixture $Root "openshim.ini.canonical" "[Shipped]"
    Write-Fixture $Root "net.ini" "[Network]"
    Write-Fixture $Root "net.ini.bak-20260101-000000" "[Network]"
    Write-Fixture $Root "net.ini.previous" "[Network]"
    Write-Fixture $Root "logs\openshim.log" "log"
    Write-Fixture $Root "openshim_update.status" "state=complete"
}

function Invoke-Uninstaller {
    param([string]$GameDir, [hashtable]$Env = @{})
    $saved = @{}
    foreach ($name in @("OPENSHIM_GAME_PATH", "OPENSHIM_DRY_RUN", "OPENSHIM_PURGE_CONFIG")) {
        $saved[$name] = [Environment]::GetEnvironmentVariable($name)
        [Environment]::SetEnvironmentVariable($name, $null)
    }
    [Environment]::SetEnvironmentVariable("OPENSHIM_GAME_PATH", $GameDir)
    foreach ($name in $Env.Keys) { [Environment]::SetEnvironmentVariable($name, $Env[$name]) }
    try {
        # Write-Host lands on the information stream, so merge every stream.
        $output = & $uninstaller *>&1 | Out-String -Width 4096
        return @{ Ok = $true; Output = $output }
    } catch {
        return @{ Ok = $false; Output = "$_" }
    } finally {
        foreach ($name in $saved.Keys) { [Environment]::SetEnvironmentVariable($name, $saved[$name]) }
    }
}

$root = Join-Path ([System.IO.Path]::GetTempPath()) ("openshim-uninstall-test-" + [System.IO.Path]::GetRandomFileName())
New-Item -ItemType Directory -Force -Path $root | Out-Null
try {
    $game = Join-Path $root "Battlezone 98 Redux"

    # --- dry run touches nothing ------------------------------------------------
    New-GameFixture $game
    $before = @(Get-ChildItem -LiteralPath $game -Recurse -Force | ForEach-Object { $_.FullName }) | Sort-Object
    $result = Invoke-Uninstaller -GameDir $game -Env @{ OPENSHIM_DRY_RUN = "1" }
    Check $result.Ok "dry run exits cleanly: $($result.Output)"
    $after = @(Get-ChildItem -LiteralPath $game -Recurse -Force | ForEach-Object { $_.FullName }) | Sort-Object
    Check ((Compare-Object $before $after | Measure-Object).Count -eq 0) "dry run leaves the folder byte-for-byte as it was"
    Check ($result.Output -match "would remove") "dry run reports what it would remove"

    # --- default run -------------------------------------------------------------
    New-GameFixture $game
    $result = Invoke-Uninstaller -GameDir $game
    Check $result.Ok "default run exits cleanly: $($result.Output)"

    $gone = @(
        "winmm.dll", "winmm.dll.previous", "winmm.dll.bak-20260101-000000",
        "bzloader.dll", "bzloader.dll.bak-20260101-000000",
        "plugins\openshim.dll", "plugins\openshim.dll.bak-20260101-000000", "plugins",
        "scripts\patches.json", "scripts\patches.json.previous", "scripts\patches.json.bak-20260101-000000",
        "openshim\renderer\enhanced\resources.version", "openshim\renderer\enhanced", "openshim\renderer",
        "openshim\OpenShimAssets.ini", "openshim",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\uiline.png", "BZ_ASSETS_CORE\common\ui\CustomWidgets\uiplate.png",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\uibtn.png", "BZ_ASSETS_CORE\common\ui\CustomWidgets\uibtnhv.png",
        "openshim.ini.canonical", "openshim_update.status"
    )
    foreach ($relative in $gone) {
        Check (-not (Test-Path -LiteralPath (Join-Path $game $relative))) "removed: $relative"
    }
    $kept = @(
        "battlezone98redux.exe",
        "winmm.dll.bak-20260102-000000",
        "scripts\stock_mission.lua", "scripts",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\player_widget.png", "BZ_ASSETS_CORE\common\ui\CustomWidgets",
        "openshim.ini", "openshim.ini.bak-20260101-000000", "openshim.ini.pre-reset-20260101-000000.bak",
        "net.ini", "net.ini.bak-20260101-000000", "net.ini.previous",
        "logs\openshim.log"
    )
    foreach ($relative in $kept) {
        Check (Test-Path -LiteralPath (Join-Path $game $relative)) "kept: $relative"
    }
    Check ($result.Output -match "KEEPING .*winmm\.dll\.bak-20260102-000000") "the foreign backup is reported as kept"
    Check ($result.Output -match "left in place") "the closing note says what was left"

    # --- purge run also removes the player ini and its backups -------------------
    New-GameFixture $game
    $result = Invoke-Uninstaller -GameDir $game -Env @{ OPENSHIM_PURGE_CONFIG = "1" }
    Check $result.Ok "purge run exits cleanly: $($result.Output)"
    foreach ($relative in @("openshim.ini", "openshim.ini.bak-20260101-000000", "openshim.ini.pre-reset-20260101-000000.bak")) {
        Check (-not (Test-Path -LiteralPath (Join-Path $game $relative))) "purge removed: $relative"
    }
    foreach ($relative in @("net.ini", "net.ini.bak-20260101-000000", "net.ini.previous", "logs\openshim.log")) {
        Check (Test-Path -LiteralPath (Join-Path $game $relative)) "purge kept: $relative"
    }

    # --- a foreign winmm.dll is never removed --------------------------------------
    New-GameFixture $game
    Write-Fixture $game "winmm.dll" $foreignMarker
    $result = Invoke-Uninstaller -GameDir $game
    Check $result.Ok "foreign proxy run exits cleanly: $($result.Output)"
    Check (Test-Path -LiteralPath (Join-Path $game "winmm.dll")) "a foreign winmm.dll survives"
    Check (-not (Test-Path -LiteralPath (Join-Path $game "bzloader.dll"))) "OpenShim's loader still goes beside a foreign proxy"

    # --- a second run is a clean no-op -----------------------------------------------
    $result = Invoke-Uninstaller -GameDir $game
    Check $result.Ok "second run on an already-clean folder exits cleanly: $($result.Output)"

    # --- a wrong OPENSHIM_GAME_PATH is refused, not silently ignored -------------------
    $notGame = Join-Path $root "not-a-game"
    New-Item -ItemType Directory -Force -Path $notGame | Out-Null
    $result = Invoke-Uninstaller -GameDir $notGame
    Check (-not $result.Ok) "a folder without the game executable is refused"
    Check ($result.Output -match "not a Battlezone 98 Redux install") "the refusal names the reason"
} finally {
    Remove-Item -Recurse -Force -LiteralPath $root -ErrorAction SilentlyContinue
}

if ($script:failures -ne 0) {
    throw "uninstall_windows_tests: $($script:failures) check(s) failed"
}
Write-Host "uninstall_windows_tests: PASS"
