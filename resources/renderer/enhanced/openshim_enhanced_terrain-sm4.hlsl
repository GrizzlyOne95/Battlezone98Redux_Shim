// DX11 SM4 terrain shader path for the OpenShim canonical Enhanced renderer.
// Enhanced mode uses the experimental legacy-compatible GGX direct-lighting model.
// IBL_ENABLED layers static split-sum image-based lighting onto that DX11 path.
// Keep shared PBR helpers synchronized with openshim_enhanced_base-sm4.hlsl.

// Force OG retro mode to ignore modern map contributions even if a program
// variant accidentally leaves those feature defines enabled.

// Compile-time atmosphere diagnostics. Runtime builds leave this disabled.
// 0 = normal rendering, 1 = total fog, 2 = height contribution,
// 3 = sun scattering, 4 = resolved atmosphere colour.
#ifndef OSE_ATMOS_DEBUG_MODE
#define OSE_ATMOS_DEBUG_MODE 0
#endif

// -----------------------------------------------------------------------------
// Stage A linear-light experiment (DX11 Enhanced only)
// -----------------------------------------------------------------------------
// Keep this block synchronized with openshim_enhanced_base-sm4.hlsl.
//
// 0 = unchanged baseline. This is the default and the compatibility path.
// 1 = experimental. Artist-authored COLOR textures are decoded sRGB -> linear at
//     the sample, the existing Enhanced lighting/GGX/IBL/emissive/atmosphere
//     maths run on those linear values, and the final RGB is encoded
//     linear -> sRGB exactly once before it reaches the ordinary UNORM target.
//
// The runtime DX11 capture recorded an R8G8B8A8_UNORM swapchain/backbuffer, no
// _SRGB resource/SRV/RTV anywhere in the pipeline, and Ogre reporting
// "sRGB Gamma Conversion = No". Nothing in the hardware path performs either
// conversion for us, so Stage A does both explicitly in the shader.
//
// Terrain detail is deliberately excluded from the decode list; see the detail
// sampling site below. See Docs/DX11_COLOR_SPACE_AUDIT.md.
#ifndef OSE_LINEAR_LIGHT
#define OSE_LINEAR_LIGHT 0
#endif

// Stage A is scoped to the Enhanced per-pixel path only. The decode and the
// single final encode must bracket exactly the same region, otherwise a variant
// could linearize its albedo and then never re-encode it. Vertex-lighting
// delegates, Retro, Default and the DX9/GL paths therefore never see a transfer
// function.
#if defined(ENHANCED_MODE) && !defined(VERTEX_LIGHTING) \
 && !defined(OG_RETRO_MODE) && !defined(RETRO_UNLIT_MODE) \
 && (OSE_LINEAR_LIGHT != 0)
#define OSE_LINEAR_LIGHT_ACTIVE 1
#else
#define OSE_LINEAR_LIGHT_ACTIVE 0
#endif

// -----------------------------------------------------------------------------
// Terrain-normal diagnostics (DX11 SM4 test permutations only)
// -----------------------------------------------------------------------------
// Production defaults preserve BZR's full-RGB tangent normal convention.
// Override these from a temporary .program preprocessor_defines entry while
// diagnosing a map, then restore all four to zero for normal play.
//
// OSE_TERRAIN_NORMAL_UNPACK_MODE:
//   0 = RGB -> XYZ (stock BZR/CR convention)
//   1 = RG  -> XY, reconstruct +Z (BC5-style diagnostic)
//   2 = AG  -> XY, reconstruct +Z (DXT5nm-style diagnostic)
// OSE_TERRAIN_NORMAL_FLIP_GREEN:
//   0 = preserve Y; 1 = negate tangent-space Y
// OSE_TERRAIN_NORMAL_BASIS_MODE:
//   0 = stock derivative/vertex TBN
//   1 = normalize each TBN axis independently
//   2 = orthonormalize derivative TBN while preserving handedness
//   3 = geometry normal only (sample still occurs; bypass map and TBN result)
//   4 = treat tangent normal as a view-space normal (bypass TBN only)
// OSE_TERRAIN_NORMAL_DEBUG_MODE:
//   0 = normal rendering
//   1 = raw sampled RGB
//   2 = raw sampled alpha (grayscale)
//   3 = unpacked tangent-space normal, remapped to [0,1]
//   4 = final post-TBN lighting-space normal, remapped to [0,1]
//   5 = first-light NdotL (grayscale)
//   6 = geometry normal, remapped to [0,1]
//   7 = normalized TBN tangent axis, remapped to [0,1]
//   8 = normalized TBN bitangent axis, remapped to [0,1]
//   9 = TBN pairwise orthogonality error (RGB; black is ideal)
//  10 = T length, B length, normalized-basis determinant (RGB; white is ideal)
//  11 = mapped-normal deviation from geometry normal (grayscale)
#ifndef OSE_TERRAIN_NORMAL_UNPACK_MODE
#define OSE_TERRAIN_NORMAL_UNPACK_MODE 0
#endif
#ifndef OSE_TERRAIN_NORMAL_FLIP_GREEN
#define OSE_TERRAIN_NORMAL_FLIP_GREEN 0
#endif
#ifndef OSE_TERRAIN_NORMAL_BASIS_MODE
#define OSE_TERRAIN_NORMAL_BASIS_MODE 0
#endif
#ifndef OSE_TERRAIN_NORMAL_DEBUG_MODE
#define OSE_TERRAIN_NORMAL_DEBUG_MODE 0
#endif

// -----------------------------------------------------------------------------
// Radial smooth fog (DX11 Enhanced only)
// -----------------------------------------------------------------------------
// Keep this block synchronized with openshim_enhanced_base-sm4.hlsl.
//
// 0 = unchanged baseline: the exponential optical-depth model.
// 1 = the fog factor is derived from true radial view-space distance with a
//     Hermite (smoothstep) falloff between the authored fog start and end.
//
// This changes only how the fog *factor* is computed. The authored fog start,
// end and colour keep their existing meanings, the height and horizon density
// modulation still applies, and every other part of the Phase 3 atmosphere -
// sun scattering, aerial desaturation, emissive transmission - is untouched.
//
// Two things are wrong with the baseline curve. It reaches only ~0.93 at the
// authored fog end and then keeps thickening past it, so "end" is not actually
// where fog becomes opaque; and because opticalDepth grows quadratically the
// approach to full fog is slow and the far field stays milky rather than
// resolving. Smoothstep pins the curve to 0 at fogStart and exactly 1 at
// fogEnd, with zero first derivative at both, which is the same shape BZCC
// uses and is what removes the visible banding at the fog onset.
#ifndef OSE_RADIAL_FOG
#define OSE_RADIAL_FOG 0
#endif

// DX11 Enhanced PSSM v2. Keep this block synchronized with openshim_enhanced_base-sm4.hlsl.
#ifndef OSE_ENHANCED_PSSM_V2
#define OSE_ENHANCED_PSSM_V2 0
#endif

#if defined(ENHANCED_MODE) && defined(SHADOWRECEIVER) \
 && defined(PSSM_ENABLED) && (OSE_ENHANCED_PSSM_V2 != 0)
#define OSE_ENHANCED_PSSM_V2_ACTIVE 1
#else
#define OSE_ENHANCED_PSSM_V2_ACTIVE 0
#endif

#define OSE_PSSM_CASCADE_BLEND_HALF_WIDTH 1.0
#define OSE_PSSM_FAR_FADE_WIDTH 24.0
#define OSE_PSSM_NORMAL_OFFSET_BASE 0.04
#define OSE_PSSM_NORMAL_OFFSET_PER_DEPTH 0.0002
#define OSE_PSSM_NORMAL_OFFSET_MAX 0.10

// Scoped exactly like Stage A: the Enhanced per-pixel path only. The legacy
// fog in the #else branch of the fragment shaders is depth-based and stays
// that way, so Default, Retro, vertex-lighting delegates and the DX9/GL paths
// cannot acquire radial fog.
#if defined(ENHANCED_MODE) && !defined(VERTEX_LIGHTING) \
 && !defined(OG_RETRO_MODE) && !defined(RETRO_UNLIT_MODE) \
 && (OSE_RADIAL_FOG != 0)
#define OSE_RADIAL_FOG_ACTIVE 1
#else
#define OSE_RADIAL_FOG_ACTIVE 0
#endif

#if defined(OG_RETRO_MODE)
#undef NORMALMAP_ENABLED
#undef SPECULARMAP_ENABLED
#undef SPECULAR_ENABLED
#undef EMISSIVEMAP_ENABLED
#undef IBL_ENABLED
#endif

// IBL is intentionally an Enhanced DX11 extension, never a standalone mode.
#if defined(IBL_ENABLED) && !defined(ENHANCED_MODE)
#undef IBL_ENABLED
#endif

#if defined(SHADOWRECEIVER)
// -----------------------------------------------------------------------------
// Shadow depth bias
// -----------------------------------------------------------------------------
// The caster writes raw post-projection depth and this receiver compared it raw,
// with no constant bias, no slope-scaled term and no normal offset. A surface
// then shadows itself wherever its own interpolated depth quantises to just
// behind the depth stored in the map.
//
// The error scales with how far the receiver's depth travels across one shadow
// texel, which is proportional to tan(angle between the surface normal and the
// light). Hence a constant floor plus a slope-scaled term. tan grows without
// bound at grazing incidence, so the slope is clamped -- unclamped it produces
// the opposite artefact, shadows visibly detaching from their casters.
//
// These are in post-projection depth units, where the whole cascade spans
// 0..1, so they are deliberately small. NOT VALIDATED IN GAME: this profile
// runs the 'high-noshadow' viewport scheme, so PCF_Filter never executes and
// there was no acne to photograph. Treat the defaults as a starting point --
// raise OSE_SHADOW_CONSTANT_BIAS if acne survives, lower it if shadows detach
// from their casters near contact points.
static const float OSE_SHADOW_CONSTANT_BIAS = 0.0015;
static const float OSE_SHADOW_SLOPE_BIAS    = 0.0035;
static const float OSE_SHADOW_MAX_SLOPE     = 4.0;

