param([int]$HostClient = 0, [int]$GuestClient = 1,
      [ValidateSet('recycler','factory')][string]$Destroyed = 'factory')
$H, $G = $HostClient, $GuestClient
$C = @(Get-CRFlowClientIndices)
$target = if ($Destroyed -eq 'recycler') { 'avrec' } else { 'lemnos' }
$debrief = if ($Destroyed -eq 'recycler') { 'misn05l1.des' } else { 'misn05l2.des' }
Invoke-CRFlowStep 'all ready; shared opening objective' {
    foreach ($client in $C) {
        Wait-CRFlowEvent $client attach -TimeoutSeconds 120 | Out-Null
        Wait-CRFlow $client 'return role().ready' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.game_start' -TimeoutSeconds 90 | Out-Null
    foreach ($client in ($C | Where-Object { $_ -ne $H })) { Wait-CRFlowOp $client AddObjective 'misn0501.otf' -TimeoutSeconds 20 }
    # Keep a complete post-loading native network observation before triggering
    # this short loss case (the four-peer health gate needs ten seconds).
    if ($C.Count -gt 2) { Start-Sleep -Seconds 10 }
}
Invoke-CRFlowStep "$Destroyed destroyed by its owner; no victory" {
    Invoke-CRFlow $H "return kill(M.$target)" | Out-Null
    Wait-CRFlow $H 'return M.missionfail and not M.missionwon' -TimeoutSeconds 15
}
Invoke-CRFlowStep 'authored loss reaches every client' {
    Wait-CRFlowOp $H FailMission $debrief -TimeoutSeconds 30 | Out-Null
    foreach ($client in ($C | Where-Object { $_ -ne $H })) { Wait-CRFlowOp $client FailMission $debrief -TimeoutSeconds 25 | Out-Null }
    $debrief
}
Test-CRFlowResultParity -Expect FailMission -Debrief $debrief -Clients $C
