# CR co-op respawn placement and lives (misn03/misn05, with an override that has
# CRCoopRespawn). Native MultST respawns a player as a pilot at the team start
# location; CR moves the new handle near a settled living teammate, else the
# phase rally point, else the player's last safe position. CR counts lives
# (CRCoop.COOP_LIVES); a death with none left fails the mission for everyone.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Seconds to wait for the native respawn after a pilot death.
      [int]$RespawnTimeout = 45,
      # Key pressed while dead, in case the native respawn waits for input (0 = none).
      [int]$RespawnKeyVk = 0)
$script:RespawnKey = $RespawnKeyVk

$H, $G = $HostClient, $GuestClient
$script:CRFlowSkipParity = $true   # deaths and respawns are per-client by design

function Assert-That([bool]$Ok, [string]$Message, $State) {
    if (-not $Ok) { throw "$Message $(if ($null -ne $State) { ConvertTo-Json $State -Compress -Depth 6 })" }
}
function Respawn-State([int]$Client) {
    Invoke-CRFlow $Client 'local r = CRCoop.GetRespawn(); local s = r and r.GetState() or {}; s.me = describe(me()); s.out = CRCoop.IsOutOfLives(); return s'
}
# Kills this client's player until a new handle appears far away (a respawn).
function Kill-UntilRespawn([int]$Client) {
    $before = Respawn-State $Client
    $n0 = [int]$before.respawns
    # Native lives drop when the player (not just a craft) dies.
    $lives0 = Invoke-CRFlow $Client 'return exu.GetLives()'
    Invoke-CRFlow $Client 'local h = me(); kill(h); return true' | Out-Null
    $deadline = (Get-Date).AddSeconds($RespawnTimeout)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 700
        $s = Respawn-State $Client
        if ([int]$s.respawns -gt $n0 -or $s.out) { return $s }
        # Craft destroyed -> ejected pilot: kill that too, but only until a life
        # is lost; after that, the next pilot is the respawn and must live.
        $dead = Invoke-CRFlow $Client "return exu.GetLives() < $lives0"
        if (-not $dead) {
            Invoke-CRFlow $Client 'local h = me(); if IsAlive(h) and IsPerson(h) then kill(h) end; return true' | Out-Null
        } elseif ($script:RespawnKey) {
            Send-CRFlowKey $Client $script:RespawnKey -Focused
        }
    }
    throw "client $Client did not respawn within ${RespawnTimeout}s: $(ConvertTo-Json (Respawn-State $Client) -Compress -Depth 5)"
}

Invoke-CRFlowStep 'probes attached; respawn service on both clients' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowEvent $G attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlow $H 'return M.coopMissionStarted and role().ready' -TimeoutSeconds 120 | Out-Null
    foreach ($c in $H, $G) {
        $ok = Invoke-CRFlow $c 'return CRCoop.GetRespawn() ~= nil and CRCoop.COOP_LIVES'
        if (-not $ok) { throw "client $c has no CRCoopRespawn (regenerate the override)" }
    }
    @{ host = Respawn-State $H; guest = Respawn-State $G; lives = (Invoke-CRFlow $H 'return { cr = CRCoop.COOP_LIVES, native = exu.GetLives and exu.GetLives() }') }
}

Invoke-CRFlowStep 'keep the mission alive (test assist)' {
    Invoke-CRFlow $H @'
kill(M.wave1_1); kill(M.wave1_2)
every('protect', 1, function()
    for _, k in ipairs({ "solar1", "solar2", "solar3", "solar4", "launch", "avrecycler", "rescue1", "rescue2", "avrec", "lemnos" }) do
        if M[k] then heal(M[k]) end
    end
    clearAroundPlayers(5, nil, 500)
end)
every('selfheal', 1, function() if not hostMortal then heal(me()) end end)
return true
'@ | Out-Null
    'protect + clear near players + host selfheal'
}

if (Invoke-CRFlow $H 'return IsValid(M.lemnos)') {
    Invoke-CRFlowStep 'both native rally labels resolve on each client' {
        foreach ($client in $H, $G) {
            $labels = Invoke-CRFlow $client 'local start = GetHandle("avrecy-1_recycler"); local factory = GetHandle("oblema110_i76building"); return { valid = IsValid(start) and IsValid(factory), start = xyz(start), factory = xyz(factory) }'
            Assert-That $labels.valid 'persistent rally labels missing' $labels
            $labels
        }
    }
}

