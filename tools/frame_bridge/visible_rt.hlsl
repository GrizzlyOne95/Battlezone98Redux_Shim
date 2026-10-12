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
    row_major float4x4 ViewToWorld;
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
    valid=valid && max(length(a-b),max(length(b-c),length(c-a)))<min(scale*.035,Radius*.125);
    Vertices[offset]=valid?a:0;
    Vertices[offset+1]=valid?b:0;
    Vertices[offset+2]=valid?c:0;
}
bool MeshSurface(uint2 pixel,float3 visible,out float3 surface,out float3 normal) {
    // Shade the exact plane represented in the two-pixel BLAS, not the
    // higher-resolution depth point which can lie behind that plane. D24
    // quantization and alpha-tested particles otherwise produce self hits.
    uint2 cell=min(pixel/2,uint2(Columns-1,Rows-1))*2;
    float2 local=float2(pixel-cell)*.5;
    float3 a,b,c;
    bool valid;
    if(local.x+local.y<=1) {
        valid=Position(cell,a); valid=Position(cell+uint2(2,0),b)&&valid;
        valid=Position(cell+uint2(0,2),c)&&valid;
    } else {
        valid=Position(cell+uint2(0,2),a); valid=Position(cell+uint2(2,0),b)&&valid;
        valid=Position(cell+uint2(2,2),c)&&valid;
    }
    float scale=max(1.0,max(length(a),max(length(b),length(c))));
    valid=valid&&max(length(a-b),max(length(b-c),length(c-a)))<min(scale*.035,Radius*.125);
    normal=cross(b-a,c-a);
    float lengthSquared=dot(normal,normal);
    if(!valid||lengthSquared<1e-12) { surface=0; normal=0; return false; }
    normal*=rsqrt(lengthSquared); if(dot(normal,-visible)<0) normal=-normal;
    float denominator=dot(normal,visible);
    float t=abs(denominator)>1e-8?dot(normal,a)/denominator:0;
    surface=visible*t;
    return t>0&&all(isfinite(surface));
}
bool StableNeighborhood(uint2 pixel,float3 center) {
    // Without opacity/coverage data, prefer no AO near uncertain depth edges.
    // This deliberately sacrifices narrow contact shadows rather than shading
    // a background depth through a transparent/alpha-tested plume silhouette.
    static const int2 offsets[8]={int2(-4,0),int2(4,0),int2(0,-4),int2(0,4),
        int2(-4,-4),int2(4,-4),int2(-4,4),int2(4,4)};
    [unroll] for(uint i=0;i<8;++i) {
        int2 other=int2(pixel)+offsets[i];
        if(any(other<0)||any(other>=int2(Width,Height))) return false;
        float3 p;
        if(!Position(uint2(other),p)||abs(p.z-center.z)>min(max(.08,abs(center.z)*.035),Radius*.125)) return false;
    }
    return true;
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
        float3 surface,n;
        if(StableNeighborhood(id.xy,p)&&MeshSurface(id.xy,p,surface,n)) {
            // Eight depth quantization steps in view units cover adjacent
            // coarse triangles too. A fixed centimeter offset is too small
            // for distant D24 / float-depth geometry.
            float offset=max(Bias,8*surface.z*surface.z*abs(ClipToView[3][2])/16777216);
            if(offset<Radius*.25) {
                float3 tangent=normalize(cross(abs(n.y)<.9?float3(0,1,0):float3(1,0,0),n));
                float3 bitangent=cross(n,tangent);
                float rotation=(Hash(id.x+id.y*Width)&65535)*(6.283185307/65536);
                float occlusion=0;
                [unroll] for(uint sample=0;sample<8;++sample) {
                    float t=(sample+.5)/8;
                    float angle=rotation+sample*2.39996323;
                    float3 direction=normalize(tangent*cos(angle)*sqrt(t)+bitangent*sin(angle)*sqrt(t)+n*sqrt(1-t));
                    RayDesc ray; ray.Origin=mul(ViewToWorld,float4(surface+n*offset,1)).xyz;
                    ray.Direction=mul(ViewToWorld,float4(direction,0)).xyz; ray.TMin=offset; ray.TMax=Radius;
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
