# Hands-on play testing of a running co-op session (after
# Run-BZRCoopMission.ps1 -Scenario play). One action per call; all state is in
# C:\BZRCoop, so calls can come from any shell, one at a time.
#
#   -Status                       processes, mission phase, last log lines
#   -Shot [-Client 0|1|both]      screenshot(s) into <run>\play-shots; prints paths
#   -Lua '<chunk>' [-Client ...]  run Lua in that client's mission (probe helpers:
#                                 M, L(), role(), players(), snap(), tp, put, kill,
#                                 killTeam, clearAroundPlayers, heal, ff, every, ...)
#   -State [-Client ...]          compact mission state (flags, phase, player, locals)
#   -Events [-Kind op] [-Last 30] [-Client ...]   probe events from the logs
#   -Key Space [-HoldMs 0] [-Client ...]          post a key (name or VK number)
#   -Click 640,360 [-Client ...]  left click in client-area pixels (1280x720)
#   -Stop                         stop clients (copies logs to the run) and the server
#
# Windows PowerShell 5.1.

param(
    [ValidateSet('0', '1', 'both')][string]$Client = 'both',
    [string]$Lua = '',
    [switch]$Shot,
    [switch]$State,
    [switch]$Events,
    [string]$Kind = '',
    [int]$Last = 30,
    [string]$Key = '',
    [int]$HoldMs = 0,
    [int[]]$Click = @(),
    [switch]$Status,
    [switch]$Stop,
    [int]$TimeoutSeconds = 20,
    [string]$BZRCoopRoot = 'C:\BZRCoop'
)

$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\BZRCoopMission.ps1"
$script:CRFlowCoopRoot = $BZRCoopRoot
$playFile = Join-Path $BZRCoopRoot 'play.json'
$play = if (Test-Path -LiteralPath $playFile) { Get-Content -LiteralPath $playFile -Raw | ConvertFrom-Json } else { $null }
$targets = if ($Client -eq 'both') { @(0, 1) } else { @([int]$Client) }

function Out-Json($Value) { ConvertTo-Json $Value -Depth 8 }

$VirtualKeys = @{ space = 0x20; enter = 0x0D; return = 0x0D; esc = 0x1B; escape = 0x1B; tab = 0x09
    shift = 0x10; ctrl = 0x11; alt = 0x12; up = 0x26; down = 0x28; left = 0x25; right = 0x27 }
function Get-VirtualKey([string]$Name) {
    if ($Name -match '^\d+$') { return [int]$Name }
    if ($Name -match '^0x[0-9a-f]+$') { return [Convert]::ToInt32($Name.Substring(2), 16) }
    $n = $Name.ToLowerInvariant()
    if ($VirtualKeys.ContainsKey($n)) { return $VirtualKeys[$n] }
    if ($n -match '^f(\d{1,2})$') { return 0x6F + [int]$Matches[1] }
    if ($n.Length -eq 1) { return [int][char]$n.ToUpperInvariant() }
    throw "Unknown key '$Name'"
}

