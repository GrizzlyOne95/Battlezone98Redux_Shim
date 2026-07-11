param(
    [Parameter(Mandatory = $true)]
    [string]$GameDir,
    [switch]$Restore
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$shaderDir = Join-Path $GameDir 'BZ_ASSETS_CORE\pc\programs\dx11'
$utf8 = New-Object System.Text.UTF8Encoding($false)

function Update-ShaderFile {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Name,
        [Parameter(Mandatory = $true)]
        [scriptblock]$Transform
    )

    $path = Join-Path $shaderDir $Name
    $backup = "$path.pre-dx11-hardening.bak"
    if (-not (Test-Path -LiteralPath $path)) {
        throw "Stock DX11 shader not found: $path"
    }

    if ($Restore) {
        if (-not (Test-Path -LiteralPath $backup)) {
            throw "No backup exists for ${Name}: $backup"
        }
        Copy-Item -LiteralPath $backup -Destination $path -Force
        return
    }

    if (-not (Test-Path -LiteralPath $backup)) {
        Copy-Item -LiteralPath $path -Destination $backup
    }

    $text = [System.IO.File]::ReadAllText($path)
    $updated = & $Transform $text
    if ($updated -ne $text) {
        [System.IO.File]::WriteAllText($path, $updated, $utf8)
    }
}

$safeNormalize = @'
float3 safe_normalize(float3 v)
{
	float lenSq = dot(v, v);
	return lenSq > 1e-8 ? v * rsqrt(lenSq) : float3(0.0, 0.0, 0.0);
}

'@

Update-ShaderFile 'base-sm4.hlsl' {
    param($text)
    if ($text.Contains('float3 safe_normalize')) { return $text }
    $text = $safeNormalize + $text
    $text = $text.Replace('normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w))', 'safe_normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w))')
    $text = $text.Replace('reflect(normalize(vViewPosition), vViewNormal)', 'reflect(safe_normalize(vViewPosition), safe_normalize(vViewNormal))')
    $text = $text.Replace('normalize(mul(normalTex.xyz, tbn))', 'safe_normalize(mul(normalTex.xyz, tbn))')
    $text = $text.Replace('normalize(vViewNormal)', 'safe_normalize(vViewNormal)')
    $text = $text.Replace('reflect(normalize(viewPos), viewNormal)', 'reflect(safe_normalize(viewPos), viewNormal)')
    $text = $text.Replace('float d = length(pixelToLight);', 'float d = max(length(pixelToLight), 1e-6);')
    $text = $text.Replace('pixelToLight /= d;', 'pixelToLight *= rcp(d);')
    $text = $text.Replace('(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w))', 'max(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w), 1e-6)')
    $text = $text.Replace('normalize(-lightDirection[i].xyz)', 'safe_normalize(-lightDirection[i].xyz)')
    $text = $text.Replace('(spotLightParams[i].x - spotLightParams[i].y)', 'max(spotLightParams[i].x - spotLightParams[i].y, 1e-6)')
    return $text
}

Update-ShaderFile 'terrain-sm4.hlsl' {
    param($text)
    if ($text.Contains('float3 safe_normalize')) { return $text }
    $text = $safeNormalize + $text
    $text = $text.Replace('sqrt(1.0 - nNormal.x*nNormal.x - nNormal.y*nNormal.y)', 'sqrt(saturate(1.0 - nNormal.x*nNormal.x - nNormal.y*nNormal.y))')
    $text = $text.Replace('normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w))', 'safe_normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w))')
    $text = $text.Replace('reflect(normalize(vViewPosition), vViewNormal)', 'reflect(safe_normalize(vViewPosition), safe_normalize(vViewNormal))')
    $text = $text.Replace('normalize(mul(normalTex, tbn))', 'safe_normalize(mul(normalTex, tbn))')
    $text = $text.Replace('normalize(vViewNormal)', 'safe_normalize(vViewNormal)')
    $text = $text.Replace('reflect(normalize(viewPos), viewNormal)', 'reflect(safe_normalize(viewPos), viewNormal)')
    $text = $text.Replace('float d = length(pixelToLight);', 'float d = max(length(pixelToLight), 1e-6);')
    $text = $text.Replace('pixelToLight /= d;', 'pixelToLight *= rcp(d);')
    $text = $text.Replace('(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w))', 'max(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w), 1e-6)')
    $text = $text.Replace('normalize(-lightDirection[i].xyz)', 'safe_normalize(-lightDirection[i].xyz)')
    $text = $text.Replace('(spotLightParams[i].x - spotLightParams[i].y)', 'max(spotLightParams[i].x - spotLightParams[i].y, 1e-6)')
    return $text
}

Update-ShaderFile 'simple-sm4.hlsl' {
    param($text)
    if ($text.Contains('float3 safe_normalize')) { return $text }
    $text = $safeNormalize + $text
    $text = $text.Replace('normalize(-viewPos.xyz)', 'safe_normalize(-viewPos.xyz)')
    $text = $text.Replace('reflect(-eyeDir, viewNormal)', 'reflect(-eyeDir, safe_normalize(viewNormal))')
    $text = $text.Replace('float d = length(pixelToLight);', 'float d = max(length(pixelToLight), 1e-6);')
    $text = $text.Replace('pixelToLight /= d;', 'pixelToLight *= rcp(d);')
    $text = $text.Replace('(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w))', 'max(lightAttenuation[i].y + d * (lightAttenuation[i].z + d * lightAttenuation[i].w), 1e-6)')
    $text = $text.Replace('normalize(-lightDirection[i].xyz)', 'safe_normalize(-lightDirection[i].xyz)')
    $text = $text.Replace('(spotLightParams[i].x - spotLightParams[i].y)', 'max(spotLightParams[i].x - spotLightParams[i].y, 1e-6)')
    return $text
}

Update-ShaderFile 'DepthShadowmap-sm4.hlsl' {
    param($text)
    return $text.Replace('depth.x / depth.y', 'depth.x / max(abs(depth.y), 1e-6)')
}

Write-Output $(if ($Restore) { "Restored stock DX11 shaders in $shaderDir" } else { "Applied stock DX11 shader hardening in $shaderDir" })
