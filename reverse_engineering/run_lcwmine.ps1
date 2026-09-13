<#
.SYNOPSIS
Repro for the Arc Mine (weaponmine) discharge at the boarding instant.

.DESCRIPTION
Deploys the lcbench Arc Mine fixture, launches the mission, and reports the
per-tick team/ammo table it prints so the discharge can be located to a single
tick without recognising a sprite in a screenshot.

Background: a 2026-09-13 play01.bzn capture (no mission script, so engine
behaviour only) showed an allied Arc Mine field discharging a gmbolt at the
player on the exact frame the player boarded a craft, twice, and on neither
hop-out. The craft took no damage.

Traced predicate, identical in 1.5 (WeaponMine::Simulate 0x0053F9CF) and Redux
(0x00612950):

    Team::FriendP(n) -> n >= 1 and (dwAllies & (1 << n))

so team 0 is nobody's friend and any object whose ACTUAL team reads 0 is a
valid target for every weapon mine, including its own side's. Person is a Craft
subclass, so pilots on foot are in craftList and are candidate targets too.

What the fixture answers:
  * does a plain friendly (team 1) Arc Mine fire at the boarding transition?
  * does a team-0 Arc Mine fire continuously, as the predicate predicts?
  * does any team read 0 for a tick across the transition?

Ammo is the witness. boltmine.odf has maxAmmo = 100 and the discharge is a
weapon shot, so a drop in GetAmmo names which mine fired and on which tick.

.EXAMPLE
pwsh -File reverse_engineering/run_lcwmine.ps1
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(30, 300)]
    [int]$RunSeconds = 55,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot

$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $env:TEMP "bzr-lcwmine-$stamp"
}
New-Item -ItemType Directory -Force -Path $OutputRoot | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$worldSource = Join-Path $repoRoot "reverse_engineering\test_missions\live_combat_scaling"
$fixture = Join-Path $repoRoot "reverse_engineering\test_missions\lcbench_wmine\rmwmine.lua"

foreach ($p in @($gameExe, $worldSource, $fixture)) {
    if (-not (Test-Path -LiteralPath $p)) { throw "missing: $p" }
}
# The install is a single shared resource and this working tree is shared with
# parallel agents; a second launch would fight over addon\lcbench.
Get-Process battlezone98redux -ErrorAction SilentlyContinue | ForEach-Object {
    throw "the game is already running (PID $($_.Id)); close it first"
}

$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $repoRoot "reverse_engineering\BZRHarness.ps1")

$createdMissionRoot = $false
$missionBackup = Join-Path $OutputRoot "pre_live"
$deployedNames = @()

try {
    if (-not (Test-Path -LiteralPath $missionRoot)) {
        New-Item -ItemType Directory -Force -Path $missionRoot | Out-Null
        $createdMissionRoot = $true
    }
    New-Item -ItemType Directory -Force -Path $missionBackup | Out-Null
    foreach ($src in (Get-ChildItem -LiteralPath $worldSource -File)) {
        $live = Join-Path $missionRoot $src.Name
        if (Test-Path -LiteralPath $live) {
            Copy-Item -LiteralPath $live -Destination (Join-Path $missionBackup $src.Name) -Force
        }
        Copy-Item -LiteralPath $src.FullName -Destination $live -Force
        $deployedNames += $src.Name
    }
    Copy-Item -LiteralPath $fixture -Destination (Join-Path $missionRoot "lcbench.lua") -Force
    Write-Host "[lcwmine] deployed lcbench world + rmwmine.lua fixture"

    $proc = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
        -WorkingDirectory $GameRoot -PassThru
    Write-Host "[lcwmine] launched PID=$($proc.Id)"
    $deadline = (Get-Date).AddSeconds($RunSeconds)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 500
        $proc.Refresh()
        if ($proc.HasExited) { Write-Warning "[lcwmine] game exited early"; break }
    }
    try { Stop-BZRGame -Id $proc.Id } catch { Write-Warning "Stop-BZRGame: $_" }
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
    $liveLua = Join-Path $missionRoot "lcbench.lua"
    $savedLua = Join-Path $missionBackup "lcbench.lua"
    if (Test-Path -LiteralPath $savedLua) {
        Copy-Item -LiteralPath $savedLua -Destination $liveLua -Force
    } elseif (Test-Path -LiteralPath $liveLua) {
        Remove-Item -LiteralPath $liveLua -Force
    }
    if ($createdMissionRoot -and (Test-Path -LiteralPath $missionRoot)) {
        if (-not (Get-ChildItem -LiteralPath $missionRoot -Force)) {
            Remove-Item -LiteralPath $missionRoot -Force
        }
    }
    Write-Host "[lcwmine] addon\lcbench restored"

    $ogreBackup = Join-Path $GameRoot "ogre.cfg.bzrharness-backup"
    if (Test-Path -LiteralPath $ogreBackup) {
        Copy-Item -LiteralPath $ogreBackup -Destination (Join-Path $GameRoot "ogre.cfg") -Force
        Remove-Item -LiteralPath $ogreBackup -Force
    }
}

