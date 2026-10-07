# Drives an already-launched BZRCoopSession through host/join/ready/launch.
#
# Run under Windows PowerShell 5.1 (BZRWindowInput.ps1 needs System.Drawing).
# Input is posted to each client's own window by pid, so it works unfocused and
# never moves the desktop cursor. Every step waits on observed state (client
# BZLogger lines or local server status), records a JSONL line and a capture of
# both clients, and fails with the last state of both clients on timeout.
#
# Coordinates are for the stock 2.2.301 shell at a 1280x720 client area.

param(
    [string]$BZRCoopRoot = 'C:\BZRCoop',
    [string]$GameName = 'BZRCoopTest',
    [int]$StepTimeoutSeconds = 45,
    [string]$GuestName = 'BZRCoop2',
    [string]$ServerLog = 'C:\BZRCoop\server\server.log',
    [string]$CapturesUrl = 'http://127.0.0.1:8080/captures',
    # Optional map pick on the host staging list: the row's y (x is fixed) and
    # the .bzn the lobby gameSettings must then name, e.g. 195 + misn02b.bzn.
    [int]$MapListY = 0,
    [string]$MapBzn = '',
    [switch]$SyncJoin,
    [switch]$Launch
)

$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\BZRWindowInput.ps1"

$session = Get-Content -LiteralPath (Join-Path $BZRCoopRoot 'session.json') -Raw | ConvertFrom-Json
$hostClient = $session.clients | Where-Object index -eq 0
$guestClient = $session.clients | Where-Object index -eq 1
$shots = New-Item -ItemType Directory -Force (Join-Path $session.runDir 'shots')
$stepLog = Join-Path $session.runDir 'steps.jsonl'
$clock = [Diagnostics.Stopwatch]::StartNew()

# Native shell layout, authored at a 1280x720 client area. Ogre clamps a
# windowed client to the desktop (a narrow Remote Desktop session gave 584x720),
# and the shell keeps each control's distance from its anchor edge, so x is
# converted per control: C = centre, R = right edge. Measured at 584 wide: the
# lounge and staging panels stay centred and are cropped at both sides; the
# corner buttons stay on the right. x is clamped into the client, which keeps
# the Sync Join label reachable at 584 (only its last pixels are on screen).
$UI = @{
    MainMultiPlayer = @(845, 163, 'C')
    LoungeCreate    = @(1138, 25, 'R')
    CreateNameField = @(725, 255, 'C')
    CreateOkay      = @(727, 358, 'C')
    LoungeFirstGame = @(560, 95, 'C')
    LoungeJoin      = @(1138, 697, 'R')
    StagingReady    = @(1138, 25, 'R')
    StagingLaunch   = @(1138, 25, 'R')
    SyncJoinToggle  = @(250, 359, 'C')
    MapList         = @(428, 0, 'C')
}
$LayoutWidth = 1280

function Get-LogPath($client) {
    Get-ChildItem -LiteralPath $client.dir, (Join-Path $client.dir 'logs') -Filter 'BZLogger.txt' -File -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty FullName
}

# Only lines written after this script started count as evidence for a step.
$logOffsets = @{}
foreach ($c in $hostClient, $guestClient) { $logOffsets[$c.index] = (Get-Item (Get-LogPath $c)).Length }

function Find-LogLine($client, [string]$Pattern) {
    $path = Get-LogPath $client
    $fs = [IO.File]::Open($path, 'Open', 'Read', 'ReadWrite')
    try {
        $null = $fs.Seek($logOffsets[$client.index], 'Begin')
        $text = (New-Object IO.StreamReader($fs)).ReadToEnd()
    } finally { $fs.Dispose() }
    $m = [regex]::Matches($text, $Pattern)
    if ($m.Count) { $m[$m.Count - 1] }
}

function Get-LastLine($client) { [string](Get-Content -LiteralPath (Get-LogPath $client) -Tail 1) }

function Write-Step([string]$Name, [string]$Status, $Extra = @{}) {
    $rec = [ordered]@{ t = (Get-Date).ToString('o'); ms = $clock.ElapsedMilliseconds; step = $Name; status = $Status }
    foreach ($k in $Extra.Keys) { $rec[$k] = $Extra[$k] }
    ($rec | ConvertTo-Json -Compress) | Add-Content -LiteralPath $stepLog
    foreach ($c in $hostClient, $guestClient) {
        try { Save-BZRClientCapture $c.pid (Join-Path $shots ("{0:D2}-{1}-c{2}.png" -f (Get-Content $stepLog).Count, $Name, $c.index)) } catch { }
    }
    Write-Host ("[lobby] {0,7:N1}s {1} {2}" -f ($clock.ElapsedMilliseconds / 1000), $Name, $Status)
}

