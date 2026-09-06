# openshim_support_wrap.ps1 - Windows-first live support telemetry wrapper.
#
# This is an experimental continuation of PR #116. It deliberately runs
# outside Battlezone so a game crash does not take telemetry down with it.
# Normal OpenShim launches do not use this file and never upload anything.
#
# Steam launch options (while qualifying the new backend):
#   cmd /c ""%LOCALAPPDATA%\openshim\openshim_support_wrap.bat" %command%"

[CmdletBinding()]
param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$Command
)

$ErrorActionPreference = 'Continue'
Set-StrictMode -Version 2

$ScriptDir = Split-Path -Parent $PSCommandPath
$Transport = Join-Path $ScriptDir 'openshim_support_transport.ps1'
$TransportAvailable = Test-Path -LiteralPath $Transport -PathType Leaf
if (-not $TransportAvailable) {
    Write-Host '[OpenShim Support] transport helper is missing; launching game without telemetry.'
}
else {
    . $Transport
}

$ConfDir = Join-Path $env:APPDATA 'openshim'
$ConfFile = Join-Path $ConfDir 'upload.conf'
$DataDir = Join-Path $env:LOCALAPPDATA 'openshim'
$SupportRoot = Join-Path $DataDir 'support-spool'
$SupportLog = Join-Path $DataDir 'openshim_support.log'
$LatestSupportIdFile = Join-Path $DataDir 'latest-support-id.txt'
$WrapperVersion = 'OpenShim-support-20260904b'
$BatchMaxEvents = 128
$BatchMaxChars = 32768
$BatchMaxAgeMs = 1000
$ArtifactMaxBytes = 24 * 1024 * 1024

function Write-SupportLog {
    param([string]$Message)
    $line = '[{0}] {1}' -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $Message
    Write-Host "[OpenShim Support] $Message"
    try {
        if (-not (Test-Path -LiteralPath $DataDir)) {
            New-Item -ItemType Directory -Force -Path $DataDir | Out-Null
        }
        Add-Content -LiteralPath $SupportLog -Value $line -Encoding UTF8 -ErrorAction Stop
    } catch { }
}

function Get-ConfValue {
    param([string]$Name)
    if (-not (Test-Path -LiteralPath $ConfFile -PathType Leaf)) { return '' }
    foreach ($line in (Get-Content -LiteralPath $ConfFile -ErrorAction SilentlyContinue)) {
        if ($line -match ('^\s*' + [regex]::Escape($Name) + '\s*=\s*(.*)$')) {
            return $Matches[1].Trim().Trim("'").Trim('"')
        }
    }
    return ''
}

function Test-ConfigEnabled {
    param([string]$Name)
    $envValue = [Environment]::GetEnvironmentVariable($Name)
    if ($envValue) { return $envValue -eq '1' }
    return (Get-ConfValue $Name) -eq '1'
}

# Steam can split an executable path with spaces across remaining arguments.
# Rejoin leading arguments until they identify an existing executable.
function Resolve-SplitCommand {
    param([string[]]$CommandArgs)
    if (-not $CommandArgs -or $CommandArgs.Count -eq 0) { return @() }
    if (Test-Path -LiteralPath $CommandArgs[0] -PathType Leaf) { return ,$CommandArgs }
    for ($n = 2; $n -le $CommandArgs.Count; ++$n) {
        $candidate = ($CommandArgs[0..($n - 1)] -join ' ')
        if (Test-Path -LiteralPath $candidate -PathType Leaf) {
            $rest = @()
            if ($n -lt $CommandArgs.Count) { $rest = @($CommandArgs[$n..($CommandArgs.Count - 1)]) }
            return ,([string[]](@($candidate) + $rest))
        }
    }
    return ,$CommandArgs
}

function Resolve-GameRoot {
    param([string]$Dir)
    if (-not $Dir) { return '' }
    if (Test-Path -LiteralPath (Join-Path $Dir 'battlezone98redux.exe') -PathType Leaf) { return $Dir }
    $up = Split-Path -Parent $Dir
    if ($up -and (Test-Path -LiteralPath (Join-Path $up 'battlezone98redux.exe') -PathType Leaf)) { return $up }
    return $Dir
}