// NdotL is the geometric surface-to-light cosine, not the normal-mapped one:
// biasing by a perturbed normal would make the bias vary with texture detail
// and reintroduce acne along normal-map edges.
float shadow_depth_bias(float NdotL)
{
    float cosine = max(NdotL, 0.05);
    float slope  = sqrt(saturate(1.0 - cosine * cosine)) / cosine;
    return OSE_SHADOW_CONSTANT_BIAS
         + OSE_SHADOW_SLOPE_BIAS * min(slope, OSE_SHADOW_MAX_SLOPE);
}

#if OSE_ENHANCED_PSSM_V2_ACTIVE
float PCF_Filter(
    in Texture2D map,
    in SamplerComparisonState sam,
    in float4 uv,
    in float2 invMapSize,
    in float depthBias)
{
    if (abs(uv.w) <= 1e-6)
        return 1.0;

    uv.xyz *= rcp(uv.w);
    // Bias after the perspective divide, so it is applied in the same
    // normalised depth space the shadow map stores.
    uv.z = min(uv.z - depthBias, 1.0);
    invMapSize = max(invMapSize, float2(1e-8, 1e-8));

    float2 halfTexel = invMapSize * 0.5;
    float result = 0.0;
    result += map.SampleCmpLevelZero(sam, uv.xy + float2(-halfTexel.x, -halfTexel.y), uv.z);
    result += map.SampleCmpLevelZero(sam, uv.xy + float2( halfTexel.x, -halfTexel.y), uv.z);
    result += map.SampleCmpLevelZero(sam, uv.xy + float2(-halfTexel.x,  halfTexel.y), uv.z);
    result += map.SampleCmpLevelZero(sam, uv.xy + float2( halfTexel.x,  halfTexel.y), uv.z);
    return result * 0.25;
}
#else
float PCF_Filter(
    in Texture2D map,
    in SamplerState sam,
    in float4 uv,
    in float2 invMapSize,
    in float depthBias)
{
    if (abs(uv.w) <= 1e-6)
        return 1.0;

    uv.xyz *= rcp(uv.w);
    uv.w = 1.0;
    uv.z = min(uv.z - depthBias, 1.0);
    invMapSize = max(invMapSize, float2(1e-8, 1e-8));

#if PCF_SIZE > 1
    float2 pixel = uv.xy / invMapSize - float2(float(PCF_SIZE - 1) * 0.5, float(PCF_SIZE - 1) * 0.5);
    float2 c = floor(pixel);
    float2 f = frac(pixel);

    float kernel[PCF_SIZE * PCF_SIZE];
    {
        [unroll] for (int y = 0; y < PCF_SIZE; ++y)
        {
            [unroll] for (int x = 0; x < PCF_SIZE; ++x)
            {
                int i = y * PCF_SIZE + x;
                kernel[i] = step(uv.z, map.Sample(sam, (c + float2(x, y)) * invMapSize).x);
            }
        }
    }

    float4 sum = float4(0.0, 0.0, 0.0, 0.0);
    {
        [unroll] for (int y = 0; y < PCF_SIZE - 1; ++y)
        {
            [unroll] for (int x = 0; x < PCF_SIZE - 1; ++x)
            {
                int i = y * PCF_SIZE + x;
                sum += float4(kernel[i], kernel[i + 1], kernel[i + PCF_SIZE], kernel[i + PCF_SIZE + 1]);
            }
        }
    }

    return lerp(lerp(sum.x, sum.y, f.x), lerp(sum.z, sum.w, f.x), f.y)
        / float((PCF_SIZE - 1) * (PCF_SIZE - 1));
#else
    return step(uv.z, map.Sample(sam, uv.xy).x);
#endif
}
#endif
#endif

#if defined(NORMALMAP_ENABLED) && !defined(VERTEX_TANGENTS)
float3x3 cotangent_frame(float3 N, float3 p, float2 uv)
{
    float3 dp1 = ddx(p);
    float3 dp2 = ddy(p);
    float2 duv1 = ddx(uv);
    float2 duv2 = ddy(uv);

    float3 dp2perp = cross(N, dp2);
    float3 dp1perp = cross(dp1, N);
    float3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    float3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    float invmax = rsqrt(max(max(dot(T, T), dot(B, B)), 1e-20));
    T *= invmax;
    B *= invmax;

#if OSE_TERRAIN_NORMAL_BASIS_MODE == 1
    // The stock cotangent frame applies one common scale. This diagnostic
    // removes only the resulting T/B length imbalance without changing their
    // directions or handedness.
    T *= rsqrt(max(dot(T, T), 1e-20));
    B *= rsqrt(max(dot(B, B), 1e-20));
    N *= rsqrt(max(dot(N, N), 1e-20));
#elif OSE_TERRAIN_NORMAL_BASIS_MODE == 2
    // Gram-Schmidt the derivative tangent against the geometry normal, then
    // rebuild B while preserving the orientation of the original derivative B.
    // This is diagnostic-only until a live A/B proves the stock frame is bad.
    float3 sourceB = B;
    N *= rsqrt(max(dot(N, N), 1e-20));
    T -= N * dot(T, N);
    T *= rsqrt(max(dot(T, T), 1e-20));
    float3 orthogonalB = cross(T, N);
    float handedness = (dot(orthogonalB, sourceB) < 0.0) ? -1.0 : 1.0;
    B = orthogonalB * handedness;
    B *= rsqrt(max(dot(B, B), 1e-20));
#endif
    return float3x3(T, B, N);
}
#endif

float3 safe_normalize(float3 v)
{
    float lenSq = dot(v, v);
    return (lenSq > 1e-8) ? v * rsqrt(lenSq) : float3(0.0, 0.0, 0.0);
}

float luminance_legacy(float3 c)
{
    return dot(c, float3(0.299, 0.587, 0.114));
}

// -----------------------------------------------------------------------------
// Detail normals
// -----------------------------------------------------------------------------
// The terrain normal atlas is sampled at 1x UV across an entire map. A few
// metres from the ground it is magnified enormously and contributes no relief at
// all, which is why the near field reads smeared and flat while the mid-range --
// where the atlas still has texel density -- reads well. The detail map is
// already tiled at 8x and 32x for brightness, so deriving a normal from its
// luminance gradient puts high-frequency relief exactly where the atlas has
// none. Every shipped *_detail.dds is 2048x2048 DXT1, so one texel constant
// covers all of them and no new asset or material edit is needed.
//
// Luminance is a height PROXY, not a height map: on a photographic regolith scan
// that holds up at this scale, but a dark patch is not necessarily a pit, so the
// strengths are deliberately conservative. A negative strength inverts the
// relief (bumps become pits) if the interpretation reads backwards.
//
// No distance fade. Mip-mapping already collapses the gradient toward zero as
// the sampling footprint grows, which is the correct LOD behaviour and needs no
// help. A hand-rolled depth fade here would be a camera term on a surface
// normal, which is exactly what made the shading swim over static ground before.
static const float OSE_TERRAIN_DETAIL_TEXEL = 1.0 / 2048.0;
static const float OSE_TERRAIN_DETAIL_NORMAL_STRENGTH = 2.2;
// The 32x layer resolves finer features, so the same luminance delta implies a
// steeper slope; it is scaled back so the near field gains texture without the
// ground turning to gravel.
static const float OSE_TERRAIN_DETAIL_NORMAL_NEAR_SCALE = 0.55;

float3 detail_normal_from_luminance(Texture2D tex, SamplerState sam,
                                    float2 uv, float strength)
{
    float2 e = float2(OSE_TERRAIN_DETAIL_TEXEL, 0.0);
    float hl = luminance_legacy(tex.Sample(sam, uv - e.xy).xyz);
    float hr = luminance_legacy(tex.Sample(sam, uv + e.xy).xyz);
    float hd = luminance_legacy(tex.Sample(sam, uv - e.yx).xyz);
    float hu = luminance_legacy(tex.Sample(sam, uv + e.yx).xyz);
    // Central differences give the surface gradient. Scaling xy rather than the
    // whole vector scales the SLOPE and keeps the result a unit normal, the same
    // reason sharpen_terrain_normal divides z instead of multiplying xy.
    return safe_normalize(float3((hl - hr) * strength, (hd - hu) * strength, 1.0));
}

// Whiteout blend: sums surface gradients rather than the vectors themselves, so
// the base shape survives instead of being averaged toward flat. Adding and
// renormalising two normals destroys exactly the relief this is meant to add.
float3 blend_detail_normal(float3 base, float3 detail)
{
    return safe_normalize(float3(base.xy * detail.z + detail.xy * base.z,
                                 base.z * detail.z));
}

#if OSE_LINEAR_LIGHT_ACTIVE
// Piecewise IEC 61966-2-1 sRGB transfer functions. Keep identical to
// openshim_enhanced_base-sm4.hlsl. These are deliberately the real piecewise curves, not
// pow(x, 2.2) / pow(x, 1/2.2) approximations, so the A/B experiment measures a
// correct decode rather than an approximation error.
//
// RGB only. Alpha is coverage/mask data, is never display-encoded, and must
// never be passed through either function.
//
// Inputs are clamped to >= 0 before any fractional pow(). lerp() evaluates both
// segments, so an unclamped negative or denormal texel would otherwise be able
// to produce a NaN in the unselected branch and still poison the result.
float3 srgb_to_linear(float3 c)
{
    c = max(c, 0.0);
    float3 low = c / 12.92;
    float3 high = pow((c + 0.055) / 1.055, 2.4);
    return lerp(low, high, step(0.04045, c));
}

float3 linear_to_srgb(float3 c)
{
    c = max(c, 0.0);
    float3 low = c * 12.92;
    float3 high = 1.055 * pow(max(c, 1e-8), 1.0 / 2.4) - 0.055;
    return lerp(low, high, step(0.0031308, c));
}
#endif

float3 unpack_terrain_normal(float4 packedNormal)
{
#if OSE_TERRAIN_NORMAL_UNPACK_MODE == 1
    float2 xy = packedNormal.rg * 2.0 - 1.0;
    float3 normal = float3(xy, sqrt(saturate(1.0 - dot(xy, xy))));
#elif OSE_TERRAIN_NORMAL_UNPACK_MODE == 2
    float2 xy = packedNormal.ag * 2.0 - 1.0;
    float3 normal = float3(xy, sqrt(saturate(1.0 - dot(xy, xy))));
#else
    float3 normal = packedNormal.rgb * 2.0 - 1.0;
#endif

#if OSE_TERRAIN_NORMAL_FLIP_GREEN != 0
    normal.y = -normal.y;
#endif
    return normal;
}

