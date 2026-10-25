#include "terrain_paint.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
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
{ results[id.x] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, OpenShimPaintGeometry(points[id.x], 0, float3(0,1,0))); }
)";
        check(TerrainPaint::Specialize(source, true, config), "paint PS source specialization failed");
        ComPtr<ID3DBlob> code, errors;
        // Compile the derivative-based shipping sampler at the native target.
        ok(D3DCompile(source.data(),source.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors));
        // Compute has no derivatives: sample level zero with zero gradients.
        const std::string noDerivatives = "#define OPENSHIM_PAINT_SAMPLE(tex,sam,uv,gx,gy) tex.SampleLevel(sam,float3(frac((uv).xy),(uv).z),0)\n"
            "#define OPENSHIM_PAINT_DDX(v) ((v) * 0)\n#define OPENSHIM_PAINT_DDY(v) ((v) * 0)\n";
        const std::string compute = noDerivatives + source;
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
        // Full material form: specular in diffuse alpha, normal+height in 5-8,
        // and the taller layer taking a 50/50 transition outright.
        TerrainPaint::Config material = config; material.sliceCount = 9; material.heightBlend = 0.5f;
        std::string materialSource = R"(
Texture2DArray diffuseMap : register(t0);
SamplerState diffuseSam : register(s0);
RWStructuredBuffer<float4> results : register(u0);
float4 PixelMain(float2 openShimHdUV : TEXCOORD9, float openShimTileSlice : TEXCOORD10) : SV_TARGET
{ float3 geometryNormal = float3(0,1,0); float3 vViewPosition = float3(openShimHdUV.x, 0, openShimHdUV.y); float2 vTexCoord = openShimHdUV;
  float3x3 tbn = cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord);
  float4 n = normalMap.Sample(normalSam, vTexCoord); float3 s = specularMap.Sample(specularSam, vTexCoord).xyz;
  return diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice)) + n + float4(mul(s, tbn), 0); }
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ OpenShimPaintGeo at = OpenShimPaintGeometry(float2(1.5, 1.5), 0, float3(0,1,0)); results[0] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, at);
  results[1] = OpenShimSampleTerrainPaintNormal(diffuseMap, diffuseSam, at);
  results[2] = float4(OpenShimSampleTerrainPaintSpecular(diffuseMap, diffuseSam, at), 1); }
)";
        const std::string frame = "float3x3 cotangent_frame(float3 N, float3 p, float2 uv) { return float3x3(ddx(p), ddy(p), N); }\n"
            "Texture2D normalMap : register(t2); SamplerState normalSam : register(s2);\n"
            "Texture2D specularMap : register(t3); SamplerState specularSam : register(s3);\n";
        const std::string materialRaw = materialSource;
        check(TerrainPaint::Specialize(materialSource, true, material), "material PS specialization failed");
        materialSource = frame + materialSource;
        ok(D3DCompile(materialSource.data(),materialSource.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors));
        const std::string materialCompute = noDerivatives + materialSource;
        compiled = D3DCompile(materialCompute.data(),materialCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> materialShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&materialShader));
        std::vector<Pixel> layers(16*9);
        const Pixel diffuse[] = {{1,0,0,.1f},{0,1,0,.7f},{0,0,1,0},{1,1,0,0}};
        const Pixel normals[] = {{.5f,.5f,1,0},{1,.5f,.5f,1},{.5f,.5f,1,0},{.5f,.5f,1,0}};  // alpha is height
        for (unsigned i=0;i<16;++i)
        {
            for (unsigned l=0;l<4;++l) { layers[l*16+i]=diffuse[l]; layers[(5+l)*16+i]=normals[l]; }
            layers[64+i]={.5f,.5f,0,0};
        }
        td.ArraySize=9; D3D11_SUBRESOURCE_DATA layerData[9]={};
        for(unsigned i=0;i<9;++i)layerData[i]={layers.data()+16*i,4*sizeof(Pixel),0};
        ComPtr<ID3D11Texture2D> materialTexture;ok(device->CreateTexture2D(&td,layerData,&materialTexture));
        ComPtr<ID3D11ShaderResourceView> materialView;ok(device->CreateShaderResourceView(materialTexture.Get(),nullptr,&materialView));
        context->CSSetShader(materialShader.Get(),nullptr,0);
        ID3D11ShaderResourceView* materialViews[]={materialView.Get()};context->CSSetShaderResources(0,1,materialViews);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        const Pixel taller[]={{0,1,0,1},{1,.5f,.5f,1},{.7f,.7f,.7f,1}};
        for(UINT i=0;i<3;++i)for(unsigned c=0;c<4;++c)check(std::abs((&values[i].r)[c]-(&taller[i].r)[c])<1e-5f,"height blend/material channels failed");
        context->Unmap(staging.Get(),0);
        // Triplanar: an IBL pass with a view normal and inverse view projects
        // walls sideways. Flat ground keeps the original XZ mapping exactly.
        std::string triplanarSource = R"(
