// Included after native ClusterCandidate resolution. Render metadata only;
// native terrain height/index buffers and gameplay terrain are never written.
struct TerrainReliefBounds
{
    void* mesh;
    AxisAlignedBox original, expanded;
    float originalRadius, expandedRadius;
};
std::map<std::string, TerrainReliefBounds> g_ReliefBounds;
bool g_ReliefBoundsActive = false;

bool TerrainReliefBoundsEqual(const AxisAlignedBox& a, const AxisAlignedBox& b)
{
    return a.extent == b.extent && a.minimum.x == b.minimum.x && a.minimum.y == b.minimum.y &&
        a.minimum.z == b.minimum.z && a.maximum.x == b.maximum.x && a.maximum.y == b.maximum.y &&
        a.maximum.z == b.maximum.z;
}

void UpdateTerrainReliefZoneBounds(void* zone)
{
    int zoneX = 0, zoneZ = 0;
    if (!SafeReadZoneInt(zone, kZoneXOffset, zoneX) || !SafeReadZoneInt(zone, kZoneZOffset, zoneZ))
        throw std::runtime_error("relief zone bounds identity unreadable");
    using NeedUpdate = void (__thiscall*)(void*, bool);
    auto update = Resolve<NeedUpdate>(GetModuleHandleW(L"OgreMain.dll"), "?needUpdate@Node@Ogre@@UAEX_N@Z");
    if (!update) throw std::runtime_error("relief node bounds invalidation unavailable");
    for (int x = 0; x < kClusterAxisCount; ++x)
    for (int z = 0; z < kClusterAxisCount; ++z)
    {
        ClusterCandidate candidate;
        bool abort = false;
        if (!ResolveClusterCandidate(zone, zoneX, zoneZ, x, z, candidate, abort))
        {
            if (abort) throw std::runtime_error("relief cluster bounds identity declined");
            continue; // native zone can be partially constructed
        }
        const auto* scale = g_ogre.getNodeScale(candidate.node);
        const auto* rotation = g_ogre.getNodeOrientation(candidate.node);
        const auto* position = g_ogre.getNodePosition(candidate.node);
        if (!scale || !rotation || scale->x != 1 || scale->y != 1 || scale->z != 1 ||
            rotation->x != 0 || rotation->y != 0 || rotation->z != 0 || std::abs(rotation->w) != 1)
            throw std::runtime_error("relief requires translation-only native terrain nodes");
        if (!position || !std::isfinite(position->x) || !std::isfinite(position->z) ||
            std::abs(position->x / 80.0f - std::round(position->x / 80.0f)) > 1e-5f ||
            std::abs(position->z / 80.0f - std::round(position->z / 80.0f)) > 1e-5f)
            throw std::runtime_error("relief cluster phase translation contract unavailable");
        const auto* current = g_ogre.getBounds(candidate.mesh);
        if (!current || current->extent != kAabbExtentFinite ||
            !std::isfinite(current->minimum.y) || !std::isfinite(current->maximum.y))
            throw std::runtime_error("relief finite mesh bounds unavailable");
        auto found = g_ReliefBounds.find(candidate.meshName);
        if (found != g_ReliefBounds.end() && found->second.mesh == candidate.mesh &&
            TerrainReliefBoundsEqual(*current, found->second.expanded))
            continue;
        // A native full rebuild can replace mesh identity or its bounds. Save
        // that fresh baseline, then pad once; never accumulate displacement.
        TerrainReliefBounds saved = { candidate.mesh, *current, *current,
            g_ogre.getRadius(candidate.mesh), 0 };
        saved.expanded.minimum.y -= g_config.microReliefAmplitude;
        saved.expanded.maximum.y += g_config.microReliefAmplitude;
        saved.expandedRadius = saved.originalRadius + g_config.microReliefAmplitude;
        g_ReliefBounds[candidate.meshName] = saved;
        g_ogre.setBounds(candidate.mesh, saved.expanded, false);
        g_ogre.setRadius(candidate.mesh, saved.expandedRadius);
        update(candidate.node, true);
    }
}

bool PrepareTerrainMicroReliefBounds()
{
    try
    {
        auto lookup = Resolve<FnGetMaterialByName>(GetModuleHandleW(L"OgreMain.dll"),
            "?getByName@MeshManager@Ogre@@QAE?AV?$SharedPtr@VMesh@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
        if (!lookup) return false; // require a restoration path before mutation
        for (const auto& zone : g_zoneOrdinals) UpdateTerrainReliefZoneBounds(zone.first);
        if (g_ReliefBounds.empty()) return false;
        g_ReliefBoundsActive = true;
        LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] micro-relief render bounds padded meshes=%zu amplitude=%.3f", g_ReliefBounds.size(), g_config.microReliefAmplitude);
        return true;
    }
    catch (...) { RestoreTerrainMicroReliefBounds(); return false; }
}

void RefreshTerrainMicroReliefBounds(void* zone)
{
    if (!g_ReliefBoundsActive) return;
    try { UpdateTerrainReliefZoneBounds(zone); }
    catch (...)
    {
        // Retire displacement before rendering a new unqualified cluster.
        LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] micro-relief bounds refresh declined; restoring native terrain");
        RestoreNativeTerrainTessellationTest();
        g_proxy.semanticMaterialInstalled = false;
        g_proxy.semanticMaterialUnsupported = true;
    }
}

void RestoreTerrainMicroReliefBounds()
{
    g_ReliefBoundsActive = false;
    if (g_ReliefBounds.empty()) return;
    HMODULE ogre = GetModuleHandleW(L"OgreMain.dll");
    auto getMesh = Resolve<FnGetMaterialByName>(ogre,
        "?getByName@MeshManager@Ogre@@QAE?AV?$SharedPtr@VMesh@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
    unsigned restored = 0;
    if (ogre && getMesh)
    for (const auto& entry : g_ReliefBounds)
    {
        OgreSharedPtr mesh;
        try
        {
            getMesh(g_ogre.getMeshManager(), &mesh, entry.first, std::string("Autodetect"));
            if (mesh.rep == entry.second.mesh &&
                TerrainReliefBoundsEqual(*g_ogre.getBounds(mesh.rep), entry.second.expanded))
            {
                g_ogre.setBounds(mesh.rep, entry.second.original, false);
                if (g_ogre.getRadius(mesh.rep) == entry.second.expandedRadius)
                    g_ogre.setRadius(mesh.rep, entry.second.originalRadius);
                ++restored;
            }
            ReleaseCloneHandoff(mesh);
        }
        catch (...) { ReleaseCloneHandoff(mesh); }
    }
    LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] micro-relief render bounds restored meshes=%u tracked=%zu", restored, g_ReliefBounds.size());
    g_ReliefBounds.clear();
}
