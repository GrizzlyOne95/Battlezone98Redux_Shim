# Stock bug pack (mpbugs map, Run-BZRMpBugs.ps1 -Case LockAllies): LockAllies(true)
# called from Start() does not lock the ally prompt in Redux, so a player in a
# forced co-op mission can still press U (unally) or Y (ally). A later call
# works. 1.5 honours the Start() call.
#
# Cause (reverse_engineering\notes\ally_lock_from_start_20261123.md): after the
# mission's Start(), sim startup rebuilds the net-game UI, which re-creates the
# ally editor and writes the lock gate back to 0. mpbugs.lua locks once in
# Start() and takes the global away from CRCoop, whose 5 s re-lock would hide it.
#
# On every peer: U and Y right after start (Stock: the box opens, the defect;
# Fixed: it stays shut), then two controls that hold in both arms: unlocked, Y
# opens the box (the probe can see it open), and a later LockAllies(true) keeps
# it shut (the probe can see it shut). Esc closes every box without sending a
# team number, so no alliance ever changes. The Stock arm turns
# [Network] AllyLockSurvivesStart off in the instance ini (Run-BZRMpBugs.ps1).
param([ValidateSet('Stock','Fixed')][string]$Expect = 'Stock',
      # Seconds after the mission is ready before the first key press.
      [int]$SettleSeconds = 6,
      # Real input with the desktop foreground (takes focus per press). The
      # default posts the key messages, which the window procedure routes to
      # the keyboard pump (0x00619BE0) while no editor has focus.
      [switch]$Focused)

$C = @(Get-CRFlowClientIndices)
$script:CRFlowSkipParity = $true   # text entry is per-client UI
$VK = @{ Y = 0x59; U = 0x55; Esc = 0x1B }

function Press([int]$Client, [string]$Key, [int]$AfterMs = 600) {
    Send-CRFlowKey $Client $VK[$Key] -Focused:$Focused
    Start-Sleep -Milliseconds $AfterMs
}
function Entry([int]$Client) { Invoke-CRFlow $Client 'return exu.GetTextEntryDebugState()' }
# Esc cancels the box without sending; a second Esc would open the pause menu.
function Close-Entry([int]$Client) {
    if ((Entry $Client).textEntryActive) { Press $Client Esc 500 }
    if (Invoke-CRFlow $Client 'return exu.IsPauseMenuOpen and exu.IsPauseMenuOpen()') { Press $Client Esc 500 }
}
function Probe([int]$Client, [string]$Key) {
    Close-Entry $Client
    Press $Client $Key
    $s = Entry $Client
    Close-Entry $Client
    $s
}

$shimLogs, $shimMarks = @{}, @{}
foreach ($i in $C) {
    $shimLogs[$i] = Join-Path (Get-CRFlowClient $i).dir 'logs\openshim.log'
    $shimMarks[$i] = 0   # the hook logs at mission start, before the scenario
}

Invoke-CRFlowStep 'fixture: Start() locked once, CRCoop cannot re-lock, probe present' {
    Start-Sleep -Seconds $SettleSeconds
    $out = @{}
    foreach ($i in $C) {
        $f = Invoke-CRFlow $i 'return { probe = type(exu.GetTextEntryDebugState), global = type(LockAllies), started = BugState().lockedInStart }'
        if ($f.probe -ne 'function') { throw "c$i EXU has no GetTextEntryDebugState" }
        if ($f.global -ne 'nil') { throw "c$i LockAllies global is $($f.global); CRCoop would re-lock" }
        if (-not $f.started) { throw "c$i Start() did not call LockAllies(true)" }
        $out["c$i"] = $f
    }
    $out
}

foreach ($i in $C) {
    $start = Invoke-CRFlowStep "c${i}: U and Y after LockAllies(true) in Start()" {
        @{ U = (Probe $i 'U'); Y = (Probe $i 'Y') }
    }
    $controls = Invoke-CRFlowStep "c${i}: controls (unlocked Y opens; later lock keeps it shut)" {
        Invoke-CRFlow $i 'return BugLockAllies(false)' | Out-Null
        $openU = Probe $i 'U'
        $openY = Probe $i 'Y'
        Invoke-CRFlow $i 'return BugLockAllies(true)' | Out-Null
        $shutU = Probe $i 'U'
        $shutY = Probe $i 'Y'
        @{ openU = $openU; openY = $openY; shutU = $shutU; shutY = $shutY }
    }
    $opened = [bool]($start.U.allyPromptOpen -or $start.Y.allyPromptOpen)
    $both = [bool]($start.U.allyPromptOpen -and $start.Y.allyPromptOpen)
    # Both keys must open the box unlocked, or a shut box after Start() proves nothing.
    Add-CRFlowCheck "control c${i}: unlocked, U and Y open the ally box" ([bool]($controls.openU.allyPromptOpen -and $controls.openY.allyPromptOpen)) $controls
    $shut = -not ($controls.shutU.textEntryActive -or $controls.shutY.textEntryActive)
    Add-CRFlowCheck "control c${i}: a later LockAllies(true) keeps U and Y shut" ([bool]$shut) $controls
    if ($Expect -eq 'Stock') {
        Add-CRFlowCheck "stock c${i}: U and Y open the ally box despite LockAllies(true) in Start()" $both $start
    } else {
        Add-CRFlowCheck "fixed c${i}: U and Y stay shut after LockAllies(true) in Start()" ([bool](-not $opened)) $start
    }
    $lines = @()
    if (Test-Path -LiteralPath $shimLogs[$i]) {
        $text = (Read-CRFlowShared $shimLogs[$i] $shimMarks[$i]).Text
        $lines = @([regex]::Matches($text, '(?m)^.*\[ALLYLOCK\].*$') | ForEach-Object { $_.Value.Trim() })
    }
    $redirected = @($lines -match 'redirected').Count -gt 0
    $restored = @($lines -match 'restored LockAllies gate').Count -gt 0
    if ($Expect -eq 'Fixed') {
        # The hook must be in and must have restored the Start() lock, or a
        # shut box would not be the fix's doing.
        Add-CRFlowCheck "fixed c${i}: [ALLYLOCK] redirected the call and restored the Start() lock" ([bool]($redirected -and $restored)) @{ lines = $lines }
    } else {
        Add-CRFlowCheck "stock c${i}: no [ALLYLOCK] redirect with the fix off" ([bool](-not $redirected)) @{ lines = $lines }
    }
}
