#include "terrain_zone_guard.h"

#include <cstdint>
#include <vector>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::TerrainZones;

    struct Write
    {
        int32_t idx;
        int32_t n;
    };

    std::vector<Write> Build(const Layout& l)
    {
        std::vector<Write> out;
        BuildBounded(l, [&](int32_t idx, int32_t n) { out.push_back({ idx, n }); });
        return out;
    }

    // The stock loop, for comparison on in-range layouts.
    std::vector<Write> Stock(const Layout& l)
    {
        std::vector<Write> out;
        int32_t n = 0;
        for (int32_t z = l.minZ; z < l.minZ + l.depth; ++z)
            for (int32_t x = l.minX; x < l.minX + l.width; ++x)
                out.push_back({ (z + 24) * 128 + 24 + x, n++ });
        return out;
    }

    bool Same(const std::vector<Write>& a, const std::vector<Write>& b)
    {
        if (a.size() != b.size())
            return false;
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i].idx != b[i].idx || a[i].n != b[i].n)
                return false;
        return true;
    }

    void TestInRangeMatchesStock()
    {
        const Layout layouts[] = { { 0, 0, 4, 4 }, { 2, 3, 8, 5 }, { -24, -24, 128, 128 }, { 0, 0, 1, 1 } };
        for (const Layout& l : layouts)
        {
            CHECK(Check(l) == 0);
            CHECK(Same(Build(l), Stock(l)));
        }
    }

    void TestNegativeMinZSkipsRowsBelowTable()
    {
        // minZ zone -30: stock rows z = -30..-25 give negative indices that
        // land below heightTable (heightTable[-1] is the default zone pointer).
        const Layout l = { 0, -30, 4, 10 };
        CHECK(Check(l) == kMinZLow);
        const std::vector<Write> stock = Stock(l);
        bool stockNegative = false;
        for (const Write& w : stock)
            stockNegative = stockNegative || w.idx < 0;
        CHECK(stockNegative);

        const std::vector<Write> bounded = Build(l);
        CHECK(bounded.size() == 4u * 4u);  // z = -24..-21
        for (const Write& w : bounded)
        {
            CHECK(w.idx >= 0 && w.idx < kTableEntries);
            // Stock numbering: zone (x, z) is n = (z - minZ) * width + (x - minX).
        }
        CHECK(bounded.front().n == 6 * 4);  // z = -24 is the 7th row
        CHECK(bounded.front().idx == 24);
    }

    void TestHighAndWideLayouts()
    {
        // MinZ + Depth past 103: rows above the table are skipped.
        const Layout high = { 0, 100, 2, 10 };
        CHECK(Check(high) == kMaxZHigh);
        const std::vector<Write> h = Build(high);
        CHECK(h.size() == 2u * 4u);  // z = 100..103
        for (const Write& w : h)
            CHECK(w.idx >= 0 && w.idx < kTableEntries);

        // x past 103 would spill into the next row in stock.
        const Layout wide = { 100, 0, 10, 1 };
        CHECK(Check(wide) == kMaxXHigh);
        const std::vector<Write> w = Build(wide);
        CHECK(w.size() == 4u);
        CHECK(w.back().n == 3);

        const Layout lowX = { -30, 0, 8, 1 };
        CHECK(Check(lowX) == kMinXLow);
        const std::vector<Write> lx = Build(lowX);
        CHECK(lx.size() == 2u);  // x = -24, -23
        CHECK(lx.front().n == 6);
        CHECK(lx.front().idx == 24 * 128);

        // A corrupt huge layout is bounded by the table, not by the area.
        const Layout huge = { -1000000, -1000000, 2000000, 2000000 };
        CHECK(Check(huge) == (kMinXLow | kMaxXHigh | kMinZLow | kMaxZHigh));
        CHECK(Build(huge).size() == static_cast<size_t>(kTableEntries));

        const Layout empty = { 500, 500, 0, 3 };
        CHECK(Check(empty) == 0);
        CHECK(Build(empty).empty());
    }

    void TestBounds()
    {
        const Layout l = { 2, 3, 8, 5 };
        const Bounds b = ComputeBounds(l, 5.0f);
        CHECK(b.minXUnits == 2 * 256);
        CHECK(b.maxXUnits == 10 * 256);
        CHECK(b.minZUnits == 3 * 256);
        CHECK(b.maxZUnits == 8 * 256);
        CHECK(b.minXMeters == 2560.0f);
        CHECK(b.maxZMeters == 10240.0f);
        const Layout neg = { 0, -30, 4, 10 };
        const Bounds nb = ComputeBounds(neg, 5.0f);
        CHECK(nb.minZUnits == -30 * 256);
        CHECK(nb.maxZUnits == -20 * 256);
    }

    void TestZonePointer()
    {
        const uintptr_t def = 0x02C119D0;
        const uintptr_t hg2 = 0x10000000;
        const uint32_t size = kHg2Header + 4 * kHg2ZoneBytes;  // 4 zones
        CHECK(ZonePointerValid(def, def, hg2, size));
        CHECK(ZonePointerValid(def, def, 0, 0));
        CHECK(ZonePointerValid(hg2 + 0xC, def, hg2, size));
        CHECK(ZonePointerValid(hg2 + 0xC + 3 * kHg2ZoneBytes, def, hg2, size));
        CHECK(!ZonePointerValid(hg2 + 0xC + 4 * kHg2ZoneBytes, def, hg2, size));  // past the end
        CHECK(!ZonePointerValid(hg2 + 0xC + 2, def, hg2, size));                  // not a block start
        CHECK(!ZonePointerValid(hg2, def, hg2, size));                            // the header
        CHECK(!ZonePointerValid(0, def, hg2, size));
        CHECK(!ZonePointerValid(0x12345678, def, hg2, size));
        CHECK(!ZonePointerValid(hg2 + 0xC, def, 0, 0));        // no hg2 loaded
        CHECK(!ZonePointerValid(hg2 + 0xC, def, hg2, 0x100));  // hg2 smaller than one zone
    }

    void TestLocate()
    {
        // Stock: idx = (z >> 8) * 128 + (x >> 8) + 0xC18, offset from the low bytes.
        Sample s = Locate(0x0123, 0x0456);
        CHECK(s.index == 4 * 128 + 1 + 0xC18);
        CHECK(s.offset == 0x56u * 0x100u + 0x23u);
        CHECK(s.inTable);
        // Off map, negative: arithmetic shift, out of the table.
        s = Locate(0xFFFF0000u, 0);
        CHECK(s.index == -256 + 0xC18);
        CHECK(s.inTable);
        s = Locate(0, 0xFFF00000u);
        CHECK(!s.inTable);
        s = Locate(0x00200000u, 0x00200000u);
        CHECK(!s.inTable);
    }

    void TestHg2Truncated()
    {
        const Layout l = { 0, 0, 2, 2 };
        CHECK(!Hg2Truncated(0x1000, kHg2Header + 4 * kHg2ZoneBytes, l));
        CHECK(Hg2Truncated(0x1000, kHg2Header + 3 * kHg2ZoneBytes, l));
        CHECK(!Hg2Truncated(0, 0, l));
    }
}

int main()
{
    TestInRangeMatchesStock();
    TestNegativeMinZSkipsRowsBelowTable();
    TestHighAndWideLayouts();
    TestBounds();
    TestZonePointer();
    TestLocate();
    TestHg2Truncated();
    return OpenShimTest::ExitCode();
}
