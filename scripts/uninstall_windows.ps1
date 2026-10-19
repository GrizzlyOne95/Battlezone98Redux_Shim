# One-line Windows uninstaller. Paste into PowerShell:
#   irm https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/uninstall_windows.ps1 | iex
#
# Removes everything install_windows.ps1 deploys, from every detected Steam/GOG
# install (or the one named by OPENSHIM_GAME_PATH): the three-binary load chain
# (winmm.dll, bzloader.dll, plugins\openshim.dll), scripts\patches.json, the
# Enhanced renderer resources and asset manifest under openshim\, the four UI
# widget tiles, openshim.ini.canonical, the .bak-<stamp> copies the installer
# made of those files on each run, and what the Workshop updater leaves behind
# (winmm.dll.previous, scripts\patches.json.previous, openshim_update.status).
#
# A binary is removed only when it identifies as OpenShim; a foreign winmm.dll
# (another proxy) is kept and reported. openshim.ini and its backups, net.ini
# and its backups, and logs\ are left in place so a reinstall finds the
# player's settings; net.ini in particular is a game file OpenShim replaced,
# and the stock bytes are not known here.
#
#   OPENSHIM_PURGE_CONFIG=1      also remove openshim.ini and its backups
#   OPENSHIM_PURGE_LEFTOVERS=1   additionally purge OpenShim logs, crash dumps,
#                               settings, and current-user uploader/data folders.
#                               Keeps net.ini and the game's shared logs.
#   OPENSHIM_DRY_RUN=1           print removals without changing anything
#
# Keep this file pure ASCII: Windows PowerShell 5.1 reads a BOM-less UTF-8
# script as ANSI, and one non-ASCII character breaks it for anyone who saves
# it and runs powershell -File.

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$steamAppId = "301650"
$defaultInstallDir = "Battlezone 98 Redux"
$requestedGamePath = if ($env:OPENSHIM_GAME_PATH) { $env:OPENSHIM_GAME_PATH } else { "" }

# UI tiles the installer writes into the game's custom-widget resource tree.
# Everything else in that folder belongs to the game or to the player.
$uiTiles = @("uiline.png", "uiplate.png", "uibtn.png", "uibtnhv.png", "osh_career_center.png", "osh_prelobby_center.png",
    "osh_options_center.png", "osh_hub_center.png", "osh_category_center.png", "osh_tile_hv.png", "osh_tile_ck.png", "osh_value_hv.png", "osh_value_ck.png",
    "osh_keys_center.png", "osh_key_hv.png", "osh_key_ck.png", "osh_tool_hv.png", "osh_tool_ck.png", "osh_preview_white.png", "osh_reticle_center.png")

function Get-Switch {
    param([string]$Name)
    $value = [Environment]::GetEnvironmentVariable($Name)
    if (-not $value) { return $false }
    switch ($value.Trim().ToLowerInvariant()) {
        "1" { return $true }
        "true" { return $true }
        "yes" { return $true }
        "on" { return $true }
        "0" { return $false }
        "false" { return $false }
        "no" { return $false }
        "off" { return $false }
        default { throw "$Name must be 1/0, true/false, yes/no, or on/off." }
    }
}

$purgeLeftovers = Get-Switch "OPENSHIM_PURGE_LEFTOVERS"
$purgeConfig = (Get-Switch "OPENSHIM_PURGE_CONFIG") -or $purgeLeftovers
$dryRun = Get-Switch "OPENSHIM_DRY_RUN"

# --- discovery: identical to install_windows.ps1 so both scripts find the ---
# --- same folders, including a Steam install whose folder was renamed.    ---

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

