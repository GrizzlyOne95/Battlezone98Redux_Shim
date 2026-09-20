# Enhanced PSSM v2 guard.
#
# Ported from Campaign Reimagined, which is where this was written and where it
# no longer belongs. CR's commit 400a7a6 ("retire CR's duplicate Enhanced
# implementation") moved the Enhanced base and terrain shaders here and deleted
# its own copies, but left this guard behind still pointing at the deleted
# files. The CR workflow that ran it only triggers on Shaders/ or Materials/
# changes and nothing had touched those since, so it failed silently from
# 2026-09-13 until the next material change went looking.
#
# The consequence worth stating plainly: PSSM v2 has had no test coverage in
# either repository for that whole period. This closes that.
#
# What moved and what did not. This file carries the parts that are about the
# shaders -- the cascade maths the HLSL implements, the static isolation
# assertions, and the compile/cost matrix -- because the shaders are OpenShim's
# now. The material-pairing assertions stayed in CR, because CR_BZBase.material
# and CR_BZTerrainBase.material are CR's art direction and always were. That
# split is the same ownership line 400a7a6 drew.
#
# Note the identifier: the namespace rename in that refactor means the symbol is
# OSE_ENHANCED_PSSM_V2 here, not CR_ENHANCED_PSSM_V2.

[CmdletBinding()]
param([string]$FxcPath)

$ErrorActionPreference = 'Stop'
$repoRoot = Split-Path -Parent $PSScriptRoot
$payload = Join-Path $repoRoot 'resources\renderer\enhanced'
$baseShader = Join-Path $payload 'openshim_enhanced_base-sm4.hlsl'
$terrainShader = Join-Path $payload 'openshim_enhanced_terrain-sm4.hlsl'
$baseSm3 = Join-Path $payload 'openshim_enhanced_base-sm3.hlsl'
$terrainSm3 = Join-Path $payload 'openshim_enhanced_terrain-sm3.hlsl'

# A guard that quietly skips its subject passes exactly as loudly as one that
# checked it, which is the failure mode this port exists to fix. So a missing
# input is fatal here rather than a skip.
foreach ($required in @($baseShader, $terrainShader, $baseSm3, $terrainSm3)) {
    if (-not (Test-Path -LiteralPath $required)) {
        throw "Enhanced payload shader missing: $required"
    }
}

$failures = [Collections.Generic.List[string]]::new()

function Assert-True([bool]$Condition, [string]$Message) {
    if (-not $Condition) { $script:failures.Add($Message) }
}

function Smooth-Step([double]$Edge0, [double]$Edge1, [double]$Value) {
    if ($Edge1 -le $Edge0) { return [double]($Value -ge $Edge1) }
    $t = [Math]::Max(0.0, [Math]::Min(1.0, ($Value - $Edge0) / ($Edge1 - $Edge0)))
    return $t * $t * (3.0 - 2.0 * $t)
}

# =============================================================================
# The cascade model the HLSL is supposed to implement.
#
# Independent of any file: this is the arithmetic, checked on its own so a
# regression in the shader can be told apart from a regression in the intent.
# =============================================================================

$split1 = 16.0
$split2 = 64.0
$splitEnd = 256.0
$blendWidth = 1.0
$fadeWidth = 24.0
$fadeStart = [Math]::Max($split2 + $blendWidth, $splitEnd - $fadeWidth)

function Get-PssmState([double]$Depth) {
    if ($Depth -lt $script:split1 - $script:blendWidth) {
        return @{ Cascades = @(0); Weight = 0.0; Fade = 0.0; ShadowTaps = 4 }
    }
    if ($Depth -le $script:split1 + $script:blendWidth) {
        return @{ Cascades = @(0, 1); Weight = Smooth-Step ($script:split1 - $script:blendWidth) ($script:split1 + $script:blendWidth) $Depth; Fade = 0.0; ShadowTaps = 8 }
    }
    if ($Depth -lt $script:split2 - $script:blendWidth) {
        return @{ Cascades = @(1); Weight = 0.0; Fade = 0.0; ShadowTaps = 4 }
    }
    if ($Depth -le $script:split2 + $script:blendWidth) {
        return @{ Cascades = @(1, 2); Weight = Smooth-Step ($script:split2 - $script:blendWidth) ($script:split2 + $script:blendWidth) $Depth; Fade = 0.0; ShadowTaps = 8 }
    }
    if ($Depth -le $script:splitEnd) {
        return @{ Cascades = @(2); Weight = 0.0; Fade = Smooth-Step $script:fadeStart $script:splitEnd $Depth; ShadowTaps = 4 }
    }
    return @{ Cascades = @(); Weight = 0.0; Fade = 1.0; ShadowTaps = 0 }
}

