<#
.SYNOPSIS
    Profiler-disabled PresentMon A/B between two OpenShim builds.

.DESCRIPTION
    Phase 2 needs to state a frame-time result for a change to the shim itself,
    which means the only thing allowed to differ between the two arms is the
    shim binary. This swaps winmm.dll between runs and drives the existing
    benchmark runner with the CPU sampler off and PresentMon on, so the numbers
    it produces are external ETW frame times rather than instrumented ones.

    Arms are interleaved (A B A B ...) rather than grouped, because a machine
    that warms or throttles during a session would otherwise put its drift
    entirely into whichever arm ran second.

.PARAMETER Arm
    Ordered pairs of "label=path-to-winmm.dll".
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [Parameter(Mandatory = $true)]
    [string[]]$Arm,
    [string[]]$Scenario = @("fourteam", "fourteam_fire"),
    [ValidateSet("DX11", "DX9")]
    [string]$Renderer = "DX11",
    [int]$Count = 80,
    [double]$Distance = 400.0,
    [int]$Repeats = 3,
    [double]$WarmupSeconds = 6.0,
    [double]$MeasureSeconds = 15.0,
    [string]$OutputRoot = (Join-Path $PSScriptRoot "snapshots\phase2_shim_ab")
)

$ErrorActionPreference = "Stop"
$runner = Join-Path $PSScriptRoot "run_live_combat_benchmark.ps1"
$target = Join-Path $GameRoot "winmm.dll"

$arms = @()
foreach ($entry in $Arm) {
    $parts = $entry.Split("=", 2)
    if ($parts.Count -ne 2) { throw "Arm must be label=path: $entry" }
    if (-not (Test-Path -LiteralPath $parts[1])) { throw "Missing shim: $($parts[1])" }
    $arms += [pscustomobject]@{
        Label = $parts[0]
        Path = (Resolve-Path -LiteralPath $parts[1]).Path
        Hash = (Get-FileHash -LiteralPath $parts[1]).Hash
    }
}

$original = Join-Path $OutputRoot "winmm.original.dll"
New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null
Copy-Item -LiteralPath $target -Destination $original -Force
Write-Host "Saved current shim to $original"

try {
    for ($repeat = 1; $repeat -le $Repeats; $repeat++) {
        foreach ($armEntry in $arms) {
            Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
                Stop-Process -Force
            Start-Sleep -Seconds 1
            # The game can still hold winmm.dll open for a second or two after
            # its process object reports exit, and a Copy-Item that fails there
            # leaves the PREVIOUS arm's binary in place. That produces a fully
            # populated capture directory labelled with the wrong arm, which is
            # indistinguishable from a real null result -- so retry, then verify
            # the deployed hash and refuse to run the arm if it does not match.
            $swapped = $false
            for ($attempt = 1; $attempt -le 15 -and -not $swapped; $attempt++) {
                try {
                    Copy-Item -LiteralPath $armEntry.Path -Destination $target `
                        -Force -ErrorAction Stop
                    $swapped = $true
                } catch {
                    Start-Sleep -Seconds 2
                }
            }
            if (-not $swapped) {
                throw "Could not replace $target with arm $($armEntry.Label)"
            }
            $deployed = (Get-FileHash -LiteralPath $target).Hash
            if ($deployed -ne $armEntry.Hash) {
                throw "Deployed shim hash does not match arm $($armEntry.Label)"
            }
            Write-Host "=== repeat $repeat arm $($armEntry.Label) sha256=$($deployed.Substring(0,16)) ==="
            & $runner -GameRoot $GameRoot `
                -OutputRoot (Join-Path $OutputRoot ("{0}_r{1}" -f $armEntry.Label, $repeat)) `
                -Renderer $Renderer -Scenario $Scenario -Count @($Count) `
                -Distance @($Distance) -WarmupSeconds $WarmupSeconds `
                -MeasureSeconds $MeasureSeconds -ProfilerDisabled `
                -ExternalPresentMon -KillExisting -RunTimeoutSeconds 90 | Out-Null
        }
    }
}
finally {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force
    Copy-Item -LiteralPath $original -Destination $target -Force
    Write-Host "Restored original shim"
}

Write-Host "A/B session complete: $OutputRoot"
$OutputRoot
