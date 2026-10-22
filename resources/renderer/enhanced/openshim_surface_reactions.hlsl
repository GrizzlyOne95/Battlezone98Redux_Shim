// Per-material reactive presentation. Zero parameters preserve the source.
// Ordinary uniforms intentionally avoid missing Renderable custom-parameter
// carryover. The caller owns a clone for per-object damage, heat and impacts.
// Keep these in the entry point's uniform parameter list alongside the base
// lighting constants. Global uniforms create a separate $Globals cbuffer from
// HLSL's $Params; the retail Ogre DX11 path cannot bind that layout correctly.
// Enhanced programs only: Stock/Retro declare none of these uniforms.
#if defined(ENHANCED_MODE)
#define OSE_SURFACE_UNIFORMS \
    uniform float4 surfaceState, uniform float4 surfaceMode, \
    uniform float4 surfaceImpact0, uniform float4 surfaceImpact1, \
    uniform float4 surfaceImpactWeights, \
    uniform float4 surfaceMuzzle0, uniform float4 surfaceMuzzle1, \
    uniform float4 surfaceBarrel0, uniform float4 surfaceBarrel1, \
    uniform float4x4 surfaceViewToLocal, uniform float surfaceRainTime,
#else
#define OSE_SURFACE_UNIFORMS
#endif
#define OSE_SURFACE_VALUES \
    float4 surfaceState, float4 surfaceMode, \
    float4 surfaceImpact0, float4 surfaceImpact1, \
    float4 surfaceImpactWeights, float4 surfaceMuzzle0, float4 surfaceMuzzle1, \
    float4 surfaceBarrel0, float4 surfaceBarrel1, \
    float4x4 surfaceViewToLocal
#define OSE_SURFACE_ARGUMENTS \
    surfaceState, surfaceMode, surfaceImpact0, surfaceImpact1, \
    surfaceImpactWeights, surfaceMuzzle0, surfaceMuzzle1, \
    surfaceBarrel0, surfaceBarrel1, surfaceViewToLocal
// Ogre supplies the current draw's inverse transform. Passing view position
// makes the masks work with CPU vertices and world-space GPU-skinned vertices.

float2 ose_water_hash(float2 cell)
{
    float3 p = frac(float3(cell.x, cell.y, cell.x) * float3(0.1031, 0.1030, 0.0973));
    p += dot(p, p.yzx + 33.33);
    return frac((p.xx + p.yz) * p.zy);
}

// One bead layer. About half the cells stay dry and the rest vary in size,
// so the pattern does not read as a grid.
float ose_water_bead(float2 grid)
{
    float2 cell = floor(grid);
    float2 random = ose_water_hash(cell);
    float2 extra = ose_water_hash(cell + 71.37);
    float size = (0.45 + extra.y * 0.55) * step(0.55, extra.x);
    float2 delta = (frac(grid) - (0.25 + random * 0.5)) / (float2(0.15, 0.19) * max(size, 0.001));
    float bead = saturate(1.0 - dot(delta, delta)) * step(0.001, size);
    bead *= bead;
    // Derivative filtering removes subpixel beads before they glitter.
    return bead * (1.0 - smoothstep(0.25, 0.75, max(fwidth(grid.x), fwidth(grid.y))));
}

// Near High-quality Enhanced objects only. One procedural height evaluation,
// no textures, passes, particles or CPU animation. Derivative filtering removes
// subpixel beads before they can glitter on distant craft.
float3 ose_water_normal(float3 viewPosition, float3 normal, float wetness,
                        float4x4 viewToLocal, float clock, out float4 water)
{
    water = 0.0;
    float nearFade = 1.0 - smoothstep(12.0, 28.0, length(viewPosition));
    // Uniform-only early out: every derivative below runs before any per-pixel
    // branch, so quads straddling the fade distance keep valid gradients.
    if (wetness < 0.002) return normal;
    float3 local = mul(viewToLocal, float4(viewPosition, 1.0)).xyz;
    float3 geometric = abs(cross(ddx(local), ddy(local)));
    bool top = geometric.y >= max(geometric.x, geometric.z);
    float2 plane = top ? local.xz : (geometric.z >= geometric.x ? local.xy : local.zy);
    // Two sparse layers at unrelated scales and a rotation hide both lattices.
    float2 rotated = float2(plane.x * 0.8 - plane.y * 0.6, plane.x * 0.6 + plane.y * 0.8);
    float bead = max(ose_water_bead(plane * 19.0), ose_water_bead(rotated * 27.0 + 0.37));
    // Local Y is down the upright hull. Horizontal decks retain beads;
    // vertical faces get sparse narrow trails and a moving runoff head.
    float column = plane.x * 3.7;
    float2 columnRandom = ose_water_hash(float2(floor(column), 19.0));
    float trailWidth = 0.045 + columnRandom.y * 0.025;
    float meander = sin(plane.y * 7.0 + clock * 0.9 + columnRandom.y * 6.28) * 0.035;
    float trailDistance = abs(frac(column) - (0.20 + columnRandom.x * 0.60 + meander));
    float trail = 1.0 - smoothstep(trailWidth, trailWidth + max(fwidth(column), 0.015), trailDistance);
    float flow = frac(plane.y * 0.65 + clock * 0.24 + columnRandom.y);
    float head = smoothstep(0.70, 0.94, flow) * (1.0 - smoothstep(0.94, 1.0, flow));
    float run = trail * (0.25 + head * 0.75) * (top ? 0.55 : 1.0);
    float strength = wetness * nearFade;
    water = float4((bead * 0.4 + run * 0.8) * strength,
                   bead * (1.0 - bead) * 4.0,
                   run, strength);
    float height = (bead * 0.0018 + run * 0.0012) * strength;
    // Surface-gradient bump mapping retains the authored normal and UV art.
    float3 dx = ddx(viewPosition), dy = ddy(viewPosition);
    float3 r1 = cross(dy, normal), r2 = cross(normal, dx);
    float determinant = dot(dx, r1);
    float3 gradient = (r1 * ddx(height) + r2 * ddy(height)) *
        (sign(determinant) / max(abs(determinant), 0.000001));
    gradient *= min(1.0, 0.30 * rsqrt(max(dot(gradient, gradient), 0.000001)));
    float3 result = normal - gradient;
    if (nearFade <= 0.0) { water = 0.0; return normal; }
    return result * rsqrt(max(dot(result, result), 0.000001));
}

