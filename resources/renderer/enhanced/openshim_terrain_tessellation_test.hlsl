// Native terrain subdivision experiment. Consumes the ordinary terrain VS
// outputs; COLOR0 is already swizzled, and UV/height decoding stays in that VS.
#ifndef OPENSHIM_TESS_FACTOR
#define OPENSHIM_TESS_FACTOR 1
#endif
#ifndef OPENSHIM_RELIEF_AMPLITUDE
#define OPENSHIM_RELIEF_AMPLITUDE 0
#endif
#ifndef OPENSHIM_TESS_TARGET_PIXELS
#define OPENSHIM_TESS_TARGET_PIXELS 12
#endif
// Paint relief scales the adaptive request: layers that displace less than
// RELIEF_FULL metres get proportionally fewer segments, down to RELIEF_FLAT.
#ifndef OPENSHIM_TESS_RELIEF_FLAT
#define OPENSHIM_TESS_RELIEF_FLAT 0.4
#endif
#ifndef OPENSHIM_TESS_RELIEF_FULL
#define OPENSHIM_TESS_RELIEF_FULL 1.5
#endif
#if defined(OPENSHIM_HEIGHT_TEST) && (!defined(OPENSHIM_RELIEF_TEST) || defined(VERTEX_LIGHTING))
#error Texture height needs the qualified per-pixel relief interface
#endif
#if defined(OPENSHIM_PAINT_HEIGHT) && (!defined(OPENSHIM_RELIEF_TEST) || !defined(OPENSHIM_TERRAIN_HD) || \
    defined(OPENSHIM_HEIGHT_TEST) || defined(VERTEX_LIGHTING))
#error Paint height needs the paint-mode HD interface and owns the domain texture slot
#endif

#if defined(OPENSHIM_TESS_ADAPTIVE)
// Ogre ACT_VIEWPORT_SIZE supplies width/height and their reciprocals per pass.
float4 tessViewport;
// Only shared endpoints and viewport affect an edge. Material UVs, normals
// and the triangle's third vertex must not change its subdivision request;
// relief is the larger of the two endpoints' own paint relief scales.
float TerrainAdaptiveEdge(float4 a, float4 b, float2 viewport, float relief)
{
    if (!all(isfinite(a)) || !all(isfinite(b)) || !all(isfinite(viewport)) ||
        any(viewport <= 0.0) || any(viewport > 16384.0) || min(a.w,b.w) <= 0.0001)
        return OPENSHIM_TESS_FACTOR;
    float2 pixels = (a.xy / a.w - b.xy / b.w) * viewport * 0.5;
    float extent = length(pixels);
    if (!isfinite(extent)) return OPENSHIM_TESS_FACTOR;
    // Fractional-even retains at least two segments and moves new samples
    // continuously between 2 and the configured cap. Never cull invalid edges.
    return clamp(extent / OPENSHIM_TESS_TARGET_PIXELS * relief, 2.0, OPENSHIM_TESS_FACTOR);
}
#endif

#if defined(OPENSHIM_RELIEF_TEST)
float4x4 reliefView;
float4x4 reliefInverseView;
float4x4 reliefInverseWorldView;
float4x4 reliefProjection;
#if defined(SHADOWRECEIVER)
float4x4 reliefShadow1;
#if defined(PSSM_ENABLED)
float4x4 reliefShadow2;
float4x4 reliefShadow3;
#endif
#endif

// Native cluster translations are multiples of eighty world units (runtime
// checked). A periodic field therefore agrees across clusters while using
// object coordinates, including under camera-relative rendering.
// No camera-driven height fade: a fixed ground point must remain fixed.
float TerrainReliefHash(int2 cell)
{
    uint2 wrapped = uint2(cell) & 31;
    uint key = wrapped.x + wrapped.y * 32;
    key ^= key >> 16;
    key *= 0x7feb352d;
    key ^= key >> 15;
    key *= 0x846ca68b;
    key ^= key >> 16;
    return float(key & 0xffffff) * (2.0 / 16777215.0) - 1.0;
}

