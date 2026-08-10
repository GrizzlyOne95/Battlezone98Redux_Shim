<#
.SYNOPSIS
    Correlated capture harness for the Phase 3A terrain semantic renderer.

.DESCRIPTION
    Runs the same mission several times, once per rendering mode, with an
    identical launch and input timeline, and captures the game window at fixed
    offsets from the first simulated frame. Companion script
    Compare-TerrainCaptures.ps1 turns the captures into RGB difference metrics.

    Modes (see Docs/terrain-render-path.md):
      stock        proxy disabled entirely  - stock terrain only
      packed       proxy enabled, semantic renderer OFF - the proxy renders
                   through the stock packed-UV material. This is the legacy
                   packed-UV reference for parity.
      quantized    proxy + semantic renderer, legacy UV quantization ON
      unquantized  proxy + semantic renderer, legacy UV quantization OFF
      uvdelta      quantized + TerrainSemanticDebug=7. The terrain is shaded by
                   |semanticUV - stockPackedUV|, so a black cluster is an
                   in-frame, per-pixel parity proof that needs no correlation
                   between separate runs.

    LIMITATION: separate runs are separate frames. Even with an identical input
    timeline the captures are only approximately correlated, so lighting
    animation, particles, HUD and unit motion all register as differences. Use
    -Region to restrict metrics to terrain, and prefer the uvdelta mode when an
    exact answer is required.

