// Execute the shipped candidate TerrainDomain, then capture its actual output
// through geometry-stage stream output. This is a geometry test, not a
// compute-only height sample or evidence of native game resource binding.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl/client.h>
#include <array>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "terrain_height_domain_binding.h"
using Microsoft::WRL::ComPtr;
static bool normalizedHeight = false;
static void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
static void ok(HRESULT result) { check(SUCCEEDED(result), "D3D11 height-domain operation failed"); }
struct Vertex { float position[4], view[3], uv[2], normal[3], tangent[3]; };
struct Output { float position[4], normal[3], tangent[3], view[3], depth, shadow1[4], shadow2[4], shadow3[4], uv[2]; };
static_assert(sizeof(Output)==28*sizeof(float));
static ComPtr<ID3DBlob> compile(const std::string& source, const char* entry, const char* target)
{
    const D3D_SHADER_MACRO macros[]={{"OPENSHIM_RELIEF_TEST","1"},{"OPENSHIM_HEIGHT_TEST","1"},
        {"OPENSHIM_RELIEF_AMPLITUDE",normalizedHeight ? ".625" : "1"},{"OPENSHIM_TESS_FACTOR","4"},
        {"NORMALMAP_ENABLED","1"},{"VERTEX_TANGENTS","1"},{"SHADOWRECEIVER","1"},{"PSSM_ENABLED","1"},{nullptr,nullptr}};
    ComPtr<ID3DBlob> code,errors;
    HRESULT result=D3DCompile(source.data(),source.size(),nullptr,macros,nullptr,entry,target,D3DCOMPILE_OPTIMIZATION_LEVEL3,0,&code,&errors);
    if (FAILED(result)&&errors) std::cerr<<static_cast<const char*>(errors->GetBufferPointer());
    ok(result); return code;
}
static std::array<float,16> identity() { return {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; }
static ComPtr<ID3D11Buffer> constants(ID3D11Device* device, ID3DBlob* code, float eyeX, float eyeZ)
{
    ComPtr<ID3D11ShaderReflection> reflection;
    ok(D3DReflect(code->GetBufferPointer(),code->GetBufferSize(),IID_ID3D11ShaderReflection,&reflection));
    auto* block=reflection->GetConstantBufferByName("$Globals");
    D3D11_SHADER_BUFFER_DESC desc{}; ok(block->GetDesc(&desc));
    std::vector<unsigned char> bytes((desc.Size+15)&~15u);
    for (const char* name:{"reliefView","reliefInverseView","reliefInverseWorldView","reliefProjection","reliefShadow1","reliefShadow2","reliefShadow3"})
    {
        D3D11_SHADER_VARIABLE_DESC variable{}; ok(block->GetVariableByName(name)->GetDesc(&variable));
        check(variable.Size==64&&variable.StartOffset+64<=bytes.size(),"height matrix reflection contract changed");
        auto matrix=identity(); // column-major HLSL memory
        if (std::strcmp(name,"reliefView")==0) { matrix[12]=-eyeX; matrix[14]=-eyeZ; }
        if (std::strcmp(name,"reliefInverseView")==0||std::strcmp(name,"reliefInverseWorldView")==0) { matrix[12]=eyeX; matrix[14]=eyeZ; }
        if (std::strcmp(name,"reliefProjection")==0) matrix[6]=.25f;
        if (std::strcmp(name,"reliefShadow1")==0) matrix[5]=2;
        if (std::strcmp(name,"reliefShadow2")==0) matrix[5]=3;
        if (std::strcmp(name,"reliefShadow3")==0) matrix[5]=4;
        std::memcpy(bytes.data()+variable.StartOffset,matrix.data(),64);
    }
    D3D11_BUFFER_DESC buffer{}; buffer.ByteWidth=static_cast<UINT>(bytes.size()); buffer.Usage=D3D11_USAGE_IMMUTABLE; buffer.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
    D3D11_SUBRESOURCE_DATA data{bytes.data(),0,0}; ComPtr<ID3D11Buffer> result;
    ok(device->CreateBuffer(&buffer,&data,&result)); return result;
}
static ComPtr<ID3D11ShaderResourceView> height_texture(ID3D11Device* device, int field)
{
    std::vector<float> pixels(64*64);
    for (unsigned y=0;y<64;++y) for (unsigned x=0;x<64;++x)
    {
        float h=.3f*(static_cast<float>(x)+.5f)/64+.2f*(static_cast<float>(y)+.5f)/64-.25f;
        if (field==0) h=0;
        if (field==2) h=std::numeric_limits<float>::quiet_NaN();
        if (field==3) h=1.5f;
        // Guarded tile art, including opposite-sign neighbors and zero slopes.
        if (field==4)
        {
            const int edge=static_cast<int>((std::min)(x,63-x));
            const int edgeY=static_cast<int>((std::min)(y,63-y));
            h=(edge<=5||edgeY<=5||x==31||x==32)?0.f:(x<32?.2f:-.2f);
        }
        pixels[y*64+x]=h;
    }
    D3D11_TEXTURE2D_DESC desc{}; desc.Width=desc.Height=64; desc.MipLevels=desc.ArraySize=1;
    desc.Format=DXGI_FORMAT_R32_FLOAT; desc.SampleDesc.Count=1; desc.Usage=D3D11_USAGE_IMMUTABLE; desc.BindFlags=D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA data{pixels.data(),64*sizeof(float),0}; ComPtr<ID3D11Texture2D> texture;
    ok(device->CreateTexture2D(&desc,&data,&texture)); ComPtr<ID3D11ShaderResourceView> view;
    ok(device->CreateShaderResourceView(texture.Get(),nullptr,&view)); return view;
}
static int run(bool normalized)
{
    normalizedHeight = normalized;
    try
    {
        std::ifstream file(TERRAIN_TESS_SHADER_PATH,std::ios::binary);
        std::string source((std::istreambuf_iterator<char>(file)),{});
        if (normalized) source = "#define OPENSHIM_HEIGHT_NORMALIZED 1\n" + source;
        check(!source.empty(),"terrain shader missing");
        source+=R"(
struct TestInput { float4 position:POSITION; float3 view:TEXCOORD0; float2 uv:TEXCOORD1; float3 normal:NORMAL; float3 tangent:TANGENT; };
TerrainTessVertex TestVertex(TestInput i) {
    TerrainTessVertex o; o.position=i.position; o.viewPosition=i.view; o.uv=i.uv;
    o.color=1; o.normal=i.normal; o.tangent=i.tangent; o.depth=i.position.z;
    o.shadow1=o.shadow2=o.shadow3=float4(i.view,1); return o;
}
[maxvertexcount(3)]
void Capture(triangle TerrainTessVertex input[3],inout TriangleStream<TerrainTessVertex> output) {
    for(uint i=0;i<3;++i) output.Append(input[i]);
}
)";
        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context; D3D_FEATURE_LEVEL level;
        ok(D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_WARP,nullptr,0,nullptr,0,D3D11_SDK_VERSION,&device,&level,&context));
        check(level>=D3D_FEATURE_LEVEL_11_0,"domain test requires feature level 11");
        auto vs=compile(source,"TestVertex","vs_5_0"),hs=compile(source,"TerrainHull","hs_5_0"),ds=compile(source,"TerrainDomain","ds_5_0"),gs=compile(source,"Capture","gs_5_0");
        ComPtr<ID3D11VertexShader> vertex; ComPtr<ID3D11HullShader> hull; ComPtr<ID3D11DomainShader> domain; ComPtr<ID3D11GeometryShader> capture;
        ok(device->CreateVertexShader(vs->GetBufferPointer(),vs->GetBufferSize(),nullptr,&vertex));
        ok(device->CreateHullShader(hs->GetBufferPointer(),hs->GetBufferSize(),nullptr,&hull));
        ok(device->CreateDomainShader(ds->GetBufferPointer(),ds->GetBufferSize(),nullptr,&domain));
        const D3D11_SO_DECLARATION_ENTRY entries[]={
            {0,"SV_POSITION",0,0,4,0},{0,"TEXCOORD",2,0,3,0},{0,"TEXCOORD",3,0,3,0},
            {0,"TEXCOORD",4,0,3,0},{0,"TEXCOORD",5,0,1,0},{0,"TEXCOORD",6,0,4,0},
            {0,"TEXCOORD",7,0,4,0},{0,"TEXCOORD",8,0,4,0},{0,"TEXCOORD",0,0,2,0}};
        const UINT outStride=sizeof(Output);
        ok(device->CreateGeometryShaderWithStreamOutput(gs->GetBufferPointer(),gs->GetBufferSize(),entries,9,&outStride,1,D3D11_SO_NO_RASTERIZED_STREAM,nullptr,&capture));
        const D3D11_INPUT_ELEMENT_DESC elements[]={
            {"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
            {"TEXCOORD",0,DXGI_FORMAT_R32G32B32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0},
            {"TEXCOORD",1,DXGI_FORMAT_R32G32_FLOAT,0,28,D3D11_INPUT_PER_VERTEX_DATA,0},
            {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,36,D3D11_INPUT_PER_VERTEX_DATA,0},
            {"TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,0,48,D3D11_INPUT_PER_VERTEX_DATA,0}};
        ComPtr<ID3D11InputLayout> layout;
        ok(device->CreateInputLayout(elements,5,vs->GetBufferPointer(),vs->GetBufferSize(),&layout));
        context->VSSetShader(vertex.Get(),nullptr,0); context->HSSetShader(hull.Get(),nullptr,0);
        context->DSSetShader(domain.Get(),nullptr,0); context->GSSetShader(capture.Get(),nullptr,0);
        context->IASetInputLayout(layout.Get()); context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
        D3D11_BUFFER_DESC outDesc{}; outDesc.ByteWidth=sizeof(Output)*1024; outDesc.Usage=D3D11_USAGE_DEFAULT; outDesc.BindFlags=D3D11_BIND_STREAM_OUTPUT;
        ComPtr<ID3D11Buffer> output,staging; ok(device->CreateBuffer(&outDesc,nullptr,&output));
        outDesc.Usage=D3D11_USAGE_STAGING; outDesc.BindFlags=0; outDesc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
        ok(device->CreateBuffer(&outDesc,nullptr,&staging));
        auto sentinel=height_texture(device.Get(),0); ID3D11ShaderResourceView* psSentinel=sentinel.Get();
        context->PSSetShaderResources(2,1,&psSentinel);
        {
            BZROpenShim::TerrainHeight::DomainBinding binding;
            auto previous=height_texture(device.Get(),1), foreign=height_texture(device.Get(),4);
            auto* previousRaw=previous.Get(); context->DSSetShaderResources(127,1,&previousRaw);
            binding.view=sentinel; binding.domains.emplace_back(domain.Get());
            binding.Select(context.Get(),domain.Get());
            check(binding.Bound(context.Get()),"owned height not bound to exact domain");
            binding.Select(context.Get(),domain.Get());
            check(binding.binds==1,"repeat domain bind overwrote saved resource");
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            ComPtr<ID3D11ShaderResourceView> restored;
            context->DSGetShaderResources(127,1,&restored);
            check(restored.Get()==previous.Get()&&binding.restores==1,"foreign domain did not restore original DS resource");
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            auto* foreignRaw=foreign.Get(); context->DSSetShaderResources(127,1,&foreignRaw);
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            restored.Reset(); context->DSGetShaderResources(127,1,&restored);
            check(restored.Get()==foreign.Get()&&binding.binds==binding.restores,"height restore overwrote a foreign writer");
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            binding.Reset(); restored.Reset(); context->DSGetShaderResources(127,1,&restored);
            check(restored.Get()==foreign.Get(),"mission cleanup failed to restore prior resource");
        }
        unsigned runs=0;
        for (int orientation=0;orientation<4;++orientation)
        for (float eye:{0.f,320.f})
        for (float slope:{0.f,.1f})
        for (int field=0;field<6;++field)
        {
            std::vector<Vertex> input;
            const float corners[6][2]={{0,0},{20,0},{0,20},{20,0},{20,20},{0,20}};
            for (const auto& corner:corners)
            {
                float x=corner[0],z=corner[1],u=x/20,v=z/20;
                if (orientation==1) { float saved=u; u=v; v=1-saved; }
                if (orientation==2) u=1-u;
                if (orientation==3) { u=0; v=0; }
                const float baseY=slope*x+slope*.5f*z;
                const float normalLength=std::sqrt(slope*slope*1.25f+1);
                const float tangentLength=std::sqrt(slope*slope+1);
                input.push_back({{x-eye,baseY,z-eye+.25f*baseY,1},{x-eye,baseY,z-eye},{u,v},
                    {-slope/normalLength,1/normalLength,-slope*.5f/normalLength},
                    {1/tangentLength,slope/tangentLength,0}});
            }
            auto cb=constants(device.Get(),ds.Get(),eye,eye); ID3D11Buffer* cbRaw=cb.Get(); context->DSSetConstantBuffers(0,1,&cbRaw);
            D3D11_BUFFER_DESC inDesc{}; inDesc.ByteWidth=static_cast<UINT>(input.size()*sizeof(Vertex)); inDesc.Usage=D3D11_USAGE_IMMUTABLE; inDesc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA inData{input.data(),0,0}; ComPtr<ID3D11Buffer> buffer; ok(device->CreateBuffer(&inDesc,&inData,&buffer));
            ID3D11Buffer* vb=buffer.Get(); UINT stride=sizeof(Vertex),offset=0; context->IASetVertexBuffers(0,1,&vb,&stride,&offset);
            auto height=height_texture(device.Get(),field); ID3D11ShaderResourceView* srv=field==5?nullptr:height.Get(); context->DSSetShaderResources(127,1,&srv);
            ID3D11Buffer* so=output.Get(); context->SOSetTargets(1,&so,&offset);
            D3D11_QUERY_DESC queryDesc{D3D11_QUERY_SO_STATISTICS,0}; ComPtr<ID3D11Query> query;
            ok(device->CreateQuery(&queryDesc,&query)); context->Begin(query.Get()); context->Draw(6,0); context->End(query.Get());
            so=nullptr; context->SOSetTargets(1,&so,&offset); context->CopyResource(staging.Get(),output.Get());
            D3D11_MAPPED_SUBRESOURCE map{}; ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&map));
            D3D11_QUERY_DATA_SO_STATISTICS statistics{};
            check(context->GetData(query.Get(),&statistics,sizeof(statistics),0)==S_OK,"SO query did not complete after readback");
            check(statistics.NumPrimitivesWritten>2&&statistics.NumPrimitivesWritten*3<=1024&&
                statistics.PrimitivesStorageNeeded==statistics.NumPrimitivesWritten,"missing tessellation or SO overflow");
            const auto* values=static_cast<const Output*>(map.pData);
            unsigned displaced=0,interior=0,seam=0;
            for (size_t i=0;i<statistics.NumPrimitivesWritten*3;++i)
            {
                const auto& o=values[i];
                const float baseY=slope*(o.view[0]+eye)+slope*.5f*(o.view[2]+eye);
                const float h=o.view[1]-baseY;
                for (size_t n=0;n<sizeof(Output)/sizeof(float);++n)
                { float value; std::memcpy(&value,reinterpret_cast<const unsigned char*>(&o)+n*sizeof(float),sizeof(float)); check(std::isfinite(value),"nonfinite domain output"); }
                check(std::abs(h)<=(normalized ? .625f : 1.f),"height exceeded padded bounds");
                if (std::abs(h)>.001f) ++displaced;
                check(std::abs(o.position[1]-o.view[1])<1e-5f,"height did not move clip geometry");
                check(std::abs(o.position[2]-(o.view[2]+.25f*o.view[1]))<1e-4f,"clip depth not displaced consistently");
                check(std::abs(o.depth-o.position[2])<1e-5f,"domain depth output stale");
                check(std::abs(o.shadow1[1]-baseY-2*h)<1e-5f&&std::abs(o.shadow2[1]-baseY-3*h)<1e-5f&&std::abs(o.shadow3[1]-baseY-4*h)<1e-5f,"shadow receiver coordinates stale");
                const float u=o.uv[0],v=o.uv[1];
                if (field==1&&orientation<3&&u>.02f&&u<.98f&&v>.02f&&v<.98f)
                {
                    const float gain=normalized ? .625f : 1.f;
                    ++interior; check(std::abs(h-gain*(.3f*u+.2f*v-.25f))<2e-5f,"domain height differs from scaled signed texture");
                    float dx=gain*.3f/20,dz=gain*.2f/20;
                    if (orientation==1) { dx=-gain*.2f/20; dz=gain*.3f/20; }
                    if (orientation==2) dx=-dx;
                    const float totalX=slope+dx,totalZ=slope*.5f+dz;
                    float length=std::sqrt(totalX*totalX+1+totalZ*totalZ);
                    check(std::abs(o.normal[0]+totalX/length)<1e-5f&&std::abs(o.normal[1]-1/length)<1e-5f&&std::abs(o.normal[2]+totalZ/length)<1e-5f,"rotated/reflected geometric normal mismatch");
                    check(std::abs(o.tangent[1]-totalX/std::sqrt(1+totalX*totalX))<1e-5f,"displaced tangent mismatch");
                }
                if (field==4&&(u<.03f||u>.97f||v<.03f||v>.97f||std::abs(u-.5f)<.001f))
                {
                    ++seam; check(std::abs(h)<1e-5f&&std::abs(o.normal[1]-1/std::sqrt(1+1.25f*slope*slope))<1e-6f,"zero-border height or slope mismatch");
                }
                if (field==0||field==2||field==3||field==5||orientation==3)
                    check(std::abs(h)<1e-5f&&std::abs(o.normal[1]-1/std::sqrt(1+1.25f*slope*slope))<1e-6f,"flat/invalid/missing height or degenerate UVs changed base geometry");
            }
            context->Unmap(staging.Get(),0);
            if (field==1&&orientation<3) check(displaced>0&&interior>0,"height test did not capture moved interior vertices");
            if (field==4&&orientation<3) check(seam>0,"guarded seam test captured no seam");
            ID3D11ShaderResourceView* retained=nullptr; context->PSGetShaderResources(2,1,&retained);
            check(retained==psSentinel,"domain texture changed pixel shader resources"); if(retained)retained->Release();
            ++runs;
        }
        std::cout<<"PASS: "<<runs<<" actual height-domain/SO runs; signed geometry, UV rotation/reflection, camera translation, normals/tangents/depth/shadow receivers, zero seams, invalid/missing textures and PS retention\n";
        return 0;
    }
    catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
int main() { if (run(false)) return 1; return run(true); }
