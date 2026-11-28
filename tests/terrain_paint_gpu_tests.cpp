#include "terrain_paint.h"
#include "terrain_height_domain_binding.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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
        triplanarSource = "#define IBL_ENABLED\n#define ENHANCED_MODE\nstatic float surfaceRainTime = 0;\n" + triplanarSource;
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
        detiledTriplanar = "#define IBL_ENABLED\n#define ENHANCED_MODE\nstatic float surfaceRainTime = 0;\n" + frame + detiledTriplanar;
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
        const std::string mipDimensionsSource = tessDefines + TerrainPaint::LayerHlsl(detiledHeight) +
            TerrainPaint::DetileHlsl() + tessRaw + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestMipDimensions(uint3 id : SV_DispatchThreadID)
{
    uint mip = id.x % 4, width, height, elements, levels;
    terrainPaintArray.GetDimensions(mip, width, height, elements, levels);
    uint baseWidth, baseHeight, baseElements, baseLevels;
    terrainPaintArray.GetDimensions(0, baseWidth, baseHeight, baseElements, baseLevels);
    uint2 dimensions = max(uint2(baseWidth, baseHeight) >> mip, 1);
    float2 uv = float2(0.17 + id.x * 0.31, 0.83 - id.x * 0.19);
    TerrainPaintTap reference = TerrainPaintBilinearGrad(terrainPaintArray, uv, 0, mip, true);
    TerrainPaintTap cached = TerrainPaintBilinearGradSized(terrainPaintArray, uv, 0, mip, true, dimensions);
    testResults[id.x] = float4(reference.v.a - cached.v.a,
        reference.du.a - cached.du.a, reference.dv.a - cached.dv.a,
        any(dimensions != uint2(width, height)) ? 1.0 : 0.0);
}
)";
        compiled = D3DCompile(mipDimensionsSource.data(),mipDimensionsSource.size(),nullptr,nullptr,nullptr,
            "TestMipDimensions","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> mipDimensionsShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&mipDimensionsShader));
        constexpr UINT mipWidth = 10, mipHeight = 6, mipLevels = 4;
        std::vector<std::vector<Pixel>> mipPixels(mipLevels);
        D3D11_SUBRESOURCE_DATA mipData[mipLevels] = {};
        for (UINT mip = 0; mip < mipLevels; ++mip)
        {
            const UINT mipWidthAtLevel = mipWidth >> mip, mipHeightAtLevel = mipHeight >> mip;
            const UINT width = mipWidthAtLevel ? mipWidthAtLevel : 1;
            const UINT height = mipHeightAtLevel ? mipHeightAtLevel : 1;
            mipPixels[mip].resize(width * height);
            for (UINT y = 0; y < height; ++y) for (UINT x = 0; x < width; ++x)
                mipPixels[mip][y * width + x] = {float(x), float(y), float(mip), float(x * 3 + y * 5 + mip)};
            mipData[mip] = {mipPixels[mip].data(), width * sizeof(Pixel), 0};
        }
        D3D11_TEXTURE2D_DESC mipDesc = {};
        mipDesc.Width = mipWidth; mipDesc.Height = mipHeight; mipDesc.MipLevels = mipLevels; mipDesc.ArraySize = 1;
        mipDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; mipDesc.SampleDesc.Count = 1;
        mipDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        ComPtr<ID3D11Texture2D> mipTexture; ok(device->CreateTexture2D(&mipDesc, mipData, &mipTexture));
        D3D11_SHADER_RESOURCE_VIEW_DESC mipViewDesc = {};
        mipViewDesc.Format = mipDesc.Format; mipViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        mipViewDesc.Texture2DArray.MostDetailedMip = 0; mipViewDesc.Texture2DArray.MipLevels = mipLevels;
        mipViewDesc.Texture2DArray.FirstArraySlice = 0; mipViewDesc.Texture2DArray.ArraySize = 1;
        ComPtr<ID3D11ShaderResourceView> mipView; ok(device->CreateShaderResourceView(mipTexture.Get(), &mipViewDesc, &mipView));
        context->CSSetShader(mipDimensionsShader.Get(),nullptr,0);
        ID3D11ShaderResourceView* mipViews[] = {mipView.Get()};
        context->CSSetShaderResources(127,1,mipViews);
        dispatch(); ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        values = static_cast<const Pixel*>(mapped.pData);
        for (UINT mip = 0; mip < mipLevels; ++mip)
            for (unsigned c = 0; c < 4; ++c)
                check(std::abs((&values[mip].r)[c]) < 1e-5f, "cached mip dimensions changed paint relief sampling");
        context->Unmap(staging.Get(),0);
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
        // Distance scale (one layer near-only), macro variation and craters: every pixel variant
        // and the domain shader compile; crater slopes match their heights.
        TerrainPaint::Config varied = detiled;
        varied.farScale = {5, 40, 250, 0.6f}; varied.macro = {260, 0.12f, 0.15f, 0.35f};
        varied.craters = {6, 0.2f, 0.5f, 3}; varied.craterLayers = {1, 0, 0, 0};
        varied.detail = {40, 1, 4, 1}; varied.detailLayers = {0.5f, 0, 0, 0};
        varied.parallax = {1, 40, 12, 0};
        varied.nearOnly = {0, 1, 0, 0};
        // Triplanar with IBL, and the top-projection material path.
        const std::pair<std::string, const char*> variants[] = {
            {triplanarRaw, "#define IBL_ENABLED\n#define ENHANCED_MODE\nstatic float surfaceRainTime = 0;\n"}, {materialRaw, ""}};
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
        // Liquid layers: the glow injection and the warped, animated taps
        // compile in the pixel pass (with the final-colour line the injection
        // needs) and in the derivative-free compute form. The pass has no
        // engine time of its own, so Specialize must declare one the shader
        // really reads; the HD bind sets it by name.
        {
            TerrainPaint::Config lava = varied;
            lava.liquid = {1.5f, 0, 0, 0}; lava.liquidFlow = {1.5f, 40, 4, 0.5f};
            std::string liquidSource = triplanarRaw;
            const std::string tail = "  return diffuseMap.Sample(";
            liquidSource.replace(liquidSource.find(tail), tail.size(),
                "  float3 emissiveContribution = 0, aerialSurface = 1, surfaceTransmission = 1; float4 oColor = 0;\n"
                "    oColor.xyz = aerialSurface * surfaceTransmission + emissiveContribution;\n  oTarget = diffuseMap.Sample(");
            const std::string signature = "float4 PixelMain(";
            liquidSource.replace(liquidSource.find(signature), signature.size(), "void terrain_fragment(out float4 oTarget : SV_TARGET, ");
            const std::string target = ") : SV_TARGET";
            liquidSource.replace(liquidSource.find(target), target.size(), ")");
            const std::string slice = "float openShimTileSlice : TEXCOORD10";
            liquidSource.replace(liquidSource.find(slice), slice.size(), slice + ", in float vDepth : TEXCOORD5, in float3 vViewPosition : TEXCOORD4");
            check(TerrainPaint::Specialize(liquidSource, true, lava) &&
                liquidSource.find("#define OPENSHIM_PAINT_LIQUID 1") != std::string::npos, "liquid PS specialization failed");
            check(liquidSource.find(std::string("terrain_fragment(uniform float ") + TerrainPaint::kTimeUniform + ", ") != std::string::npos &&
                liquidSource.find(std::string("#define OPENSHIM_PAINT_TIME ") + TerrainPaint::kTimeUniform) != std::string::npos,
                "liquid PS lacks its time parameter");
            liquidSource = "#define IBL_ENABLED\n#define OSE_LINEAR_LIGHT_ACTIVE 1\n"
                "float3 srgb_to_linear(float3 c) { return c * c; }\n" + frame + liquidSource;
            compiled = D3DCompile(liquidSource.data(),liquidSource.size(),nullptr,nullptr,nullptr,"terrain_fragment","ps_4_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
            Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;
            ok(D3DReflect(code->GetBufferPointer(), code->GetBufferSize(), __uuidof(ID3D11ShaderReflection),
                reinterpret_cast<void**>(reflection.GetAddressOf())));
            D3D11_SHADER_VARIABLE_DESC timeDesc{};
            auto* timeVariable = reflection->GetVariableByName(TerrainPaint::kTimeUniform);
            check(timeVariable && SUCCEEDED(timeVariable->GetDesc(&timeDesc)) && (timeDesc.uFlags & D3D_SVF_USED),
                "liquid PS does not read its time uniform");
            // A second buffer leaves the entry point's own uniforms at zero in game.
            D3D11_SHADER_DESC liquidDesc{};
            ok(reflection->GetDesc(&liquidDesc));
            check(liquidDesc.ConstantBuffers == 1, "liquid PS time uniform opened a second constant buffer");
            const std::string liquidCompute = noDerivatives + liquidSource;
            compiled = D3DCompile(liquidCompute.data(),liquidCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
        }
        // Stock BZR terrain programs have no emissive sum: the glow lands on
        // the colour just before fog. A pass with no anchor at all skips
        // liquid and still specializes, so the map keeps its paint.
        {
            TerrainPaint::Config lava = varied;
            lava.liquid = {1.5f, 0, 0, 0}; lava.liquidFlow = {1.5f, 40, 4, 0.5f};
            std::string stockSource = triplanarRaw;
            const std::string tail = "  return diffuseMap.Sample(";
            stockSource.replace(stockSource.find(tail), tail.size(),
                "  float4 oColor = diffuseMap.Sample(diffuseSam, float3(openShimHdUV, 0));\n"
                "\tfloat fogValue = saturate((vDepth - fogParams.y) * fogParams.w);\n"
                "\toColor.xyz = lerp(oColor.xyz, float3(1,1,1), fogValue);\n  oTarget = oColor + diffuseMap.Sample(");
            const std::string signature = "float4 PixelMain(";
            stockSource.replace(stockSource.find(signature), signature.size(), "void terrain_fragment(out float4 oTarget : SV_TARGET, ");
            const std::string target = ") : SV_TARGET";
            stockSource.replace(stockSource.find(target), target.size(), ")");
            const std::string slice = "float openShimTileSlice : TEXCOORD10";
            stockSource.replace(stockSource.find(slice), slice.size(), slice + ", in float vDepth : TEXCOORD5, in float3 vViewPosition : TEXCOORD4");
            std::string bare = stockSource;
            std::string why;
            check(TerrainPaint::Specialize(stockSource, true, lava, &why) && why.empty() &&
                stockSource.find("#define OPENSHIM_PAINT_LIQUID 1") != std::string::npos &&
                stockSource.find("    oColor.xyz += openShimPaintGlowColour * openShimPaintGlowAmount;\n#endif\n\tfloat fogValue") != std::string::npos,
                "stock liquid PS specialization failed");
            stockSource = "#define IBL_ENABLED\nstatic float4 fogParams = 0;\n" + frame + stockSource;
            compiled = D3DCompile(stockSource.data(),stockSource.size(),nullptr,nullptr,nullptr,"terrain_fragment","ps_4_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
            const std::string fog = "\tfloat fogValue = saturate((vDepth - fogParams.y) * fogParams.w);\n";
            bare.erase(bare.find(fog), fog.size());
            bare.replace(bare.find("fogValue);"), 10, "0.0);");
            check(TerrainPaint::Specialize(bare, true, lava, &why) && why == "liquid skipped: no emissive anchor or entry point" &&
                bare.find("#define OPENSHIM_PAINT_LIQUID 0") != std::string::npos &&
                bare.find(TerrainPaint::kTimeUniform + std::string(", ")) == std::string::npos,
                "anchorless liquid PS did not skip liquid");
            bare = "#define IBL_ENABLED\n" + frame + bare;
            compiled = D3DCompile(bare.data(),bare.size(),nullptr,nullptr,nullptr,"terrain_fragment","ps_4_0",0,0,&code,&errors);
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
            pomSource = "#define IBL_ENABLED\n#define ENHANCED_MODE\nstatic float surfaceRainTime = 0;\n" + pomSource;
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
        // Split control: the same weights from their own array (one slice per
        // bank, register t4) shade identically, while the colour array's
        // control slots hold unrelated texels that must not be read.
        std::vector<Pixel> combined(count);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        std::memcpy(combined.data(),mapped.pData,count*sizeof(Pixel));context->Unmap(staging.Get(),0);
        std::string splitSource = materialRaw;
        check(TerrainPaint::Specialize(splitSource, true, eight, nullptr, 4) &&
            splitSource.find("Texture2DArray openShimPaintControlMap : register(t4);") != std::string::npos &&
            splitSource.find("#define OPENSHIM_PAINT_CONTROL_SPLIT 1") != std::string::npos, "split-control PS specialization failed");
        splitSource = frame + splitSource;
        ok(D3DCompile(splitSource.data(),splitSource.size(),nullptr,nullptr,nullptr,"PixelMain","ps_4_0",0,0,&code,&errors));
        const std::string splitCompute = noDerivatives + splitSource;
        compiled = D3DCompile(splitCompute.data(),splitCompute.size(),nullptr,nullptr,nullptr,"ComputeMain","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> splitShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&splitShader));
        std::vector<Pixel> colourOnly = banks;
        for(unsigned i=0;i<16;++i) colourOnly[4*16+i]=colourOnly[13*16+i]=Pixel{0,0,1,0};
        for(unsigned i=0;i<18;++i)bankData[i]={colourOnly.data()+16*i,4*sizeof(Pixel),0};
        ComPtr<ID3D11Texture2D> colourTexture;ok(device->CreateTexture2D(&td,bankData,&colourTexture));
        ComPtr<ID3D11ShaderResourceView> colourView;ok(device->CreateShaderResourceView(colourTexture.Get(),nullptr,&colourView));
        D3D11_TEXTURE2D_DESC cd=td; cd.ArraySize=2; D3D11_SUBRESOURCE_DATA controlData[2]={{banks.data()+4*16,4*sizeof(Pixel),0},{banks.data()+13*16,4*sizeof(Pixel),0}};
        ComPtr<ID3D11Texture2D> controlTexture;ok(device->CreateTexture2D(&cd,controlData,&controlTexture));
        ComPtr<ID3D11ShaderResourceView> controlView;ok(device->CreateShaderResourceView(controlTexture.Get(),nullptr,&controlView));
        context->CSSetShader(splitShader.Get(),nullptr,0);
        ID3D11ShaderResourceView* splitViews[]={colourView.Get()};context->CSSetShaderResources(0,1,splitViews);
        ID3D11ShaderResourceView* controlViews[]={controlView.Get()};context->CSSetShaderResources(4,1,controlViews);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        for(UINT i=0;i<count;++i)for(unsigned c=0;c<4;++c)
            check(std::abs((&values[i].r)[c]-(&combined[i].r)[c])<1e-5f,"split control array shaded differently from bank slices");
        context->Unmap(staging.Get(),0);
        std::string eightTess = tessDefines + TerrainPaint::LayerHlsl(eight) + TerrainPaint::DetileHlsl() + tessRaw + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestEight(uint3 id : SV_DispatchThreadID)
{ testResults[id.x] = float4(TerrainPaintRelief(float2(1.3 + 9.1 * id.x, 0.7 + 4.3 * id.x)), 0); }
)";
        compiled = D3DCompile(eightTess.data(),eightTess.size(),nullptr,nullptr,nullptr,"TestEight","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        // The domain's relief agrees between bank control slices (t127) and
        // the split control array (t126) beside a colour array without them.
        // Heights on layers zero and five so the relief moves.
        TerrainPaint::Config eightHeight = eight; eightHeight.heightMeters = {1,0,0,0,0,2,0,0};
        const std::string reliefTess = tessDefines + TerrainPaint::LayerHlsl(eightHeight) + TerrainPaint::DetileHlsl() + tessRaw + R"(
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)] void TestEight(uint3 id : SV_DispatchThreadID)
{ testResults[id.x] = float4(TerrainPaintRelief(float2(1.3 + 9.1 * id.x, 0.7 + 4.3 * id.x)), 0); }
)";
        ComPtr<ID3D11ComputeShader> reliefShader, splitReliefShader;
        compiled = D3DCompile(reliefTess.data(),reliefTess.size(),nullptr,nullptr,nullptr,"TestEight","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&reliefShader));
        const std::string splitTess = "#define OPENSHIM_PAINT_CONTROL_SPLIT 1\n" + reliefTess;
        compiled = D3DCompile(splitTess.data(),splitTess.size(),nullptr,nullptr,nullptr,"TestEight","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&splitReliefShader));
        std::vector<Pixel> relief(count);
        ID3D11ShaderResourceView* bankTess[]={eightView.Get()};context->CSSetShaderResources(127,1,bankTess);
        context->CSSetShader(reliefShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));
        std::memcpy(relief.data(),mapped.pData,count*sizeof(Pixel));context->Unmap(staging.Get(),0);
        ID3D11ShaderResourceView* splitTessViews[]={controlView.Get(),colourView.Get()};context->CSSetShaderResources(126,2,splitTessViews);
        context->CSSetShader(splitReliefShader.Get(),nullptr,0);
        dispatch();ok(context->Map(staging.Get(),0,D3D11_MAP_READ,0,&mapped));values=static_cast<const Pixel*>(mapped.pData);
        bool reliefMoved=false;
        for(UINT i=0;i<count;++i)
        {
            for(unsigned c=0;c<3;++c) check(std::abs((&values[i].r)[c]-(&relief[i].r)[c])<1e-4f,"split control relief differs from bank slices");
            reliefMoved = reliefMoved || std::abs(relief[i].r)>1e-3f;
        }
        context->Unmap(staging.Get(),0);
        check(reliefMoved,"eight-layer relief stayed flat, so the split comparison proves nothing");
        // The adaptive hull reads both control banks for its relief scale.
        const std::string adaptiveHull = "#define OPENSHIM_TESS_ADAPTIVE 1\n#define OPENSHIM_TESS_FACTOR 8\n"
            "static const float openShimPaintReliefMeters[8] = {1,0,0,0,0,2,0,0};\n" + eightTess;
        for (const char* stage : {"TerrainHull", "TerrainDomain"})
        {
            compiled = D3DCompile(adaptiveHull.data(),adaptiveHull.size(),nullptr,nullptr,nullptr,stage,
                stage[7] == 'H' ? "hs_5_0" : "ds_5_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
            const std::string splitHull = "#define OPENSHIM_PAINT_CONTROL_SPLIT 1\n" + adaptiveHull;
            compiled = D3DCompile(splitHull.data(),splitHull.size(),nullptr,nullptr,nullptr,stage,
                stage[7] == 'H' ? "hs_5_0" : "ds_5_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
        }
        // Relief bake: the kernel stores relief and the hull's relief scale on
        // the finest vertex lattice, texel (i,j) at bounds.xy + (i,j) * 5/7 m
        // (factor 8 adaptive, 7 segments), in an RGBA16F target; the BAKED
        // DS/HS read it back bilinearly. Varied control and heights over the
        // slope test's bounds, 8 m repeats so the layer texels (2 m) are
        // coarser than the bake spacing. Sizing and the spacing define as native.
        TerrainPaint::Config bakedHeight = eightHeight; bakedHeight.repeatMeters = {8,8,8,8,8,8,8,8};
        const float bakeSpacing = 5.0f / 7.0f;
        const auto bakeSize = BZROpenShim::TerrainHeight::SizeReliefBake(93, 55, bakeSpacing);
        const UINT bakeWidth = bakeSize.width, bakeHeight = bakeSize.height;
        std::ostringstream spacingDefine; spacingDefine.imbue(std::locale::classic());
        spacingDefine << std::setprecision(9) << std::scientific << "#define OPENSHIM_RELIEF_BAKE_SPACING " << bakeSpacing << "\n";
        const std::string bakeTess = spacingDefine.str() + "#define OPENSHIM_RELIEF_TEST 1\n#define OPENSHIM_RELIEF_AMPLITUDE 100\n#define OPENSHIM_TERRAIN_HD 1\n"
            "#define OPENSHIM_PAINT_HEIGHT 1\n#define OPENSHIM_PAINT_BOUNDS float4(-3,-5,90,50)\n#define OPENSHIM_PAINT_HEIGHT_SCALE 1\n"
            "#define OPENSHIM_PAINT_CONTROL_SPLIT 1\n#define OPENSHIM_TESS_ADAPTIVE 1\n#define OPENSHIM_TESS_FACTOR 8\n"
            "static const float openShimPaintReliefMeters[8] = {1,0,0,0,0,2,0,0};\n" +
            TerrainPaint::LayerHlsl(bakedHeight) + TerrainPaint::DetileHlsl() + TerrainPaint::CraterHlsl() + tessRaw;
        const std::string bakeKernel = "#define OPENSHIM_PAINT_BAKE 1\n" + bakeTess;
        compiled = D3DCompile(bakeKernel.data(),bakeKernel.size(),nullptr,nullptr,nullptr,"TerrainReliefBake","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> bakeShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&bakeShader));
        const std::string bakedTess = "#define OPENSHIM_PAINT_BAKED 1\n" + bakeTess;
        for (const char* stage : {"TerrainHull", "TerrainDomain"})
        {
            compiled = D3DCompile(bakedTess.data(),bakedTess.size(),nullptr,nullptr,nullptr,stage,
                stage[7] == 'H' ? "hs_5_0" : "ds_5_0",0,0,&code,&errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
        }
        // Direct relief + scale and the baked sample, side by side: the first
        // 4096 points sit on the bake lattice (the finest integer-partitioned
        // vertices), the rest anywhere in bounds (adaptive fractional vertices).
        constexpr UINT parityPoints = 8192, centrePoints = 4096;
        const std::string parityKernel = bakedTess + R"(
RWStructuredBuffer<float4> parityResults : register(u0);
[numthreads(64,1,1)] void TestBaked(uint3 id : SV_DispatchThreadID)
{ uint width, height; terrainReliefBaked.GetDimensions(width, height);
  float2 span = OPENSHIM_PAINT_BOUNDS.zw - OPENSHIM_PAINT_BOUNDS.xy, xz;
  if (id.x < 4096) xz = OPENSHIM_PAINT_BOUNDS.xy + float2((id.x * 7) % width, (id.x * 13) % height) * OPENSHIM_RELIEF_BAKE_SPACING;
  else { float k = float(id.x - 4096); xz = OPENSHIM_PAINT_BOUNDS.xy + frac(float2(k * 0.6180339887, k * 0.7548776662) + 0.1234) * span; }
  parityResults[id.x * 2] = float4(TerrainPaintRelief(xz), TerrainPaintReliefScale(xz));
  parityResults[id.x * 2 + 1] = TerrainReliefBakedSample(xz); }
)";
        compiled = D3DCompile(parityKernel.data(),parityKernel.size(),nullptr,nullptr,nullptr,"TestBaked","cs_5_0",0,0,&code,&errors);
        if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
        ok(compiled);
        ComPtr<ID3D11ComputeShader> parityShader;
        ok(device->CreateComputeShader(code->GetBufferPointer(),code->GetBufferSize(),nullptr,&parityShader));
        std::vector<Pixel> bakeBanks = colourOnly, bakeControl(2*16);
        for (unsigned i=0;i<16;++i)
        {
            for (unsigned l=0;l<8;++l) bakeBanks[(l/4*9+5+l%4)*16+i].a = float((i*(l+3)+l)%16)/15;
            const float t = float((i*5)%16)/15;
            bakeControl[i] = {1-t, 0, 0, 0}; bakeControl[16+i] = {0, t, 0, 0}; // layers 0 and 5
        }
        for(unsigned i=0;i<18;++i)bankData[i]={bakeBanks.data()+16*i,4*sizeof(Pixel),0};
        ComPtr<ID3D11Texture2D> bakePaintTexture;ok(device->CreateTexture2D(&td,bankData,&bakePaintTexture));
        ComPtr<ID3D11ShaderResourceView> bakePaintView;ok(device->CreateShaderResourceView(bakePaintTexture.Get(),nullptr,&bakePaintView));
        controlData[0]={bakeControl.data(),4*sizeof(Pixel),0}; controlData[1]={bakeControl.data()+16,4*sizeof(Pixel),0};
        ComPtr<ID3D11Texture2D> bakeControlTexture;ok(device->CreateTexture2D(&cd,controlData,&bakeControlTexture));
        ComPtr<ID3D11ShaderResourceView> bakeControlView;ok(device->CreateShaderResourceView(bakeControlTexture.Get(),nullptr,&bakeControlView));
        D3D11_TEXTURE2D_DESC bd2={}; bd2.Width=bakeWidth; bd2.Height=bakeHeight; bd2.MipLevels=bd2.ArraySize=bd2.SampleDesc.Count=1;
        bd2.Format=DXGI_FORMAT_R16G16B16A16_FLOAT; bd2.BindFlags=D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_UNORDERED_ACCESS;
        ComPtr<ID3D11Texture2D> bakeTexture;ok(device->CreateTexture2D(&bd2,nullptr,&bakeTexture));
        ComPtr<ID3D11ShaderResourceView> bakeView;ok(device->CreateShaderResourceView(bakeTexture.Get(),nullptr,&bakeView));
        ComPtr<ID3D11UnorderedAccessView> bakeTarget;ok(device->CreateUnorderedAccessView(bakeTexture.Get(),nullptr,&bakeTarget));
        ID3D11ShaderResourceView* bakeInputs[]={bakeControlView.Get(),bakePaintView.Get()};context->CSSetShaderResources(126,2,bakeInputs);
        context->CSSetShader(bakeShader.Get(),nullptr,0);
        ID3D11UnorderedAccessView* bakeWrite=bakeTarget.Get();context->CSSetUnorderedAccessViews(0,1,&bakeWrite,nullptr);
        context->Dispatch((bakeWidth+7)/8,(bakeHeight+7)/8,1);
        bakeWrite=nullptr;context->CSSetUnorderedAccessViews(0,1,&bakeWrite,nullptr);
        D3D11_BUFFER_DESC pd={};pd.ByteWidth=parityPoints*2*sizeof(Pixel);pd.StructureByteStride=sizeof(Pixel);
        pd.Usage=D3D11_USAGE_DEFAULT;pd.BindFlags=D3D11_BIND_UNORDERED_ACCESS;pd.MiscFlags=D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        ComPtr<ID3D11Buffer> parityOutput;ok(device->CreateBuffer(&pd,nullptr,&parityOutput));
        ComPtr<ID3D11UnorderedAccessView> parityUav;ok(device->CreateUnorderedAccessView(parityOutput.Get(),nullptr,&parityUav));
        pd.Usage=D3D11_USAGE_STAGING;pd.BindFlags=pd.MiscFlags=pd.StructureByteStride=0;pd.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
        ComPtr<ID3D11Buffer> parityStaging;ok(device->CreateBuffer(&pd,nullptr,&parityStaging));
        ID3D11ShaderResourceView* bakedRead[]={bakeView.Get()};context->CSSetShaderResources(125,1,bakedRead);
        context->CSSetShader(parityShader.Get(),nullptr,0);
        ID3D11UnorderedAccessView* parityWrite=parityUav.Get();context->CSSetUnorderedAccessViews(0,1,&parityWrite,nullptr);
        context->Dispatch(parityPoints/64,1,1);
        parityWrite=nullptr;context->CSSetUnorderedAccessViews(0,1,&parityWrite,nullptr);
        context->CopyResource(parityStaging.Get(),parityOutput.Get());
        ok(context->Map(parityStaging.Get(),0,D3D11_MAP_READ,0,&mapped));
        std::vector<Pixel> parity(parityPoints*2); std::memcpy(parity.data(),mapped.pData,parity.size()*sizeof(Pixel));
        context->Unmap(parityStaging.Get(),0);
        ID3D11ShaderResourceView* noBake[3]={}; context->CSSetShaderResources(125,3,noBake);
        // fp16 keeps 11 significant bits (relative step 2^-11 ~ 4.9e-4).
        const auto halfTolerance = [](float v) { return std::abs(v) * 1e-3f + 1e-3f; };
        float slopeMax = 0, centreH = 0, centreScale = 0, centreSlope = 0, offH = 0, offHSum = 0, offSlope = 0, offSlopeSum = 0, offDirectSlopeSum = 0, offScale = 0, heightRange = 0;
        for (UINT i=0;i<parityPoints;++i)
        {
            const Pixel& direct = parity[i*2]; const Pixel& baked = parity[i*2+1];
            slopeMax = (std::max)(slopeMax, std::hypot(direct.g, direct.b));
            heightRange = (std::max)(heightRange, std::abs(direct.r));
            const float dh = std::abs(baked.r - direct.r), ds = std::abs(baked.a - direct.a);
            const float dslope = std::hypot(baked.g - direct.g, baked.b - direct.b);
            if (i < centrePoints)
            {
                check(dh <= halfTolerance(direct.r), "baked relief differs from direct on the vertex lattice");
                check(ds <= halfTolerance(direct.a), "baked relief scale differs from direct on the vertex lattice");
                check(dslope <= halfTolerance(std::hypot(direct.g, direct.b)), "baked slope differs from direct on the vertex lattice");
                centreH = (std::max)(centreH, dh); centreScale = (std::max)(centreScale, ds); centreSlope = (std::max)(centreSlope, dslope);
            }
            else
            {
                offH = (std::max)(offH, dh); offHSum += dh; offSlope = (std::max)(offSlope, dslope); offSlopeSum += dslope;
                offDirectSlopeSum += std::hypot(direct.g, direct.b);
                offScale = (std::max)(offScale, ds);
            }
        }
        check(heightRange > 0.5f && slopeMax > 0.1f, "relief bake test ground is flat, so parity proves nothing");
        // Off the lattice: bilinear is a convex mix of the four surrounding
        // texels, each within sqrt(2) * spacing of the point, and the relief is
        // continuous with slope at most slopeMax, so the mix errs by at most
        // sqrt(2) * spacing * slopeMax plus fp16 rounding. slopeMax is sampled,
        // so it carries a 25% margin for the slope peak between samples.
        const float offBound = std::sqrt(2.0f) * bakeSpacing * slopeMax * 1.25f + halfTolerance(heightRange);
        check(offH <= offBound, "baked relief error off texel centres exceeds the bilinear bound");
        // Slope is interpolated separately from height, so it jumps across layer
        // texel edges: measured max 1.93 (slopeMax 2.01), mean 0.114, scale max
        // 0.0034. The max check is only a sanity check (it passes even for a
        // zero-slope bake); the mean check is the real one, tied to the mean
        // direct slope so a bake with no slope fails it.
        const float slopeBound = slopeMax * 1.25f + halfTolerance(slopeMax);
        check(offSlope <= slopeBound, "baked slope error off the lattice exceeds its sanity bound");
        const float offSlopeMean = offSlopeSum / (parityPoints - centrePoints), offDirectSlopeMean = offDirectSlopeSum / (parityPoints - centrePoints);
        check(offDirectSlopeMean > 0.25f, "relief bake test ground has too little slope for the mean slope check");
        check(offSlopeMean <= 0.5f * offDirectSlopeMean, "baked slope error off the lattice drifted on average");
        check(offScale <= 0.01f, "baked relief scale error off the lattice exceeds its bound");
        std::cout << "relief bake " << bakeWidth << "x" << bakeHeight << " spacing=" << bakeSpacing << " m slopeMax=" << slopeMax
            << " |h|max=" << heightRange << "\n  lattice max |dh|=" << centreH << " |dslope|=" << centreSlope << " |dscale|=" << centreScale
            << "\n  off-lattice |dh| max=" << offH << " mean=" << offHSum / (parityPoints - centrePoints) << " bound=" << offBound
            << "\n  off-lattice |dslope| max=" << offSlope << " mean=" << offSlopeMean << " (mean direct |slope|=" << offDirectSlopeMean << ")"
            << " |dscale| max=" << offScale << "\n";
        std::cout<<"PASS: relief bake (vertex-lattice parity, bilinear bound, adaptive scale, BAKED DS/HS), split control array (pixel and domain parity), eight-layer banks and adaptive hull, close-up parallax, distance scale, macro variation and crater variants, crater and detail slopes, detile pixel/domain parity, triplanar walls and flat ground, native PS4 compilation, material slices, height-aware blend, four GPU layers, soft blends, edge clamp, normalisation, opaque output and explicit repetition\n";
        return 0;
    }
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
