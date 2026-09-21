# Compiles every HLSL variant the canonical Enhanced payload declares.
#
# The roadmap's shader-permutation discipline (Docs/DX11_ENHANCED_RENDERING_ROADMAP.md
# section 0.6) requires that every required shipped shader variant is compiled and
# validated in CI. Until this script existed, CI compiled exactly one shader --
# shaders\dx11_enhanced_fxaa.hlsl -- and nothing under resources\renderer\enhanced\.
#
# That gap mattered from the moment the OpenShim payload became canonical. Before
# then a broken OSE_* variant was masked on the only install anyone tested on,
# because Campaign Reimagined ships the en-* techniques on the stock-named
# materials and its CR_* programs are what the scheme actually resolves to. The
# OpenShim copy was compiled by Ogre and then referenced by no material. So a
# variant that does not compile reaches every user WITHOUT CR installed, and the
# developer install is precisely the configuration that cannot see it.
#
# The variant list is read from the .program files rather than hard-coded, so new
# tiers -- the Enhanced Medium and Low delegates of roadmap phase 1.1, say --
# are covered the moment they are declared, with no edit here.
#
#   powershell -ExecutionPolicy Bypass -File scripts\Test-EnhancedShaderCompile.ps1
#
# It also enforces the payload's vertex colour order contract, which no amount
# of compiling can catch: `iColor` and `iColor.bgra` both compile perfectly and
# differ only in whether blue renders as blue or as orange.
#
# Exit codes: 0 all variants compile and the colour contract holds, 1 at least
# one failed, 2 fxc.exe not found.

[CmdletBinding()]
param(
    # Payload root. Defaults to the shipped canonical Enhanced payload.
    [string]$PayloadDir,

    # Explicit fxc.exe. Defaults to the newest x86 fxc in the Windows SDK, which
    # is what the Build Win32 workflow already resolves for the FXAA step.
    [string]$Fxc,

    # Enumerate the variants and exit without compiling anything.
    [switch]$ListOnly,

    # Print fxc's own output for every variant, not only for failures.
    [switch]$ShowOutput
)

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot

if (-not $PayloadDir) {
    $PayloadDir = Join-Path $repo "resources\renderer\enhanced"
}

if (-not (Test-Path -LiteralPath $PayloadDir -PathType Container)) {
    Write-Host "Payload directory not found: $PayloadDir" -ForegroundColor Red
    exit 2
}

# -----------------------------------------------------------------------------
# Vertex colour order contract
# -----------------------------------------------------------------------------
# Native BZR geometry packs vertex colour as an ARGB DWORD, which D3D11 reads
# back in RGBA order. Every stock SM4 family that consumes vertex colour
# corrects for that -- ui, uitexmat, untextured, sky, effect, simple_one_tex
# and terrain all ship `iColor.bgra`. Payload programs stand in for those
# families and must agree with them, or a blue legacy material renders orange.
#
# The opposite rule governs Ogre-generated vertices (TextArea, ParticleFX):
# they have already passed through convertColourValue and arrive in RGBA order,
# so correcting them swaps them twice. None of them reach this payload --
# IsExcludedFromSynthesis() in dx11_legacy_material_compat.cpp rejects overlay,
# font, cursor, sprite, compositor and rtt materials first -- so inside this
# directory the rule is unconditional.
#
# Scope: vertex entry points only, identified by writing SV_POSITION, that
# declare a COLOR0 input. A fragment stage reads the interpolated value and is
# not the producer, so it is not checked.

