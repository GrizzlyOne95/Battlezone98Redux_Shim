# misn02b "CR: Scavenger escort" (Tran05), full win path with a host and one guest.
#
# The authored chain: intro film -> build a scavenger -> it reaches Scrap Field
# Alpha (staged fighters wake) -> second field (waves) -> it is shot and falls
# back -> near the base a second scavenger (scav2) spawns -> scav2 reaches the
# base -> win once the closing audio ends. The host does the player's part
# (builds the scavenger on team 1, moves mission objects it owns); the guest
# must see every objective and the result.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Who presses skip during the intro film: 'guest', 'host' or 'none'.
      [ValidateSet('guest', 'host', 'none')][string]$Skipper = 'guest',
      [int]$SkipKey = 0x20,
      # Players must start as pilots, as in single player (needs an asuser-only misn02b.vxt).
      [switch]$ExpectOnFoot,
      # Let the intro play out (no timer pulls) and check each shot as single
      # player runs it: lander (fixcam), then the dummy tank driving player_path
      # (zoomcam), then the first objective. Use with Skipper=none.
      [switch]$NaturalIntro)

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

Invoke-CRFlowStep 'mission started; intro film on both clients' {
    Wait-CRFlow $H 'return M.start_done and M.camera1' -TimeoutSeconds 120 | Out-Null
    Wait-CRFlow $G 'return L().localCameraActive' -TimeoutSeconds 20 | Out-Null
    @{ host = Invoke-CRFlow $H 'return L()'; guest = Invoke-CRFlow $G 'return L()' }
}

Invoke-CRFlowStep 'keep mission objects alive (test assist)' {
    Invoke-CRFlow $H @'
every('protect', 1, function()
    for _, k in ipairs({ "bscav", "scav2", "bhome", "recycler" }) do
        if M[k] then heal(M[k]) end
    end
end)
return #tasks()
'@ | Out-Null
    foreach ($c in $H, $G) { Invoke-CRFlow $c "every('selfheal', 1, function() heal(me()) end); return true" | Out-Null }
    'protect + selfheal'
}

if ($Skipper -ne 'none') {
    $skipClient, $watchClient = if ($Skipper -eq 'host') { $H, $G } else { $G, $H }
    Invoke-CRFlowStep "$Skipper skips the intro; the other client's film continues" {
        Send-CRFlowKey $skipClient $SkipKey
        Start-Sleep -Milliseconds 300
        Send-CRFlowKey $skipClient $SkipKey
        Wait-CRFlow $skipClient 'return L().cameraSkipped and not L().localCameraActive' -TimeoutSeconds 10 | Out-Null
        $spawn = @{ host = (Invoke-CRFlow $H 'return describe(me())'); guest = (Invoke-CRFlow $G 'return describe(me())') }
        Start-Sleep -Seconds 3
        # misn02b tracks localCameraActive only for the remote (guest) camera;
        # the host's own film is driven straight from its M.camera1/3 flags.
        $filming = Invoke-CRFlow $H 'return (M.camera1 or M.camera3) == true'
        if ($watchClient -eq $H) {
            if (-not $filming) { throw 'the guest skip ended the shared film on the host' }
            $w = @{ hostFilming = $filming; hostSkipped = (Invoke-CRFlow $H 'return L().cameraSkipped') }
            if ($w.hostSkipped) { throw 'the guest skip marked the host camera skipped' }
        } else {
            $w = Invoke-CRFlow $watchClient 'return { active = L().localCameraActive, skipped = L().cameraSkipped }'
            if ($filming -and -not $w.active) { throw "c$watchClient camera ended while the film was still running" }
        }
        @{ watcher = $w; hostFilming = $filming; players = $spawn }
    }
}

