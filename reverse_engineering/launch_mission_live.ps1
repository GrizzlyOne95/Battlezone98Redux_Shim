param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$MissionArgs = "mods/3686673790/misn03.bzn",
    # How long to wait (passively) for the sim to come up. The load voice-over is
    # no longer skipped: skipping needed SendInput + window activation, which the
    # never-activate harness forbids. The VO plays out on its own.
    [int]$InitTimeoutSeconds = 180,
    [switch]$KillExisting
)

$ErrorActionPreference = "Stop"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$bzLogger = Join-Path $GameRoot "logs\BZLogger.txt"
if (-not (Test-Path $gameExe)) { throw "exe not found: $gameExe" }

if (-not (Get-Command Assert-BZRSafeToLaunch -ErrorAction SilentlyContinue)) { . "$PSScriptRoot\BZRHarness.ps1" }

if ($KillExisting) {
    # Graceful only: Stop-BZRGame sends WM_CLOSE and escalates only if ignored.
    Stop-BZRGame
}

Write-Host "Launching: $gameExe $MissionArgs"
Assert-BZRSafeToLaunch
$proc = Start-BZRGameProcess -FilePath $gameExe -ArgumentList $MissionArgs -WorkingDirectory $GameRoot -PassThru
Write-Host "PID=$($proc.Id)"

function Read-Shared([string]$Path) {
    if (-not (Test-Path -LiteralPath $Path)) { return "" }
    $fs = [System.IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    try { $sr = New-Object System.IO.StreamReader($fs); return $sr.ReadToEnd() } finally { $fs.Dispose() }
}

# The game truncates BZLogger on launch, so a marker in the file belongs to this
# run once the process has been up for a moment; poll for the init marker.
$voSeen = $false
$initDone = $false
$deadline = (Get-Date).AddSeconds($InitTimeoutSeconds)
while ((Get-Date) -lt $deadline -and -not $proc.HasExited -and -not $initDone) {
    $txt = Read-Shared $bzLogger
    if ($txt -match 'Waiting For VO') { $voSeen = $true }
    if ($txt -match 'Game Simulation Initialized after') { $initDone = $true }
    Start-Sleep -Milliseconds 500
}

$proc.Refresh()
Write-Host "vo_seen=$voSeen init_done=$initDone has_exited=$($proc.HasExited) pid=$($proc.Id)"
Write-Host "LEFT RUNNING. Attach probes to PID $($proc.Id); stop with Stop-BZRGame -Id $($proc.Id)."
