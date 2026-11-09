# Any Nation lobby toggle live test (1 local server + 2 clients on this PC).
# Stages the mpbugs map and runs Run-BZRCoopMission.ps1 with a lobby hook.
#   -Hook coopflow\lobby-hooks\<script>.ps1   (default: any-nation-observe)
# Run with Windows PowerShell 5.1 (powershell.exe) and BZR_FORCE_WINDOWED=1.
param([string]$Hook = (Join-Path $PSScriptRoot 'coopflow\lobby-hooks\any-nation-observe.ps1'),
      [string]$Scenario = (Join-Path $PSScriptRoot 'coopflow\scenarios\noop.ps1'),
      [switch]$SkipPrepare,
      [string]$ServerRepo = (Join-Path $env:USERPROFILE 'Documents\GIT\Battlezone98Redux_DedicatedServer'),
      [string]$OpenShimRepo = (Split-Path $PSScriptRoot -Parent),
      [string]$RunName = ('anynation-' + (Get-Date -Format 'yyyyMMdd-HHmmss')))
$ErrorActionPreference = 'Stop'
$override = Join-Path 'C:\BZRCoop\runs' ($RunName + '-map')
& python (Join-Path $PSScriptRoot 'coopflow\battleload\prepare_battle_map.py') --output $override --map mpbugs
if ($LASTEXITCODE -ne 0) { throw 'map staging failed' }
$scn = Join-Path $override 'anynation-scenario.ps1'
Copy-Item -LiteralPath $Scenario -Destination $scn
& (Join-Path $PSScriptRoot 'Run-BZRCoopMission.ps1') -Mission mpbugs -Scenario $scn -MapListY 99 `
    -ContentOverride $override -Clients 2 -SkipPrepare:$SkipPrepare -MuteClients -RunName $RunName `
    -OpenShimRepo $OpenShimRepo -ServerRepo $ServerRepo -LobbyHook $Hook -HardTimeoutSeconds 900
exit $LASTEXITCODE
