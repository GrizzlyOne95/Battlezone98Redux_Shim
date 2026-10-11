// Runtime map identity, shared by the read-only exporter and paint activation.
// Only called behind the existing released engine/Ogre gates.
nlohmann::json CaptureTerrainPaintMap()
{
    int originX = 0, originZ = 0;
    if (!g_heightAt || g_zoneOrdinals.empty() || g_zoneOrdinals.size() > 256 ||
        !SafeReadIntAddress(Rebase(kTerrainOriginXVa), originX) ||
        !SafeReadIntAddress(Rebase(kTerrainOriginZVa), originZ))
        throw std::runtime_error("paint map origin/height reader unavailable");
    std::map<std::pair<int, int>, void*> zones;
    for (const auto& zone : g_zoneOrdinals)
    {
        int x = 0, z = 0;
        if (!SafeReadZoneInt(zone.first, kZoneXOffset, x) || !SafeReadZoneInt(zone.first, kZoneZOffset, z) ||
            std::abs(x) > 256 || std::abs(z) > 256 || !zones.emplace(std::make_pair(x,z), zone.first).second)
            throw std::runtime_error("paint map zone identity invalid");
    }
    std::uint64_t hash = UINT64_C(14695981039346656037);
    // The engine may relocate its terrain sample storage between launches.
    // Origins address that storage; they are not world/map identity. Hash the
    // canonical zone coordinates and values, never the relocation bias.
    TerrainPaint::HashU32(hash, uint32_t(zones.size()));
    std::uint64_t heightHash = UINT64_C(14695981039346656037);
    std::array<float, 4> bounds = {1000000,1000000,-1000000,-1000000};
    for (const auto& zone : zones)
    {
        const int zx = zone.first.first, zz = zone.first.second;
        TerrainPaint::HashU32(hash, uint32_t(zx)); TerrainPaint::HashU32(hash, uint32_t(zz));
        const int baseX = zx * 256 + originX - 128, baseZ = zz * 256 + originZ - 128;
        // Hash every native height sample. Stock material words can vary between
        // launches and are independent of the new painted appearance.
        // Canonical coordinate order is independent of resource addresses/load order.
        for (int z = 0; z < 256; ++z)
        for (int x = 0; x < 256; ++x)
        {
            const auto height = g_heightAt(baseX+x, baseZ+z);
            TerrainPaint::HashU32(hash, height); TerrainPaint::HashU32(heightHash, height);
        }
        for (int x = 0; x < kClusterAxisCount; ++x)
        for (int z = 0; z < kClusterAxisCount; ++z)
        {
            ClusterCandidate candidate; bool abort = false;
            if (!ResolveClusterCandidate(zone.second, zx, zz, x, z, candidate, abort))
                throw std::runtime_error("paint map requires all native clusters ready");
            const auto* b = g_ogre.getBounds(candidate.mesh);
            const auto* p = g_ogre.getNodePosition(candidate.node);
            const auto* s = g_ogre.getNodeScale(candidate.node);
            const auto* q = g_ogre.getNodeOrientation(candidate.node);
            if (!b || b->extent != kAabbExtentFinite || !p || !s || !q ||
                s->x != 1 || s->y != 1 || s->z != 1 || q->x != 0 || q->y != 0 || q->z != 0 || std::abs(q->w) != 1)
                throw std::runtime_error("paint map requires translation-only native clusters");
            const auto low = TerrainPaint::WorldXZ(b->minimum.x, b->minimum.z, p->x, p->z);
            const auto high = TerrainPaint::WorldXZ(b->maximum.x, b->maximum.z, p->x, p->z);
            bounds[0] = (std::min)(bounds[0], low[0]); bounds[1] = (std::min)(bounds[1], low[1]);
            bounds[2] = (std::max)(bounds[2], high[0]); bounds[3] = (std::max)(bounds[3], high[1]);
        }
    }
    return {{"terrainFingerprint", TerrainPaint::HashString(hash)}, {"boundsMeters", bounds},
        {"zoneCount", zones.size()}, {"rowZero", "minZ"}, {"originSamples", {originX,originZ}},
        {"heightFingerprint", TerrainPaint::HashString(heightHash)}};
}
