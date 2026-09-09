[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$ExePath,

    [Parameter(Mandatory)]
    [string]$OutputDir,

    [int]$WaitSeconds = 10
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$ExePath = [System.IO.Path]::GetFullPath($ExePath)
$OutputDir = [System.IO.Path]::GetFullPath($OutputDir)
if (-not (Test-Path -LiteralPath $ExePath -PathType Leaf)) {
    throw "BzE executable not found: $ExePath"
}

$GameRoot = Split-Path -Parent $ExePath
$env:BZR_FORCE_WINDOWED = '1'
. (Join-Path $PSScriptRoot 'BZRHarness.ps1')
New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null

$bytes = [System.IO.File]::ReadAllBytes($ExePath)
$peOffset = [BitConverter]::ToInt32($bytes, 0x3c)
$optionalHeader = $peOffset + 24
$magic = [BitConverter]::ToUInt16($bytes, $optionalHeader)
if ($magic -ne 0x10b) {
    throw "Only PE32 BzE executables are supported (optional-header magic 0x$($magic.ToString('x')))."
}

$imageBase = [BitConverter]::ToUInt32($bytes, $optionalHeader + 28)
$stem = [System.IO.Path]::GetFileNameWithoutExtension($ExePath)
$unpackedPath = Join-Path $OutputDir "$stem.unpacked.exe"

# ASProtect detects an attached debugger, while both ASProtect and NeoLite have
# restored their protected sections by the time the expired-build dialog is
# visible. Launch normally, snapshot the live image, and close it through the
# game harness. No system-clock change or debugger bypass is required.
$process = Start-Process -FilePath $ExePath -WorkingDirectory $GameRoot -PassThru
try {
    $deadline = [DateTime]::UtcNow.AddSeconds($WaitSeconds)
    do {
        Start-Sleep -Milliseconds 250
        $process.Refresh()
    } while (-not $process.HasExited -and
             $process.MainWindowHandle -eq 0 -and
             [DateTime]::UtcNow -lt $deadline)

    if ($process.HasExited) {
        throw "The protected executable exited before its runtime image could be captured."
    }

    & bzr-pe-sieve.cmd /pid $process.Id /dmode 3 /imp 1 /dir $OutputDir /jlvl 2
    $scanExitCode = $LASTEXITCODE
    if ($scanExitCode -notin @(0, 2)) {
        throw "PE-sieve failed with exit code $scanExitCode."
    }
} finally {
    $process.Refresh()
    if (-not $process.HasExited) {
        Stop-BZRGame -Id $process.Id -TimeoutSeconds 20
    }
}

$dumpName = '{0:x}.{1}' -f $imageBase, [System.IO.Path]::GetFileName($ExePath)
$dumpPath = Join-Path (Join-Path $OutputDir "process_$($process.Id)") $dumpName
if (-not (Test-Path -LiteralPath $dumpPath -PathType Leaf)) {
    throw "PE-sieve did not produce the expected realigned image: $dumpPath"
}
Copy-Item -LiteralPath $dumpPath -Destination $unpackedPath -Force
Write-Output $unpackedPath
