# Live test: community matchmaking server (bzr.battlezonecommunity.com:1337) vs an OpenShim build.
# Windows PowerShell 5.1.  Arms:
#   custom - pre-lobby Custom entry; [Network] Server=Custom is pre-set so a saved
#            Server=Rebellion cannot send the first connection to Rebellion.
#   switch - /bzrserver= launch switch with a saved [Network] Server (default
#            Rebellion): the switch must win, and Continue must not save Server=Custom.
# ReleaseDir holds files laid out as in the game folder (plugins\openshim.dll, ...).
# Refuses to run unless the platform is signed in (Steam ActiveUser; GOG Galaxy running,
# started here if needed).
param(
    [Parameter(Mandatory)][ValidateSet('custom', 'switch')][string]$Arm,
    [Parameter(Mandatory)][ValidateSet('GOG', 'Steam')][string]$Install,
    [Parameter(Mandatory)][string]$ReleaseDir,
    [Parameter(Mandatory)][string]$OutDir,
    [string]$ExpectVersion = '',
    [ValidateSet('Rebellion', 'Local', 'None')][string]$SavedServer = 'Rebellion',
    [string]$Tag = '',
    [int]$CapSeconds = 240
)
$ErrorActionPreference = 'Stop'
$GameRoot = if ($Install -eq 'GOG') { 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux' } else { 'C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux' }
$Repo = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
if (-not $Tag) { $Tag = "$Install-$Arm" }
New-Item -ItemType Directory -Force $OutDir | Out-Null
$report = Join-Path $OutDir "$Tag.txt"
function Note([string]$t) { try { $l = "[{0:HH:mm:ss}] $t" -f (Get-Date); Write-Host $l; Add-Content -LiteralPath $report -Value $l } catch { } }

# Sets key=value in [section], adding the key (or the section) when absent.
function Set-IniKey([string]$Text, [string]$Section, [string]$Key, [string]$Value) {
    $nl = if ($Text -match "`r`n") { "`r`n" } else { "`n" }
    $sec = [regex]::Match($Text, "(?ms)^\[$([regex]::Escape($Section))\][^\r\n]*\r?\n(.*?)(?=^\[|\z)")
    if (-not $sec.Success) { return $Text.TrimEnd() + "$nl$nl[$Section]$nl$Key = $Value$nl" }
    $body = $sec.Groups[1]
    $keyRx = "(?mi)^(\s*$([regex]::Escape($Key))\s*=).*$"
    if ([regex]::IsMatch($body.Value, $keyRx)) {
        $newBody = [regex]::Replace($body.Value, $keyRx, { param($m) $m.Groups[1].Value + ' ' + $Value })
    } else {
        $newBody = "$Key = $Value$nl" + $body.Value
    }
    return $Text.Substring(0, $body.Index) + $newBody + $Text.Substring($body.Index + $body.Length)
}

# 0. Platform sign-in preflight (fixture failure, not a product result).
if ($Install -eq 'Steam') {
    $active = (Get-ItemProperty 'HKCU:\Software\Valve\Steam\ActiveProcess' -ErrorAction SilentlyContinue).ActiveUser
    if (-not $active) { Note 'fixture: Steam is not signed in (ActiveProcess\ActiveUser = 0); not running'; exit 3 }
    Note "Steam signed in (ActiveUser $active)"
} else {
    if (-not (Get-Process -Name GalaxyClient -ErrorAction SilentlyContinue)) {
        $galaxy = 'C:\Program Files (x86)\GOG Galaxy\GalaxyClient.exe'
        if (-not (Test-Path -LiteralPath $galaxy)) { Note 'fixture: GOG Galaxy not installed; not running'; exit 3 }
        $gp = Start-Process -FilePath $galaxy -PassThru
        Note "started GOG Galaxy pid $($gp.Id); waiting 45 s for sign-in"
        [Threading.Thread]::Sleep(45000)
    }
    if (-not (Get-Process -Name GalaxyClient -ErrorAction SilentlyContinue)) { Note 'fixture: GOG Galaxy is not running; not running'; exit 3 }
    Note 'GOG Galaxy running'
}

$env:BZR_FORCE_WINDOWED = '1'
$env:OPENSHIM_NEVER_ACTIVATE = '1'
$env:OPENSHIM_NEVER_CAPTURE_MOUSE = '1'
$env:OPENSHIM_DISABLE_RAW_MOUSE_INPUT = '1'
if ($Install -eq 'Steam') { $env:SteamAppId = '301650'; $env:SteamGameId = '301650'; $env:SteamOverlayGameId = '301650' }

Add-Type -TypeDefinition @'
using System; using System.Runtime.InteropServices;
public static class CsClient {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int l, t, r, b; }
    [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h, out RECT r);
    public static int[] Size(IntPtr h) { RECT r; GetClientRect(h, out r); return new int[] { r.r - r.l, r.b - r.t }; }
}
'@
$hostName = 'bzr.battlezonecommunity.com'
$switchArg = '/bzrserver=ws://bzr.battlezonecommunity.com:1337/'
$lockPath = Join-Path $GameRoot 'bzr_livetest.lock'
$lockMine = $false
$gamePid = 0
$ogrePath = Join-Path $GameRoot 'ogre.cfg'
$ogreOrigCopy = Join-Path $OutDir "ogre-original-$Tag.cfg"
$ogreOrigHash = $null
$files = @()
$created = @()
$bak = Join-Path $OutDir "backup-$Tag"
$snapBefore = @{}

