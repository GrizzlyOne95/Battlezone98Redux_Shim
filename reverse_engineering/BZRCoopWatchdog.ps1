# Out-of-process teardown watchdog for one Run-BZRCoopMission.ps1 run.
#
# The mission runner tears its run down in a finally block, but any call that
# blocks before it (a PrintWindow or child script waiting on a hung client
# window, for example) leaves four clients, the coordinator and server.py up
# indefinitely. server.py and the coordinator also inherit the runner's
# stdout, so a caller reading it through a pipe (the retry matrix's
# Tee-Object) cannot finish until they exit, even after the runner is gone.
#
# Start-BZRCoopWatchdog starts Watch-BZRCoopRun without redirection
# (ShellExecute: no inherited handles). It polls the run folder:
#   failure   steps.jsonl timeout/client-exited, flow-steps.jsonl fail, the
#             runner's flow-failed marker, or the coordinator exiting before
#             teardown began;
#   teardown  the runner's flow-teardown marker.
# Either starts -FailureGraceSeconds for the runner to finish by itself. The
# grace expiring, or -HardTimeoutSeconds since start, makes the watchdog stop
# the clients (forced, evidence copied), coordinator, server and any other
# runner children, wait -KillGraceSeconds, then write a FAIL
# flow-summary.json if none exists and kill the runner (nonzero exit).
# Whenever the runner exits, the coordinator and server are stopped; after a
# failure, leftover clients are too, and a missing flow summary is written.
#
# Dot-sourced by the runner; defines functions only.

function Start-BZRCoopWatchdog {
    param([Parameter(Mandatory)][string]$RunDir, [string]$SessionFile = 'C:\BZRCoop\session.json',
          [int]$HardTimeoutSeconds = 0, [int]$FailureGraceSeconds = 300, [int]$KillGraceSeconds = 60, [int]$PollSeconds = 2)
    $ps51 = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
    $q = { param($s) "'" + ($s -replace "'", "''") + "'" }
    # The start time identifies this runner even if it has exited before the
    # watchdog is up, and guards every PID the watchdog stops against reuse.
    $command = ". $(& $q (Join-Path $PSScriptRoot 'BZRCoopWatchdog.ps1')); Watch-BZRCoopRun -ParentPid $PID " +
        "-ParentStartTicks $((Get-Process -Id $PID).StartTime.ToUniversalTime().Ticks) " +
        "-RunDir $(& $q $RunDir) -SessionFile $(& $q $SessionFile) -HardTimeoutSeconds $HardTimeoutSeconds " +
        "-FailureGraceSeconds $FailureGraceSeconds -KillGraceSeconds $KillGraceSeconds -PollSeconds $PollSeconds"
    # No -Redirect*/-NoNewWindow: Start-Process then uses ShellExecute, so the
    # watchdog holds none of this process's handles (a caller's stdout pipe).
    Start-Process -FilePath $ps51 -WindowStyle Hidden -PassThru -ArgumentList @(
        '-NoProfile', '-ExecutionPolicy', 'Bypass', '-Command', $command)
}

# Records the runner's long-lived children (server, launcher) for the watchdog.
function Set-BZRCoopWatchdogPid([string]$RunDir, [string]$Name, [int]$ProcessId) {
    $path = Join-Path $RunDir 'harness-pids.json'
    $pids = [ordered]@{}
    if (Test-Path -LiteralPath $path) {
        (Get-Content -LiteralPath $path -Raw | ConvertFrom-Json).PSObject.Properties | ForEach-Object { $pids[$_.Name] = $_.Value }
    }
    $pids[$Name] = $ProcessId
    $pids | ConvertTo-Json | Set-Content -LiteralPath $path
}

