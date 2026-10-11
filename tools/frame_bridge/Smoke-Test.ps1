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

foreach ($case in @('single-sample', 'msaa4')) {
    $outFile = Join-Path $buildRoot "bridge-$case.out.log"
    $errFile = Join-Path $buildRoot "bridge-$case.err.log"
    $sourceArgs = @('10')
    if ($case -eq 'msaa4') { $sourceArgs += '--msaa' }
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
        if ($Show) { $presenterArgs += '--show' }
        & $presenterExe @presenterArgs
        if ($LASTEXITCODE -ne 0) { throw "$case pixel verification failed" }
        # Reconnect while the producer is still alive; ownership must be
        # returned after GPU completion and frame numbering must stay aligned.
        & $presenterExe --pid $sourceProcess.Id --frames 80 --verify
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
