<#
.SYNOPSIS
    A/B of the stock blt-model swap chain against OpenShim's opt-in DXGI flip
    model ([Graphics] DxgiFlipModel / OPENSHIM_DXGI_FLIP_MODEL), measured with
    the frame-boundary telemetry (OPENSHIM_PERF_TELEMETRY=1).

.DESCRIPTION
    Runs every combination of -Scenario x -Display x -Arms, -Repeat times, with
    the arms interleaved (stock, flip, stock, flip ...) so drift over the
    session lands on both. Each run is analysed with analyze_frame_hitches.py
    and a summary.md table is written at the end.

    Scenarios:
      lcbench  addon\lcbench, scenario combat, 40 avtank, 6 s warm-up then
               -LcbenchMeasureSeconds of measurement; the run ends at the
               mission's benchmark-end marker.
      crwx     crsetup.bzn with mods\3686673790\crsetup.lua temporarily
               replaced by a harness that holds CRMarsWeather at Severe
               (level 5); runs -CrwxSeconds after simulation start. The
               original crsetup.lua is restored byte-for-byte in finally.

    THE RESULT IS ONLY PACING EVIDENCE AT THE PHYSICAL CONSOLE. Over RDP the
    remote compositor presents at about 30 Hz and turns every run into a 5/31
    ms alternation (frame_hitch_va_measurement_20261020.md). The script refuses
    to run in a remote session unless -AllowRemoteSession is passed, and then
    marks every run remote=true; use that only to smoke-test the plumbing.

    At the console the game is launched with foreground allowed, because DWM
    grants independent flip only to the foreground window. Leave the machine
    alone while it runs. ogre.cfg is changed per run (DX11, Full Screen, Video
    Mode, VSync; FSAA is left as configured) and restored in finally, with the
    usual ogre.cfg.bzrharness-backup for crash recovery. The game is stopped
    with Stop-BZRGame and is never killed.

.EXAMPLE
    # At the console, full matrix (about 25 minutes):
    .\reverse_engineering\run_flip_model_ab.ps1 -PresentMon

.EXAMPLE
    # Over RDP, plumbing smoke only (windowed, one crwx pair):
    .\reverse_engineering\run_flip_model_ab.ps1 -AllowRemoteSession -Display windowed -Scenario crwx -CrwxSeconds 30
#>
param(
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$OutputRoot = '',
    [ValidateSet('stock', 'flip')][string[]]$Arms = @('stock', 'flip'),
    [ValidateSet('windowed', 'fullscreen')][string[]]$Display = @('windowed', 'fullscreen'),
    [ValidateSet('lcbench', 'crwx')][string[]]$Scenario = @('lcbench', 'crwx'),
    [ValidateRange(1, 10)][int]$Repeat = 1,
    [ValidateSet('Yes', 'No')][string]$VSync = 'Yes',
    [string]$WindowedMode = '1920 x 1080 @ 32-bit colour',
    # Empty = the primary display's current resolution.
    [string]$FullscreenMode = '',
    [ValidateRange(10, 300)][int]$LcbenchMeasureSeconds = 40,
    [ValidateRange(10, 600)][int]$CrwxSeconds = 90,
    # Frames from the first seconds of the RUN_STARTED selection are load tail.
    [double]$SkipSeconds = 10.0,
    [switch]$PresentMon,
    [switch]$AllowRemoteSession,
    [switch]$SkipDeploy
)

$ErrorActionPreference = 'Stop'
$repoRoot = Split-Path -Parent $PSScriptRoot
. (Join-Path $PSScriptRoot 'BZRHarness.ps1')

