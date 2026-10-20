// Owned domain-only texture binding. The existing exact renderer/terrain gates
// qualify shader creation; the public D3D11 shader setter is the lifetime seam.
using Microsoft::WRL::ComPtr;
std::mutex g_heightMutex;
std::atomic<bool> g_heightHookReady{false};
std::atomic<bool> g_heightActive{false};
TerrainHeight::DomainBinding g_heightBinding;

void RestoreTerrainHeightTexture()
{
    std::lock_guard<std::mutex> lock(g_heightMutex);
    g_heightActive.store(false);
    g_heightBinding.RestoreSlot();
    if (g_heightBinding.view)
        LogShimA(LogLevel::Info, "terrain-height", "[TERRAIN-HEIGHT] released domains=%zu binds=%llu restores=%llu", g_heightBinding.domains.size(), g_heightBinding.binds, g_heightBinding.restores);
    g_heightBinding.Reset();
}

void PrepareTerrainHeightTexture(ID3D11Buffer* source, const std::string& relativePath)
{
    if (!g_heightHookReady.load()) throw std::runtime_error("domain texture lifetime hook unavailable");
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
