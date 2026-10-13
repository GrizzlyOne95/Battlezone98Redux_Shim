# Mission 06 "Escape from Mars" co-op, four players (also runs with two or three):
# start, ownership and alliances, per-owner starting scrap, the opening and
# Hephaestus path films (with a local skip on one guest), any-player
# discovery, guest-relayed IsInfo scans, the object-camera and 5th Platoon
# films, the launch pad scan, and the dust-off gate (Wyoming AND every player
# within 100 m), ending in the win on every client.
#
# Assists are owner-local, as in misn05-win: heal, teleport own craft, and
# edits of the leader's mission timers. The IsInfo scans are forced inside the
# GUEST's native-IsInfo wrapper (forceInfo), so the mission's own relay, "I"
# wire message and one-second expiry all run unmodified. Real selection of a
# map object is not scriptable; that is the one thing this scenario fakes.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Who skips the Hephaestus film (a local skip must not end anyone else's).
      [ValidateSet('guest','host','none')][string]$Skipper = 'guest',
      [switch]$FocusedSkip)
$H, $G = $HostClient, $GuestClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
# Distinct guests for the three starport scans and the launch pad scan (cycled
# when fewer guests exist), so the relay is exercised from several peers.
$roleOrder = @($G) + @($guests | Where-Object { $_ -ne $G })
function Get-GuestFor([int]$Index) { $roleOrder[$Index % $roleOrder.Count] }
$inv = [Globalization.CultureInfo]::InvariantCulture
function Move-ClientNear([int]$Client, $Xyz, [double]$Dist) {
    # Owner-local teleport of this client's own craft near a world position.
    $lua = 'local p = GetPositionNear(at({0}, {1}, {2}), {3}, {4}); SetPosition(me(), p); return describe(me())' -f `
        $Xyz[0].ToString($inv), $Xyz[1].ToString($inv), $Xyz[2].ToString($inv), $Dist.ToString($inv), ($Dist + 10).ToString($inv)
    Invoke-CRFlow $Client $lua | Out-Null
}
function Get-HostOps([string]$Op) { @(Get-CRFlowEvents $H op | Where-Object { $_.op -eq $Op }) }
function Assert-NoResult([string]$Why, [int]$Seconds = 6) {
    Start-Sleep -Seconds $Seconds
    $state = Invoke-CRFlow $H 'return { reached = M.pickupreached, dustoff = M.dustoff, pending = M.coopPendingResult ~= nil, result = M.coopResult == true }'
    if (-not $state.reached -or $state.dustoff -or $state.pending -or $state.result) { throw "${Why}: the mission ended early: $(ConvertTo-Json $state -Compress)" }
    foreach ($client in $C) {
        $r = @(Get-CRFlowEvents $client op | Where-Object { $_.op -in 'SucceedMission', 'FailMission' })
        if ($r.Count) { throw "${Why}: c$client already received $($r[0].op)" }
    }
    $state
}

Invoke-CRFlowStep 'probes, readiness and campaign authority' {
    foreach ($client in $C) {
        Wait-CRFlowEvent $client attach -TimeoutSeconds 120 | Out-Null
        Wait-CRFlow $client 'return role().ready' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.coopBootstrapped and M.missionstart == false' -TimeoutSeconds 90 | Out-Null
    $hostRole = Invoke-CRFlow $H 'return role()'
    if (-not $hostRole.authority) { throw 'host is not the campaign authority' }
    foreach ($client in $guests) {
        $r = Invoke-CRFlow $client 'return role()'
        if ($r.authority -or $r.team -eq $hostRole.team) { throw "c$client role incorrect: $(ConvertTo-Json $r -Compress)" }
    }
    @{ host = $hostRole }
}

Invoke-CRFlowStep 'host-only mission body; teams, alliances and mission objects' {
    # Guests return before the Execute body: its first-frame block never runs there.
    foreach ($client in $guests) {
        $g = Invoke-CRFlow $client 'return { missionstart = M.missionstart, heph = M.haephestus ~= nil, avrec = M.avrec ~= nil, player = M.player ~= nil }'
        if (-not $g.missionstart -or $g.heph -or $g.avrec -or $g.player) { throw "guest c$client ran authoritative mission startup: $(ConvertTo-Json $g -Compress)" }
    }
    $n = $C.Count
    foreach ($client in $C) {
        $bad = Invoke-CRFlow $client @"
local bad = {}
for t = 1, $n do
    if not (IsTeamAllied(t, 7) and IsTeamAllied(7, t)) then bad[#bad + 1] = 'team ' .. t .. ' not allied with support team 7' end
    if IsTeamAllied(t, 5) or IsTeamAllied(5, t) then bad[#bad + 1] = 'team ' .. t .. ' allied with CCA team 5' end
end
if IsTeamAllied(5, 7) or IsTeamAllied(7, 5) then bad[#bad + 1] = 'CCA team 5 allied with support team 7' end
return table.concat(bad, '; ')
"@
        Add-CRFlowCheck "c$client alliances: humans+support 7 allied, CCA 5 hostile to both" ([string]::IsNullOrEmpty($bad)) $bad
    }
    $world = Invoke-CRFlow $H @'
local cca, support = 0, 0
for h in AllObjects() do
    if IsValid(h) then
        local t = GetTeamNum(h)
        if t == 5 then cca = cca + 1 elseif t == 7 then support = support + 1 end
    end
end
local offline = GetHandle("player0_hover")
return {
    cca = cca, support = support,
    avrecTeam = GetTeamNum(M.avrec), avrecOdf = GetOdf(M.avrec), svrecTeam = GetTeamNum(M.svrec),
    filmTeam = IsValid(M.p5u3) and GetTeamNum(M.p5u3) or nil,
    hephOdf = GetOdf(M.haephestus), launchpadOdf = GetOdf(M.launchpad), extractpoint = M.extractpoint,
    offlinePlaceholder = IsValid(offline) and not CRCoop.IsHumanCraft(offline),
}
'@
    Add-CRFlowCheck 'Wyoming on team 1; CCA recycler on team 5; many CCA objects' ($world.avrecTeam -eq 1 -and $world.svrecTeam -eq 5 -and $world.cca -ge 20) $world
    Add-CRFlowCheck '5th Platoon film units on support team 7' ($world.filmTeam -eq 7) $world
    Add-CRFlowCheck 'offline placeholder craft removed' (-not $world.offlinePlaceholder) $world
    $world
}

Invoke-CRFlowStep 'starting scrap applied by each owner to its own team' {
    $rows = @()
    foreach ($client in $C) {
        $row = Wait-CRFlow $client 'local t = role().team; return GetScrap(t) == 5 and { team = t, scrap = GetScrap(t), maxScrap = GetMaxScrap(t), pilots = GetPilot(t), maxPilots = GetMaxPilot(t) }' -TimeoutSeconds 30
        if ($row.maxScrap -lt 5) { throw "c$client scrap capacity not reserved: $(ConvertTo-Json $row -Compress)" }
        $rows += $row
    }
    $leaderPilots = Invoke-CRFlow $H 'return GetPilot(1)'
    Add-CRFlowCheck 'every owner starts with the authored 5 scrap and the leader pilot count' (@($rows | Where-Object { $_.pilots -ne $leaderPilots }).Count -eq 0) $rows -WarnOnly
    $rows
}

Invoke-CRFlowStep 'opening path film shown on every client; a local skip does not touch the others' {
    foreach ($client in $C) { Wait-CRFlowOp $client CameraReady -TimeoutSeconds 60 | Out-Null }
    foreach ($client in $C) {
        Wait-CRFlowOp $client CameraPath 'openingcampath' -TimeoutSeconds 30 | Out-Null
    }
    $film = Invoke-CRFlow $H 'return { done = M.opencamdone, remaining = M.opencamtime - GetTime() }'
    $detail = @{ film = $film }
    # The film is 28 s from the first mission frame and clients load unevenly:
    # skip only when enough of it is left to observe, and say so otherwise.
    $skipper = Get-GuestFor 0
    if ($film.done -and $film.remaining -gt 8) {
        Send-CRFlowKey $skipper 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
        Start-Sleep -Milliseconds 300
        Send-CRFlowKey $skipper 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
        Wait-CRFlow $skipper 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 6 | Out-Null
        $others = @()
        foreach ($client in ($C | Where-Object { $_ -ne $skipper })) {
            $l = Invoke-CRFlow $client 'return L().localCameraActive'
            $others += @{ client = $client; active = $l }
        }
        $hostFilming = Invoke-CRFlow $H 'return M.opencamdone'
        $stillFilming = @($others | Where-Object { -not $_.active })
        if (-not $hostFilming -or ($stillFilming.Count -and $film.remaining -gt 14)) { throw "the opening film ended for others after c$skipper skipped: $(ConvertTo-Json @{host=$hostFilming; others=$others} -Compress)" }
        $detail.skipped = $skipper
        $detail.others = $others
    } else {
        $detail.skipped = 'film had too little time left; the Hephaestus film carries the skip check'
    }
    Wait-CRFlow $H 'return not M.opencamdone' -TimeoutSeconds 40 | Out-Null
    foreach ($client in $C) { Wait-CRFlow $client 'return not L().localCameraActive' -TimeoutSeconds 10 | Out-Null }
    $detail
}

Invoke-CRFlowStep 'protect mission objects and players (test assist)' {
    Invoke-CRFlow $H "every('protect', 0.5, function() heal(M.avrec) end); return true" | Out-Null
    foreach ($client in $C) { Invoke-CRFlow $client "every('selfheal', 0.5, function() heal(me()) end); return true" | Out-Null }
    # The CCA reinforcement waves attack Wyoming minutes later and are not what
    # this flow qualifies; push them out of the way.
    Invoke-CRFlow $H 'M.wave1 = GetTime() + 99999; M.wave2 = GetTime() + 99999; M.wave3 = GetTime() + 99999; return true' | Out-Null
    'owner-local heal only; CCA waves deferred'
}

Invoke-CRFlowStep "c$G (not the leader) discovers Hephaestus; the leader hears it" {
    $before = Invoke-CRFlow $H 'return { disc = M.haephestusdisc, hostDist = GetDistance(me(), M.haephestus) }'
    # M is not populated on guests: resolve the building by its authored label.
    Invoke-CRFlow $G 'local h = GetHandle("obheph0_i76building"); return put(me(), h, 600)' | Out-Null
    $state = Wait-CRFlow $H 'return M.haephestusdisc and { disc = true, aud = M.aud1 ~= nil }' -TimeoutSeconds 15
    foreach ($client in $guests) { Wait-CRFlowOp $client Play 'misn0602.wav' -TimeoutSeconds 20 | Out-Null }
    Add-CRFlowCheck 'Hephaestus discovery by a guest alone (leader started out of range)' ((-not $before.disc) -and $before.hostDist -gt 1000) @{ before = $before } -WarnOnly
    @{ before = $before; after = $state }
}

Invoke-CRFlowStep 'guest comes within 125 m; the Hephaestus film runs on every client' {
    Invoke-CRFlow $G 'local h = GetHandle("obheph0_i76building"); return put(me(), h, 90)' | Out-Null
    Wait-CRFlow $H 'return M.reconheaphestus and M.cam1done and L().localCameraActive' -TimeoutSeconds 15 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return L().localCameraActive' -TimeoutSeconds 10 | Out-Null }
    foreach ($client in $C) { Wait-CRFlowOp $client CameraPath 'cam1path' -TimeoutSeconds 10 | Out-Null }
    foreach ($client in $guests) {
        $p = Wait-CRFlow $client 'return L().remotePath' -TimeoutSeconds 8
        if ($p -ne 'cam1path') { throw "c$client follows $p, not cam1path" }
    }
    @{ host = Invoke-CRFlow $H 'return L()' }
}

Invoke-CRFlowStep 'Hephaestus scan relayed from a guest: leader honours it, then it expires' {
    # A guest "selects" the building: its own wrapper reports it, the leader
    # sets hephikey from the wire message, and stops honouring it a second after
    # the guest stops reporting.
    $lead = Invoke-CRFlow $H 'return isInfo("obheph")'
    if ($lead) { throw 'leader reports obheph before any guest relay' }
    Invoke-CRFlow $G 'return forceInfo("obheph", true)' | Out-Null
    Wait-CRFlow $H 'return M.hephikey' -TimeoutSeconds 10 | Out-Null
    $age = Invoke-CRFlow $H 'return L().infoReportAges'
    Invoke-CRFlow $G 'return forceInfo("obheph", false)' | Out-Null
    Start-Sleep -Milliseconds 1800
    $expired = -not (Invoke-CRFlow $H 'return isInfo("obheph")')
    Add-CRFlowCheck 'guest IsInfo report expires on the leader about a second after the guest stops' $expired @{ ages = $age }
    foreach ($client in $guests) { Wait-CRFlowOp $client SetObjectiveOff -TimeoutSeconds 10 | Out-Null }
    @{ reportAges = $age }
}

Invoke-CRFlowStep 'a local skip on one peer leaves the shared Hephaestus film running' {
    if ($Skipper -eq 'none') { return 'nobody skips' }
    $skipClient = if ($Skipper -eq 'host') { $H } else { $G }
    Send-CRFlowKey $skipClient 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
    Start-Sleep -Milliseconds 300
    Send-CRFlowKey $skipClient 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
    Wait-CRFlow $skipClient 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 6 | Out-Null
    $watching = @()
    $filming = Invoke-CRFlow $H 'return M.cam1done'
    foreach ($client in ($C | Where-Object { $_ -ne $skipClient })) {
        $active = Invoke-CRFlow $client 'return L().localCameraActive'
        if (-not $filming -or -not $active) { throw "shared film ended on c$client after c$skipClient skipped" }
        $watching += @{ client = $client; active = $active }
    }
    @{ skipper = $skipClient; watchers = $watching; hostFilming = $filming }
}

Invoke-CRFlowStep 'Hephaestus film releases everywhere; new orders and the Starport camera' {
    Wait-CRFlow $H 'return not M.cam1done' -TimeoutSeconds 60 | Out-Null
    foreach ($client in $C) { Wait-CRFlow $client 'return not L().localCameraActive' -TimeoutSeconds 10 | Out-Null }
    Wait-CRFlow $H 'return M.neworders' -TimeoutSeconds 90 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client AddObjective 'misn0603.otf' -TimeoutSeconds 30 | Out-Null }
    Wait-CRFlow $H 'return M.starportcam ~= nil and not M.buildcam' -TimeoutSeconds 60 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SetObjectiveName 'Starport' -TimeoutSeconds 20 | Out-Null }
    'all released; misn0603.otf and Starport reached the guests'
}

Invoke-CRFlowStep "c$(Get-GuestFor 1) discovers the starport; three guests scan its structures" {
    $star8 = Invoke-CRFlow $H 'return xyz(M.star8)'
    Move-ClientNear (Get-GuestFor 1) $star8 120
    Wait-CRFlow $H 'return M.starportdisc' -TimeoutSeconds 15 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client Play 'misn0608.wav' -TimeoutSeconds 20 | Out-Null }
    $scans = @(@{ prefix = 'obstp1'; flag = 'star1recon'; who = (Get-GuestFor 0) },
               @{ prefix = 'obstp8'; flag = 'star4recon'; who = (Get-GuestFor 1) },
               @{ prefix = 'obstp3'; flag = 'star6recon'; who = (Get-GuestFor 2) })
    $done = @()
    foreach ($scan in $scans) {
        $already = Invoke-CRFlow $H "return M.$($scan.flag)"
        if ($already) { throw "$($scan.flag) was set before any guest scanned $($scan.prefix)" }
        Invoke-CRFlow $scan.who "return forceInfo('$($scan.prefix)', true)" | Out-Null
        Wait-CRFlow $H "return M.$($scan.flag)" -TimeoutSeconds 10 | Out-Null
        Invoke-CRFlow $scan.who "return forceInfo('$($scan.prefix)', false)" | Out-Null
        $done += "$($scan.prefix) from c$($scan.who)"
    }
    Wait-CRFlow $H 'return M.starportreconed' -TimeoutSeconds 10 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client Play 'misn0650.wav' -TimeoutSeconds 20 | Out-Null }
    $done
}

Invoke-CRFlowStep 'CCA escort fighters head for the nearest player; object-camera film on every client' -Soft {
    Wait-CRFlow $H 'return M.ccaattack' -TimeoutSeconds 15 | Out-Null
    $played = Invoke-CRFlow $H 'return M.loopbreak1'
    if ($played) { return 'the escort film already played on its own (an escort reached the camera first)' }
    # The film fires when an escort reaches the starport camera and the three
    # starport voice lines are done. Bring one escort to the camera.
    Invoke-CRFlow $H 'M.start1 = GetTime() - 1; return true' | Out-Null
    Wait-CRFlow $H 'return M.aud5 == nil or IsAudioMessageDone(M.aud5)' -TimeoutSeconds 60 | Out-Null
    Invoke-CRFlow $H 'return put(M.wAu1, M.starportcam, 150)' | Out-Null
    Wait-CRFlow $H 'return M.cam3done and L().localCameraActive' -TimeoutSeconds 15 | Out-Null
    $seen = @()
    foreach ($client in $guests) { $seen += @{ client = $client; active = (Wait-CRFlow $client 'return L().localCameraActive' -TimeoutSeconds 6) } }
    $seen
}

Invoke-CRFlowStep 'both escorts destroyed; transport arrives and the launch pad timer starts everywhere' {
    # Film (if any) must be over before the escorts go: it follows an escort.
    Wait-CRFlow $H 'return not M.cam3done' -TimeoutSeconds 40 | Out-Null
    Invoke-CRFlow $H 'kill(M.wAu1); kill(M.wAu2); return true' | Out-Null
    Wait-CRFlow $H 'return M.ccapullout and M.transarrive' -TimeoutSeconds 15 | Out-Null
    Invoke-CRFlow $H 'M.transportarrive = GetTime() - 1; return true' | Out-Null
    Wait-CRFlow $H 'return M.touchdown' -TimeoutSeconds 15 | Out-Null
    Wait-CRFlow $H 'return M.lprecon' -TimeoutSeconds 150 | Out-Null
    foreach ($client in $C) { Wait-CRFlowOp $client StartCockpitTimer -TimeoutSeconds 25 | Out-Null }
    $timer = Get-CRFlowEvents $guests[0] op | Where-Object { $_.op -eq 'StartCockpitTimer' } | Select-Object -First 1
    Add-CRFlowCheck 'cockpit timer 540/362/180 delivered with the leader values' (@($timer.args)[0] -eq 540 -and @($timer.args)[1] -eq 362) $timer.args
    foreach ($client in $guests) { Wait-CRFlowOp $client SetObjectiveOn -TimeoutSeconds 10 | Out-Null }
    'misn0605 objective and timer on every client'
}

Invoke-CRFlowStep '5th Platoon film is held while ANY player has an enemy within 400 m' {
    # Everyone gathers at Wyoming; one hostile parks beside a non-leader.
    $wy = Invoke-CRFlow $H 'return xyz(M.avrec)'
    foreach ($client in $C) { Move-ClientNear $client $wy 70 }
    $victim = Get-GuestFor 0
    Invoke-CRFlow $H @"
local team = $($victim + 1)
for _, p in pairs(CRCoop.GetPlayers()) do
    if p.team == team and IsValid(p.handle) then
        testEnemy = BuildObject('svfigh', 5, GetPositionNear(GetPosition(p.handle), 40, 50))
        Stop(testEnemy, 0)
    end
end
return IsValid(testEnemy)
"@ | Out-Null
    $near = Invoke-CRFlow $H 'return { enemyDist = GetDistance(testEnemy, M.avrec), gate = M.threemin }'
    Invoke-CRFlow $H 'M.threeminsplatoon = GetTime() - 1; return true' | Out-Null
    Start-Sleep -Seconds 6
    $held = Invoke-CRFlow $H 'return { threemin = M.threemin, simcam = M.simcam, sim1 = M.sim1 ~= nil }'
    if (-not $held.threemin -or $held.simcam -or $held.sim1) { throw "the film started with an enemy near a guest: $(ConvertTo-Json $held -Compress)" }
    @{ near = $near; held = $held }
}

Invoke-CRFlowStep 'enemy removed; 5th Platoon film on every client with team-7 allied units' {
    Invoke-CRFlow $H 'kill(testEnemy); return true' | Out-Null
    $diag = $null
    try { Wait-CRFlow $H 'return M.simcam and M.sim5 ~= nil' -TimeoutSeconds 45 | Out-Null }
    catch {
        $diag = Invoke-CRFlow $H 'local rows = {}; CRCoop.ForEachPlayerHandle(function(h) local e = GetNearestEnemy(h); rows[#rows + 1] = { odf = GetOdf(h), enemy = IsValid(e) and GetOdf(e) or nil, dist = IsValid(e) and GetDistance(h, e) or nil } end); return rows'
        throw "film never started; nearest enemies: $(ConvertTo-Json $diag -Compress -Depth 4)"
    }
    foreach ($client in $guests) { Wait-CRFlow $client 'return L().localCameraActive' -TimeoutSeconds 12 | Out-Null }
    $fleet = Invoke-CRFlow $H 'local n, teams = 0, {}; for i = 1, 10 do local h = M["sim" .. i]; if IsValid(h) then n = n + 1; teams[GetTeamNum(h)] = true end end; return { count = n, team7 = teams[7] == true, otherTeams = (function() local c = 0; for t in pairs(teams) do if t ~= 7 then c = c + 1 end end return c end)() }'
    if ($fleet.count -ne 10 -or -not $fleet.team7 -or $fleet.otherTeams) { throw "film fleet incorrect: $(ConvertTo-Json $fleet -Compress)" }
    foreach ($client in $C) {
        $ok = Invoke-CRFlow $client 'local t = role().team; return IsTeamAllied(t, 7) and IsTeamAllied(7, t)'
        if (-not $ok) { throw "c$client is not allied with the film fleet" }
    }
    if ($Skipper -ne 'none') {
        # A second local skip on a different peer, mid object-camera film.
        $skipClient = Get-GuestFor 1
        Send-CRFlowKey $skipClient 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
        Start-Sleep -Milliseconds 300
        Send-CRFlowKey $skipClient 0x20 -Focused:$FocusedSkip -WithVk -HoldMs 400
        Wait-CRFlow $skipClient 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 6 | Out-Null
        $filming = Invoke-CRFlow $H 'return M.simcam'
        if (-not $filming) { throw "the shared film ended right after c$skipClient skipped" }
        foreach ($client in ($C | Where-Object { $_ -ne $skipClient })) {
            $active = Invoke-CRFlow $client 'return L().localCameraActive'
            if (-not $active) { throw "c$client lost the shared film after c$skipClient skipped" }
        }
        Add-CRFlowCheck "local skip on c$skipClient leaves the 5th Platoon film running for the others" $true $null
        $fleet.skipper = $skipClient
    }
    $fleet
}

Invoke-CRFlowStep '5th Platoon film ends; the fleet is removed and the timer stops everywhere' {
    Wait-CRFlow $H 'return M.removal' -TimeoutSeconds 90 | Out-Null
    foreach ($client in $C) { Wait-CRFlow $client 'return not L().localCameraActive' -TimeoutSeconds 10 | Out-Null }
    foreach ($client in $guests) { Wait-CRFlowOp $client StopCockpitTimer -TimeoutSeconds 15 | Out-Null }
    'fleet removed'
}

Invoke-CRFlowStep 'launch pad scanned by a guest; dust-off camera appears for everyone' {
    # The CCA platoon would otherwise spawn eight more attackers after its lead.
    Invoke-CRFlow $H "M.economyccaplatoon = true; every('killccap', 0.5, function() if M.ccap1 and IsAlive(M.ccap1) then kill(M.ccap1) end end); return true" | Out-Null
    $who = Get-GuestFor 2
    Invoke-CRFlow $who "return forceInfo('sblpad', true)" | Out-Null
    Wait-CRFlow $H 'return M.launchpadreconed and M.bugout' -TimeoutSeconds 10 | Out-Null
    Invoke-CRFlow $who "return forceInfo('sblpad', false)" | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client HideCockpitTimer -TimeoutSeconds 10 | Out-Null }
    Wait-CRFlow $H 'return M.dustoffcam ~= nil and IsAlive(M.dustoffcam) and M.pickupreached' -TimeoutSeconds 20 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SetObjectiveName 'Dust Off' -TimeoutSeconds 20 | Out-Null }
    Invoke-CRFlow $H 'return { point = M.extractpoint, cam = describe(M.dustoffcam) }'
}

$dustoff = Invoke-CRFlow $H 'return xyz(M.dustoffcam)'
$lastGuest = $C[$C.Count - 1]

Invoke-CRFlowStep 'every player at the dust-off point but Wyoming away: no extraction' {
    foreach ($client in $C) { Move-ClientNear $client $dustoff 45 }
    Invoke-CRFlow $H @"
local p = GetPositionNear(at($($dustoff[0].ToString($inv)), $($dustoff[1].ToString($inv)), $($dustoff[2].ToString($inv))), 350, 360)
SetPosition(M.avrec, p)
return describe(M.avrec)
"@ | Out-Null
    $d = Invoke-CRFlow $H 'return { avrec = GetDistance(M.avrec, M.dustoffcam), players = (function() local r = {}; CRCoop.ForEachPlayerHandle(function(h) r[#r + 1] = GetDistance(h, M.dustoffcam) end); return r end)() }'
    if ($d.avrec -lt 150) { throw "Wyoming not moved away: $(ConvertTo-Json $d -Compress)" }
    Assert-NoResult 'Wyoming away' | Out-Null
    $d
}

Invoke-CRFlowStep "Wyoming at the dust-off point but c$lastGuest away: no extraction" {
    Invoke-CRFlow $H @"
local p = GetPositionNear(at($($dustoff[0].ToString($inv)), $($dustoff[1].ToString($inv)), $($dustoff[2].ToString($inv))), 40, 50)
SetPosition(M.avrec, p)
return describe(M.avrec)
"@ | Out-Null
    Move-ClientNear $lastGuest $dustoff 300
    $d = Invoke-CRFlow $H 'return { avrec = GetDistance(M.avrec, M.dustoffcam), players = (function() local r = {}; CRCoop.ForEachPlayerHandle(function(h) r[#r + 1] = GetDistance(h, M.dustoffcam) end); return r end)() }'
    if ($d.avrec -gt 100 -or @($d.players | Where-Object { $_ -gt 100 }).Count -ne 1) { throw "gate setup incorrect: $(ConvertTo-Json $d -Compress)" }
    Assert-NoResult "c$lastGuest away" | Out-Null
    $d
}

Invoke-CRFlowStep "c$lastGuest joins: Wyoming and all $($C.Count) players inside 100 m; the win reaches everyone" {
    Move-ClientNear $lastGuest $dustoff 45
    $d = Invoke-CRFlow $H 'return { avrec = GetDistance(M.avrec, M.dustoffcam), players = (function() local r = {}; CRCoop.ForEachPlayerHandle(function(h) r[#r + 1] = GetDistance(h, M.dustoffcam) end); return r end)() }'
    Wait-CRFlow $H 'return M.dustoff' -TimeoutSeconds 15 | Out-Null
    Wait-CRFlowOp $H SucceedMission 'misn06w1.des' -TimeoutSeconds 30 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SucceedMission 'misn06w1.des' -TimeoutSeconds 25 | Out-Null }
    @{ gate = $d }
}
Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn06w1.des' -Clients $C
