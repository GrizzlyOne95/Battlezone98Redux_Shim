// Included inside terrain_proxy.cpp's private namespace, after the native HD
// path. TerrainTessellationSmoothing: an R16_UINT copy of the whole runtime
// height lattice for the terrain domain shader (slot 126, see
// terrain_height_domain_binding.h). Read-only: gameplay heights and native
// buffers are never written. include/terrain_lattice_smoothing.h holds the
// mapping and the CPU reference of the shader curve.
struct TerrainLatticeState
{
    TerrainLattice::Mapping mapping;
    int baseX = 0, baseZ = 0, minZoneX = 0, minZoneZ = 0;
    std::vector<uint16_t> units, scratch;
    ComPtr<ID3D11Texture2D> texture;
    ComPtr<ID3D11DeviceContext> context;
    bool active = false, readWarned = false, zoneWarned = false;
    uint64_t batches = 0, uploads = 0, texels = 0;
    uint64_t loggedBatches = 0;
    ULONGLONG lastLog = 0;
};
TerrainLatticeState g_Lattice;

// SEH around the engine height reader; keep C++ objects out of this frame.
// Writes out[(z - top) * pitch + (x - left)] for the half-open rectangle.
bool ReadTerrainLatticeRect(int baseX, int baseZ, int left, int top, int right, int bottom,
    uint16_t* out, int pitch)
{
    __try
    {
        for (int z = top; z < bottom; ++z)
        for (int x = left; x < right; ++x)
            out[std::size_t(z - top) * pitch + (x - left)] =
                uint16_t(g_heightAt(baseX + x, baseZ + z) & TerrainLattice::kHeightMask);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

void ReleaseTerrainLattice()
{
    {
        std::lock_guard<std::mutex> lock(g_heightMutex);
        if (g_heightBinding.lattice)
        {
            g_heightBinding.RestoreSlot();
            g_heightBinding.lattice.Reset();
        }
    }
    if (g_Lattice.active)
        LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] lattice smoothing released batches=%llu uploads=%llu texels=%llu",
            g_Lattice.batches, g_Lattice.uploads, g_Lattice.texels);
    g_Lattice = TerrainLatticeState{};
}

// Checks the documented lattice <-> world mapping against one cluster's
// native vertices: world XZ from POSITION plus the node translation (as paint
// mode feeds hdUV), world Y from the height stream (as it feeds tileSlice).
// With a window (the cluster's own ClusterWindow), every matched vertex's
// texel must also lie inside it, so the cluster sits where its zone and
// cluster coordinates say. Returns 1 verified, 0 too flat to tell, -1
// mismatch (error says why).
int VerifyTerrainLatticeCluster(const RenderOperation& operation, void* node,
    const TerrainLattice::Rect* window, std::string& error)
{
    void* positionBuffer = nullptr;
    void* heightBuffer = nullptr;
    std::vector<uint8_t> positions, heights;
    const auto* p = node ? g_ogre.getNodePosition(node) : nullptr;
    const uint32_t count = uint32_t(TerrainSemantic::kVertexCount);
    if (!p || !g_ogre.getVertexSize || !GetVertexBuffer(operation, 0, positionBuffer) ||
        g_ogre.getVertexSize(positionBuffer) != 16 || !ReadD3D11VertexBuffer(positionBuffer, count * 16, positions) ||
        !GetVertexBuffer(operation, 2, heightBuffer) || g_ogre.getVertexSize(heightBuffer) != 4 ||
        !ReadD3D11VertexBuffer(heightBuffer, count * 4, heights))
    {
        error = "cluster vertex streams unreadable";
        return -1;
    }
    const auto& m = g_Lattice.mapping;
    std::size_t checked = 0, mismatched = 0;
    float low = 1e30f, high = -1e30f;
    int minX = INT_MAX, maxX = INT_MIN, minZ = INT_MAX, maxZ = INT_MIN;
    for (uint32_t i = 0; i < count; ++i)
    {
        float x = 0, y = 0, z = 0;
        memcpy(&x, positions.data() + i * 16, 4); memcpy(&z, positions.data() + i * 16 + 8, 4);
        memcpy(&y, heights.data() + i * 4, 4);
        const float worldX = x + p->x, worldY = y + p->y, worldZ = z + p->z;
        const float gx = m.LatticeX(worldX), gz = m.LatticeZ(worldZ);
        if (!std::isfinite(gx) || !std::isfinite(gz) || !std::isfinite(worldY)) { ++mismatched; continue; }
        const float rx = std::round(gx), rz = std::round(gz);
        if (rx < 0 || rz < 0 || rx >= float(m.Width()) || rz >= float(m.Height())) continue;
        ++checked;
        const float expected = float(g_Lattice.units[std::size_t(rz) * m.Width() + std::size_t(rx)]) *
            TerrainLattice::kHeightUnitMeters;
        if (std::abs(gx - rx) > 1e-3f || std::abs(gz - rz) > 1e-3f || std::abs(expected - worldY) > 0.02f)
        {
            if (!mismatched)
                error = "vertex world (" + std::to_string(worldX) + "," + std::to_string(worldY) + "," +
                    std::to_string(worldZ) + ") lattice (" + std::to_string(gx) + "," + std::to_string(gz) +
                    ") sample " + std::to_string(expected);
            ++mismatched;
            continue;
        }
        low = (std::min)(low, worldY); high = (std::max)(high, worldY);
        minX = (std::min)(minX, int(rx)); maxX = (std::max)(maxX, int(rx));
        minZ = (std::min)(minZ, int(rz)); maxZ = (std::max)(maxZ, int(rz));
    }
    if (checked < 1000)
    {
        error = "only " + std::to_string(checked) + " cluster vertices inside the lattice";
        return -1;
    }
    // A few stale vertices (a deformation not yet uploaded) are tolerated; a
    // wrong mapping misses nearly everywhere the ground is not flat.
    if (mismatched * 100 > checked)
    {
        error = std::to_string(mismatched) + "/" + std::to_string(checked) + " vertices off the lattice, first " + error;
        return -1;
    }
    if (window && (minX < window->left || maxX >= window->right || minZ < window->top || maxZ >= window->bottom))
    {
        error = "cluster vertices at texels x " + std::to_string(minX) + ".." + std::to_string(maxX) + " z " +
            std::to_string(minZ) + ".." + std::to_string(maxZ) + " lie outside its window x " +
            std::to_string(window->left) + ".." + std::to_string(window->right - 1) + " z " +
            std::to_string(window->top) + ".." + std::to_string(window->bottom - 1) +
            " (zone/cluster coordinates disagree with the lattice mapping)";
        return -1;
    }
    return high - low >= 2.0f ? 1 : 0;
}

