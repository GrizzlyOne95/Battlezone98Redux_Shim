// Native HD diffuse tiles. Included after ClusterCandidate and semantic decoding.
// Geometry, native heights, gameplay and stock non-diffuse maps are unchanged.
struct NativeHdStream
{
    void* mesh; VertexDataPrefix* data; void* buffer;
};
struct NativeHdPass
{
    uint16_t technique, pass;
    std::string vertex, fragment;
};
std::map<std::string, NativeHdStream> g_HdStreams;
std::vector<NativeHdPass> g_HdPasses;
std::string g_HdSourceMaterial, g_HdBackupMaterial;
bool g_HdActive = false, g_HdDeclined = false;
void ResetNativeTerrainHd() { g_HdDeclined = false; }

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
        !TerrainHdApiAvailable())
        throw std::runtime_error("native HD APIs/restoration unavailable");
}

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
        if (!AddSharedReference(parameters)) throw std::runtime_error("native HD parameter handoff failed");
        setParameters(destination, parameters);
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
            }
            materialRestored = true;
            LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] shared native material restored passes=%zu", g_HdPasses.size());
        }
    }
    catch (...) { LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] material restoration declined"); }
    ReleaseCloneHandoff(source); ReleaseCloneHandoff(backup);
    unsigned restored = 0;
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
                void* manager = bufferManager;
                cleanBinding = g_hdCreateBinding(manager);
                if (!cleanBinding) throw std::runtime_error("HD restoration binding unavailable");
                // Preserve the CURRENT native buffers, including engine rebuilds.
                for (uint16_t slot = 0; slot < 3; ++slot)
                    g_ogre.setVertexBinding(cleanBinding, slot, *g_ogre.getBuffer(data->binding, slot));
                g_hdCopyBinding(data->binding, cleanBinding);
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
        "[TERRAIN-HD] native streams restored meshes=%u tracked=%zu", restored, g_HdStreams.size());
    g_HdStreams.clear(); g_HdPasses.clear(); g_HdSourceMaterial.clear();
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
        !SafeReadIntAddress(Rebase(kTerrainOriginXVa), c.originX) ||
        !SafeReadIntAddress(Rebase(kTerrainOriginZVa), c.originZ))
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
        std::vector<TerrainSemantic::GpuVertex> upload;
        for (const auto& v : vertices)
        {
            if (v.gpu.tileIndex >= g_proxy.hdSliceCount) throw std::runtime_error("native HD manifest slice missing");
            upload.push_back(v.gpu);
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
                sizeof(TerrainSemantic::GpuVertex), uint32_t(upload.size()), 14, false);
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

