# Mission 06 co-op loss: Wyoming (avrecy-1_recycler, team 1) destroyed. The
# leader plays the two lines (0653, 0651) and fails the mission with
# misn06l5.des; the result must reach every client exactly once.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      [ValidateSet('recycler')][string]$Destroyed = 'recycler')
$H, $G = $HostClient, $GuestClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$debrief = 'misn06l5.des'
Invoke-CRFlowStep 'all ready; shared opening objective and film' {
    foreach ($client in $C) {
        Wait-CRFlowEvent $client attach -TimeoutSeconds 120 | Out-Null
        Wait-CRFlow $client 'return role().ready' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.coopBootstrapped and M.missionstart == false' -TimeoutSeconds 90 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client AddObjective 'misn0600.otf' -TimeoutSeconds 20 | Out-Null }
    # Keep a complete post-loading native network observation before triggering
    # this short loss case (the four-peer health gate needs ten seconds).
    if ($C.Count -gt 2) { Start-Sleep -Seconds 10 }
}
Invoke-CRFlowStep 'Wyoming destroyed by its owner; no victory' {
    $before = Invoke-CRFlow $H 'return { alive = IsAlive(M.avrec), odf = GetOdf(M.avrec), team = GetTeamNum(M.avrec) }'
    if (-not $before.alive -or $before.team -ne 1) { throw "Wyoming is not a live team-1 object: $(ConvertTo-Json $before -Compress)" }
    Invoke-CRFlow $H 'return kill(M.avrec)' | Out-Null
    Wait-CRFlow $H 'return M.missionfail1 and not M.dustoff' -TimeoutSeconds 15
}
Invoke-CRFlowStep 'the lines play on every client, then the loss reaches them all' {
    foreach ($client in $guests) { Wait-CRFlowOp $client Play 'misn0653.wav' -TimeoutSeconds 20 | Out-Null }
    Wait-CRFlowOp $H FailMission $debrief -TimeoutSeconds 45 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client FailMission $debrief -TimeoutSeconds 30 | Out-Null }
    $debrief
}
Test-CRFlowResultParity -Expect FailMission -Debrief $debrief -Clients $C
