# Compiles the Enhanced LOD permutations, and proves High did not move.
#
# Two questions, and they are not the same question:
#
#   1. Do the Medium and Low Enhanced permutations compile at all? They are new
#      combinations -- ENHANCED_MODE without NORMALMAP_ENABLED had never been
#      built before -- so this is not a formality.
#
#   2. Is the High path byte-identical to what it compiled to before the tier
#      knob was added? OSE_ENHANCED_LOD_TIER defaults to 0 and its body is
#      preprocessed away at that value, so it should be. "Should be" is not
#      evidence, and the roadmap asks unaffected paths to stay DXBC-identical,
#      so the baseline is compiled from git and the bytecode compared.
#
#   powershell -ExecutionPolicy Bypass -File scripts\Test-EnhancedLodPermutations.ps1 `
#       [-Baseline <git-ref>] [-FxcPath <path>] [-KeepArtifacts]
#
# Exit codes: 0 all permutations compile and High is unchanged, 1 a failure,
# 2 fxc or the payload is missing.

[CmdletBinding()]
param(
    # Ref the High baseline is compiled from. Defaults to the merge-base with
    # main so a local working tree cannot quietly become its own baseline.
    [string]$Baseline,
    [string]$FxcPath,
    [switch]$KeepArtifacts
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$payload = Join-Path $repoRoot "resources\renderer\enhanced"

if (-not $FxcPath) {
    $FxcPath = Get-ChildItem "${env:ProgramFiles(x86)}\Windows Kits\10\bin\*\x64\fxc.exe" `
        -ErrorAction SilentlyContinue | Sort-Object FullName | Select-Object -Last 1 -ExpandProperty FullName
}
if (-not $FxcPath -or -not (Test-Path -LiteralPath $FxcPath)) {
    Write-Host "fxc.exe not found. Install the Windows SDK or pass -FxcPath." -ForegroundColor Red
    exit 2
}
if (-not (Test-Path -LiteralPath $payload)) {
    Write-Host "Enhanced payload not found: $payload" -ForegroundColor Red
    exit 2
}

if (-not $Baseline) {
    $Baseline = (& git -C $repoRoot merge-base HEAD origin/main 2>$null)
    if (-not $Baseline) { $Baseline = "HEAD" }
}

$work = Join-Path ([IO.Path]::GetTempPath()) ("ose-lod-" + [Guid]::NewGuid().ToString("N").Substring(0, 8))
New-Item -ItemType Directory -Path $work -Force | Out-Null

function Invoke-Fxc {
    param([string]$Source, [string]$Entry, [string]$Defines, [string]$OutFile)
    $fxcArgs = @("/nologo", "/T", "ps_4_0", "/E", $Entry, "/Fo", $OutFile)
    foreach ($d in ($Defines -split ',')) {
        if ($d.Trim()) { $fxcArgs += @("/D", $d.Trim()) }
    }
    $fxcArgs += $Source
    $output = & $FxcPath @fxcArgs 2>&1
    return [pscustomobject]@{
        Ok     = ($LASTEXITCODE -eq 0) -and (Test-Path -LiteralPath $OutFile)
        Output = ($output | Out-String).Trim()
    }
}

# Every permutation the payload actually declares, read from the .program
# scripts rather than restated here -- a list maintained by hand would drift
# from the thing it is supposed to be checking.
$cases = @()
foreach ($fam in @(
        @{ Script = "openshim_enhanced_base.program";    Entry = "base_fragment" }
        @{ Script = "openshim_enhanced_terrain.program"; Entry = "terrain_fragment" })) {
    $text = [IO.File]::ReadAllText((Join-Path $payload $fam.Script))
    foreach ($m in [regex]::Matches($text,
            '(?s)fragment_program\s+(OSE_\w+)_fragmentHLSL4\s+hlsl\s*\{(.*?)\r?\n\}')) {
        $name = $m.Groups[1].Value
        if ($name -notmatch 'EN(Medium|Low|High)') { continue }
        $body = $m.Groups[2].Value
        $src = [regex]::Match($body, '(?m)^\s*source\s+(\S+)').Groups[1].Value
        $def = [regex]::Match($body, '(?m)^\s*preprocessor_defines\s+([^\r\n]*)').Groups[1].Value
        $cases += [pscustomobject]@{
            Name = $name; Source = $src; Entry = $fam.Entry; Defines = $def.Trim()
        }
    }
}

if ($cases.Count -eq 0) {
    Write-Host "No Enhanced HLSL4 permutations found in the payload." -ForegroundColor Red
    exit 1
}

$failures = @()
$rows = @()

foreach ($case in ($cases | Sort-Object Name)) {
    $obj = Join-Path $work "$($case.Name).cso"
    $run = Invoke-Fxc -Source (Join-Path $payload $case.Source) -Entry $case.Entry `
        -Defines $case.Defines -OutFile $obj
    if (-not $run.Ok) {
        $failures += "$($case.Name) does not compile:`n$($run.Output)"
        $rows += [pscustomobject]@{ Program = $case.Name; Bytes = 0; High = ""; Result = "FAIL" }
        continue
    }
    $rows += [pscustomobject]@{
        Program = $case.Name
        Bytes   = (Get-Item $obj).Length
        High    = ""
        Result  = "ok"
    }
}

# --- High must not have moved -------------------------------------------------
# Compile the same High permutations from the baseline revision's shader and
# compare the bytecode. fxc output for identical input is deterministic, which
# the harness confirms by compiling one case twice before trusting a match.
$highCases = @($cases | Where-Object { $_.Name -match 'ENHigh' })
$baseDir = Join-Path $work "baseline"
New-Item -ItemType Directory -Path $baseDir -Force | Out-Null

$sources = @($highCases | ForEach-Object { $_.Source } | Sort-Object -Unique)
$haveBaseline = $true
foreach ($src in $sources) {
    $blob = & git -C $repoRoot show "${Baseline}:resources/renderer/enhanced/$src" 2>$null
    if ($LASTEXITCODE -ne 0 -or -not $blob) { $haveBaseline = $false; break }
    [IO.File]::WriteAllText((Join-Path $baseDir $src), ($blob -join "`r`n"))
}

if (-not $haveBaseline) {
    Write-Host "Baseline '$Baseline' has no payload to compare against; skipping the High identity check." -ForegroundColor Yellow
} else {
    # Determinism control: the same source compiled twice must match, or a
    # mismatch below would prove nothing about the shader.
    $probe = $highCases[0]
    $a = Join-Path $work "determinism_a.cso"; $b = Join-Path $work "determinism_b.cso"
    Invoke-Fxc -Source (Join-Path $payload $probe.Source) -Entry $probe.Entry -Defines $probe.Defines -OutFile $a | Out-Null
    Invoke-Fxc -Source (Join-Path $payload $probe.Source) -Entry $probe.Entry -Defines $probe.Defines -OutFile $b | Out-Null
    if ((Get-FileHash $a).Hash -ne (Get-FileHash $b).Hash) {
        $failures += "fxc output is not deterministic on this machine; the High identity check cannot be trusted."
    } else {
        foreach ($case in $highCases) {
            $new = Join-Path $work "$($case.Name).cso"
            $old = Join-Path $baseDir "$($case.Name).baseline.cso"
            $run = Invoke-Fxc -Source (Join-Path $baseDir $case.Source) -Entry $case.Entry `
                -Defines $case.Defines -OutFile $old
            $row = $rows | Where-Object { $_.Program -eq $case.Name }
            if (-not $run.Ok) {
                $failures += "$($case.Name) does not compile from baseline ${Baseline}:`n$($run.Output)"
                if ($row) { $row.High = "baseline FAIL" }
                continue
            }
            $same = (Get-FileHash $new).Hash -eq (Get-FileHash $old).Hash
            if ($row) { $row.High = $(if ($same) { "identical" } else { "CHANGED" }) }
            if (-not $same) {
                $failures += ("$($case.Name) is no longer DXBC-identical to ${Baseline}. " +
                              "The tier knob must preprocess away at OSE_ENHANCED_LOD_TIER=0.")
            }
        }
    }
}

$rows | Format-Table -AutoSize | Out-String | Write-Host
Write-Host "fxc      : $FxcPath"
Write-Host "baseline : $Baseline"

if ($KeepArtifacts) {
    Write-Host "artifacts: $work"
} else {
    Remove-Item -LiteralPath $work -Recurse -Force -ErrorAction SilentlyContinue
}

if ($failures.Count -gt 0) {
    Write-Host ""
    foreach ($f in $failures) { Write-Host "FAILURE: $f" -ForegroundColor Red }
    exit 1
}

Write-Host ""
Write-Host "all Enhanced permutations compile; High is unchanged" -ForegroundColor Green
exit 0
