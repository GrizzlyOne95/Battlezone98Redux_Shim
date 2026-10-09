# Four real owners exercise all-to-all comms, handle changes, simultaneous
# fallback, and a team-4 out-of-lives failure. Never mutate a remote craft.
param([int]$RespawnTimeout = 45, [switch]$AlignFallbackOutage)
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

Invoke-CRFlowStep 'shared-deadline deaths diagnose Lemnos fallback on every peer' {
    $diag = [ordered]@{ method='All owners acknowledge one absolute simulation deadline before release; candidate snapshots bracket service.Update. Observed handle age is not private eligibility age.'; arms=@(); releases=@(); clients=@() }
    $helper = Join-Path $PSScriptRoot '..\battleload\four_respawn_diagnostic.lua'
    try {
        foreach ($client in $C) { Invoke-CRFlow $client ([IO.File]::ReadAllText($helper)) | Out-Null }
        $deathAt = [double](Invoke-CRFlow 0 'return GetTime()') + 15
        $literal = $deathAt.ToString('F4', [Globalization.CultureInfo]::InvariantCulture)
        foreach ($client in $C) {
            $ack = Invoke-CRFlow $client "fourMortal = true; every('four-death', 0, function() return fourDiag.KillTick() end); return fourDiag.Arm($literal)"
            if (-not $ack.armed -or [math]::Abs($ack.deadline - $deathAt) -gt 0.001) { throw "c$client did not acknowledge common death deadline" }
            $diag.arms += @{client=$client; at=(Get-Date).ToUniversalTime().ToString('o'); ack=$ack}
        }
        if ($AlignFallbackOutage) {
            # Start a new documented generation only after all owners are held.
            # Its first outage begins 19 wall seconds later. Schedule near its
            # midpoint; recorded packet times and actual kills verify overlap.
            $response = Set-CRFlowImpairment 'outage=1000/20000,seed=13'
            $deathAt = [double](Invoke-CRFlow 0 'return GetTime()') + 19.25
            $literal = $deathAt.ToString('F4', [Globalization.CultureInfo]::InvariantCulture)
            $diag['outageAlignment'] = @{at=(Get-Date).ToUniversalTime().ToString('o');response=$response;deadline=$deathAt;acks=@()}
            foreach ($client in $C) {
                $ack = Invoke-CRFlow $client "return fourDiag.Reschedule($literal)"
                if (-not $ack.armed -or [math]::Abs($ack.deadline - $deathAt) -gt 0.001) { throw "c$client did not acknowledge aligned deadline" }
                $diag.outageAlignment.acks += @{client=$client; at=(Get-Date).ToUniversalTime().ToString('o');ack=$ack}
            }
        }
        foreach ($client in $C) {
            $ack = Invoke-CRFlow $client 'return fourDiag.Release()'
            if (-not $ack.released) { throw "c$client did not acknowledge release" }
            $diag.releases += @{client=$client; at=(Get-Date).ToUniversalTime().ToString('o'); ack=$ack}
        }
        foreach ($client in $C) {
            Wait-CRFlow $client 'local s = CRCoop.GetRespawn().GetState(); return s.respawns >= 2 and s' -TimeoutSeconds $RespawnTimeout | Out-Null
        }
        foreach ($client in $C) {
            $state = Four-State $client
            if ($state.lastRespawn.how -ne 'rally' -or $state.respawns -ne 2 -or $state.livesLeft -ne 3) { throw "c$client did not use phase-2 fallback: $(ConvertTo-Json $state -Compress -Depth 5)" }
            $subjectId = $ids[$client]
            foreach ($observer in $C) {
                Wait-CRFlow $observer "local p = CRCoop.GetPlayers()[$subjectId]; return p and IsValid(p.handle) and IsAlive(p.handle) and GetDistance(p.handle, M.lemnos) < 120 and { distance = GetDistance(p.handle, M.lemnos), pos = xyz(p.handle) }" -TimeoutSeconds 10 | Out-Null
            }
        }
    } finally {
        foreach ($client in $C) {
            try {
                Invoke-CRFlow $client "cancel('four-death'); fourMortal = false; if fourDiag then return fourDiag.Stop() end; return false" -TimeoutSeconds 3 | Out-Null
                $metadata = Invoke-CRFlow $client 'return fourDiag and fourDiag.Metadata()' -TimeoutSeconds 3
                $rows = @{client=$client; metadata=$metadata; samples=@(); events=@(); observerErrors=@()}
                if ($metadata) {
                    foreach ($kind in @('samples','events','observerErrors')) {
                        for ($begin=1; $begin -le $metadata.$kind; $begin+=16) {
                            $rows[$kind] += @(Invoke-CRFlow $client "return fourDiag.Page('$kind', $begin)" -TimeoutSeconds 3)
                        }
                    }
                }
                $diag.clients += $rows
            } catch { $diag.clients += @{client=$client; error=$_.Exception.Message} }
        }
        $diag | ConvertTo-Json -Depth 16 | Set-Content -LiteralPath (Join-Path $script:CRFlowRun.runDir 'fallback-respawn-diagnostic.json')
        $owners = @($diag.clients | Where-Object { $_.metadata })
        $badObservers = @($diag.clients | Where-Object { $_.error -or -not $_.metadata -or $_.metadata.observerErrors -gt 0 -or $_.metadata.errorDropped -gt 0 -or $_.metadata.eventDropped -gt 0 })
        Add-CRFlowCheck 'respawn diagnostic retains all owner transitions without observer errors' ($owners.Count -eq 4 -and $badObservers.Count -eq 0) $diag.clients
        $killTimes = @($owners | ForEach-Object { $_.metadata.firstKillAt } | Where-Object { $null -ne $_ })
        $lostLives = @($owners | Where-Object { $null -ne $_.metadata.lifeLostAt })
        $spread = if ($killTimes.Count -eq 4) { ($killTimes | Measure-Object -Maximum).Maximum - ($killTimes | Measure-Object -Minimum).Minimum } else { $null }
        $lateKills = @($owners | Where-Object { $null -eq $_.metadata.firstKillAt -or $_.metadata.firstKillAt -lt $_.metadata.deadline -or $_.metadata.firstKillAt -gt $_.metadata.deadline + 0.25 })
        Add-CRFlowCheck 'all four owners die at the common deadline with native life decrements' ($killTimes.Count -eq 4 -and $lostLives.Count -eq 4 -and $lateKills.Count -eq 0 -and $spread -le 0.25) @{spreadSeconds=$spread;owners=$owners}
    }
    $diag.arms
}

Invoke-CRFlowStep 'team 4 exhausts five lives; all four fail exactly once' {
    $deaths = @()
    for ($i = 0; $i -lt 3; $i++) { $deaths += Four-Die 3 }
    if (-not $deaths[-1].out -or $deaths[-1].respawns -ne 5) { throw 'team 4 did not fail at its fifth death' }
    foreach ($client in $C) { Wait-CRFlowOp $client FailMission -TimeoutSeconds 30 | Out-Null }
    $deaths
}
Test-CRFlowResultParity -Expect FailMission -Clients $C
