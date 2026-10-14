// Execute the shipped edge policy and hull/domain stages on D3D11 WARP.
// Check invalid inputs, edge reversal, viewport/distance response, continuous
// requests, and raster coverage across a shared diagonal at fractional factors.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
using Microsoft::WRL::ComPtr;
struct Vec { float x,y,z,w; };
struct Edge { Vec a,b,viewport; };
static void check(bool value,const char* message) { if(!value) throw std::runtime_error(message); }
static void ok(HRESULT result) { check(SUCCEEDED(result),"D3D11 adaptive test failed"); }
static ComPtr<ID3DBlob> compile(const std::string& source,const char* entry,const char* profile,const char* pixels="12")
{
    const D3D_SHADER_MACRO macros[]={{"OPENSHIM_TESS_ADAPTIVE","1"},{"OPENSHIM_TESS_FACTOR","4"},
        {"OPENSHIM_TESS_TARGET_PIXELS",pixels},{nullptr,nullptr}};
    ComPtr<ID3DBlob> code,errors;
    const auto hr=D3DCompile(source.data(),source.size(),nullptr,macros,nullptr,entry,profile,
        D3DCOMPILE_OPTIMIZATION_LEVEL3|D3DCOMPILE_IEEE_STRICTNESS,0,&code,&errors);
    if(FAILED(hr)&&errors) std::cerr<<static_cast<const char*>(errors->GetBufferPointer());
    ok(hr); return code;
}
int main()
{
    try
    {
        std::ifstream file(TERRAIN_TESS_SHADER_PATH,std::ios::binary);
        std::string source((std::istreambuf_iterator<char>(file)),{});
        check(!source.empty(),"shipped terrain shader missing");
        source+=R"(
struct EdgeTest { float4 a,b,viewport; };
StructuredBuffer<EdgeTest> edges : register(t0);
RWStructuredBuffer<float4> results : register(u0);
[numthreads(1,1,1)] void TestEdges(uint3 id:SV_DispatchThreadID) {
    EdgeTest e=edges[id.x];
    results[id.x]=float4(TerrainAdaptiveEdge(e.a,e.b,e.viewport.xy),
        TerrainAdaptiveEdge(e.b,e.a,e.viewport.xy),0,0);
}
TerrainTessVertex TestVertex(uint id:SV_VertexID) {
    const float2 points[6]={float2(-.25,-.25),float2(-.25,.25),float2(.25,.25),
        float2(-.25,-.25),float2(.25,.25),float2(.25,-.25)};
    TerrainTessVertex v=(TerrainTessVertex)0;
    v.position=float4(points[id],.5,1); v.normal=float3(0,1,0);
    return v;
}
float4 TestPixel(TerrainTessVertex v):SV_Target { return float4(1,1,1,1); }
)";
        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context; D3D_FEATURE_LEVEL level;
        ok(D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_WARP,nullptr,0,nullptr,0,D3D11_SDK_VERSION,&device,&level,&context));
        check(level>=D3D_FEATURE_LEVEL_11_0,"WARP feature level 11 required");
        const float nan=std::numeric_limits<float>::quiet_NaN(),inf=std::numeric_limits<float>::infinity();
        std::vector<Edge> edges={
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{128,128,0,0}}, // fractional 32/12
            {{-.25f,0,.5f,2},{.25f,0,.5f,2},{128,128,0,0}}, // farther, floor 2
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{256,128,0,0}}, // higher resolution, cap 4
            {{-.25f,0,.5f,0},{.25f,0,.5f,1},{128,128,0,0}},
            {{-.25f,0,.5f,-1},{.25f,0,.5f,1},{128,128,0,0}},
            {{nan,0,.5f,1},{.25f,0,.5f,1},{128,128,0,0}},
            {{-.25f,0,.5f,1},{inf,0,.5f,1},{128,128,0,0}},
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{0,128,0,0}},
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{128,nan,0,0}},
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{20000,128,0,0}},
            {{-1e30f,0,.5f,1},{1e30f,0,.5f,1},{128,128,0,0}},
            {{.25f,0,.5f,1},{.25f,0,.5f,1},{128,128,0,0}}, // degenerate edge, no cull
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{127.999f,128,0,0}},
            {{-.25f,0,.5f,1},{.25f,0,.5f,1},{128.001f,128,0,0}},
        };
        D3D11_BUFFER_DESC desc{}; desc.ByteWidth=static_cast<UINT>(edges.size()*sizeof(Edge));
        desc.Usage=D3D11_USAGE_IMMUTABLE; desc.BindFlags=D3D11_BIND_SHADER_RESOURCE;
        desc.MiscFlags=D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; desc.StructureByteStride=sizeof(Edge);
        D3D11_SUBRESOURCE_DATA data{edges.data(),0,0}; ComPtr<ID3D11Buffer> input;
        ok(device->CreateBuffer(&desc,&data,&input)); ComPtr<ID3D11ShaderResourceView> srv;
        ok(device->CreateShaderResourceView(input.Get(),nullptr,&srv));
        desc.ByteWidth=static_cast<UINT>(edges.size()*sizeof(Vec)); desc.StructureByteStride=sizeof(Vec);
        desc.Usage=D3D11_USAGE_DEFAULT; desc.BindFlags=D3D11_BIND_UNORDERED_ACCESS;
        ComPtr<ID3D11Buffer> output; ok(device->CreateBuffer(&desc,nullptr,&output));
        ComPtr<ID3D11UnorderedAccessView> uav; ok(device->CreateUnorderedAccessView(output.Get(),nullptr,&uav));
        desc.Usage=D3D11_USAGE_STAGING; desc.BindFlags=desc.MiscFlags=desc.StructureByteStride=0;
        desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ; ComPtr<ID3D11Buffer> staging;
        ok(device->CreateBuffer(&desc,nullptr,&staging));
        auto code=compile(source,"TestEdges","cs_5_0"); ComPtr<ID3D11ComputeShader> compute;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&compute));
        auto* read=srv.Get(); auto* write=uav.Get(); context->CSSetShader(compute.Get(),nullptr,0);
        context->CSSetShaderResources(0,1,&read); context->CSSetUnorderedAccessViews(0,1,&write,nullptr);
        context->Dispatch(static_cast<UINT>(edges.size()),1,1); write=nullptr;
        context->CSSetUnorderedAccessViews(0,1,&write,nullptr); context->CopyResource(staging.Get(),output.Get());
        D3D11_MAPPED_SUBRESOURCE mapped{}; ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        const auto* values=static_cast<const Vec*>(mapped.pData);
        for(size_t i=0;i<edges.size();++i)
        {
            check(std::isfinite(values[i].x)&&values[i].x>=2&&values[i].x<=4,"invalid/culling adaptive factor");
            check(values[i].x==values[i].y,"reversed shared edge requests disagree");
        }
        check(std::abs(values[0].x-32.0f/12.0f)<1e-5f&&values[1].x==2&&values[2].x==4,"distance/viewport response wrong");
        for(size_t i=3;i<=10;++i) check(values[i].x==4,"unsafe edge did not retain conservative cap");
        check(values[11].x==2,"degenerate edge was culled");
        check(values[13].x>values[12].x&&values[13].x-values[12].x<.001f,"factor request snapped under small view change");
        context->Unmap(staging.Get(),0);

        code=compile(source,"TestVertex","vs_5_0"); ComPtr<ID3D11VertexShader> vertex;
        ok(device->CreateVertexShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&vertex));
        code=compile(source,"TestPixel","ps_5_0"); ComPtr<ID3D11PixelShader> pixel;
        ok(device->CreatePixelShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&pixel));
        D3D11_TEXTURE2D_DESC tex{}; tex.Width=tex.Height=128; tex.MipLevels=tex.ArraySize=1;
        tex.Format=DXGI_FORMAT_R8G8B8A8_UNORM; tex.SampleDesc.Count=1; tex.BindFlags=D3D11_BIND_RENDER_TARGET;
        ComPtr<ID3D11Texture2D> target; ok(device->CreateTexture2D(&tex,nullptr,&target));
        ComPtr<ID3D11RenderTargetView> rtv; ok(device->CreateRenderTargetView(target.Get(),nullptr,&rtv));
        tex.Usage=D3D11_USAGE_STAGING; tex.BindFlags=0; tex.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
        ComPtr<ID3D11Texture2D> pixels; ok(device->CreateTexture2D(&tex,nullptr,&pixels));
        Vec viewport{128,128,1.0f/128,1.0f/128}; desc={}; desc.ByteWidth=sizeof(viewport);
        desc.Usage=D3D11_USAGE_IMMUTABLE; desc.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
        data={&viewport,0,0}; ComPtr<ID3D11Buffer> constant; ok(device->CreateBuffer(&desc,&data,&constant));
        D3D11_RASTERIZER_DESC raster{}; raster.FillMode=D3D11_FILL_SOLID; raster.CullMode=D3D11_CULL_NONE;
        raster.DepthClipEnable=TRUE; ComPtr<ID3D11RasterizerState> state;
        ok(device->CreateRasterizerState(&raster,&state)); context->RSSetState(state.Get());
        D3D11_VIEWPORT vp{0,0,128,128,0,1}; context->RSSetViewports(1,&vp);
        auto* render=rtv.Get(); context->OMSetRenderTargets(1,&render,nullptr);
        auto* cb=constant.Get(); context->HSSetConstantBuffers(0,1,&cb);
        context->VSSetShader(vertex.Get(),nullptr,0); context->PSSetShader(pixel.Get(),nullptr,0);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
        UINT64 low=0,high=0;
        for(const char* targetPixels:{"64","12","4"})
        {
            code=compile(source,"TerrainHull","hs_5_0",targetPixels); ComPtr<ID3D11HullShader> hull;
            ok(device->CreateHullShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&hull));
            code=compile(source,"TerrainDomain","ds_5_0",targetPixels); ComPtr<ID3D11DomainShader> domain;
            ok(device->CreateDomainShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&domain));
            context->HSSetShader(hull.Get(),nullptr,0); context->DSSetShader(domain.Get(),nullptr,0);
            const float black[4]={}; context->ClearRenderTargetView(rtv.Get(),black);
            D3D11_QUERY_DESC queryDesc{D3D11_QUERY_PIPELINE_STATISTICS,0}; ComPtr<ID3D11Query> query;
            ok(device->CreateQuery(&queryDesc,&query)); context->Begin(query.Get()); context->Draw(6,0); context->End(query.Get());
            context->CopyResource(pixels.Get(),target.Get()); ok(context->Map(pixels.Get(),0,D3D11_MAP_READ,0,&mapped));
            for(UINT y=48;y<80;++y) for(UINT x=48;x<80;++x)
                check(static_cast<const unsigned char*>(mapped.pData)[y*mapped.RowPitch+x*4]==255,"shared-edge raster gap");
            context->Unmap(pixels.Get(),0);
            D3D11_QUERY_DATA_PIPELINE_STATISTICS stats{};
            ok(context->GetData(query.Get(),&stats,sizeof(stats),0));
            check(stats.HSInvocations==2&&stats.DSInvocations>0&&stats.PSInvocations>0,"tessellation stages did not execute");
            if(std::string(targetPixels)=="64") low=stats.DSInvocations;
            if(std::string(targetPixels)=="4") high=stats.DSInvocations;
        }
        check(low<high,"adaptive distant cap did not reduce generated domain samples");
        std::cout<<"PASS: GPU shared edges, finite bounds, view response, fractional raster coverage; DS "<<low<<" < "<<high<<'\n';
        return 0;
    }
    catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
