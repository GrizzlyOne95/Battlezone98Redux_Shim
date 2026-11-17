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
// TerrainTessellationSmoothing (OPENSHIM_LATTICE_SMOOTH): a smooth surface
// through the 5 m height lattice moves the tessellated terrain at most
// OPENSHIM_LATTICE_MAX world units up or down. It needs paint-mode world XZ
// (hdUV) and world Y (tileSlice); the installer only enables it in paint mode.
#if defined(OPENSHIM_LATTICE_SMOOTH) && (!defined(OPENSHIM_RELIEF_TEST) || !defined(OPENSHIM_TERRAIN_HD) || \
    defined(VERTEX_LIGHTING) || !defined(OPENSHIM_LATTICE_OFFSET))
#error Lattice smoothing needs the per-pixel relief interface, paint-mode world XZ and the lattice mapping
#endif
#ifndef OPENSHIM_LATTICE_MAX
#define OPENSHIM_LATTICE_MAX 4.0
#endif
// Culling and render bounds sweep the relief and the smoothing together.
#if defined(OPENSHIM_LATTICE_SMOOTH)
#define OPENSHIM_RELIEF_SWEEP (OPENSHIM_RELIEF_AMPLITUDE + OPENSHIM_LATTICE_MAX)
#else
#define OPENSHIM_RELIEF_SWEEP OPENSHIM_RELIEF_AMPLITUDE
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
    // The pixel shader's crater field, faded at the vertex spacing. Ground
    // without crater layers, and so no crater slope either, skips it.
    [branch] if (any(craterMix != 0))
    {
        OpenShimCrater crater = OpenShimCraterField(worldXZ, OPENSHIM_PAINT_CRATERS, 5.0 / OPENSHIM_TESS_FACTOR);
        value += float3(crater.h * craterMix.x, crater.slope * craterMix.x + crater.h * craterMix.yz);
    }
#endif
#if defined(OPENSHIM_PAINT_DETAIL)
    [branch] if (any(detailMix != 0))
    {
        OpenShimCrater detail = OpenShimDetailField(worldXZ, OPENSHIM_PAINT_DETAIL, 5.0 / OPENSHIM_TESS_FACTOR);
        value += float3(detail.h * detailMix.x, detail.slope * detailMix.x + detail.h * detailMix.yz);
    }
#endif
    value *= OPENSHIM_PAINT_HEIGHT_SCALE;
    if (!all(isfinite(value))) return 0.0;
    // Pinned at the clamp, the surface is flat.
    return abs(value.x) > OPENSHIM_RELIEF_AMPLITUDE ? float3(clamp(value.x, -OPENSHIM_RELIEF_AMPLITUDE, OPENSHIM_RELIEF_AMPLITUDE), 0, 0) : value;
}

#if defined(OPENSHIM_TESS_ADAPTIVE)
// Hull side: how far a vertex's layer mix can displace, from the control
// maps alone, in metres. A pure function of world XZ; non-finite -> huge.
float TerrainPaintReliefSpan(float2 worldXZ)
{
    if (!all(isfinite(worldXZ))) return 1.0e6;
    float2 paintUV = (worldXZ - OPENSHIM_PAINT_BOUNDS.xy) / (OPENSHIM_PAINT_BOUNDS.zw - OPENSHIM_PAINT_BOUNDS.xy);
    float4 banks[OPENSHIM_PAINT_LAYERS / 4];
    [unroll] for (int b = 0; b < OPENSHIM_PAINT_LAYERS / 4; ++b)
        banks[b] = TerrainPaintBilinear(paintUV, uint(OpenShimPaintSlice(b * 4, 4)), 0, false);
    float span = OpenShimPaintDot(OpenShimPaintNormalize(banks), openShimPaintReliefMeters) * OPENSHIM_PAINT_HEIGHT_SCALE;
    return isfinite(span) ? span : 1.0e6;
}

