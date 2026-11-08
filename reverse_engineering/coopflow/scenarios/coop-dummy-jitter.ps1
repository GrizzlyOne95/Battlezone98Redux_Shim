# Does EXU turbo make the host-owned misn02b dummy tank (team 7 avtank) move
# jaggedly on guests? Drives the dummy on the host along the same leg twice,
# turbo ON (stock CR) then OFF, while every client samples its position each
# Update. Reports per-client roughness. Sampled positions are sim positions,
# a proxy for what the guest sees, not rendered frames.
param([int]$HostClient = 0, [int]$PlaySeconds = 30, [int]$LegSeconds = 15)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })

$find = @'
local function p(f, ...) local ok, a, b, c = pcall(f, ...); if ok then return a, b, c end end
local function pos(h)
  local a, b, c = p(GetPosition, h)
  if type(a) == "table" then return a.x, a.y, a.z elseif type(a) == "number" then return a, b, c end
end
local function dummy()
  for h in AllCraft() do
    if p(GetTeamNum, h) == 7 and p(GetOdf, h) == "avtank" then return h end
  end
end
'@

$startSampler = $find + @'
_G.__jit = { h = dummy(), s = {}, on = true }
if not _G.__jitWrapped then
  _G.__jitWrapped = true
  local inner = _G.Update
  _G.Update = function(...)
    local r = { inner(...) }
    local J = _G.__jit
    if J and J.on and J.h and #J.s < 6000 then
      local x, _, z = pos(J.h)
      if x then J.s[#J.s + 1] = { GetTime(), x, z } end
    end
    return (table.unpack or unpack)(r)
  end
end
return { h = tostring(_G.__jit.h) }
'@

$summary = @'
local J = _G.__jit
if not J then return { err = "no sampler" } end
J.on = false
local s, n = J.s, #J.s
if n < 3 then return { n = n, err = "too few samples" } end
local frames, sameT, stalls, path, bend, maxStep = 0, 0, 0, 0, 0, 0
local speeds = {}
for i = 2, n do
  local dt = s[i][1] - s[i - 1][1]
  if dt <= 0 then sameT = sameT + 1 else
    frames = frames + 1
    local dx, dz = s[i][2] - s[i - 1][2], s[i][3] - s[i - 1][3]
    local d = math.sqrt(dx * dx + dz * dz)
    path = path + d
    if d < 0.001 then stalls = stalls + 1 end
    if d > maxStep then maxStep = d end
    speeds[#speeds + 1] = d / dt
    if i < n then
      local ex, ez = s[i + 1][2] - 2 * s[i][2] + s[i - 1][2], s[i + 1][3] - 2 * s[i][3] + s[i - 1][3]
      bend = bend + math.sqrt(ex * ex + ez * ez)
    end
  end
end
local m = 0; for _, v in ipairs(speeds) do m = m + v end; m = m / math.max(1, #speeds)
local var = 0; for _, v in ipairs(speeds) do var = var + (v - m) ^ 2 end
local sd = math.sqrt(var / math.max(1, #speeds))
local function r3(x) return math.floor(x * 1000 + 0.5) / 1000 end
return { n = n, frames = frames, sameT = sameT, stalls = stalls, dur = r3(s[n][1] - s[1][1]),
  path = r3(path), meanSpeed = r3(m), cv = r3(m > 0 and sd / m or 0),
  rough = r3(path > 0 and bend / path or 0), maxStepRatio = r3(path > 0 and maxStep / (path / frames) or 0) }
'@

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

$plan = $null
Invoke-CRFlowStep 'host: locate dummy and pick a leg' {
    $lua = $find + @'
local d = dummy()
if not d then return { err = "no team-7 avtank" } end
local x, y, z = pos(d)
local best, bd
for h in AllObjects() do
  if IsValid(h) and p(GetTeamNum, h) == 1 then
    local hx, _, hz = pos(h)
    if hx then
      local dd = math.sqrt((hx - x) ^ 2 + (hz - z) ^ 2)
      if dd < 400 and (not bd or dd > bd) then best, bd = h, dd end
    end
  end
end
local tx, ty, tz = pos(best)
return { x = x, y = y, z = z, tx = tx, ty = ty, tz = tz, dist = bd, turbo = p(exu.GetUnitTurbo, d), local_ = p(IsLocal, d) }
'@
    $script:plan = Invoke-CRFlow $H $lua
    Write-Host ("plan: " + ($script:plan | ConvertTo-Json -Compress))
    if ($script:plan.err) { throw $script:plan.err }
    if (-not $script:plan.dist -or $script:plan.dist -lt 60) { throw "leg too short ($($script:plan.dist))" }
    $script:plan
}

function Run-Leg([string]$name, [bool]$turbo, [double]$x, [double]$y, [double]$z) {
    Invoke-CRFlowStep "leg ${name}: turbo=$turbo, sample ${LegSeconds}s" {
        foreach ($c in $C) { Invoke-CRFlow $c $startSampler | Out-Null }
        $t = if ($turbo) { 'true' } else { 'false' }
        $go = $find + @"
local d = dummy()
pcall(exu.SetUnitTurbo, d, $t)
Goto(d, SetVector($x, $y, $z), 1)
return { turbo = p(exu.GetUnitTurbo, d) }
"@
        $g = Invoke-CRFlow $H $go
        Write-Host "host turbo now: $($g.turbo)"
        Start-Sleep -Seconds $LegSeconds
        foreach ($c in $C) {
            $r = Invoke-CRFlow $c $summary
            $role = if ($c -eq $H) { 'host ' } else { 'guest' }
            Write-Host ("jit {0} c{1} {2}: " -f $name, $c, $role) ($r | ConvertTo-Json -Compress)
        }
        'done'
    }
}

Run-Leg 'A-out' $true $plan.tx $plan.ty $plan.tz
Run-Leg 'B-back' $false $plan.x $plan.y $plan.z
Run-Leg 'C-out' $false $plan.tx $plan.ty $plan.tz
Run-Leg 'D-back' $true $plan.x $plan.y $plan.z
