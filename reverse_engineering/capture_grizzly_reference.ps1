<# Captures avtank reference shots under OpenShim DX11 Enhanced on the GOG install.
   Usage: capture_grizzly_reference.ps1 [-Prefix bzr_enhanced_before] [-OutDir <dir>]
   -CRMission misn04 runs a Campaign Reimagined map instead of an lcbworld one: CR
   missions only load through the mod's crsetup.bzn, so the map's
   bzn/trn/hg2/mat/lgt are copied over the crsetup slot of mods\3686673790 and
   the fixture replaces <map>.lua (the Lua named inside the bzn). All of them are
   restored afterwards. #>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$Mission = "lcbmars",
    [string]$Prefix = "bzr_enhanced_before",
    [string]$OutDir = "",
    [string]$ArtifactDir = "",
    [string]$CRMission = ""
)
$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
if (-not $OutDir) { $OutDir = Join-Path $repo "Docs\images\redux_grizzly_shading" }
if (-not $ArtifactDir) { $ArtifactDir = Join-Path $env:TEMP ("bzr-grizzly-" + (Get-Date -Format yyyyMMdd_HHmmss)) }
New-Item -ItemType Directory -Force $OutDir, $ArtifactDir | Out-Null
$exe = Join-Path $GameRoot "battlezone98redux.exe"
$lua = Join-Path $GameRoot "addon\lcbworld\$Mission.lua"
$launchArgs = "$Mission.bzn"
$crMod = Join-Path $GameRoot "mods\3686673790"
$crSlot = @()
if ($CRMission) {
    $Mission = $CRMission
    $lua = Join-Path $crMod "$CRMission.lua"
    $launchArgs = "crsetup.bzn /nointro /renderer:dx11"
    foreach ($x in "bzn","trn","hg2","mat","lgt") {
        $crSlot += [pscustomobject]@{ Src = Join-Path $crMod "$CRMission.$x"; Dst = Join-Path $crMod "crsetup.$x"; Bak = Join-Path $ArtifactDir "crsetup.$x.orig" }
    }
    foreach ($f in $crSlot) { Copy-Item -LiteralPath $f.Dst -Destination $f.Bak -Force }
}
$fix = Join-Path $PSScriptRoot "test_missions\grizzly_shading\grizzly_cam.lua"
$shot = Join-Path $PSScriptRoot "Capture-BZRWindow.ps1"
$bak = Join-Path $ArtifactDir "$Mission.lua.orig"
Copy-Item $lua $bak -Force
$hash = (Get-FileHash $lua).Hash
$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $PSScriptRoot "BZRHarness.ps1")
$logDir = Join-Path $GameRoot "logs"
$proc = $null
try {
    foreach ($f in $crSlot) { Copy-Item -LiteralPath $f.Src -Destination $f.Dst -Force }
    Copy-Item $fix $lua -Force
    Assert-BZRSafeToLaunch
    $proc = Start-BZRGameProcess -FilePath $exe -ArgumentList $launchArgs -WorkingDirectory $GameRoot -PassThru
    Write-Host "[grz] launched PID=$($proc.Id)"
    $logFile = Join-Path $logDir "BZLogger.txt"
    $seen = @{}; $deadline = (Get-Date).AddSeconds(150); $n = 0
    while ((Get-Date) -lt $deadline -and $n -lt 4) {
        Start-Sleep -Milliseconds 500
        $proc.Refresh(); if ($proc.HasExited) { Write-Warning "game exited early"; break }
        $txt = ""
        foreach ($lf in @($logFile, (Join-Path $logDir "openshim.log"), (Join-Path $logDir "BZOgreLogfile.log"))) {
            if (Test-Path $lf) { try { $fs = [IO.File]::Open($lf,"Open","Read","ReadWrite,Delete"); $sr = New-Object IO.StreamReader $fs; $txt += $sr.ReadToEnd(); $sr.Dispose() } catch {} } }
        if ($txt) {
            foreach ($k in 1..4) {
                if (-not $seen[$k] -and $txt -match "\[GRZ\] phase $k") {
                    $seen[$k] = $true
                    Start-Sleep -Seconds 6   # let the camera settle, mid-phase
                    $out = Join-Path $OutDir ("{0}_{1}.png" -f $Prefix, @('','front_close','front_far','rear_close','rear_far')[$k])
                    powershell -NoProfile -ExecutionPolicy Bypass -File $shot -Out $out
                    Write-Host "[grz] captured $out"; $n++
                }
            }
        }
    }
}
finally {
    if ($proc) { try { Stop-BZRGame -Id $proc.Id } catch { Write-Warning "Stop: $_" } }
    Copy-Item $bak $lua -Force
    foreach ($f in $crSlot) {
        Copy-Item -LiteralPath $f.Bak -Destination $f.Dst -Force
        if ((Get-FileHash -LiteralPath $f.Bak).Hash -ne (Get-FileHash -LiteralPath $f.Dst).Hash) { Write-Warning "$($f.Dst) restore mismatch" }
    }
    if ((Get-FileHash $lua).Hash -ne $hash) { Write-Warning "$Mission.lua restore mismatch" } else { Write-Host "[grz] $Mission.lua restored" }
    $ob = Join-Path $GameRoot 'ogre.cfg.bzrharness-backup'
    if (Test-Path $ob) { Copy-Item $ob (Join-Path $GameRoot 'ogre.cfg') -Force; Remove-Item $ob -Force; Write-Host "[grz] ogre.cfg restored" }
    foreach ($l in "BZLogger.txt","BZOgreLogfile.log","openshim.log") {
        $s = Join-Path $logDir $l; if (Test-Path $s) { Copy-Item $s (Join-Path $ArtifactDir $l) -Force } }
    Write-Host "[grz] artifacts: $ArtifactDir"
}
