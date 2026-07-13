# Imports the two binaries into a single Ghidra project and runs auto-analysis.
# Legacy bzone.exe is imported WITH bzint.pdb (symbols = the names we transfer);
# the unpacked Redux exe is imported without a PDB (we only need its function RVAs).
$ErrorActionPreference = "Stop"

$Ghidra   = "C:\ghidra_12.0.4_PUBLIC"
$Headless = Join-Path $Ghidra "support\analyzeHeadless.bat"

$Here     = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjLoc  = Join-Path $Here "project"
$ProjName = "bz_bsim"
$Staging  = Join-Path $Here "staging"
$Scripts  = Join-Path $Here "ghidra_scripts"

$LegacyExe = "C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe"
$LegacyPdb = "C:\Users\istuart\Downloads\bzone15227\extracted\bzint.pdb"
$ReduxExe  = "C:\Users\istuart\Documents\GIT\Battlezone98Redux_Shim\reverse_engineering\workshop\global_decompile\redux_documents_unpacked_beta_pdb_best_effort\static_unpack\battlezone98redux.exe.unpacked.exe"

New-Item -ItemType Directory -Force -Path $ProjLoc  | Out-Null
New-Item -ItemType Directory -Force -Path $Staging  | Out-Null

# Colocate exe+pdb so the PDB Universal analyzer finds bzint.pdb next to bzone.exe.
Copy-Item -Force $LegacyExe (Join-Path $Staging "bzone.exe")
Copy-Item -Force $LegacyPdb (Join-Path $Staging "bzint.pdb")
$LegacyStaged = Join-Path $Staging "bzone.exe"

Write-Host "=== [1/2] Importing + analyzing legacy bzone.exe (with bzint.pdb) ==="
# PdbUniversalAnalyzer will not search next to the file; a pre-script must force the PDB.
& $Headless $ProjLoc $ProjName `
    -import $LegacyStaged `
    -scriptPath $Scripts `
    -preScript SetPdbFile.java (Join-Path $Staging "bzint.pdb") `
    -analysisTimeoutPerFile 5400 `
    -log (Join-Path $Here "import_legacy.log")
if ($LASTEXITCODE -ne 0) { throw "legacy import failed ($LASTEXITCODE)" }

Write-Host "=== [2/2] Importing + analyzing unpacked Redux exe ==="
& $Headless $ProjLoc $ProjName `
    -import $ReduxExe `
    -analysisTimeoutPerFile 5400 `
    -log (Join-Path $Here "import_redux.log")
if ($LASTEXITCODE -ne 0) { throw "redux import failed ($LASTEXITCODE)" }

Write-Host "=== IMPORT_DONE ==="
