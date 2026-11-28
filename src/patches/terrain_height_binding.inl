// Owned domain-only texture binding. The existing exact renderer/terrain gates
// qualify shader creation; the public D3D11 shader setter is the lifetime seam.
using Microsoft::WRL::ComPtr;
std::mutex g_heightMutex;
std::atomic<bool> g_heightHookReady{false};
std::atomic<bool> g_heightActive{false};
TerrainHeight::DomainBinding g_heightBinding;
// Optional relief bake: the paint relief evaluated once per paint change into
// a texture the owned DS/HS read at t125 (g_heightBinding.bakedView), instead
// of the full layer evaluation per tessellated vertex. Under g_heightMutex.
TerrainHeight::ReliefBake g_reliefBake;
// Atomic only: live paint uploads set it under g_mutex, which must not take
// g_heightMutex (lock order).
std::atomic<bool> g_reliefBakeDirty{false};

void RestoreTerrainHeightTexture()
{
    std::lock_guard<std::mutex> lock(g_heightMutex);
    g_heightActive.store(false);
    g_heightBinding.RestoreSlot();
    if (g_heightBinding.view)
        LogShimA(LogLevel::Info, "terrain-height", "[TERRAIN-HEIGHT] released domains=%zu binds=%llu restores=%llu bakes=%llu", g_heightBinding.domains.size(), g_heightBinding.binds, g_heightBinding.restores, g_reliefBake.dispatches);
    g_heightBinding.Reset();
    g_reliefBake = {};
    g_reliefBakeDirty.store(false);
}

void RequireTerrainHeightHook(ID3D11DeviceChild* resource)
{
    if (!g_heightHookReady.load() && resource)
    {
        ComPtr<ID3D11Device> device; resource->GetDevice(&device);
        EnsureTerrainHeightDomainHook(device.Get());
    }
    if (!g_heightHookReady.load()) throw std::runtime_error("domain texture lifetime hook unavailable");
}

void PrepareTerrainHeightTexture(ID3D11Buffer* source, const std::string& relativePath)
{
    RequireTerrainHeightHook(source);
    const std::filesystem::path relative{std::u8string(relativePath.begin(), relativePath.end())};
    if (relative.empty() || relative.has_root_path()) throw std::runtime_error("height path must be pack-relative");
    for (const auto& component : relative)
        if (component == "..") throw std::runtime_error("height path escapes pack");
    const auto path = g_hdManifest.path.parent_path() / relative;
    std::ifstream input(path, std::ios::binary | std::ios::ate);
    const auto length = input.tellg();
    if (!input || length < 128 || length > 128 + 4096 * 4096 * 4)
        throw std::runtime_error("height DDS missing or oversized");
    std::vector<uint8_t> bytes(static_cast<size_t>(length));
    input.seekg(0); input.read(reinterpret_cast<char*>(bytes.data()), bytes.size());
    if (!input) throw std::runtime_error("height DDS read failed");
    const auto image = TerrainHeight::Decode(bytes);
    ComPtr<ID3D11Device> device; source->GetDevice(&device);
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = image.width; desc.Height = image.height;
    desc.MipLevels = desc.ArraySize = desc.SampleDesc.Count = 1;
    desc.Format = DXGI_FORMAT_R32_FLOAT;
    desc.Usage = D3D11_USAGE_IMMUTABLE; desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA data{image.values.data(), image.width * 4, 0};
    ComPtr<ID3D11Texture2D> texture;
    ComPtr<ID3D11ShaderResourceView> view;
    if (!device || FAILED(device->CreateTexture2D(&desc, &data, &texture)) ||
        FAILED(device->CreateShaderResourceView(texture.Get(), nullptr, &view)))
        throw std::runtime_error("height GPU resource creation failed");
    std::lock_guard<std::mutex> lock(g_heightMutex);
    g_heightBinding.view = view;
    LogShimA(LogLevel::Info, "terrain-height", "[TERRAIN-HEIGHT] texture ready path=\"%s\" size=%ux%u format=R32_FLOAT signed-unit mip=0", path.string().c_str(), image.width, image.height);
}