function Wait-Until([string]$Name, [scriptblock]$Condition) {
    $deadline = (Get-Date).AddSeconds($StepTimeoutSeconds)
    while ((Get-Date) -lt $deadline) {
        # A crashed client never satisfies a step: fail now, not at the timeout.
        foreach ($c in $hostClient, $guestClient) {
            if (-not (Get-Process -Id $c.pid -ErrorAction SilentlyContinue)) {
                Write-Step $Name 'client-exited' @{ client = $c.index; last = (Get-LastLine $c) }
                throw "Step '$Name': client $($c.index) (pid $($c.pid)) exited; last log: $(Get-LastLine $c)"
            }
        }
        $r = & $Condition
        if ($r) { Write-Step $Name 'ok' @{ evidence = "$r" }; return ,$r }
        Start-Sleep -Milliseconds 400
    }
    Write-Step $Name 'timeout' @{ hostLast = (Get-LastLine $hostClient); guestLast = (Get-LastLine $guestClient) }
    throw "Step '$Name' timed out after ${StepTimeoutSeconds}s"
}

if (-not ('BZRWin.Rect' -as [type])) {
    Add-Type -TypeDefinition @'
using System; using System.Runtime.InteropServices;
namespace BZRWin { public static class Rect {
    [StructLayout(LayoutKind.Sequential)] struct R { public int L, T, Ri, B; }
    [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h, out R r);
    public static int Width(IntPtr h) { R r; GetClientRect(h, out r); return r.Ri - r.L; }
    public static int Height(IntPtr h) { R r; GetClientRect(h, out r); return r.B - r.T; }
} }
'@
}
$LayoutHeight = 720
$clientSize = @{}
function Get-ClientSize($client) {
    if (-not $clientSize.ContainsKey($client.index)) {
        $hwnd = Get-BZRClientWindow $client.pid
        $clientSize[$client.index] = @([BZRWin.Rect]::Width($hwnd), [BZRWin.Rect]::Height($hwnd))
    }
    $clientSize[$client.index]
}
# The shell scales uniformly with the client height (s = h/720) and keeps each
# control's distance from its anchor: C = centre, R = right edge, L = left.
# A 584x720 client (s = 1) only crops; a 624x393 one (narrow RDP/phone
# display) also shrinks everything to 0.55.
function Click($client, $xy) {
    $w, $h = Get-ClientSize $client
    $s = $h / $LayoutHeight
    $x = switch ($xy[2]) {
        'C' { ($xy[0] - $LayoutWidth / 2) * $s + $w / 2 }
        'R' { $w - ($LayoutWidth - $xy[0]) * $s }
        default { $xy[0] * $s }
    }
    $x = [Math]::Max(5, [Math]::Min($w - 5, [int]$x))
    Send-BZRClientClick $client.pid $x ([int]($xy[1] * $s))
}

# 1. Both clients into the multiplayer lounge.
Click $hostClient $UI.MainMultiPlayer
Click $guestClient $UI.MainMultiPlayer
$null = Wait-Until 'host-lounge' { Find-LogLine $hostClient 'fully entered lobby' }
$null = Wait-Until 'guest-lounge' { Find-LogLine $guestClient 'fully entered lobby' }

# 2. Host creates the game.
Click $hostClient $UI.LoungeCreate
Start-Sleep -Milliseconds 800
Click $hostClient $UI.CreateNameField
Start-Sleep -Milliseconds 200
Send-BZRClientText $hostClient.pid $GameName
Start-Sleep -Milliseconds 300
Click $hostClient $UI.CreateOkay
$created = Wait-Until 'host-created' { Find-LogLine $hostClient 'OnLobbyCreated, joined (B\d+)' }
$lobbyId = $created.Groups[1].Value
$null = Wait-Until 'host-lobby-populated' {
    if (Find-LogLine $hostClient "requesting missing data for lobby $lobbyId") { throw "host lobby $lobbyId populated without data (stuck 'Loading')" }
    Find-LogLine $hostClient "OnDataChanged, adjusting lobby $lobbyId"
}

# 3. Guest finds and joins it.
$null = Wait-Until 'guest-sees-game' { Find-LogLine $guestClient ("ID {0}, [^,]+, [^,]+, ~game~pub~~{1}" -f $lobbyId, [regex]::Escape($GameName)) }
Click $guestClient $UI.LoungeFirstGame
Start-Sleep -Milliseconds 400
Click $guestClient $UI.LoungeJoin
$assigned = Wait-Until 'host-assigned-guest' { Find-LogLine $hostClient ('Assigned Player ({0}) team (\d+), player id (\d+)' -f [regex]::Escape($GuestName)) }
$null = Wait-Until 'p2p-connected' { Find-LogLine $guestClient 'BZRNet P2P Completed (RELAY|DIRECT|LAN|WAN)\S* Connect For Client' }