# ${env:ProgramFiles(x86)} is undefined on 32-bit Windows, and Join-Path
# refuses an empty root, so filter the roots before joining.
function Get-ProgramFilesRoots {
    @(${env:ProgramFiles(x86)}, $env:PROGRAMFILES) | Where-Object { $_ } | Select-Object -Unique
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
    foreach ($programFiles in Get-ProgramFilesRoots) {
        $roots.Add((Join-Path $programFiles "Steam"))
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

# GOG records the install folder in the registry (product id 1454067812), so a
# custom GOG location is found there. Missing keys are normal and silent.
function Get-GogRegistryPaths {
    $found = New-Object System.Collections.Generic.List[string]
    foreach ($location in @(
        @{ Path = "HKLM:\SOFTWARE\WOW6432Node\GOG.com\Games\1454067812"; Name = "path" },
        @{ Path = "HKLM:\SOFTWARE\GOG.com\Games\1454067812"; Name = "path" },
        @{ Path = "HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\1454067812_is1"; Name = "InstallLocation" }
    )) {
        try {
            $item = Get-ItemProperty -Path $location.Path -ErrorAction Stop
            $value = [string]$item.($location.Name)
            if ($value) { $found.Add($value.Trim().TrimEnd('\')) }
        } catch { }
    }
    $found
}

function Add-DetectedInstall {
    param(
        [System.Collections.Generic.List[string]]$List,
        [hashtable]$Sources,
        [string]$Path,
        [string]$Source
    )
    $before = $List.Count
    Add-UniquePath -List $List -Path $Path
    if ($List.Count -gt $before) { $Sources[$List[$List.Count - 1]] = $Source }
}

# Every install found, as objects with Path and Source (Steam, GOG or Other).
function Get-GameInstalls {
    $paths = New-Object System.Collections.Generic.List[string]
    $sources = @{}
    if ($requestedGamePath) {
        if (-not (Test-BzrGameDir $requestedGamePath)) {
            throw "OPENSHIM_GAME_PATH is not a Battlezone 98 Redux install: $requestedGamePath"
        }
        Add-DetectedInstall -List $paths -Sources $sources -Path $requestedGamePath -Source "Other"
    }
    elseif ($env:OPENSHIM_TEST_GAME_PATHS) {
        # Test-only: replaces detection so a test can never reach a real install.
        foreach ($candidate in $env:OPENSHIM_TEST_GAME_PATHS.Split(';')) {
            if (Test-BzrGameDir $candidate) { Add-DetectedInstall -List $paths -Sources $sources -Path $candidate -Source "Other" }
        }
    }
    else {
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
                if (Test-BzrGameDir $candidate) { Add-DetectedInstall -List $paths -Sources $sources -Path $candidate -Source "Steam" }
            }
        }

        foreach ($candidate in Get-GogRegistryPaths) {
            if (Test-BzrGameDir $candidate) { Add-DetectedInstall -List $paths -Sources $sources -Path $candidate -Source "GOG" }
        }
        foreach ($programFiles in Get-ProgramFilesRoots) {
            $candidate = Join-Path $programFiles "GOG Galaxy\Games\Battlezone 98 Redux"
            if (Test-BzrGameDir $candidate) { Add-DetectedInstall -List $paths -Sources $sources -Path $candidate -Source "GOG" }
        }
    }
    foreach ($path in $paths) { [pscustomobject]@{ Path = $path; Source = $sources[$path] } }
}

function Get-GamePaths {
    foreach ($install in @(Get-GameInstalls)) { $install.Path }
}

# --- interactive chooser: only when OpenShimSetup.exe sets OPENSHIM_INTERACTIVE=1 ---

function Test-InteractiveSetup {
    $env:OPENSHIM_INTERACTIVE -eq "1"
}

function Read-Answer {
    param([string]$Prompt)
    try { $answer = Read-Host $Prompt } catch { $answer = $null }
    if ($null -eq $answer) { return "Q" }   # input closed: same as quitting
    $answer.Trim()
}

# Folder picker. Returns a valid game folder, or $null if the user cancels.
function Read-BrowsedGameDir {
    $testResults = $null
    if ($env:OPENSHIM_TEST_BROWSE) {
        # Test-only: stands in for the dialog; an empty entry, or none left, is Cancel.
        $testResults = New-Object System.Collections.Generic.Queue[string]
        foreach ($entry in $env:OPENSHIM_TEST_BROWSE.Split(';')) { $testResults.Enqueue($entry) }
    }
    while ($true) {
        $picked = $null
        if ($null -ne $testResults) {
            if ($testResults.Count -gt 0) { $picked = $testResults.Dequeue() }
        }
        elseif ([System.Threading.Thread]::CurrentThread.ApartmentState -eq "STA") {
            Add-Type -AssemblyName System.Windows.Forms
            $owner = New-Object System.Windows.Forms.Form
            $owner.TopMost = $true
            $dialog = New-Object System.Windows.Forms.FolderBrowserDialog
            $dialog.Description = "Choose the Battlezone 98 Redux folder (the one that contains battlezone98redux.exe)."
            if ($dialog.ShowDialog($owner) -eq [System.Windows.Forms.DialogResult]::OK) { $picked = $dialog.SelectedPath }
            $owner.Dispose()
        }
        else {
            $picked = Read-Host "Type the full path of the Battlezone 98 Redux folder (leave empty to cancel)"
        }
        if (-not $picked) { return $null }
        if (Test-BzrGameDir $picked) { return [System.IO.Path]::GetFullPath($picked) }
        Write-Host "That folder does not contain battlezone98redux.exe, so it is not a Battlezone 98 Redux folder: $picked"
    }
}

# Returns the game folders to work on. Without OPENSHIM_INTERACTIVE=1 this is
# exactly Get-GamePaths (every install found). -Filter narrows the list shown.
function Resolve-GamePaths {
    param([string]$Action, [scriptblock]$Filter)
    if (-not (Test-InteractiveSetup)) { return @(Get-GamePaths) }

    $installs = @(Get-GameInstalls)
    if ($requestedGamePath) {
        Write-Host "Game folder: $($installs[0].Path)"
        return @($installs[0].Path)
    }
    if ($Filter) {
        $narrowed = @($installs | Where-Object { & $Filter $_.Path })
        if ($narrowed.Count -gt 0) { $installs = $narrowed }
    }

    while ($true) {
        if ($installs.Count -eq 0) {
            Write-Host "Battlezone 98 Redux was not found on this computer."
            $answer = Read-Answer "Press B to browse for the game folder, or Q to quit"
        }
        elseif ($installs.Count -eq 1) {
            Write-Host "Battlezone 98 Redux was found here:"
            Write-Host "  $($installs[0].Source) - $($installs[0].Path)"
            $answer = Read-Answer "Press Enter to $Action it, B to browse for another folder, or Q to quit"
            if ($answer -eq "") { return @($installs[0].Path) }
        }
        else {
            Write-Host "Battlezone 98 Redux was found in these places:"
            for ($i = 0; $i -lt $installs.Count; $i++) {
                Write-Host ("  {0}. {1} - {2}" -f ($i + 1), $installs[$i].Source, $installs[$i].Path)
            }
            $answer = Read-Answer "Type a number to $Action that one, A for all of them, B to browse for another folder, or Q to quit"
            if ($answer -match '^[aA]$') { return @($installs | ForEach-Object { $_.Path }) }
            if ($answer -match '^\d+$' -and [int]$answer -ge 1 -and [int]$answer -le $installs.Count) {
                return @($installs[[int]$answer - 1].Path)
            }
        }
        if ($answer -match '^[qQ]$') {
            Write-Host "Cancelled. Nothing was changed."
            exit 1
        }
        if ($answer -match '^[bB]$') {
            $browsed = Read-BrowsedGameDir
            if ($browsed) { return @($browsed) }
            continue
        }
        Write-Host "Please choose one of the options listed."
    }
}

# --- identity -----------------------------------------------------------------

# Every OpenShim binary (bootstrap, loader, plugin) carries the ASCII string
# "OpenShim" in its code and the UTF-16 product name "BZR Open Shim" in its
# version resource. A winmm.dll without either is somebody else's proxy.
function Test-OpenShimBinary {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) { return $false }
    $bytes = [System.IO.File]::ReadAllBytes($Path)
    if ([System.Text.Encoding]::ASCII.GetString($bytes).Contains("OpenShim")) { return $true }
    return [System.Text.Encoding]::Unicode.GetString($bytes).Contains("BZR Open Shim")
}

# --- removal ------------------------------------------------------------------

$script:removed = 0
$script:kept = 0
$script:failed = New-Object System.Collections.Generic.List[string]

function Remove-Planned {
    param([string]$Path, [switch]$Recurse)
    if ($dryRun) {
        Write-Host "  would remove $Path"
        $script:removed++
        return
    }
    try {
        Remove-Item -Force -LiteralPath $Path -Recurse:$Recurse
        Write-Host "  removed $Path"
        $script:removed++
    } catch {
        Write-Host "  FAILED  $Path : $($_.Exception.Message)"
        $script:failed.Add($Path)
    }
}

function Remove-IfPresent {
    param([string]$Path)
    if (Test-Path -LiteralPath $Path -PathType Leaf) { Remove-Planned -Path $Path }
}

# Binaries and their installer backups: only what identifies as OpenShim.
function Remove-OpenShimBinary {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) { return }
    if (Test-OpenShimBinary $Path) {
        Remove-Planned -Path $Path
    } else {
        Write-Host "  KEEPING $Path : it does not identify as OpenShim"
        $script:kept++
    }
}

function Remove-Backups {
    param([string]$Path, [switch]$IdentityChecked)
    $dir = Split-Path -Parent $Path
    $leaf = Split-Path -Leaf $Path
    if (-not (Test-Path -LiteralPath $dir)) { return }
    foreach ($backup in Get-ChildItem -LiteralPath $dir -File -Filter "$leaf.bak-*" -ErrorAction SilentlyContinue) {
        if ($IdentityChecked) { Remove-OpenShimBinary $backup.FullName } else { Remove-Planned -Path $backup.FullName }
    }
}

function Remove-DirectoryIfEmpty {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Container)) { return }
    if ($dryRun) { return }
    if (@(Get-ChildItem -LiteralPath $Path -Force).Count -eq 0) {
        Remove-Item -LiteralPath $Path -Force
        Write-Host "  removed empty folder $Path"
    }
}

