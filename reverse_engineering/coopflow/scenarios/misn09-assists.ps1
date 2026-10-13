# misn09 (Wrangling the Fleeing Herd) test assists. Everything the real mission
# gates behind long timers or a long drive is FORCED here through the host's Lua
# probe, and every forced step is labelled as an assist in its step name. None of
# this scripts a CR outcome: the mission's own code does the spawning, ordering,
# marking and winning; the assists only move a clock or arm a trigger.
#
#   1. Smoke: probes, roles, ready, play, full roster everywhere.
#   2. AIP evidence (assist: the host's player is moved next to the Unit Factory
#      so the real "factory reached" -> artillery film -> SetAIP("misn09.aip", 5)
#      chain runs). Team-5 object counts, scrap and pilots are sampled over time.
#   3. Convoy launch (assist: M.third_warning_time moved to now; the real
#      +1300 s timer). Checks the composition (4 svfigh, 4 svtank, 2 svapc,
#      1 svhaul plus 1 svtank and 1 svfigh per extra human team, capped at +3)
#      and that every guest sees the same team-5 units.
#   4. Convoy start (the real tug pickup of the relic).
#   5. Prescott's platoon, hunting (assist: M.prescott armed as the real 350 m
#      trigger would, minus the drive): 5 avtank on team 7, the "Commander
#      Prescott" marker on every peer, orders only name convoy combat units.
#   6. Prescott drive-in and victory (assist: the convoy is killed, which is a
#      real game state): the platoon heads for a player and SucceedMission
#      misn09w1.des reaches every peer.
param([int]$HostClient = 0,
      [int]$PlaySeconds = 20,
      # How long to watch team 5 after the artillery film ends and SetAIP ran.
      [int]$AipWatchSeconds = 100,
      [int]$ConvoyStartWaitSeconds = 240,
      [int]$PrescottHuntSeconds = 25)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$humans = $C.Count
$extras = [math]::Min(3, [math]::Max(0, $humans - 1))

$teamCount = @'
local function tc(team)
  local n, o = 0, {}
  for h in AllObjects() do
    if IsValid(h) and GetTeamNum(h) == team then
      local odf = (tostring(GetOdf(h) or "?"):gsub("%.odf$", ""))
      o[odf] = (o[odf] or 0) + 1
      n = n + 1
    end
  end
  return n, o
end
'@
$teamCount += "`n"

# Host-process memory reads for the team-5 AIP evidence (OpenShim GOG exe, 32-bit, fixed base).
Add-Type -ErrorAction SilentlyContinue -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class CRFlowMem {
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr OpenProcess(int a, bool i, int pid);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool ReadProcessMemory(IntPtr h, IntPtr addr, byte[] buf, int n, out int read);
  [DllImport("kernel32.dll")] public static extern bool CloseHandle(IntPtr h);
  public static long ReadU32(int pid, long addr, int size) {
    IntPtr h = OpenProcess(0x10, false, pid); if (h == IntPtr.Zero) return -2;
    try { byte[] b = new byte[4]; int r; if (!ReadProcessMemory(h, (IntPtr)addr, b, size, out r) || r != size) return -1;
      return size == 1 ? b[0] : (long)BitConverter.ToUInt32(b, 0); } finally { CloseHandle(h); }
  }
}
"@
function Get-CRFlowAiMemory([int]$ProcessId) {
    $u = { param($a, $n = 4) [CRFlowMem]::ReadU32($ProcessId, $a, $n) }
    $m = [ordered]@{}
    $m.aiControl5 = & $u 0x2CEA478 1
    $m.started = & $u 0x930F3C 1
    $ptr = & $u 0x920F04
    $m.recordsPtr = $ptr
    $rec = if ($ptr -gt 0) { & $u ($ptr + 0x14) } else { -1 }
    $m.team5Record = $rec
    if ($rec -gt 0) { $m.rec60 = & $u ($rec + 0x60); $m.recB4 = & $u ($rec + 0xB4) }
    $m.aiTick = & $u 0x931014
    $m.cashMirror = & $u 0x2CEA404
    [pscustomobject]$m
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

Invoke-CRFlowStep 'session ready and mission running on every client' {
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 90 | Out-Null }
    'coopMissionStarted on all'
}

