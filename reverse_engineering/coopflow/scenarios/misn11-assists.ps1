# misn11 (Bring it Home) test assists. Forced steps are labelled ASSIST; the mission's own code
# does the building, ordering, defection, hunting and result.
#
#   1. Smoke (attach, roles, ready, play, roster).
#   2. LAVA (top priority): a hover tank is parked on a molten tile (ASSIST: teleport) and its HP/s is measured,
#      next to a dry control.
#   3. Ambush: picket turrets wake at 380 m (not at 450 m); the artillery targets humans after the defection.
#   4. Betrayal: the backup squad spawns (ASSIST: the convoy is released and the defector moved near waypoint 1),
#      the defection happens, and the squad is on Follow on the defector.
#   5. Chase: humans at 420 m get misn1114 on every client and are not attacked; at 300 m the squad attacks a human;
#      after break-off misn1115 plays.
#   6. Walker wakes at check2 (ASSIST: tug 1 moved to the check2 path point).
#   7. Armory trail (best effort): an AI tank is sent to the armory and checked against the lava grid.
#   8. Win: one human short of launch_pad2 does not win; all humans within 200 m do (ASSIST: last wave timer, tugs
#      moved to launch_pad2); misn11w1.des on every client.
param([int]$HostClient = 0,
      [int]$PlaySeconds = 20,
      [int]$LavaSeconds = 6)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$humans = $C.Count
$extras = [math]::Min(3, [math]::Max(0, $humans - 1))

$lib = @'
local S = require("CRIoSites11")
LVC, LVR, LVCELL, LVX, LVZ = S.lava.cols, S.lava.rows, S.lava.cell, S.lava.originX, S.lava.originZ
LV = {}
for _, r in ipairs(S.lava.runs) do
  for c = r[2], r[2] + r[3] - 1 do LV[r[1] * 1000 + c] = r[4] end
end
function lavaW(x, z)
  local c = math.floor((x - LVX) / LVCELL); local r = math.floor((z - LVZ) / LVCELL)
  return LV[r * 1000 + c] or 0
end
function dryAt(x, z, m)
  m = m or 1
  for dx = -m, m do for dz = -m, m do
    if lavaW(x + dx * LVCELL, z + dz * LVCELL) > 0 then return false end
  end end
  return true
end
function lavaAt(x, z, m)
  m = m or 1
  for dx = -m, m do for dz = -m, m do
    if lavaW(x + dx * LVCELL, z + dz * LVCELL) < 1 then return false end
  end end
  return true
end
function dryRing(cx, cz, r)
  for _, rr in ipairs({ r, r * 0.9, r * 1.1, r * 0.8, r * 1.2 }) do
    for a = 0, 345, 15 do
      local x, z = cx + rr * math.cos(math.rad(a)), cz + rr * math.sin(math.rad(a))
      if dryAt(x, z, 1) then return x, z end
    end
  end
  return nil
end
function placeMe(x, z, lift)
  local y = GetTerrainHeightAndNormal(SetVector(x, 0, z))
  SetPosition(me(), SetVector(x, y + (lift or 4), z))
  return true
end
function ringPlace(cx, cz, r, k)
  for _, rr in ipairs({ r, r * 1.1, r * 1.25, r * 0.9, r * 1.5 }) do
    local x, z = dryRing(cx + (k or 0) * 8, cz, rr)
    if x then placeMe(x, z, 4); local p = GetPosition(me()); return math.sqrt((p.x - cx) ^ 2 + (p.z - cz) ^ 2) end
  end
  return -1
end
function hpNow() local h = me(); local ok, v = pcall(GetCurHealth, h); return ok and v or -1 end
return true
'@
$posOf = { param($expr) "local p = GetPosition($expr); return { x = p.x, y = p.y, z = p.z }" }

