# Captures frames of the four-team distant battle for visual regression checks.
#
# Two things need proving and they pull in opposite directions:
#
#   * with no isolation requested the scene must be byte-for-byte the stock
#     scene, because everything this phase added to the profiler is supposed to
#     be diagnostic;
#   * with an isolation arm requested the scene must visibly lose exactly the
#     category that was asked for, because an arm that silently suppresses
#     nothing reports a false null result -- which is a mistake this phase
#     already made once.
#
# The game is forced into a window: an exclusive-fullscreen swap chain is not
# readable with CopyFromScreen. Ogre.cfg is saved and restored around the run.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("DX11", "DX9")]
    [string]$Renderer = "DX11",
    [ValidateSet("fourteam", "fourteam_fire", "fourteam_ai")]
    [string]$Scenario = "fourteam_fire",
    [ValidateSet("none", "glow", "shadow", "glow+shadow")]
    [string]$Isolate = "none",
    [int]$Count = 80,
    [double]$Distance = 400.0,
    [double]$WarmupSeconds = 5.0,
    [double]$MeasureSeconds = 30.0,
    [int]$Frames = 6,
    [int]$FrameIntervalMs = 1200,
    [string]$OutputRoot = "",
    [string]$Label = ""
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Drawing

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\fourteam_visuals"
}
if (-not $Label) {
    $Label = Get-Date -Format "yyyyMMdd_HHmmss"
}
$runRoot = Join-Path $OutputRoot ("{0}_{1}_{2}_{3:d3}_{4}" -f `
    $Label, $Renderer.ToLowerInvariant(), $Scenario,
    $Count, $Isolate.Replace("+", "-"))
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
public static class BzFourTeamWin {
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

$ownedVariables = @(
    "OPENSHIM_PROFILE_OGRE_ANIMATION",
    "OPENSHIM_PROFILE_ISOLATE")
$priorValues = @{}
foreach ($name in $ownedVariables) {
    $priorValues[$name] = [Environment]::GetEnvironmentVariable($name, "Process")
}
$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
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
    $config = $config -replace '(?m)^Video Mode=.*@ 32-bit colour$', 'Video Mode=1920 x 1080 @ 32-bit colour'
    [System.IO.File]::WriteAllText($ogreConfig, $config)

    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "$Scenario"
unitOdf = "avtank"
count = $($Count.ToString($invariant))
distance = $($Distance.ToString("0.0###", $invariant))
orientation = "facing"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = $($MeasureSeconds.ToString("0.0###", $invariant))
clusterCount = 4
clusterRadius = 300.0
spinSeconds = 0.0
"@)

    # Visual validation runs with collection off, which is the configuration
    # normal gameplay uses. The isolation arm is the only deliberate deviation.
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_PROFILE_OGRE_ANIMATION", "0", "Process")
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_PROFILE_ISOLATE",
        $(if ($Isolate -eq "none") { $null } else { $Isolate }),
        "Process")

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

    Start-Sleep -Seconds ([int][math]::Ceiling($WarmupSeconds + 9))
    [void][BzFourTeamWin]::SetForegroundWindow($handle)
    Start-Sleep -Milliseconds 500

    $captured = 0
    for ($index = 0; $index -lt $Frames; $index++) {
        $process.Refresh()
        if ($process.HasExited) { break }
        $rect = New-Object BzFourTeamWin+RECT
        if (-not [BzFourTeamWin]::GetClientRect($handle, [ref]$rect)) { break }
        $origin = New-Object BzFourTeamWin+POINT
        [void][BzFourTeamWin]::ClientToScreen($handle, [ref]$origin)
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
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force

    if (Test-Path -LiteralPath $shimLog) {
        Copy-Item -LiteralPath $shimLog `
            -Destination (Join-Path $runRoot "openshim.log") -Force
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
