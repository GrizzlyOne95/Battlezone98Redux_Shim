// Execute the shipped PN-triangle smoothing (TerrainTessellationSmoothing) in
// the hull/domain stages on D3D11 WARP. Two patches share a diagonal in
// opposite directions, as the native quad split and cluster seams do. Every
// sample on that edge must come out bit-identical from both patches (no
// crack), corners must stay put, the lift must stay within OPENSHIM_PN_LIFT,
// and smoothing must actually move the surface. Fixed and adaptive
// (fractional_even) partitioning are both run.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl/client.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
using Microsoft::WRL::ComPtr;
static void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
static void ok(HRESULT result) { check(SUCCEEDED(result), "D3D11 smoothing test failed"); }
struct Sample { float view[3], normal[3], bary[3], patch; };
static_assert(sizeof(Sample) == 10 * sizeof(float));

static const char* g_lift = "1.0";
static ComPtr<ID3DBlob> compile(const std::string& source, const char* entry, const char* profile, bool adaptive)
{
    std::vector<D3D_SHADER_MACRO> macros = {{"OPENSHIM_RELIEF_TEST","1"},{"OPENSHIM_RELIEF_AMPLITUDE","0"},
        {"OPENSHIM_TESS_FACTOR","4"},{"OPENSHIM_TESS_SMOOTH","1"},{"OPENSHIM_PN_LIFT",g_lift}};
    if (adaptive) { macros.push_back({"OPENSHIM_TESS_ADAPTIVE","1"}); macros.push_back({"OPENSHIM_TESS_TARGET_PIXELS","12"}); }
    macros.push_back({nullptr,nullptr});
    ComPtr<ID3DBlob> code, errors;
    // No IEEE strictness flag: the shader's own `precise` must be enough.
    const HRESULT hr = D3DCompile(source.data(), source.size(), nullptr, macros.data(), nullptr, entry, profile,
        D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &code, &errors);
    if (FAILED(hr) && errors) std::cerr << static_cast<const char*>(errors->GetBufferPointer());
    ok(hr); return code;
}

// Identity relief matrices (view == world, clip == view) and a viewport that
// gives fractional adaptive factors on the shared edge.
static ComPtr<ID3D11Buffer> globals(ID3D11Device* device, ID3DBlob* code)
{
    ComPtr<ID3D11ShaderReflection> reflection;
    ok(D3DReflect(code->GetBufferPointer(), code->GetBufferSize(), IID_ID3D11ShaderReflection, &reflection));
    auto* block = reflection->GetConstantBufferByName("$Globals");
    D3D11_SHADER_BUFFER_DESC desc{};
    if (FAILED(block->GetDesc(&desc))) return nullptr;
    std::vector<unsigned char> bytes((desc.Size + 15) & ~15u);
    for (UINT i = 0; i < desc.Variables; ++i)
    {
        D3D11_SHADER_VARIABLE_DESC variable{}; ok(block->GetVariableByIndex(i)->GetDesc(&variable));
        check(variable.StartOffset + variable.Size <= bytes.size(), "globals reflection out of range");
        if (std::strncmp(variable.Name, "relief", 6) == 0)
        {
            check(variable.Size == 64, "relief matrix contract changed");
            const float identity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
            std::memcpy(bytes.data() + variable.StartOffset, identity, 64);
        }
        else if (std::strcmp(variable.Name, "tessViewport") == 0)
        {
            const float viewport[4] = {97, 97, 1.0f / 97, 1.0f / 97};
            std::memcpy(bytes.data() + variable.StartOffset, viewport, 16);
        }
    }
    D3D11_BUFFER_DESC buffer{}; buffer.ByteWidth = static_cast<UINT>(bytes.size());
    buffer.Usage = D3D11_USAGE_IMMUTABLE; buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    D3D11_SUBRESOURCE_DATA data{bytes.data(), 0, 0}; ComPtr<ID3D11Buffer> result;
    ok(device->CreateBuffer(&buffer, &data, &result)); return result;
}

static const float kWorld[4][3] = {{0,0,0},{5,2,0},{5,3,5},{0,-1,5}};

