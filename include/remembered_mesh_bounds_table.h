#pragma once

// remembered_mesh_bounds_table.h
// BZR Open Shim - the per-mesh box table behind the private frustum cull and
// the restored craft bounds (src/patches/ogre_entity_frustum_cull.inl).
//
// Keyed by the Ogre::Mesh address, fixed capacity, no allocation on any hot
// path. Two things this table must never do: hand a mesh a box that belonged
// to a different mesh that once lived at the same address, and fill up with
// entries for meshes that no longer exist. So the owner forgets an entry when
// its mesh is destroyed (a Mesh::~Mesh detour), a remember for an address
// whose recorded identity differs starts the entry over, and deletion is
// backward-shift rather than tombstones, so probe chains stay short and the
// headroom is never eaten by dead slots. Header-only and engine-free so the
// probing, the reset and the deletion are host-tested.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    struct RememberedMeshBounds
    {
        const void* mesh = nullptr;
        // Identity of the resource behind `mesh` (a hash of its name), or 0
        // when unknown. A remember with a different non-zero identity means
        // the address now belongs to another mesh.
        uint32_t identity = 0;
        // The most recent finite box the mesh was given. Redux rewrites this
        // on every spawn (see the asset box below), so it is a working value
        // and not a statement about the asset.
        float minimum[3] = {};
        float maximum[3] = {};
        // The *first* finite box the mesh was given, which is the one
        // MeshSerializerImpl::readBoundsInfo set straight out of M_MESH_BOUNDS.
        // Every restored-bounds policy is derived from this and never from the
        // working value, because Redux's own per-spawn scale(2,2,2) compounds.
        float assetMinimum[3] = {};
        float assetMaximum[3] = {};
        bool haveAsset = false;
        // Cached "is this mesh only ever a first-person view model" verdict,
        // so the name test runs once per mesh rather than once per _setBounds.
        bool restoreClassified = false;
        bool restoreExcluded = false;
        // Per-mesh trace budget. Without it a 16x16 terrain grid spends the
        // whole global budget before a single craft has spawned.
        uint8_t tracedFinite = 0;
        uint8_t tracedInfinite = 0;
        // Set the first time this mesh is handed an EXTENT_INFINITE box.
        // Nothing is repaired until that has happened, so meshes the defect
        // never touched keep bit-identical bounds.
        bool sawInfinite = false;
    };

    // Open-addressed, power-of-two, linear probe, three-quarters headroom so a
    // probe always terminates on an empty slot.
    template <uint32_t Capacity>
    class RememberedMeshBoundsTable
    {
        static_assert(Capacity >= 4 && (Capacity & (Capacity - 1)) == 0,
                      "the table's capacity must be a power of two");

    public:
        static constexpr uint32_t kCapacity = Capacity;
        static constexpr uint32_t kHeadroom = (Capacity * 3) / 4;

        const RememberedMeshBounds* Find(const void* mesh) const
        {
            uint32_t slot = 0;
            return Locate(mesh, slot) ? &entries_[slot] : nullptr;
        }

        RememberedMeshBounds* FindMutable(const void* mesh)
        {
            uint32_t slot = 0;
            return Locate(mesh, slot) ? &entries_[slot] : nullptr;
        }

        // Records a finite box (min[3], max[3]) for `mesh`. The first finite
        // box becomes the asset box; later ones only update the working box.
        // A non-zero `identity` that differs from the one on record means the
        // address was reused, and the entry starts over. Returns the entry,
        // or nullptr when the mesh is new and the table is at its headroom.
        RememberedMeshBounds* Remember(const void* mesh, const float* box, uint32_t identity)
        {
            if (mesh == nullptr || box == nullptr)
                return nullptr;
            uint32_t slot = 0;
            RememberedMeshBounds* entry = nullptr;
            if (Locate(mesh, slot))
            {
                entry = &entries_[slot];
                if (entry->identity != 0 && identity != 0 && entry->identity != identity)
                {
                    *entry = RememberedMeshBounds{};
                    entry->mesh = mesh;
                    ++identityResets_;
                }
            }
            else
            {
                if (live_ >= kHeadroom)
                {
                    ++dropped_;
                    return nullptr;
                }
                entry = &entries_[slot]; // Locate left `slot` at the empty end of the probe
                *entry = RememberedMeshBounds{};
                entry->mesh = mesh;
                ++live_;
            }
            if (identity != 0)
                entry->identity = identity;
            std::memcpy(entry->minimum, box, sizeof(float) * 3);
            std::memcpy(entry->maximum, box + 3, sizeof(float) * 3);
            if (!entry->haveAsset)
            {
                std::memcpy(entry->assetMinimum, box, sizeof(float) * 3);
                std::memcpy(entry->assetMaximum, box + 3, sizeof(float) * 3);
                entry->haveAsset = true;
            }
            return entry;
        }

        // Drops the entry for `mesh`; false when there was none. Later
        // members of the probe cluster are pulled back into the hole when
        // their ideal slot allows, so every remaining entry stays reachable
        // without a tombstone.
        bool Forget(const void* mesh)
        {
            uint32_t hole = 0;
            if (mesh == nullptr || !Locate(mesh, hole))
                return false;
            uint32_t next = (hole + 1) & (Capacity - 1);
            while (entries_[next].mesh != nullptr)
            {
                const uint32_t ideal = SlotFor(entries_[next].mesh);
                // The entry at `next` may fill `hole` unless its ideal slot
                // lies strictly after the hole and at or before `next`
                // (cyclically), in which case moving it would break its chain.
                const bool movable = (hole <= next) ? (ideal <= hole || ideal > next)
                                                    : (ideal <= hole && ideal > next);
                if (movable)
                {
                    entries_[hole] = entries_[next];
                    hole = next;
                }
                next = (next + 1) & (Capacity - 1);
            }
            entries_[hole] = RememberedMeshBounds{};
            --live_;
            ++forgotten_;
            return true;
        }

        void Clear()
        {
            for (RememberedMeshBounds& entry : entries_)
                entry = RememberedMeshBounds{};
            live_ = 0;
        }

        uint32_t Live() const { return live_; }
        uint64_t Dropped() const { return dropped_; }
        uint64_t Forgotten() const { return forgotten_; }
        uint64_t IdentityResets() const { return identityResets_; }

        static uint32_t SlotFor(const void* mesh)
        {
            // Mesh pointers are allocator-aligned, so the low bits carry no
            // entropy.
            uint32_t hash = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mesh) >> 4);
            hash *= 2654435761u;
            return hash & (Capacity - 1);
        }

    private:
        // Finds `mesh`; on a miss leaves `slot` at the empty slot that ended
        // the probe (the headroom guarantees one exists).
        bool Locate(const void* mesh, uint32_t& slot) const
        {
            slot = SlotFor(mesh);
            for (uint32_t probe = 0; probe < Capacity; ++probe)
            {
                const RememberedMeshBounds& candidate = entries_[slot];
                if (candidate.mesh == nullptr)
                    return false;
                if (candidate.mesh == mesh)
                    return true;
                slot = (slot + 1) & (Capacity - 1);
            }
            return false;
        }

        RememberedMeshBounds entries_[Capacity] = {};
        uint32_t live_ = 0;
        uint64_t dropped_ = 0;
        uint64_t forgotten_ = 0;
        uint64_t identityResets_ = 0;
    };
}
