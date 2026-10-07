# Any mission: which key presses reach the mission's GameKey callback, and
# under what name. Presses each key as real (focused) input on the host and
# records every GameKey call in between. Not a pass/fail test: the step
# results are the table. Use before relying on a key in mission Lua.
#
#   Run-BZRCoopMission.ps1 -Mission misn03 -Scenario gamekey-names
param([int]$HostClient = 0,
      [string[]]$Modes = @('scan'),
      [string[]]$Keys = @('Y', 'J', 'X', 'Q', '[', ']', 'Up', 'Down', 'Left', 'Right', 'Enter', 'Slash', '1'))

$H = $HostClient
$script:CRFlowSkipParity = $true
$VK = @{ Y = 0x59; J = 0x4A; X = 0x58; Q = 0x51; '[' = 0xDB; ']' = 0xDD; Up = 0x26; Down = 0x28
         Left = 0x25; Right = 0x27; Enter = 0x0D; Slash = 0xBF; '1' = 0x31 }

Invoke-CRFlowStep 'probe attached; GameKey logged' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    Invoke-CRFlow $H @'
keysSeen = {}
local old = _G.GameKey
_G.GameKey = function(k) keysSeen[#keysSeen + 1] = tostring(k); return old(k) end
every('selfheal', 1, function() heal(me()) end)
-- Raw key state (GetAsyncKeyState via EXU), sampled every frame: shows the
-- key reached the OS/game window even when GameKey is never called.
rawSeen = {}
local names = { 'Y', 'J', 'X', 'Q', '1', 'ENTER', 'UARROW', 'DARROW', 'LARROW', 'RARROW' }
every('raw', 0, function()
    for _, n in ipairs(names) do if exu.GetGameKey(n) then rawSeen[n] = true end end
end)
return type(old)
'@
}

# scan = scan code only (KEYEVENTF_SCANCODE); vk = virtual key + scan code.
foreach ($mode in $Modes) {
    foreach ($k in $Keys) {
        Invoke-CRFlowStep "key $k ($mode)" {
            Invoke-CRFlow $H 'for i in pairs(keysSeen) do keysSeen[i] = nil end; for k in pairs(rawSeen) do rawSeen[k] = nil end; return true' | Out-Null
            Send-CRFlowKey $H $VK[$k] -Focused -WithVk:($mode -eq 'vk')
            Start-Sleep -Milliseconds 500
            $seen = Invoke-CRFlow $H 'return keysSeen'
            $raw = Invoke-CRFlow $H 'local o = {}; for k in pairs(rawSeen) do o[#o + 1] = k end; return o'
            "gameKey=[$(@($seen) -join ' ')] raw=[$(@($raw) -join ' ')]"
        } -Soft
    }
}