// -----------------------------------------------------------------------------
// Detail-map modulation range
// -----------------------------------------------------------------------------
// The detail map is modulation, not colour: the "* 2.0" makes a stored 0.5 the
// neutral 1.0 multiplier. But mn_detail.dds is a photographic regolith scan
// whose dark tail runs all the way to 0.0, and 0.0 * 2.0 is a multiplier of
// EXACTLY ZERO -- the terrain colour is annihilated, not darkened. Measured on
// the shipped 2048x2048 map: 3.83% of texels darken by more than half, 0.40% by
// more than three quarters, and 0.007% force pure black.
//
// Tiled at 8x it is magnified hard in the near field, so that tail stops being
// per-texel grain and becomes contiguous black pools several hundred pixels
// across -- the "black water" on the ground in front of the cockpit. It is
// backend-independent (DX9 shows it identically) and predates the sharpening
// work; sharpening only raised surrounding contrast so it read louder.
//
// Compressing the modulation toward neutral keeps the grain and removes the
// annihilation: at 0.55 the worst texel darkens to 0.45x instead of 0.0x, and
// the bright tail is pulled in from 2.0x to 1.55x by the same amount. Raise
// toward 1.0 to restore the original (broken) range.
static const float OSE_TERRAIN_DETAIL_CONTRAST = 0.55;

// Takes the raw sampled detail texel; returns the brightness multiplier.
float3 detail_modulation(float3 rawDetail)
{
    return 1.0 + (rawDetail * 2.0 - 1.0) * OSE_TERRAIN_DETAIL_CONTRAST;
}

#if defined(ENHANCED_MODE)
// -----------------------------------------------------------------------------
// Legacy-PBR calibration. Keep synchronized with openshim_enhanced_base-sm4.hlsl.
// -----------------------------------------------------------------------------
static const float OSE_PI = 3.14159265359;
static const float OSE_PBR_MIN_ROUGHNESS = 0.12;
static const float OSE_PBR_MAX_ROUGHNESS = 0.92;
static const float OSE_PBR_SHININESS_SCALE = 1.00;
static const float OSE_PBR_SPECULAR_ROUGHNESS_INFLUENCE = 0.10;
static const float OSE_PBR_NORMAL_VARIANCE_SCALE = 0.30;
static const float OSE_PBR_MAX_VARIANCE_ROUGHNESS = 0.35;
static const float OSE_PBR_DEFAULT_F0 = 0.04;
static const float OSE_PBR_MAX_LEGACY_F0 = 0.45;
static const float OSE_PBR_DIFFUSE_COMPENSATION = 2.70;
static const float OSE_PBR_SPECULAR_COMPENSATION = 1.00;

// Static IBL calibration. Keep synchronized with openshim_enhanced_base-sm4.hlsl, including the
// OSE_LINEAR_LIGHT_ACTIVE split: the intensities are transfer-function dependent
// and are not interchangeable between the two paths.
#if OSE_LINEAR_LIGHT_ACTIVE
static const float OSE_IBL_DIFFUSE_INTENSITY = 0.20;
static const float OSE_IBL_SPECULAR_INTENSITY = 0.25;
#else
static const float OSE_IBL_DIFFUSE_INTENSITY = 0.62;
static const float OSE_IBL_SPECULAR_INTENSITY = 0.82;
#endif
static const float OSE_IBL_LEGACY_AMBIENT_RETAIN = 0.20;
static const float OSE_IBL_SCENE_TINT_STRENGTH = 0.18;
static const float OSE_IBL_MAX_SPECULAR_MIP = 7.0;
// A 160-unit fog transition is the reference for a fully atmosphere-supported
// terrain diffuse floor. Airless/long-range environments retain a small floor
// for legibility without filling every lunar valley with neutral light.
static const float OSE_TERRAIN_IBL_REFERENCE_FOG_RANGE = 160.0;
static const float OSE_TERRAIN_IBL_AIRLESS_FLOOR = 0.15;

// -----------------------------------------------------------------------------
// DX11 Enhanced Atmospheric Calibration
// -----------------------------------------------------------------------------
// Ogre fog_params are consumed as density/start/end/inverse-range. Enhanced
// atmosphere deliberately preserves start/end/range as the authored mission
// control instead of replacing them with one global density.
static const float OSE_ATMOS_DISTANCE_DENSITY_SCALE = 1.65;
static const float OSE_ATMOS_HEIGHT_FALLOFF = 0.0035;
static const float OSE_ATMOS_HEIGHT_STRENGTH = 0.22;
static const float OSE_ATMOS_HORIZON_STRENGTH = 0.18;
static const float OSE_ATMOS_HORIZON_POWER = 3.0;
static const float OSE_ATMOS_SUN_SCATTER_POWER = 7.0;
static const float OSE_ATMOS_SUN_SCATTER_STRENGTH = 0.28;
static const float OSE_ATMOS_AMBIENT_TINT_STRENGTH = 0.16;
static const float OSE_ATMOS_SUN_TINT_STRENGTH = 0.28;
static const float OSE_ATMOS_AERIAL_DESATURATION = 0.08;
static const float OSE_ATMOS_EMISSIVE_TRANSMISSION = 0.38;
static const float OSE_ATMOS_MAX_OPTICAL_DEPTH = 12.0;

float compute_distance_optical_depth(float viewDistance, float4 fogParams)
{
    float fogStart = max(fogParams.y, 0.0);
    float fogEnd = max(fogParams.z, fogStart);
    float authoredRange = max(fogEnd - fogStart, 1e-3);
    float suppliedInvRange = abs(fogParams.w);
    float invRange = (suppliedInvRange > 1e-8) ? suppliedInvRange : rcp(authoredRange);
    invRange = min(invRange, 1e3);

    // A zero inverse range is how the legacy path effectively disables fog.
    // Keep that as the atmosphere master-strength signal for airless/light-fog maps.
    float configured = (fogEnd > fogStart + 1e-3 && suppliedInvRange > 1e-8) ? 1.0 : 0.0;
    float normalizedTravel = max(viewDistance - fogStart, 0.0) * invRange;
    float scaledTravel = min(normalizedTravel * OSE_ATMOS_DISTANCE_DENSITY_SCALE, 4.0);
    return min(scaledTravel * scaledTravel, OSE_ATMOS_MAX_OPTICAL_DEPTH) * configured;
}

// Radial view-space fog factor. Shared verbatim with openshim_enhanced_base-sm4.hlsl.
//
// The legacy fog in the non-Enhanced branch uses vDepth, which is clip-space z
// and therefore measures distance along the view axis only. Fog computed that
// way changes as the camera yaws, because a fragment at a fixed distance from
// the eye moves closer to or further from the view plane as it swings across
// the screen. viewPosition is the camera-space position of the fragment, so
// its length is the true eye-to-fragment distance and the fog shell is
// spherical rather than planar. That is the "radial" part.
//
// densityScale carries the height and horizon modulation the Phase 3
// atmosphere already computed. It scales normalized travel rather than an
// optical depth, which keeps its meaning: a denser atmosphere reaches full fog
// nearer the camera, a thinner one further away.
float compute_radial_fog_factor(float viewDistance, float4 fogParams, float densityScale)
{
    float fogStart = max(fogParams.y, 0.0);
    float fogEnd = max(fogParams.z, fogStart);
    float authoredRange = max(fogEnd - fogStart, 1e-3);
    float suppliedInvRange = abs(fogParams.w);
    float invRange = (suppliedInvRange > 1e-8) ? suppliedInvRange : rcp(authoredRange);
    invRange = min(invRange, 1e3);

    // Identical "is fog configured at all" signal to the optical-depth path: a
    // collapsed range or a zero inverse range is how the legacy path disables
    // fog, and airless maps depend on that staying true under Enhanced.
    float configured = (fogEnd > fogStart + 1e-3 && suppliedInvRange > 1e-8) ? 1.0 : 0.0;

    float normalizedTravel = saturate(max(viewDistance - fogStart, 0.0) * invRange);
    float t = saturate(normalizedTravel * densityScale);

    // Hermite smoothstep. Value and first derivative are both zero at fogStart
    // and the value reaches exactly 1 at fogEnd, so the authored end distance
    // is real full-fog opacity instead of an exponential asymptote, and the
    // onset has no derivative discontinuity to band against.
    return (t * t * (3.0 - 2.0 * t)) * configured;
}

float compute_height_density(float cameraRelativeWorldHeight)
{
    // Full Enhanced High uses a camera-relative world-space height delta. This
    // avoids subtracting huge absolute coordinates on Battlezone's large maps.
    float exponent = clamp(-cameraRelativeWorldHeight * OSE_ATMOS_HEIGHT_FALLOFF, -1.5, 1.5);
    return exp(exponent);
}

float compute_horizon_factor(float3 worldViewRay)
{
    float horizon = saturate(1.0 - abs(worldViewRay.y));
    return pow(horizon, OSE_ATMOS_HORIZON_POWER);
}

void compute_sun_scattering(
    float3 viewRay,
    float4 primaryLightPosition,
    float3 primaryLightDiffuse,
    float lightCount,
    float horizonFactor,
    out float sunScatter,
    out float3 sunTint)
{
    sunScatter = 0.0;
    sunTint = float3(1.0, 1.0, 1.0);

    // The existing lighting convention uses lightPosition.xyz directly when
    // w == 0, so only that established directional-light form may drive haze.
    if (lightCount <= 0.0 || abs(primaryLightPosition.w) >= 0.5)
        return;

    float3 sunDirection = safe_normalize(primaryLightPosition.xyz);
    if (dot(sunDirection, sunDirection) <= 1e-8)
        return;

    float forward = pow(saturate(dot(viewRay, sunDirection)), OSE_ATMOS_SUN_SCATTER_POWER);
    float peak = max(primaryLightDiffuse.r, max(primaryLightDiffuse.g, primaryLightDiffuse.b));
    if (peak > 1e-4)
        sunTint = saturate(primaryLightDiffuse / peak);

    sunScatter = forward * (0.60 + 0.40 * horizonFactor);
}

