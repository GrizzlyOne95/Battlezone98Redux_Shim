<#
.SYNOPSIS
Four-client fix-ON / stock-control stress matrix for the P2P reliable-send
backlog fix ([Network] ReliableSendBacklogFix; see
p2p_reliable_send_backlog_20261007.md).

.DESCRIPTION
Runs every misn05 four-player co-op case through the co-op flow harness
(Run-BZRCoopMission.ps1 in -HarnessRoot) on the already prepared disposable
instances (-SkipPrepare): -Passes passes with the fix on, then -Passes passes
with the kill switch OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX=1, which is
the only difference between the arms. One coordinator at a time; the harness
holds the machine launch lock and stops its clients after each run, and the
next run starts only once every client has exited.

Each run is scored by p2p_netfix_score.py (classes INCOMPLETE, CRASH, GPU,
ARM_MISMATCH, FLOW_FAIL, then STRICT_PASS / LOSS for fix-ON and REPRODUCED /
NOT_REPRODUCED for the stock control). The aggregate verdict needs every
planned run scored exactly once, every fix-ON run STRICT_PASS, no stock run
failing for infrastructure or gameplay reasons, and at least one stock run
REPRODUCED. A stock run failing only the generic native-health check is
expected evidence and never stops the matrix.

The matrix stops early (resumable) when the harness cannot start a run,
clients cannot be stopped, scoring fails, or -MaxInfraFailures consecutive
runs end INCOMPLETE / CRASH / GPU. Resume with -ResumeMatrix <matrix dir>:
the original plan is reused and only unscored runs are launched.

Preflight (also with -DryRun) refuses to launch unless: no game is running;
every instance runs DX9 ([Graphics] Renderer=DX9, ogre.cfg Direct3D9); each
instance's load chain (battlezone98redux.exe, winmm.dll, bzloader.dll,
plugins\openshim.dll, scripts\patches.json) matches its source (the stock
install's exe, -OpenShimRepo's Release build and patches.json); and no
instance overrides ReliableSendBacklogFix or the retry timers.

Runtime output goes to <BZRCoopRoot>\runs\netfix-matrix-<stamp>: matrix.json
(plan and provenance hashes), logs\, scores\, summary.json and summary.md.
Run directories are <BZRCoopRoot>\runs\netfix-<arm>-<case>-p<pass>-<stamp>.

.EXAMPLE
powershell -NoProfile -ExecutionPolicy Bypass -File .\reverse_engineering\Run-NetfixStressMatrix.ps1 -DryRun
.EXAMPLE
powershell -NoProfile -ExecutionPolicy Bypass -File .\reverse_engineering\Run-NetfixStressMatrix.ps1 -Passes 2
.EXAMPLE
powershell -NoProfile -ExecutionPolicy Bypass -File .\reverse_engineering\Run-NetfixStressMatrix.ps1 -ResumeMatrix C:\BZRCoop\runs\netfix-matrix-20261008-010000
#>
param(
    [ValidateRange(1, 20)][int]$Passes = 2,
    [ValidateSet('on', 'off')][string[]]$Arms = @('on', 'off'),
    # Substring filter on the case text, e.g. 'Skipper=host'.
    [string]$Only = '',
    # Continue an interrupted matrix: reuse its plan, launch only unscored runs.
    [string]$ResumeMatrix = '',
    [string]$HarnessRoot = (Join-Path $env:USERPROFILE 'Documents\GIT\BZR-OpenShim-coopflow\reverse_engineering'),
    [string]$ServerRepo = (Join-Path $env:USERPROFILE 'Documents\GIT\Battlezone98Redux_DedicatedServer'),
    [string]$OpenShimRepo = (Split-Path $PSScriptRoot),
    [string]$SourceRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$BZRCoopRoot = 'C:\BZRCoop',
    [string]$Python = 'python',
    [ValidateRange(2, 4)][int]$Clients = 4,
    [ValidateRange(1, 36)][int]$MaxInfraFailures = 2,
    [ValidateRange(10, 600)][int]$StopTimeoutSeconds = 120,
    [switch]$DryRun
)

