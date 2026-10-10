# Stock text entry vs CR's co-op keys (misn03), with real key presses.
#
# exu.IsTextEntryActive / IsAllyPromptOpen / GetTextEntryDebugState read the
# engine's legacy text-editor focus (chat line, ally/unally team-number box;
# TEXT_ENTRY_STATE.md). CR stops queueing its polled keys (J, [ ], arrows) and
# the X toggle while one has focus, and calls LockAllies(true) so Y/U never
# open the ally box in co-op.
#
# Needs a content override with the CR branch and the EXU build that has the
# text-entry bindings (New-CRFlowOverride.ps1 -Name coop-comms -Extra ...\exu.dll).
param([int]$HostClient = 0, [int]$GuestClient = 1)

$H, $G = $HostClient, $GuestClient
$script:CRFlowSkipParity = $true   # text entry and pings are per-client UI

$VK = @{ X = 0x58; J = 0x4A; Y = 0x59; U = 0x55; Esc = 0x1B; Enter = 0x0D; Grave = 0xC0 }

function Press([int]$Client, [string]$Key, [int]$AfterMs = 450) {
    Send-CRFlowKey $Client $VK[$Key] -Focused
    Start-Sleep -Milliseconds $AfterMs
}
function Entry([int]$Client) { Invoke-CRFlow $Client 'return exu.GetTextEntryDebugState()' }
function Assert-That([bool]$Ok, [string]$Message, $State) {
    if (-not $Ok) { throw "$Message $(if ($null -ne $State) { ConvertTo-Json $State -Compress -Depth 6 })" }
}
function GuestPingSeq { Invoke-CRFlow $H 'local p = otherPing(); return p and p.seq or 0' }
# Closes whatever editor has focus on a client (Esc cancels without sending).
function Close-Entry([int]$Client) {
    if ((Entry $Client).textEntryActive) { Press $Client Esc 500 }
    if (Invoke-CRFlow $Client 'return exu.IsPauseMenuOpen()') { Press $Client Esc 500 }
}

$setupLua = @'
pc = package.loaded.PersistentConfig
comms = CRCoop.GetComms()
otherPing = function()
    for id, p in pairs(comms.GetPings()) do if id ~= CRCoop.GetLocalPlayerId() then return p end end
end
pc._SettingsActions.SetWeaponStatsHudEnabled(false)
return { probe = type(exu.GetTextEntryDebugState), lockAllies = type(LockAllies),
         typingGate = type(pc._IsTextEntryActive), state = exu.GetTextEntryDebugState and exu.GetTextEntryDebugState() }
'@

Invoke-CRFlowStep 'probes attached; text-entry probe available on both clients' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Wait-CRFlowEvent $G attach -TimeoutSeconds 120 | Out-Null
    foreach ($c in $H, $G) {
        Wait-CRFlow $c 'return CRCoop.IsSessionReady() and CRCoop.GetComms() and CRCoop.GetComms().IsActive()' -TimeoutSeconds 90 | Out-Null
    }
    Wait-CRFlow $H 'return M.start_done and role().ready' -TimeoutSeconds 120 | Out-Null
    $r = @{ host = Invoke-CRFlow $H $setupLua; guest = Invoke-CRFlow $G $setupLua }
    foreach ($k in 'host', 'guest') {
        $s = $r[$k]
        Assert-That ($s.probe -eq 'function' -and $s.typingGate -eq 'function') "$k lacks the text-entry probe or CR gate (regenerate the override with the new exu.dll)" $s
        Assert-That ([bool]$s.state.ok) "$k text-entry probe reports ok=false (build anchors did not match)" $s
        Assert-That (-not $s.state.textEntryActive) "$k reports text entry active at baseline" $s
    }
    $r
}

