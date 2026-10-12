[CmdletBinding()]
param(
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$Mission = 'misn01.bzn',
    [ValidateRange(10, 300)][int]$InitTimeoutSeconds = 180,
    [ValidateRange(1, 10000)][int]$Frames = 120,
    [switch]$Depth,
    [ValidateRange(0, 8)][int]$DepthClearOrdinal = 0,
    [switch]$DepthSweep,
    [switch]$Camera
)

$ErrorActionPreference = 'Stop'
if ($DepthSweep -or $Camera) { $Depth = $true }
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
    try { $locked = $mutex.WaitOne([TimeSpan]::FromSeconds(5)) }
    catch [System.Threading.AbandonedMutexException] { $locked = $true }
    if (-not $locked) { throw 'Another game harness owns the launch lock' }
    if (Get-Process -Name battlezone98redux -ErrorAction SilentlyContinue) { throw 'Game already running; leave it untouched' }
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
    }.GetEnumerator()) {
        $environment[$entry.Key] = [Environment]::GetEnvironmentVariable($entry.Key, 'Process')
        [Environment]::SetEnvironmentVariable($entry.Key, $entry.Value, 'Process')
    }
    . (Join-Path $repoRoot 'reverse_engineering/BZRHarness.ps1')
    Assert-BZRSafeToLaunch
    & (Join-Path $repoRoot 'scripts/Deploy-OpenShim.ps1') -GameDir $GameRoot
    $launchTime = Get-Date
    $game = Start-BZRGameProcess -FilePath $gameExe -ArgumentList @('/renderer:dx11', $Mission) -WorkingDirectory $GameRoot -PassThru
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
    $ordinals = if ($DepthSweep) { @(1, 2, 3) } else { @($DepthClearOrdinal) }
    foreach ($ordinal in $ordinals) {
        $suffix = if ($DepthSweep) { "-clear$ordinal" } else { '' }
        $capture = Join-Path $outputRoot "game-frame$suffix.bmp"
        $presenterArgs = @('--pid', "$($game.Id)", '--frames', "$Frames", '--timeout-ms', '15000', '--capture-bmp', $capture)
        if ($Depth) {
            $presenterArgs += @('--capture-depth-pfm', (Join-Path $outputRoot "game-depth$suffix.pfm"), '--depth-clear-ordinal', "$ordinal")
        }
        if ($Camera) { $presenterArgs += '--require-camera' }
        & $presenter @presenterArgs |
            Tee-Object -FilePath (Join-Path $outputRoot "consumer$suffix.log")
        if ($LASTEXITCODE -ne 0) { throw "Real-game GPU import/capture failed at clear ordinal $ordinal" }
        Write-Host "PASS real-game color import: $capture (DLSS/RT still pending)"
    }
} finally {
    try {
        if ($game) { Stop-BZRGame -Id $game.Id -TimeoutSeconds 30 -NoForce }
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