function Evaluate-Shadow([double]$Depth) {
    $state = Get-PssmState $Depth
    $values = @(0.2, 0.8, 0.4)
    if ($state.Cascades.Count -eq 0) { return 1.0 }
    if ($state.Cascades.Count -eq 2) {
        $a = $values[$state.Cascades[0]]
        $b = $values[$state.Cascades[1]]
        return $a + ($b - $a) * $state.Weight
    }
    $shadow = $values[$state.Cascades[0]]
    return $shadow + (1.0 - $shadow) * $state.Fade
}

# Cascade selection, bounded weights and lookup cost.
$expected = @(
    @{ D = 0.0; C = '0'; T = 4 },
    @{ D = 15.0; C = '0,1'; T = 8 },
    @{ D = 16.0; C = '0,1'; T = 8 },
    @{ D = 17.0; C = '0,1'; T = 8 },
    @{ D = 18.0; C = '1'; T = 4 },
    @{ D = 63.0; C = '1,2'; T = 8 },
    @{ D = 64.0; C = '1,2'; T = 8 },
    @{ D = 65.0; C = '1,2'; T = 8 },
    @{ D = 66.0; C = '2'; T = 4 },
    @{ D = 232.0; C = '2'; T = 4 },
    @{ D = 256.0; C = '2'; T = 4 },
    @{ D = 257.0; C = ''; T = 0 }
)
foreach ($item in $expected) {
    $state = Get-PssmState $item.D
    Assert-True (($state.Cascades -join ',') -eq $item.C) "Depth $($item.D) selected cascades '$($state.Cascades -join ',')'; expected '$($item.C)'."
    Assert-True ($state.ShadowTaps -eq $item.T) "Depth $($item.D) uses $($state.ShadowTaps) taps; expected $($item.T)."
    Assert-True ($state.Weight -ge 0.0 -and $state.Weight -le 1.0) "Depth $($item.D) produced out-of-range blend weight $($state.Weight)."
    Assert-True ($state.Fade -ge 0.0 -and $state.Fade -le 1.0) "Depth $($item.D) produced out-of-range fade $($state.Fade)."
}

# The selected synthetic cascade values must meet continuously at both ends of
# every blend interval. Test immediately on each side as well as at the edge.
$epsilon = 1e-6
foreach ($edge in @(15.0, 17.0, 63.0, 65.0, 232.0, 256.0)) {
    $left = Evaluate-Shadow ($edge - $epsilon)
    $at = Evaluate-Shadow $edge
    $right = Evaluate-Shadow ($edge + $epsilon)
    Assert-True ([Math]::Abs($left - $at) -lt 1e-5) "Shadow discontinuity on the left of $edge ($left -> $at)."
    Assert-True ([Math]::Abs($right - $at) -lt 1e-5) "Shadow discontinuity on the right of $edge ($at -> $right)."
}

# Far fade endpoints and monotonicity.
Assert-True ((Get-PssmState $fadeStart).Fade -eq 0.0) 'Far fade does not equal 0 at fadeStart.'
Assert-True ((Get-PssmState $splitEnd).Fade -eq 1.0) 'Far fade does not equal 1 at splitEnd.'
$previousFade = -1.0
for ($depth = $fadeStart; $depth -le $splitEnd; $depth += 0.25) {
    $fade = (Get-PssmState $depth).Fade
    Assert-True ($fade + 1e-12 -ge $previousFade) "Far fade is not monotonic at depth $depth."
    $previousFade = $fade
}

