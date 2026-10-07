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

. "$PSScriptRoot\..\..\BZRHarness.ps1"
$H, $G = $HostClient, $GuestClient
$script:CRFlowSkipParity = $true

Invoke-CRFlowStep 'probes attached on both clients' {
    $a = Wait-CRFlowEvent $H attach -TimeoutSeconds 120
    $b = Wait-CRFlowEvent $G attach -TimeoutSeconds 120
    if (-not $a.bzfile -or -not $b.bzfile) { throw "bzfile missing (host=$($a.bzfile) guest=$($b.bzfile)); no command channel" }
    @{ mission = $a.mission }
}

Invoke-CRFlowStep 'roles: host has authority, guest does not' {
    $hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    $gr = Wait-CRFlow $G 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    if (-not $hr.authority -or $gr.authority) { throw "authority host=$($hr.authority) guest=$($gr.authority)" }
    @{ hostId = $hr.playerId; guestId = $gr.playerId }
}

Invoke-CRFlowStep 'session ready and mission running on both' {
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    Wait-CRFlow $G 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 60 | Out-Null
    Start-Sleep -Seconds $PlaySeconds
    $g = Invoke-CRFlow $G 'return { departed = role().leaderDeparted, result = M.coopResult == true, players = #players() }'
    if ($g.departed -or $g.result) { throw "guest already finished before the host left: $(ConvertTo-Json $g -Compress)" }
    $g
}

$hostPid = (Get-CRFlowClient $H).pid
Invoke-CRFlowStep 'host closes the game' {
    Stop-BZRGame -Id $hostPid -NoForce -TimeoutSeconds 30
    if (Get-Process -Id $hostPid -ErrorAction SilentlyContinue) { throw "host pid $hostPid still running after WM_CLOSE" }
    @{ hostPid = $hostPid }
}

Invoke-CRFlowStep 'guest detects the leader departure' {
    Wait-CRFlow $G 'return role().leaderDeparted and role()' -TimeoutSeconds 60
}

Invoke-CRFlowStep 'guest fails the mission' {
    $f = Wait-CRFlowOp $G FailMission -TimeoutSeconds 30
    @{ at = $f.t; args = $f.args }
}

Invoke-CRFlowStep "guest still running ${SurviveSeconds}s later" {
    Start-Sleep -Seconds $SurviveSeconds
    $gp = (Get-CRFlowClient $G).pid
    if (-not (Get-Process -Id $gp -ErrorAction SilentlyContinue)) { throw "guest pid $gp exited (crash?)" }
    $ops = @(Get-CRFlowEvents $G op | Where-Object { $_.op -in 'SucceedMission', 'FailMission' } | ForEach-Object { Get-CRFlowOpSignature $_ })
    if ($ops.Count -ne 1) { throw "expected exactly one mission result on the guest, got: $($ops -join '; ')" }
    @{ guestPid = $gp; results = $ops }
}

Test-CRFlowResultParity -Expect FailMission -Clients @($G)
