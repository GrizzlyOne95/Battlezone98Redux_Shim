# Same-PC multiplayer sessions: several real Redux clients from one coordinator.
#
# Each client runs from its own generated instance directory. The instance is a
# copy of the GOG install's executable, DLLs and small config files, with
# directory junctions to the large read-only asset trees. Goldberg's
# steam_api.dll replaces the stock one, so SteamAPI_Init succeeds and the game
# selects its "PC Steam" platform path with a per-instance Steam identity (the
# GOG exe tries Steam first and only falls back to Galaxy when that fails).
# The GOG exe is used because it is the image OpenShim targets and carries no
# SteamStub wrapper.
#
# Launch safety: this script dot-sources BZRHarness.ps1, which takes the
# machine-wide launch lock for the life of this process. Every client is
# started from this one process, one after another, so no other harness can
# launch while a session runs. Clients are always windowed and are stopped by
# PID with Stop-BZRGame -NoForce; a client that ignores WM_CLOSE is left
# running and reported, so a hang can be captured instead of killed.
#
# Instance directories are disposable runtime output under $BZRCoopRoot. They
# are never source; regenerate them rather than editing them.

param(
    [ValidateSet('Prepare', 'Launch', 'Stop', 'Status')]
    [string]$Action = 'Status',
    [ValidateRange(1, 16)][int]$Clients = 2,
    [string]$SourceRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$BZRCoopRoot = 'C:\BZRCoop',
    # Goldberg steam_api.dll (32-bit). Defaults to the copy bundled with Nucleus.
    [string]$GoldbergDll = 'C:\BZRCoop\tools\NucleusCoop\utils\GoldbergEmu\steam_api.dll',
    # Directory holding a staged CR runtime mod (the contents of mods\3686673790).
    [string]$CampaignStage = '',
    [string]$VideoMode = '1280 x  720 @ 32-bit colour',
    # Fixed first wait between client starts; shorten only after repeated
    # clean starts at this value.
    [int]$LaunchDelaySeconds = 30,
    [int]$ReadyTimeoutSeconds = 120,
    [string[]]$GameArgs = @('/nointro'),
    # 'local' (default) DNS-redirects the stock matchmaking host through
    # OpenShim to a loopback Battlezone98Redux_DedicatedServer. 'official'
    # sends test clients with Goldberg identities to Rebellion's public lobby
    # and additionally requires -AllowOfficialServer.
    [ValidateSet('official', 'local')]
    [string]$Matchmaking = 'local',
    [switch]$AllowOfficialServer,
    [string]$LocalServerHealthUrl = 'http://127.0.0.1:8080/health',
    [string]$RunName = '',
    # Stock baseline: leave OpenShim's winmm.dll proxy out of the instances.
    [switch]$NoOpenShim,
    # OpenShim checkout with a Release|Win32 build. When set, instances get that
    # build's winmm/bzloader/openshim.dll, patches.json and renderer resources
    # instead of whatever is deployed in $SourceRoot. Empty = copy from $SourceRoot.
    [string]$OpenShimRepo = ''
)

$ErrorActionPreference = 'Stop'
$GameRoot = $null  # keep BZRHarness away from any real install's ogre.cfg
if ($Action -ne 'Launch') {
    # Only Launch starts games. Stop/Status must not queue behind the lock a
    # running session holds.
    $env:BZR_LAUNCH_LOCK_HELD = "$PID-nolaunch"
}
. "$PSScriptRoot\BZRHarness.ps1"

$InstancesDir = Join-Path $BZRCoopRoot 'instances'
$RunsDir = Join-Path $BZRCoopRoot 'runs'
$SessionFile = Join-Path $BZRCoopRoot 'session.json'
# Rebellion's production matchmaking endpoint as seen in stock logs; a local
# session must never reach it.
$OfficialMatchmakingIp = '68.183.35.188'
$CampaignModId = '3686673790'
$SteamAppId = '301650'

# Large trees the game only reads. Junctions need no elevation.
$LinkedDirs = @('BZ_ASSETS', 'BZ_ASSETS_CORE', 'music', 'Text', 'giddi',
                'packaged_mods', 'Edit', 'openshim', 'plugins', 'flags')
# Root files copied per instance (anything the game or OpenShim might write).
$CopiedRootPatterns = @('battlezone98redux.exe', '*.dll', '*.cfg', '*.ini',
                        '*.map', 'BZPLYR.DEF')
