# aiCore in a networked CR mission (misn02b, misn03, misn04, misn05; the mission comes from the
# runner's $Mission). Nothing is forced: it observes. Checks, on the host unless stated:
#   - misn02b: GetAIP(6) is misn02.aip after Start (the native AIP for the CCA team 6).
#   - misn05: team 5 runs on the aiCore Lua brain with no native AI flag (GetAIP(5) nil, host
#     [0x2CEA478] == 0): team-5 objects grow, scrap is spent and units are on Attack orders.
#   - every mission: no Lua errors (the runner's log check), Pilot Mode locked in a networked game
#     and its settings-menu entry reads "Off (multiplayer)" (PersistentConfig page entries),
#     guest teams get an aiCore Team object configured as human (no base/factory management),
#     aiCore never recorded a command on a human-piloted craft.
param([int]$HostClient = 0,
      [int]$PlaySeconds = 30,
      # misn05 only: how long to watch the CCA brain build and attack.
      [int]$BrainWatchSeconds = 240)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$mission = $Mission
$enemy = if ($mission -eq 'misn02b') { 6 } else { 5 }

Add-Type -ErrorAction SilentlyContinue -TypeDefinition @"
using System; using System.Runtime.InteropServices;
public static class CRFlowMem2 {
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr OpenProcess(int a, bool i, int pid);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool ReadProcessMemory(IntPtr h, IntPtr addr, byte[] buf, int n, out int read);
  [DllImport("kernel32.dll")] public static extern bool CloseHandle(IntPtr h);
  public static long ReadByte(int pid, long addr) {
    IntPtr h = OpenProcess(0x10, false, pid); if (h == IntPtr.Zero) return -2;
    try { byte[] b = new byte[1]; int r; if (!ReadProcessMemory(h, (IntPtr)addr, b, 1, out r) || r != 1) return -1; return b[0]; } finally { CloseHandle(h); }
  }
}
"@

Invoke-CRFlowStep 'probes attached; host has authority, guests do not' {
    foreach ($client in $C) {
        $attached = Wait-CRFlowEvent $client attach -TimeoutSeconds 120
        if (-not $attached.bzfile) { throw "bzfile missing on c$client; no command channel" }
    }
    $hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    if (-not $hr.authority) { throw 'host has no authority' }
    @{ host = $hr }
}
Invoke-CRFlowStep 'session ready and mission running on every client' {
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 180 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null }
    'coopMissionStarted on all'
}
Invoke-CRFlowStep "$PlaySeconds s of play; every peer alive, full roster" {
    Start-Sleep -Seconds $PlaySeconds
    foreach ($client in $C) {
        $s = Invoke-CRFlow $client 'local d = describe(me()); return { alive = d.alive, valid = d.valid, team = d.team, players = #players() }'
        Add-CRFlowCheck "c$client alive with its own craft, sees $($C.Count) players" ($s.valid -and $s.alive -and $s.players -eq $C.Count) $s
    }
}

$aiState = @'
local ai = require("aiCore")
local PC = require("PersistentConfig")
local out = {}
local ok, aipEnemy = pcall(GetAIP, ENEMY)
out.aipEnemy = ok and tostring(aipEnemy) or "err"
out.aiLoaded = type(ai) == "table"
local locked = false
pcall(function() locked = PC._IsPilotModeLocked() end)
out.pilotLocked = locked
pcall(function()
  for _, e in ipairs(PC.P.GetSettingsPageEntries()) do
    if e.label == "Pilot Mode" then out.pilotMenuValue = e.value end
  end
end)
local teams = {}
for t = 1, 8 do
  local team = ai.ActiveTeams and ai.ActiveTeams[t]
  if team then
    local cfg = team.Config or {}
    teams[#teams + 1] = { team = t, humanTeam = team.humanTeam == true, humanByApi = ai.IsHumanTeam(t) == true,
      manageBase = cfg.manageBase, autoBuild = cfg.autoBuild, manageFactories = cfg.manageFactories,
      manageTacticalOrders = cfg.manageTacticalOrders, autoRepairWingmen = cfg.autoRepairWingmen, scavengerAssist = cfg.scavengerAssist }
  end
