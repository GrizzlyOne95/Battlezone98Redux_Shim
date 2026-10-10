# Offline end-to-end check of the harness <-> probe channel, no game needed:
# Install-CRFlowProbe on a copy of a real mission script (stub must compile),
# then two FakeClient.lua processes run the real probe while the real
# Invoke-CRFlow / Wait-CRFlow / event reader drive them through files.
# Run: powershell -ExecutionPolicy Bypass -File reverse_engineering\coopflow\Test-CRFlowChannel.ps1
param([string]$MissionScript = (Join-Path $env:USERPROFILE 'Documents\GIT\CR-release\Scripts\misn03.lua'),
      [string]$Lua = 'lua', [string]$Luac = 'luac')

$ErrorActionPreference = 'Stop'
. (Join-Path (Split-Path $PSScriptRoot) 'BZRCoopMission.ps1')
$root = Join-Path ([IO.Path]::GetTempPath()) ("crflow-channel-" + [Guid]::NewGuid().ToString('N').Substring(0, 8))
$script:CRFlowCoopRoot = $root
$checks = 0
function Check([bool]$ok, [string]$msg) { if (-not $ok) { throw "FAIL: $msg" }; $script:checks++ }

$procs = @()
try {
    $clients = @()
    $starts = @()
    foreach ($i in 0, 1) {
        $inst = Join-Path $root ("instances\Instance{0}\Battlezone 98 Redux" -f $i)
        $mod = New-Item -ItemType Directory -Force -Path (Join-Path $inst "mods\$($script:CRFlowModId)")
        Copy-Item -LiteralPath $MissionScript -Destination (Join-Path $mod 'misn03.lua')
        $r = Install-CRFlowProbe -InstanceDir $inst -Mission misn03
        Check (Test-Path $r.Probe) 'probe copied'
        # Re-installing replaces the stub instead of stacking a second one.
        $null = Install-CRFlowProbe -InstanceDir $inst -Mission misn03
        $text = Get-Content -LiteralPath $r.Script -Raw
        Check (([regex]::Matches($text, [regex]::Escape($script:CRFlowMarker))).Count -eq 1) 'one stub after reinstall'
        & $Luac -p $r.Script
        Check ($LASTEXITCODE -eq 0) 'mission script with stub compiles'
        $stub = $text.Substring($text.IndexOf($script:CRFlowMarker))
        [IO.File]::WriteAllText((Join-Path $inst 'stub.lua'), $stub)
        $clients += [ordered]@{ index = $i; pid = 0; dir = $inst }
        $starts += , @((Join-Path $PSScriptRoot 'FakeClient.lua'), "`"$inst`"", '25', $(if ($i -eq 0) { '1' } else { '0' }))
    }
    # Mark the (not yet existing) logs first, as the runner does before launch.
    @{ clients = $clients; runDir = $root } | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $root 'session.json')
    Set-CRFlowLogMark @(0, 1)
    foreach ($i in 0, 1) {
        $p = Start-Process -FilePath $Lua -ArgumentList $starts[$i] -PassThru -WindowStyle Hidden
        $procs += $p
        $clients[$i].pid = $p.Id
    }
    @{ clients = $clients; runDir = $root } | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $root 'session.json')

    $a = Wait-CRFlowEvent 0 attach -TimeoutSeconds 10
    Check ($a.mission -eq 'misn03' -and $a.bzfile) 'attach event over the log'
    $r = Invoke-CRFlow 0 'return 1 + 1'
    Check ($r -eq 2) "scalar result ($r)"
    $r = Invoke-CRFlow 1 'return role()'
    Check ($r.authority -eq $false -and $r.team -eq 2) 'guest role'
    $r = Invoke-CRFlow 0 'return { 7 }'
    Check (@($r).Count -eq 1 -and @($r)[0] -eq 7) 'one-element array survives'
    $r = Invoke-CRFlow 0 'return nil'
    Check ($null -eq $r) 'nil result'
    $r = Invoke-CRFlow 0 'error("nope")' -AllowError
    Check (-not $r.Ok -and $r.Value.error -match 'nope') 'error result'
    $threw = $false; try { Invoke-CRFlow 0 'error("nope")' | Out-Null } catch { $threw = $true }
    Check $threw 'error throws without -AllowError'
    $v = Wait-CRFlow 0 'return M.start_done' -TimeoutSeconds 10
    Check ($v -eq $true) 'Wait-CRFlow sees a flag become true'
    $ev = Wait-CRFlowOp 0 AddObjective 'misn0301.otf' -TimeoutSeconds 10
    Check ($ev.op -eq 'AddObjective') 'op event'
    $f = Wait-CRFlowEvent 0 flag -Where { $_.key -eq 'start_done' -and $_.to -eq $true } -TimeoutSeconds 10
    Check ($null -ne $f) 'flag event'
    $r = Invoke-CRFlow 1 'return tp(M.launch, 20).pos[1]'
    Check ($r -eq 520) "tp on guest ($r)"
    $snap = Wait-CRFlowEvent 1 snap -TimeoutSeconds 10
    Check ($snap.mission -eq 'misn03') 'snapshot event'
    Write-Host "Test-CRFlowChannel: $checks checks passed"
} finally {
    foreach ($p in $procs) { if (-not $p.HasExited) { Stop-Process -Id $p.Id -Force } }
    Start-Sleep -Milliseconds 300
    Remove-Item -LiteralPath $root -Recurse -Force -ErrorAction SilentlyContinue
}
