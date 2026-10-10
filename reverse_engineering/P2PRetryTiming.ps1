# Test-instance timer and receive overrides. Native defaults and shipped INIs stay unchanged.
# Token: first/interval writes EarlyUnreliableAccept = 0; first/interval+early writes 1.
function ConvertTo-P2PRetryTiming([string]$Timers) {
    if ($Timers -cnotmatch '^([0-9]+)/([0-9]+)(\+early)?$') { throw 'Timers must be decimal first/interval milliseconds, optionally followed by +early.' }
    $first = 0; $interval = 0; $early = [int]($Matches[3] -eq '+early')
    if (-not [int]::TryParse($Matches[1], [ref]$first) -or -not [int]::TryParse($Matches[2], [ref]$interval) -or
        $first -lt 50 -or $first -gt 10000 -or $interval -lt 50 -or $interval -gt 10000) {
        throw 'Both retry timers must be 50..10000 milliseconds, matching the native parser.'
    }
    @{first=$first; interval=$interval; early=$early; token="$first/$interval$(if ($early) { '+early' })"}
}

function Set-P2PRetryTimingText([string]$Text, [string]$Timers) {
    $values = ConvertTo-P2PRetryTiming $Timers
    $headers = [regex]::Matches($Text, '(?m)^\s*\[([^\]\r\n]+)\][^\r\n]*(?:\r?\n|$)')
    $network = @($headers | Where-Object { $_.Groups[1].Value.Trim() -ieq 'Network' })
    if ($network.Count -gt 1) { throw 'Ambiguous repeated [Network] sections; nothing written.' }
    $newline = if ($Text.Contains("`r`n")) { "`r`n" } else { "`n" }
    $keys = "ReliableFirstRetryMs = $($values.first)$newline" + "ReliableRetryIntervalMs = $($values.interval)$newline" +
        "EarlyUnreliableAccept = $($values.early)$newline"
    if (-not $network.Count) { return $Text.TrimEnd("`r", "`n") + $newline + '[Network]' + $newline + $keys }
    $begin = $network[0].Index + $network[0].Length
    $next = @($headers | Where-Object Index -gt $network[0].Index | Select-Object -First 1)
    $end = if ($next.Count) { $next[0].Index } else { $Text.Length }
    $body = $Text.Substring($begin, $end-$begin)
    $body = [regex]::Replace($body, '(?im)^\s*(ReliableFirstRetryMs|ReliableRetryIntervalMs|EarlyUnreliableAccept)\s*=[^\r\n]*(?:\r?\n|$)', '')
    $head = $Text.Substring(0, $begin)
    if (-not $head.EndsWith("`n")) { $head += $newline }
    if ($body -and -not $body.EndsWith("`n")) { $body += $newline }
    $head + $body + $keys + $Text.Substring($end)
}

function Set-P2PRetryTiming([string[]]$InstanceDirs, [string]$Timers, [string]$BackupDir) {
    if (Get-Process battlezone98redux -ErrorAction SilentlyContinue) { throw 'Cannot change retry timers while a game is alive.' }
    $records = @()
    # Validate every file before changing any, retaining the original bytes.
    foreach ($instance in $InstanceDirs) {
        $path = Join-Path $instance 'openshim.ini'
        $bytes = [IO.File]::ReadAllBytes($path)
        $encoding = [Text.Encoding]::GetEncoding(28591)
        $text = Set-P2PRetryTimingText ($encoding.GetString($bytes)) $Timers
        $records += @{path=$path; original=$bytes; replacement=$encoding.GetBytes($text)}
    }
    if (-not $records.Count) { throw 'No instances supplied; nothing written.' }
    if (-not $BackupDir) { throw 'A private backup directory is required before changing timers.' }
    if (Test-Path -LiteralPath $BackupDir) { throw 'Backup directory already exists; do not overwrite recovery evidence.' }
    $null = New-Item -ItemType Directory -Path $BackupDir
    # Persist exact original bytes before the first write, including a crash or
    # a client that cannot close. Recovery must wait until all games have exited.
    $records | ForEach-Object { @{path=$_.path; originalBase64=[Convert]::ToBase64String($_.original)} } |
        ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $BackupDir 'originals.json') -Encoding UTF8
    try {
        foreach ($record in $records) { [IO.File]::WriteAllBytes($record.path, $record.replacement) }
    } catch {
        foreach ($record in $records) { [IO.File]::WriteAllBytes($record.path, $record.original) }
        throw
    }
    $records
}

function Restore-P2PRetryTiming($Records) {
    if (Get-Process battlezone98redux -ErrorAction SilentlyContinue) { throw 'Clients remain alive; retry timer restoration is deferred.' }
    foreach ($record in $Records) {
        [IO.File]::WriteAllBytes($record.path, $record.original)
        $actual = [Convert]::ToBase64String([IO.File]::ReadAllBytes($record.path))
        if ($actual -ne [Convert]::ToBase64String($record.original)) { throw "Retry timer restore mismatch: $($record.path)" }
    }
}