$colorContractChecked = 0
$colorContractViolations = @()
foreach ($hlsl in (Get-ChildItem -LiteralPath $PayloadDir -Filter "*-sm4.hlsl" -File)) {
    $src = Get-Content -Raw -LiteralPath $hlsl.FullName
    # Strip line comments first, so prose about .bgra can never satisfy the
    # contract and a commented-out assignment can never break it.
    $code = [regex]::Replace($src, '//[^\r\n]*', '')
    foreach ($m in [regex]::Matches($code, '(?s)\bvoid\s+(\w+)\s*\((.*?)\)\s*\{(.*?)\r?\n\}')) {
        $entry  = $m.Groups[1].Value
        $params = $m.Groups[2].Value
        $body   = $m.Groups[3].Value
        if ($params -notmatch ':\s*SV_POSITION') { continue }
        $cm = [regex]::Match($params, '\bin\s+float4\s+(\w+)\s*:\s*COLOR0?\b')
        if (-not $cm.Success) { continue }
        $colorContractChecked++
        $inColor = $cm.Groups[1].Value
        if ($body -notmatch ('\b' + [regex]::Escape($inColor) + '\.bgra\b')) {
            $colorContractViolations += [pscustomobject]@{
                Source = $hlsl.Name; Entry = $entry; Input = $inColor
            }
        }
    }
}

if ($colorContractViolations.Count -gt 0) {
    Write-Host ""
    Write-Host ("VERTEX COLOUR ORDER CONTRACT FAILED: {0} vertex entry point(s) read a COLOR0 input without the native .bgra correction." -f $colorContractViolations.Count) -ForegroundColor Red
    foreach ($v in $colorContractViolations) {
        Write-Host ("  {0}  entry={1}  input={2}" -f $v.Source, $v.Entry, $v.Input) -ForegroundColor Red
    }
    Write-Host "  Native BZR vertex colour is an ARGB DWORD. Read it as '<input>.bgra', or blue renders orange." -ForegroundColor Red
    exit 1
}

if ($colorContractChecked -eq 0) {
    Write-Host "vertex colour order: WARNING - no vertex entry point with a COLOR0 input was found; the contract checked nothing." -ForegroundColor Yellow
} else {
    Write-Host ("vertex colour order: contract holds ({0} vertex entry point(s) checked)." -f $colorContractChecked)
}

# -----------------------------------------------------------------------------
# Parse the .program declarations
# -----------------------------------------------------------------------------
# Ogre's program script format: a `<stage>_program <name> <syntax>` header, then
# a brace block of `key value` lines. Only hlsl blocks are compiled here; the
# glsl and glsles siblings need a different toolchain and the payload ships no
# .glsles sources of its own at all -- those blocks point at the stock engine
# files by design.

function Read-ProgramVariants {
    param([string]$ProgramFile)

    $variants = @()
    $current = $null
    $depth = 0

    foreach ($rawLine in (Get-Content -LiteralPath $ProgramFile)) {
        # Strip line comments before anything else: the payload keeps superseded
        # define lines commented out next to the live ones, and compiling those
        # would validate variants that no material can ever request.
        $line = $rawLine
        $commentAt = $line.IndexOf("//")
        if ($commentAt -ge 0) {
            $line = $line.Substring(0, $commentAt)
        }
        $line = $line.Trim()
        if (-not $line) { continue }

        if ($depth -eq 0) {
            if ($line -match '^(vertex|fragment|geometry|compute)_program\s+(\S+)\s+(\S+)$') {
                $current = [pscustomobject]@{
                    File    = [System.IO.Path]::GetFileName($ProgramFile)
                    Stage   = $Matches[1]
                    Name    = $Matches[2]
                    Syntax  = $Matches[3]
                    Source  = $null
                    Target  = $null
                    Entry   = $null
                    Defines = @()
                }
            }
            if ($line -eq "{") { $depth = 1 }
            continue
        }

        if ($line -eq "{") { $depth++; continue }
        if ($line -eq "}") {
            $depth--
            if ($depth -eq 0 -and $current) {
                if ($current.Syntax -eq "hlsl") { $variants += $current }
                $current = $null
            }
            continue
        }

        # Only the outermost block carries the compile inputs; default_params and
        # other nested blocks are runtime binding, not compilation.
        if ($depth -ne 1 -or -not $current) { continue }

        if ($line -match '^source\s+(\S+)$')                 { $current.Source = $Matches[1]; continue }
        if ($line -match '^target\s+(\S+)$')                 { $current.Target = $Matches[1]; continue }
        if ($line -match '^entry_point\s+(\S+)$')            { $current.Entry  = $Matches[1]; continue }
        if ($line -match '^preprocessor_defines\s+(.+)$') {
            $current.Defines = @(
                $Matches[1].Split(",") |
                    ForEach-Object { $_.Trim() } |
                    Where-Object { $_ }
            )
            continue
        }
    }

    return $variants
}

