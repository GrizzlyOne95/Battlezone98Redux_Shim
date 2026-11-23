# Live test for [SinglePlayer] HowitzerAttackApproach: loads the lcbench world
# with the howitzerapproach.lua overlay, which builds a friendly avartl, an enemy
# svrecy EnemyGap m beyond it (out of shell reach) and an unarmed enemy decoy
# beside the path, and orders Attack(avartl, svrecy) at T+3. With the feature on
# the howitzer should pack up, drive, deploy in reach and fire, keeping the
# ordered target as it passes the decoy; off, it should stay put (stock "out of
# range"). Debug only; it deploys addon/lcbench/lcbench.lua and restores the
# prior file and openshim.ini when the game exits. Requires the lcbench
# baseline in addon\lcbench and the build deployed to the game.
#
#   pwsh -File reverse_engineering/run_lchowapproach.ps1              # feature on
#   pwsh -File reverse_engineering/run_lchowapproach.ps1 -FeatureOff  # A/B: stock out of range
#
# Runs in the background (never takes the foreground): RunInBackground is set
# to 1 for the run. Takes bzr_livetest.lock in the game root and refuses if
# another holder has it. Use Stop-BZRGame, never kill the process.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(0, 300)]
    [int]$RunSeconds = 170,   # ~18 s of loading + the 130 s script
    [switch]$FeatureOff,
    [ValidateRange(50, 1200)]
    [int]$EnemyGap = 800,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
$env:OPENSHIM_RUN_IN_BACKGROUND = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$overlay = Join-Path $PSScriptRoot "test_missions\lcbench_howitzerapproach\howitzerapproach.lua"
$ini = Join-Path $GameRoot "openshim.ini"
$logRoot = Join-Path $GameRoot "logs"
$lock = Join-Path $GameRoot "bzr_livetest.lock"
$watchdog = Join-Path $env:TEMP "bzr_foreground_watchdog.log"
$watchdogStart = if (Test-Path -LiteralPath $watchdog) { @(Get-Content -LiteralPath $watchdog).Count } else { 0 }
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$tag = if ($FeatureOff) { "off" } else { "on" }
if (-not $OutputRoot) { $OutputRoot = Join-Path $GameRoot "openshim_test_results\lchowapproach_${tag}_$stamp" }

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "The lcbench baseline is not installed at $missionRoot"
}
if (@(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue).Count -gt 0) {
    throw "Refusing to start while another Battlezone process is running"
}
# CreateNew takes the lock atomically: it fails if another holder has it.
try {
    $stream = [IO.File]::Open($lock, [IO.FileMode]::CreateNew, [IO.FileAccess]::Write)
} catch {
    throw "Live-test lock held: $(Get-Content -LiteralPath $lock -Raw -ErrorAction SilentlyContinue)"
}
$bytes = [Text.Encoding]::UTF8.GetBytes("run_lchowapproach.ps1 pid=$PID $(Get-Date -Format o)")
$stream.Write($bytes, 0, $bytes.Length)
$stream.Dispose()
$process = $null

$live = Join-Path $missionRoot "lcbench.lua"
$had = Test-Path -LiteralPath $live
$iniBackup = Join-Path $OutputRoot "openshim.ini.orig"
try {
    New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null
    if ($had) { Copy-Item -LiteralPath $live -Destination (Join-Path $OutputRoot "lcbench.lua.orig") -Force }
    Copy-Item -LiteralPath $ini -Destination $iniBackup -Force

    [IO.File]::WriteAllText($live, "EnemyGap = $EnemyGap`n" + [IO.File]::ReadAllText($overlay))
    $text = [IO.File]::ReadAllText($ini)
    $text = [regex]::Replace($text, '(?m)^(\s*RunInBackground\s*=\s*)0\b', '${1}1')
    $value = if ($FeatureOff) { '0' } else { '1' }
    if ($text -match '(?m)^\s*HowitzerAttackApproach\s*=') {
        $text = [regex]::Replace($text, '(?m)^(\s*HowitzerAttackApproach\s*=\s*)\d\b', "`${1}$value")
    } else {
        $text = [regex]::Replace($text, '(?m)^\[SinglePlayer\]\s*$', "[SinglePlayer]`r`nHowitzerAttackApproach = $value", 1)
        if ($text -notmatch '(?m)^\s*HowitzerAttackApproach\s*=') { throw "[SinglePlayer] not found in $ini" }
    }
    [IO.File]::WriteAllText($ini, $text)

    $dll = Join-Path $GameRoot "plugins\openshim.dll"
    Write-Host "openshim.dll SHA256: $((Get-FileHash -LiteralPath $dll -Algorithm SHA256).Hash)"
    Assert-BZRSafeToLaunch   # refuses unless the game cannot steal foreground/mouse; starts the watchdog
    $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
    if ($RunSeconds -gt 0) {
        if (-not $process.WaitForExit($RunSeconds * 1000)) { Stop-BZRGame -Id $process.Id }
    } else {
        $process.WaitForExit()
    }
} finally {
    # Only the PID this run started.
    if ($process -and -not $process.HasExited) { Stop-BZRGame -Id $process.Id }
    if (Test-Path -LiteralPath $iniBackup) { Copy-Item -LiteralPath $iniBackup -Destination $ini -Force }
    if ($had) { Copy-Item -LiteralPath (Join-Path $OutputRoot "lcbench.lua.orig") -Destination $live -Force }
    elseif (Test-Path -LiteralPath $live) { Remove-Item -LiteralPath $live -Force }
    foreach ($name in @("BZLogger.txt", "openshim.log")) {
        $source = Join-Path $logRoot $name
        if (Test-Path -LiteralPath $source) { Copy-Item -LiteralPath $source -Destination (Join-Path $OutputRoot $name) -Force }
    }
    Remove-Item -LiteralPath $lock -Force -ErrorAction SilentlyContinue
}
# Only lines this run added; the watchdog log is cumulative.
if ((Test-Path -LiteralPath $watchdog) -and
    (@(Get-Content -LiteralPath $watchdog | Select-Object -Skip $watchdogStart) -match "FOREGROUND-STOLEN").Count -gt 0) {
    Write-Warning "FOREGROUND-STOLEN in $watchdog - stop launching and report."
}
# Fixture check: the run must have loaded the lcbench mission.
$bzLog = Join-Path $OutputRoot "BZLogger.txt"
if (-not ((Test-Path -LiteralPath $bzLog) -and
        (Select-String -LiteralPath $bzLog -SimpleMatch "addon\lcbench\lcbench.bzn" -Quiet))) {
    Write-Warning "FIXTURE: BZLogger.txt does not show addon\lcbench\lcbench.bzn loading; results are not evidence."
}
Write-Host "Logs: $OutputRoot (look for [LCHOWA] in BZLogger.txt and [HOWAPPR] in openshim.log)"