# Large read-only root data (the .zfs archives hold the core game data). Hard
# links need no elevation; both trees must be on the same volume.
$LinkedRootPatterns = @('*.zfs', '*.zix', '*.fnt', '*.cur', 'localization_table.csv',
                        'goggame-1454067812.*')
$NeverCopy = @('steam_api.dll')
if ($NoOpenShim) { $NeverCopy += 'winmm.dll' }
# Interface versions the stock steam_api.dll exports, from Goldberg's
# generate_interfaces_file.exe; Goldberg needs it for this older SDK.
$SteamInterfaces = Join-Path $BZRCoopRoot 'tools\steam_interfaces.txt'

# Each game root keeps the stock folder name: mod loaders such as Campaign
# Reimagined's RequireFix recognise the game directory by it and otherwise
# search one level too high (exu.dll/bzfile.dll then fail to load).
function Get-InstanceDir([int]$Index) { Join-Path $InstancesDir ("Instance{0}\Battlezone 98 Redux" -f $Index) }

function Get-FileSha256([string]$Path) {
    if (Test-Path -LiteralPath $Path) { (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash.ToLowerInvariant() }
}

function Install-OpenShimBuild([string]$Dir) {
    # Deploy-OpenShim.ps1 also writes into BZ_ASSETS_CORE, which is a junction
    # to the real install here, so the instance gets the build's own files only.
    $bin = Join-Path $OpenShimRepo 'bin\Release'
    foreach ($rel in 'winmm.dll', 'bzloader.dll', 'plugins\openshim.dll') {
        $src = Join-Path $bin $rel
        if (-not (Test-Path -LiteralPath $src)) { throw "Missing OpenShim build output $src; build Release|Win32 first." }
        Copy-Item -LiteralPath $src -Destination (Join-Path $Dir $rel) -Force
    }
    Copy-Item -LiteralPath (Join-Path $OpenShimRepo 'scripts\patches.json') -Destination (Join-Path $Dir 'scripts\patches.json') -Force
    $render = Join-Path $Dir 'openshim\renderer\enhanced'
    New-Item -ItemType Directory -Path $render -Force | Out-Null
    Copy-Item -Path (Join-Path $OpenShimRepo 'resources\renderer\enhanced\*') -Destination $render -Force
    $assets = Join-Path $OpenShimRepo 'resources\openshim\OpenShimAssets.ini'
    if (Test-Path -LiteralPath $assets) { Copy-Item -LiteralPath $assets -Destination (Join-Path $Dir 'openshim') -Force }
}

function New-BZRCoopInstance {
    param([int]$Index)
    $dir = [IO.Path]::GetFullPath((Get-InstanceDir $Index))
    $safeRoot = [IO.Path]::GetFullPath($InstancesDir).TrimEnd('\') + '\'
    if (-not $dir.StartsWith($safeRoot, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Instance path is outside $safeRoot"
    }
    if (Get-Process battlezone98redux -ErrorAction SilentlyContinue |
            Where-Object { $_.Path -and $_.Path.StartsWith($dir, [StringComparison]::OrdinalIgnoreCase) }) {
        throw "A client is still running from $dir; stop the session first."
    }
    if (Test-Path -LiteralPath $dir) {
        # Junctions first, so removing the tree never descends into the real install.
        Get-ChildItem -LiteralPath $dir -Directory -Force |
            Where-Object { $_.Attributes -band [IO.FileAttributes]::ReparsePoint } |
            ForEach-Object { [IO.Directory]::Delete($_.FullName) }
        Remove-Item -LiteralPath $dir -Recurse -Force
    }
    New-Item -ItemType Directory -Path $dir | Out-Null

    $linked = $LinkedDirs
    if ($OpenShimRepo) {
        # Per-instance copies, so staging a build never writes the real install.
        $linked = $LinkedDirs | Where-Object { $_ -notin 'plugins', 'openshim' }
        New-Item -ItemType Directory -Path (Join-Path $dir 'plugins') | Out-Null
        robocopy (Join-Path $SourceRoot 'openshim') (Join-Path $dir 'openshim') /E /NFL /NDL /NJH /NJS /NP | Out-Null
        if ($LASTEXITCODE -ge 8) { throw "robocopy of openshim resources failed ($LASTEXITCODE)" }
    }
    foreach ($name in $linked) {
        $target = Join-Path $SourceRoot $name
        if (Test-Path -LiteralPath $target) {
            New-Item -ItemType Junction -Path (Join-Path $dir $name) -Target $target | Out-Null
        }
    }
    foreach ($pattern in $CopiedRootPatterns) {
        Get-ChildItem -LiteralPath $SourceRoot -Filter $pattern -File |
            Where-Object { $NeverCopy -notcontains $_.Name } |
            ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $dir }
    }
    foreach ($pattern in $LinkedRootPatterns) {
        Get-ChildItem -LiteralPath $SourceRoot -Filter $pattern -File |
            Where-Object { -not (Test-Path -LiteralPath (Join-Path $dir $_.Name)) } |
            ForEach-Object { New-Item -ItemType HardLink -Path (Join-Path $dir $_.Name) -Target $_.FullName | Out-Null }
    }
    # Clients are driven by posted window messages. OpenShim's RawMouseInput
    # setting (openshim.ini) overrides /norawinput and makes the game ignore
    # them, so every test instance turns it off in its own copy.
    $shimIni = Join-Path $dir 'openshim.ini'
    if (Test-Path -LiteralPath $shimIni) {
        $ini = [IO.File]::ReadAllText($shimIni)
        $ini = [regex]::Replace($ini, '(?m)^(\s*RawMouseInput\s*=\s*)\S+', '${1}0')
        [IO.File]::WriteAllText($shimIni, $ini)
    }
    Copy-Item -LiteralPath (Join-Path $SourceRoot 'scripts') -Destination $dir -Recurse
    if ($OpenShimRepo -and -not $NoOpenShim) { Install-OpenShimBuild $dir }
    foreach ($name in 'logs', 'save', 'shader_cache', 'mods', 'addon') {
        New-Item -ItemType Directory -Path (Join-Path $dir $name) -Force | Out-Null
    }

    # Goldberg identity, kept inside the instance (local_save.txt).
    Copy-Item -LiteralPath $GoldbergDll -Destination (Join-Path $dir 'steam_api.dll')
    New-Item -ItemType File -Path (Join-Path $dir 'local_save.txt') -Force | Out-Null
    $ss = New-Item -ItemType Directory -Path (Join-Path $dir 'steam_settings') -Force
    $steamId = 76561199023125438 + $Index
    Set-Content -LiteralPath (Join-Path $ss 'steam_appid.txt') -Value $SteamAppId -NoNewline
    Set-Content -LiteralPath (Join-Path $ss 'force_account_name.txt') -Value ("BZRCoop{0}" -f ($Index + 1)) -NoNewline
    Set-Content -LiteralPath (Join-Path $ss 'force_steamid.txt') -Value $steamId -NoNewline
    Set-Content -LiteralPath (Join-Path $dir 'steam_appid.txt') -Value $SteamAppId -NoNewline
    if (Test-Path -LiteralPath $SteamInterfaces) { Copy-Item -LiteralPath $SteamInterfaces -Destination $ss }
    # Redux only asks Steam for an identity; its traffic is BZRNet. Goldberg's
    # own LAN discovery (UDP/TCP 47584 on every adapter, VPNs included) is not
    # needed, and with OpenShim's Winsock hooks it crashed the client (a socket
    # handle read as a pointer in ucrtbase, 2026-10-05).
    New-Item -ItemType File -Path (Join-Path $ss 'disable_networking.txt') -Force | Out-Null

    if ($CampaignStage) {
        $modDir = Join-Path $dir "mods\$CampaignModId"
        robocopy $CampaignStage $modDir /E /NFL /NDL /NJH /NJS /NP | Out-Null
        if ($LASTEXITCODE -ge 8) { throw "robocopy of $CampaignStage failed ($LASTEXITCODE)" }
        # Steam-platform builds discover Workshop items through UGC; Goldberg
        # serves those from steam_settings\mods\<id>.
        $ugc = New-Item -ItemType Directory -Path (Join-Path $ss 'mods') -Force
        New-Item -ItemType Junction -Path (Join-Path $ugc $CampaignModId) -Target $modDir | Out-Null
    }

    $null = Set-BZROgreWindowed -GameRoot $dir -VideoMode $VideoMode
    [pscustomobject]@{ Index = $Index; Dir = $dir; SteamId = "$steamId"; Name = "BZRCoop$($Index + 1)" }
}

function Get-ClientLogState([string]$Dir) {
    # Stock Redux writes BZLogger.txt in the game root; OpenShim moves it to logs\.
    $log = Get-ChildItem -LiteralPath $Dir, (Join-Path $Dir 'logs') -Filter 'BZLogger.txt' -File -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty FullName
    $state = [ordered]@{ platform = $null; menu = $false; authenticatedAs = $null
                         officialContact = $false; redirect = $null; last = $null }
    $shimLog = Join-Path $Dir 'logs\openshim.log'
    if (Test-Path -LiteralPath $shimLog) {
        $m = Select-String -LiteralPath $shimLog -Pattern 'matchmaking DNS redirect enabled: \S+ -> (\S+)' |
            Select-Object -Last 1
        if ($m) { $state.redirect = $m.Matches[0].Groups[1].Value }
    }
    if (-not $log) { return $state }
    $lines = @(Get-Content -LiteralPath $log -ErrorAction SilentlyContinue)
    foreach ($l in $lines) {
        if ($l -match 'Version [\d.]+, (PC \w+)') { $state.platform = $Matches[1] }
        if ($l -match 'Start of Game Menu Display') { $state.menu = $true }
        if ($l -match 'Authenticated to BZRNet As (\S+)') { $state.authenticatedAs = $Matches[1] }
        if ($l.Contains($OfficialMatchmakingIp)) { $state.officialContact = $true }
    }
    if ($lines.Count) { $state.last = $lines[-1] }
    $state
}

function Write-SessionFile($Session) {
    # Readers poll while clients are added/authenticated. Publish one complete
    # snapshot and retry briefly if a Windows reader holds the destination.
    $pending = "$SessionFile.$PID.tmp"
    try {
        [IO.File]::WriteAllText($pending, ($Session | ConvertTo-Json -Depth 6), (New-Object Text.UTF8Encoding($false)))
        $deadline = (Get-Date).AddSeconds(5)
        while ($true) {
            try {
                if ([IO.File]::Exists($SessionFile)) { [IO.File]::Replace($pending, $SessionFile, [NullString]::Value) }
                else { [IO.File]::Move($pending, $SessionFile) }
                break
            } catch [IO.IOException] {
                if ((Get-Date) -ge $deadline) { throw }
                Start-Sleep -Milliseconds 50
            }
        }
    } finally {
        if (Test-Path -LiteralPath $pending) { Remove-Item -LiteralPath $pending -Force }
    }
}

function Read-SessionFile {
    $deadline = (Get-Date).AddMilliseconds(500)
    while ($true) {
        try {
            $stream = [IO.File]::Open($SessionFile, 'Open', 'Read', ([IO.FileShare]::ReadWrite -bor [IO.FileShare]::Delete))
            $reader = New-Object IO.StreamReader($stream)
            try { return ($reader.ReadToEnd() | ConvertFrom-Json) } finally { $reader.Dispose() }
        } catch [IO.IOException] {
            if ((Get-Date) -ge $deadline) {
                if (-not (Test-Path -LiteralPath $SessionFile)) { return }
                throw
            }
            Start-Sleep -Milliseconds 10
        }
    }
}

function Start-BZRCoopClients {
    $existing = Read-SessionFile
    if ($existing) {
        $alive = @($existing.clients | Where-Object { Get-Process -Id $_.pid -ErrorAction SilentlyContinue })
        if ($alive.Count) { throw "Session already running (pids $($alive.pid -join ', ')). Stop it first." }
    }
    if (-not $RunName) { $script:RunName = Get-Date -Format 'yyyyMMdd-HHmmss' }
    $runDir = New-Item -ItemType Directory -Path (Join-Path $RunsDir $RunName) -Force

    $env:BZR_FORCE_WINDOWED = '1'
    if ($Matchmaking -eq 'local') {
        $manifestPath = Join-Path $InstancesDir 'manifest.json'
        if ((Test-Path -LiteralPath $manifestPath) -and (Get-Content -LiteralPath $manifestPath -Raw | ConvertFrom-Json).noOpenShim) {
            throw 'Instances were prepared with -NoOpenShim; local matchmaking needs OpenShim''s redirect. Re-run Prepare without it.'
        }
        try { Invoke-RestMethod -Uri $LocalServerHealthUrl -TimeoutSec 3 | Out-Null }
        catch { throw "Local matchmaking server is not answering at $LocalServerHealthUrl; start Battlezone98Redux_DedicatedServer first." }
        $env:OPENSHIM_MATCHMAKING_ADDRESS = '127.0.0.1'
    } else {
        if (-not $AllowOfficialServer) { throw '-Matchmaking official sends test identities to the public lobby; pass -AllowOfficialServer to confirm.' }
        Remove-Item Env:OPENSHIM_MATCHMAKING_ADDRESS -ErrorAction SilentlyContinue
    }

    $session = [ordered]@{
        run = $RunName; runDir = $runDir.FullName; started = (Get-Date).ToString('o')
        sourceRoot = $SourceRoot; matchmaking = $Matchmaking; launchDelaySeconds = $LaunchDelaySeconds
        coordinatorPid = $PID; clients = @()
    }
    $clock = [Diagnostics.Stopwatch]::StartNew()
    for ($i = 0; $i -lt $Clients; $i++) {
        $inst = Get-InstanceDir $i
        if (-not (Test-Path -LiteralPath (Join-Path $inst 'battlezone98redux.exe'))) {
            throw "Instance $i is not prepared; run -Action Prepare first."
        }
        if ($i -gt 0) { Start-Sleep -Seconds $LaunchDelaySeconds }
        $p = Start-Process -FilePath (Join-Path $inst 'battlezone98redux.exe') -WorkingDirectory $inst `
                -ArgumentList $GameArgs -PassThru
        $session.clients += [ordered]@{ index = $i; pid = $p.Id; dir = $inst; launchedAtMs = $clock.ElapsedMilliseconds }
        Write-SessionFile $session
        Write-Host ("[BZRCoop] client {0} pid {1} from {2}" -f $i, $p.Id, $inst)

        $deadline = (Get-Date).AddSeconds($ReadyTimeoutSeconds)
        $redirectDeadline = (Get-Date).AddSeconds(15)
        $ready = $false
        do {
            Start-Sleep -Milliseconds 500
            $st = Get-ClientLogState $inst
            if ($p.HasExited) { throw "client $i (pid $($p.Id)) exited with $($p.ExitCode) before lobby auth; last log: $($st.last)" }
            if ($Matchmaking -eq 'local') {
                if ($st.officialContact -or (-not $st.redirect -and (Get-Date) -gt $redirectDeadline) -or
                        ($st.redirect -and $st.redirect -ne '127.0.0.1')) {
                    Stop-BZRGame -Id $p.Id -NoForce -TimeoutSeconds 20
                    throw "client $i matchmaking was not confined to 127.0.0.1 (redirect=$($st.redirect), officialContact=$($st.officialContact)); client stopped."
                }
            }
            $ready = [bool]$st.authenticatedAs
        } until ($ready -or (Get-Date) -gt $deadline)
        if (-not $ready) { throw "client $i did not authenticate to the lobby in ${ReadyTimeoutSeconds}s; last log: $($st.last)" }
        $session.clients[$i].menuAtMs = $clock.ElapsedMilliseconds
        $session.clients[$i].authenticatedAs = $st.authenticatedAs
        $session.clients[$i].redirect = $st.redirect
        Write-SessionFile $session
        Write-Host ("[BZRCoop] client {0} authenticated as {1} after {2:N1}s (redirect {3})" -f $i, $st.authenticatedAs, ($clock.ElapsedMilliseconds / 1000), $st.redirect)
    }
    $session
}

function Stop-BZRCoopClients {
    $session = Read-SessionFile
    if (-not $session) { Write-Host '[BZRCoop] no session'; return }
    # A coordinator still inside Launch would start the next client and rewrite
    # session.json after we delete it; end it before touching the clients.
    $coord = Get-CimInstance Win32_Process -Filter "ProcessId=$($session.coordinatorPid)" -ErrorAction SilentlyContinue
    if ($coord -and $coord.ProcessId -ne $PID -and $coord.CommandLine -match 'BZRCoopSession\.ps1') {
        Stop-Process -Id $coord.ProcessId -Force
        Write-Host "[BZRCoop] stopped coordinator pid $($coord.ProcessId)"
        $session = Read-SessionFile
    }
    $hung = @()
    foreach ($c in $session.clients) {
        if (-not (Get-Process -Id $c.pid -ErrorAction SilentlyContinue)) { continue }
        try { Stop-BZRGame -Id $c.pid -NoForce -TimeoutSeconds 20 }
        catch { $hung += $c.pid; Write-Warning $_ }
    }
    # Evidence: copy each client's logs into the run directory.
    foreach ($c in $session.clients) {
        $dest = New-Item -ItemType Directory -Path (Join-Path $session.runDir ("client{0}" -f $c.index)) -Force
        foreach ($f in 'BZLogger.txt', 'BZOgreLogfile.log', 'openshim.log', 'bzloader.log', 'BZChatLog.txt') {
            $src = Join-Path $c.dir $f
            if (Test-Path -LiteralPath $src) { Copy-Item -LiteralPath $src -Destination $dest }
        }
        $logs = Join-Path $c.dir 'logs'
        if (Test-Path -LiteralPath $logs) { Copy-Item -LiteralPath $logs -Destination $dest -Recurse -Force }
    }
    if ($hung.Count) { throw "Clients still running after WM_CLOSE (left for capture): $($hung -join ', ')" }
    [IO.File]::Delete($SessionFile) # another orderly stopper may already have removed it
    Write-Host "[BZRCoop] stopped; evidence in $($session.runDir)"
}

function Get-BZRCoopStatus {
    $session = Read-SessionFile
    for ($i = 0; $i -lt $Clients; $i++) {
        $dir = Get-InstanceDir $i
        $c = if ($session) { $session.clients | Where-Object index -eq $i }
        [pscustomobject]@{
            Index = $i
            Prepared = Test-Path -LiteralPath (Join-Path $dir 'battlezone98redux.exe')
            Pid = $c.pid
            Running = [bool]($c -and (Get-Process -Id $c.pid -ErrorAction SilentlyContinue))
            AuthenticatedAs = (Get-ClientLogState $dir).authenticatedAs
            Redirect = (Get-ClientLogState $dir).redirect
            LastLog = (Get-ClientLogState $dir).last
        }
    }
}

switch ($Action) {
    'Prepare' {
        $instances = @(0..($Clients - 1) | ForEach-Object { New-BZRCoopInstance $_ })
        $manifest = [ordered]@{
            prepared = (Get-Date).ToString('o'); sourceRoot = $SourceRoot
            exeSha256 = Get-FileSha256 (Join-Path $SourceRoot 'battlezone98redux.exe')
            goldbergSha256 = Get-FileSha256 $GoldbergDll
            noOpenShim = [bool]$NoOpenShim
            openshimRepo = $OpenShimRepo
            openshimCommit = if ($OpenShimRepo) { (git -C $OpenShimRepo rev-parse HEAD) } else { $null }
            openshimDirty = if ($OpenShimRepo) { [bool](git -C $OpenShimRepo status --porcelain --untracked-files=no) } else { $null }
            openshimDllSha256 = Get-FileSha256 (Join-Path (Get-InstanceDir 0) 'plugins\openshim.dll')
            bzloaderSha256 = Get-FileSha256 (Join-Path (Get-InstanceDir 0) 'bzloader.dll')
            winmmSha256 = Get-FileSha256 (Join-Path (Get-InstanceDir 0) 'winmm.dll')
            campaignStage = $CampaignStage
            instances = $instances
        }
        $manifest | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $InstancesDir 'manifest.json')
        $manifest.instances | Format-Table -AutoSize
    }
    'Launch' {
        $session = Start-BZRCoopClients
        Get-BZRCoopStatus | Format-Table -AutoSize
        # Keep this process, and with it the launch lock, alive until every
        # client has gone, so no other harness launches into a running session.
        Write-Host '[BZRCoop] holding the launch lock until all clients exit (use -Action Stop from another shell)'
        foreach ($c in $session.clients) {
            $p = Get-Process -Id $c.pid -ErrorAction SilentlyContinue
            if ($p) { $p.WaitForExit() }
        }
        Write-Host '[BZRCoop] all clients exited; lock released'
    }
    'Stop' { Stop-BZRCoopClients }
    'Status' { Get-BZRCoopStatus | Format-Table -AutoSize -Wrap }
}
