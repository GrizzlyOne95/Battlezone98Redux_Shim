# Which team does each client's radar treat as "mine"? Reads the radar colour
# globals (FUN_004db800: own team DAT_00917b00, ally gate DAT_00917a70, user
# object DAT_00917afc) with a non-invasive cdb attach on every client, and the
# Lua view of the local player's team. Observes only. Each read pauses the
# client for about a second.
param([int]$HostClient = 0, [int]$PlaySeconds = 20)
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$cdb = 'C:\Users\iestu\AppData\Local\Python\bin\cdb.cmd'

function Read-RadarGlobals([int]$c) {
    $client = @((Get-CRFlowSession).clients) | Where-Object { $_.index -eq $c } | Select-Object -First 1
    if (-not $client.pid) { throw "no pid for c$c" }
    $cmds = 'dd 0x917b00 L1; dd 0x917a70 L1; dd 0x917afc L1; dd poi(0x917afc)+0x174 L1; dd 0x9175b0 L1; dd 0x917578 L1; q'
    $out = & $cmd /c "`"$cdb`" -pv -p $($client.pid) -c `"$cmds`"" 2>&1 | Out-String
    $vals = @([regex]::Matches($out, '(?m)^([0-9a-f]{8})\s+([0-9a-f]{8})\s*$') | ForEach-Object { $_.Groups[2].Value })
    [pscustomobject]@{ client = $c; pid = $client.pid; ownTeam = $vals[0]; allyGate = $vals[1]; userObj = $vals[2]; userObjTeam = $vals[3]; ownColor = $vals[4]; allyColor = $vals[5]; raw = if ($vals.Count -lt 6) { $out } else { $null } }
}
$cmd = Join-Path $env:SystemRoot 'System32\cmd.exe'

Invoke-CRFlowStep 'probes attached, mission running' {
    foreach ($c in $C) {
        $a = Wait-CRFlowEvent $c attach -TimeoutSeconds 120
        if (-not $a.bzfile) { throw "bzfile missing on c$c" }
    }
    Wait-CRFlow $H 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 120 | Out-Null
    foreach ($c in $guests) { Wait-CRFlow $c 'return role().ready and M.coopMissionStarted' -TimeoutSeconds 90 | Out-Null }
    Start-Sleep -Seconds $PlaySeconds
    'ready'
}

Invoke-CRFlowStep 'Lua: local player team and handle' {
    foreach ($c in $C) {
        $r = Invoke-CRFlow $c 'local me = GetPlayerHandle(); return { team = GetTeamNum(me), odf = GetOdf(me), id = tostring(me) }'
        Write-Host ("c{0} lua: team={1} odf={2} id={3}" -f $c, $r.team, $r.odf, $r.id)
    }
    'read'
}

Invoke-CRFlowStep 'cdb: radar own-team globals' {
    foreach ($c in $C) {
        $g = Read-RadarGlobals $c
        Write-Host ("c{0} pid={1} ownTeam(917b00)={2} allyGate(917a70)={3} userObj(917afc)={4} userObjTeam={5} ownColor={6} allyColor={7}" -f $g.client, $g.pid, $g.ownTeam, $g.allyGate, $g.userObj, $g.userObjTeam, $g.ownColor, $g.allyColor)
        if ($g.raw) { Write-Host $g.raw }
    }
    'read'
}

# Per-object radar colour cache (FUN_004db800 writes +0x16C/+0x170; the radar
# contact getter FUN_00492ce0 reads one of them). Object = 0x0260db20 +
# (handle >> 20) * 0x400 (FUN_004da060).
Invoke-CRFlowStep 'cdb: building colour cache on every client' {
    foreach ($c in $C) {
        $list = Invoke-CRFlow $c 'local t = {} for h in AllObjects() do if IsBuilding(h) or IsCraft(h) then t[#t+1] = { id = tostring(h), team = GetTeamNum(h), odf = GetOdf(h), bld = IsBuilding(h) } end end return t'
        $client = @((Get-CRFlowSession).clients) | Where-Object { $_.index -eq $c } | Select-Object -First 1
        $rows = @($list) | Select-Object -First 24
        $cmds = 'dd 0x917b00 L1; '
        foreach ($r in $rows) {
            $h = [Convert]::ToUInt32(($r.id -replace '^.*?([0-9A-Fa-f]{8})$', '$1'), 16)
            $addr = 0x0260db20 + ([uint32]($h -shr 20)) * 0x400
            $cmds += ('dd 0x{0:x}+0x16c L3; dd dwo(0x{0:x}+0xf4)+0x14 L1; ' -f $addr)
        }
        $cmds += 'q'
        $out = & $cmd /c "`"$cdb`" -pv -p $($client.pid) -c `"$cmds`"" 2>&1 | Out-String
        $lines = @([regex]::Matches($out, '(?m)^(?:[0-9a-f]{8}`)?[0-9a-f]{8}\s+([0-9a-f]{8}(?:\s+[0-9a-f]{8})*)\s*$') | ForEach-Object { $_.Groups[1].Value })
        if ($lines.Count -lt 2) { Write-Host $out }
        Write-Host ("c{0} ownTeam={1}" -f $c, $lines[0])
        for ($i = 0; $i -lt $rows.Count; $i++) {
            Write-Host ("c{0} {1,-10} team={2} bld={3} c16c/c170/team174={4} defflags={5}" -f $c, $rows[$i].odf, $rows[$i].team, $rows[$i].bld, $lines[1 + 2 * $i], $lines[2 + 2 * $i])
        }
    }
    'read'
}
