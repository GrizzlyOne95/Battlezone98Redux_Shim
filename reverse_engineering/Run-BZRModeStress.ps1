# Unattended mode-transition stress for release qualification
# (Docs/RELEASE_QUALIFICATION.md, "Mode-transition stress (unattended)").
#
# Launches ONE game with OPENSHIM_MODE_STRESS_PLAN set. The native driver
# (src/patches/mode_stress_driver.cpp) chains the plan's missions and Instant
# Action loads through the stock shell paths, returning to the main menu
# between steps, then exits through the main menu exit button. This script
# only watches: no SendInput, no focus changes, no clicks, so it runs with
# Windows locked. It records whether the workstation was locked (LogonUI.exe).
#
# Per step it reports PASS, FAIL (driver FAIL line or missing markers), FAIL-CRASH (new crash dump or
# the process died), FAIL-STALL (a main-loop stall of -StallFailSeconds or
# more) or FAIL-LOG. FAIL-LOG means a line in ANY log the run wrote (OpenShim,
# stock BZLogger, the Ogre log, EXU, first-chance crash log, mod logs) matched
# the error/exception/fail/assert/warning patterns below and is not in
# mode_stress_known_log_noise.txt. Each log's size and head are snapshotted
# before launch, only content the run added is scanned, and each line is
# attributed to the step whose [MODESTRESS] window holds its timestamp. Hits
# are de-duplicated with counts; allowlisted hits are printed separately with
# counts, so nothing is hidden.
#
# Safety (AGENT_TOOLING.md): takes <game>\bzr_livetest.lock (stops if it
# exists), then Assert-BZRSafeToLaunch, and only then rewrites ogre.cfg
# (windowed, -Renderer) behind the harness backup, restored in finally. One
# game, never force-killed: the overall timeout closes it with WM_CLOSE
# through Stop-BZRGame.
#
# mp_host steps host a one-player LAN game inside the same game process
# (OpenShim's in-process no-sign-in LAN host; no second client, no helper
# process). For a plan with mp_host the script also sets
# OPENSHIM_DISABLE_SYNC_JOIN_DEFAULT_ON=1, multi.ini [multi] syncJoin=0
# (stock refuses a one-player launch with Sync Join on: CanLaunchGame
# FUN_00573d00 lines 51-56) and openshim.ini [Network] NoAuthLan=1, and
# restores both files in finally (the driver also writes the LAN server
# selection into openshim.ini).
#
#   powershell -NoProfile -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRModeStress.ps1
#   ... -Renderer DX9 -PlanPath my.plan
#   ... -AnalyzeOnly <report dir>     # re-score a finished run (after editing the allowlist)
#
# Exit code 0 = every step PASS and nothing outside the steps failed;
# 1 = anything else.
param(
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$PlanPath = '',
    [ValidateSet('DX11', 'DX9')][string]$Renderer = 'DX11',
    # 0 = derive from the plan (load steps get 180 s each on top of their hold).
    [ValidateRange(0, 720)][int]$TimeoutMinutes = 0,
    # Passed through as OPENSHIM_FRAME_CAPTURE (frame numbers, AGENT_TOOLING.md);
    # new openshim_frame_*.png files are moved into the report.
    [string]$FrameCapture = '',
    [string]$NoisePath = '',
    [string]$ReportDir = '',
    [ValidateRange(5, 600)][int]$HeartbeatGapSeconds = 30,
    [ValidateRange(3, 600)][int]$StallFailSeconds = 30,
    [string]$AnalyzeOnly = ''
)
$ErrorActionPreference = 'Stop'
# No Set-StrictMode: BZRHarness.ps1 is dot-sourced into this scope (see its header).

if (-not $PlanPath) { $PlanPath = Join-Path $PSScriptRoot 'mode_stress_default.plan' }
if (-not $NoisePath) { $NoisePath = Join-Path $PSScriptRoot 'mode_stress_known_log_noise.txt' }

# --- Log scanning rules ------------------------------------------------------------
# Lines that are flagged. Case-insensitive. OpenShim [WARN]/[ERROR] levels count.
$script:FlagPattern = [regex]::new(
    '\berror|exception|\bfail|assert|\bfatal\b|access violation|first-chance|\bcrash|stack traceback|' +
    'attempt to (index|call|compare|perform|concatenate|arith)|\bunhandled\b|\babort|DXGI_ERROR|' +
    'device (removed|hung|reset)|-200527052[0-9]|out of memory|\[WARN\]|\[GPUWATCH\] stall|\bwarning\b',
    'IgnoreCase, Compiled')
# Handled as markers or stall episodes, not as log findings.
$script:SkipPattern = [regex]::new('\[MODESTRESS\]|\[SOAK\] (heartbeat|main-loop)', 'Compiled')
$script:TsIso = [regex]::new('(\d{4}-\d\d-\d\dT\d\d:\d\d:\d\d(?:\.\d+)?)Z', 'Compiled')
$script:TsLocal = [regex]::new('^\[?(?:[A-Z-]+\] )?(\d{4}-\d\d-\d\d \d\d:\d\d:\d\d(?:\.\d+)?)', 'Compiled')
$script:TsClock = [regex]::new('^(\d\d):(\d\d):(\d\d):', 'Compiled')

