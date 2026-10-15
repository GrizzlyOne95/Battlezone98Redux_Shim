# Regression for a live misn12 smoke that passed despite thousands of caught
# D3D11 vertex-declaration exceptions. No clients, server or game are launched.
$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\..\BZRCoopMission.ps1"
$fixtureRoot = Join-Path ([IO.Path]::GetTempPath()) ('bzr-flow-log-errors-' + [Guid]::NewGuid())
New-Item -ItemType Directory -Path $fixtureRoot | Out-Null
$script:fixtureLog = Join-Path $fixtureRoot 'BZLogger.txt'
function Get-CRFlowClient([int]$Index) { @{index = $Index} }
function Get-CRFlowLogPath($Client) { $script:fixtureLog }
function Get-CRFlowEvents([int]$Client, [string]$Kind) { @() }
function Test-CRFlowUnresolvedCounter { } # Fixture has no live probe/session.
try {
    foreach ($case in @(
        @{name='healthy'; log='Simulation initialized'; failed=@()},
        @{name='caught Ogre exception'; log='Ogre Rendering Exception Seen: OGRE EXCEPTION(3:RenderingAPIException): Unable to set D3D11 vertex declaration'; failed=@('c0 no Ogre rendering exceptions')},
        @{name='caught UI Ogre exception'; log='Ogre Rendering Exception Seen from UI: OGRE EXCEPTION(3:RenderingAPIException): no fixed pipeline in d3d11'; failed=@('c0 no Ogre rendering exceptions')},
        @{name='Lua failure'; log='Lua error: attempt to index a nil value'; failed=@('c0 no Lua or engine script errors')},
        @{name='camera stack failure'; log='Fsm error: Camera Stack 0verfow'; failed=@('c0 no Lua or engine script errors')}
    )) {
        Set-Content -LiteralPath $script:fixtureLog -Value $case.log
        Start-CRFlowRun -RunDir $fixtureRoot -Mission fixture -Scenario $case.name
        Test-CRFlowLogErrors @(0)
        $failed = @($script:CRFlowRun.checks | Where-Object status -eq 'fail' | ForEach-Object {$_.check})
        if (($failed -join '|') -ne ($case.failed -join '|')) {
            throw "$($case.name): unexpected failed checks: $($failed -join ', ')"
        }
        if ($case.failed.Count) {
            $detail = @($script:CRFlowRun.checks | Where-Object status -eq 'fail')[0].detail
            if ($detail -notcontains $case.log) { throw "$($case.name): original error evidence was lost" }
        }
    }
    Write-Host 'PASS: healthy, caught Ogre, Lua and camera-stack logs classified correctly'
} finally {
    # fixtureRoot is a freshly created, task-owned directory inside TEMP.
    $resolvedFixture = [IO.Path]::GetFullPath($fixtureRoot)
    $tempPrefix = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not $resolvedFixture.StartsWith($tempPrefix, [StringComparison]::OrdinalIgnoreCase)) { throw 'Fixture cleanup escaped TEMP' }
    Remove-Item -LiteralPath $resolvedFixture -Recurse -Force
}