float3 TerrainMicroRelief(float2 objectXZ)
{
    float2 grid = objectXZ * 0.4; // 2.5 world units per noise cell
    int2 cell = int2(floor(grid));
    float2 f = frac(grid);
    // Quintic interpolation has zero first AND second derivatives at cell
    // boundaries, avoiding curvature kinks without changing phase or bounds.
    float2 blend = f * f * f * (f * (f * 6.0 - 15.0) + 10.0);
    float2 derivative = 30.0 * f * f * (f - 1.0) * (f - 1.0) * 0.4;
    float a = TerrainReliefHash(cell);
    float b = TerrainReliefHash(cell + int2(1,0));
    float c = TerrainReliefHash(cell + int2(0,1));
    float d = TerrainReliefHash(cell + int2(1,1));
    float h = lerp(lerp(a,b,blend.x), lerp(c,d,blend.x), blend.y);
    float2 dh = float2(lerp(b-a,d-c,blend.y) * derivative.x,
        lerp(c-a,d-b,blend.x) * derivative.y);
    return OPENSHIM_RELIEF_AMPLITUDE * float3(h, dh);
}

float2 TerrainReliefObjectXZ(float3 viewPosition, float4x4 inverseWorldView)
{
    return mul(inverseWorldView, float4(viewPosition, 1.0)).xz;
}

#if defined(OPENSHIM_HEIGHT_TEST)
// Native packs can opt into signed-unit R32 heights, scaled by their relief
// amplitude. The older GPU candidate uses explicit world meters. Mip zero
// with manual bilinear Load needs no sampler or implicit DS derivatives.
Texture2D<float> terrainHeightAtlas : register(t127);

float3 TerrainHeightSample(float2 uv)
{
    uint width, height;
    terrainHeightAtlas.GetDimensions(width, height);
    if (width < 2 || height < 2 || !all(isfinite(uv))) return 0.0;
    float2 size = float2(width, height);
    float2 pixel = clamp(uv * size - 0.5, 0.0, size - 1.0);
    int2 lo = int2(floor(pixel));
    int2 hi = min(lo + 1, int2(width - 1, height - 1));
    float2 f = frac(pixel);
    float a = terrainHeightAtlas.Load(int3(lo,0));
    float b = terrainHeightAtlas.Load(int3(hi.x,lo.y,0));
    float c = terrainHeightAtlas.Load(int3(lo.x,hi.y,0));
    float d = terrainHeightAtlas.Load(int3(hi,0));
#if defined(OPENSHIM_HEIGHT_NORMALIZED)
    a *= OPENSHIM_RELIEF_AMPLITUDE;
    b *= OPENSHIM_RELIEF_AMPLITUDE;
    c *= OPENSHIM_RELIEF_AMPLITUDE;
    d *= OPENSHIM_RELIEF_AMPLITUDE;
#endif
    if (!all(isfinite(float4(a,b,c,d))) ||
        any(abs(float4(a,b,c,d)) > OPENSHIM_RELIEF_AMPLITUDE)) return 0.0;
    float value = lerp(lerp(a,b,f.x),lerp(c,d,f.x),f.y);
    float2 gradient = float2(lerp(b-a,d-c,f.y),lerp(c-a,d-b,f.x)) * size;
    if (uv.x * size.x - 0.5 < 0.0 || uv.x * size.x - 0.5 > size.x - 1.0) gradient.x = 0;
    if (uv.y * size.y - 0.5 < 0.0 || uv.y * size.y - 0.5 > size.y - 1.0) gradient.y = 0;
    return float3(value, gradient);
}

float3 TerrainHeightRelief(float2 uv, float2 xz0, float2 xz1, float2 xz2,
                          float2 uv0, float2 uv1, float2 uv2)
{
    float2 e1 = xz1 - xz0, e2 = xz2 - xz0;
    float determinant = e1.x * e2.y - e1.y * e2.x;
    float areaScale = max(dot(e1,e1),dot(e2,e2));
    if (!all(isfinite(float4(e1,e2))) || !all(isfinite(float4(uv1-uv0,uv2-uv0))) ||
        !isfinite(determinant) || areaScale <= 0.0 || abs(determinant) <= areaScale * 1e-6) return 0.0;
    float2 t1 = uv1 - uv0, t2 = uv2 - uv0;
    float uvDeterminant = t1.x * t2.y - t1.y * t2.x;
    float uvScale = max(dot(t1,t1),dot(t2,t2));
    if (!isfinite(uvDeterminant) || uvScale <= 0.0 || abs(uvDeterminant) <= uvScale * 1e-6) return 0.0;
    float2 uvDx = (t1 * e2.y - t2 * e1.y) / determinant;
    float2 uvDz = (t2 * e1.x - t1 * e2.x) / determinant;
    float3 sample = TerrainHeightSample(uv);
    float3 result = float3(sample.x, dot(sample.yz,uvDx), dot(sample.yz,uvDz));
    return all(isfinite(result)) ? result : 0.0;
}
#endif

