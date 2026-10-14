# misn10 with a GUEST-owned scavenger while the host runs the team-5 AIP (OpenShim #469 scavenger guard).
# The host crashed (heap corruption, 0xC0000374) about 5.5 minutes into a 4-player misn10 because stock
# AI_Team_Compute_Other calls ScavengerProcess::GetScrapPosition on a guest-owned scavenger whose process is a NetProcess.
#
#   1. Smoke (attach, roles, ready).
#   2. ASSIST: a guest builds an avscav (team = the guest's own team) beside its craft; the host must see it
#      (a remote-owned object, which is what the AIP walks).
#   3. Watch for $WatchSeconds (default 780 s = 13 min, twice the old crash point): every sample checks that every peer
#      is alive, the AIP is still misn10.aip, team 5 keeps building and spending scrap. Human craft are kept healed (ASSIST).
#   4. The runner's log-wide checks cover Lua errors; the host process must still be alive at the end.
param([int]$HostClient = 0,
      [int]$GuestClient = 1,
      [int]$WatchSeconds = 780)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$G = $GuestClient

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
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($client in $guests) { Wait-CRFlow $client 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 90 | Out-Null }
    'ok'
}
Invoke-CRFlowStep "ASSIST: guest c$G builds a scavenger; the host sees it (guest-owned object the AIP will walk)" {
    $built = Invoke-CRFlow $G @'
local p = GetPosition(me())
local pos = GetPositionNear(p, 20, 40)
local s = BuildObject("avscav", role().team, pos)
SCAV = s
return { valid = IsValid(s), team = IsValid(s) and GetTeamNum(s) or -1, odf = IsValid(s) and GetOdf(s) or nil, ["local"] = IsValid(s) and describe(s)["local"] }
'@
    Start-Sleep -Seconds 5
    $seen = Invoke-CRFlow $H @'
local n, rows = 0, {}
for h in AllCraft() do
  local o = tostring(GetOdf(h) or ""):gsub("%.odf$", "")
  if o:find("scav") then n = n + 1; rows[#rows + 1] = { odf = o, team = GetTeamNum(h), ["local"] = describe(h)["local"] } end
end
return { n = n, rows = rows }
'@
    Add-CRFlowCheck "guest-built scavenger exists on the guest ($($built.odf), team $($built.team), local=$($built.local))" ($built.valid -eq $true) $built
    Add-CRFlowCheck "the host sees a scavenger owned by a guest team ($($seen.n) scavenger(s); rows: $((@($seen.rows) | % { "$($_.odf)/t$($_.team)/local=$($_.local)" }) -join ' '))" (@($seen.rows | ? { $_.team -in 2, 3, 4 }).Count -ge 1) @{ built = $built; seen = $seen } -WarnOnly
    @{ built = $built; seen = $seen }
}

$samples = @()
Invoke-CRFlowStep "watch $WatchSeconds s: host alive, AIP misn10.aip, team 5 builds and spends scrap (human craft healed: ASSIST)" {
    $hostPid = [int](Get-CRFlowSession).clients[$H].pid
    $deadline = (Get-Date).AddSeconds($WatchSeconds)
    $start = Get-Date
    $next = Get-Date
    do {
        foreach ($client in $C) { Invoke-CRFlow $client 'pcall(function() heal(me()) end); return true' | Out-Null }
        if ((Get-Date) -ge $next) {
            $r = Invoke-CRFlow $H 'local n = 0; for h in AllObjects() do if IsValid(h) and GetTeamNum(h) == 5 then n = n + 1 end end; local ok, aip = pcall(GetAIP, 5); return { t = GetTime(), n5 = n, scrap5 = GetScrap(5), aip = ok and tostring(aip) or "err" }'
            $script:samples += $r
            Write-Host ('[watch] +{0,4:N0}s t={1,6:N0} team5 n={2,3} scrap={3,4} aip={4}' -f ((Get-Date) - $start).TotalSeconds, $r.t, $r.n5, $r.scrap5, $r.aip)
            $next = (Get-Date).AddSeconds(30)
        }
        Start-Sleep -Seconds 5
    } while ((Get-Date) -lt $deadline)
    $first = $samples[0]; $last = $samples[-1]
    $peak = ($samples | Measure-Object n5 -Maximum).Maximum; $minScrap = ($samples | Measure-Object scrap5 -Minimum).Minimum
    Add-CRFlowCheck "host process $hostPid still running after $WatchSeconds s" ([bool](Get-Process -Id $hostPid -ErrorAction SilentlyContinue)) @{ pid = $hostPid }
    Add-CRFlowCheck "AIP still $($last.aip) (misn10.aip or the plan-B misn10b.aip)" ($last.aip -like 'misn10*.aip') $last
    Add-CRFlowCheck "team 5 builds: objects $($first.n5) -> peak $peak, scrap $($first.scrap5) -> min $minScrap" ($peak -gt $first.n5 -or $minScrap -lt $first.scrap5) @{ samples = $samples }
    @{ samples = $samples }
}