float ose_surface_mask(float3 position, float4 anchor)
{
    float3 delta = position - anchor.xyz;
    float mask = saturate(1.0 - dot(delta, delta) / max(anchor.w * anchor.w, 0.000001));
    return mask * mask * step(0.001, anchor.w);
}

// Barrel heat: muzzle is the tip anchor, barrel the mount (xyz) and barrel
// radius (w). The glow is even around the barrel from mount to tip, a little
// hotter at the tip. With no mount it falls back to the round tip mask.
float ose_barrel_mask(float3 position, float4 muzzle, float4 barrel)
{
    if (barrel.w < 0.001) return ose_surface_mask(position, muzzle);
    float3 axis = muzzle.xyz - barrel.xyz;
    float t = saturate(dot(position - barrel.xyz, axis) / max(dot(axis, axis), 0.000001));
    float distance = length(position - (barrel.xyz + axis * t));
    float ring = 1.0 - smoothstep(barrel.w * 0.65, barrel.w, distance);
    return ring * lerp(0.55, 1.0, t) * step(0.001, muzzle.w);
}

float3 ose_surface_finish(float3 source, float3 local, float2 uv, out float3 glow,
                         OSE_SURFACE_VALUES)
{
    glow = 0.0;
    if (dot(abs(surfaceState.xyz), float3(1, 1, 1)) + abs(surfaceMode.x) +
        dot(abs(surfaceImpactWeights.xy), float2(1, 1)) < 0.0001) return source;
    float wet = saturate(surfaceState.x);
    float damage = saturate(surfaceState.y);
    float fragment = saturate(surfaceMode.x);
    // Rain-only objects take the short path: no scorch/noise/anchor work.
    if (damage + fragment + abs(surfaceState.z) +
        dot(abs(surfaceImpactWeights.xy), float2(1, 1)) < 0.0001)
        return source * (1.0 - wet * 0.10);
    float noise = frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
    if (abs(surfaceState.z) + dot(abs(surfaceImpactWeights.xy),float2(1,1)) > 0.0001)
        local = mul(surfaceViewToLocal,float4(local,1.0)).xyz;
    float burnt = fragment * (0.35 + noise * 0.30);
    float luminance = dot(source, float3(0.2126, 0.7152, 0.0722));
    source = lerp(source, luminance.xxx, burnt * 0.55);
    source *= 1.0 - burnt * 0.60 - wet * 0.10;

    float impact = saturate(ose_surface_mask(local, surfaceImpact0) * surfaceImpactWeights.x +
        ose_surface_mask(local, surfaceImpact1) * surfaceImpactWeights.y);
    source *= 1.0 - impact * (0.40 + noise * 0.16);

    // Fine surface damage keeps the original panels, markings and instruments.
    float scratches = smoothstep(0.965, 0.995, frac(uv.x * 91.0 + sin(uv.y * 31.0) * 0.55));
    source *= 1.0 - damage * (0.10 + scratches * 0.45);
    float muzzle = max(ose_barrel_mask(local, surfaceMuzzle0, surfaceBarrel0),
                       ose_barrel_mask(local, surfaceMuzzle1, surfaceBarrel1));
    float heat = saturate(surfaceState.z);
    // Linear emission: dull red when warm, orange near the cap. The old
    // heat^2 * 0.13 peaked near 0.05 and could not be seen beside the flash.
    glow = lerp(float3(0.90, 0.12, 0.01), float3(1.0, 0.38, 0.06), heat) * (heat * muzzle * 1.5);
    // Short-lived chunks: restrained hot cracks, not an opaque replacement.
    glow += float3(0.48, 0.075, 0.008) * fragment * smoothstep(0.91, 0.99, noise) * 0.32;
    return max(source, 0.0);
}

float ose_surface_emissive_scale(float4 surfaceState, float4 surfaceMode)
{
    float off = saturate(surfaceState.w);
    float damage = saturate(surfaceState.y) * saturate(surfaceMode.y);
    // Smooth warning pulse; the controller also uses this clock for repair.
    float pulse = 0.5 + 0.5 * sin(surfaceMode.z * 7.0);
    return (1.0 - off) * (1.0 - damage * (0.12 + pulse * 0.58));
}
