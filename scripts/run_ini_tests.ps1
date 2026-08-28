# Builds and runs the openshim.ini writer unit tests with the VS 2022 x86
# toolchain. No engine or game install required.
#
#   powershell -ExecutionPolicy Bypass -File scripts\run_ini_tests.ps1

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
$out = Join-Path $repo "bin\tests"
New-Item -ItemType Directory -Force $out | Out-Null

# Keep the shipped player preset synchronized with the authoritative reference.
# This intentionally checks section/key presence rather than values: the player
# file is allowed to choose friendly defaults that differ from conservative or
# diagnostic defaults in openshim.ini.example, but no first-class knob should
# disappear from the user-editable preset as new settings are added.
function Get-OpenShimIniSettingIds {
    param(
        [Parameter(Mandatory = $true)][string]$Path,
        [switch]$ReferenceMode
    )

    $ids = [System.Collections.Generic.HashSet[string]]::new(
        [System.StringComparer]::OrdinalIgnoreCase)
    $section = ""
    $commentedFirstClassKeys = @(
        "TerrainProxyZoneX",
        "TerrainProxyZoneZ",
        "TerrainProxyClusterX",
        "TerrainProxyClusterZ",
        "Nickname"
    )

    foreach ($line in Get-Content -LiteralPath $Path) {
        if ($line -match '^\s*\[([^\]]+)\]\s*$') {
            $section = $Matches[1].Trim()
            continue
        }

        $candidate = $line
        $commented = $false
        if ($candidate -match '^\s*;(.*)$') {
            $commented = $true
            $candidate = $Matches[1]
        }

        if ($candidate -notmatch '^\s*([A-Za-z][A-Za-z0-9]*)\s*=') {
            continue
        }

        $key = $Matches[1]
        if ($commented) {
            if (-not $ReferenceMode -or $commentedFirstClassKeys -notcontains $key) {
                continue
            }
        }

        # Raw compatibility/probe variables under [Environment] are intentionally
        # excluded; the player preset exposes canonical first-class settings, not
        # every historical OPENSHIM_* / BZR_* alias.
        if ($key -like 'OPENSHIM_*' -or $key -like 'BZR_*') {
            continue
        }

        # Preset revision marker is metadata, not a first-class runtime setting.
        # It is carried as a machine-readable comment (e.g. "; OpenShimPresetRevision = 2")
        # near the top of the player preset so migration tooling can identify the
        # revision without teaching the runtime to parse it as a configurable key.
        if ($key -ieq 'OpenShimPresetRevision') {
            continue
        }

        if (-not $section) {
            continue
        }

        [void]$ids.Add("$section/$key")
    }

    return ,$ids
}

$referenceIni = Join-Path $repo "openshim.ini.example"
$playerIni = Join-Path $repo "openshim.ini"
if (-not (Test-Path -LiteralPath $referenceIni -PathType Leaf)) {
    throw "authoritative OpenShim INI reference not found: $referenceIni"
}
if (-not (Test-Path -LiteralPath $playerIni -PathType Leaf)) {
    throw "shipped player OpenShim INI not found: $playerIni"
}

$referenceIds = Get-OpenShimIniSettingIds -Path $referenceIni -ReferenceMode
$playerIds = Get-OpenShimIniSettingIds -Path $playerIni
$missing = @($referenceIds | Where-Object { -not $playerIds.Contains($_) } | Sort-Object)
$extra = @($playerIds | Where-Object { -not $referenceIds.Contains($_) } | Sort-Object)

if ($missing.Count -gt 0 -or $extra.Count -gt 0) {
    if ($missing.Count -gt 0) {
        Write-Host "Missing from openshim.ini:" -ForegroundColor Red
        $missing | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
    }
    if ($extra.Count -gt 0) {
        Write-Host "Not documented as first-class in openshim.ini.example:" -ForegroundColor Red
        $extra | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
    }
    throw "openshim.ini first-class setting set does not match openshim.ini.example"
}

Write-Host "player openshim.ini completeness passed ($($referenceIds.Count) settings)" -ForegroundColor Green

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vsroot = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $vsroot) { throw "Visual Studio with C++ tools not found" }

$vcvars = Join-Path $vsroot "VC\Auxiliary\Build\vcvars32.bat"
$exe = Join-Path $out "ini_writer_tests.exe"

cmd /c "`"$vcvars`" >nul && cl /nologo /std:c++17 /EHsc /W4 /WX /I `"$repo\include`" `"$repo\tests\ini_writer_tests.cpp`" `"$repo\src\patches\openshim_ini.cpp`" /Fe:`"$exe`" /Fo:`"$out\\`""
if ($LASTEXITCODE -ne 0) { throw "test build failed" }

& $exe
if ($LASTEXITCODE -ne 0) { throw "ini writer tests FAILED" }
Write-Host "ini writer tests passed" -ForegroundColor Green

# --- Preset migration tests (covers revision/migration framework) ---
$exe2 = Join-Path $out "openshim_preset_migration_tests.exe"
cmd /c "`"$vcvars`" >nul && cl /nologo /std:c++17 /EHsc /W4 /WX /I `"$repo\include`" `"$repo\tests\openshim_preset_migration_tests.cpp`" `"$repo\src\patches\openshim_ini.cpp`" `"$repo\src\patches\openshim_preset_migration.cpp`" bcrypt.lib /Fe:`"$exe2`" /Fo:`"$out\\`""
if ($LASTEXITCODE -ne 0) { throw "preset migration test build failed" }

& $exe2
if ($LASTEXITCODE -ne 0) { throw "preset migration tests FAILED" }
Write-Host "preset migration tests passed" -ForegroundColor Green