Invoke-CRFlowStep 'keep the mission alive (test assist)' {
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

# A guest-owned tank in the guest's reticle, so J would ping if not gated.
$aimLua = @'
local h = me()
local t = GetTransform(h)
local p = GetPosition(h)
local x, z = p.x + t.front_x * 45, p.z + t.front_z * 45
local y = GetTerrainHeightAndNormal(SetVector(x, 0, z))
if aimObj and IsValid(aimObj) then RemoveObject(aimObj) end
aimObj = BuildObject("avtank", GetTeamNum(h), SetVector(x, y + 1, z))
SetTransform(aimObj, BuildDirectionalMatrix(GetPosition(aimObj), SetVector(-t.front_x, 0, -t.front_z)))
Stop(aimObj, 1)
return true
'@
function Aim-Guest {
    Invoke-CRFlow $G $aimLua | Out-Null
    $aim = Wait-CRFlow $G 'local k = exu.GetReticleHit(); return k' -TimeoutSeconds 4
    if (-not $aim) { throw 'guest reticle sees nothing; J would not ping anyway' }
    $aim
}

# ------------------------------------------------------------ ally lock --

Invoke-CRFlowStep 'LockAllies: Y and U open no ally box; co-op alliance intact' {
    Start-Sleep -Seconds 6   # CRCoop.Update has applied the lock
    $out = @{}
    foreach ($k in 'Y', 'U') {
        Press $G $k 600
        $s = Entry $G
        $out[$k] = $s
        if ($s.textEntryActive) { Close-Entry $G }
        Assert-That (-not $s.allyPromptOpen -and -not $s.textEntryActive) "$k opened a text entry despite LockAllies" $s
    }
    # LockAllies only gates the prompt; CR's scripted alliance must still hold.
    $allied = Invoke-CRFlow $H 'for _, p in pairs(CRCoop.GetPlayers()) do if p.team ~= GetTeamNum(me()) and p.handle then return IsAlly(me(), p.handle) end end'
    Assert-That ([bool]$allied) 'host and guest are not allied' $null
    $out.allied = $allied
    $out
}

Invoke-CRFlowStep 'detector: unlocked, Y opens the ally box; J inside it sends no ping' {
    # CR re-locks within 5 s, so unlock and press straight away.
    Start-Sleep -Milliseconds 1600   # ping cooldown
    Aim-Guest | Out-Null
    $before = GuestPingSeq
    Invoke-CRFlow $G 'LockAllies(false); return true' | Out-Null
    Press $G Y 500
    $open = Entry $G
    $gate = Invoke-CRFlow $G 'return { typing = pc._IsTextEntryActive(), ally = exu.IsAllyPromptOpen() }'
    Press $G J 300
    Press $G X 600
    $pda = Invoke-CRFlow $G 'return pc.Settings.WeaponStatsHud == true'
    Start-Sleep -Seconds 1
    $after = GuestPingSeq
    Press $G Esc 600   # Esc cancels: no alliance change
    $closed = Entry $G
    Close-Entry $G
    Assert-That ($open.textEntryActive -and $open.allyPromptOpen -and -not $open.chatOpen) 'Y did not focus the ally box' $open
    Assert-That ($open.focusedNode -eq $open.allyNode) 'focused node is not the ally node' $open
    Assert-That ($gate.typing -and $gate.ally) 'IsTextEntryActive/IsAllyPromptOpen disagree with the snapshot' $gate
    Assert-That ($after -eq $before) "J in the ally box sent a ping ($before -> $after)" $null
    Assert-That (-not $pda) 'X in the ally box toggled the PDA' $null
    Assert-That (-not $closed.textEntryActive) 'Esc did not close the ally box' $closed
    @{ open = $open; gate = $gate; seqBefore = $before; seqAfter = $after; pdaOpened = $pda; afterEsc = $closed }
}

# ----------------------------------------------------------------- chat --

Invoke-CRFlowStep 'chat: Enter or ` focuses the chat line; J and X there are ignored' {
    Start-Sleep -Milliseconds 1600
    Aim-Guest | Out-Null
    $before = GuestPingSeq
    $tried = [ordered]@{}
    $open = $null
    foreach ($k in 'Enter', 'Grave') {
        Press $G $k 600
        $s = Entry $G
        $tried[$k] = $s
        if ($s.chatOpen) { $open = $s; $opener = $k; break }
        Close-Entry $G
    }
    Assert-That ($null -ne $open) 'neither Enter nor ` focused the chat line' $tried
    Assert-That ($open.focusedNode -eq $open.chatNode -and -not $open.allyPromptOpen) 'chat focus snapshot inconsistent' $open
    Press $G J 300
    Press $G X 600
    $pda = Invoke-CRFlow $G 'return pc.Settings.WeaponStatsHud == true'
    Start-Sleep -Seconds 1
    $after = GuestPingSeq
    Press $G Esc 600   # cancel: nothing is sent
    $closed = Entry $G
    Close-Entry $G
    Assert-That ($after -eq $before) "J typed in chat sent a ping ($before -> $after)" $null
    Assert-That (-not $pda) 'X typed in chat toggled the PDA' $null
    Assert-That (-not $closed.textEntryActive) 'Esc did not close chat' $closed
    @{ opener = $opener; tried = $tried; seqBefore = $before; seqAfter = $after; pdaOpened = $pda; afterEsc = $closed }
}

Invoke-CRFlowStep 'after chat closes, J pings again' {
    Start-Sleep -Milliseconds 1600
    $aim = Aim-Guest
    $before = GuestPingSeq
    Press $G J 600
    $got = Wait-CRFlow $H "local p = otherPing(); return p and p.seq > $before and p.seq" -TimeoutSeconds 8
    @{ aim = $aim; seqBefore = $before; seqAfter = $got }
}
