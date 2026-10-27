# Stock bug pack (mpbugs map, Run-BZRMpBugs.ps1 -Case Weapons): one Daywrecker
# and one Splinter, and what each peer makes of them.
#
# Reported: a single Daywrecker detonates twice (double damage, double crater)
# for every player except the launcher; Splinters misbehave in multiplayer.
# The source reading is contested (the 2026-09-04 correction atop
# Docs\MULTIPLAYER_BUG_SOURCE_INVESTIGATION.md, then
# DAYWRECKER_RECEIVER_LIFETIME_INVESTIGATION_20261007.md and
# MPAUTH_SPLINTER_STATIC_ANALYSIS.md), so this case measures instead of assuming:
#   - explosive lifetimes per peer: a consumed Daywrecker rebuilt from late
#     network state shows as a second lifetime on a receiver;
#   - witness tanks around each impact, owned by different peers: only an
#     object's owner applies damage to it, so a peer that sees a doubled blast
#     shows doubled damage on its own witnesses;
#   - terrain heights and normals on a grid around each impact, per peer;
#   - MPAUTH_* trace lines per client (Run-BZRMpBugs turns the trace on).
# The Splinter's deployed building and payload are rebuilt on each peer by
# design, so one Splinter lifetime per peer is expected; its deploy point and
# the damage per owner are recorded as observations.
#
# -Expect Stock records a duplicate as a warning (what stock does is the
# question); -Expect Fixed fails on one.
param([ValidateSet('host','guest')][string]$Launcher = 'host',
      [ValidateSet('both','daywrecker','splinter')][string]$Weapon = 'both',
      [ValidateSet('Stock','Fixed')][string]$Expect = 'Stock',
      [int]$HostClient = 0,
      # Daywreckers the launcher's Armory lobs back to back (1 to 5; the team holds 100 scrap).
      [ValidateRange(1, 5)][int]$Burst = 1,
      # Witness rings (metres from the aim point); the Daywrecker blast reaches 200 m.
      # A burst defaults to wider rings so the witnesses survive several blasts.
      [int[]]$Distances = @(80, 120),
      # Seconds to wait after the launcher's explosive is gone, for late
      # reconstruction on the receivers.
      [int]$SettleSeconds = 20)

if ($Burst -gt 1 -and -not $PSBoundParameters.ContainsKey('Distances')) { $Distances = @(150, 180) }
$H = $HostClient
$C = @(Get-CRFlowClientIndices)
$guests = @($C | Where-Object { $_ -ne $H })
$L = if ($Launcher -eq 'host') { $H } else { $guests[0] }
$receivers = @($C | Where-Object { $_ -ne $L })
$script:CRFlowSkipParity = $true # Not a presentation-stream case.
$samplePath = Join-Path $script:CRFlowRun.runDir 'weapons-samples.jsonl'
# Aim points ~440 m and more from the human spawns (z 2560), 400 m apart.
$sites = [ordered]@{ daywrecker = @{ x = 2560; z = 3000 }; splinter = @{ x = 2960; z = 3000 } }
$weapons = if ($Weapon -eq 'both') { @('daywrecker', 'splinter') } else { @($Weapon) }

