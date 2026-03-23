param(
    [Parameter(Mandatory = $true)]
    [string]$Pattern,
    [string]$PromotedRoot = "",
    [string[]]$Globs = @("*.md", "*.txt", "*.json", "*.csv", "*.c"),
    [switch]$IncludeDecomps,
    [switch]$IncludeLargeTextDumps
)

function Resolve-CorpusRoot {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Candidate,
        [Parameter(Mandatory = $true)]
        [string]$BaseDir
    )

    if ([string]::IsNullOrWhiteSpace($Candidate)) {
        return $null
    }

    if ([System.IO.Path]::IsPathRooted($Candidate)) {
        return $Candidate
    }

    return Join-Path $BaseDir $Candidate
}

if ([string]::IsNullOrWhiteSpace($PromotedRoot)) {
    $localPromotedRoot = Join-Path $PSScriptRoot "current_global_corpus"
    $repoPromotedRoot = Join-Path $PSScriptRoot "repo_corpora\bzr_gog_best_effort"
    if (Test-Path (Join-Path $localPromotedRoot "current_index.json")) {
        $PromotedRoot = $localPromotedRoot
    }
    else {
        $PromotedRoot = $repoPromotedRoot
    }
}

$indexPath = Join-Path $PromotedRoot "current_index.json"
if (-not (Test-Path $indexPath)) {
    throw "Missing promoted corpus index: $indexPath"
}

$index = Get-Content $indexPath | ConvertFrom-Json
$root = Resolve-CorpusRoot -Candidate ([string]$index.current_corpus_root) -BaseDir $PromotedRoot
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
    $paths += (Resolve-CorpusRoot -Candidate ([string]$index.manifest.decomp_dir) -BaseDir $PromotedRoot)
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
