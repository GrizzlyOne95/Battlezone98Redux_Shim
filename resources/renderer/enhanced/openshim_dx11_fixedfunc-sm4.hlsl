// DX11 fixed-function compatibility path for legacy Battlezone mods.
// SM4-only: DX9 keeps its fixed pipeline and never loads this file.
//
// Covers the overwhelmingly common legacy path from
// Docs/DX11_LEGACY_MATERIAL_COMPATIBILITY.md Level 2:
//   world/view/projection transform, vertex diffuse colour,
//   material diffuse/ambient contribution, texture unit 0,
//   texture matrix / UV animation, fog, alpha.
//
// Texture-stage combine operations that the fixed pipeline executed are
// represented here for the bounded support set (0 units; 1 unit with
// modulate/replace/add/alpha_blend). Multi-texture and exotic combines are
// intentionally NOT guessed: the engine policy marks them unsupported and
// logs once so corpus telemetry can expand coverage (Level 4).
//
// Compat family adapters (OSE_Compat_*) share these entry points with a
// COMPAT_FAMILY define recording which legacy family selected them. The
// define is informational today; per-family tuning lands here without
// touching the resolver.

// ---------------------------------------------------------------------------
// Vertex input variants
// ---------------------------------------------------------------------------
//
// D3D11 matches every element of a vertex shader's INPUT signature against
// the mesh's vertex declaration and throws "Unable to set D3D11 vertex
// declaration" on the first miss -- per draw, every frame, which the game
// treats as a render failure and eventually quits on. Fixed function never
// had that problem: a mesh without a diffuse element simply drew white.
// Blender/OgreXML exports routinely carry no DIFFUSE element (ISDF
// Chronicles' prop.mesh is POSITION/NORMAL/TANGENT/TEXCOORD0 only), so the
// vertex entry points below compile in input-reduced variants:
//
//   COMPAT_NO_VERTEX_COLOUR  no COLOR0 input; vertex colour reads as white
//   COMPAT_NO_TEXCOORD       no TEXCOORD0 input; UV reads as (0,0)
//
// Output signatures never change, so any variant pairs with the fragment
// program its full-input sibling pairs with. The runtime picks the variant
// from the renderable's declaration (FitVertexProgramToInputs).

// ---------------------------------------------------------------------------
// Textured path (1 texture unit)
// ---------------------------------------------------------------------------

void fixedfunc_vertex(
    uniform float4x4 wvpMat,
    uniform float4x4 texMatrix,
    uniform float4 diffuseColor,

    in float4 iPosition : POSITION,
#ifndef COMPAT_NO_VERTEX_COLOUR
    in float4 iColor : COLOR0,
#endif
#ifndef COMPAT_NO_TEXCOORD
    in float2 iTexCoord : TEXCOORD0,
#endif

    out float4 vColor : COLOR0,
    out float2 vTexCoord : TEXCOORD0,
    out float vDepth : TEXCOORD1,

    out float4 oPosition : SV_POSITION
)
{
    oPosition = mul(wvpMat, iPosition);
    // Vertex diffuse * material diffuse. Fixed-function modulate semantics:
    // both contribute, alpha flows through for alpha-blended particles.
    //
    // iColor.bgra, not iColor. Every consumer of this entry point is NATIVE
    // BZR geometry, whose vertex colours are ARGB DWORDs that D3D11 reads back
    // in RGBA order. Every stock SM4 family that reads vertex colour corrects
    // for that -- ui, uitexmat, untextured, sky, effect, simple_one_tex and
    // terrain all ship `iColor.bgra`. These programs stand in for those
    // families, so they must agree with them; without the correction a blue
    // legacy material renders orange.
    //
    // The opposite rule holds for Ogre-generated vertices (TextArea,
    // ParticleFX), which have already passed through the render system's
    // convertColourValue and arrive in RGBA order -- correcting those swaps
    // them a second time. This file does not have to tell the two apart:
    // IsExcludedFromSynthesis() in dx11_legacy_material_compat.cpp rejects
    // overlay, font, cursor, sprite, compositor and rtt materials before
    // anything can reach these programs.
#ifdef COMPAT_NO_VERTEX_COLOUR
    vColor = diffuseColor;
#else
    vColor = iColor.bgra * diffuseColor;
#endif
    // Texture matrix carries scroll_anim / rotate / scale from the source
    // pass without touching mod files on disk.
#ifdef COMPAT_NO_TEXCOORD
    float2 iTexCoord = float2(0.0, 0.0);
#endif
    vTexCoord = mul(texMatrix, float4(iTexCoord, 0.0, 1.0)).xy;
    vDepth = oPosition.z;
}

void fixedfunc_fragment(
    uniform Texture2D diffuseMap : register(t0),
    uniform SamplerState diffuseSam : register(s0),

    uniform float4 sceneAmbient,
    uniform float4 fogColour,
    uniform float4 fogParams,

#ifdef COMPAT_OP_REPLACE
    // replace: texture wins, vertex colour ignored (kept as a distinct
    // variant so future corpus work can bind it per-pass).
#endif

    in float4 vColor : COLOR0,
    in float2 vTexCoord : TEXCOORD0,
    in float vDepth : TEXCOORD1,

    out float4 oColor : SV_TARGET
)
{
    float4 tex = diffuseMap.Sample(diffuseSam, vTexCoord);
#if defined(COMPAT_OP_REPLACE)
    float3 albedo = tex.xyz;
    float alpha = tex.a;
#elif defined(COMPAT_OP_ADD)
    float3 albedo = vColor.xyz + tex.xyz;
    float alpha = vColor.a * tex.a;
#else
    // modulate (default) and alpha_blend share this path: albedo is the
    // product, alpha is the product. Scene blending state comes from the
    // cloned source pass, not from this shader.
    float3 albedo = vColor.xyz * tex.xyz;
    float alpha = vColor.a * tex.a;
#endif
    // Ambient floor so unlit legacy content never goes pitch black the way
    // a missing light rig would. Matches the Enhanced payload's approach of
    // a small ambient contribution on top of the diffuse term.
    albedo += sceneAmbient.xyz * 0.25;
    oColor.xyz = albedo;

    float fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
    oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);

    oColor.a = alpha;
}

// ---------------------------------------------------------------------------
// Untextured path (0 texture units)
// ---------------------------------------------------------------------------

void fixedfunc_untextured_vertex(
    uniform float4x4 wvpMat,
    uniform float4 diffuseColor,

    in float4 iPosition : POSITION,
#ifndef COMPAT_NO_VERTEX_COLOUR
    in float4 iColor : COLOR0,
#endif

    out float4 vColor : COLOR0,
    out float vDepth : TEXCOORD1,

    out float4 oPosition : SV_POSITION
)
{
    oPosition = mul(wvpMat, iPosition);
#ifdef COMPAT_NO_VERTEX_COLOUR
    vColor = diffuseColor;
#else
    // Native BGRA correction, for the reason spelled out in fixedfunc_vertex.
    vColor = iColor.bgra * diffuseColor;
#endif
    vDepth = oPosition.z;
}

void fixedfunc_untextured_fragment(
    uniform float4 sceneAmbient,
    uniform float4 fogColour,
    uniform float4 fogParams,

    in float4 vColor : COLOR0,
    in float vDepth : TEXCOORD1,

    out float4 oColor : SV_TARGET
)
{
    float3 albedo = vColor.xyz + sceneAmbient.xyz * 0.25;
    oColor.xyz = albedo;

    float fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
    oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);

    oColor.a = vColor.a;
}