function Get-GameDirFromCommand {
    param([string[]]$CommandArgs)
    foreach ($arg in $CommandArgs) {
        if ($arg -match '(?i)battlezone98redux\.exe$') { return (Split-Path -Parent $arg) }
    }
    foreach ($arg in $CommandArgs) {
        if (Test-Path -LiteralPath $arg -PathType Leaf) {
            return (Resolve-GameRoot (Split-Path -Parent $arg))
        }
    }
    return ''
}

# Match the proven launch behavior from PR #116: Steam commonly supplies
# Launcher\BZLauncher.exe, but that executable must run with the game root as
# its working directory so winmm.dll and the rest of the game-local state are
# resolved correctly.
function Start-GameProcess {
    param([string[]]$ResolvedCommand, [string]$GameDir)
    if (-not $ResolvedCommand -or $ResolvedCommand.Count -eq 0) { return $null }

    $exe = $ResolvedCommand[0]
    $workDir = $GameDir
    if (-not $workDir) { $workDir = Resolve-GameRoot (Split-Path -Parent $exe) }
    if ($workDir -and -not (Test-Path -LiteralPath $workDir)) { $workDir = '' }

    $spArgs = @{ FilePath = $exe; PassThru = $true }
    if ($ResolvedCommand.Count -gt 1) { $spArgs.ArgumentList = $ResolvedCommand[1..($ResolvedCommand.Count - 1)] }
    if ($workDir) { $spArgs.WorkingDirectory = $workDir }
    return (Start-Process @spArgs)
}

function Resolve-HarvestedPath {
    param([string]$GameDir, [string]$Name)
    if (-not $GameDir) { return $null }
    foreach ($rel in @((Join-Path 'logs' $Name), $Name)) {
        $path = Join-Path $GameDir $rel
        if (Test-Path -LiteralPath $path -PathType Leaf) { return $path }
    }
    return $null
}

function Get-FreshOpenShimLog {
    param([string]$GameDir, [DateTime]$SessionStartUtc, [System.Diagnostics.Process]$Process)
    while (-not $Process.HasExited) {
        $path = Resolve-HarvestedPath -GameDir $GameDir -Name 'openshim.log'
        if ($path) {
            try {
                if ((Get-Item -LiteralPath $path).LastWriteTimeUtc -ge $SessionStartUtc.AddSeconds(-2)) {
                    return $path
                }
            } catch { }
        }
        Start-Sleep -Milliseconds 100
        try { $Process.Refresh() } catch { }
    }
    return (Resolve-HarvestedPath -GameDir $GameDir -Name 'openshim.log')
}

function New-SpoolBatch {
    param(
        [string]$SessionDir,
        [int64]$Sequence,
        [object[]]$Events
    )
    $logDir = Join-Path $SessionDir 'logs'
    New-Item -ItemType Directory -Force -Path $logDir | Out-Null
    $name = '{0:D10}.json' -f $Sequence
    $final = Join-Path $logDir $name
    $temp = "$final.tmp"
    $payload = [ordered]@{ sequence = $Sequence; events = $Events }
    $payload | ConvertTo-Json -Depth 8 -Compress | Out-File -LiteralPath $temp -Encoding UTF8
    Move-Item -Force -LiteralPath $temp -Destination $final
    return $final
}

function Send-SpoolFile {
    param(
        [string]$Endpoint,
        [string]$SupportId,
        [string]$Token,
        [string]$Path
    )
    try {
        $payload = Get-Content -LiteralPath $Path -Raw -ErrorAction Stop | ConvertFrom-Json -ErrorAction Stop
        $uri = '{0}/v1/session/{1}/logs' -f $Endpoint.TrimEnd('/'), $SupportId
        $response = Invoke-OpenShimSupportJsonPost -Uri $uri -Body $payload -BearerToken $Token
        if ($response.Ok) {
            Remove-Item -Force -LiteralPath $Path -ErrorAction SilentlyContinue
            return $true
        }
    } catch { }
    return $false
}

function Drain-SessionLogs {
    param([string]$Endpoint, [string]$SupportId, [string]$Token, [string]$SessionDir)
    $logDir = Join-Path $SessionDir 'logs'
    if (-not (Test-Path -LiteralPath $logDir)) { return $true }
    foreach ($file in (Get-ChildItem -LiteralPath $logDir -Filter '*.json' -File -ErrorAction SilentlyContinue | Sort-Object Name)) {
        if (-not (Send-SpoolFile -Endpoint $Endpoint -SupportId $SupportId -Token $Token -Path $file.FullName)) {
            return $false
        }
    }
    return $true
}

