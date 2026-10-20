// Original OpenShim shader for explicitly selected shell-menu images.
Texture2D menuImage : register(t0);
SamplerState menuSampler : register(s0);
float4 menuTheme;
float4 menuLevels; // saturation, white level, reserved, reserved

float4 MenuThemeFragment(float4 color : COLOR0, float2 uv : TEXCOORD0) : SV_TARGET
{
    float4 pixel = menuImage.Sample(menuSampler,uv);
    if (menuTheme.w > 0.5)
    {
        float green = max(0.0,pixel.g-max(pixel.r,pixel.b));
        float mask = smoothstep(0.005,0.03,green);
        float peak = max(pixel.r,max(pixel.g,pixel.b));
        float3 themed = peak*lerp(float3(1,1,1),menuTheme.rgb,menuLevels.x);
        pixel.rgb = saturate(lerp(pixel.rgb,themed,mask)*menuLevels.y);
    }
    return pixel*color;
}