#if defined(OPENSHIM_PAINT_HEIGHT)
// Full-material paint array: control in slice 4, layer heights in the alpha
// of normal slices 5-8. hdUV carries native world XZ in paint mode. Heights
// are a pure function of world XZ at a fixed mip per layer, so the two
// patches on a shared edge displace it identically and no cracks open.
Texture2DArray<float4> terrainPaintArray : register(t127);

// A bilinear tap and its exact derivative per unit of uv (piecewise constant
// per texel, like the filter), so the relief's slope needs no extra taps.
struct TerrainPaintTap { float4 v; float4 du; float4 dv; };
TerrainPaintTap TerrainPaintBilinearGrad(float2 uv, uint slice, uint mip, bool wrap)
{
    uint width, height, elements, levels;
    terrainPaintArray.GetDimensions(mip, width, height, elements, levels);
    int2 size = int2(width, height);
    float2 pixel = (wrap ? frac(uv) : uv) * float2(size) - 0.5;
    // A clamped axis is flat past the edge texels.
    float2 inside = wrap ? 1.0 : step(0.0, pixel) * step(pixel, float2(size - 1));
    if (!wrap) pixel = clamp(pixel, 0.0, float2(size - 1));
    int2 lo = int2(floor(pixel));
    float2 f = pixel - float2(lo);
    int2 hi = min(lo + 1, size - 1);
    if (wrap) { hi = lo + 1 >= size ? 0 : lo + 1; lo = lo < 0 ? size - 1 : lo; }
    float4 a = terrainPaintArray.Load(int4(lo, slice, mip));
    float4 b = terrainPaintArray.Load(int4(hi.x, lo.y, slice, mip));
    float4 c = terrainPaintArray.Load(int4(lo.x, hi.y, slice, mip));
    float4 d = terrainPaintArray.Load(int4(hi, slice, mip));
    TerrainPaintTap t;
    t.v = lerp(lerp(a, b, f.x), lerp(c, d, f.x), f.y);
    t.du = lerp(b - a, d - c, f.y) * (size.x * inside.x);
    t.dv = lerp(c - a, d - b, f.x) * (size.y * inside.y);
    return t;
}

float4 TerrainPaintBilinear(float2 uv, uint slice, uint mip, bool wrap)
{
    return TerrainPaintBilinearGrad(uv, slice, mip, wrap).v;
}

uint TerrainPaintMip(float repeat)
{
    uint width, height, elements, levels;
    terrainPaintArray.GetDimensions(0, width, height, elements, levels);
    // Sample at roughly the finest tessellated vertex spacing (5 m native
    // grid / factor); finer texels would only alias between vertices.
    float spacing = 5.0 / OPENSHIM_TESS_FACTOR;
    return uint(clamp(ceil(log2(max(spacing * width / repeat, 1.0))), 0.0, float(levels - 1)));
}

// Layer height and its slope per world metre.
float3 TerrainPaintLayerHeightGrad(float2 worldXZ, float repeat, uint slice, bool detile)
{
    float2 uv = worldXZ / repeat;
    uint mip = TerrainPaintMip(repeat);
    if (!detile)
    {
        TerrainPaintTap t = TerrainPaintBilinearGrad(uv, slice, mip, true);
        return float3(t.v.a, float2(t.du.a, t.dv.a) / repeat);
    }
    // Same offsets as the pixel shader's top projection; outside the band
    // only one tap counts.
    OpenShimDetile d = OpenShimDetileAt(uv);
    float3 a = 0, b = 0;
    [branch] if (d.t < 1)
    {
        TerrainPaintTap t = TerrainPaintBilinearGrad(uv + d.a, slice, mip, true);
        a = float3(t.v.a, t.du.a, t.dv.a);
    }
    [branch] if (d.t > 0)
    {
        TerrainPaintTap t = TerrainPaintBilinearGrad(uv + d.b, slice, mip, true);
        b = float3(t.v.a, t.du.a, t.dv.a);
    }
    float3 h = lerp(a, b, d.t);
    if (d.t > 0 && d.t < 1) h.yz += (b.x - a.x) * OpenShimDetileSlope(uv);
    return float3(h.x, h.yz / repeat);
}

