[CmdletBinding()]
param()

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $PSScriptRoot
$sourcePath = Join-Path $repoRoot 'src/patches/net_optimizer.cpp'
$iniPath = Join-Path $repoRoot 'net.ini'

foreach ($path in @($sourcePath, $iniPath)) {
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
        throw "Required validation input is missing: $path"
    }
}

$source = Get-Content -LiteralPath $sourcePath -Raw
$ini = Get-Content -LiteralPath $iniPath -Raw

function Assert-RegexCount {
    param(
        [Parameter(Mandatory)] [string] $Name,
        [Parameter(Mandatory)] [string] $Text,
        [Parameter(Mandatory)] [string] $Pattern,
        [int] $ExpectedCount = 1
    )

    $matches = [System.Text.RegularExpressions.Regex]::Matches(
        $Text,
        $Pattern,
        [System.Text.RegularExpressions.RegexOptions]::Multiline
    )

    if ($matches.Count -ne $ExpectedCount) {
        throw "$Name failed: expected $ExpectedCount match(es), found $($matches.Count)."
    }

    Write-Host "PASS: $Name"
}

function Assert-RegexAbsent {
    param(
        [Parameter(Mandatory)] [string] $Name,
        [Parameter(Mandatory)] [string] $Text,
        [Parameter(Mandatory)] [string] $Pattern
    )

    if ([System.Text.RegularExpressions.Regex]::IsMatch(
            $Text,
            $Pattern,
            [System.Text.RegularExpressions.RegexOptions]::Multiline)) {
        throw "$Name failed: unsafe pattern is present."
    }

    Write-Host "PASS: $Name"
}

Assert-RegexCount `
    -Name 'Built-in packet reorder default is disabled' `
    -Text $source `
    -Pattern 'bool\s+enablePacketReorder\s*=\s*false\s*;'

Assert-RegexCount `
    -Name 'Missing EnablePacketReorder INI key defaults to disabled' `
    -Text $source `
    -Pattern 'ReadIniBool\(\s*"OpenShimSocket"\s*,\s*"EnablePacketReorder"\s*,\s*false\s*\)'

Assert-RegexAbsent `
    -Name 'Unsafe packet reorder INI fallback is absent' `
    -Text $source `
    -Pattern 'ReadIniBool\(\s*"OpenShimSocket"\s*,\s*"EnablePacketReorder"\s*,\s*true\s*\)'

Assert-RegexCount `
    -Name 'Built-in packet duplication default is disabled' `
    -Text $source `
    -Pattern 'bool\s+sendDup\s*=\s*false\s*;'

Assert-RegexCount `
    -Name 'Shipped profile disables packet reorder' `
    -Text $ini `
    -Pattern '^\s*EnablePacketReorder\s*=\s*0\s*(?:;.*)?$'

Assert-RegexCount `
    -Name 'Shipped profile disables packet duplication' `
    -Text $ini `
    -Pattern '^\s*SendDup\s*=\s*0\s*(?:;.*)?$'

Assert-RegexCount `
    -Name 'Reorder wake thread remains gated by explicit reorder enablement' `
    -Text $source `
    -Pattern '(?s)if\s*\(\s*g_Config\.enablePacketReorder\s*&&\s*g_Config\.enableReorderWake\s*&&\s*!g_WakeThread\s*\)\s*\{.{0,800}?CreateThread\(\s*nullptr\s*,\s*0\s*,\s*ReorderWakeThread\b'

Assert-RegexCount `
    -Name 'Governor patch thread remains disabled at GovernorStart=0' `
    -Text $source `
    -Pattern 'if\s*\(\s*g_Config\.govStart\s*!=\s*0\s*&&\s*!g_GovPatchThread\s*\)'

Assert-RegexCount `
    -Name 'Experimental reorder warning remains present' `
    -Text $source `
    -Pattern 'EXPERIMENTAL packet reordering is enabled'

Assert-RegexCount `
    -Name 'Deprecated packet duplication warning remains present' `
    -Text $source `
    -Pattern 'DEPRECATED packet duplication is enabled'

Write-Host 'Network correctness baseline validation passed.'

if ($env:GITHUB_STEP_SUMMARY) {
    @(
        '## Network baseline validation'
        ''
        '- Packet reordering defaults remain disabled.'
        '- Packet duplication defaults remain disabled.'
        '- Reorder and governor worker creation remains explicitly gated.'
        '- Experimental feature warnings remain present.'
    ) | Add-Content -LiteralPath $env:GITHUB_STEP_SUMMARY
}
