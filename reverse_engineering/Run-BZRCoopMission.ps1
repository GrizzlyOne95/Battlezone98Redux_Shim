# One-command co-op mission flow test: two to four real Redux clients on this PC.
#
#   powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopMission.ps1 -Mission misn03 -Scenario win
#
# 1. Preflight: refuses while any battlezone98redux is running (it may be
#    someone's game) or while the lobby ports are taken.
# 2. Mirrors the chosen Campaign Reimagined build into C:\BZRCoop\stage.
# 3. Starts a private Battlezone98Redux_DedicatedServer bound to 127.0.0.1.
# 4. BZRCoopSession.ps1 Prepare + probe install, then Launch (background; it
#    holds the machine-wide launch lock until all clients exit).
# 5. BZRCoopLobby.ps1: host creates, map/limit pick, guests join, Sync Join, launch.
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
    [ValidateRange(2, 4)][int]$Clients = 2,
    [switch]$MaxNetworkLogging,
    [switch]$MuteClients,
    [switch]$AllowNoAudioEndpoint,
    [string]$RunName = '',
    # OpenShim checkout with a Release|Win32 build for the instances; empty = the install's.
    [string]$OpenShimRepo = '',
    # Host map list row (stock shell, 1280x720). Empty = the known row for $Mission.
    [int]$MapListY = 0,
    [hashtable]$ScenarioArgs = @{},
    # Folder of files copied over the staged CR content in all test
    # instances (try a content fix, e.g. a .vxt, without touching CR itself).
    [string]$ContentOverride = '',
    # Reuse prepared instances (the probe is still reinstalled).
    [switch]$SkipPrepare,
    # Leave clients and server running afterwards for manual inspection.
    [switch]$KeepRunning,
    # Run the scenario against the session a -Scenario play run left in the
    # mission (C:\BZRCoop\play.json): no launch, no lobby, nothing stopped.
    [switch]$Attach,
    # Relay network impairment (relay_impairment.py spec, e.g. 'loss=3,seed=7'),
    # applied once every client is in the mission so joining and loading stay
    # clean. Needs a server with POST /relay/impairment. Scenarios can change
    # it mid-run with Set-CRFlowImpairment.
    [string]$Impair = '',
    # A matrix may keep the common lock across config changes and runs. Default
    # zero keeps the normal coordinator-owned lock. Never combine with KeepRunning.
    [int]$InheritedLaunchLockOwner = 0,
    # Out-of-process watchdog (BZRCoopWatchdog.ps1): after a step failure or
    # the start of teardown this run gets FailureGraceSeconds to finish, and
    # HardTimeoutSeconds (0 = none) overall, before it is torn down and killed.
    [ValidateRange(0, 86400)][int]$HardTimeoutSeconds = 0,
    [ValidateRange(30, 3600)][int]$FailureGraceSeconds = 300
)

$ErrorActionPreference = 'Stop'
if ($InheritedLaunchLockOwner) {
    if ($KeepRunning -or $Attach -or $Scenario -eq 'play') { throw 'An inherited lock requires a bounded, fully closed run.' }
    . "$PSScriptRoot\BZRCoopLaunchLock.ps1"
    Assert-BZRCoopInheritedLaunchLock $InheritedLaunchLockOwner
}
. "$PSScriptRoot\BZRCoopMission.ps1"
. "$PSScriptRoot\BZRCoopDiagnostics.ps1"
. "$PSScriptRoot\BZRCoopWatchdog.ps1"
$script:CRFlowCoopRoot = $BZRCoopRoot
$clientIndices = @(0..($Clients - 1))
$guestIndices = @(1..($Clients - 1))

# Rows in the host's "All Maps" list at 1280x720 (12 px pitch, first row 99).
# The lobby step confirms the pick from the server's gameSettings, so a stale
# row fails the run instead of testing the wrong map.
$KnownMapRows = @{ misn05 = 128; misn03 = 147; misn02b = 159; misn04 = 171 }
$Ports = @(@{ p = 'TCP'; n = 1337 }, @{ p = 'UDP'; n = 1338 }, @{ p = 'UDP'; n = 1339 }, @{ p = 'TCP'; n = 8080 })
$PowerShellExe = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'