if ($NaturalIntro) {
    # Stray craft: single player has none. Report every team-0 craft the probe
    # saw created on the host, with when and where.
    Invoke-CRFlowStep 'no stray team-0 craft at the start' {
        Start-Sleep -Seconds 2
        $adds = @(Get-CRFlowEvents $H add | Where-Object { $_.obj.team -eq 0 -and $_.obj.odf -notmatch '^(npscr|sscr)' })
        $now = Invoke-CRFlow $H @'
local out = {}
for h in AllCraft() do
    if GetTeamNum(h) == 0 and IsAlive(h) then out[#out + 1] = describe(h) end
end
return out
'@
        $r = @{ created = @($adds | ForEach-Object { "t=$($_.t) $($_.h) $($_.obj.odf) [$($_.obj.label)] at $($_.obj.pos -join ',')" }); alive = $now }
        if (@($now | Where-Object { $_.odf -eq 'player' }).Count) { throw "stray team-0 player craft: $(ConvertTo-Json $r -Compress -Depth 5)" }
        $r
    } -Soft

    Invoke-CRFlowStep 'intro shot 1: camera on the lander until its path ends' {
        $t0 = Invoke-CRFlow $H 'return GetTime()'
        Wait-CRFlow $H 'return M.camera3 or (not M.camera1 and not M.camera2)' -TimeoutSeconds 45 | Out-Null
        $t1 = Invoke-CRFlow $H 'return GetTime()'
        @{ shotSeconds = [math]::Round($t1 - $t0, 1) }
    }

    Invoke-CRFlowStep 'intro shot 2: both cameras follow the living dummy tank' {
        $samples = foreach ($i in 1..3) {
            Start-Sleep -Seconds 2
            # (PowerShell names ignore case: never call these $h/$g, which are $H/$G.)
            $hostShot = Invoke-CRFlow $H 'return { camera3 = M.camera3 == true, dummy = describe(M.dummy), path = L().cameraPath }'
            $guestShot = Invoke-CRFlow $G 'local l = L(); return { active = l.localCameraActive, path = l.remotePath, targetOdf = l.remoteTargetOdf }'
            @{ host = $hostShot; guest = $guestShot }
        }
        foreach ($s in $samples) {
            if (-not $s.host.camera3) { break }   # shot over
            if (-not $s.host.dummy.alive) { throw "the dummy tank died during its shot: $(ConvertTo-Json $s -Compress -Depth 5)" }
            if ($s.guest.path -ne 'zoomcam' -or -not $s.guest.active) { throw "guest camera is not following the dummy: $(ConvertTo-Json $s -Compress -Depth 5)" }
        }
        $samples
    }

    Invoke-CRFlowStep 'intro ends by itself -> first objective on guest' {
        Wait-CRFlow $H 'return not M.camera1 and not M.camera2 and not M.camera3' -TimeoutSeconds 60 | Out-Null
        Wait-CRFlowOp $G AddObjective 'misn02b1.otf' -TimeoutSeconds 30 | Out-Null
        @{ dummy = Invoke-CRFlow $H 'return describe(M.dummy)' }
    }
} else {
Invoke-CRFlowStep 'intro ends -> first objective on guest' {
    # Co-op ends each film shot on a timer (30 s + 25 s); pull both forward.
    Invoke-CRFlow $H "return ff('^cam_time$')" | Out-Null
    Wait-CRFlow $H 'return M.camera2 or M.camera3 or (not M.camera1)' -TimeoutSeconds 20 | Out-Null
    Start-Sleep -Seconds 1
    Invoke-CRFlow $H "return ff('^cam_time$')" | Out-Null
    Wait-CRFlow $H 'return not M.camera1 and not M.camera2 and not M.camera3' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn02b1.otf' -TimeoutSeconds 30 | Out-Null
    'misn02b1.otf'
}
}

Invoke-CRFlowStep 'both cameras released after the intro' {
    Wait-CRFlow $H 'return not L().localCameraActive' -TimeoutSeconds 15 | Out-Null
    Wait-CRFlow $G 'return not L().localCameraActive' -TimeoutSeconds 15
}

# Single player starts on foot beside four empty team-1 vehicles (tank, scout,
# bomber, light tank) for the "get in a vehicle" objective; each co-op player
# should start the same way, near them. (pspwn spawn points are not runtime
# objects, so distance is measured to the vehicles.)
Invoke-CRFlowStep 'players start near the empty vehicles' {
    $where = @'
local me = me()
local best, name = nil, nil
for _, l in ipairs({ "player-1_hover", "avfigh0_wingman", "avhraz0_wingman", "avltnk0_wingman" }) do
    local h = GetHandle(l)
    if h and IsValid(h) then
        local d = GetDistance(me, h)
        if not best or d < best then best, name = d, l end
    end
end
return { odf = GetOdf(me), person = IsPerson(me) and true or false, pos = xyz(me),
         nearestVehicle = name, vehicleDist = best }
'@
    $r = @{ host = (Invoke-CRFlow $H $where); guest = (Invoke-CRFlow $G $where) }
    $far = @($r.GetEnumerator() | Where-Object { $null -eq $_.Value.vehicleDist -or $_.Value.vehicleDist -gt 60 } | ForEach-Object { "$($_.Key) $(if ($null -ne $_.Value.vehicleDist) { [math]::Round([double]$_.Value.vehicleDist) } else { '?' })m" })
    if ($far.Count) { throw "far from the empty vehicles: $($far -join ', ') $(ConvertTo-Json $r -Compress -Depth 4)" }
    if ($ExpectOnFoot) {
        $mounted = @($r.GetEnumerator() | Where-Object { -not $_.Value.person } | ForEach-Object { "$($_.Key) in $($_.Value.odf)" })
        if ($mounted.Count) { throw "expected on foot: $($mounted -join ', ')" }
    }
    $r
} -Soft

Invoke-CRFlowStep 'everyone in a vehicle -> first objective complete' {
    Wait-CRFlow $H 'return M.initialObjectiveCompleted' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlowOp $G UpdateObjective 'misn02b1.otf' -TimeoutSeconds 20 | Out-Null
    'misn02b1.otf green'
} -Soft

Invoke-CRFlowStep 'host builds a scavenger -> mission tracks it' {
    Invoke-CRFlow $H 'scav = BuildObject("avscav", 1, GetPositionNear(GetPosition(M.recycler), 40, 60)); return describe(scav)' | Out-Null
    Wait-CRFlow $H 'return M.found and IsValid(M.bscav) and describe(M.bscav)' -TimeoutSeconds 15
}

Invoke-CRFlowStep 'scavenger at Scrap Field Alpha -> staged fighters wake' {
    Invoke-CRFlow $H 'return put(M.bscav, M.bhandle, 20)' | Out-Null
    Wait-CRFlow $H 'return M.patrol1 and M.message1' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlow $H 'return M.message4' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'scavenger at the second field -> waves start' {
    Invoke-CRFlow $H 'return put(M.bscav, M.bhandle2, 60)' | Out-Null
    Wait-CRFlow $H 'return M.message5' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'scavenger shot -> falls back; retreat objective on guest' {
    # An enemy fighter (team 6, host-owned) next to the scavenger, attacking it.
    Invoke-CRFlow $H @'
local f = BuildObject("svfigh", 6, GetPositionNear(GetPosition(M.bscav), 40, 60))
Attack(f, M.bscav, 1)
shooter = f
return describe(f)
'@ | Out-Null
    Wait-CRFlow $H 'return M.message2' -TimeoutSeconds 60 | Out-Null
    Invoke-CRFlow $H 'return kill(shooter)' | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn02b2.otf' -TimeoutSeconds 30 | Out-Null
    'misn02b2.otf'
}

Invoke-CRFlowStep 'mid-mission world parity' { Test-CRFlowTransport $H @($G); Test-CRFlowWorldParity $H @($G) } -Soft

Invoke-CRFlowStep 'scavenger near the base -> second scavenger spawns' {
    Invoke-CRFlow $H 'return put(M.bscav, M.bhome, 150)' | Out-Null
    Wait-CRFlow $H 'return M.message3 and IsValid(M.scav2) and describe(M.scav2)' -TimeoutSeconds 20
}

Invoke-CRFlowStep 'guest sees the second scavenger' {
    $s = Invoke-CRFlow $H 'return xyz(M.scav2)'
    Wait-CRFlow $G ("return findNear('avscav', {0}, {1}, 40) ~= nil" -f $s[0], $s[2]) -TimeoutSeconds 15
}

Invoke-CRFlowStep 'clear attackers around the convoy' {
    Invoke-CRFlow $H @'
every('clear', 2, function()
    if M.mission_won then return true end
    killTeam(6, "^svfigh", M.scav2, 800)
    killTeam(6, "^svfigh", M.bscav, 800)
end)
return true
'@
}

Invoke-CRFlowStep 'second scavenger reaches the base -> win objective on guest' {
    Invoke-CRFlow $H 'return put(M.scav2, M.bhome, 100)' | Out-Null
    Wait-CRFlow $H 'return M.mission_won' -TimeoutSeconds 20 | Out-Null
    Wait-CRFlowOp $G AddObjective 'misn02b3.otf' -TimeoutSeconds 30 | Out-Null
    'misn02b3.otf'
}

Invoke-CRFlowStep 'pre-result world parity' { Test-CRFlowTransport $H @($G); Test-CRFlowWorldParity $H @($G) } -Soft

Invoke-CRFlowStep 'win reaches both clients (after the closing audio)' {
    $a = Wait-CRFlowOp $H SucceedMission 'misn02w1.des' -TimeoutSeconds 90
    $b = Wait-CRFlowOp $G SucceedMission 'misn02w1.des' -TimeoutSeconds 30
    @{ hostAt = $a.t; guestAt = $b.t }
}

Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn02w1.des' -Clients @($H, $G)
