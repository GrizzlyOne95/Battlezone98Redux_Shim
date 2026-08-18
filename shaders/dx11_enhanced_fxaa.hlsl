// BZR Open Shim - DX11 Enhanced FXAA presentation shader
//
// The algorithm itself is NVIDIA FXAA 3.11 from the removed BZR beta files.
// This wrapper only modernizes the integration for Shader Model 5 and keeps the
// beta's preset/tuning so we can validate the historical path before adding any
// quality selector.

#define FXAA_PC 1
#define FXAA_HLSL_5 1
#define FXAA_GREEN_AS_LUMA 1
#define FXAA_QUALITY__PRESET 39

#include "Fxaa3_11.h"

Texture2D FxaaInput : register(t0);
SamplerState FxaaSampler : register(s0);

cbuffer FxaaFrameConstants : register(b0)
{
    float2 FxaaRcpFrame;
    float2 FxaaPadding;
};

struct FxaaVsOut
{
    float4 position : SV_Position;
    noperspective float2 texCoord : TEXCOORD0;
};

FxaaVsOut VSMain(uint vertexId : SV_VertexID)
{
    FxaaVsOut output;

    // Full-screen triangle with no input layout or vertex buffer. The 0..2 UV
    // triangle interpolates to 0..1 over the viewport without a half-texel hack.
    float2 uv = float2((vertexId << 1) & 2, vertexId & 2);
    output.position = float4(uv * float2(2.0, -2.0) + float2(-1.0, 1.0), 0.0, 1.0);
    output.texCoord = uv;
    return output;
}

float4 PSMain(FxaaVsOut input) : SV_Target
{
    FxaaTex tex;
    tex.smpl = FxaaSampler;
    tex.tex = FxaaInput;

    // FXAA Quality ignores the console-only position/constants. Keep the beta
    // PC tuning exactly as shipped: subpixel 0.75, edge threshold 0.063, dark
    // trim 0.0625, preset 39. GREEN_AS_LUMA requires encoded/non-linear LDR
    // input, which the native presentation hook verifies before this executes.
    return FxaaPixelShader(
        input.texCoord,
        float4(0.0, 0.0, 0.0, 0.0),
        tex,
        tex,
        tex,
        FxaaRcpFrame,
        float4(0.0, 0.0, 0.0, 0.0),
        float4(0.0, 0.0, 0.0, 0.0),
        float4(0.0, 0.0, 0.0, 0.0),
        0.75,
        0.063,
        0.0625,
        8.0,
        0.125,
        0.05,
        float4(1.0, -1.0, 0.25, -0.25));
}
