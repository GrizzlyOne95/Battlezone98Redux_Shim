// Native HD tile material arrays. Geometry, heights and gameplay stay native.
struct NativeHdStream
{
    void* mesh; VertexDataPrefix* data; void* buffer;
};
struct NativeHdPass
{
    uint16_t technique, pass;
    std::string vertex, fragment;
    std::array<bool, 3> channels{};
};
std::map<std::string, NativeHdStream> g_HdStreams;
std::vector<NativeHdPass> g_HdPasses;
std::string g_HdSourceMaterial, g_HdBackupMaterial;
bool g_HdActive = false, g_HdDeclined = false;
bool g_HdProfileSuspended = false;
// Zones seen when paint last waited for a partial terrain; 0 when not waiting.
std::size_t g_HdPaintDeferredZones = 0;
std::array<bool, 256> g_HdTileMapped{};
std::array<uint8_t, 256> g_HdSliceRemap = TerrainHdMaterial::IdentityRemap();
std::array<bool, 3> g_HdChannelEnabled{};
void ResetNativeTerrainHd() { g_HdDeclined = false; g_HdProfileSuspended = false; g_HdPaintDeferredZones = 0; }

bool HdProfileAllowed()
{
    return TerrainHdMaterial::ProfileAllowsTiles(RenderProfiles::Exports::GetActiveBackend(),
        RenderProfiles::Exports::GetEffectiveRenderProfile());
}

using HdCreateBinding = void* (__thiscall*)(void*);
using HdDestroyBinding = void (__thiscall*)(void*, void*);
using HdCopyBinding = void* (__thiscall*)(void*, const void*);
using HdRemoveElement = void (__thiscall*)(void*, int, uint16_t);
using HdGetTexture = const OgreSharedPtr* (__thiscall*)(void*);
using HdGetTextureName = const std::string* (__thiscall*)(void*);
using HdBindingCount = uint32_t (__thiscall*)(void*);
HdCreateBinding g_hdCreateBinding = nullptr;
HdDestroyBinding g_hdDestroyBinding = nullptr;
HdCopyBinding g_hdCopyBinding = nullptr;
HdRemoveElement g_hdRemoveElement = nullptr;
HdGetTexture g_hdGetTexture = nullptr;
HdGetTextureName g_hdGetTextureName = nullptr;
HdBindingCount g_hdBindingCount = nullptr;
FnGetMaterialByName g_hdGetMesh = nullptr;
using HdGetSubMesh = void* (__thiscall*)(void*, uint16_t);
using HdMeshOperation = void (__thiscall*)(void*, RenderOperation&, uint16_t);
HdGetSubMesh g_hdGetSubMesh = nullptr;
HdMeshOperation g_hdMeshOperation = nullptr;

