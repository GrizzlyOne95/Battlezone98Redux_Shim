# Stock bug pack (mpbugs map, Run-BZRMpBugs.ps1 -Case HostLeave): the host
# closes the game mid-mission and the guests are left with no authority.
#
# There is no host migration (Docs\MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md,
# investigation 7): guests keep simulating and their mission never ends. The
# mission script is stock and does nothing about the departure, unlike CR's
# leader-departure FailMission (scenarios\host-leaves.ps1). Before leaving, the
# host spawns two AI armies it owns, so the samples also show what guests keep
# of objects whose owner is gone: counts, health and movement.
#
# The host is closed the way a player closes the game (WM_CLOSE through
# Stop-BZRGame -NoForce). Guests must survive in every arm.
param([ValidateSet('Stock','Fixed')][string]$Expect = 'Stock',
      [int]$HostClient = 0,
      # AI tanks per side, owned by the host.
      [ValidateRange(0,16)][int]$PerTeam = 4,
      # Seconds of combat before the host leaves.
      [int]$PlaySeconds = 15,
      # Seconds of guest samples after the host has gone.
      [int]$WatchSeconds = 30)

$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$script:CRFlowSkipParity = $true # Streams differ once the host has gone.
$samplePath = Join-Path $script:CRFlowRun.runDir 'hostleave-samples.jsonl'

$shimLogs, $shimMarks = @{}, @{}
foreach ($i in $C) {
    $shimLogs[$i] = Join-Path (Get-CRFlowClient $i).dir 'logs\openshim.log'
    $shimMarks[$i] = if (Test-Path -LiteralPath $shimLogs[$i]) { (Get-Item -LiteralPath $shimLogs[$i]).Length } else { 0 }
}
function Get-MissionLeft([int]$Client) {
    if (-not (Test-Path -LiteralPath $shimLogs[$Client])) { return @() }
    $text = (Read-CRFlowShared $shimLogs[$Client] $shimMarks[$Client]).Text
    @([regex]::Matches($text, '(?m)^.*\[MISSION\] Mission left simulation.*$') | ForEach-Object { $_.Value.Trim() })
}
function Get-BugState([int]$Client, [string]$Phase) {
    $s = $null
    try {
        $r = Invoke-CRFlow $Client 'return BugState()' -TimeoutSeconds 3 -AllowError
        if ($r.Ok) { $s = $r.Value }
    } catch { if ($_.Exception.Message -match 'exited unexpectedly') { throw } }
    $record = [ordered]@{ at = (Get-Date).ToUniversalTime().ToString('o'); phase = $Phase; client = $Client
        missionLeft = @(Get-MissionLeft $Client).Count; state = $s }
    ($record | ConvertTo-Json -Compress -Depth 6) | Add-Content -LiteralPath $samplePath
    $s
}

$before = Invoke-CRFlowStep "host spawns $PerTeam AI tanks per side; combat on every peer" {
    if ($PerTeam) { Invoke-CRFlow $H "return BugSpawnArmies($PerTeam)" | Out-Null }
    Start-Sleep -Seconds $PlaySeconds
    $out = @{}
    foreach ($i in $C) {
        $s = Get-BugState $i 'before'
        if (-not $s) { throw "c$i does not answer BugState" }
        if (@(Get-MissionLeft $i).Count) { throw "c$i mission already over" }
        if ($i -ne $H -and $PerTeam -and $s.localCraft) { throw "guest c$i owns $($s.localCraft) of the host's AI craft" }
        $out["c$i"] = $s
    }
    $out
}

$hostPid = (Get-CRFlowClient $H).pid
$script:CRFlowExpectedExit += $hostPid
Invoke-CRFlowStep 'host closes the game' {
    Stop-BZRGame -Id $hostPid -NoForce -TimeoutSeconds 30
    if (Get-Process -Id $hostPid -ErrorAction SilentlyContinue) { throw "host pid $hostPid still running after WM_CLOSE" }
    @{ hostPid = $hostPid }
}

$samples = Invoke-CRFlowStep "guests sampled for ${WatchSeconds}s without a host" {
    $series = @{}
    foreach ($g in $guests) { $series[$g] = New-Object System.Collections.ArrayList }
    $clock = [Diagnostics.Stopwatch]::StartNew()
    while ($clock.Elapsed.TotalSeconds -lt $WatchSeconds) {
        foreach ($g in $guests) {
            $s = Get-BugState $g 'after'
            [void]$series[$g].Add([ordered]@{ s = [math]::Round($clock.Elapsed.TotalSeconds, 1); state = $s; missionLeft = @(Get-MissionLeft $g) })
        }
        Start-Sleep -Seconds 3
    }
    foreach ($g in $guests) { [ordered]@{ client = $g; samples = @($series[$g]) } }
}

foreach ($series in @($samples)) {
    $g = [int]$series.client
    $states = @($series.samples | Where-Object { $_.state } | ForEach-Object { $_.state })
    $left = @($series.samples[-1].missionLeft)
    $first = $states | Select-Object -First 1
    $last = $states | Select-Object -Last 1
    $pre = $before["c$g"]
    $alive = [bool](Get-Process -Id (Get-CRFlowClient $g).pid -ErrorAction SilentlyContinue)
    Add-CRFlowCheck "guest c$g survives the host leaving" $alive

    $running = -not $left.Count -and $first -and $last -and $last.time -gt $first.time + 10
    $detail = [ordered]@{ missionLeft = $left; answered = $states.Count; samples = @($series.samples).Count
        timeFirst = $first.time; timeLast = $last.time
        deletedPlayers = $last.deletedPlayers; rosterBefore = $pre.roster; rosterAfter = $last.roster
        leaderDeparted = $last.leaderDeparted }
    if ($Expect -eq 'Stock') {
        Add-CRFlowCheck "stock defect reproduces: guest c$g keeps simulating with no host for ${WatchSeconds}s" $running $detail
    } else {
        Add-CRFlowCheck "guest c$g leaves its mission after the host is gone" ([bool]$left.Count) $detail
    }
    if ($PerTeam -and $first -and $last) {
        # Observations, not verdicts: what happens to the departed host's objects.
        $ai = [ordered]@{
            before = @{ craft5 = $pre.craft5; craft6 = $pre.craft6; health = $pre.health; objects = $pre.objects }
            firstAfter = @{ craft5 = $first.craft5; craft6 = $first.craft6; health = $first.health; posSum = $first.posSum; objects = $first.objects; localCraft = $first.localCraft }
            lastAfter = @{ craft5 = $last.craft5; craft6 = $last.craft6; health = $last.health; posSum = $last.posSum; objects = $last.objects; localCraft = $last.localCraft }
            moved = [math]::Abs($last.posSum - $first.posSum) -gt 1
            damaged = $last.health -lt $first.health
        }
        Add-CRFlowCheck "observed on c${g}: host-owned AI after the host left (moved=$($ai.moved) damaged=$($ai.damaged) craft $($last.craft5)/$($last.craft6))" $true $ai
    }
}
