# Verify an explicit outer-controller launch lock before a coordinator borrows it.
function Assert-BZRCoopInheritedLaunchLock([int]$Owner) {
    if ($Owner -le 0 -or $env:BZR_LAUNCH_LOCK_HELD -ne "$Owner") { throw 'Inherited launch lock owner does not match the environment.' }
    $ancestor = $PID
    $found = $false
    for ($depth=0; $depth -lt 32 -and $ancestor; $depth++) {
        $process = Get-CimInstance Win32_Process -Filter "ProcessId=$ancestor"
        if (-not $process) { break }
        $ancestor = $process.ParentProcessId
        if ($ancestor -eq $Owner) { $found = $true; break }
    }
    if (-not $found -or -not (Get-Process -Id $Owner -ErrorAction SilentlyContinue)) { throw 'Inherited launch lock owner is not a live ancestor of this process.' }
    $mutex = [Threading.Mutex]::OpenExisting('Local\BZROpenShimGameLaunch')
    $acquired = $false
    try {
        try { $acquired = $mutex.WaitOne(0) }
        catch [Threading.AbandonedMutexException] { $acquired = $true }
        if ($acquired) { throw 'The purported outer launch lock is free or abandoned.' }
    } finally {
        if ($acquired) { $mutex.ReleaseMutex() }
        $mutex.Dispose()
    }
}