$log = Join-Path $OutputRoot "BZLogger.txt"
if (-not (Test-Path -LiteralPath $log)) {
    Write-Warning "[lcwmine] no BZLogger.txt captured; nothing to report"
    return
}

$events = @(Select-String -LiteralPath $log -Pattern "\[WMINE\]" | ForEach-Object { $_.Line })
$ticks = @(Select-String -LiteralPath $log -Pattern "\[WMINE-T\]" | ForEach-Object { $_.Line })

Write-Host ""
Write-Host "[lcwmine] ===== fixture events ====="
if ($events.Count -eq 0) {
    # A run with no markers is not a negative result: the mission never ran.
    Write-Warning "[lcwmine] no [WMINE] markers -- the fixture never executed, so this run says NOTHING about the bug"
} else {
    $events | ForEach-Object { Write-Host "  $_" }
}

Write-Host ""
Write-Host "[lcwmine] ===== ammo drops (a drop is a discharge) ====="
$prevF = $null
$prevN = $null
$fired = 0
foreach ($line in $ticks) {
    if ($line -notmatch "T\+([0-9.]+).*fTeam=(-?\d+) fAmmo=(-?\d+) nTeam=(-?\d+) nAmmo=(-?\d+)") { continue }
    $t = [double]$Matches[1]
    $fAmmo = [int]$Matches[3]
    $nAmmo = [int]$Matches[5]
    if ($prevF -ne $null -and $fAmmo -lt $prevF) {
        Write-Host ("  T+{0,-8:F3} FRIENDLY mine fired: ammo {1} -> {2}" -f $t, $prevF, $fAmmo)
        $fired++
    }
    if ($prevN -ne $null -and $nAmmo -lt $prevN) {
        Write-Host ("  T+{0,-8:F3} NEUTRAL  mine fired: ammo {1} -> {2}" -f $t, $prevN, $nAmmo)
        $fired++
    }
    if ($fAmmo -ge 0) { $prevF = $fAmmo }
    if ($nAmmo -ge 0) { $prevN = $nAmmo }
}
if ($fired -eq 0 -and $events.Count -gt 0) {
    Write-Host "  none -- no mine discharged during this run"
}

Write-Host ""
Write-Host "[lcwmine] ===== any tick where a team read 0 ====="
$zeros = @($ticks | Where-Object { $_ -match "(pTeam|craftTeam)=0\b" })
if ($zeros.Count -eq 0) {
    Write-Host "  none"
} else {
    $zeros | Select-Object -First 20 | ForEach-Object { Write-Host "  $_" }
}

Write-Host ""
Write-Host "[lcwmine] ===== ticks around BOARD ====="
$boardIndex = -1
for ($i = 0; $i -lt $ticks.Count; $i++) {
    if ($ticks[$i] -match "T\+([0-9.]+)") {
        if ([double]$Matches[1] -ge 24.0) { $boardIndex = $i; break }
    }
}
if ($boardIndex -ge 0) {
    $from = [math]::Max(0, $boardIndex - 6)
    $to = [math]::Min($ticks.Count - 1, $boardIndex + 10)
    for ($i = $from; $i -le $to; $i++) { Write-Host "  $($ticks[$i])" }
}

Write-Host ""
Write-Host "[lcwmine] artifacts in $OutputRoot"