Invoke-CRFlowStep "$PlaySeconds s of play; every peer alive, full roster" {
    Start-Sleep -Seconds $PlaySeconds
    foreach ($client in $C) {
        $s = Invoke-CRFlow $client 'local me = me(); local d = describe(me); return { alive = d.alive, valid = d.valid, odf = d.odf, team = d.team, players = #players(), result = M.coopResult == true }'
        Add-CRFlowCheck "c$client alive with its own craft" ($s.valid -and $s.alive -and -not $s.result) $s
        Add-CRFlowCheck "c$client sees all $humans players" ($s.players -eq $humans) $s
    }
}

Invoke-CRFlowStep 'start state: team-5 census, positions of the base, factory, geyser' {
    $r = Invoke-CRFlow $H ($teamCount + @'
local n, o = tc(5)
local out = { n = n, odfs = o, scrap = GetScrap(5), pilots = GetPilot(5), t = GetTime(), aiControl = nil }
out.muf = describe(M.nsdfmuf)
out.geyser = describe(M.convoy_geyser)
out.cutoff = describe(M.cut_off_geyser)
out.me = describe(me())
out.mufContact = M.muf_contact == true
out.gobaby = M.muf_gobaby == true
return out
'@)
    $script:StartCensus = $r
    $r
}

# ---------------------------------------------------------------- AIP --
Invoke-CRFlowStep 'ASSIST: move the host next to the Unit Factory; artillery film; SetAIP("misn09.aip", 5)' -Soft {
    $before = Invoke-CRFlow $H ($teamCount + 'local n, o = tc(5); return { n = n, odfs = o, scrap = GetScrap(5), pilots = GetPilot(5), t = GetTime() }')
    # The factory only waits for the player once the opening voice-over reports done (AudioDone); muted test clients can leave that unset, so\n    # the assist sets the same flag (without the return_path Goto) when it has not come by itself.\n    $gobaby = $null; try { $gobaby = Wait-CRFlow $H 'return M.muf_gobaby == true and "natural"' -TimeoutSeconds 45 } catch { }\n    if (-not $gobaby) { Invoke-CRFlow $H 'M.muf_gobaby = true; return "forced"' | Out-Null; $gobaby = 'forced (AudioDone never reported)' }\n    $moved = Invoke-CRFlow $H 'return tp("nsdfmuf", 45)'
    $reached = $null; $diag = $null; $forcedContact = $false
    try { $reached = Wait-CRFlow $H 'return M.cam_off == true and { t = GetTime(), camOff = true }' -TimeoutSeconds 60 } catch {
        $diag = Invoke-CRFlow $H 'local d = -1; for _, rec in pairs(CRCoop.GetPlayers() or {}) do if rec.handle and IsValid(rec.handle) and GetTeamNum(rec.handle) == 1 then d = GetDistance(rec.handle, M.nsdfmuf) end end; return { contact = M.muf_contact == true, gobaby = M.muf_gobaby == true, cameraReady = M.camera_ready == true, turret6 = IsAlive(M.ccaturret6) and true or false, hostToMuf = d, mufAlive = IsAlive(M.nsdfmuf) and true or false }'
        Write-Host ('[aip] natural factory contact did not fire in 60 s: ' + (ConvertTo-Json $diag -Compress) + '; forcing M.muf_contact')
        $forcedContact = $true
        Invoke-CRFlow $H 'M.muf_contact = true; M.movie_time = GetTime(); return true' | Out-Null
        $reached = Wait-CRFlow $H 'return M.cam_off == true and { t = GetTime(), camOff = true }' -TimeoutSeconds 90
    }
    foreach ($client in $guests) { Wait-CRFlowOp $client CameraFinish -TimeoutSeconds 30 | Out-Null }
    $script:AipStart = $reached.t
    @{ before = $before; forcedContact = $forcedContact; contactDiag = $diag; gobaby = $gobaby; moved = $moved; reached = $reached }
}

Invoke-CRFlowStep "AIP: team-5 objects, scrap and pilots for $AipWatchSeconds s after SetAIP (host)" -Soft {
    $count = $teamCount + 'local n, o = tc(5); local ok, aip = pcall(GetAIP, 5); return { n = n, odfs = o, scrap = GetScrap(5), pilots = GetPilot(5), t = GetTime(), me = describe(me()).alive, aip = ok and tostring(aip) or ("n/a: " .. tostring(aip)), setAip = M.cam_off == true }'
    $hostPid = [int](Get-CRFlowSession).clients[$H].pid
    $mems = @()
    $samples = @()
    $first = Invoke-CRFlow $H $count
    $samples += $first
    $mems += (Get-CRFlowAiMemory $hostPid)
    $deadline = (Get-Date).AddSeconds($AipWatchSeconds)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Seconds 20
        Invoke-CRFlow $H 'heal(me()); return true' | Out-Null
        $samples += (Invoke-CRFlow $H $count)
        $mems += (Get-CRFlowAiMemory $hostPid)
    }
    $last = $samples[-1]
    $peak = ($samples | Measure-Object -Property n -Maximum).Maximum
    $newOdfs = @()
    foreach ($k in $last.odfs.PSObject.Properties.Name) {
        $was = 0; if ($first.odfs.PSObject.Properties.Name -contains $k) { $was = $first.odfs.$k }
        if ($last.odfs.$k -gt $was) { $newOdfs += "$k +$($last.odfs.$k - $was)" }
    }
    Add-CRFlowCheck "team 5 grew under misn09.aip ($($first.n) -> $($last.n) objects, peak $peak; scrap $($first.scrap) -> $($last.scrap); $($newOdfs -join ', '))" ($last.n -gt $first.n -or $peak -gt $first.n) @{ first = $first; last = $last } -WarnOnly
    Write-Host ("[aip] team-5 objects {0} -> {1} (peak {2}), scrap {3} -> {4}, pilots {5} -> {6}; grew: {7}" -f $first.n, $last.n, $peak, $first.scrap, $last.scrap, $first.pilots, $last.pilots, ($newOdfs -join ', '))
    for ($i = 0; $i -lt $samples.Count; $i++) { Write-Host ('[aip] t={0,7:N0} n={1,3} scrap={2,4} aip={3} | mem {4}' -f $samples[$i].t, $samples[$i].n, $samples[$i].scrap, $samples[$i].aip, ($mems[$i] | ConvertTo-Json -Compress)) }
    @{ samples = $samples; memory = $mems; grew = $newOdfs }
}

