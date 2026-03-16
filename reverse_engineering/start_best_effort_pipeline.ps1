param(
    [string]$BinaryPath = "C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe",
    [string]$PdbPath = "",
    [string]$OutputRoot = "",
    [int]$ThreadCount = [Math]::Max(1, [Environment]::ProcessorCount / 2),
    [double]$MaxRamPercent = 50.0,
    [switch]$ForceAnalysis,
    [switch]$Callgraphs,
    [switch]$SkipCache,
    [switch]$SkipLLVM,
    [switch]$LightweightPdb,
    [switch]$ForcePdbInGhidra
)

$repoRoot = Split-Path -Parent $PSScriptRoot
$python = (Get-Command python).Source
$pipeline = Join-Path $PSScriptRoot "run_best_effort_pipeline.py"

if ([string]::IsNullOrWhiteSpace($OutputRoot)) {
    $OutputRoot = Join-Path $PSScriptRoot "workshop\global_decompile\latest"
}

New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null
$stdoutLog = Join-Path $OutputRoot "background_stdout.log"
$stderrLog = Join-Path $OutputRoot "background_stderr.log"
$pidFile = Join-Path $OutputRoot "background_pid.txt"

$arguments = @(
    $pipeline,
    "--binary", $BinaryPath,
    "--output-root", $OutputRoot,
    "--thread-count", "$ThreadCount",
    "--max-ram-percent", "$MaxRamPercent"
)

if (-not [string]::IsNullOrWhiteSpace($PdbPath)) {
    $arguments += @("--pdb", $PdbPath)
}
if ($ForceAnalysis) {
    $arguments += "--force-analysis"
}
if ($Callgraphs) {
    $arguments += "--callgraphs"
}
if ($SkipCache) {
    $arguments += "--skip-cache"
}
if ($SkipLLVM) {
    $arguments += "--skip-llvm"
}
if ($LightweightPdb) {
    $arguments += "--lightweight-pdb"
}
if ($ForcePdbInGhidra) {
    $arguments += "--force-pdb-in-ghidra"
}

$argumentString = ($arguments | ForEach-Object {
    if ($_ -match '[\s"]') {
        '"' + ($_ -replace '"', '\"') + '"'
    }
    else {
        $_
    }
}) -join ' '

$process = Start-Process -FilePath $python `
    -ArgumentList $argumentString `
    -WorkingDirectory $repoRoot `
    -RedirectStandardOutput $stdoutLog `
    -RedirectStandardError $stderrLog `
    -PassThru

Set-Content -Path $pidFile -Value $process.Id

Write-Output "PID: $($process.Id)"
Write-Output "OutputRoot: $OutputRoot"
Write-Output "StdOut: $stdoutLog"
Write-Output "StdErr: $stderrLog"