// Lattice smoothing on the hull: how far it can move an edge, from the
// world-Y difference of its two endpoints (tileSlice). Smoothing follows
// curvature, which needs height change: level ground adds nothing, and a
// drop of OPENSHIM_TESS_RELIEF_FULL / OPENSHIM_LATTICE_TESS_SLOPE (6 m) or
// more reaches full scale when the Max allows. Endpoints only, so both
// patches of a shared edge compute the same factor (no T-junction).
#ifndef OPENSHIM_LATTICE_TESS_SLOPE
#define OPENSHIM_LATTICE_TESS_SLOPE 0.25
#endif
float TerrainLatticeTessSpan(float y0, float y1)
{
#if defined(OPENSHIM_LATTICE_SMOOTH)
    float range = abs(y0 - y1);
    return isfinite(range) ? min(OPENSHIM_LATTICE_MAX, OPENSHIM_LATTICE_TESS_SLOPE * range) : OPENSHIM_LATTICE_MAX;
#else
    return 0.0;
#endif
}

// Relief span in metres -> 0..1 tessellation scale.
float TerrainReliefScale(float span)
{
    return isfinite(span) ? lerp(OPENSHIM_TESS_RELIEF_FLAT, 1.0, saturate(span / OPENSHIM_TESS_RELIEF_FULL)) : 1.0;
}

