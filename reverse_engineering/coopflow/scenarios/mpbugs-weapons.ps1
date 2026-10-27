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
# design, so one Splinter lifetime per peer is expected. Reported: each guest
# gets its own copy ("escalating devastation") and a deployed Splinter cannot be
# destroyed. So per peer it records the lifetimes (first, gone, duration), the
# deploy point, and the loss on that peer's own witnesses on close rings
# (-SplinterDistances), plus the target tank's loss on its owner (the launcher);
# per-owner mean loss per ring is compared receiver / launcher (duplicate check
# below x1.5). -KillSplinter launcher|receiver also destroys the deployed
# Splinter on that peer (-KillMethod damage: Damage 100000 on every splintb2
# there, local only; fire: a gunner tank shoots it with networked cannon fire)
# and checks that every other peer's Splinter ended within 1 s of it (1.5 s
# with -Expect Fixed), each on its own mission clock: every peer's GetTime at
# the kill moment is recorded, since the clocks differ.
#
# Also reported (veteran player, 2026-10-27): after an Armory launches, other
# players sometimes see a Daywrecker blow up AT THE ARMORY and take its damage,
# while the launcher sees nothing. So the Armory stands at a fixed site ~525 m
# from the aim point with its own witness rings, owned per peer as above: a
# Daywrecker lifetime ending there, or damage on a peer's own witnesses there,
# is that phantom. -Target armory launches at the Armory itself instead (the
# report says two self-launched Daywreckers collide overhead for double
# damage); the aim point is then the Armory site and the burst checks apply.
#
# -Expect Stock records a duplicate as a warning (what stock does is the
# question); -Expect Fixed fails on one. -Expect Fixed also fails when a
# receiver's deployed Splinter is more than 2 m from the launcher's, or when
# a killed Splinter is still alive on a peer 1.5 s after the kill (the
# [Fixes] SplinterSync deploy and kill messages; the Stock arm of
# Run-BZRMpBugs turns SplinterSync off).
param([ValidateSet('host','guest')][string]$Launcher = 'host',
      [ValidateSet('both','daywrecker','splinter')][string]$Weapon = 'both',
      [ValidateSet('site','armory')][string]$Target = 'site',
      # Witness rings around the Armory for the phantom (with -Target site).
      [int[]]$ArmoryDistances = @(60, 100),
      [ValidateSet('Stock','Fixed')][string]$Expect = 'Stock',
      [int]$HostClient = 0,
      # Daywreckers the launcher's Armory lobs back to back (1 to 5; the team holds 100 scrap).
      [ValidateRange(1, 5)][int]$Burst = 1,
      # Witness rings (metres from the aim point); the Daywrecker blast reaches 200 m.
      # A burst defaults to wider rings so the witnesses survive several blasts.
      [int[]]$Distances = @(80, 120),
      # Witness rings for the Splinter site (its shards reach tens of metres, not 200).
      [int[]]$SplinterDistances = @(12, 25),
      # Destroy the deployed Splinter on the launcher or on the first receiver
      # right after it appears there; none leaves it to run out.
      [ValidateSet('none','launcher','receiver')][string]$KillSplinter = 'none',
      # damage: Lua Damage on the killer only (local, not networked). fire: a
      # gunner tank on the killer shoots it with networked cannon fire.
      [ValidateSet('damage','fire')][string]$KillMethod = 'damage',
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
$sites = [ordered]@{ daywrecker = @{ x = 2560; z = 3000 }; splinter = @{ x = 2960; z = 3000 }; armory = @{ x = 2160; z = 2660 } }
$weapons = if ($Weapon -eq 'both') { @('daywrecker', 'splinter') } else { @($Weapon) }
if ($Target -eq 'armory') { $sites.daywrecker = $sites.armory }
$watchArmory = $Target -eq 'site' -and $weapons -contains 'daywrecker'

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
$rings = @{ daywrecker = $Distances; splinter = $SplinterDistances }
$expectedWitnesses = @{}
foreach ($w in $weapons) { $expectedWitnesses[$w] = $ranked.Count * $rings[$w].Count * 2 }
$killer = if ($KillSplinter -eq 'launcher') { $L } else { $receivers[0] }
$script:splinterFire = $null
$script:splinterKill = $null
Invoke-CRFlowStep "every peer places its witnesses ($(($weapons | ForEach-Object { "$_ " + ($rings[$_] -join '/') }) -join ', ') m)" {
    for ($r = 0; $r -lt $ranked.Count; $r++) {
        $angles = '{' + ($angleSets[$r % 4] -join ',') + '}'
        foreach ($w in $weapons) {
            $site = $sites[$w]
            $distanceList = '{' + ($rings[$w] -join ',') + '}'
            Invoke-CRFlow $ranked[$r] "return BugPlaceWitnesses($($site.x), $($site.z), $distanceList, $angles)" | Out-Null
        }
        if ($watchArmory) {
            $site = $sites.armory
            Invoke-CRFlow $ranked[$r] "return BugPlaceWitnesses($($site.x), $($site.z), {$($ArmoryDistances -join ',')}, $angles)" | Out-Null
        }
    }
    foreach ($i in $C) {
        foreach ($w in $weapons) {
            $need = $expectedWitnesses[$w]
            $s = Wait-Site $i $w 20 { param($s) @($s.witnesses | Where-Object { $_ }).Count -ge $need }
            if (-not $s) { throw "c$i never sees all $need witnesses at the $w site" }
        }
        if ($watchArmory) {
            $n = $ranked.Count * $ArmoryDistances.Count * 2
            $s = Wait-Site $i 'armory' 20 { param($s) @($s.witnesses | Where-Object { $_ }).Count -ge $n }
            if (-not $s) { throw "c$i never sees all $n witnesses at the Armory site" }
        }
    }
    @{ perSite = $expectedWitnesses; rings = $rings; owners = $ranked; armoryRings = $(if ($watchArmory) { $ArmoryDistances } else { @() }) }
}

$armoryBefore = if ($watchArmory) {
    Invoke-CRFlowStep 'every peer at the Armory site before' {
        $out = @{}
        foreach ($i in $C) { $out["c$i"] = Get-Site $i 'armory' 'before' }
        $out
    }
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
            $atSelf = if ($Target -eq 'armory') { 'true' } else { 'false' }
            Invoke-CRFlow $L "return BugLaunchDaywrecker($($site.x), $($site.z), $Burst, $($sites.armory.x), $($sites.armory.z), $atSelf)" | Out-Null
            # The Armory deploys, builds, lobs, and each bomb detonates and is removed.
            $done = Wait-Site $L $w (120 + 30 * ($Burst - 1)) { param($s) @(Get-Lifetimes $s 'daywrecker' | Where-Object { $_.gone }).Count -ge $Burst }
            if (-not $done) { throw "$Burst Daywrecker(s) did not all detonate on the launcher c$L in time (launch $((Get-Site $L $w 'poll').launch | ConvertTo-Json -Compress))" }
        } else {
            $fire = Invoke-CRFlow $L "return BugFireSplinter($($site.x), $($site.z))"
            if ($fire.weapon -notmatch 'gsplint') { throw "shooter has no Splinter in slot 3 ($($fire.weapon))" }
            $script:splinterFire = $fire
            if ($KillSplinter -ne 'none' -and $KillMethod -eq 'fire') {
                Invoke-CRFlow $killer "return BugArmSplinterGunner($($site.x), $($site.z))" | Out-Null
            }
            $fired = Wait-Site $L $w 40 { param($s) $s.fire.firedAt -or $s.fire.timedOut }
            if (-not $fired -or -not $fired.fire.firedAt) { throw "the shooter never fired its Splinter ($($fired.fire | ConvertTo-Json -Compress))" }
            if ($KillSplinter -ne 'none') {
                # BugKillSplinter hits only a live splintb2 on that peer, so polling it
                # kills the Splinter the moment it deploys there (it lives only ~5 s).
                $clock = [Diagnostics.Stopwatch]::StartNew()
                $back = 0.0
                if ($KillMethod -eq 'fire') {
                    # Poll until the gunner's target is gone (or it gave up); the kill
                    # happened at shoot.gone, $back seconds before this poll.
                    do {
                        $st = Invoke-CRFlow $killer 'return BugShootState()'
                        if ($st.shoot.gone -or $st.shoot.timedOut) { break }
                        Start-Sleep -Milliseconds 200
                    } while ($clock.Elapsed.TotalSeconds -lt 60)
                    if (-not $st.shoot.gone) { throw "the gunner on c$killer never saw a deployed Splinter go ($($st.shoot | ConvertTo-Json -Compress))" }
                    $shot = $st.shoot.lastHealth -ne $null -and $st.shoot.lastHealth -lt $st.shoot.health
                    if (-not $shot) { throw "the Splinter on c$killer ran out before the gunner damaged it ($($st.shoot | ConvertTo-Json -Compress))" }
                    $k = [ordered]@{ time = [double]$st.shoot.gone; killed = 1; method = 'fire'
                                     health = @([ordered]@{ id = $st.shoot.target; health = $st.shoot.health; lastHealth = $st.shoot.lastHealth
                                                            seenFor = [math]::Round($st.shoot.gone - $st.shoot.seen, 2) }) }
                    $back = [double]$st.time - [double]$st.shoot.gone
                } else {
                    do {
                        $k = Invoke-CRFlow $killer 'return BugKillSplinter()'
                        if ($k.killed) { break }
                        Start-Sleep -Milliseconds 200
                    } while ($clock.Elapsed.TotalSeconds -lt 40)
                    if (-not $k.killed) { throw "no deployed Splinter appeared on c$killer to kill within 40 s of firing" }
                }
                # Each peer's own mission clock at the kill moment (a fire kill is
                # read back $back seconds after it happened).
                $peerTimes = [ordered]@{}
                foreach ($i in $C) { $peerTimes["c$i"] = if ($i -eq $killer) { [double]$k.time } else { [math]::Round([double](Invoke-CRFlow $i 'return GetTime()') - $back, 3) } }
                $script:splinterKill = [ordered]@{ killer = $killer; time = $k.time; killed = $k.killed; health = $k.health; peerTimes = $peerTimes }
                ([ordered]@{ at = (Get-Date).ToUniversalTime().ToString('o'); client = $killer; site = $w; phase = 'kill'; state = $script:splinterKill } |
                    ConvertTo-Json -Compress -Depth 8) | Add-Content -LiteralPath $samplePath
            }
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
            if ($Expect -eq 'Fixed' -and $i -ne $L) {
                Add-CRFlowCheck "Splinter on c$i deployed within 2 m of the launcher's ($spread m)" ($spread -le 2) @{ spread = $spread; here = $lives[0]; launcher = $impact }
            }
        }
    }
    if ($w -eq 'splinter') {
        $site = $sites.splinter
        $kill = $script:splinterKill
        $fireInfo = $script:splinterFire
        $targetNow = $after["c$L"].target
        $targetLoss = if ($targetNow -and $null -ne $fireInfo.targetHealth) {
            [math]::Round($(if ($targetNow.alive) { $fireInfo.targetHealth - $targetNow.health } else { $fireInfo.targetHealth }), 1) }
        $targetDetail = [ordered]@{ id = $fireInfo.target; before = $fireInfo.targetHealth; now = $targetNow; loss = $targetLoss }
        # Mean loss per ring on each owner's own witnesses (rings measured from the aim point).
        $meanByOwner = @{}
        foreach ($i in $C) {
            $pre, $post = $before["c$i"], $after["c$i"]
            $lives = @(Get-Lifetimes $post $w)
            $own = @()
            foreach ($wb in @($pre.witnesses | Where-Object { $_ -and $_.mine })) {
                $wa = @($post.witnesses | Where-Object { $_ -and $_.id -eq $wb.id }) | Select-Object -First 1
                $d = [math]::Sqrt([math]::Pow($wb.x - $site.x, 2) + [math]::Pow($wb.z - $site.z, 2))
                $ring = @($SplinterDistances | Sort-Object { [math]::Abs($_ - $d) })[0]
                $own += [ordered]@{ ring = $ring; distance = [math]::Round($d, 1); before = $wb.health
                                    loss = $(if ($wa) { $wb.health - $wa.health } else { $wb.health }); killed = -not $wa }
            }
            $ownLoss = [math]::Round([double](($own | ForEach-Object { $_.loss } | Measure-Object -Sum).Sum), 1)
            $means = [ordered]@{}
            foreach ($ring in $SplinterDistances) {
                $v = @($own | Where-Object { $_.ring -eq $ring } | ForEach-Object { $_.loss })
                $means["$ring"] = if ($v.Count) { [math]::Round(($v | Measure-Object -Average).Average, 2) } else { $null }
            }
            $meanByOwner[$i] = $means
            $times = @($lives | ForEach-Object { [ordered]@{ first = $_.first; gone = $_.gone
                duration = $(if ($null -ne $_.gone) { [math]::Round($_.gone - $_.first, 2) } else { $null }) } })
            $detail = [ordered]@{ lifetimes = $times; ownWitnesses = $own; ownLoss = $ownLoss; meanLossByRing = $means
                                  mpauth = (Get-MpauthCounts $i) }
            if ($i -eq $L) { $detail.target = $targetDetail }
            $role = if ($i -eq $L) { 'launcher' } else { 'receiver' }
            Add-CRFlowCheck "observed on $role c${i}: $($lives.Count) Splinter lifetime(s) ($(@($times | ForEach-Object { "$($_.duration) s" }) -join ', ')); own witnesses lost $ownLoss" $true $detail
            if ($kill) {
                $kt = $kill.peerTimes["c$i"]
                $offsets = @($lives | Where-Object { $null -ne $_.gone } | ForEach-Object { [math]::Round($_.gone - $kt, 2) })
                # Fixed: the kill message crosses the network, so allow 1.5 s.
                $killTolerance = if ($Expect -eq 'Fixed') { 1.5 } else { 1 }
                $near = @($offsets | Where-Object { [math]::Abs($_) -le $killTolerance }).Count -gt 0
                $killDetail = [ordered]@{ killer = $kill.killer; killTimeOnKiller = $kill.time; killTimeOnThisPeer = $kt
                                          goneMinusKillTime = $offsets; killedHealthBefore = $kill.health; lifetimes = $times }
                if ($i -eq $kill.killer) {
                    Add-CRFlowCheck "observed: Splinter killed on c$i ($($kill.killed) object(s)); its lifetime ended $($offsets -join ', ') s from the kill" $true $killDetail
                } else {
                    Add-DuplicateCheck "deployed Splinter on c$i ended within $killTolerance s of the kill on c$($kill.killer)" $near $killDetail
                }
            }
        }
        foreach ($r in $receivers) {
            $ratios = [ordered]@{}
            foreach ($ring in $SplinterDistances) {
                $lm, $rm = $meanByOwner[$L]["$ring"], $meanByOwner[$r]["$ring"]
                $ratios["$ring"] = if ($lm -and $null -ne $rm) { [math]::Round($rm / $lm, 2) } else { $null }
            }
            $known = @($ratios.Values | Where-Object { $null -ne $_ })
            $ratio = if ($known.Count) { ($known | Measure-Object -Maximum).Maximum } else { $null }
            $detail = [ordered]@{ ratio = $ratio; ratioByRing = $ratios; launcherMean = $meanByOwner[$L]; receiverMean = $meanByOwner[$r]; target = $targetDetail }
            Add-CRFlowCheck "observed Splinter loss per ring, receiver c$r vs launcher c${L}: x$ratio" $true $detail
            # Worst ring decides; a launcher whose witnesses took nothing gives no ratio.
            if ($null -ne $ratio) {
                Add-DuplicateCheck "no escalated Splinter damage on receiver c$r's witnesses (x$ratio of launcher c$L)" ($ratio -lt 1.5) $detail
            }
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

# The phantom: with the aim point ~525 m away, nothing should end or hurt
# anything at the Armory. Each peer is judged on what it alone applies: its
# own witnesses' damage, plus the Daywrecker lifetimes it saw end there.
if ($watchArmory) {
    $armoryAfter = Invoke-CRFlowStep 'every peer at the Armory site after' {
        $out = @{}
        foreach ($i in $C) { $out["c$i"] = Get-Site $i 'armory' 'after' }
        $out
    }
    foreach ($i in $C) {
        $pre, $post = $armoryBefore["c$i"], $armoryAfter["c$i"]
        $ended = @(Get-Lifetimes $post 'daywrecker' | Where-Object { $_.gone })
        $own = @()
        foreach ($wb in @($pre.witnesses | Where-Object { $_ -and $_.mine })) {
            $wa = @($post.witnesses | Where-Object { $_ -and $_.id -eq $wb.id }) | Select-Object -First 1
            $own += [ordered]@{ id = $wb.id; before = $wb.health; loss = $(if ($wa) { $wb.health - $wa.health } else { $wb.health }); killed = -not $wa }
        }
        $loss = [math]::Round((@($own | ForEach-Object { $_.loss }) | Measure-Object -Sum).Sum, 1)
        $role = if ($i -eq $L) { 'launcher' } else { 'receiver' }
        $detail = [ordered]@{ role = $role; ended = $ended; ownWitnesses = $own; launch = $post.launch; mpauth = (Get-MpauthCounts $i) }
        Add-DuplicateCheck "no Daywrecker ends at the Armory on $role c$i ($($ended.Count))" ($ended.Count -eq 0) $detail
        Add-DuplicateCheck "no blast damage on $role c$i's own Armory witnesses (loss $loss)" ($loss -lt 1) $detail
    }
}
