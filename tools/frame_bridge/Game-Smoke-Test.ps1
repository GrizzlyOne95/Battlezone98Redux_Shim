[CmdletBinding()]
param(
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$Mission = 'misn01.bzn',
    [ValidateRange(10, 300)][int]$InitTimeoutSeconds = 180,
    [ValidateRange(1, 10000)][int]$Frames = 120,
    [switch]$Depth,
    [ValidateRange(0, 8)][int]$DepthClearOrdinal = 0,
    [switch]$DepthSweep,
    [switch]$Camera,
    [switch]$ShaderCameraTrace,
    [switch]$CameraMotion,
    [switch]$SceneColor,
    [ValidateSet('pre-clear', 'before-overlay')][string]$SceneStage = 'before-overlay',
    [string]$StreamlineDirectory = '',
    [switch]$VisibleRayTracing,
    [switch]$VisualEnhancements,
    [switch]$WorldEffectsReference,
    [switch]$TerrainMicroRelief,
    [ValidateSet(1, 2, 4)][int]$TerrainTessellationFactor = 4,
    [ValidateRange(0.001, 1)][float]$TerrainReliefAmplitude = 0.25,
    [switch]$StreamlineDevelopment,
    [switch]$RecordWindow,
    [switch]$RecordFrames,
    [ValidateRange(0, 1800)][int]$WaitForGameExitSeconds = 0
)

$ErrorActionPreference = 'Stop'
if ($WorldEffectsReference) {
    if ($StreamlineDirectory -or $VisibleRayTracing -or $VisualEnhancements -or $ShaderCameraTrace -or $TerrainMicroRelief) { throw 'World-effects reference is a separate diagnostic, without effects or runtime tracing' }
    if ($DepthSweep -or $SceneStage -ne 'before-overlay') { throw 'World-effects reference requires one before-overlay scene capture' }
    $SceneColor=$true
    if ($DepthClearOrdinal -eq 0) { $DepthClearOrdinal=3 }
}
if ($TerrainMicroRelief) {
    if ($DepthSweep -or $SceneStage -ne 'before-overlay') { throw 'Terrain micro-relief requires one before-overlay scene capture' }
    $SceneColor=$true
    if ($DepthClearOrdinal -eq 0) { $DepthClearOrdinal=3 }
}
if ($StreamlineDirectory) {
    $StreamlineDirectory = (Resolve-Path -LiteralPath $StreamlineDirectory).Path
    $SceneColor = $true
    if ($DepthClearOrdinal -eq 0) { $DepthClearOrdinal = 3 }
    if ($DepthSweep -or $SceneStage -ne 'before-overlay') { throw 'DLSS-G preview requires one before-overlay scene boundary' }
}
if ($VisibleRayTracing) {
    $SceneColor = $true
    if ($DepthClearOrdinal -eq 0) { $DepthClearOrdinal = 3 }
    if ($DepthSweep -or $SceneStage -ne 'before-overlay') { throw 'DXR preview requires one before-overlay scene boundary' }
}
if ($VisualEnhancements) {
    $SceneColor = $true
    if ($DepthClearOrdinal -eq 0) { $DepthClearOrdinal = 3 }
    if ($DepthSweep -or $SceneStage -ne 'before-overlay') { throw 'Cinematic preview requires one before-overlay scene boundary' }
}
if ($StreamlineDevelopment -and -not $StreamlineDirectory) { throw 'Development preview requires the development SDK runtime directory' }
if ($CameraMotion -or $SceneColor) { $Camera = $true }
if ($DepthSweep -or $Camera) { $Depth = $true }
if ($SceneColor -and -not $DepthSweep -and $DepthClearOrdinal -eq 0) { throw 'SceneColor requires a positive pre-clear ordinal or DepthSweep' }
$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$GameRoot = (Resolve-Path -LiteralPath $GameRoot).Path
$gameExe = Join-Path $GameRoot 'battlezone98redux.exe'
$presenter = Join-Path $repoRoot 'build/frame-bridge-x64/Release/frame_bridge_presenter.exe'
foreach ($path in @($gameExe, $presenter)) {
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { throw "Missing: $path" }
}
if ($Mission -notmatch '^[A-Za-z0-9_./-]+\.bzn$') { throw 'Mission must be a simple .bzn path' }

