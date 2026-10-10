# Participant selection/reporting regression, without game processes. Native
# registry, replication and input are qualified by the live four-client suite.
$ErrorActionPreference = 'Stop'
. (Join-Path (Split-Path $PSScriptRoot) 'BZRCoopMission.ps1')
$fixtureRoot = [IO.Path]::GetFullPath((Join-Path ([IO.Path]::GetTempPath()) ('crflow-participants-' + [guid]::NewGuid().ToString('N'))))
$null = New-Item -ItemType Directory -Path $fixtureRoot
$checks = 0
$script:participantCount = 4
function Check([bool]$Ok, [string]$Message) { if (-not $Ok) { throw $Message }; $script:checks++ }
function Get-CRFlowSession { @{ clients = @(0..($script:participantCount - 1) | ForEach-Object { [pscustomobject]@{ index = $_; dir = $fixtureRoot } }) } }
function Reset-Checks { $script:CRFlowRun = @{ checks = New-Object Collections.ArrayList } }
function Get-CRFlowEvents([int]$Client, [string]$Kind) { if ($Kind -eq 'op') { $script:fixtureEvents[$Client] } }
function Get-CRFlowLogPath($Client) { Join-Path $fixtureRoot "c$($Client.index).log" }
function Event([string]$Op, $Arguments) { [pscustomobject]@{ op = $Op; args = @($Arguments) } }
try {
    Check ((@(Get-CRFlowClientIndices) -join ',') -eq '0,1,2,3') ('four indices selected: ' + (@(Get-CRFlowClientIndices) -join ','))
    $script:fixtureEvents = @{}
    foreach ($client in 0..3) { $script:fixtureEvents[$client] = @(Event SucceedMission @(42, 'test.des')) }
    Reset-Checks
    Test-CRFlowResultParity -Expect SucceedMission -Debrief test.des
    Check ($script:CRFlowRun.checks.Count -eq 4 -and -not @($script:CRFlowRun.checks | Where-Object status -eq fail).Count) 'results checked on all four'
    $script:fixtureEvents[3] += Event SucceedMission @(43, 'test.des')
    Reset-Checks
    Test-CRFlowResultParity -Expect SucceedMission -Debrief test.des
    Check (@($script:CRFlowRun.checks | Where-Object status -eq fail).Count -eq 1) 'duplicate fourth-client result rejected'
    foreach ($client in 0..3) { $script:fixtureEvents[$client] = @(Event AddObjective @('test.otf', 'white')) }
    Reset-Checks
    Test-CRFlowPresentationParity
    Check ($script:CRFlowRun.checks.Count -eq 3 -and -not @($script:CRFlowRun.checks | Where-Object status -eq fail).Count) 'three guests compared with host'
    $script:participantCount = 2
    Reset-Checks
    Test-CRFlowPresentationParity
    Check ($script:CRFlowRun.checks.Count -eq 1 -and $script:CRFlowRun.checks[0].status -eq 'pass') 'two-client presentation default preserved'
    foreach ($client in 0..1) { $script:fixtureEvents[$client] = @(Event FailMission @(42, 'test.des')) }
    Reset-Checks
    Test-CRFlowResultParity -Expect FailMission -Debrief test.des
    Check ($script:CRFlowRun.checks.Count -eq 2 -and -not @($script:CRFlowRun.checks | Where-Object status -eq fail).Count) 'two-client result default preserved'
    $script:participantCount = 4
    foreach ($client in 0..3) { $script:fixtureEvents[$client] = @(Event AddObjective @('test.otf', 'white')) }
    $script:fixtureEvents[3] = @()
    Reset-Checks
    Test-CRFlowPresentationParity
    Check (@($script:CRFlowRun.checks | Where-Object status -eq fail).Count -eq 1) 'missing fourth-client presentation rejected'
    foreach ($client in 0..3) { [IO.File]::WriteAllText((Join-Path $fixtureRoot "c$client.log"), '') }
    [IO.File]::WriteAllText((Join-Path $fixtureRoot 'c3.log'), 'Lua error: fourth client')
    Reset-Checks
    Test-CRFlowLogErrors
    Check ($script:CRFlowRun.checks.Count -eq 16 -and @($script:CRFlowRun.checks | Where-Object status -eq fail).Count -eq 1) 'fourth-client script errors affect verdict'
    [IO.File]::WriteAllText((Join-Path $fixtureRoot 'c3.log'), '')
    $overlayFixture = Join-Path $fixtureRoot 'campaignReimagined_subtitle_overlay_errors.log'
    [IO.File]::WriteAllText($overlayFixture, '[11.3] reason=overlay-unavailable mode=play')
    Reset-Checks
    Test-CRFlowLogErrors -Clients @(3)
    Check (@($script:CRFlowRun.checks | Where-Object { $_.status -eq 'fail' -and $_.check -eq 'c3 subtitle overlay healthy' }).Count -eq 1) 'subtitle fallback notice affects verdict'
    Remove-Item -LiteralPath $overlayFixture

    function Invoke-CRFlowStep([string]$Name, [scriptblock]$Body) { & $Body }
    function Wait-CRFlowEvent { $true }
    function Wait-CRFlow([int]$Client) {
        @{ role = @{ team = $Client + 1; authority = ($Client -eq 0); lateJoiners = $false }
           players = @(1..4 | ForEach-Object { @{ team = $_; handle = @{ valid = $true; team = $_; local = ($_ -eq ($Client + 1) -and -not ($script:missingOwnership -and $Client -eq 3)) } } }) }
    }
    function Invoke-CRFlow([int]$Client) { -not ($script:missingAlliance -and $Client -eq 3) }
    Test-CRFlowRoster -ExpectedClients 4
    Check $true 'four-client native roster accepted'
    $script:missingAlliance = $true
    $rejected = $false
    try { Test-CRFlowRoster -ExpectedClients 4 } catch { $rejected = $_.Exception.Message -like '*missing directional human alliance*' }
    Check $rejected 'fourth-client missing alliance rejected'
    $script:missingAlliance = $false
    $script:missingOwnership = $true
    $rejected = $false
    try { Test-CRFlowRoster -ExpectedClients 4 } catch { $rejected = $_.Exception.Message -like '*incorrect human craft ownership*' }
    Check $rejected 'fourth-client missing owner rejected'
    Write-Host "Test-CRFlowParticipants: $checks checks passed"
} finally {
    $safeTemp = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not $fixtureRoot.StartsWith($safeTemp, [StringComparison]::OrdinalIgnoreCase)) { throw 'Unexpected fixture cleanup path' }
    Remove-Item -LiteralPath $fixtureRoot -Recurse -Force
}
