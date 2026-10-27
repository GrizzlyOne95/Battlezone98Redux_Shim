# Stock bug pack (mpbugs map, Run-BZRMpBugs.ps1 -Case MissionEnd): a mission
# result reaches only the peer whose script calls it.
#
# AiMission::End is local and sends nothing (Docs\MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md,
# investigation 8), so a script that calls SucceedMission on the host only, as
# stock multiplayer scripts do, ends the host's mission and leaves every guest
# simulating. -Caller all is the control arm: every peer calls it, which proves
# the detector sees a guest's mission end at all.
#
# A peer's mission end is OpenShim's "[MISSION] Mission left simulation" line
# in that client's openshim.log (the SetRunning seam), backed by the probe: a
# peer whose mission ended stops answering, one still in it keeps its clock moving.
param([ValidateSet('host','all')][string]$Caller = 'host',
      [ValidateSet('Stock','Fixed')][string]$Expect = 'Stock',
      [ValidateSet('succeed','fail')][string]$Result = 'succeed',
      [int]$HostClient = 0,
      # Seconds of mission play before the result.
      [int]$PlaySeconds = 10,
      # SucceedMission/FailMission delay (seconds of mission time).
      [int]$Delay = 3,
      # Seconds to watch every peer after the call.
      [int]$WatchSeconds = 40)

$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$script:CRFlowSkipParity = $true # The streams differ by design in the host-only arm.

$shimLogs, $shimMarks = @{}, @{}
foreach ($i in $C) {
    $shimLogs[$i] = Join-Path (Get-CRFlowClient $i).dir 'logs\openshim.log'
    $shimMarks[$i] = if (Test-Path -LiteralPath $shimLogs[$i]) { (Get-Item -LiteralPath $shimLogs[$i]).Length } else { 0 }
}
# "[MISSION] Mission left simulation" lines written since the mark.
function Get-MissionLeft([int]$Client) {
    if (-not (Test-Path -LiteralPath $shimLogs[$Client])) { return @() }
    $text = (Read-CRFlowShared $shimLogs[$Client] $shimMarks[$Client]).Text
    @([regex]::Matches($text, '(?m)^.*\[MISSION\] Mission left simulation.*$') | ForEach-Object { $_.Value.Trim() })
}
function Get-BugState([int]$Client) {
    try {
        $r = Invoke-CRFlow $Client 'return BugState()' -TimeoutSeconds 3 -AllowError
        if ($r.Ok) { $r.Value } else { $null }
    } catch { if ($_.Exception.Message -match 'exited unexpectedly') { throw }; $null }
}

Invoke-CRFlowStep 'mission running on every peer' {
    Start-Sleep -Seconds $PlaySeconds
    foreach ($i in $C) {
        $s = Get-BugState $i
        if (-not $s) { throw "c$i does not answer BugState" }
        if ($s.ended -or @(Get-MissionLeft $i).Count) { throw "c$i mission already over" }
        @{ client = $i; time = $s.time; roster = $s.roster }
    }
}

$callers = if ($Caller -eq 'all') { $C } else { @($H) }
Invoke-CRFlowStep "$Result called on $Caller ($($callers -join ','))" {
    foreach ($i in $callers) { @{ client = $i; ended = (Invoke-CRFlow $i "return BugEnd('$Result', $Delay)") } }
}

$watch = Invoke-CRFlowStep "watch every peer for ${WatchSeconds}s" {
    $seen = @{}
    foreach ($i in $C) { $seen[$i] = [ordered]@{ client = $i; leftAt = $null; left = @(); first = $null; last = $null; answered = 0; silent = 0 } }
    $clock = [Diagnostics.Stopwatch]::StartNew()
    while ($clock.Elapsed.TotalSeconds -lt $WatchSeconds) {
        foreach ($i in $C) {
            $w = $seen[$i]
            if (-not $w.leftAt) {
                $left = @(Get-MissionLeft $i)
                if ($left.Count) { $w.leftAt = [math]::Round($clock.Elapsed.TotalSeconds, 1); $w.left = $left }
            }
            if ($w.leftAt) { continue }
            $s = Get-BugState $i
            if ($s) {
                $w.answered++
                if (-not $w.first) { $w.first = $s }
                $w.last = $s
            } else { $w.silent++ }
        }
        Start-Sleep -Seconds 2
    }
    foreach ($i in $C) { $seen[$i].left = @(Get-MissionLeft $i) }
    $C | ForEach-Object { $seen[$_] }
}

$byClient = @{}
foreach ($w in @($watch)) { $byClient[[int]$w.client] = $w }
function Test-StillRunning($w) {
    # Still in the mission: no transition line, and its clock kept moving.
    -not $w.left.Count -and $w.first -and $w.last -and $w.last.time -gt $w.first.time + 5
}

foreach ($i in $callers) {
    $w = $byClient[$i]
    Add-CRFlowCheck "c$i (called $Result) leaves its mission" ([bool]$w.left.Count) $w
}
if ($Caller -eq 'all') { return }

foreach ($g in $guests) {
    $w = $byClient[$g]
    $running = Test-StillRunning $w
    $detail = [ordered]@{ left = $w.left; answered = $w.answered; silent = $w.silent
        firstTime = $w.first.time; lastTime = $w.last.time; lastRoster = $w.last.roster; lastObjects = $w.last.objects }
    if ($Expect -eq 'Stock') {
        Add-CRFlowCheck "stock defect reproduces: guest c$g is still in its mission ${WatchSeconds}s after the host's ended" $running $detail
    } else {
        Add-CRFlowCheck "guest c$g leaves its mission after the host's $Result" ([bool]$w.left.Count) $detail
    }
}
