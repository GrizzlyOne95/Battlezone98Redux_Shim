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

        // Bridge roots. The scan reads a root at OBJ76+0xF0 and at the owner's
        // +0xF0, then the Entity at root+0x94. On many object kinds those
        // slots hold floats (a stress run read 0x450C6124) or other data, and
        // a root that happened to sit in mapped memory used to keep a cached
        // "readable" verdict until its page was released and the read faulted.
        // A root is now read every frame only once it has been proven: its
        // +0x94 held an Ogre::Entity (readable, OgreMain vtable, Entity RTTI).
        // An unproven root is (re)proven with fresh page queries when it is
        // first seen and on convert passes, and skipped on other frames.
        enum class RootAction
        {
            Skip,   // unproven, not due a proof this frame: no read
            Prove,  // query pages, read +0x94, prove the Entity
            Read,   // proven: read +0x94 (SEH only, as before)
        };

        constexpr RootAction BridgeRootAction(bool proven, bool firstSeen, bool convertPass)
        {
            return proven ? RootAction::Read
                 : (firstSeen || convertPass) ? RootAction::Prove
                 : RootAction::Skip;
        }

        // An object whose RTTI may be walked without faulting: its vtable lies
        // in the module that defines the class (OgreMain.dll for an Entity),
        // aligned, with vtable[-1] inside that image too. An exe address read
        // out of a junk root (0x004F2CE0, a function prologue) fails here, so
        // its "vtable" -- code bytes -- is never dereferenced.
        constexpr bool IsVtableInModule(std::uintptr_t vtable, std::uintptr_t moduleBase, std::uintptr_t moduleEnd)
        {
            return moduleBase != 0 && moduleEnd > moduleBase && (vtable % 4u) == 0 &&
                   vtable >= moduleBase + 4u && vtable < moduleEnd;
        }

        // The MSVC RTTI walk: vtable -> CompleteObjectLocator (vtable[-1]) ->
        // TypeDescriptor (+12) -> name (+8). Each hop must at least look like a
        // pointer before it is followed.
        constexpr bool IsRttiHopShaped(std::uintptr_t pointer)
        {
            return IsCandidatePointer(pointer);
        }

        // A hop the walk reads at `pointer + readOffset` (4 bytes, or the name
        // start), required inside the module so the read cannot fault.
        constexpr bool IsRttiHopInModule(std::uintptr_t pointer, std::uintptr_t readOffset,
                                         std::uintptr_t moduleBase, std::uintptr_t moduleEnd)
        {
            return moduleBase != 0 && IsRttiHopShaped(pointer) && pointer >= moduleBase &&
                   pointer < moduleEnd && readOffset + 4u <= moduleEnd - pointer;
        }
    }
}
