<#
.SYNOPSIS
    Two-PC Battlezone 98 Redux multiplayer live test: PC 1 hosts, PC 2 joins, one verdict line.
.DESCRIPTION
    Reusable form of the ad-hoc host93f/host93s/host93x drivers. Windows PowerShell 5.1 compatible.

    PC 1 (this machine) hosts on its Steam copy through the official lobby. PC 2 (stuartserver) is
    driven ONLY through C:\Users\iestu\bin\bzr-friend-test\bzr-friend-test.ps1 (-Setup, -Do,
    -DeploySuite, -Restore, -Remove, -Status). This script never uses Invoke-Command or
    New-PSSession itself.

    Flow: take bzr_livetest.lock, Assert-BZRSafeToLaunch, back up and optionally deploy PC 1 files,
    deploy the SAME OpenShim suite to PC 2, launch PC 1, create the lobby, bring PC 2 into the
    lounge, join it with steam://rungame, click Ready on PC 2, Launch on PC 1, judge the logs.

    Verdict (last line of <OutDir>\verdict.txt and of the console):
      PASS     both logs show 'Sync Start Complete' and 'Game Simulation Initialized ... Playing',
               and neither shows 'Start Sync Failure' or 'Exiting Game' during the play window.
      FAIL     the fixture was sound and the product misbehaved (sync failure, left the game,
               sync never completed after Launch, -DoneRegex marker missing).
      FIXTURE  a precondition failed (lock, running game, hash or map mismatch, PC 2 not in the
               lounge, guest never joined, game died before Launch). Not a product result.

    Facts baked in (learned in the PR #936/#937 live tests):
      * PC 2 must run the SAME full suite as PC 1 (winmm.dll, bzloader.dll, plugins\openshim.dll,
        scripts\patches.json, openshim\ tree). A mismatch gave 'Network Start Sync Failure' with
        'Sync In At : 0'. The script deploys it with -DeploySuite and compares hashes.
      * Join is Start-Process 'steam://rungame/301650/<hostSteamID>/-connect-galaxy-lobby=B<id>' run
        on PC 2 via -Do, then a Ready click (1138,25,R) through drv_pc2.ps1.
      * The updater swaps PC 1's openshim.dll on exit, so every file is hash-restored in finally.
      * Never stops or starts Steam on PC 2. No WMI/CIM or blocking commands inside -Do. PC 2 logs
        are read back through -Do output BEFORE -Remove/-Restore.
      * Only PIDs this script started are stopped (Stop-BZRGame -Id on PC 1, Stop-Process -Id on PC 2).

    The host Steam ID is read from <Steam>\config\loginusers.vdf (the MostRecent account) unless
    -HostSteamId is given. The guest is identified by in-game name (-GuestName).
.PARAMETER Arm
    Full     (default) OpenShim on both PCs.
    Control  Full, with the PR #936/#937 fixes disabled on PC 1 by environment variable.
    Stock    PC 1 winmm.dll renamed away, so OpenShim never loads. PC 2 keeps whatever it has
             installed (no suite deploy); check the logged PC 2 hashes before trusting the arm.
.PARAMETER Pc1Build
    Optional OpenShim checkout (bin\Release\plugins\openshim.dll + scripts\patches.json) copied into
    PC 1's Steam copy for the run. Restored afterwards.
.PARAMETER Pc2Suite
    Game folder copied to PC 2 with -DeploySuite. Default: PC 1's Steam root (after -Pc1Build).
.PARAMETER ContentDir
    Optional folder (probe addon or CR co-op fix addon) deployed to BOTH PCs as <game>\addon\<leaf>,
    backing up anything already there and restoring it after. PC 2 uses bzr-friend-test.ps1
    -DeployAddon; its -Restore/-Remove undo it.
.PARAMETER Map
    Map file written to PC 1's multi.ini ('map = <Map>'). Default: leave multi.ini untouched.
    When given, the 'Launching Network Game' log line must name the same map or the run is FIXTURE.
.PARAMETER DoneRegex
    Optional host-log pattern that marks the end of a content mission (for example a probe's DONE
    line). When set, the play window lasts until it matches or -MissionSeconds passes.
.PARAMETER Attempts
    1 or 2. A second attempt runs only after a FIXTURE result. Never more than 2.
.PARAMETER Plan
    Resolve and print the configuration, check PC 1 files, then exit. Touches nothing, does not
    contact PC 2, takes no lock.
#>
[CmdletBinding()]
param(
    [ValidateSet('Full', 'Control', 'Stock')][string]$Arm = 'Full',
    [string]$Run = '',
    [string]$Pc1Build = '',
    [string]$Pc2Suite = '',
    [string]$ContentDir = '',
    [string]$Map = '',
    [string]$DoneRegex = '',
    [string]$GameRoot = 'C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux',
    [string]$HostSteamId = '',
    [string]$GuestName = 'RazorScout',
    [string]$OutDir = '',
    [string]$FriendScript = 'C:\Users\iestu\bin\bzr-friend-test\bzr-friend-test.ps1',
    [int]$JoinTimeoutSeconds = 240,
    [int]$PlaySeconds = 25,
    [int]$MissionSeconds = 330,
    [ValidateRange(1, 2)][int]$Attempts = 1,
    [switch]$KeepPc2Staged,
    [switch]$Plan
)
$ErrorActionPreference = 'Stop'
$here = $PSScriptRoot
if (-not $Run) { $Run = '{0}{1}' -f $Arm.ToLower(), (Get-Date -Format 'HHmm') }
if (-not $OutDir) { $OutDir = Join-Path $env:TEMP "bzr-twopc\run_$Run" }
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$statusFile = Join-Path $OutDir 'status.txt'
function Say($t) { $l = "[twopc $(Get-Date -Format HH:mm:ss)] $t"; Write-Host $l; try { Add-Content -LiteralPath $statusFile -Value $l } catch { } }

# ---------------------------------------------------------------- configuration
$dlls = 'winmm.dll', 'bzloader.dll', 'plugins\openshim.dll', 'scripts\patches.json'
$suite = $dlls + 'net.ini'
$multi = Join-Path $GameRoot 'multi.ini'
$lock = Join-Path $GameRoot 'bzr_livetest.lock'
$stock = ($Arm -eq 'Stock')
if (-not $Pc2Suite) { $Pc2Suite = $GameRoot }

if (-not $HostSteamId) {
    $steamRoot = ($GameRoot -split '\\steamapps\\')[0]
    $vdf = Join-Path $steamRoot 'config\loginusers.vdf'
    if (Test-Path -LiteralPath $vdf) {
        $txt = [IO.File]::ReadAllText($vdf)
        $m = [regex]::Matches($txt, '"(7656\d{13})"\s*\{[^}]*?"MostRecent"\s+"1"')
        if ($m.Count -gt 0) { $HostSteamId = $m[0].Groups[1].Value }
        else { $m = [regex]::Matches($txt, '"(7656\d{13})"'); if ($m.Count -eq 1) { $HostSteamId = $m[0].Groups[1].Value } }
    }
}
if ($HostSteamId -notmatch '^7656\d{13}$') { throw "host Steam ID unknown: pass -HostSteamId (loginusers.vdf had no usable MostRecent account)" }

$contentLeaf = ''
if ($ContentDir) {
    if (-not (Test-Path -LiteralPath $ContentDir -PathType Container)) { throw "-ContentDir not found: $ContentDir" }
    $ContentDir = (Resolve-Path -LiteralPath $ContentDir).Path
    $contentLeaf = Split-Path $ContentDir -Leaf
    $ContentDest = 'addon\' + $contentLeaf  # bzr-friend-test.ps1 -DeployAddon always uses addon\<leaf>
}
if ($Pc1Build) {
    foreach ($f in 'bin\Release\plugins\openshim.dll', 'scripts\patches.json') { if (-not (Test-Path -LiteralPath (Join-Path $Pc1Build $f))) { throw "-Pc1Build missing $f under $Pc1Build" } }
}
if ($stock -and $Pc1Build) { throw '-Pc1Build makes no sense with -Arm Stock (OpenShim is disabled)' }
if (-not (Test-Path -LiteralPath $FriendScript)) { throw "PC 2 driver not found: $FriendScript" }

Say "arm=$Arm run=$Run map=$(if ($Map) { $Map } else { '(multi.ini untouched)' }) hostSteamId=$HostSteamId guest=$GuestName attempts=$Attempts out=$OutDir"
Say "pc1Build=$(if ($Pc1Build) { $Pc1Build } else { '(installed)' }) pc2Suite=$(if ($stock) { '(stock arm: none)' } else { $Pc2Suite }) content=$(if ($ContentDir) { "$ContentDir -> $ContentDest" } else { '(none)' })"

if ($Plan) {
    foreach ($d in $suite) { $p = Join-Path $GameRoot $d; Say ("plan: {0} {1}" -f $d, $(if (Test-Path -LiteralPath $p) { (Get-FileHash $p).Hash.Substring(0, 8) } else { 'MISSING' })) }
    foreach ($f in 'openshim\renderer', 'openshim\ui', 'openshim\OpenShimAssets.ini') { if (-not (Test-Path -LiteralPath (Join-Path $Pc2Suite $f))) { Say "plan: WARNING -Pc2Suite lacks $f (-DeploySuite would refuse)" } }
    Say 'plan only: nothing launched, PC 2 not contacted'
    return
}

# ---------------------------------------------------------------- PC 2 helpers (only via the allow-listed script)
function Invoke-Pc2 {
    param([hashtable]$P2, [string]$Label)
    try { $o = (& $FriendScript @P2 2>&1 | Out-String) } catch { $o = "PC2-ERROR: $_" }
    try { Add-Content -LiteralPath (Join-Path $OutDir 'pc2_driver.log') -Value ("--- $(Get-Date -Format HH:mm:ss) $Label`r`n$o") } catch { }
    $o
}
function Invoke-Pc2Do([string]$Cmd, [int]$Wait = 15, [string]$Label = 'do', [int]$Lines = 0) {
    $a = @{ Do = $Cmd; Wait = $Wait }; if ($Lines -gt 0) { $a['Lines'] = $Lines }
    $o = Invoke-Pc2 $a $Label
    if ($o -match 'not finished after') { Say "PC2 -Do '$Label' did not finish in $Wait s" }
    $o
}
function Q([string]$s) { "'" + ($s -replace "'", "''") + "'" }   # PowerShell single-quote a literal
$pc2G = 'C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux'
function Get-Pc2Hashes([string]$statusText) {
    $h = @{}
    $m = [regex]::Match($statusText, 'openshim\.dll=(\S+) patches\.json=(\S+) winmm\.dll=(\S+) bzloader\.dll=(\S+)')
    if ($m.Success) { $h['plugins\openshim.dll'] = $m.Groups[1].Value; $h['scripts\patches.json'] = $m.Groups[2].Value; $h['winmm.dll'] = $m.Groups[3].Value; $h['bzloader.dll'] = $m.Groups[4].Value }
    $h
}
function Get-Pc2Pid {
    $o = Invoke-Pc2Do 'Get-Process battlezone98redux -EA 0 | % { "PC2PID=$($_.Id)" }; "PC2END"' 12 'pid'
    $ids = @([regex]::Matches($o, 'PC2PID=(\d+)') | ForEach-Object { [int]$_.Groups[1].Value })
    , $ids
}
# Newest BZLogger.txt written since the PC 2 game process started; reports the last match of each pattern.
function Get-Pc2LogHits([int]$ProcId, [string[]]$Patterns, [int]$TailLines = 0, [string]$Label = 'log') {
    $pl = ($Patterns | ForEach-Object { Q $_ }) -join ','
    $cmd = '$g=' + (Q $pc2G) + '; $st=(Get-Process -Id ' + $ProcId + ' -EA 0).StartTime; ' +
    '$l=$null; if($st){ $l=Get-ChildItem $g,"$g\logs" -Filter BZLogger.txt -File -EA 0 | ? { $_.LastWriteTime -ge $st.AddSeconds(-5) } | sort LastWriteTime -desc | select -First 1 }; ' +
    'if(-not $l){"PC2NOLOG"}else{ $fs=[IO.File]::Open($l.FullName,"Open","Read","ReadWrite"); $t=(New-Object IO.StreamReader($fs)).ReadToEnd(); $fs.Dispose(); $i=0; ' +
    'foreach($p in ' + $pl + '){ $m=[regex]::Matches($t,$p); if($m.Count){$v=$m[$m.Count-1].Value; if($v.Length -gt 170){$v=$v.Substring(0,170)}; "PC2HIT$i=$v"}else{"PC2MISS$i"}; $i++ } ' +
    $(if ($TailLines -gt 0) { '$t -split "`n" | select -Last ' + $TailLines + ' | % { "PC2T=" + $_.Trim() }' } else { '' }) + ' }'
    $o = Invoke-Pc2Do $cmd 20 $Label $(if ($TailLines -gt 0) { $Patterns.Count + $TailLines + 4 } else { 0 })
    $res = @{ Raw = $o; NoLog = ($o -match 'PC2NOLOG'); Hits = @{} }
    for ($i = 0; $i -lt $Patterns.Count; $i++) { $m = [regex]::Match($o, "PC2HIT$i=([^\r\n]*)"); if ($m.Success) { $res.Hits[$i] = $m.Groups[1].Value } }
    $res
}
function Send-Pc2Content([string]$Dir) {
    # bzr-friend-test.ps1 -DeployAddon copies to addon\<leaf>, moves an existing copy to C:\BZRCoop\addon-bak,
    # and -Restore/-Remove delete ours and put the original back.
    $script:pc2Deployed = $true
    $o = Invoke-Pc2 @{ DeployAddon = $Dir } 'deploy-addon'
    if ($o -match 'PC2-ERROR') { throw "FIXTURE: PC 2 -DeployAddon failed: $($o.Trim())" }
    if ($o -notmatch ('addons=[^\r\n]*' + [regex]::Escape($contentLeaf))) { throw "FIXTURE: PC 2 -Status does not list addon $contentLeaf after -DeployAddon" }
    Say "PC 2 addon deployed: addon\$contentLeaf"
}
function Stop-Pc2Game([int]$ProcId) {
    if ($ProcId -le 0) { return }
    $null = Invoke-Pc2Do ('$p=Get-Process -Id ' + $ProcId + ' -EA 0; if($p -and $p.Name -eq "battlezone98redux"){ [void]$p.CloseMainWindow(); "PC2CLOSE" } else { "PC2GONE" }') 12 'pc2-close'
    for ($i = 0; $i -lt 4; $i++) {
        Start-Sleep -Seconds 5
        $ids = Get-Pc2Pid
        if ($ids -notcontains $ProcId) { return }
    }
    Say "PC 2 game $ProcId ignored the window close; stopping that PID only"
    $null = Invoke-Pc2Do ('$p=Get-Process -Id ' + $ProcId + ' -EA 0; if($p -and $p.Name -eq "battlezone98redux"){ Stop-Process -Id ' + $ProcId + ' -Force; "PC2KILLED" }') 12 'pc2-kill'
}

# ---------------------------------------------------------------- PC 1 preconditions and lock
if (@(Get-Process battlezone98redux -ErrorAction SilentlyContinue).Count -gt 0) { Say 'VERDICT: FIXTURE - a game is already running on PC 1'; Set-Content (Join-Path $OutDir 'verdict.txt') 'VERDICT: FIXTURE - a game is already running on PC 1'; exit 2 }
& (Join-Path $here 'Wait-BZRLiveTestLock.ps1') -GameRoot $GameRoot -TimeoutSeconds 600 -PollSeconds 10
if ($LASTEXITCODE -ne 0) { Say 'VERDICT: FIXTURE - live-test lock wait timed out'; Set-Content (Join-Path $OutDir 'verdict.txt') 'VERDICT: FIXTURE - live-test lock wait timed out'; exit 2 }

$lockTaken = $false; $pids = @(); $pc2Pid = 0; $multiSaved = $false; $suiteSaved = $false; $offDone = $false
$contentDeployed1 = $false; $contentBacked1 = $false; $pc2Setup = $false; $pc2Deployed = $false
$verdict = 'FIXTURE'; $reason = 'did not finish'
$suiteBak = Join-Path $OutDir 'suite_bak'; $multiBak = Join-Path $OutDir 'multi.ini.bak'
$content1 = if ($ContentDir) { Join-Path $GameRoot $ContentDest } else { '' }
$content1Bak = if ($ContentDir) { $content1 + '.bzrtest-bak' } else { '' }
$t0 = Get-Date
$script:gamePid = 0; $script:phase = 'pre'

function LogPath { Get-ChildItem -LiteralPath $GameRoot, (Join-Path $GameRoot 'logs') -Filter 'BZLogger.txt' -File -ErrorAction SilentlyContinue | Where-Object { $_.LastWriteTime -gt $script:t0 } | Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty FullName }
function Find([string]$pat) {
    $p = LogPath; if (-not $p) { return $null }
    $fs = [IO.File]::Open($p, 'Open', 'Read', 'ReadWrite')
    try { $t = (New-Object IO.StreamReader($fs)).ReadToEnd() } finally { $fs.Dispose() }
    $m = [regex]::Matches($t, $pat); if ($m.Count) { $m[$m.Count - 1] } else { $null }
}
function Fail-Wait([string]$msg) { $tag = if ($script:phase -eq 'post') { 'FAIL' } else { 'FIXTURE' }; throw "${tag}: $msg" }
function WaitFor([string]$name, [string]$pat, [int]$sec) {
    $end = (Get-Date).AddSeconds($sec)
    while ((Get-Date) -lt $end) {
        if (-not (Get-Process -Id $script:gamePid -ErrorAction SilentlyContinue)) { Fail-Wait "PC 1 game exited during '$name'" }
        $m = Find $pat; if ($m) { Say "ok $name : $($m.Value)"; return $m }
        Start-Sleep -Milliseconds 500
    }
    Fail-Wait "timeout '$name' after $sec s"
}
function Click($xy) {
    $h = Get-BZRClientWindow $script:gamePid; $sz = [TwoPC.Rect]::Size($h); $w = $sz[0]; $ht = $sz[1]; $s = $ht / 720.0
    $x = switch ($xy[2]) { 'C' { ($xy[0] - 640) * $s + $w / 2 } 'R' { $w - (1280 - $xy[0]) * $s } default { $xy[0] * $s } }
    $x = [Math]::Max(5, [Math]::Min($w - 5, [int]$x))
    Send-BZRClientClick $script:gamePid $x ([int]($xy[1] * $s))
}
function Pc2Click([string]$arg) { Invoke-Pc2Do ("& 'C:\BZRCoop\friend\drv_pc2.ps1' -GamePid $pc2Pid -Action click -Arg '$arg'") 15 "pc2-click $arg" }

try {
    try { $lfs = [IO.File]::Open($lock, 'CreateNew', 'Write', 'None') } catch { throw "FIXTURE: live-test lock taken by another session: $(Get-Content -LiteralPath $lock -ErrorAction SilentlyContinue)" }
    $lockTaken = $true
    try { $lb = [Text.Encoding]::UTF8.GetBytes("two-PC live test $Run (Invoke-BZRTwoPCTest) pid=$PID $(Get-Date -Format s)"); $lfs.Write($lb, 0, $lb.Length) } finally { $lfs.Dispose() }
    $ogre0 = (Get-FileHash (Join-Path $GameRoot 'ogre.cfg') -Algorithm SHA256).Hash

    # back up every file the run may change, before touching anything
    New-Item -ItemType Directory -Force -Path $suiteBak | Out-Null
    $suiteHash = @{}
    foreach ($f in $suite) {
        $p = Join-Path $GameRoot $f
        if ($f -eq 'net.ini' -and -not (Test-Path -LiteralPath $p)) { continue }
        $suiteHash[$f] = (Get-FileHash $p).Hash
        Copy-Item -LiteralPath $p -Destination (Join-Path $suiteBak ($f -replace '\\', '_')) -Force
    }
    $suiteSaved = $true
    if (Test-Path -LiteralPath $multi) { Copy-Item -LiteralPath $multi -Destination $multiBak -Force; $multiSaved = $true }

    if ($Pc1Build) {
        Copy-Item -LiteralPath (Join-Path $Pc1Build 'bin\Release\plugins\openshim.dll') -Destination (Join-Path $GameRoot 'plugins\openshim.dll') -Force
        Copy-Item -LiteralPath (Join-Path $Pc1Build 'scripts\patches.json') -Destination (Join-Path $GameRoot 'scripts\patches.json') -Force
        Say "PC 1 build deployed from $Pc1Build"
    }
    $hashes0 = @{}
    $buildBak = Join-Path $OutDir 'build_bak'; New-Item -ItemType Directory -Force -Path $buildBak | Out-Null
    foreach ($d in $dlls) {
        $p = Join-Path $GameRoot $d
        $hashes0[$d] = (Get-FileHash $p -Algorithm SHA256).Hash
        Say ("PC1 {0} {1} v{2}" -f $d, $hashes0[$d].Substring(0, 8), (Get-Item $p).VersionInfo.FileVersion)
        Copy-Item -LiteralPath $p -Destination (Join-Path $buildBak ($d -replace '\', '_')) -Force
    }

    if ($Map) {
        $txt = [IO.File]::ReadAllText($multi)
        if ($txt -notmatch '(?m)^map = ') { throw 'FIXTURE: multi.ini has no "map = " line to edit' }
        [IO.File]::WriteAllText($multi, [regex]::Replace($txt, '(?m)^map = .*$', "map = $Map"))
        Say "multi.ini map = $Map"
    }
    if ($ContentDir) {
        if (Test-Path -LiteralPath $content1Bak) { throw "FIXTURE: $content1Bak already exists; resolve it by hand" }
        $contentDeployed1 = $true
        if (Test-Path -LiteralPath $content1) { Move-Item -LiteralPath $content1 -Destination $content1Bak; $contentBacked1 = $true }
        New-Item -ItemType Directory -Force -Path $content1 | Out-Null
        Copy-Item -Path (Join-Path $ContentDir '*') -Destination $content1 -Recurse -Force
        Say "PC 1 content deployed: $ContentDest ($((Get-ChildItem $content1 -Recurse -File).Count) files, backup=$contentBacked1)"
    }

    # environment per arm
    $env:BZR_FORCE_WINDOWED = '1'
    if ($stock) {
        Rename-Item -LiteralPath (Join-Path $GameRoot 'winmm.dll') -NewName 'winmm.dll.bzrtest-off'; $offDone = $true
        $env:BZR_NO_FOREGROUND_WATCHDOG = '1'; $env:BZR_ALLOW_FOREGROUND_LAUNCH = '1'
        Say 'STOCK arm: winmm.dll renamed to winmm.dll.bzrtest-off (OpenShim not loaded on PC 1)'
    }
    else {
        $env:OPENSHIM_NEVER_ACTIVATE = '1'; $env:OPENSHIM_NEVER_CAPTURE_MOUSE = '1'; $env:OPENSHIM_DISABLE_RAW_MOUSE_INPUT = '1'
        if ($Arm -eq 'Control') { $env:OPENSHIM_DISABLE_SPLINTER_PAYLOAD_LOCAL = '1'; $env:OPENSHIM_DISABLE_SNIPER_KILL_CREDIT = '1'; Say 'CONTROL arm: both fixes disabled by env' }
    }
    . (Join-Path $here 'BZRHarness.ps1')
    . (Join-Path $here 'BZRWindowInput.ps1')
    if (-not ('TwoPC.Rect' -as [type])) {
        Add-Type -TypeDefinition 'using System; using System.Runtime.InteropServices; namespace TwoPC { public static class Rect { [StructLayout(LayoutKind.Sequential)] struct R { public int L, T, Ri, B; } [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h, out R r); public static int[] Size(IntPtr h) { R r; GetClientRect(h, out r); return new int[] { r.Ri - r.L, r.B - r.T }; } } }'
    }
    $crashLog = Join-Path $GameRoot 'logs\openshim_crash.log'
    $crashLen0 = if (Test-Path $crashLog) { (Get-Item $crashLog).Length } else { 0 }
    $bzd0 = @(Get-ChildItem 'C:\BZDumps' -Filter '*.dmp' -Recurse -ErrorAction SilentlyContinue | ForEach-Object FullName)
    Assert-BZRSafeToLaunch

    # ---------------- PC 2 staging (via the allow-listed script only)
    $st = Invoke-Pc2 @{ Status = $true } 'status0'
    if ($st -match 'PC2-ERROR') { throw "FIXTURE: PC 2 driver failed: $($st.Trim())" }
    if ($st -notmatch 'task=True') { Say 'PC 2 not set up; running -Setup'; $null = Invoke-Pc2 @{ Setup = $true } 'setup'; $pc2Setup = $true }
    if (-not $stock) {
        $null = Invoke-Pc2 @{ DeploySuite = $Pc2Suite } 'deploy-suite'; $pc2Deployed = $true
    }
    if ($ContentDir) { Send-Pc2Content $ContentDir }

    for ($attempt = 1; $attempt -le $Attempts; $attempt++) {
        Say "=== attempt $attempt of $Attempts ==="
        $script:phase = 'pre'; $verdict = 'FIXTURE'; $reason = 'did not finish'; $doneMissing = $false
        $pids = @(); $pc2Pid = 0; $pc2Started = $false
        $script:t0 = Get-Date
        $ap = "a$attempt"
        try {
            # PC 2 file parity check (full suite only), fresh every attempt because the updater swaps DLLs on exit
            $st = Invoke-Pc2 @{ Status = $true } "status-a$attempt"
            $p2 = Get-Pc2Hashes $st
            Say "PC2 hashes: $(($p2.GetEnumerator() | Sort-Object Name | ForEach-Object { '{0}={1}' -f $_.Name, $_.Value }) -join ' ')"
            if (-not $stock) {
                $bad = @(); foreach ($d in $dlls) { $want = (Get-FileHash (Join-Path $GameRoot $d)).Hash.Substring(0, 8); if ($p2[$d] -ne $want) { $bad += "$d pc1=$want pc2=$($p2[$d])" } }
                if ($bad.Count -gt 0) {
                    Say "PC 2 suite differs ($($bad -join '; ')); redeploying once"
                    $null = Invoke-Pc2 @{ DeploySuite = $Pc2Suite } "redeploy-a$attempt"
                    $p2 = Get-Pc2Hashes (Invoke-Pc2 @{ Status = $true } "status-a$attempt-b")
                    $bad = @(); foreach ($d in $dlls) { $want = (Get-FileHash (Join-Path $GameRoot $d)).Hash.Substring(0, 8); if ($p2[$d] -ne $want) { $bad += "$d pc1=$want pc2=$($p2[$d])" } }
                    if ($bad.Count -gt 0) { throw "FIXTURE: PC 2 suite does not match PC 1: $($bad -join '; ')" }
                }
                Say 'PC 2 suite hashes match PC 1'
            }
            if ((Get-Pc2Pid).Count -gt 0) { throw 'FIXTURE: a Battlezone process is already running on PC 2' }
            foreach ($d in ($dlls | Where-Object { -not ($stock -and $_ -eq 'winmm.dll') })) { if ((Get-FileHash (Join-Path $GameRoot $d) -Algorithm SHA256).Hash -ne $hashes0[$d]) { throw "FIXTURE: $d changed before launch" } }

            # ---------------- PC 1: launch and create the lobby
            $gamePid = (Start-BZRGameProcess -FilePath (Join-Path $GameRoot 'battlezone98redux.exe') -ArgumentList '/nointro' -WorkingDirectory $GameRoot -PassThru).Id
            $script:gamePid = $gamePid; $pids += $gamePid
            Say "PC1 launched pid $gamePid"
            $UI = @{ MainMultiPlayer = @(845, 163, 'C'); LoungeCreate = @(1138, 25, 'R'); CreateNameField = @(725, 255, 'C'); CreateOkay = @(727, 358, 'C'); StagingLaunch = @(1138, 25, 'R') }
            $null = WaitFor 'menu' 'Start of Game Menu Display' 240
            Start-Sleep -Seconds 4
            $sz = [TwoPC.Rect]::Size((Get-BZRClientWindow $gamePid)); Say "PC1 client $($sz[0])x$($sz[1])"
            Click $UI.MainMultiPlayer
            Start-Sleep -Seconds 4
            if ($stock) {
                $end = (Get-Date).AddSeconds(20); while ((Get-Date) -lt $end -and -not (Find 'fully entered lobby')) { Start-Sleep -Milliseconds 400 }
                if (-not (Find 'fully entered lobby')) { Say 're-click MultiPlayer'; Click $UI.MainMultiPlayer }
            }
            else {
                Click @(640, 619, 'C')   # OpenShim MULTIPLAYER screen: Continue
                $end = (Get-Date).AddSeconds(15); while ((Get-Date) -lt $end -and -not (Find 'fully entered lobby')) { Start-Sleep -Milliseconds 400 }
                if (-not (Find 'fully entered lobby')) { Say 're-click Continue'; Click @(640, 619, 'C') }
            }
            $null = WaitFor 'lounge' 'fully entered lobby' 60
            Start-Sleep -Seconds 2
            Click $UI.LoungeCreate; Start-Sleep -Milliseconds 800; Click $UI.LoungeCreate; Start-Sleep -Milliseconds 500
            Click $UI.CreateNameField; Start-Sleep -Milliseconds 300
            Send-BZRClientText $gamePid "TwoPC$Run"; Start-Sleep -Milliseconds 400
            Click $UI.CreateOkay
            $created = WaitFor 'created' 'OnLobbyCreated, joined (B\d+)' 45
            $lobby = $created.Groups[1].Value
            Say "LOBBY $lobby"

            # ---------------- PC 2: start the game, reach the lounge, join, Ready
            $pc2Started = $true
            $null = Invoke-Pc2Do ('Start-Process -FilePath ' + (Q "$pc2G\battlezone98redux.exe") + ' -ArgumentList ' + (Q '/nointro') + ' -WorkingDirectory ' + (Q $pc2G) + '; "PC2STARTED"') 15 'pc2-start'
            $end = (Get-Date).AddSeconds(30)
            while ($pc2Pid -eq 0 -and (Get-Date) -lt $end) { $ids = Get-Pc2Pid; if ($ids.Count -gt 0) { $pc2Pid = $ids[0] } else { Start-Sleep -Seconds 2 } }
            if ($pc2Pid -eq 0) { throw 'FIXTURE: PC 2 game process did not appear' }
            Say "PC2 game pid $pc2Pid"
            $end = (Get-Date).AddSeconds(240); $menu = $false
            while ((Get-Date) -lt $end -and -not $menu) {
                $r = Get-Pc2LogHits $pc2Pid @('Start of Game Menu Display') 0 'pc2-menu'
                if ($r.Hits.ContainsKey(0)) { $menu = $true } else { if ((Get-Pc2Pid) -notcontains $pc2Pid) { throw 'FIXTURE: PC 2 game exited before the main menu' }; Start-Sleep -Seconds 4 }
            }
            if (-not $menu) { throw 'FIXTURE: PC 2 never reached the main menu' }
            Say 'PC2 main menu'
            Start-Sleep -Seconds 4
            $null = Pc2Click '845,163,C'
            Start-Sleep -Seconds 4
            if (-not $stock) { $null = Pc2Click '640,619,C' }
            $end = (Get-Date).AddSeconds(60); $lounge = $false
            while ((Get-Date) -lt $end -and -not $lounge) {
                $r = Get-Pc2LogHits $pc2Pid @('fully entered lobby') 0 'pc2-lounge'
                if ($r.Hits.ContainsKey(0)) { $lounge = $true } else { Start-Sleep -Seconds 3 }
            }
            if (-not $lounge) { throw 'FIXTURE: PC 2 never entered the lounge' }
            Say 'PC2 in the lounge'

            $joinCmd = "Start-Process -FilePath 'steam://rungame/301650/$HostSteamId/-connect-galaxy-lobby=$lobby'; `"PC2JOINSENT`""
            $joined = $null
            for ($try = 1; $try -le 2 -and -not $joined; $try++) {
                $null = Invoke-Pc2Do $joinCmd 15 "pc2-join-$try"
                Say "join sent ($try of 2)"
                $end = (Get-Date).AddSeconds($(if ($try -eq 1) { [Math]::Min(90, $JoinTimeoutSeconds) } else { $JoinTimeoutSeconds }))
                while ((Get-Date) -lt $end -and -not $joined) {
                    if (-not (Get-Process -Id $gamePid -ErrorAction SilentlyContinue)) { throw 'FIXTURE: PC 1 game exited waiting for the guest' }
                    $joined = Find "Assigned Player \(?$([regex]::Escape($GuestName))\)? team (\d+)"
                    if (-not $joined) { Start-Sleep -Milliseconds 700 }
                }
            }
            if (-not $joined) { throw "FIXTURE: guest $GuestName never joined the lobby" }
            Say "ok joined : $($joined.Value)"
            Start-Sleep -Seconds 4
            $null = Pc2Click '1138,25,R'   # Ready
            Say 'PC2 Ready clicked'
            Start-Sleep -Seconds 6

            # ---------------- Launch and judge
            Click $UI.StagingLaunch
            Say 'Launch clicked'
            $end = (Get-Date).AddSeconds(20)
            while ((Get-Date) -lt $end -and -not (Find 'Launching Network Game')) { Start-Sleep -Milliseconds 500 }
            if (-not (Find 'Launching Network Game')) { Say 're-click Launch'; Click $UI.StagingLaunch }
            $ln = WaitFor 'launching' 'Launching Network Game[^\r\n]*' 60
            $script:phase = 'post'
            if ($Map) { if ($ln.Value -notmatch "Map $([regex]::Escape($Map))\b") { $script:phase = 'pre'; throw "FIXTURE: launched a different map than -Map $Map : $($ln.Value)" } }
            $null = WaitFor 'sync-start' 'Sync Start, State.*' 120
            $null = WaitFor 'sync-complete' 'Sync Start Complete.*' 150
            Start-Sleep -Seconds 3
            $syncFail1 = [bool](Find 'Start Sync Failure')
            if (-not $syncFail1) {
                if ($DoneRegex) {
                    $end = (Get-Date).AddSeconds($MissionSeconds); $done = $false
                    while ((Get-Date) -lt $end) {
                        if (-not (Get-Process -Id $gamePid -ErrorAction SilentlyContinue)) { Say 'PC1 game exited during the mission'; break }
                        if (Find $DoneRegex) { $done = $true; Say "done marker seen: $DoneRegex; 8 s more"; Start-Sleep -Seconds 8; break }
                        Start-Sleep -Seconds 1
                    }
                    if (-not $done) { $doneMissing = $true }
                }
                else {
                    Say "sync complete with no failure; playing $PlaySeconds s"
                    $end = (Get-Date).AddSeconds($PlaySeconds)
                    while ((Get-Date) -lt $end) { if (-not (Get-Process -Id $gamePid -ErrorAction SilentlyContinue)) { Say 'PC1 game exited during play'; break }; Start-Sleep -Seconds 1 }
                }
            }
            # judge PC 1 at the end of the play window (our own stop later writes 'Exiting Game' too)
            $h = @{
                SyncOk  = [bool](Find 'Sync Start Complete')
                Playing = [bool](Find 'Game Simulation Initialized[^\r\n]*Playing')
                SyncFail = [bool](Find 'Start Sync Failure')
                Exited  = [bool](Find 'Exiting Game')
                Alive   = [bool](Get-Process -Id $gamePid -ErrorAction SilentlyContinue)
            }
            # PC 2 log read-back BEFORE any teardown
            $pats = @('Sync Start Complete', 'Game Simulation Initialized[^\r\n]*Playing', 'Start Sync Failure', 'Exiting Game', 'Launching Network Game')
            $r2 = Get-Pc2LogHits $pc2Pid $pats 40 'pc2-keylines'
            Set-Content -LiteralPath (Join-Path $OutDir "pc2_keylines_$ap.txt") -Value $r2.Raw
            Say "PC1 judge: $(($h.GetEnumerator() | Sort-Object Name | ForEach-Object { '{0}={1}' -f $_.Name, $_.Value }) -join ' ')"
            Say "PC2 judge: nolog=$($r2.NoLog) syncOk=$($r2.Hits.ContainsKey(0)) playing=$($r2.Hits.ContainsKey(1)) syncFail=$($r2.Hits.ContainsKey(2)) exited=$($r2.Hits.ContainsKey(3))"
            if ($r2.NoLog) { throw 'FIXTURE: PC 2 log could not be read back' }
            $why = @()
            if ($h.SyncFail) { $why += 'host Network Start Sync Failure' }
            if ($h.Exited -or -not $h.Alive) { $why += 'host left the game during the play window' }
            if ($r2.Hits.ContainsKey(2)) { $why += 'guest Start Sync Failure' }
            if ($r2.Hits.ContainsKey(3)) { $why += 'guest Exiting Game' }
            if (-not $h.SyncOk -or -not $h.Playing) { $why += 'host never showed Sync Start Complete + Playing' }
            if (-not $r2.Hits.ContainsKey(0) -or -not $r2.Hits.ContainsKey(1)) { $why += 'guest never showed Sync Start Complete + Playing' }
            if ($doneMissing) { $why += "-DoneRegex marker not seen within $MissionSeconds s" }
            if ($why.Count -gt 0) { $verdict = 'FAIL'; $reason = $why -join '; ' }
            else { $verdict = 'PASS'; $reason = 'both PCs: Sync Start Complete + Game Simulation Initialized Playing, no Exiting Game' }
        }
        catch {
            $msg = "$_"
            if ($msg -match '^(FIXTURE|FAIL): (.*)') { $verdict = $Matches[1]; $reason = $Matches[2] }
            else { $verdict = 'FIXTURE'; $reason = "driver error: $msg" }
        }
        finally {
            # per-attempt teardown: our own PIDs only
            foreach ($p in @(Get-Process battlezone98redux -ErrorAction SilentlyContinue)) {
                if ($pids -contains $p.Id) { try { Stop-BZRGame -Id $p.Id -TimeoutSeconds 40 } catch { Say "Stop-BZRGame: $_" } }
            }
            try { if ($pc2Pid -eq 0 -and $pc2Started) { $late = Get-Pc2Pid; if ($late.Count -gt 0) { $pc2Pid = $late[0] } } } catch { }
            try { if ($pc2Pid -gt 0) { Stop-Pc2Game $pc2Pid } } catch { Say "PC2 stop: $_" }
            Start-Sleep -Seconds 3
            foreach ($p in @(Get-Process battlezone98redux -ErrorAction SilentlyContinue)) {
                if ($pids -contains $p.Id) { Say "plain stop failed for $($p.Id); forcing (own windowed game)"; try { Stop-BZRGame -Id $p.Id -Force } catch { Say "force: $_" } }
            }
            Start-Sleep -Seconds 2
            foreach ($l in 'BZLogger.txt', 'BZChatLog.txt', 'logs\BZLogger.txt', 'logs\openshim.log') {
                try { $src = Join-Path $GameRoot $l; if ((Test-Path $src) -and (Get-Item $src).LastWriteTime -gt $script:t0) { Copy-Item $src (Join-Path $OutDir ("host_${ap}_" + ($l -replace '\\', '_'))) -Force } } catch { }
            }
            try { if ($pc2Pid -gt 0) { $r3 = Get-Pc2LogHits $pc2Pid @('Exiting Game') 40 'pc2-tail'; Set-Content -LiteralPath (Join-Path $OutDir "pc2_tail_$ap.txt") -Value $r3.Raw } } catch { }
            # the updater swaps PC 1 DLLs on exit: put every file back before the next attempt
            foreach ($f in $suite) { try { if (-not $suiteHash.ContainsKey($f)) { continue }; if ($offDone -and $f -eq 'winmm.dll') { continue }; $dst = Join-Path $GameRoot $f; $want = if ($hashes0.ContainsKey($f)) { $hashes0[$f] } else { $suiteHash[$f] }; $bk = if ($hashes0.ContainsKey($f)) { $buildBak } else { $suiteBak }; if ((Get-FileHash $dst).Hash -ne $want) { Copy-Item -LiteralPath (Join-Path $bk ($f -replace '\\', '_')) -Destination $dst -Force; Say "restored $f" } } catch { Say "suite restore $f : $_" } }
            Say "attempt $attempt result: $verdict - $reason"
        }
        if ($verdict -ne 'FIXTURE') { break }
        if ($attempt -lt $Attempts) { Say 'FIXTURE result; one retry allowed'; Start-Sleep -Seconds 5 }
    }
}
catch {
    $msg = "$_"
    if ($msg -match '^(FIXTURE|FAIL): (.*)') { $verdict = $Matches[1]; $reason = $Matches[2] } else { $verdict = 'FIXTURE'; $reason = "driver error: $msg" }
}
finally {
    # stuartserver: content, then suite/setup, never Steam
    try {
        if ($pc2Setup -and -not $KeepPc2Staged) { $o = Invoke-Pc2 @{ Remove = $true } 'remove'; if ($o -match 'PC2-ERROR|game is running') { Say 'WARNING: PC 2 NOT RESTORED (-Remove failed): run bzr-friend-test.ps1 -Remove by hand' } else { Say "PC2 -Remove done: $(([regex]::Match($o, 'task=[^\r\n]*')).Value)" } }
        elseif ($pc2Deployed -and -not $KeepPc2Staged) { $o = Invoke-Pc2 @{ Restore = $true } 'restore'; if ($o -match 'PC2-ERROR|game is running') { Say 'WARNING: PC 2 NOT RESTORED (-Restore failed): run bzr-friend-test.ps1 -Restore by hand' } else { Say "PC2 -Restore done: $(([regex]::Match($o, 'openshim\.dll=[^\r\n]*')).Value)" } }
        elseif ($KeepPc2Staged) { Say 'PC 2 left staged (-KeepPc2Staged): run bzr-friend-test.ps1 -Restore / -Remove yourself' }
    } catch { Say "PC2 teardown: $_" }
    # PC 1: files, content, ogre config, lock
    try { if ($contentDeployed1) { if (Test-Path -LiteralPath $content1) { Remove-Item -LiteralPath $content1 -Recurse -Force }; if ($contentBacked1 -and (Test-Path -LiteralPath $content1Bak)) { Move-Item -LiteralPath $content1Bak -Destination $content1 } } } catch { Say "PC1 content restore: $_" }
    try { if ($multiSaved) { Copy-Item -LiteralPath $multiBak -Destination $multi -Force } } catch { Say "multi restore: $_" }
    try { $off = Join-Path $GameRoot 'winmm.dll.bzrtest-off'; if ($offDone -and (Test-Path $off) -and -not (Test-Path (Join-Path $GameRoot 'winmm.dll'))) { Rename-Item -LiteralPath $off -NewName 'winmm.dll'; Say 'winmm.dll renamed back' } } catch { Say "winmm rename back: $_" }
    if ($suiteSaved) { foreach ($f in $suite) { try { if (-not $suiteHash.ContainsKey($f)) { continue }; $dst = Join-Path $GameRoot $f; if ((Get-FileHash $dst).Hash -ne $suiteHash[$f]) { Copy-Item -LiteralPath (Join-Path $suiteBak ($f -replace '\\', '_')) -Destination $dst -Force; Say "final restore $f" } } catch { Say "suite restore $f : $_" } } }
    try { Restore-BZROrphanedOgreConfig -GameRoot $GameRoot 3>$null | Out-Null } catch { Say "ogre restore: $_" }
    try { Say "ogre.cfg restored=$((Get-FileHash (Join-Path $GameRoot 'ogre.cfg') -Algorithm SHA256).Hash -eq $ogre0)" } catch { }
    try {
        $crashLen1 = if (Test-Path $crashLog) { (Get-Item $crashLog).Length } else { 0 }
        $bzd1 = @(Get-ChildItem 'C:\BZDumps' -Filter '*.dmp' -Recurse -ErrorAction SilentlyContinue | ForEach-Object FullName)
        Say "openshim_crash.log delta $($crashLen1 - $crashLen0); new BZDumps: $(@($bzd1 | Where-Object { $bzd0 -notcontains $_ }) -join ',')"
    } catch { }
    if ($lockTaken) { try { Remove-Item -LiteralPath $lock -Force } catch { Say "lock: $_" } }
    Say "cleanup done; lock=$(Test-Path $lock) content=$(if ($ContentDir) { Test-Path $content1Bak } else { 'n/a' })"
    $line = "VERDICT: $verdict - $reason (arm=$Arm run=$Run)"
    try { Set-Content -LiteralPath (Join-Path $OutDir 'verdict.txt') -Value $line } catch { }
    Write-Host $line
}
if ($verdict -eq 'PASS') { exit 0 } elseif ($verdict -eq 'FAIL') { exit 1 } else { exit 2 }