function Watch-BZRCoopRun {
    param([Parameter(Mandatory)][int]$ParentPid, [Parameter(Mandatory)][long]$ParentStartTicks, [Parameter(Mandatory)][string]$RunDir,
          [string]$SessionFile = 'C:\BZRCoop\session.json', [int]$HardTimeoutSeconds = 0,
          [int]$FailureGraceSeconds = 300, [int]$KillGraceSeconds = 60, [int]$PollSeconds = 2)
    $ErrorActionPreference = 'Stop'
    $log = Join-Path $RunDir 'watchdog.log'
    $clock = [Diagnostics.Stopwatch]::StartNew()
    $clients = @{}  # pid -> @{ index; dir; start }
    $parentStart = ([datetime]::new($ParentStartTicks, 'Utc')).ToLocalTime()

    function Write-Log([string]$Text) {
        # A reader holding the log must never stop the teardown.
        $line = "{0} {1}" -f (Get-Date).ToString('o'), $Text
        for ($i = 0; $i -lt 20; $i++) {
            try { [IO.File]::AppendAllText($log, $line + [Environment]::NewLine); return } catch { Start-Sleep -Milliseconds 50 }
        }
    }

    function Test-ParentAlive {
        $p = Get-Process -Id $ParentPid -ErrorAction SilentlyContinue
        [bool]($p -and $p.StartTime.ToUniversalTime().Ticks -eq $ParentStartTicks)
    }

    function Test-SameRun($Session) {
        $Session.runDir -and $Session.runDir.TrimEnd('\') -eq $RunDir.TrimEnd('\')
    }

    function Update-Clients {
        foreach ($path in @($SessionFile, (Join-Path $RunDir 'session-launch.json'))) {
            if (-not (Test-Path -LiteralPath $path)) { continue }
            $session = try { Get-Content -LiteralPath $path -Raw | ConvertFrom-Json } catch { $null }
            if (-not $session -or -not (Test-SameRun $session)) { continue }
            foreach ($c in @($session.clients)) {
                if (-not $c.pid -or $clients.ContainsKey([int]$c.pid)) { continue }
                $p = Get-Process -Id $c.pid -ErrorAction SilentlyContinue
                $clients[[int]$c.pid] = @{ index = $c.index; dir = $c.dir; start = if ($p) { $p.StartTime } else { $null } }
            }
        }
    }

    function Get-HarnessPids {
        $path = Join-Path $RunDir 'harness-pids.json'
        $pids = @{}
        if (Test-Path -LiteralPath $path) {
            try { (Get-Content -LiteralPath $path -Raw | ConvertFrom-Json).PSObject.Properties | ForEach-Object { $pids[$_.Name] = [int]$_.Value } } catch { }
        }
        $pids
    }

    function Find-Failure {
        foreach ($name in 'steps.jsonl', 'flow-steps.jsonl') {
            $path = Join-Path $RunDir $name
            if (-not (Test-Path -LiteralPath $path)) { continue }
            foreach ($line in [IO.File]::ReadAllLines($path)) {
                $r = try { $line | ConvertFrom-Json } catch { $null }
                if ($r -and $r.status -in 'timeout', 'client-exited', 'fail') { return "step '$($r.step)' $($r.status) ($name)" }
            }
        }
        $marker = Join-Path $RunDir 'flow-failed'
        if (Test-Path -LiteralPath $marker) { return "runner: $((Get-Content -LiteralPath $marker -Raw).Trim())" }
        $launcher = (Get-HarnessPids)['launcher']
        if ($launcher -and -not (Test-Path -LiteralPath (Join-Path $RunDir 'flow-teardown')) -and
            -not (Get-Process -Id $launcher -ErrorAction SilentlyContinue)) { return "coordinator $launcher exited during the flow" }
        $null
    }

    function Stop-Tree([int]$Root, [string]$Label) {
        if (-not $Root) { return }
        $table = @(Get-CimInstance Win32_Process | Select-Object ProcessId, ParentProcessId, CreationDate)
        # Started after the runner, so a recycled PID is never touched.
        $rootProc = $table | Where-Object { $_.ProcessId -eq $Root -and $_.CreationDate -ge $parentStart }
        if (-not $rootProc) { return }
        $order = New-Object System.Collections.ArrayList
        $queue = New-Object System.Collections.Queue
        $queue.Enqueue($rootProc)
        while ($queue.Count) {
            $p = $queue.Dequeue()
            [void]$order.Insert(0, $p)
            foreach ($c in @($table | Where-Object { $_.ParentProcessId -eq $p.ProcessId -and $_.CreationDate -ge $p.CreationDate -and $_.ProcessId -ne $PID })) {
                $queue.Enqueue($c)
            }
        }
        foreach ($p in $order) {
            $proc = Get-Process -Id $p.ProcessId -ErrorAction SilentlyContinue
            if (-not $proc) { continue }
            try { $proc.Kill(); [void]$proc.WaitForExit(10000); Write-Log "stopped $Label pid $($p.ProcessId)" } catch { }
        }
    }

    function Stop-Clients {
        foreach ($id in @($clients.Keys)) {
            $c = $clients[$id]
            $p = Get-Process -Id $id -ErrorAction SilentlyContinue
            if ($p -and (-not $c.start -or $p.StartTime -eq $c.start)) {
                try { $p.Kill(); [void]$p.WaitForExit(10000); Write-Log "stopped client $($c.index) pid $id" }
                catch { Write-Log "client $($c.index) pid ${id}: $_" }
            }
            # The evidence BZRCoopSession.ps1 -Action Stop copies; its copy wins.
            $dest = Join-Path $RunDir ("client{0}" -f $c.index)
            if ($c.dir -and -not (Test-Path -LiteralPath $dest)) {
                $null = New-Item -ItemType Directory -Path $dest -Force
                foreach ($f in 'BZLogger.txt', 'BZOgreLogfile.log', 'openshim.log', 'bzloader.log', 'BZChatLog.txt', 'openshim.ini', 'net.ini') {
                    Copy-Item -LiteralPath (Join-Path $c.dir $f) -Destination $dest -ErrorAction SilentlyContinue
                }
                $logs = Join-Path $c.dir 'logs'
                if (Test-Path -LiteralPath $logs) { Copy-Item -LiteralPath $logs -Destination $dest -Recurse -Force -ErrorAction SilentlyContinue }
            }
        }
        if ($clients.Count -and (Test-Path -LiteralPath $SessionFile)) {
            $session = try { Get-Content -LiteralPath $SessionFile -Raw | ConvertFrom-Json } catch { $null }
            if ($session -and (Test-SameRun $session)) { Remove-Item -LiteralPath $SessionFile -Force -ErrorAction SilentlyContinue }
        }
    }

    function Stop-Harness {
        $pids = Get-HarnessPids
        Stop-Tree $pids['launcher'] 'coordinator'
        Stop-Tree $pids['server'] 'server'
    }

    function Write-FailSummary([string]$Reason) {
        $path = Join-Path $RunDir 'flow-summary.json'
        if (Test-Path -LiteralPath $path) { return }
        [ordered]@{
            mission = ''; scenario = ''; started = ''; clients = @($clients.Values | ForEach-Object { $_.index } | Sort-Object)
            seconds = [math]::Round($clock.Elapsed.TotalSeconds, 1); verdict = 'FAIL'; outcome = "Watchdog: $Reason"
            steps = @(); checks = @([ordered]@{ check = 'run finished within the watchdog bounds'; status = 'fail'; detail = $Reason })
        } | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $path
        Write-Log "wrote FAIL flow-summary.json: $Reason"
    }

    function Complete-AfterRunner([string]$Reason) {
        Update-Clients
        Stop-Harness
        if (-not $Reason -and -not (Test-Path -LiteralPath (Join-Path $RunDir 'flow-summary.json'))) {
            $Reason = 'the runner exited without a flow summary'
        }
        # After a clean run, hung clients stay up for capture (Session Stop).
        if ($Reason) { Stop-Clients; Write-FailSummary $Reason }
        Write-Log 'done'
    }

    Write-Log "watching runner $ParentPid (hard $HardTimeoutSeconds s, grace $FailureGraceSeconds s, kill grace $KillGraceSeconds s)"
    $failure = $null
    $graceFrom = $null
    $reason = $null
    while (-not $reason) {
        Update-Clients
        if (-not (Test-ParentAlive)) {
            Write-Log 'runner exited'
            Complete-AfterRunner $failure
            return
        }
        if (-not $failure) {
            $failure = Find-Failure
            if ($failure) { Write-Log "failure: $failure" }
        }
        if ($null -eq $graceFrom -and ($failure -or (Test-Path -LiteralPath (Join-Path $RunDir 'flow-teardown')))) {
            $graceFrom = $clock.Elapsed.TotalSeconds
            Write-Log "runner has $FailureGraceSeconds s to finish"
        }
        if ($null -ne $graceFrom -and $clock.Elapsed.TotalSeconds - $graceFrom -ge $FailureGraceSeconds) {
            $reason = "runner did not finish within $FailureGraceSeconds s of " + $(if ($failure) { $failure } else { 'starting teardown' })
        } elseif ($HardTimeoutSeconds -gt 0 -and $clock.Elapsed.TotalSeconds -ge $HardTimeoutSeconds) {
            $reason = "hard timeout of $HardTimeoutSeconds s" + $(if ($failure) { " after $failure" } else { '' })
        } else {
            Start-Sleep -Seconds $PollSeconds
        }
    }

    Write-Log "tearing down: $reason"
    # Clients first: whatever the runner is blocked on usually involves them.
    Stop-Clients
    Stop-Harness
    # Other runner children (a lobby or session script), never the watchdog.
    foreach ($child in @(Get-CimInstance Win32_Process -Filter "ParentProcessId=$ParentPid" | Where-Object ProcessId -ne $PID)) {
        Stop-Tree $child.ProcessId 'runner child'
    }
    $deadline = $clock.Elapsed.TotalSeconds + $KillGraceSeconds
    while ((Test-ParentAlive) -and $clock.Elapsed.TotalSeconds -lt $deadline) { Start-Sleep -Seconds 1 }
    if (Test-ParentAlive) {
        Write-FailSummary $reason
        try { Stop-Process -Id $ParentPid -Force; Write-Log "killed runner $ParentPid" } catch { Write-Log "runner kill: $_" }
    }
    Complete-AfterRunner $reason
}
