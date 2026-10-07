param([int]$HostClient = 0, [int]$GuestClient = 1,
      [ValidateSet('recycler','factory')][string]$Destroyed = 'factory')
$H, $G = $HostClient, $GuestClient
$target = if ($Destroyed -eq 'recycler') { 'avrec' } else { 'lemnos' }
$debrief = if ($Destroyed -eq 'recycler') { 'misn05l1.des' } else { 'misn05l2.des' }
Invoke-CRFlowStep 'both ready; shared opening objective' {
    foreach ($client in $H, $G) {
        Wait-CRFlowEvent $client attach -TimeoutSeconds 120 | Out-Null
        Wait-CRFlow $client 'return role().ready' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.game_start' -TimeoutSeconds 90 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn0501.otf' -TimeoutSeconds 20
}
Invoke-CRFlowStep "$Destroyed destroyed by its owner; no victory" {
    Invoke-CRFlow $H "return kill(M.$target)" | Out-Null
    Wait-CRFlow $H 'return M.missionfail and not M.missionwon' -TimeoutSeconds 15
}
Invoke-CRFlowStep 'authored loss reaches both clients' {
    Wait-CRFlowOp $H FailMission $debrief -TimeoutSeconds 30 | Out-Null
    Wait-CRFlowOp $G FailMission $debrief -TimeoutSeconds 25 | Out-Null
    $debrief
}
Test-CRFlowResultParity -Expect FailMission -Debrief $debrief -Clients @($H, $G)
