// Original OpenShim experimental visible-depth DXR AO.
Texture2D<float> Depth : register(t0);
Texture2D<float4> SceneColor : register(t1);
Texture2D<float4> FinalColor : register(t2);
RaytracingAccelerationStructure VisibleScene : register(t3);
RWStructuredBuffer<float3> Vertices : register(u0);
RWTexture2D<float4> SceneOutput : register(u1);
RWTexture2D<float4> FinalOutput : register(u2);
cbuffer Params : register(b0) {
    row_major float4x4 ClipToView;
    uint Width; uint Height; uint Columns; uint Rows;
    float ClearDepth; float Radius; float Bias; float Strength;
};
bool Position(uint2 pixel, out float3 position) {
    float z=Depth.Load(int3(pixel,0));
    float2 uv=(float2(pixel)+.5)/float2(Width,Height);
    float4 v=mul(ClipToView,float4(uv.x*2-1,1-uv.y*2,z,1));
    position=v.xyz/v.w;
    return isfinite(z) && z>=0 && z<=1 && z!=ClearDepth && all(isfinite(position));
}
void Triangle(uint offset,float3 a,float3 b,float3 c,bool valid) {
    // Reject depth silhouette bridges. Invalid primitives are degenerate.
    float scale=max(1.0,max(length(a),max(length(b),length(c))));
    valid=valid && max(length(a-b),max(length(b-c),length(c-a)))<scale*.035;
    Vertices[offset]=valid?a:0;
    Vertices[offset+1]=valid?b:0;
    Vertices[offset+2]=valid?c:0;
}
[numthreads(8,8,1)]
void Mesh(uint3 id:SV_DispatchThreadID) {
    if(id.x>=Columns||id.y>=Rows) return;
    uint2 p=id.xy*2;
    float3 a,b,c,d;
    bool va=Position(p,a),vb=Position(p+uint2(2,0),b);
    bool vc=Position(p+uint2(0,2),c),vd=Position(p+uint2(2,2),d);
    uint offset=(id.y*Columns+id.x)*6;
    Triangle(offset,a,b,c,va&&vb&&vc);
    Triangle(offset+3,c,b,d,vc&&vb&&vd);
}
uint Hash(uint x) { x^=x>>16; x*=0x7feb352d; x^=x>>15; x*=0x846ca68b; return x^(x>>16); }
[numthreads(8,8,1)]
void Rays(uint3 id:SV_DispatchThreadID) {
    if(id.x>=Width||id.y>=Height) return;
    float4 scene=SceneColor.Load(int3(id.xy,0)),final=FinalColor.Load(int3(id.xy,0));
    float factor=1;
    float3 p;
    if(Position(id.xy,p) && id.x>0 && id.y>0 && id.x+1<Width && id.y+1<Height) {
        float3 l,r,u,d;
        bool vl=Position(id.xy-uint2(1,0),l),vr=Position(id.xy+uint2(1,0),r);
        bool vu=Position(id.xy-uint2(0,1),u),vd=Position(id.xy+uint2(0,1),d);
        if((vl||vr)&&(vu||vd)) {
            float3 dx=vr && (!vl||abs(r.z-p.z)<abs(l.z-p.z)) ? r-p : p-l;
            float3 dy=vd && (!vu||abs(d.z-p.z)<abs(u.z-p.z)) ? d-p : p-u;
            float3 n=cross(dx,dy);
            if(dot(n,n)>1e-12) {
                n=normalize(n); if(dot(n,-p)<0) n=-n;
                float3 tangent=normalize(cross(abs(n.y)<.9?float3(0,1,0):float3(1,0,0),n));
                float3 bitangent=cross(n,tangent);
                float rotation=(Hash(id.x+id.y*Width)&65535)*(6.283185307/65536);
                float occlusion=0;
                [unroll] for(uint sample=0;sample<8;++sample) {
                    float t=(sample+.5)/8;
                    float angle=rotation+sample*2.39996323;
                    float3 direction=normalize(tangent*cos(angle)*sqrt(t)+bitangent*sin(angle)*sqrt(t)+n*sqrt(1-t));
                    RayDesc ray; ray.Origin=p+n*Bias; ray.Direction=direction; ray.TMin=Bias; ray.TMax=Radius;
                    RayQuery<RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH|RAY_FLAG_FORCE_OPAQUE> query;
                    query.TraceRayInline(VisibleScene,RAY_FLAG_NONE,255,ray);
                    while(query.Proceed()) {}
                    if(query.CommittedStatus()==COMMITTED_TRIANGLE_HIT) occlusion+=1-saturate(query.CommittedRayT()/Radius);
                }
                factor=1-Strength*occlusion/8;
            }
        }
    }
    SceneOutput[id.xy]=float4(scene.rgb*factor,scene.a);
    // Conservative preview-only HUD difference mask. FXAA and identical HUD
    // colors make this approximate; no alpha/compositing qualification claim.
    float3 difference=abs(final.rgb-scene.rgb);
    bool same=max(difference.r,max(difference.g,difference.b))<2.0/255;
    FinalOutput[id.xy]=float4(same?final.rgb*factor:final.rgb,final.a);
}
