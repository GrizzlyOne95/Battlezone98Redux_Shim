# CR co-op PDA and pings driven by real key presses on both clients (misn03).
#
# The protocol itself is covered by CR's Tools\Test-CoopCommsLive.ps1 (Lua
# calls). This drives the controls a player uses and checks what each side
# ends up with: X opens/closes the PDA (Co-op page first), [ / ] walk the
# pages, arrows move/change rows, J acts on the selected row or, with the PDA
# closed, pings the reticle target. Plus suppression, the ping cooldown and
# whether Q could carry the ping.
#
# Needs a content override with the CR comms branch and the new exu.dll
# (New-CRFlowOverride.ps1 -Name coop-comms -Extra ...\exu.dll).
#
# Keys: every key is real input (-Focused takes the desktop focus for the
# press and gives it back). Posted key messages reach neither CR's polled keys
# nor GameKey. In a network game Redux calls GameKey only for some keys (Y,
# digits, /; not J, [ ], arrows, Enter: scenarios\gamekey-names.ps1), so CR
# polls J / [ ] / arrows there through exu.GetGameKey and tracks chat itself.
param([int]$HostClient = 0, [int]$GuestClient = 1,
      # Also check Q as a ping key candidate (throttle_up in stock input.map).
      [switch]$SkipQ)

$H, $G = $HostClient, $GuestClient
# Target selection and pings are local presentation; mission parity does not apply.
$script:CRFlowSkipParity = $true

$VK = @{ X = 0x58; J = 0x4A; Q = 0x51; '[' = 0xDB; ']' = 0xDD; Up = 0x26; Down = 0x28
         Left = 0x25; Right = 0x27; Esc = 0x1B; Enter = 0x0D }

function Press([int]$Client, [string]$Key, [int]$AfterMs = 450) {
    Send-CRFlowKey $Client $VK[$Key] -Focused
    # CR consumes queued keys in its next Update; give it a few frames.
    Start-Sleep -Milliseconds $AfterMs
}
function Pda([int]$Client) { Invoke-CRFlow $Client 'return pdaState()' }
function Assert-That([bool]$Ok, [string]$Message, $State) {
    if (-not $Ok) { throw "$Message $(if ($null -ne $State) { ConvertTo-Json $State -Compress -Depth 6 })" }
}

# Lua installed on each client: state readers, a GameKey/DisplayMessage log.
$setupLua = @'
pc = package.loaded.PersistentConfig
comms = CRCoop.GetComms()
local function upvalue(f, want)
    for i = 1, 80 do
        local n, v = debug.getupvalue(f, i)
        if not n then return nil end
        if n == want then return v end
    end