function Save-SessionState {
    param([string]$SessionDir, $State)
    New-Item -ItemType Directory -Force -Path $SessionDir | Out-Null
    $State | ConvertTo-Json -Depth 6 | Out-File -LiteralPath (Join-Path $SessionDir 'session-state.json') -Encoding UTF8
}

function Read-SessionState {
    param([string]$SessionDir)
    $path = Join-Path $SessionDir 'session-state.json'
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { return $null }
    try { return (Get-Content -LiteralPath $path -Raw | ConvertFrom-Json) } catch { return $null }
}

function Copy-SanitizedTextArtifact {
    param([string]$Source, [string]$Destination)
    if (-not $Source -or -not (Test-Path -LiteralPath $Source -PathType Leaf)) { return $false }
    try {
        $encoding = New-Object System.Text.UTF8Encoding($false)
        $writer = New-Object System.IO.StreamWriter($Destination, $false, $encoding)
        try {
            foreach ($line in (Get-Content -LiteralPath $Source -ErrorAction Stop)) {
                $writer.WriteLine((Protect-OpenShimSupportText ([string]$line)))
            }
        } finally {
            $writer.Dispose()
        }
        return $true
    } catch {
        return $false
    }
}

function Copy-SanitizedTailArtifact {
    param([string]$Source, [string]$Destination, [int]$Tail = 5000)
    if (-not $Source -or -not (Test-Path -LiteralPath $Source -PathType Leaf)) { return $false }
    try {
        $lines = Get-Content -LiteralPath $Source -Tail $Tail -ErrorAction Stop
        $safe = @($lines | ForEach-Object { Protect-OpenShimSupportText ([string]$_) })
        $safe | Out-File -LiteralPath $Destination -Encoding UTF8
        return $true
    } catch {
        return $false
    }
}

function Send-PendingArtifacts {
    param([string]$Endpoint, [string]$SupportId, [string]$Token, [string]$SessionDir)
    $artifactDir = Join-Path $SessionDir 'artifacts'
    if (-not (Test-Path -LiteralPath $artifactDir)) { return @() }
    $sent = @()
    foreach ($file in (Get-ChildItem -LiteralPath $artifactDir -File -ErrorAction SilentlyContinue)) {
        if ($file.Length -gt $ArtifactMaxBytes) {
            Write-SupportLog "artifact $($file.Name) is over the support limit; retaining locally"
            continue
        }
        if (Send-OpenShimSupportArtifact -Endpoint $Endpoint -SupportId $SupportId -Token $Token -FilePath $file.FullName -ArtifactName $file.Name) {
            $sent += $file.Name
            Remove-Item -Force -LiteralPath $file.FullName -ErrorAction SilentlyContinue
        }
    }
    return ,$sent
}

function Invoke-PendingFinish {
    param([string]$Endpoint, [string]$SupportId, [string]$Token, [string]$SessionDir)
    $finishPath = Join-Path $SessionDir 'finish-pending.json'
    if (-not (Test-Path -LiteralPath $finishPath -PathType Leaf)) { return $false }
    try {
        $body = Get-Content -LiteralPath $finishPath -Raw | ConvertFrom-Json
        $uri = '{0}/v1/session/{1}/finish' -f $Endpoint.TrimEnd('/'), $SupportId
        $response = Invoke-OpenShimSupportJsonPost -Uri $uri -Body $body -BearerToken $Token
        if ($response.Ok) {
            Remove-Item -Force -LiteralPath $finishPath -ErrorAction SilentlyContinue
            return $true
        }
    } catch { }
    return $false
}

