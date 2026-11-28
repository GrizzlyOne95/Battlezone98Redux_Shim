// Execute the shipped candidate TerrainDomain, then capture its actual output
// through geometry-stage stream output. This is a geometry test, not a
// compute-only height sample or evidence of native game resource binding.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl/client.h>
#include <array>
#include <cmath>
#include <cstdint>
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
            auto previousHull=height_texture(device.Get(),2); auto* previousHullRaw=previousHull.Get();
            context->HSSetShaderResources(127,1,&previousHullRaw);
            binding.view=sentinel; binding.domains.emplace_back(domain.Get());
            binding.Select(context.Get(),domain.Get());
            check(binding.Bound(context.Get()),"owned height not bound to exact domain");
            ComPtr<ID3D11ShaderResourceView> hullView; context->HSGetShaderResources(127,1,&hullView);
            check(hullView.Get()==sentinel.Get(),"owned height not bound to the hull for adaptive relief");
            binding.Select(context.Get(),domain.Get());
            check(binding.binds==1,"repeat domain bind overwrote saved resource");
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            ComPtr<ID3D11ShaderResourceView> restored;
            context->DSGetShaderResources(127,1,&restored);
            check(restored.Get()==previous.Get()&&binding.restores==1,"foreign domain did not restore original DS resource");
            hullView.Reset(); context->HSGetShaderResources(127,1,&hullView);
            check(hullView.Get()==previousHull.Get(),"foreign domain did not restore original HS resource");
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            auto* foreignRaw=foreign.Get(); context->DSSetShaderResources(127,1,&foreignRaw);
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            restored.Reset(); context->DSGetShaderResources(127,1,&restored);
            check(restored.Get()==foreign.Get()&&binding.binds==binding.restores,"height restore overwrote a foreign writer");
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            binding.Reset(); restored.Reset(); context->DSGetShaderResources(127,1,&restored);
            check(restored.Get()==foreign.Get(),"mission cleanup failed to restore prior resource");
        }
        {
            // A split paint control array rides slot 126 beside the height
            // array and restores in step with it.
            BZROpenShim::TerrainHeight::DomainBinding binding;
            auto control=height_texture(device.Get(),3), previousControl=height_texture(device.Get(),5);
            auto* previousControlRaw=previousControl.Get();
            context->DSSetShaderResources(126,1,&previousControlRaw); context->HSSetShaderResources(126,1,&previousControlRaw);
            binding.view=sentinel; binding.controlView=control; binding.domains.emplace_back(domain.Get());
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            check(binding.Bound(context.Get()),"split control array not bound with the height array");
            ComPtr<ID3D11ShaderResourceView> slot; context->HSGetShaderResources(126,1,&slot);
            check(slot.Get()==control.Get(),"split control array not bound to the hull");
            context->DSSetShaderResources(126,1,&previousControlRaw);
            check(!binding.Bound(context.Get()),"lost control slot still reported bound");
            auto* controlRaw=control.Get(); context->DSSetShaderResources(126,1,&controlRaw);
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            slot.Reset(); context->DSGetShaderResources(126,1,&slot);
            check(slot.Get()==previousControl.Get(),"foreign domain did not restore the DS control slot");
            slot.Reset(); context->HSGetShaderResources(126,1,&slot);
            check(slot.Get()==previousControl.Get(),"foreign domain did not restore the HS control slot");
            binding.Reset();
            ID3D11ShaderResourceView* none=nullptr; context->DSSetShaderResources(126,1,&none); context->HSSetShaderResources(126,1,&none);
            context->DSSetShader(domain.Get(),nullptr,0);
        }
        {
            // The relief bake rides slot 125 under the same rules: bound to
            // DS and HS, restored only while still ours, foreign SRVs kept.
            BZROpenShim::TerrainHeight::DomainBinding binding;
            auto baked=height_texture(device.Get(),3), previousBaked=height_texture(device.Get(),5), foreign=height_texture(device.Get(),4);
            auto* previousBakedRaw=previousBaked.Get();
            context->DSSetShaderResources(125,1,&previousBakedRaw); context->HSSetShaderResources(125,1,&previousBakedRaw);
            binding.view=sentinel; binding.bakedView=baked; binding.domains.emplace_back(domain.Get());
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            check(binding.Bound(context.Get()),"relief bake not bound with the height array");
            ComPtr<ID3D11ShaderResourceView> slot; context->HSGetShaderResources(125,1,&slot);
            check(slot.Get()==baked.Get(),"relief bake not bound to the hull");
            context->DSSetShaderResources(125,1,&previousBakedRaw);
            check(!binding.Bound(context.Get()),"lost relief bake slot still reported bound");
            auto* bakedRaw=baked.Get(); context->DSSetShaderResources(125,1,&bakedRaw);
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            slot.Reset(); context->DSGetShaderResources(125,1,&slot);
            check(slot.Get()==previousBaked.Get(),"foreign domain did not restore the DS relief bake slot");
            slot.Reset(); context->HSGetShaderResources(125,1,&slot);
            check(slot.Get()==previousBaked.Get(),"foreign domain did not restore the HS relief bake slot");
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            auto* foreignRaw=foreign.Get(); context->DSSetShaderResources(125,1,&foreignRaw); context->HSSetShaderResources(125,1,&foreignRaw);
            context->DSSetShader(nullptr,nullptr,0); binding.Select(context.Get(),nullptr);
            slot.Reset(); context->DSGetShaderResources(125,1,&slot);
            check(slot.Get()==foreign.Get(),"relief bake restore overwrote a foreign DS writer");
            slot.Reset(); context->HSGetShaderResources(125,1,&slot);
            check(slot.Get()==foreign.Get(),"relief bake restore overwrote a foreign HS writer");
            context->DSSetShader(domain.Get(),nullptr,0); binding.Select(context.Get(),domain.Get());
            binding.Reset();
            check(!binding.bakedView,"reset kept the relief bake view");
            slot.Reset(); context->DSGetShaderResources(125,1,&slot);
            check(slot.Get()==foreign.Get(),"mission cleanup failed to restore the prior relief bake slot");
            ID3D11ShaderResourceView* none=nullptr; context->DSSetShaderResources(125,1,&none); context->HSSetShaderResources(125,1,&none);
            context->DSSetShader(domain.Get(),nullptr,0);
        }
        {
            // The native relief bake dispatch (TerrainHeight::DispatchReliefBake, the code
            // the shim runs): it must put back a foreign compute shader, its t126/t127
            // SRVs and its u0 UAV untouched, clear the dirty flag on the immediate
            // context only, and do nothing on a deferred one.
            using namespace BZROpenShim::TerrainHeight;
            const auto refs=[](IUnknown* object){ object->AddRef(); return object->Release(); };
            const auto computeShader=[&](const char* text){
                ComPtr<ID3DBlob> code,errors;
                HRESULT result=D3DCompile(text,std::strlen(text),nullptr,nullptr,nullptr,"main","cs_5_0",0,0,&code,&errors);
                if (FAILED(result)&&errors) std::cerr<<static_cast<const char*>(errors->GetBufferPointer());
                ok(result); ComPtr<ID3D11ComputeShader> shader;
                ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&shader)); return shader;
            };
            const auto uavTexture=[&](UINT size,ComPtr<ID3D11Texture2D>& texture,ComPtr<ID3D11UnorderedAccessView>& uav){
                D3D11_TEXTURE2D_DESC desc{}; desc.Width=desc.Height=size; desc.MipLevels=desc.ArraySize=desc.SampleDesc.Count=1;
                desc.Format=DXGI_FORMAT_R16G16B16A16_FLOAT; desc.BindFlags=D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_UNORDERED_ACCESS;
                ok(device->CreateTexture2D(&desc,nullptr,&texture)); ok(device->CreateUnorderedAccessView(texture.Get(),nullptr,&uav));
            };
            ReliefBake bake; DomainBinding binding; std::atomic<bool> dirty{true};
            bake.shader=computeShader("RWTexture2D<float4> o:register(u0); Texture2D<float4> c:register(t126); Texture2D<float4> p:register(t127);"
                "[numthreads(8,8,1)] void main(uint3 id:SV_DispatchThreadID){ o[id.xy]=float4(c.Load(int3(0,0,0)).r,p.Load(int3(0,0,0)).r,0,1); }");
            uavTexture(16,bake.texture,bake.target); bake.width=bake.height=16;
            binding.view=height_texture(device.Get(),1); binding.controlView=height_texture(device.Get(),3);
            binding.domains.emplace_back(domain.Get());
            auto foreignShader=computeShader("[numthreads(1,1,1)] void main(){}");
            auto foreignControl=height_texture(device.Get(),4), foreignPaint=height_texture(device.Get(),5);
            ComPtr<ID3D11Texture2D> foreignTexture; ComPtr<ID3D11UnorderedAccessView> foreignTarget; uavTexture(4,foreignTexture,foreignTarget);
            ID3D11ShaderResourceView* foreignViews[2]={foreignControl.Get(),foreignPaint.Get()};
            ID3D11UnorderedAccessView* foreignUav=foreignTarget.Get();
            context->CSSetShader(foreignShader.Get(),nullptr,0); context->CSSetShaderResources(126,2,foreignViews);
            context->CSSetUnorderedAccessViews(0,1,&foreignUav,nullptr);
            const ULONG before[]={refs(foreignShader.Get()),refs(foreignControl.Get()),refs(foreignPaint.Get()),refs(foreignTarget.Get())};
            // A deferred context never bakes, and keeps the work pending.
            ComPtr<ID3D11DeviceContext> deferred; ok(device->CreateDeferredContext(0,&deferred));
            check(!DispatchReliefBake(bake,binding,dirty,deferred.Get(),domain.Get())&&dirty.load()&&bake.dispatches==0,
                "deferred context baked or cleared the dirty flag");
            binding.Select(context.Get(),domain.Get());
            check(binding.context.Get()==context.Get(),"bake test could not bind the owned domain first");
            check(DispatchReliefBake(bake,binding,dirty,context.Get(),domain.Get()),"relief bake did not dispatch on the immediate context");
            check(!dirty.load()&&bake.dispatches==1,"relief bake left the dirty flag set or did not count");
            check(!binding.context&&binding.restores==1,"relief bake kept the domain binding while its UAV was bound");
            {
                // The kernel wrote (t126.r, t127.r, 0, 1): control (field 3, 1.5) then
                // paint (field 1, texel 0,0), so swapped views or a missing UAV fail.
                D3D11_TEXTURE2D_DESC bakeDesc{}; bake.texture->GetDesc(&bakeDesc);
                bakeDesc.Usage=D3D11_USAGE_STAGING; bakeDesc.BindFlags=0; bakeDesc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
                ComPtr<ID3D11Texture2D> readback; ok(device->CreateTexture2D(&bakeDesc,nullptr,&readback));
                context->CopyResource(readback.Get(),bake.texture.Get());
                D3D11_MAPPED_SUBRESOURCE bakeMap{}; ok(context->Map(readback.Get(),0,D3D11_MAP_READ,0,&bakeMap));
                uint16_t texel[4]; std::memcpy(texel,bakeMap.pData,sizeof(texel)); context->Unmap(readback.Get(),0);
                const auto half=[](uint16_t h){
                    const int exponent=(h>>10)&31; const float mantissa=float(h&1023);
                    float value=exponent==0?std::ldexp(mantissa,-24):std::ldexp(1024+mantissa,exponent-25);
                    return (h&0x8000)?-value:value; };
                const float expectedPaint=.3f*.5f/64+.2f*.5f/64-.25f;
                check(std::abs(half(texel[0])-1.5f)<1e-3f&&std::abs(half(texel[1])-expectedPaint)<1e-3f&&
                    half(texel[2])==0&&half(texel[3])==1,"relief bake did not write control (t126) then paint (t127) into its target");
            }
            check(!DispatchReliefBake(bake,binding,dirty,context.Get(),domain.Get())&&bake.dispatches==1,"clean relief bake dispatched again");
            ComPtr<ID3D11ComputeShader> shaderAfter; context->CSGetShader(&shaderAfter,nullptr,nullptr);
            ID3D11ShaderResourceView* rawViews[2]{}; context->CSGetShaderResources(126,2,rawViews);
            ComPtr<ID3D11ShaderResourceView> keepControl,keepPaint; keepControl.Attach(rawViews[0]); keepPaint.Attach(rawViews[1]);
            ComPtr<ID3D11UnorderedAccessView> uavAfter; context->CSGetUnorderedAccessViews(0,1,&uavAfter);
            check(shaderAfter.Get()==foreignShader.Get(),"relief bake did not restore the foreign compute shader");
            check(keepControl.Get()==foreignControl.Get()&&keepPaint.Get()==foreignPaint.Get(),"relief bake did not restore the foreign t126/t127 views");
            check(uavAfter.Get()==foreignTarget.Get(),"relief bake did not restore the foreign u0 view");
            shaderAfter.Reset(); keepControl.Reset(); keepPaint.Reset(); uavAfter.Reset();
            const ULONG after[]={refs(foreignShader.Get()),refs(foreignControl.Get()),refs(foreignPaint.Get()),refs(foreignTarget.Get())};
            for (int i=0;i<4;++i) check(before[i]==after[i],"relief bake leaked or dropped a reference on a foreign object");
            ID3D11ShaderResourceView* noViews[2]={}; ID3D11UnorderedAccessView* noUav=nullptr;
            context->CSSetShader(nullptr,nullptr,0); context->CSSetShaderResources(126,2,noViews); context->CSSetUnorderedAccessViews(0,1,&noUav,nullptr);
            context->DSSetShader(domain.Get(),nullptr,0);
            // Sizing: exact lattice below the 4096 cap, a coarser covering step above it.
            const auto lattice=SizeReliefBake(93,55,5.0f/7);
            check(!lattice.capped&&lattice.step==double(5.0f/7)&&lattice.width==132&&lattice.height==78,"relief bake lattice size changed");
            const auto capped=SizeReliefBake(20000,100,1);
            check(capped.capped&&capped.width==4096&&std::abs(capped.step-20000.0/4095)<1e-9&&
                (capped.width-1)*capped.step>=20000-1e-6&&capped.height<=4096,"relief bake cap did not coarsen the spacing");
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
        // Hull off-screen cull: with no hull matrices bound it must never cull;
        // with them bound it culls only patches whose relief sweep stays outside.
        const auto hullPrimitives=[&](float x0,float y,bool bindHull)
        {
            std::vector<Vertex> input;
            const float corners[6][2]={{0,0},{20,0},{0,20},{20,0},{20,20},{0,20}};
            for (const auto& corner:corners)
                input.push_back({{x0+corner[0],y,corner[1],1},{x0+corner[0],y,corner[1]},{corner[0]/20,corner[1]/20},{0,1,0},{1,0,0}});
            ComPtr<ID3D11Buffer> hullCb;
            if (bindHull)
            {
                ComPtr<ID3D11ShaderReflection> reflection;
                ok(D3DReflect(hs->GetBufferPointer(),hs->GetBufferSize(),IID_ID3D11ShaderReflection,&reflection));
                auto* block=reflection->GetConstantBufferByName("$Globals");
                D3D11_SHADER_BUFFER_DESC desc{}; ok(block->GetDesc(&desc));
                std::vector<unsigned char> bytes((desc.Size+15)&~15u);
                for (const char* name:{"reliefView","reliefProjection"})
                {
                    D3D11_SHADER_VARIABLE_DESC variable{}; ok(block->GetVariableByName(name)->GetDesc(&variable));
                    check(variable.Size==64&&variable.StartOffset+64<=bytes.size(),"hull cull matrix reflection contract changed");
                    auto matrix=identity(); std::memcpy(bytes.data()+variable.StartOffset,matrix.data(),64);
                }
                D3D11_BUFFER_DESC buffer{}; buffer.ByteWidth=static_cast<UINT>(bytes.size()); buffer.Usage=D3D11_USAGE_IMMUTABLE; buffer.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
                D3D11_SUBRESOURCE_DATA data{bytes.data(),0,0}; ok(device->CreateBuffer(&buffer,&data,&hullCb));
            }
            ID3D11Buffer* hullRaw=hullCb.Get(); context->HSSetConstantBuffers(0,1,&hullRaw);
            D3D11_BUFFER_DESC inDesc{}; inDesc.ByteWidth=static_cast<UINT>(input.size()*sizeof(Vertex)); inDesc.Usage=D3D11_USAGE_IMMUTABLE; inDesc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA inData{input.data(),0,0}; ComPtr<ID3D11Buffer> buffer; ok(device->CreateBuffer(&inDesc,&inData,&buffer));
            ID3D11Buffer* vb=buffer.Get(); UINT stride=sizeof(Vertex),offset=0; context->IASetVertexBuffers(0,1,&vb,&stride,&offset);
            ID3D11Buffer* so=output.Get(); context->SOSetTargets(1,&so,&offset);
            D3D11_QUERY_DESC queryDesc{D3D11_QUERY_SO_STATISTICS,0}; ComPtr<ID3D11Query> query;
            ok(device->CreateQuery(&queryDesc,&query)); context->Begin(query.Get()); context->Draw(6,0); context->End(query.Get());
            so=nullptr; context->SOSetTargets(1,&so,&offset); hullRaw=nullptr; context->HSSetConstantBuffers(0,1,&hullRaw);
            D3D11_QUERY_DATA_SO_STATISTICS statistics{};
            while (context->GetData(query.Get(),&statistics,sizeof(statistics),0)==S_FALSE) {}
            return statistics.NumPrimitivesWritten;
        };
        const float amplitude=normalizedHeight ? .625f : 1.f;
        check(hullPrimitives(-320,0,false)>2,"hull culled without bound matrices");
        check(hullPrimitives(-320,0,true)==0,"hull kept a patch left of the screen");
        check(hullPrimitives(0,0,true)>2,"hull culled a patch on screen");
        check(hullPrimitives(0,-1.1f-amplitude*.5f,true)>2,"hull culled a patch relief can raise into view");
        check(hullPrimitives(0,-1.1f-amplitude*1.5f,true)==0,"hull kept a patch below its relief reach");
        std::cout<<"PASS: "<<runs<<" actual height-domain/SO runs; signed geometry, UV rotation/reflection, camera translation, normals/tangents/depth/shadow receivers, zero seams, invalid/missing textures, PS retention, split control and relief bake slots and hull off-screen cull\n";
        return 0;
    }
    catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
int main() { if (run(false)) return 1; return run(true); }