Texture2DArray diffuseMap : register(t0);
SamplerState diffuseSam : register(s0);
RWStructuredBuffer<float4> results : register(u0);
float4 PixelMain(float2 openShimHdUV : TEXCOORD9, float openShimTileSlice : TEXCOORD10,
    in float3 vViewNormal : TEXCOORD2, uniform float4x4 inverseViewMatrix) : SV_TARGET
{ float3 geometryNormal = normalize(vViewNormal);
  float3x3 tbn = cotangent_frame(geometryNormal, vViewPosition.xyz, vTexCoord);
  float4 n = normalMap.Sample(normalSam, vTexCoord);
  return diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice)) + float4(mul(n.xyz * 2 - 1, tbn), 0); }
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ OpenShimPaintGeo flat = OpenShimPaintGeometry(float2(1.25, 0.25), 0.75, float3(0,1,0));
  OpenShimPaintGeo east = OpenShimPaintGeometry(float2(1.25, 0.25), 0.75, float3(1,0,0));
  OpenShimPaintGeo west = OpenShimPaintGeometry(float2(1.25, 0.25), 0.75, float3(-1,0,0));
  OpenShimPaintGeo north = OpenShimPaintGeometry(float2(1.25, 0.25), 0.75, float3(0,0,1));
  results[0] = OpenShimSampleTerrainPaintNormal(diffuseMap, diffuseSam, flat);
  results[1] = OpenShimSampleTerrainPaintNormal(diffuseMap, diffuseSam, north);
  results[2] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, flat);
  results[3] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, east);
  results[4] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, west);
  results[5] = OpenShimSampleTerrainPaint(diffuseMap, diffuseSam, north); }
)";
        const std::string triplanarRaw = triplanarSource;
        check(TerrainPaint::Specialize(triplanarSource, true, material) &&
            triplanarSource.find("#define OPENSHIM_PAINT_TRIPLANAR_SOURCE 1") != std::string::npos, "triplanar PS specialization failed");
        triplanarSource = "#define IBL_ENABLED\n#define ENHANCED_MODE\n" + triplanarSource;
        compiled = D3DCompile(triplanarSource.data(),triplanarSource.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        const std::string triplanarCompute = noDerivatives + triplanarSource;
        compiled = D3DCompile(triplanarCompute.data(),triplanarCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> triplanarShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&triplanarShader));
        // Layer zero only: colour encodes the texel, its normal leans to +x.
        for (unsigned y=0;y<4;++y) for (unsigned x=0;x<4;++x)
        {
            const unsigned i=y*4+x;
            layers[i]={float(x+1)/4,float(y+1)/4,0,0}; layers[5*16+i]={1,.5f,.5f,0}; layers[64+i]={1,0,0,0};
        }
        for(unsigned i=0;i<9;++i)context->UpdateSubresource(materialTexture.Get(),i,nullptr,layers.data()+16*i,4*sizeof(Pixel),0);
        context->CSSetShader(triplanarShader.Get(),nullptr,0);
        sd.AddressU=sd.AddressV=sd.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
        sampler.Reset();ok(device->CreateSamplerState(&sd,&sampler));sample=sampler.Get();context->CSSetSamplers(0,1,&sample);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        // Flat (x,z)=(1.25,.25) is texel (2,0); the east wall projects (z,y)
        // to texel (0,1), the west wall mirrors u to texel (3,1) and the north
        // wall projects (-x,y) to texel (1,1). On the north wall the +x lean
        // points along world -X, which is -t in its frame.
        const Pixel projected[]={{1,.5f,.5f,1},{0,.5f,.5f,1},{.75f,.25f,0,1},{.25f,.5f,0,1},{1,.5f,0,1},{.5f,.5f,0,1}};
        for(UINT i=0;i<6;++i)for(unsigned c=0;c<4;++c)check(std::abs((&values[i].r)[c]-(&projected[i].r)[c])<1e-5f,"triplanar projection/normal failed");
        context->Unmap(staging.Get(),0);
        // De-tiling: the shipping PS4 targets compile, the offsets move the
        // pattern, and the domain shader picks the same height as the pixel
        // shader so displacement follows the shaded tile.
        TerrainPaint::Config detiled = material; detiled.detile = {1, 0, 0, 0};
        std::string detiledTriplanar = triplanarRaw;
        check(TerrainPaint::Specialize(detiledTriplanar, true, detiled), "detile PS specialization failed");
        detiledTriplanar = "#define IBL_ENABLED\n#define ENHANCED_MODE\n" + frame + detiledTriplanar;
        compiled = D3DCompile(detiledTriplanar.data(),detiledTriplanar.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        std::string detileSource = R"(
Texture2DArray diffuseMap : register(t0);
SamplerState diffuseSam : register(s0);
RWStructuredBuffer<float4> results : register(u0);
float4 PixelMain(float2 openShimHdUV : TEXCOORD9, float openShimTileSlice : TEXCOORD10) : SV_TARGET
{ return diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice)); }
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ OpenShimPaintGeo g = OpenShimPaintGeometry(float2(1.3 + 9.1 * id.x, 0.7 + 4.3 * id.x), 0, float3(0,1,0));
  results[id.x] = float4(OpenShimPaintTap(diffuseMap, diffuseSam, g, openShimPaintRepeats[0], 5, openShimPaintDetile[0] > 0).a,
      OpenShimPaintTap(diffuseMap, diffuseSam, g, openShimPaintRepeats[0], 5, false).a, 0, 0); }
)";
        check(TerrainPaint::Specialize(detileSource, true, detiled), "detile compute specialization failed");
        ok(D3DCompile(detileSource.data(),detileSource.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors));
        const std::string detileCompute = noDerivatives + detileSource;
        compiled = D3DCompile(detileCompute.data(),detileCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> detileShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&detileShader));
        std::ifstream tessFile(TERRAIN_TESS_SHADER_PATH, std::ios::binary);
        std::string tessSource((std::istreambuf_iterator<char>(tessFile)), {});
        check(!tessSource.empty(), "shipped terrain shader missing");
        const std::string tessRaw = tessSource;
        // The domain shader takes the same layer constants as the pixel shader.
        const std::string tessDefines = "#define OPENSHIM_RELIEF_TEST 1\n#define OPENSHIM_RELIEF_AMPLITUDE 100\n#define OPENSHIM_TERRAIN_HD 1\n"
            "#define OPENSHIM_PAINT_HEIGHT 1\n#define OPENSHIM_PAINT_BOUNDS float4(0,0,4,4)\n#define OPENSHIM_PAINT_HEIGHT_SCALE 1\n";
        TerrainPaint::Config detiledHeight = detiled; detiledHeight.heightMeters = {1, 0, 0, 0};
        tessSource = tessDefines + TerrainPaint::LayerHlsl(detiledHeight) + TerrainPaint::DetileHlsl() + tessSource + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestDetile(uint3 id : SV_DispatchThreadID)
{ float2 p = float2(1.3 + 9.1 * id.x, 0.7 + 4.3 * id.x);
  testResults[id.x] = float4(TerrainPaintLayerHeight(p, 2, 5, true), TerrainPaintLayerHeight(p, 2, 5, false), 0, 0); }
)";
        compiled = D3DCompile(tessSource.data(),tessSource.size(),nullptr,nullptr,nullptr,"TestDetile","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> tessShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&tessShader));
        for (unsigned i=0;i<16;++i) layers[5*16+i].a = float((i*7)%16)/15;
        context->UpdateSubresource(materialTexture.Get(),5,nullptr,layers.data()+5*16,4*sizeof(Pixel),0);
        std::vector<Pixel> shaded(count), displaced(count);
        context->CSSetShader(detileShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        std::memcpy(shaded.data(),mapped.pData,count*sizeof(Pixel));context->Unmap(staging.Get(),0);
        ID3D11ShaderResourceView* tessViews[]={materialView.Get()};context->CSSetShaderResources(127,1,tessViews);
        context->CSSetShader(tessShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        std::memcpy(displaced.data(),mapped.pData,count*sizeof(Pixel));context->Unmap(staging.Get(),0);
        bool moved=false;
        for(UINT i=0;i<count;++i)
        {
            check(std::abs(shaded[i].r-displaced[i].r)<0.01f&&std::abs(shaded[i].g-displaced[i].g)<0.01f,"detile height differs between pixel and domain shaders");
            moved = moved || std::abs(shaded[i].r-shaded[i].g)>0.05f;
        }
        check(moved,"detile offsets left the pattern unchanged");
        // The relief's analytic slope matches a fine central difference of its
        // height through control normalisation, the height-aware selection,
        // detile and craters (the detail field's slope is approximate by design
        // and checked on its own below). Kinks (texel edges, selection
        // switches) may disagree for a few of the 448 samples.
        TerrainPaint::Config slopedHeight = detiled; slopedHeight.heightMeters = {1, .6f, 0, 0};
        slopedHeight.craterLayers = {1, 0, 0, 0}; slopedHeight.detailLayers = {.5f, .5f, 0, 0};
        const std::string slopeTess = "#define OPENSHIM_RELIEF_TEST 1\n#define OPENSHIM_RELIEF_AMPLITUDE 100\n#define OPENSHIM_TERRAIN_HD 1\n"
            "#define OPENSHIM_PAINT_HEIGHT 1\n#define OPENSHIM_PAINT_BOUNDS float4(-3,-5,90,50)\n#define OPENSHIM_PAINT_HEIGHT_SCALE 1\n"
            "#define OPENSHIM_PAINT_CRATERS float4(6,0.2,0.5,3)\n" +
            TerrainPaint::LayerHlsl(slopedHeight) + TerrainPaint::DetileHlsl() + TerrainPaint::CraterHlsl() + tessRaw + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestSlope(uint3 id : SV_DispatchThreadID)
{ const float e = 0.001; float worst = 0, misses = 0, steep = 0;
  [loop] for (int s = 0; s < 64; ++s)
  { float2 p = float2(0.37 + 5.3 * id.x + 0.57 * s, 0.61 + 3.1 * id.x + 0.71 * (s % 9));
    // One inlined relief: the 32-bit compiler runs out of memory on five.
    // Divide by the steps the floats actually took, not by 2e.
    float2 at[5] = { p, p + float2(e, 0), p - float2(e, 0), p + float2(0, e), p - float2(0, e) };
    float3 r[5];
    [loop] for (int k = 0; k < 5; ++k) r[k] = TerrainPaintRelief(at[k]);
    float2 fd = float2((r[1].x - r[2].x) / (at[1].x - at[2].x), (r[3].x - r[4].x) / (at[3].y - at[4].y));
    float err = length(r[0].yz - fd) / max(1.0, length(fd));
    if (err > 0.02) misses += 1; else worst = max(worst, err);
    steep += length(r[0].yz); }
  testResults[id.x] = float4(worst, misses, steep, 0); }
)";
        compiled = D3DCompile(slopeTess.data(),slopeTess.size(),nullptr,nullptr,nullptr,"TestSlope","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> slopeShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&slopeShader));
        const std::vector<Pixel> keptLayers = layers;
        for (unsigned i=0;i<16;++i)
        {
            layers[4*16+i] = {float(i%4)/3, float(i/4)/3 + .1f, 0, 0};
            layers[6*16+i].a = float((i*5)%16)/15;
        }
        for (unsigned s : {4u, 6u}) context->UpdateSubresource(materialTexture.Get(),s,nullptr,layers.data()+s*16,4*sizeof(Pixel),0);
        context->CSSetShader(slopeShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        float misses = 0, steep = 0;
        for(UINT i=0;i<count;++i)
        {
            check(values[i].r<0.02f,"relief slope differs from its height");
            misses += values[i].g; steep += values[i].b;
        }
        context->Unmap(staging.Get(),0);
        check(misses<=count*64*0.03f,"relief slope differs from its height at too many samples");
        check(steep>count*64*0.05f,"relief slope test ground is flat");
        layers = keptLayers;
        for (unsigned s : {4u, 6u}) context->UpdateSubresource(materialTexture.Get(),s,nullptr,layers.data()+s*16,4*sizeof(Pixel),0);
        // Distance scale, macro variation and craters: every pixel variant
        // and the domain shader compile; crater slopes match their heights.
        TerrainPaint::Config varied = detiled;
        varied.farScale = {5, 40, 250, 0.6f}; varied.macro = {260, 0.12f, 0.15f, 0.35f};
        varied.craters = {6, 0.2f, 0.5f, 3}; varied.craterLayers = {1, 0, 0, 0};
        varied.detail = {40, 1, 4, 1}; varied.detailLayers = {0.5f, 0, 0, 0};
        varied.parallax = {1, 40, 12, 0};
        // Triplanar with IBL, and the top-projection material path.
        const std::pair<std::string, const char*> variants[] = {
            {triplanarRaw, "#define IBL_ENABLED\n#define ENHANCED_MODE\n"}, {materialRaw, ""}};
        for (const auto& [raw, prefix] : variants)
            {
                std::string variant = raw;
                const std::string slice = "float openShimTileSlice : TEXCOORD10";
                // The triplanar pass also takes the view position, for parallax.
                const bool ibl = *prefix != 0;
                variant.replace(variant.find(slice), slice.size(), slice + ", in float vDepth : TEXCOORD5" +
                    (ibl ? ", in float3 vViewPosition : TEXCOORD4" : ""));
                check(TerrainPaint::Specialize(variant, true, varied) &&
                    variant.find("#define OPENSHIM_PAINT_VIEW_DEPTH vDepth") != std::string::npos &&
                    variant.find(std::string("#define OPENSHIM_PAINT_PARALLAX ") + (ibl ? "1" : "0")) != std::string::npos,
                    "varied PS specialization failed");
                variant = prefix + frame + variant;
                compiled = D3DCompile(variant.data(),variant.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors);
                if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
                ok(compiled);
            }
        // Parallax: layer 0's height is a checker at mip 0 and flat 0.5 above,
        // so the fine-minus-coarse relief is the checker alone. Looking
        // straight down, beyond the fade or at a wall leaves the point; an
        // oblique ray moves along its own XZ to where it meets the relief.
        {
            TerrainPaint::Config pom = material;
            pom.repeatMeters = {1, 1, 1, 1}; pom.heightMeters = {1, 0, 0, 0}; pom.detile = {};
            pom.bounds = {0, 0, 8, 8}; pom.parallax = {1, 40, 32, 0};
            std::string pomSource = R"(
Texture2DArray diffuseMap : register(t0);
SamplerState diffuseSam : register(s0);
RWStructuredBuffer<float4> results : register(u0);
float4 PixelMain(float2 openShimHdUV : TEXCOORD9, float openShimTileSlice : TEXCOORD10, in float vDepth : TEXCOORD5,
    in float3 vViewPosition : TEXCOORD4, in float3 vViewNormal : TEXCOORD2, uniform float4x4 inverseViewMatrix) : SV_TARGET
{ return diffuseMap.Sample(diffuseSam, float3(openShimHdUV, openShimTileSlice)); }
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ float2 p = float2(0.31 + 0.137 * id.x, 0.23 + 0.071 * id.x);
  float3 n = id.x == 2 ? float3(1, 0, 0) : float3(0, 1, 0);
  float3 view = id.x == 0 ? float3(0, -1, 0) : float3(1, -1, 0);
  float depth = id.x == 1 ? 50 : 5;
  OpenShimPaintGeo g = OpenShimPaintGeometryAt(p, 0, n, depth);
  OpenShimPaintGeo hit = OpenShimPaintParallaxAt(diffuseMap, diffuseSam, g, view, depth);
  float2 moved = hit.pos.xz - g.pos.xz;
  // run is (1, 0) at 45 degrees, so the ray meets the relief at height -moved.x.
  float relief = OpenShimPaintFineHeight(diffuseMap, diffuseSam, g, OpenShimPaintControl(diffuseMap, diffuseSam, p), hit.pos.xz) * 0.875;
  results[id.x] = float4(moved, relief + moved.x, 0); }
)";
            check(TerrainPaint::Specialize(pomSource, true, pom) &&
                pomSource.find("#define OPENSHIM_PAINT_PARALLAX 1") != std::string::npos, "parallax PS specialization failed");
            pomSource = "#define IBL_ENABLED\n#define ENHANCED_MODE\n" + pomSource;
            compiled = D3DCompile(pomSource.data(),pomSource.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
            // Explicit gradients work in compute; zero ones read mip 0.
            const std::string pomCompute = "#define OPENSHIM_PAINT_SAMPLE(tex,sam,uv,gx,gy) tex.SampleGrad(sam,float3(frac((uv).xy),(uv).z),gx,gy)\n"
                "#define OPENSHIM_PAINT_DDX(v) ((v) * 0)\n#define OPENSHIM_PAINT_DDY(v) ((v) * 0)\n" + pomSource;
            compiled = D3DCompile(pomCompute.data(),pomCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
            ComPtr<ID3D11ComputeShader> pomShader;
            ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&pomShader));
            constexpr UINT side=8, mips=4;
            std::vector<std::vector<Pixel>> texels; std::vector<D3D11_SUBRESOURCE_DATA> pomData;
            for (UINT s=0;s<9;++s) for (UINT m=0;m<mips;++m)
            {
                const UINT w=side>>m; std::vector<Pixel> level(w*w,Pixel{0,0,0,0});
                for (UINT i=0;i<w*w;++i)
                {
                    if (s==4) level[i]={1,0,0,0};
                    if (s==5) level[i].a = m ? .5f : float(((i%w)+(i/w))%2);
                }
                texels.push_back(std::move(level));
            }
            for (UINT i=0;i<texels.size();++i) pomData.push_back({texels[i].data(),(side>>(i%mips))*UINT(sizeof(Pixel)),0});
            D3D11_TEXTURE2D_DESC pd=td; pd.Width=pd.Height=side; pd.MipLevels=mips; pd.ArraySize=9;
            ComPtr<ID3D11Texture2D> pomTexture; ok(device->CreateTexture2D(&pd,pomData.data(),&pomTexture));
            ComPtr<ID3D11ShaderResourceView> pomView; ok(device->CreateShaderResourceView(pomTexture.Get(),nullptr,&pomView));
            ComPtr<ID3D11ShaderResourceView> savedView; context->CSGetShaderResources(0,1,&savedView);
            ID3D11ShaderResourceView* pomViews[]={pomView.Get()}; context->CSSetShaderResources(0,1,pomViews);
            context->CSSetShader(pomShader.Get(),nullptr,0);
            dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
            bool shifted=false;
            for(UINT i=0;i<count;++i)
            {
                if (i<3) { check(values[i].r==0&&values[i].g==0,"parallax moved a point it should leave"); continue; }
                // Top is half the 1 m relief, faded to 0.875 at 5 m.
                check(std::abs(values[i].r)<=.4375f+1e-4f&&values[i].g==0,"parallax left its ray or bound");
                check(std::abs(values[i].b)<.03f,"parallax missed the relief");
                shifted = shifted || std::abs(values[i].r)>.05f;
            }
            context->Unmap(staging.Get(),0);
            check(shifted,"parallax never moved the point");
            ID3D11ShaderResourceView* restore[]={savedView.Get()}; context->CSSetShaderResources(0,1,restore);
        }
        std::string craterSource = std::string(TerrainPaint::DetileHlsl()) + TerrainPaint::CraterHlsl() + R"(
RWStructuredBuffer<float4> results : register(u0);
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ float2 p = float2(3.7 + 13.1 * id.x, 1.9 + 7.7 * id.x); const float e = 0.002;
  float4 params = float4(6, 0.2, 0.9, 3);
  OpenShimCrater c = OpenShimCraterField(p, params, 0);
  float dx = (OpenShimCraterField(p + float2(e, 0), params, 0).h - OpenShimCraterField(p - float2(e, 0), params, 0).h) / (2 * e);
  float dz = (OpenShimCraterField(p + float2(0, e), params, 0).h - OpenShimCraterField(p - float2(0, e), params, 0).h) / (2 * e);
  results[id.x] = float4(c.h, c.slope - float2(dx, dz), OpenShimCraterField(p, params, 100).h); }
)";
        compiled = D3DCompile(craterSource.data(),craterSource.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> craterShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&craterShader));
        context->CSSetShader(craterShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        bool cratered=false;
        for(UINT i=0;i<count;++i)
        {
            // Kinks at the floor and rim edge make a few samples disagree
            // only where the finite difference straddles them.
            check(std::abs(values[i].g)<0.05f&&std::abs(values[i].b)<0.05f,"crater slope differs from its height");
            check(values[i].a==0,"unresolvable craters did not fade out");
            cratered = cratered || std::abs(values[i].r)>0.01f;
        }
        context->Unmap(staging.Get(),0);
        check(cratered,"crater field left the ground flat");
        // Erosion detail: undamped, the analytic slope matches its height (the
        // damping term is left out of the slope on purpose); it stays within
        // its metres, and octaves finer than the footprint fade out.
        std::string detailSource = std::string(TerrainPaint::DetileHlsl()) + TerrainPaint::CraterHlsl() + R"(
RWStructuredBuffer<float4> results : register(u0);
[numthreads(1,1,1)] void ComputeMain(uint3 id : SV_DispatchThreadID)
{ float2 p = float2(3.7 + 13.1 * id.x, 1.9 + 7.7 * id.x); const float e = 0.002;
  float4 params = float4(20, 1.5, 5, 0);
  OpenShimCrater c = OpenShimDetailField(p, params, 0);
  float dx = (OpenShimDetailField(p + float2(e, 0), params, 0).h - OpenShimDetailField(p - float2(e, 0), params, 0).h) / (2 * e);
  float dz = (OpenShimDetailField(p + float2(0, e), params, 0).h - OpenShimDetailField(p - float2(0, e), params, 0).h) / (2 * e);
  results[id.x] = float4(c.h, c.slope - float2(dx, dz), OpenShimDetailField(p, params, 100).h); }
)";
        compiled = D3DCompile(detailSource.data(),detailSource.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> detailShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&detailShader));
        context->CSSetShader(detailShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        bool rough=false;
        for(UINT i=0;i<count;++i)
        {
            check(std::abs(values[i].g)<0.01f&&std::abs(values[i].b)<0.01f,"detail slope differs from its height");
            check(std::abs(values[i].r)<=1.5f&&values[i].a==0,"detail height escaped its bound or did not fade");
            rough = rough || std::abs(values[i].r)>0.05f;
        }
        context->Unmap(staging.Get(),0);
        check(rough,"detail field left the ground flat");
        TerrainPaint::Config craterHeight = material; craterHeight.heightMeters = {1, 0, 0, 0};
        craterHeight.craters = {6, 0.2f, 0.5f, 3}; craterHeight.craterLayers = {1, 0, 0, 0};
        craterHeight.detail = {40, 1, 4, 1}; craterHeight.detailLayers = {0.5f, 0, 0, 0};
        std::string craterTess = tessDefines + "#define OPENSHIM_PAINT_CRATERS float4(6,0.2,0.5,3)\n"
            "#define OPENSHIM_PAINT_DETAIL float4(40,1,4,1)\n" +
            TerrainPaint::LayerHlsl(craterHeight) + TerrainPaint::DetileHlsl() + TerrainPaint::CraterHlsl() + tessRaw + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestCraters(uint3 id : SV_DispatchThreadID)
{ testResults[id.x] = float4(TerrainPaintRelief(float2(1.3 + 9.1 * id.x, 0.7 + 4.3 * id.x)), 0); }
)";
        compiled = D3DCompile(craterTess.data(),craterTess.size(),nullptr,nullptr,nullptr,"TestCraters","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        // Eight layers in two 9-slice banks: the second control (slice 13)
        // weights layers 4-7, whose diffuse sits in 9-12 and normal+height in
        // 14-17, and the height-aware blend runs across both banks.
        TerrainPaint::Config eight = material; eight.sliceCount = 18; eight.repeatMeters = {2,2,2,2,2,2,2,2};
        std::string eightSource = materialRaw;
        check(TerrainPaint::Specialize(eightSource, true, eight), "eight-layer PS specialization failed");
        eightSource = frame + eightSource;
        ok(D3DCompile(eightSource.data(),eightSource.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors));
        const std::string eightCompute = noDerivatives + eightSource;
        compiled = D3DCompile(eightCompute.data(),eightCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> eightShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&eightShader));
        std::vector<Pixel> banks(16*18);
        for (unsigned i=0;i<16;++i)
        {
            for (unsigned l=0;l<8;++l)
            {
                const unsigned bank=l/4*9, local=l%4;
                banks[(bank+local)*16+i]={float(l)/8,float(l%2),.25f,float(l)/10};
                banks[(bank+5+local)*16+i]={.5f,.5f,1,l==5?1.0f:0.0f};
            }
            banks[5*16+i]={1,.5f,.5f,0};  // layer zero leans +x
            banks[4*16+i]={0,0,0,0}; banks[13*16+i]={0,1,0,0};
        }
        td.ArraySize=18; D3D11_SUBRESOURCE_DATA bankData[18]={};
        for(unsigned i=0;i<18;++i)bankData[i]={banks.data()+16*i,4*sizeof(Pixel),0};
        ComPtr<ID3D11Texture2D> eightTexture;ok(device->CreateTexture2D(&td,bankData,&eightTexture));
        ComPtr<ID3D11ShaderResourceView> eightView;ok(device->CreateShaderResourceView(eightTexture.Get(),nullptr,&eightView));
        context->CSSetShader(eightShader.Get(),nullptr,0);
        ID3D11ShaderResourceView* eightViews[]={eightView.Get()};context->CSSetShaderResources(0,1,eightViews);
        // Second control alone, then a 50/50 split with layer zero where the
        // taller layer five takes the transition.
        for (const Pixel first : {Pixel{0,0,0,0},Pixel{1,0,0,0}})
        {
            for(unsigned i=0;i<16;++i)banks[4*16+i]=first;
            context->UpdateSubresource(eightTexture.Get(),4,nullptr,banks.data()+4*16,4*sizeof(Pixel),0);
            dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
            const Pixel layerFive[]={{5.0f/8,1,.25f,1},{.5f,.5f,1,1},{.5f,.5f,.5f,1}};
            for(UINT i=0;i<3;++i)for(unsigned c=0;c<4;++c)check(std::abs((&values[i].r)[c]-(&layerFive[i].r)[c])<1e-5f,"eight-layer bank or blend failed");
            context->Unmap(staging.Get(),0);
        }
        std::string eightTess = tessDefines + TerrainPaint::LayerHlsl(eight) + TerrainPaint::DetileHlsl() + tessRaw + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestEight(uint3 id : SV_DispatchThreadID)
{ testResults[id.x] = float4(TerrainPaintRelief(float2(1.3 + 9.1 * id.x, 0.7 + 4.3 * id.x)), 0); }
)";
        compiled = D3DCompile(eightTess.data(),eightTess.size(),nullptr,nullptr,nullptr,"TestEight","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        // The adaptive hull reads both control banks for its relief scale.
        const std::string adaptiveHull = "#define OPENSHIM_TESS_ADAPTIVE 1\n#define OPENSHIM_TESS_FACTOR 8\n"
            "static const float openShimPaintReliefMeters[8] = {1,0,0,0,0,2,0,0};\n" + eightTess;
        for (const char* stage : {"TerrainHull", "TerrainDomain"})
        {
            compiled = D3DCompile(adaptiveHull.data(),adaptiveHull.size(),nullptr,nullptr,nullptr,stage,
                stage[7] == 'H' ? "hs_5_0" : "ds_5_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
        }
        std::cout<<"PASS: eight-layer banks and adaptive hull, close-up parallax, distance scale, macro variation and crater variants, crater and detail slopes, detile pixel/domain parity, triplanar walls and flat ground, native PS4 compilation, material slices, height-aware blend, four GPU layers, soft blends, edge clamp, normalisation, opaque output and explicit repetition\n";
        return 0;
    }
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