// One edge's scale: the larger endpoint paint span plus the edge's lattice span.
float TerrainEdgeReliefScale(float paintA, float paintB, float yA, float yB)
{
    return TerrainReliefScale(max(paintA, paintB) + TerrainLatticeTessSpan(yA, yB));
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

#if defined(OPENSHIM_RELIEF_TEST)
// A patch can be skipped (tess factor 0) only when all three corners, each
// swept through the full clamped relief range, lie outside the same clip
// plane or behind the eye. Non-finite input, or a hull whose matrices were
// never bound (a zero projection w row), is never culled.
bool TerrainPatchOffscreen(float4 a, float4 b, float4 c)
{
    if (all(reliefProjection[3] == 0.0)) return false;
    float4 sweep = mul(reliefProjection, mul(reliefView, float4(0.0, OPENSHIM_RELIEF_SWEEP, 0.0, 0.0)));
    if (!all(isfinite(a)) || !all(isfinite(b)) || !all(isfinite(c)) || !all(isfinite(sweep))) return false;
    float4 corner[6] = { a + sweep, a - sweep, b + sweep, b - sweep, c + sweep, c - sweep };
    bool4 sideOut = bool4(true, true, true, true);
    bool behind = true;
    [unroll] for (int i = 0; i < 6; ++i)
    {
        float4 q = corner[i];
        sideOut = sideOut && (float4(q.x, -q.x, q.y, -q.y) > q.w + abs(q.w) * 0.02);
        behind = behind && (q.w <= 0.0);
    }
    return any(sideOut) || behind;
}
#endif


TerrainTessFactors TerrainPatchConstants(InputPatch<TerrainTessVertex, 3> p)
{
    TerrainTessFactors f;
#if defined(OPENSHIM_TESS_ADAPTIVE)
    float relief[3] = { 1.0, 1.0, 1.0 };
#if defined(OPENSHIM_PAINT_HEIGHT)
    float paint[3];
    [unroll] for (int i = 0; i < 3; ++i) paint[i] = TerrainPaintReliefSpan(p[i].hdUV);
    relief[0] = TerrainEdgeReliefScale(paint[1], paint[2], p[1].tileSlice, p[2].tileSlice);
    relief[1] = TerrainEdgeReliefScale(paint[2], paint[0], p[2].tileSlice, p[0].tileSlice);
    relief[2] = TerrainEdgeReliefScale(paint[0], paint[1], p[0].tileSlice, p[1].tileSlice);
#endif
    f.edge[0] = TerrainAdaptiveEdge(p[1].position,p[2].position,tessViewport.xy,relief[0]);
    f.edge[1] = TerrainAdaptiveEdge(p[2].position,p[0].position,tessViewport.xy,relief[1]);
    f.edge[2] = TerrainAdaptiveEdge(p[0].position,p[1].position,tessViewport.xy,relief[2]);
    f.inside = max(f.edge[0],max(f.edge[1],f.edge[2]));
#else
    f.edge[0] = f.edge[1] = f.edge[2] = OPENSHIM_TESS_FACTOR;
    f.inside = OPENSHIM_TESS_FACTOR;
#endif
#if defined(OPENSHIM_RELIEF_TEST)
    if (TerrainPatchOffscreen(p[0].position, p[1].position, p[2].position))
        f.edge[0] = f.edge[1] = f.edge[2] = f.inside = 0.0;
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

#if defined(OPENSHIM_LATTICE_SMOOTH)
// The whole runtime height lattice in masked 0.1 m units (R16_UINT, mip 0).
// include/terrain_lattice_smoothing.h is the CPU reference of this curve.
Texture2D<uint> terrainLattice : register(t126);

struct TerrainLatticeSegment { float h; float slope; int clampedTo; };
// Catmull-Rom between p1 (t = 0, exact) and p2 (t = 1), clamped to that
// segment's own range so no 1D pass overshoots.
TerrainLatticeSegment TerrainLatticeCatmullRom(float p0, float p1, float p2, float p3, float t)
{
    float a = (-p0 + 3.0 * p1) + (p3 - 3.0 * p2);
    float b = (2.0 * p0 - 5.0 * p1) + (4.0 * p2 - p3);
    float c = p2 - p0;
    TerrainLatticeSegment s;
    s.h = 0.5 * (((a * t + b) * t + c) * t) + p1;
    s.slope = 0.5 * ((3.0 * a * t + 2.0 * b) * t + c);
    s.clampedTo = 0;
    float lo = min(p1, p2), hi = max(p1, p2);
    if (s.h < lo || s.h > hi)
    {
        bool low = s.h < lo;
        s.h = low ? lo : hi;
        s.clampedTo = (low ? p1 <= p2 : p1 > p2) ? 1 : 2;
        s.slope = 0.0;
    }
    return s;
}

float TerrainLatticeFetch(int x, int z, int2 size)
{
    int2 texel = clamp(int2(x, z), int2(0, 0), size - 1);
    return float(terrainLattice.Load(int3(texel, 0)) & 0x1FFF) * 0.1;
}

// float4(height, dh/dX, dh/dZ, valid) in world metres at native world XZ.
// Separable bicubic: each pass clamps to its own segment, so the height stays
// within the central 2x2 samples and is continuous across cell borders.
float4 TerrainLatticeSurface(float2 worldXZ)
{
    uint width, height;
    terrainLattice.GetDimensions(width, height);
    if (width < 4 || height < 4 || !all(isfinite(worldXZ))) return 0.0;
    int2 size = int2(width, height);
    float2 g = float2(worldXZ.x * 0.2 + OPENSHIM_LATTICE_OFFSET.x, OPENSHIM_LATTICE_OFFSET.y - worldXZ.y * 0.2);
    float2 cell = floor(g);
    if (any(abs(cell) > 32768.0)) return 0.0;
    int2 i = int2(cell);
    float2 t = g - cell;
    float row[4], rowSlope[4];
    [unroll] for (int r = 0; r < 4; ++r)
    {
        int z = i.y - 1 + r;
        TerrainLatticeSegment s = TerrainLatticeCatmullRom(TerrainLatticeFetch(i.x - 1, z, size),
            TerrainLatticeFetch(i.x, z, size), TerrainLatticeFetch(i.x + 1, z, size),
            TerrainLatticeFetch(i.x + 2, z, size), t.x);
        row[r] = s.h;
        rowSlope[r] = s.slope;
    }
    TerrainLatticeSegment column = TerrainLatticeCatmullRom(row[0], row[1], row[2], row[3], t.y);
    float dx;
    if (column.clampedTo == 1) dx = rowSlope[1];
    else if (column.clampedTo == 2) dx = rowSlope[2];
    else
    {
        float t2 = t.y * t.y, t3 = t2 * t.y;
        float4 w = 0.5 * float4(-t.y + 2.0 * t2 - t3, 2.0 - 5.0 * t2 + 3.0 * t3, t.y + 4.0 * t2 - 3.0 * t3, t3 - t2);
        dx = dot(w, float4(rowSlope[0], rowSlope[1], rowSlope[2], rowSlope[3]));
    }
    // Lattice x follows world +X; lattice z runs toward world -Z.
    float4 result = float4(column.h, dx * 0.2, -column.slope * 0.2, 1.0);
    return all(isfinite(result)) ? result : 0.0;
}

// Interpolation from the control points with unfused products summed in a
// fixed order. On a shared edge the opposite weight is exactly 0, so both
// patches add the same two rounded products (IEEE addition commutes) and
// produce the same bits whichever slot each endpoint occupies.
float2 TerrainLatticeLerp2(float2 a, float2 b, float2 c, float3 w)
{
    precise float2 r = (a * w.x + b * w.y) + c * w.z;
    return r;
}

float TerrainLatticeLerp1(float a, float b, float c, float3 w)
{
    precise float r = (a * w.x + b * w.y) + c * w.z;
    return r;
}
#endif

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
    float latticeDelta = 0.0;
#if defined(OPENSHIM_LATTICE_SMOOTH)
    // Paint mode: hdUV is native world XZ and tileSlice native world Y, so
    // the offset depends only on world XZ and the stock (linear) height.
    // 0 = stock normal/tangent, 1 = the smoothed surface's.
    float latticeWeight = 0.0;
    float3 latticeWorldNormal = float3(0.0, 1.0, 0.0);
    {
        float2 worldXZ = TerrainLatticeLerp2(p[0].hdUV, p[1].hdUV, p[2].hdUV, b);
        float linearY = TerrainLatticeLerp1(p[0].tileSlice, p[1].tileSlice, p[2].tileSlice, b);
        float4 surface = TerrainLatticeSurface(worldXZ);
        float delta = surface.x - linearY;
        if (surface.w > 0.0 && isfinite(delta))
        {
            latticeDelta = clamp(delta, -OPENSHIM_LATTICE_MAX, OPENSHIM_LATTICE_MAX);
            // Well inside the bound the surface is the bicubic one: take its
            // analytic normal. Pinned at the clamp it keeps the stock slope.
            // Blend over the last quarter of the bound so the clamp line
            // leaves no shading seam.
            latticeWeight = saturate((OPENSHIM_LATTICE_MAX - abs(delta)) / (0.25 * OPENSHIM_LATTICE_MAX));
            latticeWorldNormal = normalize(float3(-surface.y, 1.0, -surface.z));
            float3 blended = lerp(worldNormal, latticeWorldNormal, latticeWeight);
            if (latticeWeight > 0.0 && all(isfinite(blended)) && dot(blended, blended) > 1e-12)
                worldNormal = normalize(blended);
        }
    }
#endif
    // The differential of (x,y,z) -> (x,y+h(x,z),z) transforms the normal
    // by inverse transpose; this preserves native slopes and adds relief.
    worldNormal = normalize(float3(worldNormal.x - worldNormal.y * relief.y,
        worldNormal.y, worldNormal.z - worldNormal.y * relief.z));
    o.normal = mul(reliefView, float4(worldNormal, 0.0)).xyz;
#if defined(NORMALMAP_ENABLED) && defined(VERTEX_TANGENTS)
    float3 worldTangent = mul(reliefInverseView, float4(o.tangent, 0.0)).xyz;
#if defined(OPENSHIM_LATTICE_SMOOTH)
    // Lay the stock tangent onto the smoothed surface before the relief slope.
    worldTangent -= latticeWeight * latticeWorldNormal * dot(worldTangent, latticeWorldNormal);
#endif
    worldTangent.y += relief.y * worldTangent.x + relief.z * worldTangent.z;
    o.tangent = mul(reliefView, float4(normalize(worldTangent), 0.0)).xyz;
#endif
    float4 vertical = float4(0.0, relief.x + latticeDelta, 0.0, 0.0);
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