Add-Type -Namespace FlipAb -Name Native -MemberDefinition @'
[DllImport("user32.dll")] public static extern int GetSystemMetrics(int index);
[DllImport("user32.dll")] public static extern System.IntPtr GetForegroundWindow();
[DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(System.IntPtr h, out uint pid);
[DllImport("user32.dll")] public static extern bool SetForegroundWindow(System.IntPtr h);
[DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, System.UIntPtr extra);
'@

$SM_REMOTESESSION = 0x1000
$remote = [FlipAb.Native]::GetSystemMetrics($SM_REMOTESESSION) -ne 0
if ($remote -and -not $AllowRemoteSession) {
    throw ("This is a remote (RDP) session. Its ~30 Hz compositor invalidates every pacing number. " +
           "Run at the physical console, or pass -AllowRemoteSession for a plumbing smoke test only.")
}
if ($remote -and ($Display -contains 'fullscreen')) {
    throw "Refusing exclusive fullscreen over RDP; pass -Display windowed for a remote smoke test."
}

if (-not $OutputRoot) { $OutputRoot = Join-Path $PSScriptRoot 'snapshots\flip_model_ab' }
$session = Join-Path $OutputRoot (Get-Date -Format 'yyyyMMdd_HHmmss')
New-Item -ItemType Directory -Force $session | Out-Null

$exe = Join-Path $GameRoot 'battlezone98redux.exe'
$logs = Join-Path $GameRoot 'logs'
$bzLogger = Join-Path $logs 'BZLogger.txt'
$ogreCfg = Join-Path $GameRoot 'ogre.cfg'
$ogreBackup = Join-Path $GameRoot 'ogre.cfg.bzrharness-backup'
$lcbSource = Join-Path $PSScriptRoot 'test_missions\live_combat_scaling'
$lcbRoot = Join-Path $GameRoot 'addon\lcbench'
$crLua = Join-Path $GameRoot 'mods\3686673790\crsetup.lua'
$crHarness = Join-Path $PSScriptRoot 'flip_model_ab\crwx_harness.lua'
$analyzer = Join-Path $PSScriptRoot 'analyze_frame_hitches.py'
$presentMonExe = 'C:\Program Files\AMD\CNext\CNext\PresentMon-x64.exe'
if ($PresentMon -and -not (Test-Path -LiteralPath $presentMonExe)) { throw "PresentMon not found: $presentMonExe" }

if (-not $FullscreenMode) {
    $vc = Get-CimInstance Win32_VideoController | Where-Object CurrentHorizontalResolution | Select-Object -First 1
    $FullscreenMode = '{0} x {1} @ 32-bit colour' -f $vc.CurrentHorizontalResolution, $vc.CurrentVerticalResolution
}

function Read-SharedText([string]$Path) {
    if (-not (Test-Path -LiteralPath $Path)) { return '' }
    $fs = [IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    try { return (New-Object IO.StreamReader($fs)).ReadToEnd() } finally { $fs.Dispose() }
}

function Set-RunOgreConfig([string]$Original, [string]$DisplayMode) {
    $full = if ($DisplayMode -eq 'fullscreen') { 'Yes' } else { 'No' }
    $mode = if ($DisplayMode -eq 'fullscreen') { $FullscreenMode } else { $WindowedMode }
    $c = $Original -replace '(?m)^Render System=.*$', 'Render System=Direct3D11 Rendering Subsystem'
    $c = $c -replace '(?m)^Full Screen=.*$', "Full Screen=$full"
    $c = $c -replace '(?m)^Video Mode=.*$', "Video Mode=$mode"
    $c = $c -replace '(?m)^VSync=.*$', "VSync=$VSync"
    [IO.File]::WriteAllText($ogreCfg, $c)
}

function Get-GameProcess {
    Get-Process battlezone98redux -ErrorAction SilentlyContinue | Select-Object -First 1
}

function Test-GameForeground {
    $p = Get-GameProcess
    if (-not $p) { return $false }
    [uint32]$fgPid = 0
    [void][FlipAb.Native]::GetWindowThreadProcessId([FlipAb.Native]::GetForegroundWindow(), [ref]$fgPid)
    return $fgPid -eq $p.Id
}

function Send-SpaceIfForeground {
    # Space skips Redux's loading voice-over. Never send it anywhere but the game.
    if (-not (Test-GameForeground)) { return }
    [FlipAb.Native]::keybd_event(0x20, 0x39, 0, [UIntPtr]::Zero)
    [FlipAb.Native]::keybd_event(0x20, 0x39, 2, [UIntPtr]::Zero)
}

function Start-Game([string]$Arguments) {
    $environment = @(foreach ($e in [Environment]::GetEnvironmentVariables().GetEnumerator()) { '{0}={1}' -f $e.Key, $e.Value })
    $st = New-CimInstance -ClassName Win32_ProcessStartup -ClientOnly -Property @{
        ShowWindow = [uint16]$(if ($remote) { 4 } else { 1 }); EnvironmentVariables = [string[]]$environment }
    $r = Invoke-CimMethod -ClassName Win32_Process -MethodName Create -Arguments @{
        CommandLine = "`"$exe`" $Arguments"; CurrentDirectory = $GameRoot; ProcessStartupInformation = $st }
    if ($r.ReturnValue -ne 0) { throw "WMI launch failed ($($r.ReturnValue))" }
}

function Invoke-Run([string]$ScenarioName, [string]$DisplayMode, [string]$Arm, [int]$Rep, [string]$OgreOriginal) {
    $runId = '{0}_{1}_{2}_r{3}' -f $ScenarioName, $DisplayMode, $Arm, $Rep
    $runRoot = Join-Path $session $runId
    New-Item -ItemType Directory -Force $runRoot | Out-Null
    Write-Host "=== $runId"

    Set-RunOgreConfig $OgreOriginal $DisplayMode
    Get-ChildItem $logs -File -ErrorAction SilentlyContinue |
        Where-Object Name -Match '^openshim_(cpu_samples|frames|va)_' | Remove-Item -Force
    $env:OPENSHIM_PERF_TELEMETRY = '1'
    $env:OPENSHIM_PROFILE_NATIVE_CPU = $null
    $env:OPENSHIM_PROFILE_NATIVE_CPU_LABEL = $runId
    $env:OPENSHIM_DXGI_FLIP_MODEL = $(if ($Arm -eq 'flip') { '1' } else { '0' })

    if ($ScenarioName -eq 'lcbench') {
        Copy-Item -Path (Join-Path $lcbSource '*') -Destination $lcbRoot -Force
        [IO.File]::WriteAllText((Join-Path $lcbRoot 'lcbcfg.odf'), @"
[Benchmark]
scenario = "combat"
unitOdf = "avtank"
count = 40
distance = 50.0
orientation = "facing"
warmupSeconds = 6.0
measureSeconds = $LcbenchMeasureSeconds.0
"@)
        $arguments = 'lcbench.bzn'
        $timeout = 120 + $LcbenchMeasureSeconds
    } else {
        $arguments = 'crsetup.bzn /nointro'
        $timeout = 150 + $CrwxSeconds
    }

    $started = Get-Date
    Start-Game $arguments
    $simAt = $null; $endAt = $null; $done = $false; $pm = $null; $nextSpace = Get-Date
    $deadline = $started.AddSeconds($timeout)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 250
        $game = Get-GameProcess
        if (-not $game -and ((Get-Date) - $started).TotalSeconds -gt 20) { Write-Warning "$runId game exited early"; break }
        if (-not (Test-Path $bzLogger) -or (Get-Item $bzLogger).LastWriteTime -lt $started) { continue }
        $text = Read-SharedText $bzLogger
        if (-not $simAt -and $text -match 'Game Simulation Initialized') {
            $simAt = Get-Date
            if ($ScenarioName -eq 'crwx') { $endAt = $simAt.AddSeconds($CrwxSeconds) }
            if (-not $remote -and $game -and $game.MainWindowHandle -ne 0) {
                [void][FlipAb.Native]::SetForegroundWindow($game.MainWindowHandle)
            }
            if ($PresentMon -and $game) {
                $pm = Start-Process -FilePath $presentMonExe -WindowStyle Hidden -PassThru -ArgumentList @(
                    '--process_id', $game.Id, '--output_file', (Join-Path $runRoot 'presentmon.csv'),
                    '--no_console_stats', '--v1_metrics', '--terminate_on_proc_exit', '--session_name', "flipab_$($game.Id)")
            }
        }
        if ($text -match 'Waiting For VO' -and (Get-Date) -ge $nextSpace) {
            Send-SpaceIfForeground; $nextSpace = (Get-Date).AddMilliseconds(500)
        }
        if ($ScenarioName -eq 'lcbench' -and $text -match '\[LIVE_COMBAT_BENCH\].*benchmark-end') { $done = $true; break }
        if ($endAt -and (Get-Date) -ge $endAt) { $done = $true; break }
    }
    $foregroundAtEnd = Test-GameForeground
    $game = Get-GameProcess
    if ($game) { Stop-BZRGame -Id $game.Id }
    if ($pm) {
        Start-Process -FilePath $presentMonExe -WindowStyle Hidden -Wait -ArgumentList @(
            '--terminate_existing_session', '--session_name', "flipab_$($game.Id)") | Out-Null
        [void]$pm.WaitForExit(10000)
    }
    Start-Sleep -Seconds 2
    if (Get-GameProcess) { throw "$runId the game is still running after Stop-BZRGame; not launching another run" }

    [IO.File]::WriteAllText((Join-Path $runRoot 'BZLogger.txt'), (Read-SharedText $bzLogger))
    foreach ($n in 'openshim.log', 'exu.log') { if (Test-Path "$logs\$n") { Copy-Item "$logs\$n" $runRoot -Force } }
    foreach ($pair in @(@('openshim_frames_*.bin', 'frames.bin'), @('openshim_va_*.csv', 'va.csv'))) {
        $f = Get-ChildItem $logs -Filter $pair[0] -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($f) { Move-Item $f.FullName (Join-Path $runRoot $pair[1]) -Force } else { Write-Warning "$runId produced no $($pair[1])" }
    }

    $shim = Read-SharedText (Join-Path $runRoot 'openshim.log')
    $flipLine = ([regex]::Matches($shim, '\[DXGI Flip\] (active|kept|flip swap chain refused|could not|first present)[^\r\n]*') | ForEach-Object Value) -join ' || '
    $flipActive = $shim -match '\[DXGI Flip\] active'
    if ($Arm -eq 'flip' -and -not $flipActive) { Write-Warning "$runId flip arm did NOT engage: $flipLine" }
    if ($Arm -eq 'stock' -and $flipActive) { throw "$runId stock arm engaged flip model; the switch leaked" }

    $analysis = ''
    if (Test-Path (Join-Path $runRoot 'frames.bin')) {
        $analysis = (& python $analyzer (Join-Path $runRoot 'frames.bin') --skip-seconds $SkipSeconds 2>&1) -join "`n"
        [IO.File]::WriteAllText((Join-Path $runRoot 'analysis.txt'), $analysis)
    }
    $presentModes = ''
    $pmCsv = Join-Path $runRoot 'presentmon.csv'
    if (Test-Path $pmCsv) {
        $presentModes = (Import-Csv $pmCsv | Group-Object PresentMode | Sort-Object Count -Descending |
            ForEach-Object { '{0}:{1}' -f $_.Name, $_.Count }) -join ' '
    }
    $meta = [ordered]@{
        run = $runId; scenario = $ScenarioName; display = $DisplayMode; arm = $Arm; repeat = $Rep
        remote_session = $remote; vsync = $VSync
        video_mode = $(if ($DisplayMode -eq 'fullscreen') { $FullscreenMode } else { $WindowedMode })
        flip_active = $flipActive; flip_line = $flipLine; completed = $done
        foreground_at_end = $foregroundAtEnd; present_modes = $presentModes
        started = $started.ToString('o'); simulation = $(if ($simAt) { $simAt.ToString('o') } else { $null })
    }
    $meta | ConvertTo-Json | Set-Content (Join-Path $runRoot 'run.json')
    [pscustomobject]($meta + @{ analysis = $analysis })
}

function Get-Metric([string]$Analysis, [string]$Pattern) {
    $m = [regex]::Match($Analysis, $Pattern)
    if ($m.Success) { return $m.Groups[1].Value } else { return '-' }
}

$lock = Enter-BZRLaunchLock
$ogreOriginal = $null
$luaOriginal = $null
$priorEnv = @{}
$envNames = 'OPENSHIM_PERF_TELEMETRY', 'OPENSHIM_PROFILE_NATIVE_CPU', 'OPENSHIM_PROFILE_NATIVE_CPU_LABEL',
    'OPENSHIM_DXGI_FLIP_MODEL', 'OPENSHIM_NEVER_ACTIVATE', 'OPENSHIM_NEVER_CAPTURE_MOUSE', 'BZR_ALLOW_FOREGROUND_LAUNCH'
foreach ($n in $envNames) { $priorEnv[$n] = [Environment]::GetEnvironmentVariable($n, 'Process') }
$results = @()
try {
    if (Get-GameProcess) { throw 'Battlezone is already running; close it first (never force-kill).' }
    if (-not $SkipDeploy) {
        & (Join-Path $repoRoot 'scripts\Deploy-OpenShim.ps1') | Out-Null
        $want = (Get-FileHash (Join-Path $repoRoot 'bin\Release\plugins\openshim.dll')).Hash
        if ((Get-FileHash (Join-Path $GameRoot 'plugins\openshim.dll')).Hash -ne $want) { throw 'deployed openshim.dll does not match the build' }
        Write-Host "deployed openshim.dll $want"
    }
    if (-not $remote) {
        # Independent flip is granted only to the foreground window.
        $env:BZR_ALLOW_FOREGROUND_LAUNCH = '1'
        $env:OPENSHIM_NEVER_ACTIVATE = '0'
        $env:OPENSHIM_NEVER_CAPTURE_MOUSE = '0'
    }

    $ogreOriginal = [IO.File]::ReadAllText($ogreCfg)
    [IO.File]::WriteAllText($ogreBackup, $ogreOriginal)
    if ($Scenario -contains 'crwx') {
        $luaOriginal = [IO.File]::ReadAllBytes($crLua)
        Copy-Item -LiteralPath $crHarness -Destination $crLua -Force
    }
    New-Item -ItemType Directory -Force $lcbRoot | Out-Null

    foreach ($scen in $Scenario) {
        foreach ($disp in $Display) {
            for ($rep = 1; $rep -le $Repeat; $rep++) {
                # Alternate which arm goes first so warm caches favour neither.
                $order = if ($rep % 2 -eq 1) { $Arms } else { @($Arms)[($Arms.Count - 1)..0] }
                foreach ($arm in $order) { $results += Invoke-Run $scen $disp $arm $rep $ogreOriginal }
            }
        }
    }
} finally {
    if ($null -ne $ogreOriginal) {
        [IO.File]::WriteAllText($ogreCfg, $ogreOriginal)
        Remove-Item -LiteralPath $ogreBackup -Force -ErrorAction SilentlyContinue
    }
    if ($null -ne $luaOriginal) {
        [IO.File]::WriteAllBytes($crLua, $luaOriginal)
        $same = (Get-FileHash $crLua).Hash -eq ([BitConverter]::ToString(
            [Security.Cryptography.SHA256]::Create().ComputeHash($luaOriginal)) -replace '-', '')
        Write-Host "restored crsetup.lua byte-for-byte: $same"
    }
    $sourceCfg = Join-Path $lcbSource 'lcbcfg.odf'
    if (Test-Path $lcbRoot) { Copy-Item -LiteralPath $sourceCfg -Destination (Join-Path $lcbRoot 'lcbcfg.odf') -Force }
    foreach ($n in $envNames) { [Environment]::SetEnvironmentVariable($n, $priorEnv[$n], 'Process') }
    Exit-BZRLaunchLock $lock
}

$lines = @(
    "# Flip-model A/B $(Split-Path -Leaf $session)",
    '',
    "remote session: $remote; VSync=$VSync; windowed $WindowedMode; fullscreen $FullscreenMode; skip ${SkipSeconds}s",
    '',
    '| run | flip active | fps | p50 / p90 / p99 ms | pacing median abs dt delta | uneven pairs | present modes |',
    '|---|---|---|---|---|---|---|')
foreach ($r in $results) {
    $a = $r.analysis
    $lines += '| {0} | {1} | {2} | {3} / {4} / {5} | {6} ms | {7}% | {8} |' -f $r.run, $r.flip_active,
        (Get-Metric $a '([\d.]+) fps\)'), (Get-Metric $a 'p50=([\d.]+)'), (Get-Metric $a 'p90=([\d.]+)'),
        (Get-Metric $a 'p99=([\d.]+)'), (Get-Metric $a 'median \|dt\[i\]-dt\[i-1\]\|=([\d.]+)'),
        (Get-Metric $a 'uneven pairs=([\d.]+)'), $r.present_modes
}
$lines -join "`n" | Set-Content (Join-Path $session 'summary.md')
$lines -join "`n"
$session
