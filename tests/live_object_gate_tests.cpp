// live_object_gate_tests.cpp
//
// Pins the liveness decisions in include/live_object_gate.h.
//
// The regression this exists for: GPU skinning's frame scan took every
// GameObject arena slot with an exe-range vtable as live. A freed slot keeps
// GameObject::vftable and its freed OBJ76 pointer (only +0x15C is zeroed), so
// the scan read through freed OBJ76s and handed garbage such as 0xFFFF000C to
// the Entity code (openshim_crash.log, release 6609392ea, CCA1).

#include "live_object_gate.h"

#include <cstdint>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::LiveObjectGate;

namespace
{
    void ArenaSlots()
    {
        const std::uintptr_t base = 0x00400000u;
        Check(kGameObjectSequenceOffset == 0x15C,
              "sequence number offset is GetHandle 0x00462380's +0x15C");
        Check(IsArenaSlotLive(0x0088A000u, base, 7u), "live: exe vtable and a sequence number");
        Check(!IsArenaSlotLive(0x0088A000u, base, 0u),
              "freed: pool free 0x004DA010 zeroes +0x15C but leaves the vtable");
        Check(!IsArenaSlotLive(0u, base, 0u), "never used: an all-zero slot");
        Check(!IsArenaSlotLive(0x12345678u, base, 7u), "heap-looking vtable is not live");
        Check(!IsArenaSlotLive(base - 4u, base, 7u), "vtable below the module is not live");
        Check(!IsArenaSlotLive(base + kMainModuleVtableSpan, base, 7u), "vtable past the span is not live");
        Check(IsArenaSlotLive(base, base, 1u), "first byte of the module counts");
        Check(!IsArenaSlotLive(0x0088A000u, 0u, 7u), "unknown module base is not live");
    }

    void CandidatePointers()
    {
        Check(!IsCandidatePointer(0u), "null");
        Check(!IsCandidatePointer(0x0000FFFCu), "null guard region");
        Check(IsCandidatePointer(0x00010000u), "lowest user page");
        Check(IsCandidatePointer(0x379A5FA8u), "aligned user address");
        Check(!IsCandidatePointer(0x379A5FA9u), "misaligned");
        Check(IsCandidatePointer(0xFFFEFFFCu), "top of a large-address-aware WOW64 process");
        Check(!IsCandidatePointer(0xFFFF000Cu), "the value the scan handed to the RTTI probe");
        Check(!IsCandidatePointer(0x3F800000u + 1u), "misaligned float-like junk");
    }

    void EntityNames()
    {
        Check(!IsEntityNameShaped(0u, 15u), "empty name");
        Check(IsEntityNameShaped(12u, 15u), "short inline name");
        Check(IsEntityNameShaped(kMaxEntityNameLength, kMaxEntityNameLength), "longest accepted name");
        Check(!IsEntityNameShaped(kMaxEntityNameLength + 1u, 4096u), "too long");
        Check(!IsEntityNameShaped(20u, 15u), "size beyond capacity is not a string");
    }

    void EntityProbes()
    {
        EntityProbe live;
        live.nameRead = true;
        live.nameShaped = true;
        live.queryOk = true;
        live.hasEntity = true;
        live.sameObject = true;
        Check(IsEntityProvenLive(live), "registered and maps back to the same pointer");

        EntityProbe p = live;
        p.nameRead = false;
        Check(!IsEntityProvenLive(p), "name read faulted");
        p = live;
        p.nameShaped = false;
        Check(!IsEntityProvenLive(p), "name is not a plausible string");
        p = live;
        p.queryOk = false;
        Check(!IsEntityProvenLive(p), "scene query faulted or threw");
        p = live;
        p.hasEntity = false;
        Check(!IsEntityProvenLive(p), "destroyed: the scene no longer has the name");
        p = live;
        p.sameObject = false;
        Check(!IsEntityProvenLive(p), "the name now belongs to another Entity");
        Check(!IsEntityProvenLive(EntityProbe{}), "nothing observed");
    }

    void UnprovenRecords()
    {
        Check(KeepUnprovenRecord(1u), "one failed proof keeps the record");
        Check(KeepUnprovenRecord(kMaxUnprovenFrames - 1u), "below the limit keeps the record");
        Check(!KeepUnprovenRecord(kMaxUnprovenFrames), "the limit drops the record");
    }

    void BridgeRoots()
    {
        Check(BridgeRootAction(true, false, false) == RootAction::Read, "proven root is read every frame");
        Check(BridgeRootAction(true, true, true) == RootAction::Read, "proven root needs no new proof");
        Check(BridgeRootAction(false, true, false) == RootAction::Prove, "new root is proven at once");
        Check(BridgeRootAction(false, false, true) == RootAction::Prove, "unproven root is re-proven on a convert pass");
        Check(BridgeRootAction(false, false, false) == RootAction::Skip,
              "unproven root (0x450C6124, a float) is not read between convert passes");
    }

    void RttiWalk()
    {
        const std::uintptr_t base = 0x10000000u;
        const std::uintptr_t end = 0x10800000u;
        Check(IsVtableInModule(0x106C83B0u, base, end), "Entity vftable inside OgreMain");
        Check(!IsVtableInModule(0x004F2CE0u, base, end), "exe code read as an object is not an Entity");
        Check(!IsVtableInModule(0x8B55FF8Bu, base, end), "prologue bytes read as a vtable");
        Check(!IsVtableInModule(base, base, end), "vtable[-1] would sit before the image");
        Check(IsVtableInModule(base + 4u, base, end), "first slot that keeps vtable[-1] inside");
        Check(!IsVtableInModule(end, base, end), "one past the image");
        Check(!IsVtableInModule(0x106C83B1u, base, end), "misaligned");
        Check(!IsVtableInModule(0x106C83B0u, 0u, 0u), "OgreMain not loaded");
        Check(!IsRttiHopShaped(0x00EC8B55u), "unaligned code bytes are not a hop");
        Check(!IsRttiHopShaped(0u), "null hop");
        Check(IsRttiHopShaped(0x10712340u), "aligned image address is a hop");
        Check(IsRttiHopInModule(0x10712340u, 12u, base, end), "COL inside OgreMain");
        Check(!IsRttiHopInModule(0x20000000u, 12u, base, end), "COL outside OgreMain");
        Check(!IsRttiHopInModule(end - 8u, 12u, base, end), "col+12 would run past the image");
        Check(IsRttiHopInModule(end - 16u, 12u, base, end), "col+12 is the image's last dword");
        Check(!IsRttiHopInModule(0x10712341u, 8u, base, end), "misaligned descriptor");
    }
}

int main()
{
    ArenaSlots();
    CandidatePointers();
    EntityNames();
    EntityProbes();
    UnprovenRecords();
    BridgeRoots();
    RttiWalk();
    return OpenShimTest::ExitCode();
}
