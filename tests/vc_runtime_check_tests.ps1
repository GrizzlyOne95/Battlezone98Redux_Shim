# Tests for Get-MissingVcRuntime in scripts/install_windows.ps1: the x86
# VC++ 2015-2022 runtime check behind the installer's "missing prerequisite"
# warning. Read-only against the machine: every case points the function at
# scratch system and game folders.
#
#   powershell -ExecutionPolicy Bypass -File tests\vc_runtime_check_tests.ps1

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

# Pull the function out of the installer without running it.
$ast = [System.Management.Automation.Language.Parser]::ParseFile((Join-Path $repo "scripts\install_windows.ps1"), [ref]$null, [ref]$null)
$def = $ast.Find({ param($n) $n -is [System.Management.Automation.Language.FunctionDefinitionAst] -and $n.Name -eq "Get-MissingVcRuntime" }, $true)
if (-not $def) { Write-Host "FAIL: install_windows.ps1 defines Get-MissingVcRuntime" -ForegroundColor Red; exit 1 }
. ([scriptblock]::Create("function global:$($def.Name) $($def.Body.Extent.Text)"))

$scratch = Join-Path ([System.IO.Path]::GetTempPath()) ("openshim-vcrt-" + [guid]::NewGuid().ToString("N"))
$sys = Join-Path $scratch "sys"
$game = Join-Path $scratch "game"
New-Item -ItemType Directory -Force -Path $sys, $game | Out-Null
try {
    $missing = @(Get-MissingVcRuntime -GameDir $game -SystemDir $sys)
    Check ($missing.Count -eq 2 -and $missing -contains "msvcp140.dll" -and $missing -contains "vcruntime140.dll") "empty system and game folders report both DLLs (got: $($missing -join ','))"

    Set-Content -LiteralPath (Join-Path $sys "msvcp140.dll") -Value "x"
    $missing = @(Get-MissingVcRuntime -GameDir $game -SystemDir $sys)
    Check ($missing.Count -eq 1 -and $missing[0] -eq "vcruntime140.dll") "a partial system runtime reports only the absent DLL (got: $($missing -join ','))"

    Set-Content -LiteralPath (Join-Path $game "vcruntime140.dll") -Value "x"
    $missing = @(Get-MissingVcRuntime -GameDir $game -SystemDir $sys)
    Check ($missing.Count -eq 0) "an app-local copy in the game folder satisfies the check (got: $($missing -join ','))"

    Remove-Item -LiteralPath (Join-Path $sys "msvcp140.dll")
    Set-Content -LiteralPath (Join-Path $game "msvcp140.dll") -Value "x"
    $missing = @(Get-MissingVcRuntime -GameDir $game -SystemDir $sys)
    Check ($missing.Count -eq 0) "app-local copies alone satisfy the check (got: $($missing -join ','))"

    # The default folder must be the 32-bit one: the game is Win32, so on
    # 64-bit Windows System32 holds the wrong runtime.
    Check ($def.Body.Extent.Text -match '"SysWOW64"') "default system folder is SysWOW64 on 64-bit Windows"
}
finally {
    Remove-Item -Recurse -Force -LiteralPath $scratch -ErrorAction SilentlyContinue
}

if ($script:failures -gt 0) { Write-Host "$script:failures check(s) failed." -ForegroundColor Red; exit 1 }
Write-Host "vc_runtime_check_tests: all checks passed."
