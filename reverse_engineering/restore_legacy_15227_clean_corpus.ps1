param(
    [string]$ArchivePath = "",
    [string]$DestinationRoot = "",
    [switch]$Force
)

$repoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")

if ([string]::IsNullOrWhiteSpace($ArchivePath)) {
    $ArchivePath = Join-Path $PSScriptRoot "corpus_artifacts\legacy_15227_clean_pdb_c.zip"
}

if ([string]::IsNullOrWhiteSpace($DestinationRoot)) {
    $DestinationRoot = Join-Path $PSScriptRoot "decompilation_from_1.5_exe-pdb"
}

if (-not (Test-Path $ArchivePath)) {
    throw "Missing corpus archive: $ArchivePath. Run 'git lfs pull' first."
}

$destinationRootFull = [System.IO.Path]::GetFullPath($DestinationRoot)
$repoRootFull = [System.IO.Path]::GetFullPath($repoRoot)
if (-not $destinationRootFull.StartsWith($repoRootFull, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "Destination must be inside this repo: $destinationRootFull"
}

$cleanRoot = Join-Path $destinationRootFull "clean_pdb_c"
if ((Test-Path $cleanRoot) -and -not $Force) {
    throw "Destination already exists: $cleanRoot. Pass -Force to replace it."
}

if (Test-Path $cleanRoot) {
    $cleanRootFull = [System.IO.Path]::GetFullPath($cleanRoot)
    if (-not $cleanRootFull.StartsWith($repoRootFull, [System.StringComparison]::OrdinalIgnoreCase)) {
        throw "Refusing to delete path outside repo: $cleanRootFull"
    }
    Remove-Item -LiteralPath $cleanRootFull -Recurse -Force
}

New-Item -ItemType Directory -Force -Path $destinationRootFull | Out-Null
Expand-Archive -LiteralPath $ArchivePath -DestinationPath $destinationRootFull -Force

$expandedNested = Join-Path $destinationRootFull "clean_pdb_c"
if (-not (Test-Path (Join-Path $expandedNested "manifest.json"))) {
    throw "Archive did not restore the expected clean_pdb_c corpus under: $destinationRootFull"
}

$legacyPointer = Join-Path $PSScriptRoot "current_legacy_global_corpus"
New-Item -ItemType Directory -Force -Path $legacyPointer | Out-Null

$cleanFunctions = Join-Path $expandedNested "functions"
$existingIndex = Join-Path $legacyPointer "current_index.json"
$existingManifest = Join-Path $legacyPointer "current_manifest.json"

if ((Test-Path $existingManifest) -and (Test-Path $existingIndex)) {
    $manifest = Get-Content $existingManifest -Raw | ConvertFrom-Json
    $manifest.decomp_dir = $cleanFunctions
    $manifest | Add-Member -NotePropertyName clean_pdb_c_root -NotePropertyValue $expandedNested -Force
    $manifest | Add-Member -NotePropertyName clean_pdb_c_manifest -NotePropertyValue (Join-Path $expandedNested "manifest.json") -Force
    $manifest | ConvertTo-Json -Depth 20 | Set-Content $existingManifest -Encoding UTF8

    $index = Get-Content $existingIndex -Raw | ConvertFrom-Json
    $index.manifest.decomp_dir = $cleanFunctions
    $index.manifest | Add-Member -NotePropertyName clean_pdb_c_root -NotePropertyValue $expandedNested -Force
    $index.manifest | Add-Member -NotePropertyName clean_pdb_c_manifest -NotePropertyValue (Join-Path $expandedNested "manifest.json") -Force
    foreach ($target in $index.search_targets) {
        if ($target.label -eq "Decomp Root") {
            $target.path = $cleanFunctions
        }
    }
    $index | ConvertTo-Json -Depth 30 | Set-Content $existingIndex -Encoding UTF8
}
else {
    $cleanManifest = Get-Content (Join-Path $expandedNested "manifest.json") -Raw | ConvertFrom-Json
    $manifest = [pscustomobject]@{
        binary_path = "bzone.exe 1.5.2.27 Update 1"
        pdb_path = "bzint.pdb"
        output_root = $destinationRootFull
        counts = [pscustomobject]@{
            clean_pdb_function_records = $cleanManifest.function_count
            clean_pdb_decompiled = $cleanManifest.decompiled_count
            clean_pdb_failed = $cleanManifest.failed_count
        }
        pdb_exact_match = $true
        decomp_dir = $cleanFunctions
        clean_pdb_c_root = $expandedNested
        clean_pdb_c_manifest = (Join-Path $expandedNested "manifest.json")
    }
    $index = [pscustomobject]@{
        manifest = $manifest
        current_corpus_root = $destinationRootFull
        promoted_from = $ArchivePath
        search_targets = @(
            [pscustomobject]@{ label = "Decomp Root"; path = $cleanFunctions },
            [pscustomobject]@{ label = "Clean PDB C Manifest"; path = (Join-Path $expandedNested "manifest.json") },
            [pscustomobject]@{ label = "Clean PDB C Failures"; path = (Join-Path $expandedNested "decompile_failures.tsv") }
        )
    }
    $manifest | ConvertTo-Json -Depth 20 | Set-Content $existingManifest -Encoding UTF8
    $index | ConvertTo-Json -Depth 30 | Set-Content $existingIndex -Encoding UTF8
}

@"
Restored clean legacy corpus:
  $expandedNested

Search:
  .\reverse_engineering\search_legacy_15227_clean.ps1 -Pattern "Producer"
  .\reverse_engineering\search_re_corpora.ps1 -CorpusLabels legacy -Pattern "Producer" -IncludeDecomps
"@ | Write-Host
