// The frustum-cull / restored-bounds table: the one failure mode its design
// forbids is handing a mesh a box that belonged to a different mesh at the
// same address. Audit item P1-3 (Docs/CODE_AUDIT_20260925.md): the table was
// keyed by the raw Mesh* and never invalidated on unload, so a reused address
// kept the earlier mesh's asset box (the box every restored bound is derived
// from) and could restore a too-small one. These tests pin the two defences,
// forgetting on destruction and starting over on a changed identity, and the
// backward-shift deletion that keeps probe chains and headroom intact.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "remembered_mesh_bounds_table.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace
{
    using BZROpenShim::RememberedMeshBounds;
    using BZROpenShim::RememberedMeshBoundsTable;

    int g_failures = 0;

    void Require(bool condition, const char* message)
    {
        if (!condition)
        {
            std::fprintf(stderr, "remembered_mesh_bounds_table_tests: FAIL %s\n", message);
            ++g_failures;
        }
    }

    const void* Ptr(uintptr_t value)
    {
        return reinterpret_cast<const void*>(value);
    }

    bool BoxIs(const float* actual, const float* expected)
    {
        return std::memcmp(actual, expected, sizeof(float) * 3) == 0;
    }

    const float kBoxSmall[6] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
    const float kBoxTank[6] = { -3.16f, -0.06f, -3.74f, 3.16f, 2.76f, 2.96f };
    const float kBoxDoubled[6] = { -6.32f, -0.12f, -7.48f, 6.32f, 5.52f, 5.92f };

    void TestRememberAndFind()
    {
        RememberedMeshBoundsTable<1024> table;
        const void* mesh = Ptr(0x10010000u);
        Require(table.Find(mesh) == nullptr, "an unknown mesh is not found");
        RememberedMeshBounds* entry = table.Remember(mesh, kBoxTank, 0x1234u);
        Require(entry != nullptr && table.Find(mesh) == entry, "a remembered mesh is found");
        Require(entry->haveAsset && BoxIs(entry->assetMinimum, kBoxTank) &&
                    BoxIs(entry->assetMaximum, kBoxTank + 3),
                "the first finite box is the asset box");
        Require(table.Remember(mesh, kBoxDoubled, 0x1234u) == entry, "a later box updates in place");
        Require(BoxIs(entry->minimum, kBoxDoubled) && BoxIs(entry->maximum, kBoxDoubled + 3),
                "the working box follows the latest write");
        Require(BoxIs(entry->assetMinimum, kBoxTank), "the asset box keeps the first write");
        Require(table.Live() == 1, "one live entry");
        Require(table.Remember(nullptr, kBoxTank, 1u) == nullptr, "a null mesh is refused");
        Require(table.Remember(mesh, nullptr, 1u) == nullptr, "a null box is refused");
        Require(table.Find(nullptr) == nullptr && !table.Forget(nullptr), "null lookups are harmless");
    }

    void TestChangedIdentityStartsOver()
    {
        RememberedMeshBoundsTable<1024> table;
        const void* address = Ptr(0x10020000u);
        RememberedMeshBounds* first = table.Remember(address, kBoxSmall, 0xAAAAu);
        first->sawInfinite = true;
        first->restoreClassified = true;
        first->restoreExcluded = true;
        // The same address, now another mesh: its own first box must become
        // the asset box, and nothing decided about the old mesh may survive.
        RememberedMeshBounds* second = table.Remember(address, kBoxTank, 0xBBBBu);
        Require(second == first, "the slot is reused in place");
        Require(BoxIs(second->assetMinimum, kBoxTank) && BoxIs(second->assetMaximum, kBoxTank + 3),
                "a changed identity re-captures the asset box (the old, smaller one is gone)");
        Require(!second->sawInfinite && !second->restoreClassified && !second->restoreExcluded,
                "a changed identity clears the old verdicts");
        Require(second->identity == 0xBBBBu, "the new identity is recorded");
        Require(table.IdentityResets() == 1 && table.Live() == 1, "one reset, still one entry");
        // An unknown identity (0) never resets, and is filled in when it
        // becomes known.
        RememberedMeshBounds* third = table.Remember(address, kBoxDoubled, 0u);
        Require(third == second && BoxIs(third->assetMinimum, kBoxTank), "identity 0 keeps the record");
        RememberedMeshBoundsTable<1024> late;
        RememberedMeshBounds* unknown = late.Remember(address, kBoxSmall, 0u);
        Require(unknown->identity == 0, "an unknown identity stays 0");
        Require(late.Remember(address, kBoxSmall, 0xCCCCu)->identity == 0xCCCCu &&
                    late.IdentityResets() == 0,
                "a late identity is adopted without a reset");
    }

    void TestForgetThenReuse()
    {
        RememberedMeshBoundsTable<1024> table;
        const void* address = Ptr(0x10030000u);
        table.Remember(address, kBoxSmall, 0xAAAAu);
        Require(table.Forget(address), "a remembered mesh can be forgotten");
        Require(table.Find(address) == nullptr && table.Live() == 0 && table.Forgotten() == 1,
                "a forgotten mesh is gone");
        Require(!table.Forget(address), "forgetting twice reports nothing to forget");
        // The allocator hands the address to a new mesh with the same name
        // hash: the record still starts fresh, because destruction emptied it.
        RememberedMeshBounds* fresh = table.Remember(address, kBoxTank, 0xAAAAu);
        Require(fresh != nullptr && BoxIs(fresh->assetMinimum, kBoxTank) && !fresh->sawInfinite,
                "a reused address after destruction starts a fresh record");
    }

    // Addresses that all hash to the same slot of a 16-entry table, so the
    // probe cluster is real.
    std::vector<const void*> CollidingAddresses(uint32_t slot, size_t count)
    {
        std::vector<const void*> out;
        for (uintptr_t value = 0x20000000u; out.size() < count; value += 16u)
        {
            const void* candidate = Ptr(value);
            if (RememberedMeshBoundsTable<16>::SlotFor(candidate) == slot)
                out.push_back(candidate);
        }
        return out;
    }

    void CheckClusterSurvivesDeletion(uint32_t slot)
    {
        RememberedMeshBoundsTable<16> table;
        const std::vector<const void*> meshes = CollidingAddresses(slot, 5);
        for (size_t i = 0; i < meshes.size(); ++i)
        {
            const float box[6] = { static_cast<float>(i), 0.0f, 0.0f, static_cast<float>(i) + 1.0f, 1.0f, 1.0f };
            Require(table.Remember(meshes[i], box, 0u) != nullptr, "cluster member remembered");
        }
        Require(table.Live() == 5, "five colliding entries");

        Require(table.Forget(meshes[2]), "the middle of the cluster is forgotten");
        for (size_t i = 0; i < meshes.size(); ++i)
        {
            const RememberedMeshBounds* entry = table.Find(meshes[i]);
            if (i == 2)
            {
                Require(entry == nullptr, "the forgotten member is gone");
                continue;
            }
            Require(entry != nullptr && entry->minimum[0] == static_cast<float>(i),
                    "the others stay reachable with their own boxes after a middle deletion");
        }
        Require(table.Forget(meshes[0]), "the head of the cluster is forgotten");
        Require(table.Find(meshes[1]) != nullptr && table.Find(meshes[3]) != nullptr &&
                    table.Find(meshes[4]) != nullptr,
                "the others stay reachable after a head deletion");
        Require(table.Find(meshes[0]) == nullptr, "the head is gone");

        const std::vector<const void*> more = CollidingAddresses(slot, 7);
        const float box[6] = { 9.0f, 0.0f, 0.0f, 10.0f, 1.0f, 1.0f };
        Require(table.Remember(more[6], box, 0u) != nullptr && table.Find(more[6])->minimum[0] == 9.0f,
                "a new colliding entry lands after the deletions");
        Require(table.Live() == 4, "live count tracks the deletions");
    }

    void TestBackwardShiftKeepsClusters()
    {
        CheckClusterSurvivesDeletion(3);  // a cluster in the middle of the table
        CheckClusterSurvivesDeletion(15); // a cluster that wraps past the end
    }

    void TestHeadroomIsReclaimed()
    {
        RememberedMeshBoundsTable<16> table;
        std::vector<const void*> meshes;
        for (uintptr_t value = 0x30000000u; meshes.size() < 13; value += 16u)
            meshes.push_back(Ptr(value));
        for (size_t i = 0; i < 12; ++i)
            Require(table.Remember(meshes[i], kBoxTank, 0u) != nullptr, "entries up to the headroom are kept");
        Require(table.Live() == 12 && table.Dropped() == 0, "twelve live entries in a sixteen-slot table");
        Require(table.Remember(meshes[12], kBoxTank, 0u) == nullptr && table.Dropped() == 1,
                "a new mesh past the headroom is dropped");
        Require(table.Remember(meshes[0], kBoxDoubled, 0u) != nullptr,
                "a known mesh is still updated at the headroom");
        Require(table.Forget(meshes[5]), "one entry is forgotten");
        Require(table.Remember(meshes[12], kBoxTank, 0u) != nullptr,
                "forgetting frees real capacity (no tombstone is left behind)");
        Require(table.Live() == 12, "live count is back at the headroom");
        table.Clear();
        Require(table.Live() == 0 && table.Find(meshes[0]) == nullptr, "clear empties the table");
    }
}

int main()
{
    TestRememberAndFind();
    TestChangedIdentityStartsOver();
    TestForgetThenReuse();
    TestBackwardShiftKeepsClusters();
    TestHeadroomIsReclaimed();

    if (g_failures == 0)
        std::printf("remembered_mesh_bounds_table_tests: all checks passed\n");
    return g_failures == 0 ? 0 : 1;
}
