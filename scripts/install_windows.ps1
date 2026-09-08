# One-line Windows installer. Paste from the README into PowerShell:
#   irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_windows.ps1 | iex
#
# Downloads ONE versioned release bundle, OpenShim-Suite.zip, verifies it
# against the published SHA-256, and deploys the whole compatibility set:
# winmm.dll, scripts\patches.json, openshim.ini, net.ini, the mandatory Enhanced
# renderer resources, and the custom UI widget tiles. Downloading the loose
# per-file assets instead would silently drop the resource trees, and the
# Enhanced renderer refuses to enable without its validated resource set.
#
# An existing player openshim.ini is preserved by default. The installer always
# refreshes openshim.ini.canonical so startup migration has the current shipped
# preset available. Set OPENSHIM_RESET_INI=1 for an explicit backup-and-reset.
#
# OPENSHIM_DLL is an advanced override and only proceeds when a matching
# artifact set sits beside that DLL. No Steam launch options are required on
# Windows.

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$repoSlug = if ($env:OPENSHIM_REPO) { $env:OPENSHIM_REPO } else { "GrizzlyOne95/Battlezone98Redux_Shim" }
$ref = if ($env:OPENSHIM_REF) { $env:OPENSHIM_REF } else { "main" }
if ($ref -notmatch '^[A-Za-z0-9._/-]+$' -or $ref -match '^-|\.\.|//|/$') {
    throw "Refusing malformed OPENSHIM_REF '$ref'."
}
$steamAppId = "301650"
$defaultInstallDir = "Battlezone 98 Redux"

# UI tiles the game actually loads out of the custom-widget resource tree.
$uiTiles = @("uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png")

$requestedGamePath = if ($env:OPENSHIM_GAME_PATH) { $env:OPENSHIM_GAME_PATH } else { "" }

function Get-ResetIniRequested {
    if (-not $env:OPENSHIM_RESET_INI) { return $false }
    switch ($env:OPENSHIM_RESET_INI.Trim().ToLowerInvariant()) {
        "1" { return $true }
        "true" { return $true }
        "yes" { return $true }
        "on" { return $true }
        "0" { return $false }
        "false" { return $false }
        "no" { return $false }
        "off" { return $false }
        default { throw "OPENSHIM_RESET_INI must be 1/0, true/false, yes/no, or on/off." }
    }
}

$resetIni = Get-ResetIniRequested

function Test-BzrGameDir {
    param([string]$Dir)
    if (-not $Dir) { return $false }
    (Test-Path -LiteralPath (Join-Path $Dir "battlezone98redux.exe")) -or
        (Test-Path -LiteralPath (Join-Path $Dir "BZR.exe"))
}

function Add-UniquePath {
    param(
        [System.Collections.Generic.List[string]]$List,
        [string]$Path
    )
    if (-not $Path -or -not (Test-Path -LiteralPath $Path)) { return }
    $full = [System.IO.Path]::GetFullPath($Path)
    if ($List -notcontains $full) { $List.Add($full) }
}

function Get-SteamRoots {
    $roots = New-Object System.Collections.Generic.List[string]
    foreach ($location in @(
        @{ Path = "HKCU:\Software\Valve\Steam"; Names = @("SteamPath", "Path") },
        @{ Path = "HKLM:\SOFTWARE\WOW6432Node\Valve\Steam"; Names = @("InstallPath") },
        @{ Path = "HKLM:\SOFTWARE\Valve\Steam"; Names = @("InstallPath") }
    )) {
        try {
            $item = Get-ItemProperty -Path $location.Path -ErrorAction Stop
            foreach ($name in $location.Names) {
                $value = [string]$item.$name
                if ($value) { $roots.Add($value) }
            }
        } catch { }
    }
    foreach ($fallback in @(
        (Join-Path ${env:ProgramFiles(x86)} "Steam"),
        (Join-Path $env:PROGRAMFILES "Steam")
    )) {
        if ($fallback) { $roots.Add($fallback) }
    }
    $roots | Where-Object { $_ } | Select-Object -Unique
}

