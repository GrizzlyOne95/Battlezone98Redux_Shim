# Render-profile runtime qualification matrix driver.
# Scratch tooling for agent/openshim-render-profiles merge qualification; not
# tracked. Deploys the branch build to the GOG install, exercises the matrix
# rows that can be driven headlessly (backend x profile x resource integrity),
# captures openshim.log per case, asserts expected [RENDER] behavior, restores
# the pre-existing deployment at the end.
#
#   powershell -ExecutionPolicy Bypass -File tmp\render_profile_matrix.ps1 [-Cases dx11-redux,dx11-enh,...]

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$RepoRoot = "",
    [int]$MissionSeconds = 30,
    [string[]]$Cases = @()
)

$ErrorActionPreference = "Stop"
if (-not $RepoRoot) { $RepoRoot = Split-Path -Parent $PSScriptRoot }
$binDll = Join-Path $RepoRoot "bin\Release\winmm.dll"
$patches = Join-Path $RepoRoot "scripts\patches.json"
$resDir = Join-Path $RepoRoot "resources\renderer\enhanced"
$snapRoot = Join-Path $RepoRoot "reverse_engineering\snapshots\render_profile_matrix"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$gameWinmm = Join-Path $GameRoot "winmm.dll"
$gameExuDll = Join-Path $GameRoot "exu.dll"
$gamePatches = Join-Path $GameRoot "scripts\patches.json"
$gameIni = Join-Path $GameRoot "openshim.ini"
$gameOgreCfg = Join-Path $GameRoot "Ogre.cfg"
$gameLog = Join-Path $GameRoot "logs\openshim.log"
$gameResDir = Join-Path $GameRoot "openshim\renderer\enhanced"

foreach ($required in @($binDll, $patches, (Join-Path $resDir "resources.version"), $gameIni, $gameOgreCfg)) {
    if (-not (Test-Path -LiteralPath $required)) { throw "Required input missing: $required" }
}

function Stop-Game {
    Get-Process battlezone98redux -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Milliseconds 2500
}

# --- one-time backup of the pre-existing deployment -------------------------
$stamp = "matrix-bak"
foreach ($f in @($gameWinmm, $gameExuDll, $gamePatches, $gameIni, $gameOgreCfg)) {
    if ((Test-Path -LiteralPath $f) -and -not (Test-Path -LiteralPath "$f.$stamp")) {
        Copy-Item -LiteralPath $f -Destination "$f.$stamp" -Force
    }
}

function Deploy-NewStack {
    Stop-Game
    Copy-Item $binDll $gameWinmm -Force
    New-Item -ItemType Directory -Force -Path (Split-Path $gamePatches) | Out-Null
    Copy-Item $patches $gamePatches -Force
    if (Test-Path $gameResDir) { Remove-Item -Recurse -Force $gameResDir }
    New-Item -ItemType Directory -Force -Path $gameResDir | Out-Null
    Copy-Item (Join-Path $resDir "*") $gameResDir -Force
}

function Set-IniGraphics {
    param([string]$Profile, [string]$Renderer)
    $lines = [System.IO.File]::ReadAllLines($gameIni) | Where-Object {
        $_ -notmatch '^\s*(Renderer|RenderProfile)\s*='
    }
    if ($lines -notcontains '[Graphics]') {
        # strip a stale section header from previous edits, then append fresh
        $lines = $lines | Where-Object { $_ -ne '[Graphics]' }
        $lines += ''
        $lines += '[Graphics]'
    }
    if ($Renderer) { $lines += "Renderer = $Renderer" }
    if ($Profile)  { $lines += "RenderProfile = $Profile" }
    [System.IO.File]::WriteAllLines($gameIni, $lines)
}

function Set-OgreRenderer {
    param([string]$Name)
    $renderSystem = if ($Name -eq "DX9") { "Direct3D9 Rendering Subsystem" }
                    else { "Direct3D11 Rendering Subsystem" }
    $cfg = [System.IO.File]::ReadAllText($gameOgreCfg)
    $cfg = $cfg -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
    [System.IO.File]::WriteAllText($gameOgreCfg, $cfg)
}

