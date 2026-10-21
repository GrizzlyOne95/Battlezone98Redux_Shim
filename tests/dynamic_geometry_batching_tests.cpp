// Tests for include/dynamic_geometry_batching.h: the raw-field sort
// comparator, the begin() reuse predicate, the getter decoder, the name
// cache, and a model of prepareForSubmit's sort + merge showing that piece
// reuse yields the same submitted batches as stock.
#include "dynamic_geometry_batching.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    namespace Dgb = DynamicGeometryBatching;

    const Dgb::RenderableLayout kLayout = { 0x11, 0x12 };

    struct Batch
    {
        uint8_t bytes[Dgb::kBatchSize] = {};

        template <typename T>
        void Set(uint32_t offset, T value)
        {
            std::memcpy(bytes + offset, &value, sizeof(T));
        }
    };

    Batch MakeBatch(uint8_t group, float key, uint8_t blended, uint32_t material,
                    int32_t op, uint8_t proj, uint8_t view, uint32_t index)
    {
        Batch b;
        b.bytes[Dgb::kBatchQueueGroup] = group;
        b.Set<float>(Dgb::kBatchDepthKey, key);
        b.bytes[Dgb::kBatchBlended] = blended;
        b.Set<uint32_t>(Dgb::kBatchMaterialRep, material);
        b.Set<int32_t>(Dgb::kBatchOperation, op);
        b.bytes[kLayout.identityProjection] = proj;
        b.bytes[kLayout.identityView] = view;
        b.Set<uint32_t>(Dgb::kBatchCreationIndex, index);
        b.bytes[Dgb::kBatchMergeable] = 1;
        return b;
    }

    bool Less(const Batch& a, const Batch& b, bool withDepth = true)
    {
        return Dgb::BatchLess(a.bytes, b.bytes, kLayout, withDepth);
    }

    void TestComparatorOrder()
    {
        const Batch base = MakeBatch(50, 10.0f, 0, 0x1000, 4, 0, 0, 5);
        Check(!Less(base, base), "a batch is not less than itself");
        Check(Dgb::BatchLess(nullptr, base.bytes, kLayout, true), "null sorts first");
        Check(!Dgb::BatchLess(base.bytes, nullptr, kLayout, true), "non-null vs null is false");
        Check(!Dgb::BatchLess(nullptr, nullptr, kLayout, true), "null vs null is false");

        Batch b = base;
        b.bytes[Dgb::kBatchQueueGroup] = 51;
        Check(Less(base, b) && !Less(b, base), "lower queue group first");

        b = base;
        b.Set<float>(Dgb::kBatchDepthKey, 9.0f);
        Check(Less(base, b) && !Less(b, base), "larger depth key first (far to near)");
        b.Set<uint32_t>(Dgb::kBatchMaterialRep, 0u); // would win on material if keys tied
        Check(Less(base, b), "depth key outranks material");
        Check(!Less(base, b, false) && Less(b, base, false),
              "opaque re-sort ignores the depth key");

        b = base;
        b.bytes[Dgb::kBatchBlended] = 1;
        Check(Less(base, b) && !Less(b, base), "opaque before blended at equal key");
        Check(!Less(base, b, false) && !Less(b, base, false),
              "opaque re-sort ignores blended");

        b = base;
        b.Set<uint32_t>(Dgb::kBatchMaterialRep, 0x80000000u);
        Check(Less(base, b) && !Less(b, base), "material compares unsigned");

        b = base;
        b.Set<int32_t>(Dgb::kBatchOperation, -1);
        Check(Less(b, base) && !Less(base, b), "operation compares signed");

        b = base;
        b.bytes[kLayout.identityProjection] = 1;
        Check(Less(base, b) && !Less(b, base), "identity projection ascending");
        b = base;
        b.bytes[kLayout.identityView] = 1;
        Check(Less(base, b) && !Less(b, base), "identity view ascending");

        b = base;
        b.Set<uint32_t>(Dgb::kBatchCreationIndex, 6);
        Check(Less(base, b) && !Less(b, base), "creation index is the final tie-break");

        // comiss semantics: a NaN key is neither greater nor smaller, so the
        // compare falls through to the next field.
        b = base;
        b.Set<float>(Dgb::kBatchDepthKey, std::numeric_limits<float>::quiet_NaN());
        b.Set<uint32_t>(Dgb::kBatchCreationIndex, 9);
        Check(Less(base, b) && !Less(b, base), "NaN key falls through to later fields");
    }

    void TestDecodeGetter()
    {
        const uint8_t ok[] = { 0x8A, 0x41, 0x11, 0xC3 };
        const uint8_t bad1[] = { 0x8A, 0x41, 0x11, 0x90 };
        const uint8_t bad2[] = { 0x0F, 0xB6, 0x41, 0x12 };
        Check(Dgb::DecodeByteGetterOffset(ok) == 0x11, "decodes mov al,[ecx+11]; ret");
        Check(Dgb::DecodeByteGetterOffset(bad1) == 0, "rejects a missing ret");
        Check(Dgb::DecodeByteGetterOffset(bad2) == 0, "rejects another encoding");
    }

    void TestReusePredicate()
    {
        uint8_t dg[0x200] = {};
        dg[Dgb::kDgIdentityProjection] = 0;
        dg[Dgb::kDgIdentityView] = 1;
        const uint32_t cursor = 120, staging = 2;
        std::memcpy(dg + Dgb::kDgVertexCursor, &cursor, 4);
        std::memcpy(dg + Dgb::kDgStagingIndex, &staging, 4);

        Batch b = MakeBatch(50, 10.0f, 1, 0x1000, 4, 0, 1, 3);
        b.Set<uint32_t>(Dgb::kBatchVertexStart, 100u);
        b.Set<uint32_t>(Dgb::kBatchStagingIndex, staging);
        Check(Dgb::BatchMatchesBegin(b.bytes, dg, 0x1000, 4, 50, kLayout), "matching batch reusable");
        Check(!Dgb::BatchMatchesBegin(b.bytes, dg, 0x2000, 4, 50, kLayout), "material differs");
        Check(!Dgb::BatchMatchesBegin(b.bytes, dg, 0, 4, 50, kLayout), "null material");
        Check(!Dgb::BatchMatchesBegin(b.bytes, dg, 0x1000, 5, 50, kLayout), "operation differs");
        Check(!Dgb::BatchMatchesBegin(b.bytes, dg, 0x1000, 4, 51, kLayout), "queue group differs");

        Batch c = b;
        c.bytes[Dgb::kBatchMergeable] = 0;
        Check(!Dgb::BatchMatchesBegin(c.bytes, dg, 0x1000, 4, 50, kLayout), "occlusion batch not reusable");
        c = b;
        c.bytes[kLayout.identityView] = 0;
        Check(!Dgb::BatchMatchesBegin(c.bytes, dg, 0x1000, 4, 50, kLayout), "identity view differs");
        c = b;
        c.bytes[kLayout.identityProjection] = 1;
        Check(!Dgb::BatchMatchesBegin(c.bytes, dg, 0x1000, 4, 50, kLayout), "identity projection differs");
        c = b;
        c.Set<uint32_t>(Dgb::kBatchVertexStart, cursor);
        Check(!Dgb::BatchMatchesBegin(c.bytes, dg, 0x1000, 4, 50, kLayout), "empty batch not reusable");
        c = b;
        c.Set<uint32_t>(Dgb::kBatchStagingIndex, staging + 1);
        Check(!Dgb::BatchMatchesBegin(c.bytes, dg, 0x1000, 4, 50, kLayout), "staging buffer switched");

        Check(Dgb::ReusableBeginDistance(0.0f), "zero distance reusable");
        Check(Dgb::ReusableBeginDistance(12.5f), "positive distance reusable");
        Check(!Dgb::ReusableBeginDistance(-1.0f), "negative distance falls back to stock");
        Check(!Dgb::ReusableBeginDistance(std::numeric_limits<float>::quiet_NaN()),
              "NaN distance falls back to stock");
    }

    void TestNameCache()
    {
        Dgb::NameCache cache;
        int ownerA = 0, ownerB = 0;
        Check(!cache.Matches(&ownerA, 0x10, "smoke", 5), "empty cache misses");
        cache.Store(&ownerA, 0x10, "smoke", 5);
        Check(cache.Matches(&ownerA, 0x10, "smoke", 5), "stored entry hits");
        Check(!cache.Matches(&ownerB, 0x10, "smoke", 5), "other DynamicGeometry misses");
        Check(!cache.Matches(&ownerA, 0x20, "smoke", 5), "current batch holds another material");
        Check(!cache.Matches(&ownerA, 0x10, "smokE", 5), "different name misses");
        Check(!cache.Matches(&ownerA, 0x10, "smoke2", 6), "longer name misses");
        cache.Clear();
        Check(!cache.Matches(&ownerA, 0x10, "smoke", 5), "cleared cache misses");
        char longName[100];
        std::memset(longName, 'x', sizeof(longName));
        cache.Store(&ownerA, 0x10, longName, 64);
        Check(!cache.Matches(&ownerA, 0x10, longName, 64), "over-long names are not cached");
        cache.Store(&ownerA, 0, "smoke", 5);
        Check(!cache.Matches(&ownerA, 0, "smoke", 5), "null material is not cached");
    }

    // ---- prepareForSubmit model -----------------------------------------
    struct Piece
    {
        Batch batch;
        float squaredDepth = 0.0f;
        std::vector<int> vertices;
    };

    struct Submitted
    {
        float headDepth;
        std::vector<int> vertices;
        bool operator==(const Submitted& o) const
        {
            return headDepth == o.headDepth && vertices == o.vertices;
        }
    };

    float StockKey(float sq, uint8_t group, uint8_t blended, uint32_t stride)
    {
        float key = std::log2(sq + 1.17549435e-38f) * 32.0f;
        if (group < 100)
            key = std::floor(key);
        if (blended && group < 100 && stride > 1)
            key = std::floor(key / static_cast<float>(stride)) * static_cast<float>(stride);
        return key;
    }

    bool SameMergeClass(const Batch& a, const Batch& b)
    {
        return a.bytes[Dgb::kBatchMergeable] && b.bytes[Dgb::kBatchMergeable] &&
               a.bytes[Dgb::kBatchQueueGroup] == b.bytes[Dgb::kBatchQueueGroup] &&
               Dgb::Read<uint32_t>(a.bytes, Dgb::kBatchMaterialRep) ==
                   Dgb::Read<uint32_t>(b.bytes, Dgb::kBatchMaterialRep) &&
               Dgb::Read<int32_t>(a.bytes, Dgb::kBatchOperation) ==
                   Dgb::Read<int32_t>(b.bytes, Dgb::kBatchOperation) &&
               a.bytes[kLayout.identityProjection] == b.bytes[kLayout.identityProjection] &&
               a.bytes[kLayout.identityView] == b.bytes[kLayout.identityView];
    }

    std::vector<Submitted> SortAndMerge(std::vector<Piece> pieces)
    {
        std::vector<Piece*> order;
        for (auto& p : pieces)
            order.push_back(&p);
        std::sort(order.begin(), order.end(), [](const Piece* a, const Piece* b) {
            return Less(a->batch, b->batch, true);
        });
        // Opaque runs are re-sorted without the depth key.
        for (size_t i = 0; i < order.size();)
        {
            if (order[i]->batch.bytes[Dgb::kBatchBlended])
            {
                ++i;
                continue;
            }
            size_t j = i;
            while (j < order.size() && !order[j]->batch.bytes[Dgb::kBatchBlended])
                ++j;
            std::sort(order.begin() + static_cast<std::ptrdiff_t>(i),
                      order.begin() + static_cast<std::ptrdiff_t>(j),
                      [](const Piece* a, const Piece* b) {
                          return Less(a->batch, b->batch, false);
                      });
            i = j;
        }
        std::vector<Submitted> out;
        const Piece* head = nullptr;
        for (const Piece* p : order)
        {
            if (p->vertices.empty())
                continue;
            if (head && SameMergeClass(head->batch, p->batch))
            {
                out.back().vertices.insert(
                    out.back().vertices.end(), p->vertices.begin(), p->vertices.end());
                continue;
            }
            head = p;
            out.push_back({ p->squaredDepth, p->vertices });
        }
        return out;
    }

    uint32_t g_Rng = 12345u;
    uint32_t Next()
    {
        g_Rng = g_Rng * 1664525u + 1013904223u;
        return g_Rng >> 8;
    }

    void TestReuseMatchesStockSortAndMerge()
    {
        int mismatches = 0;
        size_t stockPieces = 0, reusePieces = 0;
        for (int trial = 0; trial < 400; ++trial)
        {
            std::vector<Piece> stock, reuse;
            uint8_t dg[0x200] = {};
            uint32_t cursor = 0;
            int nextVertex = 0;
            const int begins = 20 + static_cast<int>(Next() % 200);
            const uint32_t stride = (trial % 2) ? 8u : 1u;
            float baseDepth = 50.0f + static_cast<float>(Next() % 5000);
            for (int i = 0; i < begins; ++i)
            {
                const uint32_t material = 0x1000u + (Next() % 3u) * 0x100u;
                const uint8_t blended = material == 0x1200u ? 1 : 0;
                const int32_t op = (Next() % 8u) == 0 ? 3 : 4;
                const uint8_t group = (Next() % 10u) == 0 ? 105 : 50;
                // Emitters walk particles roughly in depth order.
                baseDepth += static_cast<float>(static_cast<int>(Next() % 200u) - 100) * 0.05f;
                const float dist = std::max(1.0f, baseDepth);
                const float sq = dist * dist;
                const int count = static_cast<int>(Next() % 5u); // 0 = empty piece
                const float key = StockKey(sq, group, blended, stride);

                Batch b = MakeBatch(group, key, blended, material, op, 0, 0, 0);
                b.Set<uint32_t>(Dgb::kBatchVertexStart, cursor);

                // Stock: a new piece whenever the exact squared depth differs.
                if (stock.empty() || stock.back().squaredDepth != sq ||
                    !SameMergeClass(stock.back().batch, b))
                {
                    Piece p;
                    p.batch = b;
                    p.batch.Set<uint32_t>(Dgb::kBatchCreationIndex,
                                          static_cast<uint32_t>(stock.size()));
                    p.squaredDepth = sq;
                    stock.push_back(p);
                }

                // Reuse: the hook's predicate plus an equal depth key.
                bool absorbed = false;
                if (!reuse.empty())
                {
                    std::memcpy(dg + Dgb::kDgVertexCursor, &cursor, 4);
                    const Batch& cur = reuse.back().batch;
                    absorbed = reuse.back().squaredDepth == sq ||
                               (Dgb::BatchMatchesBegin(cur.bytes, dg, material, op, group, kLayout) &&
                                Dgb::Read<float>(cur.bytes, Dgb::kBatchDepthKey) == key);
                    absorbed = absorbed && SameMergeClass(cur, b);
                }
                if (!absorbed)
                {
                    Piece p;
                    p.batch = b;
                    p.batch.Set<uint32_t>(Dgb::kBatchCreationIndex,
                                          static_cast<uint32_t>(reuse.size()));
                    p.squaredDepth = sq;
                    reuse.push_back(p);
                }

                for (int v = 0; v < count; ++v)
                {
                    stock.back().vertices.push_back(nextVertex);
                    reuse.back().vertices.push_back(nextVertex);
                    ++nextVertex;
                    ++cursor;
                }
            }
            stockPieces += stock.size();
            reusePieces += reuse.size();
            if (!(SortAndMerge(stock) == SortAndMerge(reuse)))
                ++mismatches;
        }
        std::printf("model: %zu stock pieces -> %zu with reuse\n", stockPieces, reusePieces);
        Check(mismatches == 0, "reuse submits the same batches as stock");
        Check(reusePieces < stockPieces, "reuse removes pieces in the model");
    }
}

int main()
{
    TestComparatorOrder();
    TestDecodeGetter();
    TestReusePredicate();
    TestNameCache();
    TestReuseMatchesStockSortAndMerge();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("dynamic_geometry_batching_tests passed\n");
    return OpenShimTest::ExitCode();
}
