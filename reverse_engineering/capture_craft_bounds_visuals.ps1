# Captures a deterministic burst of game frames under a chosen craft-bounds
# mode, so stock and restored bounds can be compared frame for frame.
#
# The game is forced into a window for the duration: an exclusive-fullscreen
# swap chain is not readable with CopyFromScreen or PrintWindow, which is why
# the PR #47 pass failed to produce any visual evidence at all. Ogre.cfg is
# saved and restored around the run.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("stock", "private", "restore")]
    [string]$Mode = "restore",
    [ValidateSet("DX11", "DX9")]
    [string]$Renderer = "DX11",
    [string]$Scenario = "dispersed",
    [string]$UnitOdf = "avtank",
    [int]$Count = 40,
    [double]$Distance = 50.0,
    [string]$Orientation = "facing",
    [double]$SpinSeconds = 1.5,
    [double]$WarmupSeconds = 6.0,
    [double]$MeasureSeconds = 30.0,
    [int]$Frames = 40,
    [int]$FrameIntervalMs = 500,
    [double]$RestoreScale = 2.0,
    [string]$OutputRoot = "",
    [string]$Label = ""
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Drawing

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\craft_bounds_visuals"
}
if (-not $Label) {
    $Label = Get-Date -Format "yyyyMMdd_HHmmss"
}
$runRoot = Join-Path $OutputRoot ("{0}_{1}_{2}_{3}_{4:d3}_{5}" -f `
    $Label, $Mode, $Renderer.ToLowerInvariant(), $UnitOdf, $Count, $Orientation)
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
public static class BzWin {
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$originalMissionConfig = if (Test-Path -LiteralPath $missionConfig) {
    [System.IO.File]::ReadAllText($missionConfig)
} else { $null }

$ownedVariables = @(
    "OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING",
    "OPENSHIM_RESTORE_CRAFT_BOUNDS",
    "OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE",
    "OPENSHIM_PROFILE_OGRE_ANIMATION")
$priorValues = @{}
foreach ($name in $ownedVariables) {
    $priorValues[$name] = [Environment]::GetEnvironmentVariable($name, "Process")
}

try {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force

    # Windowed, and small enough that the whole client area fits on screen.
    $renderSystem = if ($Renderer -eq "DX9") {
        "Direct3D9 Rendering Subsystem"
    } else {
        "Direct3D11 Rendering Subsystem"
    }
    $config = $originalOgreConfig -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
    $config = $config -replace '(?m)^Full Screen=Yes$', 'Full Screen=No'
    $config = $config -replace '(?m)^VSync=Yes$', 'VSync=No'
    $config = $config -replace '(?m)^Video Mode=.*$', 'Video Mode=1600 x  900 @ 32-bit colour'
    [System.IO.File]::WriteAllText($ogreConfig, $config)

    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "$Scenario"
unitOdf = "$UnitOdf"
count = $($Count.ToString($invariant))
distance = $($Distance.ToString("0.0###", $invariant))
orientation = "$Orientation"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = $($MeasureSeconds.ToString("0.0###", $invariant))
clusterCount = 4
clusterRadius = 300.0
spinSeconds = $($SpinSeconds.ToString("0.0###", $invariant))
"@)

    foreach ($name in $ownedVariables) {
        [Environment]::SetEnvironmentVariable($name, $null, "Process")
    }
    switch ($Mode) {
        "stock" {
            [Environment]::SetEnvironmentVariable(
                "OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING", "1", "Process")
        }
        "private" { }
        "restore" {
            [Environment]::SetEnvironmentVariable(
                "OPENSHIM_RESTORE_CRAFT_BOUNDS", "1", "Process")
            [Environment]::SetEnvironmentVariable(
                "OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE",
                $RestoreScale.ToString("0.00", $invariant), "Process")
        }
    }
    [Environment]::SetEnvironmentVariable("OPENSHIM_PROFILE_OGRE_ANIMATION", "1", "Process")

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

    # Let the mission load and the spawner finish before the first frame.
    Start-Sleep -Seconds ([int][math]::Ceiling($WarmupSeconds + 6))
    [void][BzWin]::SetForegroundWindow($handle)
    Start-Sleep -Milliseconds 500

    $captured = 0
    for ($index = 0; $index -lt $Frames; $index++) {
        $process.Refresh()
        if ($process.HasExited) { break }
        $rect = New-Object BzWin+RECT
        if (-not [BzWin]::GetClientRect($handle, [ref]$rect)) { break }
        $origin = New-Object BzWin+POINT
        [void][BzWin]::ClientToScreen($handle, [ref]$origin)
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
        $process.WaitForExit(20000) | Out-Null
    }
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force

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