function Get-SteamLibraryRoots {
    param([string]$SteamRoot)
    $libraryRoots = New-Object System.Collections.Generic.List[string]
    $libraryRoots.Add($SteamRoot)
    $libraryVdf = Join-Path $SteamRoot "steamapps\libraryfolders.vdf"
    if (Test-Path -LiteralPath $libraryVdf) {
        foreach ($line in Get-Content -Path $libraryVdf) {
            $match = [regex]::Match($line, '"path"\s+"([^"]+)"')
            if (-not $match.Success) {
                $match = [regex]::Match($line, '^\s*"\d+"\s+"([^"]+)"')
            }
            if ($match.Success) {
                $libraryRoots.Add($match.Groups[1].Value.Replace('\\', '\'))
            }
        }
    }
    $libraryRoots | Where-Object { $_ } | Select-Object -Unique
}

function Get-GamePaths {
    $paths = New-Object System.Collections.Generic.List[string]
    if ($requestedGamePath) {
        if (-not (Test-BzrGameDir $requestedGamePath)) {
            throw "OPENSHIM_GAME_PATH is not a Battlezone 98 Redux install: $requestedGamePath"
        }
        Add-UniquePath -List $paths -Path $requestedGamePath
        return $paths
    }

    foreach ($steamRoot in Get-SteamRoots) {
        foreach ($libraryRoot in Get-SteamLibraryRoots -SteamRoot $steamRoot) {
            $steamApps = Join-Path $libraryRoot "steamapps"
            $manifest = Join-Path $steamApps "appmanifest_$steamAppId.acf"
            $installDir = $defaultInstallDir
            if (Test-Path -LiteralPath $manifest) {
                foreach ($line in Get-Content -Path $manifest) {
                    $match = [regex]::Match($line, '"installdir"\s+"([^"]+)"')
                    if ($match.Success) {
                        $installDir = $match.Groups[1].Value
                        break
                    }
                }
            }
            $candidate = Join-Path $steamApps (Join-Path "common" $installDir)
            if (Test-BzrGameDir $candidate) { Add-UniquePath -List $paths -Path $candidate }
        }
    }

    foreach ($candidate in @(
        (Join-Path ${env:ProgramFiles(x86)} "GOG Galaxy\Games\Battlezone 98 Redux"),
        (Join-Path $env:PROGRAMFILES "GOG Galaxy\Games\Battlezone 98 Redux")
    )) {
        if (Test-BzrGameDir $candidate) { Add-UniquePath -List $paths -Path $candidate }
    }

    return $paths
}

function Test-OpenShimDll {
    param([string]$DllPath)
    if (-not (Test-Path -LiteralPath $DllPath)) { return $false }
    $raw = [System.Text.Encoding]::ASCII.GetString([System.IO.File]::ReadAllBytes($DllPath))
    return $raw.Contains("OpenShim")
}

# Resolve one artifact set out of a tree. OpenShim-Suite.zip mirrors the
# repository layout on purpose, so the extracted bundle, a local checkout, and
# a flat directory beside an explicit OPENSHIM_DLL all resolve here. Returns
# $null unless the four core files are all present. This is the PowerShell twin
# of find_artifact_set in install_linux.sh; keep the two in step.
function Get-ArtifactSet {
    param([string]$Root, [string]$DllOverride)

    $dllPath = $null
    if ($DllOverride) {
        $dllPath = $DllOverride
    } elseif (Test-Path -LiteralPath (Join-Path $Root "bin\Release\winmm.dll")) {
        $dllPath = Join-Path $Root "bin\Release\winmm.dll"
    } elseif (Test-Path -LiteralPath (Join-Path $Root "winmm.dll")) {
        $dllPath = Join-Path $Root "winmm.dll"
    }

    $patches = Join-Path $Root "scripts\patches.json"
    if (-not (Test-Path -LiteralPath $patches)) {
        $patches = Join-Path $Root "patches.json"
    }
    $ini = Join-Path $Root "openshim.ini"
    $net = Join-Path $Root "net.ini"

    if (-not $dllPath -or -not (Test-Path -LiteralPath $dllPath) -or
        -not (Test-Path -LiteralPath $patches) -or
        -not (Test-Path -LiteralPath $ini) -or
        -not (Test-Path -LiteralPath $net)) {
        return $null
    }

    # The version marker gates the runtime validator, so a tree without it is
    # not a deployable resource set even if some payloads are there.
    $render = Join-Path $Root "resources\renderer\enhanced"
    if (-not (Test-Path -LiteralPath (Join-Path $render "resources.version"))) {
        $render = $null
    }
    $ui = Join-Path $Root "resources\ui\custom_widgets"
    if (-not (Test-Path -LiteralPath $ui)) {
        $ui = $null
    }
    $manifest = Join-Path $Root "resources\openshim\OpenShimAssets.ini"
    if (-not (Test-Path -LiteralPath $manifest)) {
        $manifest = $null
    }

    return @{
        Dll = $dllPath
        Patches = $patches
        Ini = $ini
        Net = $net
        RenderSource = $render
        UiSource = $ui
        ManifestSource = $manifest
    }
}

function Get-SuiteBundle {
    param([string]$Base, [string]$TempRoot)

    $zip = Join-Path $TempRoot "OpenShim-Suite.zip"
    $sidecar = Join-Path $TempRoot "OpenShim-Suite.zip.sha256"

    Write-Host "Downloading matched release bundle from $repoSlug ..."
    Get-FileFromUri -Uri "$Base/OpenShim-Suite.zip" -OutFile $zip
    Get-FileFromUri -Uri "$Base/OpenShim-Suite.zip.sha256" -OutFile $sidecar

    $first = Get-Content -LiteralPath $sidecar -TotalCount 1
    $expected = (($first -split '\s+') | Where-Object { $_ })[0]
    if ($expected -notmatch '^[0-9a-fA-F]{64}$') {
        throw "That release publishes no usable OpenShim-Suite.zip.sha256, so the bundle cannot be verified. Refusing to deploy it."
    }
    Assert-Hash -FilePath $zip -Expected $expected.ToLowerInvariant()
    Write-Host "  verified OpenShim-Suite.zip sha256=$($expected.ToLowerInvariant())"

    $suite = Join-Path $TempRoot "suite"
    Expand-Archive -LiteralPath $zip -DestinationPath $suite -Force

    $metadata = Join-Path $suite "release_metadata.json"
    if (Test-Path -LiteralPath $metadata) {
        $tag = [regex]::Match((Get-Content -LiteralPath $metadata -Raw), '"Tag"\s*:\s*"([^"]*)"')
        if ($tag.Success) {
            Write-Host "  bundle release: $($tag.Groups[1].Value)"
        }
    }

    return $suite
}

function Copy-ResourceDirectory {
    param([string]$Source, [string]$Destination)
    if (-not (Test-Path -LiteralPath $Destination)) {
        New-Item -ItemType Directory -Force -Path $Destination | Out-Null
    }
    Copy-Item -Path (Join-Path $Source "*") -Destination $Destination -Recurse -Force
}

function Get-FileFromUri {
    param(
        [string]$Uri,
        [string]$OutFile
    )
    Invoke-WebRequest -Uri $Uri -UseBasicParsing -OutFile $OutFile
}

function Get-ShaMap {
    param([string]$Text)
    $map = @{}
    foreach ($line in ($Text -split "`r?`n")) {
        $match = [regex]::Match($line, '([0-9a-fA-F]{64})\s+(\S+)')
        if ($match.Success) {
            $map[$match.Groups[2].Value] = $match.Groups[1].Value.ToLowerInvariant()
        }
    }
    return $map
}

function Assert-Hash {
    param([string]$FilePath, [string]$Expected)
    if (-not $Expected) { return }
    $actual = (Get-FileHash -Algorithm SHA256 -LiteralPath $FilePath).Hash.ToLowerInvariant()
    if ($actual -ne $Expected) {
        throw "Hash mismatch for $(Split-Path -Leaf $FilePath). Expected $Expected, got $actual"
    }
}

function Get-WrapperVersion {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path)) { return "none" }
    $m = Select-String -Path $Path -Pattern '^\$WrapperVersion\s*=\s*"(.+)"' -ErrorAction SilentlyContinue |
         Select-Object -First 1
    if ($m) { return $m.Matches[0].Groups[1].Value }
    return "unversioned"
}

