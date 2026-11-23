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
    Write-Fixture $Root "bzloader.dll.previous" $openShimMarker
    Write-Fixture $Root "bzloader.dll.bak-20260101-000000" $openShimMarker
    Write-Fixture $Root "plugins\openshim.dll" $openShimMarker
    Write-Fixture $Root "plugins\openshim.dll.previous" $openShimMarker
    Write-Fixture $Root "plugins\openshim.dll.bak-20260101-000000" $openShimMarker

    # Steam launcher skip proxy beside Rebellion's own launcher (which stays).
    Write-Fixture $Root "Launcher\d3d9.dll" $openShimMarker
    Write-Fixture $Root "Launcher\BZLauncher.exe" "launcher"

    # patches.json family: old layout under scripts\, new layout under openshim\.
    Write-Fixture $Root "openshim\patches.json" "{}"
    Write-Fixture $Root "openshim\patches.json.previous" "{}"
    Write-Fixture $Root "openshim\patches.json.bak-20260101-000000" "{}"
    Write-Fixture $Root "scripts\patches.json" "{}"
    Write-Fixture $Root "scripts\patches.json.previous" "{}"
    Write-Fixture $Root "scripts\patches.json.bak-20260101-000000" "{}"
    Write-Fixture $Root "scripts\stock_mission.lua" "-- the game's own script"

    # Resource trees and the asset manifest.
    Write-Fixture $Root "openshim\renderer\enhanced\resources.version" "3"
    Write-Fixture $Root "openshim\renderer\enhanced\openshim_enhanced_base.program" "program"
    Write-Fixture $Root "openshim\OpenShimAssets.ini" "[Assets]"

    # Widget tiles beside a file that is not the installer's, in the current
    # folder and in the legacy one older releases used.
    foreach ($uiDir in @("openshim\ui", "BZ_ASSETS_CORE\common\ui\CustomWidgets")) {
        foreach ($tile in @("uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png", "odyssey.ogv", "openshim_widgets.sha256")) {
            Write-Fixture $Root "$uiDir\$tile" "png"
        }
        Write-Fixture $Root "$uiDir\player_widget.png" "png"
    }

    # New-layout state, cache, bundled LAN tools and the stock backups. The
    # stock net.ini differs from the OpenShim-edited one in the game root.
    Write-Fixture $Root "openshim\openshim.ini" "[Player]"
    Write-Fixture $Root "openshim\openshim.ini.bak-20260101-000000" "[Player]"
    Write-Fixture $Root "openshim\openshim.ini.pre-reset-20260101-000000.bak" "[Player]"
    Write-Fixture $Root "openshim\openshim.ini.premigrate-r1.bak" "[Player]"
    Write-Fixture $Root "openshim\openshim.ini.canonical" "[Shipped]"
    Write-Fixture $Root "openshim\state\openshim_update.status" "state=complete"
    Write-Fixture $Root "openshim\state\steam_tunnel_peers.txt" "peers"
    Write-Fixture $Root "openshim\cache\shaders\a.bin" "cache"
    Write-Fixture $Root "openshim\tools\lan\BZRServer.exe" "server"
    Write-Fixture $Root "openshim\stock-backup\net.ini" "[Stock]"
    Write-Fixture $Root "openshim\stock-backup\Ogre.cfg" "stock ogre"
    Write-Fixture $Root "Ogre.cfg" "openshim ogre"

    # Old-layout leftovers from an install that never ran the new DLL.
    Write-Fixture $Root "tools\lan\BZRServer.exe" "server"
    Write-Fixture $Root "tools\lan\licenses\LICENSE.txt" "license"
    Write-Fixture $Root "shader_cache\a.bin" "cache"
    Write-Fixture $Root "steam_tunnel_peers.txt" "peers"
    Write-Fixture $Root "steam_tunnel_peers.txt.lock" "lock"
    Write-Fixture $Root "bzloader.log" "loader"

    # Player data that must always survive.
    Write-Fixture $Root "Save\slot1.sav" "save"
    Write-Fixture $Root "career_stats.cfg" "stats"
    Write-Fixture $Root "bans.cfg" "bans"
    Write-Fixture $Root "flags.cfg" "flags"
    Write-Fixture $Root "flags\one.flag" "flag"
    Write-Fixture $Root "multi.ini" "multi"
    Write-Fixture $Root "campaignReimagined_settings.cfg" "settings"

    # Old-layout player configuration, its backups, the canonical copy, the
    # network config family, logs, and the updater status file.
    Write-Fixture $Root "openshim.ini" "[Player]"
    Write-Fixture $Root "openshim.ini.bak-20260101-000000" "[Player]"
    Write-Fixture $Root "openshim.ini.pre-reset-20260101-000000.bak" "[Player]"
    Write-Fixture $Root "openshim.ini.canonical" "[Shipped]"
    Write-Fixture $Root "net.ini" "[OpenShimNetwork]"
    Write-Fixture $Root "net.ini.bak-20260101-000000" "[Network]"
    Write-Fixture $Root "net.ini.previous" "[Network]"
    Write-Fixture $Root "logs\openshim.log" "log"
    Write-Fixture $Root "logs\openshim_crash.log" "crash"
    Write-Fixture $Root "logs\openshim_crash_20261015_150000.dmp" "dump"
    Write-Fixture $Root "logs\bzloader.log" "loader"
    Write-Fixture $Root "logs\winmm_shim.log" "proxy"
    Write-Fixture $Root "logs\BZLogger.txt" "stock"
    Write-Fixture $Root "logs\other_mod.log" "other"
    Write-Fixture $Root "logs\openshim_custom.mod" "not a log"
    Write-Fixture $Root "logs\openshim_cpu_samples_main_100.bin" "capture"
    Write-Fixture $Root "logs\openshim_frames_main_100.bin" "capture"
    Write-Fixture $Root "logs\openshim_va_main_100.csv" "capture"
    Write-Fixture $Root "logs\openshim_soak_lighting_100_01.png" "capture"
    Write-Fixture $Root "logs\terrain_probe.json" "capture"
    Write-Fixture $Root "logs\terrain_probe_001.json" "capture"
    Write-Fixture $Root "logs\openshim_backend_pending.txt" "capture"
    Write-Fixture $Root "logs\bz_buffer_log.bin" "capture"
    Write-Fixture $Root "logs\bz_relay_control.jsonl" "capture"
    Write-Fixture $Root "logs\terrain_notes.json" "not ours"
    Write-Fixture $Root "logs\other_mod_capture.bin" "not ours"
    Write-Fixture $Root "openshim.log" "fallback"
    Write-Fixture $Root "openshim.ini.example" "reference"
    Write-Fixture $Root "openshim_update.status" "state=complete"

    # Current-user folders are dedicated to OpenShim and removed only by the
    # explicit full-clean option. Tests redirect AppData away from the machine.
    $localRoot = Join-Path $script:root "LocalAppData"
    $roamingRoot = Join-Path $script:root "RoamingAppData"
    Write-Fixture $localRoot "openshim\openshim_wrap.ps1" "wrapper"
    Write-Fixture $localRoot "openshim\outbox\failed.zip" "bundle"
    Write-Fixture $localRoot "openshim\openshim_wrap.log" "log"
    Write-Fixture $localRoot "not-openshim\keep.txt" "keep"
    Write-Fixture $roamingRoot "openshim\upload.conf" "secret"
    Write-Fixture $roamingRoot "not-openshim\keep.txt" "keep"
}