function Retry-PriorSessions {
    param([string]$CurrentSessionDir)
    if (-not (Test-Path -LiteralPath $SupportRoot)) { return }
    foreach ($dir in (Get-ChildItem -LiteralPath $SupportRoot -Directory -ErrorAction SilentlyContinue)) {
        if ($CurrentSessionDir -and $dir.FullName -eq $CurrentSessionDir) { continue }
        $state = Read-SessionState $dir.FullName
        if (-not $state) { continue }
        try {
            if ([DateTime]::Parse([string]$state.expires_at).ToUniversalTime() -le [DateTime]::UtcNow) {
                Write-SupportLog "prior support session $($state.support_id) expired; retaining unsent files locally"
                Remove-Item -Force -LiteralPath (Join-Path $dir.FullName 'session-state.json') -ErrorAction SilentlyContinue
                continue
            }
        } catch { continue }

        [void](Drain-SessionLogs -Endpoint $state.endpoint -SupportId $state.support_id -Token $state.token -SessionDir $dir.FullName)
        [void](Send-PendingArtifacts -Endpoint $state.endpoint -SupportId $state.support_id -Token $state.token -SessionDir $dir.FullName)

        $logsLeft = @(Get-ChildItem -LiteralPath (Join-Path $dir.FullName 'logs') -Filter '*.json' -File -ErrorAction SilentlyContinue).Count
        $artifactsLeft = @(Get-ChildItem -LiteralPath (Join-Path $dir.FullName 'artifacts') -File -ErrorAction SilentlyContinue).Count
        if ($logsLeft -eq 0 -and $artifactsLeft -eq 0 -and (Invoke-PendingFinish -Endpoint $state.endpoint -SupportId $state.support_id -Token $state.token -SessionDir $dir.FullName)) {
            Write-SupportLog "completed retry for prior support session $($state.support_id)"
            Remove-Item -Recurse -Force -LiteralPath $dir.FullName -ErrorAction SilentlyContinue
        }
    }
}

function Test-CleanGameExit {
    param([string]$GameDir)
    $bz = Resolve-HarvestedPath -GameDir $GameDir -Name 'BZLogger.txt'
    if (-not $bz) { return $false }
    try {
        return [bool]((Get-Content -LiteralPath $bz -Tail 2000 -ErrorAction Stop) -match 'Exiting Game With Return Code')
    } catch { return $false }
}

function Prepare-FinalArtifacts {
    param([string]$GameDir, [string]$SessionDir, [DateTime]$SessionStartUtc)
    $artifactDir = Join-Path $SessionDir 'artifacts'
    New-Item -ItemType Directory -Force -Path $artifactDir | Out-Null

    $shimLog = Resolve-HarvestedPath -GameDir $GameDir -Name 'openshim.log'
    if ($shimLog) { [void](Copy-SanitizedTextArtifact -Source $shimLog -Destination (Join-Path $artifactDir 'openshim.log')) }

    $crashLog = Resolve-HarvestedPath -GameDir $GameDir -Name 'openshim_crash.log'
    if ($crashLog) {
        try {
            if ((Get-Item -LiteralPath $crashLog).LastWriteTimeUtc -ge $SessionStartUtc.AddSeconds(-2)) {
                [void](Copy-SanitizedTextArtifact -Source $crashLog -Destination (Join-Path $artifactDir 'openshim_crash.log'))
            }
        } catch { }
    }

    $bzLog = Resolve-HarvestedPath -GameDir $GameDir -Name 'BZLogger.txt'
    if ($bzLog) { [void](Copy-SanitizedTailArtifact -Source $bzLog -Destination (Join-Path $artifactDir 'BZLogger.tail.txt') -Tail 5000) }

    # Minidumps can contain arbitrary process memory. Keep them opt-in even
    # inside support mode; text diagnostics are sanitized by default.
    if (Test-ConfigEnabled 'OPENSHIM_SUPPORT_INCLUDE_DUMPS') {
        $logDir = Join-Path $GameDir 'logs'
        if (Test-Path -LiteralPath $logDir) {
            foreach ($dump in (Get-ChildItem -LiteralPath $logDir -Filter 'openshim_crash_*.dmp' -File -ErrorAction SilentlyContinue)) {
                if ($dump.LastWriteTimeUtc -lt $SessionStartUtc.AddSeconds(-2)) { continue }
                if ($dump.Length -gt $ArtifactMaxBytes) {
                    Write-SupportLog "dump $($dump.Name) exceeds artifact limit; retaining only local game copy"
                    continue
                }
                Copy-Item -Force -LiteralPath $dump.FullName -Destination (Join-Path $artifactDir $dump.Name)
            }
        }
    }
}

