// Bounded GPU evidence, using the existing terrain topology observer.
// The immediate context owns command ordering; pending queries never flush/wait.
struct TerrainTessQuery
{
    ID3D11Query* query = nullptr;
    bool attempted = false;
    bool ended = false;
    unsigned polls = 0;
    unsigned attempts = 0;
    unsigned skipCandidates = 0;
};
TerrainTessQuery g_TessQueries[2]; // one ordinary draw and one tessellated draw
bool g_TessStatisticsEnabled = false;
std::mutex g_TessQueryMutex;

void PollTerrainTessQueries(ID3D11DeviceContext* context)
{
    if (context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE) return;
    for (unsigned kind = 0; kind < 2; ++kind)
    {
        auto& sample = g_TessQueries[kind];
        if (!sample.query || !sample.ended) continue;
        D3D11_QUERY_DATA_PIPELINE_STATISTICS data = {};
        const HRESULT result = context->GetData(sample.query, &data, sizeof(data),
                                                D3D11_ASYNC_GETDATA_DONOTFLUSH);
        if (result == S_OK)
        {
            LogShimA(LogLevel::Info, "terrain-tess",
                "[TERRAIN-TESS] GPU statistics tessellated=%u iaPrimitives=%llu hsInvocations=%llu dsInvocations=%llu clipPrimitives=%llu psInvocations=%llu",
                kind, data.IAPrimitives, data.HSInvocations, data.DSInvocations, data.CPrimitives, data.PSInvocations);
            // A native submission can be completely clipped. Try a bounded
            // number of other clusters rather than accepting that as pixels.
            if (kind == 1 && (data.CPrimitives < 128 || data.PSInvocations < 1024) && sample.attempts < 16)
            {
                sample.attempted = false;
                // Do not repeatedly sample the first (often occluded) cluster
                // in the next frame. Advance through later terrain operations.
                sample.skipCandidates = sample.attempts * 8;
            }
        }
        if (result != S_FALSE || ++sample.polls >= 10000)
        {
            if (result != S_OK)
                LogShimA(LogLevel::Warn, "terrain-tess",
                    "[TERRAIN-TESS] GPU statistics unavailable hr=0x%08X polls=%u", result, sample.polls);
            sample.query->Release();
            sample.query = nullptr;
        }
    }
}

