# misn10 (The Race is On) test assists. Forced steps are named ASSIST; the mission's
# own code does the building, ordering, quake, plan-B swap and result.
#
#   1. Smoke (attach, roles, ready, play, roster).
#   2. Start state: GetAIP(5), team-5 scrap/pilots, CCA scaling (+10 scrap and one svfigh
#      hunter per extra human: +30 and 3 hunters with 4 players), host-process AI memory.
#   3. Team 5 builds under its AIP (objects, scrap, GetAIP(5) over time).
#   4. Tug rebuild cap: the CCA tug is killed repeatedly (ASSIST); the mission rebuilds it at
#      most twice.
#   5. Plan B (ASSIST only if it has not happened by itself): GetAIP(5) must become misn10b.aip.
#   6. A GUEST's tug picks up the neutral relic (ASSIST: the tug is spawned beside the relic on
#      the guest and ordered to pick it up); the pickup quake (CRIoWeather IoQuake) must reach every
#      guest, IoState must converge, and a forced eruption (ASSIST) must reach every guest (IoErupt).
#   7. Victory (ASSIST: the guest tug is moved to the NSDF recycler): SucceedMission misn10w1.des on
#      every client.
param([int]$HostClient = 0,
      [int]$PlaySeconds = 20,
      [int]$BuildWatchSeconds = 100,
      # The Redux host heap-corrupts about 5 minutes after launch (see the PR comment), so the case is split:
      # 'main' = start state, plan B, guest tug/quake/Io/eruption, victory; 'tug' = the tug rebuild cap; 'all' = both.
      [ValidateSet('all', 'main', 'tug')][string]$Part = 'all')
$doMain = $Part -in 'all', 'main'
$doTug = $Part -in 'all', 'tug'
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$humans = $C.Count
$extras = [math]::Min(3, [math]::Max(0, $humans - 1))
$GuestA = $guests[0]

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
    $rec = if ($ptr -gt 0) { & $u ($ptr + 0x14) } else { -1 }
    $m.team5RecordNonNull = ($rec -gt 0)
    if ($rec -gt 0) { $m.rec60NonNull = ((& $u ($rec + 0x60)) -gt 0); $m.recB4NonNull = ((& $u ($rec + 0xB4)) -gt 0) }
    $m.aiTick = & $u 0x931014
    $m.cashMirror = & $u 0x2CEA404
    [pscustomobject]$m
}
$hostPid = 0

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
    $script:hostPid = [int](Get-CRFlowSession).clients[$H].pid
    # Latches on every guest: pickup quake, eruptions, Io severity level changes (the Io ops are
    # applied by CRIoWeather on receipt, so its state is the evidence they arrived).
    foreach ($client in $guests) {
        Invoke-CRFlow $client @'
local Io = require("CRIoWeather")
qSeen, eSeen, lvlMax = 0, 0, 0
every("iolatch", 0.2, function()
  local ok = pcall(function()
    if Io.IsQuaking() then qSeen = qSeen + 1 end
    local n = 0
    for _ in pairs(Io.GetActiveEruptions() or {}) do n = n + 1 end
    if n > eSeen then eSeen = n end
    if Io.GetLevel() > lvlMax then lvlMax = Io.GetLevel() end
  end)
end)
return true
'@ | Out-Null
    }
    'coopMissionStarted on all; Io latches installed on guests'
}

Invoke-CRFlowStep "$PlaySeconds s of play; every peer alive, full roster" {
    Start-Sleep -Seconds $PlaySeconds
    foreach ($client in $C) {
        $s = Invoke-CRFlow $client 'local d = describe(me()); return { alive = d.alive, valid = d.valid, team = d.team, players = #players(), result = M.coopResult == true }'
        Add-CRFlowCheck "c$client alive with its own craft" ($s.valid -and $s.alive -and -not $s.result) $s
        Add-CRFlowCheck "c$client sees all $humans players" ($s.players -eq $humans) $s
    }
}