if ($Stop) {
    if (Test-Path -LiteralPath (Join-Path $BZRCoopRoot 'session.json')) {
        & (Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe') -NoProfile -ExecutionPolicy Bypass `
            -File (Join-Path $PSScriptRoot 'BZRCoopSession.ps1') -Action Stop -BZRCoopRoot $BZRCoopRoot
    }
    if ($play) {
        $srv = Get-CimInstance Win32_Process -Filter "ProcessId=$($play.serverPid)" -ErrorAction SilentlyContinue
        if ($srv -and $srv.CommandLine -match 'server\.py') { Stop-Process -Id $play.serverPid -Force; Write-Host "[play] server $($play.serverPid) stopped" }
        Remove-Item -LiteralPath $playFile -Force
        Write-Host "[play] evidence in $($play.runDir)"
    }
    return
}

$session = Get-CRFlowSession

if ($Status) {
    foreach ($c in $session.clients) {
        $alive = [bool](Get-Process -Id $c.pid -ErrorAction SilentlyContinue)
        $log = Get-CRFlowLogPath $c
        [pscustomobject]@{ client = $c.index; pid = $c.pid; alive = $alive
            role = if ($alive) { try { Invoke-CRFlow $c.index 'return role()' -TimeoutSeconds 5 } catch { $_.Exception.Message } } else { $null }
            lastLog = if ($log) { (Get-Content -LiteralPath $log -Tail 1) } else { '' } }
    }
    if ($play) { "run $($play.run) ($($play.mission)); server pid $($play.serverPid)" }
    return
}

if ($Shot) {
    $runDir = if ($play) { $play.runDir } else { $session.runDir }
    $dir = New-Item -ItemType Directory -Force -Path (Join-Path $runDir 'play-shots')
    $stamp = Get-Date -Format 'HHmmss'
    foreach ($i in $targets) {
        $p = Join-Path $dir ("{0}-c{1}.png" -f $stamp, $i)
        Save-BZRClientCapture (Get-CRFlowClient $i).pid $p
        $p
    }
    return
}

if ($Lua) {
    foreach ($i in $targets) {
        $r = Invoke-CRFlow -Client $i -Lua $Lua -TimeoutSeconds $TimeoutSeconds -AllowError
        "--- c$i ok=$($r.Ok)"
        Out-Json $r.Value
    }
    return
}

if ($State) {
    $chunk = @'
local s = snap()
local flags = {}
for k, v in pairs((s.M and s.M.flags) or {}) do if v == true then flags[#flags + 1] = k end end
table.sort(flags)
return { role = s.role, player = s.player, locals = s.locals, teams = s.teams, trueFlags = flags,
         players = s.players, time = GetTime() }
'@
    foreach ($i in $targets) { "--- c$i"; Out-Json (Invoke-CRFlow -Client $i -Lua $chunk -TimeoutSeconds $TimeoutSeconds) }
    return
}

if ($Events) {
    foreach ($i in $targets) {
        $script:CRFlowLogPos[$i] = 0
        $script:CRFlowEvents[$i] = New-Object System.Collections.ArrayList
        $all = @(Get-CRFlowEvents $i $Kind | Where-Object { $_.k -ne 'snap' -or $Kind -eq 'snap' })
        "--- c$i ($($all.Count) events$(if ($Kind) { " of kind $Kind" }))"
        foreach ($e in ($all | Select-Object -Last $Last)) {
            $body = $e | Select-Object * -ExcludeProperty k, t, f, client
            "{0,8} {1,-5} {2}" -f $e.t, $e.k, (ConvertTo-Json $body -Compress -Depth 5)
        }
    }
    return
}

if ($Key) {
    $vk = Get-VirtualKey $Key
    foreach ($i in $targets) {
        if ($HoldMs -gt 0) {
            $h = Get-BZRClientWindow (Get-CRFlowClient $i).pid
            [void][BZRWin.Native]::PostMessage($h, 0x0100, [IntPtr]$vk, [IntPtr]1)
            $end = (Get-Date).AddMilliseconds($HoldMs)
            # Autorepeat while held, as a real keyboard does.
            while ((Get-Date) -lt $end) { Start-Sleep -Milliseconds 33; [void][BZRWin.Native]::PostMessage($h, 0x0100, [IntPtr]$vk, [IntPtr]0x40000001) }
            [void][BZRWin.Native]::PostMessage($h, 0x0101, [IntPtr]$vk, [IntPtr]([int]0xC0000001 -bor 0))
        } else {
            Send-CRFlowKey $i $vk
        }
        "c$i key $Key (vk 0x{0:X2}, hold {1}ms)" -f $vk, $HoldMs
    }
    return
}

if ($Click.Count -eq 2) {
    foreach ($i in $targets) { Send-BZRClientClick (Get-CRFlowClient $i).pid $Click[0] $Click[1]; "c$i click $($Click -join ',')" }
    return
}

Write-Host 'Nothing to do; see the header of this script for actions.'