# Only OpenShim's own names are removed from the shared game logs folder.
# Never remove BZLogger.txt, BZOgreLogfile.log, or unrelated proxy logs.
function Remove-OpenShimLogs {
    param([string]$GameDir)
    foreach ($logDir in @($GameDir, (Join-Path $GameDir "logs"))) {
        if (-not (Test-Path -LiteralPath $logDir -PathType Container)) { continue }
        $item = Get-Item -LiteralPath $logDir -Force
        if ($item.Attributes -band [System.IO.FileAttributes]::ReparsePoint) {
            Write-Host "  KEEPING reparse-point log directory $logDir"
            $script:kept++
            continue
        }
        foreach ($file in Get-ChildItem -LiteralPath $logDir -File -Force) {
            if ($file.Name -match '^(?:openshim.*\.(?:log|dmp)(?:\.\d+)?|bzloader\.log|winmm_shim\.log)$') {
                Remove-Planned -Path $file.FullName
            }
        }
    }
    Remove-DirectoryIfEmpty (Join-Path $GameDir "logs")
}

# Remove a *dedicated* OpenShim data tree without traversing any reparse
# points (junctions/symlinks). Keep and report unfamiliar links.
function Remove-OpenShimDataTree {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path -PathType Container)) { return }
    $item = Get-Item -LiteralPath $Path -Force
    if ($item.Attributes -band [System.IO.FileAttributes]::ReparsePoint) {
        Write-Host "  KEEPING reparse point $Path"
        $script:kept++
        return
    }
    foreach ($child in @(Get-ChildItem -LiteralPath $Path -Force)) {
        if ($child.Attributes -band [System.IO.FileAttributes]::ReparsePoint) {
            Write-Host "  KEEPING reparse point $($child.FullName)"
            $script:kept++
        } elseif ($child.PSIsContainer) {
            Remove-OpenShimDataTree -Path $child.FullName
        } else {
            Remove-Planned -Path $child.FullName
        }
    }
    Remove-DirectoryIfEmpty $Path
}

