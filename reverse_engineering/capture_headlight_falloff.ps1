# Captures the player headlight's Ogre Light parameters and a burst of frames,
# so the hard bright/dark terrain terminator can be attributed to a specific
# light property instead of guessed at.
#
# The game is forced into a window for the duration: an exclusive-fullscreen
# swap chain is not readable with CopyFromScreen, so a fullscreen run produces
# black captures and no visual evidence at all. Ogre.cfg and openshim.ini are
# saved and restored around the run.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("DX11", "DX9")]
    [string]$Renderer = "DX9",
    # "stock" leaves HeadlightColor/HeadlightBeam unset so the run measures the
    # engine's own headlight; the others exercise the shim's overrides.
    [ValidateSet("stock", "white-wide", "white-focused", "off")]
    [string]$Headlight = "white-wide",
    # "on" is the shipped repair; "off" restores the pre-repair cone exponent
    # and leaves attenuation alone, which is the before half of the A/B.
    [ValidateSet("on", "off")]
    [string]$FalloffRepair = "on",
    [string]$Scenario = "quiet",
    [double]$SpinSeconds = 0.0,
    [double]$WarmupSeconds = 4.0,
    [double]$MeasureSeconds = 40.0,
    [int]$Frames = 12,
    [int]$FrameIntervalMs = 1200,
    [string]$OutputRoot = "",
    [string]$Label = ""
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Drawing

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\headlight_falloff"
}
if (-not $Label) {
    $Label = Get-Date -Format "yyyyMMdd_HHmmss"
}
$runRoot = Join-Path $OutputRoot ("{0}_{1}_{2}_repair-{3}" -f `
    $Label, $Renderer.ToLowerInvariant(), $Headlight, $FalloffRepair)
New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$ogreConfig = Join-Path $GameRoot "Ogre.cfg"
$shimIni = Join-Path $GameRoot "openshim.ini"
$missionSourceRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$missionConfig = Join-Path $missionRoot "lcbcfg.odf"
$shimLog = Join-Path $GameRoot "logs\openshim.log"

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath $ogreConfig)) { throw "Ogre.cfg not found: $ogreConfig" }

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class BzHeadlightWin {
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$originalShimIni = if (Test-Path -LiteralPath $shimIni) {
    [System.IO.File]::ReadAllText($shimIni)
} else { $null }
$originalMissionConfig = if (Test-Path -LiteralPath $missionConfig) {
    [System.IO.File]::ReadAllText($missionConfig)
} else { $null }

try {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force
    Start-Sleep -Seconds 2

    $renderSystem = if ($Renderer -eq "DX9") {
        "Direct3D9 Rendering Subsystem"
    } else {
        "Direct3D11 Rendering Subsystem"
    }
    $config = $originalOgreConfig -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
    $config = $config -replace '(?m)^Full Screen=Yes$', 'Full Screen=No'
    $config = $config -replace '(?m)^VSync=Yes$', 'VSync=No'
    # 1920x1080 is four digits in both dimensions, so it round-trips through
    # D3D9's "%4d x %4d" mode description and D3D11's unpadded one identically.
    # MSAA is dropped: D3D9 rejects a windowed 8x MSAA swap chain on this
    # adapter and throws out of RenderSystem_Direct3D9 before the first frame.
    $config = $config -replace '(?m)^Video Mode=.*@ 32-bit colour$', 'Video Mode=1920 x 1080 @ 32-bit colour'
    $config = $config -replace '(?m)^FSAA=.*$', 'FSAA=0'
    [System.IO.File]::WriteAllText($ogreConfig, $config)

    # Deterministic single-player headlight config plus the light probe.
    $headlightBlock = switch ($Headlight) {
        "stock"         { "Headlights = 1" }
        "white-wide"    { "Headlights = 1`r`nHeadlightColor = White`r`nHeadlightBeam = Wide" }
        "white-focused" { "Headlights = 1`r`nHeadlightColor = White`r`nHeadlightBeam = Focused" }
        "off"           { "Headlights = 0" }
    }
    [System.IO.File]::WriteAllText($shimIni, @"
[SinglePlayer]
$headlightBlock
OtherHeadlights = 0

HeadlightFalloffRepair = $(if ($FalloffRepair -eq "on") { 1 } else { 0 })

[Diagnostics]
HeadlightLightTrace = 1
"@)

    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "$Scenario"
unitOdf = "avtank"
count = 0
distance = 50.0
orientation = "facing"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = $($MeasureSeconds.ToString("0.0###", $invariant))
clusterCount = 4
clusterRadius = 300.0
spinSeconds = $($SpinSeconds.ToString("0.0###", $invariant))
"@)

    # The previous run's process can still hold the log open for a moment after
    # Stop-Process returns; a stale log is far less bad than a failed run, so
    # truncation is best-effort and the run continues either way.
    if (Test-Path -LiteralPath $shimLog) {
        try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop }
        catch {
            Start-Sleep -Seconds 3
            try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { }
        }
    }

    $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
        -WorkingDirectory $GameRoot -PassThru

    $handle = [IntPtr]::Zero
    $deadline = (Get-Date).AddSeconds(60)
    while ((Get-Date) -lt $deadline) {
        $process.Refresh()
        if ($process.HasExited) { throw "Game exited before a window appeared" }
        if ($process.MainWindowHandle -ne [IntPtr]::Zero) {
            $handle = $process.MainWindowHandle
            break
        }
        Start-Sleep -Milliseconds 250
    }
    if ($handle -eq [IntPtr]::Zero) { throw "No game window appeared within 60s" }

    Start-Sleep -Seconds ([int][math]::Ceiling($WarmupSeconds + 8))
    [void][BzHeadlightWin]::SetForegroundWindow($handle)
    Start-Sleep -Milliseconds 750

    $captured = 0
    for ($index = 0; $index -lt $Frames; $index++) {
        $process.Refresh()
        if ($process.HasExited) { break }
        $rect = New-Object BzHeadlightWin+RECT
        if (-not [BzHeadlightWin]::GetClientRect($handle, [ref]$rect)) { break }
        $origin = New-Object BzHeadlightWin+POINT
        [void][BzHeadlightWin]::ClientToScreen($handle, [ref]$origin)
        $width = $rect.Right - $rect.Left
        $height = $rect.Bottom - $rect.Top
        if ($width -le 0 -or $height -le 0) { break }

        $bitmap = New-Object System.Drawing.Bitmap $width, $height
        $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
        $graphics.CopyFromScreen(
            (New-Object System.Drawing.Point $origin.X, $origin.Y),
            [System.Drawing.Point]::Empty,
            (New-Object System.Drawing.Size $width, $height))
        $bitmap.Save((Join-Path $runRoot ("frame_{0:d3}.png" -f $index)))
        $graphics.Dispose()
        $bitmap.Dispose()
        $captured++
        Start-Sleep -Milliseconds $FrameIntervalMs
    }

    $process.Refresh()
    if (-not $process.HasExited) {
        $process.WaitForExit(25000) | Out-Null
    }
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force

    if (Test-Path -LiteralPath $shimLog) {
        Copy-Item -LiteralPath $shimLog -Destination (Join-Path $runRoot "openshim.log") -Force
        Select-String -LiteralPath $shimLog -Pattern "HEADLIGHT" |
            ForEach-Object { $_.Line } |
            Set-Content -LiteralPath (Join-Path $runRoot "headlight_probe.txt")
    }
    Write-Host "Captured $captured frame(s) to $runRoot"
}
finally {
    [System.IO.File]::WriteAllText($ogreConfig, $originalOgreConfig)
    if ($null -ne $originalShimIni) {
        [System.IO.File]::WriteAllText($shimIni, $originalShimIni)
    }
    if ($null -ne $originalMissionConfig) {
        [System.IO.File]::WriteAllText($missionConfig, $originalMissionConfig)
    }
}

$runRoot