float TerrainPaintLayerHeight(float2 worldXZ, float repeat, uint slice, bool detile)
{
    return TerrainPaintLayerHeightGrad(worldXZ, repeat, slice, detile).x;
}

// Height and its world XZ slope from one evaluation: every step (bilinear
// taps, normalisation, the height-aware selection, craters, detail) is
// differentiated alongside its value as (value, d/dx, d/dz), where finite
// differences took four more full evaluations.
float3 TerrainPaintRelief(float2 worldXZ)
{
    if (!all(isfinite(worldXZ))) return 0.0;
    float2 span = OPENSHIM_PAINT_BOUNDS.zw - OPENSHIM_PAINT_BOUNDS.xy;
    float2 paintUV = (worldXZ - OPENSHIM_PAINT_BOUNDS.xy) / span;
    float3 control[OPENSHIM_PAINT_LAYERS];
    float3 total = 0;
    [unroll] for (int b = 0; b < OPENSHIM_PAINT_LAYERS / 4; ++b)
    {
        TerrainPaintTap t = TerrainPaintBilinearGrad(paintUV, uint(OpenShimPaintSlice(b * 4, 4)), 0, false);
        [unroll] for (int c = 0; c < 4; ++c)
        {
            control[b * 4 + c] = t.v[c] > 0 ? float3(t.v[c], t.du[c] / span.x, t.dv[c] / span.y) : 0.0;
            total += control[b * 4 + c];
        }
    }
    // OpenShimPaintNormalize, differentiated.
    OpenShimPaintMix weights;
    float3 mix[OPENSHIM_PAINT_LAYERS];
    [unroll] for (int n = 0; n < OPENSHIM_PAINT_LAYERS; ++n)
    {
        mix[n] = total.x > 0.00001 ? float3(control[n].x / total.x, (control[n].yz * total.x - control[n].x * total.yz) / (total.x * total.x))
                                   : float3(n == 0 ? 1.0 : 0.0, 0, 0);
        weights.w[n] = mix[n].x;
    }
    float3 heights[OPENSHIM_PAINT_LAYERS];
    [unroll] for (int i = 0; i < OPENSHIM_PAINT_LAYERS; ++i)
    {
        heights[i] = float3(0.5, 0, 0);
        [branch] if (OpenShimPaintPresent(weights, i))
            heights[i] = TerrainPaintLayerHeightGrad(worldXZ, openShimPaintRepeats[i], uint(OpenShimPaintSlice(i, 5)), openShimPaintDetile[i] > 0);
    }
    // OpenShimPaintSelect, differentiated: it is piecewise linear.
    float3 lifted[OPENSHIM_PAINT_LAYERS];
    float3 crest = 0;
    [unroll] for (int s = 0; s < OPENSHIM_PAINT_LAYERS; ++s)
    {
        lifted[s] = OpenShimPaintPresent(weights, s) ? mix[s] + heights[s] * openShimPaintHeightBlend : 0.0;
        if (lifted[s].x > crest.x) crest = lifted[s];
    }
    float3 kept[OPENSHIM_PAINT_LAYERS];
    float3 keptTotal = 0;
    [unroll] for (int k = 0; k < OPENSHIM_PAINT_LAYERS; ++k)
    {
        float3 above = lifted[k] - (crest - float3(0.2, 0, 0));
        kept[k] = OpenShimPaintPresent(weights, k) && above.x > 0 ? above : 0.0;
        keptTotal += kept[k];
    }
    float3 value = 0, craterMix = 0, detailMix = 0;
    [unroll] for (int j = 0; j < OPENSHIM_PAINT_LAYERS; ++j)
    {
        float3 w = keptTotal.x > 0.00001 ? float3(kept[j].x / keptTotal.x, (kept[j].yz * keptTotal.x - kept[j].x * keptTotal.yz) / (keptTotal.x * keptTotal.x))
                                         : mix[j];
        float h = heights[j].x - 0.5;
        value += float3(w.x * h, w.yz * h + w.x * heights[j].yz) * openShimPaintHeightMeters[j];
        craterMix += w * openShimPaintCraterLayers[j];
        detailMix += w * openShimPaintDetailLayers[j];
    }
#if defined(OPENSHIM_PAINT_CRATERS)
    // The pixel shader's crater field, faded at the vertex spacing.
    OpenShimCrater crater = OpenShimCraterField(worldXZ, OPENSHIM_PAINT_CRATERS, 5.0 / OPENSHIM_TESS_FACTOR);
    value += float3(crater.h * craterMix.x, crater.slope * craterMix.x + crater.h * craterMix.yz);
#endif
#if defined(OPENSHIM_PAINT_DETAIL)
    OpenShimCrater detail = OpenShimDetailField(worldXZ, OPENSHIM_PAINT_DETAIL, 5.0 / OPENSHIM_TESS_FACTOR);
    value += float3(detail.h * detailMix.x, detail.slope * detailMix.x + detail.h * detailMix.yz);
#endif
    value *= OPENSHIM_PAINT_HEIGHT_SCALE;
    if (!all(isfinite(value))) return 0.0;
    // Pinned at the clamp, the surface is flat.
    return abs(value.x) > OPENSHIM_RELIEF_AMPLITUDE ? float3(clamp(value.x, -OPENSHIM_RELIEF_AMPLITUDE, OPENSHIM_RELIEF_AMPLITUDE), 0, 0) : value;
}

