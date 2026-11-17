// Execute the shipped lattice smoothing (TerrainTessellationSmoothing) in the
// hull/domain stages on D3D11 WARP, in the paint-mode HD interface it needs
// (hdUV = native world XZ, tileSlice = native world Y). Two patches share a
// diagonal in opposite directions, as the native quad split does, with the
// shared edge on control-point slots 0-2/0-1 or on slots 1-2 in both. Samples
// on that edge must come out bit-identical from both patches, both ways (no
// crack), the offset must be vertical, match the CPU reference
// (include/terrain_lattice_smoothing.h) and stay within OPENSHIM_LATTICE_MAX,
// the normal must follow the blend between the stock and smoothed normals,
// and a flat lattice must not move at all. Fixed and adaptive partitioning,
// plus a run at a map-sized offset (2048) on texel 0, where Loads clamp at
// the texture edge and world coordinates are ~10 km.
#include "terrain_lattice_smoothing.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl/client.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
using Microsoft::WRL::ComPtr;
using namespace BZROpenShim;
static void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }
static void ok(HRESULT result) { check(SUCCEEDED(result), "D3D11 lattice smoothing test failed"); }
struct Sample { float view[3], normal[3], bary[3], patch; };
static_assert(sizeof(Sample) == 10 * sizeof(float));

constexpr int kSize = 8;
// Quad corners v0..v3 = base + (0,0), (1,0), (1,1), (0,1) in lattice texels.
static const int kQuad[4][2] = {{0,0},{1,0},{1,1},{0,1}};
// Patch corner orders (v indices). Order 0: A = (v0,v1,v2), B = (v0,v2,v3),
// shared v0-v2 on slots 0-2 / 0-1. Order 1: A = (v1,v0,v2), B = (v3,v0,v2),
// shared v0-v2 on slots 1-2 in both.
static const int kOrder[2][2][3] = {{{0,1,2},{0,2,3}}, {{1,0,2},{3,0,2}}};
// The slot whose weight is 0 on the shared edge, per order and patch.
static const int kOffEdgeSlot[2][2] = {{1,2},{0,0}};

struct Config
{
    bool adaptive = false;
    float max = 4.0f;
    bool flat = false;
    int order = 0;
    int base = 2;          // lattice texel of v0
    float offset = 2.0f;   // OPENSHIM_LATTICE_OFFSET.x and .y
};

static std::string Number(float value)
{
    std::string text = std::to_string(value);
    return text;
}