bool InstallNativeTerrainHd()
{
    if (!g_config.hdEnabled || g_HdDeclined) return false;
    if (g_HdActive) return true;
    OgreSharedPtr source, backup, array, program;
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
        g_proxy.generation = ++g_resourceSerial;
        g_proxy.semanticMaterialGeneration = ++g_semanticMaterialSerial;
        g_proxy.semanticMaterialName = "OpenShim/TerrainNativeHD/Backup/" + std::to_string(g_proxy.semanticMaterialGeneration);
        g_ogre.getMaterialByName(g_ogre.getMaterialManager(), &source, g_proxy.materialName, std::string("Autodetect"));
        if (!source.rep) throw std::runtime_error("native HD material unavailable");
        if (!binding->diffuseResource.empty())
        {
            if (!g_ogre.getNumTechniques(source.rep)) throw std::runtime_error("native HD source technique unavailable");
            void* technique = g_ogre.getTechnique(source.rep, 0);
            if (!g_ogre.getNumPasses(technique)) throw std::runtime_error("native HD source pass unavailable");
            void* pass = g_ogre.getPass(technique, 0);
            if (!g_ogre.getNumTextureUnitStates(pass)) throw std::runtime_error("native HD source diffuse unavailable");
            const auto* name = g_hdGetTextureName(g_ogre.getTextureUnitState(pass, 0));
            if (!name || *name != binding->diffuseResource)
                throw std::runtime_error("native HD source atlas does not match pack: expected=" +
                    binding->diffuseResource + " actual=" + (name ? *name : "<unavailable>"));
        }
        g_ogre.cloneMaterial(source.rep, &backup, g_proxy.semanticMaterialName, false, std::string());
        if (!backup.rep) throw std::runtime_error("native HD backup unavailable");
        ++g_semanticMaterialCreated;
        g_HdBackupMaterial = g_proxy.semanticMaterialName;
        NativeHdContext selected = {0,0,g_proxy.zoneX,g_proxy.zoneZ,g_proxy.clusterX,g_proxy.clusterZ};
        if (!SafeReadIntAddress(Rebase(kTerrainOriginXVa), selected.originX) ||
            !SafeReadIntAddress(Rebase(kTerrainOriginZVa), selected.originZ) ||
            !TerrainSemantic::BuildVertices(ProvideNativeHdCell, &selected, g_proxy.semanticVertices))
            throw std::runtime_error("native HD selected tile semantics unavailable");
        if (!BuildTerrainHdTextureArray(*binding, array)) throw std::runtime_error("native HD texture array declined");
        std::map<std::string, std::string> cache;
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
            const std::string name = "OpenShim/TerrainNativeHD/" + std::to_string(g_proxy.semanticMaterialGeneration) +
                "/" + SourceHashSuffix(key + generated + defines);
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
            ReleaseCloneHandoff(program); cache.emplace(key, name); return name;
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
                if (!name || *name != binding->diffuseResource) continue;
            }
            const std::string vs = generate(g_ogre.getVertexProgram(pass), false);
            if (vs.empty()) continue;
            const std::string ps = generate(g_ogre.getFragmentProgram(pass), true);
            if (ps.empty() || !g_ogre.getNumTextureUnitStates(pass)) throw std::runtime_error("native HD matching fragment unavailable");
            g_HdPasses.push_back({t,p,vs,ps});
        }
        if (g_HdPasses.empty()) throw std::runtime_error("native HD compatible terrain passes unavailable");
        for (const auto& zone : g_zoneOrdinals) UpdateNativeHdZone(zone.first, false);
        if (g_HdStreams.empty()) throw std::runtime_error("native HD compatible clusters unavailable");
        g_HdSourceMaterial = g_proxy.materialName; // rollback before first write
        for (const auto& saved : g_HdPasses)
        {
            void* pass = g_ogre.getPass(g_ogre.getTechnique(source.rep, saved.technique), saved.pass);
            void* original = g_ogre.getPass(g_ogre.getTechnique(backup.rep, saved.technique), saved.pass);
            CopyHdPrograms(pass, original, saved.vertex, saved.fragment);
            g_ogre.setTexture(g_ogre.getTextureUnitState(pass, 0), array);
        }
        g_HdActive = true;
        LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] shared native material installed source=\"%s\" passes=%zu meshes=%zu size=%ux%u slices=%u packedUV=exact",
            g_HdSourceMaterial.c_str(), g_HdPasses.size(), g_HdStreams.size(), g_proxy.hdWidth, g_proxy.hdHeight, g_proxy.hdSliceCount);
        ReleaseCloneHandoff(source); ReleaseCloneHandoff(backup); ReleaseCloneHandoff(array);
        return true;
    }
    catch (const std::exception& error) { LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] native tiles declined: %s; stock atlas retained", error.what()); }
    catch (...) { LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] native tiles declined after Ogre exception"); }
    ReleaseCloneHandoff(program); ReleaseCloneHandoff(source); ReleaseCloneHandoff(backup); ReleaseCloneHandoff(array);
    RestoreNativeTerrainHd(); RemoveSemanticResources("native-hd-declined");
    g_HdDeclined = true;
    return false;
}