function Invoke-Case {
    param([string]$Id, [scriptblock]$Setup, [scriptblock[]]$Asserts)
    Write-Host ""
    Write-Host "=== case $Id ===" -ForegroundColor Cyan
    for ($attempt = 1; $attempt -le 2; $attempt++) {
        Stop-Game
        if ($attempt -eq 1) { & $Setup }
        Remove-Item $gameLog -Force -ErrorAction SilentlyContinue
        Start-Sleep -Milliseconds 600
        $proc = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
            -WorkingDirectory $GameRoot -PassThru
        Start-Sleep -Seconds $MissionSeconds
        $logNow = if (Test-Path $gameLog) { Get-Content -Raw $gameLog } else { "" }
        if ($logNow -match '\[RENDER\]' -or $attempt -eq 2) { break }
        Write-Host "  retry [$Id]: no RENDER output on attempt $attempt (startup flake)" -ForegroundColor Yellow
    }
    $aliveAtSample = -not $proc.HasExited
    Stop-Game
    $snap = Join-Path $snapRoot $Id
    New-Item -ItemType Directory -Force -Path $snap | Out-Null
    if (Test-Path $gameLog) { Copy-Item $gameLog (Join-Path $snap "openshim.log") -Force }

    # lcbench missions complete and exit on their own; an early exit is only a
    # failure when it left no usable log behind.
    $logText = if (Test-Path (Join-Path $snap "openshim.log")) {
        Get-Content -Raw (Join-Path $snap "openshim.log")
    } else { "" }
    if (-not $aliveAtSample -and ($logText -notmatch '\[RENDER\]')) {
        Write-Host "  FAIL [$Id]: game exited before sampling window ended and wrote no RENDER log" -ForegroundColor Red
        return $false
    }
    $ok = $true
    foreach ($assert in $Asserts) {
        $r = & $assert $logText
        if (-not $r.pass) {
            Write-Host ("  FAIL [{0}]: {1}" -f $Id, $r.msg) -ForegroundColor Red
            $ok = $false
        } else {
            Write-Host ("  pass: {0}" -f $r.msg) -ForegroundColor DarkGray
        }
    }
    if ($ok) { Write-Host "  PASS [$Id]" -ForegroundColor Green }
    return $ok
}

function Assert-Contains {
    param([string]$Needle, [string]$Msg)
    {
        param($log)
        if ($log -like "*$Needle*") { @{ pass = $true; msg = $Msg } }
        else { @{ pass = $false; msg = "$Msg (missing: '$Needle')" } }
    }.GetNewClosure()
}

function Assert-NotContains {
    param([string]$Needle, [string]$Msg)
    {
        param($log)
        if ($log -notlike "*$Needle*") { @{ pass = $true; msg = $Msg } }
        else { @{ pass = $false; msg = "$Msg (forbidden present: '$Needle')" } }
    }.GetNewClosure()
}

$results = [ordered]@{}
$allCases = @('dx11-redux','dx11-enh','dx11-retro','dx9-redux','dx9-enh',
              'dx11-enh-exu','res-mismatch','res-missing','old-exu','new-exu-old-shim')
$runCases = if ($Cases.Count -gt 0) { @($Cases | ForEach-Object { $_ -split ',' }) } else { $allCases }

Deploy-NewStack

