# Measures stock Redux replication one case at a time: one real client acts,
# the other is observed. Mission-independent (needs only the probe); objects
# are spawned near the host player. Every case writes a finding with its raw
# evidence to <run>\replication-findings.jsonl/.md. Findings are observations,
# not pass/fail: a case only fails the run if the harness itself breaks.
#
# Classifications:
#   replicated  the other peer converged to the actor's result
#   local-only  only the actor changed; the other peer never did
#   reverted    the actor's own change was undone by replication
#   diverged    both changed, but to different results
#   none        the operation had no effect even on the actor
param([int]$HostClient = 0, [int]$GuestClient = 1, [int]$ObserveSeconds = 6)

$H, $G = $HostClient, $GuestClient
$findingsJsonl = Join-Path $script:CRFlowRun.runDir 'replication-findings.jsonl'
$findings = New-Object System.Collections.ArrayList

function Poll([int]$Client, [string]$Lua, [double]$Seconds = $ObserveSeconds) {
    $sw = [Diagnostics.Stopwatch]::StartNew()
    do {
        $v = Invoke-CRFlow $Client $Lua
        if (Test-CRFlowTruthy $v) { return [pscustomobject]@{ value = $v; seconds = [math]::Round($sw.Elapsed.TotalSeconds, 1) } }
        Start-Sleep -Milliseconds 300
    } while ($sw.Elapsed.TotalSeconds -lt $Seconds)
    [pscustomobject]@{ value = $v; seconds = $null }
}

function Add-Finding([string]$Id, [string]$Area, [string]$Question, [string]$Result, $Evidence) {
    $f = [ordered]@{ id = $Id; area = $Area; question = $Question; result = $Result; evidence = $Evidence; at = (Get-Date).ToString('o') }
    [void]$findings.Add($f)
    ($f | ConvertTo-Json -Compress -Depth 8) | Add-Content -LiteralPath $findingsJsonl
    Write-Host ("[finding] {0,-4} {1,-11} {2}" -f $Id, $Result, $Question) -ForegroundColor Cyan
    $Result
}

# Spawn point helper: a fresh spot near the host player for each case, so
# objects from different cases never match each other.
$script:ring = 0
function Next-Spot {
    $script:ring += 1
    $d = 70 + 25 * $script:ring
    $p = Invoke-CRFlow $H "return near(me(), $d, $($d + 5))"
    @{ x = [math]::Round($p[0], 1); y = [math]::Round($p[1], 1); z = [math]::Round($p[2], 1) }
}
function Find-Lua([string]$Odf, $S, [int]$Radius = 25) { "findNear('$Odf', $($S.x), $($S.z), $Radius)" }

Invoke-CRFlowStep 'probes attached and roles known' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowEvent $G attach -TimeoutSeconds 120 | Out-Null
    $script:hr = Wait-CRFlow $H 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    $script:gr = Wait-CRFlow $G 'local r = role(); return r.playerId ~= nil and r' -TimeoutSeconds 90
    # Bring the guest next to the host so every spawn is near both players.
    Invoke-CRFlow $G 'local hp; for _, p in pairs(CRCoop and CRCoop.GetPlayers() or {}) do if p.team ~= role().team and p.handle then hp = p.handle end end; if hp then return tp(hp, 30) end' | Out-Null
    $api = Invoke-CRFlow $H "local t = {}; for _, n in ipairs({'SetName','GetName','SetObjectiveName','GetObjectiveName','GiveWeapon','GetWeaponClass','SetTeamNum','SetLocal','IsRemote','AllObjects','SetVector','Send','GetMaxHealth','SetMaxHealth','SetOwner','GetOwner'}) do t[n] = type(_G[n]) == 'function' end; return t"
    @{ hostTeam = $hr.team; guestTeam = $gr.team; api = $api }
}

