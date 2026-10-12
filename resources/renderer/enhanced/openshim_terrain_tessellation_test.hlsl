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
#if defined(OPENSHIM_HEIGHT_TEST) && (!defined(OPENSHIM_RELIEF_TEST) || defined(VERTEX_LIGHTING))
#error Texture height needs the qualified per-pixel relief interface
#endif

#if defined(OPENSHIM_TESS_ADAPTIVE)
// Ogre ACT_VIEWPORT_SIZE supplies width/height and their reciprocals per pass.
float4 tessViewport;
// Only shared endpoints and viewport affect an edge. Material UVs, normals
// and the triangle's third vertex must not change its subdivision request.
float TerrainAdaptiveEdge(float4 a, float4 b, float2 viewport)
{
    if (!all(isfinite(a)) || !all(isfinite(b)) || !all(isfinite(viewport)) ||
        any(viewport <= 0.0) || any(viewport > 16384.0) || min(a.w,b.w) <= 0.0001)
        return OPENSHIM_TESS_FACTOR;
    float2 pixels = (a.xy / a.w - b.xy / b.w) * viewport * 0.5;
    float extent = length(pixels);
    if (!isfinite(extent)) return OPENSHIM_TESS_FACTOR;
    // Fractional-even retains at least two segments and moves new samples
    // continuously between 2 and the configured cap. Never cull invalid edges.
    return clamp(extent / OPENSHIM_TESS_TARGET_PIXELS, 2.0, OPENSHIM_TESS_FACTOR);
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
// Experimental GPU-qualified path; the native material installer does not
// enable this define until submission/resource ownership is qualified.
// An explicit signed R32_FLOAT height atlas stores world meters. Mip zero
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
    f.edge[0] = TerrainAdaptiveEdge(p[1].position,p[2].position,tessViewport.xy);
    f.edge[1] = TerrainAdaptiveEdge(p[2].position,p[0].position,tessViewport.xy);
    f.edge[2] = TerrainAdaptiveEdge(p[0].position,p[1].position,tessViewport.xy);
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
#if defined(OPENSHIM_HEIGHT_TEST)
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