$shimLogs, $shimMarks = @{}, @{}
foreach ($i in $C) {
    $shimLogs[$i] = Join-Path (Get-CRFlowClient $i).dir 'logs\openshim.log'
    $shimMarks[$i] = if (Test-Path -LiteralPath $shimLogs[$i]) { (Get-Item -LiteralPath $shimLogs[$i]).Length } else { 0 }
}
# MPAUTH_* trace lines since the mark, counted by tag. Leads, not proof
# (DAYWRECKER_RECEIVER_LIFETIME_INVESTIGATION_20261007.md lists their limits).
function Get-MpauthCounts([int]$Client) {
    $counts = [ordered]@{}
    if (-not (Test-Path -LiteralPath $shimLogs[$Client])) { return $counts }
    $text = (Read-CRFlowShared $shimLogs[$Client] $shimMarks[$Client]).Text
    foreach ($m in [regex]::Matches($text, 'MPAUTH_[A-Z_]+')) { $counts[$m.Value] = 1 + [int]$counts[$m.Value] }
    $counts
}
function Get-Site([int]$Client, [string]$Name, [string]$Phase) {
    $site = $sites[$Name]
    $s = Invoke-CRFlow $Client "return BugSite($($site.x), $($site.z))"
    $record = [ordered]@{ at = (Get-Date).ToUniversalTime().ToString('o'); client = $Client; site = $Name; phase = $Phase; state = $s }
    ($record | ConvertTo-Json -Compress -Depth 8) | Add-Content -LiteralPath $samplePath
    $s
}
function Get-Lifetimes($s, [string]$Kind) { @($s.lifetimes | Where-Object { $_ -and $_.kind -eq $Kind }) }
function Get-Grid([string]$Text) { @($Text -split ' ' | Where-Object { $_ } | ForEach-Object { [double]$_ }) }
function Get-MaxAbsDiff($a, $b) {
    $m = 0.0
    for ($k = 0; $k -lt [math]::Min($a.Count, $b.Count); $k++) { $m = [math]::Max($m, [math]::Abs($a[$k] - $b[$k])) }
    [math]::Round($m, 4)
}
function Wait-Site([int]$Client, [string]$Name, [int]$TimeoutSeconds, [scriptblock]$Until) {
    $clock = [Diagnostics.Stopwatch]::StartNew()
    do {
        $s = Get-Site $Client $Name 'poll'
        if (& $Until $s) { return $s }
        Start-Sleep -Seconds 1
    } while ($clock.Elapsed.TotalSeconds -lt $TimeoutSeconds)
    $null
}
function Add-DuplicateCheck([string]$Name, [bool]$Pass, $Detail) {
    if ($Expect -eq 'Fixed') { Add-CRFlowCheck $Name $Pass $Detail } else { Add-CRFlowCheck $Name $Pass $Detail -WarnOnly }
}

# Witness angles per client rank, so owners alternate around each ring.
$angleSets = @(@(0, 180), @(90, 270), @(45, 225), @(135, 315))
$ranked = @($H) + $guests
$expectedWitnesses = $ranked.Count * $Distances.Count * 2
Invoke-CRFlowStep "every peer places its witnesses ($($Distances -join '/') m)" {
    $distanceList = '{' + ($Distances -join ',') + '}'
    for ($r = 0; $r -lt $ranked.Count; $r++) {
        $angles = '{' + ($angleSets[$r % 4] -join ',') + '}'
        foreach ($w in $weapons) {
            $site = $sites[$w]
            Invoke-CRFlow $ranked[$r] "return BugPlaceWitnesses($($site.x), $($site.z), $distanceList, $angles)" | Out-Null
        }
    }
    foreach ($i in $C) {
        foreach ($w in $weapons) {
            $s = Wait-Site $i $w 20 { param($s) @($s.witnesses | Where-Object { $_ }).Count -ge $expectedWitnesses }
            if (-not $s) { throw "c$i never sees all $expectedWitnesses witnesses at the $w site" }
        }
    }
    @{ perSite = $expectedWitnesses; owners = $ranked }
}