.EXAMPLE
    .\Test-TerrainSemanticParity.ps1 -Modes packed,quantized -Mission "misn04.bzn" `
        -DeployShim -KillExistingGame
#>
[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$Mission = "misn04.bzn",
    [string]$ExtraArgs = "-renderer:dx11",
    [ValidateSet("stock", "packed", "quantized", "unquantized", "uvdelta")]
    [string[]]$Modes = @("packed", "quantized"),
    [int[]]$CaptureOffsetsMs = @(3000, 6000),
    [int]$RunTimeoutSeconds = 120,
    [int]$MainWindowTimeoutSeconds = 30,
    [int]$SimReadyTimeoutSeconds = 90,
    [string]$ProxySelector = "",
    [double[]]$ProxyOffset = @(0.0, 0.0, 0.0),
    [switch]$MotionSweep,
    [string]$MotionKey = "W",
    [int]$MotionDurationMs = 6000,
    [int]$MotionCaptureIntervalMs = 1000,
    [string]$Region = "",
    [int]$FrameCaptures = 3,
    [int]$FrameCaptureStride = 300,
    [switch]$DeployShim,
    [switch]$KillExistingGame,
    [switch]$SkipCompare
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
using System.Text;

public static class OpenShimParityNative
{
    public const int SW_RESTORE = 9;
    public const uint KEYEVENTF_KEYUP = 0x0002;
    public const uint INPUT_KEYBOARD = 1;

    [StructLayout(LayoutKind.Sequential)]
    public struct RECT { public int Left; public int Top; public int Right; public int Bottom; }

    [StructLayout(LayoutKind.Sequential)]
    public struct KEYBDINPUT
    {
        public ushort wVk; public ushort wScan; public uint dwFlags;
        public uint time; public IntPtr dwExtraInfo;
    }

    [StructLayout(LayoutKind.Explicit)]
    public struct InputUnion { [FieldOffset(0)] public KEYBDINPUT ki; }

    [StructLayout(LayoutKind.Sequential)]
    public struct INPUT { public uint type; public InputUnion U; }

    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
    [DllImport("user32.dll", SetLastError = true)]
    private static extern uint SendInput(uint nInputs, INPUT[] pInputs, int cbSize);

    public static bool SendKey(ushort virtualKey, bool keyUp)
    {
        INPUT[] inputs = new INPUT[1];
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].U.ki.wVk = virtualKey;
        inputs[0].U.ki.dwFlags = keyUp ? KEYEVENTF_KEYUP : 0u;
        return SendInput(1, inputs, Marshal.SizeOf(typeof(INPUT))) == 1;
    }

    [DllImport("kernel32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
    public static extern bool WritePrivateProfileStringA(string section, string key, string value, string file);
}
"@

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
if (-not (Test-Path $gameExe)) { throw "Game executable not found: $gameExe" }

$repoRoot = Split-Path -Parent $PSScriptRoot
$iniPath = Join-Path $GameRoot "openshim.ini"
$iniBackup = "$iniPath.parity-backup"
$shimSource = Join-Path $repoRoot "bin\Release\winmm.dll"
$bzLogger = Join-Path $GameRoot "logs\BZLogger.txt"
$shimLog = Join-Path $GameRoot "logs\openshim.log"
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$seriesRoot = Join-Path $repoRoot "reverse_engineering\snapshots\terrain_parity_$stamp"
New-Item -ItemType Directory -Path $seriesRoot -Force | Out-Null

# ---------------------------------------------------------------- helpers ----

# Rewrite the whole [Terrain] section as text. The profile API caches writes,
# which produced runs that silently used the previous mode's settings.
function Set-TerrainSection {
    param([System.Collections.IDictionary]$Settings)

    $existing = @()
    if (Test-Path $iniPath) { $existing = Get-Content -LiteralPath $iniPath }
    $out = New-Object System.Collections.Generic.List[string]
    $inTerrain = $false
    foreach ($line in $existing) {
        if ($line -match '^\s*\[(.+)\]\s*$') {
            $inTerrain = ($Matches[1] -ieq 'Terrain')
            if ($inTerrain) { continue }
        }
        if (-not $inTerrain) { $out.Add($line) }
    }
    $out.Add("[Terrain]")
    foreach ($key in $Settings.Keys) { $out.Add("$key = $($Settings[$key])") }
    Set-Content -LiteralPath $iniPath -Value $out -Encoding ASCII
}

function Get-ModeSettings {
    param([string]$Mode)
    $settings = [ordered]@{
        TerrainProxyEnabled                 = "0"
        TerrainProxyVisible                 = "1"
        TerrainSemanticRenderer             = "0"
        TerrainSemanticValidateUV           = "0"
        TerrainSemanticLegacyUVQuantization = "1"
        TerrainSemanticDebug                = "0"
        TerrainSemanticLifecycleLog         = "1"
        TerrainSemanticFrameCapture         = "$FrameCaptures"
        TerrainSemanticFrameCaptureStride   = "$FrameCaptureStride"
        TerrainProxyOffsetX                 = ("{0:0.###}" -f $ProxyOffset[0])
        TerrainProxyOffsetY                 = ("{0:0.###}" -f $ProxyOffset[1])
        TerrainProxyOffsetZ                 = ("{0:0.###}" -f $ProxyOffset[2])
    }
    switch ($Mode) {
        "stock" { }
        "packed" {
            $settings.TerrainProxyEnabled = "1"
        }
        "quantized" {
            $settings.TerrainProxyEnabled = "1"
            $settings.TerrainSemanticRenderer = "1"
            $settings.TerrainSemanticValidateUV = "1"
        }
        "unquantized" {
            $settings.TerrainProxyEnabled = "1"
            $settings.TerrainSemanticRenderer = "1"
            $settings.TerrainSemanticValidateUV = "1"
            $settings.TerrainSemanticLegacyUVQuantization = "0"
        }
        "uvdelta" {
            $settings.TerrainProxyEnabled = "1"
            $settings.TerrainSemanticRenderer = "1"
            $settings.TerrainSemanticValidateUV = "1"
            $settings.TerrainSemanticDebug = "7"
        }
    }
    return $settings
}

function Get-FileLengthOrZero {
    param([string]$Path)
    if (-not (Test-Path $Path)) { return 0L }
    try { return (Get-Item -LiteralPath $Path).Length } catch { return 0L }
}

function Get-LinesAfterOffset {
    param([string]$Path, [long]$StartOffset)
    if (-not (Test-Path $Path)) { return @() }
    try {
        $stream = [System.IO.File]::Open($Path, [System.IO.FileMode]::Open,
            [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite)
        try {
            if ($StartOffset -gt $stream.Length) { $StartOffset = 0L }
            [void]$stream.Seek($StartOffset, [System.IO.SeekOrigin]::Begin)
            $reader = New-Object System.IO.StreamReader($stream)
            try { return $reader.ReadToEnd() -split "`r?`n" } finally { $reader.Dispose() }
        }
        finally { $stream.Dispose() }
    }
    catch { return @() }
}

function Wait-ForMainWindow {
    param([System.Diagnostics.Process]$Process, [int]$TimeoutSeconds)
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    while ((Get-Date) -lt $deadline) {
        if ($Process.HasExited) { return $false }
        $Process.Refresh()
        if ($Process.MainWindowHandle -ne 0) { return $true }
        Start-Sleep -Milliseconds 200
    }
    return $false
}

function Set-GameForeground {
    param([System.Diagnostics.Process]$Process)
    try {
        $Process.Refresh()
        if ($Process.HasExited -or $Process.MainWindowHandle -eq 0) { return $false }
        [void][OpenShimParityNative]::ShowWindow($Process.MainWindowHandle, [OpenShimParityNative]::SW_RESTORE)
        [void][OpenShimParityNative]::BringWindowToTop($Process.MainWindowHandle)
        [void][OpenShimParityNative]::SetForegroundWindow($Process.MainWindowHandle)
        Start-Sleep -Milliseconds 120
        return $true
    }
    catch { return $false }
}

function Save-WindowCapture {
    param([System.Diagnostics.Process]$Process, [string]$OutPath)
    $Process.Refresh()
    if ($Process.HasExited -or $Process.MainWindowHandle -eq 0) { return $false }
    $rect = New-Object OpenShimParityNative+RECT
    if (-not [OpenShimParityNative]::GetWindowRect($Process.MainWindowHandle, [ref]$rect)) { return $false }
    $width = [Math]::Max(1, $rect.Right - $rect.Left)
    $height = [Math]::Max(1, $rect.Bottom - $rect.Top)
    $bitmap = New-Object System.Drawing.Bitmap $width, $height
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    try {
        $graphics.CopyFromScreen($rect.Left, $rect.Top, 0, 0, $bitmap.Size)
        $bitmap.Save($OutPath, [System.Drawing.Imaging.ImageFormat]::Png)
        return $true
    }
    finally { $graphics.Dispose(); $bitmap.Dispose() }
}

function Wait-ForSimulationReady {
    param(
        [System.Diagnostics.Process]$Process,
        [long]$LogOffset,
        [int]$TimeoutSeconds
    )
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    $offset = $LogOffset
    while ((Get-Date) -lt $deadline) {
        if ($Process.HasExited) { return $null }
        $length = Get-FileLengthOrZero -Path $bzLogger
        $lines = Get-LinesAfterOffset -Path $bzLogger -StartOffset $offset
        $offset = $length
        foreach ($line in $lines) {
            # 'Sim Startup: Waiting For VO' is NOT a prompt for input. This
            # used to send SPACE to skip the briefing; SPACE is a bound live
            # gameplay action (self-destruct/eject) and ended the mission about
            # 190 ms after the first frame, so every automated series measured a
            # mission that had already terminated. The correct action here is to
            # do nothing and let the VO finish. Do not substitute another key
            # unless a UI-state-specific mechanism proves one is required.
            if ($line -match 'Sim Startup: First Frame after' -or
                $line -match 'Game Simulation Initialized after') {
                return (Get-Date)
            }
        }
        Start-Sleep -Milliseconds 150
    }
    return $null
}

function Get-VirtualKeyCode {
    param([string]$Key)
    $upper = $Key.ToUpperInvariant()
    if ($upper.Length -eq 1 -and $upper -match '[A-Z0-9]') {
        return [ushort][char]$upper
    }
    throw "MotionKey must be a single letter or digit; got '$Key'"
}

# ------------------------------------------------------------------- run -----

if (Test-Path $iniPath) {
    Copy-Item -LiteralPath $iniPath -Destination $iniBackup -Force
}
else {
    Set-Content -LiteralPath $iniPath -Value "[Terrain]" -Encoding ASCII
}

if ($DeployShim) {
    if (-not (Test-Path $shimSource)) { throw "Shim not built: $shimSource" }
    Get-Process battlezone98redux -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Seconds 3
    $shimTarget = Join-Path $GameRoot "winmm.dll"
    Copy-Item -LiteralPath $shimSource -Destination $shimTarget -Force
    # The running game locks winmm.dll, and Campaign Reimagined queues its own
    # OpenShim replacement for the next launch. Both can silently leave a stale
    # DLL in place, which invalidates an entire measurement series, so verify.
    $expected = (Get-FileHash -LiteralPath $shimSource).Hash
    $actual = (Get-FileHash -LiteralPath $shimTarget).Hash
    if ($expected -ne $actual) {
        throw "Deployed winmm.dll does not match the build ($actual != $expected). Close the game and any Campaign Reimagined updater, then retry."
    }
    Write-Host "Deployed shim verified: $expected"
}

$runs = @()
try {
    foreach ($mode in $Modes) {
        if ($KillExistingGame) {
            Get-Process battlezone98redux -ErrorAction SilentlyContinue | Stop-Process -Force
            Start-Sleep -Seconds 2
        }

        $modeRoot = Join-Path $seriesRoot $mode
        New-Item -ItemType Directory -Path $modeRoot -Force | Out-Null

        $settings = Get-ModeSettings -Mode $mode
        if ($ProxySelector) {
            foreach ($pair in $ProxySelector.Split(";")) {
                if (-not $pair) { continue }
                $parts = $pair.Split("=")
                if ($parts.Count -eq 2) { $settings[$parts[0].Trim()] = $parts[1].Trim() }
            }
        }
        Set-TerrainSection -Settings $settings
        Copy-Item -LiteralPath $iniPath -Destination (Join-Path $modeRoot "openshim.ini") -Force

        # In-process captures land beside the executable. Nothing in the game
        # directory is deleted; a run is only credited with files it wrote
        # after this point.
        $runStartedAt = Get-Date

        $preShim = Get-FileLengthOrZero -Path $shimLog
        $preBz = Get-FileLengthOrZero -Path $bzLogger

        $arguments = @($Mission)
        if ($ExtraArgs) { $arguments += $ExtraArgs.Split(" ") }
        $process = Start-Process -FilePath $gameExe -ArgumentList $arguments `
            -WorkingDirectory $GameRoot -PassThru
        $runDeadline = (Get-Date).AddSeconds($RunTimeoutSeconds)

        $windowReady = Wait-ForMainWindow -Process $process -TimeoutSeconds $MainWindowTimeoutSeconds
        $simReadyAt = $null
        if ($windowReady) {
            $simReadyAt = Wait-ForSimulationReady -Process $process -LogOffset $preBz `
                -TimeoutSeconds $SimReadyTimeoutSeconds
        }

        $captures = @()
        if ($simReadyAt) {
            [void](Set-GameForeground -Process $process)
            foreach ($offset in ($CaptureOffsetsMs | Sort-Object)) {
                $target = $simReadyAt.AddMilliseconds($offset)
                while ((Get-Date) -lt $target -and -not $process.HasExited -and (Get-Date) -lt $runDeadline) {
                    Start-Sleep -Milliseconds 25
                }
                if ($process.HasExited) { break }
                $shot = Join-Path $modeRoot ("frame_{0:00000}ms.png" -f $offset)
                if (Save-WindowCapture -Process $process -OutPath $shot) { $captures += $shot }
            }

            if ($MotionSweep -and -not $process.HasExited) {
                $key = Get-VirtualKeyCode -Key $MotionKey
                [void](Set-GameForeground -Process $process)
                $motionStart = Get-Date
                [void][OpenShimParityNative]::SendKey($key, $false)
                try {
                    $captureAt = $MotionCaptureIntervalMs
                    while ($captureAt -le $MotionDurationMs) {
                        $target = $motionStart.AddMilliseconds($captureAt)
                        while ((Get-Date) -lt $target -and -not $process.HasExited) {
                            Start-Sleep -Milliseconds 20
                        }
                        if ($process.HasExited) { break }
                        $shot = Join-Path $modeRoot ("motion_{0:00000}ms.png" -f $captureAt)
                        if (Save-WindowCapture -Process $process -OutPath $shot) { $captures += $shot }
                        $captureAt += $MotionCaptureIntervalMs
                    }
                }
                finally {
                    [void][OpenShimParityNative]::SendKey($key, $true)
                }
            }
        }

        $exitedNaturally = $false
        $process.Refresh()
        if ($process.HasExited) { $exitedNaturally = $true }
        else { Stop-Process -Id $process.Id -Force; Start-Sleep -Milliseconds 400 }

        # Collect the deterministic in-process captures. Names are normalized
        # so the same dispatch index pairs across modes.
        $engineCaptures = @()
        $engineRoot = Join-Path $modeRoot "engine"
        $produced = @(Get-ChildItem -LiteralPath $GameRoot -Filter "terrain_semantic_frame_*.png" `
            -ErrorAction SilentlyContinue |
            Where-Object { $_.LastWriteTime -gt $runStartedAt } | Sort-Object Name)
        if ($produced.Count -gt 0) {
            New-Item -ItemType Directory -Path $engineRoot -Force | Out-Null
            foreach ($file in $produced) {
                $index = 0
                if ($file.BaseName -match '_(\d+)$') { $index = [int]$Matches[1] }
                $target = Join-Path $engineRoot ("capture_{0:00}.png" -f $index)
                Copy-Item -LiteralPath $file.FullName -Destination $target -Force
                $engineCaptures += $target
            }
        }

        $shimSlice = Get-LinesAfterOffset -Path $shimLog -StartOffset $preShim
        $slicePath = Join-Path $modeRoot "openshim.slice.log"
        [System.IO.File]::WriteAllLines($slicePath, [string[]]$shimSlice)

        $terrainLines = @($shimSlice | Where-Object { $_ -match 'TERRAIN-P3|TERRAIN-PROXY' })
        $uvLine = @($terrainLines | Where-Object { $_ -match 'TERRAIN-P3-UV\] checked=' }) | Select-Object -Last 1
        $shaderLine = @($terrainLines | Where-Object { $_ -match 'terrain_semantic_shader: material=' }) | Select-Object -Last 1

        $runs += [pscustomobject][ordered]@{
            mode              = $mode
            pid               = $process.Id
            window_ready      = $windowReady
            sim_ready         = [bool]$simReadyAt
            exited_naturally  = $exitedNaturally
            captures          = $captures
            capture_directory = $modeRoot
            engine_captures   = $engineCaptures
            engine_directory  = if ($engineCaptures.Count -gt 0) { $engineRoot } else { "" }
            slice             = $slicePath
            terrain_log_lines = $terrainLines.Count
            uv_validation     = $uvLine
            shader_summary    = $shaderLine
        }
    }
}
finally {
    if (Test-Path $iniBackup) {
        Copy-Item -LiteralPath $iniBackup -Destination $iniPath -Force
        Remove-Item -LiteralPath $iniBackup -Force
    }
}