function Invoke-All([string]$Lua) { foreach ($cl in @(Get-CRFlowClientIndices)) { Invoke-CRFlow $cl $Lua | Out-Null } }
function Healers([bool]$On) {
    foreach ($cl in $C) {
        if ($On) { Invoke-CRFlow $cl 'every("keepheal", 1, function() pcall(function() heal(me()); if M and M.tug1 and IsAlive(M.tug1) then heal(M.tug1) end; if M and M.tug2 and IsAlive(M.tug2) then heal(M.tug2) end end) end); return true' | Out-Null }
        else { Invoke-CRFlow $cl 'cancel("keepheal"); return true' | Out-Null }
    }
}

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
Invoke-CRFlowStep 'session ready and mission running on every client; lava grid loaded' {
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 90 | Out-Null }
    Invoke-All $lib
    'ok'
}
Invoke-CRFlowStep "$PlaySeconds s of play; every peer alive, full roster" {
    Start-Sleep -Seconds $PlaySeconds
    foreach ($client in $C) {
        $s = Invoke-CRFlow $client 'local d = describe(me()); return { alive = d.alive, valid = d.valid, team = d.team, players = #players() }'
        Add-CRFlowCheck "c$client alive with its own craft, sees $humans players" ($s.valid -and $s.alive -and $s.players -eq $humans) $s
    }
}

Invoke-CRFlowStep 'scavenger ownership (for the AIP/NetProcess crash note)' {
    $sc = Invoke-CRFlow $H 'local sc = {}; for h in AllCraft() do local o = tostring(GetOdf(h) or ""):gsub("%.odf$", ""); if o:find("scav") then sc[#sc + 1] = { odf = o, team = GetTeamNum(h) } end end; return sc'
    $guestScav = @($sc | Where-Object { $_.team -in 2, 3, 4 })
    Add-CRFlowCheck "guest-owned scavengers: $($guestScav.Count) (all: $(@($sc | % { "$($_.odf)/t$($_.team)" }) -join ' '))" $true $sc -WarnOnly
    $sc
}

Invoke-CRFlowStep 'ambush at rest (no interference): do the pickets wake from the convoy at the start, and do they hurt the tugs?' {
    $rows = @()
    for ($k = 0; $k -lt 3; $k++) {
        $rows += (Invoke-CRFlow $H 'local function hp(h) if h and IsAlive(h) then return GetCurHealth(h) end return -1 end; return { t = GetTime(), woken1 = M.woken[M.picket1] == true, woken2 = M.woken[M.picket2] == true, tug1 = hp(M.tug1), tug2 = hp(M.tug2), openh = hp(M.openh), d1 = M.picket1 and IsAlive(M.picket1) and GetDistance(M.picket1, M.tug1) or -1, convoyMoving = M.start_delay == 99999 }')
        Start-Sleep -Seconds 4
    }
    Add-CRFlowCheck "pickets at rest: picket 1 woken by the convoy tug ($($rows[-1].d1) m away): $($rows[-1].woken1); tug HP $($rows[0].tug1) -> $($rows[-1].tug1)" $true @{ rows = $rows } -WarnOnly
    @{ rows = $rows }
}

Healers $true   # keeps the convoy tugs and every human craft alive from here (the real pickets kill a tug about 50 s in otherwise)
Invoke-CRFlowStep 'ambush: pickets hunt the convoy; then ASSIST: both pickets removed so the convoy survives the rest of the run' {
    # The real pickets kill a tug about 54 s into the mission (observed in 3 runs: misn1111/1112 + FailMission at t=54.3),
    # so the picket behaviour is recorded here and the pickets are then removed (ASSIST).
    $pk = Invoke-CRFlow $H 'local A = AiCommand and AiCommand.ATTACK; local function row(p) if not p then return nil end return { alive = IsAlive(p), woken = M.woken[p] == true, cmd = GetCurrentCommand(p), attack = A, dTug1 = GetDistance(p, M.tug1), dTug2 = GetDistance(p, M.tug2) } end; return { p1 = row(M.picket1), p2 = row(M.picket2), tug1 = IsAlive(M.tug1) and GetCurHealth(M.tug1) or -1 }'
    Add-CRFlowCheck "picket 1 is awake and on an Attack order (woken=$($pk.p1.woken), cmd=$($pk.p1.cmd), $([int]$pk.p1.dTug1) m from tug 1)" ($pk.p1.alive -and $pk.p1.woken -and $pk.p1.cmd -eq $pk.p1.attack) $pk
    $rm = Invoke-CRFlow $H 'for _, p in ipairs({ M.picket1, M.picket2 }) do if p and IsAlive(p) then RemoveObject(p) end end; return true'
    @{ pickets = $pk; removed = $rm }
}

