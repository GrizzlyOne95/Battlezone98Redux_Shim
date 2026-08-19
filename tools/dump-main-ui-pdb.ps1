param(
    [string]$PdbPath = "battlezone98redux.pdb",
    [string]$OutputDirectory = "artifacts/main-ui-re"
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

function Find-LlvmPdbUtil {
    $candidates = @()

    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path -LiteralPath $vswhere) {
        $installations = & $vswhere -products * -format json | ConvertFrom-Json
        foreach ($installation in $installations) {
            if (-not $installation.installationPath) { continue }
            $root = [string]$installation.installationPath
            $candidates += Join-Path $root "VC\Tools\Llvm\x64\bin\llvm-pdbutil.exe"
            $candidates += Join-Path $root "VC\Tools\Llvm\bin\llvm-pdbutil.exe"
        }
    }

    $pathHit = Get-Command llvm-pdbutil.exe -ErrorAction SilentlyContinue
    if ($pathHit) { $candidates += $pathHit.Source }

    foreach ($candidate in $candidates | Select-Object -Unique) {
        if ($candidate -and (Test-Path -LiteralPath $candidate -PathType Leaf)) {
            return (Resolve-Path -LiteralPath $candidate).Path
        }
    }

    throw "llvm-pdbutil.exe was not found in the Visual Studio LLVM toolsets or PATH"
}

function Write-MatchingBlocks {
    param(
        [Parameter(Mandatory=$true)][string[]]$Lines,
        [Parameter(Mandatory=$true)][string]$Pattern,
        [Parameter(Mandatory=$true)][string]$Path,
        [int]$Before = 5,
        [int]$After = 8
    )

    $selected = [System.Collections.Generic.SortedSet[int]]::new()
    for ($i = 0; $i -lt $Lines.Count; ++$i) {
        if ($Lines[$i] -match $Pattern) {
            $start = [Math]::Max(0, $i - $Before)
            $end = [Math]::Min($Lines.Count - 1, $i + $After)
            for ($j = $start; $j -le $end; ++$j) {
                [void]$selected.Add($j)
            }
        }
    }

    $output = [System.Collections.Generic.List[string]]::new()
    $last = -2
    foreach ($index in $selected) {
        if ($index -gt ($last + 1)) { $output.Add("---") }
        $output.Add($Lines[$index])
        $last = $index
    }
    $output | Set-Content -LiteralPath $Path -Encoding UTF8
}

$pdb = (Resolve-Path -LiteralPath $PdbPath).Path
$tool = Find-LlvmPdbUtil
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null

Write-Host "llvm-pdbutil: $tool"
Write-Host "PDB: $pdb"

$publicRaw = Join-Path $OutputDirectory "pdb_publics_globals.txt"
$typeRaw = Join-Path $OutputDirectory "pdb_types.txt"
$uiSymbols = Join-Path $OutputDirectory "ui_symbol_context.txt"
$uiTypes = Join-Path $OutputDirectory "ui_type_context.txt"
$summaryPath = Join-Path $OutputDirectory "ui_inventory_summary.txt"

# Public/global records give us named functions/data plus section:offset records.
& $tool dump -publics -globals $pdb 2>&1 | Out-File -LiteralPath $publicRaw -Encoding utf8
if ($LASTEXITCODE -ne 0) { throw "llvm-pdbutil public/global dump failed with $LASTEXITCODE" }

# TPI/IPI records give us class/type topology and member signatures. This can be
# large, but CI retains the full artifact while the report below only keeps cUI context.
& $tool dump -types $pdb 2>&1 | Out-File -LiteralPath $typeRaw -Encoding utf8
if ($LASTEXITCODE -ne 0) { throw "llvm-pdbutil type dump failed with $LASTEXITCODE" }

$publicLines = Get-Content -LiteralPath $publicRaw
$typeLines = Get-Content -LiteralPath $typeRaw

Write-MatchingBlocks -Lines $publicLines -Pattern 'cUI_' -Path $uiSymbols -Before 5 -After 8
Write-MatchingBlocks -Lines $typeLines -Pattern 'cUI_' -Path $uiTypes -Before 7 -After 16

# Build a compact unique-name inventory that is stable enough to diff between
# future PDBs. Keep both undecorated cUI_* tokens and MSVC decorated fragments.
$allUiLines = @($publicLines + $typeLines) | Where-Object { $_ -match 'cUI_' }
$tokens = [System.Collections.Generic.SortedSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)
foreach ($line in $allUiLines) {
    foreach ($m in [regex]::Matches($line, 'cUI_[A-Za-z0-9_]+')) {
        [void]$tokens.Add($m.Value)
    }
}

$summary = [System.Collections.Generic.List[string]]::new()
$summary.Add("Redux main/shell UI PDB inventory")
$summary.Add("================================")
$summary.Add("PDB: $([IO.Path]::GetFileName($pdb))")
$summary.Add("llvm-pdbutil: $tool")
$summary.Add("cUI-bearing public/type lines: $($allUiLines.Count)")
$summary.Add("unique cUI tokens: $($tokens.Count)")
$summary.Add("")
$summary.Add("Unique cUI class/name tokens")
$summary.Add("---------------------------")
foreach ($token in $tokens) { $summary.Add($token) }
$summary.Add("")
$summary.Add("Files")
$summary.Add("-----")
$summary.Add("ui_symbol_context.txt - cUI public/global records with address context")
$summary.Add("ui_type_context.txt   - cUI TPI/IPI records with type/member context")
$summary.Add("pdb_publics_globals.txt / pdb_types.txt - complete raw llvm-pdbutil dumps")

$summary | Set-Content -LiteralPath $summaryPath -Encoding UTF8

Write-Host ""
Write-Host "=== UI PDB SUMMARY ==="
Get-Content -LiteralPath $summaryPath
Write-Host ""
Write-Host "=== FIRST UI SYMBOL CONTEXT ==="
Get-Content -LiteralPath $uiSymbols -TotalCount 500
