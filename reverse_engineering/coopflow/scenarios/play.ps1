# Play-test mode: wait until both clients are in the mission with the probe
# answering, then hand over to BZRCoopPlay.ps1. Mission-independent.
param([int]$HostClient = 0, [int]$GuestClient = 1)

Invoke-CRFlowStep 'probes attached on both clients' {
    $a = Wait-CRFlowEvent $HostClient attach -TimeoutSeconds 120
    Wait-CRFlowEvent $GuestClient attach -TimeoutSeconds 120 | Out-Null
    @{ mission = $a.mission; lua = $a.lua }
}
Invoke-CRFlowStep 'both clients answer commands' {
    @{ host = Wait-CRFlow $HostClient 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
       guest = Wait-CRFlow $GuestClient 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90 }
}
