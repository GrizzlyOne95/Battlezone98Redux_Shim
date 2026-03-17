param(
    [string]$ProcessName = "battlezone98redux.exe",
    [int]$TimeoutSeconds = 120,
    [double]$PollIntervalSeconds = 1.0,
    [string]$OutputRoot = "reverse_engineering/snapshots",
    [switch]$NoDumpSections,
    [switch]$Launch,
    [string]$GameExe = "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\battlezone98redux.exe"
)

$scriptDir = Split-Path -Parent $PSCommandPath
$pythonScript = Join-Path $scriptDir "capture_runtime_layout.py"

if ($Launch) {
    $baseName = [System.IO.Path]::GetFileNameWithoutExtension($ProcessName)
    if (-not (Get-Process -Name $baseName -ErrorAction SilentlyContinue)) {
        Start-Process -FilePath $GameExe | Out-Null
    }
}

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
    "--output-root", $OutputRoot
)

if ($NoDumpSections) {
    $arguments += "--no-dump-sections"
}

& $pythonCommand.Source @arguments
exit $LASTEXITCODE