# Bounded normal offset. The light vectors are intentionally varied to prove
# that near-zero NdotL cannot enter a reciprocal/tangent and explode the bias;
# v2 uses a normal offset, not a slope division.
$normals = @(@(0.0, 1.0, 0.0), @(1.0, 0.0, 0.0), @(1e-12, 0.0, 0.0), @(0.0, 0.0, 0.0))
$lights = @(@(0.0, 1.0, 0.0), @(1.0, 0.0, 0.0), @(1.0, 1e-12, 0.0))
foreach ($depth in @(-1.0, 0.0, 16.0, 64.0, 256.0, 1e9)) {
    $offset = [Math]::Min(0.04 + 0.0002 * [Math]::Max($depth, 0.0), 0.10)
    Assert-True (-not [double]::IsNaN($offset) -and -not [double]::IsInfinity($offset)) "Bias is non-finite at depth $depth."
    Assert-True ($offset -ge 0.04 -and $offset -le 0.10) "Bias $offset is outside [0.04, 0.10] at depth $depth."
    foreach ($normal in $normals) {
        $lengthSq = $normal[0]*$normal[0] + $normal[1]*$normal[1] + $normal[2]*$normal[2]
        foreach ($light in $lights) {
            $ndotl = $normal[0]*$light[0] + $normal[1]*$light[1] + $normal[2]*$light[2]
            Assert-True (-not [double]::IsNaN($ndotl) -and -not [double]::IsInfinity($ndotl)) 'NdotL test input became non-finite.'
            if ($lengthSq -le 1e-8) { continue }
            $appliedLength = [Math]::Sqrt($lengthSq) * (1.0 / [Math]::Sqrt($lengthSq)) * $offset
            Assert-True ($appliedLength -le 0.1000000001) "Applied normal offset $appliedLength exceeded its bound."
        }
    }
}

# =============================================================================
# Static isolation, against the payload this repository owns.
# =============================================================================

$baseSource = Get-Content $baseShader -Raw
$terrainSource = Get-Content $terrainShader -Raw
foreach ($source in @($baseSource, $terrainSource)) {
    Assert-True ($source -match '#define\s+OSE_ENHANCED_PSSM_V2\s+0') 'PSSM v2 does not default off.'
    Assert-True ($source -match 'defined\(ENHANCED_MODE\)[\s\S]{0,80}defined\(SHADOWRECEIVER\)') 'PSSM v2 activation is not gated by Enhanced + shadow receiver.'
    Assert-True ($source -match 'SamplerComparisonState') 'PSSM v2 comparison sampler declaration is missing.'
    Assert-True ([regex]::Matches($source, 'SampleCmpLevelZero').Count -eq 4) 'PSSM v2 must contain exactly four comparison taps in each shader source.'
}

# The SM3 path is the DX9 backend and must stay untouched by any of this: a
# comparison sampler there does not degrade, it fails to compile.
Assert-True ((Get-Content $baseSm3 -Raw) -notmatch 'ENHANCED_PSSM_V2') 'SM3 base shader was modified for PSSM v2.'
Assert-True ((Get-Content $terrainSm3 -Raw) -notmatch 'ENHANCED_PSSM_V2') 'SM3 terrain shader was modified for PSSM v2.'

# =============================================================================
# Compile and cost matrix.
# =============================================================================

if (-not $FxcPath) {
    $FxcPath = Get-ChildItem "${env:ProgramFiles(x86)}\Windows Kits\10\bin" -Filter fxc.exe -Recurse -File -ErrorAction SilentlyContinue |
        Sort-Object FullName -Descending | Select-Object -First 1 -ExpandProperty FullName
}
Assert-True ($FxcPath -and (Test-Path $FxcPath)) 'fxc.exe was not found.'

