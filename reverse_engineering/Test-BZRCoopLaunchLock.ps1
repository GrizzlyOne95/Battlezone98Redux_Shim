$ErrorActionPreference = 'Stop'
$env:BZR_LAUNCH_LOCK_HELD = "$PID-nolaunch"
$GameRoot = $null
. "$PSScriptRoot\BZRHarness.ps1"
$ps51 = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
$helper = Join-Path $PSScriptRoot 'BZRCoopLaunchLock.ps1'
$lease = Enter-BZRLaunchLock -TimeoutSeconds 1
$env:BZR_LAUNCH_LOCK_HELD = "$PID"
try {
    # A real child must accept a locked live ancestor without waiting on it.
    & $ps51 -NoProfile -Command ". '$helper'; Assert-BZRCoopInheritedLaunchLock $PID"
    if ($LASTEXITCODE -ne 0) { throw 'Child did not accept the locked ancestor.' }
    # Incorrect claimed ownership must fail even while the common mutex is held.
    & $ps51 -NoProfile -Command ". '$helper'; try { Assert-BZRCoopInheritedLaunchLock 1; exit 1 } catch { exit 0 }"
    if ($LASTEXITCODE -ne 0) { throw 'Incorrect ownership was accepted.' }
} finally { Exit-BZRLaunchLock $lease }
# A matching live ancestor/env value without a held mutex must fail.
& $ps51 -NoProfile -Command ". '$helper'; try { Assert-BZRCoopInheritedLaunchLock $PID; exit 1 } catch { exit 0 }"
if ($LASTEXITCODE -ne 0) { throw 'An unlocked ancestor was accepted.' }
Write-Host '[PASS] Real child accepted held ancestor; wrong and unlocked ownership rejected.'