// The source cluster first, then others until one has relief to compare and
// one has passed its cluster window check. The source's window comes from
// the proxy selection; without one, another cluster must pass it.
void VerifyTerrainLatticeMapping(const RenderOperation& source)
{
    const auto& m = g_Lattice.mapping;
    std::string error;
    bool windowChecked = g_proxy.selected;
    TerrainLattice::Rect sourceWindow;
    if (windowChecked)
        sourceWindow = TerrainLattice::ClusterWindow(m, g_proxy.zoneX - g_Lattice.minZoneX,
            g_proxy.zoneZ - g_Lattice.minZoneZ, g_proxy.clusterX, g_proxy.clusterZ);
    int result = VerifyTerrainLatticeCluster(source, g_proxy.sourceNode, windowChecked ? &sourceWindow : nullptr, error);
    if (result < 0) throw std::runtime_error("lattice mapping check failed: " + error);
    int attempts = 0;
    for (auto zone = g_zoneOrdinals.begin(); (result == 0 || !windowChecked) && zone != g_zoneOrdinals.end() && attempts < 24; ++zone)
    {
        int zoneX = 0, zoneZ = 0;
        if (!SafeReadZoneInt(zone->first, kZoneXOffset, zoneX) || !SafeReadZoneInt(zone->first, kZoneZOffset, zoneZ))
            continue;
        for (int cluster = 5; cluster < 16 && (result == 0 || !windowChecked) && attempts < 24; cluster += 5)
        {
            ClusterCandidate candidate; bool abort = false;
            RenderOperation operation = {}; void* subEntity = nullptr;
            if (!ResolveClusterCandidate(zone->first, zoneX, zoneZ, cluster / 4, cluster % 4, candidate, abort) ||
                !GetEntityOperation(candidate.entity, operation, subEntity))
                continue;
            ++attempts;
            const TerrainLattice::Rect window = TerrainLattice::ClusterWindow(m, zoneX - g_Lattice.minZoneX,
                zoneZ - g_Lattice.minZoneZ, cluster / 4, cluster % 4);
            const int checked = VerifyTerrainLatticeCluster(operation, candidate.node, &window, error);
            if (checked < 0) throw std::runtime_error("lattice mapping check failed: " + error);
            windowChecked = true;
            result = (std::max)(result, checked);
        }
    }
    if (!windowChecked) throw std::runtime_error("lattice mapping unverified: no cluster passed its window check");
    if (result == 0) throw std::runtime_error("lattice mapping unverified: no cluster with relief to compare");
}