void ResolveNativeHdApi()
{
    // This code is reached only after the parent exact-build Ogre gate.
    HMODULE ogre = GetModuleHandleW(L"OgreMain.dll");
    g_hdCreateBinding = Resolve<HdCreateBinding>(ogre, "?createVertexBufferBinding@HardwareBufferManager@Ogre@@UAEPAVVertexBufferBinding@2@XZ");
    g_hdDestroyBinding = Resolve<HdDestroyBinding>(ogre, "?destroyVertexBufferBinding@HardwareBufferManager@Ogre@@UAEXPAVVertexBufferBinding@2@@Z");
    g_hdCopyBinding = Resolve<HdCopyBinding>(ogre, "??4VertexBufferBinding@Ogre@@QAEAAV01@ABV01@@Z");
    g_hdRemoveElement = Resolve<HdRemoveElement>(ogre, "?removeElement@VertexDeclaration@Ogre@@UAEXW4VertexElementSemantic@2@G@Z");
    g_hdGetTexture = Resolve<HdGetTexture>(ogre, "?_getTexturePtr@TextureUnitState@Ogre@@QBEABV?$SharedPtr@VTexture@Ogre@@@2@XZ");
    g_hdGetTextureName = Resolve<HdGetTextureName>(ogre, "?getTextureName@TextureUnitState@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
    g_hdBindingCount = Resolve<HdBindingCount>(ogre, "?getBufferCount@VertexBufferBinding@Ogre@@UBEIXZ");
    g_hdGetMesh = Resolve<FnGetMaterialByName>(ogre, "?getByName@MeshManager@Ogre@@QAE?AV?$SharedPtr@VMesh@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
    g_hdGetSubMesh = Resolve<HdGetSubMesh>(ogre, "?getSubMesh@Mesh@Ogre@@QBEPAVSubMesh@2@G@Z");
    g_hdMeshOperation = Resolve<HdMeshOperation>(ogre, "?_getRenderOperation@SubMesh@Ogre@@QAEXAAVRenderOperation@2@G@Z");
    if (!g_hdGetSubMesh || !g_hdMeshOperation || !g_hdCreateBinding || !g_hdDestroyBinding || !g_hdCopyBinding || !g_hdRemoveElement ||
        !g_hdGetTexture || !g_hdGetTextureName || !g_hdBindingCount || !g_hdGetMesh || !g_ogre.isBufferBound ||
        !g_ogre.findElementBySemantic || !g_ogre.programSupported ||
        !g_ogre.getFragmentProgram || !g_ogre.setFragmentProgram ||
        !g_ogre.getFragmentProgramParameters || !g_ogre.setFragmentProgramParameters ||
        !g_ogre.findNamedConstant || !g_ogre.setNamedAutoConstantReal || !g_ogre.copyMatchingNamedConstants ||
        !TerrainHdApiAvailable())
        throw std::runtime_error("native HD APIs/restoration unavailable");
}

// GpuProgramParameters::ACT_TIME_0_X (enum order in OgreGpuProgramParams.h).
constexpr int kAutoTime0X = 90;

void CopyHdPrograms(void* destination, void* source,
    const std::string& vertex, const std::string& fragment)
{
    OgreSharedPtr parameters;
    const auto bind = [&](bool pixel, const std::string& name) {
        auto get = pixel ? g_ogre.getFragmentProgramParameters : g_ogre.getVertexProgramParameters;
        auto setProgram = pixel ? g_ogre.setFragmentProgram : g_ogre.setVertexProgram;
        auto setParameters = pixel ? g_ogre.setFragmentProgramParameters : g_ogre.setVertexProgramParameters;
        get(source, &parameters);
        if (!parameters.rep || !parameters.info) throw std::runtime_error("native HD parameters unavailable");
        setProgram(destination, name, false);
        // setProgram rebuilt the destination's parameters for the new program.
        // A liquid pass keeps them, since only they can hold its time uniform,
        // and takes the source's matching constants and autos by name; other
        // passes take the source's set as is.
        bool timed = false;
        if (pixel)
        {
            OgreSharedPtr rebuilt;
            get(destination, &rebuilt);
            try
            {
                if (rebuilt.rep && g_ogre.findNamedConstant(rebuilt.rep, TerrainPaint::kTimeUniform, false))
                {
                    g_ogre.copyMatchingNamedConstants(rebuilt.rep, parameters.rep);
                    g_ogre.setNamedAutoConstantReal(rebuilt.rep, TerrainPaint::kTimeUniform, kAutoTime0X, 4000.0f);
                    timed = true;
                }
            }
            catch (...) { ReleaseCloneHandoff(rebuilt); throw; }
            ReleaseCloneHandoff(rebuilt);
        }
        if (!timed)
        {
            if (!AddSharedReference(parameters)) throw std::runtime_error("native HD parameter handoff failed");
            setParameters(destination, parameters);
        }
        ReleaseCloneHandoff(parameters);
        const auto* bound = (pixel ? g_ogre.getFragmentProgram : g_ogre.getVertexProgram)(destination);
        if (!bound || !bound->rep || *g_ogre.getResourceName(bound->rep) != name)
            throw std::runtime_error("native HD program bind audit failed");
    };
    try { bind(false, vertex); bind(true, fragment); }
    catch (...) { ReleaseCloneHandoff(parameters); throw; }
}

void RestoreNativeTerrainHd()
{
    g_HdActive = false;
    g_HdPaint = {};
    OgreSharedPtr source, backup;
    bool materialRestored = g_HdSourceMaterial.empty();
    try
    {
        if (!g_HdSourceMaterial.empty() && GetModuleHandleW(L"OgreMain.dll"))
        {
            void* manager = g_ogre.getMaterialManager();
            if (!manager) throw std::runtime_error("HD material manager already retired");
            g_ogre.getMaterialByName(manager, &source, g_HdSourceMaterial, std::string("Autodetect"));
            g_ogre.getMaterialByName(manager, &backup, g_HdBackupMaterial, std::string("Autodetect"));
            if (!source.rep || !backup.rep) throw std::runtime_error("HD restoration material unavailable");
            for (const auto& saved : g_HdPasses)
            {
                void* pass = g_ogre.getPass(g_ogre.getTechnique(source.rep, saved.technique), saved.pass);
                void* original = g_ogre.getPass(g_ogre.getTechnique(backup.rep, saved.technique), saved.pass);
                CopyHdPrograms(pass, original, *g_ogre.getResourceName(g_ogre.getVertexProgram(original)->rep),
                    *g_ogre.getResourceName(g_ogre.getFragmentProgram(original)->rep));
                const auto* texture = g_hdGetTexture(g_ogre.getTextureUnitState(original, 0));
                if (!texture || !texture->rep) throw std::runtime_error("HD original diffuse texture unavailable");
                g_ogre.setTexture(g_ogre.getTextureUnitState(pass, 0), *texture);
                for (unsigned c = 0; c < 3; ++c)
                {
                    if (!saved.channels[c]) continue;
                    const auto* originalTexture = g_hdGetTexture(g_ogre.getTextureUnitState(original, uint16_t(c + 2)));
                    if (!originalTexture || !originalTexture->rep) throw std::runtime_error("HD original material channel unavailable");
                    g_ogre.setTexture(g_ogre.getTextureUnitState(pass, uint16_t(c + 2)), *originalTexture);
                }
            }
            materialRestored = true;
            LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] shared native material restored passes=%zu", g_HdPasses.size());
        }
    }
    catch (...) { LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] material restoration declined"); }
    ReleaseCloneHandoff(source); ReleaseCloneHandoff(backup);
    unsigned restored = 0;
    int minReferences = INT_MAX, maxReferences = 0;
    void* meshManager = GetModuleHandleW(L"OgreMain.dll") ? g_ogre.getMeshManager() : nullptr;
    void* bufferManager = GetModuleHandleW(L"OgreMain.dll") ? g_ogre.getHardwareBufferManager() : nullptr;
    // Never remove inputs while a source shader still needs them. The mesh
    // owner retires those buffers during scene destruction if restoration fails.
    if (materialRestored && meshManager && bufferManager && g_hdGetMesh)
    for (const auto& entry : g_HdStreams)
    {
        OgreSharedPtr mesh;
        void* cleanBinding = nullptr;
        try
        {
            g_hdGetMesh(meshManager, &mesh, entry.first, std::string("Autodetect"));
            // Name lookup plus resource identity, never a stale scene pointer.
            if (mesh.rep == entry.second.mesh)
            {
                RenderOperation operation = {};
                g_hdMeshOperation(g_hdGetSubMesh(mesh.rep, 0), operation, 0);
                if (operation.vertexData != entry.second.data) throw std::runtime_error("HD vertex data owner changed");
                auto* data = operation.vertexData;
                // A foreign feature extending the binding is not ours to
                // overwrite. Leave the unused HD stream to the mesh owner.
                if (g_hdBindingCount(data->binding) != 4)
                    throw std::runtime_error("HD restoration binding layout changed");
                const auto* current = g_ogre.getBuffer(data->binding, 3);
                if (!current || current->rep != entry.second.buffer) throw std::runtime_error("HD slot owner changed");
                int references = 0;
                if (current->info && g_ogre.sharedPtrCount)
                {
                    references = int(g_ogre.sharedPtrCount(current));
                    minReferences = (std::min)(minReferences, references);
                    maxReferences = (std::max)(maxReferences, references);
                }
                void* manager = bufferManager;
                cleanBinding = g_hdCreateBinding(manager);
                if (!cleanBinding) throw std::runtime_error("HD restoration binding unavailable");
                // Preserve the CURRENT native buffers, including engine rebuilds.
                for (uint16_t slot = 0; slot < 3; ++slot)
                    g_ogre.setVertexBinding(cleanBinding, slot, *g_ogre.getBuffer(data->binding, slot));
                g_hdCopyBinding(data->binding, cleanBinding);
                if (g_hdBindingCount(data->binding) != 3 || g_ogre.isBufferBound(data->binding, 3))
                    throw std::runtime_error("HD stream binding retirement failed");
                for (uint16_t semantic = 2; semantic <= 4; ++semantic)
                    g_hdRemoveElement(data->declaration, 7, semantic);
                g_hdDestroyBinding(manager, cleanBinding); cleanBinding = nullptr;
                ++restored;
            }
        }
        catch (...) { if (cleanBinding) g_hdDestroyBinding(bufferManager, cleanBinding); }
        ReleaseCloneHandoff(mesh);
    }
    if (!g_HdStreams.empty()) LogShimA(LogLevel::Info, "terrain-hd",
        "[TERRAIN-HD] native streams restored meshes=%u tracked=%zu sharedRefsBefore=%d..%d", restored, g_HdStreams.size(), minReferences, maxReferences);
    g_HdStreams.clear(); g_HdPasses.clear(); g_HdSourceMaterial.clear();
    g_HdSliceRemap = TerrainHdMaterial::IdentityRemap(); g_HdChannelEnabled = {};
    if (!g_HdBackupMaterial.empty())
    {
        try
        {
            if (GetModuleHandleW(L"OgreMain.dll"))
            {
                if (void* manager = g_ogre.getMaterialManager())
                {
                    g_ogre.removeResource(manager, g_HdBackupMaterial);
                    ++g_semanticMaterialRemoved;
                }
            }
        }
        catch (...) { LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] backup material removal declined"); }
        if (g_proxy.semanticMaterialName == g_HdBackupMaterial) g_proxy.semanticMaterialName.clear();
        g_HdBackupMaterial.clear();
    }
}

struct NativeHdContext { int originX, originZ, zoneX, zoneZ, clusterX, clusterZ; };
bool ProvideNativeHdCell(void* opaque, int x, int z, TerrainSemantic::Cell& cell)
{
    const auto& c = *static_cast<NativeHdContext*>(opaque);
    cell.cellX = x; cell.cellZ = z;
    cell.terrainX = c.zoneX * 256 + c.originX - 128 + (c.clusterX * 16 + x) * 4;
    cell.terrainZ = c.zoneZ * 256 + c.originZ - 128 + (c.clusterZ * 16 + z) * 4;
    AtlasRect rect = {};
    if (!ReadTerrainSemantic(cell.terrainX, cell.terrainZ, cell.word, cell.tileIndex, rect)) return false;
    cell.typeA = uint8_t((cell.word >> 12) & 15); cell.typeB = uint8_t((cell.word >> 8) & 15);
    cell.mix = cell.orientation = uint8_t((cell.word >> 4) & 15); cell.variant = uint8_t(cell.word & 3);
    cell.rect = { rect.u, rect.v, rect.w, rect.h };
    return true;
}

void UpdateNativeHdZone(void* zone, bool dirty)
{
    NativeHdContext c = {};
    if (!SafeReadZoneInt(zone, kZoneXOffset, c.zoneX) || !SafeReadZoneInt(zone, kZoneZOffset, c.zoneZ) ||
        !SafeReadIntAddress(g_terrainOriginXVa, c.originX) ||
        !SafeReadIntAddress(g_terrainOriginZVa, c.originZ))
        throw std::runtime_error("native HD zone coordinates unavailable");
    for (c.clusterX = 0; c.clusterX < kClusterAxisCount; ++c.clusterX)
    for (c.clusterZ = 0; c.clusterZ < kClusterAxisCount; ++c.clusterZ)
    {
        ClusterCandidate candidate; bool abort = false;
        if (!ResolveClusterCandidate(zone, c.zoneX, c.zoneZ, c.clusterX, c.clusterZ, candidate, abort))
        {
            if (abort) throw std::runtime_error("native HD cluster identity declined");
            continue;
        }
        RenderOperation operation = {}; void* sub = nullptr; void* stock = nullptr;
        if (!GetEntityOperation(candidate.entity, operation, sub) || !GetVertexBuffer(operation, 1, stock))
            throw std::runtime_error("native HD render operation unavailable");
        if (*g_ogre.getMaterialName(sub) != g_proxy.materialName)
            throw std::runtime_error("native HD requires one terrain material per mission");
        auto found = g_HdStreams.find(candidate.meshName);
        const bool installed = found != g_HdStreams.end() && found->second.mesh == candidate.mesh &&
            found->second.data == operation.vertexData;
        if (installed && !dirty) continue;
        std::vector<TerrainSemantic::Vertex> vertices;
        if (!TerrainSemantic::BuildVertices(ProvideNativeHdCell, &c, vertices) || !ValidateSemanticVertexRanges(vertices))
            throw std::runtime_error("native HD semantic generation declined");
        std::vector<uint8_t> bytes;
        if (!ReadD3D11VertexBuffer(stock, uint32_t(TerrainSemantic::kVertexCount * 4), bytes))
            throw std::runtime_error("native HD packed UV audit unavailable");
        const auto audit = TerrainSemantic::ValidatePackedUv(vertices, bytes.data(), 4, 0);
        if (audit.checked != TerrainSemantic::kVertexCount || audit.mismatches)
            throw std::runtime_error("native HD packed UV parity failed");
        std::vector<uint8_t> positions, heights;
        Vector3 translation = {};
        if (g_HdPaint.enabled)
        {
            void* buffer = nullptr; void* heightBuffer = nullptr;
            const auto* p = g_ogre.getNodePosition(candidate.node);
            if (!p || !GetVertexBuffer(operation, 0, buffer) || g_ogre.getVertexSize(buffer) != 16 ||
                !ReadD3D11VertexBuffer(buffer, uint32_t(TerrainSemantic::kVertexCount * 16), positions))
                throw std::runtime_error("paint native position stream unavailable");
            // The released terrain VS replaces object Y with this stream.
            if (!GetVertexBuffer(operation, 2, heightBuffer) || g_ogre.getVertexSize(heightBuffer) != 4 ||
                !ReadD3D11VertexBuffer(heightBuffer, uint32_t(TerrainSemantic::kVertexCount * 4), heights))
                throw std::runtime_error("paint native height stream unavailable");
            translation = *p;
        }
        std::vector<TerrainSemantic::GpuVertex> upload;
        upload.reserve(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            auto gpu = vertices[i].gpu;
            if (g_HdPaint.enabled)
            {
                // Copy actual native POSITION.xz, not tile UV or camera-relative
                // positions. This preserves duplicated seams and native spacing.
                // The atlas rect is unused here; its x carries world Y (the
                // native height stream) for the triplanar side projections.
                float x = 0, y = 0, z = 0;
                memcpy(&x, positions.data() + i*16, 4); memcpy(&z, positions.data() + i*16+8, 4);
                memcpy(&y, heights.data() + i*4, 4);
                if (!std::isfinite(y) || std::abs(y) > 1000000) throw std::runtime_error("paint native height invalid");
                const auto world = TerrainPaint::WorldXZ(x, z, translation.x, translation.z);
                gpu.localU = world[0]; gpu.localV = world[1]; gpu.tileIndex = 0;
                gpu.atlasU = y + translation.y;
            }
            else if (!g_HdTileMapped[gpu.tileIndex] ||
                !TerrainHdMaterial::Remap(g_HdSliceRemap, gpu.tileIndex, g_proxy.hdSliceCount, gpu.tileIndex))
                throw std::runtime_error("native HD manifest slice missing");
            upload.push_back(gpu);
        }
        const uint32_t size = uint32_t(upload.size() * sizeof(TerrainSemantic::GpuVertex));
        if (installed)
        {
            const auto* buffer = g_ogre.getBuffer(operation.vertexData->binding, 3);
            if (!buffer || buffer->rep != found->second.buffer || !WriteD3D11VertexBuffer(buffer->rep, upload.data(), size))
                throw std::runtime_error("native HD stream refresh failed");
            continue;
        }
        if (!ValidateTerrainOperation(candidate.mesh, candidate.entity, "native HD") ||
            g_hdBindingCount(operation.vertexData->binding) != 3 ||
            g_ogre.isBufferBound(operation.vertexData->binding, 3))
            throw std::runtime_error("native HD stream layout occupied");
        for (uint16_t index = 2; index <= 4; ++index)
            if (g_ogre.findElementBySemantic(operation.vertexData->declaration, 7, index))
                throw std::runtime_error("native HD semantic occupied");
        OgreSharedPtr buffer;
        try
        {
            g_ogre.createVertexBuffer(g_ogre.getHardwareBufferManager(), &buffer,
                sizeof(TerrainSemantic::GpuVertex), uint32_t(upload.size()), 5, false);
            if (!buffer.rep || !buffer.info || !WriteD3D11VertexBuffer(buffer.rep, upload.data(), size))
                throw std::runtime_error("native HD stream upload failed");
            // Record ownership before mutating the declaration, for rollback.
            g_HdStreams[candidate.meshName] = {candidate.mesh, operation.vertexData, buffer.rep};
            g_ogre.setVertexBinding(operation.vertexData->binding, 3, buffer);
            g_ogre.addVertexElement(operation.vertexData->declaration, 3, 0, 1, 7, 2);
            g_ogre.addVertexElement(operation.vertexData->declaration, 3, 8, 9, 7, 3);
            g_ogre.addVertexElement(operation.vertexData->declaration, 3, 12, 3, 7, 4);
            ReleaseCloneHandoff(buffer);
        }
        catch (...) { ReleaseCloneHandoff(buffer); throw; }
    }
}

void RefreshNativeTerrainHd(void* zone, bool dirty)
{
    if (!g_HdActive) return;
    try { UpdateNativeHdZone(zone, dirty); }
    catch (const std::exception& error)
    {
        LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] refresh declined: %s", error.what());
        RestoreNativeTerrainTessellationTest(); RestoreNativeTerrainHd();
        g_HdDeclined = true;
    }
    catch (...) { RestoreNativeTerrainTessellationTest(); RestoreNativeTerrainHd(); g_HdDeclined = true; }
}

