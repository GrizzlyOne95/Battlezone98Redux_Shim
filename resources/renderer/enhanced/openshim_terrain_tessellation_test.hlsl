// Zero-displacement submission experiment. Consumes the ordinary terrain VS
// outputs; COLOR0 is already swizzled, and UV/height decoding stays in that VS.
#ifndef OPENSHIM_TESS_FACTOR
#define OPENSHIM_TESS_FACTOR 1
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
    return o;
}