end
IS = upvalue(pc.R.QueueGameKey, "InputState")
local hudSlots = function() return upvalue(pc.CoopPingHud.Update, "slots") or {} end
COOP = pc.CoopPda.IsActive() and pc.CoopPda.PageOrder()[1] or nil
keysSeen, msgs = keysSeen or {}, msgs or {}
if not crflowKeyHook then
    crflowKeyHook = true
    local oldKey, oldMsg = _G.GameKey, _G.DisplayMessage
    _G.GameKey = function(k) keysSeen[#keysSeen + 1] = tostring(k); return oldKey(k) end
    _G.DisplayMessage = function(t, ...)
        msgs[#msgs + 1] = { t = GetTime(), text = tostring(t) }
        return oldMsg(t, ...)
    end
end
local function count(t) local n = 0; for _ in pairs(t) do n = n + 1 end; return n end
pdaState = function()
    local ui = pc.CoopPda
    return { open = pc.Settings.WeaponStatsHud == true, page = IS.pdaPage, coop = COOP,
             pageNo = (ui.PageNumber(IS.pdaPage)), pages = #ui.PageOrder(),
             row = ui.row, response = ui.response, pingId = ui.pingId, requestId = ui.requestId,
             pings = count(comms.GetPings()), requests = count(comms.GetRequests()),
             keys = keysSeen, lastToggle = IS.last_toggle_state }
end
otherPing = function()
    for id, p in pairs(comms.GetPings()) do if id ~= CRCoop.GetLocalPlayerId() then return p end end
end
pingList = function()
    local out = {}
    for id, p in pairs(comms.GetPings()) do
        out[#out + 1] = { from = id, seq = p.seq, kind = p.kind, name = p.name,
            handle = p.handle and describe(p.handle) or nil,
            pos = { p.position.x, p.position.y, p.position.z }, left = p.expires - GetTime() }
    end
    return out
end
hudState = function()
    local out = {}
    for i, s in pairs(hudSlots()) do out[#out + 1] = { slot = i, visible = s.visible == true, ready = s.ready == true } end
    return out
end
msgsSince = function(t0)
    local out = {}
    for _, m in ipairs(msgs) do if m.t >= t0 then out[#out + 1] = m.text end end
    return out
end
-- Known starting point: PDA closed, Co-op page selected, row 1.
pc._SettingsActions.SetWeaponStatsHudEnabled(false)
pc.CoopPda.row, pc.CoopPda.response = 1, 1
for k in pairs(keysSeen) do keysSeen[k] = nil end
return { coop = COOP, pages = pc.CoopPda.PageOrder(), inputState = IS ~= nil, debug = debug ~= nil,
         hit = type(exu.GetReticleHit), authority = CRCoop.IsAuthority() }
'@

Invoke-CRFlowStep 'probes attached; co-op comms active on both clients' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowEvent $G attach -TimeoutSeconds 120 | Out-Null
    foreach ($c in $H, $G) {
        Wait-CRFlow $c 'return CRCoop.IsSessionReady() and CRCoop.GetComms() and CRCoop.GetComms().IsActive()' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.start_done and role().ready' -TimeoutSeconds 120 | Out-Null
    @{ host = Invoke-CRFlow $H $setupLua; guest = Invoke-CRFlow $G $setupLua }
}

Invoke-CRFlowStep 'keep the mission alive (test assist)' {
    # misn03 is lost to the first wave in ~77 s if nobody fights.
    Invoke-CRFlow $H @'
kill(M.wave1_1); kill(M.wave1_2)
every('protect', 1, function()
    for _, k in ipairs({ "solar1", "solar2", "solar3", "solar4", "launch", "avrecycler", "rescue1", "rescue2" }) do
        if M[k] then heal(M[k]) end
    end
    clearAroundPlayers(5, nil, 400)
end)
return true
'@ | Out-Null
    foreach ($c in $H, $G) { Invoke-CRFlow $c "every('selfheal', 1, function() heal(me()) end); return true" | Out-Null }
    'protect + selfheal + clear near players'
}

# ---------------------------------------------------------- input path --

Invoke-CRFlowStep 'input path: polled keys reach CR (X opens, ] turns the page)' {
    $poller = Invoke-CRFlow $H 'return type(pc._PollNetworkGameKeys) == "function" and CRCoop.IsNetworkGame()'
    if (-not $poller) { throw 'CR build has no network key polling (PersistentConfig._PollNetworkGameKeys); regenerate the override' }
    Press $H X 600
    $s = Pda $H
    Assert-That ($s.open) 'X did not open the PDA' $s
    $before = $s.page
    Press $H ']' 600
    $s = Pda $H
    Assert-That ($s.page -ne $before) '] did not change the page' $s
    # Back to the known state.
    Invoke-CRFlow $H 'pc._SettingsActions.SetWeaponStatsHudEnabled(false); for k in pairs(keysSeen) do keysSeen[k] = nil end; return true' | Out-Null
    @{ pageBefore = $before; pageAfter = $s.page; gameKeyCalls = @($s.keys) }
}

# Chat is not covered: CR cannot tell chat typing from play in a network game
# (polled keys), and Enter did not open a chat line in these test clients.
# --------------------------------------------------------- open / pages --

foreach ($c in $H, $G) {
    $who = if ($c -eq $H) { 'host' } else { 'guest' }
    Invoke-CRFlowStep "$who`: X opens the PDA on the Co-op page, X closes it" {
        # Leave the PDA on another page first: opening in co-op must land on Co-op.
        Invoke-CRFlow $c 'IS.pdaPage = pc.CoopPda.PageOrder()[3]; return true' | Out-Null
        Press $c X
        $opened = Pda $c
        Assert-That ($opened.open -and $opened.page -eq $opened.coop -and $opened.pageNo -eq 1) 'X did not open on the Co-op page' $opened
        Press $c X
        $closed = Pda $c
        Assert-That (-not $closed.open) 'second X did not close the PDA' $closed
        Press $c X   # open again for the next steps
        @{ opened = $opened; closed = $closed.open }
    }

    Invoke-CRFlowStep "$who`: [ and ] walk every page and wrap" {
        $start = Pda $c
        $n = [int]$start.pages
        $fwd = foreach ($i in 1..$n) { Press $c ']' 350; (Pda $c).page }
        Assert-That ($fwd[-1] -eq $start.coop) "$n x ] did not wrap back to Co-op" @{ fwd = $fwd }
        Assert-That (@($fwd | Sort-Object -Unique).Count -eq $n) 'some page was skipped or repeated' @{ fwd = $fwd }
        Press $c '[' 350
        $back = Pda $c
        Assert-That ($back.page -eq $fwd[-2]) '[ from Co-op did not wrap to the last page' @{ fwd = $fwd; back = $back.page }
        Press $c ']' 350
        Assert-That ((Pda $c).page -eq $start.coop) '] did not return to Co-op' $null
        @{ pages = $n; order = $fwd }
    }
}

Invoke-CRFlowStep 'host: arrows move the row and change the reply' {
    $rows = @()
    Press $H Down; $rows += (Pda $H).row
    Press $H Up; $rows += (Pda $H).row
    Press $H Up; $rows += (Pda $H).row          # wraps to the last host row (6, Reply)
    Assert-That (($rows -join ',') -eq '2,1,6') "row sequence $($rows -join ',') (want 2,1,6)" @{ gameKeys = (Pda $H).keys }
    Press $H Right; $r1 = (Pda $H).response
    Press $H Left; $r2 = (Pda $H).response
    Assert-That ($r1 -eq 2 -and $r2 -eq 1) "reply toggles $r1,$r2 (want 2,1)" $null
    Press $H Down                               # back to row 1
    Assert-That ((Pda $H).row -eq 1) 'Down from the last row did not wrap to 1' (Pda $H)
    @{ rows = $rows; replies = @($r1, $r2) }
}

Invoke-CRFlowStep 'guest: arrows wrap over its four rows' {
    $rows = @()
    Press $G Up; $rows += (Pda $G).row
    Press $G Down; $rows += (Pda $G).row
    Assert-That (($rows -join ',') -eq '4,1') "guest row sequence $($rows -join ',') (want 4,1)" @{ gameKeys = (Pda $G).keys }
    $rows
}

# --------------------------------------------------------------- pings --

# Puts an object of this client's own team ahead of its craft, in the reticle.
$aimLua = @'
local h = me()
local t = GetTransform(h)
local p = GetPosition(h)
local d = %DIST%
local x, z = p.x + t.front_x * d, p.z + t.front_z * d
local y = GetTerrainHeightAndNormal(SetVector(x, 0, z))
aimObj = BuildObject("%ODF%", GetTeamNum(h), SetVector(x, y + 1, z))
SetTransform(aimObj, BuildDirectionalMatrix(GetPosition(aimObj), SetVector(-t.front_x, 0, -t.front_z)))
Stop(aimObj, 1)
return describe(aimObj)
'@

Invoke-CRFlowStep 'guest: PDA row 1 + J pings what it aims at; host sees ping and marker' {
    $t0 = Invoke-CRFlow $H 'return GetTime()'
    # Something the guest owns in its reticle, so the aim does not depend on spawn.
    Invoke-CRFlow $G ($aimLua -replace '%DIST%', '45' -replace '%ODF%', 'avtank') | Out-Null
    $aim = Wait-CRFlow $G 'local k, h, pos = exu.GetReticleHit(); return k and { kind = k, h = h and describe(h), pos = pos and { pos.x, pos.y, pos.z } }' -TimeoutSeconds 4
    Assert-That ((Pda $G).row -eq 1) 'guest is not on row 1' (Pda $G)
    Press $G J 600
    if (-not $aim.kind) { throw "guest reticle sees nothing; nothing to ping: $(ConvertTo-Json $aim -Compress)" }
    $ping = Wait-CRFlow $H 'for id, p in pairs(comms.GetPings()) do if id ~= CRCoop.GetLocalPlayerId() then return pingList() end end' -TimeoutSeconds 8
    $marker = Wait-CRFlow $H 'for _, s in ipairs(hudState()) do if s.visible then return hudState() end end' -TimeoutSeconds 4
    $notice = Invoke-CRFlow $H "return msgsSince($t0)"
    Assert-That (@($ping | Where-Object { $_.kind -eq $aim.kind }).Count -ge 1) "host got a ping of another kind than the guest aimed ($($aim.kind))" $ping
    Assert-That (@($notice | Where-Object { $_ -match 'pinged' }).Count -ge 1) 'no "pinged" notice on the host' $notice
    @{ aim = $aim; hostPings = $ping; hostMarker = $marker; hostNotice = $notice }
}

Invoke-CRFlowStep 'host: PDA closed, J on terrain -> terrain ping on guest' {
    Press $H X
    Assert-That (-not (Pda $H).open) 'host PDA did not close' (Pda $H)
    Start-Sleep -Milliseconds 1600   # ping cooldown
    # Clear host-owned objects (mission pilots, craft) out of the line of sight;
    # the reticle hit updates on the next frame.
    foreach ($i in 1..4) {
        $aim = Invoke-CRFlow $H 'local k, h = exu.GetReticleHit(); return { kind = k, h = h and describe(h), local_ = h and IsLocal(h) or false }'
        if ($aim.kind -ne 'object' -or -not $aim.local_) { break }
        Invoke-CRFlow $H 'local k, h = exu.GetReticleHit(); if h then put(h, me(), 250) end; return true' | Out-Null
        Start-Sleep -Milliseconds 300
    }
    if ($aim.kind -ne 'terrain') { throw "host reticle is not on terrain ($(ConvertTo-Json $aim -Compress)); cannot run this case" }
    $before = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    Press $H J 600
    $got = Wait-CRFlow $G "local p = otherPing(); return p and p.seq > $before and p.kind == 'terrain' and pingList()" -TimeoutSeconds 8
    $marker = Invoke-CRFlow $G 'return hudState()'
    @{ aim = $aim; guestPings = $got; guestMarker = $marker }
}

Invoke-CRFlowStep 'host: PDA closed, J on an object -> object ping follows it on guest' {
    Start-Sleep -Milliseconds 1600
    Invoke-CRFlow $H ($aimLua -replace '%DIST%', '45' -replace '%ODF%', 'avtank') | Out-Null
    $aim = Wait-CRFlow $H 'local k, h = exu.GetReticleHit(); return k == "object" and { kind = k, h = describe(h), isAim = h == aimObj }' -TimeoutSeconds 4
    Press $H J 600
    $got = Wait-CRFlow $G "local p = otherPing(); return p and p.kind == 'object' and p.handle and IsValid(p.handle) and pingList()" -TimeoutSeconds 8
    # The marker follows the craft: move it and compare the ping position source.
    $moved = Invoke-CRFlow $H 'put(aimObj, me(), 70); return xyz(aimObj)'
    Start-Sleep -Seconds 1
    $seen = Invoke-CRFlow $G 'local p = otherPing(); local q = GetPosition(p.handle); return { q.x, q.y, q.z }'
    $drift = [math]::Sqrt([math]::Pow($moved[0] - $seen[0], 2) + [math]::Pow($moved[2] - $seen[2], 2))
    @{ aim = $aim; guestPings = $got; movedTo = $moved; guestSeesHandleAt = $seen; driftM = [math]::Round($drift, 1) }
}

Invoke-CRFlowStep 'cooldown: two J presses inside 1.5 s send one ping' {
    Start-Sleep -Milliseconds 1600
    $before = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    $t0 = Invoke-CRFlow $H 'return GetTime()'
    Press $H J 200
    Press $H J 600
    $t1 = Invoke-CRFlow $H 'return GetTime()'
    Start-Sleep -Seconds 2
    $after = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    $hostMsgs = Invoke-CRFlow $H "return msgsSince($t0)"
    Assert-That (($after - $before) -eq 1) "guest saw $($after - $before) new pings (want 1)" @{ before = $before; after = $after; gameSeconds = $t1 - $t0; hostMsgs = $hostMsgs }
    @{ newPings = $after - $before; gameSeconds = [math]::Round($t1 - $t0, 2); hostMsgs = $hostMsgs }
}

# -------------------------------------------------------------- rescue --

Invoke-CRFlowStep 'guest hops out; requests rescue from the PDA' {
    Invoke-CRFlow $H 'if aimObj then RemoveObject(aimObj); aimObj = nil end; return true' | Out-Null
    Invoke-CRFlow $G 'HopOut(GetPlayerHandle()); return true' | Out-Null
    Wait-CRFlow $G 'return IsPerson(GetPlayerHandle())' -TimeoutSeconds 10 | Out-Null
    Wait-CRFlow $H 'for _, p in pairs(CRCoop.GetPlayers()) do if p.team ~= 1 then return p.handle and IsPerson(p.handle) end end' -TimeoutSeconds 10 | Out-Null
    $t0 = Invoke-CRFlow $H 'return GetTime()'
    $s = Pda $G
    if (-not $s.open) { Press $G X; $s = Pda $G }
    Assert-That ($s.open -and $s.page -eq $s.coop) 'guest PDA not open on Co-op' $s
    while ((Pda $G).row -ne 2) { Press $G Down 300 }
    Press $G J 600
    $req = Wait-CRFlow $H 'for id, r in pairs(comms.GetRequests()) do return { id = id, name = r.name, status = r.status } end' -TimeoutSeconds 8
    $text = Invoke-CRFlow $H 'return pc.CoopPda.BuildText(function() return "" end, function() end)'
    $notice = Invoke-CRFlow $H "return msgsSince($t0)"
    Assert-That ($text -match 'Rescue: ') 'host PDA text has no rescue row' $text
    Assert-That (@($notice | Where-Object { $_ -match 'needs a rescue' }).Count -ge 1) 'no rescue notice on the host' $notice
    @{ request = $req; hostPda = $text; hostNotice = $notice }
}

Invoke-CRFlowStep 'host replies "Coming" from the PDA; guest sees status and notice' {
    $t0 = Invoke-CRFlow $G 'return GetTime()'
    $s = Pda $H
    if (-not $s.open) { Press $H X }
    while ((Pda $H).row -ne 6) { Press $H Up 300 }
    if ((Pda $H).response -ne 1) { Press $H Left }
    Press $H J 600
    $st = Wait-CRFlow $G 'local r = comms.GetRequests()[CRCoop.GetLocalPlayerId()]; return r and r.status == "Help on the way" and r.status' -TimeoutSeconds 8
    $notice = Invoke-CRFlow $G "return msgsSince($t0)"
    $text = Invoke-CRFlow $G 'return pc.CoopPda.BuildText(function() return "" end, function() end)'
    Assert-That ($text -match 'Help on the way') 'guest PDA does not show the reply' $text
    Assert-That (@($notice | Where-Object { $_ -match 'Help on the way' }).Count -ge 1) 'no reply notice on the guest' $notice
    @{ status = $st; guestNotice = $notice; guestPda = $text }
}

Invoke-CRFlowStep 'host replies "No craft available"; guest cancels from the PDA' {
    Press $H Right
    Assert-That ((Pda $H).response -eq 2) 'Right did not select "No craft available"' (Pda $H)
    Start-Sleep -Milliseconds 500
    Press $H J 600
    Wait-CRFlow $G 'local r = comms.GetRequests()[CRCoop.GetLocalPlayerId()]; return r and r.status == "No craft available"' -TimeoutSeconds 8 | Out-Null
    Assert-That ((Pda $G).row -eq 2) 'guest row moved' (Pda $G)
    Press $G J 600
    Wait-CRFlow $H 'return next(comms.GetRequests()) == nil' -TimeoutSeconds 8 | Out-Null
    Wait-CRFlow $G 'return next(comms.GetRequests()) == nil' -TimeoutSeconds 8
}

# --------------------------------------------------------- suppression --

Invoke-CRFlowStep 'suppressed during a film: J sends no ping and markers hide' {
    Invoke-CRFlow $G 'pc._SettingsActions.SetWeaponStatsHudEnabled(false); return true' | Out-Null
    Invoke-CRFlow $H 'pc._SettingsActions.SetWeaponStatsHudEnabled(false); return true' | Out-Null
    Start-Sleep -Milliseconds 1600
    # A guest ping first, so there is a marker on the host to hide.
    Press $G J 600
    Wait-CRFlow $H 'for _, s in ipairs(hudState()) do if s.visible then return true end end' -TimeoutSeconds 6 | Out-Null
    $before = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    $ok = Invoke-CRFlow $H 'native.CameraReady(); every("film", 0, function() native.CameraPath("camera_path", 3000, 1000, me()) end); return setCameraActive(true)'
    if (-not $ok) { throw 'probe stub has no setCameraActive; reinstall the probe' }
    Start-Sleep -Milliseconds 600
    $hidden = Invoke-CRFlow $H 'return hudState()'
    Press $H J 600
    Start-Sleep -Seconds 2
    $after = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    Invoke-CRFlow $H 'cancel("film"); setCameraActive(false); native.CameraFinish(); return true' | Out-Null
    Assert-That ($after -eq $before) "a ping was sent during the film ($before -> $after)" $null
    Assert-That (@($hidden | Where-Object { $_.visible }).Count -eq 0) 'markers still visible during the film' $hidden
    @{ seqBefore = $before; seqAfter = $after; hostMarkersDuringFilm = $hidden }
} -Soft

Invoke-CRFlowStep 'suppressed with the Esc menu open' {
    Start-Sleep -Milliseconds 1600
    $before = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    Press $H Esc 800
    $menu = Invoke-CRFlow $H 'return exu.IsPauseMenuOpen and exu.IsPauseMenuOpen()'
    Press $H J 600
    Start-Sleep -Seconds 2
    $after = Invoke-CRFlow $G 'local p = otherPing(); return p and p.seq or 0'
    if ($menu) { Press $H Esc 800 }
    $menuAfter = Invoke-CRFlow $H 'return exu.IsPauseMenuOpen and exu.IsPauseMenuOpen()'
    Assert-That ([bool]$menu) 'Esc did not open the menu (exu.IsPauseMenuOpen false)' $null
    Assert-That ($after -eq $before) "a ping was sent with the menu open ($before -> $after)" $null
    @{ menuOpen = $menu; menuAfterSecondEsc = $menuAfter; seqBefore = $before; seqAfter = $after }
} -Soft

# ------------------------------------------------------- Q as ping key --

if (-not $SkipQ) {
    Invoke-CRFlowStep 'Q candidate: does GameKey see it, and how much throttle does a tap add' {
        # Back in a craft and parked, so a throttle change shows as speed.
        $craft = Invoke-CRFlow $H 'local h = me(); SetVelocity(h, SetVector(0, 0, 0)); return { odf = GetOdf(h), person = IsPerson(h) }'
        Start-Sleep -Seconds 1
        $v0 = Invoke-CRFlow $H 'for k in pairs(keysSeen) do keysSeen[k] = nil end; local v = GetVelocity(me()); return math.sqrt(v.x * v.x + v.z * v.z)'
        Press $H Q 1500
        $v1 = Invoke-CRFlow $H 'local v = GetVelocity(me()); return math.sqrt(v.x * v.x + v.z * v.z)'
        Start-Sleep -Seconds 2
        $v2 = Invoke-CRFlow $H 'local v = GetVelocity(me()); return math.sqrt(v.x * v.x + v.z * v.z)'
        $keys = Invoke-CRFlow $H 'return keysSeen'
        @{ craft = $craft; gameKeySawQ = (@($keys) -contains 'Q' -or @($keys) -contains 'q'); keys = $keys
           speed0 = [math]::Round($v0, 2); speedAfter1_5s = [math]::Round($v1, 2); speedAfter3_5s = [math]::Round($v2, 2) }
    } -Soft
}
