# End-to-end: import + analyze -> BSim compare -> merge into the symbol-map pipeline.
$ErrorActionPreference = "Stop"
$Here = Split-Path -Parent $MyInvocation.MyCommand.Path

& (Join-Path $Here "import_programs.ps1")
& (Join-Path $Here "run_bsim_compare.ps1")

$py = Get-Command python -ErrorAction SilentlyContinue
if (-not $py) { $py = Get-Command py -ErrorAction SilentlyContinue }
if (-not $py) { throw "python not found on PATH" }
& $py.Source (Join-Path $Here "merge_bsim_into_symbol_map.py")

Write-Host "=== RUN_ALL_DONE ==="
