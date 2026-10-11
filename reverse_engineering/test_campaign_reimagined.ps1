<#
.SYNOPSIS
Runs a bounded Campaign Reimagined smoke and restores saves, configuration,
mod selection, and any temporarily deployed OpenShim files.
.DESCRIPTION
Run in a separate pwsh process. Uses BZRHarness's machine-wide launch lock,
windowed mode, and graceful shutdown. The label must be new: evidence and
backups are never overwritten. Only CR is enabled during the test. Use a
mission basename; the engine's map-name buffer truncates directory paths.
This is a startup/exit smoke, not a campaign playthrough or release gate.
Ogre warnings require review in the captured BZOgreLogfile.log.
For direct Steam launches with the client running, set SteamAppId, SteamGameId
and SteamOverlayGameId to 301650 in the calling process. Stock Steam engine
logs can remain at the game root; both log locations are captured.
Use -ModContainer packaged_mods for a local candidate under the Steam game.
With -MenuStart, activate the local candidate and select the mission through
the game menu. The harness allows five minutes for selection, then requires
40 seconds of simulation before applying the same native-path checks.
.EXAMPLE
pwsh -NoProfile -File reverse_engineering/test_campaign_reimagined.ps1 `
  -Label main-dx11 -EvidenceDirectory C:\Temp\cr-validation `
  -ShimRepo C:\src\BZR-OpenShim -Renderer dx11
