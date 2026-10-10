<#
.SYNOPSIS
Compare guarded retry timings with four prepared internal battle-load clients.
.DESCRIPTION
Uses Run-BZRBattleLoad.ps1's launch lock, maximum captures, and graceful close.
Each arm saves original INI bytes before writing, verifies all four archived
configs/native apply logs, and restores the INIs after all games exit. A live
game prevents restoration and the next launch; originals.json is retained for
recovery. Native defaults remain unchanged. Prepare/deploy the full matching
load chain and an active DX9 display mode before calling this script.
Timer tokens are first/interval ms; append +early and/or +nak (or +nak0), in that order
(e.g. 1000/2500+early+nak), to enable the opt-in EarlyUnreliableAccept and
EarlyNakAccept receivers in that arm. +nak pins EarlyNakReorderMs 40; +nak0 pins
it to 0 (the previous NAK gate) so the two gates can be A/B tested.
Equal impairment seeds mean equal configured profiles, not identical traffic.
.EXAMPLE
./Run-P2PRetryBattleMatrix.ps1 -BattleRepo C:\path\BZR-OpenShim-battleload -ServerRepo C:\path\server -DryRun
#>
param(
    [Parameter(Mandatory=$true)][string]$BattleRepo,
    [Parameter(Mandatory=$true)][string]$ServerRepo,
    [string]$BZRCoopRoot = 'C:\BZRCoop',
    [string]$Python = 'python',
    [string[]]$Timers = @('1000/2500','300/800'),
    [string[]]$Impair = @('loss=3,seed=212','loss=3,rate=256,queue=200,seed=213'),
    [ValidateRange(1,10)][int]$Passes = 1,
    [ValidateRange(4,160)][int]$Units = 80,
    [ValidateRange(15,300)][int]$Seconds = 60,
    [ValidateRange(0,16)][int]$Beacons = 16,
    [ValidateRange(0,128)][int]$Powerups = 64,
    [string]$RunStamp = (Get-Date -Format 'yyyyMMdd-HHmmss'),
    [string]$CoopOverride = '',
    [switch]$AllowNoAudioEndpoint,
    [ValidateSet('Classic','Strategy')][string]$Mode = 'Classic',
    [switch]$DryRun
)
$ErrorActionPreference = 'Stop'
if ([IO.Path]::GetFullPath($BZRCoopRoot).TrimEnd('\') -ine 'C:\BZRCoop') { throw 'The current battle harness supports only C:\BZRCoop.' }
. (Join-Path $PSScriptRoot 'P2PRetryTiming.ps1')
$battle = Join-Path $BattleRepo 'reverse_engineering\Run-BZRBattleLoad.ps1'
$scorer = Join-Path $PSScriptRoot 'p2p_netfix_score.py'
$ps51 = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'
if ($RunStamp -notmatch '^[a-zA-Z0-9-]+$') { throw 'RunStamp must contain only letters, digits and hyphens.' }
if ($Units % 2) { throw 'Units must be even.' }
if ($Mode -eq 'Strategy') {
    # One owned army per client (Run-BZRBattleLoad -Mode Strategy); no extras.
    if ($Units % 4) { throw 'Strategy mode needs Units divisible by 4 (one army per client).' }
    $Beacons = 0; $Powerups = 0
}
if (Get-Process battlezone98redux -ErrorAction SilentlyContinue) { throw 'A game is alive; nothing changed.' }
. (Join-Path $PSScriptRoot 'BZRHarness.ps1')
if (-not (Test-Path -LiteralPath $battle)) { throw "Missing battle harness: $battle" }
if (-not (Get-Command $battle).Parameters.ContainsKey('InheritedLaunchLockOwner')) { throw 'Battle harness lacks the explicit inherited-lock handoff.' }
$coopHash = $null
if ($CoopOverride) {
    if (-not (Get-Command $battle).Parameters.ContainsKey('CoopOverride')) { throw 'Battle harness lacks the co-op test override.' }
    $coopHash = (Get-FileHash -LiteralPath $CoopOverride).Hash
}
if (-not $Timers.Count -or -not $Impair.Count) { throw 'Timer and impairment axes must not be empty.' }
$Timers = @($Timers | ForEach-Object { (ConvertTo-P2PRetryTiming $_).token })
if (@($Timers | Select-Object -Unique).Count -ne $Timers.Count) { throw 'Duplicate timer arms.' }
$instances = @(0..3 | ForEach-Object { Join-Path $BZRCoopRoot "instances\Instance$_\Battlezone 98 Redux" })
$chain = @('winmm.dll','bzloader.dll','plugins\openshim.dll','scripts\patches.json')
$hashes = @{}
foreach ($rel in $chain) {
    $source = Join-Path (Split-Path $PSScriptRoot) $(if ($rel -eq 'scripts\patches.json') { $rel } else { "bin\Release\$rel" })
    $hashes[$rel] = (Get-FileHash -LiteralPath $source).Hash
    foreach ($instance in $instances) {
        if ((Get-FileHash -LiteralPath (Join-Path $instance $rel)).Hash -ne $hashes[$rel]) { throw "Load chain mismatch: $instance\$rel" }
    }
}
# Validate every INI for every timer arm without writing.
foreach ($instance in $instances) {
    $text = [IO.File]::ReadAllText((Join-Path $instance 'openshim.ini'))
    foreach ($timer in $Timers) { Set-P2PRetryTimingText $text $timer | Out-Null }
}
$control = Join-Path $BZRCoopRoot "runs\retry-battle-matrix-$RunStamp"
if (Test-Path -LiteralPath $control) { throw 'Matrix already exists; use a new RunStamp to preserve captures.' }
$plan = @()
foreach ($pass in 1..$Passes) {
    for ($profileIndex=0; $profileIndex -lt $Impair.Count; $profileIndex++) {
        # Reverse timer order on alternate passes to reduce order bias.
        $order = @($Timers)
        if ($pass % 2 -eq 0) { [array]::Reverse($order) }
        foreach ($timer in $order) {
            $tag = $timer.Replace('/','x').Replace('+early','e').Replace('+nak0','z').Replace('+nak','n')
            $plan += [pscustomobject]@{index=$plan.Count+1; arm='on'; pass=$pass; timers=$timer; impair=$Impair[$profileIndex];
                case="$(if ($Mode -eq 'Strategy') { 'sbattle' } else { 'nbattle' }) ${Units}AI ${Beacons}beacons ${Powerups}powerups ${Seconds}s";
                run="retry-battle-t$tag-i$($profileIndex+1)-p$pass-$RunStamp"}
        }
    }
}
$plan | Format-Table index,timers,impair,run | Out-Host
if ($DryRun) { Write-Host '[retry] Dry run: no config changes or launches.'; exit 0 }
$scores = Join-Path $control 'scores'
$null = New-Item -ItemType Directory -Path $control,$scores
$toolHashes = @{}
foreach ($name in @('Run-P2PRetryBattleMatrix.ps1','P2PRetryTiming.ps1','p2p_retry_timing.py','p2p_netfix_score.py')) {
    $toolHashes[$name] = (Get-FileHash -LiteralPath (Join-Path $PSScriptRoot $name)).Hash
}
$harnessHashes = @{}
foreach ($name in @('Run-BZRBattleLoad.ps1','Run-BZRCoopMission.ps1','BZRCoopLaunchLock.ps1','BZRHarness.ps1')) {
    $harnessHashes[$name] = (Get-FileHash -LiteralPath (Join-Path $BattleRepo "reverse_engineering\$name")).Hash
}
[ordered]@{started=(Get-Date).ToString('o'); clients=4; plan=$plan; sourceHashes=$hashes; toolHashes=$toolHashes;
    harnessHashes=$harnessHashes;
    coopOverrideSha256=$coopHash;
    note='Fix ON in every arm; guarded timer overrides plus explicit [Network] EarlyUnreliableAccept and EarlyNakAccept (tokens +early / +nak / +nak0 = 1, else 0; EarlyNakReorderMs 40 / 0 for +nak / +nak0), '+
        'verified per client from the archived INI and [P2PRECV] native armed/unavailable/total log lines; nondeterministic combat/traffic.'} |
    ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $control 'matrix.json')
$prior = @{}
foreach ($key in @('OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX','BZR_DISABLE_RELIABLE_SEND_BACKLOG_FIX','BZRNET_FAULT_INJECT','BZR_FORCE_WINDOWED')) {
    $prior[$key] = [Environment]::GetEnvironmentVariable($key,'Process')
    [Environment]::SetEnvironmentVariable($key,$null,'Process')
}
$env:BZR_FORCE_WINDOWED='1'
try {
    foreach ($row in $plan) {
        $records = @(Set-P2PRetryTiming $instances $row.timers (Join-Path $control "timer-backup-$($row.index)"))
        try {
            $runPath = Join-Path $BZRCoopRoot "runs\$($row.run)"
            if (Test-Path -LiteralPath $runPath) { throw 'Run already exists; refusing to overwrite captures.' }
            $battleArgs = @('-NoProfile','-ExecutionPolicy','Bypass','-File',$battle,'-Units',$Units,'-Seconds',$Seconds,
                '-Beacons',$Beacons,'-Powerups',$Powerups,'-RunName',$row.run,'-ServerRepo',$ServerRepo,'-Python',$Python,
                '-InheritedLaunchLockOwner',$env:BZR_LAUNCH_LOCK_HELD)
            if ($row.impair) { $battleArgs += @('-Impair',$row.impair) }
            if ($Mode -eq 'Strategy') {
                if (-not (Get-Command $battle).Parameters.ContainsKey('Mode')) { throw 'Battle harness lacks -Mode Strategy.' }
                $battleArgs += @('-Mode','Strategy')
            }
            if ($AllowNoAudioEndpoint) { $battleArgs += '-AllowNoAudioEndpoint' }
            if ($CoopOverride) {
                if ((Get-FileHash -LiteralPath $CoopOverride).Hash -ne $coopHash) { throw 'Co-op override changed between arms.' }
                $battleArgs += @('-CoopOverride',$CoopOverride)
            }
            & $ps51 @battleArgs 2>&1 | Tee-Object -FilePath (Join-Path $control "run-$($row.index).log") | Out-Host
            $exitCode = $LASTEXITCODE
            if (Get-Process battlezone98redux -ErrorAction SilentlyContinue) { throw 'Games remain alive; restoration deferred and matrix stopped.' }
            $out = Join-Path $scores ('{0:D2}.json' -f $row.index)
            $scoreArgs = @('score',$runPath,'--arm','on','--clients',4,'--timers',$row.timers,'--case',$row.case,'--pass-index',$row.pass,'--index',$row.index,'--out',$out)
            if ($row.impair) { $scoreArgs += @('--impair',$row.impair) }
            & $Python $scorer @scoreArgs | Out-Host
            if ($LASTEXITCODE -ne 0) { throw 'Scoring failed.' }
            $result = Get-Content -LiteralPath $out -Raw | ConvertFrom-Json
            if ($result.class -in @('INCOMPLETE','CRASH','GPU','ARM_MISMATCH','FLOW_FAIL')) { throw "Run failed: $($result.class), harness exit $exitCode" }
        } finally {
            Restore-P2PRetryTiming $records
        }
    }
} finally {
    foreach ($key in $prior.Keys) { [Environment]::SetEnvironmentVariable($key,$prior[$key],'Process') }
    & $Python $scorer aggregate $control | Out-Host
}
if ((Get-Content -LiteralPath (Join-Path $control 'summary.json') -Raw | ConvertFrom-Json).verdict -ne 'PASS') { throw 'Matrix acceptance failed; see summary.json.' }
Write-Host "[retry] Completed: $control"
