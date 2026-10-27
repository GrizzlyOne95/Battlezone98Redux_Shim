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
        @{name='camera stack failure'; log='Fsm error: Camera Stack 0verfow'; failed=@('c0 no Lua or engine script errors')},
        @{name='device removed'; log='Simulation initialized'; ogre='12:00:01: OGRE EXCEPTION(-2005270523:RenderingAPIException): Failed to create depth stencil state'; failed=@('c0 D3D11 device not removed')},
        @{name='device hung'; log='Simulation initialized'; ogre='12:00:01: OGRE EXCEPTION(-2005270522:RenderingAPIException): Failed to Map buffer'; failed=@('c0 D3D11 device not removed')},
        @{name='device reset'; log='Simulation initialized'; ogre='12:00:01: OGRE EXCEPTION(-2005270521:RenderingAPIException): Present failed'; failed=@('c0 D3D11 device not removed')},
        @{name='renderer log missing'; log='Simulation initialized'; noOgre=$true; evidence='no renderer log'; failed=@('c0 D3D11 device not removed')},
        @{name='shim device recreation'; log='Simulation initialized'; shim='[DX11 Recovery] device recreation #1: hardware adapter settled after 40 ms (2 probes)'; failed=@('c0 D3D11 device not removed')}
    )) {
        Set-Content -LiteralPath $script:fixtureLog -Value $case.log
        $ogre = if ($case.ogre) { $case.ogre } else { 'Start main loop' }
        $ogrePath = Join-Path $fixtureRoot 'BZOgreLogfile.log'
        if ($case.noOgre) { Remove-Item -LiteralPath $ogrePath -ErrorAction SilentlyContinue }
        else { Set-Content -LiteralPath $ogrePath -Value $ogre }
        $shim = if ($case.shim) { $case.shim } else { '[DX11 Buffers] installed' }
        Set-Content -LiteralPath (Join-Path $fixtureRoot 'openshim.log') -Value $shim
        Start-CRFlowRun -RunDir $fixtureRoot -Mission fixture -Scenario $case.name
        Test-CRFlowLogErrors @(0)
        $failed = @($script:CRFlowRun.checks | Where-Object status -eq 'fail' | ForEach-Object {$_.check})
        if (($failed -join '|') -ne ($case.failed -join '|')) {
            throw "$($case.name): unexpected failed checks: $($failed -join ', ')"
        }
        if ($case.failed.Count) {
            $detail = @($script:CRFlowRun.checks | Where-Object status -eq 'fail')[0].detail
            if ($case.evidence) {
                if (-not ($detail -match [regex]::Escape($case.evidence))) { throw "$($case.name): evidence missing from detail: $detail" }
            } else {
                $evidence = if ($case.ogre) { $case.ogre } elseif ($case.shim) { $case.shim } else { $case.log }
                if ($detail -notcontains $evidence) { throw "$($case.name): original error evidence was lost" }
            }
        }
    }
    Write-Host 'PASS: healthy, caught Ogre, device removed/hung/reset, missing renderer log, shim recreation, Lua and camera-stack logs classified correctly'
} finally {
    # fixtureRoot is a freshly created, task-owned directory inside TEMP.
    $resolvedFixture = [IO.Path]::GetFullPath($fixtureRoot)
    $tempPrefix = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not $resolvedFixture.StartsWith($tempPrefix, [StringComparison]::OrdinalIgnoreCase)) { throw 'Fixture cleanup escaped TEMP' }
    Remove-Item -LiteralPath $resolvedFixture -Recurse -Force
}
