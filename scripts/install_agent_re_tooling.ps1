param(
    [string]$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [string]$UserBin = "$env:USERPROFILE\bin",
    [string]$CodexConfigPath = "$env:USERPROFILE\.codex\config.toml",
    [string]$GameDir = "",
    [string]$GameExe = "",
    [string]$GhidraInstallDir = "",
    [switch]$SkipWinget,
    [switch]$SkipPip,
    [switch]$SkipWrappers,
    [switch]$SkipCodexConfig
)

$ErrorActionPreference = "Stop"

function Write-Info([string]$Message) {
    Write-Host "[tooling] $Message"
}

function Ensure-Directory([string]$PathValue) {
    if (-not (Test-Path $PathValue)) {
        New-Item -ItemType Directory -Path $PathValue -Force | Out-Null
    }
}

function Ensure-UserPathContains([string]$PathEntry) {
    $userPath = [Environment]::GetEnvironmentVariable("Path", "User")
    $entries = @()
    if ($userPath) {
        $entries = $userPath -split ";" | Where-Object { $_ }
    }

    if ($entries -contains $PathEntry) {
        return
    }

    $updated = @($entries + $PathEntry) -join ";"
    [Environment]::SetEnvironmentVariable("Path", $updated, "User")
    Write-Info "Added to user PATH: $PathEntry"
}

function Invoke-WingetInstall([string]$Id) {
    if ($SkipWinget) {
        Write-Info "Skipping winget install for $Id"
        return
    }

    $already = winget list --id $Id --accept-source-agreements 2>$null
    if ($LASTEXITCODE -eq 0 -and $already -match [regex]::Escape($Id)) {
        Write-Info "winget package already present: $Id"
        return
    }

    Write-Info "Installing winget package: $Id"
    winget install --id $Id --accept-source-agreements --accept-package-agreements --disable-interactivity
}

function Invoke-PipInstall([string[]]$Packages) {
    if ($SkipPip) {
        Write-Info "Skipping pip installs"
        return
    }

    Write-Info "Installing Python packages: $($Packages -join ', ')"
    python -m pip install --user @Packages
}

function Get-PythonUserScripts() {
    $scriptsDir = python -c "import sysconfig; print(sysconfig.get_path('scripts', 'nt_user'))"
    if ($LASTEXITCODE -ne 0 -or -not $scriptsDir) {
        throw "Unable to resolve Python user scripts directory"
    }
    return $scriptsDir.Trim()
}

function Resolve-CommandPath([string]$CommandName, [string[]]$Candidates = @()) {
    foreach ($candidate in $Candidates) {
        if ($candidate -and (Test-Path $candidate)) {
            return $candidate
        }
    }

    $command = Get-Command $CommandName -ErrorAction SilentlyContinue
    if ($command -and $command.Source -and (Test-Path $command.Source)) {
        return $command.Source
    }

    return ""
}

function Get-PreferredGhidraInstallDir() {
    if ($GhidraInstallDir) {
        return $GhidraInstallDir
    }

    $envOverride = [Environment]::GetEnvironmentVariable("BZR_GHIDRA_INSTALL_DIR", "User")
    if ($envOverride -and (Test-Path $envOverride)) {
        return $envOverride
    }

    $envFallback = [Environment]::GetEnvironmentVariable("GHIDRA_INSTALL_DIR", "User")
    if ($envFallback -and (Test-Path $envFallback)) {
        return $envFallback
    }

    $defaultPath = "C:\ghidra_12.0.4_PUBLIC"
    if (Test-Path $defaultPath) {
        return $defaultPath
    }

    return ""
}

function Get-WinDbgRoot() {
    $install = (Get-AppxPackage Microsoft.WinDbg | Select-Object -ExpandProperty InstallLocation -ErrorAction SilentlyContinue)
    if ($install) {
        return $install
    }
    return ""
}

function Get-X32DbgPath() {
    $base = Join-Path $env:LOCALAPPDATA "Microsoft\WinGet\Packages"
    if (-not (Test-Path $base)) {
        return ""
    }

    $match = Get-ChildItem $base -Recurse -Filter x32dbg.exe -ErrorAction SilentlyContinue |
        Select-Object -First 1 -ExpandProperty FullName
    return $match
}

function Get-CutterPath() {
    $base = Join-Path $env:LOCALAPPDATA "Microsoft\WinGet\Packages"
    if (-not (Test-Path $base)) {
        return ""
    }

    $match = Get-ChildItem $base -Recurse -Filter cutter.exe -ErrorAction SilentlyContinue |
        Select-Object -First 1 -ExpandProperty FullName
    return $match
}