# ------------------------------------------------------------- convoy --
Invoke-CRFlowStep 'ASSIST: convoy launch (M.third_warning_time := now): composition, scaling, replicas' {
    $far = Invoke-CRFlow $H @'
local worst = math.huge
for _, rec in pairs(CRCoop.GetPlayers() or {}) do
  if rec.handle and IsValid(rec.handle) then worst = math.min(worst, GetDistance(rec.handle, M.convoy_geyser)) end
end
return { nearestPlayerToGeyser = worst }
'@
    $before = Invoke-CRFlow $H ($teamCount + 'local n, o = tc(5); return { n = n, odfs = o }')
    $forced = Invoke-CRFlow $H 'M.third_warning_time = GetTime() - 1; return { forcedAt = GetTime(), thirdWarning = M.third_warning == true }'
    $built = Wait-CRFlow $H 'return M.third_warning == true and M.ccatug ~= nil and { t = GetTime() }' -TimeoutSeconds 60
    Start-Sleep -Seconds 3
    # Exact composition from the mission's own handles on the host.
    $exact = Invoke-CRFlow $H @'
local out = { svfigh = 0, svtank = 0, svapc = 0, svhaul = 0, extraTanks = 0, extraFighters = 0, extraTotal = 0 }
local function odf(h) return (tostring(GetOdf(h) or "?"):gsub("%.odf$", "")) end
local base = { M.ccatug, M.convoy1, M.convoy2, M.convoy3, M.convoy4, M.convoy5, M.convoy6, M.convoy7, M.convoy8, M.convoy9, M.convoy0 }
for _, h in ipairs(base) do
  if h ~= nil and IsValid(h) then local o = odf(h); out[o] = (out[o] or 0) + 1; if GetTeamNum(h) ~= 5 then out.wrongTeam = (out.wrongTeam or 0) + 1 end end
end
for _, h in ipairs(M.convoy_extra or {}) do
  if IsValid(h) then
    out.extraTotal = out.extraTotal + 1
    local o = odf(h)
    if o == "svtank" then out.extraTanks = out.extraTanks + 1 elseif o == "svfigh" then out.extraFighters = out.extraFighters + 1 end
    if GetTeamNum(h) ~= 5 then out.wrongTeam = (out.wrongTeam or 0) + 1 end
  end
end
out.relic = describe(M.relic)
return out
'@
    $after = Invoke-CRFlow $H ($teamCount + 'local n, o = tc(5); return { n = n, odfs = o }')
    Add-CRFlowCheck "base convoy: 4 svfigh + 4 svtank (+ extras) + 2 svapc + 1 svhaul, all team 5 ($humans humans)" `
        ($exact.svfigh -eq 4 -and $exact.svtank -eq 4 -and $exact.svapc -eq 2 -and $exact.svhaul -eq 1 -and -not $exact.wrongTeam) $exact
    Add-CRFlowCheck "convoy scaling: +$extras svtank and +$extras svfigh for $humans humans" `
        ($exact.extraTanks -eq $extras -and $exact.extraFighters -eq $extras -and $exact.extraTotal -eq (2 * $extras)) $exact
    Add-CRFlowCheck "relic built (neutral team 0)" ($exact.relic.valid -and $exact.relic.team -eq 0) $exact.relic
    $hostAfter = $after
    foreach ($client in $guests) {
        $g = Wait-CRFlow $client ($teamCount + 'local n, o = tc(5); local want = ' + [int]$hostAfter.n + '; return n >= want and { n = n, odfs = o }') -TimeoutSeconds 45
        $same = $true
        foreach ($k in 'svfigh', 'svtank', 'svapc', 'svhaul') {
            if ($g.odfs.$k -ne $hostAfter.odfs.$k) { $same = $false }
        }
        Add-CRFlowCheck "c$client sees the host's team-5 units (svfigh/svtank/svapc/svhaul equal, $($g.n) objects)" $same @{ host = $hostAfter.odfs; guest = $g.odfs }
    }
    @{ nearestPlayer = $far; before = $before; exact = $exact; hostTeam5 = $after }
}

