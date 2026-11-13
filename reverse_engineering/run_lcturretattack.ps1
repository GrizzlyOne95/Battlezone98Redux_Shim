# Live test for [SinglePlayer] TurretAttackOrders: loads the lcbench world with
# the turretattack.lua overlay, which builds a friendly avturr and an enemy
# svrecy EnemyGap m apart and orders Attack(avturr, svrecy) at T+3. A turret
# ordered at a target beyond its range should pack up, close in, deploy and
# fire. Debug only; it deploys addon/lcbench/lcbench.lua and restores the prior
# file and openshim.ini when the game exits. Requires the lcbench baseline in
# addon\lcbench and the build deployed with scripts/Deploy-OpenShim.ps1.
#
#   pwsh -File reverse_engineering/run_lcturretattack.ps1 -RunSeconds 100              # feature on
#   pwsh -File reverse_engineering/run_lcturretattack.ps1 -RunSeconds 100 -FeatureOff  # A/B: stock deploy-in-place
#
# Runs in the background (never takes the foreground): RunInBackground is set
# to 1 for the run. Takes bzr_livetest.lock in the game root and refuses if
# another holder has it. Use Stop-BZRGame, never kill the process.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(0, 300)]
    [int]$RunSeconds = 100,
    [switch]$FeatureOff,
    [ValidateRange(50, 900)]
    [int]$EnemyGap = 450,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
$env:OPENSHIM_RUN_IN_BACKGROUND = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$overlay = Join-Path $PSScriptRoot "test_missions\lcbench_turretattack\turretattack.lua"
$ini = Join-Path $GameRoot "openshim.ini"
$logRoot = Join-Path $GameRoot "logs"
$lock = Join-Path $GameRoot "bzr_livetest.lock"
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$tag = if ($FeatureOff) { "off" } else { "on" }
if (-not $OutputRoot) { $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcturretattack_${tag}_$stamp" }

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "The lcbench baseline is not installed at $missionRoot"
}
if (@(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue).Count -gt 0) {
    throw "Refusing to start while another Battlezone process is running"
}
if (Test-Path -LiteralPath $lock) {
    throw "Live-test lock held: $(Get-Content -LiteralPath $lock -Raw)"
}
[IO.File]::WriteAllText($lock, "run_lcturretattack.ps1 pid=$PID $(Get-Date -Format o)")

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
    if ($text -match '(?m)^\s*TurretAttackOrders\s*=') {
        $text = [regex]::Replace($text, '(?m)^(\s*TurretAttackOrders\s*=\s*)\d\b', "`${1}$value")
    } else {
        $text = [regex]::Replace($text, '(?m)^\[SinglePlayer\]\s*$', "[SinglePlayer]`r`nTurretAttackOrders = $value", 1)
        if ($text -notmatch '(?m)^\s*TurretAttackOrders\s*=') { throw "[SinglePlayer] not found in $ini" }
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
    $own = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Where-Object { try { $_.Path -ieq $gameExe } catch { $false } })
    if ($own.Count -gt 0) { Stop-BZRGame -Id @($own.Id) }
    if (Test-Path -LiteralPath $iniBackup) { Copy-Item -LiteralPath $iniBackup -Destination $ini -Force }
    if ($had) { Copy-Item -LiteralPath (Join-Path $OutputRoot "lcbench.lua.orig") -Destination $live -Force }
    elseif (Test-Path -LiteralPath $live) { Remove-Item -LiteralPath $live -Force }
    foreach ($name in @("BZLogger.txt", "openshim.log")) {
        $source = Join-Path $logRoot $name
        if (Test-Path -LiteralPath $source) { Copy-Item -LiteralPath $source -Destination (Join-Path $OutputRoot $name) -Force }
    }
    Remove-Item -LiteralPath $lock -Force -ErrorAction SilentlyContinue
}
$watchdog = Join-Path $env:TEMP "bzr_foreground_watchdog.log"
if ((Test-Path -LiteralPath $watchdog) -and (Select-String -LiteralPath $watchdog -Pattern "FOREGROUND-STOLEN" -Quiet)) {
    Write-Warning "FOREGROUND-STOLEN in $watchdog - stop launching and report."
}
Write-Host "Logs: $OutputRoot (look for [LCTATK] in BZLogger.txt and [TURRETATK] in openshim.log)"
