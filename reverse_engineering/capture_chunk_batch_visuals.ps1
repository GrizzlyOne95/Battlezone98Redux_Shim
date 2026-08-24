# Captures frames during *active* chunk spawning, movement and expiry, with the
# generic chunk batch's state-version reuse enabled and disabled.
#
# Capturing after the debris settles would prove nothing: a cache trivially
# matches a static scene. The dispersed firing scenario keeps chunklets being
# created and expiring for the whole capture window, so a stale-cache bug shows
# up as debris that lags, freezes, or lingers a frame past its lifetime.
#
# The game is forced into a window: an exclusive-fullscreen swap chain is not
# readable with CopyFromScreen. Ogre.cfg is saved and restored around the run.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("DX11", "DX9")]
    [string]$Renderer = "DX11",
    [ValidateSet("reuse", "rebuild")]
    [string]$Mode = "reuse",
    [string]$Scenario = "dispersed",
    [int]$Count = 20,
    [double]$SpinSeconds = 0.0,
    [double]$WarmupSeconds = 5.0,
    [double]$MeasureSeconds = 35.0,
    [int]$Frames = 24,
    [int]$FrameIntervalMs = 400,
    [string]$OutputRoot = "",
    [string]$Label = ""
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Drawing

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\chunk_batch_visuals"
}
if (-not $Label) {
    $Label = Get-Date -Format "yyyyMMdd_HHmmss"
}
$runRoot = Join-Path $OutputRoot ("{0}_{1}_{2}_{3:d3}" -f `
    $Label, $Renderer.ToLowerInvariant(), $Mode, $Count)
New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$ogreConfig = Join-Path $GameRoot "Ogre.cfg"
$missionSourceRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$missionConfig = Join-Path $missionRoot "lcbcfg.odf"
$shimLog = Join-Path $GameRoot "logs\openshim.log"

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class BzChunkWin {
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

$ownedVariables = @(
    "OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS",
    "OPENSHIM_DISABLE_CHUNK_BATCH_REUSE")
$priorValues = @{}
foreach ($name in $ownedVariables) {
    $priorValues[$name] = [Environment]::GetEnvironmentVariable($name, "Process")
}
$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$originalMissionConfig = if (Test-Path -LiteralPath $missionConfig) {
    [System.IO.File]::ReadAllText($missionConfig)
} else { $null }

try {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Seconds 2

    $renderSystem = if ($Renderer -eq "DX9") {
        "Direct3D9 Rendering Subsystem"
    } else {
        "Direct3D11 Rendering Subsystem"
    }
    $config = $originalOgreConfig -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
    $config = $config -replace '(?m)^Full Screen=Yes$', 'Full Screen=No'
    $config = $config -replace '(?m)^VSync=Yes$', 'VSync=No'
    $config = $config -replace '(?m)^Video Mode=.*@ 32-bit colour$', 'Video Mode=1920 x 1080 @ 32-bit colour'
    $config = $config -replace '(?m)^FSAA=.*$', 'FSAA=0'
    [System.IO.File]::WriteAllText($ogreConfig, $config)

    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "$Scenario"
unitOdf = "avtank"
count = $($Count.ToString($invariant))
distance = 50.0
orientation = "facing"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = $($MeasureSeconds.ToString("0.0###", $invariant))
clusterCount = 4
clusterRadius = 300.0
spinSeconds = $($SpinSeconds.ToString("0.0###", $invariant))
"@)

    foreach ($name in $ownedVariables) {
        [Environment]::SetEnvironmentVariable($name, $null, "Process")
    }
    [Environment]::SetEnvironmentVariable("OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS", "1", "Process")
    if ($Mode -eq "rebuild") {
        [Environment]::SetEnvironmentVariable("OPENSHIM_DISABLE_CHUNK_BATCH_REUSE", "1", "Process")
    }

    if (Test-Path -LiteralPath $shimLog) {
        try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop }
        catch { Start-Sleep -Seconds 3; try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { } }
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

    # Start capturing as soon as the spawner has finished, so the frames land
    # while chunks are still being created and destroyed rather than after.
    Start-Sleep -Seconds ([int][math]::Ceiling($WarmupSeconds + 7))
    [void][BzChunkWin]::SetForegroundWindow($handle)
    Start-Sleep -Milliseconds 500

    $captured = 0
    for ($index = 0; $index -lt $Frames; $index++) {
        $process.Refresh()
        if ($process.HasExited) { break }
        $rect = New-Object BzChunkWin+RECT
        if (-not [BzChunkWin]::GetClientRect($handle, [ref]$rect)) { break }
        $origin = New-Object BzChunkWin+POINT
        [void][BzChunkWin]::ClientToScreen($handle, [ref]$origin)
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
    if (-not $process.HasExited) { $process.WaitForExit(25000) | Out-Null }
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue | Stop-Process -Force

    if (Test-Path -LiteralPath $shimLog) {
        Copy-Item -LiteralPath $shimLog -Destination (Join-Path $runRoot "openshim.log") -Force
    }
    Write-Host "Captured $captured frame(s) to $runRoot"
}
finally {
    [System.IO.File]::WriteAllText($ogreConfig, $originalOgreConfig)
    if ($null -ne $originalMissionConfig) {
        [System.IO.File]::WriteAllText($missionConfig, $originalMissionConfig)
    }
    foreach ($name in $ownedVariables) {
        [Environment]::SetEnvironmentVariable($name, $priorValues[$name], "Process")
    }
}

$runRoot