function Get-ModeStressPlan([string]$Path) {
    $steps = @(); $loops = 1
    $n = 0
    foreach ($raw in [IO.File]::ReadAllLines($Path)) {
        $n++
        $line = ($raw -replace '#.*$', '').Trim()
        if (-not $line) { continue }
        $tok = @($line -split '\s+')
        switch ($tok[0]) {
            'loop' { $loops = [int]$tok[1] }
            'shell' { $steps += [pscustomobject]@{ kind = 'shell'; arg = '-'; seconds = [int]$tok[1] } }
            { $_ -in @('mission', 'ia', 'mp_host') } {
                $steps += [pscustomobject]@{ kind = $tok[0]; arg = $tok[1]; seconds = [int]$tok[2] }
            }
            default { throw "Plan line ${n}: unknown step '$($tok[0])' (the driver would refuse it too)" }
        }
    }
    if (-not $steps.Count) { throw "Plan $Path has no steps" }
    $all = @()
    for ($p = 0; $p -lt $loops; $p++) { $all += $steps }
    return $all
}

function Read-NoiseRules([string]$Path) {
    $rules = @()
    if (-not (Test-Path -LiteralPath $Path)) { return , $rules }
    $n = 0
    foreach ($raw in [IO.File]::ReadAllLines($Path)) {
        $n++
        $line = $raw.Trim()
        if (-not $line -or $line.StartsWith('#')) { continue }
        $parts = $line -split ' :: ', 2
        if ($parts.Count -ne 2) { throw "${Path}:${n}: expected '<log glob> :: <regex>'" }
        $rules += [pscustomobject]@{
            id = "line $n"; log = $parts[0].Trim(); text = $parts[1]
            regex = [regex]::new($parts[1], 'IgnoreCase')
        }
    }
    return , $rules
}