// Full-material paint packs displace from the live paint arrays themselves:
// second views of the owned Ogre textures (colour/normal+height at t127, the
// split control array at t126), released with the binding.
void PrepareTerrainPaintHeightTexture(ID3D11Texture2D* paintArray, ID3D11Texture2D* controlArray)
{
    if (!paintArray) throw std::runtime_error("paint array texture unavailable");
    if (!controlArray) throw std::runtime_error("paint control array texture unavailable");
    RequireTerrainHeightHook(paintArray);
    D3D11_TEXTURE2D_DESC desc{}, controlDesc{}; paintArray->GetDesc(&desc); controlArray->GetDesc(&controlDesc);
    if ((desc.ArraySize != 9 && desc.ArraySize != 18) || !(desc.BindFlags & D3D11_BIND_SHADER_RESOURCE))
        throw std::runtime_error("paint array is not a 9- or 18-slice shader resource");
    if (controlDesc.ArraySize != desc.ArraySize / 9 || !(controlDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE))
        throw std::runtime_error("paint control array does not hold one slice per bank");
    ComPtr<ID3D11Device> device; paintArray->GetDevice(&device);
    ComPtr<ID3D11ShaderResourceView> view, controlView;
    if (!device || FAILED(device->CreateShaderResourceView(paintArray, nullptr, &view)) ||
        FAILED(device->CreateShaderResourceView(controlArray, nullptr, &controlView)))
        throw std::runtime_error("paint height view creation failed");
    std::lock_guard<std::mutex> lock(g_heightMutex);
    g_heightBinding.view = view;
    g_heightBinding.controlView = controlView;
    g_reliefBakeDirty.store(true);
    LogShimA(LogLevel::Info, "terrain-height", "[TERRAIN-HEIGHT] paint array view ready size=%ux%u slices=%u mips=%u format=%d control=%ux%u slices=%u format=%d",
        desc.Width, desc.Height, desc.ArraySize, desc.MipLevels, int(desc.Format),
        controlDesc.Width, controlDesc.Height, controlDesc.ArraySize, int(controlDesc.Format));
}

