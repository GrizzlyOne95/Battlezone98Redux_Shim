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

# Shipping-default policy:
#
#   ON by default:
#     - crash prevention, stability fixes, and qualified Redux bug fixes unless
#       they can materially change mixed-client multiplayer behavior;
#     - qualified netcode fixes;
#     - the native keybind UI and OpenShim Settings UI.
#
#   OFF by default:
#     - every other enhancement, gameplay/presentation change, autosave,
#       diagnostic, experiment, convenience feature, or fix with unresolved /
#       material stock-vs-OpenShim multiplayer impact.
#
# Stock-preserving values may numerically look enabled (AllowStartupAutoLoad,
# SunFlashbang, Renderer=Auto), and numeric tuning values for disabled masters
# remain populated. The allowlist below is intentionally per-setting: there is
# no blanket [Fixes] exemption. Adding an entry is a shipping-policy decision,
# not a way to make this test pass.
$allowedEnabledLookingValues = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
@(
    # Stock-preserving values that merely read as ON/enabled-looking.
    "Startup/AllowStartupAutoLoad",
    "Graphics/Renderer",
    "Display/SunFlashbang",
    "Diagnostics/TerrainRenderProbeMaxClusters",

    # UI: the supported doors to every other setting.
    "General/SettingsUi",
    "General/CustomBindsUi",

    # Straight bug/stability fixes with no material mixed-client divergence.
    # MapRefreshFixes includes the multiplayer map-list refresh/jump and
    # selection-preservation repair and is deliberately part of the ON baseline.
    "General/MapRefreshFixes",
    "General/MusicGlobalFocus",
    "General/OgreMaterialCollisionGuard",
    "General/EditorOverheadPlacementOrder",

    # Qualified [Fixes] entries. The five simulation fixes below stand down in
    # network games; MagnetZeroRangeGuard is defensive; VehicleListModScoping
    # repairs asset lookup only; the CLI parser repair has no gameplay effect.
    "Fixes/ApcAlliedTargetDeploy",
    "Fixes/SplinterUndead",
    "Fixes/HowitzerUndeployedRetaliation",
    "Fixes/TugCargoPostLoad",
    "Fixes/ConstructorRemoteBuild",
    "Fixes/MagnetZeroRangeGuard",
    "Fixes/VehicleListModScoping",
    "Fixes/CliMultiParameterOptions",

    # Qualified socket/netcode baseline.
    "Network/NetImprovements",

    # Proven Redux regressions that are hard-disabled in network games.
    "SinglePlayer/JumpSnipeCrouch",
    "SinglePlayer/SatelliteVisibilityFix"
) | ForEach-Object { [void]$allowedEnabledLookingValues.Add($_) }

$enabledLookingTokens = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
@("1", "true", "on", "yes", "enabled", "enhanced", "auto") |
    ForEach-Object { [void]$enabledLookingTokens.Add($_) }

$playerValues = @{}
$unexpectedEnabledValues = @()
$section = ""
foreach ($line in Get-Content -LiteralPath $playerIni) {
    if ($line -match '^\s*\[([^\]]+)\]\s*$') {
        $section = $Matches[1].Trim()
        continue
    }
    if ($line -notmatch '^\s*([A-Za-z][A-Za-z0-9]*)\s*=\s*([^;]*?)\s*$') {
        continue
    }
    $key = $Matches[1]
    $value = $Matches[2].Trim()
    $id = "$section/$key"
    $playerValues[$id] = $value
    if ($enabledLookingTokens.Contains($value) -and
        -not $allowedEnabledLookingValues.Contains($id)) {
        $unexpectedEnabledValues += "$id = $value"
    }
}

if ($unexpectedEnabledValues.Count -gt 0) {
    Write-Host "Unexpected enabled-looking values in conservative openshim.ini:" -ForegroundColor Red
    $unexpectedEnabledValues | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
    throw "openshim.ini opt-in default policy failed"
}

# Exact stock-preserving baselines. These are not OpenShim features even when
# their values are non-zero/textual.
$stockValueChecks = @{
    "General/SoundChannels" = "0"
    "General/RawMouseInput" = "0"
    "Graphics/RenderProfile" = "Redux"
    "Display/UnderAttackAlert" = "Normal"
    "Display/TargetPolicy" = "Default"
    "Display/ScrapPilotHud" = "Stock"
    "Display/UnitVoFeedback" = "Normal"
    "Network/RoutePreference" = "Stock"
    "Network/LobbyBzrnetIntegration" = "0"
    "SinglePlayer/HeadlightColor" = "Stock"
    "SinglePlayer/HeadlightBeam" = "Stock"
}
foreach ($entry in $stockValueChecks.GetEnumerator()) {
    if (-not $playerValues.ContainsKey($entry.Key) -or
        $playerValues[$entry.Key] -cne $entry.Value) {
        $actual = if ($playerValues.ContainsKey($entry.Key)) {
            $playerValues[$entry.Key]
        } else {
            "<missing>"
        }
        throw "openshim.ini stock baseline mismatch: $($entry.Key) expected '$($entry.Value)', got '$actual'"
    }
}

# Lock the deliberate policy choices in both directions. This catches someone
# disabling a qualified fix as well as someone re-enabling an enhancement or a
# multiplayer-risk fix. Generic enabled-looking detection above remains the
# catch-all for newly added settings.
$shippingPolicyChecks = @{
    "General/CustomBindsUi" = "1"
    "General/SettingsUi" = "1"
    "General/MapRefreshFixes" = "1"
    "General/MusicGlobalFocus" = "1"
    "General/OgreMaterialCollisionGuard" = "1"
    "General/EditorOverheadPlacementOrder" = "1"

    "Fixes/AiMultiProducerMakers" = "0"
    "Fixes/ApcAlliedTargetDeploy" = "1"
    "Fixes/SplinterUndead" = "1"
    "Fixes/HowitzerUndeployedRetaliation" = "1"
    "Fixes/TugCargoPostLoad" = "1"
    "Fixes/ConstructorRemoteBuild" = "1"
    "Fixes/MagnetZeroRangeGuard" = "1"
    "Fixes/ProducerScriptPredicates" = "0"
    "Fixes/VehicleListModScoping" = "1"
    "Fixes/CliMultiParameterOptions" = "1"

    "DX11Enhanced/FXAA" = "0"
    "DX11Enhanced/EnhancedLightSelectionV2" = "0"
    "Display/MultiplayerFlags" = "0"
    "Network/NetImprovements" = "1"
    "Network/GovernorTuning" = "OpenShim"
    "Network/ReauthOnNicknameChange" = "0"
    "Network/LobbyReadouts" = "0"
    "Career/StatsTracking" = "0"
    "SinglePlayer/JumpSnipeCrouch" = "1"
    "SinglePlayer/AttackRevealPerceivedTeam" = "0"
    "SinglePlayer/SatelliteVisibilityFix" = "1"
}
foreach ($entry in $shippingPolicyChecks.GetEnumerator()) {
    if (-not $playerValues.ContainsKey($entry.Key) -or
        $playerValues[$entry.Key] -cne $entry.Value) {
        $actual = if ($playerValues.ContainsKey($entry.Key)) {
            $playerValues[$entry.Key]
        } else {
            "<missing>"
        }
        throw "openshim.ini shipping-policy mismatch: $($entry.Key) expected '$($entry.Value)', got '$actual'"
    }
}

Write-Host "player openshim.ini conservative shipping policy passed" -ForegroundColor Green

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