Invoke-CRFlowStep 'convoy starts (the CCA tug takes the relic; the real pickup)' {
    $started = Wait-CRFlow $H 'return M.convoy_started == true and { t = GetTime(), seized = M.relic_seized == true, tug = describe(M.ccatug) }' -TimeoutSeconds $ConvoyStartWaitSeconds
    foreach ($client in $guests) { Wait-CRFlowOp $client Play 'misn0903.wav' -TimeoutSeconds 60 | Out-Null }
    $started
}

# ----------------------------------------------------------- Prescott --
Invoke-CRFlowStep "ASSIST: arm Prescott's platoon with the convoy alive (the 350 m trigger); hunt for $PrescottHuntSeconds s" {
    $armed = Invoke-CRFlow $H 'if M.prescott == nil then M.prescott = { due = GetTime() + 3.0, spawned = false, units = {}, orders = {}, next = 0 }; return "armed" end; return "already armed"'
    $sp = Wait-CRFlow $H 'return M.prescott ~= nil and M.prescott.spawned == true and { t = GetTime(), units = #M.prescott.units }' -TimeoutSeconds 60
    Start-Sleep -Seconds 5
    $plat = Invoke-CRFlow $H @'
local out = { avtank = 0, wrongTeam = 0, units = #M.prescott.units }
for _, h in ipairs(M.prescott.units) do
  if IsValid(h) then
    if (tostring(GetOdf(h) or ""):gsub("%.odf$", "")) == "avtank" then out.avtank = out.avtank + 1 end
    if GetTeamNum(h) ~= 7 then out.wrongTeam = out.wrongTeam + 1 end
  end
end
out.leader = describe(M.prescott.leader)
out.marked = M.prescott.marked == true
local p = GetPosition(M.prescott.leader)
local nearest, best = nil, math.huge
for _, rec in pairs(CRCoop.GetPlayers()) do
  if rec.handle and IsValid(rec.handle) then local d = GetDistance(M.prescott.leader, rec.handle); if d < best then best = d end end
end
out.leaderToNearestHuman = best
out.rear = M.convoy_rear
return out
'@
    Add-CRFlowCheck 'Prescott: 5 avtank on team 7 spawned by the real SpawnPrescott' ($plat.avtank -eq 5 -and $plat.wrongTeam -eq 0 -and $plat.units -eq 5) $plat
    Add-CRFlowCheck 'Prescott: leader is the middle tank and carries the marker' ($plat.leader.valid -and $plat.marked) $plat
    Wait-CRFlowOp $H SetObjectiveName 'Commander Prescott' -TimeoutSeconds 20 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SetObjectiveName 'Commander Prescott' -TimeoutSeconds 25 | Out-Null }
    Add-CRFlowCheck 'Prescott: the "Commander Prescott" objective name reached the host and every guest' $true
    foreach ($client in $guests) {
        $g = Wait-CRFlow $client ($teamCount + 'local n, o = tc(7); return o.avtank == 5 and { n = n, odfs = o }') -TimeoutSeconds 45
        Add-CRFlowCheck "c$client sees 5 team-7 avtank" ($g.odfs.avtank -eq 5) $g
    }
    Start-Sleep -Seconds $PrescottHuntSeconds
    $orders = Invoke-CRFlow $H @'
local names, bad = {}, 0
for i, t in pairs(M.prescott.orders) do
  if t and t ~= false and IsValid(t) then
    local o = (tostring(GetOdf(t) or "?"):gsub("%.odf$", ""))
    names[#names + 1] = o
    if o == "svhaul" or o == "svapc" or o == "sblpad" then bad = bad + 1 end
  end
end
local alive = 0
for _, h in ipairs(M.prescott.units) do if IsAlive(h) then alive = alive + 1 end end
return { targets = names, badTargets = bad, platoonAlive = alive, convoyAlive = (function() local n = 0 for h in AllCraft() do if GetTeamNum(h) == 5 and IsAlive(h) then local o = (tostring(GetOdf(h) or ""):gsub("%.odf$", "")); if o == "svfigh" or o == "svtank" or o == "svapc" or o == "svhaul" then n = n + 1 end end end return n end)() }
'@
    Add-CRFlowCheck 'Prescott hunting: attack orders name only convoy combat units (no tug, APC or pad)' ($orders.badTargets -eq 0 -and @($orders.targets).Count -gt 0) $orders
    $orders
}

Invoke-CRFlowStep 'ASSIST: destroy the convoy (a real state); Prescott drives in to a player; victory' {
    $killed = 0
    foreach ($pat in 'svfigh', 'svtank', 'svapc', 'svhaul') {
        $killed += [int](Invoke-CRFlow $H "return killTeam(5, '$pat')")
    }
    # Keep the humans (and so the win preconditions) alive during the drive.
    $tStart = Get-Date
    $drive = Wait-CRFlow $H 'return M.prescott ~= nil and M.prescott.destroyed == true and M.prescott.driveStart ~= nil and { t = GetTime(), driveStart = M.prescott.driveStart }' -TimeoutSeconds 60
    $track = @()
    $won = $null
    $deadline = (Get-Date).AddSeconds(190)
    while ((Get-Date) -lt $deadline) {
        $row = Invoke-CRFlow $H @'
local best = math.huge
if M.prescott and M.prescott.leader and IsValid(M.prescott.leader) then
  for _, rec in pairs(CRCoop.GetPlayers()) do
    if rec.handle and IsValid(rec.handle) then best = math.min(best, GetDistance(M.prescott.leader, rec.handle)) end
  end
end
return { t = GetTime(), leaderToHuman = best, won = M.prescott and M.prescott.won or nil, gameOver = M.game_over == true,
  leaderAlive = M.prescott and IsAlive(M.prescott.leader) or false }
'@
        $track += $row
        if ($row.won) { $won = $row.won; break }
        Start-Sleep -Seconds 8
    }
    Add-CRFlowCheck "convoy units destroyed ($killed damaged)" ($killed -gt 0) @{ killed = $killed }
    $first = ($track | Where-Object { $_.leaderToHuman -lt 1e8 } | Select-Object -First 1)
    $last = ($track | Where-Object { $_.leaderToHuman -lt 1e8 } | Select-Object -Last 1)
    if ($first -and $last) {
        Write-Host ("[prescott] leader to nearest human {0:N0} m -> {1:N0} m over {2:N0} s; win reason: {3}" -f $first.leaderToHuman, $last.leaderToHuman, ($last.t - $first.t), $won)
    }
    Add-CRFlowCheck 'Prescott drive-in: leader approaches a human (distance shrinks)' ($first -and $last -and ($last.leaderToHuman -lt $first.leaderToHuman -or $won -eq 'arrived')) @{ track = $track }
    Add-CRFlowCheck "victory armed by WinThroughPrescott (reason: $won)" ([bool]$won) @{ won = $won }
    Wait-CRFlowOp $H SucceedMission 'misn09w1.des' -TimeoutSeconds 30 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SucceedMission 'misn09w1.des' -TimeoutSeconds 30 | Out-Null }
    @{ reason = $won; track = $track }
}

Invoke-CRFlowStep 'result parity: SucceedMission misn09w1.des on every client' {
    Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn09w1.des' -Clients $C
}
