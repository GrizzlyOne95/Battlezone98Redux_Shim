// terrain_zone_guard.h -- engine-independent logic for the terrain zone
// table guards (src/patches/terrain_zone_guard.cpp).
//
// GOG Redux 2.2.301. The TRN parser (0x00786340) stores the playable area in
// 1280 m zones: minX 0x02CC40B0, minZ 0x02CC40AC, width 0x02CC40A8, depth
// 0x02CC40B4. The zone-table build (0x0077E230) then writes, for every zone
// n = 0, 1, ... in z-major order,
//   idx = (z + 24) * 128 + 24 + x
//   heightTable[idx]   = hg2 + 0xC + n * 0x20000      (0x02CC5108, 0x4000 entries)
//   materialTable[idx] = mat + n * 0x2000             (0x02CD99A0, 0x4000 entries)
// with no bounds check. A zone with z + 24 outside 0..127 writes outside the
// tables; x + 24 outside 0..127 lands in another row. The height sampler
// (0x00784100) reads heightTable[idx] for idx 0..0x3FFF and the default zone
// pointer 0x02CC5104 (heightTable[-1]) otherwise.
//
// Header-only and free of Windows and engine dependencies so that
// tests/terrain_zone_guard_tests.cpp can drive it with fakes.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace BZROpenShim
{
namespace TerrainZones
{
    constexpr int32_t kZoneOrigin = 24;     // table column/row of zone 0
    constexpr int32_t kTableSide = 128;     // zones per table row and column
    constexpr int32_t kTableEntries = kTableSide * kTableSide;  // 0x4000
    constexpr int32_t kMinZone = -kZoneOrigin;                   // -24
    constexpr int32_t kMaxZone = kTableSide - kZoneOrigin - 1;   // 103
    constexpr uint32_t kHg2Header = 0xC;
    constexpr uint32_t kHg2ZoneBytes = 0x20000;

    struct Layout
    {
        int32_t minX;
        int32_t minZ;
        int32_t width;
        int32_t depth;
    };

    // Which TRN value pushes zones out of kMinZone..kMaxZone; 0 = in range.
    enum OutOfRange : uint32_t
    {
        kMinXLow = 1u << 0,   // MinX zone below -24
        kMaxXHigh = 1u << 1,  // MinX + Width reaches past 103
        kMinZLow = 1u << 2,   // MinZ zone below -24
        kMaxZHigh = 1u << 3,  // MinZ + Depth reaches past 103
    };

    // An empty area (width or depth <= 0) writes nothing, as stock.
    inline uint32_t Check(const Layout& l)
    {
        if (l.width <= 0 || l.depth <= 0)
            return 0;
        uint32_t bits = 0;
        const int64_t endX = static_cast<int64_t>(l.minX) + l.width - 1;
        const int64_t endZ = static_cast<int64_t>(l.minZ) + l.depth - 1;
        if (l.minX < kMinZone) bits |= kMinXLow;
        if (endX > kMaxZone) bits |= kMaxXHigh;
        if (l.minZ < kMinZone) bits |= kMinZLow;
        if (endZ > kMaxZone) bits |= kMaxZHigh;
        return bits;
    }

    inline bool ZoneInRange(int32_t x, int32_t z)
    {
        return x >= kMinZone && x <= kMaxZone && z >= kMinZone && z <= kMaxZone;
    }

    inline int32_t TableIndex(int32_t x, int32_t z) { return (z + kZoneOrigin) * kTableSide + kZoneOrigin + x; }

    // The stock zone loop with out-of-range zones skipped. n keeps the stock
    // count (z-major, every zone of the area), so each in-range zone gets the
    // same hg2/mat block stock gives it. Only in-range rows and columns are
    // visited, so a huge corrupt layout does not loop for long.
    // write(idx, n) stores heightTable[idx] / materialTable[idx] for zone n.
    template <typename Write>
    inline uint32_t BuildBounded(const Layout& l, Write write)
    {
        if (l.width <= 0 || l.depth <= 0)
            return 0;
        const int64_t endX = static_cast<int64_t>(l.minX) + l.width;  // exclusive
        const int64_t endZ = static_cast<int64_t>(l.minZ) + l.depth;
        const int64_t x0 = l.minX > kMinZone ? l.minX : kMinZone;
        const int64_t z0 = l.minZ > kMinZone ? l.minZ : kMinZone;
        const int64_t x1 = endX < kMaxZone + 1 ? endX : kMaxZone + 1;
        const int64_t z1 = endZ < kMaxZone + 1 ? endZ : kMaxZone + 1;
        uint32_t written = 0;
        for (int64_t z = z0; z < z1; ++z)
        {
            for (int64_t x = x0; x < x1; ++x)
            {
                const int64_t n = (z - l.minZ) * l.width + (x - l.minX);
                write(TableIndex(static_cast<int32_t>(x), static_cast<int32_t>(z)), static_cast<int32_t>(n));
                ++written;
            }
        }
        return written;
    }

    // The eight globals stock sets after the zone loop (0x0077E3FA..), from
    // the loop locals minX, minX + width, minZ, minZ + depth.
    struct Bounds
    {
        int32_t minXUnits;   // 0x02CE99C0 = minX << 8
        int32_t maxXUnits;   // 0x02CE99A0 = (minX + width) * 256
        int32_t minZUnits;   // 0x02CD9984 = minZ << 8
        int32_t maxZUnits;   // 0x02CE99C4 = (minZ + depth) * 256
        float minXMeters;    // 0x02CD912C = (float)minXUnits * 5.0f
        float maxXMeters;    // 0x02CD9124
        float minZMeters;    // 0x02CD9130
        float maxZMeters;    // 0x02CD9128
    };

    inline Bounds ComputeBounds(const Layout& l, float scale)
    {
        // Stock does these in 32-bit int (shl / imul wrap).
        const uint32_t ex = static_cast<uint32_t>(l.minX) + static_cast<uint32_t>(l.width);
        const uint32_t ez = static_cast<uint32_t>(l.minZ) + static_cast<uint32_t>(l.depth);
        Bounds b;
        b.minXUnits = static_cast<int32_t>(static_cast<uint32_t>(l.minX) << 8);
        b.maxXUnits = static_cast<int32_t>(ex << 8);
        b.minZUnits = static_cast<int32_t>(static_cast<uint32_t>(l.minZ) << 8);
        b.maxZUnits = static_cast<int32_t>(ez << 8);
        b.minXMeters = static_cast<float>(b.minXUnits) * scale;
        b.maxXMeters = static_cast<float>(b.maxXUnits) * scale;
        b.minZMeters = static_cast<float>(b.minZUnits) * scale;
        b.maxZMeters = static_cast<float>(b.maxZUnits) * scale;
        return b;
    }

    // ---- height sampler (0x00784100) --------------------------------------

    // A height-table pointer is valid when it is the default zone or the
    // start of a whole zone block inside the loaded hg2 buffer.
    inline bool ZonePointerValid(uintptr_t p, uintptr_t defaultZone, uintptr_t hg2, uint32_t hg2Size)
    {
        if (p == defaultZone)
            return true;
        if (hg2 == 0 || hg2Size < kHg2Header + kHg2ZoneBytes)
            return false;
        const uintptr_t first = hg2 + kHg2Header;
        const uintptr_t span = hg2Size - kHg2Header - kHg2ZoneBytes;  // offset of the last whole block
        const uintptr_t rel = p - first;  // wraps huge below first
        return rel <= span && (rel & (kHg2ZoneBytes - 1)) == 0;
    }

    struct Sample
    {
        int32_t index;       // table index (may be outside 0..0x3FFF)
        uint32_t offset;     // sample index inside the zone (0..0xFFFF)
        bool inTable;        // index in 0..0x3FFF
    };

    // Same arithmetic as stock: arithmetic shifts on the signed coordinates.
    inline Sample Locate(uint32_t x, uint32_t z)
    {
        Sample s;
        s.offset = (z & 0xFFu) * 0x100u + (x & 0xFFu);
        s.index = (static_cast<int32_t>(z) >> 8) * kTableSide + (static_cast<int32_t>(x) >> 8) +
                  (kZoneOrigin * kTableSide + kZoneOrigin);
        s.inTable = s.index >= 0 && s.index < kTableEntries;
        return s;
    }

    // ---- .hg2 truncation diagnostic ---------------------------------------

    inline bool Hg2Truncated(uintptr_t hg2, uint32_t hg2Size, const Layout& l)
    {
        if (hg2 == 0 || l.width <= 0 || l.depth <= 0)
            return false;
        const uint64_t need = kHg2Header + static_cast<uint64_t>(l.width) * static_cast<uint64_t>(l.depth) * kHg2ZoneBytes;
        return hg2Size < need;
    }
}
}
