<#
.SYNOPSIS
Live validation for the OpenShim pilot flashlight.

.DESCRIPTION
Deploys the freshly built winmm.dll, turns the feature on in the installed
openshim.ini, drops the endless on-foot fixture into addon/lcbench, launches the
mission windowed, captures screenshots while the pilot is on foot, then restores
the ini and the mission Lua byte-for-byte and reports the [PILOTLIGHT] lines.

Windowed is required: an exclusive-fullscreen DXGI swapchain returns black to
CopyFromScreen, so a fullscreen run cannot produce visual evidence.
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [int]$RunSeconds = 60,
    [string]$Color = "Red",
    [string]$Beam = "Focused",
    [switch]$SkipDeploy,
    [string]$OutDir = "",
    [string]$Fixture = "pilot_flashlight_fixture.lua",
    [string]$Offset = "",
    [string]$Pitch = "",
    [string]$Bone = ""
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot

if (-not $OutDir) {
    $OutDir = Join-Path $env:TEMP ("bzr-pilot-flashlight-val-" + (Get-Date -Format "yyyyMMdd_HHmmss"))
}
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$exe = Join-Path $GameRoot "battlezone98redux.exe"
$builtDll = Join-Path $repoRoot "bin\Release\winmm.dll"
$installedIni = Join-Path $GameRoot "openshim.ini"
$missionLua = Join-Path $GameRoot "addon\lcbench\lcbench.lua"
$fixture = Join-Path $repoRoot "reverse_engineering\test_missions\pilot_anim_capture\$Fixture"
foreach ($p in @($exe, $installedIni, $missionLua, $fixture)) {
    if (-not (Test-Path $p)) { throw "missing: $p" }
}

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms

# The game window is not necessarily in front -- a screen grab taken while it is
# behind captures the desktop instead, which reads as "no beam". Front the window
# and capture only its own rect.
Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class Win {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
    [DllImport("user32.dll")] public static extern IntPtr SetActiveWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, IntPtr pid);
    [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
    [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
    // PW_RENDERFULLCONTENT (2) asks the window to redraw itself into a DC,
    // which works for a windowed DXGI swapchain without owning the foreground.
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr dc, uint flags);
    // SetForegroundWindow is refused for a process that does not already own the
    // foreground. Borrowing the current foreground thread's input queue lifts
    // that restriction for the duration of the call.
    public static bool ForceForeground(IntPtr h) {
        IntPtr fg = GetForegroundWindow();
        if (fg == h) return true;
        uint fgThread = GetWindowThreadProcessId(fg, IntPtr.Zero);
        uint me = GetCurrentThreadId();
        bool attached = (fgThread != 0 && fgThread != me) && AttachThreadInput(me, fgThread, true);
        ShowWindow(h, 9);
        BringWindowToTop(h);
        SetForegroundWindow(h);
        SetActiveWindow(h);
        if (attached) AttachThreadInput(me, fgThread, false);
        return GetForegroundWindow() == h;
    }
}
"@

# Sets a key inside an existing section, or appends it to that section.
function Set-IniKey {
    param([string[]]$Lines, [string]$Section, [string]$Key, [string]$Value)
    $out = New-Object System.Collections.Generic.List[string]
    $inSection = $false
    $written = $false
    $lastSectionLine = -1
    for ($i = 0; $i -lt $Lines.Count; $i++) {
        $line = $Lines[$i]
        if ($line -match '^\s*\[(.+?)\]\s*$') {
            if ($inSection -and -not $written) {
                $out.Insert($lastSectionLine + 1, "$Key = $Value")
                $written = $true
            }
            $inSection = ($Matches[1] -eq $Section)
            $out.Add($line) | Out-Null
            if ($inSection) { $lastSectionLine = $out.Count - 1 }
            continue
        }
        if ($inSection -and -not $written -and $line -match "^\s*$([regex]::Escape($Key))\s*=") {
            $out.Add("$Key = $Value") | Out-Null
            $written = $true
            continue
        }
        $out.Add($line) | Out-Null
    }
    if (-not $written -and $lastSectionLine -ge 0) {
        $out.Insert($lastSectionLine + 1, "$Key = $Value")
    }
    return $out.ToArray()
}

$iniBackup = Join-Path $OutDir "openshim.ini.orig"
$luaBackup = Join-Path $OutDir "lcbench.lua.orig"
Copy-Item $installedIni $iniBackup -Force
Copy-Item $missionLua $luaBackup -Force
$iniHash = (Get-FileHash $installedIni -Algorithm SHA256).Hash
$luaHash = (Get-FileHash $missionLua -Algorithm SHA256).Hash

$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $repoRoot "reverse_engineering\BZRHarness.ps1")