$ErrorActionPreference = 'Stop'
$PowerShellExe = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
$Scorer = Join-Path $PSScriptRoot 'p2p_netfix_score.py'
$MissionScript = Join-Path $HarnessRoot 'Run-BZRCoopMission.ps1'
$SessionScript = Join-Path $HarnessRoot 'BZRCoopSession.ps1'

# The misn05 four-player cases. Skipper=host is the strongest stock
# reproduction seen so far.
$Cases = @(
    'misn05 four-services Override=misn05-coop',
    'misn05 win Override=misn05-coop',
    'misn05 win Override=misn05-coop GuestClient=2',
    'misn05 win Override=misn05-coop GuestClient=3',
    'misn05 win Override=misn05-coop Skipper=host',
    'misn05 win Override=misn05-coop Skipper=none',
    'misn05 lose Override=misn05-coop Destroyed=factory',
    'misn05 lose Override=misn05-coop Destroyed=recycler',
    'misn05 host-leaves Override=misn05-coop'
)

function Get-IniValue([string]$Path, [string]$Section, [string]$Key) {
    $inSection = $false
    foreach ($line in [IO.File]::ReadAllLines($Path)) {
        $t = $line.Trim()
        if ($t -match '^\[(.+)\]$') { $inSection = ($Matches[1] -eq $Section); continue }
        if ($inSection -and $t -match "^$([regex]::Escape($Key))\s*=\s*(.*?)\s*(;.*)?$") { return $Matches[1] }
    }
    return $null
}

function Get-Hash([string]$Path) {
    if (Test-Path -LiteralPath $Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash } else { 'missing' }
}

function Get-GameProcesses { @(Get-Process battlezone98redux -ErrorAction SilentlyContinue) }

function Get-RepoState([string]$Repo, [string[]]$Files) {
    $hashes = [ordered]@{}
    foreach ($f in $Files) { $hashes[$f] = Get-Hash (Join-Path $Repo $f) }
    [ordered]@{
        commit = (git -C $Repo rev-parse HEAD)
        dirty = @(git -C $Repo status --porcelain --untracked-files=no)
        files = $hashes
    }
}

# ------------------------------------------------------------ preflight --
foreach ($p in @($MissionScript, $SessionScript, $Scorer)) {
    if (-not (Test-Path -LiteralPath $p)) { throw "missing $p" }
}
$problems = New-Object System.Collections.ArrayList
if (Get-GameProcesses) { [void]$problems.Add('battlezone98redux is running; the matrix needs the machine to itself') }

