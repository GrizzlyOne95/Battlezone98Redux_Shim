# misn04 end film only: jump the host (authority) straight to the win and check
# the closing film on both clients: the camera pod on the Face's summit, both
# cameras orbiting it on endcin, the pod removed afterwards, and
# misn04w1.des on both. Faster than misn04-win and independent of audio (the
# film runs on its own 20 s timer).
param([int]$HostClient = 0, [int]$GuestClient = 1)
$H, $G = $HostClient, $GuestClient

Invoke-CRFlowStep 'probes attached; host ready' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowEvent $G attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlow $H 'return M.missionstart and IsAlive(M.avrec) and IsAlive(M.relic)' -TimeoutSeconds 90
    Invoke-CRFlow $H 'every("protect", 0.5, function() heal(M.avrec); heal(M.relic) end); return true' | Out-Null
}

Invoke-CRFlowStep 'host wins -> end film starts with a summit target' {
    Invoke-CRFlow $H 'M.relicsecure = true; M.basesecure = true; return true' | Out-Null
    Wait-CRFlow $H 'return M.cin_started and IsValid(M.endcamTarget)' -TimeoutSeconds 60 | Out-Null
    Invoke-CRFlow $H 'return { target = describe(M.endcamTarget), path = L().cameraPath }'
}

foreach ($s in 4, 10, 16) {
    Invoke-CRFlowStep "end film t~${s}s: both cameras orbit the summit" {
        Start-Sleep -Seconds 5
        $hostShot = Invoke-CRFlow $H 'return { path = L().cameraPath, active = L().localCameraActive }'
        $guestShot = Invoke-CRFlow $G 'local l = L(); return { path = l.remotePath, active = l.localCameraActive, targetOdf = l.remoteTargetOdf }'
        if ($guestShot.path -ne 'endcin' -or $guestShot.targetOdf -ne 'apcamr') { throw "guest film: $(ConvertTo-Json $guestShot -Compress)" }
        @{ host = $hostShot; guest = $guestShot }
    }
}

Invoke-CRFlowStep 'film ends -> pod removed, win on both' {
    Wait-CRFlowOp $H SucceedMission -TimeoutSeconds 40 | Out-Null
    Wait-CRFlowOp $G SucceedMission -TimeoutSeconds 30 | Out-Null
    $left = Invoke-CRFlow $H 'return IsValid(M.endcamTarget)'
    if ($left) { throw 'the summit camera pod is still there after the film' }
    'removed'
}

Test-CRFlowResultParity -Expect SucceedMission
