# misn04 "CR: Relic recovery" (Mars), full win path with a host and one guest.
#
# The authored chain: base objectives -> a player nears the relic (CCA
# patrols wake, the recon camera arrives) -> the relic is seen (relic film) ->
# the relic reaches Recycler Montana (relic secure) -> the CCA recycler and its
# waves are destroyed (base secure) -> closing audio and the 20 s end film ->
# win. The host does the players' part on objects it owns (the relic, CCA AI);
# each client moves only its own craft. The guest must see every objective,
# both films and the result.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Who presses skip during the relic film: 'guest', 'host' or 'none'.
      [ValidateSet('guest', 'host', 'none')][string]$Skipper = 'guest',
      [int]$SkipKey = 0x20)

$H, $G = $HostClient, $GuestClient

Invoke-CRFlowStep 'probes attached on both clients' {
    $a = Wait-CRFlowEvent $H attach -TimeoutSeconds 120
    $b = Wait-CRFlowEvent $G attach -TimeoutSeconds 120
    if (-not $a.bzfile -or -not $b.bzfile) { throw "bzfile missing (host=$($a.bzfile) guest=$($b.bzfile)); no command channel" }
    @{ lua = $a.lua }
}

Invoke-CRFlowStep 'roles: host has authority, guest does not' {
    $hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    $gr = Wait-CRFlow $G 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    if (-not $hr.authority -or $gr.authority) { throw "authority host=$($hr.authority) guest=$($gr.authority)" }
    if ($hr.team -eq $gr.team) { throw "host and guest share team $($hr.team)" }
    @{ hostTeam = $hr.team; guestTeam = $gr.team }
}

Invoke-CRFlowStep 'mission started; base objectives on guest' {
    Wait-CRFlow $H 'return M.missionstart and IsAlive(M.relic)' -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn0401.otf' -TimeoutSeconds 30 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn0400.otf' -TimeoutSeconds 30 | Out-Null
    'misn0401.otf + misn0400.otf'
}

Invoke-CRFlowStep 'guest never ran the authority gates' {
    $g = Invoke-CRFlow $G 'return { missionstart = M.missionstart == true, relic = M.relic ~= nil }'
    if ($g.missionstart) { throw "guest advanced authority state: $(ConvertTo-Json $g -Compress)" }
    $g
}

Invoke-CRFlowStep 'keep objectives and players alive (test assist)' {
    Invoke-CRFlow $H @'
every('protect', 1, function()
    for _, k in ipairs({ "avrec", "relic" }) do
        if M[k] then heal(M[k]) end
    end
end)
return #tasks()
'@ | Out-Null
    foreach ($c in $H, $G) { Invoke-CRFlow $c "every('selfheal', 1, function() heal(me()) end); return true" | Out-Null }
    'protect + selfheal'
}

Invoke-CRFlowStep 'host nears the relic -> CCA patrols and recon camera' {
    Invoke-CRFlow $H 'return tp(M.relic, 500)' | Out-Null
    Wait-CRFlow $H 'return M.surveysent and M.reconsent' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'guest sees the recon objective marker' {
    Wait-CRFlowOp $G SetObjectiveName 'Investigate CCA' -TimeoutSeconds 60 | Out-Null
    'Investigate CCA'
} -Soft

Invoke-CRFlowStep 'relic seen -> relic film on both clients' {
    Invoke-CRFlow $H 'return tp(M.relic, 120)' | Out-Null
    Wait-CRFlow $H 'return M.discoverrelic and L().localCameraActive' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 20 | Out-Null
    @{ host = Invoke-CRFlow $H 'return L()'; guest = Invoke-CRFlow $G 'return L()' }
}

Invoke-CRFlowStep 'clear the relic patrols (test assist)' {
    Invoke-CRFlow $H @'
every('clear', 2, function()
    if M.missionwon then return true end
    clearAroundPlayers(5, "^sv", 500)
end)
return true
'@
}

if ($Skipper -ne 'none') {
    $skipClient, $watchClient = if ($Skipper -eq 'host') { $H, $G } else { $G, $H }
    Invoke-CRFlowStep "$Skipper skips the relic film; the other client's film continues" {
        Send-CRFlowKey $skipClient $SkipKey
        Start-Sleep -Milliseconds 300
        Send-CRFlowKey $skipClient $SkipKey
        Wait-CRFlow $skipClient 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 10 | Out-Null
        Start-Sleep -Seconds 3
        $w = Invoke-CRFlow $watchClient 'return L().localCameraActive'
        $filming = Invoke-CRFlow $H 'return M.discoverrelic and not M.cin1done'
        if ($filming -and -not $w) { throw "c$watchClient camera ended while the film was still running" }
        @{ watcherActive = $w; hostFilming = $filming }
    }
}

Invoke-CRFlowStep 'relic film ends; relic objective on guest' {
    Wait-CRFlow $H 'return M.cin1done' -TimeoutSeconds 40 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn0403.otf' -TimeoutSeconds 30 | Out-Null
    'misn0403.otf'
}

Invoke-CRFlowStep 'both cameras released after the relic film' {
    Wait-CRFlow $H 'return not L().localCameraActive' -TimeoutSeconds 15 | Out-Null
    Wait-CRFlow $G 'return not L().localCameraActive' -TimeoutSeconds 15
}

Invoke-CRFlowStep 'relic delivered to Recycler Montana -> relic secure' {
    Invoke-CRFlow $H 'return put(M.relic, M.avrec, 40)' | Out-Null
    Wait-CRFlow $H 'return M.relicsecure' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'mid-mission world parity' { Test-CRFlowTransport $H @($G); Test-CRFlowWorldParity $H @($G) } -Soft

Invoke-CRFlowStep 'CCA recycler and its waves destroyed -> base secure' {
    Invoke-CRFlow $H @'
local n = 0
for k, v in pairs(M) do
    if type(k) == "string" and k:find("^w%du%d$") and kill(v) then n = n + 1 end
end
return { waves = n, svrec = kill(M.svrec) }
'@ | Out-Null
    Wait-CRFlow $H 'return M.basesecure' -TimeoutSeconds 30
}

Invoke-CRFlowStep 'both secure -> mission won on host' {
    Wait-CRFlow $H 'return M.missionwon' -TimeoutSeconds 20 | Out-Null
    $o = Wait-CRFlowEvent $G op -TimeoutSeconds 30 -Description 'misn0401 green' -Where { $_.op -eq 'AddObjective' -and @($_.args) -contains 'misn0401.otf' -and @($_.args) -contains 'green' }
    @{ guestObjective = $o.args }
}

Invoke-CRFlowStep 'end film plays on both clients' {
    Wait-CRFlow $H 'return M.cin_started' -TimeoutSeconds 90 | Out-Null
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 20
} -Soft

Invoke-CRFlowStep 'win reaches both clients' {
    $a = Wait-CRFlowOp $H SucceedMission 'misn04w1.des' -TimeoutSeconds 60
    $b = Wait-CRFlowOp $G SucceedMission 'misn04w1.des' -TimeoutSeconds 30
    @{ hostAt = $a.t; guestAt = $b.t }
}

Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn04w1.des' -Clients @($H, $G)
