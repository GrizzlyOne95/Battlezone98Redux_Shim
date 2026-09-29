[CmdletBinding()]
param([string]$ShimPath = (Join-Path $PSScriptRoot '..\bin\Release\winmm.dll'))

$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
$fixture = Join-Path ([IO.Path]::GetTempPath()) ('openshim-verifier-' + [Guid]::NewGuid().ToString('N'))
$shell = (Get-Process -Id $PID).Path
if (-not (Test-Path -LiteralPath $ShimPath -PathType Leaf)) { throw 'Build Release Win32 before running this test.' }

function Assert-Verdict([bool]$ExpectedPass, [string]$Name) {
    $output = & $shell -NoProfile -File (Join-Path $repo 'verify_windows.ps1') -GamePath $fixture 2>&1
    $code = $LASTEXITCODE
    $text = $output -join "`n"
    if ($ExpectedPass) {
        if ($code -ne 0 -or $text -notmatch 'RESULT: PASS') { throw "$Name failed ($code):`n$text" }
    } elseif ($code -eq 0 -or $text -notmatch 'RESULT: FAIL') {
        throw "$Name should fail with a nonzero exit code ($code):`n$text"
    }
    Write-Host "PASS: $Name"
}

try {
    foreach ($relative in @('scripts','logs','mods\3686673790')) {
        New-Item -ItemType Directory -Path (Join-Path $fixture $relative) -Force | Out-Null
    }
    $deployed = Join-Path $fixture 'winmm.dll'
    $bundled = Join-Path $fixture 'mods\3686673790\winmm.dll'
    Copy-Item -LiteralPath $ShimPath -Destination $deployed
    Copy-Item -LiteralPath $ShimPath -Destination $bundled
    Copy-Item -LiteralPath (Join-Path $repo 'scripts\patches.json') -Destination (Join-Path $fixture 'scripts\patches.json')
    $log = Join-Path $fixture 'logs\openshim.log'
    @('session start', 'Real winmm.dll loaded successfully', 'Initialization complete',
      'Winsock IAT hooks installed: 1', 'SO_SNDBUF 65536 -> 524288',
      'SO_RCVBUF 65536 -> 4194304') | Set-Content -LiteralPath $log

    Assert-Verdict $true 'identical coordinated deployment'
    # Preserve the PE version resource but change its content. The updater can
    # promote this same-version file, so hash equality must be decisive.
    $stream = [IO.File]::Open($bundled, [IO.FileMode]::Append)
    try { $stream.WriteByte(0) } finally { $stream.Dispose() }
    Assert-Verdict $false 'same version with different bytes'
    Copy-Item -LiteralPath $ShimPath -Destination $bundled -Force
    Add-Content -LiteralPath $log -Value '[STALE-CONFIG] test fixture'
    Assert-Verdict $false 'stale patch registration returns failure'
    Remove-Item -LiteralPath $log
    Assert-Verdict $false 'missing session log returns failure'
} finally {
    # Delete only this test's unique temporary directory after canonicalizing it.
    $resolved = [IO.Path]::GetFullPath($fixture)
    $tempRoot = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not $resolved.StartsWith($tempRoot, [StringComparison]::OrdinalIgnoreCase) -or
        [IO.Path]::GetFileName($resolved) -notlike 'openshim-verifier-*') {
        throw 'Refusing to clean an unexpected fixture path.'
    }
    if (Test-Path -LiteralPath $resolved) { Remove-Item -LiteralPath $resolved -Recurse -Force }
}
exit 0
