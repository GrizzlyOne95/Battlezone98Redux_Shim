# Live test for SkinnedGibs: loads the lcbench world with the gibs.lua overlay,
# which spawns the four stock pilots and kills them one by one. Debug only; it
# deploys addon/lcbench/lcbench.lua and restores the prior file when the game
# exits. Requires the existing lcbench baseline in addon\lcbench and
# [General] SkinnedGibs = 1 in the game's openshim.ini.
#
#   pwsh -File reverse_engineering/run_lcgibs.ps1                # watch it, close the game yourself
#   pwsh -File reverse_engineering/run_lcgibs.ps1 -RunSeconds 40 # capture logs and stop after 40 s
#
# Add [Diagnostics] TraceSkinnedGibs = 1 for per-gib log lines. Windowed is
# forced (BZR_FORCE_WINDOWED=1); use Stop-BZRGame, never kill the process.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(0, 300)]
    [int]$RunSeconds = 0,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$overlay = Join-Path $PSScriptRoot "test_missions\lcbench_gibs\gibs.lua"
$logRoot = Join-Path $GameRoot "logs"
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) { $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcgibs_$stamp" }

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "The lcbench baseline is not installed at $missionRoot (run_lcroad_pilot.ps1 documents how it is installed)"
}
if (@(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue).Count -gt 0) {
    throw "Refusing to start while another Battlezone process is running"
}

$live = Join-Path $missionRoot "lcbench.lua"
$had = Test-Path -LiteralPath $live
New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null
if ($had) { Copy-Item -LiteralPath $live -Destination (Join-Path $OutputRoot "lcbench.lua.orig") -Force }

try {
    Copy-Item -LiteralPath $overlay -Destination $live -Force
    Assert-BZRSafeToLaunch   # refuses unless the game cannot steal foreground/mouse; starts the watchdog
    $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
    if ($RunSeconds -gt 0) {
        if (-not $process.WaitForExit($RunSeconds * 1000)) { Stop-BZRGame -Id $process.Id }
    } else {
        Write-Host "Game running; the pilots die from T+4 s, one every 2.5 s. Close the game when done."
        $process.WaitForExit()
    }
} finally {
    $own = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Where-Object { try { $_.Path -ieq $gameExe } catch { $false } })
    if ($own.Count -gt 0) { Stop-BZRGame -Id @($own.Id) }
    if ($had) { Copy-Item -LiteralPath (Join-Path $OutputRoot "lcbench.lua.orig") -Destination $live -Force }
    elseif (Test-Path -LiteralPath $live) { Remove-Item -LiteralPath $live -Force }
    foreach ($name in @("BZLogger.txt", "openshim.log")) {
        $source = Join-Path $logRoot $name
        if (Test-Path -LiteralPath $source) { Copy-Item -LiteralPath $source -Destination (Join-Path $OutputRoot $name) -Force }
    }
}
$watchdog = Join-Path $env:TEMP "bzr_foreground_watchdog.log"
if ((Test-Path -LiteralPath $watchdog) -and (Select-String -LiteralPath $watchdog -Pattern "FOREGROUND-STOLEN" -Quiet)) {
    Write-Warning "FOREGROUND-STOLEN in $watchdog - stop launching and report."
}
Write-Host "Logs: $OutputRoot (look for [LCGIBS] in BZLogger.txt and [SKINNEDGIBS] / [DX11COMPAT] in openshim.log)"