# Each instance's load chain must be byte-identical to its source.
$chain = [ordered]@{
    'battlezone98redux.exe' = Join-Path $SourceRoot 'battlezone98redux.exe'
    'winmm.dll'             = Join-Path $OpenShimRepo 'bin\Release\winmm.dll'
    'bzloader.dll'          = Join-Path $OpenShimRepo 'bin\Release\bzloader.dll'
    'plugins\openshim.dll'  = Join-Path $OpenShimRepo 'bin\Release\plugins\openshim.dll'
    'scripts\patches.json'  = Join-Path $OpenShimRepo 'scripts\patches.json'
}
$sourceHashes = [ordered]@{}
foreach ($rel in $chain.Keys) {
    $sourceHashes[$rel] = Get-Hash $chain[$rel]
    if ($sourceHashes[$rel] -eq 'missing') { [void]$problems.Add("source $($chain[$rel]) is missing") }
}
$instances = [ordered]@{}
foreach ($i in 0..($Clients - 1)) {
    $inst = Join-Path $BZRCoopRoot ("instances\Instance{0}\Battlezone 98 Redux" -f $i)
    $ini = Join-Path $inst 'openshim.ini'
    $ogre = Join-Path $inst 'ogre.cfg'
    if (-not (Test-Path -LiteralPath $ini)) { [void]$problems.Add("instance $i is not prepared"); continue }
    $h = [ordered]@{}
    foreach ($rel in $chain.Keys) {
        $h[$rel] = Get-Hash (Join-Path $inst $rel)
        if ($h[$rel] -ne $sourceHashes[$rel]) { [void]$problems.Add("instance ${i}: $rel differs from its source") }
    }
    $h['openshim.ini'] = Get-Hash $ini
    $h['ogre.cfg'] = Get-Hash $ogre
    $instances["Instance$i"] = $h
    if ((Get-IniValue $ini 'Graphics' 'Renderer') -ne 'DX9') { [void]$problems.Add("instance ${i}: [Graphics] Renderer is not DX9") }
    if (-not (Select-String -LiteralPath $ogre -Pattern '^Render System=Direct3D9' -Quiet)) { [void]$problems.Add("instance ${i}: ogre.cfg is not Direct3D9") }
    $fix = Get-IniValue $ini 'Network' 'ReliableSendBacklogFix'
    if ($fix -and $fix -notin '1', 'true', 'on', 'yes') { [void]$problems.Add("instance ${i}: ReliableSendBacklogFix=$fix") }
    foreach ($t in @(@('ReliableFirstRetryMs', '1000'), @('ReliableRetryIntervalMs', '2500'))) {
        $v = Get-IniValue $ini 'Network' $t[0]
        if ($v -and $v -ne $t[1]) { [void]$problems.Add("instance ${i}: $($t[0])=$v (the matrix uses stock timers)") }
    }
}

# ----------------------------------------------------------------- plan --
if ($ResumeMatrix) {
    $matrixDir = (Resolve-Path -LiteralPath $ResumeMatrix).Path
    $doc = Get-Content -LiteralPath (Join-Path $matrixDir 'matrix.json') -Raw | ConvertFrom-Json
    $plan = @($doc.plan)
    $origDll = $doc.sourceHashes.'plugins\openshim.dll'
    if ($origDll -ne $sourceHashes['plugins\openshim.dll']) { [void]$problems.Add("resume: openshim.dll changed since the matrix started ($origDll)") }
} else {
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $plan = New-Object System.Collections.ArrayList
    foreach ($arm in $Arms) {
        foreach ($pass in 1..$Passes) {
            foreach ($case in $Cases) {
                if ($Only -and $case -notlike "*$Only*") { continue }
                $parts = @($case -split '\s+' | Where-Object { $_ })
                $tag = (@($parts | Select-Object -Skip 1 | Where-Object { $_ -notlike 'Override=*' }) -join '-') -replace '[^\w-]', ''
                [void]$plan.Add([pscustomobject][ordered]@{
                    index = $plan.Count + 1; arm = $arm; pass = $pass; case = $case
                    run = "netfix-$arm-$tag-p$pass-$stamp"
                })
            }
        }
    }
    $matrixDir = Join-Path $BZRCoopRoot "runs\netfix-matrix-$stamp"
}
if (-not $plan.Count) { throw "empty plan (Only='$Only')" }
$scoresDir = Join-Path $matrixDir 'scores'
$done = @{}
if (Test-Path -LiteralPath $scoresDir) {
    foreach ($f in Get-ChildItem -LiteralPath $scoresDir -Filter *.json) { $done[[int]($f.Name.Substring(0, 2))] = $true }
}

