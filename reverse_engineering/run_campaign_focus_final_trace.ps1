param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$GameArgs = "/nointro",
    [int]$AttachPid = 0,
    [string]$OutputDirectory = "",
    [int]$DurationSeconds = 0
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$traceScript = Join-Path $PSScriptRoot "campaign_focus_final_trace.js"
if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game executable not found: $gameExe" }
if (-not (Test-Path -LiteralPath $traceScript)) { throw "Trace script not found: $traceScript" }

if (-not $OutputDirectory) {
    $stamp = Get-Date -Format "yyyyMMdd_HHmmss"
    $OutputDirectory = Join-Path $PSScriptRoot "runtime_traces\campaign_focus_final_$stamp"
}
New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null

$launched = $false
if ($AttachPid -gt 0) {
    $game = Get-Process -Id $AttachPid -ErrorAction Stop
    if ($game.ProcessName -ne "battlezone98redux") { throw "PID $AttachPid is not battlezone98redux" }
} else {
    # This is intentionally visible: during the later unlocked validation the
    # tester only needs to complete/force the custom final mission and observe.
    $game = Start-Process -FilePath $gameExe -ArgumentList $GameArgs -WorkingDirectory $GameRoot -PassThru
    $launched = $true
}

# Attach before the render window appears so the trace includes the earliest
# activation/size messages. A window handle is not required for Frida attach.
Start-Sleep -Milliseconds 500
$game.Refresh()
if ($game.HasExited) { throw "Redux exited before Frida could attach" }

$exeHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $gameExe).Hash
$exeInfo = Get-Item -LiteralPath $gameExe
$manifest = [ordered]@{
    captured_at = (Get-Date).ToString("o")
    executable = $gameExe
    sha256 = $exeHash
    file_size = $exeInfo.Length
    pid = $game.Id
    launched_by_script = $launched
    arguments = $GameArgs
    trace_script = $traceScript
}
$manifest | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $OutputDirectory "manifest.json") -Encoding UTF8

$stdout = Join-Path $OutputDirectory "campaign_focus_trace.log"
$stderr = Join-Path $OutputDirectory "campaign_focus_trace.err.log"
$fridaArgs = @("-p", $game.Id, "-q", "-t", "inf", "-l", $traceScript)
$frida = Start-Process -FilePath "bzr-frida.cmd" -ArgumentList $fridaArgs -WorkingDirectory $repoRoot `
    -RedirectStandardOutput $stdout -RedirectStandardError $stderr -PassThru -WindowStyle Hidden

Write-Output "Trace ready: $stdout"
Write-Output "Complete or force the custom final mission, observe the transition, then exit Redux."

try {
    if ($DurationSeconds -gt 0) {
        Wait-Process -Id $game.Id -Timeout $DurationSeconds -ErrorAction SilentlyContinue
    } else {
        Wait-Process -Id $game.Id
    }
} finally {
    if ($frida -and -not $frida.HasExited) {
        Stop-Process -Id $frida.Id -Force
    }
    if ($DurationSeconds -gt 0 -and $launched) {
        $stillRunning = Get-Process -Id $game.Id -ErrorAction SilentlyContinue
        if ($stillRunning) { Stop-Process -Id $game.Id }
    }
}

Write-Output "Trace complete: $OutputDirectory"
