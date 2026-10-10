# misn03 loss path: the Command Tower falls during the defense phase.
# The failure must be decided once by the host and replicated, with the same
# red objective and debrief, to the guest.
param([int]$HostClient = 0, [int]$GuestClient = 1)

$H, $G = $HostClient, $GuestClient

Invoke-CRFlowStep 'probes attached on both clients' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowEvent $G attach -TimeoutSeconds 120 | Out-Null
    'both'
}

Invoke-CRFlowStep 'mission started on host' {
    Wait-CRFlow $H 'return M.start_done and role().ready' -TimeoutSeconds 120
}

Invoke-CRFlowStep 'guest shows the defense objective' {
    Wait-CRFlowOp $G AddObjective 'misn0301.otf' -TimeoutSeconds 30 | Out-Null
    'misn0301.otf'
}

Invoke-CRFlowStep 'host destroys the Command Tower' {
    Invoke-CRFlow $H 'return kill(M.solar1)' | Out-Null
    Wait-CRFlow $H 'return M.lost and M.dead1' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'guest sees the tower objective fail' {
    Wait-CRFlowEvent $G op -TimeoutSeconds 30 -Description 'AddObjective misn0311.otf red' -Where {
        $_.op -eq 'AddObjective' -and @($_.args)[0] -eq 'misn0311.otf' -and @($_.args)[1] -eq 'red'
    } | Out-Null
    'misn0311.otf red'
}

Invoke-CRFlowStep 'tower destroyed on the guest too' {
    Wait-CRFlow $G 'return not IsAlive(M.solar1)' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'loss reaches both clients' {
    Wait-CRFlowOp $H FailMission 'misn03f1.des' -TimeoutSeconds 30 | Out-Null
    Wait-CRFlowOp $G FailMission 'misn03f1.des' -TimeoutSeconds 30 | Out-Null
    'misn03f1.des'
}

Test-CRFlowResultParity -Expect FailMission -Debrief 'misn03f1.des' -Clients @($H, $G)
