[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$BasePath,

    [Parameter(Mandatory)]
    [string]$ExpandedPath,

    [Parameter(Mandatory)]
    [string]$OutputCsv
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$BasePath = [System.IO.Path]::GetFullPath($BasePath).TrimEnd('\')
$ExpandedPath = [System.IO.Path]::GetFullPath($ExpandedPath).TrimEnd('\')
$OutputCsv = [System.IO.Path]::GetFullPath($OutputCsv)

function Get-TreeHashes {
    param([Parameter(Mandatory)][string]$Root)

    $hashes = @{}
    Get-ChildItem -LiteralPath $Root -Recurse -File | ForEach-Object {
        $relative = $_.FullName.Substring($Root.Length).TrimStart('\')
        $hashes[$relative] = (Get-FileHash -Algorithm SHA256 -LiteralPath $_.FullName).Hash
    }
    return $hashes
}

$baseHashes = Get-TreeHashes -Root $BasePath
$expandedHashes = Get-TreeHashes -Root $ExpandedPath
$allPaths = @($baseHashes.Keys + $expandedHashes.Keys | Sort-Object -Unique)
$rows = foreach ($relative in $allPaths) {
    $inBase = $baseHashes.ContainsKey($relative)
    $inExpanded = $expandedHashes.ContainsKey($relative)
    $status = if (-not $inBase) {
        'Added'
    } elseif (-not $inExpanded) {
        'Removed'
    } elseif ($baseHashes[$relative] -ne $expandedHashes[$relative]) {
        'Changed'
    } else {
        'Unchanged'
    }
    if ($status -ne 'Unchanged') {
        [pscustomobject]@{
            Status = $status
            RelativePath = $relative
            BaseSHA256 = if ($inBase) { $baseHashes[$relative] } else { $null }
            ExpandedSHA256 = if ($inExpanded) { $expandedHashes[$relative] } else { $null }
        }
    }
}

$parent = Split-Path -Parent $OutputCsv
New-Item -ItemType Directory -Path $parent -Force | Out-Null
$rows | Export-Csv -LiteralPath $OutputCsv -NoTypeInformation
$rows | Group-Object Status | Sort-Object Name | Select-Object Name, Count
