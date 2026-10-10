# Session publication under real Windows reader contention; no game launches.
$ErrorActionPreference = 'Stop'
$source = Join-Path (Split-Path $PSScriptRoot) 'BZRCoopSession.ps1'
$tokens = $null; $errors = $null
$ast = [Management.Automation.Language.Parser]::ParseFile($source, [ref]$tokens, [ref]$errors)
if ($errors) { throw ($errors | Out-String) }
$writer = $ast.Find({ param($node) $node -is [Management.Automation.Language.FunctionDefinitionAst] -and $node.Name -eq 'Write-SessionFile' }, $true)
Invoke-Expression $writer.Extent.Text
$snapshotReader = $ast.Find({ param($node) $node -is [Management.Automation.Language.FunctionDefinitionAst] -and $node.Name -eq 'Read-SessionFile' }, $true).Extent.Text
$fixture = [IO.Path]::GetFullPath((Join-Path ([IO.Path]::GetTempPath()) ('bzr-session-io-' + [guid]::NewGuid().ToString('N'))))
$null = New-Item -ItemType Directory -Path $fixture
$SessionFile = Join-Path $fixture 'session.json'
$ready = Join-Path $fixture 'ready'; $stop = Join-Path $fixture 'stop'
$jobs = @()
try {
    Write-SessionFile @{ count = 0; clients = @(0, 1, 2, 3); payload = ('x' * 4096); tail = 'done' }
    if ((Get-Content -LiteralPath $SessionFile -Raw | ConvertFrom-Json).count -ne 0) { throw 'Initial snapshot failed' }
    $holder = Start-Job -ArgumentList $SessionFile, $ready -ScriptBlock {
        param($path, $signal)
        $stream = [IO.File]::Open($path, 'Open', 'Read', 'Read')
        try { [IO.File]::WriteAllText($signal, 'locked'); Start-Sleep -Milliseconds 400 }
        finally { $stream.Dispose() }
    }
    $jobs += $holder
    $deadline = (Get-Date).AddSeconds(10)
    while (-not (Test-Path -LiteralPath $ready)) {
        if ((Get-Date) -ge $deadline) { throw 'Reader lock did not start' }
        Start-Sleep -Milliseconds 10
    }
    $clock = [Diagnostics.Stopwatch]::StartNew()
    Write-SessionFile @{ count = 1; clients = @(0, 1, 2, 3); payload = ('x' * 4096); tail = 'done' }
    if ($clock.ElapsedMilliseconds -lt 150) { throw 'Reader lock did not exercise retry' }
    $null = Wait-Job $holder -Timeout 5
    Receive-Job $holder -ErrorAction Stop | Out-Null
    if ((Get-Content -LiteralPath $SessionFile -Raw | ConvertFrom-Json).count -ne 1) { throw 'Snapshot after lock failed' }

    Remove-Item -LiteralPath $ready
    $reader = Start-Job -ArgumentList $SessionFile, $ready, $stop, $snapshotReader -ScriptBlock {
        param($path, $signal, $done, $definition)
        $ErrorActionPreference = 'Stop'
        $SessionFile = $path
        Invoke-Expression $definition
        $reads = 0
        [IO.File]::WriteAllText($signal, 'reading')
        $deadline = (Get-Date).AddSeconds(15)
        while (-not (Test-Path -LiteralPath $done)) {
            if ((Get-Date) -ge $deadline) { throw 'Writer never finished' }
            $snapshot = Read-SessionFile
            if ($snapshot.tail -ne 'done' -or $snapshot.payload.Length -ne 4096 -or @($snapshot.clients).Count -ne 4) { throw "Reader observed a partial snapshot: count=$($snapshot.count), tail=$($snapshot.tail), bytes=$($snapshot.payload.Length), clients=$(@($snapshot.clients).Count)" }
            $reads++
            Start-Sleep -Milliseconds 2
        }
        $reads
    }
    $jobs += $reader
    $deadline = (Get-Date).AddSeconds(10)
    while (-not (Test-Path -LiteralPath $ready)) {
        if ((Get-Date) -ge $deadline) { throw 'Polling reader did not start' }
        Start-Sleep -Milliseconds 10
    }
    foreach ($count in 2..101) { Write-SessionFile @{ count = $count; clients = @(0, 1, 2, 3); payload = ('x' * 4096); tail = 'done' } }
    [IO.File]::WriteAllText($stop, 'done')
    $null = Wait-Job $reader -Timeout 5
    $reads = Receive-Job $reader -ErrorAction Stop
    if ($reader.State -ne 'Completed' -or $reads -lt 1) { throw 'Polling reader did not complete' }
    if ((Get-Content -LiteralPath $SessionFile -Raw | ConvertFrom-Json).count -ne 101) { throw 'Latest snapshot was lost' }
    $missionSource = Join-Path (Split-Path $PSScriptRoot) 'BZRCoopMission.ps1'
    $missionAst = [Management.Automation.Language.Parser]::ParseFile($missionSource, [ref]$tokens, [ref]$errors)
    foreach ($functionName in @('Read-CRFlowShared', 'Get-CRFlowSession')) {
        $definition = $missionAst.Find({ param($node) $node -is [Management.Automation.Language.FunctionDefinitionAst] -and $node.Name -eq $functionName }, $true)
        Invoke-Expression $definition.Extent.Text
    }
    $script:CRFlowCoopRoot = $fixture
    $script:CRFlowLatin1 = [Text.Encoding]::GetEncoding(28591)
    $flowSnapshot = Get-CRFlowSession
    if ($flowSnapshot.count -ne 101 -or @($flowSnapshot.clients).Count -ne 4) { throw 'Mission reader did not decode the session snapshot' }
    if (Get-ChildItem -LiteralPath $fixture -Filter '*.tmp') { throw 'Pending snapshot leaked' }
    Write-Host "Session IO passed: held-reader retry, 100 concurrent publications / $reads complete reads, latest snapshot and sidecar cleanup."
} finally {
    foreach ($job in $jobs) { if ($job.State -eq 'Running') { Stop-Job $job }; Remove-Job $job }
    $tempRoot = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not $fixture.StartsWith($tempRoot, [StringComparison]::OrdinalIgnoreCase)) { throw 'Unexpected fixture cleanup path' }
    Remove-Item -LiteralPath $fixture -Recurse -Force
}
