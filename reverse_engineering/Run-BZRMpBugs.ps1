# Stock multiplayer bug pack (coopflow\battleload\mpbugs.lua) on the private
# server: stages the mpbugs map, then runs one case through Run-BZRCoopMission.
#
#   MissionEnd  a mission result called on the host only (or on every peer, as
#               the control arm) and whether each guest's mission ends.
#   HostLeave   the host closes the game mid-mission; what the guests keep.
#   Weapons     one Daywrecker and one Splinter, from the host or a guest
#               (-ScenarioArgs @{ Launcher = 'guest' }): explosive lifetimes,
#               witness damage per owner and terrain per peer. Turns on the
#               MPAUTH trace (Docs\MPAUTH_* investigations) unless -NoTrace.
#
# -Expect Stock passes when the stock defect reproduces; -Expect Fixed passes
# when it is gone, so the same case serves as a regression test after a fix.
param([Parameter(Mandatory)][ValidateSet('MissionEnd','HostLeave','Weapons')][string]$Case,
      [ValidateRange(2,4)][int]$Clients = 2,
      [ValidateSet('Stock','Fixed')][string]$Expect = 'Stock',
      [hashtable]$ScenarioArgs = @{},
      [string]$Impair = '',
      [string]$Python = 'python',
      [switch]$AllowNoAudioEndpoint,
      # Run beside another session's game (see Run-BZRCoopMission.ps1).
      [switch]$AllowOtherGames,
      [switch]$MaxNetworkLogging,
      [switch]$NoTrace,
      # Reuse the prepared C:\BZRCoop instances instead of re-mirroring the install.
      [switch]$SkipPrepare,
      [string]$RunName = ('mpbugs-' + $Case.ToLower() + '-' + (Get-Date -Format 'yyyyMMdd-HHmmss')),
      [int]$InheritedLaunchLockOwner = 0)
$ErrorActionPreference = 'Stop'
$override = Join-Path 'C:\BZRCoop\runs' ($RunName + '-map')
& $Python (Join-Path $PSScriptRoot 'coopflow\battleload\prepare_battle_map.py') --output $override --map mpbugs
if ($LASTEXITCODE -ne 0) { throw 'Bug pack map staging failed.' }
$scenarioName = @{ MissionEnd = 'mpbugs-mission-end.ps1'; HostLeave = 'mpbugs-host-leave.ps1'; Weapons = 'mpbugs-weapons.ps1' }[$Case]
# The clients inherit this process's environment.
if ($Case -eq 'Weapons' -and -not $NoTrace) { $env:OPENSHIM_TRACE_MPAUTH = '1' }
$scenario = Join-Path $override $scenarioName
Copy-Item -LiteralPath (Join-Path $PSScriptRoot ('coopflow\scenarios\' + $scenarioName)) -Destination $scenario
$ScenarioArgs = $ScenarioArgs.Clone()
$ScenarioArgs.Expect = $Expect
& (Join-Path $PSScriptRoot 'Run-BZRCoopMission.ps1') -Mission mpbugs -Scenario $scenario `
    -MapListY 99 -ContentOverride $override -Clients $Clients -SkipPrepare:$SkipPrepare -MuteClients `
    -MaxNetworkLogging:$MaxNetworkLogging -RunName $RunName -Python $Python -Impair $Impair `
    -AllowNoAudioEndpoint:$AllowNoAudioEndpoint -AllowOtherGames:$AllowOtherGames `
    -InheritedLaunchLockOwner $InheritedLaunchLockOwner -HardTimeoutSeconds 1500 `
    -ScenarioArgs $ScenarioArgs
exit $LASTEXITCODE
