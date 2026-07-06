# Extracts the Lua script-binding registration table from BOTH programs.
# 1.5 is run first as a self-check: its func pointers should resolve to functions
# already named like the documented API primitives. Redux then yields the exact RVAs.
param(
    [string]$ApiNames = "",
    [string]$Legacy   = "bzone.exe",
    [string]$Redux    = "battlezone98redux.exe.unpacked.exe"
)
$ErrorActionPreference = "Stop"

$Ghidra   = "C:\ghidra_12.0.4_PUBLIC"
$Headless = Join-Path $Ghidra "support\analyzeHeadless.bat"
$Here     = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjLoc  = Join-Path $Here "project"
$ProjName = "bz_bsim"
$Scripts  = Join-Path $Here "ghidra_scripts"
$OutDir   = Join-Path $Here "out"
if (-not $ApiNames) { $ApiNames = Join-Path $OutDir "lua_api_names.txt" }

function Run-Extract($program, $tag) {
    $outCsv = Join-Path $OutDir "lua_bindings_$tag.csv"
    Write-Host "=== Lua binding extract: $program -> $outCsv ==="
    & $Headless $ProjLoc $ProjName `
        -process $program `
        -noanalysis `
        -scriptPath $Scripts `
        -postScript LuaBindingTableExtractor.java $ApiNames $outCsv `
        -log (Join-Path $Here "lua_bindings_$tag.log")
    if ($LASTEXITCODE -ne 0) { throw "extract failed for $program ($LASTEXITCODE)" }
    if (Test-Path $outCsv) {
        $n = (Get-Content $outCsv | Measure-Object -Line).Lines
        Write-Host "rows (incl header): $n"
    }
}

Run-Extract $Legacy "legacy"
Run-Extract $Redux  "redux"
Write-Host "=== LUA_BINDINGS_DONE ==="
