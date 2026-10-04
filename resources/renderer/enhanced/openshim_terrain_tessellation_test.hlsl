// Zero-displacement submission experiment. Consumes the ordinary terrain VS
// outputs; COLOR0 is already swizzled, and UV/height decoding stays in that VS.
#ifndef OPENSHIM_TESS_FACTOR
#define OPENSHIM_TESS_FACTOR 1
#endif
#ifndef OPENSHIM_RELIEF_AMPLITUDE
#define OPENSHIM_RELIEF_AMPLITUDE 0
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
    f.edge[0] = f.edge[1] = f.edge[2] = OPENSHIM_TESS_FACTOR;
    f.inside = OPENSHIM_TESS_FACTOR;
    return f;
}

[domain("tri")]
[partitioning("integer")]
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
    float3 relief = TerrainMicroRelief(TerrainReliefObjectXZ(o.viewPosition, reliefInverseWorldView));
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
