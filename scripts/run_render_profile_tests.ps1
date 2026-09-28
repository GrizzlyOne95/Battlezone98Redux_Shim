# Builds and runs the renderer-profile resolution unit tests with the VS 2022
# x86 toolchain. No engine or game install required.
#
#   powershell -ExecutionPolicy Bypass -File scripts\run_render_profile_tests.ps1

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
$out = Join-Path $repo "bin\tests"
New-Item -ItemType Directory -Force $out | Out-Null

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vsroot = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $vsroot) { throw "Visual Studio with C++ tools not found" }

$vcvars = Join-Path $vsroot "VC\Auxiliary\Build\vcvars32.bat"

# The DX11 fixed-function test reads the shipped payload files; tests/CMakeLists.txt
# passes the same two paths. Forward slashes keep them valid C string literals.
$enhanced = ($repo -replace '\\', '/') + "/resources/renderer/enhanced"
$fixedFuncDefines = @(
    "_CRT_SECURE_NO_WARNINGS",
    "BZR_FIXEDFUNC_PROGRAM=\`"$enhanced/openshim_dx11_fixedfunc.program\`"",
    "BZR_FIXEDFUNC_HLSL=\`"$enhanced/openshim_dx11_fixedfunc-sm4.hlsl\`""
)

$testSuites = @(
    @{ Exe = "render_profile_tests.exe"; Sources = @("$repo\tests\render_profile_tests.cpp", "$repo\src\engine\render_profile.cpp") },
    @{ Exe = "request_apply_tracker_tests.exe"; Sources = @("$repo\tests\request_apply_tracker_tests.cpp") },
    @{ Exe = "render_profile_resources_tests.exe"; Sources = @("$repo\tests\render_profile_resources_tests.cpp", "$repo\src\engine\render_profile_resources.cpp") },
    @{ Exe = "dx11_legacy_material_compat_tests.exe"; Sources = @("$repo\tests\dx11_legacy_material_compat_tests.cpp", "$repo\src\engine\dx11_legacy_material_compat.cpp"); Defines = $fixedFuncDefines },
    @{ Exe = "enhanced_resource_bootstrap_tests.exe"; Sources = @("$repo\tests\enhanced_resource_bootstrap_tests.cpp", "$repo\src\engine\enhanced_resource_bootstrap.cpp") }
)

foreach ($suite in $testSuites) {
    $exe = Join-Path $out $suite.Exe
    $sources = ($suite.Sources | ForEach-Object { "`"$_`"" }) -join " "
    $defines = if ($suite.Defines) { ($suite.Defines | ForEach-Object { "/D$_" }) -join " " } else { "" }
    cmd /c "`"$vcvars`" >nul && cl /nologo /std:c++20 /EHsc /W4 /WX $defines /I `"$repo\include`" $sources /Fe:`"$exe`" /Fo:`"$out\\`""
    if ($LASTEXITCODE -ne 0) { throw "test build failed: $($suite.Exe)" }

    & $exe
    if ($LASTEXITCODE -ne 0) { throw "$($suite.Exe) FAILED" }
}
Write-Host "render profile tests passed" -ForegroundColor Green