function Test-FreshCrashEvidence {
    param([string]$GameDir, [DateTime]$SessionStartUtc)
    $crashLog = Resolve-HarvestedPath -GameDir $GameDir -Name 'openshim_crash.log'
    if ($crashLog) {
        try {
            if ((Get-Item -LiteralPath $crashLog).LastWriteTimeUtc -ge $SessionStartUtc.AddSeconds(-2) -and
                (Get-Item -LiteralPath $crashLog).Length -gt 0) { return $true }
        } catch { }
    }
    $logDir = Join-Path $GameDir 'logs'
    if (Test-Path -LiteralPath $logDir) {
        foreach ($dump in (Get-ChildItem -LiteralPath $logDir -Filter 'openshim_crash_*.dmp' -File -ErrorAction SilentlyContinue)) {
            if ($dump.LastWriteTimeUtc -ge $SessionStartUtc.AddSeconds(-2)) { return $true }
        }
    }
    return $false
}

function Run-LiveTail {
    param(
        [System.Diagnostics.Process]$Process,
        [string]$LogPath,
        [string]$Endpoint,
        [string]$SupportId,
        [string]$Token,
        [string]$SessionDir
    )

    $sequence = [int64]0
    $events = New-Object System.Collections.ArrayList
    $chars = 0
    $lastFlush = [DateTime]::UtcNow
    $stream = $null
    $reader = $null

    if ($LogPath) {
        try {
            $stream = New-Object System.IO.FileStream($LogPath, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite)
            $reader = New-Object System.IO.StreamReader($stream)
        } catch {
            Write-SupportLog "could not tail openshim.log: $($_.Exception.Message)"
        }
    }

    try {
        while ($true) {
            $readAny = $false
            if ($reader) {
                while (-not $reader.EndOfStream) {
                    $line = $reader.ReadLine()
                    if ($null -eq $line) { break }
                    $event = Convert-OpenShimSupportLogLine -Line $line
                    [void]$events.Add($event)
                    $chars += $line.Length
                    $readAny = $true
                    if ($events.Count -ge $BatchMaxEvents -or $chars -ge $BatchMaxChars) { break }
                }
            }

            $ageMs = ([DateTime]::UtcNow - $lastFlush).TotalMilliseconds
            if ($events.Count -gt 0 -and ($events.Count -ge $BatchMaxEvents -or $chars -ge $BatchMaxChars -or $ageMs -ge $BatchMaxAgeMs -or $Process.HasExited)) {
                $batch = @($events.ToArray())
                [void](New-SpoolBatch -SessionDir $SessionDir -Sequence $sequence -Events $batch)
                ++$sequence
                $events.Clear()
                $chars = 0
                $lastFlush = [DateTime]::UtcNow
                [void](Drain-SessionLogs -Endpoint $Endpoint -SupportId $SupportId -Token $Token -SessionDir $SessionDir)
            }

            if ($Process.HasExited) {
                if (-not $reader -or $reader.EndOfStream) { break }
            }
            if (-not $readAny) { Start-Sleep -Milliseconds 100 }
            try { $Process.Refresh() } catch { }
        }
    } finally {
        if ($reader) { $reader.Dispose() }
        elseif ($stream) { $stream.Dispose() }
    }

    return $sequence - 1
}

if (-not $Command -or $Command.Count -eq 0) {
    Write-SupportLog 'no Steam command supplied'
    exit 2
}

$resolved = @(Resolve-SplitCommand $Command)
if (-not $resolved -or $resolved.Count -eq 0 -or -not (Test-Path -LiteralPath $resolved[0] -PathType Leaf)) {
    Write-SupportLog "could not resolve Steam command: $($Command -join ' ')"
    exit 2
}

$gameDir = Get-GameDirFromCommand $resolved
$endpoint = ''
if ($TransportAvailable) {
    $endpoint = Get-OpenShimSupportEndpoint -ConfFile $ConfFile
}

# Always try old pending support sessions before creating a new one. This is
# what makes a transient outage or an abrupt wrapper close survivable.
if ($TransportAvailable) {
    Retry-PriorSessions -CurrentSessionDir ''
}

