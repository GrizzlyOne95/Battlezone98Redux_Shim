# Non-live test for BZRCoopWatchdog.ps1: no game, lobby server or C:\BZRCoop
# state is touched. Fake runners are read through a stdout pipe, as the retry
# matrix reads Run-BZRBattleLoad.ps1, with a fake server that inherits it.
#   hung    runner blocks after a lobby step timeout: the watchdog stops
#           clients and server, writes a FAIL summary, kills the runner, and
#           the pipe reaches EOF.
#   clean   runner exits after a PASS summary but leaves its server up: the
#           server is stopped, the summary and clients are left alone.
#   crashed runner exits after a failure without a summary: clients and server
#           are stopped and a FAIL summary is written.
$ErrorActionPreference = 'Stop'
$ps51 = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
$root = Join-Path ([IO.Path]::GetTempPath()) ("bzrcoop-watchdog-test-" + [guid]::NewGuid().ToString('N'))
$null = New-Item -ItemType Directory -Path $root
$library = Join-Path $PSScriptRoot 'BZRCoopWatchdog.ps1'

$runner = Join-Path $root 'runner.ps1'
@'
param([string]$Library, [string]$RunDir, [string]$SessionFile, [string]$Mode)
$ErrorActionPreference = 'Stop'
. $Library
$ps51 = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
$null = Start-BZRCoopWatchdog -RunDir $RunDir -SessionFile $SessionFile -FailureGraceSeconds 3 -KillGraceSeconds 3 -PollSeconds 1
# Redirected like server.py: inherits this process's stdout pipe.
$server = Start-Process -FilePath $ps51 -ArgumentList '-NoProfile', '-Command', 'Start-Sleep 600' -WindowStyle Hidden -PassThru `
    -RedirectStandardError (Join-Path $RunDir 'server.log') -RedirectStandardOutput (Join-Path $RunDir 'server.out.log')
Set-BZRCoopWatchdogPid $RunDir 'server' $server.Id
$client = Start-Process -FilePath $ps51 -ArgumentList '-NoProfile', '-Command', 'Start-Sleep 600' -WindowStyle Hidden -PassThru
$dir = New-Item -ItemType Directory -Path (Join-Path $RunDir 'instance0') -Force
Set-Content -LiteralPath (Join-Path $dir 'openshim.log') -Value 'fake client log'
@{ runDir = $RunDir; clients = @(@{ index = 0; pid = $client.Id; dir = $dir.FullName }) } |
    ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $SessionFile
Write-Output "runner started server $($server.Id) client $($client.Id)"
switch ($Mode) {
    'hung' {
        @{ step = 'c0-lounge'; status = 'timeout' } | ConvertTo-Json -Compress | Add-Content -LiteralPath (Join-Path $RunDir 'steps.jsonl')
        Start-Sleep 600
    }
    'clean' {
        @{ verdict = 'PASS' } | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $RunDir 'flow-summary.json')
        exit 0
    }
    'crashed' {
        Set-Content -LiteralPath (Join-Path $RunDir 'flow-failed') -Value 'Stopped early: fake'
        Start-Sleep 2
        exit 1
    }
}
'@ | Set-Content -LiteralPath $runner

function Invoke-FakeRun([string]$Mode) {
    $runDir = (New-Item -ItemType Directory -Path (Join-Path $root $Mode)).FullName
    $session = Join-Path $runDir 'session.json'
    $psi = New-Object Diagnostics.ProcessStartInfo $ps51
    $psi.Arguments = "-NoProfile -ExecutionPolicy Bypass -File `"$runner`" -Library `"$library`" -RunDir `"$runDir`" -SessionFile `"$session`" -Mode $Mode"
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $psi.CreateNoWindow = $true
    $p = [Diagnostics.Process]::Start($psi)
    $read = $p.StandardOutput.ReadToEndAsync()
    # EOF needs every holder of the pipe gone, not just the runner.
    if (-not $read.Wait(90000)) { throw "${Mode}: stdout pipe still open after 90 s" }
    $p.WaitForExit()
    $line = @($read.Result -split "`r?`n" | Where-Object { $_ -match '^runner started' })[0]
    if ($line -notmatch 'server (\d+) client (\d+)') { throw "${Mode}: no runner start line: $($read.Result)" }
    $r = @{ runDir = $runDir; session = $session; exit = $p.ExitCode; server = [int]$Matches[1]; client = [int]$Matches[2] }
    # The watchdog finishes its last step right after the pipe closes.
    $deadline = (Get-Date).AddSeconds(30)
    while (-not (Test-WatchdogDone $runDir)) {
        if ((Get-Date) -gt $deadline) { throw "${Mode}: watchdog never finished: $(Get-Content (Join-Path $runDir 'watchdog.log') -Raw)" }
        Start-Sleep -Milliseconds 250
    }
    $r
}
function Test-WatchdogDone([string]$RunDir) {
    try { [bool](Select-String -LiteralPath (Join-Path $RunDir 'watchdog.log') -Pattern ' done$' -Quiet -ErrorAction Stop) } catch { $false }
}
function Test-Alive([int]$Id) { [bool](Get-Process -Id $Id -ErrorAction SilentlyContinue) }
function Assert([bool]$Condition, [string]$Message) { if (-not $Condition) { throw $Message } }

$started = @()
try {
    $r = Invoke-FakeRun 'hung'
    $started += $r.server, $r.client
    Assert ($r.exit -ne 0) "hung: runner exit $($r.exit)"
    Assert (-not (Test-Alive $r.server)) 'hung: server left running'
    Assert (-not (Test-Alive $r.client)) 'hung: client left running'
    $summary = Get-Content -LiteralPath (Join-Path $r.runDir 'flow-summary.json') -Raw | ConvertFrom-Json
    Assert ($summary.verdict -eq 'FAIL' -and $summary.outcome -like 'Watchdog:*c0-lounge*') "hung: summary $($summary.outcome)"
    Assert (Test-Path -LiteralPath (Join-Path $r.runDir 'client0\openshim.log')) 'hung: client evidence not copied'
    Assert (-not (Test-Path -LiteralPath $r.session)) 'hung: session file left behind'

    $r = Invoke-FakeRun 'clean'
    $started += $r.server, $r.client
    Assert ($r.exit -eq 0) "clean: runner exit $($r.exit)"
    Assert (-not (Test-Alive $r.server)) 'clean: server left running'
    Assert (Test-Alive $r.client) 'clean: client stopped after a clean run'
    Assert ((Get-Content -LiteralPath (Join-Path $r.runDir 'flow-summary.json') -Raw | ConvertFrom-Json).verdict -eq 'PASS') 'clean: summary replaced'

    $r = Invoke-FakeRun 'crashed'
    $started += $r.server, $r.client
    Assert ($r.exit -ne 0) "crashed: runner exit $($r.exit)"
    Assert (-not (Test-Alive $r.server)) 'crashed: server left running'
    Assert (-not (Test-Alive $r.client)) 'crashed: client left running'
    $summary = Get-Content -LiteralPath (Join-Path $r.runDir 'flow-summary.json') -Raw | ConvertFrom-Json
    Assert ($summary.verdict -eq 'FAIL' -and $summary.outcome -like '*fake*') "crashed: summary $($summary.outcome)"
} finally {
    foreach ($id in $started) { Stop-Process -Id $id -Force -ErrorAction SilentlyContinue }
}
Remove-Item -LiteralPath $root -Recurse -Force -ErrorAction SilentlyContinue
Write-Host '[PASS] Hung runner torn down and killed; clean run keeps clients; crashed runner recorded; pipe closes in each.'
