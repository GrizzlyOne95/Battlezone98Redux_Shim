# Load/first-use hitch attribution probe (copy of BZ_Native_Chunk_Pivots_20261003\run_pivot_probe.ps1).
# Adds: the native stack sampler (OPENSHIM_PROFILE_NATIVE_CPU), hashes of all
# three shim modules before and after, an optional cold microcode-cache arm,
# and a done-marker so the runner can be launched detached (via WMI) and
# polled from another shell.
param([ValidateSet('DX9','DX11')][string]$Renderer='DX9',[string]$Label='live-dx9',[int]$Seconds=110,[switch]$ColdShaderCache,[string[]]$ExtraEnv=@(),[ValidateSet('Normal','Minimized','Hidden')][string]$WindowStyle='Normal')
$ErrorActionPreference='Stop'
$gameRoot=[IO.Path]::GetFullPath('C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux')
$repoRoot='C:\Users\iestu\Documents\GIT\BZR-OpenShim'
$modRoot=Join-Path $gameRoot 'addon\ISDF Chronicles'
$sourceRoot='C:\Users\iestu\Documents\BZ_IA_MapPack\ProbeFixture\ISDF'
$evidence=Join-Path $PSScriptRoot $Label
$names=@('ncprobe.bzn','ncprobe.trn','ncprobe.hg2','ncprobe.mat','ncprobe.lgt','ncprobe.lua','ncprobe.ini','earthgood.dds','earthgood.material')
$modules=@('winmm.dll','bzloader.dll','plugins\openshim.dll','battlezone98redux.exe')
function Get-ModuleHashes { $h=[ordered]@{}; foreach($m in $modules){ $h[$m]=(Get-FileHash -LiteralPath (Join-Path $gameRoot $m)).Hash }; $h }
if(Get-Process battlezone98redux -ErrorAction SilentlyContinue){throw 'Another game is active'}
if(Test-Path -LiteralPath $evidence){throw 'Existing probe evidence'}
foreach($name in $names){
 if(Test-Path -LiteralPath (Join-Path $modRoot $name)){throw "Existing mod file: $name"}
 if(-not(Test-Path -LiteralPath (Join-Path $sourceRoot $name))){throw "Missing fixture: $name"}
}
. (Join-Path $repoRoot 'reverse_engineering\BZRHarness.ps1')
$lock=Enter-BZRLaunchLock -TimeoutSeconds 600
New-Item -ItemType Directory -Path $evidence | Out-Null
Start-Transcript -LiteralPath (Join-Path $evidence 'runner.transcript.txt') | Out-Null
$archive=Join-Path $evidence 'fixture'
New-Item -ItemType Directory -Path $archive | Out-Null
$selection=Join-Path $gameRoot 'modEnabled.dat'
$config=Join-Path $gameRoot 'ogre.cfg'
$originalSelection=[IO.File]::ReadAllBytes($selection)
$originalConfig=[IO.File]::ReadAllBytes($config)
[IO.File]::WriteAllBytes((Join-Path $evidence 'modEnabled.before.dat'),$originalSelection)
[IO.File]::WriteAllBytes((Join-Path $evidence 'ogre.before.cfg'),$originalConfig)
$hashesBefore=Get-ModuleHashes
$cacheDir=Join-Path $gameRoot 'shader_cache'
$cacheBackup=Join-Path $evidence 'shader_cache.backup'
$cacheMoved=$false
$launchUtc=$null
$created=@();$gameProc=$null;$extraNames=@()
try {
 foreach($name in $names){
  $path=Join-Path $modRoot $name
  Copy-Item -LiteralPath (Join-Path $sourceRoot $name) -Destination $path
  $created+=$path
 }
 Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'pivot_probe.lua') -Destination (Join-Path $modRoot 'ncprobe.lua') -Force
 if($ColdShaderCache -and (Test-Path -LiteralPath $cacheDir)){
  New-Item -ItemType Directory -Path $cacheBackup | Out-Null
  Get-ChildItem -LiteralPath $cacheDir -File | Copy-Item -Destination $cacheBackup
  Get-ChildItem -LiteralPath $cacheDir -File -Filter 'ogre_microcode.*' | Remove-Item
  $cacheMoved=$true
 }
 $env:BZR_FORCE_WINDOWED='1'
 $env:OPENSHIM_FORCE_STARTUP_AUTOLOAD='1'
 $env:OPENSHIM_CHUNK_LOG_BUDGET='16000'
 $env:OPENSHIM_CHUNK_TRACE_ENTRY_LIMIT='400'
 $env:OPENSHIM_PROFILE_NATIVE_CPU='1'
 $env:OPENSHIM_PROFILE_NATIVE_CPU_HZ='1000'
 $env:OPENSHIM_PROFILE_NATIVE_CPU_DEPTH='64'
 $env:OPENSHIM_PROFILE_NATIVE_CPU_LABEL=$Label
 $extraNames=@(); foreach($kv in $ExtraEnv){ $k,$v=$kv.Split('=',2); $extraNames+=$k; Set-Item -Path ('env:'+$k) -Value $v }
 $originalOgre=Set-BZROgreWindowed -GameRoot $gameRoot
 [IO.File]::WriteAllText($selection,$modRoot+"`r`n",[Text.UTF8Encoding]::new($false))
 $launchUtc=[DateTime]::UtcNow
 $gameProc=Start-Process -FilePath (Join-Path $gameRoot 'battlezone98redux.exe') -ArgumentList @('ncprobe.bzn','/nointro',('/renderer:'+$Renderer.ToLowerInvariant())) -WorkingDirectory $gameRoot -WindowStyle $WindowStyle -PassThru
 Write-Output "Started load-hitch probe PID=$($gameProc.Id)"
 for($i=0;$i -lt $Seconds;$i+=2){
  Start-Sleep -Seconds 2
  $gameProc.Refresh()
  if($gameProc.HasExited){throw "Probe exited early: $($gameProc.ExitCode)"}
 }
 Stop-BZRGame -Id $gameProc.Id -TimeoutSeconds 60
 $gameProc.Refresh()
 Write-Output "Exited with code $($gameProc.ExitCode)"
 $gameProc.ExitCode | Set-Content -LiteralPath (Join-Path $evidence 'exit-code.txt')
 $gameProc=$null
} finally {
 if($gameProc){Stop-BZRGame -Id $gameProc.Id -TimeoutSeconds 60}
 foreach($k in $extraNames){ Remove-Item -Path ('env:'+$k) -ErrorAction SilentlyContinue }
 [IO.File]::WriteAllBytes($selection,$originalSelection)
 [IO.File]::WriteAllBytes($config,$originalConfig)
 if($cacheMoved){
  Get-ChildItem -LiteralPath $cacheDir -File -Filter 'ogre_microcode.*' | ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination (Join-Path $evidence ('regenerated.'+$_.Name)); Remove-Item -LiteralPath $_.FullName }
  Get-ChildItem -LiteralPath $cacheBackup -File | Copy-Item -Destination $cacheDir
 }
 foreach($path in $created){
  $resolved=(Resolve-Path -LiteralPath $path).Path
  if(-not $resolved.StartsWith($modRoot+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Fixture outside mod'}
  Move-Item -LiteralPath $resolved -Destination $archive
 }
 foreach($name in @('openshim.log','BZLogger.txt','BZOgreLogfile.log','openshim_crash.log')){
  $path=Join-Path $gameRoot ('logs\'+$name)
  if(Test-Path -LiteralPath $path){Copy-Item -LiteralPath $path -Destination (Join-Path $evidence $name)}
 }
 if($launchUtc){
  Get-ChildItem -LiteralPath (Join-Path $gameRoot 'logs') -Filter ('openshim_cpu_samples_'+$Label+'_*.bin') |
   Where-Object { $_.LastWriteTimeUtc -ge $launchUtc } | Move-Item -Destination $evidence
 }
 $hashesAfter=Get-ModuleHashes
 [ordered]@{renderer=$Renderer;label=$Label;extraEnv=$ExtraEnv;coldShaderCache=[bool]$ColdShaderCache;launchUtc=$launchUtc;
  version=(Get-Item -LiteralPath (Join-Path $gameRoot 'plugins\openshim.dll')).VersionInfo.FileVersion;
  hashesBefore=$hashesBefore;hashesAfter=$hashesAfter;
  hashesStable=(($hashesBefore.Values -join ',') -eq ($hashesAfter.Values -join ','));
  session=(query session 2>&1 | Out-String)} | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $evidence 'metadata.json')
 Exit-BZRLaunchLock -Mutex $lock
 Stop-Transcript | Out-Null
 Set-Content -LiteralPath (Join-Path $evidence 'DONE') -Value ([DateTime]::UtcNow.ToString('o'))
}
Write-Output 'Original configuration and mod files restored'