foreach ($w in $weapons) {
    $before = Invoke-CRFlowStep "${w}: every peer before" {
        $out = @{}
        foreach ($i in $C) { $out["c$i"] = Get-Site $i $w 'before' }
        $out
    }

    Invoke-CRFlowStep "${w}: c$L launches" {
        $site = $sites[$w]
        if ($w -eq 'daywrecker') {
            Invoke-CRFlow $L "return BugLaunchDaywrecker($($site.x), $($site.z), $Burst)" | Out-Null
            # The Armory deploys, builds, lobs, and each bomb detonates and is removed.
            $done = Wait-Site $L $w (120 + 30 * ($Burst - 1)) { param($s) @(Get-Lifetimes $s 'daywrecker' | Where-Object { $_.gone }).Count -ge $Burst }
            if (-not $done) { throw "$Burst Daywrecker(s) did not all detonate on the launcher c$L in time (launch $((Get-Site $L $w 'poll').launch | ConvertTo-Json -Compress))" }
        } else {
            $fire = Invoke-CRFlow $L "return BugFireSplinter($($site.x), $($site.z))"
            if ($fire.weapon -notmatch 'gsplint') { throw "shooter has no Splinter in slot 3 ($($fire.weapon))" }
            $fired = Wait-Site $L $w 40 { param($s) $s.fire.firedAt -or $s.fire.timedOut }
            if (-not $fired -or -not $fired.fire.firedAt) { throw "the shooter never fired its Splinter ($($fired.fire | ConvertTo-Json -Compress))" }
            $done = Wait-Site $L $w 40 { param($s) @(Get-Lifetimes $s 'splinter' | Where-Object { $_.gone }).Count }
            if (-not $done) { throw "no deployed Splinter finished on the launcher c$L within 40 s of firing" }
        }
        Start-Sleep -Seconds $SettleSeconds
        @{ launcher = $L; settle = $SettleSeconds }
    }

    $after = Invoke-CRFlowStep "${w}: every peer after" {
        $out = @{}
        foreach ($i in $C) { $out["c$i"] = Get-Site $i $w 'after' }
        $out
    }

    $launcherLife = @(Get-Lifetimes $after["c$L"] $w)
    $impact = $launcherLife | Select-Object -First 1
    $hostAfterHeights = Get-Grid $after["c$H"].heights
    $hostBeforeHeights = Get-Grid $before["c$H"].heights
    $damage = @()
    foreach ($i in $C) {
        $pre, $post = $before["c$i"], $after["c$i"]
        $lives = @(Get-Lifetimes $post $w)
        $hb, $ha = (Get-Grid $pre.heights), (Get-Grid $post.heights)
        $nb, $na = (Get-Grid $pre.normals), (Get-Grid $post.normals)
        # This peer's own witnesses: it alone applied their damage.
        $own = @()
        foreach ($wb in @($pre.witnesses | Where-Object { $_ -and $_.mine })) {
            $wa = @($post.witnesses | Where-Object { $_ -and $_.id -eq $wb.id }) | Select-Object -First 1
            $d = if ($impact) { [math]::Round([math]::Sqrt([math]::Pow($wb.x - $impact.lastX, 2) + [math]::Pow($wb.z - $impact.lastZ, 2)), 1) } else { $null }
            $loss = if ($wa) { $wb.health - $wa.health } else { $wb.health }
            $own += [ordered]@{ distance = $d; before = $wb.health; loss = $loss; killed = -not $wa }
        }
        $damage += [ordered]@{ owner = $i; witnesses = $own }
        $detail = [ordered]@{
            lifetimes = $lives
            terrainHeightChange = (Get-MaxAbsDiff $hb $ha); terrainNormalChange = (Get-MaxAbsDiff $nb $na)
            heightsVsHostBefore = (Get-MaxAbsDiff $hostBeforeHeights $hb); heightsVsHostAfter = (Get-MaxAbsDiff $hostAfterHeights $ha)
            ownWitnesses = $own; mpauth = (Get-MpauthCounts $i) }
        Add-CRFlowCheck "${w} reached c$i ($($lives.Count) lifetime(s))" ([bool]$lives.Count) $detail
        $launched = if ($w -eq 'daywrecker') { $Burst } else { 1 }
        if ($i -ne $L) {
            Add-DuplicateCheck "no duplicate ${w} lifetime on receiver c$i ($($lives.Count) for $launched launched)" ($lives.Count -le $launched) $detail
        }
        if ($w -eq 'daywrecker' -and $Burst -gt 1) {
            # Each peer should see exactly one detonation per Daywrecker launched.
            $blasts = @($lives | Where-Object { $_.gone }).Count
            Add-DuplicateCheck "c$i saw $blasts Daywrecker detonation(s) for $Burst launched" ($blasts -eq $Burst) ([ordered]@{
                detonations = @($lives | ForEach-Object { $_.gone }); launch = $post.launch })
        }
        if ($w -eq 'splinter' -and $impact -and $lives.Count) {
            $spread = [math]::Round([math]::Sqrt([math]::Pow($lives[0].lastX - $impact.lastX, 2) + [math]::Pow($lives[0].lastZ - $impact.lastZ, 2)), 1)
            Add-CRFlowCheck "observed on c${i}: Splinter deployed $spread m from the launcher's" $true @{ spread = $spread; here = $lives[0]; launcher = $impact }
        }
    }
    # A doubled blast on one peer shows as about twice the damage on its own
    # witnesses at the same distance. Falloff is assumed linear to 200 m
    # (xbmbxpl damageRadius), so loss / (200 - d) is compared across owners.
    if ($w -eq 'daywrecker' -and $impact) {
        $norm = @{}
        foreach ($g in $damage) {
            $vals = @($g.witnesses | Where-Object { -not $_.killed -and $_.distance -lt 195 } | ForEach-Object { $_.loss / (200 - $_.distance) })
            $norm[$g.owner] = if ($vals.Count) { ($vals | Measure-Object -Average).Average } else { $null }
        }
        foreach ($r in $receivers) {
            $ratio = if ($norm[$L] -and $norm[$r]) { [math]::Round($norm[$r] / $norm[$L], 2) } else { $null }
            Add-DuplicateCheck "no doubled Daywrecker damage on receiver c$r's witnesses (x$ratio of launcher c$L)" ($null -ne $ratio -and $ratio -lt 1.5) ([ordered]@{ ratio = $ratio; damage = $damage })
        }
    }
}