static ComPtr<ID3DBlob> compile(const std::string& source, const char* entry, const char* profile, const Config& c)
{
    const std::string max = Number(c.max), offset = "float2(" + Number(c.offset) + "," + Number(c.offset) + ")";
    const std::string base = std::to_string(c.base), order = std::to_string(c.order), offsetValue = Number(c.offset);
    std::vector<D3D_SHADER_MACRO> macros = {{"OPENSHIM_TERRAIN_HD","1"},{"OPENSHIM_RELIEF_TEST","1"},
        {"OPENSHIM_RELIEF_AMPLITUDE","0"},{"OPENSHIM_TESS_FACTOR","4"},{"OPENSHIM_LATTICE_SMOOTH","1"},
        {"OPENSHIM_LATTICE_MAX",max.c_str()},{"OPENSHIM_LATTICE_OFFSET",offset.c_str()},
        {"TEST_BASE",base.c_str()},{"TEST_ORDER",order.c_str()},{"TEST_OFFSET",offsetValue.c_str()}};
    if (c.adaptive) { macros.push_back({"OPENSHIM_TESS_ADAPTIVE","1"}); macros.push_back({"OPENSHIM_TESS_TARGET_PIXELS","12"}); }
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

static bool SameBits(const Sample* a, const Sample* b)
{
    return std::memcmp(a->view, b->view, sizeof(a->view)) == 0 && std::memcmp(a->normal, b->normal, sizeof(a->normal)) == 0;
}

static void run(ID3D11Device* device, ID3D11DeviceContext* context, const std::string& source,
    const TerrainLattice::Grid& grid, const Config& c)
{
    const float max = c.max;
    auto vs = compile(source, "TestVertex", "vs_5_0", c), hs = compile(source, "TerrainHull", "hs_5_0", c);
    auto ds = compile(source, "TerrainDomain", "ds_5_0", c), gs = compile(source, "Capture", "gs_5_0", c);
    ComPtr<ID3D11VertexShader> vertex; ComPtr<ID3D11HullShader> hull; ComPtr<ID3D11DomainShader> domain; ComPtr<ID3D11GeometryShader> capture;
    ok(device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &vertex));
    ok(device->CreateHullShader(hs->GetBufferPointer(), hs->GetBufferSize(), nullptr, &hull));
    ok(device->CreateDomainShader(ds->GetBufferPointer(), ds->GetBufferSize(), nullptr, &domain));
    const D3D11_SO_DECLARATION_ENTRY entries[] = {{0,"TEXCOORD",0,0,3,0},{0,"TEXCOORD",1,0,3,0},
        {0,"TEXCOORD",2,0,3,0},{0,"TEXCOORD",3,0,1,0}};
    const UINT stride = sizeof(Sample);
    ok(device->CreateGeometryShaderWithStreamOutput(gs->GetBufferPointer(), gs->GetBufferSize(), entries, 4,
        &stride, 1, D3D11_SO_NO_RASTERIZED_STREAM, nullptr, &capture));

    // The lattice exactly as the installer uploads it: R16_UINT, DEFAULT, t126.
    D3D11_TEXTURE2D_DESC textureDesc{};
    textureDesc.Width = textureDesc.Height = kSize;
    textureDesc.MipLevels = textureDesc.ArraySize = textureDesc.SampleDesc.Count = 1;
    textureDesc.Format = DXGI_FORMAT_R16_UINT; textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA texels{grid.units.data(), kSize * 2, 0};
    ComPtr<ID3D11Texture2D> texture; ComPtr<ID3D11ShaderResourceView> view;
    ok(device->CreateTexture2D(&textureDesc, &texels, &texture));
    ok(device->CreateShaderResourceView(texture.Get(), nullptr, &view));
    ID3D11ShaderResourceView* lattice = view.Get();
    context->VSSetShaderResources(126, 1, &lattice); // the test VS reads corner heights from it
    context->DSSetShaderResources(126, 1, &lattice);

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

    float world[4][3];
    for (int v = 0; v < 4; ++v)
    {
        const int tx = c.base + kQuad[v][0], tz = c.base + kQuad[v][1];
        world[v][0] = 5.0f * (float(tx) - c.offset);
        world[v][1] = grid(tx, tz);
        world[v][2] = -5.0f * (float(tz) - c.offset);
    }
    // World coordinates ~10 km carry ~1e-3 m float error, i.e. ~4e-4 texel
    // in the shader's lattice coordinate; heights then differ by slope x that.
    const float worldScale = (std::max)(std::fabs(world[0][0]), std::fabs(world[0][2])) + 10.0f;
    const float horizontal = (std::max)(1e-4f, worldScale * 4e-7f);
    const float texelError = worldScale * 0.2f * 4e-7f;
    std::vector<const Sample*> edge[2];
    float maxLift = 0.0f, maxEdgeLift = 0.0f, maxError = 0.0f;
    for (size_t i = 0; i < count; ++i)
    {
        const Sample& s = samples[i];
        const int patch = static_cast<int>(s.patch);
        check(patch == 0 || patch == 1, "unexpected patch id");
        float linear[3] = {}, gx = 0.0f, gz = 0.0f;
        for (int k = 0; k < 3; ++k)
        {
            const int v = kOrder[c.order][patch][k];
            for (int j = 0; j < 3; ++j) linear[j] += s.bary[k] * world[v][j];
            gx += s.bary[k] * float(c.base + kQuad[v][0]);
            gz += s.bary[k] * float(c.base + kQuad[v][1]);
        }
        for (int k = 0; k < 3; ++k) check(std::isfinite(s.view[k]) && std::isfinite(s.normal[k]), "non-finite smoothing output");
        check(std::fabs(s.view[0] - linear[0]) < horizontal && std::fabs(s.view[2] - linear[2]) < horizontal,
            "smoothing moved a sample horizontally");
        const float lift = s.view[1] - linear[1];
        check(std::fabs(lift) <= max + 1e-4f, "smoothing exceeded OPENSHIM_LATTICE_MAX");
        // CPU reference at the same lattice point (from the barycentrics).
        auto reference = TerrainLattice::Evaluate(grid, gx, gz);
        const float delta = reference.h - linear[1];
        const float expected = TerrainLattice::Delta(reference.h, linear[1], max);
        const float tolerance = 2e-3f + (std::fabs(reference.dx) + std::fabs(reference.dz)) * texelError;
        maxError = (std::max)(maxError, std::fabs(lift - expected));
        check(std::fabs(lift - expected) < tolerance, "GPU smoothing differs from the CPU reference");
        const float n = std::sqrt(s.normal[0]*s.normal[0] + s.normal[1]*s.normal[1] + s.normal[2]*s.normal[2]);
        check(std::fabs(n - 1.0f) < 1e-3f && s.normal[1] > 0.0f, "smoothed normal not a unit up-facing normal");
        // Stock normal (0,1,0) blended toward the smoothed surface normal over
        // the last quarter of the bound: weight 1 well inside, 0 at the clamp.
        {
            const float w = std::clamp((max - std::fabs(delta)) / (0.25f * max), 0.0f, 1.0f);
            // World slopes: lattice x follows +X, lattice z runs toward -Z, 5 m texels.
            const float dx = reference.dx * 0.2f, dz = -reference.dz * 0.2f;
            const float length = std::sqrt(dx * dx + 1.0f + dz * dz);
            const float smooth[3] = {-dx / length, 1.0f / length, -dz / length};
            float blended[3] = {w * smooth[0], (1.0f - w) + w * smooth[1], w * smooth[2]};
            const float b = std::sqrt(blended[0]*blended[0] + blended[1]*blended[1] + blended[2]*blended[2]);
            // Near the blend ends GPU/CPU delta rounding moves w slightly.
            for (int k = 0; k < 3; ++k)
                check(std::fabs(s.normal[k] - blended[k] / b) < 3e-2f, "normal does not follow the stock/smoothed blend");
        }
        int atCorner = -1;
        for (int k = 0; k < 3; ++k) if (s.bary[k] == 1.0f) atCorner = k;
        if (atCorner >= 0)
            check(std::fabs(lift) < 1e-4f + (std::fabs(reference.dx) + std::fabs(reference.dz)) * texelError,
                "smoothing moved a lattice sample");
        maxLift = (std::max)(maxLift, std::fabs(lift));
        if (c.flat) check(lift == 0.0f, "flat lattice moved");
        if (s.bary[kOffEdgeSlot[c.order][patch]] == 0.0f)
        {
            edge[patch].push_back(&s);
            maxEdgeLift = (std::max)(maxEdgeLift, std::fabs(lift));
        }
    }
    check(edge[0].size() >= 3 && edge[1].size() >= 3, "shared-edge samples missing");
    // Two-way: every shared-edge sample of each patch has a bit-identical twin
    // in the other patch.
    for (int from = 0; from < 2; ++from)
        for (const Sample* a : edge[from])
        {
            const auto& other = edge[1 - from];
            if (std::none_of(other.begin(), other.end(), [a](const Sample* b) { return SameBits(a, b); }))
            {
                std::cerr << "unmatched shared-edge sample (patch " << from << ") " << a->view[0] << ',' << a->view[1] << ',' << a->view[2] << '\n';
                throw std::runtime_error(c.adaptive ? "adaptive shared edge differs between patches" : "fixed shared edge differs between patches");
            }
        }
    if (!c.flat)
    {
        check(maxEdgeLift > 0.01f && maxLift > 0.01f, "smoothing left the surface flat");
        if (max < 1.0f) check(maxLift > max - 1e-4f, "tight lattice bound never engaged");
    }
    context->Unmap(staging.Get(), 0);
    ID3D11ShaderResourceView* none = nullptr;
    context->VSSetShaderResources(126, 1, &none); context->DSSetShaderResources(126, 1, &none);
    std::cout << (c.flat ? "flat " : "") << (c.adaptive ? "adaptive" : "fixed") << " max=" << max << " order=" << c.order
              << " base=" << c.base << " offset=" << c.offset << ": " << count
              << " samples, " << edge[0].size() << '/' << edge[1].size() << " shared-edge samples bit-identical both ways, max lift "
              << maxLift << ", max CPU difference " << maxError << '\n';
}