// Live paint (OPENSHIM_TERRAIN_PAINT_LIVE=1): a multi-map pack whose paint
// carries a "live" autopaint recipe generates control images for missions
// with no baked entry. Baked entries always win. See Docs/terrain-live-paint.md.
bool LivePaintRequested()
{
    char value[8] = {};
    const DWORD length = GetEnvironmentVariableA("OPENSHIM_TERRAIN_PAINT_LIVE", value, sizeof(value));
    return length == 1 && value[0] == '1';
}

bool ReadLivePaintWord(int x, int z, uint16_t& word)
{
    __try
    {
        const uint16_t* p = g_terrainWordAt(x, z);
        if (!p) return false;
        word = *p;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

bool ReadLivePaintHeight(int x, int z, uint16_t& height)
{
    __try { height = uint16_t(g_heightAt(x, z) & 0x1FFF); return true; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

// Memory caps for the 32-bit process: the slope fields are doubles at full
// height resolution and the upscale holds every layer at the array width.
constexpr int kLivePaintMaxFileZones = 64;
constexpr unsigned kLivePaintMaxSize = 2048;

// The HG2/MAT rectangle as the engine holds it: one runtime zone more per axis
// than the file, the file starting at the centre of the lowest zone.
TerrainLivePaint::Input ReadLivePaintInput(const nlohmann::json& map, const nlohmann::json& recipe)
{
    int originX = 0, originZ = 0;
    if (!g_heightAt || !g_terrainWordAt || !SafeReadIntAddress(g_terrainOriginXVa, originX) ||
        !SafeReadIntAddress(g_terrainOriginZVa, originZ))
        throw std::runtime_error("live paint terrain readers unavailable");
    std::set<std::pair<int, int>> zones;
    int minX = INT_MAX, minZ = INT_MAX, maxX = INT_MIN, maxZ = INT_MIN;
    for (const auto& zone : g_zoneOrdinals)
    {
        int x = 0, z = 0;
        if (!SafeReadZoneInt(zone.first, kZoneXOffset, x) || !SafeReadZoneInt(zone.first, kZoneZOffset, z))
            throw std::runtime_error("live paint zone identity invalid");
        zones.emplace(x, z);
        minX = (std::min)(minX, x); maxX = (std::max)(maxX, x);
        minZ = (std::min)(minZ, z); maxZ = (std::max)(maxZ, z);
    }
    if (zones.empty()) throw std::runtime_error("live paint has no zones");
    const int columns = maxX - minX + 1, rows = maxZ - minZ + 1;
    if (columns < 2 || rows < 2 || std::size_t(columns) * rows != zones.size())
        throw std::runtime_error("live paint needs a full rectangle of at least 2x2 zones");
    if ((columns - 1) * (rows - 1) > kLivePaintMaxFileZones)
        throw std::runtime_error("live paint map too large: " + std::to_string(columns - 1) + "x" + std::to_string(rows - 1) + " file zones");
    TerrainLivePaint::Input input;
    input.zonesX = columns - 1; input.zonesZ = rows - 1;
    const int baseX = minX * 256 + originX, baseZ = minZ * 256 + originZ;
    const int width = input.zonesX * 256, depth = input.zonesZ * 256;
    input.plane.resize(std::size_t(width) * depth);
    for (int z = 0; z < depth; ++z)
    for (int x = 0; x < width; ++x)
        if (!ReadLivePaintHeight(baseX + x, baseZ + z, input.plane[std::size_t(z) * width + x]))
            throw std::runtime_error("live paint height unreadable");
    const int cellsX = input.zonesX * 64, cellsZ = input.zonesZ * 64;
    input.cells.resize(std::size_t(cellsX) * cellsZ);
    for (int z = 0; z < cellsZ; ++z)
    for (int x = 0; x < cellsX; ++x)
        if (!ReadLivePaintWord(baseX + 4 * x, baseZ + 4 * z, input.cells[std::size_t(z) * cellsX + x]))
            throw std::runtime_error("live paint material word unreadable");
    input.bounds = map.at("boundsMeters").get<std::array<float, 4>>();
    input.seed = TerrainLivePaint::Generator::Seed(recipe, map.at("terrainFingerprint").get<std::string>());
    return input;
}

// Optional offline check: the generator CLI input (tests/terrain_live_paint_tests.cpp)
// and its RGBA output, for tests/terrain_live_paint_parity.py --dump.
void DumpLivePaint(const TerrainLivePaint::Input& input, const std::vector<std::vector<uint8_t>>& images,
    const std::string& fingerprint, int size)
{
    char dir[MAX_PATH] = {};
    const DWORD length = GetEnvironmentVariableA("OPENSHIM_TERRAIN_PAINT_LIVE_DUMP", dir, sizeof(dir));
    if (!length || length >= sizeof(dir)) return;
    const std::string base = (std::filesystem::path(dir) / ("live_" + fingerprint)).string();
    std::ofstream bin(base + ".bin", std::ios::binary);
    const int32_t zones[2] = {input.zonesX, input.zonesZ};
    bin.write(reinterpret_cast<const char*>(zones), 8);
    bin.write(reinterpret_cast<const char*>(input.bounds.data()), 16);
    bin.write(reinterpret_cast<const char*>(&input.seed), 4);
    bin.write(reinterpret_cast<const char*>(input.cells.data()), std::streamsize(input.cells.size() * 2));
    bin.write(reinterpret_cast<const char*>(input.plane.data()), std::streamsize(input.plane.size() * 2));
    std::ofstream rgba(base + ".rgba", std::ios::binary);
    for (const auto& image : images) rgba.write(reinterpret_cast<const char*>(image.data()), std::streamsize(image.size()));
    LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-PAINT] live paint dumped \"%s\" size=%d ok=%d",
        base.c_str(), size, int(bin.good() && rgba.good()));
}

// Overwrite the placeholder control slices (4, and 13 for eight layers) of the
// built diffuse array, every mip. Bytes go in raw like the PNG path; Ogre loads
// PNGs as BGRA, so swizzle for a B8G8R8A8 array.
void UploadLivePaint(const std::vector<std::vector<uint8_t>>& images, UINT size)
{
    ID3D11Texture2D* texture = g_hdDiffuseNativeTexture;
    if (!texture) throw std::runtime_error("live paint diffuse array unavailable");
    D3D11_TEXTURE2D_DESC desc = {};
    texture->GetDesc(&desc);
    const bool bgra = desc.Format == DXGI_FORMAT_B8G8R8A8_UNORM || desc.Format == DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    const bool rgba = desc.Format == DXGI_FORMAT_R8G8B8A8_UNORM || desc.Format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    if ((!bgra && !rgba) || desc.Width != size || desc.Height != size || desc.Usage != D3D11_USAGE_DEFAULT ||
        desc.ArraySize < (images.size() > 1 ? 14u : 5u))
        throw std::runtime_error("live paint needs an uncompressed square default-usage diffuse array: format=" +
            std::to_string(int(desc.Format)) + " size=" + std::to_string(desc.Width) + "x" + std::to_string(desc.Height));
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    texture->GetDevice(device.GetAddressOf());
    if (device) device->GetImmediateContext(context.GetAddressOf());
    if (!context) throw std::runtime_error("live paint device context unavailable");
    const UINT slices[2] = {4, 13};
    for (std::size_t i = 0; i < images.size() && i < 2; ++i)
    {
        std::vector<uint8_t> level = images[i];
        if (bgra) for (std::size_t p = 0; p < level.size(); p += 4) std::swap(level[p], level[p + 2]);
        UINT w = size;
        for (UINT mip = 0; mip < desc.MipLevels; ++mip)
        {
            context->UpdateSubresource(texture, D3D11CalcSubresource(mip, slices[i], desc.MipLevels), nullptr,
                level.data(), w * 4, 0);
            if (w == 1) break;
            const UINT half = w / 2;
            std::vector<uint8_t> next(std::size_t(half) * half * 4);
            for (UINT y = 0; y < half; ++y)
            for (UINT x = 0; x < half; ++x)
            for (UINT k = 0; k < 4; ++k)
            {
                const auto at = [&](UINT px, UINT py) { return UINT(level[(std::size_t(py) * w + px) * 4 + k]); };
                next[(std::size_t(y) * half + x) * 4 + k] =
                    uint8_t((at(2 * x, 2 * y) + at(2 * x + 1, 2 * y) + at(2 * x, 2 * y + 1) + at(2 * x + 1, 2 * y + 1) + 2) / 4);
            }
            level.swap(next); w = half;
        }
    }
}

bool InstallNativeTerrainHd()
{
    // Cleared before every early return: a stale deferral would keep
    // tessellation waiting for a paint retry that never comes.
    g_HdPaintDeferredZones = 0;
    if (!g_config.hdEnabled || g_HdDeclined) return false;
    if (!HdProfileAllowed())
    {
        if (!g_HdProfileSuspended) LogShimA(LogLevel::Info, "terrain-hd",
            "[TERRAIN-HD] stock atlas retained: effective DX11 Enhanced profile required; HD arrays not allocated");
        g_HdProfileSuspended = true;
        return false;
    }
    g_HdProfileSuspended = false;
    if (g_HdActive) return true;
    OgreSharedPtr source, backup, array, program;
    std::array<OgreSharedPtr, 3> channelArrays{};
    try
    {
        ResolveNativeHdApi();
        // Require released DX11 identity before using its buffer/program ABI.
        std::string hash;
        if (!VerifyModuleHash(GetModuleHandleW(L"RenderSystem_Direct3D11.dll"),
            "78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0", hash))
            throw std::runtime_error("native HD released DX11 identity declined");
        RenderOperation operation = {}; void* sub = nullptr;
        if (!GetEntityOperation(g_proxy.sourceEntity, operation, sub)) throw std::runtime_error("native HD source unavailable");
        g_proxy.materialName = *g_ogre.getMaterialName(sub);
        const auto* binding = FindTerrainHdBinding(g_proxy.materialName);
        if (!binding) throw std::runtime_error("native HD manifest binding missing");
        g_HdSliceRemap = binding->sliceRemap;
        g_HdTileMapped.fill(true);
        if (!binding->tileRects.empty())
        {
            void* manager = g_terrainManager();
            if (!manager) throw std::runtime_error("HD native tile table unavailable");
            g_HdTileMapped.fill(false);
            for (unsigned i = 0; i < 256; ++i)
            {
                const auto* rect = g_atlasRectAt(manager, i);
                if (rect) g_HdTileMapped[i] = TerrainHdMaterial::FindRectSlice(binding->tileRects,
                    {rect->u, rect->v, rect->w, rect->h}, g_HdSliceRemap[i]);
            }
        }
        for (unsigned c = 0; c < 3; ++c) g_HdChannelEnabled[c] = binding->channels[c].enabled;
        if (!g_config.surfaceManifest.empty() && std::any_of(g_HdChannelEnabled.begin(), g_HdChannelEnabled.end(), [](bool value){return value;}))
            throw std::runtime_error("HD material channels and surface-atlas override cannot own the same bindings");
        g_proxy.generation = ++g_resourceSerial;
        g_proxy.semanticMaterialGeneration = ++g_semanticMaterialSerial;
        g_proxy.semanticMaterialName = "OpenShim/TerrainNativeHD/Backup/" + std::to_string(g_proxy.semanticMaterialGeneration);
        g_ogre.getMaterialByName(g_ogre.getMaterialManager(), &source, g_proxy.materialName, std::string("Autodetect"));
        if (!source.rep) throw std::runtime_error("native HD material unavailable");
        if (!binding->diffuseResource.empty())
        {
            if (!g_ogre.getNumTechniques(source.rep)) throw std::runtime_error("native HD source technique unavailable");
            // Any pass whose unit 0 is the pack atlas proves identity. Technique 0
            // is not always the diffuse one: on stock moon maps it is the glow
            // technique (unit 0 = black.dds), like the shadow techniques below.
            // Ogre resource names are case-insensitive; TRNs spell the atlas in either case.
            bool atlasFound = false;
            const std::string* firstName = nullptr;
            for (uint16_t t = 0; t < g_ogre.getNumTechniques(source.rep) && !atlasFound; ++t)
            for (uint16_t p = 0; p < g_ogre.getNumPasses(g_ogre.getTechnique(source.rep, t)); ++p)
            {
                void* pass = g_ogre.getPass(g_ogre.getTechnique(source.rep, t), p);
                if (!g_ogre.getNumTextureUnitStates(pass)) continue;
                const auto* name = g_hdGetTextureName(g_ogre.getTextureUnitState(pass, 0));
                if (!firstName) firstName = name;
                if (name && _stricmp(name->c_str(), binding->diffuseResource.c_str()) == 0) { atlasFound = true; break; }
            }
            if (!atlasFound)
                throw std::runtime_error("native HD source atlas does not match pack: expected=" +
                    binding->diffuseResource + " actual=" + (firstName ? *firstName : "<unavailable>"));
        }
        std::optional<TerrainHdMaterialBinding> selectedBinding;
        std::optional<TerrainLivePaint::Input> liveInput;
        if (binding->paint.enabled)
        {
            const auto map = CaptureTerrainPaintMap();
            if (!binding->paint.maps.empty())
            {
                // Multi-map pack: take the entry matching this mission and bind
                // its control images as slices 4 and 13; no match declines the whole pack.
                const auto* entry = TerrainPaint::SelectMap(binding->paint,
                    map.at("terrainFingerprint").get<std::string>(),
                    map.at("boundsMeters").get<std::array<float, 4>>());
                if (!entry)
                {
                    if (TerrainPaint::MapMayGrow(binding->paint, map.at("boundsMeters").get<std::array<float, 4>>(),
                            map.at("zoneCount").get<std::size_t>(), map.at("zoneMeters").get<float>()))
                    {
                        g_HdPaintDeferredZones = g_zoneOrdinals.size();
                        throw std::runtime_error("paint map incomplete, retrying as zones are built: actual=" + map.dump());
                    }
                    if (!binding->livePaint.is_object() || !LivePaintRequested())
                        throw std::runtime_error("paint pack has no map entry for this mission: actual=" + map.dump());
                    liveInput = ReadLivePaintInput(map, binding->livePaint);
                    const double undefined = TerrainLivePaint::Generator(binding->livePaint, *liveInput).UndefinedShare();
                    if (undefined > 0.01)
                        throw std::runtime_error("live paint recipe leaves " + std::to_string(int(undefined * 100 + 0.5)) +
                            "% of material cells unmapped (another world's map?): actual=" + map.dump());
                    // The first baked entry's tiles stand in until the array exists; UploadLivePaint replaces them.
                    const auto& placeholder = binding->paint.maps.front();
                    selectedBinding = *binding;
                    selectedBinding->tiles[4] = placeholder.control;
                    if (!placeholder.control2.empty()) selectedBinding->tiles[13] = placeholder.control2;
                    selectedBinding->paint.fingerprint = map.at("terrainFingerprint").get<std::string>();
                    selectedBinding->paint.bounds = map.at("boundsMeters").get<std::array<float, 4>>();
                    selectedBinding->paint.maps.clear();
                    binding = &*selectedBinding;
                    LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-PAINT] live paint selected fingerprint=%s fileZones=%dx%d undefined=%.4f",
                        binding->paint.fingerprint.c_str(), liveInput->zonesX, liveInput->zonesZ, undefined);
                }
                else
                {
                    selectedBinding = *binding;
                    selectedBinding->tiles[4] = entry->control;
                    if (!entry->control2.empty()) selectedBinding->tiles[13] = entry->control2;
                    selectedBinding->paint.fingerprint = entry->fingerprint;
                    selectedBinding->paint.bounds = entry->bounds;
                    selectedBinding->paint.maps.clear();
                    binding = &*selectedBinding;
                    LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-PAINT] multi-map entry selected fingerprint=%s control=\"%s\"",
                        entry->fingerprint.c_str(), entry->control.c_str());
                }
            }
            if (map.at("terrainFingerprint").get<std::string>() != binding->paint.fingerprint ||
                map.at("boundsMeters").get<std::array<float, 4>>() != binding->paint.bounds)
                throw std::runtime_error("paint terrain fingerprint/bounds do not match this mission: expected=" +
                    binding->paint.fingerprint + " actual=" + map.dump());
            g_HdPaint = binding->paint;
            LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-PAINT] map accepted fingerprint=%s zones=%zu bounds=(%.1f,%.1f,%.1f,%.1f)",
                g_HdPaint.fingerprint.c_str(), g_zoneOrdinals.size(), g_HdPaint.bounds[0], g_HdPaint.bounds[1], g_HdPaint.bounds[2], g_HdPaint.bounds[3]);
        }
        g_ogre.cloneMaterial(source.rep, &backup, g_proxy.semanticMaterialName, false, std::string());
        if (!backup.rep) throw std::runtime_error("native HD backup unavailable");
        ++g_semanticMaterialCreated;
        g_HdBackupMaterial = g_proxy.semanticMaterialName;
        NativeHdContext selected = {0,0,g_proxy.zoneX,g_proxy.zoneZ,g_proxy.clusterX,g_proxy.clusterZ};
        if (!SafeReadIntAddress(g_terrainOriginXVa, selected.originX) ||
            !SafeReadIntAddress(g_terrainOriginZVa, selected.originZ) ||
            !TerrainSemantic::BuildVertices(ProvideNativeHdCell, &selected, g_proxy.semanticVertices))
            throw std::runtime_error("native HD selected tile semantics unavailable");
        if (!BuildTerrainHdTextureArray(*binding, array)) throw std::runtime_error("native HD texture array declined");
        if (liveInput)
        {
            const auto start = std::chrono::steady_clock::now();
            if (g_proxy.hdWidth > kLivePaintMaxSize)
                throw std::runtime_error("live paint array too wide: " + std::to_string(g_proxy.hdWidth));
            const auto images = TerrainLivePaint::Generate(binding->livePaint, *liveInput, int(g_proxy.hdWidth));
            DumpLivePaint(*liveInput, images, binding->paint.fingerprint, int(g_proxy.hdWidth));
            UploadLivePaint(images, g_proxy.hdWidth);
            LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-PAINT] live paint generated fileZones=%dx%d size=%u images=%zu ms=%lld",
                liveInput->zonesX, liveInput->zonesZ, g_proxy.hdWidth, images.size(),
                (long long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count());
        }
        for (unsigned c = 0; c < 3; ++c)
        {
            if (!g_HdChannelEnabled[c]) continue;
            auto channel = *binding;
            channel.fallback = binding->channels[c].fallback;
            channel.tiles = binding->channels[c].tiles;
            if (!BuildTerrainHdTextureArray(channel, channelArrays[c], int(c)))
                throw std::runtime_error("native HD material array declined");
        }
        std::map<std::string, std::string> cache;
        std::map<std::string, std::array<bool, 3>> programChannels;
        const auto generate = [&](const OgreSharedPtr* input, bool pixel) -> std::string {
            if (!input || !input->rep) return {};
            const std::string* text = g_ogre.getProgramSource(input->rep);
            if (!text || text->empty()) { input = g_ogre.getUnifiedDelegate(input->rep); if (!input || !input->rep) return {}; text = g_ogre.getProgramSource(input->rep); }
            std::string target, entry, defines;
            g_ogre.getStringParameter(input->rep, &target, std::string("target"));
            g_ogre.getStringParameter(input->rep, &entry, std::string("entry_point"));
            g_ogre.getStringParameter(input->rep, &defines, std::string("preprocessor_defines"));
            if (!text || target.rfind(pixel ? "ps_4" : "vs_4", 0) != 0 || entry != (pixel ? "terrain_fragment" : "terrain_vertex") ||
                defines.find("VERTEX_LIGHTING") != std::string::npos) return {};
            const std::string key = *g_ogre.getResourceName(input->rep);
            auto known = cache.find(key); if (known != cache.end()) return known->second;
            std::string generated; bool debug = false;
            if (!(pixel ? BuildSemanticFragmentSource(*text, false, true, generated) :
                BuildSemanticProgramSource(*text, true, true, 0, key, generated, debug))) return {};
            if (pixel && !TerrainHdMaterial::Specialize(generated, g_HdChannelEnabled))
                throw std::runtime_error("HD material shader contract unavailable");
            if (pixel && !TerrainHdMaterial::SpecializeDetail(generated, binding->detail))
                throw std::runtime_error("HD detail tuning shader contract unavailable");
            if (binding->paint.enabled && !TerrainPaint::Specialize(generated, pixel, binding->paint))
                throw std::runtime_error("native paint shader specialization declined");
            // Content-only name: the microcode cache must hit on every run.
            const std::string name = "OpenShim/TerrainNativeHD/" + SourceHashSuffix(key + generated + defines);
            ForgetGeneratedProgram(g_ogre.getHighLevelProgramManager(), name);
            g_ogre.createHighLevelProgram(g_ogre.getHighLevelProgramManager(), &program, name, std::string("General"), std::string("hlsl"), pixel ? 1 : 0);
            if (!program.rep) throw std::runtime_error("native HD program creation failed");
            g_proxy.semanticProgramNames.push_back(name); ++g_semanticProgramsCreatedTotal;
            g_ogre.setProgramSource(program.rep, generated);
            if (!g_ogre.setStringParameter(program.rep, std::string("target"), target) ||
                !g_ogre.setStringParameter(program.rep, std::string("entry_point"), entry) ||
                !g_ogre.setStringParameter(program.rep, std::string("preprocessor_defines"), defines + ",OPENSHIM_TERRAIN_HD=1"))
                throw std::runtime_error("native HD program parameters declined");
            g_ogre.loadResource(program.rep, true);
            if (!g_ogre.programSupported(program.rep)) throw std::runtime_error("native HD shader unsupported");
            if (pixel)
            {
                constexpr const char* flags[] = {"NORMALMAP_ENABLED", "SPECULARMAP_ENABLED", "EMISSIVEMAP_ENABLED"};
                std::array<bool, 3> channels{};
                for (unsigned c = 0; c < 3; ++c)
                    channels[c] = g_HdChannelEnabled[c] && TerrainHdMaterial::HasDefine(defines, flags[c]);
                programChannels.emplace(name, channels);
            }
            ReleaseCloneHandoff(program); cache.emplace(key, name);
            // This compile blocks the main thread for up to seconds, dozens of times on a
            // cold cache: keep the window responsive and the finished work on disk, so
            // a load the player gives up on doesn't start over.
            { MSG pending; PeekMessageW(&pending, nullptr, 0, 0, PM_NOREMOVE); }
            OgreShaderCacheTick();
            return name;
        };
        for (uint16_t t = 0; t < g_ogre.getNumTechniques(backup.rep); ++t)
        for (uint16_t p = 0; p < g_ogre.getNumPasses(g_ogre.getTechnique(backup.rep, t)); ++p)
        {
            void* pass = g_ogre.getPass(g_ogre.getTechnique(backup.rep, t), p);
            // The ordinary diffuse pass above establishes pack identity. Some
            // terrain shadow techniques intentionally use black.dds at unit
            // zero; retain their original programs and texture bindings.
            if (!binding->diffuseResource.empty())
            {
                if (!g_ogre.getNumTextureUnitStates(pass)) continue;
                const auto* name = g_hdGetTextureName(g_ogre.getTextureUnitState(pass, 0));
                if (!name || _stricmp(name->c_str(), binding->diffuseResource.c_str()) != 0) continue;
            }
            const std::string vs = generate(g_ogre.getVertexProgram(pass), false);
            if (vs.empty()) continue;
            const std::string ps = generate(g_ogre.getFragmentProgram(pass), true);
            if (ps.empty() || !g_ogre.getNumTextureUnitStates(pass)) throw std::runtime_error("native HD matching fragment unavailable");
            const auto channels = programChannels.at(ps);
            for (unsigned c = 0; c < 3; ++c)
            {
                if (!channels[c]) continue;
                if (g_ogre.getNumTextureUnitStates(pass) <= c + 2)
                    throw std::runtime_error("HD material pass has no guarded channel");
                const auto* resource = g_hdGetTextureName(g_ogre.getTextureUnitState(pass, uint16_t(c + 2)));
                if (!resource || _stricmp(resource->c_str(), binding->channels[c].sourceResource.c_str()) != 0)
                    throw std::runtime_error("HD material source identity mismatch: slot=" + std::to_string(c + 2) +
                        " expected=" + binding->channels[c].sourceResource + " actual=" + (resource ? *resource : "<missing>"));
            }
            g_HdPasses.push_back({t,p,vs,ps,channels});
        }
        if (g_HdPasses.empty()) throw std::runtime_error("native HD compatible terrain passes unavailable");
        for (unsigned c = 0; c < 3; ++c)
            if (g_HdChannelEnabled[c] && std::none_of(g_HdPasses.begin(), g_HdPasses.end(),
                [c](const NativeHdPass& pass){return pass.channels[c];}))
                throw std::runtime_error("HD material channel has no compatible shader pass");
        for (const auto& zone : g_zoneOrdinals) UpdateNativeHdZone(zone.first, false);
        if (g_HdStreams.empty()) throw std::runtime_error("native HD compatible clusters unavailable");
        g_HdSourceMaterial = g_proxy.materialName; // rollback before first write
        for (const auto& saved : g_HdPasses)
        {
            void* pass = g_ogre.getPass(g_ogre.getTechnique(source.rep, saved.technique), saved.pass);
            void* original = g_ogre.getPass(g_ogre.getTechnique(backup.rep, saved.technique), saved.pass);
            CopyHdPrograms(pass, original, saved.vertex, saved.fragment);
            g_ogre.setTexture(g_ogre.getTextureUnitState(pass, 0), array);
            for (unsigned c = 0; c < 3; ++c)
                if (saved.channels[c]) g_ogre.setTexture(g_ogre.getTextureUnitState(pass, uint16_t(c + 2)), channelArrays[c]);
        }
        g_HdActive = true;
        LogShimA(LogLevel::Info, "terrain-hd",
            "[TERRAIN-HD] detail tuning material=\"%s\" contrast=%.3f normalStrength=%.3f nearScale=%.3f",
            g_HdSourceMaterial.c_str(), binding->detail.contrast, binding->detail.normalStrength, binding->detail.nearNormalScale);
        LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] shared native material installed source=\"%s\" passes=%zu meshes=%zu size=%ux%u slices=%u packedUV=exact",
            g_HdSourceMaterial.c_str(), g_HdPasses.size(), g_HdStreams.size(), g_proxy.hdWidth, g_proxy.hdHeight, g_proxy.hdSliceCount);
        if (g_HdPaint.enabled) LogShimA(LogLevel::Info, "terrain-hd",
            "[TERRAIN-PAINT] %u-layer diffuse installed weights=%s coordinates=native-world-XZ alpha=opaque",
            g_HdPaint.Layers(), g_HdPaint.Layers() == 8 ? "slice4+slice13" : "slice4");
        ReleaseCloneHandoff(source); ReleaseCloneHandoff(backup); ReleaseCloneHandoff(array);
        for (auto& channel : channelArrays) ReleaseCloneHandoff(channel);
        return true;
    }
    catch (const std::exception& error)
    {
        if (g_HdPaintDeferredZones) LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] native tiles deferred: %s", error.what());
        else LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] native tiles declined: %s; stock atlas retained", error.what());
    }
    catch (...) { g_HdPaintDeferredZones = 0; LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] native tiles declined after Ogre exception"); }
    ReleaseCloneHandoff(program); ReleaseCloneHandoff(source); ReleaseCloneHandoff(backup); ReleaseCloneHandoff(array);
    for (auto& channel : channelArrays) ReleaseCloneHandoff(channel);
    RestoreNativeTerrainHd(); RemoveSemanticResources("native-hd-declined");
    // A deferred paint match stays retryable: ObserveZone reinstalls when a zone is added.
    g_HdDeclined = g_HdPaintDeferredZones == 0;
    return false;
}

// Runs on the existing world-render seam, before terrain submission. Restore
// while the scene is alive; reactivation rediscoveries use the native zone seam.
void UpdateNativeTerrainHdProfile()
{
    if (!g_config.hdEnabled || g_proxy.tearingDown) return;
    if (!HdProfileAllowed())
    {
        if (!g_HdActive) return;
        RestoreNativeTerrainTessellationTest();
        RestoreNativeTerrainHd();
        RemoveSemanticResources("profile-fallback");
        g_HdProfileSuspended = true;
        LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] profile fallback restored stock atlas");
    }
    else if (g_HdProfileSuspended && !g_HdDeclined)
    {
        g_HdProfileSuspended = false;
        g_proxy.selected = false;
        LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] Enhanced resumed; native tile discovery rearmed");
    }
}