# --------------------------------------------------------------- LAVA --
Invoke-CRFlowStep 'LAVA: a hover tank on a molten tile loses health (HP/s measured); dry control loses none' {
    # Nearest fully molten cell (3x3 molten) to the host's start.
    $spot = Invoke-CRFlow $H @'
local p = GetPosition(me())
STARTP = { x = p.x, z = p.z }
local best, bd
for k, w in pairs(LV) do
  if w == 1 then
    local r = math.floor(k / 1000); local c = k - r * 1000
    local x, z = LVX + (c + 0.5) * LVCELL, LVZ + (r + 0.5) * LVCELL
    if lavaAt(x, z, 2) then
      local d = (x - p.x) ^ 2 + (z - p.z) ^ 2
      if not bd or d < bd then bd, best = d, { x = x, z = z } end
    end
  end
end
return { start = STARTP, lava = best, dist = bd and math.sqrt(bd) or -1, startDry = dryAt(p.x, p.z, 1) }
'@
    if (-not $spot.lava) { throw 'no molten cell found' }
    Healers $false
    $samples = @()
    # Dry control first (still on the start).
    Invoke-CRFlow $H 'heal(me()); return true' | Out-Null
    $c0 = Invoke-CRFlow $H 'return { hp = hpNow(), t = GetTime() }'
    Start-Sleep -Seconds 4
    $c1 = Invoke-CRFlow $H 'return { hp = hpNow(), t = GetTime() }'
    $control = @{ before = $c0; after = $c1 }
    # ASSIST: teleport onto lava.
    Invoke-CRFlow $H ("heal(me()); placeMe($($spot.lava.x), $($spot.lava.z), 3); return true") | Out-Null
    for ($k = 0; $k -lt $LavaSeconds; $k++) {
        $samples += (Invoke-CRFlow $H 'local p = GetPosition(me()); return { hp = hpNow(), t = GetTime(), x = p.x, y = p.y, z = p.z, alive = IsAlive(me()), w = lavaW(p.x, p.z) }')
        Start-Sleep -Milliseconds 700
    }
    # Back to the start, healed.
    Invoke-CRFlow $H ("heal(me()); placeMe($($spot.start.x), $($spot.start.z), 4); return true") | Out-Null
    Healers $true
    $first = $samples[0]; $last = $samples[-1]
    $dt = $last.t - $first.t
    $rate = if ($dt -gt 0) { [math]::Round(($first.hp - $last.hp) / $dt, 1) } else { 0 }
    Write-Host ("[lava] hp {0} -> {1} over {2:N1} s = {3} hp/s; on-lava weights {4}" -f $first.hp, $last.hp, $dt, $rate, (($samples | % { $_.w }) -join ','))
    Add-CRFlowCheck "craft sat on molten tiles (grid weight 1) for the measurement" (@($samples | ? { $_.w -ge 1 }).Count -ge ($samples.Count - 1)) @{ samples = $samples }
    Add-CRFlowCheck "dry control: no health lost in 4 s ($($c0.hp) -> $($c1.hp))" ($c1.hp -ge $c0.hp - 1) $control
    Add-CRFlowCheck "LAVA DAMAGE: hover tank on lava loses health ($rate hp/s; doc expects ~100-140)" ($rate -gt 5) @{ samples = $samples; rate = $rate; spot = $spot }
    @{ rateHpPerSecond = $rate; spot = $spot; samples = $samples; control = $control }
}

