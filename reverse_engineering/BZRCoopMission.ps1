# In-mission co-op flow testing for BZRCoopSession clients (dot-source it).
#
# BZRCoopSession.ps1 gets two real clients onto one PC and BZRCoopLobby.ps1
# launches a map on both. This library takes over once the mission loads:
#
#   * Install-CRFlowProbe puts coopflow\CRFlowProbe.lua into an instance's copy
#     of Campaign Reimagined and appends an Attach() stub to the mission script.
#     Instances are disposable copies under C:\BZRCoop; the live install and the
#     CR repository are never touched.
#   * Invoke-CRFlow runs a Lua chunk inside one client's mission
#     (<instance>\crflow\cmd.txt -> out.txt) and returns its decoded result.
#     Wait-CRFlow polls a Lua condition until it is true.
#   * Update-CRFlowEvents / Wait-CRFlowEvent read the probe's "[CRFLOW] {json} #END"
#     lines from each client's BZLogger (flags, presentation ops, snapshots).
#   * Invoke-CRFlowStep records a named step (JSONL + screenshots of both
#     clients) and Test-CRFlow* add host/guest parity checks to the report.
#
# Scenarios (coopflow\scenarios\*.ps1) are plain PowerShell using these
# functions; Run-BZRCoopMission.ps1 runs one end to end. Windows PowerShell 5.1
# compatible (BZRWindowInput.ps1 needs System.Drawing).

. "$PSScriptRoot\BZRWindowInput.ps1"

$script:CRFlowCoopRoot = 'C:\BZRCoop'
$script:CRFlowModId = '3686673790'
$script:CRFlowProbeSource = Join-Path $PSScriptRoot 'coopflow\CRFlowProbe.lua'
$script:CRFlowMarker = '-- [CRFLOW] test probe stub (BZRCoopMission.ps1; test instances only)'
# Byte-preserving text encoding for mission scripts of unknown encoding.
$script:CRFlowLatin1 = [Text.Encoding]::GetEncoding(28591)
$script:CRFlowEvents = @{}
$script:CRFlowLogPos = @{}
$script:CRFlowRun = $null

# Presentation calls the leader replicates; the guest's op stream must match.
$script:CRFlowReplicatedOps = @('ClearObjectives', 'AddObjective', 'UpdateObjective', 'SetObjectiveOn',
    'SetObjectiveOff', 'SetObjectiveName', 'SetUserTarget', 'RemoveObject', 'SetMaxHealth',
    'Play', 'Queue', 'Stop', 'SucceedMission', 'FailMission')

# ------------------------------------------------------------- install --

function Get-CRFlowStub([string]$Mission) {
    # Appended at the end of the mission chunk, so M/CRCoop/native/... resolve
    # to the mission's file-level locals; names a mission lacks resolve to nil.
@"

$script:CRFlowMarker
do
    local ok, probe = pcall(require, "CRFlowProbe")
    if ok and type(probe) == "table" then
        probe.Attach({
            mission = "$Mission",
            getM = function() return M end,
            CRCoop = CRCoop, exu = exu, native = native,
            getLocals = function()
                return {
                    events = type(events) == "table" and #events or nil,
                    receivedEvent = receivedEvent,
                    localCameraActive = localCameraActive,
                    cameraSkipped = cameraSkipped,
                    cameraGeneration = cameraGeneration,
                    localCameraGeneration = localCameraGeneration,
                    remoteCameraSerial = remoteCameraSerial,
                }
            end,
        })
    else
        print("[CRFLOW] {\"k\":\"error\",\"msg\":\"require CRFlowProbe failed: " .. tostring(probe):gsub('[\\"]', "'") .. "\"} #END")
    end
end
"@ -replace "`r?`n", "`r`n"
}

