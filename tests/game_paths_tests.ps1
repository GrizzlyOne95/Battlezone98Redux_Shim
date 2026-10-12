# Tests for the game-folder discovery and chooser shared by
# scripts/install_windows.ps1 and scripts/uninstall_windows.ps1. Read-only
# against the machine: it only reads the registry, and every install/uninstall
# run below is pointed at fake game folders (OPENSHIM_TEST_GAME_PATHS /
# OPENSHIM_GAME_PATH) with LOCALAPPDATA/APPDATA redirected to a scratch folder.
#
#   powershell -ExecutionPolicy Bypass -File tests\game_paths_tests.ps1

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$repo = Split-Path -Parent $PSScriptRoot
$script:failures = 0

function Check {
    param([bool]$Condition, [string]$Message)
    if ($Condition) { return }
    Write-Host "FAIL: $Message" -ForegroundColor Red
    $script:failures++
}

# Pull the discovery functions out of a script without running it.
function Import-Discovery {
    param([string]$ScriptPath)
    $ast = [System.Management.Automation.Language.Parser]::ParseFile($ScriptPath, [ref]$null, [ref]$null)
    $names = "Test-BzrGameDir", "Add-UniquePath", "Get-ProgramFilesRoots", "Get-SteamRoots", "Get-SteamLibraryRoots",
        "Get-GogRegistryPaths", "Add-DetectedInstall", "Get-GameInstalls", "Get-GamePaths"
    $defs = $ast.FindAll({ param($n) $n -is [System.Management.Automation.Language.FunctionDefinitionAst] -and $names -contains $n.Name }, $true)
    Check ($defs.Count -eq $names.Count) "$ScriptPath defines all discovery functions"
    foreach ($def in $defs) { . ([scriptblock]::Create("function global:$($def.Name) $($def.Body.Extent.Text)")) }
}

