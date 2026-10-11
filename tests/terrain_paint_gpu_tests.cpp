#include "terrain_paint.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
using Microsoft::WRL::ComPtr;
using namespace BZROpenShim;
struct Pixel { float r,g,b,a; };
static void check(bool v, const char* text) { if (!v) throw std::runtime_error(text); }
static void ok(HRESULT v) { check(SUCCEEDED(v), "D3D11 paint operation failed"); }
int main()
{
    try
    {
        TerrainPaint::Config config = {true,"0123456789abcdef",{0,0,4,4},{2,2,2,2}};
        std::string source = R"(
Texture2DArray diffuseMap : register(t0);
SamplerState diffuseSam : register(s0);
StructuredBuffer<float2> points : register(t1);
RWStructuredBuffer<float4> results : register(u0);
float4 PixelMain(float2 openShimHdUV : TEXCOORD9, float openShimTileSlice : TEXCOORD10) : SV_TARGET
{ return diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice)); }
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ results[id.x] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, points[id.x]); }
)";
        check(TerrainPaint::Specialize(source, true, config), "paint PS source specialization failed");
        ComPtr<ID3DBlob> code, errors;
        // Compile the derivative-based shipping sampler at the native target.
        ok(D3DCompile(source.data(),source.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors));
        const std::string compute = "#define OPENSHIM_PAINT_SAMPLE(tex,sam,uv) tex.SampleLevel(sam,float3(frac((uv).xy),(uv).z),0)\n" + source;
        HRESULT compiled = D3DCompile(compute.data(),compute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context;
        ok(D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_WARP,nullptr,0,nullptr,0,D3D11_SDK_VERSION,&device,nullptr,&context));
        ComPtr<ID3D11ComputeShader> shader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&shader));
        context->CSSetShader(shader.Get(),nullptr,0);
        std::vector<Pixel> pixels(4*4*5);
        const Pixel colors[] = {{1,0,0,1},{0,1,0,1},{0,0,1,1},{1,1,0,1}};
        for (unsigned slice=0; slice<4; ++slice) for (unsigned i=0; i<16; ++i) pixels[slice*16+i]=colors[slice];
        for (unsigned y=0;y<4;++y) for (unsigned x=0;x<4;++x)
        { Pixel w={0,0,0,0}; (&w.r)[x]=1; pixels[64+y*4+x]=w; }
        D3D11_TEXTURE2D_DESC td={};td.Width=td.Height=4;td.MipLevels=1;td.ArraySize=5;
        td.Format=DXGI_FORMAT_R32G32B32A32_FLOAT;td.SampleDesc.Count=1;td.BindFlags=D3D11_BIND_SHADER_RESOURCE;
        D3D11_SUBRESOURCE_DATA data[5]={};for(unsigned i=0;i<5;++i)data[i]={pixels.data()+16*i,4*sizeof(Pixel),0};
        ComPtr<ID3D11Texture2D> texture;ok(device->CreateTexture2D(&td,data,&texture));
        ComPtr<ID3D11ShaderResourceView> textureView;ok(device->CreateShaderResourceView(texture.Get(),nullptr,&textureView));
        const float points[][2]={{.5f,.5f},{1.5f,.5f},{2.5f,.5f},{3.5f,.5f},{1,.5f},{-100,.5f},{100,.5f}};
        constexpr UINT count=UINT(sizeof(points)/sizeof(points[0]));
        D3D11_BUFFER_DESC bd={};bd.ByteWidth=sizeof(points);bd.Usage=D3D11_USAGE_IMMUTABLE;bd.BindFlags=D3D11_BIND_SHADER_RESOURCE;
        bd.MiscFlags=D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;bd.StructureByteStride=sizeof(points[0]);
        D3D11_SUBRESOURCE_DATA inputData={points,0,0};ComPtr<ID3D11Buffer> input;ok(device->CreateBuffer(&bd,&inputData,&input));
        ComPtr<ID3D11ShaderResourceView> pointView;ok(device->CreateShaderResourceView(input.Get(),nullptr,&pointView));
        bd.ByteWidth=count*sizeof(Pixel);bd.StructureByteStride=sizeof(Pixel);bd.Usage=D3D11_USAGE_DEFAULT;bd.BindFlags=D3D11_BIND_UNORDERED_ACCESS;
        ComPtr<ID3D11Buffer> output;ok(device->CreateBuffer(&bd,nullptr,&output));
        ComPtr<ID3D11UnorderedAccessView> uav;ok(device->CreateUnorderedAccessView(output.Get(),nullptr,&uav));
        bd.Usage=D3D11_USAGE_STAGING;bd.BindFlags=bd.MiscFlags=bd.StructureByteStride=0;bd.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
        ComPtr<ID3D11Buffer> staging;ok(device->CreateBuffer(&bd,nullptr,&staging));
        D3D11_SAMPLER_DESC sd={};sd.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;sd.AddressU=sd.AddressV=sd.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
        sd.MaxLOD=D3D11_FLOAT32_MAX;ComPtr<ID3D11SamplerState> sampler;ok(device->CreateSamplerState(&sd,&sampler));
        ID3D11SamplerState* sample=sampler.Get();context->CSSetSamplers(0,1,&sample);
        ID3D11ShaderResourceView* views[]={textureView.Get(),pointView.Get()};context->CSSetShaderResources(0,2,views);
        const auto dispatch=[&](){ID3D11UnorderedAccessView* write=uav.Get();context->CSSetUnorderedAccessViews(0,1,&write,nullptr);context->Dispatch(count,1,1);
            write=nullptr;context->CSSetUnorderedAccessViews(0,1,&write,nullptr);context->CopyResource(staging.Get(),output.Get());};
        dispatch();D3D11_MAPPED_SUBRESOURCE mapped={};ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        const auto* values=static_cast<const Pixel*>(mapped.pData);
        const Pixel expected[]={{1,0,0,1},{0,1,0,1},{0,0,1,1},{1,1,0,1},{.5f,.5f,0,1},{1,0,0,1},{1,1,0,1}};
        for(UINT i=0;i<count;++i)for(unsigned c=0;c<4;++c)check(std::abs((&values[i].r)[c]-(&expected[i].r)[c])<1e-5f,"paint blend/edge clamp/alpha failed");
        context->Unmap(staging.Get(),0);
        // All-zero maps fall back to layer zero; unnormalised input stays stable.
        for (const Pixel control : {Pixel{0,0,0,0},Pixel{2,2,0,0}})
        {
            for(unsigned i=64;i<80;++i)pixels[i]=control;
            context->UpdateSubresource(texture.Get(),4,nullptr,pixels.data()+64,4*sizeof(Pixel),0);
            dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
            const float green=control.r?0.5f:0;
            for(UINT i=0;i<count;++i)check(std::abs(values[i].r-(1-green))<1e-5f&&std::abs(values[i].g-green)<1e-5f&&values[i].a==1,"weight normalisation/fallback failed");
            context->Unmap(staging.Get(),0);
        }
        // Repeat independently of the stock atlas sampler. A clamping sampler
        // would otherwise turn distant terrain into a constant edge texel.
        for(unsigned y=0;y<4;++y)for(unsigned x=0;x<4;++x)pixels[y*4+x]={float(x+1)/4,0,0,1};
        for(unsigned i=64;i<80;++i)pixels[i]={1,0,0,0};
        context->UpdateSubresource(texture.Get(),0,nullptr,pixels.data(),4*sizeof(Pixel),0);
        context->UpdateSubresource(texture.Get(),4,nullptr,pixels.data()+64,4*sizeof(Pixel),0);
        sd.AddressU=sd.AddressV=sd.AddressW=D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler.Reset();ok(device->CreateSamplerState(&sd,&sampler));sample=sampler.Get();context->CSSetSamplers(0,1,&sample);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        const float repeating[]={.375f,.875f,.375f,.875f,.625f,.25f,.25f};
        for(UINT i=0;i<count;++i)check(std::abs(values[i].r-repeating[i])<1e-5f,"native clamp sampler stopped material repetition");
        context->Unmap(staging.Get(),0);
        std::cout<<"PASS: native PS4 compilation, four GPU layers, soft blends, edge clamp, normalisation, opaque output and explicit repetition\n";
        return 0;
    }
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
