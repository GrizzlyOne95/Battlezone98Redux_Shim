# Runs the in-memory BSim two-program comparison and writes out\bsim_matches.csv.
# Assumes import_programs.ps1 already built + analyzed the bz_bsim project.
param(
    [int]$MaxMatches = 5,
    [double]$MinSim  = 0.50,
    [string]$Target  = "battlezone98redux.exe.unpacked.exe",
    [string]$Source  = "bzone.exe"
)
$ErrorActionPreference = "Stop"

$Ghidra   = "C:\ghidra_12.0.4_PUBLIC"
$Headless = Join-Path $Ghidra "support\analyzeHeadless.bat"
$Here     = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjLoc  = Join-Path $Here "project"
$ProjName = "bz_bsim"
$Scripts  = Join-Path $Here "ghidra_scripts"
$OutDir   = Join-Path $Here "out"
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$OutCsv   = Join-Path $OutDir "bsim_matches.csv"

Write-Host "=== BSim compare: $Source  ->  $Target  (top $MaxMatches, minSim $MinSim) ==="
# -process opens the source as currentProgram; -noanalysis because both are already analyzed.
# The post-script opens the target from the same project and writes the CSV itself.
& $Headless $ProjLoc $ProjName `
    -process $Source `
    -noanalysis `
    -scriptPath $Scripts `
    -postScript BSimCompareExport.java $Target $OutCsv $MaxMatches $MinSim `
    -log (Join-Path $Here "bsim_compare.log")
if ($LASTEXITCODE -ne 0) { throw "bsim compare failed ($LASTEXITCODE)" }

Write-Host "=== BSIM_COMPARE_DONE -> $OutCsv ==="
if (Test-Path $OutCsv) {
    $n = (Get-Content $OutCsv | Measure-Object -Line).Lines
    Write-Host "rows (incl header): $n"
}
