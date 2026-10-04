// Read-only authoring capture, reached only after terrain_proxy's exact-build
// engine/Ogre gates. Capture before HD changes the native diffuse binding.
void ExportNativeTerrainAtlas()
{
    static bool attempted = false;
    if (attempted) return;
    attempted = true; // One authoring capture per fresh game process.
    OgreSharedPtr material;
    try
    {
        const std::filesystem::path path(g_config.hdExportPath);
        if (!path.is_absolute()) throw std::runtime_error("atlas export needs an absolute output path");
        RenderOperation operation = {}; void* sub = nullptr;
        if (!GetEntityOperation(g_proxy.sourceEntity, operation, sub) ||
            !g_ogre.getTextureWidth || !g_ogre.getTextureHeight || !g_ogre.getTextureDepth)
            throw std::runtime_error("atlas export APIs unavailable");
        const std::string name = *g_ogre.getMaterialName(sub);
        g_ogre.getMaterialByName(g_ogre.getMaterialManager(), &material, name, std::string("Autodetect"));
        const auto getTexture = Resolve<HdGetTexture>(GetModuleHandleW(L"OgreMain.dll"),
            "?_getTexturePtr@TextureUnitState@Ogre@@QBEABV?$SharedPtr@VTexture@Ogre@@@2@XZ");
        if (!material.rep || !getTexture || !g_ogre.getNumTechniques(material.rep))
            throw std::runtime_error("atlas export material unavailable");
        void* technique = g_ogre.getTechnique(material.rep, 0);
        if (!g_ogre.getNumPasses(technique)) throw std::runtime_error("atlas export pass unavailable");
        void* pass = g_ogre.getPass(technique, 0);
        if (!g_ogre.getNumTextureUnitStates(pass)) throw std::runtime_error("atlas export diffuse unavailable");
        const auto* texture = getTexture(g_ogre.getTextureUnitState(pass, 0));
        if (!texture || !texture->rep || g_ogre.getTextureDepth(texture->rep) != 1)
            throw std::runtime_error("atlas export requires the original 2D diffuse texture");
        nlohmann::json root = {
            {"schema", "bzr-openshim-terrain-atlas-v1"}, {"material", name},
            {"diffuseResource", *g_ogre.getResourceName(texture->rep)},
            {"width", g_ogre.getTextureWidth(texture->rep)},
            {"height", g_ogre.getTextureHeight(texture->rep)},
            {"tiles", nlohmann::json::object()}, {"usedIndices", nlohmann::json::array()}
        };
        root["paintMap"] = CaptureTerrainPaintMap();
        void* manager = g_terrainManager();
        if (!manager) throw std::runtime_error("atlas export terrain manager unavailable");
        // The validated released-build table has 256 entries. CSV row order
        // does not define this table's semantic tile indices.
        for (uint32_t index = 0; index < 256; ++index)
        {
            const AtlasRect* r = g_atlasRectAt(manager, index);
            if (r && std::isfinite(r->u) && std::isfinite(r->v) &&
                std::isfinite(r->w) && std::isfinite(r->h) && r->u >= 0 && r->v >= 0 &&
                r->w > 0 && r->h > 0 && r->u + r->w <= 1.000001f && r->v + r->h <= 1.000001f)
                root["tiles"][std::to_string(index)] = {r->u, r->v, r->w, r->h};
        }
        std::set<uint8_t> used;
        NativeHdContext c = {};
        if (!SafeReadIntAddress(Rebase(kTerrainOriginXVa), c.originX) ||
            !SafeReadIntAddress(Rebase(kTerrainOriginZVa), c.originZ))
            throw std::runtime_error("atlas export origin unavailable");
        for (const auto& zone : g_zoneOrdinals)
        {
            if (!SafeReadZoneInt(zone.first, kZoneXOffset, c.zoneX) ||
                !SafeReadZoneInt(zone.first, kZoneZOffset, c.zoneZ))
                throw std::runtime_error("atlas export zone unavailable");
            for (c.clusterX = 0; c.clusterX < kClusterAxisCount; ++c.clusterX)
            for (c.clusterZ = 0; c.clusterZ < kClusterAxisCount; ++c.clusterZ)
            for (int x = 0; x < 16; ++x)
            for (int z = 0; z < 16; ++z)
            {
                TerrainSemantic::Cell cell;
                if (!ProvideNativeHdCell(&c, x, z, cell)) throw std::runtime_error("atlas export cell unavailable");
                if (!root["tiles"].contains(std::to_string(cell.tileIndex)))
                    throw std::runtime_error("atlas export used tile has an invalid rectangle");
                used.insert(cell.tileIndex);
            }
        }
        for (const auto index : used) root["usedIndices"].push_back(index);
        std::ofstream output(path, std::ios::binary | std::ios::trunc);
        output << root.dump(2) << '\n';
        output.close();
        if (!output) throw std::runtime_error("atlas export output could not be written");
        LogShimA(LogLevel::Info, "terrain-hd", "[TERRAIN-HD] atlas exported material=%s tiles=%zu used=%zu path=\"%s\"",
            name.c_str(), root["tiles"].size(), used.size(), path.string().c_str());
    }
    catch (const std::exception& error)
    {
        LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] atlas export declined: %s", error.what());
    }
    catch (...) { LogShimA(LogLevel::Warn, "terrain-hd", "[TERRAIN-HD] atlas export declined after Ogre exception"); }
    ReleaseCloneHandoff(material);
}