# -Scenario play: lobby + mission load only, then everything stays up for
# hands-on play testing with BZRCoopPlay.ps1 (stop with BZRCoopPlay.ps1 -Stop).
$playMode = $Scenario -eq 'play'
if ($playMode) { $KeepRunning = $true; $scenarioPath = Join-Path $PSScriptRoot 'coopflow\scenarios\play.ps1' }
elseif (Test-Path -LiteralPath $Scenario) { $scenarioPath = (Resolve-Path -LiteralPath $Scenario).Path }
else {
    # Mission-specific scenario first, then a generic one (e.g. host-leaves).
    $scenarioPath = Join-Path $PSScriptRoot "coopflow\scenarios\$Mission-$Scenario.ps1"
    if (-not (Test-Path -LiteralPath $scenarioPath)) { $scenarioPath = Join-Path $PSScriptRoot "coopflow\scenarios\$Scenario.ps1" }
}
if (-not (Test-Path -LiteralPath $scenarioPath)) { throw "Scenario not found: $scenarioPath" }
if (-not $MapListY) {
    if (-not $KnownMapRows.ContainsKey($Mission)) { throw "No known map row for $Mission; pass -MapListY." }
    $MapListY = $KnownMapRows[$Mission]
}
if (-not $RunName) { $RunName = 'cr-{0}-{1}-{2}' -f $Mission, [IO.Path]::GetFileNameWithoutExtension($scenarioPath).Replace("$Mission-", ''), (Get-Date -Format 'yyyyMMdd-HHmmss') }

if ($Attach) {
    $playFile = Join-Path $BZRCoopRoot 'play.json'
    if (-not (Test-Path -LiteralPath $playFile)) { throw "No play session ($playFile); start one with -Scenario play." }
    $play = Get-Content -LiteralPath $playFile -Raw | ConvertFrom-Json
    if ($play.mission -ne $Mission) { throw "The play session is running $($play.mission), not $Mission." }
    $s = Get-CRFlowSession
    if (@($s.clients).Count -ne $Clients -or @($s.clients | Where-Object { Get-Process -Id $_.pid -ErrorAction SilentlyContinue }).Count -ne $Clients) { throw "The play session must have $Clients running clients; pass its count with -Clients." }
    $runDir = (New-Item -ItemType Directory -Force -Path (Join-Path $play.runDir $RunName)).FullName
    Write-Host "[run] attached to $($play.run): $RunName -> $runDir"
    # Events count from the start of each client's log, i.e. this mission load.
    Set-CRFlowLogMark $clientIndices -FromStart
    Start-CRFlowRun -RunDir $runDir -Mission $Mission -Scenario ([IO.Path]::GetFileNameWithoutExtension($scenarioPath))
    $outcome = ''
    try { Test-CRFlowRoster -ExpectedClients $Clients; . $scenarioPath @ScenarioArgs } catch {
        $outcome = "Stopped early: $($_.Exception.Message)"
        Write-Host "[run] $outcome" -ForegroundColor Red
    }
    Start-Sleep -Seconds 3
    # A scenario that ends the session unevenly (host leaves) sets this.
    if (-not $script:CRFlowSkipParity) { Test-CRFlowPresentationParity 0 $guestIndices }
    Test-CRFlowLogErrors $clientIndices
    $summary = Complete-CRFlowRun -Outcome $outcome
    Write-Host "[run] session left up; stop with BZRCoopPlay.ps1 -Stop"
    if ($summary.verdict -eq 'PASS') { exit 0 }
    exit 1
}

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
if ($ContentOverride -and -not (Test-Path -LiteralPath $ContentOverride -PathType Container)) { throw "Content override folder not found: $ContentOverride" }
$hasBaseMission = Test-Path -LiteralPath (Join-Path $CampaignContent "$Mission.lua") -PathType Leaf
$hasOverrideMission = $ContentOverride -and (Test-Path -LiteralPath (Join-Path $ContentOverride "$Mission.lua") -PathType Leaf)
if (-not ($hasBaseMission -or $hasOverrideMission)) { throw "$Mission.lua not in campaign content or content override" }

