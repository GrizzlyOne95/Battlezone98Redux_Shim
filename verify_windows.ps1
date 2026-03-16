[CmdletBinding()]
param (
    [string]$GamePath = ""
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$defaultPaths = @(
    "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux",
    "C:\Program Files\Steam\steamapps\common\Battlezone 98 Redux",
    "$env:PROGRAMFILES\Steam\steamapps\common\Battlezone 98 Redux",
    "C:\GOG Games\Battlezone 98 Redux",
    "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"
)

if (-not $GamePath) {
    foreach ($path in $defaultPaths) {
        if (Test-Path $path) {
            $GamePath = $path
            break
        }
    }
}

if (-not $GamePath -or -not (Test-Path $GamePath)) {
    Write-Host "ERROR: game folder not found. Pass -GamePath explicitly." -ForegroundColor Red
    exit 1
}

$dllPath = Join-Path $GamePath "winmm.dll"
$logPath = Join-Path $GamePath "openshim.log"
$pass = $true
$issues = @()

Write-Host ""
Write-Host "=== BZR Open Shim - Windows netcode verifier ==="
Write-Host "Game folder : $GamePath"
Write-Host ""

if (Test-Path $dllPath) {
    Write-Host "[PASS] winmm.dll present in game folder" -ForegroundColor Green
} else {
    Write-Host "[FAIL] winmm.dll NOT found in game folder" -ForegroundColor Red
    $issues += "winmm.dll is missing from the game folder"
    $pass = $false
}

if (-not (Test-Path $logPath)) {
    Write-Host "[FAIL] openshim.log not found" -ForegroundColor Red
    $issues += "openshim.log is missing - launch the game once with OpenShim installed"
    $pass = $false
} else {
    Write-Host "[PASS] openshim.log found" -ForegroundColor Green

    $lines = Get-Content $logPath
    $startIdx = 0
    for ($i = $lines.Count - 1; $i -ge 0; $i--) {
        if ($lines[$i] -match "session start") {
            $startIdx = $i
            break
        }
    }

    $sessionLines = if ($lines.Count -gt 0) { $lines[$startIdx..($lines.Count - 1)] } else { @() }
    $sessionLog = $sessionLines -join "`n"

    if ($sessionLog -match "Real winmm\.dll loaded successfully") {
        Write-Host "[PASS] Real winmm.dll load confirmed" -ForegroundColor Green
    } else {
        Write-Host "[WARN] Could not confirm real winmm.dll load in latest session" -ForegroundColor Yellow
    }

    if ($sessionLog -match "Initialization complete") {
        Write-Host "[PASS] Network optimizer initialization confirmed" -ForegroundColor Green
    } else {
        Write-Host "[FAIL] Network optimizer initialization not confirmed" -ForegroundColor Red
        $issues += "OpenShim netcode initialization did not complete in the latest session"
        $pass = $false
    }

    if ($sessionLog -match "Winsock IAT hooks installed: [1-9]") {
        Write-Host "[PASS] Winsock IAT hooks installed" -ForegroundColor Green
    } else {
        Write-Host "[FAIL] Winsock IAT hook installation not confirmed" -ForegroundColor Red
        $issues += "No non-zero Winsock IAT hook installation line was found in the latest session"
        $pass = $false
    }

    $sendPatterns = @(
        "SO_SNDBUF .*-> 524288",
        "opt=SO_SNDBUF\(\d+\) .*readback=524288",
        "reasserted SO_SNDBUF floor.*finalReadback=524288"
    )
    $recvPatterns = @(
        "SO_RCVBUF .*-> 4194304",
        "opt=SO_RCVBUF\(\d+\) .*readback=4194304",
        "reasserted SO_RCVBUF floor.*finalReadback=4194304"
    )

    $sendMatch = $null
    foreach ($pattern in $sendPatterns) {
        $sendMatch = $sessionLines | Where-Object { $_ -match $pattern } | Select-Object -First 1
        if ($sendMatch) { break }
    }

    $recvMatch = $null
    foreach ($pattern in $recvPatterns) {
        $recvMatch = $sessionLines | Where-Object { $_ -match $pattern } | Select-Object -First 1
        if ($recvMatch) { break }
    }

    if ($sendMatch) {
        Write-Host "[PASS] SO_SNDBUF readback reached 524288" -ForegroundColor Green
        Write-Host "       $sendMatch"
    } else {
        Write-Host "[FAIL] No SO_SNDBUF readback reached 524288 in the latest session" -ForegroundColor Red
        $issues += "No matching SO_SNDBUF readback line reached 524288 in openshim.log"
        $pass = $false
    }

    if ($recvMatch) {
        Write-Host "[PASS] SO_RCVBUF readback reached 4194304" -ForegroundColor Green
        Write-Host "       $recvMatch"
    } else {
        Write-Host "[FAIL] No SO_RCVBUF readback reached 4194304 in the latest session" -ForegroundColor Red
        $issues += "No matching SO_RCVBUF readback line reached 4194304 in openshim.log"
        $pass = $false
    }

    Write-Host ""
    Write-Host "--- Last 25 lines of openshim.log (latest session) ---"
    $tail = $sessionLines | Select-Object -Last 25
    foreach ($line in $tail) {
        Write-Host "  $line"
    }
    Write-Host "--- end of log ---"
}

Write-Host ""
if ($pass) {
    Write-Host "=== RESULT: PASS - OpenShim netcode targets were observed ===" -ForegroundColor Green
} else {
    Write-Host "=== RESULT: FAIL ===" -ForegroundColor Red
    foreach ($issue in $issues) {
        Write-Host "  * $issue" -ForegroundColor Yellow
    }
}
Write-Host ""
