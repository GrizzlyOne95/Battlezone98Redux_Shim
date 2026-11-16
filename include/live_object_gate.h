// live_object_gate.h
//
// SPDX-License-Identifier: MIT
//
// Pure liveness decisions for pointers the shim finds by walking engine memory
// rather than receiving from the engine: GameObject arena slots, and the
// Ogre::Entity a GPU skinning scan reads out of an object's bridge root.
//
// Arena slots. The GameObject pool (0x0260DB20, 0x1000 slots of 0x400) is
// never unmapped, and freeing a slot does not clear its vtable or its OBJ76
// pointer. GOG Redux 2.2.301:
//   - the deleting destructor (e.g. 0x0046D120) runs the destructor chain,
//     which passes through GameObject's (0x004DAB60) storing
//     GameObject::vftable -- an exe address -- and then hands the slot to the
//     pool free 0x004DA010;
//   - the pool free writes only the free-list link (+0x104) and zeroes the
//     sequence number (+0x15C). +0xF4 keeps the freed OBJ76;
//   - the constructor 0x004DA0B0 stores the OBJ76 at +0xF4 and the next
//     value of the global sequence counter at +0x15C;
//   - GameObject::GetHandle 0x00462380 returns 0 when +0x15C is 0, and
//     GetObj 0x004DA060 compares a handle's low 20 bits against it.
// So a vtable check alone accepts every slot that has ever held an object;
// a non-zero sequence number is what marks a slot as in use.
//
// Entities. A pointer read from engine memory is not proof that Ogre still
// owns the Entity there. It is trusted only when its name is readable within
// a bounded length and the live SceneManager maps that name back to the same
// pointer -- the check ordnance_entity_leak.cpp uses before it destroys one.
//
// Host-tested in tests/live_object_gate_tests.cpp.
#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace LiveObjectGate
    {
        // GameObject::GetHandle 0x00462380 `if (*(this+0x15C) == 0) return 0`.
        constexpr std::size_t kGameObjectSequenceOffset = 0x15C;
        // Span of the main module a live GameObject's primary vtable sits in
        // (observed around 0x0088xxxx; headlights.cpp IsLiveHeadlightObjectSlot).
        constexpr std::uintptr_t kMainModuleVtableSpan = 0x00600000;

        constexpr bool IsArenaSlotLive(std::uintptr_t vtable, std::uintptr_t mainBase, std::uint32_t sequence)
        {
            return mainBase != 0 && vtable >= mainBase && vtable < mainBase + kMainModuleVtableSpan &&
                   sequence != 0;
        }

        // A user-mode pointer an x86 process can hold: above the null guard
        // region, 4-byte aligned, and below 0xFFFF0000. A large-address-aware
        // process under WOW64 tops out at 0xFFFEFFFF; values above it (a scan
        // read 0xFFFF000C) are never addresses.
        constexpr bool IsCandidatePointer(std::uintptr_t address)
        {
            return address >= 0x00010000u && address < 0xFFFF0000u && (address % 4u) == 0;
        }

        // Ogre names stock entities with short generated strings; anything
        // longer than this is read as garbage, not as a name.
        constexpr std::size_t kMaxEntityNameLength = 256;

        constexpr bool IsEntityNameShaped(std::size_t length, std::size_t capacity)
        {
            return length > 0 && length <= kMaxEntityNameLength && capacity >= length;
        }

        struct EntityProbe
        {
            bool nameRead = false;      // the name was copied without faulting
            bool nameShaped = false;    // IsEntityNameShaped held for it
            bool queryOk = false;       // the SceneManager queries ran without faulting
            bool hasEntity = false;     // SceneManager::hasEntity(name)
            bool sameObject = false;    // SceneManager::getEntity(name) == the pointer
        };

        // Only an Entity the live scene maps back to itself may be read
        // through or written to. Every other outcome skips that entity.
        constexpr bool IsEntityProvenLive(const EntityProbe& probe)
        {
            return probe.nameRead && probe.nameShaped && probe.queryOk && probe.hasEntity && probe.sameObject;
        }

        // A converted Entity that fails the proof is skipped, never touched.
        // Its record survives this many consecutive failed frames before it is
        // dropped, so one transient false negative cannot strand a live Entity
        // on clone materials it no longer tracks. A destroyed one is dropped
        // after the same few frames without ever being read through.
        constexpr unsigned kMaxUnprovenFrames = 3;

        constexpr bool KeepUnprovenRecord(unsigned consecutiveFailures)
        {
            return consecutiveFailures < kMaxUnprovenFrames;
        }
    }
}