$comparisons = @()
if (-not $SkipCompare -and $runs.Count -ge 2) {
    $comparer = Join-Path $PSScriptRoot "Compare-TerrainCaptures.ps1"
    for ($i = 1; $i -lt $runs.Count; $i++) {
        $reference = $runs[0]
        $candidate = $runs[$i]
        # Prefer the engine captures: they are taken at the same terrain
        # dispatch index in both runs, so they are genuinely correlated.
        # Desktop captures are only wall-clock aligned.
        $pairs = @()
        if ($reference.engine_directory -and $candidate.engine_directory) {
            $pairs += @{ kind = "engine"; ref = $reference.engine_directory; cand = $candidate.engine_directory }
        }
        if ($reference.captures -and $candidate.captures) {
            $pairs += @{ kind = "desktop"; ref = $reference.capture_directory; cand = $candidate.capture_directory }
        }
        foreach ($pair in $pairs) {
            $diffRoot = Join-Path $seriesRoot `
                ("diff_" + $pair.kind + "_" + $reference.mode + "_vs_" + $candidate.mode)
            $json = & $comparer -Reference $pair.ref -Candidate $pair.cand `
                -OutputDirectory $diffRoot -Region $Region 2>$null | Select-Object -Last 1
            $comparisons += [pscustomobject]@{
                kind      = $pair.kind
                reference = $reference.mode
                candidate = $candidate.mode
                output    = $diffRoot
                metrics   = $json
            }
        }
    }
}

$summary = [ordered]@{
    captured_at        = (Get-Date).ToString("o")
    game_root          = $GameRoot
    mission            = $Mission
    extra_args         = $ExtraArgs
    modes              = $Modes
    capture_offsets_ms = $CaptureOffsetsMs
    motion_sweep       = [bool]$MotionSweep
    motion_key         = $MotionKey
    region             = $Region
    series_root        = $seriesRoot
    runs               = $runs
    comparisons        = $comparisons
}
$summaryPath = Join-Path $seriesRoot "series_summary.json"
$summary | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $summaryPath -Encoding ASCII
Write-Host "Series written to $seriesRoot"
$summary | ConvertTo-Json -Depth 8
