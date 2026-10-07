# One-command co-op mission flow test: two real Redux clients on this PC.
#
#   powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopMission.ps1 -Mission misn03 -Scenario win
#
# 1. Preflight: refuses while any battlezone98redux is running (it may be
#    someone's game) or while the lobby ports are taken.
# 2. Mirrors the chosen Campaign Reimagined build into C:\BZRCoop\stage.
# 3. Starts a private Battlezone98Redux_DedicatedServer bound to 127.0.0.1.
# 4. BZRCoopSession.ps1 Prepare + probe install, then Launch (background; it
#    holds the machine-wide launch lock until both clients exit).
# 5. BZRCoopLobby.ps1: host creates, guest joins, map pick, Sync Join, launch.
# 6. Runs coopflow\scenarios\<Mission>-<Scenario>.ps1 against the live mission.
# 7. Log-wide checks (presentation parity, Lua errors), writes
#    flow-summary.md/.json in the run folder, stops clients and server.
#
# Exit code 0 = PASS. Evidence: C:\BZRCoop\runs\<RunName>\.
# Windows PowerShell 5.1 (the input/capture helpers need System.Drawing).

param(
    [Parameter(Mandatory)][string]$Mission,
    [string]$Scenario = 'win',
    [string]$CampaignContent = (Join-Path $env:USERPROFILE 'Documents\GIT\CR-release\Local\Workshop\content'),
    [string]$ServerRepo = (Join-Path $env:USERPROFILE 'Documents\GIT\Battlezone98Redux_DedicatedServer'),
    [string]$Python = 'python',
    [string]$BZRCoopRoot = 'C:\BZRCoop',
    [string]$RunName = '',
    # OpenShim checkout with a Release|Win32 build for the instances; empty = the install's.
    [string]$OpenShimRepo = '',
    # Host map list row (stock shell, 1280x720). Empty = the known row for $Mission.
    [int]$MapListY = 0,
    [hashtable]$ScenarioArgs = @{},
    # Reuse prepared instances (the probe is still reinstalled).
    [switch]$SkipPrepare,
    # Leave clients and server running afterwards for manual inspection.
    [switch]$KeepRunning
)

$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\BZRCoopMission.ps1"
$script:CRFlowCoopRoot = $BZRCoopRoot

# Rows in the host's "All Maps" list at 1280x720 (12 px pitch, first row 99).
# The lobby step confirms the pick from the server's gameSettings, so a stale
# row fails the run instead of testing the wrong map.
$KnownMapRows = @{ misn03 = 147; misn02b = 159; misn04 = 171 }
$Ports = @(@{ p = 'TCP'; n = 1337 }, @{ p = 'UDP'; n = 1338 }, @{ p = 'UDP'; n = 1339 }, @{ p = 'TCP'; n = 8080 })
$PowerShellExe = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'

# -Scenario play: lobby + mission load only, then everything stays up for
# hands-on play testing with BZRCoopPlay.ps1 (stop with BZRCoopPlay.ps1 -Stop).
$playMode = $Scenario -eq 'play'
if ($playMode) { $KeepRunning = $true; $scenarioPath = Join-Path $PSScriptRoot 'coopflow\scenarios\play.ps1' }
elseif (Test-Path -LiteralPath $Scenario) { $scenarioPath = (Resolve-Path -LiteralPath $Scenario).Path }
else { $scenarioPath = Join-Path $PSScriptRoot "coopflow\scenarios\$Mission-$Scenario.ps1" }
if (-not (Test-Path -LiteralPath $scenarioPath)) { throw "Scenario not found: $scenarioPath" }
if (-not $MapListY) {
    if (-not $KnownMapRows.ContainsKey($Mission)) { throw "No known map row for $Mission; pass -MapListY." }
    $MapListY = $KnownMapRows[$Mission]
}
if (-not $RunName) { $RunName = 'cr-{0}-{1}-{2}' -f $Mission, [IO.Path]::GetFileNameWithoutExtension($scenarioPath).Replace("$Mission-", ''), (Get-Date -Format 'yyyyMMdd-HHmmss') }
$runDir = (New-Item -ItemType Directory -Force -Path (Join-Path $BZRCoopRoot "runs\$RunName")).FullName
$stage = Join-Path $BZRCoopRoot "stage\$($script:CRFlowModId)"

