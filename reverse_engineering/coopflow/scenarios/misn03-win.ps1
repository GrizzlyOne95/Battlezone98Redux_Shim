# misn03 "CR: Eagle's Nest 1 Coop", full win path with a host and one guest.
#
# Drives the real mission through each authored gate, using the probe to do
# what players would (kill the first wave, clear attackers, escort, reach the
# launch pad) and pulling long timers forward. The host only touches objects
# it owns (mission AI on teams 1 and 5); each client moves only its own craft.
# At every gate the guest must see the same presentation the host published.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Virtual key posted to the guest to skip the evacuation film (Space).
      [int]$SkipKey = 0x20,
      # Seconds to let the outro play on its own before pulling its 90s fallback.
      [int]$NaturalOutroSeconds = 45)

$H, $G = $HostClient, $GuestClient

Invoke-CRFlowStep 'probes attached on both clients' {
    $a = Wait-CRFlowEvent $H attach -TimeoutSeconds 120
    $b = Wait-CRFlowEvent $G attach -TimeoutSeconds 120
    if (-not $a.bzfile -or -not $b.bzfile) { throw "bzfile missing (host=$($a.bzfile) guest=$($b.bzfile)); no command channel" }
    @{ lua = $a.lua; hostRoot = $a.root; guestRoot = $b.root }
}

Invoke-CRFlowStep 'roles: host has authority, guest does not' {
    $hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    $gr = Wait-CRFlow $G 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    if (-not $hr.authority -or $gr.authority) { throw "authority host=$($hr.authority) guest=$($gr.authority)" }
    if ($hr.team -eq $gr.team) { throw "host and guest share team $($hr.team)" }
    @{ hostTeam = $hr.team; guestTeam = $gr.team; hostId = $hr.playerId; guestId = $gr.playerId }
}

Invoke-CRFlowStep 'session ready and mission started on host' {
    Wait-CRFlow $H 'return M.start_done and role().ready' -TimeoutSeconds 120 | Out-Null
    Invoke-CRFlow $H 'return players()'
}

Invoke-CRFlowStep 'guest shows the defense objective' {
    Wait-CRFlowOp $G AddObjective 'misn0301.otf' -TimeoutSeconds 30 | Out-Null
    'misn0301.otf'
}

Invoke-CRFlowStep 'guest never ran the authority gates' {
    $g = Invoke-CRFlow $G 'return { start_done = M.start_done == true, first_wave_done = M.first_wave_done == true }'
    if ($g.start_done -or $g.first_wave_done) { throw "guest advanced authority state: $(ConvertTo-Json $g -Compress)" }
    $g
}

Invoke-CRFlowStep 'keep objectives and players alive (test assist)' {
    Invoke-CRFlow $H @'
every('protect', 1, function()
    for _, k in ipairs({ "solar1", "solar2", "solar3", "solar4", "launch", "avrecycler", "rescue1", "rescue2" }) do
        if M[k] then heal(M[k]) end
    end
end)
return #tasks()
'@ | Out-Null
    foreach ($c in $H, $G) { Invoke-CRFlow $c "every('selfheal', 1, function() heal(me()) end); return true" | Out-Null }
    'protect + selfheal'
}

Invoke-CRFlowStep 'first wave destroyed -> retreat' {
    Invoke-CRFlow $H 'return kill(M.wave1_1), kill(M.wave1_2)' | Out-Null
    Wait-CRFlow $H 'return M.start_retreat' -TimeoutSeconds 30
}

Invoke-CRFlowStep 'fortify phase on host' {
    Invoke-CRFlow $H "return ff('^new_message_time$')" | Out-Null
    Wait-CRFlow $H 'return M.done_retreat and role().phase == 2' -TimeoutSeconds 30
}

Invoke-CRFlowStep 'guest shows the fortify objective' {
    Wait-CRFlowOp $G AddObjective 'misn0302.otf' -TimeoutSeconds 30 | Out-Null
    'misn0302.otf'
}

Invoke-CRFlowStep 'mid-mission world parity' { Test-CRFlowTransport $H @($G); Test-CRFlowWorldParity $H @($G) } -Soft

Invoke-CRFlowStep 'waves 2-4 and reinforcements (timers pulled)' {
    Invoke-CRFlow $H "return { ff('^second_wave_time$'), ff('^third_wave_time$'), ff('^fourth_wave_time$'), ff('^support_time$') }" | Out-Null
    Wait-CRFlow $H 'return M.second_wave_done and M.third_wave_done and M.fourth_wave_done and M.help_spawn' -TimeoutSeconds 60
}

Invoke-CRFlowStep 'every player clear of enemies -> evacuation' {
    Invoke-CRFlow $H @'
every('clear', 2, function()
    if M.second_objective then return true end
    clearAroundPlayers(5, "^svtank", 600)
    clearAroundPlayers(5, "^svfigh", 600)
end)
return ff('^apc_spawn_time$')
'@ | Out-Null
    Wait-CRFlow $H 'return M.second_objective' -TimeoutSeconds 120
}