void compute_enhanced_atmosphere(
    float3 viewPosition,
    float4 fogParams,
    float3 fogColour,
    float3 sceneAmbient,
    float4 primaryLightPosition,
    float3 primaryLightDiffuse,
    float lightCount,
    float cameraRelativeWorldHeight,
    float horizonFactor,
    out float fogFactor,
    out float heightContribution,
    out float sunScatter,
    out float3 atmosphereColour,
    out float surfaceTransmission,
    out float emissiveTransmission)
{
    // Radial: length() of the camera-space position, not clip-space depth.
    // This is already what the Enhanced path used, and it is what the radial
    // fog factor consumes.
    float viewDistance = max(length(viewPosition), 0.0);
    // Declared here, in its original position, so that the OSE_RADIAL_FOG=0
    // token stream is an exact match for the pre-radial-fog baseline. Moving it
    // into the #else below is semantically identical but perturbs fxc's
    // instruction scheduling on the register-heavy IBL permutations, which
    // would cost the bit-identical A/B guarantee for no benefit.
#if !OSE_RADIAL_FOG_ACTIVE
    float distanceOpticalDepth = compute_distance_optical_depth(viewDistance, fogParams);
#endif

    float heightDensity = compute_height_density(cameraRelativeWorldHeight);
    float heightScale = lerp(1.0, heightDensity, OSE_ATMOS_HEIGHT_STRENGTH);
    heightContribution = saturate(abs(heightScale - 1.0) * 2.0);

    float densityScale = max(heightScale + horizonFactor * OSE_ATMOS_HORIZON_STRENGTH, 0.25);
#if OSE_RADIAL_FOG_ACTIVE
    fogFactor = compute_radial_fog_factor(viewDistance, fogParams, densityScale);
    // Keep the composite below an exact lerp between surface and atmosphere.
    // Everything downstream - aerial desaturation, emissive transmission, the
    // debug modes - reads these two, so defining transmission as the exact
    // complement is what keeps the rest of the model unchanged.
    surfaceTransmission = 1.0 - fogFactor;
#else
    float opticalDepth = min(distanceOpticalDepth * densityScale, OSE_ATMOS_MAX_OPTICAL_DEPTH);
    surfaceTransmission = exp(-opticalDepth);
    fogFactor = saturate(1.0 - surfaceTransmission);
#endif

    float3 viewRay = safe_normalize(viewPosition);
    float3 sunTint;
    compute_sun_scattering(
        viewRay,
        primaryLightPosition,
        primaryLightDiffuse,
        lightCount,
        horizonFactor,
        sunScatter,
        sunTint);
    sunScatter *= fogFactor;

    float3 authoredFog = saturate(fogColour);
#if OSE_LINEAR_LIGHT_ACTIVE
    // Ogre supplies the mission-authored fog colour in display-referred RGB.
    // Enhanced lighting composites in linear space and encodes once at output.
    authoredFog = srgb_to_linear(authoredFog);
#endif
    float3 ambientTarget = saturate(authoredFog + sceneAmbient * 0.35);
    atmosphereColour = lerp(authoredFog, ambientTarget, OSE_ATMOS_AMBIENT_TINT_STRENGTH);
    float sunBlend = saturate(sunScatter * OSE_ATMOS_SUN_SCATTER_STRENGTH);
    float3 sunwardAtmosphere = saturate(atmosphereColour + sunTint * OSE_ATMOS_SUN_TINT_STRENGTH);
    atmosphereColour = lerp(atmosphereColour, sunwardAtmosphere, sunBlend);

    // Emission still extinguishes with distance, but less aggressively than
    // reflected surface light so engines/panels remain legible through haze.
    float softenedTransmission = sqrt(saturate(surfaceTransmission));
    emissiveTransmission = lerp(
        surfaceTransmission,
        softenedTransmission,
        OSE_ATMOS_EMISSIVE_TRANSMISSION);
}

// Terrain-specific legacy calibration. Vehicle/building materials keep the
// broader object ranges in openshim_enhanced_base-sm4.hlsl; terrain is predominantly dusty
// rock/soil and should remain a rough dielectric rather than reading as wet.
static const float OSE_TERRAIN_PBR_MIN_ROUGHNESS = 0.56;
static const float OSE_TERRAIN_PBR_MAX_F0 = 0.12;
static const float OSE_TERRAIN_IBL_SPECULAR_SCALE = 0.72;

// -----------------------------------------------------------------------------
// Terrain normal sharpening
// -----------------------------------------------------------------------------
// The gain divides Z instead of multiplying XY. Multiplying XY needs a slope
// ceiling to stay on the unit sphere, and that ceiling plateaus: every input
// past ~30 degrees lands on one output angle, flattening the crater rims that
// carry the relief into a single tone. Dividing Z gives exactly
// tan(out) = gain * tan(in) - monotonic over the whole range, asymptotic at 90
// degrees, no clamp needed, and scale-invariant, so the non-unit RGB that BC1
// quantization produces sharpens identically to a unit normal.
//
// The gain is a CONSTANT, deliberately. An earlier version faded it by view
// distance, by N.V and by texel footprint. Every one of those is a function of
// the camera, so the gain on a patch of ground changed as the camera
// approached it and the shading crawled over static ground. A surface normal
// must depend on the surface, not on where it is viewed from. Minification is
// handled where it belongs: the normal atlas is mip-mapped, so distant samples
// are already averaged toward flat, and filter_roughness_from_normal_variance()
// widens roughness where the shaded normal varies fast in screen space.
// Measured two ways, and the second overruled the first.
//
// OFFLINE, against the shipped MOON_ATLAS_N.dds (median texel tilt 2.2 deg, p90
// 19.3 deg) swept over sun elevations 10-30 deg on flat ground, the gain looked
// expensive: 2.10 manufactured shadow -- texels pushed past N.L <= 0 that were
// lit at gain 1.0 -- across 4.14% of the ground, against 2.51% at 1.60, for 11%
// more relief. On that basis this constant was dropped to 1.60.
//
// IN GAME, on play01 with the camera at rest and the same frame captured under
// each variant (8 frames per run, cross-run camera agreement tighter than the
// frame-to-frame noise floor), the drop from 2.10 to 1.60 turned out to be
// close to a wash:
//
//     dark speckle (% of ground below half its local mean)   -2%
//     relative contrast on the lit surface                   -1.3%
//     high-frequency surface detail (RMS vs a 9px blur)      -4.1%
//
// Against that, repairing the N.V gate in evaluate_legacy_pbr removed 28% of
// the speckle on its own. The gate was doing essentially all the damage; the
// gain was never the problem, so it is back at 2.10 where the mid- and
// long-range relief reads best.
//
// Caveat on scope: that capture is a third-person view of open ground at one
// sun angle. The offline sweep says the gain matters considerably more when the
// sun is low, where 2.10 manufactures shadow over 4.9% of flat ground against
// 2.8% at 1.60. If a low-sun map shows hard dark patches on flat ground again,
// lower this first -- the table above is the map, and nothing else depends on
// the value.
//
// A tilt-dependent roll-off was also tested as an alternative shaping function
// and beat a flat gain by only 3-6% at matched cost, which does not justify a
// second tunable.
static const float OSE_TERRAIN_NORMAL_SHARPEN_GAIN = 2.10;

// Scale-invariant and view-independent: depends only on the sampled texel.
float3 sharpen_terrain_normal(float3 normalTex)
{
    return safe_normalize(float3(normalTex.xy,
                                 normalTex.z / OSE_TERRAIN_NORMAL_SHARPEN_GAIN));
}



float legacy_shininess_to_roughness(float shininess)
{
    float scaledShininess = max(shininess * OSE_PBR_SHININESS_SCALE, 0.0);
    float roughness = sqrt(2.0 / (scaledShininess + 2.0));
    return clamp(roughness, OSE_PBR_MIN_ROUGHNESS, OSE_PBR_MAX_ROUGHNESS);
}

float3 legacy_specular_to_f0(float3 specularTex)
{
    specularTex = saturate(specularTex);
    float peak = max(max(specularTex.r, specularTex.g), specularTex.b);
    float3 tint = (peak > 1e-4) ? specularTex / peak : float3(1.0, 1.0, 1.0);
    float strength = lerp(OSE_PBR_DEFAULT_F0, OSE_PBR_MAX_LEGACY_F0, pow(peak, 1.35));
    return saturate(lerp(float3(OSE_PBR_DEFAULT_F0, OSE_PBR_DEFAULT_F0, OSE_PBR_DEFAULT_F0),
                         tint * strength,
                         saturate(peak * 0.90)));
}

float derive_legacy_roughness(float materialShininess, float specularMask)
{
    float roughness = legacy_shininess_to_roughness(materialShininess);
    float smoothnessBias = (specularMask - 0.5) * 2.0;
    roughness *= 1.0 - smoothnessBias * OSE_PBR_SPECULAR_ROUGHNESS_INFLUENCE;
    return clamp(roughness, OSE_PBR_MIN_ROUGHNESS, OSE_PBR_MAX_ROUGHNESS);
}

float filter_roughness_from_normal_variance(float3 N, float roughness)
{
    float3 dNdx = ddx(N);
    float3 dNdy = ddy(N);
    float variance = max(dot(dNdx, dNdx), dot(dNdy, dNdy));
    variance = min(variance * OSE_PBR_NORMAL_VARIANCE_SCALE, OSE_PBR_MAX_VARIANCE_ROUGHNESS);
    float filtered = sqrt(max(roughness * roughness + variance, 0.0));
    return clamp(filtered, OSE_PBR_MIN_ROUGHNESS, OSE_PBR_MAX_ROUGHNESS);
}

float distribution_ggx(float NdotH, float roughness)
{
    float a = max(roughness * roughness, 1e-4);
    float a2 = a * a;
    float n2 = NdotH * NdotH;
    float denom = n2 * (a2 - 1.0) + 1.0;
    return a2 / max(OSE_PI * denom * denom, 1e-6);
}

float geometry_schlick_ggx(float NdotX, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) * 0.125;
    return NdotX / max(NdotX * (1.0 - k) + k, 1e-6);
}

