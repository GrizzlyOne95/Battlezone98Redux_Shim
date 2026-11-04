# Live test for the AI turret range refresh and MAG charge release: loads the
# lcbench world with the turretrange.lua overlay, which builds a friendly avturr
# and an enemy svturr EnemyGap m apart on the heading with the clearest
# terrain line of sight (logged as LOS), then gives the avturr a MAG cannon and
# logs each hit on the svturr. Debug only; it deploys
# addon/lcbench/lcbench.lua and restores the prior file when the game exits.
# Requires the lcbench baseline in addon\lcbench and the build deployed with
# scripts/Deploy-OpenShim.ps1.
#
#   pwsh -File reverse_engineering/run_lcturret.ps1 -RunSeconds 75             # fix on
#   pwsh -File reverse_engineering/run_lcturret.ps1 -RunSeconds 75 -TuningOff  # A/B: AiOdfGameplayTuning = 0
#   pwsh -File reverse_engineering/run_lcturret.ps1 -RunSeconds 75 -EnemyGap 225  # low-charge (300 m) shots only
#
# -TuningOff sets AiOdfGameplayTuning = 0 for the run and puts
# openshim.ini back afterwards. Windowed is forced (BZR_FORCE_WINDOWED=1);
# use Stop-BZRGame, never kill the process.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(0, 300)]
    [int]$RunSeconds = 0,
    [switch]$TuningOff,
    [ValidateRange(20, 230)]
    [int]$EnemyGap = 170,   # avturr-to-svturr distance in metres; the mod avturr scans to 230 m
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
$env:OPENSHIM_TRACE_AI_RANGE = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$overlay = Join-Path $PSScriptRoot "test_missions\lcbench_turretrange\turretrange.lua"
$ini = Join-Path $GameRoot "openshim.ini"
$logRoot = Join-Path $GameRoot "logs"
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$tag = if ($TuningOff) { "off" } else { "on" }
if (-not $OutputRoot) { $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcturret_${tag}_$stamp" }

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
$iniBackup = Join-Path $OutputRoot "openshim.ini.orig"
Copy-Item -LiteralPath $ini -Destination $iniBackup -Force

try {
    [IO.File]::WriteAllText($live, "EnemyGap = $EnemyGap`n" + [IO.File]::ReadAllText($overlay))
    if ($TuningOff) {
        $text = [IO.File]::ReadAllText($ini)
        $patched = [regex]::Replace($text, '(?m)^(\s*AiOdfGameplayTuning\s*=\s*)1\b', '${1}0')
        if ($patched -eq $text) { throw "AiOdfGameplayTuning = 1 not found in $ini" }
        [IO.File]::WriteAllText($ini, $patched)
    }
    Assert-BZRSafeToLaunch   # refuses unless the game cannot steal foreground/mouse; starts the watchdog
    $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
    if ($RunSeconds -gt 0) {
        if (-not $process.WaitForExit($RunSeconds * 1000)) { Stop-BZRGame -Id $process.Id }
    } else {
        Write-Host "Game running; the avturr gets its MAG cannon at T+3 s and the test ends at T+63 s."
        $process.WaitForExit()
    }
} finally {
    $own = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Where-Object { try { $_.Path -ieq $gameExe } catch { $false } })
    if ($own.Count -gt 0) { Stop-BZRGame -Id @($own.Id) }
    Copy-Item -LiteralPath $iniBackup -Destination $ini -Force
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
Write-Host "Logs: $OutputRoot (look for [LCTURR] in BZLogger.txt and [AIODF] Turret in openshim.log)"