if ($runCases -contains 'dx11-redux') {
    $results['dx11-redux'] = Invoke-Case 'dx11-redux' `
        { Set-IniGraphics $null $null; Set-OgreRenderer "DX11" } `
        @(
            (Assert-Contains "scheme takeover installed at 0x00681585" "scheme takeover installed (site 1)"),
            (Assert-Contains "backend.effective=DX11" "DX11 backend observed"),
            (Assert-Contains "backend identified" "observation thread landed"),
            (Assert-Contains "resources compatible=yes" "renderer resources validated"),
            (Assert-Contains "profile.effective=Redux" "Redux baseline effective"),
            (Assert-Contains "enhanced.pssm=yes" "modern capability bits present"),
            (Assert-NotContains "scheme rewrite incoming" "no rewrites under Redux passthrough"),
            (Assert-Contains "attached to swapchain" "FXAA presentation attached (profile-independent)")
        )
}
if ($runCases -contains 'dx11-enh') {
    $results['dx11-enh'] = Invoke-Case 'dx11-enh' `
        { Set-IniGraphics "Enhanced" "DX11" } `
        @(
            (Assert-Contains "profile.effective=Enhanced" "Enhanced effective"),
            (Assert-Contains "final=en-" "en- policy prefix applied by takeover"),
            (Assert-Contains "enhanced.lightSelection=yes" "light-selection capability reported")
        )
}
if ($runCases -contains 'dx11-retro') {
    $results['dx11-retro'] = Invoke-Case 'dx11-retro' `
        { Set-IniGraphics "Retro" "DX11" } `
        @(
            (Assert-Contains "profile.effective=Retro" "Retro effective"),
            (Assert-Contains "final=og-" "og- policy prefix applied")
        )
}
if ($runCases -contains 'dx9-redux') {
    $results['dx9-redux'] = Invoke-Case 'dx9-redux' `
        { Set-IniGraphics $null "DX9" } `
        @(
            (Assert-Contains "backend.effective=DX9" "DX9 backend observed"),
            (Assert-Contains "backend identified" "observation thread landed"),
            (Assert-Contains "enhanced.sharpening=yes" "legacy sharpening bit present"),
            (Assert-Contains "enhanced.pssm=no" "modern pssm bit correctly absent on DX9"),
            (Assert-Contains "profile.effective=Redux" "DX9 Redux baseline")
        )
}
if ($runCases -contains 'dx9-enh') {
    $results['dx9-enh'] = Invoke-Case 'dx9-enh' `
        { Set-IniGraphics "Enhanced" "DX9" } `
        @(
            (Assert-Contains "profile.effective=Enhanced" "DX9 Enhanced STAYS Enhanced (no silent degrade)"),
            (Assert-Contains "final=en-" "en- schemes requested on DX9 (SM3 delegates)"),
            (Assert-Contains "enhanced.linearLighting=no" "DX11-only bits honestly absent"),
            (Assert-NotContains "fallback=Enhanced unavailable" "no Enhanced fallback fired for DX9+Enhanced")
        )
}
if ($runCases -contains 'dx11-enh-exu') {
    # Full canonical chain: new shim + new EXU. EXU's mission-init call into
    # OpenShimResetMissionHookOverrides drives deferred hook retries, so the
    # Enhanced-only light selector must install after the render system loads.
    Stop-Game
    $newExuFull = Join-Path (Split-Path $RepoRoot) "ExtraUtilities-render-profiles-wt\Release\exu.dll"
    if (-not (Test-Path $newExuFull)) { throw "built exu.dll not found: $newExuFull" }
    Copy-Item $newExuFull $gameExuDll -Force
    Set-OgreRenderer "DX11"
    $results['dx11-enh-exu'] = Invoke-Case 'dx11-enh-exu' `
        { Set-IniGraphics "Enhanced" "DX11" } `
        @(
            (Assert-Contains "backend.effective=DX11" "DX11 backend observed"),
            (Assert-Contains "profile.effective=Enhanced" "Enhanced effective"),
            (Assert-Contains "final=en-" "en- policy prefix applied"),
            (Assert-Contains "enhanced.lightSelection=yes" "light-selection capability reported")
        )
}
if ($runCases -contains 'baseline-lightsel') {
    # Control: pre-migration winmm.dll + production exu.dll on the SAME
    # lcbench harness. If the Enhanced-only light selector also never installs
    # here, its absence in matrix runs is a harness artifact (no EXU-driven
    # retry), not a migration regression.
    Stop-Game
    Copy-Item "$gameWinmm.$stamp" $gameWinmm -Force
    Copy-Item "$gamePatches.$stamp" $gamePatches -Force
    if (Test-Path "$gameExuDll.$stamp") { Copy-Item "$gameExuDll.$stamp" $gameExuDll -Force }
    Set-OgreRenderer "DX11"
    $results['baseline-lightsel'] = Invoke-Case 'baseline-lightsel' `
        { Set-IniGraphics $null $null } `
        @(
            (Assert-Contains "Direct3D11 renderer found" "DX11 session reached renderer"),
            (Assert-NotContains "installed Enhanced-only selector" "selector equally absent on baseline harness")
        )
}
if ($runCases -contains 'res-mismatch') {
    $results['res-mismatch'] = Invoke-Case 'res-mismatch' `
        { Set-IniGraphics "Enhanced" "DX11"; Set-Content (Join-Path $gameResDir "resources.version") "999" -NoNewline } `
        @(
            (Assert-Contains "resource version mismatch" "stale-resource detection fired"),
            (Assert-Contains "resources.compatible=no" "compatibility reported down"),
            (Assert-Contains "profile.effective=Enhanced" "Enhanced still effective (retrofit gated, scheme layer intact)")
        )
}
if ($runCases -contains 'res-missing') {
    $results['res-missing'] = Invoke-Case 'res-missing' `
        { Set-IniGraphics "Enhanced" "DX11"; Rename-Item $gameResDir "enhanced-off" } `
        @(
            (Assert-Contains "Enhanced resource set absent" "absent resource set detected"),
            (Assert-Contains "profile.effective=Enhanced" "CR-supplied techniques path unaffected")
        )
    # restore regardless
    $off = Join-Path (Split-Path $gameResDir) "enhanced-off"
    if (Test-Path $off) { Rename-Item $off "enhanced" }
}
if ($runCases -contains 'old-exu') {
    # Pre-existing (Aug 10) production exu.dll against the new shim: the legacy
    # EXU must keep working; its own hook overwrites ours exactly like today.
    Stop-Game
    Copy-Item "$gameExuDll.$stamp" $gameExuDll -Force
    Set-IniGraphics "Enhanced" "DX11"
    $results['old-exu'] = Invoke-Case 'old-exu' `
        { } `
        @(
            (Assert-Contains "profile.effective=Enhanced" "user INI Enhanced resolves"),
            (Assert-NotContains "EXU request" "legacy EXU never uses the new bridge")
        )
}
if ($runCases -contains 'new-exu-old-shim') {
    # Newly built exu.dll against the PRE-MIGRATION shim: bridge absent, so
    # EXU must take its legacy local path unchanged.
    Stop-Game
    Copy-Item "$gameWinmm.$stamp" $gameWinmm -Force
    Copy-Item "$gamePatches.$stamp" $gamePatches -Force
    $newExu = Join-Path (Split-Path $RepoRoot) "ExtraUtilities-render-profiles-wt\Release\exu.dll"
    if (-not (Test-Path $newExu)) { throw "built exu.dll not found: $newExu" }
    Copy-Item $newExu $gameExuDll -Force
    $results['new-exu-old-shim'] = Invoke-Case 'new-exu-old-shim' `
        { Set-IniGraphics "Enhanced" "DX11" } `
        @(
            (Assert-NotContains "backend.requested=" "pre-migration shim emits no render-profile block (bridge absent)"),
            (Assert-NotContains "profile.effective=" "no profile resolution from pre-migration shim")
        )
}

# --- restore the pre-existing deployment ------------------------------------
Stop-Game
Copy-Item "$gameWinmm.$stamp" $gameWinmm -Force
Copy-Item "$gameExuDll.$stamp" $gameExuDll -Force
Copy-Item "$gamePatches.$stamp" $gamePatches -Force
Copy-Item "$gameIni.$stamp" $gameIni -Force
Copy-Item "$gameOgreCfg.$stamp" $gameOgreCfg -Force

Write-Host ""
Write-Host "=== matrix summary ===" -ForegroundColor Cyan
$failed = 0
foreach ($k in $results.Keys) {
    $v = $results[$k]
    if ($v -eq $true)  { Write-Host ("  {0,-18} PASS" -f $k) -ForegroundColor Green }
    elseif ($v -eq $false) { Write-Host ("  {0,-18} FAIL" -f $k) -ForegroundColor Red; $failed++ }
    else { Write-Host ("  {0,-18} SKIPPED" -f $k) -ForegroundColor Yellow }
}
Write-Host ""
Write-Host "Logs: $snapRoot"
Write-Host "Pre-existing deployment restored from .$stamp backups."
if ($failed -gt 0) { throw "$failed matrix case(s) failed" }
