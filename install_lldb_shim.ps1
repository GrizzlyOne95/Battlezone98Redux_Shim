[CmdletBinding()]
param()

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$llvmBin = "C:\Program Files\LLVM\bin"
$llvmLldb = Join-Path $llvmBin "lldb.exe"
$llvmLldbDap = Join-Path $llvmBin "lldb-dap.exe"
$userBin = Join-Path $env:USERPROFILE "bin"
$shimRuntimeCandidates = @(
    "C:\Program Files\Android\Android Studio\plugins\android-ndk\resources\lldb"
    "C:\Program Files\Blender Foundation\Blender 4.5\4.5\python"
)

function Find-Python311Runtime {
    foreach ($candidate in $shimRuntimeCandidates) {
        $dllPath = Join-Path $candidate "bin\python311.dll"
        $encodingsPath = Join-Path $candidate "lib\encodings"
        if ((Test-Path $dllPath) -and (Test-Path $encodingsPath)) {
            return $candidate
        }
    }

    throw "Unable to find a complete Python 3.11 runtime for LLDB."
}

function New-LldbWrapper {
    param(
        [Parameter(Mandatory = $true)]
        [string]$WrapperPath,
        [Parameter(Mandatory = $true)]
        [string]$TargetExe,
        [Parameter(Mandatory = $true)]
        [string]$RuntimeRoot
    )

    $wrapper = @(
        "@echo off"
        "set ""PATH=$RuntimeRoot\bin;%PATH%"""
        "set ""PYTHONHOME=$RuntimeRoot"""
        """$TargetExe"" %*"
    )

    Set-Content -Path $WrapperPath -Value $wrapper -Encoding ASCII
}

if (-not (Test-Path $llvmLldb)) {
    throw "LLVM LLDB not found at '$llvmLldb'."
}

if (-not (Test-Path $llvmLldbDap)) {
    throw "LLVM LLDB DAP not found at '$llvmLldbDap'."
}

$runtimeRoot = Find-Python311Runtime

New-Item -ItemType Directory -Path $userBin -Force | Out-Null
New-LldbWrapper -WrapperPath (Join-Path $userBin "lldb.cmd") -TargetExe $llvmLldb -RuntimeRoot $runtimeRoot
New-LldbWrapper -WrapperPath (Join-Path $userBin "lldb-dap.cmd") -TargetExe $llvmLldbDap -RuntimeRoot $runtimeRoot

$userPath = [Environment]::GetEnvironmentVariable("Path", "User")
$pathEntries = @()
if ($userPath) {
    $pathEntries = $userPath.Split(';', [System.StringSplitOptions]::RemoveEmptyEntries)
}

if (-not ($pathEntries -contains $userBin)) {
    $newUserPath = if ($userPath) { "$userBin;$userPath" } else { $userBin }
    [Environment]::SetEnvironmentVariable("Path", $newUserPath, "User")
    Write-Host "Added $userBin to the user PATH."
} else {
    Write-Host "$userBin is already present in the user PATH."
}

Write-Host "Installed LLDB wrappers using Python runtime: $runtimeRoot"
Write-Host "Use a new shell or restart VS Code to pick up the updated PATH."
