# Minimal co-op smoke for any CR co-op mission (used for misn07 and misn08):
# load, reach gameplay, every peer alive and on the roster, a stretch of play,
# host/guest presentation parity (the runner checks it after the scenario),
# no unresolved co-op labels (the runner's log check) and a clean exit. It does
# not script a win.
#
# -Aip (misn08): after the smoke, force the story beat that hands team 5 its
# strategic AI (M.bad_news; the mission then runs SetAIP("misn08.aip", 5) with
# scrap and pilots) and watch the host for team-5 growth: new team-5 units and
# factory production. The Colorado massacre chain that sets bad_news on its own
# takes far longer than a smoke run, so this is a test assist, recorded as such.
param([int]$HostClient = 0,
      # Seconds of play to observe after readiness.
      [int]$PlaySeconds = 45,
      [switch]$Aip,
      # How long to watch team 5 after forcing the AIP beat.
      [int]$AipWatchSeconds = 240)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })

Invoke-CRFlowStep 'probes attached; host has authority, guests do not' {
    foreach ($client in $C) {
        $attached = Wait-CRFlowEvent $client attach -TimeoutSeconds 120
        if (-not $attached.bzfile) { throw "bzfile missing on c$client; no command channel" }
    }
    $hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    if (-not $hr.authority) { throw 'host has no authority' }
    foreach ($client in $guests) {
        $gr = Wait-CRFlow $client 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
        if ($gr.authority) { throw "guest c$client has authority" }
    }
    @{ host = $hr }
}

Invoke-CRFlowStep 'session ready and mission running on every client' {
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 90 | Out-Null }
    'coopMissionStarted on all'
}

Invoke-CRFlowStep "$PlaySeconds s of play; every peer alive with a craft, full roster everywhere" {
    Start-Sleep -Seconds $PlaySeconds
    $rows = @()
    foreach ($client in $C) {
        $s = Invoke-CRFlow $client 'local me = me(); local d = describe(me); return { alive = d.alive, valid = d.valid, odf = d.odf, team = d.team, players = #players(), result = M.coopResult == true, departed = role().leaderDeparted == true }'
        $rows += @{ client = $client; state = $s }
        Add-CRFlowCheck "c$client alive with its own craft, no early result" ($s.valid -and $s.alive -and -not $s.result -and -not $s.departed) $s
        Add-CRFlowCheck "c$client sees all $($C.Count) players" ($s.players -eq $C.Count) $s
    }
    $rows
}

if ($Aip) {
    Invoke-CRFlowStep 'team-5 AIP: force the story beat; watch for new team-5 units and production' -Soft {
        $count = 'local n, odfs = 0, {}; for h in AllObjects() do if IsValid(h) and GetTeamNum(h) == 5 then n = n + 1; local o = GetOdf(h) or "?"; odfs[o] = (odfs[o] or 0) + 1 end end; return { n = n, odfs = odfs, scrap = GetScrap(5), pilots = GetPilot(5), t = GetTime() }'
        $before = Invoke-CRFlow $H $count
        $forced = Invoke-CRFlow $H 'if M.ccarecycle_spawned then return "already spawned" end; M.bad_news = true; return "bad_news forced"'
        $samples = @($before)
        $deadline = (Get-Date).AddSeconds($AipWatchSeconds)
        $peak = $before.n
        while ((Get-Date) -lt $deadline) {
            Start-Sleep -Seconds 20
            $now = Invoke-CRFlow $H $count
            $samples += $now
            if ($now.n -gt $peak) { $peak = $now.n }
        }
        $after = $samples[-1]
        $spawned = Invoke-CRFlow $H 'return { recycler = M.ccarecycle_spawned == true, badNews = M.bad_news == true }'
        $grew = $after.n -gt $before.n
        Add-CRFlowCheck "team 5 grew under the AIP ($($before.n) -> $($after.n) objects, peak $peak)" $grew @{ forced = $forced; spawned = $spawned; before = $before; after = $after } -WarnOnly
        Write-Host ("[aip] {0}; team-5 objects {1} -> {2}, scrap {3} -> {4}" -f $forced, $before.n, $after.n, $before.scrap, $after.scrap)
        @{ forced = $forced; spawned = $spawned; samples = $samples }
    }
}