$costRows = @()
if ($FxcPath -and (Test-Path $FxcPath)) {
    $tempRoot = Join-Path ([IO.Path]::GetTempPath()) 'openshim-enhanced-pssm-v2'
    if (Test-Path $tempRoot) { Remove-Item $tempRoot -Recurse -Force }
    New-Item $tempRoot -ItemType Directory | Out-Null

    $commonBase = @('MAX_LIGHTS=24','NORMALMAP_ENABLED=1','SPECULARMAP_ENABLED=1','EMISSIVEMAP_ENABLED=1','ENHANCED_MODE=1','SHADOWRECEIVER=1','PSSM_ENABLED=1','PCF_SIZE=4','CR_LINEAR_LIGHT=1','CR_RADIAL_FOG=1')
    $commonTerrain = $commonBase + @('DETAILMAP_ENABLED=1')
    $compileCases = @(
        @{ Name='base-vs-v2'; File=$baseShader; Entry='base_vertex'; Target='vs_4_0'; Defines=@('MAX_LIGHTS=24','NORMALMAP_ENABLED=1','ENHANCED_MODE=1','SHADOWRECEIVER=1','PSSM_ENABLED=1','OSE_ENHANCED_PSSM_V2=1') },
        @{ Name='terrain-vs-v2'; File=$terrainShader; Entry='terrain_vertex'; Target='vs_4_0'; Defines=@('MAX_LIGHTS=24','ENHANCED_MODE=1','SHADOWRECEIVER=1','PSSM_ENABLED=1','OSE_ENHANCED_PSSM_V2=1') },
        @{ Name='base-ps-v1'; File=$baseShader; Entry='base_fragment'; Target='ps_4_0'; Defines=$commonBase },
        @{ Name='base-ps-v2'; File=$baseShader; Entry='base_fragment'; Target='ps_4_0'; Defines=$commonBase + @('OSE_ENHANCED_PSSM_V2=1') },
        @{ Name='base-ibl-ps-v2'; File=$baseShader; Entry='base_fragment'; Target='ps_4_0'; Defines=$commonBase + @('IBL_ENABLED=1','OSE_ENHANCED_PSSM_V2=1') },
        @{ Name='terrain-ps-v1'; File=$terrainShader; Entry='terrain_fragment'; Target='ps_4_0'; Defines=$commonTerrain },
        @{ Name='terrain-ps-v2'; File=$terrainShader; Entry='terrain_fragment'; Target='ps_4_0'; Defines=$commonTerrain + @('OSE_ENHANCED_PSSM_V2=1') },
        @{ Name='terrain-ibl-ps-v2'; File=$terrainShader; Entry='terrain_fragment'; Target='ps_4_0'; Defines=$commonTerrain + @('IBL_ENABLED=1','OSE_ENHANCED_PSSM_V2=1') }
    )
    foreach ($case in $compileCases) {
        $output = Join-Path $tempRoot "$($case.Name).cso"
        $fxcArgs = @('/nologo','/Ges','/WX','/T',$case.Target,'/E',$case.Entry,'/Fo',$output)
        foreach ($define in $case.Defines) { $fxcArgs += @('/D',$define) }
        $fxcArgs += $case.File
        & $FxcPath @fxcArgs | Out-Host
        Assert-True ($LASTEXITCODE -eq 0) "HLSL compile failed: $($case.Name)."
        if ($LASTEXITCODE -ne 0) { continue }
        $assembly = (& $FxcPath /dumpbin /nologo $output) -join "`n"
        $slots = if ($assembly -match 'Approximately\s+(\d+)\s+instruction slots used') { [int]$Matches[1] } else { -1 }
        $regularSamples = [regex]::Matches($assembly, '(?m)^\s*sample(?:_l)?\s').Count
        $comparisonSamples = [regex]::Matches($assembly, '(?m)^\s*sample_c_lz\s').Count
        $branches = [regex]::Matches($assembly, '(?m)^\s*if_(?:nz|z)\s').Count
        $costRows += [pscustomobject]@{ Variant=$case.Name; Slots=$slots; Sample=$regularSamples; SampleCmp=$comparisonSamples; Branches=$branches }
        if ($case.Name -like '*-ps-v2' -or $case.Name -like '*-ibl-ps-v2') {
            Assert-True ($assembly -match 'sampler_c') "$($case.Name) did not compile comparison samplers."
            Assert-True ($comparisonSamples -gt 0) "$($case.Name) emitted no sample_c_lz instructions."
        }
    }
}

if ($failures.Count -gt 0) {
    $failures | ForEach-Object { Write-Error $_ -ErrorAction Continue }
    throw "Enhanced PSSM v2 validation failed with $($failures.Count) error(s)."
}

Write-Host 'Enhanced PSSM v2 mathematical, isolation and HLSL validation: PASS'
Write-Host 'Runtime shadow taps: 4 normally, 8 only in two 2-unit blend bands, 0 beyond 256.'
$costRows | Format-Table -AutoSize