end
out.teams = teams
-- Commands aiCore recorded against human-piloted craft.
local humanOrdered, recorded = {}, 0
for h, st in pairs(ai.CommandState or {}) do
  recorded = recorded + 1
  if IsValid(h) and ai.IsHumanCraft(h) and st and st.time and st.time > -900 then humanOrdered[#humanOrdered + 1] = { odf = GetOdf(h), team = GetTeamNum(h), cmd = st.cmd } end
end
out.commandsRecorded = recorded
out.humanOrdered = humanOrdered
local humans = {}
for _, h in ipairs(ai.GetHumanPlayers()) do humans[#humans + 1] = GetTeamNum(h) end
out.humanTeams = humans
local sc = {}
for h in AllCraft() do
  local o = tostring(GetOdf(h) or ""):gsub("%.odf$", "")
  if o:find("scav") then sc[#sc + 1] = { odf = o, team = GetTeamNum(h) } end
end
out.scavengers = sc
return out
'@.Replace('ENEMY', "$enemy")

Invoke-CRFlowStep "aiCore state on the host ($mission, enemy team $enemy)" {
    $s = Invoke-CRFlow $H $aiState
    Add-CRFlowCheck "aiCore module loaded" ($s.aiLoaded -eq $true) $s
    Add-CRFlowCheck "Pilot Mode locked in the networked game" ($s.pilotLocked -eq $true) $s
    Add-CRFlowCheck "Pilot Mode menu entry reads 'Off (multiplayer)' (read: '$($s.pilotMenuValue)')" ($s.pilotMenuValue -eq 'Off (multiplayer)') $s -WarnOnly:([string]::IsNullOrEmpty($s.pilotMenuValue))
    $humanTeams = @($s.teams | Where-Object { $_.team -in 2, 3, 4 })
    $guestTeamCount = @($s.humanTeams | Where-Object { $_ -in 2, 3, 4 }).Count
    Add-CRFlowCheck "guest teams have an aiCore Team object set up as human (found $(@($humanTeams | % { $_.team }) -join ',') of $guestTeamCount guest team(s))" `
        ($humanTeams.Count -ge 1 -and @($humanTeams | Where-Object { -not $_.humanTeam -or $_.manageBase -or $_.autoBuild -or $_.manageFactories }).Count -eq 0) $s -WarnOnly
    Add-CRFlowCheck "aiCore recorded no command on a human-piloted craft ($($s.commandsRecorded) commands recorded)" (@($s.humanOrdered).Count -eq 0) $s
    $guestScav = @($s.scavengers | Where-Object { $_.team -in 2, 3, 4 })
    Add-CRFlowCheck "guest-owned scavengers on the host: $($guestScav.Count) (all scavengers: $(@($s.scavengers | % { "$($_.odf)/t$($_.team)" }) -join ' '))" $true $s -WarnOnly
    $script:AiBefore = $s
    $s
}

if ($mission -eq 'misn02b') {
    Invoke-CRFlowStep 'misn02b: GetAIP(6) is set after Start' {
        $r = Wait-CRFlow $H 'local ok, a = pcall(GetAIP, 6); return ok and a ~= nil and { aip = tostring(a) }' -TimeoutSeconds 60
        Add-CRFlowCheck "GetAIP(6) = $($r.aip)" ($r.aip -like 'misn02*.aip') $r
        $r
    }
}

if ($mission -eq 'misn05') {
    Invoke-CRFlowStep "misn05: team-5 aiCore brain builds and attacks with no native AI flag ($BrainWatchSeconds s)" {
        $hostPid = [int](Get-CRFlowSession).clients[$H].pid
        $flag = [CRFlowMem2]::ReadByte($hostPid, 0x2CEA478)
        $count = @'
local n, atk, builders, odfs = 0, 0, 0, {}
local A = AiCommand and AiCommand.ATTACK
for h in AllObjects() do
  if IsValid(h) and GetTeamNum(h) == 5 then
    n = n + 1
    local o = (tostring(GetOdf(h) or "?"):gsub("%.odf$", ""))
    odfs[o] = (odfs[o] or 0) + 1
    if A ~= nil and IsAlive(h) and GetCurrentCommand(h) == A then atk = atk + 1 end
  end
end
local ok, aip = pcall(GetAIP, 5)
return { n = n, attacking = atk, odfs = odfs, scrap = GetScrap(5), t = GetTime(), aip = ok and tostring(aip) or "err" }
'@
        $samples = @()
        $deadline = (Get-Date).AddSeconds($BrainWatchSeconds)
        $keep = 'for h in AllObjects() do if IsValid(h) and GetTeamNum(h) >= 1 and GetTeamNum(h) <= 4 then pcall(heal, h) end end; return true'
        $nextSample = Get-Date
        do {
            # ASSIST: every human-team object is healed every 4 s so the CCA's attacks cannot fail the mission (a failed
            # mission opens a UI screen that closes the host on this renderer) while its brain is observed.
            Invoke-CRFlow $H $keep | Out-Null
            if ((Get-Date) -ge $nextSample) { $samples += (Invoke-CRFlow $H $count); $nextSample = (Get-Date).AddSeconds(20) }
            Start-Sleep -Seconds 4
        } while ((Get-Date) -lt $deadline)
        foreach ($s in $samples) { Write-Host ('[brain] t={0,6:N0} n={1,3} attacking={2,3} scrap={3,4} aip={4}' -f $s.t, $s.n, $s.attacking, $s.scrap, $s.aip) }
        $first = $samples[0]; $peakN = ($samples | Measure-Object n -Maximum).Maximum; $peakAtk = ($samples | Measure-Object attacking -Maximum).Maximum
        $minScrap = ($samples | Measure-Object scrap -Minimum).Minimum
        Add-CRFlowCheck "no native AI: team-5 AI control flag byte is $flag (0 = off) and GetAIP(5) is '$($first.aip)'" ($flag -eq 0 -and $first.aip -in 'nil', 'err', '') @{ flag = $flag; aip = $first.aip }
        Add-CRFlowCheck "the aiCore brain builds: team-5 objects $($first.n) -> peak $peakN, scrap $($first.scrap) (min $minScrap)" ($peakN -gt $first.n -or $minScrap -lt $first.scrap) @{ samples = $samples }
        Add-CRFlowCheck "the aiCore brain attacks: up to $peakAtk team-5 units on Attack orders" ($peakAtk -gt 0) @{ samples = $samples }
        @{ flag = $flag; samples = $samples }
    }
}

Invoke-CRFlowStep 'aiCore state after the watch: still no command on a human-piloted craft' {
    $s = Invoke-CRFlow $H $aiState
    Add-CRFlowCheck "no aiCore command recorded on a human-piloted craft ($($s.commandsRecorded) recorded, $(@($s.humanOrdered).Count) on humans)" (@($s.humanOrdered).Count -eq 0) $s
    $s
}