float geometry_smith(float NdotV, float NdotL, float roughness)
{
    return geometry_schlick_ggx(NdotV, roughness)
         * geometry_schlick_ggx(NdotL, roughness);
}

float3 fresnel_schlick(float cosTheta, float3 F0)
{
    float m = saturate(1.0 - cosTheta);
    float m2 = m * m;
    float m5 = m2 * m2 * m;
    return F0 + (1.0 - F0) * m5;
}

float3 fresnel_schlick_roughness(float cosTheta, float3 F0, float roughness)
{
    float m = saturate(1.0 - cosTheta);
    float m2 = m * m;
    float m5 = m2 * m2 * m;
    float3 grazing = max(float3(1.0 - roughness, 1.0 - roughness, 1.0 - roughness), F0);
    return F0 + (grazing - F0) * m5;
}

float3 ibl_scene_tint(float3 sceneAmbient, float3 fogColour)
{
    float3 sceneTint = saturate(sceneAmbient + fogColour * 0.35);
    return lerp(float3(1.0, 1.0, 1.0), sceneTint, OSE_IBL_SCENE_TINT_STRENGTH);
}

float terrain_ibl_diffuse_strength(float4 fogParams)
{
    float validFogRange = (fogParams.z > fogParams.y && abs(fogParams.w) > 1e-8) ? 1.0 : 0.0;
    float atmosphereSupport = saturate(abs(fogParams.w) * OSE_TERRAIN_IBL_REFERENCE_FOG_RANGE) * validFogRange;
    return lerp(OSE_TERRAIN_IBL_AIRLESS_FLOOR, 1.0, atmosphereSupport);
}

void evaluate_legacy_pbr(
    float3 N,
    float3 V,
    float3 L,
    float3 F0,
    float roughness,
    out float3 diffuseWeight,
    out float3 specularBRDF,
    out float NdotL)
{
    NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));
    diffuseWeight = float3(0.0, 0.0, 0.0);
    specularBRDF = float3(0.0, 0.0, 0.0);

    // Lambertian diffuse has no view term: it is albedo/PI * N.L, and nothing
    // in it depends on where the surface is being looked at from. The N.V test
    // below belongs to the SPECULAR branch only -- the microfacet denominator
    // divides by N.V, so that term genuinely has to bail. Testing both outputs
    // against it meant any texel whose normal tipped even slightly away from
    // the camera lost ALL of its direct light in one step and dropped to the
    // ambient floor.
    //
    // On terrain that is severe. Ground seen from a cockpit is viewed at a
    // grazing angle, so N.V hovers near zero across the whole near field, and
    // normal-map detail -- especially once sharpened -- pushes large patches of
    // it past the threshold. The result was hard-edged pools of near-black with
    // flat interiors (the interior is the ambient floor, which is spatially
    // constant) that slid across static ground as the camera moved, because
    // N.V is a function of the camera. Two earlier diagnoses missed this: a
    // Lambert terminator cannot explain motion, and removing the view-dependent
    // weighting from the normal sharpening did not help because the view
    // dependence was never in the sharpening -- it was here.
    //
    // It bites hardest on airless maps, where terrain_ibl_diffuse_strength()
    // floors the IBL contribution at OSE_TERRAIN_IBL_AIRLESS_FLOOR and only
    // OSE_IBL_LEGACY_AMBIENT_RETAIN of the scene ambient survives, so "no direct
    // light" is a much deeper hole than it is under an atmosphere.
    if (NdotL <= 0.0)
        return;

    float3 H = safe_normalize(V + L);
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));

    // VdotH is well defined whatever N.V does, so the diffuse/specular energy
    // split stays valid here.
    float3 F = fresnel_schlick(VdotH, F0);
    diffuseWeight = (1.0 - F) * (OSE_PBR_DIFFUSE_COMPENSATION / OSE_PI);

    if (NdotV <= 0.0)
        return;

    float D = distribution_ggx(NdotH, roughness);
    float G = geometry_smith(NdotV, NdotL, roughness);
    specularBRDF = (D * G * F) / max(4.0 * NdotV * NdotL, 1e-5);
}
#endif

void ComputeSpotlightTerms(
    float3 pixelToLight,
    float3 lightDir,
    float4 spotParams,
    out float diffuseSpotAttenuation,
    out float specularSpotAttenuation)
{
    float spotRange = max(spotParams.x - spotParams.y, 1e-6);
    float cone = dot(pixelToLight, safe_normalize(-lightDir));
    float spotMask = saturate((cone - spotParams.y) / spotRange);
    float spotEnabled = (spotParams.z > 1e-4) ? 1.0 : 0.0;
    float spotPower = max(spotParams.z, 1.0);
    diffuseSpotAttenuation = lerp(1.0, pow(max(spotMask, 1e-4), spotPower), spotEnabled);
    specularSpotAttenuation = lerp(1.0, pow(max(spotMask, 1e-4), max(spotPower * 1.5, 1.0)), spotEnabled);
}

void terrain_vertex(
    uniform float4x4 wvpMat,
    uniform float4x4 worldViewMat,

#if defined(SHADOWRECEIVER)
    uniform float4x4 texWorldViewProj1,
#if defined(PSSM_ENABLED)
    uniform float4x4 texWorldViewProj2,
    uniform float4x4 texWorldViewProj3,
#endif
#endif

#if defined(VERTEX_LIGHTING)
    uniform float4 lightPosition[MAX_LIGHTS],
    uniform float4 lightDiffuse[MAX_LIGHTS],
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    uniform float4 lightSpecular[MAX_LIGHTS],
    uniform float materialShininess,
#endif
#endif

    in float4 iPosition : POSITION0,
    in uint4 iBlendIndices : BLENDINDICES,
#if !defined(VERTEX_LIGHTING) && defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    in float3 iTangent : TANGENT0,
#endif
    in float4 iColor : COLOR0,
    in float heightOffset : TEXCOORD1,

    out float4 vColor : COLOR0,
#if defined(VERTEX_LIGHTING)
    out float3 vLightResult : COLOR1,
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    out float3 vSpecularResult : COLOR2,
#endif
#endif

    out float2 vTexCoord : TEXCOORD0,
#if !defined(VERTEX_LIGHTING)
    out float3 vViewNormal : TEXCOORD2,
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    out float3 vViewTangent : TEXCOORD3,
#endif
    out float3 vViewPosition : TEXCOORD4,
#endif
    out float vDepth : TEXCOORD5,
#if defined(SHADOWRECEIVER)
    out float4 vLightSpacePos1 : TEXCOORD6,
#if defined(PSSM_ENABLED)
    out float4 vLightSpacePos2 : TEXCOORD7,
    out float4 vLightSpacePos3 : TEXCOORD8,
#endif
#endif

    out float4 oPosition : SV_POSITION
)
{
    iPosition.y = heightOffset;
    float2 nNormal = (float2(iBlendIndices.zw) - float2(127.0, 127.0)) / float2(127.0, 127.0);
    float3 iNormal = float3(nNormal.x, sqrt(saturate(1.0 - dot(nNormal, nNormal))), nNormal.y);

    oPosition = mul(wvpMat, iPosition);
    vTexCoord = (float2(iBlendIndices.xy) + 0.5) / 160.0;

#if defined(VERTEX_LIGHTING)
    float3 vViewPosition, vViewNormal;
#endif
    vViewPosition = mul(worldViewMat, float4(iPosition.xyz, 1.0)).xyz;
    vViewNormal = mul(worldViewMat, float4(iNormal.xyz, 0.0)).xyz;
#if !defined(VERTEX_LIGHTING) && defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    vViewTangent = mul(worldViewMat, float4(iTangent.xyz, 0.0)).xyz;
#endif

    vDepth = oPosition.z;
    vColor = iColor.bgra;

#if defined(SHADOWRECEIVER)
    float4 shadowPosition = iPosition;
#if OSE_ENHANCED_PSSM_V2_ACTIVE
    float normalLengthSq = dot(iNormal, iNormal);
    if (normalLengthSq > 1e-8)
    {
        float receiverOffset = min(
            OSE_PSSM_NORMAL_OFFSET_BASE
                + OSE_PSSM_NORMAL_OFFSET_PER_DEPTH * max(vDepth, 0.0),
            OSE_PSSM_NORMAL_OFFSET_MAX);
        shadowPosition.xyz += iNormal * rsqrt(normalLengthSq) * receiverOffset;
    }
#endif
    vLightSpacePos1 = mul(texWorldViewProj1, shadowPosition);
#if defined(PSSM_ENABLED)
    vLightSpacePos2 = mul(texWorldViewProj2, shadowPosition);
    vLightSpacePos3 = mul(texWorldViewProj3, shadowPosition);
#endif
#endif

#if defined(VERTEX_LIGHTING)
    float3 vertexNormal = safe_normalize(vViewNormal);
    float3 pixelToLight = safe_normalize(lightPosition[0].xyz - (vViewPosition * lightPosition[0].w));

    float attenuation = max(dot(vertexNormal, pixelToLight.xyz), 0.0);
#if defined(OG_RETRO_MODE)
    attenuation = saturate(attenuation * 0.55 + 0.20);
#endif
    vLightResult = lightDiffuse[0].xyz * attenuation;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float3 viewReflect = reflect(safe_normalize(vViewPosition), vertexNormal);
    attenuation *= pow(max(dot(viewReflect, pixelToLight), 0.0), materialShininess);
    vSpecularResult = lightSpecular[0].xyz * attenuation;
#endif
#endif
}

