# Private test-map entry point. Native deployment/display adaptation belongs to
# the existing network control runner; this reuses its prepared internal clients.
param([ValidateRange(4,160)][int]$Units = 40,
      [ValidateRange(15,300)][int]$Seconds = 60,
      [string]$Impair = '',
      [string]$ServerRepo = 'C:\Users\iestu\Documents\GIT\Battlezone98Redux_DedicatedServer-bounded-pairports',
      [string]$Python = 'python',
      [switch]$AllowNoAudioEndpoint,
      [string]$RunName = ('battle-load-' + (Get-Date -Format 'yyyyMMdd-HHmmss')))
$ErrorActionPreference = 'Stop'
if ($Units % 2) { throw 'Units must be even.' }
$override = Join-Path 'C:\BZRCoop\runs' ($RunName + '-map')
& $Python (Join-Path $PSScriptRoot 'coopflow\battleload\prepare_battle_map.py') --output $override
if ($LASTEXITCODE -ne 0) { throw 'Battle map staging failed.' }
$scenario = Join-Path $override 'nbattle-battle-load.ps1'
Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'coopflow\scenarios\nbattle-battle-load.ps1') -Destination $scenario
& (Join-Path $PSScriptRoot 'Run-BZRCoopMission.ps1') -Mission nbattle -Scenario $scenario `
    -MapListY 99 -ContentOverride $override -Clients 4 -SkipPrepare -MaxNetworkLogging -MuteClients `
    -RunName $RunName -ServerRepo $ServerRepo -Python $Python -Impair $Impair `
    -AllowNoAudioEndpoint:$AllowNoAudioEndpoint `
    -ScenarioArgs @{Units=$Units; Seconds=$Seconds}
exit $LASTEXITCODE
