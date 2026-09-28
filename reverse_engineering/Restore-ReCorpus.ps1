<#
.SYNOPSIS
Copies the private reverse-engineering corpus into this checkout's git-ignored paths.

.DESCRIPTION
The decompiler corpus, the PDB-derived corpus zips and the 2016 prerelease
binaries are not tracked in this public repository. They live in the private
GrizzlyOne95/Battlezone_Source repository under BZ1\Redux\openshim_re_corpus.
This script copies them to the paths OpenShim's tooling reads:

  bzr_gog_best_effort\           -> reverse_engineering\repo_corpora\bzr_gog_best_effort\
  corpus_artifacts\*.zip         -> reverse_engineering\corpus_artifacts\
  prerelease_2016_exes\          -> reverse_engineering\prerelease_2016\exes\
  prerelease_2016_removed_files\ -> reverse_engineering\prerelease_2016\removed_files\ (tool binaries)

Existing files are overwritten; nothing else is touched.

.EXAMPLE
pwsh -File reverse_engineering\Restore-ReCorpus.ps1
pwsh -File reverse_engineering\Restore-ReCorpus.ps1 -SourceRoot D:\src\Battlezone_Source
#>
param(
    # A Battlezone_Source checkout. Defaults to a sibling of this repository.
    [string]$SourceRoot = (Join-Path (Split-Path -Parent (Split-Path -Parent $PSScriptRoot)) 'Battlezone_Source')
)

$ErrorActionPreference = 'Stop'
$corpus = Join-Path $SourceRoot 'BZ1\Redux\openshim_re_corpus'
if (-not (Test-Path -LiteralPath $corpus)) {
    throw "Corpus not found at '$corpus'. Clone the private Battlezone_Source repository (main) and pass -SourceRoot."
}

$map = @(
    @{ From = 'bzr_gog_best_effort';           To = 'repo_corpora\bzr_gog_best_effort' },
    @{ From = 'corpus_artifacts';              To = 'corpus_artifacts' },
    @{ From = 'prerelease_2016_exes';          To = 'prerelease_2016\exes' },
    @{ From = 'prerelease_2016_removed_files'; To = 'prerelease_2016\removed_files' }
)

foreach ($entry in $map) {
    $from = Join-Path $corpus $entry.From
    $to = Join-Path $PSScriptRoot $entry.To
    if (-not (Test-Path -LiteralPath $from)) {
        Write-Warning "missing in source: $from"
        continue
    }
    New-Item -ItemType Directory -Force -Path $to | Out-Null
    Copy-Item -Path (Join-Path $from '*') -Destination $to -Recurse -Force
    $count = (Get-ChildItem -LiteralPath $to -Recurse -File | Measure-Object).Count
    Write-Host ("restored {0,-30} -> reverse_engineering\{1} ({2} files)" -f $entry.From, $entry.To, $count)
}
