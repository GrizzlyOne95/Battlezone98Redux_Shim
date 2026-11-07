# Does a building's (and a craft's) health replicate? Logs team/health of every
# building and craft on host and guest, damages one host-owned building and one
# host-owned craft on the host, waits, and logs again. Observes only otherwise.
param([int]$HostClient = 0, [int]$SettleSeconds = 5, [int]$PlaySeconds = 20)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })

$dump = @'
local function p(f, ...) local ok, a = pcall(f, ...); if ok then return a end return nil end
local me = GetPlayerHandle()
local mt = p(GetTeamNum, me)
local rows = {}
for h in AllObjects() do
  if IsValid(h) then
    local bld = p(IsBuilding, h) == true
    local cra = p(IsCraft, h) == true
    local t = p(GetTeamNum, h)
    if t and t ~= 0 and (bld or cra) and t <= 4 then
      local x, y, z
      local a, b, c = p(GetPosition, h)
      if type(a) == "table" then x, y, z = a.x, a.y, a.z elseif type(a) == "number" then x, y, z = a, b, c end
      rows[#rows + 1] = { id = tostring(h), odf = p(GetOdf, h), lbl = p(GetLabel, h), kind = bld and "bld" or "craft",
        team = t, ratio = p(GetHealth, h), cur = p(GetCurHealth, h), max = p(GetMaxHealth, h),
        ally = p(IsAlly, mt, t), allyH = p(IsAlly, me, h), x = x and math.floor(x), z = z and math.floor(z) }
    end
  end
end
return { myTeam = mt, n = #rows, rows = rows }
'@

function Show($tag, $c, $d) {
    Write-Host "== $tag c${c}: myTeam=$($d.myTeam) objects=$($d.n)"
    foreach ($r in $d.rows) {
        Write-Host ("   {0,-5} {1,-12} {2,-10} team={3} ally={4}/{11} ratio={5} cur={6} max={7} @({8},{9}) id={10}" -f $r.kind, $r.odf, $r.lbl, $r.team, $r.ally, $r.ratio, $r.cur, $r.max, $r.x, $r.z, $r.id, $r.allyH)
    }
}

Invoke-CRFlowStep 'probes attached, mission running' {
    foreach ($c in $C) {
        $a = Wait-CRFlowEvent $c attach -TimeoutSeconds 120
        if (-not $a.bzfile) { throw "bzfile missing on c$c" }
    }
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($c in $guests) { Wait-CRFlow $c 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 90 | Out-Null }
    Start-Sleep -Seconds $PlaySeconds
    'ready'
}

$before = @{}
Invoke-CRFlowStep 'BEFORE: dump buildings and craft on every client' {
    foreach ($c in $C) { $before[$c] = Invoke-CRFlow $c $dump; Show 'BEFORE' $c $before[$c] }
    'dumped'
}

$hostTeam = $before[$H].myTeam
Invoke-CRFlowStep 'host damages one host-team building and one host-team craft' {
    $lua = @"
local function p(f, ...) local ok, a = pcall(f, ...); if ok then return a end return nil end
local ht = $hostTeam
local out = {}
for h in AllObjects() do
  if IsValid(h) and GetTeamNum(h) == ht and not out.bld and p(IsBuilding, h) == true and p(GetMaxHealth, h) then
    local m = GetMaxHealth(h); SetCurHealth(h, m * 0.5)
    out.bld = { odf = GetOdf(h), x = 0, z = 0, cur = GetCurHealth(h), max = m }
  end
end
local me = GetPlayerHandle()
if IsValid(me) and p(GetMaxHealth, me) then
  local m = GetMaxHealth(me); SetCurHealth(me, m * 0.5)
  out.craft = { odf = GetOdf(me), cur = GetCurHealth(me), max = m }
end
return out
"@
    $r = Invoke-CRFlow $H $lua
    Write-Host ("damaged: " + ($r | ConvertTo-Json -Compress -Depth 5))
    $r
}

Invoke-CRFlowStep "AFTER ${SettleSeconds}s: dump again" {
    Start-Sleep -Seconds $SettleSeconds
    $after = @{}
    foreach ($c in $C) { $after[$c] = Invoke-CRFlow $c $dump; Show 'AFTER' $c $after[$c] }
    'dumped'
}
