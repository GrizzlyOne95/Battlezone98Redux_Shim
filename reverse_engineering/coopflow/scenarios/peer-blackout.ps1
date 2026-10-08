# One player's network goes dark mid-mission, then comes back. The relay drops
# every datagram to and from the subject for -BlackoutSeconds (the server's
# relay impairment, so the run needs a server with POST /relay/impairment).
# The other players must keep exchanging comms throughout, and once the link
# returns every client must reach every other again within -RecoverySeconds.
# A subject the game drops instead is a finding, reported as a failed step.
#
#   Run-BZRCoopMission.ps1 -Mission misn05 -Scenario peer-blackout -Clients 4 `
#       -ContentOverride coopflow\overrides\misn05-coop -ScenarioArgs @{ BlackoutSeconds = 20 }
param([int]$Subject = 3, [int]$BlackoutSeconds = 20, [int]$RecoverySeconds = 60)
$C = @(Get-CRFlowClientIndices)
if ($C.Count -lt 3) { throw 'peer-blackout needs at least three clients' }
if ($Subject -notin $C -or $Subject -eq 0) { throw "subject c$Subject must be a guest client" }
$others = @($C | Where-Object { $_ -ne $Subject })
# The subject misses presentation ops while it is dark.
$script:CRFlowSkipParity = $true
$ids = @{}

# Every listed receiver sees this round's terrain ping from every listed
# sender. Pings keep the latest per sender, so each round stamps a fresh
# nonce into the ping height and receivers wait for exactly that value.
$script:BlackoutNonce = 5000
function Blackout-Pings([int[]]$Senders, [int[]]$Receivers, [int]$TimeoutSeconds) {
    $script:BlackoutNonce++
    $nonce = $script:BlackoutNonce
    foreach ($client in $Senders) {
        $send = "local p = GetPosition(me()); p.x = p.x + role().team * 10; p.y = $nonce; return CRCoop.GetComms().SendPing('terrain', nil, p)"
        $ok = Invoke-CRFlow $client $send
        if (-not $ok) { Start-Sleep -Milliseconds 1600; $ok = Invoke-CRFlow $client $send }  # 1.5 s ping cooldown
        if (-not $ok) { throw "c$client could not publish a terrain ping" }
    }
    $senderIds = ($Senders | ForEach-Object { $ids[$_] }) -join ', '
    $clock = [Diagnostics.Stopwatch]::StartNew()
    foreach ($client in $Receivers) {
        Wait-CRFlow $client "local pings = CRCoop.GetComms().GetPings(); for _, id in ipairs({ $senderIds }) do local p = pings[id]; if not p or p.kind ~= 'terrain' or not p.position or math.abs(p.position.y - $nonce) > 0.01 then return false end end; return true" -TimeoutSeconds $TimeoutSeconds | Out-Null
    }
    [math]::Round($clock.Elapsed.TotalSeconds, 1)
}

Invoke-CRFlowStep 'protect objectives and every player' {
    Wait-CRFlow 0 'return M.game_start' -TimeoutSeconds 90 | Out-Null
    Invoke-CRFlow 0 "every('protect', 0.5, function() heal(M.avrec); heal(M.lemnos); clearAroundPlayers(5, nil, 500) end); return true" | Out-Null
    foreach ($client in $C) {
        $ids[$client] = (Invoke-CRFlow $client 'return role()').playerId
        Invoke-CRFlow $client "every('selfheal', 0.5, function() heal(me()) end); return true" | Out-Null
    }
    @($C | ForEach-Object { @{ client = $_; playerId = $ids[$_] } })
}

Invoke-CRFlowStep 'baseline: pings from every sender reach every client' {
    "all-to-all in $(Blackout-Pings $C $C 15) s"
}

$name = @((Get-CRFlowSession).clients | Where-Object { $_.index -eq $Subject })[0].authenticatedAs
if (-not $name) { throw "no BZRNet name for c$Subject" }

Invoke-CRFlowStep "c$Subject goes dark for $BlackoutSeconds s; the others keep talking" {
    $before = Set-CRFlowImpairment "loss=100,peer=$name,for=$BlackoutSeconds"
    $started = [Diagnostics.Stopwatch]::StartNew()
    $exchanges = @()
    while ($started.Elapsed.TotalSeconds -lt $BlackoutSeconds - 5) {
        $exchanges += Blackout-Pings $others $others 10
        Start-Sleep -Seconds 2
    }
    $state = Invoke-RestMethod -Uri "$($script:CRFlowHealthUrl)/relay/impairment" -TimeoutSec 5
    if (-not $state.impairment.dropped_loss) { throw "the blackout dropped nothing; peer=$name matched no stream" }
    # Let the impairment expire on its own.
    while ($started.Elapsed.TotalSeconds -lt $BlackoutSeconds + 1) { Start-Sleep -Milliseconds 500 }
    @{ subject = $name; othersExchangeS = $exchanges; dropped = $state.impairment.dropped_loss }
}

Invoke-CRFlowStep "c$Subject is back: pings from every sender reach every client" {
    $clock = [Diagnostics.Stopwatch]::StartNew()
    $last = $null
    while ($true) {
        try { $s = Blackout-Pings $C $C 10; break }
        catch { $last = $_.Exception.Message }
        if ($clock.Elapsed.TotalSeconds -ge $RecoverySeconds) { throw "no all-to-all exchange ${RecoverySeconds}s after the blackout: $last" }
    }
    "recovered after $([math]::Round($clock.Elapsed.TotalSeconds, 1)) s (last exchange $s s)"
}

Invoke-CRFlowStep 'the game kept every player' {
    foreach ($client in $C) {
        $n = Invoke-CRFlow $client 'local n = 0; for _ in pairs(CRCoop.GetPlayers()) do n = n + 1 end; return n'
        if ($n -ne $C.Count) { throw "c$client lists $n players, not $($C.Count)" }
    }
    "$($C.Count) players on every client"
}