void terrain_fragment(
    uniform Texture2D diffuseMap : register(t0),
    uniform SamplerState diffuseSam : register(s0),
#if defined(DETAILMAP_ENABLED)
    uniform Texture2D detailMap : register(t1),
    uniform SamplerState detailSam : register(s1),
#endif
#if defined(NORMALMAP_ENABLED)
    uniform Texture2D normalMap : register(t2),
    uniform SamplerState normalSam : register(s2),
#endif
#if defined(SPECULARMAP_ENABLED)
    uniform Texture2D specularMap : register(t3),
    uniform SamplerState specularSam : register(s3),
#endif
#if defined(EMISSIVEMAP_ENABLED)
    uniform Texture2D emissiveMap : register(t4),
    uniform SamplerState emissiveSam : register(s4),
#endif
#if defined(SHADOWRECEIVER)
    uniform Texture2D shadowMap1 : register(t5),
#if OSE_ENHANCED_PSSM_V2_ACTIVE
    uniform SamplerComparisonState shadowSam1 : register(s5),
#else
    uniform SamplerState shadowSam1 : register(s5),
#endif
#if defined(PSSM_ENABLED)
    uniform Texture2D shadowMap2 : register(t6),
#if OSE_ENHANCED_PSSM_V2_ACTIVE
    uniform SamplerComparisonState shadowSam2 : register(s6),
#else
    uniform SamplerState shadowSam2 : register(s6),
#endif
    uniform Texture2D shadowMap3 : register(t7),
#if OSE_ENHANCED_PSSM_V2_ACTIVE
    uniform SamplerComparisonState shadowSam3 : register(s7),
#else
    uniform SamplerState shadowSam3 : register(s7),
#endif
#endif

    uniform float4 invShadowMapSize1,
#if defined(PSSM_ENABLED)
    uniform float4 invShadowMapSize2,
    uniform float4 invShadowMapSize3,
    uniform float4 pssmSplitPoints,
#endif
#endif

#if defined(IBL_ENABLED)
#if defined(PSSM_ENABLED)
    uniform TextureCube irradianceMap : register(t8),
    uniform SamplerState irradianceSam : register(s8),
    uniform TextureCube prefilteredEnvMap : register(t9),
    uniform SamplerState prefilteredEnvSam : register(s9),
    uniform Texture2D brdfLut : register(t10),
    uniform SamplerState brdfLutSam : register(s10),
#elif defined(SHADOWRECEIVER)
    uniform TextureCube irradianceMap : register(t6),
    uniform SamplerState irradianceSam : register(s6),
    uniform TextureCube prefilteredEnvMap : register(t7),
    uniform SamplerState prefilteredEnvSam : register(s7),
    uniform Texture2D brdfLut : register(t8),
    uniform SamplerState brdfLutSam : register(s8),
#else
    uniform TextureCube irradianceMap : register(t5),
    uniform SamplerState irradianceSam : register(s5),
    uniform TextureCube prefilteredEnvMap : register(t6),
    uniform SamplerState prefilteredEnvSam : register(s6),
    uniform Texture2D brdfLut : register(t7),
    uniform SamplerState brdfLutSam : register(s7),
#endif
    uniform float4x4 inverseViewMatrix,
#endif

    uniform float4 sceneAmbient,

#if !defined(VERTEX_LIGHTING)
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    uniform float materialShininess,
#endif
    uniform float4 lightDiffuse[MAX_LIGHTS],
    uniform float4 lightPosition[MAX_LIGHTS],
    uniform float4 lightSpecular[MAX_LIGHTS],
    uniform float4 lightAttenuation[MAX_LIGHTS],
    uniform float4 spotLightParams[MAX_LIGHTS],
    uniform float4 lightDirection[MAX_LIGHTS],
    uniform float lightCount,
#endif

    uniform float4 fogColour,
    uniform float4 fogParams,

    in float4 vColor : COLOR0,
#if defined(VERTEX_LIGHTING)
    in float3 vLightResult : COLOR1,
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    in float3 vSpecularResult : COLOR2,
#endif
#endif
    in float2 vTexCoord : TEXCOORD0,
#if !defined(VERTEX_LIGHTING)
    in float3 vViewNormal : TEXCOORD2,
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    in float3 vViewTangent : TEXCOORD3,
#endif
    in float3 vViewPosition : TEXCOORD4,
#endif
    in float vDepth : TEXCOORD5,
#if defined(SHADOWRECEIVER)
    in float4 vLightSpacePos1 : TEXCOORD6,
#if defined(PSSM_ENABLED)
    in float4 vLightSpacePos2 : TEXCOORD7,
    in float4 vLightSpacePos3 : TEXCOORD8,
#endif
#endif

    out float4 oColor : SV_TARGET
#if defined(LOGDEPTH_ENABLE)
    , out float oDepth : SV_DEPTH
#endif
)
{
#if defined(SHADOWRECEIVER)
    // Geometric cosine for the slope term. VERTEX_LIGHTING permutations carry
    // no interpolated normal, so they fall back to the constant floor.
    float shadowNdotL = 1.0;
#if !defined(VERTEX_LIGHTING)
    if (lightCount > 0.0)
    {
        float3 shadowToLight = lightPosition[0].xyz
                             - (vViewPosition.xyz * lightPosition[0].w);
        shadowNdotL = saturate(dot(safe_normalize(vViewNormal),
                                   safe_normalize(shadowToLight)));
    }
#endif
    float shadowBias = shadow_depth_bias(shadowNdotL);

    float shadow;
#if defined(PSSM_ENABLED)
#if OSE_ENHANCED_PSSM_V2_ACTIVE
    float split1 = pssmSplitPoints.y;
    float split2 = pssmSplitPoints.z;
    float splitEnd = pssmSplitPoints.w;
    float blendWidth = OSE_PSSM_CASCADE_BLEND_HALF_WIDTH;

    [branch] if (vDepth < split1 - blendWidth)
    {
        shadow = PCF_Filter(shadowMap1, shadowSam1, vLightSpacePos1, invShadowMapSize1.xy, shadowBias);
    }
    else if (vDepth <= split1 + blendWidth)
    {
        float shadow1 = PCF_Filter(shadowMap1, shadowSam1, vLightSpacePos1, invShadowMapSize1.xy, shadowBias);
        float shadow2 = PCF_Filter(shadowMap2, shadowSam2, vLightSpacePos2, invShadowMapSize2.xy, shadowBias);
        float blend = smoothstep(split1 - blendWidth, split1 + blendWidth, vDepth);
        shadow = lerp(shadow1, shadow2, blend);
    }
    else if (vDepth < split2 - blendWidth)
    {
        shadow = PCF_Filter(shadowMap2, shadowSam2, vLightSpacePos2, invShadowMapSize2.xy, shadowBias);
    }
    else if (vDepth <= split2 + blendWidth)
    {
        float shadow2 = PCF_Filter(shadowMap2, shadowSam2, vLightSpacePos2, invShadowMapSize2.xy, shadowBias);
        float shadow3 = PCF_Filter(shadowMap3, shadowSam3, vLightSpacePos3, invShadowMapSize3.xy, shadowBias);
        float blend = smoothstep(split2 - blendWidth, split2 + blendWidth, vDepth);
        shadow = lerp(shadow2, shadow3, blend);
    }
    else if (vDepth <= splitEnd)
    {
        shadow = PCF_Filter(shadowMap3, shadowSam3, vLightSpacePos3, invShadowMapSize3.xy, shadowBias);
        float fadeStart = max(split2 + blendWidth, splitEnd - OSE_PSSM_FAR_FADE_WIDTH);
        float farFade = smoothstep(fadeStart, splitEnd, vDepth);
        shadow = lerp(shadow, 1.0, farFade);
    }
    else
    {
        shadow = 1.0;
    }
#else
    if (vDepth <= pssmSplitPoints.y)
    {
        shadow = PCF_Filter(shadowMap1, shadowSam1, vLightSpacePos1, invShadowMapSize1.xy, shadowBias);
    }
    else if (vDepth <= pssmSplitPoints.z)
    {
        shadow = PCF_Filter(shadowMap2, shadowSam2, vLightSpacePos2, invShadowMapSize2.xy, shadowBias);
    }
    else
    {
        shadow = PCF_Filter(shadowMap3, shadowSam3, vLightSpacePos3, invShadowMapSize3.xy, shadowBias);
    }
#endif
#else
    shadow = PCF_Filter(shadowMap1, shadowSam1, vLightSpacePos1, invShadowMapSize1.xy, shadowBias);
#endif
#if defined(ENHANCED_MODE)
    shadow = shadow * 0.78 + 0.22;
#else
    shadow = shadow * 0.7 + 0.3;
#endif
#if defined(OG_RETRO_MODE)
    shadow = shadow * 0.5 + 0.5;
#endif
#endif

#if defined(VERTEX_LIGHTING)

#if defined(RETRO_UNLIT_MODE)
    float3 lightResult = vLightResult;
#if defined(SHADOWRECEIVER)
    lightResult *= shadow;
#endif
#if defined(OG_RETRO_MODE)
    lightResult += max(sceneAmbient.xyz * 1.10, float3(0.22, 0.22, 0.22));
#else
    lightResult += sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float3 specularResult = float3(0.0, 0.0, 0.0);
#endif
#else
    float3 lightResult = vLightResult;
#if defined(SHADOWRECEIVER)
    lightResult *= shadow;
#endif
#if defined(OG_RETRO_MODE)
    lightResult += max(sceneAmbient.xyz * 1.10, float3(0.22, 0.22, 0.22));
#else
    lightResult += sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float3 specularResult = vSpecularResult;
#endif
#endif

#else

    float3 viewPos = vViewPosition;

#if defined(NORMALMAP_ENABLED)
    float3 geometryNormal = safe_normalize(vViewNormal);
#if defined(VERTEX_TANGENTS)
    float3 baseNormal = geometryNormal;
    float3 baseTangent = safe_normalize(vViewTangent);
    float3 binormal = safe_normalize(cross(baseTangent, baseNormal));
    float3x3 tbn = float3x3(baseTangent, binormal, baseNormal);
#else
    float3x3 tbn = cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord);
#endif

    // Mode 0 is BZR's full-RGB DXT1/BC1 convention. Modes 1/2 and the green
    // flip are explicit diagnostics for proving or rejecting alternate packing
    // conventions on the live misn04 terrain before changing production math.
    float4 normalSample = normalMap.Sample(normalSam, vTexCoord);
    float3 normalTex = unpack_terrain_normal(normalSample);

    // normalTex stays the raw unpack so DEBUG_MODE 3 remains a packing
    // diagnostic; the sharpened copy is what the lighting consumes. This runs
    // upstream of the TBN transform, so the extra variance it introduces is
    // picked up by ddx/ddy in filter_roughness_from_normal_variance() below
    // and fed back into roughness rather than aliasing the specular lobe.
    float3 shapedNormalTex = normalTex;
