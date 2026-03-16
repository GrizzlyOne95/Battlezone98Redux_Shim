param(
    [string]$ReduxOutputRoot = "",
    [string]$LegacyOutputRoot = "",
    [string]$PortableRoot = "",
    [switch]$SkipRedux,
    [switch]$SkipLegacy
)

if ([string]::IsNullOrWhiteSpace($PortableRoot)) {
    $PortableRoot = Join-Path $PSScriptRoot "portable_corpora"
}

if ([string]::IsNullOrWhiteSpace($ReduxOutputRoot)) {
    $ReduxOutputRoot = Join-Path $PortableRoot "bzr_gog_best_effort"
}

if ([string]::IsNullOrWhiteSpace($LegacyOutputRoot)) {
    $LegacyOutputRoot = Join-Path $PortableRoot "legacy_bz1_exact_full"
}

$python = (Get-Command python -ErrorAction Stop).Source
$finalizer = Join-Path $PSScriptRoot "finalize_global_corpus.py"
if (-not (Test-Path $finalizer)) {
    throw "Missing corpus finalizer: $finalizer"
}

$targets = @()
if (-not $SkipRedux) {
    $targets += @{
        Label = "redux"
        OutputRoot = $ReduxOutputRoot
        PromotedRoot = (Join-Path $PSScriptRoot "current_global_corpus")
    }
}
if (-not $SkipLegacy) {
    $targets += @{
        Label = "legacy"
        OutputRoot = $LegacyOutputRoot
        PromotedRoot = (Join-Path $PSScriptRoot "current_legacy_global_corpus")
    }
}

$imported = @()
foreach ($target in $targets) {
    $outputRoot = [string]$target.OutputRoot
    $manifestPath = Join-Path $outputRoot "pipeline_manifest.json"
    if (-not (Test-Path $manifestPath)) {
        Write-Warning "Skipping $($target.Label): missing pipeline manifest at $manifestPath"
        continue
    }

    & $python $finalizer --output-root $outputRoot --promoted-root $target.PromotedRoot
    if ($LASTEXITCODE -ne 0) {
        throw "Failed to import corpus '$($target.Label)' from $outputRoot"
    }
    $imported += [pscustomobject]@{
        label = $target.Label
        output_root = (Resolve-Path $outputRoot).Path
        promoted_root = (Resolve-Path $target.PromotedRoot).Path
    }
}

if (-not $imported) {
    throw "No corpora were imported. Copy transferred corpus roots into $PortableRoot or pass explicit -ReduxOutputRoot / -LegacyOutputRoot."
}

$imported | ConvertTo-Json -Depth 3
