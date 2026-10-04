// Execute the shipped HLSL function on Microsoft's software D3D11 device.
// Check bounds, fixed terrain coordinates, duplicate seam coordinates, and
// analytic normals against finite differences of actual GPU height samples.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
using Microsoft::WRL::ComPtr;
struct Point { float x, z, eyeX, eyeZ; };
struct Result { float height, dx, dz, unused; };
static void check(bool value, const char* message)
{
    if (!value) throw std::runtime_error(message);
}
static void ok(HRESULT result) { check(SUCCEEDED(result), "D3D11 test operation failed"); }

int main()
{
    try
    {
        std::ifstream file(TERRAIN_TESS_SHADER_PATH, std::ios::binary);
        std::string source((std::istreambuf_iterator<char>(file)), {});
        check(!source.empty(), "shipped terrain shader missing");
        source += R"(
StructuredBuffer<float4> testPoints : register(t0);
RWStructuredBuffer<float4> testResults : register(u0);
[numthreads(1,1,1)]
void TestRelief(uint3 id : SV_DispatchThreadID)
{
    float4 p = testPoints[id.x];
    // A translated cluster and rotated/moving camera. The world-view
    // combination is unchanged by Ogre's camera-origin subtraction.
    float3 world = float3(p.x+320,0,p.y-640);
    float3 eye = float3(p.z,1,p.w);
    float3 viewPosition = (world-eye).yzx;
    float4x4 inverseWorldView = float4x4(
        0,0,1,eye.x-320, 1,0,0,eye.y, 0,1,0,eye.z+640, 0,0,0,1);
    float2 fixedXZ = TerrainReliefObjectXZ(viewPosition, inverseWorldView);
    testResults[id.x] = float4(TerrainMicroRelief(fixedXZ),0);
}
)";
        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> context;
        D3D_FEATURE_LEVEL level;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0,
            D3D11_SDK_VERSION, &device, &level, &context));
        check(level >= D3D_FEATURE_LEVEL_11_0, "WARP tessellation feature level unavailable");
        const float epsilon = 0.02f;
        std::vector<Point> points;
        for (float origin : {0.0f, -640.0f, 4800.0f})
        for (float distance : {0.0f, 3.0f, 39.0f, 40.0f, 60.0f, 90.0f, 119.0f, 120.0f, 150.0f})
        {
            Point p = {origin + distance, origin + 2.0f, origin, origin + 2.0f};
            points.push_back(p);
            points.push_back({p.x + epsilon, p.z, p.eyeX, p.eyeZ});
            points.push_back({p.x - epsilon, p.z, p.eyeX, p.eyeZ});
            points.push_back({p.x, p.z + epsilon, p.eyeX, p.eyeZ});
            points.push_back({p.x, p.z - epsilon, p.eyeX, p.eyeZ});
            points.push_back({p.x + 320.0f, p.z - 320.0f, p.eyeX + 77.0f, p.eyeZ - 23.0f}); // neighboring cluster, different camera
        }
        D3D11_BUFFER_DESC inputDesc = {};
        inputDesc.ByteWidth = static_cast<UINT>(points.size() * sizeof(Point));
        inputDesc.Usage = D3D11_USAGE_IMMUTABLE;
        inputDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        inputDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        inputDesc.StructureByteStride = sizeof(Point);
        D3D11_SUBRESOURCE_DATA inputData = {points.data(), 0, 0};
        ComPtr<ID3D11Buffer> input;
        ok(device->CreateBuffer(&inputDesc, &inputData, &input));
        ComPtr<ID3D11ShaderResourceView> srv;
        ok(device->CreateShaderResourceView(input.Get(), nullptr, &srv));
        auto outputDesc = inputDesc;
        outputDesc.Usage = D3D11_USAGE_DEFAULT;
        outputDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
        ComPtr<ID3D11Buffer> output;
        ok(device->CreateBuffer(&outputDesc, nullptr, &output));
        ComPtr<ID3D11UnorderedAccessView> uav;
        ok(device->CreateUnorderedAccessView(output.Get(), nullptr, &uav));
        auto stagingDesc = outputDesc;
        stagingDesc.Usage = D3D11_USAGE_STAGING;
        stagingDesc.BindFlags = stagingDesc.MiscFlags = stagingDesc.StructureByteStride = 0;
        stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        ComPtr<ID3D11Buffer> staging;
        ok(device->CreateBuffer(&stagingDesc, nullptr, &staging));
        for (const char* amplitude : {"0.0", "0.25", "1.0"})
        {
            const D3D_SHADER_MACRO macros[] = {
                {"OPENSHIM_RELIEF_TEST", "1"}, {"OPENSHIM_RELIEF_AMPLITUDE", amplitude}, {nullptr, nullptr}};
            ComPtr<ID3DBlob> code, errors;
            const HRESULT compiled = D3DCompile(source.data(), source.size(), nullptr, macros, nullptr,
                "TestRelief", "cs_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &code, &errors);
            if (FAILED(compiled) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
            ok(compiled);
            ComPtr<ID3D11ComputeShader> shader;
            ok(device->CreateComputeShader(code->GetBufferPointer(), code->GetBufferSize(), nullptr, &shader));
            context->CSSetShader(shader.Get(), nullptr, 0);
            ID3D11ShaderResourceView* read = srv.Get();
            ID3D11UnorderedAccessView* write = uav.Get();
            context->CSSetShaderResources(0, 1, &read);
            context->CSSetUnorderedAccessViews(0, 1, &write, nullptr);
            context->Dispatch(static_cast<UINT>(points.size()), 1, 1);
            write = nullptr;
            context->CSSetUnorderedAccessViews(0, 1, &write, nullptr);
            context->CopyResource(staging.Get(), output.Get());
            D3D11_MAPPED_SUBRESOURCE mapped = {};
            ok(context->Map(staging.Get(), 0, D3D11_MAP_READ, 0, &mapped));
            const auto* values = static_cast<const Result*>(mapped.pData);
            const float bound = std::stof(amplitude);
            for (size_t i = 0; i < points.size(); i += 6)
            {
                const auto& v = values[i];
                check(std::isfinite(v.height) && std::isfinite(v.dx) && std::isfinite(v.dz), "nonfinite relief");
                check(std::abs(v.height) <= bound + 1e-6f, "displacement exceeded padded bounds");
                check(std::abs(v.height - values[i+5].height) < 0.0002f &&
                    std::abs(v.dx - values[i+5].dx) < 0.0002f &&
                    std::abs(v.dz - values[i+5].dz) < 0.0002f, "cluster seam/camera disagreement");
                const float dx = (values[i+1].height - values[i+2].height) / (points[i+1].x - points[i+2].x);
                const float dz = (values[i+3].height - values[i+4].height) / (points[i+3].z - points[i+4].z);
                check(std::abs(v.dx - dx) < 0.012f && std::abs(v.dz - dz) < 0.012f, "normal derivative differs from GPU height");
                // At a noise-cell boundary the quintic relief has zero
                // curvature. Cubic interpolation leaves a visible kink here.
                if (std::abs(std::remainder(points[i].x, 2.5f)) < 1e-5f)
                    check(std::abs((values[i+1].dx - v.dx) / (points[i+1].x - points[i].x)) < 0.1f,
                        "relief curvature kink at noise-cell boundary");
                if (bound == 0)
                    check(v.height == 0 && v.dx == 0 && v.dz == 0, "zero-amplitude fallback not flat");
            }
            context->Unmap(staging.Get(), 0);
        }
        std::cout << "PASS: shipped GPU relief bounds, fixed phase, seam agreement and normal derivatives\n";
        return 0;
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