$scratch = Join-Path ([System.IO.Path]::GetTempPath()) ("openshim-gamepaths-" + [guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $scratch | Out-Null
try {
    function New-FakeGame {
        param([string]$Dir)
        New-Item -ItemType Directory -Force -Path $Dir | Out-Null
        [System.IO.File]::WriteAllText((Join-Path $Dir "battlezone98redux.exe"), "MZ fake")
    }

    # --- the two scripts keep an identical copy of the shared block ----------
    $blocks = foreach ($name in "install_windows.ps1", "uninstall_windows.ps1") {
        $text = [System.IO.File]::ReadAllText((Join-Path $repo "scripts\$name"))
        $start = $text.IndexOf("function Get-GogRegistryPaths")
        $end = $text.IndexOf("function Resolve-GamePaths")
        $end = $text.IndexOf("`n}", $end)
        $text.Substring($start, $end - $start)
    }
    Check ($blocks[0] -eq $blocks[1]) "install and uninstall scripts carry identical discovery/chooser code"

    # --- registry detection on this machine -----------------------------------
    Import-Discovery (Join-Path $repo "scripts\install_windows.ps1")
    $script:steamAppId = "301650"
    $script:defaultInstallDir = "Battlezone 98 Redux"
    $script:requestedGamePath = ""

    $gogKey = Get-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\GOG.com\Games\1454067812" -ErrorAction SilentlyContinue
    if ($gogKey -and $gogKey.path) {
        $expected = [System.IO.Path]::GetFullPath(([string]$gogKey.path).TrimEnd('\'))
        $registryPaths = @(Get-GogRegistryPaths)
        Check ($registryPaths -contains $expected) "registry path $expected is read"
        if (Test-BzrGameDir $expected) {
            $installs = @(Get-GameInstalls)
            $hit = @($installs | Where-Object { $_.Path -eq $expected })
            Check ($hit.Count -eq 1) "GOG install found once via detection"
            if ($hit.Count -eq 1) { Check ($hit[0].Source -eq "GOG") "GOG install labelled GOG (got $($hit[0].Source))" }
        }
    } else {
        Write-Host "SKIP: GOG registry key not present on this machine"
    }
    Check (@(Get-GogRegistryPaths | Where-Object { $_ -match '\\$' }).Count -eq 0) "registry paths have no trailing backslash"

    # --- override / requested path ---------------------------------------------
    $fakeA = Join-Path $scratch "A\Game"; New-FakeGame $fakeA
    $fakeB = Join-Path $scratch "B\Game"; New-FakeGame $fakeB
    $notGame = Join-Path $scratch "NotGame"; New-Item -ItemType Directory -Path $notGame | Out-Null
    $env:OPENSHIM_TEST_GAME_PATHS = "$fakeA;$fakeB;$fakeA;$notGame"
    $found = @(Get-GamePaths)
    Check ($found.Count -eq 2) "override lists two unique valid fake installs (got $($found.Count))"
    $env:OPENSHIM_TEST_GAME_PATHS = ""
    $script:requestedGamePath = $notGame
    $threw = $false
    try { Get-GamePaths | Out-Null } catch { $threw = $true }
    Check $threw "a non-game OPENSHIM_GAME_PATH still throws"
    $script:requestedGamePath = ""

    # --- mocked registry: a custom GOG folder known only to the uninstall entry ---
    function global:Get-ItemProperty {
        param([string]$Path)
        if ($Path -like "*Uninstall*1454067812_is1") { return [pscustomobject]@{ InstallLocation = "$($script:fakeA)\" } }
        throw "mock: key not found"
    }
    $mocked = @(Get-GogRegistryPaths)
    Check ($mocked.Count -eq 1 -and $mocked[0] -eq $fakeA) "uninstall-entry InstallLocation is read, trailing backslash trimmed"
    $mockedInstalls = @(Get-GameInstalls | Where-Object { $_.Path -eq $fakeA })
    Check ($mockedInstalls.Count -eq 1 -and $mockedInstalls[0].Source -eq "GOG") "registry-only custom GOG folder is detected as GOG"
    Remove-Item function:\Get-ItemProperty

    # --- the chooser, driven through the real scripts with piped answers -------
    $fakeLocal = Join-Path $scratch "local"; New-Item -ItemType Directory -Path $fakeLocal | Out-Null
    $psExe = Join-Path $env:SystemRoot "System32\WindowsPowerShell\v1.0\powershell.exe"
    $uninstaller = Join-Path $repo "scripts\uninstall_windows.ps1"

    function Invoke-Chooser {
        param([string]$Answers, [hashtable]$Env)
        $saved = @{}
        $all = @{
            OPENSHIM_INTERACTIVE = "1"; OPENSHIM_DRY_RUN = "1"; LOCALAPPDATA = $fakeLocal; APPDATA = $fakeLocal
            OPENSHIM_TEST_GAME_PATHS = ""; OPENSHIM_GAME_PATH = ""; OPENSHIM_TEST_BROWSE = ""
        }
        foreach ($k in $Env.Keys) { $all[$k] = $Env[$k] }
        foreach ($k in $all.Keys) { $saved[$k] = [Environment]::GetEnvironmentVariable($k); [Environment]::SetEnvironmentVariable($k, $all[$k]) }
        try {
            $out = ($Answers -split ";" | & $psExe -NoProfile -ExecutionPolicy Bypass -File $uninstaller 2>&1 | Out-String)
            return @{ Code = $LASTEXITCODE; Out = $out }
        } finally {
            foreach ($k in $saved.Keys) { [Environment]::SetEnvironmentVariable($k, $saved[$k]) }
        }
    }

    $two = @{ OPENSHIM_TEST_GAME_PATHS = "$fakeA;$fakeB" }
    $r = Invoke-Chooser "Q" $two
    Check ($r.Code -eq 1) "Q exits 1 (got $($r.Code))"
    Check ($r.Out -match "1\. Other - " -and $r.Out -match "2\. Other - ") "two installs are listed and numbered"
    Check ($r.Out -notmatch "would remove") "Q touches nothing"

    $r = Invoke-Chooser "2" $two
    Check ($r.Code -eq 0) "choosing 2 succeeds (got $($r.Code)): $($r.Out)"
    Check ($r.Out -match [regex]::Escape("Game folder: $fakeB") -and $r.Out -notmatch [regex]::Escape("Game folder: $fakeA")) "choosing 2 uses only the second install"

    $r = Invoke-Chooser "A" $two
    Check ($r.Out -match [regex]::Escape("Game folder: $fakeA") -and $r.Out -match [regex]::Escape("Game folder: $fakeB")) "A uses every listed install"

    $r = Invoke-Chooser "9;x;1" $two
    Check ($r.Code -eq 0 -and $r.Out -match [regex]::Escape("Game folder: $fakeA")) "bad answers re-prompt"

    $one = @{ OPENSHIM_TEST_GAME_PATHS = $fakeA }
    $r = Invoke-Chooser "" $one
    Check ($r.Code -eq 0 -and $r.Out -match [regex]::Escape("Game folder: $fakeA")) "Enter confirms the single install"
    $r = Invoke-Chooser "Q" $one
    Check ($r.Code -eq 1) "Q quits with a single install"

    # None found -> straight to Browse; invalid folder is refused, then a valid one accepted.
    $none = @{ OPENSHIM_TEST_GAME_PATHS = $notGame; OPENSHIM_TEST_BROWSE = "$notGame;$fakeB" }
    $r = Invoke-Chooser "B" $none
    Check ($r.Out -match "was not found") "none found is stated plainly"
    Check ($r.Out -match "does not contain battlezone98redux.exe") "a non-game folder is refused"
    Check ($r.Code -eq 0 -and $r.Out -match [regex]::Escape("Game folder: $fakeB")) "browse then accepts a valid folder"
    $r = Invoke-Chooser "B;Q" @{ OPENSHIM_TEST_GAME_PATHS = $notGame; OPENSHIM_TEST_BROWSE = ";" }
    Check ($r.Code -eq 1) "cancelled browse returns to the menu, Q quits"

    # Valid OPENSHIM_GAME_PATH skips the chooser but states the target.
    $r = Invoke-Chooser "" @{ OPENSHIM_GAME_PATH = $fakeA }
    Check ($r.Code -eq 0 -and $r.Out -match [regex]::Escape("Game folder: $fakeA") -and $r.Out -notmatch "Type a number") "valid OPENSHIM_GAME_PATH skips the chooser"

    # Non-interactive: every install, no prompt.
    $r = Invoke-Chooser "" @{ OPENSHIM_INTERACTIVE = ""; OPENSHIM_TEST_GAME_PATHS = "$fakeA;$fakeB" }
    Check ($r.Code -eq 0 -and $r.Out -match [regex]::Escape("Game folder: $fakeA") -and $r.Out -match [regex]::Escape("Game folder: $fakeB")) "non-interactive still handles all installs"
}
finally {
    Remove-Item -Recurse -Force -LiteralPath $scratch -ErrorAction SilentlyContinue
}

if ($script:failures -gt 0) { Write-Host "$script:failures check(s) failed." -ForegroundColor Red; exit 1 }
Write-Host "game_paths_tests: all checks passed."
