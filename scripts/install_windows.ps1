# One-line Windows installer. Paste from the README into PowerShell:
#   irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_windows.ps1 | iex
#
# Downloads one matched GitHub-release set: winmm.dll + patches.json +
# openshim.ini + net.ini. No Steam launch options are required on Windows.

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$repoSlug = if ($env:OPENSHIM_REPO) { $env:OPENSHIM_REPO } else { "GrizzlyOne95/Battlezone98Redux_Shim" }
$steamAppId = "301650"
$defaultInstallDir = "Battlezone 98 Redux"

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

function Get-MatchedCompanions {
    param([string]$Root)
    $patches = Join-Path $Root "scripts\patches.json"
    if (-not (Test-Path -LiteralPath $patches)) {
        $patches = Join-Path $Root "patches.json"
    }
    $ini = Join-Path $Root "openshim.ini"
    $net = Join-Path $Root "net.ini"
    if ((Test-Path -LiteralPath $patches) -and (Test-Path -LiteralPath $ini) -and (Test-Path -LiteralPath $net)) {
        return @{ Patches = $patches; Ini = $ini; Net = $net }
    }
    return $null
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
    $dll = $null
    $patches = $null
    $openshimIni = $null
    $netIni = $null
    $hashes = @{}

    if ($env:OPENSHIM_DLL -and (Test-Path -LiteralPath $env:OPENSHIM_DLL)) {
        $dll = $env:OPENSHIM_DLL
        $companions = Get-MatchedCompanions -Root (Split-Path -Parent $dll)
        if (-not $companions) {
            throw "OPENSHIM_DLL requires patches.json, openshim.ini, and net.ini beside the DLL (or scripts\patches.json). Refusing to mix versions."
        }
        $patches = $companions.Patches
        $openshimIni = $companions.Ini
        $netIni = $companions.Net
        Write-Host "Using OPENSHIM_DLL with matched companions: $dll"
    } elseif ($localRoot) {
        $companions = Get-MatchedCompanions -Root $localRoot
        if ($companions -and (Test-Path -LiteralPath (Join-Path $localRoot "bin\Release\winmm.dll"))) {
            $dll = Join-Path $localRoot "bin\Release\winmm.dll"
            $patches = $companions.Patches
            $openshimIni = $companions.Ini
            $netIni = $companions.Net
            Write-Host "Using local Release build with matched companions: $dll"
        }
    }

    if (-not $dll) {
        $base = "https://github.com/$repoSlug/releases/latest/download"
        try {
            Write-Host "Downloading matched GitHub release set from $repoSlug ..."
            Get-FileFromUri -Uri "$base/winmm.dll" -OutFile (Join-Path $tempRoot "winmm.dll")
            Get-FileFromUri -Uri "$base/patches.json" -OutFile (Join-Path $tempRoot "patches.json")
            Get-FileFromUri -Uri "$base/openshim.ini" -OutFile (Join-Path $tempRoot "openshim.ini")
            Get-FileFromUri -Uri "$base/net.ini" -OutFile (Join-Path $tempRoot "net.ini")
            try {
                $shaText = (Invoke-WebRequest -Uri "$base/SHA256SUMS.txt" -UseBasicParsing).Content
                if ($shaText -is [byte[]]) {
                    $shaText = [System.Text.Encoding]::ASCII.GetString($shaText)
                }
                $hashes = Get-ShaMap -Text $shaText
            } catch { }
            $dll = Join-Path $tempRoot "winmm.dll"
            $patches = Join-Path $tempRoot "patches.json"
            $openshimIni = Join-Path $tempRoot "openshim.ini"
            $netIni = Join-Path $tempRoot "net.ini"
            Write-Host "Using GitHub release artifacts from $repoSlug"
        } catch {
            if ("$_" -match 'virus|potentially unwanted|malicious') {
                Write-DefenderHelp -DllPath (Join-Path $gamePaths[0] "winmm.dll")
            }
            throw
        }
    }

    if (-not $dll -or -not (Test-Path -LiteralPath $dll) -or -not $patches -or -not $openshimIni -or -not $netIni) {
        throw "No matched OpenShim artifact set found. Set OPENSHIM_REPO to a repo that publishes releases, or OPENSHIM_DLL with matching companions."
    }

    Assert-Hash -FilePath $dll -Expected $hashes["winmm.dll"]
    Assert-Hash -FilePath $patches -Expected $hashes["patches.json"]
    Assert-Hash -FilePath $openshimIni -Expected $hashes["openshim.ini"]
    Assert-Hash -FilePath $netIni -Expected $hashes["net.ini"]

    $stamp = Get-Date -Format "yyyyMMdd-HHmmss"
    foreach ($gameDir in $gamePaths) {
        Write-Host ""
        Write-Host "Installing OpenShim to: $gameDir"
        $destDll = Join-Path $gameDir "winmm.dll"
        if ((Test-Path -LiteralPath $destDll) -and -not (Test-OpenShimDll $destDll)) {
            throw "Refusing to overwrite non-OpenShim winmm.dll in $gameDir. Remove or rename that proxy first."
        }
        Backup-ThenCopy -Source $dll -Dest $destDll -Stamp $stamp
        Backup-ThenCopy -Source $patches -Dest (Join-Path $gameDir "scripts\patches.json") -Stamp $stamp
        Backup-ThenCopy -Source $openshimIni -Dest (Join-Path $gameDir "openshim.ini") -Stamp $stamp
        Backup-ThenCopy -Source $netIni -Dest (Join-Path $gameDir "net.ini") -Stamp $stamp
    }

    Start-Sleep -Seconds 3
    foreach ($gameDir in $gamePaths) {
        $destDll = Join-Path $gameDir "winmm.dll"
        if (-not (Test-Path -LiteralPath $destDll)) {
            Write-DefenderHelp -DllPath $destDll
            throw "winmm.dll vanished right after install in $gameDir — quarantined. Follow the steps above, then re-run."
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
