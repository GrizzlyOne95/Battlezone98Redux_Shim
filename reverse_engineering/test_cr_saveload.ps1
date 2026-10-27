<#
.SYNOPSIS
Save/load smoke for every Campaign Reimagined single-player mission: starts each
mission, saves it through the menu path and OpenShim's autosave, then loads each
save in a fresh process and requires the loaded mission to keep running.
.DESCRIPTION
Run in a separate pwsh process. Per mission, three launches:

  start     <mission>.bzn /saveafterload. The engine writes Save\game1.sav through
            the menu save path right after load; OpenShim's autosave then writes
            Save\auto.sav once the mission has run for -AutosaveDelaySeconds.
  autoload  Bare launch with OPENSHIM_FORCE_STARTUP_AUTOLOAD=1: the stock shell
            autoload resumes Save\auto.sav (the "Continue" path).
  menuload  Positional Save\game1.sav argument: the engine's LoadGame path.

Each load must reach the bookmark/simulation markers and survive -HoldSeconds
(the 2026-10-26 misn02b crash fired on the first Update after load). A run fails
on early exit, a new crash dump, an unhandled [CRASH] report, a Lua/load error,
a missing clean engine exit, a stale patch registration, exu.dll loading from
anywhere but the CR folder, or an OpenShim GetIndependence guard rejection --
the guard turns that crash into a warning, so a rejection means a script
regressed into calling GetIndependence while a save was loading.

A command-line .bzn has no campaign id, so the engine infers one from the mission
name: stock campaigns first, then mod campaigns. With CR at mapType = "campaign"
that infers the stock "usa" campaign for every CR mission whose name is in the
stock table, and nothing mounts CR. For those missions the run temporarily sets
mapType = "mod" in the game's copy, which loads CR's files exactly as the campaign
does, but not through the campaign-select screen. misn15.bzn and misn16.bzn are
not in the stock table (it lists misn15b/misn16b), so with "mod" nothing would
mount; they run with crcampgn.ini as shipped, which infers CR's own campaign.
Saves, configuration, crcampgn.ini and modEnabled.dat are
snapshotted and restored with hash checks; every save the run creates is archived
into the evidence folder and removed. Uses BZRHarness's machine-wide launch lock
(waiting up to -LockTimeoutSeconds), windowed mode, and graceful shutdown.

Refuses to run when the game's CR Lua differs from -CrRepo (a stale test copy
tests yesterday's scripts); deploy CR first, or pass -CrRepo '' to skip.
.EXAMPLE
pwsh -NoProfile -File reverse_engineering/test_cr_saveload.ps1 `
  -Label saveload-all -EvidenceDirectory C:\Temp\cr-saveload
.EXAMPLE
pwsh -NoProfile -File reverse_engineering/test_cr_saveload.ps1 `
  -Label saveload-misn02b -EvidenceDirectory C:\Temp\cr-saveload -Missions misn02b.bzn