bool PrepareTerrainLatticeSmoothing(ID3D11Buffer* source, const RenderOperation& operation,
    bool shaderSupportsSmoothing, std::string& defines)
{
    defines.clear();
    ReleaseTerrainLattice();
    try
    {
        // The game loads the .hlsl from its own folder, not from the DLL.
        if (!shaderSupportsSmoothing)
        {
            LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] lattice smoothing off: the deployed openshim_terrain_tessellation_test.hlsl predates it (deploy openshim\\renderer\\enhanced with the DLL)");
            return false;
        }
        if (g_activeTerrainReliefAmplitude <= 0.0f) throw std::runtime_error("micro relief inactive");
        // Only paint mode carries native world XZ (hdUV) and world Y (tileSlice)
        // into the domain; other variants have cluster-local coordinates only.
        if (!g_HdActive || !g_HdPaint.enabled) throw std::runtime_error("needs an installed HD paint pack (native world XZ)");
        int originX = 0, originZ = 0;
        if (!g_heightAt || !SafeReadIntAddress(g_terrainOriginXVa, originX) || !SafeReadIntAddress(g_terrainOriginZVa, originZ))
            throw std::runtime_error("terrain height reader unavailable");
        const TerrainZoneRect rect = ReadTerrainZoneRect("lattice");
        TerrainLattice::Mapping mapping{rect.columns, rect.rows};
        if (mapping.Width() > TerrainLattice::kMaxTextureSize || mapping.Height() > TerrainLattice::kMaxTextureSize)
            throw std::runtime_error("map too large for the lattice texture");
        g_Lattice.mapping = mapping;
        g_Lattice.minZoneX = rect.minX; g_Lattice.minZoneZ = rect.minZ;
        g_Lattice.baseX = rect.minX * TerrainLattice::kZoneSamples + originX - 128;
        g_Lattice.baseZ = rect.minZ * TerrainLattice::kZoneSamples + originZ - 128;
        const int width = mapping.Width(), height = mapping.Height();
        g_Lattice.units.assign(std::size_t(width) * height, 0);
        if (!ReadTerrainLatticeRect(g_Lattice.baseX, g_Lattice.baseZ, 0, 0, width, height, g_Lattice.units.data(), width))
            throw std::runtime_error("terrain heights unreadable");
        VerifyTerrainLatticeMapping(operation);
        RequireTerrainHeightHook(source);
        ComPtr<ID3D11Device> device; source->GetDevice(&device);
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = UINT(width); desc.Height = UINT(height);
        desc.MipLevels = desc.ArraySize = desc.SampleDesc.Count = 1;
        desc.Format = DXGI_FORMAT_R16_UINT;
        desc.Usage = D3D11_USAGE_DEFAULT; desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        D3D11_SUBRESOURCE_DATA data{g_Lattice.units.data(), UINT(width) * 2, 0};
        ComPtr<ID3D11ShaderResourceView> view;
        if (!device || FAILED(device->CreateTexture2D(&desc, &data, &g_Lattice.texture)) ||
            FAILED(device->CreateShaderResourceView(g_Lattice.texture.Get(), nullptr, &view)))
            throw std::runtime_error("lattice GPU resource creation failed");
        device->GetImmediateContext(&g_Lattice.context);
        if (!g_Lattice.context) throw std::runtime_error("immediate context unavailable");
        {
            std::lock_guard<std::mutex> lock(g_heightMutex);
            g_heightBinding.lattice = view;
        }
        g_Lattice.active = true;
        const float max = g_config.tessellationSmoothingMax;
        std::ostringstream text; text.imbue(std::locale::classic()); text << std::setprecision(9) << std::fixed;
        text << "#define OPENSHIM_LATTICE_SMOOTH 1\n#define OPENSHIM_LATTICE_MAX " << max <<
            "\n#define OPENSHIM_LATTICE_OFFSET float2(" << mapping.OffsetX() << "," << mapping.OffsetZ() << ")\n";
        defines = text.str();
        LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] lattice smoothing installed size=%dx%d max=%.2f",
            width, height, max);
        LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] lattice mapping zones=%dx%d minZone=(%d,%d) base=(%d,%d) offset=(%.1f,%.1f) format=R16_UINT slot=%u",
            rect.columns, rect.rows, rect.minX, rect.minZ, g_Lattice.baseX, g_Lattice.baseZ,
            mapping.OffsetX(), mapping.OffsetZ(), TerrainHeight::kLatticeSlot);
        return true;
    }
    catch (const std::exception& error)
    {
        LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] lattice smoothing off: %s; terrain otherwise unchanged", error.what());
    }
    catch (...)
    {
        LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] lattice smoothing off after an exception; terrain otherwise unchanged");
    }
    ReleaseTerrainLattice();
    return false;
}