$sessionStartUtc = [DateTime]::UtcNow
$session = $null
$sessionDir = ''
if ($endpoint) {
    $distribution = if ($gameDir -match '(?i)[\\/]steamapps[\\/]') { 'steam' } elseif ($gameDir -match '(?i)gog') { 'gog' } else { 'unknown' }
    $exeHash = ''
    $gameExe = if ($gameDir) { Join-Path $gameDir 'battlezone98redux.exe' } else { '' }
    if ($gameExe -and (Test-Path -LiteralPath $gameExe -PathType Leaf)) {
        try { $exeHash = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash } catch { }
    }

    $session = New-OpenShimSupportSession -Endpoint $endpoint -Platform 'windows' -Distribution $distribution -WrapperVersion $WrapperVersion -ExeSha256 $exeHash
    if ($session.Ok) {
        $sessionDir = Join-Path $SupportRoot $session.SupportId
        $state = [ordered]@{
            endpoint = $endpoint
            support_id = $session.SupportId
            token = $session.Token
            expires_at = $session.ExpiresAt
            started_at = $sessionStartUtc.ToString('o')
        }
        Save-SessionState -SessionDir $sessionDir -State $state
        try { $session.SupportId | Out-File -LiteralPath $LatestSupportIdFile -Encoding ASCII } catch { }
        Write-SupportLog "remote support enabled - Support ID: $($session.SupportId)"
        Write-Host ''
        Write-Host '============================================================'
        Write-Host "  OpenShim Support ID: $($session.SupportId)"
        Write-Host '  Send this ID to the person helping you.'
        Write-Host '============================================================'
        Write-Host ''
    } else {
        Write-SupportLog "support backend unavailable (HTTP $($session.StatusCode)); game will launch normally"
        $session = $null
    }
} else {
    Write-SupportLog 'OPENSHIM_SUPPORT_ENDPOINT is not configured; game will launch normally'
}

$process = $null
try {
    $process = Start-GameProcess -ResolvedCommand $resolved -GameDir $gameDir
} catch {
    Write-SupportLog "game launch failed: $($_.Exception.Message)"
    exit 3
}
if (-not $process) {
    Write-SupportLog 'game launch failed without a process handle'
    exit 3
}

$finalSequence = [int64]-1
if ($session) {
    $logPath = Get-FreshOpenShimLog -GameDir $gameDir -SessionStartUtc $sessionStartUtc -Process $process
    $finalSequence = Run-LiveTail -Process $process -LogPath $logPath -Endpoint $endpoint -SupportId $session.SupportId -Token $session.Token -SessionDir $sessionDir
} else {
    $process.WaitForExit()
}

try { $process.WaitForExit() } catch { }
$exitCode = 0
try { $exitCode = $process.ExitCode } catch { }

if ($session) {
    [void](Drain-SessionLogs -Endpoint $endpoint -SupportId $session.SupportId -Token $session.Token -SessionDir $sessionDir)
    Prepare-FinalArtifacts -GameDir $gameDir -SessionDir $sessionDir -SessionStartUtc $sessionStartUtc
    [void](Send-PendingArtifacts -Endpoint $endpoint -SupportId $session.SupportId -Token $session.Token -SessionDir $sessionDir)

    $cleanExit = Test-CleanGameExit -GameDir $gameDir
    $crashed = (Test-FreshCrashEvidence -GameDir $gameDir -SessionStartUtc $sessionStartUtc) -or (-not $cleanExit)
    $finish = [ordered]@{
        exit_code = $exitCode
        clean_exit = [bool]$cleanExit
        crashed = [bool]$crashed
        final_sequence = $finalSequence
        artifacts = @()
    }
    $finish | ConvertTo-Json -Depth 5 | Out-File -LiteralPath (Join-Path $sessionDir 'finish-pending.json') -Encoding UTF8

    $logsLeft = @(Get-ChildItem -LiteralPath (Join-Path $sessionDir 'logs') -Filter '*.json' -File -ErrorAction SilentlyContinue).Count
    $artifactsLeft = @(Get-ChildItem -LiteralPath (Join-Path $sessionDir 'artifacts') -File -ErrorAction SilentlyContinue).Count
    if ($logsLeft -eq 0 -and $artifactsLeft -eq 0 -and (Invoke-PendingFinish -Endpoint $endpoint -SupportId $session.SupportId -Token $session.Token -SessionDir $sessionDir)) {
        Write-SupportLog "support session $($session.SupportId) completed"
        Remove-Item -Recurse -Force -LiteralPath $sessionDir -ErrorAction SilentlyContinue
    } else {
        Write-SupportLog "support session $($session.SupportId) has pending data in $sessionDir; next support launch will retry it"
    }
}

exit $exitCode