# Server-log evidence: only frames after the given offset count.
function Get-ServerOffset { (Get-Item -LiteralPath $ServerLog).Length }
function Find-ServerLine([long]$Offset, [string]$Pattern) {
    $fs = [IO.File]::Open($ServerLog, 'Open', 'Read', 'ReadWrite')
    try { $null = $fs.Seek($Offset, 'Begin'); $t = (New-Object IO.StreamReader($fs)).ReadToEnd() } finally { $fs.Dispose() }
    $m = [regex]::Matches($t, $Pattern)
    if ($m.Count) { $m[$m.Count - 1].Value }
}
$readyPattern = '< TEXT .\{"content":\{"key":"ready"[^\r\n]*'

# 4. Optional Sync Join before anyone readies: a settings change bumps the
# gameSettings version and invalidates earlier ready values. The toggle only
# takes clicks on its label, not the value cell.
# The debug log truncates frame text; the server's /captures previews keep the
# whole gameSettings value: "<version>*<map>.bzn*<crc>*<mod>*<syncJoin>*...".
function Get-GameSettings {
    $caps = try { (Invoke-RestMethod -Uri $CapturesUrl -TimeoutSec 3).protocol.history } catch { @() }
    $last = @($caps | Where-Object { $_.type -eq 'SetLobbyData' -and $_.preview -match '"key":"gameSettings"' }) | Select-Object -Last 1
    if ($last -and $last.preview -match '"value":"([^"]*)"') { ,($Matches[1] -split '\*') }
}
function Wait-NewSettings([string]$Version) {
    $deadline = (Get-Date).AddSeconds(4)
    while ((Get-Date) -lt $deadline) {
        $s = Get-GameSettings
        if ($s -and $s[0] -ne $Version) { return ,$s }
        Start-Sleep -Milliseconds 250
    }
}

Start-Sleep -Seconds 2
if ($MapListY) {
    # Row height follows the client size (12 px at 1280 wide, ~8.5 px at 584),
    # so try the 1280 row first, then walk the list until the map is selected.
    $tries = @($MapListY) + @(for ($y = 88; $y -le 230; $y += 8) { $y })
    foreach ($y in $tries) {
        $before = Get-GameSettings
        Click $hostClient @($UI.MapList[0], $y, $UI.MapList[2])
        $s = Wait-NewSettings $(if ($before) { $before[0] } else { '' })
        if ($s -and $s[1] -eq $MapBzn) { break }
    }
    $null = Wait-Until 'host-map' { $s = Get-GameSettings; if ($s -and $s[1] -eq $MapBzn) { "$MapBzn (row y=$y)" } }
    Start-Sleep -Milliseconds 500
}
if ($SyncJoin) {
    # The setting can persist from an earlier session; only toggle it on.
    $s = Get-GameSettings
    if (-not $s -or $s[4] -ne '1') { Click $hostClient $UI.SyncJoinToggle }
    $null = Wait-Until 'host-sync-join' { $s = Get-GameSettings; if ($s -and $s[4] -eq '1') { $s -join '*' } }
    Start-Sleep -Milliseconds 500
}

# 5. Guest ready.
$off = Get-ServerOffset
Click $guestClient $UI.StagingReady
$null = Wait-Until 'guest-ready-sent' { Find-ServerLine $off $readyPattern }
Write-Step 'lobby-ready' 'ok' @{ lobby = $lobbyId; guest = $assigned.Groups[1].Value; guestTeam = $assigned.Groups[2].Value }

if (-not $Launch) { return }
# 6. Host Launch (non-sync) / Ready (sync) also goes out as the host's ready value.
$off = Get-ServerOffset
Click $hostClient $UI.StagingLaunch
$null = Wait-Until 'host-ready-sent' { Find-ServerLine $off $readyPattern }
# Both peers leave the shell for the mission; the exact load lines are recorded as evidence.
$null = Wait-Until 'host-left-shell' { Find-LogLine $hostClient '(SetRunning: was \w+, now RUN_\w+|Loading (map|mission|world)[^\r\n]*)' }
$null = Wait-Until 'guest-left-shell' { Find-LogLine $guestClient '(SetRunning: was \w+, now RUN_\w+|Loading (map|mission|world)[^\r\n]*)' }