function Invoke-Child([string]$Script, [string[]]$Arguments) {
    # Each harness script runs in its own process: BZRCoopSession sets
    # launch-lock environment state that must not leak into this one.
    & $PowerShellExe -NoProfile -ExecutionPolicy Bypass -File (Join-Path $PSScriptRoot $Script) @Arguments
    if ($LASTEXITCODE -ne 0) { throw "$Script $($Arguments -join ' ') exited with $LASTEXITCODE" }
}

# ------------------------------------------------------------ preflight --
$running = @(Get-Process battlezone98redux -ErrorAction SilentlyContinue)
if ($running.Count) { throw "Battlezone is already running (pid $($running.Id -join ', ')); close it first. Nothing was changed." }
if (Test-Path -LiteralPath (Join-Path $BZRCoopRoot 'session.json')) {
    $old = Get-Content -LiteralPath (Join-Path $BZRCoopRoot 'session.json') -Raw | ConvertFrom-Json
    if (@($old.clients | Where-Object { Get-Process -Id $_.pid -ErrorAction SilentlyContinue }).Count) { throw 'A BZRCoop session is still running; run BZRCoopSession.ps1 -Action Stop.' }
    Remove-Item -LiteralPath (Join-Path $BZRCoopRoot 'session.json') -Force
}
foreach ($port in $Ports) {
    $busy = if ($port.p -eq 'TCP') { Get-NetTCPConnection -State Listen -LocalPort $port.n -ErrorAction SilentlyContinue }
            else { Get-NetUDPEndpoint -LocalPort $port.n -ErrorAction SilentlyContinue }
    if ($busy) { throw "$($port.p) $($port.n) is in use (pid $(@($busy.OwningProcess) -join ', ')); a lobby server is already running." }
}
if (-not (Test-Path -LiteralPath (Join-Path $CampaignContent "$Mission.lua"))) { throw "$Mission.lua not in $CampaignContent" }