#if defined(OPENSHIM_TESS_ADAPTIVE)
// Hull side: how far a vertex's layer mix can displace, from the control
// maps alone, as a 0..1 tessellation scale. A pure function of world XZ.
float TerrainPaintReliefScale(float2 worldXZ)
{
    if (!all(isfinite(worldXZ))) return 1.0;
    float2 paintUV = (worldXZ - OPENSHIM_PAINT_BOUNDS.xy) / (OPENSHIM_PAINT_BOUNDS.zw - OPENSHIM_PAINT_BOUNDS.xy);
    float4 banks[OPENSHIM_PAINT_LAYERS / 4];
    [unroll] for (int b = 0; b < OPENSHIM_PAINT_LAYERS / 4; ++b)
        banks[b] = TerrainPaintBilinear(paintUV, uint(OpenShimPaintSlice(b * 4, 4)), 0, false);
    float span = OpenShimPaintDot(OpenShimPaintNormalize(banks), openShimPaintReliefMeters) * OPENSHIM_PAINT_HEIGHT_SCALE;
    return isfinite(span) ? lerp(OPENSHIM_TESS_RELIEF_FLAT, 1.0, saturate(span / OPENSHIM_TESS_RELIEF_FULL)) : 1.0;
}
#endif
#endif
#endif

struct TerrainTessVertex
{
    float4 color : COLOR0;
#if defined(VERTEX_LIGHTING)
    float3 light : COLOR1;
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    float3 specular : COLOR2;
#endif
#endif
    float2 uv : TEXCOORD0;
#if defined(OPENSHIM_TERRAIN_HD)
    float2 hdUV : TEXCOORD9;
    float tileSlice : TEXCOORD10;
#endif
#if !defined(VERTEX_LIGHTING)
    float3 normal : TEXCOORD2;
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    float3 tangent : TEXCOORD3;
#endif
    float3 viewPosition : TEXCOORD4;
#endif
    float depth : TEXCOORD5;
#if defined(SHADOWRECEIVER)
    float4 shadow1 : TEXCOORD6;
#if defined(PSSM_ENABLED)
    float4 shadow2 : TEXCOORD7;
    float4 shadow3 : TEXCOORD8;
#endif
#endif
    float4 position : SV_POSITION;
};

