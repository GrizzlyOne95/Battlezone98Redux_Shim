// dynamic_geometry_batching.h
// Pure helpers for the DynamicGeometry piece-reuse, material-cache and
// fast-sort hooks (src/patches/dynamic_geometry_hooks.cpp). They operate on
// raw DynamicGeometryBatch bytes so the unit tests exercise the exact code the
// hooks run. Offsets were measured on the GOG Redux executable; see
// reverse_engineering/dynamic_geometry_begin_sort_20261021.md.
#pragma once

#include <cstdint>
#include <cstring>

namespace DynamicGeometryBatching
{
    // DynamicGeometryBatch (0xB4 bytes; the occlusion-query batch is 0xBC).
    constexpr uint32_t kBatchCreationIndex = 0x2C; // uint32, list size() at begin
    constexpr uint32_t kBatchMergeable = 0x30;     // byte, 0 for occlusion batches
    constexpr uint32_t kBatchBlended = 0x31;       // byte, material classification
    constexpr uint32_t kBatchDepthKey = 0x34;      // float, sort key
    constexpr uint32_t kBatchMaterialRep = 0x3C;   // MaterialPtr, pRep first
    constexpr uint32_t kBatchVertexStart = 0x54;   // uint32
    constexpr uint32_t kBatchStagingIndex = 0x78;  // uint32
    constexpr uint32_t kBatchOperation = 0x94;     // int32 OperationType
    constexpr uint32_t kBatchQueueGroup = 0xAC;    // byte
    constexpr uint32_t kBatchSquaredDepth = 0xB0;  // float
    constexpr uint32_t kBatchSize = 0xB4;

    // DynamicGeometry.
    constexpr uint32_t kDgDefaultMaterial = 0x140;   // MaterialPtr
    constexpr uint32_t kDgIdentityProjection = 0x150; // byte
    constexpr uint32_t kDgIdentityView = 0x151;       // byte
    constexpr uint32_t kDgStagingIndex = 0x190;       // uint32
    constexpr uint32_t kDgCurrentBatch = 0x1C8;       // DynamicGeometryBatch*
    constexpr uint32_t kDgVertexCursor = 0x1D4;       // uint32
    constexpr uint32_t kDgGroupVirtualOffset = 0xB0;  // vtable byte offset

    // Ogre::Renderable bool fields, decoded at runtime from the exported
    // getters (mov al, [ecx+disp8]; ret).
    struct RenderableLayout
    {
        uint32_t identityProjection = 0;
        uint32_t identityView = 0;
    };

    template <typename T>
    inline T Read(const uint8_t* p, uint32_t offset)
    {
        T v;
        std::memcpy(&v, p + offset, sizeof(T));
        return v;
    }

    // Decodes "8A 41 xx C3" (mov al, byte ptr [ecx+xx]; ret). Returns 0 when
    // the bytes are anything else.
    inline uint32_t DecodeByteGetterOffset(const uint8_t* code)
    {
        if (code[0] == 0x8A && code[1] == 0x41 && code[3] == 0xC3)
            return code[2];
        return 0;
    }

    // Stock begin() clamps its distance with (0 < d || 0 == d) ? d : 0, so a
    // NaN or negative distance becomes 0. Only non-negative finite-or-inf
    // distances take the reuse path; anything else falls back to stock.
    inline bool ReusableBeginDistance(float dist)
    {
        return dist >= 0.0f;
    }

