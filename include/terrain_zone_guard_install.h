#pragma once
// Installers for the terrain zone table guards. See terrain_zone_guard.h.

namespace BZROpenShim
{
    namespace TerrainZones
    {
        // [Fixes] TerrainZoneTableGuard: detours the zone-table build
        // (0x0077E230) so zones outside the 128x128 table are skipped instead
        // of written past it, and logs a truncated .hg2. Fail-closed.
        void InstallTerrainZoneTableGuardIfPossible();

        // [Fixes] TerrainHeightSampleGuard: replaces the height sampler
        // (0x00784100) with one that only reads a zone pointer it can prove
        // (the default zone or a whole block of the loaded .hg2). Fail-closed.
        void InstallTerrainHeightSampleGuardIfPossible();
    }
}