$proc = $null
try {
    if (-not $SkipDeploy) {
        if (-not (Test-Path $builtDll)) { throw "build first: $builtDll" }
        Get-Process battlezone98redux -ErrorAction SilentlyContinue | ForEach-Object {
            throw "the game is already running (PID $($_.Id)); close it before deploying"
        }
        Copy-Item $builtDll (Join-Path $GameRoot "winmm.dll") -Force
        Write-Host "[val] deployed winmm.dll $((Get-FileHash $builtDll -Algorithm SHA256).Hash)"
    }

    $lines = Get-Content $installedIni
    $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlight" "1"
    $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightColor" $Color
    $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightBeam" $Beam
    if ($Offset) { $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightOffset" $Offset }
    if ($Pitch)  { $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightPitch" $Pitch }
    if ($Bone)   { $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightBone" $Bone }
    Set-Content -Path $installedIni -Value $lines -Encoding ASCII
    Write-Host "[val] openshim.ini: PilotFlashlight=1 Color=$Color Beam=$Beam"

    Copy-Item $fixture $missionLua -Force
    $proc = Start-Process -FilePath $exe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
    Write-Host "[val] launched PID=$($proc.Id)"

    $shotIndex = 0
    $deadline = (Get-Date).AddSeconds($RunSeconds)
    $nextShot = (Get-Date).AddSeconds(18)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 500
        $proc.Refresh()
        if ($proc.HasExited) { Write-Warning "[val] game exited early"; break }
        if ((Get-Date) -ge $nextShot) {
            $nextShot = (Get-Date).AddSeconds(8)
            $shotIndex++
            $hwnd = $proc.MainWindowHandle
            $fronted = $true
            if ($hwnd -ne [IntPtr]::Zero) {
                $fronted = [Win]::ForceForeground($hwnd)
                if (-not $fronted) {
                    try { (New-Object -ComObject WScript.Shell).AppActivate($proc.Id) | Out-Null } catch {}
                    $fronted = ([Win]::GetForegroundWindow() -eq $hwnd)
                }
                Start-Sleep -Milliseconds 900
            }
            if (-not $fronted) {
                Write-Warning "[val] shot $($shotIndex): game window is not in front; capture would show the desktop"
            }
            $rect = New-Object Win+RECT
            if ($hwnd -ne [IntPtr]::Zero -and [Win]::GetWindowRect($hwnd, [ref]$rect)) {
                $origin = New-Object System.Drawing.Point $rect.L, $rect.T
                $size = New-Object System.Drawing.Size ($rect.R - $rect.L), ($rect.B - $rect.T)
            } else {
                $b = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds
                $origin = $b.Location
                $size = $b.Size
            }
            $bmp = New-Object System.Drawing.Bitmap $size.Width, $size.Height
            $gfx = [System.Drawing.Graphics]::FromImage($bmp)
            $printed = $false
            if ($hwnd -ne [IntPtr]::Zero) {
                $hdc = $gfx.GetHdc()
                try { $printed = [Win]::PrintWindow($hwnd, $hdc, 2) } finally { $gfx.ReleaseHdc($hdc) }
            }
            if (-not $printed) {
                $gfx.CopyFromScreen($origin, [System.Drawing.Point]::Empty, $size)
            }
            $path = Join-Path $OutDir ("shot{0:D2}.png" -f $shotIndex)
            $bmp.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
            $gfx.Dispose(); $bmp.Dispose()
            Write-Host "[val] captured $path"
        }
    }
}
finally {
    if ($proc -ne $null) {
        try { Stop-BZRGame -Id $proc.Id } catch { Write-Warning "Stop-BZRGame: $_" }
    }
    Copy-Item $iniBackup $installedIni -Force
    Copy-Item $luaBackup $missionLua -Force
    $iniNow = (Get-FileHash $installedIni -Algorithm SHA256).Hash
    $luaNow = (Get-FileHash $missionLua -Algorithm SHA256).Hash
    if ($iniNow -ne $iniHash) { throw "openshim.ini restore mismatch" }
    if ($luaNow -ne $luaHash) { throw "lcbench.lua restore mismatch" }
    Write-Host "[val] openshim.ini and lcbench.lua restored"

    $ogreBackup = Join-Path $GameRoot 'ogre.cfg.bzrharness-backup'
    if (Test-Path $ogreBackup) {
        Copy-Item $ogreBackup (Join-Path $GameRoot 'ogre.cfg') -Force
        Remove-Item $ogreBackup -Force
        Write-Host "[val] ogre.cfg restored"
    }

    foreach ($log in @("BZLogger.txt", "BZOgreLogfile.log", "openshim.log")) {
        $src = Join-Path $GameRoot "logs\$log"
        if (Test-Path $src) { Copy-Item $src (Join-Path $OutDir $log) -Force }
    }
    $shimLog = Join-Path $OutDir "openshim.log"
    if (Test-Path $shimLog) {
        Write-Host "[val] --- PILOTLIGHT lines ---"
        Select-String -Path $shimLog -Pattern "PILOTLIGHT" | Select-Object -Last 40 |
            ForEach-Object { Write-Host $_.Line }
    }
    Write-Host "[val] artifacts in $OutDir"
}