#if defined(ENHANCED_MODE)
    shapedNormalTex = sharpen_terrain_normal(normalTex);
#if defined(DETAILMAP_ENABLED)
    // Detail relief is blended in AFTER sharpening, deliberately. The sharpen
    // gain is calibrated against the atlas's own slope distribution; applying it
    // to the detail gradient as well would steepen normals the calibration never
    // accounted for and re-manufacture the terminator shadow it was tuned to
    // avoid.
    shapedNormalTex = blend_detail_normal(
        shapedNormalTex,
        detail_normal_from_luminance(detailMap, detailSam, vTexCoord * 8.0,
                                     OSE_TERRAIN_DETAIL_NORMAL_STRENGTH));
    shapedNormalTex = blend_detail_normal(
        shapedNormalTex,
        detail_normal_from_luminance(detailMap, detailSam, vTexCoord * 32.0,
                                     OSE_TERRAIN_DETAIL_NORMAL_STRENGTH
                                         * OSE_TERRAIN_DETAIL_NORMAL_NEAR_SCALE));
#endif
#endif

    float3 mappedViewNormal = safe_normalize(mul(shapedNormalTex, tbn));
#if OSE_TERRAIN_NORMAL_BASIS_MODE == 3
    float3 viewNormal = geometryNormal;
#elif OSE_TERRAIN_NORMAL_BASIS_MODE == 4
    float3 viewNormal = safe_normalize(normalTex);
#else
    float3 viewNormal = mappedViewNormal;
#endif
#else
    float3 viewNormal = safe_normalize(vViewNormal);
#endif

#if defined(NORMALMAP_ENABLED) && (OSE_TERRAIN_NORMAL_DEBUG_MODE != 0)
    float3 terrainNormalDebug;
#if OSE_TERRAIN_NORMAL_DEBUG_MODE == 1
    terrainNormalDebug = normalSample.rgb;
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 2
    terrainNormalDebug = normalSample.aaa;
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 3
    terrainNormalDebug = saturate(normalTex * 0.5 + 0.5);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 4
    terrainNormalDebug = saturate(viewNormal * 0.5 + 0.5);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 5
    float3 debugPixelToLight = safe_normalize(lightPosition[0].xyz - (viewPos * lightPosition[0].w));
    float debugNdotL = (lightCount > 0.0) ? saturate(dot(viewNormal, debugPixelToLight)) : 0.0;
    terrainNormalDebug = float3(debugNdotL, debugNdotL, debugNdotL);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 6
    terrainNormalDebug = saturate(geometryNormal * 0.5 + 0.5);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 7
    terrainNormalDebug = saturate(safe_normalize(tbn[0]) * 0.5 + 0.5);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 8
    terrainNormalDebug = saturate(safe_normalize(tbn[1]) * 0.5 + 0.5);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 9
    float3 debugTangent = safe_normalize(tbn[0]);
    float3 debugBitangent = safe_normalize(tbn[1]);
    float3 debugBasisNormal = safe_normalize(tbn[2]);
    terrainNormalDebug = saturate(abs(float3(
        dot(debugTangent, debugBasisNormal),
        dot(debugBitangent, debugBasisNormal),
        dot(debugTangent, debugBitangent))) * 8.0);
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 10
    float3 debugTangent = safe_normalize(tbn[0]);
    float3 debugBitangent = safe_normalize(tbn[1]);
    float3 debugBasisNormal = safe_normalize(tbn[2]);
    float debugDeterminant = abs(dot(cross(debugTangent, debugBitangent), debugBasisNormal));
    terrainNormalDebug = saturate(float3(length(tbn[0]), length(tbn[1]), debugDeterminant));
#elif OSE_TERRAIN_NORMAL_DEBUG_MODE == 11
    float normalDeviation = 1.0 - saturate(dot(mappedViewNormal, geometryNormal));
    terrainNormalDebug = float3(normalDeviation, normalDeviation, normalDeviation);
#else
    terrainNormalDebug = float3(1.0, 0.0, 1.0);
#endif
    oColor = float4(terrainNormalDebug, 1.0);
#if defined(LOGDEPTH_ENABLE)
    const float debugLogDepthC = 0.1;
    const float debugLogDepthFar = 1e+09;
    const float debugLogDepthOffset = 1.0;
    oDepth = log(debugLogDepthC * vDepth + debugLogDepthOffset)
           / log(debugLogDepthC * debugLogDepthFar + debugLogDepthOffset);
#endif
    return;
#endif

#if defined(SPECULARMAP_ENABLED)
    float3 specularTex = specularMap.Sample(specularSam, vTexCoord).xyz;
    float specularMask = saturate(luminance_legacy(specularTex));
#if defined(ENHANCED_MODE)
    float3 surfaceF0 = min(
        legacy_specular_to_f0(specularTex),
        float3(OSE_TERRAIN_PBR_MAX_F0, OSE_TERRAIN_PBR_MAX_F0, OSE_TERRAIN_PBR_MAX_F0));
#else
    float3 specularTint = lerp(float3(0.04, 0.04, 0.04), specularTex, specularMask);
#endif
#elif defined(ENHANCED_MODE)
    float specularMask = 0.5;
    float3 surfaceF0 = float3(OSE_PBR_DEFAULT_F0, OSE_PBR_DEFAULT_F0, OSE_PBR_DEFAULT_F0);
#endif

#if defined(ENHANCED_MODE)
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float surfaceRoughness = max(
        derive_legacy_roughness(materialShininess, specularMask),
        OSE_TERRAIN_PBR_MIN_ROUGHNESS);
#if defined(NORMALMAP_ENABLED)
    surfaceRoughness = filter_roughness_from_normal_variance(viewNormal, surfaceRoughness);
#endif
    surfaceRoughness = max(surfaceRoughness, OSE_TERRAIN_PBR_MIN_ROUGHNESS);
#endif
#endif

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED) || defined(ENHANCED_MODE)
    float3 eyeDir = safe_normalize(-viewPos);
#endif

#if defined(OG_RETRO_MODE)
    float3 lightResult = max(sceneAmbient.xyz * 1.10, float3(0.22, 0.22, 0.22));
#elif defined(IBL_ENABLED)
    float3 lightResult = sceneAmbient.xyz * OSE_IBL_LEGACY_AMBIENT_RETAIN;
#else
    float3 lightResult = sceneAmbient.xyz;
#endif
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float3 specularResult = float3(0.0, 0.0, 0.0);
#endif

#if defined(RETRO_UNLIT_MODE)
    if (lightCount > 0.0)
    {
        const int i = 0;
        float3 pixelToLight = lightPosition[i].xyz - (viewPos * lightPosition[i].w);
        float d = max(length(pixelToLight), 1e-6);
        pixelToLight *= rcp(d);

#if defined(SHADOWRECEIVER)
        float attenuation = shadow;
#else
        float attenuation = 1.0;
#endif

        float diffuseTerm = max(dot(viewNormal, pixelToLight), 0.0);
#if defined(OG_RETRO_MODE)
        diffuseTerm = saturate(diffuseTerm * 0.55 + 0.20);
#endif
        lightResult.xyz += lightDiffuse[i].xyz * (attenuation * diffuseTerm);
    }
#else

#if MAX_LIGHTS > 1
    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        if (i >= int(lightCount))
            break;
#else
    {
        const int i = 0;
#endif
        float3 pixelToLight = lightPosition[i].xyz - (viewPos * lightPosition[i].w);
        float d = max(length(pixelToLight), 1e-6);
        pixelToLight *= rcp(d);

        float attenuationDenom = lightAttenuation[i].y
                               + d * (lightAttenuation[i].z + d * lightAttenuation[i].w);
        float distanceAttenuation = saturate(rcp(max(attenuationDenom, 1e-6)));

        float diffuseSpotAttenuation = 1.0;
        float specularSpotAttenuation = 1.0;
        ComputeSpotlightTerms(
            pixelToLight,
            lightDirection[i].xyz,
            spotLightParams[i],
            diffuseSpotAttenuation,
            specularSpotAttenuation);

        float attenuation = distanceAttenuation * diffuseSpotAttenuation;
        float specularAttenuation = distanceAttenuation * specularSpotAttenuation;

#if defined(SHADOWRECEIVER)
        attenuation *= shadow;
        specularAttenuation *= shadow;
#endif

#if defined(ENHANCED_MODE) && (defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED))
        float3 diffuseWeight;
        float3 specularBRDF;
        float NdotL;
        evaluate_legacy_pbr(
            viewNormal,
            eyeDir,
            pixelToLight,
            surfaceF0,
            surfaceRoughness,
            diffuseWeight,
            specularBRDF,
            NdotL);

        lightResult.xyz += lightDiffuse[i].xyz * attenuation * NdotL * diffuseWeight;
        specularResult.xyz += lightSpecular[i].xyz
                            * specularAttenuation
                            * NdotL
                            * specularBRDF
                            * OSE_PBR_SPECULAR_COMPENSATION;
#elif defined(ENHANCED_MODE)
        float NdotL = saturate(dot(viewNormal, pixelToLight));
        lightResult.xyz += lightDiffuse[i].xyz
                         * attenuation
                         * NdotL
                         * (OSE_PBR_DIFFUSE_COMPENSATION / OSE_PI);
#else
        float diffuseTerm = max(dot(viewNormal, pixelToLight), 0.0);
#if defined(OG_RETRO_MODE)
        diffuseTerm = saturate(diffuseTerm * 0.55 + 0.20);
#endif
        attenuation *= diffuseTerm;
        lightResult.xyz += lightDiffuse[i].xyz * attenuation;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
        if (diffuseTerm > 0.0)
        {
            float3 halfVector = safe_normalize(pixelToLight + eyeDir);
            float ndotv = max(dot(viewNormal, eyeDir), 0.0);
            float ndoth = max(dot(viewNormal, halfVector), 0.0);
#if defined(SPECULARMAP_ENABLED)
            float specularPower = lerp(
                max(materialShininess * 0.9 + 6.0, 8.0),
                max(materialShininess * 2.25 + 24.0, 24.0),
                specularMask);
            float3 specularColor = lerp(specularTint * 0.65, specularTint, pow(1.0 - ndotv, 5.0));
#else
            float specularPower = max(materialShininess * 1.5 + 12.0, 16.0);
            float3 specularColor = lerp(float3(0.025, 0.025, 0.025), float3(0.04, 0.04, 0.04), pow(1.0 - ndotv, 5.0));
#endif
            float specularLobe = pow(ndoth, specularPower);
            specularResult.xyz += lightSpecular[i].xyz
                                * specularAttenuation
                                * diffuseTerm
                                * specularLobe
                                * specularColor;
        }
#endif
#endif

#if defined(SHADOWRECEIVER)
        shadow = 1.0;
#endif
    }