# Copy or download openshim_wrap.* into $WrapDir. Prefer a sibling checkout so
# a fork install does not wait on a GitHub raw URL that is not on main yet.
function Update-WrapperFiles {
    param([string]$WrapDir)
    $dest = Join-Path $WrapDir "openshim_wrap.ps1"
    $old = Get-WrapperVersion -Path $dest
    $localUpload = $null
    if ($PSScriptRoot) {
        $candidate = Join-Path (Split-Path -Parent $PSScriptRoot) "upload"
        if (Test-Path -LiteralPath (Join-Path $candidate "openshim_wrap.ps1")) {
            $localUpload = $candidate
        }
    }
    foreach ($wf in @("openshim_wrap.ps1", "openshim_wrap.bat")) {
        $wfDest = Join-Path $WrapDir $wf
        Remove-Item -Force -ErrorAction SilentlyContinue $wfDest
        if ($localUpload) {
            Copy-Item -LiteralPath (Join-Path $localUpload $wf) -Destination $wfDest -Force
        } else {
            $wu = "https://raw.githubusercontent.com/$repoSlug/$ref/upload/$wf"
            Invoke-WebRequest -Uri $wu -UseBasicParsing -OutFile $wfDest
        }
    }
    $new = Get-WrapperVersion -Path $dest
    if ($old -eq $new) {
        Write-Host "Uploader wrapper: $new (already current)."
    } else {
        Write-Host "Uploader wrapper: $old -> $new."
    }
}