# Acquire the same launch mutex before deployment or the harness's Ogre.cfg
# edits. Dot-sourcing then reuses our ownership instead of waiting on itself.
$mutex = [System.Threading.Mutex]::new($false, 'Local\BZROpenShimGameLaunch')
$locked = $false
$game = $null
$gameExitCode = $null
$snapshot = @()
$environment = @{}
$restoreErrors = @()
$outputRoot = Join-Path $repoRoot ('build/game-bridge-' + (Get-Date -Format 'yyyyMMdd-HHmmss-fff'))
function Read-SharedText([string]$Path) {
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) { return '' }
    $stream = [System.IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    try {
        $reader = [System.IO.StreamReader]::new($stream)
        return $reader.ReadToEnd()
    } finally { $stream.Dispose() }
}
try {
    $launchDeadline = [DateTime]::UtcNow.AddSeconds([Math]::Max(5, $WaitForGameExitSeconds))
    $waitingReported = $false
    while ($true) {
        try { $locked = $mutex.WaitOne([TimeSpan]::FromSeconds(1)) }
        catch [System.Threading.AbandonedMutexException] { $locked = $true }
        $anotherGame = Get-Process -Name battlezone98redux -ErrorAction SilentlyContinue
        if ($locked -and -not $anotherGame) { break }
        if ($locked) { $mutex.ReleaseMutex(); $locked = $false }
        if ($WaitForGameExitSeconds -eq 0 -or [DateTime]::UtcNow -ge $launchDeadline) {
            throw 'Game or harness already running; leave it untouched'
        }
        if (-not $waitingReported) {
            Write-Host 'Waiting for the other game/harness to exit normally before deployment'
            $waitingReported = $true
        }
        Start-Sleep -Milliseconds 500
    }
    if (Test-Path -LiteralPath (Join-Path $GameRoot 'ogre.cfg.bzrharness-backup')) {
        throw 'An earlier harness left an Ogre.cfg backup; recover that run before testing'
    }
    New-Item -ItemType Directory -Path $outputRoot | Out-Null

    # Snapshot the whole deployment surface, including existing configs and UI
    # assets. Deploy-OpenShim's binary backups alone do not cover resource edits.
    $targets = @('winmm.dll', 'bzloader.dll', 'plugins/openshim.dll', 'scripts/patches.json', 'openshim/OpenShimAssets.ini')
    $targets += Get-ChildItem -LiteralPath (Join-Path $repoRoot 'resources/renderer/enhanced') -File |
        ForEach-Object { 'openshim/renderer/enhanced/' + $_.Name }
    $targets += Get-ChildItem -LiteralPath (Join-Path $repoRoot 'resources/ui/custom_widgets') -File |
        ForEach-Object { 'BZ_ASSETS_CORE/common/ui/CustomWidgets/' + $_.Name }
    $targets += Get-ChildItem -LiteralPath $GameRoot -File |
        Where-Object { $_.Extension -in @('.cfg', '.ini') } | ForEach-Object { $_.Name }
    foreach ($relative in ($targets | Sort-Object -Unique)) {
        $target = [System.IO.Path]::GetFullPath((Join-Path $GameRoot $relative))
        if (-not $target.StartsWith($GameRoot + '\', [StringComparison]::OrdinalIgnoreCase)) { throw 'Target outside game root' }
        $exists = Test-Path -LiteralPath $target -PathType Leaf
        $backup = Join-Path $outputRoot ('original/' + $relative)
        $hash = $null
        if ($exists) {
            New-Item -ItemType Directory -Force -Path (Split-Path -Parent $backup) | Out-Null
            Copy-Item -LiteralPath $target -Destination $backup
            $hash = (Get-FileHash -LiteralPath $backup -Algorithm SHA256).Hash
        }
        $snapshot += [pscustomobject]@{ Target = $target; Backup = $backup; Existed = $exists; Hash = $hash }
    }
    $snapshot | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $outputRoot 'restore-manifest.json')
    foreach ($entry in @{
        BZR_LAUNCH_LOCK_HELD = "$PID"; BZR_FORCE_WINDOWED = '1';
        OPENSHIM_FRAME_BRIDGE = '1'; OPENSHIM_RUN_IN_BACKGROUND = '1';
        OPENSHIM_DX11_SCENE_DEPTH_DIAG = $(if ($Depth) { '0' } else { '1' })
        OPENSHIM_FRAME_BRIDGE_DEPTH = $(if ($Depth) { '1' } else { '0' })
        OPENSHIM_FRAME_BRIDGE_SCENE_COLOR = $(if ($SceneColor) { '1' } else { '0' })
        OPENSHIM_FRAME_BRIDGE_WORLD_EFFECTS_REFERENCE = $(if ($WorldEffectsReference) { '1' } else { '0' })
        OPENSHIM_TERRAIN_TESSELLATION_TEST = $(if ($TerrainMicroRelief) { '1' } else { '0' })
        OPENSHIM_TERRAIN_MICRO_RELIEF_TEST = $(if ($TerrainMicroRelief) { '1' } else { '0' })
        OPENSHIM_TERRAIN_TESSELLATION_FACTOR = "$TerrainTessellationFactor"
        OPENSHIM_TERRAIN_MICRO_RELIEF_AMPLITUDE = $TerrainReliefAmplitude.ToString('R', [Globalization.CultureInfo]::InvariantCulture)
        OPENSHIM_TERRAIN_TESSELLATION_WIREFRAME = '0'
    }.GetEnumerator()) {
        $environment[$entry.Key] = [Environment]::GetEnvironmentVariable($entry.Key, 'Process')
        [Environment]::SetEnvironmentVariable($entry.Key, $entry.Value, 'Process')
    }
    . (Join-Path $repoRoot 'reverse_engineering/BZRHarness.ps1')
    if ($StreamlineDirectory) { $null = Set-BZROgreWindowed -GameRoot $GameRoot -VideoMode '1280 x 720' }
    Assert-BZRSafeToLaunch
    & (Join-Path $repoRoot 'scripts/Deploy-OpenShim.ps1') -GameDir $GameRoot
    $launchTime = Get-Date
    $game = Start-BZRGameProcess -FilePath $gameExe -ArgumentList @('/renderer:dx11', $Mission) -WorkingDirectory $GameRoot -PassThru
    # Start-BZRGameProcess returns Get-Process, rather than Process.Start's
    # retained handle. Open it while alive so exit status survives PID removal.
    $null = $game.Handle
    Write-Host "GAME pid=$($game.Id) output=$outputRoot"
    $deadline = [DateTime]::UtcNow.AddSeconds($InitTimeoutSeconds)
    $initialized = $false
    while ([DateTime]::UtcNow -lt $deadline -and -not $game.HasExited) {
        $text = Read-SharedText (Join-Path $GameRoot 'logs/BZLogger.txt')
        # The prior run's log can exist briefly before the game truncates it.
        # Accept only a timestamped initialization marker from this launch.
        foreach ($match in [regex]::Matches($text, '(?m)^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d+) .*Game Simulation Initialized after')) {
            $markerTime = [DateTime]::Parse($match.Groups[1].Value, [Globalization.CultureInfo]::InvariantCulture)
            if ($markerTime -ge $launchTime) { $initialized = $true; break }
        }
        if ($initialized) { break }
        Start-Sleep -Milliseconds 500
        $game.Refresh()
    }
    if (-not $initialized) { throw 'Mission failed to initialize before deadline' }
    # Give depth's observation worker time to emit its 15-second registry report.
    Start-Sleep -Seconds 16
    if ($ShaderCameraTrace) {
        # Attach only to our harness-owned PID. The CLI timeout detaches; it
        # must never terminate or eternalize instrumentation in the game.
        $frida = Get-Command bzr-frida.cmd -ErrorAction Stop
        [pscustomobject]@{
            Backend = 'frida-cli'; Pid = $game.Id; Mission = $Mission
            ExecutableSHA256 = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
            OgreSHA256 = (Get-FileHash -LiteralPath (Join-Path $GameRoot 'OgreMain.dll') -Algorithm SHA256).Hash
            RendererSHA256 = (Get-FileHash -LiteralPath (Join-Path $GameRoot 'RenderSystem_Direct3D11.dll') -Algorithm SHA256).Hash
            ScriptSHA256 = (Get-FileHash -LiteralPath (Join-Path $PSScriptRoot 'Trace-Shader-Cameras.js') -Algorithm SHA256).Hash
            Arguments = @('-p', "$($game.Id)", '-q', '-t', '14', '--exit-on-error', '--no-auto-reload', '-l', (Join-Path $PSScriptRoot 'Trace-Shader-Cameras.js'))
        } | ConvertTo-Json -Depth 3 | Set-Content -LiteralPath (Join-Path $outputRoot 'shader-camera-trace.build.json')
        & $frida.Source -p $game.Id -q -t 14 --exit-on-error --no-auto-reload -l (Join-Path $PSScriptRoot 'Trace-Shader-Cameras.js') |
            Tee-Object -FilePath (Join-Path $outputRoot 'shader-camera-trace.jsonl')
        if ($LASTEXITCODE -ne 0) { throw 'Shader camera trace failed' }
        $trace = Read-SharedText (Join-Path $outputRoot 'shader-camera-trace.jsonl')
        $records = @($trace -split '\r?\n' | Where-Object { $_.StartsWith('{') } | ForEach-Object { $_ | ConvertFrom-Json })
        $completed = @($records | Where-Object { $_.type -eq 'complete' })
        $variants = @($records | Where-Object { $_.type -eq 'variant' })
        $draws = @($records | Where-Object { $_.type -eq 'draw-group' })
        $objects = @($records | Where-Object { $_.type -eq 'object-transform-group' })
        if ($completed.Count -ne 1 -or $completed[0].reason -ne 'frame-limit' -or $completed[0].frames -ne 30 -or
            $completed[0].errors -ne 0 -or $completed[0].overflow -ne 0 -or $variants.Count -eq 0 -or
            $completed[0].variants -ne $variants.Count -or $completed[0].drawGroups -ne $draws.Count -or
            $completed[0].objectTransformGroups -ne $objects.Count -or
            $completed[0].drawCalls -le 0 -or $completed[0].linkedDrawCalls -le 0) {
            throw 'Shader camera trace incomplete, invalid or overflowed; retain diagnostics without qualifying matrices'
        }
    }
    $ordinals = if ($DepthSweep) { @(1, 2, 3) } else { @($DepthClearOrdinal) }
    foreach ($ordinal in $ordinals) {
        $suffix = if ($DepthSweep) { "-clear$ordinal" } else { '' }
        $capture = Join-Path $outputRoot "game-frame$suffix.bmp"
        $presenterArgs = @('--pid', "$($game.Id)", '--frames', "$Frames", '--timeout-ms', '15000', '--capture-bmp', $capture)
        if ($Depth) {
            $presenterArgs += @('--capture-depth-pfm', (Join-Path $outputRoot "game-depth$suffix.pfm"), '--depth-clear-ordinal', "$ordinal")
        }
        if ($Camera) { $presenterArgs += '--require-camera' }
        if ($CameraMotion) { $presenterArgs += @('--capture-camera-motion-pfm', (Join-Path $outputRoot "game-camera-motion$suffix.pfm")) }
        if ($SceneColor) { $presenterArgs += @('--capture-scene-bmp', (Join-Path $outputRoot "game-scene$suffix.bmp"), '--scene-stage', $SceneStage) }
        if ($StreamlineDirectory) { $presenterArgs += @('--streamline-dir', $StreamlineDirectory, '--fg-report', (Join-Path $outputRoot 'dlss-fg-report.json')) }
        if ($VisibleRayTracing) { $presenterArgs += @('--rt-visible-ao', '--capture-rt-bmp', (Join-Path $outputRoot 'game-dxr-ao.bmp')) }
        if ($VisualEnhancements) {
            $presenterArgs += @('--show', '--visual-preset', 'cinematic', '--capture-enhanced-bmp', (Join-Path $outputRoot 'game-cinematic.bmp'),
                '--capture-enhanced-scene-bmp', (Join-Path $outputRoot 'game-cinematic-scene.bmp'))
        }
        if ($RecordWindow) { $presenterArgs += @('--record-window', (Join-Path $outputRoot 'demo-window.bzrvid')) }
        if ($RecordFrames) { $presenterArgs += @('--record-frames', (Join-Path $outputRoot 'demo-rendered.bzrvid')) }
        if ($StreamlineDevelopment) {
            $presenterArgs += '--streamline-development'
        }
        Push-Location $outputRoot
        try {
            & $presenter @presenterArgs | Tee-Object -FilePath (Join-Path $outputRoot "consumer$suffix.log")
            if ($LASTEXITCODE -ne 0) { throw "Real-game GPU import/capture failed at clear ordinal $ordinal" }
        } finally { Pop-Location }
        Write-Host "PASS real-game capture: $capture (inspect SDK and DXR reports for effective preview state)"
        if ($WorldEffectsReference) {
            $referenceLog=Read-SharedText (Join-Path $GameRoot 'logs/openshim.log')
            if ($referenceLog -notmatch 'bound effect program reference APIs qualified' -or $referenceLog -notmatch 'world-effect reference skipped=') {
                throw 'World-effects reference did not qualify or omit any draws; leave output unqualified'
            }
            @{ diagnosticOnly=$true; opacityMaskQualified=$false; opaqueSceneQualified=$false; worldEffectProgram='Effect_fragment';
                requiresBoundShaderMatch=$true; boundProgram='Effect_fragmentHLSL4'; preservesIdentityHUD=$true; observedSkip=$true } |
                ConvertTo-Json | Set-Content -LiteralPath (Join-Path $outputRoot 'world-effects-reference.json')
        }
    }
} finally {
    try {
        if ($game) { Stop-BZRGame -Id $game.Id -TimeoutSeconds 30 -NoForce }
        if ($game -and $game.WaitForExit(0)) { $gameExitCode=$game.ExitCode }
    } finally {
        $stillRunning = $game -and (Get-Process -Id $game.Id -ErrorAction SilentlyContinue)
        if ($stillRunning) {
            Write-Warning "Game left running. Do not restore files until it exits. Snapshot: $outputRoot/restore-manifest.json"
        } elseif ($snapshot.Count -gt 0) {
            if (Get-Command Restore-BZROrphanedOgreConfig -ErrorAction SilentlyContinue) {
                $null = Restore-BZROrphanedOgreConfig -GameRoot $GameRoot
            }
            foreach ($relative in @('logs/openshim.log', 'bzloader.log', 'logs/BZLogger.txt', 'logs/BZOgreLogfile.log')) {
                $source = Join-Path $GameRoot $relative
                if (Test-Path -LiteralPath $source -PathType Leaf) {
                    Copy-Item -LiteralPath $source -Destination (Join-Path $outputRoot ([System.IO.Path]::GetFileName($relative))) -Force -ErrorAction Continue
                }
            }
            $restoreErrors = @()
            foreach ($item in $snapshot) {
                try {
                    if ($item.Existed) {
                        Copy-Item -LiteralPath $item.Backup -Destination $item.Target -Force
                        if ((Get-FileHash -LiteralPath $item.Target -Algorithm SHA256).Hash -ne $item.Hash) {
                            throw "Restore hash mismatch: $($item.Target)"
                        }
                    } elseif (Test-Path -LiteralPath $item.Target -PathType Leaf) {
                        # Only explicit files under the verified game root, never directories.
                        Remove-Item -LiteralPath $item.Target
                    }
                } catch { $restoreErrors += $_.ToString() }
            }
            if ($restoreErrors.Count -gt 0) {
                Write-Warning "Some files could not be restored. Snapshot: $outputRoot/restore-manifest.json"
            } else {
                Write-Host "RESTORED $($snapshot.Count) deployment/config files; SHA256 matches original snapshot"
            }
        }
        foreach ($entry in $environment.GetEnumerator()) {
            [Environment]::SetEnvironmentVariable($entry.Key, $entry.Value, 'Process')
        }
        if ($locked) { $mutex.ReleaseMutex() }
        $mutex.Dispose()
        if ($restoreErrors.Count -gt 0) { throw ($restoreErrors -join [Environment]::NewLine) }
    }
}
if ($TerrainMicroRelief) {
    # Validate only this launch, after graceful exit has emitted cleanup proof.
    # Installation messages alone do not establish rasterized tessellation.
    $terrainLines=@((Read-SharedText (Join-Path $outputRoot 'openshim.log')) -split '\r?\n' |
        Where-Object { $_ -match ("\[pid:" + $game.Id + " ") })
    $terrainText=$terrainLines -join "`n"
    $install=[regex]::Matches($terrainText, 'shared native material installed .*factor=(\d+) displacement=([0-9.]+) wireframe=0 passes=(\d+)')
    $statistics=@([regex]::Matches($terrainText, 'GPU statistics tessellated=1 iaPrimitives=(\d+) hsInvocations=(\d+) dsInvocations=(\d+) clipPrimitives=(\d+) psInvocations=(\d+) hdTiles=(\d+)') |
        Where-Object { [uint64]$_.Groups[1].Value -eq 12800 -and [uint64]$_.Groups[2].Value -gt 0 -and
            [uint64]$_.Groups[3].Value -gt 0 -and [uint64]$_.Groups[4].Value -ge 128 -and [uint64]$_.Groups[5].Value -ge 1024 })
    $bounds=[regex]::Matches($terrainText, 'micro-relief render bounds restored meshes=(\d+) tracked=(\d+)')
    $material=[regex]::Matches($terrainText, 'shared material restored source="[^"]+" passes=(\d+)')
    if ($install.Count -ne 1 -or [int]$install[0].Groups[1].Value -ne $TerrainTessellationFactor -or
        [Math]::Abs([float]::Parse($install[0].Groups[2].Value, [Globalization.CultureInfo]::InvariantCulture) - $TerrainReliefAmplitude) -gt 0.00051 -or
        $statistics.Count -eq 0 -or $bounds.Count -ne 1 -or [int]$bounds[0].Groups[1].Value -le 0 -or
        $bounds[0].Groups[1].Value -ne $bounds[0].Groups[2].Value -or $material.Count -ne 1 -or
        $material[0].Groups[1].Value -ne $install[0].Groups[3].Value -or $null -eq $gameExitCode -or $gameExitCode -ne 0) {
        throw 'Terrain bridge capture lacks fresh-session rasterization, requested parameters or complete clean restoration; leave output unqualified'
    }
    $sample=$statistics[0]
    @{ pid=$game.Id; nativeTessellationRasterized=$true; bridgeCaptureCompleted=$true;
        gameExitCode=$gameExitCode; factor=$TerrainTessellationFactor; displacementAmplitude=$TerrainReliefAmplitude; displacementSource='procedural micro-relief';
        iaPrimitives=[uint64]$sample.Groups[1].Value; hullInvocations=[uint64]$sample.Groups[2].Value;
        domainInvocations=[uint64]$sample.Groups[3].Value; clippedPrimitives=[uint64]$sample.Groups[4].Value;
        pixelInvocations=[uint64]$sample.Groups[5].Value; restoredMeshes=[int]$bounds[0].Groups[1].Value;
        restoredPasses=[int]$material[0].Groups[1].Value; gameplayTerrainChanged=$false;
        adaptiveSubdivision=$false; materialHeightMaps=$false; fullTerrainGeometryExport=$false;
        sameFrameUntessellatedComparison=$false; performanceQualified=$false } |
        ConvertTo-Json | Set-Content -LiteralPath (Join-Path $outputRoot 'terrain-bridge-report.json')
    Write-Host "PASS native terrain -> DX12 bridge: factor=$TerrainTessellationFactor amplitude=$TerrainReliefAmplitude; rasterization and cleanup verified"
}
