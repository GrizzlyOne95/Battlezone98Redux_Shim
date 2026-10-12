// Original OpenShim SDR cinematic preview. These are raster post effects,
// independent of the optional hardware DXR pass.
Texture2D<float> Depth : register(t0);
Texture2D<float4> Scene : register(t1);
Texture2D<float4> OriginalScene : register(t2);
Texture2D<float4> OriginalFinal : register(t3);
Texture2D<float4> BloomA : register(t4);
Texture2D<float4> BloomB : register(t5);
RWTexture2D<float4> WriteBloomA : register(u0);
RWTexture2D<float4> WriteBloomB : register(u1);
RWTexture2D<float4> SceneOutput : register(u2);
RWTexture2D<float4> FinalOutput : register(u3);
cbuffer Params : register(b0) {
    row_major float4x4 ClipToView;
    uint Width; uint Height; uint BloomWidth; uint BloomHeight;
    float ClearDepth; float Exposure; float Contrast; float Saturation;
    float BloomThreshold; float BloomStrength; float HazeDensity; float HazeStart;
    float3 HazeColor; float Padding;
};
float3 Linear(float3 value) {
    return float3(value.r<=.04045?value.r/12.92:pow(max((value.r+.055)/1.055,0),2.4),
                  value.g<=.04045?value.g/12.92:pow(max((value.g+.055)/1.055,0),2.4),
                  value.b<=.04045?value.b/12.92:pow(max((value.b+.055)/1.055,0),2.4));
}
float3 Encoded(float3 value) {
    value=saturate(value);
    return float3(value.r<=.0031308?value.r*12.92:1.055*pow(max(value.r,0),1/2.4)-.055,
                  value.g<=.0031308?value.g*12.92:1.055*pow(max(value.g,0),1/2.4)-.055,
                  value.b<=.0031308?value.b*12.92:1.055*pow(max(value.b,0),1/2.4)-.055);
}
float Luminance(float3 c) { return dot(c,float3(.2126,.7152,.0722)); }
[numthreads(8,8,1)]
void Extract(uint3 id:SV_DispatchThreadID) {
    if(id.x>=BloomWidth||id.y>=BloomHeight) return;
    float3 sum=0;
    [unroll] for(uint y=0;y<2;++y) [unroll] for(uint x=0;x<2;++x) {
        uint2 pixel=min(id.xy*2+uint2(x,y),uint2(Width-1,Height-1));
        float3 c=Linear(Scene.Load(int3(pixel,0)).rgb);
        float light=Luminance(c);
        sum+=c*max(light-BloomThreshold,0)/max(light,.0001);
    }
    WriteBloomA[id.xy]=float4(sum*.25,0);
}
static const float Weights[5]={.227027027,.194594595,.121621622,.054054054,.016216216};
int2 Bounded(int2 pixel) { return clamp(pixel,int2(0,0),int2(BloomWidth-1,BloomHeight-1)); }
[numthreads(8,8,1)]
void BlurHorizontal(uint3 id:SV_DispatchThreadID) {
    if(id.x>=BloomWidth||id.y>=BloomHeight) return;
    float3 c=BloomA.Load(int3(id.xy,0)).rgb*Weights[0];
    [unroll] for(int i=1;i<5;++i) {
        c+=(BloomA.Load(int3(Bounded(int2(id.xy)+int2(i,0)),0)).rgb+
            BloomA.Load(int3(Bounded(int2(id.xy)-int2(i,0)),0)).rgb)*Weights[i];
    }
    WriteBloomB[id.xy]=float4(c,0);
}
[numthreads(8,8,1)]
void BlurVertical(uint3 id:SV_DispatchThreadID) {
    if(id.x>=BloomWidth||id.y>=BloomHeight) return;
    float3 c=BloomB.Load(int3(id.xy,0)).rgb*Weights[0];
    [unroll] for(int i=1;i<5;++i) {
        c+=(BloomB.Load(int3(Bounded(int2(id.xy)+int2(0,i)),0)).rgb+
            BloomB.Load(int3(Bounded(int2(id.xy)-int2(0,i)),0)).rgb)*Weights[i];
    }
    WriteBloomA[id.xy]=float4(c,0);
}
float3 FilteredBloom(uint2 pixel) {
    float2 p=(float2(pixel)+.5)*.5-.5;
    int2 lo=int2(floor(p)); float2 f=frac(p);
    return lerp(lerp(BloomA.Load(int3(Bounded(lo),0)).rgb,BloomA.Load(int3(Bounded(lo+int2(1,0)),0)).rgb,f.x),
                lerp(BloomA.Load(int3(Bounded(lo+int2(0,1)),0)).rgb,BloomA.Load(int3(Bounded(lo+1),0)).rgb,f.x),f.y);
}
[numthreads(8,8,1)]
void Composite(uint3 id:SV_DispatchThreadID) {
    if(id.x>=Width||id.y>=Height) return;
    float4 scene=Scene.Load(int3(id.xy,0));
    float3 c=Linear(scene.rgb)+FilteredBloom(id.xy)*BloomStrength;
    float z=Depth.Load(int3(id.xy,0));
    float2 uv=(float2(id.xy)+.5)/float2(Width,Height);
    float4 v=mul(ClipToView,float4(uv.x*2-1,1-uv.y*2,z,1));
    if(isfinite(z)&&z>=0&&z<=1&&z!=ClearDepth&&all(isfinite(v))&&abs(v.w)>1e-8) {
        float distance=length(v.xyz/v.w);
        float haze=1-exp(-max(distance-HazeStart,0)*HazeDensity);
        c=lerp(c,Linear(HazeColor),haze);
    }
    // A power contrast curve preserves dark cockpit detail; a linear pivot
    // would clip SDR shadows before the final encoding.
    c=.18*pow(max(c*Exposure/.18,0),Contrast);
    c=lerp(Luminance(c).xxx,c,Saturation);
    float3 output=Encoded(c);
    SceneOutput[id.xy]=float4(output,scene.a);
    float4 original=OriginalFinal.Load(int3(id.xy,0));
    float3 difference=abs(original.rgb-OriginalScene.Load(int3(id.xy,0)).rgb);
    float delta=max(difference.r,max(difference.g,difference.b));
    float sceneWeight=1-smoothstep(4.0/255,24.0/255,delta);
    // Apply an effect delta to the original raster result, retaining its FXAA
    // detail instead of replacing individual pixels with pre-HUD scene color.
    // Low-opacity/identical-color UI cannot be qualified from this difference.
    float3 enhanced=saturate(original.rgb+output-OriginalScene.Load(int3(id.xy,0)).rgb);
    FinalOutput[id.xy]=float4(lerp(original.rgb,enhanced,sceneWeight),original.a);
}