function Write-DefenderHelp {
    param([string]$DllPath)
    Write-Host ""
    Write-Warning "Windows Defender blocked OpenShim's winmm.dll. Unsigned proxy DLLs trip this heuristic."
    Write-Warning "Fix (keep Defender on):"
    Write-Warning "  1. Windows Security > Virus & threat protection > Protection history"
    Write-Warning "  2. Allow the block, or from admin PowerShell:"
    Write-Warning "       Add-MpPreference -ExclusionPath `"$DllPath`""
    Write-Warning "  3. Re-run the install command."
}

function Get-ThirdPartyAV {
    try {
        $avs = Get-CimInstance -Namespace 'root\SecurityCenter2' -ClassName AntiVirusProduct -ErrorAction Stop
        foreach ($av in $avs) {
            if ($av.displayName -and $av.displayName -notmatch 'Windows Defender|Microsoft Defender') {
                return $av.displayName
            }
        }
    } catch { }
    return $null
}

function Add-DefenderExclusions {
    param([string[]]$Paths)
    if (-not (Get-Command Add-MpPreference -ErrorAction SilentlyContinue)) { return }
    foreach ($p in $Paths) {
        try { Add-MpPreference -ExclusionPath $p -ErrorAction Stop }
        catch { }
    }
}

function Backup-ThenCopy {
    param([string]$Source, [string]$Dest, [string]$Stamp)
    $destDir = Split-Path -Parent $Dest
    if (-not (Test-Path -LiteralPath $destDir)) {
        New-Item -ItemType Directory -Force -Path $destDir | Out-Null
    }
    if (Test-Path -LiteralPath $Dest) {
        Copy-Item -LiteralPath $Dest -Destination "$Dest.bak-$Stamp" -Force
    }
    Copy-Item -LiteralPath $Source -Destination $Dest -Force
    $info = Get-Item -LiteralPath $Dest
    Write-Host ("  deployed {0,-14} {1,9:N0} bytes" -f $info.Name, $info.Length)
}

function Deploy-PlayerIni {
    param(
        [string]$Source,
        [string]$GameDir,
        [string]$Stamp,
        [bool]$Reset
    )

    $live = Join-Path $GameDir "openshim.ini"
    $canonical = Join-Path $GameDir "openshim.ini.canonical"

    # Canonical is installer-owned. Runtime preset migration already checks this
    # filename first when it needs the current shipped bytes for a full repair.
    Copy-Item -LiteralPath $Source -Destination $canonical -Force
    Write-Host "  refreshed openshim.ini.canonical"

    if (-not (Test-Path -LiteralPath $live)) {
        Copy-Item -LiteralPath $Source -Destination $live -Force
        Write-Host "  created openshim.ini from shipped defaults"
        return
    }

    if (-not $Reset) {
        Write-Host "  preserved existing openshim.ini"
        return
    }

    $backup = "$live.pre-reset-$Stamp.bak"
    Copy-Item -LiteralPath $live -Destination $backup -Force
    Copy-Item -LiteralPath $Source -Destination $live -Force
    Write-Host "  reset openshim.ini (backup: $(Split-Path -Leaf $backup))"
}

$gamePaths = @(Get-GamePaths)
if ($gamePaths.Count -eq 0) {
    throw "Could not find Battlezone 98 Redux. Set OPENSHIM_GAME_PATH to the game folder and run again."
}

$tempRoot = Join-Path ([System.IO.Path]::GetTempPath()) ([System.IO.Path]::GetRandomFileName())
New-Item -ItemType Directory -Path $tempRoot | Out-Null

$localRoot = $null
if ($PSScriptRoot) {
    $candidateRoot = Split-Path -Parent $PSScriptRoot
    if (Test-Path -LiteralPath (Join-Path $candidateRoot "bin\Release\winmm.dll")) {
        $localRoot = $candidateRoot
    }
}

try {
    $artifacts = $null
    $hashes = @{}

    if ($env:OPENSHIM_DLL -and (Test-Path -LiteralPath $env:OPENSHIM_DLL)) {
        # Resolve first. A bare "winmm.dll" has no parent, and Join-Path
        # refuses an empty root when Get-ArtifactSet looks beside it.
        $resolvedDll = (Resolve-Path -LiteralPath $env:OPENSHIM_DLL).ProviderPath
        $artifacts = Get-ArtifactSet -Root (Split-Path -Parent $resolvedDll) -DllOverride $resolvedDll
        if (-not $artifacts) {
            throw "OPENSHIM_DLL requires patches.json, openshim.ini, and net.ini beside the DLL (or scripts\patches.json). Refusing to mix versions."
        }
        Write-Host "Using OPENSHIM_DLL with matched companions: $($artifacts.Dll)"
    } elseif ($localRoot) {
        $artifacts = Get-ArtifactSet -Root $localRoot
        if ($artifacts) {
            Write-Host "Using local Release build with matched companions: $($artifacts.Dll)"
        }
    }

    # A DLL-only set stays supported as a deliberate manual override, but it is
    # a degraded install: the Enhanced renderer validates its deployed resource
    # set and refuses to enable without one. Say so rather than shipping a
    # silently half-featured game.
    if ($artifacts -and -not $artifacts.RenderSource) {
        Write-Warning "No resources\renderer\enhanced beside that DLL."
        Write-Warning "The Enhanced renderer will stay unavailable in this install."
    }

    if (-not $artifacts) {
        $base = "https://github.com/$repoSlug/releases/latest/download"
        try {
            $suiteRoot = Get-SuiteBundle -Base $base -TempRoot $tempRoot
            $artifacts = Get-ArtifactSet -Root $suiteRoot
            if (-not $artifacts) {
                throw "The release bundle is missing one of winmm.dll, patches.json, openshim.ini, or net.ini."
            }
            if (-not $artifacts.RenderSource) {
                throw "The release bundle carries no Enhanced renderer resource set. Refusing to deploy a bundle that would leave Enhanced unavailable."
            }
            # The bundle hash already covers these; the per-file map is what the
            # post-install quarantine re-check compares winmm.dll against.
            $sums = Join-Path $suiteRoot "SHA256SUMS.txt"
            if (Test-Path -LiteralPath $sums) {
                $hashes = Get-ShaMap -Text (Get-Content -LiteralPath $sums -Raw)
            }
            Write-Host "Using verified release bundle: $($artifacts.Dll)"
        } catch {
            if ("$_" -match 'virus|potentially unwanted|malicious') {
                Write-DefenderHelp -DllPath (Join-Path $gamePaths[0] "winmm.dll")
            }
            throw
        }
    }

    if (-not $artifacts) {
        throw "No matched OpenShim artifact set found. Set OPENSHIM_REPO to a repo that publishes OpenShim-Suite.zip releases, or OPENSHIM_DLL with matching companions."
    }

    $dll = $artifacts.Dll
    $patches = $artifacts.Patches
    $openshimIni = $artifacts.Ini
    $netIni = $artifacts.Net

    Assert-Hash -FilePath $dll -Expected $hashes["winmm.dll"]
    Assert-Hash -FilePath $patches -Expected $hashes["patches.json"]
    Assert-Hash -FilePath $openshimIni -Expected $hashes["openshim.ini"]
    Assert-Hash -FilePath $netIni -Expected $hashes["net.ini"]

    # Refuse the whole run before touching anything: with several installs
    # detected, throwing inside the copy loop would leave earlier game
    # directories rewritten and later ones untouched.
    foreach ($gameDir in $gamePaths) {
        $existingDll = Join-Path $gameDir "winmm.dll"
        if ((Test-Path -LiteralPath $existingDll) -and -not (Test-OpenShimDll $existingDll)) {
            throw "Refusing to overwrite non-OpenShim winmm.dll in $gameDir. Remove or rename that proxy first. Nothing was installed."
        }
    }

    $stamp = Get-Date -Format "yyyyMMdd-HHmmss"
    foreach ($gameDir in $gamePaths) {
        Write-Host ""
        Write-Host "Installing OpenShim to: $gameDir"
        $destDll = Join-Path $gameDir "winmm.dll"
        Backup-ThenCopy -Source $dll -Dest $destDll -Stamp $stamp
        Backup-ThenCopy -Source $patches -Dest (Join-Path $gameDir "scripts\patches.json") -Stamp $stamp
        Deploy-PlayerIni -Source $openshimIni -GameDir $gameDir -Stamp $stamp -Reset $resetIni
        Backup-ThenCopy -Source $netIni -Dest (Join-Path $gameDir "net.ini") -Stamp $stamp

        if ($artifacts.RenderSource) {
            Copy-ResourceDirectory -Source $artifacts.RenderSource `
                -Destination (Join-Path $gameDir "openshim\renderer\enhanced")
            Write-Host "  deployed Enhanced renderer resources"
        }

        if ($artifacts.ManifestSource) {
            $manifestTarget = Join-Path $gameDir "openshim\OpenShimAssets.ini"
            $manifestTargetDir = Split-Path -Parent $manifestTarget
            if (-not (Test-Path -LiteralPath $manifestTargetDir)) {
                New-Item -ItemType Directory -Force -Path $manifestTargetDir | Out-Null
            }
            Copy-Item -LiteralPath $artifacts.ManifestSource -Destination $manifestTarget -Force
            Write-Host "  deployed asset manifest"
        }

        if ($artifacts.UiSource) {
            $uiTarget = Join-Path $gameDir "BZ_ASSETS_CORE\common\ui\CustomWidgets"
            if (-not (Test-Path -LiteralPath $uiTarget)) {
                New-Item -ItemType Directory -Force -Path $uiTarget | Out-Null
            }
            foreach ($tile in $uiTiles) {
                $tileSource = Join-Path $artifacts.UiSource $tile
                if (Test-Path -LiteralPath $tileSource) {
                    Copy-Item -LiteralPath $tileSource -Destination $uiTarget -Force
                }
            }
            Write-Host "  deployed UI widget tiles"
        }
    }

    Start-Sleep -Seconds 3
    foreach ($gameDir in $gamePaths) {
        $destDll = Join-Path $gameDir "winmm.dll"
        if (-not (Test-Path -LiteralPath $destDll)) {
            Write-DefenderHelp -DllPath $destDll
            # Keep this file pure ASCII: Windows PowerShell 5.1 reads a BOM-less
            # UTF-8 script as ANSI, and one non-ASCII character here breaks the
            # whole script for anyone who saves it and runs powershell -File.
            throw "winmm.dll vanished right after install in $gameDir - quarantined. Follow the steps above, then re-run."
        }
        if ($hashes["winmm.dll"]) {
            Assert-Hash -FilePath $destDll -Expected $hashes["winmm.dll"]
        }
    }

    # Zero prompts by design: the tester's whole job is to run one command and
    # paste one launch line. The webhook rides in on OPENSHIM_WEBHOOK, which is
    # baked into the install command pinned in the private channel - so the
    # credential lives in that channel, never in this public repo. No
    # OPENSHIM_WEBHOOK (i.e. a normal player) means no uploader and no questions.
    $wrapperReady = $false
    $wrapperFailed = $false
    $wrapDir = Join-Path $env:LOCALAPPDATA "openshim"
    if ($env:OPENSHIM_WEBHOOK -or (Test-Path -LiteralPath (Join-Path $wrapDir "openshim_wrap.ps1"))) {
        Add-DefenderExclusions -Paths @($wrapDir)
        $thirdPartyAv = Get-ThirdPartyAV
        if ($thirdPartyAv) {
            Write-Host ""
            Write-Host "Heads up: $thirdPartyAv is your antivirus, not Windows Defender." -ForegroundColor Yellow
            Write-Host "If this install fails or uploads never arrive, add this folder to"
            Write-Host "$thirdPartyAv's own exceptions (Add-MpPreference only configures Defender):"
            Write-Host "    $wrapDir"
            if ($thirdPartyAv -match 'Bitdefender') {
                Write-Host "  Bitdefender: Protection > Antivirus > Settings > Manage Exceptions."
            }
            Write-Host ""
        }
    }
    if ($env:OPENSHIM_WEBHOOK) {
        if ($env:OPENSHIM_WEBHOOK -notmatch '^https://discord(app)?\.com/api/webhooks/') {
            Write-Warning "OPENSHIM_WEBHOOK is not a Discord webhook URL; skipping upload setup."
        } else {
            try {
                New-Item -ItemType Directory -Force -Path $wrapDir | Out-Null
                Update-WrapperFiles -WrapDir $wrapDir
                $confDir = Join-Path $env:APPDATA "openshim"
                New-Item -ItemType Directory -Force -Path $confDir | Out-Null
                $player = if ($env:OPENSHIM_PLAYER) { $env:OPENSHIM_PLAYER } else { "" }
                @(
                    "# Written by install_windows.ps1. Do not commit this file."
                    "OPENSHIM_WEBHOOK='$($env:OPENSHIM_WEBHOOK)'"
                    "OPENSHIM_PLAYER='$player'"
                    "OPENSHIM_INCLUDE_PROTON=0"
                ) | Out-File -FilePath (Join-Path $confDir "upload.conf") -Encoding utf8
                $shown = if ($player) { $player } else { "your in-game name (read at upload time)" }
                Write-Host "Automatic log upload configured for '$shown'."
                $wrapperReady = $true
            } catch {
                Write-Warning "Upload wrapper setup failed: $_"
                $wrapperFailed = $true
            }
        }
    } elseif (Test-Path -LiteralPath (Join-Path $wrapDir "openshim_wrap.ps1")) {
        try {
            Update-WrapperFiles -WrapDir $wrapDir
            $wrapperReady = $true
        } catch {
            Write-Warning "Could not refresh the existing upload wrapper: $_"
        }
    }

    if ($wrapperFailed) {
        Write-Host ""
        Write-Host "THE LOG UPLOADER DID NOT INSTALL." -ForegroundColor Red
        Write-Host "'Access denied' writing into $env:LOCALAPPDATA\openshim almost always"
        Write-Host "means the antivirus is blocking the wrapper script. Fix, keeping AV on:"
        Write-Host "  1. Windows Security > Virus & threat protection > Protection history"
        Write-Host "     > find the openshim_wrap block > Actions > Allow"
        Write-Host "  2. Or exclude the wrapper folder (admin PowerShell):"
        Write-Host "       Add-MpPreference -ExclusionPath `"$env:LOCALAPPDATA\openshim`""
        Write-Host "  3. Then: Remove-Item -Recurse -Force `"$env:LOCALAPPDATA\openshim`""
        Write-Host "     and re-run this install command."
        Write-Host "  NOTE: Add-MpPreference only configures Windows Defender. Running"
        Write-Host "  Bitdefender or another third-party AV? Add the same folder in THAT"
        Write-Host "  product's own exceptions UI instead (for Bitdefender: Protection >"
        Write-Host "  Antivirus > Settings > Manage Exceptions), and restore anything it"
        Write-Host "  quarantined."
        Write-Host ""
        Write-Host "Until that is fixed, leave the Steam launch options EMPTY - pointing"
        Write-Host "them at a wrapper that is not there stops the game from starting."
    }

    if (-not $env:OPENSHIM_WEBHOOK) {
        Write-Host ""
        if ($wrapperReady) {
            Write-Host "No OPENSHIM_WEBHOOK in this shell. The existing log uploader was updated in" -ForegroundColor Yellow
            Write-Host "place and its saved webhook was left alone. Test crew: if uploads stop"
            Write-Host "arriving, re-run the pinned command from the private channel."
        } else {
            Write-Host "No OPENSHIM_WEBHOOK in this shell, so the log uploader was NOT installed." -ForegroundColor Yellow
            Write-Host "Normal players: that is correct, ignore this. Test crew: paste the pinned"
            Write-Host "command from the private channel into a PowerShell window and run it again."
        }
    }

    if ($wrapperReady) {
        foreach ($wf in @("openshim_wrap.ps1", "openshim_wrap.bat")) {
            if (-not (Test-Path -LiteralPath (Join-Path $wrapDir $wf))) {
                Write-DefenderHelp -DllPath (Join-Path $wrapDir $wf)
                throw "$wf vanished right after install - quarantined. Follow the steps above, then re-run."
            }
        }
    }

    Write-Host ""
    Write-Host "Install complete." -ForegroundColor Green
    if ($wrapperReady) {
        Write-Host "OpenShim DLL: OK    Log uploader: OK" -ForegroundColor Green
    } elseif ($wrapperFailed) {
        Write-Host "OpenShim DLL: OK    LOG UPLOADER: DID NOT INSTALL (blocked - scroll up for the fix)" -ForegroundColor Red
    } elseif ($env:OPENSHIM_WEBHOOK) {
        Write-Host "OpenShim DLL: OK    Log uploader: skipped (OPENSHIM_WEBHOOK is not a Discord webhook URL)" -ForegroundColor Yellow
    } else {
        Write-Host "OpenShim DLL: OK    Log uploader: not requested (no OPENSHIM_WEBHOOK - correct for normal players)" -ForegroundColor Yellow
    }
    if ($wrapperReady) {
        Write-Host ""
        Write-Host "One step left - set the Steam launch options (Steam > Battlezone 98 Redux"
        Write-Host "> Properties > Launch Options) to:"
        Write-Host ""
        Write-Host '  cmd /c ""%LOCALAPPDATA%\openshim\openshim_wrap.bat" %command%"' -ForegroundColor Cyan
        Write-Host ""
        Write-Host "A console window stays open while the game runs - that is the wrapper"
        Write-Host "waiting to bundle your logs on exit. Closing it kills the upload, not the game."
        Write-Host "Without that line, nothing is ever uploaded."
    } else {
        Write-Host "No Steam launch option changes are needed on Windows. Just start the game."
    }
}
finally {
    Remove-Item -Recurse -Force -ErrorAction SilentlyContinue $tempRoot
}
