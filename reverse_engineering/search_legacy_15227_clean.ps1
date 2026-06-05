param(
    [Parameter(Mandatory = $true)]
    [string]$Pattern,
    [string]$Root = "",
    [string[]]$Globs = @("*.c", "*.tsv", "*.json", "*.md"),
    [switch]$IncludeFailedAsm
)

if ([string]::IsNullOrWhiteSpace($Root)) {
    $Root = Join-Path $PSScriptRoot "decompilation_from_1.5_exe-pdb\clean_pdb_c"
}

if (-not (Test-Path $Root)) {
    throw "Clean legacy PDB corpus is missing: $Root"
}

$paths = @(
    (Join-Path $Root "function_index.tsv"),
    (Join-Path $Root "decompile_failures.tsv"),
    (Join-Path $Root "manifest.json"),
    (Join-Path $Root "README.md"),
    (Join-Path $Root "functions")
)

if ($IncludeFailedAsm) {
    $paths += (Join-Path $Root "failed_asm")
    if ($Globs -notcontains "*.asm") {
        $Globs += "*.asm"
    }
}

$existing = $paths | Where-Object { Test-Path $_ } | Select-Object -Unique
if (-not $existing) {
    throw "No searchable paths exist under: $Root"
}

$globArgs = @()
foreach ($glob in $Globs) {
    $globArgs += @("-g", $glob)
}

& rg --line-number --smart-case $globArgs -- $Pattern $existing
$exitCode = $LASTEXITCODE
if ($exitCode -gt 1) {
    throw "rg failed with exit code $exitCode"
}
