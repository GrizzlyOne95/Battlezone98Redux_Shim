# Lobby websocket drop mid-mission on the same-PC harness (PR #615
# [Network] LobbyDropKeepsMatch). Stages the mpbugs map and runs
# coopflow\scenarios\lobby-drop.ps1. -ServerRepo must be a DedicatedServer
# copy patched with coopflow\lobbydrop_test_server.py (POST /test/drop-ws).
#   -Mode Keep [-Silent]  both clients must stay in the mission
#   -Mode TrueLoss        the subject's relay goes dark first; stock quit
# Run with Windows PowerShell 5.1 (powershell.exe) and BZR_FORCE_WINDOWED=1.
param([ValidateSet('Keep','TrueLoss')][string]$Mode = 'Keep',
      [int]$Subject = 1,
      [switch]$Silent,
      [switch]$SkipPrepare,
      [switch]$StockShim,
      [Parameter(Mandatory)][string]$ServerRepo,
      [string]$OpenShimRepo = (Split-Path $PSScriptRoot -Parent),
      [string]$RunName = ('lobbydrop-' + (Get-Date -Format 'yyyyMMdd-HHmmss')))
$ErrorActionPreference = 'Stop'
$override = Join-Path 'C:\BZRCoop\runs' ($RunName + '-map')
& python (Join-Path $PSScriptRoot 'coopflow\battleload\prepare_battle_map.py') --output $override --map mpbugs
if ($LASTEXITCODE -ne 0) { throw 'map staging failed' }
$scenario = Join-Path $override 'lobby-drop.ps1'
Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'coopflow\scenarios\lobby-drop.ps1') -Destination $scenario
if ($StockShim) { $env:OPENSHIM_DISABLE_LOBBY_DROP_KEEPS_MATCH = '1' }
& (Join-Path $PSScriptRoot 'Run-BZRCoopMission.ps1') -Mission mpbugs -Scenario $scenario `
    -MapListY 99 -ContentOverride $override -Clients 2 -SkipPrepare:$SkipPrepare -MuteClients `
    -RunName $RunName -OpenShimRepo $OpenShimRepo -ServerRepo $ServerRepo -HardTimeoutSeconds 900 `
    -ScenarioArgs @{ Mode = $Mode; Subject = $Subject; Silent = [bool]$Silent }
exit $LASTEXITCODE
