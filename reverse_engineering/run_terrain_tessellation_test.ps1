[CmdletBinding()]
param(
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [string]$Mission = 'misn04.bzn',
    [ValidateSet(1, 2, 4)][int]$Factor = 2,
    [switch]$Wireframe,
    [switch]$MicroRelief,
    [ValidateRange(0, 1)][float]$ReliefAmplitude = 0.25,
    [switch]$Editor,
    [ValidateRange(10, 120)][int]$RunSeconds = 45,
    [switch]$Deploy
)
$ErrorActionPreference = 'Stop'
if (Get-Process -Name battlezone98redux -ErrorAction SilentlyContinue) {
    throw 'A game is already running; finish that session before this test.'
}
$savedWindowed = $env:BZR_FORCE_WINDOWED
$env:BZR_FORCE_WINDOWED = '1'
. "$PSScriptRoot\BZRHarness.ps1"
if (Get-Process -Name battlezone98redux -ErrorAction SilentlyContinue) {
    throw 'A game is already running; finish that session before this test.'
}
$repo = Split-Path -Parent $PSScriptRoot
$output = Join-Path $repo ("build\terrain-tessellation\run-" + (Get-Date -Format 'yyyyMMdd-HHmmss') + "-f$Factor")
New-Item -ItemType Directory -Force -Path $output | Out-Null
$variables = @{
    OPENSHIM_TERRAIN_TESSELLATION_TEST = '1'
    OPENSHIM_TERRAIN_TESSELLATION_FACTOR = "$Factor"
    OPENSHIM_TERRAIN_TESSELLATION_WIREFRAME = $(if ($Wireframe) { '1' } else { '0' })
    OPENSHIM_TERRAIN_MICRO_RELIEF_TEST = $(if ($MicroRelief) { '1' } else { '0' })
    OPENSHIM_TERRAIN_MICRO_RELIEF_AMPLITUDE = $ReliefAmplitude.ToString('R', [Globalization.CultureInfo]::InvariantCulture)
}
$saved = @{}
$process = $null
try {
    if ($Deploy) {
        & "$PSScriptRoot\..\scripts\Deploy-OpenShim.ps1" -GameDir $GameRoot
    }
    foreach ($key in $variables.Keys) {
        $saved[$key] = [Environment]::GetEnvironmentVariable($key, 'Process')
        [Environment]::SetEnvironmentVariable($key, $variables[$key], 'Process')
    }
    $arguments = @($Mission, '-renderer:dx11')
    if ($Editor) { $arguments += '/edit' }
    # This is the interactive visual test window, not a background helper.
    $launch = @{
        FilePath = (Join-Path $GameRoot 'battlezone98redux.exe')
        ArgumentList = $arguments
        WorkingDirectory = $GameRoot
        PassThru = $true
    }
    $process = Start-Process @launch
    Write-Host "Terrain test PID=$($process.Id), factor=$Factor, wireframe=$Wireframe, microRelief=$MicroRelief, amplitude=$ReliefAmplitude. Press Space if the mission waits for briefing."
    $deadline = (Get-Date).AddSeconds($RunSeconds)
    while ((Get-Date) -lt $deadline -and -not $process.HasExited) {
        Start-Sleep -Milliseconds 500
        $process.Refresh()
    }
}
finally {
    if ($process) { Stop-BZRGame -Id $process.Id }
    $null = Restore-BZROrphanedOgreConfig -GameRoot $GameRoot
    $env:BZR_FORCE_WINDOWED = $savedWindowed
    foreach ($key in $saved.Keys) {
        [Environment]::SetEnvironmentVariable($key, $saved[$key], 'Process')
    }
}
$records = @()
foreach ($name in 'openshim.log', 'BZOgreLogfile.log', 'BZLogger.txt') {
    $source = Join-Path (Join-Path $GameRoot 'logs') $name
    if (Test-Path -LiteralPath $source) {
        Copy-Item -LiteralPath $source -Destination (Join-Path $output $name)
        if ($name -eq 'openshim.log') {
            # PID selection prevents an earlier session from supplying a pass.
            $records = @(Get-Content -LiteralPath $source |
                Where-Object { $_ -match ("\[pid:" + $process.Id + " ") })
        }
    }
}
$evidence = @($records | Where-Object { $_ -match '\[TERRAIN-TESS\]' })
$evidence | Set-Content -LiteralPath (Join-Path $output 'evidence.txt')
$evidence | ForEach-Object { Write-Host $_ }
$proved = @($evidence | Where-Object {
    $_ -match 'GPU statistics tessellated=1' -and
    $_ -match 'iaPrimitives=12800 ' -and
    $_ -match 'hsInvocations=[1-9][0-9]*' -and
    $_ -match 'dsInvocations=[1-9][0-9]*' -and
    [uint64]([regex]::Match($_, 'psInvocations=([0-9]+)').Groups[1].Value) -ge 1024 -and
    [uint64]([regex]::Match($_, 'clipPrimitives=([0-9]+)').Groups[1].Value) -ge 128
}).Count -gt 0
$restored = @($evidence | Where-Object { $_ -match 'shared material restored' }).Count -gt 0
if ($MicroRelief -and $ReliefAmplitude -gt 0) {
    $boundsRestored = @($evidence | Where-Object {
        $_ -match 'micro-relief render bounds restored meshes=([0-9]+) tracked=([0-9]+)' -and
        [int]$Matches[1] -gt 0 -and $Matches[1] -eq $Matches[2]
    }).Count -gt 0
    $restored = $restored -and $boundsRestored
}
$process.Refresh()
$cleanExit = $process.HasExited -and $process.ExitCode -eq 0
Write-Host "Evidence saved to $output"
if (-not ($proved -and $restored -and $cleanExit)) {
    throw "Submission test failed: GPU proof=$proved, restored=$restored, cleanExit=$cleanExit. Inspect the fresh-session logs."
}
Write-Host 'PASS: tessellation submission, rasterization and clean restoration. Camera-motion and terrain-contact acceptance require visual checks.'
