<#
.SYNOPSIS
    Waits for another session's bzr_livetest.lock to disappear.
.DESCRIPTION
    Run this BEFORE dot-sourcing BZRHarness.ps1: dot-sourcing touches the
    shared ogre.cfg, which the lock protects. Polls for bzr_livetest.lock in
    the game root. Exits 0 once the lock is absent, or 1 on timeout after
    printing the holder (the lock file contents). Never deletes or takes the
    lock: create it yourself right after this returns (AGENT_TOOLING.md,
    "Shared live-test state"). Use it instead of reporting "blocked".
.EXAMPLE
    & .\reverse_engineering\Wait-BZRLiveTestLock.ps1 -GameRoot $GameRoot
    if ($LASTEXITCODE -ne 0) { return }
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)] [string]$GameRoot,
    [int]$TimeoutSeconds = 2400,
    [int]$PollSeconds = 20
)

$lock = Join-Path $GameRoot 'bzr_livetest.lock'
$deadline = (Get-Date).AddSeconds($TimeoutSeconds)
while (Test-Path -LiteralPath $lock) {
    if ((Get-Date) -ge $deadline) {
        $holder = try { (Get-Content -LiteralPath $lock -Raw -ErrorAction Stop).Trim() } catch { '(unreadable)' }
        Write-Warning ("Timed out after {0}s waiting for {1}; held by: {2}" -f $TimeoutSeconds, $lock, $holder)
        exit 1
    }
    Start-Sleep -Seconds $PollSeconds
}
exit 0
