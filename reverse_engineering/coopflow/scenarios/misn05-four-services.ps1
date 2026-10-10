# Four real owners exercise all-to-all comms, handle changes, simultaneous
# fallback, and a team-4 out-of-lives failure. Never mutate a remote craft.
param([int]$RespawnTimeout = 45)
$C = @(Get-CRFlowClientIndices)
if (($C -join ',') -ne '0,1,2,3') { throw 'four-services requires -Clients 4' }
$script:CRFlowSkipParity = $true # local deaths/respawns have different HUD messages
$ids = @{}

function Four-State([int]$Client) {
    Invoke-CRFlow $Client 'local s = CRCoop.GetRespawn().GetState(); s.native = exu.GetLives(); s.out = CRCoop.IsOutOfLives(); s.player = describe(me()); return s'
}
function Four-Die([int]$Client) {
    $before = Four-State $Client
    Invoke-CRFlow $Client 'fourMortal = true; kill(me()); return true' | Out-Null
    $deadline = (Get-Date).AddSeconds($RespawnTimeout)
    while ((Get-Date) -lt $deadline) {
        $state = Four-State $Client
        if ($state.respawns -gt $before.respawns -or $state.out) {
            Invoke-CRFlow $Client 'fourMortal = false; return true' | Out-Null
            return $state
        }
        if ($state.native -ge $before.native) {
            Invoke-CRFlow $Client 'if IsAlive(me()) and IsPerson(me()) then kill(me()) end; return true' | Out-Null
        }
        Start-Sleep -Milliseconds 400
    }
    throw "c$Client failed to respawn: $(ConvertTo-Json (Four-State $Client) -Compress -Depth 5)"
}

Invoke-CRFlowStep 'protect objectives and four locally owned players' {
    Wait-CRFlow 0 'return M.game_start' -TimeoutSeconds 90 | Out-Null
    Invoke-CRFlow 0 "every('protect', 0.5, function() heal(M.avrec); heal(M.lemnos); clearAroundPlayers(5, nil, 500) end); return true" | Out-Null
    foreach ($client in $C) {
        $ids[$client] = (Invoke-CRFlow $client 'return role()').playerId
        Invoke-CRFlow $client "every('selfheal', 0.5, function() if not fourMortal then heal(me()) end end); return true" | Out-Null
    }
    @($C | ForEach-Object { @{ client = $_; playerId = $ids[$_] } })
}

Invoke-CRFlowStep 'terrain pings from all four senders reach every client' {
    foreach ($client in $C) {
        $ok = Invoke-CRFlow $client 'local p = GetPosition(me()); p.x = p.x + role().team * 10; return CRCoop.GetComms().SendPing("terrain", nil, p)'
        if (-not $ok) { throw "c$client could not publish a terrain ping" }
    }
    foreach ($client in $C) {
        Wait-CRFlow $client 'local c = CRCoop.GetComms(); local n = 0; for id in pairs(CRCoop.GetPlayers()) do local p = c.GetPings()[id]; if not p or p.kind ~= "terrain" or not p.position then return false end; n = n + 1 end; return n == 4 and c.GetPings()' -TimeoutSeconds 8
    }
}

Invoke-CRFlowStep 'object pings preserve the replicated Lemnos handle on all four' {
    Start-Sleep -Milliseconds 1600
    foreach ($client in $C) {
        if (-not (Invoke-CRFlow $client 'return CRCoop.GetComms().SendPing("object", M.lemnos)')) { throw "c$client could not publish an object ping" }
    }
    foreach ($client in $C) {
        Wait-CRFlow $client 'local c = CRCoop.GetComms(); local n = 0; for id in pairs(CRCoop.GetPlayers()) do local p = c.GetPings()[id]; if not p or p.kind ~= "object" or p.handle ~= M.lemnos then return false end; n = n + 1 end; return n == 4' -TimeoutSeconds 8
    }
}

Invoke-CRFlowStep 'all four settle at the discovered phase-2 objective' {
    foreach ($client in $C) { Invoke-CRFlow $client 'return tp(M.lemnos, 90)' | Out-Null }
    Wait-CRFlow 0 'return M.reconfactory and M.lemcin2' -TimeoutSeconds 20 | Out-Null
    foreach ($client in $C) { Wait-CRFlow $client 'return role().phase == 2 and not L().localCameraActive' -TimeoutSeconds 15 | Out-Null }
    Start-Sleep -Seconds 10
    'phase 2; settled living teammates'
}

