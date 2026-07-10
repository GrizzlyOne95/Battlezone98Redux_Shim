param(
    [string]$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [string]$UserBin = "$env:USERPROFILE\bin",
    [string]$CodexConfigPath = "$env:USERPROFILE\.codex\config.toml",
    [string]$GameDir = "",
    [string]$GameExe = "",
    [string]$GhidraInstallDir = "",
    [string]$UnrealEngineDir = "",
    [string]$RetoolkitDir = "",
    [string]$GhidraMcpHost = "127.0.0.1",
    [int]$GhidraMcpPort = 8765,
    [switch]$SkipWinget,
    [switch]$SkipPip,
    [switch]$SkipWrappers,
    [switch]$SkipCodexConfig,
    [switch]$SkipGhidraService
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
    if (-not $PathEntry -or -not (Test-Path $PathEntry)) {
        return
    }

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

function Remove-UserPathEntriesMatching([string]$Pattern) {
    $userPath = [Environment]::GetEnvironmentVariable("Path", "User")
    if (-not $userPath) {
        return
    }

    $entries = @($userPath -split ";" | Where-Object { $_ })
    $updatedEntries = @($entries | Where-Object { $_ -notmatch $Pattern })
    if ($updatedEntries.Count -ne $entries.Count) {
        [Environment]::SetEnvironmentVariable("Path", ($updatedEntries -join ";"), "User")
        Write-Info "Removed stale user PATH entries matching: $Pattern"
    }
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

    $candidates = @(
        (Join-Path $env:USERPROFILE "Tools\ghidra_12.0.4_PUBLIC"),
        (Join-Path $env:USERPROFILE "Tools")
    )

    foreach ($candidate in $candidates) {
        if (-not (Test-Path $candidate)) {
            continue
        }

        if ((Split-Path $candidate -Leaf) -like "ghidra_*") {
            return $candidate
        }

        $match = Get-ChildItem $candidate -Directory -Filter "ghidra_*_PUBLIC" -ErrorAction SilentlyContinue |
            Sort-Object Name -Descending |
            Select-Object -First 1 -ExpandProperty FullName
        if ($match) {
            return $match
        }
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

function Get-VisualStudioInstallPath() {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $path = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
        if ($LASTEXITCODE -eq 0 -and $path -and (Test-Path $path.Trim())) {
            return $path.Trim()
        }
    }

    $fallback = "C:\Program Files\Microsoft Visual Studio\2022\Community"
    if (Test-Path $fallback) {
        return $fallback
    }

    return ""
}

function Get-UnrealEngineDir() {
    if ($UnrealEngineDir -and (Test-Path $UnrealEngineDir)) {
        if ((Split-Path $UnrealEngineDir -Leaf) -ieq "Engine") {
            return (Split-Path $UnrealEngineDir -Parent)
        }
        return $UnrealEngineDir
    }

    foreach ($envName in @("UE_ENGINE_DIR", "UE_ROOT")) {
        $value = [Environment]::GetEnvironmentVariable($envName, "User")
        if ($value -and (Test-Path $value)) {
            if ((Split-Path $value -Leaf) -ieq "Engine") {
                return (Split-Path $value -Parent)
            }
            return $value
        }
    }

    $epicRoot = "C:\Program Files\Epic Games"
    if (Test-Path $epicRoot) {
        $match = Get-ChildItem $epicRoot -Directory -Filter "UE_*" -ErrorAction SilentlyContinue |
            Sort-Object Name -Descending |
            Select-Object -First 1 -ExpandProperty FullName
        if ($match) {
            return $match
        }
    }

    return ""
}

function Get-RetoolkitDir() {
    if ($RetoolkitDir -and (Test-Path $RetoolkitDir)) {
        return $RetoolkitDir
    }

    $default = Join-Path $env:LOCALAPPDATA "Programs\retoolkit"
    if (Test-Path $default) {
        return $default
    }

    return ""
}

function Set-CmdWrapper([string]$WrapperPath, [string]$TargetCommand) {
    $content = "@echo off`r`n$TargetCommand %*`r`n"
    Set-Content -Path $WrapperPath -Value $content -Encoding ASCII
}

function Set-CmdWrapperContent([string]$WrapperPath, [string[]]$Lines) {
    $content = "@echo off`r`n" + (($Lines -join "`r`n") + "`r`n")
    Set-Content -Path $WrapperPath -Value $content -Encoding ASCII
}

function Set-UserRunEntry([string]$Name, [string]$CommandValue) {
    $runKey = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run"
    if (-not (Test-Path $runKey)) {
        New-Item -Path $runKey -Force | Out-Null
    }
    Set-ItemProperty -Path $runKey -Name $Name -Value $CommandValue
    Write-Info "Set startup entry $Name"
}

function Remove-UserRunEntry([string]$Name) {
    $runKey = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run"
    if (Test-Path $runKey) {
        Remove-ItemProperty -Path $runKey -Name $Name -ErrorAction SilentlyContinue
    }
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

    $repoToml = $RepoRoot -replace "\\", "/"
    $ghidraUrl = "http://$GhidraMcpHost`:$GhidraMcpPort/mcp"

    $block = @"
$startMarker
[mcp_servers.ghidra]
url = "$ghidraUrl"

[mcp_servers.redux_debug]
command = "python"
args = [
  "$repoToml/scripts/redux_debug_bridge.py",
  "mcp"
]
$endMarker
"@

    $pattern = "(?s)$([regex]::Escape($startMarker)).*?$([regex]::Escape($endMarker))"
    $updated = $existing
    if ($updated -match $pattern) {
        $updated = [regex]::Replace($updated, $pattern, $block)
    } else {
        $ghidraBlockPattern = '(?ms)^\[mcp_servers\.ghidra\]\r?\n(?:.+\r?\n)*?(?=^\[|\z)'
        $reduxBlockPattern = '(?ms)^\[mcp_servers\.redux_debug\]\r?\n(?:.+\r?\n)*?(?=^\[|\z)'
        $updated = [regex]::Replace($updated, $ghidraBlockPattern, "")
        $updated = [regex]::Replace($updated, $reduxBlockPattern, "")
        $updated = $updated.TrimEnd()
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
Invoke-WingetInstall "Kitware.CMake"
Invoke-WingetInstall "Ninja-build.Ninja"
Invoke-WingetInstall "7zip.7zip"
Invoke-WingetInstall "mentebinaria.retoolkit"

Invoke-PipInstall @(
    "pyghidra-mcp",
    "angr",
    "frida",
    "frida-tools",
    "qiling",
    "ghidriff",
    "r2pipe",
    "construct"
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
$rizin = Resolve-CommandPath "rizin.exe" @("C:\Program Files\Rizin\bin\rizin.exe")
$rzBin = Resolve-CommandPath "rz-bin.exe" @("C:\Program Files\Rizin\bin\rz-bin.exe")
$rzAsm = Resolve-CommandPath "rz-asm.exe" @("C:\Program Files\Rizin\bin\rz-asm.exe")
$cmake = Resolve-CommandPath "cmake.exe" @("C:\Program Files\CMake\bin\cmake.exe")
$ninja = Resolve-CommandPath "ninja.exe" @((Join-Path $env:LOCALAPPDATA "Microsoft\WinGet\Packages\Ninja-build.Ninja_Microsoft.Winget.Source_8wekyb3d8bbwe\ninja.exe"))
$sevenZip = Resolve-CommandPath "7z.exe" @("C:\Program Files\7-Zip\7z.exe")
$vsInstall = Get-VisualStudioInstallPath
$vsDevCmd = if ($vsInstall) { Join-Path $vsInstall "Common7\Tools\VsDevCmd.bat" } else { "" }
$devenv = if ($vsInstall) { Join-Path $vsInstall "Common7\IDE\devenv.exe" } else { "" }
$ueRoot = Get-UnrealEngineDir
$ueBin = if ($ueRoot) { Join-Path $ueRoot "Engine\Binaries\Win64" } else { "" }
$ueBatch = if ($ueRoot) { Join-Path $ueRoot "Engine\Build\BatchFiles" } else { "" }
$unrealEditor = if ($ueBin) { Join-Path $ueBin "UnrealEditor.exe" } else { "" }
$unrealEditorCmd = if ($ueBin) { Join-Path $ueBin "UnrealEditor-Cmd.exe" } else { "" }
$runUat = if ($ueBatch) { Join-Path $ueBatch "RunUAT.bat" } else { "" }
$ueBuild = if ($ueBatch) { Join-Path $ueBatch "Build.bat" } else { "" }
$retRoot = Get-RetoolkitDir
$retBin = if ($retRoot) { Join-Path $retRoot "bin" } else { "" }

if (-not $SkipWrappers) {
    Ensure-Directory $UserBin
    Ensure-UserPathContains $UserBin
    if ($cmake) { Ensure-UserPathContains (Split-Path $cmake -Parent) }
    if ($ninja) { Ensure-UserPathContains (Split-Path $ninja -Parent) }
    if ($sevenZip) { Ensure-UserPathContains (Split-Path $sevenZip -Parent) }
    if ($ueRoot) {
        Remove-UserPathEntriesMatching "\\Epic Games\\UE_5\.[0-9]+\\Engine\\(Binaries\\Win64|Build\\BatchFiles)$"
        Ensure-UserPathContains $ueBin
        Ensure-UserPathContains $ueBatch
    }

    Set-CmdWrapper (Join-Path $UserBin "bzr-ghidra-mcp.cmd") "python `"$RepoRoot\scripts\ghidra_mcp_bz98.py`""
    Set-CmdWrapper (Join-Path $UserBin "bzr-ghidra-mcp-service.cmd") "python `"$RepoRoot\scripts\ghidra_mcp_bz98.py`" --ensure-service --service-host $GhidraMcpHost --service-port $GhidraMcpPort"
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
    if ($cmake -and (Test-Path $cmake)) { Set-CmdWrapper (Join-Path $UserBin "bzr-cmake.cmd") "`"$cmake`"" }
    if ($ninja -and (Test-Path $ninja)) { Set-CmdWrapper (Join-Path $UserBin "bzr-ninja.cmd") "`"$ninja`"" }
    if ($sevenZip -and (Test-Path $sevenZip)) { Set-CmdWrapper (Join-Path $UserBin "bzr-7z.cmd") "`"$sevenZip`"" }
    if ($devenv -and (Test-Path $devenv)) { Set-CmdWrapper (Join-Path $UserBin "bzr-devenv.cmd") "`"$devenv`"" }
    if ($vsDevCmd -and (Test-Path $vsDevCmd)) {
        Set-CmdWrapperContent (Join-Path $UserBin "bzr-vsdevcmd.cmd") @("call `"$vsDevCmd`" -arch=x86 -host_arch=x64", "cmd.exe /k")
        Set-CmdWrapperContent (Join-Path $UserBin "bzr-cl.cmd") @("call `"$vsDevCmd`" -arch=x86 -host_arch=x64 >nul", "cl.exe %*")
        Set-CmdWrapperContent (Join-Path $UserBin "bzr-link.cmd") @("call `"$vsDevCmd`" -arch=x86 -host_arch=x64 >nul", "link.exe %*")
        Set-CmdWrapperContent (Join-Path $UserBin "bzr-dumpbin.cmd") @("call `"$vsDevCmd`" -arch=x86 -host_arch=x64 >nul", "dumpbin.exe %*")
    }
    if ($unrealEditor -and (Test-Path $unrealEditor)) { Set-CmdWrapper (Join-Path $UserBin "bzr-unreal-editor.cmd") "`"$unrealEditor`"" }
    if ($unrealEditorCmd -and (Test-Path $unrealEditorCmd)) { Set-CmdWrapper (Join-Path $UserBin "bzr-unreal-editor-cmd.cmd") "`"$unrealEditorCmd`"" }
    if ($runUat -and (Test-Path $runUat)) { Set-CmdWrapper (Join-Path $UserBin "bzr-runuat.cmd") "`"$runUat`"" }
    if ($ueBuild -and (Test-Path $ueBuild)) { Set-CmdWrapper (Join-Path $UserBin "bzr-ue-build.cmd") "`"$ueBuild`"" }
    if ($retBin -and (Test-Path $retBin)) {
        foreach ($toolName in @("capa", "floss", "yara", "yarac", "upx", "pe-sieve", "entropy", "goresym", "redress")) {
            $toolPath = Join-Path $retBin "$toolName.exe"
            if (Test-Path $toolPath) {
                Set-CmdWrapper (Join-Path $UserBin "bzr-$toolName.cmd") "`"$toolPath`""
            }
        }
    }

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
if ($ueRoot) {
    [Environment]::SetEnvironmentVariable("UE_ROOT", $ueRoot, "User")
    [Environment]::SetEnvironmentVariable("UE_ENGINE_DIR", (Join-Path $ueRoot "Engine"), "User")
    Write-Info "Set user env UE_ROOT=$ueRoot"
}

Update-CodexConfig

$ghidraServiceWrapper = Join-Path $UserBin "bzr-ghidra-mcp-service.cmd"
if (-not $SkipGhidraService -and (Test-Path $ghidraServiceWrapper)) {
    Set-UserRunEntry "BzrGhidraMcp" "`"$ghidraServiceWrapper`""
    Write-Info "Ensuring persistent Ghidra MCP service is running"
    & $ghidraServiceWrapper | Out-Null
} elseif ($SkipGhidraService) {
    Remove-UserRunEntry "BzrGhidraMcp"
    Write-Info "Skipping Ghidra MCP startup hook"
}

if (-not (Get-PreferredGhidraInstallDir)) {
    Write-Info "Ghidra install not detected. Set BZR_GHIDRA_INSTALL_DIR or rerun with -GhidraInstallDir once Ghidra is installed."
}

Write-Info "Done. Open a new shell if newly created wrappers are not visible yet."