function Get-WinGetPackageExe([string]$PackageId, [string]$ExeName) {
    $base = Join-Path $env:LOCALAPPDATA "Microsoft\WinGet\Packages"
    if (-not (Test-Path $base)) {
        return ""
    }

    $packageRoot = Get-ChildItem $base -Directory -Filter "$PackageId*" -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
    if (-not $packageRoot) {
        return ""
    }

    $match = Get-ChildItem $packageRoot -Recurse -Filter $ExeName -ErrorAction SilentlyContinue |
        Sort-Object FullName |
        Select-Object -First 1 -ExpandProperty FullName
    return $match
}

function Set-CmdWrapper([string]$WrapperPath, [string]$TargetCommand) {
    $content = "@echo off`r`n$TargetCommand %*`r`n"
    Set-Content -Path $WrapperPath -Value $content -Encoding ASCII
}

function Update-CodexConfig() {
    if ($SkipCodexConfig) {
        Write-Info "Skipping Codex config update"
        return
    }

    Ensure-Directory (Split-Path $CodexConfigPath -Parent)
    if (-not (Test-Path $CodexConfigPath)) {
        Set-Content -Path $CodexConfigPath -Value "" -Encoding UTF8
    }

    $existing = Get-Content $CodexConfigPath -Raw
    $startMarker = "# >>> BZR agent tooling >>>"
    $endMarker = "# <<< BZR agent tooling <<<"

    $ghidraDirValue = Get-PreferredGhidraInstallDir
    $ghidraEnvLine = ""
    if ($ghidraDirValue) {
        $ghidraEnvLine = "env = { `"GHIDRA_INSTALL_DIR`" = `"$($ghidraDirValue -replace '\\', '/')`" }"
    }
    $repoToml = $RepoRoot -replace "\\", "/"

    $block = @"
$startMarker
[mcp_servers.ghidra]
command = "python"
args = [
  "$repoToml/scripts/ghidra_mcp_bz98.py"
]
$ghidraEnvLine

[mcp_servers.redux_debug]
command = "python"
args = [
  "$repoToml/scripts/redux_debug_bridge.py",
  "mcp"
]
$endMarker
"@

    $pattern = "(?s)$([regex]::Escape($startMarker)).*?$([regex]::Escape($endMarker))"
    if ($existing -match $pattern) {
        $updated = [regex]::Replace($existing, $pattern, $block)
    } else {
        $updated = $existing.TrimEnd()
        if ($updated) {
            $updated += "`r`n`r`n"
        }
        $updated += $block + "`r`n"
    }

    Set-Content -Path $CodexConfigPath -Value $updated -Encoding UTF8
    Write-Info "Updated Codex config: $CodexConfigPath"
}

Invoke-WingetInstall "Microsoft.WinDbg"
Invoke-WingetInstall "x64dbg.x64dbg"
Invoke-WingetInstall "Rizin.Rizin"
Invoke-WingetInstall "Rizin.Cutter"
Invoke-WingetInstall "horsicq.DIE-engine"
Invoke-WingetInstall "Microsoft.Sysinternals.ProcessMonitor"
Invoke-WingetInstall "Microsoft.Sysinternals.ProcessExplorer"

Invoke-PipInstall @(
    "pyghidra-mcp",
    "angr",
    "frida",
    "frida-tools",
    "qiling",
    "ghidriff"
)

$pythonExe = (Get-Command python -ErrorAction Stop).Source
$pythonInstallDir = Split-Path $pythonExe -Parent
$pythonInstallScripts = Join-Path $pythonInstallDir "Scripts"
$pythonScripts = Get-PythonUserScripts
$winDbgRoot = Get-WinDbgRoot
$cdb32 = if ($winDbgRoot) { Join-Path $winDbgRoot "x86\cdb.exe" } else { "" }
$x32dbg = Get-X32DbgPath
$cutter = Get-CutterPath
$frida = Resolve-CommandPath "frida.exe" @(
    (Join-Path $pythonInstallScripts "frida.exe"),
    (Join-Path $pythonScripts "frida.exe")
)
$fridaPs = Resolve-CommandPath "frida-ps.exe" @(
    (Join-Path $pythonInstallScripts "frida-ps.exe"),
    (Join-Path $pythonScripts "frida-ps.exe")
)
$fridaTrace = Resolve-CommandPath "frida-trace.exe" @(
    (Join-Path $pythonInstallScripts "frida-trace.exe"),
    (Join-Path $pythonScripts "frida-trace.exe")
)
$angrCli = Resolve-CommandPath "angr.exe" @(
    (Join-Path $pythonInstallScripts "angr.exe"),
    (Join-Path $pythonScripts "angr.exe")
)
$ghidriff = Resolve-CommandPath "ghidriff.exe" @(
    (Join-Path $pythonInstallScripts "ghidriff.exe"),
    (Join-Path $pythonScripts "ghidriff.exe")
)
$die = Get-WinGetPackageExe "horsicq.DIE-engine" "die.exe"
$diec = Get-WinGetPackageExe "horsicq.DIE-engine" "diec.exe"
$procmon = Get-WinGetPackageExe "Microsoft.Sysinternals.ProcessMonitor" "Procmon.exe"
$procexp = Get-WinGetPackageExe "Microsoft.Sysinternals.ProcessExplorer" "procexp.exe"
$rizin = "C:\Program Files\Rizin\bin\rizin.exe"
$rzBin = "C:\Program Files\Rizin\bin\rz-bin.exe"
$rzAsm = "C:\Program Files\Rizin\bin\rz-asm.exe"

