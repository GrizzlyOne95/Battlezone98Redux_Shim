param(
    [Parameter(Mandatory = $true)]
    [string]$Pattern,
    [string[]]$CorpusLabels = @(),
    [string]$ConfigPath = "",
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

if ([string]::IsNullOrWhiteSpace($ConfigPath)) {
    $ConfigPath = Join-Path $PSScriptRoot "current_re_corpora.json"
}

if (-not (Test-Path $ConfigPath)) {
    throw "Missing corpus config: $ConfigPath"
}

$config = Get-Content $ConfigPath | ConvertFrom-Json
$configDir = Split-Path -Parent (Resolve-Path $ConfigPath)
$corpora = @($config.corpora)
if ($CorpusLabels.Count -gt 0) {
    $wanted = $CorpusLabels | ForEach-Object { $_.ToLowerInvariant() }
    $corpora = @($corpora | Where-Object { $wanted -contains $_.label.ToLowerInvariant() })
}

if (-not $corpora) {
    throw "No corpora selected from config: $ConfigPath"
}

$globArgs = @()
foreach ($glob in $Globs) {
    $globArgs += @("-g", $glob)
}

$searchedAny = $false

foreach ($corpus in $corpora) {
    $label = [string]$corpus.label
    $promotedRoot = [string]$corpus.promoted_root
    if (-not [System.IO.Path]::IsPathRooted($promotedRoot)) {
        $promotedRoot = Join-Path $configDir $promotedRoot
    }
    $indexPath = Join-Path $promotedRoot "current_index.json"
    if (-not (Test-Path $indexPath)) {
        Write-Warning "Skipping corpus '$label' because index is missing: $indexPath"
        continue
    }

    $index = Get-Content $indexPath | ConvertFrom-Json
    $root = Resolve-CorpusRoot -Candidate ([string]$index.current_corpus_root) -BaseDir $promotedRoot
    if (-not (Test-Path $root)) {
        Write-Warning "Skipping corpus '$label' because root does not exist: $root"
        continue
    }

    $paths = @(
        (Join-Path $root "inventory"),
        (Join-Path $root "merged"),
        (Join-Path $root "pdb_reference"),
        (Join-Path $root "binary_strings")
    )

    if ($IncludeDecomps) {
        $paths += (Resolve-CorpusRoot -Candidate ([string]$index.manifest.decomp_dir) -BaseDir $promotedRoot)
    }

    if ($IncludeLargeTextDumps) {
        $paths += (Join-Path $root "logs")
    }

    $existing = $paths | Where-Object { $_ -and (Test-Path $_) } | Select-Object -Unique
    if (-not $existing) {
        Write-Warning "Skipping corpus '$label' because no search paths exist under: $root"
        continue
    }

    $searchedAny = $true
    Write-Host "=== [$label] $root ==="
    & rg --line-number --smart-case $globArgs -- $Pattern $existing
    $exitCode = $LASTEXITCODE
    if ($exitCode -gt 1) {
        throw "rg failed for corpus '$label' with exit code $exitCode"
    }
    Write-Host ""
}

if (-not $searchedAny) {
    throw "No corpora were searchable from config: $ConfigPath"
}
