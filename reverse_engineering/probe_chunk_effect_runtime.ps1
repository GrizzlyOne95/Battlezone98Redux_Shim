param(
    [string]$ProcessName = "battlezone98redux.exe",
    [int]$TimeoutSeconds = 120,
    [double]$PollIntervalSeconds = 0.05,
    [double]$SampleWindowSeconds = 2.0,
    [int]$MaxEntries = 16,
    [int]$MaxObjects = 8,
    [string]$OutputRoot = "reverse_engineering/snapshots"
)

$scriptDir = Split-Path -Parent $PSCommandPath
$pythonScript = Join-Path $scriptDir "probe_chunk_effect_runtime.py"

$pythonCommand = Get-Command python -ErrorAction SilentlyContinue
if (-not $pythonCommand) {
    $pythonCommand = Get-Command py -ErrorAction SilentlyContinue
}

if (-not $pythonCommand) {
    throw "python or py was not found on PATH."
}

$arguments = @(
    $pythonScript,
    "--process-name", $ProcessName,
    "--timeout", $TimeoutSeconds,
    "--poll-interval", $PollIntervalSeconds,
    "--sample-window", $SampleWindowSeconds,
    "--max-entries", $MaxEntries,
    "--max-objects", $MaxObjects,
    "--output-root", $OutputRoot
)

& $pythonCommand.Source @arguments
exit $LASTEXITCODE
