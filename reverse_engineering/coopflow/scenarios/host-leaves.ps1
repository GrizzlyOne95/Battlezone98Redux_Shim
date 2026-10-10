# Any CR co-op mission: the host quits mid-mission and the guest must end the
# mission itself (CR's leader-departure FailMission) instead of hanging or
# carrying on without an authority.
#
# The host is closed the way a player closing the game would (WM_CLOSE through
# Stop-BZRGame -NoForce; never TerminateProcess). Host/guest presentation parity
# is skipped: after the host leaves the streams are expected to differ.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Seconds of mission play before the host leaves.
      [int]$PlaySeconds = 20,
      # Seconds the guest must stay up after the failure.
      [int]$SurviveSeconds = 15)

$H, $G = $HostClient, $GuestClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$script:CRFlowSkipParity = $true

Invoke-CRFlowStep 'probes attached on both clients' {
    $a = Wait-CRFlowEvent $H attach -TimeoutSeconds 120
    foreach ($client in $C) {
        $attached = Wait-CRFlowEvent $client attach -TimeoutSeconds 120
        if (-not $attached.bzfile) { throw "bzfile missing on c$client; no command channel" }
    }
    @{ mission = $a.mission }
}

Invoke-CRFlowStep 'roles: host has authority, guest does not' {
    $hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    if (-not $hr.authority) { throw 'host has no authority' }
    foreach ($client in $guests) {
        $gr = Wait-CRFlow $client 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
        if ($gr.authority) { throw "guest c$client has authority" }
        @{ hostId = $hr.playerId; guestId = $gr.playerId; client = $client }
    }
}

Invoke-CRFlowStep 'session ready and mission running on both' {
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 60 | Out-Null }
    Start-Sleep -Seconds $PlaySeconds
    foreach ($client in $guests) {
        $guestState = Invoke-CRFlow $client 'return { departed = role().leaderDeparted, result = M.coopResult == true, players = #players() }'
        if ($guestState.departed -or $guestState.result -or $guestState.players -ne $C.Count) { throw "guest c$client already finished or lost the roster before the host left" }
        $guestState
    }
}

$hostPid = (Get-CRFlowClient $H).pid
$script:CRFlowExpectedExit += $hostPid
Invoke-CRFlowStep 'host closes the game' {
    Stop-BZRGame -Id $hostPid -NoForce -TimeoutSeconds 30
    if (Get-Process -Id $hostPid -ErrorAction SilentlyContinue) { throw "host pid $hostPid still running after WM_CLOSE" }
    @{ hostPid = $hostPid }
}

Invoke-CRFlowStep 'guest detects the leader departure' {
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().leaderDeparted and role()' -TimeoutSeconds 60 }
}

Invoke-CRFlowStep 'guest fails the mission' {
    foreach ($client in $guests) {
        $f = Wait-CRFlowOp $client FailMission -TimeoutSeconds 30
        @{ client = $client; at = $f.t; args = $f.args }
    }
}

Invoke-CRFlowStep "guest still running ${SurviveSeconds}s later" {
    Start-Sleep -Seconds $SurviveSeconds
    foreach ($client in $guests) {
        $gp = (Get-CRFlowClient $client).pid
        if (-not (Get-Process -Id $gp -ErrorAction SilentlyContinue)) { throw "guest pid $gp exited (crash?)" }
        $ops = @(Get-CRFlowEvents $client op | Where-Object { $_.op -in 'SucceedMission', 'FailMission' } | ForEach-Object { Get-CRFlowOpSignature $_ })
        if ($ops.Count -ne 1) { throw "expected exactly one mission result on c$client, got: $($ops -join '; ')" }
        @{ guestPid = $gp; results = $ops }
    }
}

Test-CRFlowResultParity -Expect FailMission -Clients $guests