if (-not $SkipWrappers) {
    Ensure-Directory $UserBin
    Ensure-UserPathContains $UserBin
    Set-CmdWrapper (Join-Path $UserBin "bzr-ghidra-mcp.cmd") "python `"$RepoRoot\scripts\ghidra_mcp_bz98.py`""
    Set-CmdWrapper (Join-Path $UserBin "bzr-redux-debug.cmd") "python `"$RepoRoot\scripts\redux_debug_bridge.py`""
    Set-CmdWrapper (Join-Path $UserBin "bzr-qiling.cmd") "python `"$RepoRoot\scripts\qiling_cli.py`""
    if ($frida) { Set-CmdWrapper (Join-Path $UserBin "bzr-frida.cmd") "`"$frida`"" }
    if ($fridaPs) { Set-CmdWrapper (Join-Path $UserBin "bzr-frida-ps.cmd") "`"$fridaPs`"" }
    if ($fridaTrace) { Set-CmdWrapper (Join-Path $UserBin "bzr-frida-trace.cmd") "`"$fridaTrace`"" }
    if ($angrCli) { Set-CmdWrapper (Join-Path $UserBin "bzr-angr.cmd") "`"$angrCli`"" }
    if (Test-Path $ghidriff) { Set-CmdWrapper (Join-Path $UserBin "bzr-ghidriff.cmd") "`"$ghidriff`"" }

    if (Test-Path $rizin) { Set-CmdWrapper (Join-Path $UserBin "bzr-rizin.cmd") "`"$rizin`"" }
    if (Test-Path $rzBin) { Set-CmdWrapper (Join-Path $UserBin "bzr-rz-bin.cmd") "`"$rzBin`"" }
    if (Test-Path $rzAsm) { Set-CmdWrapper (Join-Path $UserBin "bzr-rz-asm.cmd") "`"$rzAsm`"" }
    if ($cutter -and (Test-Path $cutter)) { Set-CmdWrapper (Join-Path $UserBin "bzr-cutter.cmd") "`"$cutter`"" }
    if ($cdb32 -and (Test-Path $cdb32)) { Set-CmdWrapper (Join-Path $UserBin "bzr-cdb32.cmd") "`"$cdb32`"" }
    if ($x32dbg -and (Test-Path $x32dbg)) { Set-CmdWrapper (Join-Path $UserBin "bzr-x32dbg.cmd") "`"$x32dbg`"" }
    if ($die -and (Test-Path $die)) { Set-CmdWrapper (Join-Path $UserBin "bzr-die.cmd") "`"$die`"" }
    if ($diec -and (Test-Path $diec)) { Set-CmdWrapper (Join-Path $UserBin "bzr-diec.cmd") "`"$diec`"" }
    if ($procmon -and (Test-Path $procmon)) { Set-CmdWrapper (Join-Path $UserBin "bzr-procmon.cmd") "`"$procmon`"" }
    if ($procexp -and (Test-Path $procexp)) { Set-CmdWrapper (Join-Path $UserBin "bzr-procexp.cmd") "`"$procexp`"" }

    Write-Info "Wrote wrappers to $UserBin"
}

if ($GameDir) {
    [Environment]::SetEnvironmentVariable("BZR_GAME_DIR", $GameDir, "User")
    Write-Info "Set user env BZR_GAME_DIR=$GameDir"
}
if ($GameExe) {
    [Environment]::SetEnvironmentVariable("BZR_GAME_EXE", $GameExe, "User")
    Write-Info "Set user env BZR_GAME_EXE=$GameExe"
}
if ($GhidraInstallDir) {
    [Environment]::SetEnvironmentVariable("BZR_GHIDRA_INSTALL_DIR", $GhidraInstallDir, "User")
    Write-Info "Set user env BZR_GHIDRA_INSTALL_DIR=$GhidraInstallDir"
}

Update-CodexConfig

if (-not (Get-PreferredGhidraInstallDir)) {
    Write-Info "Ghidra install not detected. Set BZR_GHIDRA_INSTALL_DIR or rerun with -GhidraInstallDir once Ghidra is installed."
}

Write-Info "Done. Open a new shell if newly created wrappers are not visible yet."
