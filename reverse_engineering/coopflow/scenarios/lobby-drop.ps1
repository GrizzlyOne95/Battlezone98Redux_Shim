# OpenShim PR #615 ([Network] LobbyDropKeepsMatch): one client's lobby
# websocket is reset mid-mission while its P2P (relay) traffic keeps flowing.
# Needs a DedicatedServer copy patched by coopflow\lobbydrop_test_server.py:
# POST /test/drop-ws aborts the session's TCP transport, and -Silent also
# leaves the session registered, as when the server never saw the drop (the
# DedicatedServer #16 takeover path). Run via Run-BZRLobbyDrop.ps1.
#
#   -Mode Keep      both clients must stay in the mission, with [LOBBYDROP] logs
#   -Mode TrueLoss  the subject's relay goes dark first, so P2P is silent too;
#                   the subject must quit exactly as stock
param([ValidateSet('Keep','TrueLoss')][string]$Mode = 'Keep',
      [string]$Expect = '',
      [int]$Subject = 1,
      [switch]$Silent,
      [int]$PlaySeconds = 10,
      [int]$WatchSeconds = 40,
      [int]$DarkSeconds = 10)

$C = @(Get-CRFlowClientIndices)
$others = @($C | Where-Object { $_ -ne $Subject })
$script:CRFlowSkipParity = $true
$samplePath = Join-Path $script:CRFlowRun.runDir 'lobbydrop-samples.jsonl'

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
function Get-State([int]$Client, [string]$Phase) {
    $s = $null
    try {
        $r = Invoke-CRFlow $Client 'return BugState()' -TimeoutSeconds 3 -AllowError
        if ($r.Ok) { $s = $r.Value }
    } catch { if ($_.Exception.Message -match 'exited unexpectedly') { throw } }
    $record = [ordered]@{ at = (Get-Date).ToUniversalTime().ToString('o'); phase = $Phase; client = $Client; state = $s }
    ($record | ConvertTo-Json -Compress -Depth 6) | Add-Content -LiteralPath $samplePath
    $s
}

$subjectAuth = @((Get-CRFlowSession).clients | Where-Object { $_.index -eq $Subject })[0].authenticatedAs
$subjectId = if ($subjectAuth) { ($subjectAuth -split ":")[0] } else { "BZRCoop$($Subject + 1)" }

$before = Invoke-CRFlowStep "play ${PlaySeconds}s; every peer answers" {
    Start-Sleep -Seconds $PlaySeconds
    $out = @{}
    foreach ($i in $C) {
        $s = Get-State $i 'before'
        if (-not $s) { throw "c$i does not answer BugState" }
        $out["c$i"] = $s
    }
    $out
}

if ($Mode -eq 'TrueLoss') {
    Invoke-CRFlowStep "c$Subject relay dark for ${DarkSeconds}s (P2P silent)" {
        Set-CRFlowImpairment "loss=100,peer=$subjectId,for=$($DarkSeconds + 60)" | Out-Null
        Start-Sleep -Seconds $DarkSeconds
    } | Out-Null
    $script:CRFlowExpectedExit += (Get-CRFlowClient $Subject).pid
}

$drop = Invoke-CRFlowStep "server resets c$Subject's websocket ($subjectId, silent=$([bool]$Silent))" {
    $body = @{ match = $subjectId; silent = [bool]$Silent } | ConvertTo-Json -Compress
    $r = Invoke-RestMethod -Method Post -Uri 'http://127.0.0.1:8080/test/drop-ws' -Body $body -ContentType 'application/json' -TimeoutSec 5
    if (-not @($r.dropped).Count) { throw "drop-ws matched no session for '$subjectId'" }
    $r
}

$samples = Invoke-CRFlowStep "all clients sampled for ${WatchSeconds}s after the drop" {
    $series = @{}
    foreach ($i in $C) { $series["c$i"] = New-Object System.Collections.ArrayList }
    $clock = [Diagnostics.Stopwatch]::StartNew()
    while ($clock.Elapsed.TotalSeconds -lt $WatchSeconds) {
        foreach ($i in $C) {
            $alive = [bool](Get-Process -Id (Get-CRFlowClient $i).pid -ErrorAction SilentlyContinue)
            $s = if ($alive) { Get-State $i 'after' } else { $null }
            [void]$series["c$i"].Add([ordered]@{ s = [math]::Round($clock.Elapsed.TotalSeconds, 1); alive = $alive; state = $s })
        }
        Start-Sleep -Seconds 3
    }
    $series
}

foreach ($i in $C) {
    $alive = [bool](Get-Process -Id (Get-CRFlowClient $i).pid -ErrorAction SilentlyContinue)
    $states = @($samples["c$i"] | Where-Object { $_.state } | ForEach-Object { $_.state })
    $last = $states | Select-Object -Last 1
    $quit = @(Get-LogLines $gameLogs $gameMarks $i 'Quiting Game Due to Net Execute failure')
    $wsClose = @(Get-LogLines $gameLogs $gameMarks $i 'reset active_con due to websocket connection close')
    $lobbyDrop = @(Get-LogLines $shimLogs $shimMarks $i '\[LOBBYDROP\]')
    $left = @(Get-LogLines $shimLogs $shimMarks $i '\[MISSION\] Mission left simulation')
    $detail = [ordered]@{ alive = $alive; answered = $states.Count; samples = @($samples["c$i"]).Count
        timeBefore = $before["c$i"].time; timeLast = $last.time; rosterBefore = $before["c$i"].roster; rosterLast = $last.roster
        quit = $quit; wsClose = $wsClose; lobbyDrop = $lobbyDrop; missionLeft = $left }

    if ($Mode -eq 'Keep') {
        $inGame = $alive -and -not $quit.Count -and -not $left.Count -and $last -and ($last.time -gt $before["c$i"].time + $WatchSeconds / 2)
        Add-CRFlowCheck "c$i stays in the mission and its clock runs" ([bool]$inGame) $detail
        if ($i -eq $Subject) {
            Add-CRFlowCheck "c$i saw the websocket close and kept the match" `
                ([bool]($wsClose.Count -and ($lobbyDrop -match 'keeping the match'))) $detail
        } elseif (-not $Silent) {
            Add-CRFlowCheck "c$i kept c$Subject when the lobby dropped it" `
                ([bool](($lobbyDrop -match 'kept in the match') -and $last.roster -eq $before["c$i"].roster)) $detail
        } else {
            Add-CRFlowCheck "observed on c${i}: roster $($before["c$i"].roster) -> $($last.roster)" $true $detail
        }
    } else {
        if ($i -eq $Subject) {
            Add-CRFlowCheck "c$i with silent P2P takes the stock leave and quits" `
                ([bool](($lobbyDrop -match 'stock leave') -and $quit.Count)) $detail
        } else {
            # The stock player-left on the host logs a [MISSION] RUN_WAS_QUIT
            # transition while its mission keeps running, so judge by the clock.
            Add-CRFlowCheck "c$i stays in the mission and its clock runs" `
                ([bool]($alive -and -not $quit.Count -and $last -and ($last.time -gt $before["c$i"].time + $WatchSeconds / 2))) $detail
        }
    }
}
