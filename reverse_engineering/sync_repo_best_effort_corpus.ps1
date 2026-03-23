param(
    [string]$SourceRoot = "",
    [string]$DestinationRoot = ""
)

$ErrorActionPreference = "Stop"

if ([string]::IsNullOrWhiteSpace($SourceRoot)) {
    $SourceRoot = Join-Path $PSScriptRoot "workshop\global_decompile\bzr_gog_best_effort"
}

if ([string]::IsNullOrWhiteSpace($DestinationRoot)) {
    $DestinationRoot = Join-Path $PSScriptRoot "repo_corpora\bzr_gog_best_effort"
}

$SourceRoot = (Resolve-Path $SourceRoot).Path

if (-not (Test-Path $SourceRoot)) {
    throw "Missing source corpus: $SourceRoot"
}

New-Item -ItemType Directory -Force -Path $DestinationRoot | Out-Null

$copyItems = @(
    "binary_strings",
    "ghidrecomp",
    "inventory",
    "merged",
    "pdb_reference",
    "pipeline_manifest.json",
    "SUMMARY.md"
)

foreach ($item in $copyItems) {
    $sourcePath = Join-Path $SourceRoot $item
    if (-not (Test-Path $sourcePath)) {
        throw "Missing corpus item: $sourcePath"
    }

    $destPath = Join-Path $DestinationRoot $item
    if ((Get-Item $sourcePath) -is [System.IO.DirectoryInfo]) {
        New-Item -ItemType Directory -Force -Path $destPath | Out-Null
        & robocopy $sourcePath $destPath /MIR /NFL /NDL /NJH /NJS /NC /NS /NP | Out-Null
        if ($LASTEXITCODE -ge 8) {
            throw "robocopy failed for $sourcePath -> $destPath with exit code $LASTEXITCODE"
        }
    }
    else {
        if (Test-Path $destPath) {
            Remove-Item -Force $destPath
        }
        Copy-Item -Force $sourcePath $destPath
    }
}

$manifest = [ordered]@{
    binary_path = "battlezone98redux.exe (GOG source binary not bundled)"
    binary_sha256 = "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413"
    pdb_path = "battlezone98redux.pdb (advisory PDB source not bundled)"
    output_root = "."
    ghidra_project_path = "ghidra_projects"
    ghidra_project_name = "battlezone98redux.exe-6777ca"
    counts = [ordered]@{
        ascii_strings = 15255
        utf16_strings = 77
        merged_rva_names = 497
    }
    pdb_exact_match = $false
    decomp_dir = "ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps"
    inventory_dir = "inventory"
    strings_dir = "binary_strings"
    pdb_dir = "pdb_reference"
    logs_dir = "logs"
}

$index = [ordered]@{
    manifest = $manifest
    current_corpus_root = "."
    promoted_from = "repo_corpora/bzr_gog_best_effort"
    search_targets = @(
        @{ label = "Summary"; path = "SUMMARY.md" }
        @{ label = "Pipeline Manifest"; path = "pipeline_manifest.json" }
        @{ label = "Inventory Functions"; path = "inventory/functions.csv" }
        @{ label = "Inventory Symbols"; path = "inventory/symbols.csv" }
        @{ label = "Merged RVA Matches"; path = "merged/function_matches_by_rva.csv" }
        @{ label = "PDB Public Functions"; path = "pdb_reference/public_functions.csv" }
        @{ label = "PDB Modules"; path = "pdb_reference/modules.csv" }
        @{ label = "ASCII Strings"; path = "binary_strings/ascii_strings.csv" }
        @{ label = "UTF16 Strings"; path = "binary_strings/utf16_strings.csv" }
        @{ label = "Decomp Root"; path = "ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps" }
    )
}

$readme = @'
# Repo-Tracked Redux Best-Effort Corpus

This is the trimmed portable Battlezone 98 Redux GOG best-effort decompile
bundle tracked in the repo for use on other PCs.

Included:
- ghidrecomp decomp output
- inventory CSVs
- merged RVA name matches
- PDB reference exports
- binary string dumps
- portable current corpus index/manifest

Excluded:
- ghidra_projects
- local background/watcher pid files
- local pipeline logs

Refresh from a local workshop output with:

```powershell
.\reverse_engineering\sync_repo_best_effort_corpus.ps1
```
'@

$utf8NoBom = New-Object System.Text.UTF8Encoding($false)
[System.IO.File]::WriteAllText((Join-Path $DestinationRoot "current_manifest.json"), ($manifest | ConvertTo-Json -Depth 6), $utf8NoBom)
[System.IO.File]::WriteAllText((Join-Path $DestinationRoot "current_index.json"), ($index | ConvertTo-Json -Depth 6), $utf8NoBom)
[System.IO.File]::WriteAllText((Join-Path $DestinationRoot "README.md"), $readme, $utf8NoBom)

Write-Host "Repo-tracked Redux best-effort corpus synced to: $DestinationRoot"