int main()
{
    try
    {
        std::ifstream file(TERRAIN_TESS_SHADER_PATH, std::ios::binary);
        std::string source((std::istreambuf_iterator<char>(file)), {});
        check(!source.empty(), "shipped terrain shader missing");
        check(source.find("OPENSHIM_LATTICE_SMOOTH") != std::string::npos, "shader lacks the lattice smoothing token");
        source += R"(
static const int2 testQuad[4] = { int2(0,0), int2(1,0), int2(1,1), int2(0,1) };
#if TEST_ORDER == 0
static const uint testIndex[6] = { 0,1,2, 0,2,3 };
#else
static const uint testIndex[6] = { 1,0,2, 3,0,2 };
#endif
TerrainTessVertex TestVertex(uint id : SV_VertexID) {
    TerrainTessVertex v = (TerrainTessVertex)0;
    uint corner = testIndex[id];
    uint width, height;
    terrainLattice.GetDimensions(width, height);
    int2 c = int2(TEST_BASE, TEST_BASE) + testQuad[corner];
    // Native frame: X = 5 (x - offset), Z = -5 (z - offset), Y = the sample.
    float3 w = float3(5.0 * (c.x - TEST_OFFSET), TerrainLatticeFetch(c.x, c.y, int2(width, height)), -5.0 * (c.y - TEST_OFFSET));
    v.viewPosition = w;
    v.hdUV = w.xz;
    v.tileSlice = w.y;
    v.normal = float3(0, 1, 0);
    float2 q = float2(testQuad[corner]);
    v.position = float4(q.x * 0.5 - 0.25, q.y * 0.5 - 0.25, 0.5, 1);
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
        // A rolling patch of ground (0 to 30 m) whose diagonal bulges away
        // from the flat triangles, and a flat one.
        TerrainLattice::Grid rolling{kSize, kSize, std::vector<uint16_t>(kSize * kSize)};
        for (int z = 0; z < kSize; ++z)
        for (int x = 0; x < kSize; ++x)
            rolling.units[z * kSize + x] = uint16_t((x * x * 37 + z * z * 53 + x * z * 11) % 300);
        TerrainLattice::Grid flat{kSize, kSize, std::vector<uint16_t>(kSize * kSize, 1000)};

        ComPtr<ID3D11Device> device; ComPtr<ID3D11DeviceContext> context; D3D_FEATURE_LEVEL level;
        ok(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &device, &level, &context));
        check(level >= D3D_FEATURE_LEVEL_11_0, "WARP feature level 11 required");
        for (int order : {0, 1})
        {
            run(device.Get(), context.Get(), source, rolling, Config{false, 4.0f, false, order});
            run(device.Get(), context.Get(), source, rolling, Config{true, 4.0f, false, order});
            // A tight bound must clamp (and the clamped edge must still agree).
            run(device.Get(), context.Get(), source, rolling, Config{true, 0.5f, false, order});
        }
        run(device.Get(), context.Get(), source, flat, Config{true, 4.0f, true});
        // Map-sized offset, patch on texel 0: the Loads at x/z = -1 clamp to
        // the edge and world coordinates are ~10 km (precision).
        for (int order : {0, 1})
            run(device.Get(), context.Get(), source, rolling, Config{true, 4.0f, false, order, 0, 2048.0f});
        std::cout << "PASS: lattice smoothing shared edges bit-identical both ways (two slot orders), matches the CPU reference, "
                     "bounded, vertical only, normal blend, flat unchanged, edge clamping at a 2048 offset\n";
        return 0;
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