struct TerrainTessFactors
{
    float edge[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

TerrainTessFactors TerrainPatchConstants(InputPatch<TerrainTessVertex, 3> p)
{
    TerrainTessFactors f;
#if defined(OPENSHIM_TESS_ADAPTIVE)
    float relief[3] = { 1.0, 1.0, 1.0 };
#if defined(OPENSHIM_PAINT_HEIGHT)
    [unroll] for (int i = 0; i < 3; ++i) relief[i] = TerrainPaintReliefScale(p[i].hdUV);
#endif
    f.edge[0] = TerrainAdaptiveEdge(p[1].position,p[2].position,tessViewport.xy,max(relief[1],relief[2]));
    f.edge[1] = TerrainAdaptiveEdge(p[2].position,p[0].position,tessViewport.xy,max(relief[2],relief[0]));
    f.edge[2] = TerrainAdaptiveEdge(p[0].position,p[1].position,tessViewport.xy,max(relief[0],relief[1]));
    f.inside = max(f.edge[0],max(f.edge[1],f.edge[2]));
#else
    f.edge[0] = f.edge[1] = f.edge[2] = OPENSHIM_TESS_FACTOR;
    f.inside = OPENSHIM_TESS_FACTOR;
#endif
    return f;
}

[domain("tri")]
#if defined(OPENSHIM_TESS_ADAPTIVE)
[partitioning("fractional_even")]
#else
[partitioning("integer")]
#endif
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("TerrainPatchConstants")]
TerrainTessVertex TerrainHull(InputPatch<TerrainTessVertex, 3> p,
                              uint id : SV_OutputControlPointID)
{
    return p[id];
}

#define TERRAIN_INTERPOLATE(field) o.field = p[0].field * b.x + p[1].field * b.y + p[2].field * b.z
[domain("tri")]
TerrainTessVertex TerrainDomain(TerrainTessFactors f, float3 b : SV_DomainLocation,
                                const OutputPatch<TerrainTessVertex, 3> p)
{
    TerrainTessVertex o;
    TERRAIN_INTERPOLATE(color);
    TERRAIN_INTERPOLATE(uv);
#if defined(OPENSHIM_TERRAIN_HD)
    TERRAIN_INTERPOLATE(hdUV);
    TERRAIN_INTERPOLATE(tileSlice);
#endif
    TERRAIN_INTERPOLATE(depth);
    TERRAIN_INTERPOLATE(position);
#if defined(VERTEX_LIGHTING)
    TERRAIN_INTERPOLATE(light);
#if defined(SPECULAR_ENABLED) || defined(SPECULARMAP_ENABLED)
    TERRAIN_INTERPOLATE(specular);
#endif
#else
    TERRAIN_INTERPOLATE(normal);
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    TERRAIN_INTERPOLATE(tangent);
#endif
    TERRAIN_INTERPOLATE(viewPosition);
#endif
#if defined(SHADOWRECEIVER)
    TERRAIN_INTERPOLATE(shadow1);
#if defined(PSSM_ENABLED)
    TERRAIN_INTERPOLATE(shadow2);
    TERRAIN_INTERPOLATE(shadow3);
#endif
#endif
// Recover native object position with inverse WORLD-view, which remains
// valid when Ogre subtracts the camera origin from world/view transforms.
#if defined(OPENSHIM_RELIEF_TEST)
#if defined(OPENSHIM_PAINT_HEIGHT)
    // hdUV is world XZ and object XZ differs only by translation, so the
    // world-space gradient is already the object-space one.
    float3 relief = TerrainPaintRelief(o.hdUV);
#elif defined(OPENSHIM_HEIGHT_TEST)
    float3 relief = TerrainHeightRelief(o.uv,
        TerrainReliefObjectXZ(p[0].viewPosition, reliefInverseWorldView),
        TerrainReliefObjectXZ(p[1].viewPosition, reliefInverseWorldView),
        TerrainReliefObjectXZ(p[2].viewPosition, reliefInverseWorldView),
        p[0].uv, p[1].uv, p[2].uv);
#else
    float3 relief = TerrainMicroRelief(TerrainReliefObjectXZ(o.viewPosition, reliefInverseWorldView));
#endif
    float3 worldNormal = normalize(mul(reliefInverseView, float4(o.normal, 0.0)).xyz);
    // The differential of (x,y,z) -> (x,y+h(x,z),z) transforms the normal
    // by inverse transpose; this preserves native slopes and adds relief.
    worldNormal = normalize(float3(worldNormal.x - worldNormal.y * relief.y,
        worldNormal.y, worldNormal.z - worldNormal.y * relief.z));
    o.normal = mul(reliefView, float4(worldNormal, 0.0)).xyz;
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    float3 worldTangent = mul(reliefInverseView, float4(o.tangent, 0.0)).xyz;
    worldTangent.y += relief.y * worldTangent.x + relief.z * worldTangent.z;
    o.tangent = mul(reliefView, float4(normalize(worldTangent), 0.0)).xyz;
#endif
    float4 vertical = float4(0.0, relief.x, 0.0, 0.0);
    o.viewPosition += mul(reliefView, vertical).xyz;
    o.position += mul(reliefProjection, mul(reliefView, vertical));
    o.depth = o.position.z;
#if defined(SHADOWRECEIVER)
    o.shadow1 += mul(reliefShadow1, vertical);
#if defined(PSSM_ENABLED)
    o.shadow2 += mul(reliefShadow2, vertical);
    o.shadow3 += mul(reliefShadow3, vertical);
#endif
#endif
#endif
    return o;
}
