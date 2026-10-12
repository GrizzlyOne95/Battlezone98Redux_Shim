[CmdletBinding()]
param([switch]$Show)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$buildRoot = Join-Path $repoRoot 'build'
$sourceExe = Join-Path $buildRoot 'frame-bridge-x86/Release/frame_bridge_test_source.exe'
$presenterExe = Join-Path $buildRoot 'frame-bridge-x64/Release/frame_bridge_presenter.exe'
foreach ($file in @($sourceExe, $presenterExe)) {
    if (-not (Test-Path -LiteralPath $file -PathType Leaf)) { throw "Build first: $file" }
}

foreach ($case in @('single-sample', 'msaa4', 'padded-rgba', 'padded-bgra', 'depth', 'depth-msaa4')) {
    $outFile = Join-Path $buildRoot "bridge-$case.out.log"
    $errFile = Join-Path $buildRoot "bridge-$case.err.log"
    $sourceArgs = @('10')
    if ($case -in @('msaa4', 'depth-msaa4')) { $sourceArgs += '--msaa' }
    if ($case -like 'depth*') { $sourceArgs += @('--depth', '--padded') }
    if ($case -like 'padded-*') { $sourceArgs += '--padded' }
    if ($case -eq 'padded-bgra') { $sourceArgs += '--bgra' }
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
            if (-not $metadata.cameraObservation.valid -or $metadata.cameraObservation.view[3] -ne $metadata.frameId -or
                -not $metadata.cameraObservation.recognizedPerspective -or $metadata.protocolVersion -ne 4 -or
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
        }
        # Reconnect while the producer is still alive; ownership must be
        # returned after GPU completion and frame numbering must stay aligned.
        $reconnectArgs = @('--pid', "$($sourceProcess.Id)", '--frames', '80', '--verify')
        if ($case -like 'depth*') { $reconnectArgs += '--verify-depth' }
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