// Compiles the bake kernel from the full paint DS source and sizes its target
// on the finest tessellated vertex lattice over the paint bounds. Returns the
// spacing define the BAKED DS/HS need. Throws, so the tessellation install
// declines rather than running the direct path.
std::string PrepareTerrainReliefBake(ID3D11DeviceChild* resource, const std::string& source,
    const std::array<float, 4>& bounds, float spacing)
{
    ComPtr<ID3D11Device> device; if (resource) resource->GetDevice(&device);
    if (!device) throw std::runtime_error("relief bake device unavailable");
    const float spanX = bounds[2] - bounds[0], spanZ = bounds[3] - bounds[1];
    if (!std::isfinite(spanX) || !std::isfinite(spanZ) || spanX <= 0.0f || spanZ <= 0.0f ||
        !std::isfinite(spacing) || spacing <= 0.0f)
        throw std::runtime_error("relief bake bounds/spacing invalid");
    const auto size = TerrainHeight::SizeReliefBake(spanX, spanZ, spacing);
    const UINT width = size.width, height = size.height;
    const double step = size.step;
    if (size.capped)
        LogShimA(LogLevel::Warn, "terrain-height", "[TERRAIN-HEIGHT] relief bake capped at 4096 texels: spacing %.4f -> %.4f (off the vertex lattice)",
            double(spacing), step);
    std::ostringstream define; define.imbue(std::locale::classic());
    define << std::setprecision(9) << std::scientific << "#define OPENSHIM_RELIEF_BAKE_SPACING " << float(step) << "\n";
    const std::string kernel = define.str() + source;
    // Optional compiler, as in the frame bridge: no new eager DLL import.
    const HMODULE compiler = LoadLibraryExW(L"d3dcompiler_47.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!compiler) throw std::runtime_error("relief bake compiler unavailable");
    ComPtr<ID3DBlob> bytecode, errors;
    const auto compile = reinterpret_cast<decltype(&D3DCompile)>(GetProcAddress(compiler, "D3DCompile"));
    HRESULT hr = compile ? compile(kernel.data(), kernel.size(), "openshim_terrain_relief_bake",
        nullptr, nullptr, "TerrainReliefBake", "cs_5_0", 0, 0, &bytecode, &errors) : E_NOINTERFACE;
    std::string message = errors ? std::string(static_cast<const char*>(errors->GetBufferPointer()),
        strnlen(static_cast<const char*>(errors->GetBufferPointer()), errors->GetBufferSize())) : std::string();
    ComPtr<ID3D11ComputeShader> shader;
    if (SUCCEEDED(hr))
        hr = device->CreateComputeShader(bytecode->GetBufferPointer(), bytecode->GetBufferSize(), nullptr, &shader);
    bytecode.Reset(); errors.Reset(); // blobs die before their module
    FreeLibrary(compiler);
    if (FAILED(hr))
    {
        char code[16]; snprintf(code, sizeof code, "0x%08lX", static_cast<unsigned long>(hr));
        throw std::runtime_error(std::string("relief bake compile failed hr=") + code +
            (message.empty() ? "" : ": " + message.substr(0, 512)));
    }
    D3D11_TEXTURE2D_DESC desc{};
    desc.Width = width; desc.Height = height;
    desc.MipLevels = desc.ArraySize = desc.SampleDesc.Count = 1;
    desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    ComPtr<ID3D11Texture2D> texture;
    ComPtr<ID3D11ShaderResourceView> view;
    ComPtr<ID3D11UnorderedAccessView> target;
    if (FAILED(device->CreateTexture2D(&desc, nullptr, &texture)) ||
        FAILED(device->CreateShaderResourceView(texture.Get(), nullptr, &view)) ||
        FAILED(device->CreateUnorderedAccessView(texture.Get(), nullptr, &target)))
        throw std::runtime_error("relief bake GPU resource creation failed");
    std::lock_guard<std::mutex> lock(g_heightMutex);
    g_reliefBake.shader = shader; g_reliefBake.texture = texture; g_reliefBake.target = target;
    g_reliefBake.width = width; g_reliefBake.height = height; g_reliefBake.dispatches = 0;
    g_heightBinding.bakedView = view;
    g_reliefBakeDirty.store(true);
    LogShimA(LogLevel::Info, "terrain-height", "[TERRAIN-HEIGHT] relief bake ready size=%ux%u spacing=%.4f format=R16G16B16A16_FLOAT mb=%.2f",
        width, height, step, double(width) * height * 8.0 / (1024.0 * 1024.0));
    return define.str();
}

// Caller holds g_heightMutex. The save/bind/dispatch/restore body lives in
// terrain_height_domain_binding.h so the GPU tests run the real code.
void DispatchTerrainReliefBake(ID3D11DeviceContext* context, ID3D11DomainShader* shader)
{
    if (!TerrainHeight::DispatchReliefBake(g_reliefBake, g_heightBinding, g_reliefBakeDirty, context, shader)) return;
    LogShimA(LogLevel::Info, "terrain-height", "[TERRAIN-HEIGHT] relief baked dispatch=%llu groups=%ux%u",
        g_reliefBake.dispatches, (g_reliefBake.width + 7) / 8, (g_reliefBake.height + 7) / 8);
}

void RegisterTerrainHeightDomain(void* program)
{
    using Getter = ID3D11DomainShader* (__thiscall*)(void*);
    auto get = Resolve<Getter>(GetModuleHandleW(L"RenderSystem_Direct3D11.dll"),
        "?getDomainShader@D3D11HLSLProgram@Ogre@@QBEPAUID3D11DomainShader@@XZ");
    auto* shader = get ? get(program) : nullptr;
    if (!shader) throw std::runtime_error("owned domain shader identity unavailable");
    std::lock_guard<std::mutex> lock(g_heightMutex);
    g_heightBinding.domains.emplace_back(shader); // acquire own reference to borrowed getter
    g_heightActive.store(true);
}