Invoke-CRFlowStep 'evacuation film plays on both clients' {
    Wait-CRFlow $H 'return M.camera_ready and L().localCameraActive' -TimeoutSeconds 30 | Out-Null
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 20 | Out-Null
    @{ host = Invoke-CRFlow $H 'return L()'; guest = Invoke-CRFlow $G 'return L()' }
}

Invoke-CRFlowStep 'guest skips the film; host film continues' {
    Send-CRFlowKey $G $SkipKey
    Start-Sleep -Milliseconds 300
    Send-CRFlowKey $G $SkipKey
    Wait-CRFlow $G 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 10 | Out-Null
    $hostCam = Invoke-CRFlow $H 'return { active = L().localCameraActive, over = M.movie_over == true }'
    if (-not $hostCam.active -and -not $hostCam.over) { throw 'host camera ended without the film finishing' }
    $hostCam
}

Invoke-CRFlowStep 'film ends -> escort objective on guest' {
    Wait-CRFlow $H 'return M.movie_over' -TimeoutSeconds 40 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn0303.otf' -TimeoutSeconds 30 | Out-Null
    'misn0303.otf'
}

Invoke-CRFlowStep 'guest camera released after the film' {
    Wait-CRFlow $G 'return not L().localCameraActive' -TimeoutSeconds 15
}

Invoke-CRFlowStep 'cinematic props removed on both' {
    Wait-CRFlow $H 'return M.remove_props' -TimeoutSeconds 30 | Out-Null
    $count = @(Get-CRFlowEvents $G op | Where-Object op -eq 'RemoveObject').Count
    if ($count -lt 1) { throw 'guest received no RemoveObject' }
    @{ guestRemoveObject = $count }
}

Invoke-CRFlowStep 'transports reach the launch pad' {
    Wait-CRFlow $H 'return IsAlive(M.rescue1) and IsAlive(M.rescue2)' -TimeoutSeconds 60 | Out-Null
    Invoke-CRFlow $H 'return put(M.rescue1, M.launch, 30), put(M.rescue2, M.launch, 45)' | Out-Null
    Wait-CRFlow $H 'return M.third_objective' -TimeoutSeconds 30
}

Invoke-CRFlowStep 'guest shows the launch objective' {
    Wait-CRFlowOp $G AddObjective 'misn0304.otf' -TimeoutSeconds 30 | Out-Null
    'misn0304.otf'
}

Invoke-CRFlowStep 'pre-launch world parity' { Test-CRFlowTransport $H @($G); Test-CRFlowWorldParity $H @($G) } -Soft

Invoke-CRFlowStep 'host alone at the pad does not finish' {
    Invoke-CRFlow $H 'return tp(M.launch, 25)' | Out-Null
    Start-Sleep -Seconds 4
    $done = Invoke-CRFlow $H 'return M.final_objective == true'
    if ($done) { throw 'final objective fired with the guest away from the pad' }
    'waiting for guest'
}

Invoke-CRFlowStep 'both players at the launch pad -> outro' {
    Invoke-CRFlow $G 'return tp(M.launch, 35)' | Out-Null
    Wait-CRFlow $H 'return M.final_objective' -TimeoutSeconds 30 | Out-Null
    Wait-CRFlow $H 'return M.startfinishingmovie' -TimeoutSeconds 15
}

Invoke-CRFlowStep 'outro film plays on guest' {
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 20
} -Soft

$natural = $true
# The co-op outro can end in the result itself (coopResult) without the
# single-player camera_off flag ever being set.
Invoke-CRFlowStep "outro completes on its own (${NaturalOutroSeconds}s)" {
    Wait-CRFlow $H 'return M.camera_off or M.coopResult or M.coopPendingResult ~= nil' -TimeoutSeconds $NaturalOutroSeconds
} -Soft
if (-not (Invoke-CRFlow $H 'return M.camera_off == true or M.coopResult == true or M.coopPendingResult ~= nil')) {
    $natural = $false
    Invoke-CRFlowStep 'outro fallback (90s deadline pulled)' {
        Invoke-CRFlow $H "return ff('^coopOutroDeadline$', 1)" | Out-Null
        Wait-CRFlow $H 'return M.camera_off' -TimeoutSeconds 30
    }
}

Invoke-CRFlowStep 'win reaches both clients' {
    $a = Wait-CRFlowOp $H SucceedMission 'misn03w1.des' -TimeoutSeconds 30
    $b = Wait-CRFlowOp $G SucceedMission 'misn03w1.des' -TimeoutSeconds 30
    @{ hostAt = $a.t; guestAt = $b.t; naturalOutro = $natural }
}

Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn03w1.des' -Clients @($H, $G)
