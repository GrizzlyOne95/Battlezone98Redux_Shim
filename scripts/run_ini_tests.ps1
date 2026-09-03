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

# The shipped player preset is opt-in for anything that changes how the game
# plays or looks. Catch accidental regressions where such a key is re-enabled,
# while allowing the values that preserve stock behavior, one numeric count, and
# the four buckets that ship ON by policy:
#
#   UI          the settings page and the keybind page, because they are how a
#               player reaches every other switch without editing this file --
#               which the installer overwrites on each update anyway;
#   Netcode     the socket layer and the lobby/nickname readouts;
#   Bug fixes   defects with no gameplay intent (map-list refresh, the alt-tab
#               music dropout, the duplicate-material crash guard);
#   [Fixes]     see below.
#
# Everything else -- gameplay behavior, visual/audio enhancements, autosave,
# diagnostics, terrain development -- must stay OFF here and be opted into from
# the settings page. Adding a key to the allowlist below is a policy decision,
# not a way to make this test pass.
#
# [Fixes] is exempt as a section: those keys are confirmed Redux engine defects,
# not enhancements, so the opt-in policy does not apply to them -- they ship ON
# and exist only so an individual fix can be switched off for multiplayer parity
# or to bisect a suspected regression. A new key added there must still be
# documented in openshim.ini.example, which the completeness check above covers.
$allowedEnabledLookingSections = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
[void]$allowedEnabledLookingSections.Add("Fixes")

$allowedEnabledLookingValues = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
@(
    # Stock-preserving values that merely read as ON.
    "Startup/AllowStartupAutoLoad",
    "Graphics/Renderer",
    "Display/SunFlashbang",
    "Diagnostics/TerrainRenderProbeMaxClusters",

    # UI: the doors to every other setting.
    "General/SettingsUi",
    "General/CustomBindsUi",

    # Straight bug fixes with no gameplay intent.
    "General/MapRefreshFixes",
    "General/MusicGlobalFocus",
    "General/OgreMaterialCollisionGuard",

    # Netcode improvements. NetImprovements is the wholesale opt-out, so it has
    # to ship ON for the others under it to mean anything.
    "Network/NetImprovements",
    "Network/LiveNicknameKeys",
    "Network/LobbyReadouts",

    # Restores the BZ 1.5 overhead-view / control-panel display order. Only
    # reachable in a session launched with /edit, so it changes nothing for a
    # player who is not using the editor.
    "General/EditorOverheadPlacementOrder",

    # Master switch for OpenShim multiplayer vehicle flags. ON is the shipped
    # feature; OFF removes OpenShim flag work entirely, so it is the opt-out
    # rather than the opt-in.
    "Display/MultiplayerFlags",

    # Career statistics. Native multiplayer kill/death recording previously ran
    # unconditionally, with no key at all, so this key is the opt-OUT for
    # behavior every existing install already has -- shipping it 0 would be a
    # silent regression rather than a conservative default. Same shape as
    # NetImprovements and MultiplayerFlags above. It is observational: one
    # local text file, no gameplay, visual, audio or network effect.
    "Career/StatsTracking",

    # [DX11Enhanced] is gated behind Graphics/RenderProfile, which this same
    # script pins to Redux below. Both keys are inert until a player opts into
    # the Enhanced profile on DX11; pre-arming them means that opt-in gets the
    # whole Enhanced feature set rather than a half-configured one.
    "DX11Enhanced/FXAA",
    "DX11Enhanced/EnhancedLightSelectionV2"
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
        -not $allowedEnabledLookingSections.Contains($section) -and
        -not $allowedEnabledLookingValues.Contains($id)) {
        $unexpectedEnabledValues += "$id = $value"
    }
}

if ($unexpectedEnabledValues.Count -gt 0) {
    Write-Host "Unexpected enabled-looking values in conservative openshim.ini:" -ForegroundColor Red
    $unexpectedEnabledValues | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
    throw "openshim.ini opt-in default policy failed"
}

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

Write-Host "player openshim.ini conservative defaults passed" -ForegroundColor Green

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
