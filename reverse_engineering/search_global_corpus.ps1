param(
    [Parameter(Mandatory = $true)]
    [string]$Pattern,
    [string]$PromotedRoot = "",
    [string[]]$Globs = @("*.md", "*.txt", "*.json", "*.csv", "*.c"),
    [switch]$IncludeDecomps,
    [switch]$IncludeLargeTextDumps
)

if ([string]::IsNullOrWhiteSpace($PromotedRoot)) {
    $PromotedRoot = Join-Path $PSScriptRoot "current_global_corpus"
}

$indexPath = Join-Path $PromotedRoot "current_index.json"
if (-not (Test-Path $indexPath)) {
    throw "Missing promoted corpus index: $indexPath"
}

$index = Get-Content $indexPath | ConvertFrom-Json
$root = $index.current_corpus_root
if (-not (Test-Path $root)) {
    throw "Promoted corpus root does not exist: $root"
}

$paths = @(
    (Join-Path $root "inventory"),
    (Join-Path $root "merged"),
    (Join-Path $root "pdb_reference"),
    (Join-Path $root "binary_strings")
)

if ($IncludeDecomps) {
    $paths += $index.manifest.decomp_dir
}

if ($IncludeLargeTextDumps) {
    $paths += (Join-Path $root "logs")
}

$existing = $paths | Where-Object { $_ -and (Test-Path $_) } | Select-Object -Unique
if (-not $existing) {
    throw "No search paths exist under promoted corpus root: $root"
}

$globArgs = @()
foreach ($glob in $Globs) {
    $globArgs += @("-g", $glob)
}

& rg --line-number --smart-case $globArgs -- $Pattern $existing
