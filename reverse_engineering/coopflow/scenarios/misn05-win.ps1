# Full authored Lemnos mission progression, using owner-local setup assists.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      [ValidateSet('guest','host','none')][string]$Skipper = 'guest',
      [switch]$FocusedSkip)
$H, $G = $HostClient, $GuestClient

Invoke-CRFlowStep 'probes, readiness and campaign authority' {
    foreach ($client in $H, $G) {
        Wait-CRFlowEvent $client attach -TimeoutSeconds 120 | Out-Null
        Wait-CRFlow $client 'return role().ready' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.game_start' -TimeoutSeconds 90 | Out-Null
    $hostRole = Invoke-CRFlow $H 'return role()'
    $guestRole = Invoke-CRFlow $G 'return role()'
    if (-not $hostRole.authority -or $guestRole.authority -or $hostRole.team -eq $guestRole.team) { throw 'campaign roles incorrect' }
    @{ host = $hostRole; guest = $guestRole }
}

Invoke-CRFlowStep 'shared opening objective; one authored Montana and no guest AI execution' {
    Wait-CRFlowOp $G AddObjective 'misn0501.otf' -TimeoutSeconds 25 | Out-Null
    $state = Invoke-CRFlow $H @'
local mines, humanRecyclers = 0, 0
for h in AllObjects() do
    if IsValid(h) then
        local odf = GetOdf(h)
        if odf == "boltmine" or odf == "boltmine.odf" then mines = mines + 1 end
        if GetTeamNum(h) >= 1 and GetTeamNum(h) <= 4 and IsOdf(h, "avrec5") then humanRecyclers = humanRecyclers + 1 end
    end
end
return { mines = mines, humanRecyclers = humanRecyclers, enemyTeam = GetTeamNum(M.svrec), mineTeam = 6 }
'@
    if ($state.enemyTeam -ne 5 -or $state.humanRecyclers -ne 1 -or $state.mines -ne 23) { throw "native team/recycler/mine setup incorrect: $(ConvertTo-Json $state -Compress)" }
    $guestStarted = Invoke-CRFlow $G 'return M.game_start'
    if ($guestStarted) { throw 'guest ran authoritative mission startup' }
    $state
}

Invoke-CRFlowStep 'protect mission objectives and players (test assist)' {
    Invoke-CRFlow $H "every('protect', 0.5, function() heal(M.avrec); heal(M.lemnos) end); return true" | Out-Null
    foreach ($client in $H, $G) { Invoke-CRFlow $client "every('selfheal', 0.5, function() heal(me()) end); return true" | Out-Null }
    'owner-local heal only'
}

Invoke-CRFlowStep 'guest discovers Lemnos; recon film reaches both clients' {
    Invoke-CRFlow $G 'return tp(M.lemnos, 120)' | Out-Null
    Wait-CRFlow $H 'return M.reconfactory and L().localCameraActive' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 10 | Out-Null
    @{ host = Invoke-CRFlow $H 'return L()'; guest = Invoke-CRFlow $G 'return L()' }
}

Invoke-CRFlowStep 'recon film ends; all cameras released' {
    Wait-CRFlow $H 'return M.lemcin2' -TimeoutSeconds 12 | Out-Null
    foreach ($client in $H, $G) { Wait-CRFlow $client 'return not L().localCameraActive' -TimeoutSeconds 8 | Out-Null }
    'both released'
}

Invoke-CRFlowStep 'factory identified; defense orders reach guest' {
    Invoke-CRFlow $H 'M.start = GetTime() - 1; return true' | Out-Null
    Wait-CRFlowOp $G SetObjectiveName 'Lemnos Factory' -TimeoutSeconds 20 | Out-Null
    Invoke-CRFlow $H 'M.readtime = GetTime() - 1; return true' | Out-Null
    Wait-CRFlow $H 'return M.neworders' -TimeoutSeconds 10 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn0502.otf' -TimeoutSeconds 20 | Out-Null
    'shared identification and defense objectives'
}

Invoke-CRFlowStep 'all four shuffled CCA deployment waves spawn; surviving extras block assault' {
    Invoke-CRFlow $H 'for i = 1, 4 do M.sendTime[i] = GetTime() - 1 end; return true' | Out-Null
    $deployment = Wait-CRFlow $H 'return M.sent1Done and M.sent2Done and M.sent3Done and M.sent4Done and { count = #M.preAttackEnemies, assault = M.attacktimeset }' -TimeoutSeconds 15
    if ($deployment.assault -or $deployment.count -lt 12) { throw 'deployment gate failed' }
    $deployment
}

Invoke-CRFlowStep 'clear deployment; final Lemnos assault spawns once' {
    Invoke-CRFlow $H 'for _, h in ipairs(M.preAttackEnemies) do kill(h) end; return true' | Out-Null
    Wait-CRFlow $H 'return M.attacktimeset and M.go' -TimeoutSeconds 20 | Out-Null
    Invoke-CRFlow $H 'M.platoonhere = GetTime() - 1; return true' | Out-Null
    Wait-CRFlow $H 'return M.aw1 and IsAlive(M.aw1) and not M.go' -TimeoutSeconds 15
}

Invoke-CRFlowStep 'all four reinforcement waves; shared severe weather' {
    Invoke-CRFlow $H 'M.aw1t = GetTime() - 1; M.aw2t = M.aw1t; M.aw3t = M.aw1t; M.aw4t = M.aw1t; return true' | Out-Null
    Wait-CRFlow $H 'return M.aw1sent and M.aw2sent and M.aw3sent and M.aw4sent and M.weatherSetPiece' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlow $G 'return require("CRMarsWeather").GetTargetLevel() >= 4' -TimeoutSeconds 20 | Out-Null
    'reinforcements and weather cues delivered'
}

Invoke-CRFlowStep 'destroy CCA recycler; a surviving scripted attacker still blocks victory' {
    Invoke-CRFlow $H 'return kill(M.svrec)' | Out-Null
    Wait-CRFlow $H 'return M.possiblewin and not M.missionwon' -TimeoutSeconds 15
}

Invoke-CRFlowStep 'all victory-gating attackers cleared; friendly fleet on reserved team 7' {
    Invoke-CRFlow $H 'for _, h in ipairs(M.victoryEnemies) do kill(h) end; return true' | Out-Null
    Wait-CRFlow $H 'return M.missionwon and M.endseq_started and #M.endFleet == 7' -TimeoutSeconds 15 | Out-Null
    $fleet = Invoke-CRFlow $H 'return { count = #M.endFleet, team = GetTeamNum(M.endFleet[1]) }'
    if ($fleet.team -ne 7) { throw 'friendly fleet collides with a human or mine team' }
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 12 | Out-Null
    $fleet
}

if ($Skipper -ne 'none') {
    $skipClient, $watchClient = if ($Skipper -eq 'host') { $H, $G } else { $G, $H }
    Invoke-CRFlowStep "$Skipper skips locally; shared closing film remains timed" {
        # The recon film is only four seconds; verify skip during the ten-second
        # closing film. -FocusedSkip optionally tests real desktop input.
        Send-CRFlowKey $skipClient 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
        Start-Sleep -Milliseconds 300
        Send-CRFlowKey $skipClient 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
        Wait-CRFlow $skipClient 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 5 | Out-Null
        $filming = Invoke-CRFlow $H 'return not M.endseq_cutscene_done'
        $watching = Invoke-CRFlow $watchClient 'return L().localCameraActive'
        if (-not $filming -or -not $watching) { throw 'shared closing film ended on the local skip' }
        @{ watcherActive = $watching; hostFilming = $filming }
    }
}

Invoke-CRFlowStep 'closing film releases; commander reveal and win reach both' {
    Wait-CRFlow $H 'return M.endseq_cutscene_done' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlowOp $G SetObjectiveName 'Commander Eldritch' -TimeoutSeconds 30 | Out-Null
    Wait-CRFlowOp $H SucceedMission 'misn05w1.des' -TimeoutSeconds 30 | Out-Null
    Wait-CRFlowOp $G SucceedMission 'misn05w1.des' -TimeoutSeconds 20 | Out-Null
    'misn05w1.des on both clients'
}
Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn05w1.des' -Clients @($H, $G)
