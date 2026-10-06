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

# Native shell layout (1280x720).
$UI = @{
    MainMultiPlayer = @(860, 163)
    LoungeCreate    = @(1138, 25)
    CreateNameField = @(725, 255)
    CreateOkay      = @(727, 358)
    LoungeFirstGame = @(560, 95)
    LoungeJoin      = @(1138, 697)
    StagingReady    = @(1138, 25)
    StagingLaunch   = @(1138, 25)
    SyncJoinToggle  = @(250, 359)
}

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

function Get-LastLine($client) { (Get-Content -LiteralPath (Get-LogPath $client) -Tail 1) }

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
        $r = & $Condition
        if ($r) { Write-Step $Name 'ok' @{ evidence = "$r" }; return ,$r }
        Start-Sleep -Milliseconds 400
    }
    Write-Step $Name 'timeout' @{ hostLast = (Get-LastLine $hostClient); guestLast = (Get-LastLine $guestClient) }
    throw "Step '$Name' timed out after ${StepTimeoutSeconds}s"
}

function Click($client, $xy) { Send-BZRClientClick $client.pid $xy[0] $xy[1] }

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
Start-Sleep -Seconds 2
if ($MapListY) {
    $off = Get-ServerOffset
    Click $hostClient @(330, $MapListY)
    # The debug log truncates frame text; the server's /captures previews keep
    # the whole gameSettings value ("N*<map>.bzn*...").
    $null = Wait-Until 'host-map' {
        $caps = try { (Invoke-RestMethod -Uri $CapturesUrl -TimeoutSec 3).protocol.history } catch { @() }
        $last = @($caps | Where-Object { $_.type -eq 'SetLobbyData' -and $_.preview -match '"key":"gameSettings"' }) | Select-Object -Last 1
        if ($last -and $last.preview -match ('"value":"\d+\*' + [regex]::Escape($MapBzn) + '\*')) { $last.preview }
    }
    Start-Sleep -Milliseconds 500
}
if ($SyncJoin) {
    $off = Get-ServerOffset
    Click $hostClient $UI.SyncJoinToggle
    $null = Wait-Until 'host-sync-join' { Find-ServerLine $off '< TEXT .\{"content":\{"key":"gameSettings"[^\r\n]*' }
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