# Readable while the game holds the file open for writing.
function Read-FileBytes([string]$Path, [long]$Offset, [int]$MaxBytes = [int]::MaxValue) {
    $fs = [IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite, Delete')
    try {
        $len = $fs.Length
        if ($Offset -ge $len) { return , [byte[]]@() }
        $count = [int][Math]::Min([long]$MaxBytes, $len - $Offset)
        $buf = New-Object byte[] $count
        [void]$fs.Seek($Offset, 'Begin')
        $read = 0
        while ($read -lt $count) {
            $r = $fs.Read($buf, $read, $count - $read)
            if ($r -le 0) { break }
            $read += $r
        }
        if ($read -lt $count) { $buf = $buf[0..($read - 1)] }
        return , $buf
    } finally { $fs.Dispose() }
}

function Get-LogCandidates([string]$Root) {
    $logs = Join-Path $Root 'logs'
    $files = @()
    if (Test-Path -LiteralPath $logs) {
        $files += @(Get-ChildItem -LiteralPath $logs -File | Where-Object {
            $_.Extension -in @('.log', '.txt') -and $_.Name -notmatch '\.prev\.' })
    }
    foreach ($n in @('BZLogger.txt', 'BZOgreLogfile.log')) {
        $p = Join-Path $Root $n
        if (Test-Path -LiteralPath $p) { $files += Get-Item -LiteralPath $p }
    }
    return , $files
}

function Get-LogSnapshot([string]$Root) {
    $snap = @{}
    foreach ($f in (Get-LogCandidates $Root)) {
        $head = Read-FileBytes $f.FullName 0 256
        $snap[$f.FullName] = [pscustomobject]@{ length = $f.Length; head = [Convert]::ToBase64String($head) }
    }
    return $snap
}

# Offset where this run's content starts: 0 for a file that is new or was
# rewritten (rotated at launch), else the length seen before launch.
function Get-NewContentStart([string]$Path, $Snap) {
    if (-not $Snap.ContainsKey($Path)) { return 0 }
    $old = $Snap[$Path]
    $len = (Get-Item -LiteralPath $Path).Length
    if ($len -lt $old.length) { return 0 }
    $headNow = [Convert]::ToBase64String((Read-FileBytes $Path 0 256))
    $oldHead = [Convert]::FromBase64String($old.head)
    $nowHead = [Convert]::FromBase64String($headNow)
    $n = [Math]::Min($oldHead.Length, $nowHead.Length)
    for ($i = 0; $i -lt $n; $i++) { if ($oldHead[$i] -ne $nowHead[$i]) { return 0 } }
    return $old.length
}

function Get-LogLabel([string]$Root, [string]$Path) {
    $rel = $Path.Substring($Root.TrimEnd('\').Length).TrimStart('\')
    return ($rel -replace '[\\/]', '_')
}

function ConvertTo-LineTime([string]$Line, [datetime]$RunStartLocal) {
    $m = $script:TsIso.Match($Line)
    if ($m.Success -and $m.Index -lt 4) {
        return [datetime]::Parse($m.Groups[1].Value, [Globalization.CultureInfo]::InvariantCulture,
            [Globalization.DateTimeStyles]'AdjustToUniversal, AssumeUniversal')
    }
    $m = $script:TsLocal.Match($Line)
    if ($m.Success) {
        $t = [datetime]::Parse($m.Groups[1].Value, [Globalization.CultureInfo]::InvariantCulture,
            [Globalization.DateTimeStyles]::AssumeLocal)
        return $t.ToUniversalTime()
    }
    $m = $script:TsClock.Match($Line)
    if ($m.Success) {
        $t = $RunStartLocal.Date.AddHours([int]$m.Groups[1].Value).AddMinutes([int]$m.Groups[2].Value).AddSeconds([int]$m.Groups[3].Value)
        if ($t -lt $RunStartLocal.AddHours(-1)) { $t = $t.AddDays(1) }  # ran past midnight
        return $t.ToUniversalTime()
    }
    return $null
}

function Get-NormalizedLine([string]$Line) {
    $s = $script:TsIso.Replace($Line, '')
    $s = $s -replace '^\[?(?:[A-Z-]+\] )?\d{4}-\d\d-\d\d \d\d:\d\d:\d\d(?:\.\d+)?\]?', ''
    $s = $s -replace '^\d\d:\d\d:\d\d:', ''
    $s = $s -replace '\[pid:\d+ tid:\d+\]', ''
    $s = $s -replace '0x[0-9A-Fa-f]+', '0x#'
    $s = $s -replace '\d+', '#'
    return $s.Trim()
}

# --- Run analysis ------------------------------------------------------------------
function Get-MarkerTimeline([string[]]$ShimLines) {
    $tl = [ordered]@{ planLoaded = $null; menu = $null; done = $null; exit = $null; shutdown = $null; fails = @();
        steps = @{}; heartbeats = @(); stalls = @(); listener = $false }
    $stepRx = [regex]'\[MODESTRESS\] step (\d+)/(\d+) (\S+) (\S+) (\S+)(.*)$'
    $openStall = $null
    foreach ($line in $ShimLines) {
        $tsm = $script:TsIso.Match($line)
        if (-not $tsm.Success) { continue }
        $t = [datetime]::Parse($tsm.Groups[1].Value, [Globalization.CultureInfo]::InvariantCulture,
            [Globalization.DateTimeStyles]'AdjustToUniversal, AssumeUniversal')
        if ($line -match '\[SOAK\] heartbeat') { $tl.heartbeats += $t; continue }
        if ($line -match '\[SOAK\] main-loop stalled ms=(\d+)') {
            $openStall = [pscustomobject]@{ start = $t.AddMilliseconds(-[double]$Matches[1]); ms = $null; resolved = $false }
            $tl.stalls += $openStall; continue
        }
        if ($line -match '\[SOAK\] main-loop resumed after ms=(\d+)') {
            if ($openStall) { $openStall.ms = [int]$Matches[1]; $openStall.resolved = $true; $openStall = $null }
            continue
        }
        if ($line -notmatch '\[MODESTRESS\]') { continue }
        $m = $stepRx.Match($line)
        if ($m.Success) {
            $i = [int]$m.Groups[1].Value
            if (-not $tl.steps.ContainsKey($i)) { $tl.steps[$i] = [ordered]@{ events = [ordered]@{}; detail = @() } }
            $what = $m.Groups[5].Value
            if (-not $tl.steps[$i].events.Contains($what)) { $tl.steps[$i].events[$what] = $t }
            continue
        }
        if ($line -match '\[MODESTRESS\] FAIL (.*)$') {
            $reason = $Matches[1]
            $si = if ($reason -match 'step=(\d+)/') { [int]$Matches[1] } else { 0 }
            $tl.fails += [pscustomobject]@{ time = $t; step = $si; reason = $reason }
        }
        elseif ($line -match '\[MODESTRESS\] plan loaded') { $tl.planLoaded = $t }
        elseif ($line -match '\[MODESTRESS\] main menu reached') { $tl.menu = $t }
        elseif ($line -match '\[MODESTRESS\] done') { $tl.done = $t }
        elseif ($line -match '\[MODESTRESS\] exit requested') { $tl.exit = $t }
        elseif ($line -match '\[MODESTRESS\] shutdown') { $tl.shutdown = $line }
        elseif ($line -match '\[MODESTRESS\] frame listener installed') { $tl.listener = $true }
    }
    return $tl
}

# Step index for a UTC time: the step whose begin is the latest at or before
# it; 0 = startup (before step 1); -1 = shutdown (after "done").
function Get-StepForTime($Timeline, [int]$StepCount, $Time) {
    if ($null -eq $Time) { return $null }
    if ($Timeline.done -and $Time -gt $Timeline.done) { return -1 }
    $best = 0
    for ($i = 1; $i -le $StepCount; $i++) {
        if (-not $Timeline.steps.ContainsKey($i)) { continue }
        $b = $Timeline.steps[$i].events['begin']
        if ($b -and $b -le $Time) { $best = $i }
    }
    return $best
}

function Invoke-LogScan([string]$Dir, $Segments, $Timeline, [int]$StepCount, $Rules, [datetime]$RunStartLocal) {
    $findings = @{}
    foreach ($seg in $Segments) {
        $lastTime = $null
        foreach ($line in [IO.File]::ReadAllLines((Join-Path $Dir $seg.file))) {
            $t = ConvertTo-LineTime $line $RunStartLocal
            if ($t) { $lastTime = $t }
            if ($script:SkipPattern.IsMatch($line) -or -not $script:FlagPattern.IsMatch($line)) { continue }
            $step = Get-StepForTime $Timeline $StepCount $lastTime
            if ($null -eq $step) { $step = 0 }
            $rule = $null
            foreach ($r in $Rules) {
                if ($seg.label -like $r.log -and $r.regex.IsMatch($line)) { $rule = $r; break }
            }
            $key = "$step|$($seg.label)|$(Get-NormalizedLine $line)"
            if (-not $findings.ContainsKey($key)) {
                $findings[$key] = [pscustomobject]@{
                    step = $step; log = $seg.label; count = 0; sample = $line.Trim()
                    allowlisted = [bool]$rule; rule = $(if ($rule) { $rule.id } else { $null })
                }
            }
            $findings[$key].count++
        }
    }
    return , @($findings.Values | Sort-Object step, log, sample)
}

function Get-StepName([int]$Index, $Steps) {
    if ($Index -eq 0) { return 'startup' }
    if ($Index -eq -1) { return 'shutdown' }
    $s = $Steps[$Index - 1]
    return "step $Index/$($Steps.Count) $($s.kind) $($s.arg)"
}

function Invoke-ModeStressAnalysis([string]$Dir) {
    $meta = Get-Content -LiteralPath (Join-Path $Dir 'run.json') -Raw | ConvertFrom-Json
    $steps = @(Get-ModeStressPlan (Join-Path $Dir 'plan.txt'))
    $rules = Read-NoiseRules $NoisePath
    $runStartLocal = [datetime]::Parse($meta.startedLocal, [Globalization.CultureInfo]::InvariantCulture)
    $segments = @($meta.segments | Where-Object { $_ })
    $shim = @($segments | Where-Object { $_.label -eq 'logs_openshim.log' })
    $shimLines = if ($shim.Count) { [IO.File]::ReadAllLines((Join-Path $Dir $shim[0].file)) } else { @() }
    $tl = Get-MarkerTimeline $shimLines
    $findings = Invoke-LogScan $Dir $segments $tl $steps.Count $rules $runStartLocal

    $crashes = @($meta.crashDumps | Where-Object { $_ } | ForEach-Object {
        $t = [datetime]::Parse($_.timeUtc, [Globalization.CultureInfo]::InvariantCulture,
            [Globalization.DateTimeStyles]'AdjustToUniversal, AssumeUniversal')
        [pscustomobject]@{ file = $_.file; step = (Get-StepForTime $tl $steps.Count $t) } })

    $gaps = @()
    for ($i = 1; $i -lt $tl.heartbeats.Count; $i++) {
        $g = ($tl.heartbeats[$i] - $tl.heartbeats[$i - 1]).TotalSeconds
        if ($g -gt $HeartbeatGapSeconds) {
            $gaps += [pscustomobject]@{ seconds = [Math]::Round($g, 1); step = (Get-StepForTime $tl $steps.Count $tl.heartbeats[$i - 1]) }
        }
    }
    $stalls = @($tl.stalls | ForEach-Object {
        [pscustomobject]@{ step = (Get-StepForTime $tl $steps.Count $_.start); ms = $_.ms; resolved = $_.resolved } })

    $results = @()
    for ($i = 1; $i -le $steps.Count; $i++) {
        $s = $steps[$i - 1]
        $ev = if ($tl.steps.ContainsKey($i)) { $tl.steps[$i].events } else { [ordered]@{} }
        $reasons = @()
        $status = 'PASS'
        $fail = @($tl.fails | Where-Object { $_.step -eq $i })
        if ($fail.Count) { $status = 'FAIL'; $reasons += @($fail | ForEach-Object { $_.reason }) }
        elseif (-not $ev.Contains('begin')) { $status = 'NOT-RUN'; $reasons += 'no begin marker' }
        elseif (-not $ev.Contains('end')) { $status = 'FAIL'; $reasons += 'no end marker' }
        elseif (-not $ev.Contains('ready')) { $status = 'FAIL'; $reasons += 'no ready marker' }
        $stepCrash = @($crashes | Where-Object { $_.step -eq $i })
        if ($stepCrash.Count) { $status = 'FAIL-CRASH'; $reasons += @($stepCrash | ForEach-Object { "crash dump $($_.file)" }) }
        $limitMs = $StallFailSeconds * 1000
        $bad = @($stalls | Where-Object { $_.step -eq $i -and (-not $_.resolved -or $_.ms -ge $limitMs) })
        if ($bad.Count -and $status -eq 'PASS') { $status = 'FAIL-STALL' }
        if ($bad.Count) { $reasons += @($bad | ForEach-Object { if ($_.resolved) { "main-loop stall $($_.ms) ms" } else { 'main-loop stall never resumed' } }) }
        $stepGaps = @($gaps | Where-Object { $_.step -eq $i })
        if ($stepGaps.Count) { $reasons += @($stepGaps | ForEach-Object { "heartbeat gap $($_.seconds) s" }) }
        $logHits = @($findings | Where-Object { $_.step -eq $i -and -not $_.allowlisted })
        if ($logHits.Count -and $status -eq 'PASS') { $status = 'FAIL-LOG' }
        if ($logHits.Count) { $reasons += "$($logHits.Count) non-allowlisted log line kind(s)" }
        $holdSeconds = $null
        if ($ev.Contains('ready') -and $ev.Contains('end')) { $holdSeconds = [Math]::Round(($ev['end'] - $ev['ready']).TotalSeconds, 1) }
        $loadSeconds = $null
        if ($ev.Contains('launched') -and $ev.Contains('ready')) { $loadSeconds = [Math]::Round(($ev['ready'] - $ev['launched']).TotalSeconds, 1) }
        $results += [pscustomobject]@{
            index = $i; kind = $s.kind; arg = $s.arg; seconds = $s.seconds; status = $status
            loadSeconds = $loadSeconds; readyToEndSeconds = $holdSeconds; earlyEnd = $ev.Contains('early-end')
            markers = @($ev.Keys | ForEach-Object { "$_@$($ev[$_].ToString('HH:mm:ss.fff'))Z" })
            reasons = $reasons
        }
    }

    $outside = @()
    foreach ($idx in @(0, -1)) {
        $name = Get-StepName $idx $steps
        $hits = @($findings | Where-Object { $_.step -eq $idx -and -not $_.allowlisted })
        $cr = @($crashes | Where-Object { $_.step -eq $idx })
        $outside += [pscustomobject]@{ phase = $name; nonAllowlisted = $hits.Count; crashes = $cr.Count }
    }
    $globalReasons = @()
    if (-not $tl.planLoaded) { $globalReasons += 'driver never logged "plan loaded" (env var not seen, plan rejected or rows did not bind)' }
    if (@($tl.fails | Where-Object { $_.step -eq 0 }).Count) { $globalReasons += @($tl.fails | Where-Object { $_.step -eq 0 } | ForEach-Object { "FAIL $($_.reason)" }) }
    if (-not $tl.done) { $globalReasons += 'no "[MODESTRESS] done"' }
    if ($meta.timedOut) { $globalReasons += 'overall timeout: closed with WM_CLOSE' }
    if ($meta.leftRunning) { $globalReasons += 'game ignored WM_CLOSE and was left running' }
    if ($tl.done -and -not $tl.exit) { $globalReasons += 'done but no exit request' }
    if ($meta.exitedUnexpectedly) { $globalReasons += "process exited without an exit request (code $($meta.exitCode))" }
    foreach ($o in $outside) {
        if ($o.nonAllowlisted) { $globalReasons += "$($o.nonAllowlisted) non-allowlisted log line kind(s) during $($o.phase)" }
        if ($o.crashes) { $globalReasons += "$($o.crashes) crash dump(s) during $($o.phase)" }
    }
    if (@($gaps | Where-Object { $_.step -le 0 }).Count) { $globalReasons += 'heartbeat gap outside the steps' }
    $verdict = if ($globalReasons.Count -eq 0 -and -not @($results | Where-Object { $_.status -ne 'PASS' }).Count) { 'PASS' } else { 'FAIL' }

    $report = [ordered]@{
        verdict = $verdict
        reasons = $globalReasons
        renderer = $meta.renderer
        plan = $meta.planPath
        startedLocal = $meta.startedLocal
        workstationLocked = $meta.locked
        exeSha256 = $meta.exeSha256
        shimSha256 = $meta.shimSha256
        allowlist = $NoisePath
        steps = $results
        logFindings = @($findings | ForEach-Object {
            [pscustomobject]@{ phase = (Get-StepName $_.step $steps); log = $_.log; count = $_.count
                allowlisted = $_.allowlisted; rule = $_.rule; sample = $_.sample } })
        crashDumps = $crashes
        heartbeatGaps = $gaps
        mainLoopStalls = $stalls
        logSegments = @($segments | ForEach-Object { [pscustomobject]@{ log = $_.label; fromOffset = $_.offset; bytes = $_.bytes } })
        frameCaptures = @($meta.frameCaptures | Where-Object { $_ })
    }
    $json = $report | ConvertTo-Json -Depth 8
    [IO.File]::WriteAllText((Join-Path $Dir 'mode_stress_report.json'), $json)

    Write-Host ''
    Write-Host "Mode-transition stress: $verdict  ($($meta.renderer), locked: $($meta.locked))"
    foreach ($r in $results) {
        $extra = if ($r.reasons.Count) { ' - ' + ($r.reasons -join '; ') } else { '' }
        Write-Host ('{0,-10} step {1}/{2} {3} {4}{5}' -f $r.status, $r.index, $results.Count, $r.kind, $r.arg, $extra)
    }
    foreach ($g in $globalReasons) { Write-Host "FAIL       run: $g" }
    $bad = @($findings | Where-Object { -not $_.allowlisted })
    if ($bad.Count) {
        Write-Host ''
        Write-Host 'Non-allowlisted log lines (phase, log, count, first sample):'
        foreach ($f in $bad) { Write-Host ('  [{0}] {1} x{2}: {3}' -f (Get-StepName $f.step $steps), $f.log, $f.count, $f.sample) }
    }
    $ok = @($findings | Where-Object { $_.allowlisted })
    if ($ok.Count) {
        Write-Host ''
        Write-Host 'Allowlisted log lines (known noise, still counted):'
        $grouped = $ok | Group-Object log, rule
        foreach ($g in $grouped) {
            $total = ($g.Group | Measure-Object count -Sum).Sum
            Write-Host ('  {0} x{1} ({2}): {3}' -f $g.Group[0].log, $total, $g.Group[0].rule, $g.Group[0].sample)
        }
    }
    Write-Host ''
    Write-Host "Report: $(Join-Path $Dir 'mode_stress_report.json')"
    return $verdict
}

if ($AnalyzeOnly) {
    $verdict = Invoke-ModeStressAnalysis (Resolve-Path -LiteralPath $AnalyzeOnly).Path
    if ($verdict -eq 'PASS') { exit 0 } else { exit 1 }
}

# Sets [Section] Key = Value in an INI file, keeping every other line; adds
# the key (and the section) when missing.
function Set-IniValue([string]$Path, [string]$Section, [string]$Key, [string]$Value) {
    $lines = [Collections.Generic.List[string]]::new()
    if (Test-Path -LiteralPath $Path) { $lines.AddRange([string[]][IO.File]::ReadAllLines($Path)) }
    $inSection = $false; $sectionEnd = -1; $done = $false
    for ($i = 0; $i -lt $lines.Count; $i++) {
        $t = $lines[$i].Trim()
        if ($t -match '^\[(.+)\]$') {
            if ($inSection) { $sectionEnd = $i; break }
            $inSection = $Matches[1].Trim() -ieq $Section
            continue
        }
        if ($inSection -and $t -match '^([^=;#]+?)\s*=' -and $Matches[1].Trim() -ieq $Key) {
            $lines[$i] = "$Key = $Value"; $done = $true; break
        }
    }
    if (-not $done) {
        if ($inSection) {
            if ($sectionEnd -lt 0) { $sectionEnd = $lines.Count }
            $lines.Insert($sectionEnd, "$Key = $Value")
        } else {
            $lines.Add("[$Section]"); $lines.Add("$Key = $Value")
        }
    }
    [IO.File]::WriteAllLines($Path, $lines)
}

# --- Live run ------------------------------------------------------------------------
$gameExe = Join-Path $GameRoot 'battlezone98redux.exe'
if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
$PlanPath = (Resolve-Path -LiteralPath $PlanPath).Path
$steps = @(Get-ModeStressPlan $PlanPath)
[void](Read-NoiseRules $NoisePath)  # a malformed allowlist fails before launch
if ($TimeoutMinutes -eq 0) {
    $sec = 300
    foreach ($s in $steps) { $sec += $s.seconds + $(if ($s.kind -in @('mission', 'ia', 'mp_host')) { 180 } else { 30 }) }
    $TimeoutMinutes = [int][Math]::Ceiling($sec / 60.0)
}
$stamp = Get-Date -Format 'yyyyMMdd_HHmmss'
if (-not $ReportDir) { $ReportDir = Join-Path $GameRoot "openshim_test_results\modestress_${Renderer}_$stamp" }
New-Item -ItemType Directory -Path (Join-Path $ReportDir 'logs') -Force | Out-Null
Copy-Item -LiteralPath $PlanPath -Destination (Join-Path $ReportDir 'plan.txt') -Force

if (@(Get-Process -Name 'battlezone98redux' -ErrorAction SilentlyContinue).Count -gt 0) {
    throw 'Refusing to start while another Battlezone process is running'
}
$lock = Join-Path $GameRoot 'bzr_livetest.lock'
if (Test-Path -LiteralPath $lock) { throw "Live-test lock held: $(Get-Content -LiteralPath $lock -Raw)" }
[IO.File]::WriteAllText($lock, "Run-BZRModeStress.ps1 pid=$PID $(Get-Date -Format o)")

$meta = [ordered]@{
    planPath = $PlanPath; renderer = $Renderer; startedLocal = $null; locked = 'unknown'
    exeSha256 = $null; shimSha256 = $null; timedOut = $false; leftRunning = $false
    exitedUnexpectedly = $false; exitCode = $null; segments = @(); crashDumps = @(); frameCaptures = @()
}
$ogreTouched = $false
$process = $null
$hasMpHost = @($steps | Where-Object { $_.kind -eq 'mp_host' }).Count -gt 0
$iniBackups = @()
try {
    # Harness helpers (launch mutex, foreground watchdog). BZR_FORCE_WINDOWED stays
    # unset here so dot-sourcing does not touch ogre.cfg before the safety check.
    $env:BZR_FORCE_WINDOWED = $null
    . "$PSScriptRoot\BZRHarness.ps1"
    $env:OPENSHIM_NEVER_ACTIVATE = '1'
    Assert-BZRSafeToLaunch

    # ogre.cfg: windowed + renderer, behind the harness backup name so a crash of
    # this script is recovered by the next harness run (Restore-BZROrphanedOgreConfig).
    $ogre = Join-Path $GameRoot 'ogre.cfg'
    Copy-Item -LiteralPath $ogre -Destination (Join-Path $GameRoot $script:BZROgreBackupName) -Force
    $ogreTouched = $true
    [void](Set-BZROgreWindowed -GameRoot $GameRoot)
    $renderSystem = if ($Renderer -eq 'DX9') { 'Direct3D9 Rendering Subsystem' } else { 'Direct3D11 Rendering Subsystem' }
    $cfg = [IO.File]::ReadAllText($ogre) -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
    [IO.File]::WriteAllText($ogre, $cfg)

    if ($hasMpHost) {
        foreach ($n in @('multi.ini', 'openshim.ini')) {
            $src = Join-Path $GameRoot $n
            $bak = "$src.modestress-bak"
            if (Test-Path -LiteralPath $bak) { throw "$bak exists (an earlier run did not restore it); restore it by hand first" }
            Copy-Item -LiteralPath $src -Destination $bak
            $iniBackups += [pscustomobject]@{ file = $src; backup = $bak }
        }
        Set-IniValue (Join-Path $GameRoot 'multi.ini') 'multi' 'syncJoin' '0'
        Set-IniValue (Join-Path $GameRoot 'openshim.ini') 'Network' 'NoAuthLan' '1'
        $env:OPENSHIM_DISABLE_SYNC_JOIN_DEFAULT_ON = '1'
    }

    $env:OPENSHIM_MODE_STRESS_PLAN = $PlanPath
    $env:OPENSHIM_SOAK_TELEMETRY = '1'
    if ($FrameCapture) { $env:OPENSHIM_FRAME_CAPTURE = $FrameCapture } else { $env:OPENSHIM_FRAME_CAPTURE = $null }

    $meta.exeSha256 = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
    $dll = Join-Path $GameRoot 'plugins\openshim.dll'
    if (Test-Path -LiteralPath $dll) { $meta.shimSha256 = (Get-FileHash -LiteralPath $dll -Algorithm SHA256).Hash }

    $snapshot = Get-LogSnapshot $GameRoot
    $dumpRx = '^openshim_crash_.*\.dmp$'
    $dumpDirs = @((Join-Path $GameRoot 'logs'), $GameRoot)
    $dumpsBefore = @{}
    foreach ($d in $dumpDirs) {
        if (Test-Path -LiteralPath $d) {
            Get-ChildItem -LiteralPath $d -File | Where-Object { $_.Name -match $dumpRx } | ForEach-Object { $dumpsBefore[$_.FullName] = $true }
        }
    }
    $startUtc = (Get-Date).ToUniversalTime()
    $meta.startedLocal = (Get-Date).ToString('o')

    Write-Host "Launching $Renderer, $($steps.Count) steps, timeout $TimeoutMinutes min, report $ReportDir"
    $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList '/nointro' -WorkingDirectory $GameRoot -PassThru
    $deadline = (Get-Date).AddMinutes($TimeoutMinutes)
    $shimLog = Join-Path $GameRoot 'logs\openshim.log'
    $lockedSamples = 0; $samples = 0
    $sawExit = $false; $sawFail = $false; $failSince = $null; $exitSince = $null
    # Tail openshim.log from where this run's content starts (the game rotates it
    # at launch, so that start moves to 0 once the new file appears).
    $tailBase = -1; $tailPos = 0; $carry = ''
    while (-not $process.HasExited) {
        Start-Sleep -Seconds 2
        $samples++
        if (@(Get-Process -Name 'LogonUI' -ErrorAction SilentlyContinue).Count) { $lockedSamples++ }
        if (Test-Path -LiteralPath $shimLog) {
            $base = Get-NewContentStart $shimLog $snapshot
            if ($base -ne $tailBase) { $tailBase = $base; $tailPos = $base; $carry = '' }
            $bytes = Read-FileBytes $shimLog $tailPos
            $tailPos += $bytes.Length
            $chunk = $carry + [Text.Encoding]::UTF8.GetString($bytes)
            $cut = $chunk.LastIndexOf("`n")
            if ($cut -ge 0) { $carry = $chunk.Substring($cut + 1); $chunk = $chunk.Substring(0, $cut) } else { $carry = $chunk; $chunk = '' }
            foreach ($line in @($chunk -split "`n" | Where-Object { $_ -match '\[MODESTRESS\]' })) {
                Write-Host ($line.Trim() -replace '^.*\[MODESTRESS\]', '[MODESTRESS]')
                if (-not $sawExit -and $line -match '\[MODESTRESS\] exit requested') { $sawExit = $true; $exitSince = Get-Date }
                if (-not $sawFail -and $line -match '\[MODESTRESS\] FAIL') { $sawFail = $true; $failSince = Get-Date }
            }
        }
        # A driver FAIL stops the plan; give the logs a few seconds, then close.
        if ($sawFail -and ((Get-Date) - $failSince).TotalSeconds -ge 10) { break }
        # The exit button normally ends the process within seconds.
        if ($sawExit -and ((Get-Date) - $exitSince).TotalSeconds -ge 120) { break }
        if ((Get-Date) -ge $deadline) { $meta.timedOut = $true; break }
    }
    $meta.locked = if ($samples -eq 0) { 'unknown' } elseif ($lockedSamples -eq $samples) { 'all' } elseif ($lockedSamples) { 'partly' } else { 'never' }
    if (-not $process.HasExited) {
        Stop-BZRGame -Id $process.Id -ErrorAction Continue
        $process.Refresh()
        if (-not $process.HasExited) { $meta.leftRunning = $true }
    } elseif (-not $sawExit) {
        $meta.exitedUnexpectedly = -not $sawFail
        try { $meta.exitCode = $process.ExitCode } catch { }
    }

    # This run's new log content, one file per log.
    foreach ($f in (Get-LogCandidates $GameRoot)) {
        $start = Get-NewContentStart $f.FullName $snapshot
        $bytes = Read-FileBytes $f.FullName $start
        if (-not $bytes.Length) { continue }
        $label = Get-LogLabel $GameRoot $f.FullName
        [IO.File]::WriteAllBytes((Join-Path $ReportDir "logs\$label"), $bytes)
        $meta.segments += [pscustomobject]@{ label = $label; source = $f.FullName; offset = $start; bytes = $bytes.Length; file = "logs\$label" }
    }
    foreach ($d in $dumpDirs) {
        if (-not (Test-Path -LiteralPath $d)) { continue }
        foreach ($f in @(Get-ChildItem -LiteralPath $d -File | Where-Object { $_.Name -match $dumpRx -and -not $dumpsBefore.ContainsKey($_.FullName) })) {
            $meta.crashDumps += [pscustomobject]@{ file = $f.FullName; timeUtc = $f.LastWriteTimeUtc.ToString('o') }
        }
    }
    if ($FrameCapture) {
        foreach ($f in @(Get-ChildItem -LiteralPath $GameRoot -File -Filter 'openshim_frame_*.png' |
                Where-Object { $_.LastWriteTimeUtc -ge $startUtc })) {
            Move-Item -LiteralPath $f.FullName -Destination (Join-Path $ReportDir $f.Name) -Force
            $meta.frameCaptures += $f.Name
        }
    }
} finally {
    if ($process -and -not $process.HasExited) {
        Stop-BZRGame -Id $process.Id -ErrorAction Continue
    }
    if ($ogreTouched) { [void](Restore-BZROrphanedOgreConfig -GameRoot $GameRoot) }
    foreach ($b in $iniBackups) {
        Copy-Item -LiteralPath $b.backup -Destination $b.file -Force
        Remove-Item -LiteralPath $b.backup -Force
    }
    foreach ($v in @('OPENSHIM_MODE_STRESS_PLAN', 'OPENSHIM_FRAME_CAPTURE', 'OPENSHIM_DISABLE_SYNC_JOIN_DEFAULT_ON')) { Set-Item -Path "env:$v" -Value $null -ErrorAction SilentlyContinue }
    Remove-Item -LiteralPath $lock -Force -ErrorAction SilentlyContinue
    [IO.File]::WriteAllText((Join-Path $ReportDir 'run.json'), ($meta | ConvertTo-Json -Depth 6))
}

$verdict = Invoke-ModeStressAnalysis $ReportDir
if ($verdict -eq 'PASS') { exit 0 } else { exit 1 }
