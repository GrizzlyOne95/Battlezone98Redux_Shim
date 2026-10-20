[CmdletBinding()]
param(
    [switch]$Show,
    [ValidateSet('single-sample', 'msaa4', 'padded-rgba', 'padded-bgra', 'depth', 'depth-msaa4', 'depth-motion', 'depth-scene', 'depth-scene-msaa4', 'depth-scene-bgra')]
    [string[]]$Cases = @('single-sample', 'msaa4', 'padded-rgba', 'padded-bgra', 'depth', 'depth-msaa4', 'depth-motion', 'depth-scene', 'depth-scene-msaa4', 'depth-scene-bgra')
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$buildRoot = Join-Path $repoRoot 'build'
$sourceExe = Join-Path $buildRoot 'frame-bridge-x86/Release/frame_bridge_test_source.exe'
$presenterExe = Join-Path $buildRoot 'frame-bridge-x64/Release/frame_bridge_presenter.exe'
foreach ($file in @($sourceExe, $presenterExe)) {
    if (-not (Test-Path -LiteralPath $file -PathType Leaf)) { throw "Build first: $file" }
}

foreach ($case in $Cases) {
    $outFile = Join-Path $buildRoot "bridge-$case.out.log"
    $errFile = Join-Path $buildRoot "bridge-$case.err.log"
    $sourceArgs = @('10')
    if ($case -in @('msaa4', 'depth-msaa4', 'depth-scene-msaa4')) { $sourceArgs += '--msaa' }
    if ($case -like 'depth*') { $sourceArgs += @('--depth', '--padded') }
    if ($case -eq 'depth-motion') { $sourceArgs += '--motion-fixture' }
    if ($case -like 'depth-scene*') { $sourceArgs += '--scene-color' }
    if ($case -like 'padded-*') { $sourceArgs += '--padded' }
    if ($case -in @('padded-bgra', 'depth-scene-bgra')) { $sourceArgs += '--bgra' }
    # No elevation, injection or interactive helper window. The source exits on
    # its own deadline, including on a failing consumer. Never force-stop games.
    $sourceProcess = Start-Process -FilePath $sourceExe -ArgumentList $sourceArgs -WindowStyle Hidden `
        -PassThru -RedirectStandardOutput $outFile -RedirectStandardError $errFile
    $failure = $null
    try {
        $deadline = [DateTime]::UtcNow.AddSeconds(3)
        $ready = $false
        while ([DateTime]::UtcNow -lt $deadline) {
            try {
                $mapping = [System.IO.MemoryMappedFiles.MemoryMappedFile]::OpenExisting("Local\OpenShim.FrameBridge.$($sourceProcess.Id)")
                $mapping.Dispose()
                $ready = $true
                break
            } catch { Start-Sleep -Milliseconds 25 }
        }
        if (-not $ready) { throw 'Source mapping did not appear' }
        if ($case -eq 'single-sample') {
            # Hold the metadata's consumer claim without acquiring a GPU slot.
            # A rejected second client must not clear another reader's claim.
            $claimMap = [System.IO.MemoryMappedFiles.MemoryMappedFile]::OpenExisting("Local\OpenShim.FrameBridge.$($sourceProcess.Id)")
            $claimView = $claimMap.CreateViewAccessor(0, 128)
            try {
                $claimView.Write(40, [int]$PID)
                $rejectedOutput = & $presenterExe --pid $sourceProcess.Id --frames 1 --verify 2>&1
                if ($LASTEXITCODE -eq 0 -or "$rejectedOutput" -notmatch 'already has a consumer') {
                    throw 'Expected duplicate consumer rejection'
                }
                if ($claimView.ReadInt32(40) -ne $PID) { throw 'Rejected client cleared another consumer claim' }
                Write-Host 'PASS duplicate consumer rejected without clearing owner'
            } finally {
                $claimView.Write(40, [int]0)
                $claimView.Dispose()
                $claimMap.Dispose()
            }
        }
        $presenterArgs = @('--pid', "$($sourceProcess.Id)", '--frames', '120', '--verify')
        $captureFile = Join-Path $buildRoot "bridge-$case.bmp"
        $presenterArgs += @('--capture-bmp', $captureFile)
        if ($case -like 'depth*') {
            $depthFile = Join-Path $buildRoot "bridge-$case.pfm"
            $presenterArgs += @('--verify-depth', '--capture-depth-pfm', $depthFile)
        }
        if ($case -eq 'depth-motion') {
            $motionFile = Join-Path $buildRoot 'bridge-camera-motion.pfm'
            $presenterArgs += @('--capture-camera-motion-pfm', $motionFile)
        }
        if ($case -like 'depth-scene*') {
            $sceneFile = Join-Path $buildRoot "bridge-$case-scene.bmp"
            $presenterArgs += @('--capture-scene-bmp', $sceneFile, '--depth-clear-ordinal', '1', '--verify-scene')
        }
        if ($Show) { $presenterArgs += '--show' }
        & $presenterExe @presenterArgs
        if ($LASTEXITCODE -ne 0) { throw "$case pixel verification failed" }
        # Validate saved BGRA layout separately from the consumer's GPU checks.
        # Odd width exercises the padded final row footprint caught by gameplay.
        $bytes = [System.IO.File]::ReadAllBytes($captureFile)
        $width = if ($case -like 'padded-*' -or $case -like 'depth*') { 333 } else { 320 }
        $height = if ($case -like 'padded-*' -or $case -like 'depth*') { 181 } else { 180 }
        if ($bytes.Length -ne 54 + $width * $height * 4 -or
            [BitConverter]::ToUInt16($bytes, 0) -ne 0x4d42 -or
            [BitConverter]::ToInt32($bytes, 18) -ne $width -or
            [BitConverter]::ToInt32($bytes, 22) -ne -$height) { throw 'Invalid BMP size/orientation' }
        for ($pixel = 54; $pixel -lt $bytes.Length; $pixel += 4) {
            if ($bytes[$pixel] -ne 64 -or $bytes[$pixel + 1] -ne 0 -or
                $bytes[$pixel + 2] -ne 120 -or $bytes[$pixel + 3] -ne 255) {
                throw "Invalid BMP color at byte $pixel"
            }
        }
        if ($case -like 'depth*') {
            $metadata = Get-Content -LiteralPath ($depthFile + '.json') -Raw | ConvertFrom-Json
            if ($metadata.frameId -ne 120 -or $metadata.width -ne $width -or $metadata.height -ne $height -or
                -not $metadata.candidateOnly -or $metadata.sourceFormat -ne 45) { throw 'Invalid depth capture metadata' }
            $expectedTranslation = if ($case -eq 'depth-motion') { $metadata.frameId / 1000.0 } else { $metadata.frameId }
            if (-not $metadata.cameraObservation.valid -or [Math]::Abs($metadata.cameraObservation.view[3] - $expectedTranslation) -gt 0.000001 -or
                -not $metadata.cameraObservation.recognizedPerspective -or $metadata.protocolVersion -ne 5 -or
                $metadata.cameraObservation.matrixSource -ne 'synthetic' -or
                $metadata.cameraObservation.projection.Count -ne 16) { throw 'Stale or invalid camera artifact' }
            $depthBytes = [System.IO.File]::ReadAllBytes($depthFile)
            $header = [Text.Encoding]::ASCII.GetBytes("Pf`n$width $height`n-1.0`n")
            if ($depthBytes.Length -ne $header.Length + $width * $height * 4) { throw 'Invalid PFM size' }
            for ($byte = 0; $byte -lt $header.Length; ++$byte) {
                if ($depthBytes[$byte] -ne $header[$byte]) { throw 'Invalid PFM header' }
            }
            for ($byte = $header.Length; $byte -lt $depthBytes.Length; $byte += 4) {
                if ([Math]::Abs([BitConverter]::ToSingle($depthBytes, $byte) - 120.0 / 1024.0) -gt 0.000001) {
                    throw "Invalid PFM depth at byte $byte"
                }
            }
            if ($case -eq 'depth-motion') {
                $motionMetadata = Get-Content -LiteralPath ($motionFile + '.json') -Raw | ConvertFrom-Json
                if (-not $motionMetadata.diagnosticOnly -or $motionMetadata.dlssReady -or
                    $motionMetadata.currentFrameId -ne 120 -or $motionMetadata.previousFrameId -ne 119 -or
                    $motionMetadata.validPixels -eq 0 -or $motionMetadata.maximumPixels -le 0) { throw 'Invalid camera motion metadata' }
                $motionBytes = [IO.File]::ReadAllBytes($motionFile)
                $motionHeader = [Text.Encoding]::ASCII.GetBytes("PF`n$width $height`n-1.0`n")
                if ($motionBytes.Length -ne $motionHeader.Length + $width * $height * 12) { throw 'Invalid motion PFM size' }
                for ($byte = 0; $byte -lt $motionHeader.Length; ++$byte) {
                    if ($motionBytes[$byte] -ne $motionHeader[$byte]) { throw 'Invalid motion PFM header' }
                }
                # Analytic perspective translation: dx = deltaViewX * P00 * width/(2*z).
                # z derives from the actual GPU D24 readback, not the requested clear.
                $rawDepth = [BitConverter]::ToSingle($depthBytes, $header.Length)
                $projection = $metadata.cameraObservation.projection
                $distance = $projection[11] / ($rawDepth + $projection[10])
                $deltaX = $motionMetadata.previousView[3] - $metadata.cameraObservation.view[3]
                $expectedDx = $deltaX * $projection[0] * $width / (2 * $distance)
                $validCount = 0
                for ($y = 0; $y -lt $height; ++$y) {
                    for ($x = 0; $x -lt $width; ++$x) {
                        $at = $motionHeader.Length + ($y * $width + $x) * 12
                        $dx = [BitConverter]::ToSingle($motionBytes, $at)
                        $dy = [BitConverter]::ToSingle($motionBytes, $at + 4)
                        $valid = [BitConverter]::ToSingle($motionBytes, $at + 8)
                        $expectedValid = ($x + 0.5 + $expectedDx -ge 0 -and $x + 0.5 + $expectedDx -le $width)
                        if ($expectedValid) {
                            ++$validCount
                            if ($valid -ne 1 -or [Math]::Abs($dx - $expectedDx) -gt 0.00001 -or [Math]::Abs($dy) -gt 0.00001) {
                                throw "Incorrect analytic motion at $x,$y"
                            }
                        } elseif ($valid -ne 0 -or $dx -ne 0 -or $dy -ne 0) { throw 'Offscreen motion must be invalid' }
                    }
                }
                if ($validCount -ne $motionMetadata.validPixels) { throw 'Motion validity count mismatch' }
            }
        }
        if ($case -like 'depth-scene*') {
            $sceneMetadata = Get-Content -LiteralPath ($sceneFile + '.json') -Raw | ConvertFrom-Json
            if ($sceneMetadata.protocolVersion -ne 5 -or $sceneMetadata.frameId -ne 120 -or
                $sceneMetadata.capturedClearOrdinal -ne 1 -or -not $sceneMetadata.cameraObservation.valid -or
                $sceneMetadata.hudFreeQualified -or -not $sceneMetadata.candidateOnly) { throw 'Invalid scene metadata' }
            $sceneBytes = [IO.File]::ReadAllBytes($sceneFile)
            if ($sceneBytes.Length -ne $bytes.Length) { throw 'Invalid scene BMP size' }
            for ($pixel = 54; $pixel -lt $sceneBytes.Length; $pixel += 4) {
                if ($sceneBytes[$pixel] -ne 128 -or $sceneBytes[$pixel + 1] -ne 0 -or
                    $sceneBytes[$pixel + 2] -ne 120 -or $sceneBytes[$pixel + 3] -ne 255) { throw 'Stale/final/wrong scene pixels' }
            }
        }
        # Reconnect while the producer is still alive; ownership must be
        # returned after GPU completion and frame numbering must stay aligned.
        $reconnectArgs = @('--pid', "$($sourceProcess.Id)", '--frames', '80', '--verify')
        if ($case -like 'depth*') { $reconnectArgs += '--verify-depth' }
        if ($case -like 'depth-scene*') { $reconnectArgs += @('--verify-scene', '--depth-clear-ordinal', '1') }
        & $presenterExe @reconnectArgs
        if ($LASTEXITCODE -ne 0) { throw "$case reconnect failed" }
    } catch { $failure = $_ }
    finally {
        if (-not $sourceProcess.WaitForExit(15000)) { throw 'Synthetic source failed its bounded shutdown' }
        Get-Content -LiteralPath $outFile
        Get-Content -LiteralPath $errFile
    }
    if ($failure) { throw $failure }
    if ($sourceProcess.ExitCode -ne 0) { throw "$case source failed" }
    $summary = Get-Content -LiteralPath $outFile -Raw
    if ($summary -notmatch 'pointer_bits=32' -or $summary -notmatch 'skipped=[1-9][0-9]*') {
        throw 'Expected real x86 source and backpressure after consumer disconnect'
    }
    Write-Host "PASS ${case}: x86 -> x64 DX12 pixels, reconnect, bounded backpressure/shutdown"
}