#endif

#if defined(IBL_ENABLED) && (defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED))
    float NdotVForIBL = saturate(dot(viewNormal, eyeDir));
    float3 ambientFresnel = fresnel_schlick_roughness(NdotVForIBL, surfaceF0, surfaceRoughness);
    float3 diffuseEnergy = 1.0 - ambientFresnel;

    float3 worldNormal = safe_normalize(mul(inverseViewMatrix, float4(viewNormal, 0.0)).xyz);
    float3 viewReflection = reflect(-eyeDir, viewNormal);
    float3 worldReflection = safe_normalize(mul(inverseViewMatrix, float4(viewReflection, 0.0)).xyz);

    float3 environmentTint = ibl_scene_tint(sceneAmbient.xyz, fogColour.xyz);
    float3 irradiance = irradianceMap.Sample(irradianceSam, worldNormal).xyz * environmentTint;
    float terrainDiffuseIblStrength = terrain_ibl_diffuse_strength(fogParams);
    lightResult.xyz += irradiance * diffuseEnergy * OSE_IBL_DIFFUSE_INTENSITY * terrainDiffuseIblStrength;

    float specularMip = saturate(surfaceRoughness) * OSE_IBL_MAX_SPECULAR_MIP;
    float3 prefilteredEnvironment = prefilteredEnvMap.SampleLevel(
        prefilteredEnvSam,
        worldReflection,
        specularMip).xyz * environmentTint;
    float2 environmentBRDF = brdfLut.Sample(
        brdfLutSam,
        float2(NdotVForIBL, saturate(surfaceRoughness))).rg;

    specularResult.xyz += prefilteredEnvironment
                        * (surfaceF0 * environmentBRDF.x + environmentBRDF.y)
                        * OSE_IBL_SPECULAR_INTENSITY
                        * OSE_TERRAIN_IBL_SPECULAR_SCALE;
#elif defined(ENHANCED_MODE)
    float NdotVForFill = saturate(dot(viewNormal, eyeDir));
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float3 grazingFresnel = fresnel_schlick(NdotVForFill, surfaceF0);
    lightResult.xyz += sceneAmbient.xyz * grazingFresnel * (1.0 - surfaceRoughness) * 0.15;
#else
    lightResult.xyz += sceneAmbient.xyz * pow(1.0 - NdotVForFill, 4.0) * 0.10;
#endif
#endif
#endif

    float4 diffuseTex = diffuseMap.Sample(diffuseSam, vTexCoord);
#if OSE_LINEAR_LIGHT_ACTIVE
    // Terrain diffuse (t0) is artist-authored COLOR. Decode RGB only.
    // diffuseTex.a is the detail-blend weight consumed further down and must
    // stay in its numerical space.
    diffuseTex.rgb = srgb_to_linear(diffuseTex.rgb);
#endif

    // Per-vertex terrain tint. It multiplies the decoded albedo directly, so it
    // is authored COLOR and needs the same transfer function - leaving it
    // encoded would multiply a linear albedo by a gamma-space tint. BZCC applies
    // the equivalent decode to every vertex-colour layout it ships, terrain
    // (layout 8) included: pow(COLOR.rgb, 2.2) with alpha passed through
    // untouched. See reverse_engineering/bzcc_bzr_dx11_probe.
    //
    // Stage A is scoped to the per-pixel path, so this happens here rather than
    // in the vertex stage as BZCC does. The tint is therefore interpolated
    // encoded and decoded afterwards; over a single triangle that is a small
    // deviation, and it is what lets Default/Retro keep sharing these vertex
    // programs unmodified.
    //
    // vColor.a is untouched: it is the terrain output alpha, not colour.
    float3 vertexTint = vColor.xyz;
#if OSE_LINEAR_LIGHT_ACTIVE
    vertexTint = srgb_to_linear(vertexTint);
#endif

    oColor.xyz = lightResult.xyz * vertexTint * diffuseTex.xyz;

#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    oColor.xyz += specularResult.xyz;
#endif

    float3 emissiveContribution = float3(0.0, 0.0, 0.0);
#if defined(EMISSIVEMAP_ENABLED)
    float3 emissiveTex = emissiveMap.Sample(emissiveSam, vTexCoord).xyz;
#if OSE_LINEAR_LIGHT_ACTIVE
    // Terrain emissive is artist-authored COLOR. Decode at the sample, ahead of
    // the detail multiplication and the atmospheric transmission below.
    emissiveTex = srgb_to_linear(emissiveTex);
#endif
#if defined(ENHANCED_MODE)
    emissiveContribution = emissiveTex.xyz;
#else
    oColor.xyz += emissiveTex.xyz;
#endif
#endif

#if defined(DETAILMAP_ENABLED)
    // Stage A deliberately does NOT decode the detail map, even under
    // OSE_LINEAR_LIGHT=1. Mathematically this is modulation data, not COLOR: the
    // "* 2.0" below makes a stored 0.5 the neutral 1.0 multiplier. An sRGB
    // decode would turn 0.5 into ~0.214, so the neutral point would become
    // ~0.43 and the whole terrain would darken by more than half. Treat the
    // detail texture as numerical modulation and leave it alone.
    float3 detailTex = detail_modulation(detailMap.Sample(detailSam, vTexCoord * 8.0).xyz);
    float3 fullbrightDetail = float3(1.0, 1.0, 1.0);
#if defined(ENHANCED_MODE)
    float detailDistance = saturate(vDepth * 0.015);
    float3 detailColor = lerp(detailTex, fullbrightDetail, detailDistance);
    float3 detailTexNear = detail_modulation(detailMap.Sample(detailSam, vTexCoord * 32.0).xyz);
    float detailNearFade = saturate(vDepth * 0.08);
    detailColor *= lerp(lerp(detailTexNear, fullbrightDetail, 0.5), fullbrightDetail, detailNearFade);
#else
    float detailDistance = saturate(vDepth * 0.025);
    float3 detailColor = lerp(detailTex, fullbrightDetail, detailDistance);
#endif
#if defined(OG_RETRO_MODE)
    float3 detailMultiplier = lerp(float3(1.0, 1.0, 1.0), detailColor, diffuseTex.a * 0.35);
#else
    float3 detailMultiplier = lerp(float3(1.0, 1.0, 1.0), detailColor, diffuseTex.a);
#endif
    oColor.xyz *= detailMultiplier;
#if defined(ENHANCED_MODE)
    // Keep pre-atmosphere terrain emissive behavior identical to the old
    // combined-color detail multiply before applying reduced extinction.
    emissiveContribution *= detailMultiplier;
#endif
#endif

#if defined(ENHANCED_MODE) && !defined(VERTEX_LIGHTING)
    float cameraRelativeWorldHeight = 0.0;
    float horizonFactor = 0.0;
#if defined(IBL_ENABLED)
    float3 cameraRelativeWorldPosition = mul(inverseViewMatrix, float4(viewPos, 0.0)).xyz;
    float3 worldViewRay = safe_normalize(mul(inverseViewMatrix, float4(safe_normalize(viewPos), 0.0)).xyz);
    cameraRelativeWorldHeight = cameraRelativeWorldPosition.y;
    horizonFactor = compute_horizon_factor(worldViewRay);
#endif

    float fogValue;
    float heightContribution;
    float sunScatter;
    float3 atmosphereColour;
    float surfaceTransmission;
    float emissiveTransmission;
    compute_enhanced_atmosphere(
        viewPos,
        fogParams,
        fogColour.xyz,
        sceneAmbient.xyz,
        lightPosition[0],
        lightDiffuse[0].xyz,
        lightCount,
        cameraRelativeWorldHeight,
        horizonFactor,
        fogValue,
        heightContribution,
        sunScatter,
        atmosphereColour,
        surfaceTransmission,
        emissiveTransmission);

    float surfaceLuminance = luminance_legacy(oColor.xyz);
    float3 aerialSurface = lerp(
        oColor.xyz,
        float3(surfaceLuminance, surfaceLuminance, surfaceLuminance),
        fogValue * OSE_ATMOS_AERIAL_DESATURATION);
    oColor.xyz = aerialSurface * surfaceTransmission
               + atmosphereColour * fogValue
               + emissiveContribution * emissiveTransmission;

#if OSE_ATMOS_DEBUG_MODE == 1
    oColor.xyz = float3(fogValue, fogValue, fogValue);
#elif OSE_ATMOS_DEBUG_MODE == 2
    oColor.xyz = float3(heightContribution, heightContribution, heightContribution);
#elif OSE_ATMOS_DEBUG_MODE == 3
    oColor.xyz = float3(sunScatter, sunScatter, sunScatter);
#elif OSE_ATMOS_DEBUG_MODE == 4
    oColor.xyz = atmosphereColour;
#endif
#else
#if defined(ENHANCED_MODE) && defined(EMISSIVEMAP_ENABLED)
    oColor.xyz += emissiveContribution;
#endif
    float fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
    oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);
#endif

#if OSE_LINEAR_LIGHT_ACTIVE
    // Stage A single output encode. Everything above - direct lighting, GGX,
    // IBL, emissive, detail modulation, Phase 3 atmosphere and aerial
    // perspective - has run on linearized COLOR input, so encode exactly once
    // here, as late as the opaque pixel pipeline allows, because the bound
    // render target is an ordinary non-sRGB UNORM surface that will not do it
    // for us. Alpha is not a display-encoded quantity and is written untouched.
    oColor.rgb = linear_to_srgb(oColor.rgb);
#endif

    oColor.a = vColor.a;

#if defined(LOGDEPTH_ENABLE)
    const float C = 0.1;
    const float far = 1e+09;
    const float offset = 1.0;
    oDepth = log(C * vDepth + offset) / log(C * far + offset);
#endif
}