#>
#requires -Version 7.0
[CmdletBinding()]
param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9_-]+$')][string]$Label,
    [Parameter(Mandatory)][string]$EvidenceDirectory,
    [string]$GameRoot='C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    # Default: every missionBZN in the game copy's crcampgn.ini, in campaign order.
    # Comma-separated also works, since pwsh -File binds only one array value.
    [ValidatePattern('^[A-Za-z0-9_,.-]+$')][string[]]$Missions,
    [ValidateSet('autoload','menuload')][string[]]$Loads=@('autoload','menuload'),
    [string]$CrRepo=(Join-Path $env:USERPROFILE 'Documents\GIT\Campaign-Reimagined'),
    [ValidateSet('dx9','dx11')][string]$Renderer='dx11',
    [ValidateRange(5,600)][int]$AutosaveDelaySeconds=25,
    [ValidateRange(10,600)][int]$HoldSeconds=30,
    [ValidateRange(30,900)][int]$LoadTimeoutSeconds=240,
    [int]$LockTimeoutSeconds=7200
)
$ErrorActionPreference='Stop'
$missionList=@($Missions | ForEach-Object { $_ -split ',' } | Where-Object { $_ })
foreach($m in $missionList){if($m -notmatch '^[A-Za-z0-9_-]+\.bzn$'){throw "Not a mission basename: $m"}}
$GameRoot=(Resolve-Path -LiteralPath $GameRoot).Path.TrimEnd('\')
$campaignRoot=Join-Path $GameRoot 'mods\3686673790'
$campaignIni=Join-Path $campaignRoot 'crcampgn.ini'
# CR missions the stock usa table (0x482E20) does not list; see the description.
$stockTableLacks=@('misn15.bzn','misn16.bzn')
$auditRoot=Join-Path ([IO.Path]::GetFullPath($EvidenceDirectory)) $Label
if($auditRoot.StartsWith($GameRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Evidence must be outside the game installation'}
if(Test-Path -LiteralPath $auditRoot){throw 'Use a new label; never overwrite evidence'}
if(-not (Test-Path -LiteralPath $campaignIni)){throw "Campaign Reimagined is not installed at $campaignRoot"}
New-Item -ItemType Directory -Path $auditRoot | Out-Null
$exe=Join-Path $GameRoot 'battlezone98redux.exe'
$saveRoot=[IO.Path]::GetFullPath((Join-Path $GameRoot 'save'))
$snapshot=[Collections.Generic.Dictionary[string,object]]::new([StringComparer]::OrdinalIgnoreCase)
$results=[Collections.Generic.List[object]]::new()
$failure=$null
$launched=$false
$proc=$null

function Save-AuditFile([string]$Path) {
    $canonical=[IO.Path]::GetFullPath($Path)
    if($snapshot.ContainsKey($canonical)){return}
    if(-not $canonical.StartsWith($GameRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Backup path outside game root'}
    $relative=[IO.Path]::GetRelativePath($GameRoot,$canonical)
    $backup=Join-Path (Join-Path $auditRoot 'before') $relative
    $exists=Test-Path -LiteralPath $canonical -PathType Leaf
    if($exists){
        New-Item -ItemType Directory -Force -Path (Split-Path -Parent $backup) | Out-Null
        Copy-Item -LiteralPath $canonical -Destination $backup
    }
    $snapshot.Add($canonical,[pscustomobject]@{Path=$canonical;Relative=$relative;Backup=$backup;Existed=$exists;Hash=$(if($exists){(Get-FileHash -LiteralPath $canonical).Hash}else{$null})})
}
function Set-IniValues([string]$Path,[string]$Section,[Collections.IDictionary]$Values) {
    $lines=[Collections.Generic.List[string]]::new([string[]][IO.File]::ReadAllLines($Path))
    $start=-1
    for($i=0;$i -lt $lines.Count;$i++){if($lines[$i].Trim() -ieq "[$Section]"){$start=$i;break}}
    if($start -lt 0){$lines.Add("[$Section]");$start=$lines.Count-1}
    foreach($key in $Values.Keys){
        $end=$lines.Count
        for($i=$start+1;$i -lt $lines.Count;$i++){if($lines[$i] -match '^\s*\['){$end=$i;break}}
        $found=$false
        for($i=$start+1;$i -lt $end;$i++){
            if($lines[$i] -match ('^\s*'+[regex]::Escape($key)+'\s*=')){$lines[$i]="$key = $($Values[$key])";$found=$true;break}
        }
        if(-not $found){$lines.Insert($start+1,"$key = $($Values[$key])")}
    }
    [IO.File]::WriteAllLines($Path,$lines,[Text.UTF8Encoding]::new($false))
}
function Get-LogFile([string]$Name) {
    @(foreach($path in @((Join-Path (Join-Path $GameRoot 'logs') $Name),(Join-Path $GameRoot $Name))){
        if(Test-Path -LiteralPath $path -PathType Leaf){Get-Item -LiteralPath $path}
    }) | Sort-Object LastWriteTime -Descending | Select-Object -First 1
}
# The game holds its logs open for writing; File.ReadAllBytes would refuse them.
function Read-SharedBytes([string]$Path) {
    $stream=[IO.FileStream]::new($Path,[IO.FileMode]::Open,[IO.FileAccess]::Read,[IO.FileShare]::ReadWrite -bor [IO.FileShare]::Delete)
    try {
        $buffer=[IO.MemoryStream]::new()
        $stream.CopyTo($buffer)
        ,$buffer.ToArray()  # the comma stops the pipeline unrolling the byte[]
    } finally { $stream.Dispose() }
}
# Marks a log so New-LogText returns only what this run appended. A file the game
# rewrote from the top (different first bytes, or shorter) counts as all new.
function Get-LogMark([string]$Name) {
    $file=Get-LogFile $Name
    if(-not $file){return [pscustomobject]@{Name=$Name;Path=$null;Length=0;Head=$null}}
    $bytes=Read-SharedBytes $file.FullName
    [pscustomobject]@{Name=$Name;Path=$file.FullName;Length=$bytes.Length;Head=[Convert]::ToBase64String($bytes,0,[Math]::Min(4096,$bytes.Length))}
}
function New-LogText($Mark,[datetime]$Since) {
    $file=Get-LogFile $Mark.Name
    # No LastWriteTime test: NTFS can leave it stale while the game holds the
    # file open, and an untouched file already yields nothing past the mark.
    if(-not $file){return ''}
    $bytes=Read-SharedBytes $file.FullName
    $offset=0
    if($Mark.Path -ieq $file.FullName -and $bytes.Length -ge $Mark.Length -and $Mark.Head -and
        [Convert]::ToBase64String($bytes,0,[Math]::Min(4096,$Mark.Length)) -eq $Mark.Head){$offset=$Mark.Length}
    [Text.Encoding]::UTF8.GetString($bytes,$offset,$bytes.Length-$offset)
}
function Test-Fresh([string]$Path,[datetime]$Since) {
    (Test-Path -LiteralPath $Path -PathType Leaf) -and (Get-Item -LiteralPath $Path).LastWriteTime -ge $Since
}
function Wait-NoGame {
    for($i=0;$i -lt 90;$i++){
        if(-not (Get-Process battlezone98redux -ErrorAction SilentlyContinue)){return}
        Start-Sleep -Seconds 2
    }
    throw 'A Battlezone process is still running after the launch lock was granted; not launching over it'
}

# One launch: start, wait for the load to finish, hold, capture, stop, judge.
function Invoke-SaveLoadRun {
    param([string]$Mission,[string]$Avenue,[string[]]$Arguments,[hashtable]$Environment=@{})
    $runDir=Join-Path (Join-Path $auditRoot ([IO.Path]::GetFileNameWithoutExtension($Mission))) $Avenue
    New-Item -ItemType Directory -Force -Path $runDir | Out-Null
    $problems=[Collections.Generic.List[string]]::new()
    $notes=[Collections.Generic.List[string]]::new()
    $marks=@{}
    foreach($name in 'BZLogger.txt','openshim.log','openshim_crash.log','exu.log'){$marks[$name]=Get-LogMark $name}
    $dumpsBefore=@(Get-ChildItem -LiteralPath (Join-Path $GameRoot 'logs') -Filter '*.dmp' -File | ForEach-Object FullName)
    $saved=@{}
    foreach($k in $Environment.Keys){$saved[$k]=[Environment]::GetEnvironmentVariable($k);[Environment]::SetEnvironmentVariable($k,$Environment[$k])}
    Wait-NoGame
    $started=Get-Date
    $script:proc=$null
    $exitedEarly=$false
    $modules=@()
    try {
        Assert-BZRSafeToLaunch
        $script:proc=Start-BZRGameProcess -FilePath $exe -ArgumentList $Arguments -WorkingDirectory $GameRoot -WindowStyle Hidden -PassThru
        $script:launched=$true
    } finally {
        foreach($k in $saved.Keys){[Environment]::SetEnvironmentVariable($k,$saved[$k])}
    }
    $p=$script:proc
    Write-Host ("[{0}] {1} {2}: pid {3}, args '{4}'" -f (Get-Date -Format 'HH:mm:ss'),$Mission,$Avenue,$p.Id,($Arguments -join ' '))

    # The mission is up once the engine logs simulation start; a load also logs
    # the bookmark line first. Requiring the simulation line covers both.
    $loadedAt=$null
    $deadline=$started.AddSeconds($LoadTimeoutSeconds)
    while((Get-Date) -lt $deadline){
        Start-Sleep -Seconds 2
        $p.Refresh()
        if($p.HasExited){$exitedEarly=$true;break}
        $bz=New-LogText $marks['BZLogger.txt'] $started
        if($bz -match 'Quiting Game because failed to load game files'){break}
        if($bz -match 'Game Simulation Initialized'){$loadedAt=Get-Date;break}
    }
    if($loadedAt){
        $notes.Add(("loaded in {0:N0}s" -f ($loadedAt-$started).TotalSeconds))
        # start: hold until OpenShim's autosave lands (or the window passes);
        # loads: hold the full window so the first Updates after load run.
        $holdUntil=if($Avenue -eq 'start'){$loadedAt.AddSeconds($AutosaveDelaySeconds+60)}else{$loadedAt.AddSeconds($HoldSeconds)}
        while((Get-Date) -lt $holdUntil){
            Start-Sleep -Seconds 2
            $p.Refresh()
            if($p.HasExited){$exitedEarly=$true;break}
            if($Avenue -eq 'start' -and ((Get-Date) -ge $loadedAt.AddSeconds($AutosaveDelaySeconds)) -and
                ((New-LogText $marks['openshim.log'] $started) -match "\[pid:$($p.Id) [^\]]*\] \[INFO\] \[autosave\] Saved .*auto\.sav")){
                Start-Sleep -Seconds 5  # let the save finish flushing before closing
                break
            }
        }
    }
    $p.Refresh()
    if(-not $p.HasExited){
        $modules=@($p.Modules | Where-Object ModuleName -Match 'winmm|bzloader|openshim|exu|bzfile' | Select-Object ModuleName,FileName)
        $modules | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $runDir 'modules.json')
        Stop-BZRGame -Id $p.Id
        $p.Refresh()
        if(-not $p.HasExited){throw "Game pid $($p.Id) ignored WM_CLOSE and was left running; aborting the batch"}
    } elseif(-not $exitedEarly){$exitedEarly=$true}
    $script:proc=$null
    foreach($helper in @(Get-Process bzfile_replace_helper -ErrorAction SilentlyContinue)){
        if($helper.StartTime -ge $started){Wait-Process -Id $helper.Id -Timeout 45 -ErrorAction SilentlyContinue}
    }
    $elapsed=((Get-Date)-$started).TotalSeconds

    $text=@{}
    foreach($name in $marks.Keys){
        $text[$name]=New-LogText $marks[$name] $started
        if($text[$name]){[IO.File]::WriteAllText((Join-Path $runDir $name),$text[$name])}
    }
    # openshim.log can carry other processes' lines; judge only this pid's.
    $shim=(($text['openshim.log'] -split "`r?`n") | Where-Object { $_ -match "\[pid:$($p.Id) " }) -join "`n"
    $bz=$text['BZLogger.txt']
    $newDumps=@(Get-ChildItem -LiteralPath (Join-Path $GameRoot 'logs') -Filter '*.dmp' -File | Where-Object { $dumpsBefore -notcontains $_.FullName })

    if($exitedEarly){$problems.Add("process exited on its own (exit $($p.ExitCode))")}
    if(-not $loadedAt){$problems.Add($(if($bz -match 'Quiting Game because failed to load game files'){'engine failed to load the game files'}else{"no 'Game Simulation Initialized' within ${LoadTimeoutSeconds}s"}))}
    if($bz -notmatch 'Exiting Game With Return Code 0'){$problems.Add('no clean engine exit')}
    $luaErrors=@(($bz -split "`r?`n") | Where-Object { $_ -match 'Lua Error|Error in Lua|Error in Update|Error loading|Could not load' })
    if($luaErrors.Count){$problems.Add("Lua/load error: $($luaErrors[0].Trim())")}
    if($text['openshim_crash.log'] -match '\[CRASH\]'){$problems.Add('unhandled exception reported in openshim_crash.log')}
    if($newDumps.Count){$problems.Add("new crash dump(s): $($newDumps.Name -join ', ')")}
    if($shim -match '\[STALE-CONFIG\]'){$problems.Add('stale patch registration')}
    $rejects=@(($shim -split "`n") | Where-Object { $_ -match 'GetIndependence\(0x[0-9A-Fa-f]+\): AI process' })
    if($rejects.Count){$problems.Add("GetIndependence guard rejected $($rejects.Count) call(s): a script read independence while the save was loading")}
    if($modules.Count){
        $exu=[IO.Path]::GetFullPath((Join-Path $campaignRoot 'exu.dll'))
        if(-not ($modules | Where-Object { $_.ModuleName -ieq 'exu.dll' -and [IO.Path]::GetFullPath($_.FileName) -ieq $exu })){$problems.Add('exu.dll not loaded from the CR folder (CR did not mount)')}
    }
    # Any save load passes through the bookmark run state; a fresh .bzn start
    # never does. The positional .sav path sets it without the menu's log line.
    if($Avenue -ne 'start'){
        if($bz -notmatch 'now RUN_WAS_BOOKMARK'){$problems.Add('engine never entered the bookmark run state (the save was not loaded)')}
        if($Avenue -eq 'autoload' -and $bz -notmatch 'Auto Load Game: Run state set to bookmark'){$problems.Add('the shell autoload did not run')}
    } elseif($bz -match 'now RUN_WAS_BOOKMARK'){$problems.Add('the start run loaded a save instead of the mission')}
    if($shim -match '\[autosave\] Saved .*auto\.sav'){$notes.Add('autosave written')}
    $firstChance=([regex]::Matches($text['openshim_crash.log'],'\[FIRST-CHANCE\]')).Count
    if($firstChance){$notes.Add("$firstChance handled first-chance report(s)")}

    [pscustomobject]@{
        Mission=$Mission; Avenue=$Avenue; Verdict=$(if($problems.Count){'FAIL'}else{'PASS'})
        Seconds=[int]$elapsed; Pid=$p.Id; Problems=@($problems); Notes=@($notes); Started=$started
    }
}

# Copies this mission's saves to evidence. Files the snapshot does not know are
# removed after the copy is verified; snapshotted files come back in finally.
function Save-MissionSaves([string]$Mission) {
    $dest=Join-Path (Join-Path $auditRoot ([IO.Path]::GetFileNameWithoutExtension($Mission))) 'saves'
    foreach($file in @(Get-ChildItem -LiteralPath $saveRoot -File -Recurse)){
        $canonical=[IO.Path]::GetFullPath($file.FullName)
        if(-not $canonical.StartsWith($saveRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Unexpected save path'}
        $original=$snapshot[$canonical]
        if($original -and $original.Existed -and (Get-FileHash -LiteralPath $canonical).Hash -eq $original.Hash){continue}
        $copy=Join-Path $dest ([IO.Path]::GetRelativePath($saveRoot,$canonical))
        New-Item -ItemType Directory -Force -Path (Split-Path -Parent $copy) | Out-Null
        Copy-Item -LiteralPath $canonical -Destination $copy -Force
        if((Get-FileHash -LiteralPath $canonical).Hash -ne (Get-FileHash -LiteralPath $copy).Hash){throw 'Save archival failed'}
        if(-not $original){Remove-Item -LiteralPath $canonical}
    }
}

# Fail before touching anything if the game's CR scripts are not the repo's.
if($CrRepo){
    $repoHashes=@{}
    foreach($file in Get-ChildItem -LiteralPath $CrRepo -Filter '*.lua' -File -Recurse | Where-Object { $_.FullName -notmatch '\\(\.git|Local|Tests|Tools|References|Prototypes)\\' }){
        $repoHashes[$file.Name]=@($repoHashes[$file.Name])+(Get-FileHash -LiteralPath $file.FullName).Hash
    }
    $stale=@(foreach($file in Get-ChildItem -LiteralPath $campaignRoot -Filter '*.lua' -File){
        if($repoHashes.ContainsKey($file.Name) -and $repoHashes[$file.Name] -notcontains (Get-FileHash -LiteralPath $file.FullName).Hash){$file.Name}
    })
    if($stale.Count){throw ("The game's CR copy differs from $CrRepo in $($stale.Count) Lua file(s): $(($stale | Select-Object -First 8) -join ', '). " +
        "Deploy CR (Manage-CampaignFiles.ps1 -deploy) or pass -CrRepo '' to test the installed copy as-is.")}
}

$env:BZR_FORCE_WINDOWED='1'
$env:OPENSHIM_NEVER_ACTIVATE='1'
$env:OPENSHIM_NEVER_CAPTURE_MOUSE='1'
$env:OPENSHIM_FORCE_STARTUP_AUTOLOAD=$null
$env:BZR_LAUNCH_LOCK_TIMEOUT_SECONDS=[string]$LockTimeoutSeconds
Write-Output "Waiting for the game-launch lock (up to ${LockTimeoutSeconds}s)..."
# Dot-sourcing takes the launch lock first, then backs ogre.cfg up and forces
# windowed; Restore-BZROrphanedOgreConfig in finally puts the original back.
. (Join-Path $PSScriptRoot 'BZRHarness.ps1')
try {
    Wait-NoGame
    foreach($file in Get-ChildItem -LiteralPath $saveRoot -File -Recurse){Save-AuditFile $file.FullName}
    foreach($relative in @('openshim.ini','modEnabled.dat','campaignReimagined_settings.cfg','career_stats.cfg','save\auto.sav','save\auto2.sav','save\game1.sav')){
        Save-AuditFile (Join-Path $GameRoot $relative)
    }
    Save-AuditFile $campaignIni
    @($snapshot.Values) | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $auditRoot 'before.json')

    if(-not $missionList){
        $missionList=@(Select-String -LiteralPath $campaignIni -Pattern '^\s*missionBZN\s*=\s*"([^"]+)"' | ForEach-Object { $_.Matches[0].Groups[1].Value })
        if(-not $missionList.Count){throw 'No missionBZN entries in crcampgn.ini'}
    }
    [IO.File]::WriteAllText((Join-Path $GameRoot 'modEnabled.dat'),$campaignRoot+"`r`n",[Text.UTF8Encoding]::new($false))
    $ini=[IO.File]::ReadAllText($campaignIni)
    $flipped=[regex]::Replace($ini,'(?m)^(\s*mapType\s*=\s*)"campaign"','$1"mod"')
    if($flipped -eq $ini){throw 'crcampgn.ini has no mapType = "campaign" line to switch'}
    # One autosave per mission, AutosaveDelaySeconds in; never deferred to CR's own.
    Set-IniValues (Join-Path $GameRoot 'openshim.ini') 'AutoSave' ([ordered]@{
        Enabled=1; InitialDelaySeconds=$AutosaveDelaySeconds; IntervalSeconds=3600; RetrySeconds=5; BackupExisting=0; RespectExternalAutoSave=0})
    $ogre=Join-Path $GameRoot 'ogre.cfg'
    $renderName=if($Renderer -eq 'dx11'){'Direct3D11 Rendering Subsystem'}else{'Direct3D9 Rendering Subsystem'}
    [IO.File]::WriteAllText($ogre,([IO.File]::ReadAllText($ogre)-replace '(?m)^Render System=.*$',"Render System=$renderName"))
    [pscustomobject]@{Missions=$missionList;Loads=$Loads;Renderer=$Renderer;AutosaveDelaySeconds=$AutosaveDelaySeconds;HoldSeconds=$HoldSeconds
        Exe=(Get-FileHash -LiteralPath $exe).Hash;Shim=(Get-Item -LiteralPath (Join-Path $GameRoot 'plugins\openshim.dll')).VersionInfo.FileVersion} |
        ConvertTo-Json | Set-Content -LiteralPath (Join-Path $auditRoot 'run.json')

    $autoSave=Join-Path $saveRoot 'auto.sav'
    $auto2=Join-Path $saveRoot 'auto2.sav'
    $menuSave=Join-Path $saveRoot 'game1.sav'
    $common=@('/nointro',"/renderer:$Renderer")
    foreach($mission in $missionList){
        $campaignMode=$stockTableLacks -contains $mission
        [IO.File]::WriteAllText($campaignIni,$(if($campaignMode){$ini}else{$flipped}),[Text.UTF8Encoding]::new($false))
        # The stock autoload resumes the newer of auto.sav and auto2.sav.
        if(Test-Path -LiteralPath $auto2){Remove-Item -LiteralPath $auto2}
        $start=Invoke-SaveLoadRun -Mission $mission -Avenue 'start' -Arguments (@($mission)+$common+'/saveafterload')
        if($campaignMode){$start.Notes+='crcampgn.ini as shipped (mapType campaign)'}
        $hasAuto=Test-Fresh $autoSave $start.Started
        $hasMenu=Test-Fresh $menuSave $start.Started
        if(-not $hasAuto){$start.Problems+="OpenShim autosave did not write Save\auto.sav"}
        if(-not $hasMenu){$start.Problems+="/saveafterload did not write Save\game1.sav"}
        if($start.Problems.Count){$start.Verdict='FAIL'}
        $results.Add($start)
        foreach($avenue in $Loads){
            $have=if($avenue -eq 'autoload'){$hasAuto}else{$hasMenu}
            if(-not $have){
                $results.Add([pscustomobject]@{Mission=$mission;Avenue=$avenue;Verdict='SKIP';Seconds=0;Pid=$null;Problems=@('no save from the start run');Notes=@();Started=$null})
                continue
            }
            $run=if($avenue -eq 'autoload'){
                Invoke-SaveLoadRun -Mission $mission -Avenue 'autoload' -Arguments $common -Environment @{OPENSHIM_FORCE_STARTUP_AUTOLOAD='1'}
            } else {
                Invoke-SaveLoadRun -Mission $mission -Avenue 'menuload' -Arguments (@('Save\game1.sav')+$common)
            }
            $results.Add($run)
        }
        Save-MissionSaves $mission
        foreach($r in @($results | Where-Object Mission -eq $mission)){
            Write-Output ("  {0,-8} {1,-4} {2}" -f $r.Avenue,$r.Verdict,(@($r.Problems)+@($r.Notes) -join '; '))
        }
    }
} catch {
    $failure=$_.ToString()
} finally {
    try {
        if($proc){$proc.Refresh(); if(-not $proc.HasExited){Stop-BZRGame -Id $proc.Id}}
        if($launched){
            foreach($file in @(Get-ChildItem -LiteralPath $saveRoot -File -Recurse)){
                $canonical=[IO.Path]::GetFullPath($file.FullName)
                if(-not $snapshot.ContainsKey($canonical)){
                    $copy=Join-Path (Join-Path $auditRoot 'leftover-saves') ([IO.Path]::GetRelativePath($saveRoot,$canonical))
                    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $copy) | Out-Null
                    Copy-Item -LiteralPath $canonical -Destination $copy
                    if((Get-FileHash -LiteralPath $canonical).Hash -ne (Get-FileHash -LiteralPath $copy).Hash){throw 'Save archival failed'}
                    Remove-Item -LiteralPath $canonical
                }
            }
        }
        $null=Restore-BZROrphanedOgreConfig -GameRoot $GameRoot
        foreach($original in $snapshot.Values){
            if($original.Existed){
                Copy-Item -LiteralPath $original.Backup -Destination $original.Path -Force
                if((Get-FileHash -LiteralPath $original.Path).Hash -ne $original.Hash){throw "Restore hash mismatch: $($original.Relative)"}
            } elseif(Test-Path -LiteralPath $original.Path){Remove-Item -LiteralPath $original.Path}
        }
        "Restored and verified $($snapshot.Count) snapshotted paths." | Tee-Object -FilePath (Join-Path $auditRoot 'restore.txt')
    } finally { Exit-BZRLaunchLock -Mutex $global:BZRAutoLock }
}

$results | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $auditRoot 'results.json')
$table=@('| Mission | Avenue | Verdict | Seconds | Details |','|---|---|---|---|---|')+@(foreach($r in $results){
    "| $($r.Mission) | $($r.Avenue) | $($r.Verdict) | $($r.Seconds) | $((@($r.Problems)+@($r.Notes)) -join '; ') |"
})
$table | Set-Content -LiteralPath (Join-Path $auditRoot 'results.md')
$failed=@($results | Where-Object Verdict -ne 'PASS')
$verdict=if($failure){"FAIL: harness error: $failure"}
    elseif($failed.Count){"FAIL: $($failed.Count) of $($results.Count) runs did not pass: " + (($failed | ForEach-Object { "$($_.Mission)/$($_.Avenue)" }) -join ', ')}
    else{"PASS: $($results.Count) runs across $(@($results.Mission | Select-Object -Unique).Count) mission(s); every start saved and every save loaded and ran."}
$verdict | Tee-Object -FilePath (Join-Path $auditRoot 'result.txt')
if($failure -or $failed.Count){exit 1}
