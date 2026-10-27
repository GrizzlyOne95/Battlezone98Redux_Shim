# Stock bug pack (mpbugs map, Run-BZRMpBugs.ps1 -Case HostLeave): the host
# closes the game mid-mission and the guests are left with no authority.
#
# Investigation 7 (Docs\MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md) predicts from
# 1.5 that guests keep simulating and their mission never ends. Redux does not
# reproduce that with two clients (mpbugs-hl-7): within a second the guest logs
# "You have been elected host" and NotifyNowHost, every host-owned object is
# deleted, and the guest is put on the Game Over screen (dialog 11,
# RUN_WAS_QUIT). -Expect Stock checks that characterization, so a regression
# shows; -Expect Fixed (HostLeave on) asks that the guest is NOT put on Game Over
# and that the host's AI craft still exist on it. The Stock arm turns
# [Fixes] HostLeave off in the instance ini (Run-BZRMpBugs.ps1). With two or
# more guests (mpbugs-hl-3c-1) the host migrates instead: one guest is elected,
# nobody gets Game Over and the mission keeps running, so both arms check
# that. Host-owned objects are still deleted on every guest. The mission
# script is stock and does nothing about the departure, unlike CR's
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

$shimLogs, $shimMarks, $gameLogs, $gameMarks = @{}, @{}, @{}, @{}
foreach ($i in $C) {
    $shimLogs[$i] = Join-Path (Get-CRFlowClient $i).dir 'logs\openshim.log'
    $shimMarks[$i] = if (Test-Path -LiteralPath $shimLogs[$i]) { (Get-Item -LiteralPath $shimLogs[$i]).Length } else { 0 }
    $gameLogs[$i] = Join-Path (Get-CRFlowClient $i).dir 'logs\BZLogger.txt'
    $gameMarks[$i] = if (Test-Path -LiteralPath $gameLogs[$i]) { (Get-Item -LiteralPath $gameLogs[$i]).Length } else { 0 }
}
function Get-LogLines([hashtable]$Logs, [hashtable]$Marks, [int]$Client, [string]$Pattern) {
    if (-not (Test-Path -LiteralPath $Logs[$Client])) { return @() }
    $text = (Read-CRFlowShared $Logs[$Client] $Marks[$Client]).Text
    @([regex]::Matches($text, "(?m)^.*(?:$Pattern).*$") | ForEach-Object { $_.Value.Trim() })
}
function Get-MissionLeft([int]$Client) { Get-LogLines $shimLogs $shimMarks $Client '\[MISSION\] Mission left simulation' }
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

$electedBy = @{}
foreach ($series in @($samples)) {
    $g = [int]$series.client
    $states = @($series.samples | Where-Object { $_.state } | ForEach-Object { $_.state })
    $left = @($series.samples[-1].missionLeft)
    $first = $states | Select-Object -First 1
    $last = $states | Select-Object -Last 1
    $pre = $before["c$g"]
    $alive = [bool](Get-Process -Id (Get-CRFlowClient $g).pid -ErrorAction SilentlyContinue)
    Add-CRFlowCheck "guest c$g survives the host leaving" $alive

    $elected = @(Get-LogLines $gameLogs $gameMarks $g 'You have been elected host|NotifyNowHost')
    $gameOver = @(Get-LogLines $gameLogs $gameMarks $g 'escape/in game UI wrapper with dialog 11')
    $detail = [ordered]@{ missionLeft = $left; elected = $elected; gameOver = $gameOver
        answered = $states.Count; samples = @($series.samples).Count; timeFirst = $first.time; timeLast = $last.time
        deletedPlayers = $last.deletedPlayers; rosterBefore = $pre.roster; rosterAfter = $last.roster
        leaderDeparted = $last.leaderDeparted }
    $electedBy["c$g"] = $elected.Count
    if ($guests.Count -gt 1) {
        # Host migration: both arms expect the mission to carry on.
        $running = [bool]($first -and $last -and $last.time -gt $first.time)
        Add-CRFlowCheck "guest c$g stays in its mission under a new host (no Game Over, mission time advances)" `
            ([bool](-not $gameOver.Count -and -not $left.Count -and $running)) $detail
    } elseif ($Expect -eq 'Stock') {
        Add-CRFlowCheck "stock: guest c$g is elected host, then put on Game Over (dialog 11) and leaves its mission" `
            ([bool]($elected.Count -and $gameOver.Count -and $left.Count)) $detail
    } else {
        # HostLeave on: the survivor stays in the mission with no Game Over.
        Add-CRFlowCheck "fixed: guest c$g is not put on Game Over and keeps its mission after the host left" `
            ([bool](-not $gameOver.Count -and -not $left.Count)) $detail
    }
    if ($Expect -eq 'Fixed' -and $PerTeam -and $first -and $pre) {
        # The departed host's AI (teams 5 and 6) must still exist on the guest:
        # some of each side after the leave, compared with before it.
        $beforeCount = [int]$pre.craft5 + [int]$pre.craft6
        $afterCount = [int]$first.craft5 + [int]$first.craft6
        Add-CRFlowCheck "fixed: host-owned AI still exists on c$g after the leave (craft $beforeCount before, $afterCount just after, $([int]$last.craft5 + [int]$last.craft6) at the end)" `
            ([bool]($beforeCount -gt 0 -and $afterCount -gt 0 -and $last.craft5 + $last.craft6 -gt 0)) `
            ([ordered]@{ before = @{ craft5 = $pre.craft5; craft6 = $pre.craft6 }; firstAfter = @{ craft5 = $first.craft5; craft6 = $first.craft6 }; lastAfter = @{ craft5 = $last.craft5; craft6 = $last.craft6 } })
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
if ($guests.Count -gt 1) {
    $n = @($electedBy.Values | Where-Object { $_ }).Count
    Add-CRFlowCheck "exactly one guest is elected host ($n of $($guests.Count))" ($n -eq 1) $electedBy
}
