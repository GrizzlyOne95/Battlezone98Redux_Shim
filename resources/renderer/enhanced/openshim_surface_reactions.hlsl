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
    uniform float4x4 surfaceViewToLocal, uniform float surfaceRainTime, \
    uniform float4 surfaceSnow, uniform float4 surfaceDust,
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

// Procedural snow on upward faces. surfaceSnow: x cover amount, y snow albedo
// (linear, 0 = default 0.85), z blue tint, w reserved. Zero keeps the source.
float ose_snow_value(float2 p)
{
    float2 i = floor(p), f = frac(p);
    f = f * f * (3.0 - 2.0 * f);
    return lerp(lerp(ose_water_hash(i).x, ose_water_hash(i + float2(1, 0)).x, f.x),
                lerp(ose_water_hash(i + float2(0, 1)).x, ose_water_hash(i + float2(1, 1)).x, f.x), f.y);
}

// Two octaves, centred on zero. The caller picks the plane: object-local
// position for craft and buildings, the world-tiling UV for terrain.
float ose_snow_noise(float2 p)
{
    return ose_snow_value(p) * 0.65 + ose_snow_value(p * 3.7 + 0.37) * 0.35 - 0.5;
}

// Thruster wash w = (x, z, radius, strength): full inside half the radius,
// fading to the rim; edge (about -0.2..0.2) roughens the rim.
float ose_wash(float4 w, float2 xz, float edge)
{
    float d = length(xz - w.xy) / max(w.z, 0.001) + edge;
    return w.w * (1.0 - smoothstep(0.5, 1.0, d));
}

// up is the world-space normal's Y. More snow lowers the threshold so cover
// creeps from flat tops down onto slopes; noise breaks the line up.
float ose_snow_cover(float up, float noise, float amount)
{
    amount = saturate(amount);
    if (amount < 0.002) return 0.0;
    float threshold = lerp(1.05, 0.15, amount);
    return smoothstep(threshold, threshold + 0.25, up + noise * 0.30) * min(1.0, amount * 4.0);
}

// Dust: surfaceDust rgb is the linear dust colour, w the amount. Up-facing
// faces collect it first; sheltered (1 - AO exposure) and concave texels
// collect it even on slopes. Tops out at 75% so markings still read.
float ose_dust_cover(float up, float noise, float shelter, float concave, float amount)
{
    amount = saturate(amount);
    if (amount < 0.002) return 0.0;
    float settle = smoothstep(lerp(0.9, 0.1, amount), 1.0, up + noise * 0.35);
    float trapped = saturate(shelter * 1.2 + concave * 0.8) * smoothstep(-0.6, 0.3, up);
    return saturate(max(settle, trapped) * (0.55 + noise * 0.45)) * min(1.0, amount * 3.0) * 0.75;
}

// The dust keeps a third of the surface luminance pattern.
float3 ose_dust_blend(float3 surface, float3 dustColour, float cover)
{
    float luma = dot(surface, float3(0.299, 0.587, 0.114));
    return lerp(surface, dustColour * lerp(1.0, saturate(luma * 2.2), 0.33), cover);
}

// Object-space push (metres) for fully covered vertices.
static const float OSE_SNOW_THICKNESS = 0.07;

float3 ose_snow_albedo(float4 snow)
{
    float brightness = snow.y > 0.0 ? snow.y : 0.85;
    return brightness * lerp(float3(1.0, 1.0, 1.0), float3(0.86, 0.93, 1.0), saturate(snow.z));
}

// Snow over a surface: never a full white-out. Cover tops out at 80% and the
// snow keeps 40% of the surface luminance pattern, so diffuse detail, decals
// and seams still read through it.
float3 ose_snow_blend(float3 surface, float3 snowAlbedo, float cover)
{
    float luma = dot(surface, float3(0.299, 0.587, 0.114));
    float3 snowTex = snowAlbedo * lerp(1.0, saturate(luma * 2.5), 0.4);
    return lerp(surface, snowTex, cover * 0.8);
}

// Parallax ice: surfaceSnow.w is the ice depth in metres (0 = off). The UV
// offset is where the view ray, entering a flat surface at p, reaches that
// depth: the plane vector is mapped to UV through the screen-space gradients
// of uv (same basis as cotangent_frame). N and p are view space.
float2 ose_ice_parallax_uv(float3 N, float3 p, float2 uv, float depth)
{
    float3 dp1 = ddx(p);
    float3 dp2 = ddy(p);
    float2 duv1 = ddx(uv);
    float2 duv2 = ddy(uv);
    float3 dp2perp = cross(N, dp2);
    float3 dp1perp = cross(dp1, N);
    float det = dot(dp1, dp2perp);
    if (abs(det) < 1e-12) return float2(0.0, 0.0);
    float3 gradU = (dp2perp * duv1.x + dp1perp * duv2.x) / det;
    float3 gradV = (dp2perp * duv1.y + dp1perp * duv2.y) / det;
    float3 V = normalize(-p);
    float NdotV = dot(V, N);
    // Grazing views would slide the layer off the cell; 0.3 caps it at ~3x depth.
    float3 shift = -(V - N * NdotV) * (depth / max(NdotV, 0.3));
    return float2(dot(gradU, shift), dot(gradV, shift));
}

// Blue-dominant albedo reads as ice; rock, scorch and base pads stay opaque.
float ose_ice_mask(float3 albedo)
{
    return saturate((albedo.b - max(albedo.r, albedo.g * 0.92)) * 9.0);
}

static const float3 OSE_ICE_DEEP_TINT = float3(0.66, 0.82, 1.0);

float ose_surface_mask(float3 position, float4 anchor)
{
    float3 delta = position - anchor.xyz;
    float mask = saturate(1.0 - dot(delta, delta) / max(anchor.w * anchor.w, 0.000001));
    return mask * mask * step(0.001, anchor.w);
}

// Barrel heat: muzzle is the tip anchor, barrel the far end of the heated
// stretch (xyz) and barrel radius (w). The glow is even around the barrel and
// fades from full at the tip to nothing at that end. With no end point it
// falls back to the round tip mask.
float ose_barrel_mask(float3 position, float4 muzzle, float4 barrel)
{
    if (barrel.w < 0.001) return ose_surface_mask(position, muzzle);
    float3 axis = muzzle.xyz - barrel.xyz;
    float t = saturate(dot(position - barrel.xyz, axis) / max(dot(axis, axis), 0.000001));
    float distance = length(position - (barrel.xyz + axis * t));
    float ring = 1.0 - smoothstep(barrel.w * 0.65, barrel.w, distance);
    return ring * t * t * step(0.001, muzzle.w);
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