# ------------------------------------------------------------ spawning --
Invoke-CRFlowStep 'A1 host BuildObject craft (team 5 AI)' {
    $s = Next-Spot
    $a = Invoke-CRFlow $H "a1 = BuildObject('svfigh', 5, at($($s.x), $($s.y), $($s.z))); return { d = describe(a1), isLocal = IsLocal(a1), isRemote = IsRemote and IsRemote(a1) }"
    $o = Poll $G "local h = $(Find-Lua 'svfigh' $s 80); return h and { d = describe(h), isLocal = IsLocal(h), isRemote = IsRemote and IsRemote(h) }"
    Add-Finding 'A1' 'spawn' 'Host-built AI craft appears on the guest' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

Invoke-CRFlowStep 'A2 host BuildObject building' {
    $s = Next-Spot
    $script:b2spot = $s
    $a = Invoke-CRFlow $H "b2 = BuildObject('abspow', $($hr.team), at($($s.x), $($s.y), $($s.z))); return { d = describe(b2), isLocal = IsLocal(b2) }"
    $o = Poll $G "local h = $(Find-Lua 'abspow' $s); return h and { d = describe(h), isLocal = IsLocal(h) }"
    Add-Finding 'A2' 'spawn' 'Host-built building appears on the guest' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

Invoke-CRFlowStep 'A3 guest BuildObject craft (own team)' {
    $s = Next-Spot
    $a = Invoke-CRFlow $G "a3 = BuildObject('avfimp', $($gr.team), at($($s.x), $($s.y), $($s.z))); return { d = describe(a3), isLocal = IsLocal(a3) }"
    $o = Poll $H "local h = $(Find-Lua 'avfimp' $s 60); return h and { d = describe(h), isLocal = IsLocal(h) }"
    Add-Finding 'A3' 'spawn' 'Guest-built craft appears on the host' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

Invoke-CRFlowStep 'A4 guest BuildObject building' {
    $s = Next-Spot
    $a = Invoke-CRFlow $G "a4 = BuildObject('abspow', $($gr.team), at($($s.x), $($s.y), $($s.z))); return { d = describe(a4), isLocal = IsLocal(a4) }"
    $o = Poll $H "local h = $(Find-Lua 'abspow' $s); return h and { d = describe(h), isLocal = IsLocal(h) }"
    Add-Finding 'A4' 'spawn' 'Guest-built building appears on the host' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

# ------------------------------------------------- handle identity (Send) --
Invoke-CRFlowStep 'C1 host Send(handle) resolves on the guest' {
    $s = $script:b2spot
    Invoke-CRFlow $G 'inbox(); return true' | Out-Null
    Invoke-CRFlow $H "Send(0, '~', 'C1', b2); return true" | Out-Null
    $o = Poll $G "local m = inbox()[1]; if not m then return nil end; local h = m.args[2] and m.args[2].handle; local mine = $(Find-Lua 'abspow' $s); return { received = m.args[1], valid = h ~= nil and IsValid(h), same = h ~= nil and h == mine, seen = m.args[2] and m.args[2].seen, mine = mine and describe(mine) }"
    $r = if (-not $o.value) { 'none' } elseif ($o.value.same) { 'replicated' } elseif ($o.value.valid) { 'diverged' } else { 'local-only' }
    Add-Finding 'C1' 'handles' 'A host-owned handle sent with Send() is the same object on the guest' $r @{ other = $o.value; seconds = $o.seconds }
}

Invoke-CRFlowStep 'C2 guest Send(own craft) resolves on the host' {
    Invoke-CRFlow $H 'inbox(); return true' | Out-Null
    Invoke-CRFlow $G "Send(0, '~', 'C2', me()); return true" | Out-Null
    $o = Poll $H "local m = inbox()[1]; if not m then return nil end; local h = m.args[2] and m.args[2].handle; local tracked; for _, p in pairs(CRCoop and CRCoop.GetPlayers() or {}) do if p.team == $($gr.team) then tracked = p.handle end end; return { valid = h ~= nil and IsValid(h), sameAsTracked = h ~= nil and h == tracked, seen = m.args[2] and m.args[2].seen }"
    $r = if (-not $o.value) { 'none' } elseif ($o.value.sameAsTracked) { 'replicated' } elseif ($o.value.valid) { 'diverged' } else { 'local-only' }
    Add-Finding 'C2' 'handles' "The guest's own craft handle sent with Send() matches the host's view of that player" $r @{ other = $o.value; seconds = $o.seconds }
}

# ---------------------------------------------------------------- names --
Invoke-CRFlowStep 'D1 host SetObjectiveName / SetName' {
    $s = $script:b2spot
    $a = Invoke-CRFlow $H "SetObjectiveName(b2, 'CRFLOW-OBJ'); local n1 = GetObjectiveName(b2); if SetName then SetName(b2, 'CRFLOW-NAME') end; return { afterObjectiveName = n1, afterSetName = GetObjectiveName(b2), name = GetName and GetName(b2) }"
    Start-Sleep -Seconds $ObserveSeconds
    $o = Invoke-CRFlow $G "local h = $(Find-Lua 'abspow' $s); return h and { objectiveName = GetObjectiveName(h), name = GetName and GetName(h) }"
    $r = if ($o -and ($o.objectiveName -like 'CRFLOW*' -or $o.name -like 'CRFLOW*')) { 'replicated' } else { 'local-only' }
    Add-Finding 'D1' 'names' 'Host SetObjectiveName/SetName on a host-owned object shows on the guest' $r @{ actor = $a; other = $o }
}

# --------------------------------------------------------------- health --
Invoke-CRFlowStep 'F1 host Damage on host-owned building' {
    $s = Next-Spot
    $script:f1spot = $s
    Invoke-CRFlow $H "f1 = BuildObject('abspow', $($hr.team), at($($s.x), $($s.y), $($s.z))); return true" | Out-Null
    Poll $G "return $(Find-Lua 'abspow' $s) ~= nil" | Out-Null
    $a = Invoke-CRFlow $H 'local before = GetHealth(f1); Damage(f1, GetMaxHealth(f1) * 0.4); return { before = before, after = GetHealth(f1) }'
    $o = Poll $G "local h = $(Find-Lua 'abspow' $s); return h and GetHealth(h) < 0.95 and GetHealth(h)"
    Add-Finding 'F1' 'health' 'Host Damage() on a host-owned object reaches the guest' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

Invoke-CRFlowStep 'F2 guest Damage on host-owned building' {
    $s = $script:f1spot
    $hostBefore = Invoke-CRFlow $H 'return GetHealth(f1)'
    $a = Invoke-CRFlow $G "f2 = $(Find-Lua 'abspow' $s); local before = GetHealth(f2); Damage(f2, GetMaxHealth(f2) * 0.3); return { before = before, after = GetHealth(f2) }"
    $o = Poll $H "local v = GetHealth(f1); return v < $hostBefore - 0.05 and v"
    Start-Sleep -Seconds 2
    $guestLater = Invoke-CRFlow $G 'return GetHealth(f2)'
    $r = if ($o.value) { 'replicated' } elseif ($a.after -lt $a.before -and $guestLater -gt $a.after + 0.05) { 'reverted' } elseif ($a.after -lt $a.before) { 'diverged' } else { 'none' }
    Add-Finding 'F2' 'ownership' 'Guest Damage() on a host-owned object reaches the host' $r @{ actor = $a; hostBefore = $hostBefore; host = $o.value; guestAfterWait = $guestLater; seconds = $o.seconds }
}

Invoke-CRFlowStep 'F3 host SetMaxHealth / SetCurHealth' {
    $s = $script:f1spot
    $a = Invoke-CRFlow $H 'local m = GetMaxHealth(f1); SetMaxHealth(f1, m * 3); SetCurHealth(f1, m * 3); return { max = GetMaxHealth(f1), cur = GetCurHealth and GetCurHealth(f1), frac = GetHealth(f1) }'
    Start-Sleep -Seconds $ObserveSeconds
    $o = Invoke-CRFlow $G "local h = $(Find-Lua 'abspow' $s); return h and { max = GetMaxHealth(h), cur = GetCurHealth and GetCurHealth(h), frac = GetHealth(h) }"
    $r = if ($o -and [math]::Abs($o.max - $a.max) -lt 1) { 'replicated' } else { 'local-only' }
    Add-Finding 'F3' 'health' 'Host SetMaxHealth() is visible on the guest' $r @{ actor = $a; other = $o }
}

# ------------------------------------------------------------- position --
Invoke-CRFlowStep 'G1 host SetPosition on host-owned building' {
    $s = $script:f1spot
    $a = Invoke-CRFlow $H "SetPosition(f1, at($($s.x + 40), $($s.y), $($s.z))); return xyz(f1)"
    $o = Poll $G "local h = $(Find-Lua 'abspow' @{ x = $s.x + 40; z = $s.z } 10); return h and xyz(h)"
    Add-Finding 'G1' 'position' 'Host SetPosition() on a host-owned object reaches the guest' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

Invoke-CRFlowStep 'G2 guest SetPosition on host-owned building' {
    $s = @{ x = $script:f1spot.x + 40; z = $script:f1spot.z; y = $script:f1spot.y }
    $a = Invoke-CRFlow $G "g2 = $(Find-Lua 'abspow' $s 10); SetPosition(g2, at($($s.x + 40), $($s.y), $($s.z))); return xyz(g2)"
    $o = Poll $H "local p = xyz(f1); return math.abs(p[1] - $($s.x + 40)) < 10 and p"
    Start-Sleep -Seconds 2
    $guestLater = Invoke-CRFlow $G 'return xyz(g2)'
    $moved = [math]::Abs($a[0] - ($s.x + 40)) -lt 10
    $back = [math]::Abs($guestLater[0] - $s.x) -lt 10
    $r = if ($o.value) { 'replicated' } elseif ($moved -and $back) { 'reverted' } elseif ($moved) { 'diverged' } else { 'none' }
    Add-Finding 'G2' 'ownership' 'Guest SetPosition() on a host-owned object reaches the host' $r @{ actor = $a; host = $o.value; guestAfterWait = $guestLater; seconds = $o.seconds }
}

# ----------------------------------------------------------------- team --
Invoke-CRFlowStep 'H1 host SetTeamNum on host-owned building' {
    $s = @{ x = $script:f1spot.x + 40; z = $script:f1spot.z }
    $a = Invoke-CRFlow $H 'SetTeamNum(f1, 5); return GetTeamNum(f1)'
    $o = Poll $G "local h = $(Find-Lua 'abspow' $s 60); return h and GetTeamNum(h) == 5 and GetTeamNum(h)"
    Add-Finding 'H1' 'team' 'Host SetTeamNum() on a host-owned object reaches the guest' $(if ($o.value) { 'replicated' } else { 'local-only' }) @{ actor = $a; other = $o.value; seconds = $o.seconds }
}

# --------------------------------------------------------------- weapons --
Invoke-CRFlowStep 'I1 guest GiveWeapon on own craft' {
    $slots = "local function slots(h) local t = {}; for i = 0, 4 do local ok, w = pcall(GetWeaponClass, h, i); t[#t + 1] = ok and (w or '') or '?' end; return t end"
    $a = Invoke-CRFlow $G "$slots; local before = slots(me()); local ok = GiveWeapon(me(), 'gmortar'); return { before = before, gave = ok, after = slots(me()) }"
    Start-Sleep -Seconds $ObserveSeconds
    $o = Invoke-CRFlow $H "$slots; for _, p in pairs(CRCoop and CRCoop.GetPlayers() or {}) do if p.team == $($gr.team) and p.handle then return slots(p.handle) end end"
    $hasMortar = @($o) -contains 'gmortar'
    $r = if (-not (@($a.after) -contains 'gmortar')) { 'none' } elseif ($hasMortar) { 'replicated' } else { 'local-only' }
    Add-Finding 'I1' 'weapons' "Guest GiveWeapon() on its own craft shows in the host's view of that craft" $r @{ actor = $a; host = $o }
}

Invoke-CRFlowStep 'I2 host GiveWeapon on the guest craft' {
    $slots = "local function slots(h) local t = {}; for i = 0, 4 do local ok, w = pcall(GetWeaponClass, h, i); t[#t + 1] = ok and (w or '') or '?' end; return t end"
    $a = Invoke-CRFlow $H "$slots; for _, p in pairs(CRCoop and CRCoop.GetPlayers() or {}) do if p.team == $($gr.team) and p.handle then local ok = GiveWeapon(p.handle, 'gspstab'); return { gave = ok, after = slots(p.handle) } end end"
    Start-Sleep -Seconds $ObserveSeconds
    $o = Invoke-CRFlow $G "$slots; return slots(me())"
    $r = if (-not (@($a.after) -contains 'gspstab')) { 'none' } elseif (@($o) -contains 'gspstab') { 'replicated' } else { 'local-only' }
    Add-Finding 'I2' 'ownership' "Host GiveWeapon() on the guest's craft reaches the guest" $r @{ actor = $a; guest = $o }
}

# ------------------------------------------------------------ removal --
Invoke-CRFlowStep 'B2 guest RemoveObject on host-owned building' {
    $s = $script:b2spot
    $a = Invoke-CRFlow $G "local h = $(Find-Lua 'abspow' $s); RemoveObject(h); return { removedLocally = $(Find-Lua 'abspow' $s) == nil }"
    Start-Sleep -Seconds $ObserveSeconds
    $hostHas = Invoke-CRFlow $H 'return IsValid(b2)'
    $guestHasAgain = Invoke-CRFlow $G "return $(Find-Lua 'abspow' $s) ~= nil"
    $r = if (-not $a.removedLocally) { 'none' } elseif (-not $hostHas) { 'replicated' } elseif ($guestHasAgain) { 'reverted' } else { 'diverged' }
    Add-Finding 'B2' 'ownership' 'Guest RemoveObject() on a host-owned object reaches the host' $r @{ actor = $a; hostStillHas = $hostHas; guestHasAgainAfterWait = $guestHasAgain }
}

Invoke-CRFlowStep 'B1 host RemoveObject on host-owned building' {
    $s = $script:b2spot
    $before = Invoke-CRFlow $G "return $(Find-Lua 'abspow' $s) ~= nil"
    Invoke-CRFlow $H 'RemoveObject(b2); return IsValid(b2)' | Out-Null
    $o = Poll $G "return $(Find-Lua 'abspow' $s) == nil"
    $r = if (-not $before) { 'n/a (guest had no copy)' } elseif ($o.value) { 'replicated' } else { 'local-only' }
    Add-Finding 'B1' 'spawn' 'Host RemoveObject() on a host-owned object removes it on the guest' $r @{ guestHadIt = $before; seconds = $o.seconds }
}

# ------------------------------------------------------ custom events --
Invoke-CRFlowStep 'J1 Send/Receive value types and payload size' {
    Invoke-CRFlow $G 'inbox(); return true' | Out-Null
    $sw = [Diagnostics.Stopwatch]::StartNew()
    Invoke-CRFlow $H "Send(0, '~', 'J1', 1.25, -7, true, false, 'text'); Send(0, '~', 'J2', string.rep('x', 200)); Send(0, '~', 'J3', string.rep('y', 400)); return true" | Out-Null
    $o = Poll $G 'local m = inbox(); return #m > 0 and m' 5
    Start-Sleep -Seconds 2
    $more = Invoke-CRFlow $G 'return inbox()'
    $all = @($o.value) + @($more) | Where-Object { $_ }
    $j1 = $all | Where-Object { @($_.args)[0] -eq 'J1' } | Select-Object -First 1
    $len = { param($tag) $m = $all | Where-Object { @($_.args)[0] -eq $tag } | Select-Object -First 1; if ($m) { (@($m.args)[1]).Length } else { $null } }
    $ev = @{ firstSeconds = $o.seconds; j1 = $(if ($j1) { $j1.args } else { $null }); j2len = & $len 'J2'; j3len = & $len 'J3'; sendCallSeconds = [math]::Round($sw.Elapsed.TotalSeconds, 1) }
    $r = if ($j1 -and $ev.j2len -eq 200 -and $ev.j3len -eq 400) { 'replicated' } elseif ($j1) { 'partial' } else { 'none' }
    Add-Finding 'J1' 'events' 'Send(0, ...) delivers numbers/booleans/strings; 200 and 400 byte strings' $r $ev
}

Invoke-CRFlowStep 'J2 guest Send to host' {
    Invoke-CRFlow $H 'inbox(); return true' | Out-Null
    Invoke-CRFlow $G "Send(0, '~', 'J4', 42); return true" | Out-Null
    $o = Poll $H 'local m = inbox(); return #m > 0 and m' 5
    Add-Finding 'J2' 'events' 'Guest Send(0, ...) reaches the host' $(if ($o.value) { 'replicated' } else { 'none' }) @{ received = $o.value; seconds = $o.seconds }
}

# --------------------------------------------------------------- report --
$md = New-Object System.Text.StringBuilder
[void]$md.AppendLine('# Stock replication findings (live, two clients)')
[void]$md.AppendLine('')
[void]$md.AppendLine("Run ``$(Split-Path $script:CRFlowRun.runDir -Leaf)``, mission ``$($script:CRFlowRun.mission)``, host team $($hr.team), guest team $($gr.team). Observation window ${ObserveSeconds}s. Raw evidence: ``replication-findings.jsonl``.")
[void]$md.AppendLine('')
[void]$md.AppendLine('| Case | Area | Question | Result | Latency (s) |')
[void]$md.AppendLine('|---|---|---|---|---|')
foreach ($f in $findings) {
    $lat = if ($f.evidence -is [hashtable] -and $f.evidence.ContainsKey('seconds')) { $f.evidence.seconds } else { '' }
    [void]$md.AppendLine("| $($f.id) | $($f.area) | $($f.question) | **$($f.result)** | $lat |")
}
Set-Content -LiteralPath (Join-Path $script:CRFlowRun.runDir 'replication-findings.md') -Value $md.ToString()
Add-CRFlowCheck "replication cases recorded ($($findings.Count))" ($findings.Count -gt 0) (@($findings | ForEach-Object { "$($_.id)=$($_.result)" }))