static void run(ID3D11Device* device, ID3D11DeviceContext* context, const std::string& source, bool adaptive)
{
    auto vs = compile(source, "TestVertex", "vs_5_0", adaptive), hs = compile(source, "TerrainHull", "hs_5_0", adaptive);
    auto ds = compile(source, "TerrainDomain", "ds_5_0", adaptive), gs = compile(source, "Capture", "gs_5_0", adaptive);
    ComPtr<ID3D11VertexShader> vertex; ComPtr<ID3D11HullShader> hull; ComPtr<ID3D11DomainShader> domain; ComPtr<ID3D11GeometryShader> capture;
    ok(device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &vertex));
    ok(device->CreateHullShader(hs->GetBufferPointer(), hs->GetBufferSize(), nullptr, &hull));
    ok(device->CreateDomainShader(ds->GetBufferPointer(), ds->GetBufferSize(), nullptr, &domain));
    const D3D11_SO_DECLARATION_ENTRY entries[] = {{0,"TEXCOORD",0,0,3,0},{0,"TEXCOORD",1,0,3,0},
        {0,"TEXCOORD",2,0,3,0},{0,"TEXCOORD",3,0,1,0}};
    const UINT stride = sizeof(Sample);
    ok(device->CreateGeometryShaderWithStreamOutput(gs->GetBufferPointer(), gs->GetBufferSize(), entries, 4,
        &stride, 1, D3D11_SO_NO_RASTERIZED_STREAM, nullptr, &capture));
    auto hsGlobals = globals(device, hs.Get()), dsGlobals = globals(device, ds.Get());
    check(dsGlobals != nullptr, "domain relief matrices missing");
    ID3D11Buffer* bind = hsGlobals.Get(); context->HSSetConstantBuffers(0, 1, &bind);
    bind = dsGlobals.Get(); context->DSSetConstantBuffers(0, 1, &bind);
    context->IASetInputLayout(nullptr);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
    context->VSSetShader(vertex.Get(), nullptr, 0); context->HSSetShader(hull.Get(), nullptr, 0);
    context->DSSetShader(domain.Get(), nullptr, 0); context->GSSetShader(capture.Get(), nullptr, 0);
    context->PSSetShader(nullptr, nullptr, 0);
    D3D11_BUFFER_DESC desc{}; desc.ByteWidth = sizeof(Sample) * 3 * 512; desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_STREAM_OUTPUT;
    ComPtr<ID3D11Buffer> output, staging; ok(device->CreateBuffer(&desc, nullptr, &output));
    desc.Usage = D3D11_USAGE_STAGING; desc.BindFlags = 0; desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    ok(device->CreateBuffer(&desc, nullptr, &staging));
    UINT offset = 0; ID3D11Buffer* so = output.Get(); context->SOSetTargets(1, &so, &offset);
    D3D11_QUERY_DESC queryDesc{D3D11_QUERY_SO_STATISTICS, 0}; ComPtr<ID3D11Query> query;
    ok(device->CreateQuery(&queryDesc, &query));
    context->Begin(query.Get()); context->Draw(6, 0); context->End(query.Get());
    so = nullptr; context->SOSetTargets(1, &so, &offset);
    D3D11_QUERY_DATA_SO_STATISTICS stats{};
    int polls = 0;
    while (context->GetData(query.Get(), &stats, sizeof(stats), 0) == S_FALSE && ++polls < 1000000) {}
    check(polls < 1000000, "stream-out query timed out");
    check(stats.NumPrimitivesWritten > 2 && stats.NumPrimitivesWritten <= 512, "tessellated patches not captured");
    context->CopyResource(staging.Get(), output.Get());
    D3D11_MAPPED_SUBRESOURCE mapped{}; ok(context->Map(staging.Get(), 0, D3D11_MAP_READ, 0, &mapped));
    const auto* samples = static_cast<const Sample*>(mapped.pData);
    const size_t count = static_cast<size_t>(stats.NumPrimitivesWritten) * 3;
    // Corners in patch order: A = (v0, v1, v2), B = (v0, v2, v3).
    const int corners[2][3] = {{0,1,2},{0,2,3}};
    std::vector<const Sample*> edge[2];
    float maxLift = 0.0f, maxEdgeLift = 0.0f;
    for (size_t i = 0; i < count; ++i)
    {
        const Sample& s = samples[i];
        const int patch = static_cast<int>(s.patch);
        check(patch == 0 || patch == 1, "unexpected patch id");
        float flat[3] = {};
        for (int c = 0; c < 3; ++c) for (int k = 0; k < 3; ++k) flat[k] += s.bary[c] * kWorld[corners[patch][c]][k];
        for (int k = 0; k < 3; ++k) check(std::isfinite(s.view[k]) && std::isfinite(s.normal[k]), "non-finite smoothing output");
        check(std::fabs(s.view[0] - flat[0]) < 1e-4f && std::fabs(s.view[2] - flat[2]) < 1e-4f,
            "smoothing moved a sample horizontally");
        const float lift = s.view[1] - flat[1];
        check(std::fabs(lift) <= std::stof(g_lift) + 1e-4f, "smoothing exceeded OPENSHIM_PN_LIFT");
        const float n = std::sqrt(s.normal[0]*s.normal[0] + s.normal[1]*s.normal[1] + s.normal[2]*s.normal[2]);
        check(std::fabs(n - 1.0f) < 1e-3f && s.normal[1] > 0.0f, "smoothed normal not a unit up-facing normal");
        int atCorner = -1;
        for (int c = 0; c < 3; ++c) if (s.bary[c] == 1.0f) atCorner = c;
        if (atCorner >= 0) check(std::fabs(lift) < 1e-5f, "smoothing moved a patch corner");
        maxLift = (std::max)(maxLift, std::fabs(lift));
        // Shared diagonal v0-v2: A's third (v1) and B's third (v3) weight is 0.
        const bool shared = patch == 0 ? s.bary[1] == 0.0f : s.bary[2] == 0.0f;
        if (shared) { edge[patch].push_back(&s); maxEdgeLift = (std::max)(maxEdgeLift, std::fabs(lift)); }
    }
    check(edge[0].size() >= 3 && edge[1].size() >= 3, "shared-edge samples missing");
    for (const Sample* a : edge[0])
    {
        bool matched = false;
        for (const Sample* b : edge[1])
            if (std::memcmp(a->view, b->view, sizeof(a->view)) == 0 && std::memcmp(a->normal, b->normal, sizeof(a->normal)) == 0)
                matched = true;
        if (!matched)
        {
            std::cerr << "unmatched shared-edge sample " << a->view[0] << ',' << a->view[1] << ',' << a->view[2] << '\n';
            throw std::runtime_error(adaptive ? "adaptive shared edge differs between patches" : "fixed shared edge differs between patches");
        }
    }
    check(maxEdgeLift > 0.01f && maxLift > 0.01f, "smoothing left the surface flat");
    if (std::stof(g_lift) < 0.5f) check(maxLift > std::stof(g_lift) - 1e-4f, "tight lift bound never engaged");
    context->Unmap(staging.Get(), 0);
    std::cout << (adaptive ? "adaptive" : "fixed") << ": " << count << " samples, " << edge[0].size()
              << " shared-edge samples bit-identical, max lift " << maxLift << '\n';
}