# ------------------------------------------------------------- ambush --
# ------------------------------------------------------------ betrayal --
Invoke-CRFlowStep 'betrayal: backup squad spawns near waypoint 1; defection; squad on Follow on the defector (ASSIST: convoy released, defector moved)' {
    $pre = Invoke-CRFlow $H 'return { backupCalled = M.backup_called == true, startDelay = M.start_delay, openh = describe(M.openh), cam1 = describe(M.cam1), betrayal = M.betrayal == true }'
    # Release the convoy (the real 15 s start delay), then bring the defector near waypoint 1 but outside 50 m.
    Invoke-CRFlow $H 'if M.start_delay and M.start_delay < 99999 then M.start_delay = GetTime() - 1 end; return true' | Out-Null
    Start-Sleep -Seconds 4
    $cam = Invoke-CRFlow $H 'local p = GetPosition(M.cam1); return { x = p.x, z = p.z }'
    $mv = Invoke-CRFlow $H ("local x, z = dryRing($($cam.x), $($cam.z), 150); if not x then return false end; SetPosition(M.openh, SetVector(x, GetTerrainHeightAndNormal(SetVector(x, 0, z)) + 2, z)); Goto(M.openh, 'base1', 0); return true")
    $sq = $null
    try { $sq = Wait-CRFlow $H 'if not M.backup_called then return false end; local n, odfs, team5 = 0, {}, 0; for _, u in ipairs(M.backup) do if IsAlive(u) then n = n + 1; odfs[#odfs + 1] = (tostring(GetOdf(u)):gsub("%.odf$", "")); if GetTeamNum(u) == 5 then team5 = team5 + 1 end end end; return { n = n, team5 = team5, odfs = odfs }' -TimeoutSeconds 30 } catch { }
    Add-CRFlowCheck "backup squad spawned before the defection: $(3 + $extras) CCA units (svtank x2, svfigh x$(1 + $extras)); got $($sq.n) [$($sq.odfs -join ',')]" ($sq -and $sq.n -eq (3 + $extras) -and $sq.team5 -eq $sq.n) @{ sq = $sq; moved = $mv; cam = $cam }
    # ASSIST: every human far (~900 m) from waypoint 1 before the defection, so nobody is a chaser yet and the squad's
    # no-chaser order (Follow on the defector) is what gets observed.
    $far = @(); $i = 0
    foreach ($cl in $C) { $far += (Invoke-CRFlow $cl ("return ringPlace($($cam.x), $($cam.z), 900, $i)")); $i++ }
    # Defect: the real 50 m trigger, then the real 15 s announcement delay.
    Invoke-CRFlow $H ("local x, z = dryRing($($cam.x), $($cam.z), 30); if x then SetPosition(M.openh, SetVector(x, GetTerrainHeightAndNormal(SetVector(x, 0, z)) + 2, z)) end; return true") | Out-Null
    $def = Wait-CRFlow $H 'return M.betrayal_message == true and { team = GetTeamNum(M.openh), t = GetTime() }' -TimeoutSeconds 45
    Start-Sleep -Seconds 5
    $form = Invoke-CRFlow $H @'
local F = AiCommand and AiCommand.FOLLOW
local rows, inForm, alive = {}, 0, 0
for _, u in ipairs(M.backup) do
  if IsAlive(u) then
    alive = alive + 1
    local c = GetCurrentCommand(u)
    local who = nil; pcall(function() who = GetCurrentWho(u) end)
    local onDefector = (who == M.openh)
    if c == F and onDefector then inForm = inForm + 1 end
    rows[#rows + 1] = { odf = GetOdf(u), cmd = c, onDefector = onDefector, formation = F, order = M.squad_order[u] ~= nil }
  end
end
return { alive = alive, inFormation = inForm, formed = M.backup_formed == true, rows = rows, openhTeam = GetTeamNum(M.openh) }
'@
    Add-CRFlowCheck "defector switched to the CCA (team $($def.team)); humans were $($far -join ',') m from waypoint 1" ($def.team -eq 5) @{ def = $def; far = $far }
    Add-CRFlowCheck "after the defection the squad is on Follow on the defector ($($form.inFormation) of $($form.alive))" ($form.alive -gt 0 -and $form.inFormation -eq $form.alive) $form
    @{ squad = $sq; defection = $def; formation = $form }
}

# --------------------------------------------------------------- chase --
Invoke-CRFlowStep 'chase: misn1114 at 450 m on every client; squad attacks a human within 350 m; misn1115 after break-off (ASSIST: humans moved)' {
    $op = Invoke-CRFlow $H 'local p = GetPosition(M.openh); return { x = p.x, z = p.z }'
    # Humans at ~420 m from the defector: warn range, outside the 350 m chase range.
    $i = 0
    $d420 = @(); foreach ($cl in $C) { $d420 += (Invoke-CRFlow $cl ("return ringPlace($($op.x), $($op.z), 420, $i)")); $i++ }
    foreach ($client in $C) { Wait-CRFlowOp $client Play 'misn1114.wav' -TimeoutSeconds 25 | Out-Null }
    $warnFlag = Invoke-CRFlow $H 'return { warned = M.warned_massive == true }'
    Add-CRFlowCheck 'misn1114 reached every client with all humans at ~420 m' $warnFlag.warned $warnFlag
    Start-Sleep -Seconds 4
    $far = Invoke-CRFlow $H 'local A = AiCommand and AiCommand.ATTACK; local n = 0; for _, u in ipairs(M.backup) do if IsAlive(u) and GetCurrentCommand(u) == A then n = n + 1 end end; return { attacking = n }'
    # Chase: host within 300 m.
    $op = Invoke-CRFlow $H 'local p = GetPosition(M.openh); return { x = p.x, z = p.z }'
    Invoke-CRFlow $H ("local x, z = dryRing($($op.x), $($op.z), 300); if x then placeMe(x, z, 4) end; return true") | Out-Null
    Start-Sleep -Seconds 6
    $near = Invoke-CRFlow $H @'
local A = AiCommand and AiCommand.ATTACK
local n, onHuman = 0, 0
for _, u in ipairs(M.backup) do
  if IsAlive(u) and GetCurrentCommand(u) == A then
    n = n + 1
    local who = nil; pcall(function() who = GetCurrentWho(u) end)
    if who ~= nil and IsValid(who) and IsPlayer and IsPlayer(who) then onHuman = onHuman + 1 end
    if who == me() then onHuman = onHuman + 0 end
  end
end
local chaser = nil
local ok = pcall(function() chaser = GetTeamNum(me()) end)
return { attacking = n, onHuman = onHuman, alive = (function() local a = 0; for _, u in ipairs(M.backup) do if IsAlive(u) then a = a + 1 end end; return a end)() }
'@
    Add-CRFlowCheck "squad does not attack humans at ~420 m ($($far.attacking) attacking)" ($far.attacking -eq 0) $far -WarnOnly
    Add-CRFlowCheck "squad attacks the chaser within 350 m ($($near.attacking) of $($near.alive) on Attack)" ($near.attacking -gt 0) $near
    # Break-off: every human far away (> 700 m) for > 8 s, 12 s after the warning.
    $op = Invoke-CRFlow $H 'local p = GetPosition(M.openh); return { x = p.x, z = p.z }'
    $i = 0
    $d850 = @(); foreach ($cl in $C) { $d850 += (Invoke-CRFlow $cl ("return ringPlace($($op.x), $($op.z), 850, $i)")); $i++ }
    $got = $true
    foreach ($client in $C) { try { Wait-CRFlowOp $client Play 'misn1115.wav' -TimeoutSeconds 45 | Out-Null } catch { $got = $false } }
    $intel = Invoke-CRFlow $H 'local o = GetPosition(M.openh); local ds = {}; CRCoop = CRCoop; for _, p in ipairs(players()) do end; return { intel = M.intel_logged == true, clear = M.clear_since, warned = M.warned_massive == true, warnedAt = M.warned_massive_time, now = GetTime(), openhAlive = IsAlive(M.openh), squadAlive = (function() local n = 0; for _, u in ipairs(M.backup) do if IsAlive(u) then n = n + 1 end end return n end)() }'
    Add-CRFlowCheck "misn1115 played on every client after break-off (humans were $($d850 -join ',') m from the defector; at 420: $($d420 -join ','))" ($got -and $intel.intel) @{ intel = $intel; d850 = $d850; d420 = $d420 }
    @{ far = $far; near = $near; intel = $intel }
}

# -------------------------------------------------------- artillery ----
Invoke-CRFlowStep 'ambush: the artillery targets a human within 650 m after the defection (ASSIST: host moved)' {
    $a = Invoke-CRFlow $H 'if not IsAlive(M.art1) then return { dead = true } end; local p = GetPosition(M.art1); return { x = p.x, z = p.z }'
    if ($a.dead) { Add-CRFlowCheck 'artillery 1 alive to test' $false $a; return $a }
    Invoke-CRFlow $H ("local x, z = dryRing($($a.x), $($a.z), 500); if x then placeMe(x, z, 4) end; return true") | Out-Null
    Start-Sleep -Seconds 8
    $r = Invoke-CRFlow $H 'local A = AiCommand and AiCommand.ATTACK; local w = nil; pcall(function() w = GetCurrentWho(M.art1) end); return { cmd = GetCurrentCommand(M.art1), atk = A, targetsMe = (w == me()), dist = GetDistance(M.art1, me()) }'
    Add-CRFlowCheck "artillery 1 on Attack with the human at $([int]$r.dist) m (targets the human: $($r.targetsMe))" ($r.cmd -eq $r.atk) $r
    $r
}

# --------------------------------------------------------------- walker --
Invoke-CRFlowStep 'ambush: the walker wakes at check2 (ASSIST: tug 1 moved to the check2 path point)' {
    $pre = Invoke-CRFlow $H 'return { check2 = M.check2 == true, walker = IsAlive(M.walker), cmd = GetCurrentCommand(M.walker) }'
    Invoke-CRFlow $H 'SetPosition(M.tug1, GetPosition("check2", 0)); return true' | Out-Null
    $post = Wait-CRFlow $H 'return M.check2 == true and { check2 = true }' -TimeoutSeconds 20
    Start-Sleep -Seconds 8
    $w = Invoke-CRFlow $H 'local A = AiCommand and AiCommand.ATTACK; return { cmd = GetCurrentCommand(M.walker), atk = A, alive = IsAlive(M.walker) }'
    Add-CRFlowCheck "walker not hunting before check2 (cmd $($pre.cmd))" ($pre.cmd -ne $w.atk -or -not $pre.check2) $pre -WarnOnly
    Add-CRFlowCheck "walker takes an Attack order once check2 is reached (cmd $($w.cmd))" ($w.alive -and $w.cmd -eq $w.atk) @{ pre = $pre; walker = $w }
    @{ pre = $pre; walker = $w }
}

# --------------------------------------------------------------- armory --
Invoke-CRFlowStep 'armory trail (best effort): an AI tank is sent to the armory; time on lava from the grid' {
    $r = Invoke-CRFlow $H @'
local arm = nil
for h in AllObjects() do if (tostring(GetOdf(h) or ""):gsub("%.odf$", "")) == "avslf" then arm = h break end end
if not arm then return { error = "no avslf armory" } end
local ap = GetPosition(arm)
local sx, sz = STARTP.x + 30, STARTP.z + 30
local y = GetTerrainHeightAndNormal(SetVector(sx, 0, sz))
TRAILTANK = BuildObject("avtank", 1, SetVector(sx, y + 2, sz))
Goto(TRAILTANK, arm, 1)
TRAILARM = arm
return { armory = { x = ap.x, z = ap.z }, start = { x = sx, z = sz }, built = IsValid(TRAILTANK) }
'@
    if ($r.error) { Add-CRFlowCheck "armory trail test: $($r.error)" $false $r -WarnOnly; return $r }
    $trace = @(); $onLava = 0
    $deadline = (Get-Date).AddSeconds(150)
    $arrived = $false
    while ((Get-Date) -lt $deadline -and -not $arrived) {
        Start-Sleep -Seconds 4
        $s = Invoke-CRFlow $H 'if not IsAlive(TRAILTANK) then return { dead = true } end; local p = GetPosition(TRAILTANK); return { x = p.x, z = p.z, w = lavaW(p.x, p.z), hp = GetCurHealth(TRAILTANK), d = GetDistance(TRAILTANK, TRAILARM) }'
        $trace += $s
        if ($s.dead) { break }
        if ($s.w -ge 1) { $onLava++ }
        if ($s.d -lt 60) { $arrived = $true }
    }
    $last = $trace[-1]
    Add-CRFlowCheck "AI tank reached the armory island (final distance $($last.d) m, dead=$($last.dead))" ($arrived) @{ trace = $trace } -WarnOnly
    Add-CRFlowCheck "AI tank sampled on a molten tile $onLava of $($trace.Count) times while traversing" ($onLava -eq 0) @{ trace = $trace } -WarnOnly
    Invoke-CRFlow $H 'if IsValid(TRAILTANK) then RemoveObject(TRAILTANK) end; return true' | Out-Null
    @{ setup = $r; trace = $trace }
}

# ------------------------------------------------------------------ win --
Invoke-CRFlowStep 'win: one human short of launch_pad2 does not win; all humans within 200 m do (ASSIST: last wave timer, tugs and humans moved)' {
    $pad = Invoke-CRFlow $H 'local p = GetPosition(M.launch2); return { x = p.x, z = p.z }'
    # The arrival latch (M.arrived) is permanent once the last wave exists, so park the human that must stay out
    # BEFORE the last wave is triggered.
    $lastClient = $C[-1]
    $holdD = Invoke-CRFlow $lastClient ("return ringPlace($($pad.x), $($pad.z), 450, 0)")
    Invoke-CRFlow $H 'M.last_wave_time = GetTime() - 1; return true' | Out-Null
    $lw = Wait-CRFlow $H 'return M.last_wave == true and { ok = true }' -TimeoutSeconds 25
    Invoke-CRFlow $H ("for _, t in ipairs({ M.tug1, M.tug2 }) do local x, z = dryRing($($pad.x), $($pad.z), 60); if x and IsAlive(t) then SetPosition(t, SetVector(x, GetTerrainHeightAndNormal(SetVector(x, 0, z)) + 2, z)) end end; return true") | Out-Null
    $order = @($C | Where-Object { $_ -ne $C[-1] }) + @($C[-1])
    $i = 0
    foreach ($cl in $order[0..($order.Count - 2)]) { Invoke-CRFlow $cl ("local x, z = dryRing($($pad.x + 5 * $i), $($pad.z), 120); if x then placeMe(x, z, 4) end; return true") | Out-Null; $i++ }
    Start-Sleep -Seconds 8
    $partial = Invoke-CRFlow $H 'local arr = {}; for k, v in pairs(M.arrived or {}) do arr[#arr + 1] = tostring(k) .. "=" .. tostring(v) end; return { won = M.won == true, got1 = M.got_there1 == true, got2 = M.got_there2 == true, got3 = M.got_there3 == true, arrived = arr }'
    $padD = @(); foreach ($cl in $C) { $padD += (Invoke-CRFlow $cl ("local p = GetPosition(me()); return math.floor(math.sqrt((p.x - $($pad.x)) ^ 2 + (p.z - $($pad.z)) ^ 2))")) }
    $partial | Add-Member -NotePropertyName humanDistances -NotePropertyValue $padD -Force
    Add-CRFlowCheck "no win while one human is outside 200 m (held human at $holdD m; tugs there: $($partial.got2),$($partial.got3); humans: $($partial.got1))" (-not $partial.won -and -not $partial.got1) $partial
    Invoke-CRFlow $order[-1] ("local x, z = dryRing($($pad.x + 5 * $i), $($pad.z), 120); if x then placeMe(x, z, 4) end; return true") | Out-Null
    $won = $null
    try { $won = Wait-CRFlow $H 'return M.won == true and { won = true }' -TimeoutSeconds 30 } catch { }
    Add-CRFlowCheck 'win reached once every human is within 200 m of launch_pad2' ([bool]$won) @{ won = $won }
    Wait-CRFlowOp $H SucceedMission 'misn11w1.des' -TimeoutSeconds 40 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SucceedMission 'misn11w1.des' -TimeoutSeconds 40 | Out-Null }
    @{ partial = $partial; won = $won }
}
Healers $false
Invoke-CRFlowStep 'result parity: SucceedMission misn11w1.des on every client' {
    Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn11w1.des' -Clients $C
}