Write-Host "[matrix] $($plan.Count) planned runs ($($done.Count) already scored): arms $(@($plan.arm | Select-Object -Unique) -join '/'), DX9, muted, max network logging, stock retry timers"
foreach ($r in $plan) { Write-Host ("  {0,2}. {1,-3} p{2} {3}{4}" -f $r.index, $r.arm, $r.pass, $r.case, $(if ($done[[int]$r.index]) { '  (scored)' } else { '' })) }
if ($problems.Count) {
    $problems | ForEach-Object { Write-Host "[matrix] preflight: $_" -ForegroundColor Red }
    Write-Host '[matrix] preflight failed; nothing launched' -ForegroundColor Red
    exit 2
}
Write-Host "[matrix] preflight OK: $Clients instances match the source load chain (openshim.dll $($sourceHashes['plugins\openshim.dll'].Substring(0, 12)))"
if ($DryRun) { Write-Host "[matrix] dry run: nothing launched; would write $matrixDir"; exit 0 }

$null = New-Item -ItemType Directory -Force -Path $matrixDir, (Join-Path $matrixDir 'logs'), $scoresDir
if (-not $ResumeMatrix) {
    [ordered]@{
        started = (Get-Date).ToString('o'); passes = $Passes; arms = $Arms; only = $Only; clients = $Clients
        plan = $plan
        sourceHashes = $sourceHashes; instances = $instances
        openShim = Get-RepoState $OpenShimRepo @('reverse_engineering\Run-NetfixStressMatrix.ps1', 'reverse_engineering\p2p_netfix_score.py')
        harness = Get-RepoState (Split-Path $HarnessRoot) @(@('Run-BZRCoopMission.ps1', 'BZRCoopMission.ps1', 'BZRCoopLobby.ps1',
            'BZRCoopSession.ps1', 'BZRCoopDiagnostics.ps1', 'BZRCoopAudio.cs') | ForEach-Object { "reverse_engineering\$_" })
        server = Get-RepoState $ServerRepo @('server.py', 'native_network_health.py')
    } | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $matrixDir 'matrix.json')
}
Write-Host "[matrix] -> $matrixDir"

