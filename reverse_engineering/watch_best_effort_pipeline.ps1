param(
    [Parameter(Mandatory = $true)]
    [int]$ProcessId,
    [Parameter(Mandatory = $true)]
    [string]$OutputRoot,
    [string]$PromotedRoot = "",
    [int]$PollSeconds = 30
)

$repoRoot = Split-Path -Parent $PSScriptRoot
$python = (Get-Command python).Source
$finalizer = Join-Path $PSScriptRoot "finalize_global_corpus.py"

if ([string]::IsNullOrWhiteSpace($PromotedRoot)) {
    $PromotedRoot = Join-Path $PSScriptRoot "current_global_corpus"
}

while ($true) {
    $proc = Get-Process -Id $ProcessId -ErrorAction SilentlyContinue
    if (-not $proc) {
        break
    }
    Start-Sleep -Seconds $PollSeconds
}

$manifest = Join-Path $OutputRoot "pipeline_manifest.json"
if (-not (Test-Path $manifest)) {
    throw "Pipeline exited but manifest is missing: $manifest"
}

& $python $finalizer --output-root $OutputRoot --promoted-root $PromotedRoot
if ($LASTEXITCODE -ne 0) {
    throw "Finalization failed with exit code $LASTEXITCODE"
}

Write-Output "Promoted corpus: $PromotedRoot"