foreach ($subjectClient in $C) {
    Invoke-CRFlowStep "c$subjectClient dies locally; teammate placement and new handle agree on every peer" {
        $state = Four-Die $subjectClient
        if ($state.lastRespawn.how -ne 'teammate' -or $state.livesLeft -ne 4) { throw "c$subjectClient missed teammate respawn or consumed extra lives" }
        $position = Invoke-CRFlow $subjectClient 'return xyz(me())'
        $subjectId = $ids[$subjectClient]
        foreach ($observer in $C) {
            # The ejected pilot can remain alive in a peer's registry until the
            # next handle broadcast. Wait for the actual placed replica too.
            $seen = Wait-CRFlow $observer "local p = CRCoop.GetPlayers()[$subjectId]; if not p or not IsValid(p.handle) or not IsAlive(p.handle) or not IsPerson(p.handle) then return false end; local pos = GetPosition(p.handle); local dx, dz = pos.x - $($position[0]), pos.z - $($position[2]); return math.sqrt(dx * dx + dz * dz) <= 30 and xyz(p.handle)" -TimeoutSeconds 10
            $distance = [math]::Sqrt([math]::Pow($seen[0] - $position[0], 2) + [math]::Pow($seen[2] - $position[2], 2))
            if ($distance -gt 30) { throw "c$observer sees c$subjectClient respawn ${distance}m from its owner's position" }
        }
        $state
    }
}

Invoke-CRFlowStep 'four pilots request rescue; host responses reach every client' {
    foreach ($client in $C) {
        if (-not (Invoke-CRFlow $client 'return CRCoop.GetComms().RequestRescue()')) { throw "c$client could not request rescue" }
    }
    foreach ($client in $C) {
        Wait-CRFlow $client 'local requests = CRCoop.GetComms().GetRequests(); for id in pairs(CRCoop.GetPlayers()) do if not requests[id] then return false end end; return requests' -TimeoutSeconds 10
    }
    foreach ($client in $C) {
        $subjectId = $ids[$client]
        if (-not (Invoke-CRFlow 0 "return CRCoop.GetComms().Respond($subjectId, 1)")) { throw "host could not answer c$client" }
    }
    foreach ($client in $C) {
        Wait-CRFlow $client 'local requests = CRCoop.GetComms().GetRequests(); for id in pairs(CRCoop.GetPlayers()) do if not requests[id] or requests[id].status ~= "Help on the way" then return false end end; return true' -TimeoutSeconds 10
    }
}

Invoke-CRFlowStep 'all four cancel rescue; every peer clears all requests' {
    foreach ($client in $C) {
        if (-not (Invoke-CRFlow $client 'return CRCoop.GetComms().CancelRescue()')) { throw "c$client could not cancel rescue" }
    }
    foreach ($client in $C) { Wait-CRFlow $client 'return next(CRCoop.GetComms().GetRequests()) == nil' -TimeoutSeconds 10 | Out-Null }
    'all requests cleared'
}

Invoke-CRFlowStep 'four scheduled deaths use the Lemnos rally; positions agree on every peer' {
    # Arm all owners before the first death. The eight-second delay also lets
    # each registry observe the preceding individual handle changes.
    foreach ($client in $C) {
        Invoke-CRFlow $client @'
fourMortal = true
fourDeathLives = exu.GetLives()
fourDeathAt = GetTime() + 8
every('four-death', 0, function()
    if GetTime() < fourDeathAt then return end
    if exu.GetLives() < fourDeathLives then return true end
    if IsAlive(me()) then kill(me()) end
end)
return true
'@ | Out-Null
    }
    foreach ($client in $C) {
        Wait-CRFlow $client 'local s = CRCoop.GetRespawn().GetState(); return s.respawns >= 2 and s' -TimeoutSeconds $RespawnTimeout | Out-Null
    }
    foreach ($client in $C) {
        $state = Four-State $client
        if ($state.lastRespawn.how -ne 'rally' -or $state.respawns -ne 2 -or $state.livesLeft -ne 3) { throw "c$client did not use phase-2 fallback: $(ConvertTo-Json $state -Compress -Depth 5)" }
        Invoke-CRFlow $client 'fourMortal = false; return true' | Out-Null
        $subjectId = $ids[$client]
        foreach ($observer in $C) {
            Wait-CRFlow $observer "local p = CRCoop.GetPlayers()[$subjectId]; return p and IsValid(p.handle) and IsAlive(p.handle) and GetDistance(p.handle, M.lemnos) < 120 and { distance = GetDistance(p.handle, M.lemnos), pos = xyz(p.handle) }" -TimeoutSeconds 10
        }
    }
}

Invoke-CRFlowStep 'team 4 exhausts five lives; all four fail exactly once' {
    $deaths = @()
    for ($i = 0; $i -lt 3; $i++) { $deaths += Four-Die 3 }
    if (-not $deaths[-1].out -or $deaths[-1].respawns -ne 5) { throw 'team 4 did not fail at its fifth death' }
    foreach ($client in $C) { Wait-CRFlowOp $client FailMission -TimeoutSeconds 30 | Out-Null }
    $deaths
}
Test-CRFlowResultParity -Expect FailMission -Clients $C