# ------------------------------------------------------------------ run --
$infraStreak = 0
$stopReason = ''
foreach ($r in $plan) {
    if ($done[[int]$r.index]) { continue }
    $parts = @($r.case -split '\s+' | Where-Object { $_ })
    $mission, $scenario = $parts[0], $parts[1]
    $override = ''
    $argText = @($parts | Select-Object -Skip 2 | ForEach-Object {
        $k, $v = $_ -split '=', 2
        if ($k -eq 'Override') { $override = Join-Path $HarnessRoot "coopflow\overrides\$v"; return }
        if ($v -in '1', 'true') { return "$k=`$true" }
        if ($v -in '0', 'false') { return "$k=`$false" }
        "$k='$($v -replace "'", "''")'"
    }) -join '; '

    # The arm is the only difference between runs: the kill switch is
    # inherited by the coordinator and every client it starts.
    $env:PSModulePath = ''
    $env:BZRNET_FAULT_INJECT = ''
    Remove-Item Env:BZR_DISABLE_RELIABLE_SEND_BACKLOG_FIX -ErrorAction SilentlyContinue
    if ($r.arm -eq 'off') { $env:OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX = '1' }
    else { Remove-Item Env:OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX -ErrorAction SilentlyContinue }

    $q = { param($s) "'" + ($s -replace "'", "''") + "'" }
    $cmd = "& $(& $q $MissionScript) -Mission $mission -Scenario $scenario -Clients $Clients -MaxNetworkLogging -MuteClients -SkipPrepare " +
           "-OpenShimRepo $(& $q $OpenShimRepo) -ServerRepo $(& $q $ServerRepo) -BZRCoopRoot $(& $q $BZRCoopRoot) -RunName $(& $q $r.run)" +
           $(if ($override) { " -ContentOverride $(& $q $override)" } else { '' }) +
           " -ScenarioArgs @{$argText}; exit `$LASTEXITCODE"
    $log = Join-Path $matrixDir ("logs\{0:D2}-{1}.log" -f [int]$r.index, $r.run)
    Write-Host ("`n[matrix] {0}/{1} {2} p{3} {4} -> {5}" -f $r.index, $plan.Count, $r.arm, $r.pass, $r.case, $r.run) -ForegroundColor Cyan
    $clock = [Diagnostics.Stopwatch]::StartNew()
    # Output goes to files: the run's server and coordinator inherit handles
    # and can outlive it, which would hold a pipe open.
    $p = Start-Process -FilePath $PowerShellExe -WorkingDirectory (Split-Path $HarnessRoot) `
        -ArgumentList '-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass', '-Command', "`"$($cmd -replace '"', '\"')`"" `
        -RedirectStandardOutput $log -RedirectStandardError "$log.err" -NoNewWindow -PassThru
    $null = $p.Handle
    $p.WaitForExit()
    $exit = $p.ExitCode
    Remove-Item Env:OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX -ErrorAction SilentlyContinue

    # Sequential, graceful: the next run starts only once every client is gone.
    $deadline = (Get-Date).AddSeconds($StopTimeoutSeconds)
    while ((Get-GameProcesses) -and (Get-Date) -lt $deadline) { Start-Sleep -Seconds 2 }
    if (Get-GameProcesses) {
        Write-Host '[matrix] clients still running; asking the harness to stop them' -ForegroundColor Yellow
        & $PowerShellExe -NoProfile -NonInteractive -ExecutionPolicy Bypass -File $SessionScript -Action Stop -Clients $Clients -BZRCoopRoot $BZRCoopRoot | Out-Null
        Start-Sleep -Seconds 10
        if (Get-GameProcesses) { $stopReason = 'clients would not stop'; break }
    }

    $runDir = Join-Path $BZRCoopRoot "runs\$($r.run)"
    if (-not (Test-Path -LiteralPath $runDir)) { $stopReason = "harness did not start $($r.run) (exit $exit; see $log)"; break }
    $scorePath = Join-Path $scoresDir ("{0:D2}-{1}.json" -f [int]$r.index, $r.run)
    & $Python $Scorer score $runDir --arm $r.arm --clients $Clients --case $r.case --pass-index $r.pass --index $r.index --out $scorePath
    if ($LASTEXITCODE -ne 0 -or -not (Test-Path -LiteralPath $scorePath)) { $stopReason = "scoring $($r.run) failed (exit $LASTEXITCODE)"; break }
    $class = (Get-Content -LiteralPath $scorePath -Raw | ConvertFrom-Json).class
    Write-Host ("[matrix] {0} -> {1} (harness exit {2}, {3:N1} min)" -f $r.run, $class, $exit, $clock.Elapsed.TotalMinutes) `
        -ForegroundColor $(if ($class -in 'STRICT_PASS', 'REPRODUCED', 'NOT_REPRODUCED') { 'Green' } else { 'Red' })
    & $Python $Scorer aggregate $matrixDir | Out-Null
    if ($LASTEXITCODE -ne 0) { $stopReason = "aggregate failed (exit $LASTEXITCODE)"; break }

    $infraStreak = if ($class -in 'INCOMPLETE', 'CRASH', 'GPU') { $infraStreak + 1 } else { 0 }
    if ($infraStreak -ge $MaxInfraFailures) { $stopReason = "$infraStreak consecutive infrastructure failures"; break }
}

& $Python $Scorer aggregate $matrixDir
if ($LASTEXITCODE -ne 0) { Write-Host '[matrix] aggregate failed' -ForegroundColor Red; exit 3 }
$summary = Get-Content -LiteralPath (Join-Path $matrixDir 'summary.json') -Raw | ConvertFrom-Json
if ($stopReason) {
    Write-Host "[matrix] stopped early: $stopReason. Resume: -ResumeMatrix '$matrixDir'" -ForegroundColor Red
}
Write-Host "`n[matrix] verdict $($summary.verdict) (acceptance $($summary.acceptance), comparison $($summary.comparison), $($summary.scored)/$($summary.planned) scored) -> $(Join-Path $matrixDir 'summary.md')"
if ($stopReason) { exit 4 }
if ($summary.verdict -ne 'PASS') { exit 1 }
exit 0
