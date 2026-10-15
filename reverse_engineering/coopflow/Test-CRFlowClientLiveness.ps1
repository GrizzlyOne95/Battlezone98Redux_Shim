# Real liveness policy with fake process presence: no game is launched.
$ErrorActionPreference='Stop'
. (Join-Path (Split-Path $PSScriptRoot) 'BZRCoopMission.ps1')
function Get-CRFlowSession { @{coordinatorPid=900;clients=@(@{index=0;pid=901},@{index=1;pid=902})} }
function Get-Process([int]$Id) {if($script:present -contains $Id){[pscustomobject]@{Id=$Id}}}
function Get-CRFlowLogPath { $null }
function Verify([int[]]$Present,[int[]]$ExpectedExit,[string]$Expected,[string]$Label){
 $script:present=$Present;$script:CRFlowExpectedExit=$ExpectedExit
 $script:CRFlowRun=@{checks=New-Object Collections.ArrayList}
 Test-CRFlowClientLiveness
 if($script:CRFlowRun.checks.Count -ne 1 -or $script:CRFlowRun.checks[0].status -ne $Expected){throw $Label}
}
Verify @(900,901,902) @() pass 'live peers accepted'
Verify @(900,901) @() fail 'exit after last scenario step must fail'
Verify @(900,902) @(901) pass 'intentional host departure remains allowed'
Verify @(901,902) @() fail 'orphaned live peers must fail'
Verify @() @() fail 'clean logs cannot accept an exited session'
Write-Host 'Test-CRFlowClientLiveness: 5 cases passed'
