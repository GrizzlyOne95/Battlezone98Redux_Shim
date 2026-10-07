# Runs a list of co-op mission flow cases back to back (each a full
# Run-BZRCoopMission.ps1 run: fresh server, launch, lobby, scenario, stop) and
# writes one table of verdicts.
#
#   powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopSuite.ps1
#   powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopSuite.ps1 -Only misn04
#
# A case is "<mission> <scenario> [Name=Value ...]"; Name=Value pairs become
# the scenario's -ScenarioArgs, except Override=<folder>, which runs with
# coopflow\overrides\<folder> copied over the staged CR content. Stops at the first case whose run could not
# start (preflight refused, e.g. the game is open); a failed verdict continues.
# Summary: C:\BZRCoop\runs\suite-<stamp>\suite.md. Windows PowerShell 5.1.

param(
    [string[]]$Cases = @(
        'misn03 win',
        'misn03 win Skipper=host',
        'misn03 lose-tower',
        'misn02b win Override=misn02b-onfoot ExpectOnFoot=1',
        'misn02b win Override=misn02b-onfoot ExpectOnFoot=1 Skipper=host',
        'misn02b win Override=misn02b-onfoot ExpectOnFoot=1 Skipper=none NaturalIntro=1',
        'misn04 win',
        'misn02b host-leaves Override=misn02b-onfoot',
        'misn05 win Override=misn05-coop',
        'misn05 win Override=misn05-coop Skipper=host',
        'misn05 win Override=misn05-coop Skipper=none',
        'misn05 lose Override=misn05-coop Destroyed=factory',
        'misn05 lose Override=misn05-coop Destroyed=recycler',
        'misn05 coop-respawn Override=misn05-coop',
        'misn05 host-leaves Override=misn05-coop'
    ),
    # Run only cases whose text contains this.
    [string]$Only = '',
    [ValidateRange(2, 4)][int]$Clients = 2,
    [switch]$StopOnFailure,
    [string]$BZRCoopRoot = 'C:\BZRCoop'
)

$ErrorActionPreference = 'Stop'
$PowerShellExe = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$suiteDir = (New-Item -ItemType Directory -Force -Path (Join-Path $BZRCoopRoot "runs\suite-$stamp")).FullName
$rows = New-Object System.Collections.ArrayList

foreach ($case in $Cases) {
    if ($Only -and $case -notlike "*$Only*") { continue }
    $parts = @($case -split '\s+' | Where-Object { $_ })
    $mission, $scenario = $parts[0], $parts[1]
    $override = ''
    $argText = @($parts | Select-Object -Skip 2 | ForEach-Object {
        $k, $v = $_ -split '=', 2
        if ($k -eq 'Override') { $override = Join-Path $PSScriptRoot "coopflow\overrides\$v"; return }
        # Switches (e.g. ExpectOnFoot=1) need a real boolean when splatted.
        if ($v -in '1', 'true') { return "$k=`$true" }
        if ($v -in '0', 'false') { return "$k=`$false" }
        "$k='$($v -replace "'", "''")'"
    }) -join '; '
    $overrideArg = if ($override) { " -ContentOverride '$override'" } else { '' }
    $tag = (@($parts | Select-Object -Skip 1) -join '-') -replace '[^\w-]', ''
    $runName = "cr-$mission-$tag-$($Clients)p-$stamp"
    Write-Host "`n[suite] $case -> $runName" -ForegroundColor Cyan
    $cmd = "& '$PSScriptRoot\Run-BZRCoopMission.ps1' -Mission $mission -Scenario $scenario -Clients $Clients -RunName '$runName' -BZRCoopRoot '$BZRCoopRoot'$overrideArg -ScenarioArgs @{$argText}; exit `$LASTEXITCODE"
    $clock = [Diagnostics.Stopwatch]::StartNew()
    # Output goes to files, not a pipe: the run's server and coordinator inherit
    # its handles and can outlive it, which would hold a pipe open forever.
    $log = Join-Path $suiteDir "$runName.log"
    $p = Start-Process -FilePath $PowerShellExe -ArgumentList '-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass', '-Command', "`"$($cmd -replace '"', '\"')`"" `
        -RedirectStandardOutput $log -RedirectStandardError "$log.err" -NoNewWindow -PassThru
    $null = $p.Handle   # keeps ExitCode readable after exit
    $p.WaitForExit()
    $code = $p.ExitCode
    Get-Content -LiteralPath $log, "$log.err" -ErrorAction SilentlyContinue | Out-Host
    $summaryPath = Join-Path $BZRCoopRoot "runs\$runName\flow-summary.json"
    $s = if (Test-Path -LiteralPath $summaryPath) { Get-Content -LiteralPath $summaryPath -Raw | ConvertFrom-Json } else { $null }
    $failed = if ($s) { @(@($s.steps | Where-Object status -eq 'fail' | ForEach-Object { "step: $($_.step) -- $($_.detail)" }) + @($s.checks | Where-Object status -eq 'fail' | ForEach-Object { "check: $($_.check)" })) } else { @() }
    $warned = if ($s) { @(@($s.steps | Where-Object status -eq 'warn' | ForEach-Object { $_.step }) + @($s.checks | Where-Object status -eq 'warn' | ForEach-Object { $_.check })) } else { @() }
    [void]$rows.Add([ordered]@{
        case = $case; clients = $Clients; run = $runName; verdict = if ($s) { $s.verdict } else { 'NO RUN' }
        minutes = [math]::Round($clock.Elapsed.TotalMinutes, 1); exit = $code
        failed = $failed; warned = $warned
    })
    Write-Host "[suite] $case -> $($rows[-1].verdict)" -ForegroundColor $(if ($rows[-1].verdict -eq 'PASS') { 'Green' } else { 'Red' })
    if (-not $s) { Write-Host '[suite] run did not start; stopping the suite.' -ForegroundColor Red; break }
    if ($StopOnFailure -and $rows[-1].verdict -ne 'PASS') { Write-Host '[suite] stopping at the first failed case.' -ForegroundColor Red; break }
}

$md = New-Object System.Text.StringBuilder
[void]$md.AppendLine("# Co-op flow suite $stamp`n")
[void]$md.AppendLine('| Case | Verdict | Min | Failed | Warnings | Run |')
[void]$md.AppendLine('|---|---|---|---|---|---|')
foreach ($r in $rows) {
    [void]$md.AppendLine("| $($r.case) | $($r.verdict) | $($r.minutes) | $(($r.failed -join '<br>') -replace '\|', '/') | $(($r.warned -join '<br>') -replace '\|', '/') | ``runs\$($r.run)`` |")
}
Set-Content -LiteralPath (Join-Path $suiteDir 'suite.md') -Value $md.ToString()
$rows | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $suiteDir 'suite.json')
Write-Host "`n$($md.ToString())"
Write-Host "[suite] -> $(Join-Path $suiteDir 'suite.md')"
if (@($rows | Where-Object verdict -ne 'PASS').Count) { exit 1 }
exit 0