$programFiles = @(Get-ChildItem -LiteralPath $PayloadDir -Filter *.program -File | Sort-Object Name)
if ($programFiles.Count -eq 0) {
    Write-Host "No .program files under $PayloadDir" -ForegroundColor Red
    exit 2
}

$variants = @()
foreach ($pf in $programFiles) {
    $variants += Read-ProgramVariants -ProgramFile $pf.FullName
}

$incomplete = @($variants | Where-Object { -not $_.Source -or -not $_.Target -or -not $_.Entry })
foreach ($bad in $incomplete) {
    Write-Host ("  ! {0}: missing source/target/entry_point" -f $bad.Name) -ForegroundColor Yellow
}
$variants = @($variants | Where-Object { $_.Source -and $_.Target -and $_.Entry })

# Many program names differ only in their runtime bindings and compile to the
# same thing. Compile each distinct (source, target, entry, defines) once and
# report which program names it covers -- the count of names is what the
# permutation matrix is actually made of.
$groups = $variants | Group-Object -Property {
    "{0}|{1}|{2}|{3}" -f $_.Source, $_.Target, $_.Entry, (($_.Defines | Sort-Object) -join ",")
}

Write-Host "Payload    : $PayloadDir"
Write-Host ("Declared   : {0} HLSL programs across {1} script(s), {2} distinct compilations" -f `
    $variants.Count, $programFiles.Count, $groups.Count)

# A payload .hlsl that no program block names is not validated by anything here.
# That is worth saying out loud rather than reporting a clean pass over a subset.
$referenced = $variants | ForEach-Object { $_.Source.ToLowerInvariant() } | Sort-Object -Unique
$onDisk = Get-ChildItem -LiteralPath $PayloadDir -Filter *.hlsl -File | ForEach-Object { $_.Name }
$uncovered = @($onDisk | Where-Object { $referenced -notcontains $_.ToLowerInvariant() })
if ($uncovered.Count -gt 0) {
    Write-Host ""
    Write-Host "Not covered by any .program in this payload (declared elsewhere, e.g. in a material's own script):" -ForegroundColor Yellow
    foreach ($u in $uncovered) { Write-Host "  $u" -ForegroundColor Yellow }
}
Write-Host ""

if ($ListOnly) {
    foreach ($g in $groups) {
        $v = $g.Group[0]
        Write-Host ("{0,-10} {1,-16} {2}" -f $v.Target, $v.Entry, $v.Source)
        Write-Host ("           defines: {0}" -f (($v.Defines -join ",") -replace '^$', '(none)'))
        Write-Host ("           programs: {0}" -f ($g.Group.Count))
    }
    exit 0
}

# -----------------------------------------------------------------------------
# Resolve fxc
# -----------------------------------------------------------------------------
if (-not $Fxc) {
    $kitsBin = Join-Path ${env:ProgramFiles(x86)} "Windows Kits\10\bin"
    if (Test-Path -LiteralPath $kitsBin) {
        $Fxc = Get-ChildItem -LiteralPath $kitsBin -Filter fxc.exe -File -Recurse -ErrorAction SilentlyContinue |
            Where-Object { $_.FullName -match '\\x86\\fxc\.exe$' } |
            Sort-Object FullName -Descending |
            Select-Object -First 1 |
            ForEach-Object { $_.FullName }
    }
}

if (-not $Fxc -or -not (Test-Path -LiteralPath $Fxc -PathType Leaf)) {
    Write-Host "Windows SDK fxc.exe was not found. Pass -Fxc." -ForegroundColor Red
    exit 2
}

Write-Host "fxc        : $Fxc"
Write-Host ""

# -----------------------------------------------------------------------------
# Compile
# -----------------------------------------------------------------------------
$outDir = Join-Path ([System.IO.Path]::GetTempPath()) ("ose-shader-compile-" + [Guid]::NewGuid().ToString("n").Substring(0, 8))
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$failures = @()
$passed = 0
$index = 0

try {
    foreach ($g in $groups) {
        $index++
        $v = $g.Group[0]
        $sourcePath = Join-Path $PayloadDir $v.Source

        if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
            $failures += [pscustomobject]@{
                Name = $v.Name; Target = $v.Target; Entry = $v.Entry
                Source = $v.Source; Defines = ($v.Defines -join ",")
                Output = "source file not found: $sourcePath"
            }
            Write-Host ("[{0,3}/{1}] MISSING  {2}" -f $index, $groups.Count, $v.Source) -ForegroundColor Red
            continue
        }

        # Ogre's D3D11 program gives a bare define the value "1"; mirror that
        # exactly, or a `#if FOO` in the shader evaluates differently here than
        # it does at runtime and the validation is of a variant nobody ships.
        $args = @("/nologo", "/T", $v.Target, "/E", $v.Entry)
        foreach ($d in $v.Defines) {
            if ($d -match "=") { $args += @("/D", $d) } else { $args += @("/D", "$d=1") }
        }
        $args += @("/Fo", (Join-Path $outDir ("v{0}.cso" -f $index)), $sourcePath)

        # fxc writes warnings to stderr and still exits 0. With the script-wide
        # $ErrorActionPreference = "Stop" in force, PowerShell promotes any
        # native stderr write to a terminating NativeCommandError, so ONE
        # warning aborted the whole run -- openshim_enhanced_base-sm3.hlsl's
        # X3078 loop-variable shadow killed it at variant 72 of 192, and the
        # remaining 120 had never actually been compiled by this script. The
        # exit code is the verdict here, not the presence of stderr output.
        $previousPreference = $ErrorActionPreference
        $ErrorActionPreference = "Continue"
        try {
            $output = & $Fxc @args 2>&1
            $code = $LASTEXITCODE
        }
        finally {
            $ErrorActionPreference = $previousPreference
        }

        if ($code -ne 0) {
            $failures += [pscustomobject]@{
                Name = $v.Name; Target = $v.Target; Entry = $v.Entry
                Source = $v.Source; Defines = ($v.Defines -join ",")
                Output = ($output | Out-String).Trim()
            }
            Write-Host ("[{0,3}/{1}] FAIL     {2} {3} {4}" -f $index, $groups.Count, $v.Target, $v.Entry, $v.Source) -ForegroundColor Red
            Write-Host ("           defines: {0}" -f (($v.Defines -join ",") -replace '^$', '(none)')) -ForegroundColor Red
        }
        else {
            $passed += $g.Group.Count
            Write-Host ("[{0,3}/{1}] ok       {2} {3} {4}  ({5} program(s))" -f `
                $index, $groups.Count, $v.Target, $v.Entry, $v.Source, $g.Group.Count)
            if ($ShowOutput -and $output) { Write-Host ($output | Out-String).Trim() }
        }
    }
}
finally {
    Remove-Item -LiteralPath $outDir -Recurse -Force -ErrorAction SilentlyContinue
}

Write-Host ""
if ($failures.Count -gt 0) {
    Write-Host ("FAILED: {0} of {1} distinct compilations" -f $failures.Count, $groups.Count) -ForegroundColor Red
    foreach ($f in $failures) {
        Write-Host ""
        Write-Host ("  {0}  [{1} {2}]" -f $f.Name, $f.Target, $f.Entry) -ForegroundColor Red
        Write-Host ("  source  : {0}" -f $f.Source)
        Write-Host ("  defines : {0}" -f ($f.Defines -replace '^$', '(none)'))
        Write-Host ("  {0}" -f ($f.Output -replace "`r?`n", "`n  "))
    }
    exit 1
}

Write-Host ("All {0} distinct compilations passed, covering {1} declared HLSL programs." -f $groups.Count, $passed) -ForegroundColor Green
exit 0