Invoke-CRFlowStep 'host moves far from the start; guest stays at spawn' {
    $spawn = Invoke-CRFlow $G 'return xyz(me())'
    # Move to the mission's far objective; host owns its own craft.
    Invoke-CRFlow $H 'return tp(M.launch or M.lemnos or "launch", 60)' | Out-Null
    Start-Sleep -Seconds 10   # the host's handle must be settled (8 s) to be a target
    $hostPos = Invoke-CRFlow $H 'return xyz(me())'
    $d = [math]::Sqrt([math]::Pow($hostPos[0] - $spawn[0], 2) + [math]::Pow($hostPos[2] - $spawn[2], 2))
    $script:respawnSpawn = $spawn
    if ($d -lt 300) { throw "host only ${d}m from the guest spawn; pick a farther target" }
    @{ guestSpawn = $spawn; host = $hostPos; distance = [math]::Round($d) }
}

Invoke-CRFlowStep 'guest dies -> respawns near the host (both clients agree)' {
    $s = Kill-UntilRespawn $G
    Assert-That ($s.lastRespawn.how -eq 'teammate') 'guest did not respawn near the teammate' $s
    Start-Sleep -Seconds 2
    $hostPos = Invoke-CRFlow $H 'return xyz(me())'
    $guestPos = Invoke-CRFlow $G 'return xyz(me())'
    $dist = [math]::Sqrt([math]::Pow($hostPos[0] - $guestPos[0], 2) + [math]::Pow($hostPos[2] - $guestPos[2], 2))
    # What the host sees of the guest's new handle (replication of the move).
    $seen = Invoke-CRFlow $H 'for id, p in pairs(CRCoop.GetPlayers()) do if p.team ~= 1 and p.handle and IsValid(p.handle) then local q = GetPosition(p.handle); return { q.x, q.y, q.z } end end'
    $seenDist = if ($seen) { [math]::Sqrt([math]::Pow($hostPos[0] - $seen[0], 2) + [math]::Pow($hostPos[2] - $seen[2], 2)) } else { $null }
    Assert-That ($dist -lt 120) "guest is ${dist}m from the host" $s
    Assert-That ($null -ne $seenDist -and $seenDist -lt 120) "host sees the guest ${seenDist}m away" @{ seen = $seen }
    $msgs = Invoke-CRFlow $G 'return describe(me())'
    @{ state = $s; guestToHostM = [math]::Round($dist); hostSeesGuestM = [math]::Round($seenDist); guest = $msgs }
}

Invoke-CRFlowStep 'both die together -> guest uses its own fallback, not the respawning host' {
    Start-Sleep -Seconds 20   # let the guest's safe samples build up at its new spot
    Invoke-CRFlow $H 'hostMortal = true; return true' | Out-Null
    $job = Kill-UntilRespawn $H
    $s = Kill-UntilRespawn $G
    Invoke-CRFlow $H 'hostMortal = false; return true' | Out-Null
    Assert-That ($s.lastRespawn.how -ne 'teammate') 'guest followed the host, who had just respawned' $s
    @{ host = $job; guest = $s }
} -Soft

if (Invoke-CRFlow $H 'return IsValid(M.lemnos)') {
    Invoke-CRFlowStep 'phase 2 fallback actually lands near Lemnos on both clients' {
        $rally = Invoke-CRFlow $G 'return { how = CRCoop.GetRespawn().lastRespawn.how, phase = CRCoop.GetMissionPhase(), distance = GetDistance(me(), M.lemnos), pos = xyz(me()) }'
        Assert-That ($rally.how -eq 'rally' -and $rally.phase -eq 2 -and $rally.distance -lt 120) 'guest missed the Lemnos rally point' $rally
        $seenRally = Invoke-CRFlow $H 'for id, p in pairs(CRCoop.GetPlayers()) do if p.team ~= 1 and IsValid(p.handle) then return GetDistance(p.handle, M.lemnos) end end'
        Assert-That ($null -ne $seenRally -and $seenRally -lt 120) 'host sees the guest outside the Lemnos rally' @{ distance = $seenRally }
        @{ guest = $rally; hostSeesDistance = $seenRally }
    }
}

Invoke-CRFlowStep 'guest uses up its lives -> mission fails on both clients' {
    $deaths = @()
    for ($i = 0; $i -lt 8; $i++) {
        $s = Kill-UntilRespawn $G
        $deaths += @{ how = $s.lastRespawn.how; left = $s.livesLeft; out = $s.out }
        if ($s.out) { break }
    }
    Assert-That ([bool]$s.out) 'guest never ran out of lives' $deaths
    $a = Wait-CRFlowOp $H FailMission -TimeoutSeconds 30
    $b = Wait-CRFlowOp $G FailMission -TimeoutSeconds 30
    @{ deaths = $deaths; hostFail = $a.t; guestFail = $b.t }
}