int main()
{
    try
    {
        std::ifstream file(TERRAIN_TESS_SHADER_PATH, std::ios::binary);
        std::string source((std::istreambuf_iterator<char>(file)), {});
        check(!source.empty(), "shipped terrain shader missing");
        source += R"(
static const float3 testWorld[4] = { float3(0,0,0), float3(5,2,0), float3(5,3,5), float3(0,-1,5) };
// Stock-like 1-ring normals of a rolling surface; v0 and v2 lean apart so the
// shared diagonal bulges.
static const float3 testNormal[4] = { float3(-0.35,1,-0.2), float3(-0.1,1,0.25), float3(0.3,1,-0.15), float3(0.2,1,0.4) };
static const uint testIndex[6] = { 0,1,2, 0,2,3 };
TerrainTessVertex TestVertex(uint id : SV_VertexID) {
    TerrainTessVertex v = (TerrainTessVertex)0;
    uint corner = testIndex[id];
    float3 w = testWorld[corner];
    v.viewPosition = w;
    v.normal = normalize(testNormal[corner]);
    v.position = float4(w.x * 0.1 - 0.25, w.z * 0.1 - 0.25, 0.5, 1);
    v.color = float4(id % 3 == 0, id % 3 == 1, id % 3 == 2, id / 3); // barycentric and patch tags
    v.depth = 0.5;
    return v;
}
struct TestSample { float3 view : TEXCOORD0; float3 normal : TEXCOORD1; float3 bary : TEXCOORD2; float patch : TEXCOORD3; };
[maxvertexcount(3)]
void Capture(triangle TerrainTessVertex input[3], inout TriangleStream<TestSample> output) {
    for (uint i = 0; i < 3; ++i) {
        TestSample s; s.view = input[i].viewPosition; s.normal = input[i].normal;
        s.bary = input[i].color.xyz; s.patch = round(input[i].color.w); output.Append(s);
    }
}
)";
        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context; D3D_FEATURE_LEVEL level;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context));
        check(level >= D3D_FEATURE_LEVEL_11_0, "WARP feature level 11 required");
        run(device.Get(), context.Get(), source, false);
        run(device.Get(), context.Get(), source, true);
        // A tight bound must clamp (and the clamped edge must still agree).
        g_lift = "0.25";
        run(device.Get(), context.Get(), source, true);
        std::cout << "PASS: PN smoothing shared edges bit-identical, corners fixed, lift bounded, vertical only\n";
        return 0;
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