function Install-CRFlowProbe {
    param([Parameter(Mandatory)][string]$InstanceDir, [Parameter(Mandatory)][string]$Mission)
    $full = [IO.Path]::GetFullPath($InstanceDir)
    $instances = [IO.Path]::GetFullPath((Join-Path $script:CRFlowCoopRoot 'instances')) + '\'
    if (-not $full.StartsWith($instances, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Refusing to install the test probe outside $instances ($full)"
    }
    $mod = Join-Path $full "mods\$($script:CRFlowModId)"
    $scriptPath = Join-Path $mod "$Mission.lua"
    if (-not (Test-Path -LiteralPath $scriptPath)) { throw "Mission script not found: $scriptPath (was the instance prepared with -CampaignStage?)" }
    Copy-Item -LiteralPath $script:CRFlowProbeSource -Destination (Join-Path $mod 'CRFlowProbe.lua') -Force

    $text = [IO.File]::ReadAllText($scriptPath, $script:CRFlowLatin1)
    $at = $text.IndexOf($script:CRFlowMarker)
    if ($at -ge 0) { $text = $text.Substring(0, $at).TrimEnd() + "`r`n" }
    [IO.File]::WriteAllText($scriptPath, $text + (Get-CRFlowStub $Mission), $script:CRFlowLatin1)

    $flow = Join-Path $full 'crflow'
    if (Test-Path -LiteralPath $flow) { Remove-Item -LiteralPath $flow -Recurse -Force }
    New-Item -ItemType Directory -Path $flow | Out-Null
    [pscustomobject]@{ Instance = $full; Script = $scriptPath; Probe = (Join-Path $mod 'CRFlowProbe.lua') }
}

# ------------------------------------------------------------- session --

function Get-CRFlowSession {
    $path = Join-Path $script:CRFlowCoopRoot 'session.json'
    if (-not (Test-Path -LiteralPath $path)) { throw "No BZRCoop session ($path)" }
    Get-Content -LiteralPath $path -Raw | ConvertFrom-Json
}

function Get-CRFlowClient([int]$Index) {
    $c = (Get-CRFlowSession).clients | Where-Object index -eq $Index
    if (-not $c) { throw "No client $Index in the session" }
    $c
}

function Get-CRFlowLogPath($Client) {
    Get-ChildItem -LiteralPath $Client.dir, (Join-Path $Client.dir 'logs') -Filter 'BZLogger.txt' -File -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty FullName
}

function Read-CRFlowShared([string]$Path, [long]$Offset = 0) {
    $fs = [IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    try {
        if ($Offset -gt $fs.Length) { $Offset = 0 }
        $null = $fs.Seek($Offset, 'Begin')
        $bytes = New-Object byte[] ($fs.Length - $Offset)
        $read = 0
        while ($read -lt $bytes.Length) {
            $n = $fs.Read($bytes, $read, $bytes.Length - $read)
            if ($n -le 0) { break }
            $read += $n
        }
        [pscustomobject]@{ Text = $script:CRFlowLatin1.GetString($bytes, 0, $read); End = $Offset + $read }
    } finally { $fs.Dispose() }
}

# -------------------------------------------------------------- commands --

function ConvertFrom-CRFlowJson([string]$Json) {
    $Json = $Json.Trim()
    if ($Json -eq '' -or $Json -eq 'null') { return $null }
    if ($Json -eq 'true') { return $true }
    if ($Json -eq 'false') { return $false }
    # Wrapping keeps scalars and one-element arrays intact under PS 5.1.
    (ConvertFrom-Json ('{"v":' + $Json + '}')).v
}

function Invoke-CRFlow {
    param([Parameter(Mandatory)][int]$Client, [Parameter(Mandatory)][string]$Lua,
          [int]$TimeoutSeconds = 20, [switch]$AllowError)
    $c = Get-CRFlowClient $Client
    $dir = Join-Path $c.dir 'crflow'
    $cmd = Join-Path $dir 'cmd.txt'
    $out = Join-Path $dir 'out.txt'
    $seq = 1
    if (Test-Path -LiteralPath $cmd) {
        $m = [regex]::Match((Read-CRFlowShared $cmd).Text, '^seq=(\d+)')
        if ($m.Success) { $seq = [int]$m.Groups[1].Value + 1 }
    }
    $tmp = Join-Path $dir 'cmd.tmp'
    [IO.File]::WriteAllText($tmp, "seq=$seq`n$Lua", [Text.UTF8Encoding]::new($false))
    for ($i = 0; ; $i++) {
        try { Move-Item -LiteralPath $tmp -Destination $cmd -Force; break }
        catch [IO.IOException] { if ($i -ge 20) { throw }; Start-Sleep -Milliseconds 50 }
    }
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 150
        if (-not (Test-Path -LiteralPath $out)) { continue }
        $text = try { (Read-CRFlowShared $out).Text } catch { '' }
        $m = [regex]::Match($text, '^seq=(\d+)\r?\nok=(true|false)\r?\n([\s\S]*)\r?\n#END\r?\n?$')
        if ($m.Success -and [int]$m.Groups[1].Value -eq $seq) {
            $ok = $m.Groups[2].Value -eq 'true'
            $value = ConvertFrom-CRFlowJson $m.Groups[3].Value
            if (-not $ok -and -not $AllowError) { throw "client $Client command $seq failed: $($value.error)`n$Lua" }
            if ($AllowError) { return [pscustomobject]@{ Ok = $ok; Value = $value } }
            return $value
        }
    }
    $alive = [bool](Get-Process -Id $c.pid -ErrorAction SilentlyContinue)
    $log = Get-CRFlowLogPath $c
    $last = if ($log) { (Get-Content -LiteralPath $log -Tail 1) } else { '' }
    throw "client $Client did not answer command $seq in ${TimeoutSeconds}s (process alive=$alive; is the probe attached and the mission running?). Last log: $last"
}

function Test-CRFlowTruthy($Value) {
    # Lua truthiness: only nil and false are false.
    -not ($null -eq $Value -or ($Value -is [bool] -and -not $Value))
}

function Wait-CRFlow {
    param([Parameter(Mandatory)][int]$Client, [Parameter(Mandatory)][string]$Lua,
          [int]$TimeoutSeconds = 60, [double]$PollSeconds = 1)
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    $last = $null
    do {
        $last = Invoke-CRFlow -Client $Client -Lua $Lua
        if (Test-CRFlowTruthy $last) { return $last }
        Start-Sleep -Milliseconds ([int]($PollSeconds * 1000))
    } while ((Get-Date) -lt $deadline)
    throw "client ${Client}: '$Lua' still false after ${TimeoutSeconds}s (last $(ConvertTo-Json $last -Compress -Depth 6))"
}

function Send-CRFlowKey([int]$Client, [int]$VirtualKey) {
    Send-BZRClientKey (Get-CRFlowClient $Client).pid $VirtualKey
}

# ---------------------------------------------------------------- events --

# Starts event collection at the current end of each client's log, so only
# lines written by the coming mission count.
# -FromStart reads each log from the beginning instead (attaching to a mission
# that is already running; each client log covers one launch).
function Set-CRFlowLogMark([int[]]$Clients = @(0, 1), [switch]$FromStart) {
    foreach ($i in $Clients) {
        $log = Get-CRFlowLogPath (Get-CRFlowClient $i)
        $script:CRFlowLogPos[$i] = if ($log -and -not $FromStart) { (Get-Item -LiteralPath $log).Length } else { 0 }
        $script:CRFlowEvents[$i] = New-Object System.Collections.ArrayList
    }
}

function Update-CRFlowEvents([int]$Client) {
    if (-not $script:CRFlowEvents.ContainsKey($Client)) { Set-CRFlowLogMark @($Client) }
    $log = Get-CRFlowLogPath (Get-CRFlowClient $Client)
    if (-not $log) { return $script:CRFlowEvents[$Client] }
    $chunk = Read-CRFlowShared $log $script:CRFlowLogPos[$Client]
    $complete = $chunk.Text.LastIndexOf("`n")
    if ($complete -ge 0) {
        $text = $chunk.Text.Substring(0, $complete + 1)
        $script:CRFlowLogPos[$Client] += $script:CRFlowLatin1.GetByteCount($text)
        foreach ($m in [regex]::Matches($text, '\[CRFLOW\] (\{.*\}) #END')) {
            try {
                $ev = ConvertFrom-Json $m.Groups[1].Value
                $ev | Add-Member -NotePropertyName client -NotePropertyValue $Client
                [void]$script:CRFlowEvents[$Client].Add($ev)
            } catch {
                [void]$script:CRFlowEvents[$Client].Add([pscustomobject]@{ k = 'unparsed'; client = $Client; raw = $m.Groups[1].Value })
            }
        }
    }
    $script:CRFlowEvents[$Client]
}

function Get-CRFlowEvents([int]$Client, [string]$Kind = '') {
    $all = Update-CRFlowEvents $Client
    if ($Kind) { @($all | Where-Object k -eq $Kind) } else { @($all) }
}

function Wait-CRFlowEvent {
    param([Parameter(Mandatory)][int]$Client, [string]$Kind = '', [scriptblock]$Where = { $true },
          [int]$TimeoutSeconds = 60, [string]$Description = '')
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    do {
        $hit = Get-CRFlowEvents $Client $Kind | Where-Object $Where | Select-Object -First 1
        if ($hit) { return $hit }
        Start-Sleep -Milliseconds 500
    } while ((Get-Date) -lt $deadline)
    throw "client ${Client}: no '$Kind' event $Description within ${TimeoutSeconds}s"
}

# Shorthand for the common case: an objective/result/subtitle op on one client.
function Wait-CRFlowOp {
    param([Parameter(Mandatory)][int]$Client, [Parameter(Mandatory)][string]$Op, $Arg = $null, [int]$TimeoutSeconds = 60)
    Wait-CRFlowEvent -Client $Client -Kind op -TimeoutSeconds $TimeoutSeconds -Description "$Op $Arg" -Where {
        $_.op -eq $Op -and ($null -eq $Arg -or (@($_.args) -contains $Arg))
    }.GetNewClosure()
}

# ------------------------------------------------------------ run report --

function Start-CRFlowRun {
    param([Parameter(Mandatory)][string]$RunDir, [string]$Mission = '', [string]$Scenario = '')
    $shots = New-Item -ItemType Directory -Force -Path (Join-Path $RunDir 'flow-shots')
    $script:CRFlowRun = [ordered]@{
        runDir = $RunDir; shots = $shots.FullName; mission = $Mission; scenario = $Scenario
        started = (Get-Date).ToString('o'); clock = [Diagnostics.Stopwatch]::StartNew()
        steps = New-Object System.Collections.ArrayList
        checks = New-Object System.Collections.ArrayList
        stepLog = Join-Path $RunDir 'flow-steps.jsonl'
    }
}

function Save-CRFlowShots([string]$Name) {
    $run = $script:CRFlowRun
    $n = $run.steps.Count + 1
    $paths = @()
    foreach ($c in (Get-CRFlowSession).clients) {
        $p = Join-Path $run.shots ("{0:D2}-{1}-c{2}.png" -f $n, ($Name -replace '[^\w.-]', '_'), $c.index)
        try { Save-BZRClientCapture $c.pid $p; $paths += $p } catch { }
    }
    $paths
}

function Invoke-CRFlowStep {
    param([Parameter(Mandatory)][string]$Name, [Parameter(Mandatory)][scriptblock]$Body, [switch]$Soft)
    $run = $script:CRFlowRun
    $t0 = $run.clock.Elapsed.TotalSeconds
    $status, $detail, $result = 'ok', $null, $null
    try { $result = & $Body }
    catch { $status = if ($Soft) { 'warn' } else { 'fail' }; $detail = $_.Exception.Message }
    $rec = [ordered]@{
        step = $Name; status = $status; startS = [math]::Round($t0, 1)
        seconds = [math]::Round($run.clock.Elapsed.TotalSeconds - $t0, 1)
        result = $result; detail = $detail; shots = @(Save-CRFlowShots $Name)
    }
    [void]$run.steps.Add($rec)
    ($rec | ConvertTo-Json -Compress -Depth 8) | Add-Content -LiteralPath $run.stepLog
    $color = @{ ok = 'Green'; warn = 'Yellow'; fail = 'Red' }[$status]
    Write-Host ("[flow] {0,7:N1}s {1,-4} {2}{3}" -f $run.clock.Elapsed.TotalSeconds, $status, $Name, $(if ($detail) { " -- $detail" } else { '' })) -ForegroundColor $color
    if ($status -eq 'fail') { throw "Step '$Name' failed: $detail" }
    $result
}

function Add-CRFlowCheck {
    param([Parameter(Mandatory)][string]$Name, [Parameter(Mandatory)][bool]$Pass, $Detail = $null, [switch]$WarnOnly)
    $status = if ($Pass) { 'pass' } elseif ($WarnOnly) { 'warn' } else { 'fail' }
    [void]$script:CRFlowRun.checks.Add([ordered]@{ check = $Name; status = $status; detail = $Detail })
    $color = @{ pass = 'Green'; warn = 'Yellow'; fail = 'Red' }[$status]
    Write-Host ("[check] {0,-4} {1}" -f $status, $Name) -ForegroundColor $color
}

# ---------------------------------------------------------------- parity --

function Get-CRFlowOpSignature($Event) {
    $opArgs = @($Event.args)
    if ($Event.op -in 'SucceedMission', 'FailMission') {
        # Arg 1 is each peer's own clock; only the debrief file must match.
        $opArgs = @($opArgs | Select-Object -Skip 1)
    }
    $parts = foreach ($a in $opArgs) {
        if ($a -is [psobject] -and $a.PSObject.Properties['valid']) { '@' + $a.odf + '/' + $a.label }
        else { ConvertTo-Json $a -Compress -Depth 4 }
    }
    $Event.op + '(' + ($parts -join ',') + ')'
}

function Test-CRFlowPresentationParity([int]$HostClient = 0, [int[]]$Guests = @(1)) {
    $hostOps = @(Get-CRFlowEvents $HostClient op | Where-Object { $_.op -in $script:CRFlowReplicatedOps } | ForEach-Object { Get-CRFlowOpSignature $_ })
    foreach ($g in $Guests) {
        $guestOps = @(Get-CRFlowEvents $g op | Where-Object { $_.op -in $script:CRFlowReplicatedOps } | ForEach-Object { Get-CRFlowOpSignature $_ })
        $first = -1
        $deadHandles = New-Object System.Collections.ArrayList
        for ($i = 0; $i -lt [math]::Min($hostOps.Count, $guestOps.Count); $i++) {
            if ($hostOps[$i] -eq $guestOps[$i]) { continue }
            # The host removes the object as it queues the event, so the handle
            # is dead before it is sent and arrives as nil. Not a stream fault:
            # the owner's deletion replicates on its own (world parity checks it).
            if ($guestOps[$i] -eq 'RemoveObject()' -and $hostOps[$i] -like 'RemoveObject(@*)') { [void]$deadHandles.Add($hostOps[$i]); continue }
            $first = $i; break
        }
        if ($deadHandles.Count) {
            Add-CRFlowCheck "c$g RemoveObject events carried dead handles ($($deadHandles.Count))" $false @($deadHandles | Select-Object -First 8) -WarnOnly
        }
        $detail = [ordered]@{ hostOps = $hostOps.Count; guestOps = $guestOps.Count }
        if ($first -ge 0) {
            $detail.firstMismatch = $first
            $detail.host = @($hostOps[$first..([math]::Min($first + 4, $hostOps.Count - 1))])
            $detail.guest = @($guestOps[$first..([math]::Min($first + 4, $guestOps.Count - 1))])
        } elseif ($guestOps.Count -lt $hostOps.Count) {
            $detail.guestMissing = @($hostOps[$guestOps.Count..($hostOps.Count - 1)] | Select-Object -First 8)
        } elseif ($guestOps.Count -gt $hostOps.Count) {
            $detail.guestExtra = @($guestOps[$hostOps.Count..($guestOps.Count - 1)] | Select-Object -First 8)
        }
        Add-CRFlowCheck "presentation stream host=c$HostClient guest=c$g ($($hostOps.Count) ops)" `
            ($first -lt 0 -and $hostOps.Count -eq $guestOps.Count -and $hostOps.Count -gt 0) $detail
    }
}

function Test-CRFlowResultParity([string]$Expect, [string]$Debrief = '', [int[]]$Clients = @(0, 1)) {
    foreach ($i in $Clients) {
        $r = @(Get-CRFlowEvents $i op | Where-Object { $_.op -in 'SucceedMission', 'FailMission' })
        $detail = @($r | ForEach-Object { Get-CRFlowOpSignature $_ })
        $pass = $r.Count -ge 1 -and $r[0].op -eq $Expect -and (-not $Debrief -or @($r[0].args) -contains $Debrief)
        Add-CRFlowCheck "c$i result $Expect $Debrief" $pass $detail
    }
}

function Test-CRFlowTransport([int]$HostClient = 0, [int[]]$Guests = @(1)) {
    $sent = Invoke-CRFlow $HostClient 'return L().events' -TimeoutSeconds 10
    foreach ($g in $Guests) {
        $got = Invoke-CRFlow $g 'return L().receivedEvent' -TimeoutSeconds 10
        Add-CRFlowCheck "event stream delivered to c$g" ($null -ne $sent -and $sent -eq $got) @{ hostEvents = $sent; guestReceived = $got }
    }
}

# Handles stored in M on both peers (Start() resolves BZN labels on each):
# alive/odf must agree; positions are compared loosely and only warn.
function Test-CRFlowWorldParity([int]$HostClient = 0, [int[]]$Guests = @(1), [double]$Tolerance = 30) {
    $lua = 'local s = snap(); return s.M and s.M.handles'
    $h = Invoke-CRFlow $HostClient $lua
    if (-not $h) { Add-CRFlowCheck "world state c$HostClient readable" $false 'host returned no M handles'; return }
    foreach ($g in $Guests) {
        $o = Invoke-CRFlow $g $lua
        if (-not $o) { Add-CRFlowCheck "world state c$g readable" $false 'guest returned no M handles'; continue }
        $diffs, $moved, $shared = @(), @(), 0
        foreach ($p in $h.PSObject.Properties) {
            $gp = $o.PSObject.Properties[$p.Name]
            if (-not $gp) { continue }
            $a, $b = $p.Value, $gp.Value
            if (-not $a.valid -and -not $b.valid) { continue }
            $shared++
            if ([bool]$a.alive -ne [bool]$b.alive -or $a.odf -ne $b.odf) {
                $diffs += "$($p.Name): host alive=$($a.alive) $($a.odf) / guest alive=$($b.alive) $($b.odf)"
            } elseif ($a.pos -and $b.pos) {
                $d = [math]::Sqrt([math]::Pow($a.pos[0] - $b.pos[0], 2) + [math]::Pow($a.pos[2] - $b.pos[2], 2))
                if ($d -gt $Tolerance) { $moved += "$($p.Name) $($a.odf): $([math]::Round($d))m" }
            }
        }
        Add-CRFlowCheck "world state c$HostClient vs c$g ($shared shared handles)" ($diffs.Count -eq 0) $diffs
        if ($moved.Count) { Add-CRFlowCheck "positions within ${Tolerance}m c$HostClient vs c$g" $false $moved -WarnOnly }
    }
}

function Test-CRFlowLogErrors([int[]]$Clients = @(0, 1)) {
    foreach ($i in $Clients) {
        $probeErrors = @(Get-CRFlowEvents $i error | ForEach-Object { "$($_.where) $($_.msg)" })
        $log = Get-CRFlowLogPath (Get-CRFlowClient $i)
        $hits = @()
        if ($log) {
            $hits = @(Select-String -LiteralPath $log -Pattern 'stack traceback|attempt to (index|call|compare|perform|concatenate)|Lua error|LUA ERROR' |
                Select-Object -Last 10 | ForEach-Object { $_.Line.Trim() })
        }
        Add-CRFlowCheck "c$i no Lua errors" ($hits.Count -eq 0) $hits
        Add-CRFlowCheck "c$i probe healthy" ($probeErrors.Count -eq 0) $probeErrors -WarnOnly
    }
}

function Complete-CRFlowRun {
    param([string]$Outcome = '')
    $run = $script:CRFlowRun
    $failedSteps = @($run.steps | Where-Object status -eq 'fail').Count
    $failedChecks = @($run.checks | Where-Object status -eq 'fail').Count
    $pass = $failedSteps -eq 0 -and $failedChecks -eq 0 -and $run.steps.Count -gt 0
    $summary = [ordered]@{
        mission = $run.mission; scenario = $run.scenario; started = $run.started
        seconds = [math]::Round($run.clock.Elapsed.TotalSeconds, 1)
        verdict = if ($pass) { 'PASS' } else { 'FAIL' }; outcome = $Outcome
        steps = $run.steps; checks = $run.checks
    }
    $summary | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath (Join-Path $run.runDir 'flow-summary.json')

    $md = New-Object System.Text.StringBuilder
    [void]$md.AppendLine("# Co-op flow: $($run.mission) / $($run.scenario) - $($summary.verdict)")
    [void]$md.AppendLine('')
    if ($Outcome) { [void]$md.AppendLine("$Outcome`n") }
    [void]$md.AppendLine('| # | Step | Status | At (s) | Took (s) | Detail |')
    [void]$md.AppendLine('|---|---|---|---|---|---|')
    $n = 0
    foreach ($s in $run.steps) {
        $n++
        $d = if ($s.detail) { $s.detail } elseif ($null -ne $s.result) { ConvertTo-Json $s.result -Compress -Depth 4 } else { '' }
        if ($d.Length -gt 160) { $d = $d.Substring(0, 157) + '...' }
        [void]$md.AppendLine("| $n | $($s.step) | $($s.status) | $($s.startS) | $($s.seconds) | $($d -replace '\|', '/') |")
    }
    [void]$md.AppendLine("`n| Check | Status | Detail |`n|---|---|---|")
    foreach ($c in $run.checks) {
        $d = if ($null -ne $c.detail) { ConvertTo-Json $c.detail -Compress -Depth 4 } else { '' }
        if ($d.Length -gt 240) { $d = $d.Substring(0, 237) + '...' }
        [void]$md.AppendLine("| $($c.check) | $($c.status) | $($d -replace '\|', '/') |")
    }
    [void]$md.AppendLine("`nScreenshots: ``flow-shots\``; events: each client's ``[CRFLOW]`` lines in ``client<N>\logs\BZLogger.txt``.")
    Set-Content -LiteralPath (Join-Path $run.runDir 'flow-summary.md') -Value $md.ToString()
    Write-Host ("[flow] {0}: {1} steps, {2} checks ({3} failed) -> {4}" -f $summary.verdict, $run.steps.Count, $run.checks.Count, $failedChecks, (Join-Path $run.runDir 'flow-summary.md'))
    $summary
}
