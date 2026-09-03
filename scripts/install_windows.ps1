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
# OPENSHIM_DLL is an advanced override and only proceeds when a matching
# artifact set sits beside that DLL. No Steam launch options are required on
# Windows.

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$repoSlug = if ($env:OPENSHIM_REPO) { $env:OPENSHIM_REPO } else { "GrizzlyOne95/Battlezone98Redux_Shim" }
$steamAppId = "301650"
$defaultInstallDir = "Battlezone 98 Redux"

# UI tiles the game actually loads out of the custom-widget resource tree.
$uiTiles = @("uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png")

$requestedGamePath = if ($env:OPENSHIM_GAME_PATH) { $env:OPENSHIM_GAME_PATH } else { "" }

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

    return @{
        Dll = $dllPath
        Patches = $patches
        Ini = $ini
        Net = $net
        RenderSource = $render
        UiSource = $ui
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
        Backup-ThenCopy -Source $openshimIni -Dest (Join-Path $gameDir "openshim.ini") -Stamp $stamp
        Backup-ThenCopy -Source $netIni -Dest (Join-Path $gameDir "net.ini") -Stamp $stamp

        if ($artifacts.RenderSource) {
            Copy-ResourceDirectory -Source $artifacts.RenderSource `
                -Destination (Join-Path $gameDir "openshim\renderer\enhanced")
            Write-Host "  deployed Enhanced renderer resources"
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

    Write-Host ""
    Write-Host "Install complete." -ForegroundColor Green
    Write-Host "No Steam launch option changes are needed on Windows. Just start the game."
}
finally {
    Remove-Item -Recurse -Force -ErrorAction SilentlyContinue $tempRoot
}
