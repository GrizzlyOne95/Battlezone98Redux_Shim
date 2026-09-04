# Installs the opt-in OpenShim remote-support sidecar on Windows.
#
# This does NOT install or replace OpenShim itself. It only places the support
# wrapper/transport under %LOCALAPPDATA%\openshim and records the public support
# Worker endpoint. Nothing uploads unless the printed wrapper is placed in
# Steam launch options.
#
# Qualification usage before a production endpoint is baked in:
#   $env:OPENSHIM_SUPPORT_ENDPOINT='https://YOUR-WORKER.workers.dev'; \
#     irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/agent/openshim-support-telemetry/scripts/install_support_windows.ps1 | iex

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repoSlug = if ($env:OPENSHIM_REPO) { $env:OPENSHIM_REPO } else { 'GrizzlyOne95/Battlezone98Redux_Shim' }
$ref = if ($env:OPENSHIM_REF) { $env:OPENSHIM_REF } else { 'agent/openshim-support-telemetry' }
$endpoint = if ($env:OPENSHIM_SUPPORT_ENDPOINT) { $env:OPENSHIM_SUPPORT_ENDPOINT.TrimEnd('/') } else { '' }

if ($repoSlug -notmatch '^[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+$') {
    throw "Refusing malformed OPENSHIM_REPO '$repoSlug'."
}
if ($ref -notmatch '^[A-Za-z0-9._/-]+$' -or $ref -match '^-|\.\.|//|/$') {
    throw "Refusing malformed OPENSHIM_REF '$ref'."
}
if (-not $endpoint) {
    throw 'OPENSHIM_SUPPORT_ENDPOINT is required until the production Worker URL is assigned.'
}
if ($endpoint -notmatch '^https://[A-Za-z0-9.-]+(?::\d+)?(?:/.*)?$') {
    throw 'OPENSHIM_SUPPORT_ENDPOINT must be an HTTPS URL.'
}

$dataDir = Join-Path $env:LOCALAPPDATA 'openshim'
$confDir = Join-Path $env:APPDATA 'openshim'
$confFile = Join-Path $confDir 'upload.conf'
$files = @(
    'openshim_support_transport.ps1',
    'openshim_support_wrap.ps1',
    'openshim_support_wrap.bat'
)

New-Item -ItemType Directory -Force -Path $dataDir, $confDir | Out-Null

function Get-SourceFile {
    param([string]$Name, [string]$Destination)

    # A local checkout is useful for branch qualification and avoids an
    # unnecessary network round trip. Piped installers have no usable
    # PSScriptRoot and fall back to the raw GitHub source below.
    if ($PSScriptRoot) {
        $root = Split-Path -Parent $PSScriptRoot
        $local = Join-Path (Join-Path $root 'upload') $Name
        if (Test-Path -LiteralPath $local -PathType Leaf) {
            Copy-Item -Force -LiteralPath $local -Destination $Destination
            return
        }
    }

    $uri = "https://raw.githubusercontent.com/$repoSlug/$ref/upload/$Name"
    Invoke-WebRequest -Uri $uri -UseBasicParsing -OutFile $Destination
    if (-not (Test-Path -LiteralPath $Destination -PathType Leaf) -or
        (Get-Item -LiteralPath $Destination).Length -eq 0) {
        throw "Downloaded empty support file: $Name"
    }
}

foreach ($name in $files) {
    $temp = Join-Path $env:TEMP ("openshim-support-{0}-{1}" -f ([Guid]::NewGuid().ToString('N')), $name)
    try {
        Get-SourceFile -Name $name -Destination $temp
        Move-Item -Force -LiteralPath $temp -Destination (Join-Path $dataDir $name)
    } finally {
        Remove-Item -Force -LiteralPath $temp -ErrorAction SilentlyContinue
    }
}

# Preserve PR #116's existing Discord uploader settings if present. The new
# endpoint is just another non-secret key in the same private config file.
$existing = @()
if (Test-Path -LiteralPath $confFile -PathType Leaf) {
    $existing = @(Get-Content -LiteralPath $confFile | Where-Object {
        $_ -notmatch '^\s*OPENSHIM_SUPPORT_ENDPOINT\s*=' -and
        $_ -notmatch '^\s*OPENSHIM_SUPPORT_INCLUDE_DUMPS\s*='
    })
}

$includeDumps = if ($env:OPENSHIM_SUPPORT_INCLUDE_DUMPS -eq '1') { '1' } else { '0' }
@(
    $existing
    "OPENSHIM_SUPPORT_ENDPOINT='$endpoint'"
    "OPENSHIM_SUPPORT_INCLUDE_DUMPS=$includeDumps"
) | Out-File -LiteralPath $confFile -Encoding UTF8

# Parse the scripts using the same Windows PowerShell parser the Steam wrapper
# will use. Do not install a launch option that points at syntactically broken
# support tooling.
foreach ($path in @(
    (Join-Path $dataDir 'openshim_support_transport.ps1'),
    (Join-Path $dataDir 'openshim_support_wrap.ps1')
)) {
    $tokens = $null
    $errors = $null
    [void][System.Management.Automation.Language.Parser]::ParseFile(
        $path,
        [ref]$tokens,
        [ref]$errors)
    if ($errors.Count -gt 0) {
        $messages = ($errors | ForEach-Object { $_.Message }) -join '; '
        throw "Installed support script failed PowerShell parsing: $path - $messages"
    }
}

Write-Host ''
Write-Host 'OpenShim remote support sidecar installed.' -ForegroundColor Green
Write-Host "Endpoint: $endpoint"
Write-Host "Crash minidump upload: $(if ($includeDumps -eq '1') { 'ENABLED' } else { 'off (text crash logs still upload)' })"
Write-Host ''
Write-Host 'Nothing uploads until you opt in by setting this Battlezone Steam launch option:' -ForegroundColor Yellow
Write-Host ''
Write-Host '  cmd /c ""%LOCALAPPDATA%\openshim\openshim_support_wrap.bat" %command%"' -ForegroundColor Cyan
Write-Host ''
Write-Host 'Remove that Steam launch option when the support session is over.'
Write-Host 'The most recent OCP support ID is also saved to:'
Write-Host "  $(Join-Path $dataDir 'latest-support-id.txt')"