# Only immediate directories named openshim below existing rooted AppData
# locations qualify. Never recurse over a user-supplied arbitrary directory.
function Remove-OpenShimUserData {
    param([string]$BaseDir)
    if (-not $BaseDir -or -not [System.IO.Path]::IsPathRooted($BaseDir)) { return }
    $base = [System.IO.Path]::GetFullPath($BaseDir).TrimEnd('\')
    if (-not (Test-Path -LiteralPath $base -PathType Container)) { return }
    $target = Join-Path $base "openshim"
    if (-not (Test-Path -LiteralPath $target -PathType Container)) { return }
    Write-Host "  dedicated current-user data: $target"
    Remove-OpenShimDataTree -Path $target
}

function Test-GameRunningFrom {
    param([string]$GameDir)
    $prefix = [System.IO.Path]::GetFullPath($GameDir).TrimEnd('\') + '\'
    foreach ($process in Get-Process -Name "battlezone98redux", "BZR" -ErrorAction SilentlyContinue) {
        try {
            $path = $process.Path
            if ($path -and $path.StartsWith($prefix, [System.StringComparison]::OrdinalIgnoreCase)) {
                return $true
            }
        } catch { }
    }
    return $false
}

# Offer the installs that actually hold OpenShim; fall back to all if none do.
$gamePaths = @(Resolve-GamePaths -Action "remove OpenShim from" -Filter {
    param($dir)
    foreach ($relative in @("winmm.dll", "bzloader.dll", "plugins\openshim.dll")) {
        if (Test-OpenShimBinary (Join-Path $dir $relative)) { return $true }
    }
    return $false
})
if ($gamePaths.Count -eq 0) {
    throw "Could not find Battlezone 98 Redux. Set OPENSHIM_GAME_PATH and run again."
}

# Refuse before touching anything: a running game holds the DLLs open, and a
# half-removed load chain is the one state neither installer nor game handles.
foreach ($gameDir in $gamePaths) {
    if (Test-GameRunningFrom $gameDir) {
        throw "Battlezone 98 Redux is running from $gameDir. Close the game, then run the uninstaller again. Nothing was removed."
    }
}

if ($dryRun) { Write-Host "Dry run: nothing will be removed." }

foreach ($gameDir in $gamePaths) {
    Write-Host ""
    Write-Host "Game folder: $gameDir"

    # Load chain, plus the previous-version copies the Workshop updater keeps.
    foreach ($relative in @("winmm.dll", "winmm.dll.previous",
            "bzloader.dll", "bzloader.dll.previous",
            "plugins\openshim.dll", "plugins\openshim.dll.previous")) {
        Remove-OpenShimBinary (Join-Path $gameDir $relative)
    }
    foreach ($relative in @("winmm.dll", "bzloader.dll", "plugins\openshim.dll")) {
        Remove-Backups -Path (Join-Path $gameDir $relative) -IdentityChecked
    }
    Remove-DirectoryIfEmpty (Join-Path $gameDir "plugins")

    # patches.json travels with the DLL and nothing else writes that name.
    $patches = Join-Path $gameDir "scripts\patches.json"
    Remove-IfPresent $patches
    Remove-IfPresent "$patches.previous"
    Remove-Backups -Path $patches

    # Enhanced renderer resources and the asset manifest. openshim\ is created
    # by the installer, but only its own entries are removed; anything else a
    # player put there is reported and left.
    $openshimDir = Join-Path $gameDir "openshim"
    $renderDir = Join-Path $openshimDir "renderer\enhanced"
    # The in-game asset sync keeps a marker in the folder and swaps it through
    # .pending/.old siblings; remove those along with the folder itself.
    Remove-IfPresent (Join-Path $renderDir "openshim_set.sha256")
    foreach ($leftover in @($renderDir, "$renderDir.pending", "$renderDir.old")) {
        if (Test-Path -LiteralPath $leftover -PathType Container) {
            Remove-Planned -Path $leftover -Recurse
        }
    }
    Remove-IfPresent (Join-Path $openshimDir "OpenShimAssets.ini")
    Remove-DirectoryIfEmpty (Join-Path $openshimDir "renderer")
    Remove-DirectoryIfEmpty $openshimDir
    if (-not $dryRun -and (Test-Path -LiteralPath $openshimDir -PathType Container)) {
        Write-Host "  KEEPING $openshimDir : it still holds files the installer did not put there"
        $script:kept++
    }

    # The four widget tiles; the folder may hold the game's or the player's own
    # widgets, so it goes only when those four were all it contained.
    $uiDir = Join-Path $gameDir "BZ_ASSETS_CORE\common\ui\CustomWidgets"
    foreach ($tile in $uiTiles) { Remove-IfPresent (Join-Path $uiDir $tile) }
    Remove-IfPresent (Join-Path $uiDir "openshim_widgets.sha256")
    Remove-DirectoryIfEmpty $uiDir

    # Installer-owned copy of the shipped preset, and the updater's status file.
    Remove-IfPresent (Join-Path $gameDir "openshim.ini.canonical")
    Remove-IfPresent (Join-Path $gameDir "openshim_update.status")

    if ($purgeConfig) {
        $ini = Join-Path $gameDir "openshim.ini"
        Remove-IfPresent $ini
        Remove-Backups -Path $ini
        foreach ($reset in Get-ChildItem -LiteralPath $gameDir -File -Filter "openshim.ini.pre-reset-*.bak" -ErrorAction SilentlyContinue) {
            Remove-Planned -Path $reset.FullName
        }
    }
    if ($purgeLeftovers) {
        Remove-IfPresent (Join-Path $gameDir "openshim.ini.example")
        Remove-OpenShimLogs -GameDir $gameDir
    }
}

if ($purgeLeftovers) {
    # The uploader/outbox and webhook settings belong to this Windows user,
    # shared by any OpenShim installs. Do not change Steam launch options.
    Write-Host "Purging current-user OpenShim data (shared by any OpenShim installations):"
    Remove-OpenShimUserData -BaseDir $env:LOCALAPPDATA
    Remove-OpenShimUserData -BaseDir $env:APPDATA
}

Write-Host ""
if ($dryRun) {
    Write-Host "Dry run complete: $($script:removed) item(s) would be removed, $($script:kept) kept."
} else {
    Write-Host "Uninstall complete: $($script:removed) item(s) removed, $($script:kept) kept."
}
if ($purgeLeftovers) {
    Write-Host "OpenShim-owned settings, logs, crash dumps, and current-user data cleanup requested."
    Write-Host "Shared net.ini, BZLogger.txt, generic game logs, and unrelated mod files were kept."
    Write-Host "If configured, CLEAR the OpenShim upload wrapper from Steam Launch Options."
    Write-Host "This uninstaller cannot edit Steam launch options for you."
} elseif ($purgeConfig) {
    Write-Host "openshim.ini and its backups were removed (OPENSHIM_PURGE_CONFIG). net.ini and logs were left in place."
} else {
    Write-Host "openshim.ini, net.ini, their backups, and logs were left in place."
    Write-Host "Set OPENSHIM_PURGE_CONFIG=1 for settings, or OPENSHIM_PURGE_LEFTOVERS=1 for full cleanup."
}
if (-not $purgeLeftovers) {
    $wrapDir = if ($env:LOCALAPPDATA) { Join-Path $env:LOCALAPPDATA "openshim" } else { "" }
    if ($wrapDir -and (Test-Path -LiteralPath $wrapDir)) {
        Write-Host "The optional log-upload wrapper is still installed at $wrapDir;"
        Write-Host "delete that folder and clear the Steam launch option that names it if you set one."
    }
}
if ($script:failed.Count -gt 0) {
    throw "$($script:failed.Count) item(s) could not be removed (listed above as FAILED). Close anything using them and run again."
}