$server = $null
$launcher = $null
$summary = $null
Write-Host "[run] $RunName -> $runDir"
try {
    # ------------------------------------------------------------ stage --
    robocopy $CampaignContent $stage /MIR /NFL /NDL /NJH /NJS /NP | Out-Null
    if ($LASTEXITCODE -ge 8) { throw "robocopy $CampaignContent -> $stage failed ($LASTEXITCODE)" }
    $contentCommit = try { git -C (Split-Path (Split-Path (Split-Path $CampaignContent))) rev-parse --short HEAD 2>$null } catch { $null }
    Write-Host "[run] staged CR from $CampaignContent ($contentCommit)"

    # ----------------------------------------------------------- server --
    $serverLog = Join-Path $runDir 'server.log'
    $serverArgs = @('server.py', '--ws-host', '127.0.0.1', '--udp-host', '127.0.0.1', '--relay-host', '127.0.0.1',
                    '--health-host', '127.0.0.1', '--state-file', (Join-Path $runDir 'server-state.json'), '--log-level', 'DEBUG')
    $server = Start-Process -FilePath $Python -ArgumentList $serverArgs -WorkingDirectory $ServerRepo -WindowStyle Hidden -PassThru `
        -RedirectStandardError $serverLog -RedirectStandardOutput (Join-Path $runDir 'server.out.log')
    $deadline = (Get-Date).AddSeconds(20)
    while ($true) {
        try { Invoke-RestMethod -Uri 'http://127.0.0.1:8080/health' -TimeoutSec 2 | Out-Null; break } catch { }
        if ($server.HasExited) { throw "server.py exited with $($server.ExitCode); see $serverLog" }
        if ((Get-Date) -gt $deadline) { throw "server.py did not answer /health; see $serverLog" }
        Start-Sleep -Milliseconds 500
    }
    Write-Host "[run] private server pid $($server.Id) on 127.0.0.1 ($(git -C $ServerRepo rev-parse --short HEAD))"

    # ---------------------------------------------- prepare + probe --
    if (-not $SkipPrepare) {
        $prep = @('-Action', 'Prepare', '-CampaignStage', $stage, '-BZRCoopRoot', $BZRCoopRoot)
        if ($OpenShimRepo) { $prep += @('-OpenShimRepo', $OpenShimRepo) }
        Invoke-Child 'BZRCoopSession.ps1' $prep
    }
    foreach ($i in 0, 1) {
        $inst = Join-Path $BZRCoopRoot ("instances\Instance{0}\Battlezone 98 Redux" -f $i)
        robocopy $stage (Join-Path $inst "mods\$($script:CRFlowModId)") /MIR /NFL /NDL /NJH /NJS /NP | Out-Null
        if ($LASTEXITCODE -ge 8) { throw "robocopy stage -> instance $i failed ($LASTEXITCODE)" }
        $p = Install-CRFlowProbe -InstanceDir $inst -Mission $Mission
        Write-Host "[run] probe installed: $($p.Script)"
    }

    # ----------------------------------------------------------- launch --
    $launchCmd = "& '$PSScriptRoot\BZRCoopSession.ps1' -Action Launch -BZRCoopRoot '$BZRCoopRoot' -RunName '$RunName' -GameArgs '/nointro','/norawinput'"
    Remove-Item Env:BZR_LAUNCH_LOCK_HELD -ErrorAction SilentlyContinue
    $launcher = Start-Process -FilePath $PowerShellExe -ArgumentList @('-NoProfile', '-ExecutionPolicy', 'Bypass', '-Command', $launchCmd) `
        -WindowStyle Hidden -PassThru -RedirectStandardOutput (Join-Path $runDir 'coordinator.log') -RedirectStandardError (Join-Path $runDir 'coordinator.err.log')
    $deadline = (Get-Date).AddMinutes(6)
    while ($true) {
        Start-Sleep -Seconds 2
        $s = try { Get-CRFlowSession } catch { $null }
        if ($s -and @($s.clients | Where-Object authenticatedAs).Count -ge 2) { break }
        if ($launcher.HasExited) { throw "client launch failed: $((Get-Content (Join-Path $runDir 'coordinator.err.log') -Raw), (Get-Content (Join-Path $runDir 'coordinator.log') -Tail 5) -join ' ')" }
        if ((Get-Date) -gt $deadline) { throw 'clients did not both reach the lobby in 6 minutes' }
    }
    Write-Host "[run] both clients authenticated"

    # ---------------------------------------------------- lobby + flow --
    Set-CRFlowLogMark @(0, 1)
    Start-CRFlowRun -RunDir $runDir -Mission $Mission -Scenario ([IO.Path]::GetFileNameWithoutExtension($scenarioPath))
    $outcome = ''
    try {
        Invoke-CRFlowStep 'lobby: create, join, map, sync join, ready, launch' {
            Invoke-Child 'BZRCoopLobby.ps1' @('-BZRCoopRoot', $BZRCoopRoot, '-ServerLog', $serverLog,
                '-MapListY', "$MapListY", '-MapBzn', "$Mission.bzn", '-SyncJoin', '-Launch')
            "$Mission.bzn"
        } | Out-Null
        # Dot-sourced: scenarios share this script scope with the library state.
        . $scenarioPath @ScenarioArgs
    } catch {
        $outcome = "Stopped early: $($_.Exception.Message)"
        Write-Host "[run] $outcome" -ForegroundColor Red
    }
    Start-Sleep -Seconds 3
    Test-CRFlowPresentationParity 0 @(1)
    Test-CRFlowLogErrors @(0, 1)
    $summary = Complete-CRFlowRun -Outcome $outcome
    $summary | Add-Member -NotePropertyName campaignContent -NotePropertyValue "$CampaignContent ($contentCommit)"
} finally {
    if ($KeepRunning) {
        if ($server) {
            [ordered]@{ run = $RunName; runDir = $runDir; mission = $Mission; serverPid = $server.Id; launcherPid = $launcher.Id } |
                ConvertTo-Json | Set-Content -LiteralPath (Join-Path $BZRCoopRoot 'play.json')
        }
        Write-Host "[run] clients and server left up. Drive with BZRCoopPlay.ps1; stop with:`n  powershell -File `"$PSScriptRoot\BZRCoopPlay.ps1`" -Stop"
    } else {
        if (Test-Path -LiteralPath (Join-Path $BZRCoopRoot 'session.json')) {
            try { Invoke-Child 'BZRCoopSession.ps1' @('-Action', 'Stop', '-BZRCoopRoot', $BZRCoopRoot) } catch { Write-Warning "session stop: $_" }
        }
        if ($server -and -not $server.HasExited) { Stop-Process -Id $server.Id -Force }
    }
}
if ($summary -and $summary.verdict -eq 'PASS') { exit 0 }
exit 1