function Invoke-Uninstaller {
    param([string]$GameDir, [hashtable]$Env = @{})
    $saved = @{}
    foreach ($name in @("OPENSHIM_GAME_PATH", "OPENSHIM_DRY_RUN", "OPENSHIM_PURGE_CONFIG",
                           "OPENSHIM_PURGE_LEFTOVERS", "LOCALAPPDATA", "APPDATA")) {
        $saved[$name] = [Environment]::GetEnvironmentVariable($name)
        [Environment]::SetEnvironmentVariable($name, $null)
    }
    [Environment]::SetEnvironmentVariable("OPENSHIM_GAME_PATH", $GameDir)
    [Environment]::SetEnvironmentVariable("LOCALAPPDATA", (Join-Path $script:root "LocalAppData"))
    [Environment]::SetEnvironmentVariable("APPDATA", (Join-Path $script:root "RoamingAppData"))
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
        "bzloader.dll", "bzloader.dll.previous", "bzloader.dll.bak-20260101-000000",
        "plugins\openshim.dll", "plugins\openshim.dll.previous",
        "plugins\openshim.dll.bak-20260101-000000", "plugins",
        "Launcher\d3d9.dll",
        "scripts\patches.json", "scripts\patches.json.previous", "scripts\patches.json.bak-20260101-000000",
        "openshim\renderer\enhanced\resources.version", "openshim\renderer\enhanced", "openshim\renderer",
        "openshim\OpenShimAssets.ini",
        "openshim\ui\uiline.png", "openshim\ui\uiplate.png", "openshim\ui\uibtn.png", "openshim\ui\uibtnhv.png",
        "openshim\ui\odyssey.ogv", "openshim\ui\openshim_widgets.sha256",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\uiline.png", "BZ_ASSETS_CORE\common\ui\CustomWidgets\uiplate.png",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\uibtn.png", "BZ_ASSETS_CORE\common\ui\CustomWidgets\uibtnhv.png",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\odyssey.ogv", "BZ_ASSETS_CORE\common\ui\CustomWidgets\openshim_widgets.sha256",
        "openshim.ini.canonical", "openshim_update.status",
        "openshim\patches.json", "openshim\patches.json.previous", "openshim\patches.json.bak-20260101-000000",
        "openshim\openshim.ini.canonical", "openshim\state", "openshim\cache", "openshim\tools", "openshim\stock-backup",
        "openshim\ui\player_widget.png", "openshim\ui",
        "tools", "shader_cache", "steam_tunnel_peers.txt", "steam_tunnel_peers.txt.lock", "bzloader.log"
    )
    foreach ($relative in $gone) {
        Check (-not (Test-Path -LiteralPath (Join-Path $game $relative))) "removed: $relative"
    }
    $kept = @(
        "battlezone98redux.exe",
        "winmm.dll.bak-20260102-000000",
        "Launcher\BZLauncher.exe",
        "scripts\stock_mission.lua", "scripts",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\player_widget.png", "BZ_ASSETS_CORE\common\ui\CustomWidgets",
        "openshim", "openshim\openshim.ini", "openshim\openshim.ini.bak-20260101-000000",
        "openshim\openshim.ini.pre-reset-20260101-000000.bak", "openshim\openshim.ini.premigrate-r1.bak",
        "openshim.ini", "openshim.ini.bak-20260101-000000", "openshim.ini.pre-reset-20260101-000000.bak",
        "net.ini", "net.ini.bak-20260101-000000", "net.ini.previous", "Ogre.cfg",
        "Save\slot1.sav", "career_stats.cfg", "bans.cfg", "flags.cfg", "flags\one.flag", "multi.ini",
        "campaignReimagined_settings.cfg",
        "logs\openshim.log", "logs\openshim_crash.log", "logs\openshim_crash_20261015_150000.dmp",
        "logs\bzloader.log", "logs\winmm_shim.log", "logs\BZLogger.txt", "logs\other_mod.log", "logs\openshim_custom.mod",
        "openshim.log", "openshim.ini.example"
    )
    foreach ($relative in $kept) {
        Check (Test-Path -LiteralPath (Join-Path $game $relative)) "kept: $relative"
    }
    Check ($result.Output -match "KEEPING .*winmm\.dll\.bak-20260102-000000") "the foreign backup is reported as kept"
    Check ($result.Output -match "left in place") "the closing note says what was left"
    Check ((Get-Content -LiteralPath (Join-Path $game "net.ini") -Raw) -eq "[Stock]") "net.ini was restored from openshim\stock-backup"
    Check ((Get-Content -LiteralPath (Join-Path $game "Ogre.cfg") -Raw) -eq "stock ogre") "Ogre.cfg was restored from openshim\stock-backup"
    Check ((Get-Content -LiteralPath (Join-Path $game "career_stats.cfg") -Raw) -eq "stats") "player data content is untouched"

    # --- UI folders and openshim\ holding no player ini are removed entirely -------
    New-GameFixture $game
    Remove-Item -Force (Join-Path $game "openshim\openshim.ini*")
    Remove-Item -LiteralPath (Join-Path $game "BZ_ASSETS_CORE\common\ui\CustomWidgets\player_widget.png") -Force
    $result = Invoke-Uninstaller -GameDir $game
    Check $result.Ok "owned-only UI run exits cleanly: $($result.Output)"
    foreach ($relative in @("openshim\ui", "openshim", "BZ_ASSETS_CORE\common\ui\CustomWidgets")) {
        Check (-not (Test-Path -LiteralPath (Join-Path $game $relative))) "owned-only UI run removed: $relative"
    }
    Check (Test-Path -LiteralPath (Join-Path $game "BZ_ASSETS_CORE\common\ui")) "owned-only UI run keeps the game's ui folder"

    # --- purge run also removes the player ini and its backups -------------------
    New-GameFixture $game
    $result = Invoke-Uninstaller -GameDir $game -Env @{ OPENSHIM_PURGE_CONFIG = "1" }
    Check $result.Ok "purge run exits cleanly: $($result.Output)"
    foreach ($relative in @("openshim.ini", "openshim.ini.bak-20260101-000000", "openshim.ini.pre-reset-20260101-000000.bak",
            "openshim\openshim.ini", "openshim\openshim.ini.bak-20260101-000000",
            "openshim\openshim.ini.pre-reset-20260101-000000.bak", "openshim\openshim.ini.premigrate-r1.bak", "openshim")) {
        Check (-not (Test-Path -LiteralPath (Join-Path $game $relative))) "purge removed: $relative"
    }
    foreach ($relative in @("net.ini", "net.ini.bak-20260101-000000", "net.ini.previous", "logs\openshim.log", "career_stats.cfg", "Save\slot1.sav")) {
        Check (Test-Path -LiteralPath (Join-Path $game $relative)) "purge kept: $relative"
    }

    # --- opt-in complete cleanup of OpenShim-only logs and per-user data ---------
    New-GameFixture $game
    $allBefore = @(
        (Join-Path $game "logs\openshim.log"),
        (Join-Path $script:root "LocalAppData\openshim\outbox\failed.zip"),
        (Join-Path $script:root "RoamingAppData\openshim\upload.conf")
    )
    $result = Invoke-Uninstaller -GameDir $game -Env @{
        OPENSHIM_PURGE_LEFTOVERS = "1"
        OPENSHIM_DRY_RUN = "1"
    }
    Check $result.Ok "full-clean dry run completes: $($result.Output)"
    foreach ($file in $allBefore) {
        Check (Test-Path -LiteralPath $file) "full-clean dry run retains: $file"
    }

    New-GameFixture $game
    $result = Invoke-Uninstaller -GameDir $game -Env @{ OPENSHIM_PURGE_LEFTOVERS = "1" }
    Check $result.Ok "full-clean completes: $($result.Output)"
    foreach ($relative in @(
        "openshim.ini", "openshim.ini.bak-20260101-000000", "openshim.ini.pre-reset-20260101-000000.bak",
        "openshim\openshim.ini", "openshim",
        "openshim.ini.example", "openshim.log", "logs\openshim.log", "logs\openshim_crash.log",
        "logs\openshim_crash_20261015_150000.dmp", "logs\bzloader.log", "logs\winmm_shim.log",
        "logs\openshim_cpu_samples_main_100.bin", "logs\openshim_frames_main_100.bin", "logs\openshim_va_main_100.csv",
        "logs\openshim_soak_lighting_100_01.png", "logs\terrain_probe.json", "logs\terrain_probe_001.json",
        "logs\openshim_backend_pending.txt", "logs\bz_buffer_log.bin", "logs\bz_relay_control.jsonl"
    )) {
        Check (-not (Test-Path -LiteralPath (Join-Path $game $relative))) "full-clean removed: $relative"
    }
    foreach ($relative in @(
        "net.ini", "net.ini.previous", "net.ini.bak-20260101-000000",
        "logs\BZLogger.txt", "logs\other_mod.log", "logs\openshim_custom.mod",
        "logs\terrain_notes.json", "logs\other_mod_capture.bin",
        "BZ_ASSETS_CORE\common\ui\CustomWidgets\player_widget.png", "career_stats.cfg", "Save\slot1.sav"
    )) {
        Check (Test-Path -LiteralPath (Join-Path $game $relative)) "full-clean preserved: $relative"
    }
    foreach ($relative in @("LocalAppData\openshim", "RoamingAppData\openshim")) {
        Check (-not (Test-Path -LiteralPath (Join-Path $script:root $relative))) "full-clean removed user data: $relative"
    }
    foreach ($relative in @("LocalAppData\not-openshim\keep.txt", "RoamingAppData\not-openshim\keep.txt")) {
        Check (Test-Path -LiteralPath (Join-Path $script:root $relative)) "full-clean preserved other user data: $relative"
    }
    Check ($result.Output -match "CLEAR the OpenShim upload wrapper") "full-clean warns to clear Steam launch option"

    # --- unknown entries in openshim\ stay; .before-uninstall copies never overwrite -----
    New-GameFixture $game
    Write-Fixture $game "openshim\my_mod\keep.txt" "mine"
    Write-Fixture $game "openshim\notes.txt" "mine"
    Write-Fixture $game "openshim\patches.json.superseded" "{}"
    Write-Fixture $game "Ogre.cfg.before-uninstall-20200101-000000" "earlier"
    $result = Invoke-Uninstaller -GameDir $game
    Check $result.Ok "unknown-entry run exits cleanly: $($result.Output)"
    foreach ($relative in @("openshim\my_mod\keep.txt", "openshim\notes.txt", "openshim")) {
        Check (Test-Path -LiteralPath (Join-Path $game $relative)) "unknown entry kept: $relative"
    }
    Check (-not (Test-Path -LiteralPath (Join-Path $game "openshim\patches.json.superseded"))) "patches.json.superseded is removed with the family"
    Check ($result.Output -match "KEEPING .*notes\.txt : not an OpenShim file") "an unknown file is reported"
    Check ($result.Output -match "KEEPING .*my_mod : not an OpenShim folder") "an unknown folder is reported"
    Check ((Get-Content -LiteralPath (Join-Path $game "Ogre.cfg.before-uninstall-20200101-000000") -Raw) -eq "earlier") "an earlier .before-uninstall copy is not overwritten"
    Check (@(Get-ChildItem -LiteralPath $game -Filter "Ogre.cfg.before-uninstall-*").Count -eq 2) "this run's .before-uninstall copy has its own name"

    # --- openshim\ that is itself a junction is not entered ---------------------------
    New-GameFixture $game
    $realOpenShim = Join-Path $root "elsewhere"
    Move-Item -LiteralPath (Join-Path $game "openshim") -Destination $realOpenShim
    New-Item -ItemType Junction -Path (Join-Path $game "openshim") -Target $realOpenShim | Out-Null
    $result = Invoke-Uninstaller -GameDir $game
    Check $result.Ok "linked openshim run exits cleanly: $($result.Output)"
    Check (Test-Path -LiteralPath (Join-Path $realOpenShim "patches.json")) "a linked openshim\ target is untouched"
    Check ($result.Output -match "KEEPING .*openshim : it is a link") "a linked openshim\ is reported"
    [System.IO.Directory]::Delete((Join-Path $game "openshim"))

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
