# Builds and runs the stock-derived UI decoration/layout tests with the VS 2022
# x86 toolchain. No game install is required.

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
$out = Join-Path $repo "bin\tests"
New-Item -ItemType Directory -Force $out | Out-Null

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vsroot = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $vsroot) { throw "Visual Studio with C++ tools not found" }

$vcvars = Join-Path $vsroot "VC\Auxiliary\Build\vcvars32.bat"
$exe = Join-Path $out "ui_decor_tests.exe"
$testSource = Join-Path $repo "tests\ui_decor_tests.cpp"
$decorSource = Join-Path $repo "src\engine\ui_decor.cpp"

Push-Location $out
try {
    cmd /c "`"$vcvars`" >nul && cl /nologo /std:c++20 /EHsc /W4 /WX /I `"$repo\include`" `"$testSource`" `"$decorSource`" /Fe:`"$exe`""
    if ($LASTEXITCODE -ne 0) { throw "UI decoration test build failed" }
}
finally {
    Pop-Location
}

& $exe
if ($LASTEXITCODE -ne 0) { throw "UI decoration tests FAILED" }
Write-Host "UI decoration tests passed" -ForegroundColor Green