# 1. Lock (wait, then take) before touching anything.
& "$Repo\reverse_engineering\Wait-BZRLiveTestLock.ps1" -GameRoot $GameRoot -TimeoutSeconds 2400 -PollSeconds 15
if ($LASTEXITCODE -ne 0) { Note 'lock wait timed out'; exit 2 }
Set-Content -LiteralPath $lockPath -Value "community-server live test pid=$PID arm=$Tag $(Get-Date -Format o)"
$lockMine = $true
Note "lock taken $lockPath"

try {
    # 2. Backups.
    Copy-Item -LiteralPath $ogrePath -Destination $ogreOrigCopy -Force
    $ogreOrigHash = (Get-FileHash -LiteralPath $ogreOrigCopy).Hash
    $ogreBakH = Join-Path $GameRoot 'ogre.cfg.bzrharness-backup'
    if (Test-Path -LiteralPath $ogreBakH) { throw 'ogre.cfg.bzrharness-backup exists (orphan from another run); not touching' }
    New-Item -ItemType Directory -Force $bak | Out-Null

    $iniRel = if (Test-Path -LiteralPath "$GameRoot\openshim\openshim.ini") { 'openshim\openshim.ini' } else { 'openshim.ini' }
    # Release files -> live paths (relative layout of the release zip).
    $deploy = @()
    foreach ($rf in Get-ChildItem -LiteralPath $ReleaseDir -Recurse -File) {
        $rel = $rf.FullName.Substring($ReleaseDir.TrimEnd('\').Length + 1)
        $deploy += @{ rel = $rel; src = $rf.FullName }
    }
    $trackRels = @($deploy | ForEach-Object { $_.rel }) + @($iniRel, 'openshim\openshim.ini', 'openshim.ini', 'career_stats.cfg', 'flags.cfg') | Select-Object -Unique
    foreach ($rel in $trackRels) {
        $live = Join-Path $GameRoot $rel
        $f = @{ rel = $rel; live = $live; existed = (Test-Path -LiteralPath $live) }
        if ($f.existed) {
            $f.hash = (Get-FileHash -LiteralPath $live).Hash
            $f.bak = Join-Path $bak ($rel -replace '[\\/]', '__')
            Copy-Item -LiteralPath $live -Destination $f.bak -Force
        }
        $files += $f
        Note ("backup {0} existed={1} {2}" -f $rel, $f.existed, $f.hash)
    }
    # Snapshot top-level + openshim\ (non-log) so new files can be removed afterwards.
    function Get-Snap { $h = @{}; foreach ($p in @(Get-ChildItem -LiteralPath $GameRoot -File -Force) + @(Get-ChildItem -LiteralPath "$GameRoot\openshim" -File -Recurse -Force -ErrorAction SilentlyContinue) + @(Get-ChildItem -LiteralPath "$GameRoot\scripts", "$GameRoot\plugins" -File -Force -ErrorAction SilentlyContinue)) { $h[$p.FullName] = (Get-FileHash -LiteralPath $p.FullName).Hash }; $h }
    $snapBefore = Get-Snap

    # 3. Deploy.
    foreach ($d in $deploy) {
        $live = Join-Path $GameRoot $d.rel
        New-Item -ItemType Directory -Force (Split-Path $live) | Out-Null
        Copy-Item -LiteralPath $d.src -Destination $live -Force
    }
    $dllHash = (Get-FileHash -LiteralPath "$GameRoot\plugins\openshim.dll").Hash
    $relHash = (Get-FileHash -LiteralPath (Join-Path $ReleaseDir 'plugins\openshim.dll')).Hash
    $ver = (Get-Item "$GameRoot\plugins\openshim.dll").VersionInfo.FileVersion
    Note ("deployed {0} files; dll {1} ver {2} matchesRelease={3}" -f $deploy.Count, $dllHash, $ver, ($dllHash -eq $relHash))
    if ($dllHash -ne $relHash) { throw 'fixture: deployed dll does not match ReleaseDir' }
    if ($ExpectVersion -and $ver -ne $ExpectVersion) { throw "fixture: deployed dll is $ver, expected $ExpectVersion" }

    # ini: shell-driving settings only (RawMouseInput=0, RunInBackground=0).
    $ini = Join-Path $GameRoot $iniRel
    $t = [IO.File]::ReadAllText($ini)
    $t = [regex]::Replace($t, '(?m)^(\s*RawMouseInput\s*=\s*)\S+', '${1}0')
    $t = [regex]::Replace($t, '(?m)^(\s*RunInBackground\s*=\s*)\S+', '${1}0')
    if ($Arm -eq 'custom') {
        $t = Set-IniKey $t 'Network' 'Server' 'Custom'
        $t = Set-IniKey $t 'Network' 'CustomServer' $hostName
    } elseif ($SavedServer -ne 'None') {
        $t = Set-IniKey $t 'Network' 'Server' $SavedServer
    }
    [IO.File]::WriteAllText($ini, $t)
    $net = Select-String -LiteralPath $ini -Pattern '^\s*(Server|CustomServer|PreLobby)\s*=' | ForEach-Object { $_.Line.Trim() }
    Note ("ini {0} network keys before launch: {1}" -f $iniRel, ($net -join ' | '))

    # 4. Ogre.cfg: windowed D3D11 1600x900 everywhere.
    $cfg = [IO.File]::ReadAllText($ogreOrigCopy)
    $d3d11 = @"
[Direct3D11 Rendering Subsystem]
Allow NVPerfHUD=No
Backbuffer Count=Auto
Driver type=Hardware
FSAA=1
Floating-point mode=Consistent
Full Screen=No
Information Queue Exceptions Bottom Level=No information queue exceptions
Max Requested Feature Levels=11.0
Min Requested Feature Levels=9.1
Rendering Device=(default)
VSync=Yes
VSync Interval=1
Video Mode=1600 x  900 @ 32-bit colour
sRGB Gamma Conversion=No
"@ -replace "`r?`n", "`r`n"
    $cfg = [regex]::Replace($cfg, '(?ms)^\[Direct3D11 Rendering Subsystem\].*?(?=^\[|\z)', $d3d11.TrimEnd() + "`r`n`r`n")
    $cfg = [regex]::Replace($cfg, '(?m)^Render System=.*$', 'Render System=Direct3D11 Rendering Subsystem')
    $cfg = [regex]::Replace($cfg, '(?m)^Full Screen=Yes', 'Full Screen=No')
    [IO.File]::WriteAllText($ogrePath, $cfg)

    . "$Repo\reverse_engineering\BZRHarness.ps1"
    . "$Repo\reverse_engineering\BZRWindowInput.ps1"
    # Harness rewrote Video Mode lines in every section; make sure D3D11 is our valid mode and nothing is fullscreen.
    $check = [IO.File]::ReadAllText($ogrePath)
    if ($check -match '(?m)^Full Screen=Yes' -or $check -notmatch '(?ms)\[Direct3D11 Rendering Subsystem\][^\[]*Full Screen=No[^\[]*Video Mode=1600 x  900 @ 32-bit colour') { throw 'fixture: Ogre.cfg not windowed; not launching' }
    Note 'Ogre.cfg: D3D11 windowed 1600x900, no Full Screen=Yes'

    $env:OPENSHIM_FRAME_CAPTURE = ((1..120 | ForEach-Object { $_ * 240 }) -join ',')
    $logDir = Join-Path $GameRoot 'logs'
    Get-ChildItem $logDir -Filter 'openshim_frame_*.png' -ErrorAction SilentlyContinue | Remove-Item -Force
    Get-ChildItem $GameRoot -Filter 'openshim_frame_*.png' -ErrorAction SilentlyContinue | Remove-Item -Force

    $shimLog = Join-Path $logDir 'openshim.log'
    $bzLog = Join-Path $logDir 'BZLogger.txt'
    $script:off = @{}
    foreach ($l in @($shimLog, $bzLog, (Join-Path $GameRoot 'BZLogger.txt'))) { $script:off[$l] = if (Test-Path -LiteralPath $l) { (Get-Item -LiteralPath $l).Length } else { 0 } }
    function Read-New([string]$p) {
        if (-not (Test-Path -LiteralPath $p)) { return '' }
        $fs = [IO.File]::Open($p, 'Open', 'Read', 'ReadWrite')
        try {
            $o = $script:off[$p]; if ($fs.Length -lt $o) { $o = 0 }
            $null = $fs.Seek($o, 'Begin')
            return (New-Object IO.StreamReader($fs)).ReadToEnd()
        } finally { $fs.Dispose() }
    }
    function All-New { (Read-New $shimLog) + "`n" + (Read-New $bzLog) + "`n" + (Read-New (Join-Path $GameRoot 'BZLogger.txt')) }
    function Wait-Log([string]$Pattern, [int]$Seconds) {
        $deadline = (Get-Date).AddSeconds($Seconds)
        while ((Get-Date) -lt $deadline) {
            if (-not (Get-Process -Id $script:gamePid -ErrorAction SilentlyContinue)) { throw "game pid $script:gamePid exited" }
            if ((Get-Date) -gt $script:hardStop) { throw "arm cap of $CapSeconds s reached" }
            $m = [regex]::Match((All-New), $Pattern)
            if ($m.Success) { return $m.Value }
            [Threading.Thread]::Sleep(500)
        }
        return $null
    }
    # Pre-lobby: 1440x1080 design space scaled by h/1080 and centred.
    $script:cw = 1600; $script:ch = 900
    function Design([double]$x, [double]$y) { $s = $script:ch / 1080.0; $ox = ($script:cw - 1440.0 * $s) / 2; Send-BZRClientClick $script:gamePid ([int]($ox + $x * $s)) ([int]($y * $s)) }
    # Stock shell: 1280x720 layout, s = h/720, anchors C/R/L.
    function Shell([double]$x, [double]$y, [string]$a) {
        $s = $script:ch / 720.0
        $px = switch ($a) { 'C' { ($x - 640) * $s + $script:cw / 2 } 'R' { $script:cw - (1280 - $x) * $s } default { $x * $s } }
        $px = [Math]::Max(5, [Math]::Min($script:cw - 5, [int]$px))
        Send-BZRClientClick $script:gamePid $px ([int]($y * $s))
    }
    function Measure-Client {
        $h = Get-BZRClientWindow $script:gamePid
        $sz = [CsClient]::Size($h); $script:cw = $sz[0]; $script:ch = $sz[1]
    }

    # 5. Launch (lock re-check immediately before).
    if (-not (Test-Path -LiteralPath $lockPath) -or -not ((Get-Content -LiteralPath $lockPath -Raw) -match "pid=$PID")) { throw 'lock lost' }
    if ((Get-FileHash -LiteralPath "$GameRoot\plugins\openshim.dll").Hash -ne $relHash) { throw 'fixture: dll changed before launch' }
    Assert-BZRSafeToLaunch
    $launchArgs = @('/nointro')
    if ($Arm -eq 'switch') { $launchArgs += $switchArg }
    $proc = Start-BZRGameProcess -FilePath "$GameRoot\battlezone98redux.exe" -ArgumentList $launchArgs -WorkingDirectory $GameRoot -PassThru
    $gamePid = $proc.Id; $script:gamePid = $gamePid
    $script:hardStop = (Get-Date).AddSeconds($CapSeconds)
    Note "launched pid $gamePid args: $($launchArgs -join ' ')"

    $hook = Wait-Log 'Click_MultiPlayer hook installed[^\r\n]*' 90
    if (-not $hook) { throw 'fixture: no Click_MultiPlayer hook line' }
    $verLine = [regex]::Match((Read-New $shimLog), '[^\r\n]*(1\.0\.0\.\d+)[^\r\n]*').Value
    Note "shim version line: $verLine"
    $opened = $null
    for ($i = 0; $i -lt 30 -and -not $opened; $i++) {
        try { Measure-Client; Design 1062 243 } catch { }
        $opened = Wait-Log '\[SHELLUI\] creating screen [^\r\n]*' 5
    }
    if (-not $opened) { throw "fixture: pre-lobby never opened (client $($script:cw)x$($script:ch))" }
    Note "opened: $opened ; client $($script:cw)x$($script:ch)"
    [Threading.Thread]::Sleep(3000)

    if ($Arm -eq 'custom') {
        $edit = $null
        for ($i = 0; $i -lt 3 -and -not $edit; $i++) {
            Design 1089 321; [Threading.Thread]::Sleep(1500)
            Design 1089 321; [Threading.Thread]::Sleep(1500)
            Design 1004 425; [Threading.Thread]::Sleep(1000)
            Design 1004 425
            $edit = Wait-Log 'Nickname edit active \(source=prelobby_server_click[^\r\n]*' 4
        }
        if (-not $edit) { throw 'fixture: server entry click not seen (Custom slot / host well)' }
        Note "edit: $edit"
        Send-BZRClientText $gamePid ([string][char]8 * 60)
        [Threading.Thread]::Sleep(300)
        Send-BZRClientText $gamePid $hostName
        [Threading.Thread]::Sleep(1500)
    } else {
        [Threading.Thread]::Sleep(1500)
    }
    $preFrames = @(Get-ChildItem $logDir, $GameRoot -Filter 'openshim_frame_*.png' -ErrorAction SilentlyContinue | Sort-Object LastWriteTime)
    if ($preFrames) { Copy-Item -LiteralPath ($preFrames[-1].FullName) -Destination (Join-Path $OutDir "$Tag-prelobby.png") -Force; Note "prelobby frame $($preFrames[-1].Name)" }

    Design 720 934
    Note 'clicked Continue'
    $applied = Wait-Log '\[PRELOBBY\] (server selection applied|continue)[^\r\n]*' 10
    Note "prelobby: $applied"
    $lobby = Wait-Log 'fully entered lobby[^\r\n]*' 45
    if (-not $lobby) {
        # one retry of Continue
        Design 720 934
        $lobby = Wait-Log 'fully entered lobby[^\r\n]*' 30
    }
    Note "lobby: $lobby"
    [Threading.Thread]::Sleep(6000)
    $lobbyFrames = @(Get-ChildItem $logDir, $GameRoot -Filter 'openshim_frame_*.png' -ErrorAction SilentlyContinue | Sort-Object LastWriteTime)
    if ($lobbyFrames) { Copy-Item -LiteralPath ($lobbyFrames[-1].FullName) -Destination (Join-Path $OutDir "$Tag-lobby.png") -Force; Note "lobby frame $($lobbyFrames[-1].Name)" }

    if ($lobby) {
        $gameName = "OSRC81_$Install"
        Shell 1138 25 'R'; [Threading.Thread]::Sleep(800)
        Shell 1138 25 'R'; [Threading.Thread]::Sleep(600)
        Shell 725 255 'C'; [Threading.Thread]::Sleep(300)
        Send-BZRClientText $gamePid $gameName
        [Threading.Thread]::Sleep(400)
        Shell 727 358 'C'
        $made = Wait-Log 'OnLobbyCreated[^\r\n]*' 20
        Note "create: $made"
        if ($made) {
            $pop = Wait-Log 'OnDataChanged, adjusting lobby[^\r\n]*' 15
            Note "populated: $pop"
            [Threading.Thread]::Sleep(6000)
            $sf = @(Get-ChildItem $logDir, $GameRoot -Filter 'openshim_frame_*.png' -ErrorAction SilentlyContinue | Sort-Object LastWriteTime)
            if ($sf) { Copy-Item -LiteralPath ($sf[-1].FullName) -Destination (Join-Path $OutDir "$Tag-staging.png") -Force; Note "staging frame $($sf[-1].Name)" }
            # Leave: staging Back (top-left).
            $before = (All-New).Length
            Shell 130 25 'L'
            [Threading.Thread]::Sleep(5000)
            $tail = (All-New).Substring($before)
            Note ("after leave click:`n" + (($tail -split "`r?`n" | Where-Object { $_ -match '(?i)lobby|leave|screen|left' } | Select-Object -First 15) -join "`n"))
        }
    }
} catch {
    Note "ERROR: $_"
} finally {
    try {
        $all = All-New
        $keep = $all -split "`r?`n" | Where-Object { $_ -match '(?i)OpenShimNet\] (Saved server|Redirecting|Custom server|sid=\d+ ticket|ticket_withheld|lookup )|BZRNET\]|PRELOBBY|LAN-NOAUTH|fully entered lobby|OnLobby|websocket|ws://|wss://|bzrserver|battlezonecommunity|rebellion|matchmak|ID B\d+|lobby list|Lobby|Disconnect|refused|timed out|error' } | Select-Object -First 300
        Set-Content -LiteralPath (Join-Path $OutDir "$Tag-keylines.txt") -Value $keep
        Set-Content -LiteralPath (Join-Path $OutDir "$Tag-alllog.txt") -Value $all
    } catch { Note "log save error: $_" }
    try {
        if ($gamePid) {
            Stop-BZRGame -Id $gamePid -TimeoutSeconds 25 -ErrorAction SilentlyContinue
            if (Get-Process -Id $gamePid -ErrorAction SilentlyContinue) { Stop-BZRGame -Id $gamePid -Force -ErrorAction SilentlyContinue }
            for ($w = 0; $w -lt 60 -and (Get-Process -Id $gamePid -ErrorAction SilentlyContinue); $w++) { [Threading.Thread]::Sleep(500) }
            Note ("pid $gamePid alive after stop: {0}" -f [bool](Get-Process -Id $gamePid -ErrorAction SilentlyContinue))
        }
    } catch { Note "stop error: $_" }
    try {
        $pngs = @(Get-ChildItem "$GameRoot\logs", $GameRoot -Filter 'openshim_frame_*.png' -ErrorAction SilentlyContinue | Sort-Object LastWriteTime)
        if ($pngs.Count) {
            $kd = Join-Path $OutDir "frames-$Tag"; New-Item -ItemType Directory -Force $kd | Out-Null
            $pngs | Select-Object -Last 6 | ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $kd -Force }
            Note "kept last 6 of $($pngs.Count) frames in $kd"
        }
        $pngs | Remove-Item -Force -ErrorAction SilentlyContinue
    } catch { }
    try {
        $iniNow = @($files | Where-Object { $_.rel -match 'openshim\.ini$' -and (Test-Path -LiteralPath $_.live) } | ForEach-Object { Select-String -LiteralPath $_.live -Pattern '^\s*(Server|CustomServer)\s*=' | ForEach-Object { "$($_.Path.Substring($GameRoot.Length)): $($_.Line.Trim())" } })
        Note ("ini network keys after run (before restore): " + ($iniNow -join ' | '))
        if ($Arm -eq 'switch') {
            $persisted = @($iniNow | Where-Object { $_ -match 'Server\s*=\s*Custom' -or $_ -match 'CustomServer\s*=.*battlezonecommunity' })
            Note ("switch persistence: {0}" -f $(if ($persisted.Count) { 'FAIL (launch host saved: ' + ($persisted -join ' | ') + ')' } else { 'PASS (launch host not saved)' }))
        }
    } catch { }
    foreach ($f in $files) {
        try {
            if ($f.existed) {
                Copy-Item -LiteralPath $f.bak -Destination $f.live -Force
                Note ("restore {0} match={1}" -f $f.rel, ((Get-FileHash -LiteralPath $f.live).Hash -eq $f.hash))
            } elseif (Test-Path -LiteralPath $f.live) {
                Remove-Item -LiteralPath $f.live -Force
                Note ("removed new {0}" -f $f.rel)
            }
        } catch { Note "restore error $($f.rel): $_" }
    }
    try {
        $after = Get-Snap
        foreach ($k in $after.Keys) { if ($k -match 'bzr_livetest.lock|bzrharness-backup|ogre.cfg$') { continue }; if (-not $snapBefore.ContainsKey($k)) { Note "SNAPDIFF new: $k" } elseif ($snapBefore[$k] -ne $after[$k]) { Note "SNAPDIFF changed: $k" } }
        foreach ($k in $snapBefore.Keys) { if (-not $after.ContainsKey($k)) { Note "SNAPDIFF missing: $k" } }
    } catch { }
    try {
        if ($ogreOrigHash) {
            Copy-Item -LiteralPath $ogreOrigCopy -Destination $ogrePath -Force
            $hb = Join-Path $GameRoot 'ogre.cfg.bzrharness-backup'
            if (Test-Path -LiteralPath $hb) { Remove-Item -LiteralPath $hb -Force }
            Note ("Ogre.cfg restored match={0}" -f ((Get-FileHash -LiteralPath $ogrePath).Hash -eq $ogreOrigHash))
        }
    } catch { Note "ogre restore error: $_" }
    try { if ($lockMine) { Remove-Item -LiteralPath $lockPath -Force; Note 'lock released' } } catch { Note "lock release error: $_" }
    try { Exit-BZRLaunchLock $global:BZRAutoLock } catch { }
}
