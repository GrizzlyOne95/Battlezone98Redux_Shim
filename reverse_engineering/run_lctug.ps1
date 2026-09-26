<#
.SYNOPSIS
Live check for the OpenShim [BuildingClass] tuggable = 1 ODF key.

.DESCRIPTION
Deploys the lcbench world plus the lcbench_tug fixture (rmtug.lua, tugpow.odf,
tugctl.odf), launches lcbench.bzn windowed, waits for the fixture's DONE marker,
and reports its [TUGFIX] RESULT lines next to the [TUGODF] lines from
openshim.log. Deploy the build under test with scripts/Deploy-OpenShim.ps1
first; the script prints the deployed openshim.dll hash before and after.

Expected on a working build:
  [TUGODF] installed ...                         (openshim.log)
  [TUGODF] ODF tugpow BuildingClass tuggable=1   (openshim.log)
  RESULT POW odf=tugpow picked_up=true  ... PASS
  RESULT CTL odf=tugctl picked_up=false ... PASS
  RESULT STK odf=abstor picked_up=true  ... PASS

.EXAMPLE
pwsh -File reverse_engineering/run_lctug.ps1
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(30, 400)]
    [int]$RunSeconds = 200,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot

$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $env:TEMP "bzr-lctug-$stamp"
}
New-Item -ItemType Directory -Force -Path $OutputRoot | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$worldSource = Join-Path $repoRoot "reverse_engineering\test_missions\live_combat_scaling"
$fixtureRoot = Join-Path $repoRoot "reverse_engineering\test_missions\lcbench_tug"
$pluginDll = Join-Path $GameRoot "plugins\openshim.dll"

foreach ($p in @($gameExe, $worldSource, $fixtureRoot, $pluginDll)) {
    if (-not (Test-Path -LiteralPath $p)) { throw "missing: $p" }
}
Get-Process battlezone98redux -ErrorAction SilentlyContinue | ForEach-Object {
    throw "the game is already running (PID $($_.Id)); close it first"
}

$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $repoRoot "reverse_engineering\BZRHarness.ps1")

$hashBefore = (Get-FileHash -LiteralPath $pluginDll -Algorithm SHA256).Hash
Write-Host "[lctug] openshim.dll before: $hashBefore"

# Fixture files land in addon\lcbench under these names; rmtug.lua becomes the
# mission script.
$deploy = @()
foreach ($src in (Get-ChildItem -LiteralPath $worldSource -File)) {
    $deploy += @{ Source = $src.FullName; Name = $src.Name }
}
foreach ($name in @("tugpow.odf", "tugctl.odf")) {
    $deploy += @{ Source = (Join-Path $fixtureRoot $name); Name = $name }
}
$deploy += @{ Source = (Join-Path $fixtureRoot "rmtug.lua"); Name = "lcbench.lua" }

$missionBackup = Join-Path $OutputRoot "pre_live"
New-Item -ItemType Directory -Force -Path $missionBackup | Out-Null
$createdMissionRoot = $false
$deployedNames = @()
$bzLogger = Join-Path $GameRoot "logs\BZLogger.txt"
$mutex = $null

try {
    $mutex = Enter-BZRLaunchLock
    if (-not (Test-Path -LiteralPath $missionRoot)) {
        New-Item -ItemType Directory -Force -Path $missionRoot | Out-Null
        $createdMissionRoot = $true
    }
    foreach ($item in $deploy) {
        $live = Join-Path $missionRoot $item.Name
        if ((Test-Path -LiteralPath $live) -and -not (Test-Path -LiteralPath (Join-Path $missionBackup $item.Name))) {
            Copy-Item -LiteralPath $live -Destination (Join-Path $missionBackup $item.Name) -Force
        }
        Copy-Item -LiteralPath $item.Source -Destination $live -Force
        $deployedNames += $item.Name
    }
    Write-Host "[lctug] deployed lcbench world + tug fixture"

    $t0 = Get-Date
    Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot | Out-Null
    # battlezone98redux.exe re-execs: follow the process by name, not the
    # launch pid.
    $deadline = $t0.AddSeconds($RunSeconds)
    $sawGame = $false
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Seconds 2
        $game = @(Get-Process battlezone98redux -ErrorAction SilentlyContinue)
        if ($game.Count -gt 0) { $sawGame = $true }
        elseif ($sawGame) { Write-Warning "[lctug] game exited early"; break }
        if ((Test-Path -LiteralPath $bzLogger) -and
            (Get-Item -LiteralPath $bzLogger).LastWriteTime -gt $t0 -and
            (Select-String -LiteralPath $bzLogger -Pattern "\[TUGFIX\].*(DONE|ABORT)" -Quiet)) {
            Write-Host "[lctug] fixture finished"
            break
        }
    }
    foreach ($p in @(Get-Process battlezone98redux -ErrorAction SilentlyContinue)) {
        try { Stop-BZRGame -Id $p.Id } catch { Write-Warning "Stop-BZRGame: $_" }
    }
}
finally {
    foreach ($log in @("BZLogger.txt", "openshim.log", "BZOgreLogfile.log")) {
        $src = Join-Path $GameRoot "logs\$log"
        if (Test-Path -LiteralPath $src) {
            Copy-Item -LiteralPath $src -Destination (Join-Path $OutputRoot $log) -Force
        }
    }
    foreach ($name in $deployedNames) {
        $live = Join-Path $missionRoot $name
        $saved = Join-Path $missionBackup $name
        if (Test-Path -LiteralPath $saved) {
            Copy-Item -LiteralPath $saved -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
    if ($createdMissionRoot -and (Test-Path -LiteralPath $missionRoot)) {
        if (-not (Get-ChildItem -LiteralPath $missionRoot -Force)) {
            Remove-Item -LiteralPath $missionRoot -Force
        }
    }
    Write-Host "[lctug] addon\lcbench restored"
    Exit-BZRLaunchLock -Mutex $mutex
}

$hashAfter = (Get-FileHash -LiteralPath $pluginDll -Algorithm SHA256).Hash
Write-Host "[lctug] openshim.dll after:  $hashAfter"
if ($hashAfter -ne $hashBefore) {
    Write-Warning "[lctug] openshim.dll changed during the run; this run is not evidence about the deployed build"
}

Write-Host ""
Write-Host "[lctug] ===== openshim.log [TUGODF] ====="
$shimLog = Join-Path $OutputRoot "openshim.log"
if (Test-Path -LiteralPath $shimLog) {
    $tug = @(Select-String -LiteralPath $shimLog -Pattern "TUGODF|0x0047B6C0|BuildingClass::String16|ParameterDB::GetInt|Building::Building" | ForEach-Object { $_.Line })
    if ($tug.Count -eq 0) { Write-Warning "  no TUGODF lines: the extension did not install" }
    $tug | ForEach-Object { Write-Host "  $_" }
}

Write-Host ""
Write-Host "[lctug] ===== fixture ====="
$log = Join-Path $OutputRoot "BZLogger.txt"
$fixture = @()
if (Test-Path -LiteralPath $log) {
    $fixture = @(Select-String -LiteralPath $log -Pattern "\[TUGFIX\]" | ForEach-Object { $_.Line })
}
if ($fixture.Count -eq 0) {
    Write-Warning "  no [TUGFIX] markers -- the fixture never ran, so this run says NOTHING"
} else {
    $fixture | Where-Object { $_ -notmatch " TICK " } | ForEach-Object { Write-Host "  $_" }
}
Write-Host ""
Write-Host "[lctug] artifacts in $OutputRoot"
