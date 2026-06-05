param(
    [string]$ArchivePath = "",
    [string]$DestinationRoot = "",
    [switch]$Force
)

$repoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")

if ([string]::IsNullOrWhiteSpace($ArchivePath)) {
    $ArchivePath = Join-Path $PSScriptRoot "corpus_artifacts\redux_documents_unpacked_beta_pdb_best_effort.zip"
}

if ([string]::IsNullOrWhiteSpace($DestinationRoot)) {
    $DestinationRoot = Join-Path $PSScriptRoot "workshop\global_decompile"
}

if (-not (Test-Path $ArchivePath)) {
    throw "Missing corpus archive: $ArchivePath. Run 'git lfs pull' first."
}

$repoRootFull = [System.IO.Path]::GetFullPath($repoRoot)
$destinationRootFull = [System.IO.Path]::GetFullPath($DestinationRoot)
if (-not $destinationRootFull.StartsWith($repoRootFull, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "Destination must be inside this repo: $destinationRootFull"
}

$corpusName = "redux_documents_unpacked_beta_pdb_best_effort"
$corpusRoot = Join-Path $destinationRootFull $corpusName
if ((Test-Path $corpusRoot) -and -not $Force) {
    throw "Destination already exists: $corpusRoot. Pass -Force to replace it."
}

if (Test-Path $corpusRoot) {
    $corpusRootFull = [System.IO.Path]::GetFullPath($corpusRoot)
    if (-not $corpusRootFull.StartsWith($repoRootFull, [System.StringComparison]::OrdinalIgnoreCase)) {
        throw "Refusing to delete path outside repo: $corpusRootFull"
    }
    Remove-Item -LiteralPath $corpusRootFull -Recurse -Force
}

New-Item -ItemType Directory -Force -Path $destinationRootFull | Out-Null
Expand-Archive -LiteralPath $ArchivePath -DestinationPath $destinationRootFull -Force

if (-not (Test-Path (Join-Path $corpusRoot "pipeline_manifest.json"))) {
    throw "Archive did not restore expected corpus: $corpusRoot"
}

python (Join-Path $PSScriptRoot "finalize_global_corpus.py") `
    --output-root $corpusRoot `
    --promoted-root (Join-Path $PSScriptRoot "current_global_corpus")

@"
Restored unpacked Redux corpus:
  $corpusRoot

Search:
  .\reverse_engineering\search_re_corpora.ps1 -CorpusLabels redux -Pattern "Producer" -IncludeDecomps
  python reverse_engineering\build_re_brief.py --query "weapon mask howitzer"
"@ | Write-Host