#>
#requires -Version 7.0
[CmdletBinding()]
param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9_-]+$')][string]$Label,
    [Parameter(Mandatory)][string]$EvidenceDirectory,
    [string]$GameRoot='C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [ValidateSet('mods','addon','packaged_mods')][string]$ModContainer='mods',
    [string]$ShimRepo,
    [ValidateSet('dx9','dx11')][string]$Renderer='dx11',
    [ValidatePattern('^[A-Za-z0-9_-]+\.bzn$')][string]$Mission='misn02b.bzn',
    [switch]$SetupOnly,
    [switch]$MenuStart
)
$ErrorActionPreference='Stop'
$GameRoot=(Resolve-Path -LiteralPath $GameRoot).Path.TrimEnd('\')
$auditCampaignRoot=Join-Path $GameRoot ($ModContainer+'\3686673790')
$auditRoot=Join-Path ([IO.Path]::GetFullPath($EvidenceDirectory)) $Label
if($auditRoot.StartsWith($GameRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Evidence must be outside the game installation'}
if(Test-Path -LiteralPath $auditRoot){throw 'Use a new label; never overwrite evidence'}
New-Item -ItemType Directory -Path $auditRoot | Out-Null
$auditSnapshot=[Collections.Generic.Dictionary[string,object]]::new([StringComparer]::OrdinalIgnoreCase)
$auditProc=$null
$auditFailure=$null
$auditGameLaunched=$false
$auditSaveRoot=[IO.Path]::GetFullPath((Join-Path $GameRoot 'save'))
function Save-AuditFile([string]$Path) {
    $canonical=[IO.Path]::GetFullPath($Path)
    if($auditSnapshot.ContainsKey($canonical)){return}
    if(-not $canonical.StartsWith($GameRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Backup path outside game root'}
    $relative=[IO.Path]::GetRelativePath($GameRoot,$canonical)
    $backup=Join-Path (Join-Path $auditRoot 'before') $relative
    $exists=Test-Path -LiteralPath $canonical -PathType Leaf
    if($exists){
        New-Item -ItemType Directory -Force -Path (Split-Path -Parent $backup) | Out-Null
        Copy-Item -LiteralPath $canonical -Destination $backup
    }
    $auditSnapshot.Add($canonical,[pscustomobject]@{Path=$canonical;Relative=$relative;Backup=$backup;Existed=$exists;Hash=$(if($exists){(Get-FileHash -LiteralPath $canonical).Hash}else{$null})})
}
function Copy-AuditLogs([string[]]$Names) {
    foreach($name in $Names){
        $paths=@((Join-Path (Join-Path $GameRoot 'logs') $name),(Join-Path $GameRoot $name))
        $file=@(foreach($path in $paths){if(Test-Path -LiteralPath $path -PathType Leaf){Get-Item -LiteralPath $path}}) |
            Sort-Object LastWriteTime -Descending | Select-Object -First 1
        if($file){Copy-Item -LiteralPath $file.FullName -Destination (Join-Path $auditRoot $name) -Force}
    }
}
if(Get-Process battlezone98redux -ErrorAction SilentlyContinue){throw 'Another game session is active'}
$env:BZR_FORCE_WINDOWED='1'
$env:OPENSHIM_FORCE_STARTUP_AUTOLOAD='1'
# Preserve the configuration before the shared harness forces windowed mode.
Save-AuditFile (Join-Path $GameRoot 'ogre.cfg')
. (Join-Path $PSScriptRoot 'BZRHarness.ps1')
try {
    if(Get-Process battlezone98redux -ErrorAction SilentlyContinue){throw 'Another game session is active'}
    foreach($file in Get-ChildItem -LiteralPath $auditSaveRoot -File -Recurse){Save-AuditFile $file.FullName}
    foreach($relative in @('openshim.ini','net.ini','modEnabled.dat','campaignReimagined_settings.cfg','career_stats.cfg','winmm.dll','bzloader.dll','plugins\openshim.dll','scripts\patches.json','openshim\OpenShimAssets.ini',
        'openshim_update.status','winmm.dll.previous','bzloader.dll.previous','plugins\openshim.dll.previous','net.ini.previous','scripts\patches.json.previous',
        "$ModContainer\3686673790\winmm.dll","$ModContainer\3686673790\exu.dll","$ModContainer\3686673790\bzfile.dll","$ModContainer\3686673790\bzfile_replace_helper.exe")){
        Save-AuditFile (Join-Path $GameRoot $relative)
    }
    if($ShimRepo){
        foreach($pair in @(@('resources\renderer\enhanced','openshim\renderer\enhanced'),@('resources\ui\custom_widgets','BZ_ASSETS_CORE\common\ui\CustomWidgets'))){
            foreach($file in Get-ChildItem -LiteralPath (Join-Path $ShimRepo $pair[0]) -File){Save-AuditFile (Join-Path (Join-Path $GameRoot $pair[1]) $file.Name)}
        }
    }
    @($auditSnapshot.Values) | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $auditRoot 'before.json')
    [IO.File]::WriteAllText((Join-Path $GameRoot 'modEnabled.dat'),$auditCampaignRoot+"`r`n",[Text.UTF8Encoding]::new($false))
    if($ShimRepo){
        & pwsh -NoProfile -File (Join-Path $ShimRepo 'scripts\Deploy-OpenShim.ps1') -GameDir $GameRoot *> (Join-Path $auditRoot 'deploy.log')
        if($LASTEXITCODE -ne 0){throw 'Complete-chain deployment failed'}
    }
    $ogre=Join-Path $GameRoot 'ogre.cfg'
    $renderName=if($Renderer -eq 'dx11'){'Direct3D11 Rendering Subsystem'}else{'Direct3D9 Rendering Subsystem'}
    [IO.File]::WriteAllText($ogre,([IO.File]::ReadAllText($ogre)-replace '(?m)^Render System=.*$',"Render System=$renderName"))
    $auditArtifacts=@(foreach($relative in @('battlezone98redux.exe','winmm.dll','bzloader.dll','plugins\openshim.dll','scripts\patches.json',"$ModContainer\3686673790\exu.dll","$ModContainer\3686673790\bzfile.dll")){
        $p=Join-Path $GameRoot $relative
        [pscustomobject]@{Path=$relative;Sha256=(Get-FileHash -LiteralPath $p).Hash}
    })
    $auditArtifacts | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $auditRoot 'artifacts.json')
    $auditDumpsBefore=@(Get-ChildItem -LiteralPath (Join-Path $GameRoot 'logs') -Filter '*.dmp' -File | ForEach-Object FullName)
    $auditStarted=Get-Date
    $launchArguments=if($MenuStart){@('/nointro',"/renderer:$Renderer")}else{@($Mission,'/nointro',"/renderer:$Renderer")}
    Assert-BZRSafeToLaunch
    $auditProc=Start-BZRGameProcess -FilePath (Join-Path $GameRoot 'battlezone98redux.exe') -ArgumentList $launchArguments -WorkingDirectory $GameRoot -WindowStyle Hidden -PassThru
    $auditGameLaunched=$true
    [pscustomobject]@{Pid=$auditProc.Id;Started=$auditStarted.ToString('o');Mission=$Mission;Renderer=$Renderer;ShimRepo=$ShimRepo;EnabledMod=$auditCampaignRoot;MenuStart=[bool]$MenuStart} |
        ConvertTo-Json | Set-Content -LiteralPath (Join-Path $auditRoot 'run.json')
    Write-Output "Started $Label PID=$($auditProc.Id) mission=$Mission renderer=$Renderer"
    if($MenuStart){
        Write-Output 'Activate the intended local campaign and select its mission in the game menu (five-minute limit).'
        $simulationObserved=$false
        for($i=0;$i -lt 150;$i++){
            Start-Sleep -Seconds 2
            $auditProc.Refresh()
            if($auditProc.HasExited){throw "Game exited during menu selection (exit $($auditProc.ExitCode))"}
            foreach($path in @((Join-Path $GameRoot 'BZLogger.txt'),(Join-Path $GameRoot 'logs\BZLogger.txt'))){
                if((Test-Path -LiteralPath $path) -and (Get-Item -LiteralPath $path).LastWriteTime -ge $auditStarted -and
                    (Select-String -LiteralPath $path -SimpleMatch 'Game Simulation Initialized' -Quiet)){$simulationObserved=$true;break}
            }
            if($simulationObserved){break}
        }
        if(-not $simulationObserved){throw 'No simulation was selected within five minutes.'}
        (Get-Date).ToString('o') | Set-Content -LiteralPath (Join-Path $auditRoot 'simulation-observed.txt')
    }
    for($i=0;$i -lt 20;$i++){
        Start-Sleep -Seconds 2
        $auditProc.Refresh()
        if($auditProc.HasExited){throw "Game exited before the 40-second smoke completed (exit $($auditProc.ExitCode))"}
    }
    $auditModules=@($auditProc.Modules | Where-Object ModuleName -Match 'winmm|bzloader|openshim|exu|bzfile|RenderSystem' | Select-Object ModuleName,FileName)
    $auditModules | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $auditRoot 'modules.json')
    Stop-BZRGame -Id $auditProc.Id
    $auditProc=$null
    foreach($helper in @(Get-Process bzfile_replace_helper -ErrorAction SilentlyContinue)){
        if($helper.StartTime -ge $auditStarted){Wait-Process -Id $helper.Id -Timeout 45 -ErrorAction Stop}
    }
    $status=Join-Path $GameRoot 'openshim_update.status'
    if(Test-Path -LiteralPath $status){Copy-Item -LiteralPath $status -Destination (Join-Path $auditRoot 'openshim_update.status')}
    Copy-AuditLogs @('BZLogger.txt','openshim.log','exu.log','BZOgreLogfile.log','openshim_crash.log','openpatch_setup.log','openshim_update.log')
    $auditNewDumps=@(Get-ChildItem -LiteralPath (Join-Path $GameRoot 'logs') -Filter '*.dmp' -File | Where-Object { $auditDumpsBefore -notcontains $_.FullName })
    @($auditNewDumps.FullName) | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $auditRoot 'new-dumps.json')
    foreach($artifact in $auditArtifacts){
        if((Get-FileHash -LiteralPath (Join-Path $GameRoot $artifact.Path)).Hash -ne $artifact.Sha256){throw "Artifact changed during test: $($artifact.Path)"}
    }
    $nativeModules=if($SetupOnly){@('bzfile.dll')}else{@('exu.dll','bzfile.dll')}
    foreach($native in $nativeModules){
        $expected=[IO.Path]::GetFullPath((Join-Path $auditCampaignRoot $native))
        if(-not ($auditModules | Where-Object { $_.ModuleName -ieq $native -and [IO.Path]::GetFullPath($_.FileName) -ieq $expected })){throw "Campaign native module not loaded from the campaign folder: $native"}
    }
    foreach($required in (@('bzloader.dll','openshim.dll')+$nativeModules)){
        if($auditModules.ModuleName -notcontains $required){throw "Required module did not load: $required"}
    }
    $bzlog=Join-Path $auditRoot 'BZLogger.txt'
    if((Get-Item -LiteralPath $bzlog).LastWriteTime -lt $auditStarted){throw 'Stale game log'}
    if(-not (Select-String -LiteralPath $bzlog -SimpleMatch 'Game Simulation Initialized' -Quiet)){throw 'Campaign simulation initialization not observed'}
    if(-not (Select-String -LiteralPath $bzlog -SimpleMatch 'Exiting Game With Return Code 0' -Quiet)){throw 'Clean engine exit was not observed'}
    if(Select-String -LiteralPath $bzlog -Pattern 'Lua Error|Error in Lua|Error in Update|Error loading|Could not load' -Quiet){throw 'Campaign reported a Lua/load error'}
    if(Select-String -LiteralPath (Join-Path $auditRoot 'openshim.log') -SimpleMatch '[STALE-CONFIG]' -Quiet){throw 'Stale patch registration'}
    if($auditNewDumps.Count){throw "Shutdown created $($auditNewDumps.Count) crash dump(s): $($auditNewDumps.Name -join ', ')"}
    $auditVerdict='PASS: 40-second process run with campaign initialization and clean engine exit; campaign native modules loaded; no new dumps, Lua errors, or artifact changes.'
} catch {
    $auditFailure=$_.ToString()
    $auditVerdict="FAIL: $auditFailure"
} finally {
    try {
        if($auditProc -and -not $auditProc.HasExited){Stop-BZRGame -Id $auditProc.Id}
        if($auditGameLaunched){
            # Keep fresh logs even when startup failed before the normal capture.
            Copy-AuditLogs @('BZLogger.txt','openshim.log','exu.log','BZOgreLogfile.log','openshim_crash.log')
            $newDumps=@(Get-ChildItem -LiteralPath (Join-Path $GameRoot 'logs') -Filter '*.dmp' -File | Where-Object { $auditDumpsBefore -notcontains $_.FullName })
            @($newDumps.FullName) | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $auditRoot 'new-dumps.json')
        }
        # Copy new saves to evidence; remove only individually verified paths
        # absent from the canonical pre-launch snapshot. Never move old saves.
        if($auditGameLaunched){
            foreach($file in @(Get-ChildItem -LiteralPath $auditSaveRoot -File -Recurse)){
                $canonical=[IO.Path]::GetFullPath($file.FullName)
                if(-not $canonical.StartsWith($auditSaveRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Unexpected save path'}
                if(-not $auditSnapshot.ContainsKey($canonical)){
                    $relative=[IO.Path]::GetRelativePath($auditSaveRoot,$canonical)
                    $copy=Join-Path (Join-Path $auditRoot 'created-saves') $relative
                    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $copy) | Out-Null
                    Copy-Item -LiteralPath $canonical -Destination $copy
                    if((Get-FileHash -LiteralPath $canonical).Hash -ne (Get-FileHash -LiteralPath $copy).Hash){throw 'New save archival failed'}
                    Remove-Item -LiteralPath $canonical
                }
            }
        }
        $null=Restore-BZROrphanedOgreConfig -GameRoot $GameRoot
        foreach($original in $auditSnapshot.Values){
            if($original.Existed){
                Copy-Item -LiteralPath $original.Backup -Destination $original.Path -Force
                if((Get-FileHash -LiteralPath $original.Path).Hash -ne $original.Hash){throw "Restore hash mismatch: $($original.Relative)"}
            } elseif(Test-Path -LiteralPath $original.Path){Remove-Item -LiteralPath $original.Path}
        }
        "Restored and verified $($auditSnapshot.Count) snapshotted paths; save files remaining=$(@(Get-ChildItem -LiteralPath $auditSaveRoot -File -Recurse).Count)." | Tee-Object -FilePath (Join-Path $auditRoot 'restore.txt')
    } finally { Exit-BZRLaunchLock -Mutex $global:BZRAutoLock }
}
$auditVerdict | Tee-Object -FilePath (Join-Path $auditRoot 'result.txt')
if($auditFailure){exit 1}
