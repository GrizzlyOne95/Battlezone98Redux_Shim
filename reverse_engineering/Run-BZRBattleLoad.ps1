# Private test-map entry point. Native deployment/display adaptation belongs to
# the existing network control runner; this reuses its prepared internal clients.
param([ValidateRange(4,160)][int]$Units = 40,
      [ValidateRange(15,300)][int]$Seconds = 60,
      [string]$Impair = '',
      [string]$ServerRepo = 'C:\Users\iestu\Documents\GIT\Battlezone98Redux_DedicatedServer-bounded-pairports',
      [string]$Python = 'python',
      [switch]$AllowNoAudioEndpoint,
      [ValidateRange(0,16)][int]$Beacons = 0,
      [ValidateRange(0,128)][int]$Powerups = 0,
      # Classic: host owns both armies (teams 5/6). Strategy: each of the 4 clients
      # owns its own army (teams 5..8); Units is the total and must divide by 4.
      [ValidateSet('Classic','Strategy')][string]$Mode = 'Classic',
      [string]$RunName = ('battle-load-' + (Get-Date -Format 'yyyyMMdd-HHmmss')),
      [int]$InheritedLaunchLockOwner = 0,
      # Private test copy only; the immutable staged campaign is not edited.
      [string]$CoopOverride = '')
$ErrorActionPreference = 'Stop'
if ($Units % 2) { throw 'Units must be even.' }
if ($Mode -eq 'Strategy' -and $Units % 4) { throw 'Strategy mode: Units must be divisible by 4.' }
if ($Mode -eq 'Strategy' -and ($Beacons -or $Powerups)) { throw 'Strategy mode does not stage beacons or powerups.' }
$override = Join-Path 'C:\BZRCoop\runs' ($RunName + '-map')
& $Python (Join-Path $PSScriptRoot 'coopflow\battleload\prepare_battle_map.py') --output $override
if ($LASTEXITCODE -ne 0) { throw 'Battle map staging failed.' }
$scenarioName = if ($Mode -eq 'Strategy') { 'sbattle-battle-load.ps1' } else { 'nbattle-battle-load.ps1' }
$scenario = Join-Path $override $scenarioName
Copy-Item -LiteralPath (Join-Path $PSScriptRoot ('coopflow\scenarios\' + $scenarioName)) -Destination $scenario
if ($CoopOverride) {
    if (-not (Test-Path -LiteralPath $CoopOverride -PathType Leaf)) { throw 'CoopOverride file is missing.' }
    Copy-Item -LiteralPath $CoopOverride -Destination (Join-Path $override 'CRCoop.lua')
    @{source=$CoopOverride; sha256=(Get-FileHash -LiteralPath $CoopOverride).Hash} |
        ConvertTo-Json | Set-Content -LiteralPath (Join-Path $override 'coop-override-provenance.json')
}
& (Join-Path $PSScriptRoot 'Run-BZRCoopMission.ps1') -Mission nbattle -Scenario $scenario `
    -MapListY 99 -ContentOverride $override -Clients 4 -SkipPrepare -MaxNetworkLogging -MuteClients `
    -RunName $RunName -ServerRepo $ServerRepo -Python $Python -Impair $Impair `
    -AllowNoAudioEndpoint:$AllowNoAudioEndpoint `
    -InheritedLaunchLockOwner $InheritedLaunchLockOwner `
    -HardTimeoutSeconds (1500 + 2 * $Seconds) `
    -ScenarioArgs @{Units=$Units; Seconds=$Seconds; Beacons=$Beacons; Powerups=$Powerups}
exit $LASTEXITCODE