ID3D11Query* BeginTerrainTessQuery(ID3D11DeviceContext* context, UINT count,
                                  UINT start, INT base)
{
    if (!g_TessStatisticsEnabled || g_ShutdownRequested.load() ||
        context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE)
        return nullptr;
    if (count != kTerrainExpectedIndexCount || start != 0 || base != 0)
        return nullptr;
    D3D11_PRIMITIVE_TOPOLOGY topology;
    context->IAGetPrimitiveTopology(&topology);
    const unsigned kind = topology == D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST ? 1 : 0;
    if ((kind == 0 && topology != D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ||
        g_TessQueries[kind].attempted)
        return nullptr;
    // Shadow/depth-only submissions cannot establish a visible terrain test.
    // Sample a color pass with a pixel shader and an actual render target.
    ID3D11PixelShader* pixel = nullptr;
    ID3D11RenderTargetView* color = nullptr;
    context->PSGetShader(&pixel, nullptr, nullptr);
    context->OMGetRenderTargets(1, &color, nullptr);
    D3D11_RENDER_TARGET_VIEW_DESC colorDesc = {};
    if (color) color->GetDesc(&colorDesc);
    // Redux's shadow maps can have both a PS and a single-channel color
    // target. Limit this evidence lane to normal RGBA scene targets.
    const bool sceneFormat = colorDesc.Format == DXGI_FORMAT_R16G16B16A16_FLOAT ||
        colorDesc.Format == DXGI_FORMAT_R8G8B8A8_UNORM ||
        colorDesc.Format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB ||
        colorDesc.Format == DXGI_FORMAT_B8G8R8A8_UNORM ||
        colorDesc.Format == DXGI_FORMAT_B8G8R8A8_UNORM_SRGB ||
        colorDesc.Format == DXGI_FORMAT_R10G10B10A2_UNORM;
    const bool colorPass = pixel && color && sceneFormat;
    if (pixel) pixel->Release();
    if (color) color->Release();
    if (!colorPass) return nullptr;
    ID3D11Buffer* buffers[3] = {};
    UINT strides[3] = {}, offsets[3] = {};
    context->IAGetVertexBuffers(0, 3, buffers, strides, offsets);
    bool terrain = strides[0] == 16 && strides[1] == 4 && strides[2] == 4;
    for (unsigned i = 0; i < 3; ++i)
    {
        if (!buffers[i]) { terrain = false; continue; }
        D3D11_BUFFER_DESC desc = {};
        buffers[i]->GetDesc(&desc);
        terrain &= offsets[i] == 0 && desc.ByteWidth >= kTerrainExpectedVertexCount * strides[i];
        buffers[i]->Release();
    }
    if (!terrain) return nullptr;
    ID3D11Buffer* indices = nullptr;
    DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    UINT indexOffset = 0;
    context->IAGetIndexBuffer(&indices, &format, &indexOffset);
    if (!indices) return nullptr;
    D3D11_BUFFER_DESC indexDesc = {};
    indices->GetDesc(&indexDesc);
    indices->Release();
    if (format != DXGI_FORMAT_R16_UINT || indexOffset != 0 ||
        indexDesc.ByteWidth != kTerrainExpectedIndexCount * sizeof(uint16_t))
        return nullptr;
    ID3D11HullShader* hull = nullptr;
    ID3D11DomainShader* domain = nullptr;
    context->HSGetShader(&hull, nullptr, nullptr);
    context->DSGetShader(&domain, nullptr, nullptr);
    const bool bound = hull && domain;
    if (hull) hull->Release();
    if (domain) domain->Release();
    if ((kind == 1) != bound) return nullptr;
    auto& sample = g_TessQueries[kind];
    if (sample.skipCandidates)
    {
        --sample.skipCandidates;
        return nullptr;
    }
    sample.attempted = true;
    sample.ended = false;
    sample.polls = 0;
    ++sample.attempts;
    ID3D11Device* device = nullptr;
    context->GetDevice(&device);
    if (!device) return nullptr;
    const D3D11_QUERY_DESC desc = { D3D11_QUERY_PIPELINE_STATISTICS, 0 };
    const HRESULT result = device->CreateQuery(&desc, &sample.query);
    device->Release();
    if (FAILED(result))
    {
        LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] query creation failed hr=0x%08X", result);
        return nullptr;
    }
    LogShimA(LogLevel::Info, "terrain-tess",
        "[TERRAIN-TESS] sampling native submission tessellated=%u indices=%u topology=%u hullDomainBound=%d colorFormat=%u",
        kind, count, static_cast<unsigned>(topology), bound ? 1 : 0, static_cast<unsigned>(colorDesc.Format));
    context->Begin(sample.query);
    return sample.query;
}

// Ogre selects topology after binding the complete terrain operation, directly
// before its draw. Close the query at the next topology selection. This covers
// that submission without overwriting optimized/foreign COM draw wrappers.
ID3D11Query* g_ActiveTessQuery = nullptr;
ID3D11DeviceContext* g_ActiveTessContext = nullptr;
void ObserveTerrainTessTopology(ID3D11DeviceContext* context)
{
    std::lock_guard<std::mutex> lock(g_TessQueryMutex);
    if (g_ShutdownRequested.load()) return;
    if (context->GetType() != D3D11_DEVICE_CONTEXT_IMMEDIATE) return;
    if (g_ActiveTessQuery)
    {
        if (context != g_ActiveTessContext) return;
        context->End(g_ActiveTessQuery);
        for (auto& sample : g_TessQueries)
            if (sample.query == g_ActiveTessQuery) sample.ended = true;
        g_ActiveTessQuery = nullptr;
        g_ActiveTessContext->Release();
        g_ActiveTessContext = nullptr;
    }
    PollTerrainTessQueries(context);
    g_ActiveTessQuery = BeginTerrainTessQuery(context, kTerrainExpectedIndexCount, 0, 0);
    if (g_ActiveTessQuery)
    {
        context->AddRef();
        g_ActiveTessContext = context;
    }
}

void ReleaseTerrainTessQueries()
{
    std::lock_guard<std::mutex> lock(g_TessQueryMutex);
    // Shutdown only releases owned COM references; it issues no GPU commands.
    if (g_ActiveTessContext) g_ActiveTessContext->Release();
    g_ActiveTessContext = nullptr;
    g_ActiveTessQuery = nullptr;
    for (auto& sample : g_TessQueries)
    {
        if (sample.query) sample.query->Release();
        sample.query = nullptr;
    }
}
