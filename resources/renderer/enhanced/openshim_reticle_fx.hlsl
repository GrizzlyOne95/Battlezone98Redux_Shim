// Original OpenShim shader for the stock sprite reticle: team recolor, hit
// flash and an outward ripple of the weapon's own reticle art. The quad is
// drawn fxShape.x times the atlas cell so ripples can leave the cell; every
// sample stays inside fxCell, so neighboring atlas cells never bleed in.
Texture2D reticleArt : register(t0);
SamplerState reticleSampler : register(s0);
float4 fxCell;      // atlas cell u0, v0, u1, v1
float4 fxShape;     // quad expansion, reticle pop scale, flash, reserved
float4 fxTint;      // relation rgb, recolor amount
float4 fxRingScale; // up to four ripple scales
float4 fxRingAlpha; // ripple opacities; 0 leaves a slot unused
float4 fxRingColor; // ripple rgb multiplier

float4 Cell(float2 c)
{
    float inside = step(abs(c.x), 0.5) * step(abs(c.y), 0.5);
    float4 art = reticleArt.SampleLevel(reticleSampler, lerp(fxCell.xy, fxCell.zw, saturate(c + 0.5)), 0);
    // Recolor by brightness so colored stock art reads as the tint.
    float peak = max(art.r, max(art.g, art.b));
    art.rgb = lerp(art.rgb, peak * fxTint.rgb, fxTint.w);
    return art * inside;
}

float4 Over(float4 top, float4 bottom)
{
    float a = top.a + bottom.a * (1 - top.a);
    float3 rgb = (top.rgb * top.a + bottom.rgb * bottom.a * (1 - top.a)) / max(a, 1e-4);
    return float4(rgb, a);
}

float4 ReticleFxFragment(float4 color : COLOR0, float2 uv : TEXCOORD0) : SV_TARGET
{
    float2 span = fxCell.zw - fxCell.xy;
    span = sign(span) * max(abs(span), 1e-6);
    float2 c = ((uv - fxCell.xy) / span - 0.5) * fxShape.x;
    float4 result = Cell(c / fxShape.y);
    result.rgb = lerp(result.rgb, float3(1, 1, 1), fxShape.z);
    [unroll] for (int i = 0; i < 4; ++i)
    {
        float4 ring = Cell(c / fxRingScale[i]);
        ring.rgb *= fxRingColor.rgb;
        ring.a *= fxRingAlpha[i];
        result = Over(result, ring);
    }
    return result * color;
}