$server = $null
$launcher = $null
$summary = $null
$flowFinished = $false
$fatal = $null
Write-Host "[run] $RunName -> $runDir"
if (-not $KeepRunning) {
    foreach ($f in 'flow-failed', 'flow-teardown', 'harness-pids.json') { Remove-Item -LiteralPath (Join-Path $runDir $f) -ErrorAction SilentlyContinue }
    $watchdog = Start-BZRCoopWatchdog -RunDir $runDir -SessionFile (Join-Path $BZRCoopRoot 'session.json') `
        -HardTimeoutSeconds $HardTimeoutSeconds -FailureGraceSeconds $FailureGraceSeconds
    Write-Host "[run] watchdog pid $($watchdog.Id) (grace $FailureGraceSeconds s, hard $(if ($HardTimeoutSeconds) { "$HardTimeoutSeconds s" } else { 'none' }))"
}
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
    # A shared relay destination cannot distinguish a sender's multiple peers.
    # Private loopback runs use one negotiated UDP destination per peer pair.
    if ($Clients -gt 2) {
        $serverArgs += '--relay-pair-ports'
        $serverArgs += @('--relay-trace', (Join-Path $runDir 'relay-trace.jsonl'))
    }
    if ($MaxNetworkLogging) {
        if ($Clients -le 2) { $serverArgs += @('--relay-trace', (Join-Path $runDir 'relay-trace.jsonl')) }
        $serverArgs += '--relay-trace-payloads'
        $serverArgs += @('--protocol-trace', (Join-Path $runDir 'protocol-trace.jsonl'))
    }
    $server = Start-Process -FilePath $Python -ArgumentList $serverArgs -WorkingDirectory $ServerRepo -WindowStyle Hidden -PassThru `
        -RedirectStandardError $serverLog -RedirectStandardOutput (Join-Path $runDir 'server.out.log')
    Set-BZRCoopWatchdogPid $runDir 'server' $server.Id
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
        $prep = @('-Action', 'Prepare', '-CampaignStage', $stage, '-BZRCoopRoot', $BZRCoopRoot, '-Clients', "$Clients")
        if ($OpenShimRepo) { $prep += @('-OpenShimRepo', $OpenShimRepo) }
        Invoke-Child 'BZRCoopSession.ps1' $prep
    }
    foreach ($i in $clientIndices) {
        $inst = Join-Path $BZRCoopRoot ("instances\Instance{0}\Battlezone 98 Redux" -f $i)
        if (-not (Test-Path -LiteralPath (Join-Path $inst 'battlezone98redux.exe'))) { throw "Instance $i is not prepared; run without -SkipPrepare." }
        robocopy $stage (Join-Path $inst "mods\$($script:CRFlowModId)") /MIR /NFL /NDL /NJH /NJS /NP | Out-Null
        if ($LASTEXITCODE -ge 8) { throw "robocopy stage -> instance $i failed ($LASTEXITCODE)" }
        if ($ContentOverride) {
            $over = @(Get-ChildItem -LiteralPath $ContentOverride -File)
            $over | Copy-Item -Destination (Join-Path $inst "mods\$($script:CRFlowModId)") -Force
            Write-Host "[run] content override in instance ${i}: $($over.Name -join ', ')"
        }
        $p = Install-CRFlowProbe -InstanceDir $inst -Mission $Mission
        Write-Host "[run] probe installed: $($p.Script)"
    }

    # Preserve the exact inputs even when the relay or generated override has
    # not been committed yet. The session manifest records native DLL hashes.
    $inputs = [ordered]@{
        clients = $Clients
        allowNoAudioEndpoint = [bool]$AllowNoAudioEndpoint
        harnessCommit = (git -C (Split-Path $PSScriptRoot) rev-parse HEAD)
        harnessFiles = @(@('Run-BZRCoopMission.ps1', 'BZRCoopMission.ps1', 'BZRCoopLobby.ps1', 'BZRCoopSession.ps1', 'BZRCoopDiagnostics.ps1', 'BZRCoopWatchdog.ps1', 'BZRCoopAudio.cs', 'coopflow\CRFlowProbe.lua') | ForEach-Object {
            @{ name = $_; sha256 = (Get-FileHash -LiteralPath (Join-Path $PSScriptRoot $_)).Hash }
        })
        scenario = $scenarioPath
        scenarioSha256 = (Get-FileHash -LiteralPath $scenarioPath).Hash
        scenarioArgs = $ScenarioArgs
        serverCommit = (git -C $ServerRepo rev-parse HEAD)
        serverSha256 = (Get-FileHash -LiteralPath (Join-Path $ServerRepo 'server.py')).Hash
        nativeHealthAnalyzerSha256 = if ($Clients -gt 2) { (Get-FileHash -LiteralPath (Join-Path $ServerRepo 'native_network_health.py')).Hash } else { $null }
        relayPairPorts = ($Clients -gt 2)
        impair = $Impair
        maxNetworkLogging = [bool]$MaxNetworkLogging
        muteClients = [bool]$MuteClients
        serverArgs = $serverArgs
        campaignContent = "$CampaignContent ($contentCommit)"
        contentOverride = $ContentOverride
        overrideFiles = @(if ($ContentOverride) { Get-ChildItem -LiteralPath $ContentOverride -File | Sort-Object Name | ForEach-Object {
            @{ name = $_.Name; sha256 = (Get-FileHash -LiteralPath $_.FullName).Hash }
        } })
    }
    $inputs | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $runDir 'flow-inputs.json')

    # ----------------------------------------------------------- launch --
    $launchCmd = "& '$PSScriptRoot\BZRCoopSession.ps1' -Action Launch -Clients $Clients -BZRCoopRoot '$BZRCoopRoot' -RunName '$RunName' -GameArgs '/nointro','/norawinput'"
    if ($MaxNetworkLogging) { $launchCmd += ' -MaxNetworkLogging' }
    if ($MuteClients) { $launchCmd += ' -MuteClients' }
    if ($AllowNoAudioEndpoint) { $launchCmd += ' -AllowNoAudioEndpoint' }
    if ($InheritedLaunchLockOwner) {
        Assert-BZRCoopInheritedLaunchLock $InheritedLaunchLockOwner
        $env:BZR_LAUNCH_LOCK_HELD = "$InheritedLaunchLockOwner"
    } else { Remove-Item Env:BZR_LAUNCH_LOCK_HELD -ErrorAction SilentlyContinue }
    $launcher = Start-Process -FilePath $PowerShellExe -ArgumentList @('-NoProfile', '-ExecutionPolicy', 'Bypass', '-Command', $launchCmd) `
        -WindowStyle Hidden -PassThru -RedirectStandardOutput (Join-Path $runDir 'coordinator.log') -RedirectStandardError (Join-Path $runDir 'coordinator.err.log')
    Set-BZRCoopWatchdogPid $runDir 'launcher' $launcher.Id
    $deadline = (Get-Date).AddSeconds([math]::Max(360, $Clients * 150))
    while ($true) {
        Start-Sleep -Seconds 2
        $s = try { Get-CRFlowSession } catch { $null }
        if ($s -and @($s.clients | Where-Object authenticatedAs).Count -eq $Clients) { break }
        if ($launcher.HasExited) { throw "client launch failed: $((Get-Content (Join-Path $runDir 'coordinator.err.log') -Raw), (Get-Content (Join-Path $runDir 'coordinator.log') -Tail 5) -join ' ')" }
        if ((Get-Date) -gt $deadline) { throw "$Clients clients did not all reach the lobby before the launch deadline" }
    }
    Write-Host "[run] all $Clients clients authenticated"
    if ($MuteClients) {
        if (@($s.clients | Where-Object { $_.mutedAudioSessions -lt 1 -and (-not $AllowNoAudioEndpoint -or $_.activeAudioEndpoints -gt 0) }).Count) { throw 'A client has no verified muted audio session.' }
        Write-Host "[run] audio mode: verified muted sessions or explicitly allowed zero active endpoints; audio timing qualification is recorded per client"
    }

    # ---------------------------------------------------- lobby + flow --
    Set-CRFlowLogMark $clientIndices
    Start-CRFlowRun -RunDir $runDir -Mission $Mission -Scenario ([IO.Path]::GetFileNameWithoutExtension($scenarioPath))
    $outcome = ''
    try {
        Invoke-CRFlowStep 'lobby: create, join, map, sync join, ready, launch' {
            Invoke-Child 'BZRCoopLobby.ps1' @('-BZRCoopRoot', $BZRCoopRoot, '-ServerLog', $serverLog,
                '-MapListY', "$MapListY", '-MapBzn', "$Mission.bzn", '-SyncJoin', '-Launch')
            "$Mission.bzn"
        } | Out-Null
        Test-CRFlowRoster -ExpectedClients $Clients
        if ($Impair) { Set-CRFlowImpairment $Impair | Out-Null }
        # Dot-sourced: scenarios share this script scope with the library state.
        . $scenarioPath @ScenarioArgs
    } catch {
        $outcome = "Stopped early: $($_.Exception.Message)"
        Write-Host "[run] $outcome" -ForegroundColor Red
        Set-Content -LiteralPath (Join-Path $runDir 'flow-failed') -Value $outcome
    }
    Start-Sleep -Seconds 3
    # A scenario that ends the session unevenly (host leaves) sets this.
    if (-not $script:CRFlowSkipParity) { Test-CRFlowPresentationParity 0 $guestIndices }
    Test-CRFlowLogErrors $clientIndices
    if ($Impair) {
        # Final relay counters, before the server stops.
        try {
            Invoke-RestMethod -Uri "$($script:CRFlowHealthUrl)/relay/impairment" -TimeoutSec 5 |
                ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $runDir 'relay-impairment-final.json')
        } catch { Write-Warning "relay impairment counters: $_" }
    }
    $flowFinished = $true
} catch {
    $fatal = $_
    Set-Content -LiteralPath (Join-Path $runDir 'flow-failed') -Value "Stopped early: $($_.Exception.Message)"
} finally {
    if (-not $KeepRunning) { Set-Content -LiteralPath (Join-Path $runDir 'flow-teardown') -Value (Get-Date).ToString('o') }
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
if ($fatal) {
    # The run still records its failure before the error propagates.
    if ($script:CRFlowRun) { $summary = Complete-CRFlowRun -Outcome "Stopped early: $($fatal.Exception.Message)" -Clients $clientIndices }
    throw $fatal
}
if ($flowFinished) {
    if ($MaxNetworkLogging -and $MuteClients -and -not $KeepRunning) {
        try {
            $diagnostics = @(Test-BZRCoopDiagnosticEvidence $runDir $Clients)
            Add-CRFlowCheck 'all clients have verified audio conditions and complete maximum network captures' $true $diagnostics
        } catch {
            Add-CRFlowCheck 'all clients have verified audio conditions and complete maximum network captures' $false $_.Exception.Message
        }
    }
    if ($Clients -gt 2 -and -not $KeepRunning) {
        # WM_CLOSE has archived complete native logs. Forwarding alone cannot
        # detect the game's sustained rejection of newer position/ping data.
        $healthPath = Join-Path $runDir 'native-network-health.json'
        try {
            & $Python (Join-Path $ServerRepo 'native_network_health.py') --run-dir $runDir --clients $Clients --json-out $healthPath | Out-Host
            $healthExit = $LASTEXITCODE
            $health = Get-Content -LiteralPath $healthPath -Raw | ConvertFrom-Json
            Add-CRFlowCheck 'native peers have no sustained post-loading sequence rejection' ($healthExit -eq 0 -and $health.status -eq 'pass') @{ status = $health.status; report = $healthPath }
        } catch {
            Add-CRFlowCheck 'native peers have no sustained post-loading sequence rejection' $false $_.Exception.Message
        }
    }
    $summary = Complete-CRFlowRun -Outcome $outcome -Clients $clientIndices
}
if ($summary -and $summary.verdict -eq 'PASS') { exit 0 }
exit 1
