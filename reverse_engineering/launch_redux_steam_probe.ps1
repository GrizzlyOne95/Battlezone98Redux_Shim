param(
    [int]$AppId = 301650,
    [string]$ArgLine = "/nointro",
    [int]$TimeoutSeconds = 90,
    [switch]$KillExisting,
    [switch]$ClickLauncherPlay,
    [double]$PlayClickXRatio = 0.25,
    [double]$PlayClickYRatio = 0.46,
    [switch]$ProbeDefaultSites
)

$ErrorActionPreference = "Stop"

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;

namespace ReduxProbe {
    public static class NativeMethods {
        [StructLayout(LayoutKind.Sequential)]
        public struct RECT {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        [DllImport("user32.dll")]
        public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);

        [DllImport("user32.dll")]
        public static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        public static extern bool SetCursorPos(int X, int Y);

        [DllImport("user32.dll")]
        public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint dwData, UIntPtr dwExtraInfo);
    }
}
"@

function Get-SteamRoot {
    $candidates = @()
    try {
        $steamExe = (Get-ItemProperty -Path "HKCU:\Software\Valve\Steam" -ErrorAction SilentlyContinue).SteamExe
        if ($steamExe) { $candidates += (Split-Path -Parent $steamExe) }
    } catch {}

    $programFilesX86 = ${env:ProgramFiles(x86)}
    if ($programFilesX86) { $candidates += (Join-Path $programFilesX86 "Steam") }

    foreach ($candidate in $candidates) {
        if ($candidate -and (Test-Path (Join-Path $candidate "steam.exe"))) {
            return (Resolve-Path $candidate).Path
        }
    }

    throw "Could not locate Steam root"
}

function Read-AcfValue {
    param(
        [string]$Path,
        [string]$Key
    )

    if (-not (Test-Path $Path)) { return $null }
    $pattern = '^\s*"' + [regex]::Escape($Key) + '"\s*"([^"]*)"'
    foreach ($line in Get-Content $Path) {
        $match = [regex]::Match($line, $pattern)
        if ($match.Success) { return $match.Groups[1].Value }
    }
    return $null
}

function Get-ReduxProcess {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Sort-Object StartTime -Descending |
        Select-Object -First 1
}

function Wait-ReduxProcess {
    param([int]$Seconds)

    $deadline = (Get-Date).AddSeconds($Seconds)
    while ((Get-Date) -lt $deadline) {
        $proc = Get-ReduxProcess
        if ($proc) {
            $proc.Refresh()
            if ($proc.MainWindowTitle -like "Battlezone 98 Redux*") {
                return $proc
            }
            if ($proc.MainWindowTitle -eq "Steam Error") {
                throw "Redux launched into Steam Error; use Steam app launch, not direct exe launch"
            }
        }
        Start-Sleep -Milliseconds 500
    }

    throw "Timed out waiting for Battlezone 98 Redux process"
}

function Click-WindowPoint {
    param(
        [System.Diagnostics.Process]$Process,
        [double]$XRatio,
        [double]$YRatio
    )

    if (-not $Process.MainWindowHandle -or $Process.MainWindowHandle -eq [IntPtr]::Zero) {
        throw "Redux process has no main window handle to click"
    }

    $rect = New-Object ReduxProbe.NativeMethods+RECT
    if (-not [ReduxProbe.NativeMethods]::GetWindowRect($Process.MainWindowHandle, [ref]$rect)) {
        throw "Could not read Redux window rectangle"
    }

    $width = $rect.Right - $rect.Left
    $height = $rect.Bottom - $rect.Top
    if ($width -le 0 -or $height -le 0) {
        throw "Redux window rectangle is invalid"
    }

    $x = [int]($rect.Left + ($width * $XRatio))
    $y = [int]($rect.Top + ($height * $YRatio))
    [ReduxProbe.NativeMethods]::SetForegroundWindow($Process.MainWindowHandle) | Out-Null
    Start-Sleep -Milliseconds 250
    [ReduxProbe.NativeMethods]::SetCursorPos($x, $y) | Out-Null
    Start-Sleep -Milliseconds 100
    [ReduxProbe.NativeMethods]::mouse_event(0x0002, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 80
    [ReduxProbe.NativeMethods]::mouse_event(0x0004, 0, 0, 0, [UIntPtr]::Zero)

    [ordered]@{
        x = $x
        y = $y
        window_left = $rect.Left
        window_top = $rect.Top
        window_width = $width
        window_height = $height
    }
}

$steamRoot = Get-SteamRoot
$steamExe = Join-Path $steamRoot "steam.exe"
$manifest = Join-Path $steamRoot ("steamapps\appmanifest_{0}.acf" -f $AppId)
$installDir = Read-AcfValue -Path $manifest -Key "installdir"
$gameDir = if ($installDir) { Join-Path (Join-Path $steamRoot "steamapps\common") $installDir } else { "" }

if ($KillExisting) {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Seconds 2
}

$proc = Get-ReduxProcess
if (-not $proc) {
    $args = @("-applaunch", "$AppId")
    if ($ArgLine) { $args += ($ArgLine -split " " | Where-Object { $_ }) }
    Start-Process -FilePath $steamExe -ArgumentList $args | Out-Null
    $proc = Wait-ReduxProcess -Seconds $TimeoutSeconds
} else {
    $proc.Refresh()
    if ($proc.MainWindowTitle -eq "Steam Error") {
        throw "Existing Redux process is Steam Error; close it and relaunch through this script"
    }
    if ($proc.MainWindowTitle -notlike "Battlezone 98 Redux*") {
        $proc = Wait-ReduxProcess -Seconds $TimeoutSeconds
    }
}

$result = [ordered]@{
    app_id = $AppId
    steam_exe = $steamExe
    manifest = $manifest
    game_dir = $gameDir
    pid = $proc.Id
    title = $proc.MainWindowTitle
    path = $proc.Path
    launcher_play_click = $null
    probes = @()
}

if ($ClickLauncherPlay) {
    $result.launcher_play_click = Click-WindowPoint -Process $proc -XRatio $PlayClickXRatio -YRatio $PlayClickYRatio
    Start-Sleep -Seconds 5
    $proc.Refresh()
    $result.pid = $proc.Id
    $result.title = $proc.MainWindowTitle
}

if ($ProbeDefaultSites) {
    $sites = @(
        @{ name = "Stock MP initialiseResourceGroup call"; address = "0x0076A3E7"; expected = "FF 15 10 99 86 00" },
        @{ name = "Stock MP selection detail call"; address = "0x007A4202"; expected = "E8 79 FD FF FF" },
        @{ name = "cWorkshop::buildMPResources"; address = "0x0076A240"; expected = "55 8B EC" },
        @{ name = "cWorkshop::buildSingleMPResource"; address = "0x0076B350"; expected = "55 8B EC" }
    )

    foreach ($site in $sites) {
        $json = & bzr-redux-debug.cmd read $site.address --length 16 --pid $proc.Id
        $read = $json | ConvertFrom-Json
        $bytes = $read.bytes
        $result.probes += [ordered]@{
            name = $site.name
            address = $site.address
            bytes = $bytes
            expected_prefix = $site.expected
            matches = $bytes.StartsWith($site.expected)
        }
    }

    $shimLog = Join-Path $gameDir "winmm_shim.log"
    if (Test-Path -LiteralPath $shimLog) {
        $result["ogre_material_collision_log"] = @(Get-Content -LiteralPath $shimLog -Tail 40 |
            Where-Object { $_ -like "*OgreMaterialCollision*" })
    }
}

$result | ConvertTo-Json -Depth 5