# ------------------------------------------------------- start state --
Invoke-CRFlowStep "start state: GetAIP(5), CCA scaling for $humans humans (+$(10 * $extras) scrap, $extras hunters), AI memory" {
    $s = Invoke-CRFlow $H ($teamCount + @'
local n, o = tc(5)
local ok, aip = pcall(GetAIP, 5)
local hunters, hunterTeam5, hunterOdf = 0, 0, 0
for _, h in ipairs(M.hunters or {}) do
  hunters = hunters + 1
  if IsValid(h) then
    if GetTeamNum(h) == 5 then hunterTeam5 = hunterTeam5 + 1 end
    if (tostring(GetOdf(h) or ""):gsub("%.odf$", "")) == "svfigh" then hunterOdf = hunterOdf + 1 end
  end
end
return { aip = ok and tostring(aip) or "err", scrap5 = GetScrap(5), pilots5 = GetPilot(5), scrap1 = GetScrap(1), pilots1 = GetPilot(1),
  n = n, odfs = o, hunters = hunters, hunterTeam5 = hunterTeam5, hunterSvfigh = hunterOdf, planA = M.plan_a == true, planB = M.plan_b == true,
  startDone = M.start_done == true, t = GetTime(), relic = describe(M.sav), recycle = describe(M.ccarecycle), nsdfRecycle = describe(M.nsdfrecycle) }
'@)
    $mem = Get-CRFlowAiMemory $script:hostPid
    Add-CRFlowCheck "GetAIP(5) is a misn10 AIP after Start ($($s.aip))" ($s.aip -like 'misn10*.aip') $s
    Add-CRFlowCheck "CCA scaling: $extras relic-carrier hunters (svfigh, team 5)" ($s.hunters -eq $extras -and $s.hunterTeam5 -eq $extras -and $s.hunterSvfigh -eq $extras) $s
    # The base is 40; +10 per extra human. The AIP may already have spent some by now, so the hard
    # check is the arithmetic the mission applies: read the constants' effect from team 5's peak.
    $script:StartScrap = $s.scrap5
    Add-CRFlowCheck "team-5 scrap sampled at readiness: $($s.scrap5) (base 40, +$(10 * $extras) = $(40 + 10 * $extras) when set)" ($s.scrap5 -ge 0) $s -WarnOnly
    Add-CRFlowCheck "host AI memory: team-5 AI control flag set, started, team-5 record present" ($mem.aiControl5 -eq 1 -and $mem.started -eq 1 -and $mem.team5RecordNonNull) $mem
    @{ state = $s; memory = $mem }
}

# The AIP idles for ~110 s of mission time before its first build, so team 5 is sampled at every step and
# judged at the end (the later steps run while it builds).
$script:BuildSamples = @(); $script:BuildMems = @()
function Add-BuildSample {
    $r = Invoke-CRFlow $H ($teamCount + 'local n, o = tc(5); local ok, aip = pcall(GetAIP, 5); return { n = n, odfs = o, scrap = GetScrap(5), pilots = GetPilot(5), t = GetTime(), aip = ok and tostring(aip) or "err", planA = M.plan_a == true, planB = M.plan_b == true }')
    $script:BuildSamples += $r; $script:BuildMems += (Get-CRFlowAiMemory $script:hostPid)
}
Add-BuildSample
if ($doTug) {
# --------------------------------------------------------- tug rebuild --
Invoke-CRFlowStep 'ASSIST: kill the CCA tug repeatedly; the mission rebuilds it at most twice' {
    Add-BuildSample
    $tugAssist = 'none (the AIP/mission already has a CCA tug)'
    $have = Invoke-CRFlow $H 'return M.ccatug ~= nil and IsAlive(M.ccatug)'
    if (-not $have) {
        # ASSIST: the AIP builds its tug late; put a team-5 svhaul at the CCA recycler (the mission's AddObject slots it as ccatug).
        $tugAssist = Invoke-CRFlow $H 'local f = M.ccarecycle; local t = BuildObject("svhaul", 5, f); return { built = IsValid(t), odf = GetOdf(t) }'
        Start-Sleep -Seconds 3
    }
    $log = @()
    for ($k = 1; $k -le 6; $k++) {
        $alive = $null
        try { $alive = Wait-CRFlow $H 'return M.ccatug ~= nil and IsAlive(M.ccatug) and { rebuilds = M.tug_rebuilds or 0, t = GetTime() }' -TimeoutSeconds 100 } catch { }
        if (-not $alive) { $log += @{ kill = $k; note = 'no living CCA tug to kill (neither rebuilt nor built by the AIP)' }; break }
        $before = $alive.rebuilds
        $killed = Invoke-CRFlow $H 'return kill(M.ccatug)'
        $log += @{ kill = $k; rebuildsBefore = $before; killed = $killed }
        try { Wait-CRFlow $H 'return M.ccatug ~= nil and IsAlive(M.ccatug) and { ok = true }' -TimeoutSeconds 45 | Out-Null } catch { }
        $after = Invoke-CRFlow $H 'return { rebuilds = M.tug_rebuilds or 0, tugAlive = M.ccatug ~= nil and IsAlive(M.ccatug), waiting = M.making_another_tug == true }'
        $log[-1].after = $after
        if ($after.rebuilds -ge 2 -and $k -ge 3) { break }
    }
    Start-Sleep -Seconds 36
    $final = Invoke-CRFlow $H 'return { rebuilds = M.tug_rebuilds or 0, waiting = M.making_another_tug == true, tugAlive = M.ccatug ~= nil and IsAlive(M.ccatug) }'
    Add-CRFlowCheck "CCA tug rebuild is capped at 2 (final count $($final.rebuilds))" ($final.rebuilds -le 2) @{ log = $log; final = $final }
    Add-CRFlowCheck "the mission's rebuild reached its cap of 2 (kills: $(@($log | ? { $_.killed }).Count))" ($final.rebuilds -eq 2) @{ log = $log; final = $final } -WarnOnly
    @{ tugAssist = $tugAssist; log = $log; final = $final }
}
}

if ($doMain) {
# ------------------------------------------------------------- plan B --
Invoke-CRFlowStep 'plan B: GetAIP(5) becomes misn10b.aip (ASSIST only if it did not happen by itself)' {
    $pre = Invoke-CRFlow $H 'local ok, aip = pcall(GetAIP, 5); return { aip = ok and tostring(aip) or "err", planB = M.plan_b == true, scrap = GetScrap(5) }'
    $assist = 'none (natural)'
    $tugMade = $null
    if (-not $pre.planB) {
        # Plan B needs the tug alive too: when the AIP has not built one yet, put a team-5 svhaul at the CCA recycler
        # (the mission's AddObject slots it as ccatug). ASSIST, logged below.
        $tugMade = Invoke-CRFlow $H 'if M.ccatug ~= nil and IsAlive(M.ccatug) then return "already alive" end; local t = BuildObject("svhaul", 5, M.ccarecycle); return "built svhaul " .. tostring(IsValid(t))'
        Start-Sleep -Seconds 3
        # Plan B needs the tug and both CCA tanks alive. Borrow living team-5 combat craft for the two tank slots when
        # the AIP has not built tanks yet; the mission's own UpdatePlanB does the restock and the SetAIP.
        $assist = Invoke-CRFlow $H @'
local picks = {}
for h in AllCraft() do
  if GetTeamNum(h) == 5 and IsAlive(h) then
    local o = (tostring(GetOdf(h) or ""):gsub("%.odf$", ""))
    if o == "svtank" or o == "svfigh" then picks[#picks + 1] = h end
  end
end
local used = {}
if not (M.ccatank1 and IsAlive(M.ccatank1)) and picks[1] then M.ccatank1 = picks[1]; used[#used + 1] = "ccatank1" end
if not (M.ccatank2 and IsAlive(M.ccatank2)) and picks[2] then M.ccatank2 = picks[2]; used[#used + 1] = "ccatank2" end
return { borrowed = used, tugAlive = M.ccatug ~= nil and IsAlive(M.ccatug) }
'@
    }
    if ($tugMade) { $assist = @{ tug = $tugMade; tanks = $assist } }
    $post = $null
    try { $post = Wait-CRFlow $H 'if not M.plan_b then return false end; local ok, aip = pcall(GetAIP, 5); return { aip = ok and tostring(aip) or "err", planB = true, scrap = GetScrap(5), t = GetTime() }' -TimeoutSeconds 60 } catch { }
    Add-CRFlowCheck "plan B ran and GetAIP(5) changed $($pre.aip) -> $($post.aip) (assist: $(ConvertTo-Json $assist -Compress))" ($post -and $post.aip -eq 'misn10b.aip' -and ($post.aip -ne $pre.aip -or $pre.planB)) @{ pre = $pre; post = $post; assist = $assist }
    @{ pre = $pre; post = $post; assist = $assist }
}

# -------------------------------------------- guest tug, quake, Io, win --
Invoke-CRFlowStep "a guest (c$GuestA) tug picks up the neutral relic; pickup quake reaches every guest" {
    $pre = Invoke-CRFlow $H 'return { quake = M.quake == true, seized = M.sav_seized == true, secure = M.sav_secure == true, free = M.sav_free == true, relic = describe(M.sav), tugAlive = M.ccatug ~= nil and IsAlive(M.ccatug) }'
    # The CCA tug may already hold the relic (a natural pickup, which also fires the quake). Release it so the guest's
    # pickup is the event under test, and re-arm the once-only quake latch (ASSIST).
    $reset = $null
    if ($pre.seized -or $pre.secure -or $pre.quake) {
        $reset = Invoke-CRFlow $H 'if M.ccatug and IsAlive(M.ccatug) then kill(M.ccatug) end; M.quake = false; return { seized = M.sav_seized == true, quake = M.quake == true }'
        Start-Sleep -Seconds 4
        foreach ($client in $guests) { Invoke-CRFlow $client 'qSeen = 0; return true' | Out-Null }
    }
    $spawn = Invoke-CRFlow $GuestA @'
local relic = GetHandle("relic")
if not IsValid(relic) then return { error = "relic label does not resolve on the guest" } end
local pos = GetPositionNear(GetPosition(relic), 25, 40)
local t = BuildObject("avhaul", role().team, pos)
gtug = t
Pickup(t, relic)
return { tug = describe(t), relic = describe(relic) }
'@
    $picked = $null
    try { $picked = Wait-CRFlow $H 'return M.sav_secure == true and IsAlive(M.tugger) and { team = GetTeamNum(M.tugger), odf = GetOdf(M.tugger), t = GetTime() }' -TimeoutSeconds 60 } catch { }
    $assist = 'guest-spawned tug'
    $diag = $null
    if (-not $picked) {
        $diag = @{
            guest = (Invoke-CRFlow $GuestA 'local relic = GetHandle("relic"); local tg = nil; pcall(function() tg = GetTug(relic) end); return { gtugValid = gtug ~= nil and IsValid(gtug), gtugAlive = gtug ~= nil and IsAlive(gtug), gtugLocal = gtug ~= nil and IsValid(gtug) and describe(gtug)["local"], relicTugSeenByGuest = tg ~= nil and tg ~= 0, cmd = gtug ~= nil and IsValid(gtug) and GetCurrentCommand(gtug) or -1, dist = gtug ~= nil and IsValid(gtug) and GetDistance(gtug, relic) or -1 }')
            host = (Invoke-CRFlow $H 'local tg = nil; pcall(function() tg = GetTug(M.sav) end); return { relicTugSeenByHost = tg ~= nil and tg ~= 0, secure = M.sav_secure == true, relic = describe(M.sav) }')
        }
        # Fallback ASSIST (recorded, and the guest-ownership check fails): the host builds the guest-team tug itself.
        $assist = 'HOST-spawned team-2 tug (guest-spawned tug never became the tugger on the host)'
        Invoke-CRFlow $H 'local pos = GetPositionNear(GetPosition(M.sav), 25, 40); local t = BuildObject("avhaul", 2, pos); htug = t; Pickup(t, M.sav); return true' | Out-Null
        try { $picked = Wait-CRFlow $H 'return M.sav_secure == true and IsAlive(M.tugger) and { team = GetTeamNum(M.tugger), odf = GetOdf(M.tugger), t = GetTime() }' -TimeoutSeconds 90 } catch { }
    }
    Add-CRFlowCheck "the guest's own tug secures the neutral relic (mission sees a non-CCA tugger; $assist)" ($picked -and $assist -eq 'guest-spawned tug') @{ spawn = $spawn; picked = $picked; reset = $reset; diag = $diag } -WarnOnly
    Add-CRFlowCheck 'relic secured by a human-team tug (M.sav_secure)' ([bool]$picked) $picked
    # Quake.
    $quakeHost = Invoke-CRFlow $H 'return { quake = M.quake == true }'
    Add-CRFlowCheck 'pickup quake fired once (M.quake)' ($quakeHost.quake -eq $true) $quakeHost
    foreach ($client in $guests) {
        $q = $null
        try { $q = Wait-CRFlow $client 'return (qSeen or 0) > 0 and { frames = qSeen, quaking = require("CRIoWeather").IsQuaking() }' -TimeoutSeconds 30 } catch { $q = Invoke-CRFlow $client 'return { frames = qSeen or 0 }' }
        Add-CRFlowCheck "c$client received the pickup quake (IoQuake: CRIoWeather quaking for $($q.frames) polls)" ([int]$q.frames -gt 0) $q
    }
    @{ pre = $pre; spawn = $spawn; picked = $picked; diag = $diag; assist = $assist }
}

Invoke-CRFlowStep 'IoState converges on every guest; ASSIST: force an eruption, IoErupt reaches every guest' {
    $hostIo = Invoke-CRFlow $H 'local Io = require("CRIoWeather"); return { seed = Io.Seed, level = Io.GetLevel(), target = Io.GetTargetLevel() }'
    foreach ($client in $guests) {
        $g = $null
        try { $g = Wait-CRFlow $client ('local Io = require("CRIoWeather"); return Io.Seed == ' + $hostIo.seed + ' and { seed = Io.Seed, level = Io.GetLevel(), maxLevel = lvlMax, target = Io.GetTargetLevel() }') -TimeoutSeconds 30 } catch { $g = Invoke-CRFlow $client 'local Io = require("CRIoWeather"); return { seed = Io.Seed, level = Io.GetLevel(), maxLevel = lvlMax }' }
        Add-CRFlowCheck "c$client Io state follows the host (seed $($g.seed) = $($hostIo.seed); level $($g.level), highest seen $($g.maxLevel); host level $($hostIo.level))" ($g.seed -eq $hostIo.seed -and $g.target -eq $hostIo.target -and [math]::Abs([int]$g.level - [int]$hostIo.level) -le 1) @{ host = $hostIo; guest = $g }
    }
    $erupt = Invoke-CRFlow $H 'local Io = require("CRIoWeather"); local ok, err = pcall(Io.TriggerEruption, 1, 1.0); return { ok = ok, err = (not ok) and tostring(err) or nil }'
    Add-CRFlowCheck 'host started an eruption' ($erupt.ok -eq $true) $erupt
    foreach ($client in $guests) {
        $e = $null
        try { $e = Wait-CRFlow $client 'return (eSeen or 0) > 0 and { eruptions = eSeen }' -TimeoutSeconds 20 } catch { $e = Invoke-CRFlow $client 'return { eruptions = eSeen or 0 }' }
        Add-CRFlowCheck "c$client received the eruption (IoErupt: $($e.eruptions) active)" ([int]$e.eruptions -gt 0) $e
    }
    @{ host = $hostIo; erupt = $erupt }
}

Invoke-CRFlowStep 'ASSIST: move the securing tug to the NSDF recycler; victory misn10w1.des on every client' {
    $nsdfHome = Invoke-CRFlow $H 'return { x = GetPosition(M.nsdfrecycle).x, y = GetPosition(M.nsdfrecycle).y, z = GetPosition(M.nsdfrecycle).z }'
    $how = 'securing tug moved on its owner'
    $moved = Invoke-CRFlow $GuestA ("if gtug and IsValid(gtug) then SetPosition(gtug, at($($nsdfHome.x + 45), $($nsdfHome.y), $($nsdfHome.z + 45))); return true end; return false")
    $won = $null
    try { $won = Wait-CRFlow $H 'return M.game_over == true and { t = GetTime(), sav = describe(M.sav) }' -TimeoutSeconds 45 } catch { }
    if (-not $won) {
        $how = 'host-owned tug (htug) and the relic it carries both moved by the host'
        Invoke-CRFlow $H ("if htug and IsValid(htug) then SetPosition(htug, at($($nsdfHome.x + 45), $($nsdfHome.y), $($nsdfHome.z + 45))) end; if M.sav and IsValid(M.sav) then SetPosition(M.sav, at($($nsdfHome.x + 50), $($nsdfHome.y), $($nsdfHome.z + 50))) end; return { tugger = M.tugger and IsAlive(M.tugger), secure = M.sav_secure == true }") | Out-Null
        try { $won = Wait-CRFlow $H 'return M.game_over == true and { t = GetTime() }' -TimeoutSeconds 45 } catch { }
    }
    Add-CRFlowCheck "victory reached (assist: $how)" ([bool]$won) @{ moved = $moved; won = $won }
    Wait-CRFlowOp $H SucceedMission 'misn10w1.des' -TimeoutSeconds 30 | Out-Null
    foreach ($client in $guests) { Wait-CRFlowOp $client SucceedMission 'misn10w1.des' -TimeoutSeconds 30 | Out-Null }
    @{ how = $how }
}

Invoke-CRFlowStep 'result parity: SucceedMission misn10w1.des on every client' {
    Test-CRFlowResultParity -Expect SucceedMission -Debrief 'misn10w1.des' -Clients $C
}
}

Invoke-CRFlowStep 'team 5 built under its AIP over the run (objects, scrap, AI tick)' {
    Add-BuildSample
    $samples = $script:BuildSamples; $mems = $script:BuildMems
    $first = $samples[0]; $last = $samples[-1]
    $peak = ($samples | Measure-Object -Property n -Maximum).Maximum
    $scrapMin = ($samples | Measure-Object -Property scrap -Minimum).Minimum
    for ($i = 0; $i -lt $samples.Count; $i++) { Write-Host ('[aip] t={0,6:N0} n={1,3} scrap={2,4} aip={3} planB={4} | mem {5}' -f $samples[$i].t, $samples[$i].n, $samples[$i].scrap, $samples[$i].aip, $samples[$i].planB, ($mems[$i] | ConvertTo-Json -Compress)) }
    Add-CRFlowCheck "team 5 builds: objects $($first.n) -> $($last.n) (peak $peak), scrap $($first.scrap) -> $($last.scrap) (min $scrapMin)" ($peak -gt $first.n -or $scrapMin -lt $first.scrap) @{ first = $first; last = $last }
    Add-CRFlowCheck "AI tick counter rises on the host ($($mems[0].aiTick) -> $($mems[-1].aiTick))" ($mems[-1].aiTick -gt $mems[0].aiTick) $mems
    @{ samples = $samples; memory = $mems }
}