// Before the original zone process consumes them: clusters whose height
// (0x250), next-height (0x260) or full (0x270) dirty byte is set, as a bit
// per cluster index clusterX * 4 + clusterZ.
uint16_t TerrainLatticeDirtyClusters(void* zone, bool& full)
{
    full = false;
    if (!g_Lattice.active) return 0;
    uint16_t mask = 0;
    for (size_t i = 0; i < 16; ++i)
    {
        uint8_t fullByte = 0, height = 0, next = 0;
        if (!SafeReadZoneByte(zone, kFullDirtyOffset + i, fullByte) ||
            !SafeReadZoneByte(zone, kHeightDirtyOffset + i, height) ||
            !SafeReadZoneByte(zone, kHeightDirtyNextOffset + i, next))
            return 0;
        if (fullByte) full = true;
        if (fullByte || height || next) mask = uint16_t(mask | (1u << i));
    }
    return mask;
}

// After the original: re-read the dirty clusters' windows and upload only the
// bounding rectangle, and only when a height changed. A full rebuild refreshes
// the zone's whole window; the engine dispatches every zone, so a map-wide
// rebuild refreshes the whole texture zone by zone.
void RefreshTerrainLattice(void* zone, uint16_t mask, bool full)
{
    if (!g_Lattice.active || !g_Lattice.texture || !g_Lattice.context || !mask) return;
    int zoneX = 0, zoneZ = 0;
    if (!SafeReadZoneInt(zone, kZoneXOffset, zoneX) || !SafeReadZoneInt(zone, kZoneZOffset, zoneZ)) return;
    const auto& m = g_Lattice.mapping;
    const int column = zoneX - g_Lattice.minZoneX, row = zoneZ - g_Lattice.minZoneZ;
    if (column < 0 || row < 0 || column >= m.columns || row >= m.rows)
    {
        if (!g_Lattice.zoneWarned)
            LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] lattice refresh skipped zone (%d,%d) outside the installed rectangle", zoneX, zoneZ);
        g_Lattice.zoneWarned = true;
        return;
    }
    TerrainLattice::Rect box;
    bool any = false;
    for (int i = 0; i < 16; ++i)
    {
        if (!full && !(mask & (1u << i))) continue;
        const auto window = TerrainLattice::ClusterWindow(m, column, row, i / 4, i % 4);
        if (TerrainLattice::Empty(window)) continue;
        if (!any) box = window;
        else
        {
            box.left = (std::min)(box.left, window.left); box.top = (std::min)(box.top, window.top);
            box.right = (std::max)(box.right, window.right); box.bottom = (std::max)(box.bottom, window.bottom);
        }
        any = true;
    }
    if (!any) return;
    ++g_Lattice.batches;
    const int pitch = box.right - box.left, rows = box.bottom - box.top, width = m.Width();
    g_Lattice.scratch.resize(std::size_t(pitch) * rows);
    if (!ReadTerrainLatticeRect(g_Lattice.baseX, g_Lattice.baseZ, box.left, box.top, box.right, box.bottom,
            g_Lattice.scratch.data(), pitch))
    {
        if (!g_Lattice.readWarned)
            LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] lattice refresh could not read heights; smoothing keeps the previous lattice");
        g_Lattice.readWarned = true;
        return;
    }
    bool changed = false;
    for (int z = 0; z < rows; ++z)
    {
        uint16_t* target = g_Lattice.units.data() + std::size_t(box.top + z) * width + box.left;
        const uint16_t* fresh = g_Lattice.scratch.data() + std::size_t(z) * pitch;
        if (memcmp(target, fresh, std::size_t(pitch) * 2)) { memcpy(target, fresh, std::size_t(pitch) * 2); changed = true; }
    }
    if (changed)
    {
        const D3D11_BOX region{UINT(box.left), UINT(box.top), 0, UINT(box.right), UINT(box.bottom), 1};
        g_Lattice.context->UpdateSubresource(g_Lattice.texture.Get(), 0, &region,
            g_Lattice.units.data() + std::size_t(box.top) * width + box.left, UINT(width) * 2, 0);
        ++g_Lattice.uploads;
        g_Lattice.texels += uint64_t(pitch) * rows;
    }
    const ULONGLONG now = GetTickCount64();
    if (now - g_Lattice.lastLog >= 2000)
    {
        LogShimA(LogLevel::Debug, "terrain-tess", "[TERRAIN-TESS] lattice refresh zone=(%d,%d) clusters=0x%04X full=%d rect=[%d,%d)-[%d,%d) changed=%d batches=%llu (+%llu) uploads=%llu",
            zoneX, zoneZ, unsigned(mask), full ? 1 : 0, box.left, box.top, box.right, box.bottom, changed ? 1 : 0,
            g_Lattice.batches, g_Lattice.batches - g_Lattice.loggedBatches, g_Lattice.uploads);
        g_Lattice.lastLog = now;
        g_Lattice.loggedBatches = g_Lattice.batches;
    }
}