    // Everything stock begin() compares, except the exact squared depth, plus
    // the extra conditions that make an absorbed piece pixel-identical:
    //   - the current batch is mergeable (excludes occlusion-query batches);
    //   - it already holds vertices (empty batches are skipped by the merge,
    //     so the next piece would otherwise be the merged batch's head);
    //   - it still writes to the current staging buffer.
    // The caller additionally requires an equal depth key.
    inline bool BatchMatchesBegin(const uint8_t* batch,
                                  const uint8_t* dg,
                                  uint32_t materialRep,
                                  int32_t operation,
                                  uint8_t queueGroup,
                                  const RenderableLayout& layout)
    {
        return batch[kBatchMergeable] != 0 &&
               Read<int32_t>(batch, kBatchOperation) == operation &&
               Read<uint32_t>(batch, kBatchMaterialRep) == materialRep &&
               materialRep != 0 &&
               batch[layout.identityProjection] == dg[kDgIdentityProjection] &&
               batch[layout.identityView] == dg[kDgIdentityView] &&
               batch[kBatchQueueGroup] == queueGroup &&
               Read<uint32_t>(dg, kDgVertexCursor) !=
                   Read<uint32_t>(batch, kBatchVertexStart) &&
               Read<uint32_t>(dg, kDgStagingIndex) ==
                   Read<uint32_t>(batch, kBatchStagingIndex);
    }

    // Exact re-statement of the stock prepareForSubmit comparators.
    // withDepth=true is the main sort; false is the opaque-run re-sort, which
    // skips the depth key and blended steps. Float compares match comiss:
    // a NaN key compares as neither greater nor smaller.
    inline bool BatchLess(const uint8_t* a,
                          const uint8_t* b,
                          const RenderableLayout& layout,
                          bool withDepth)
    {
        if (!a)
            return b != nullptr;
        if (!b)
            return false;

        const uint8_t ga = a[kBatchQueueGroup];
        const uint8_t gb = b[kBatchQueueGroup];
        if (ga < gb)
            return true;
        if (ga > gb)
            return false;

        if (withDepth)
        {
            const float ka = Read<float>(a, kBatchDepthKey);
            const float kb = Read<float>(b, kBatchDepthKey);
            if (ka > kb)
                return true;
            if (kb > ka)
                return false;

            const uint8_t ba = a[kBatchBlended];
            const uint8_t bb = b[kBatchBlended];
            if (ba < bb)
                return true;
            if (ba > bb)
                return false;
        }

        const uint32_t ma = Read<uint32_t>(a, kBatchMaterialRep);
        const uint32_t mb = Read<uint32_t>(b, kBatchMaterialRep);
        if (ma < mb)
            return true;
        if (ma > mb)
            return false;

        const int32_t oa = Read<int32_t>(a, kBatchOperation);
        const int32_t ob = Read<int32_t>(b, kBatchOperation);
        if (oa < ob)
            return true;
        if (oa > ob)
            return false;

        const uint8_t pa = a[layout.identityProjection];
        const uint8_t pb = b[layout.identityProjection];
        if (pa < pb)
            return true;
        if (pa > pb)
            return false;

        const uint8_t va = a[layout.identityView];
        const uint8_t vb = b[layout.identityView];
        if (va < vb)
            return true;
        if (va > vb)
            return false;

        return Read<uint32_t>(a, kBatchCreationIndex) <
               Read<uint32_t>(b, kBatchCreationIndex);
    }

    // Single-entry name -> Material cache. An entry is only trusted while the
    // current batch still holds that exact Material (so the pointer is alive);
    // it is flushed every prepareForSubmit and whenever the owner changes.
    struct NameCache
    {
        static constexpr uint32_t kMaxName = 63;
        const void* owner = nullptr;
        uint32_t materialRep = 0;
        uint32_t length = 0;
        char name[kMaxName + 1] = {};

        void Clear()
        {
            owner = nullptr;
            materialRep = 0;
            length = 0;
        }

        bool Matches(const void* dg, uint32_t currentRep, const char* text, uint32_t size) const
        {
            return materialRep != 0 && owner == dg && currentRep == materialRep &&
                   size == length && std::memcmp(name, text, size) == 0;
        }

        void Store(const void* dg, uint32_t rep, const char* text, uint32_t size)
        {
            if (rep == 0 || size > kMaxName)
            {
                Clear();
                return;
            }
            owner = dg;
            materialRep = rep;
            length = size;
            std::memcpy(name, text, size);
            name[size] = '\0';
        }
    };
}
