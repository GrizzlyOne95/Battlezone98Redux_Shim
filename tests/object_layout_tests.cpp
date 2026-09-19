// object_layout_tests.cpp
//
// Pins the GameObject / Ordnance field offsets in include/bzr_object_layout.h.
//
// These are not arbitrary numbers that a future edit may freely retune. Each
// one names the instruction in exact GOG Redux 2.2.301 that proves it, and the
// failure text repeats that instruction so a red test tells the reader where to
// go and look rather than only that a literal moved.
//
// The regression this exists for: kGameObjectOwnerHandleOffset shipped as 0x220
// between 2026-09-13 and 2026-09-19. 0x220 is the tug/cargo claim handle, not
// the owner, so the owned-object reveal resolved an owner for nothing at all
// and the Splinter emitter link wrote a craft handle into a live engine field.
// bzr_hooks.cpp static_asserts its own copies against this header, so the pair
// of checks catches a drift on either side.

#include "bzr_object_layout.h"

#include <cstddef>
#include <cstdio>

using namespace BZROpenShim::ObjectLayout;

namespace
{
    int g_Failures = 0;

    void CheckOffset(const char* field, std::size_t actual, std::size_t expected,
                     const char* evidence)
    {
        if (actual == expected)
            return;
        std::fprintf(stderr,
                     "FAIL: %s is 0x%zX, expected 0x%zX\n      evidence: %s\n",
                     field, actual, expected, evidence);
        ++g_Failures;
    }

    void Check(bool condition, const char* what)
    {
        if (condition)
            return;
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_Failures;
    }
}

int main()
{
    CheckOffset("kGameObjectActualTeam", kGameObjectActualTeam, 0x174,
                "GetTeam 0x00462450 `mov eax,[ecx+0x15C]` on the +0x18 "
                "interface subobject; Save walker xref 0x004DE211");
    CheckOffset("kGameObjectPerceivedTeam", kGameObjectPerceivedTeam, 0x180,
                "SetPerceivedTeam 0x004DB4F0 `mov [ecx+0x180],edx`; "
                "Save walker \"perceivedTeam\" xref 0x004DE7E0 `add ecx,0x180`");
    CheckOffset("kGameObjectObj76", kGameObjectObj76, 0xF4,
                "GameObject ctor store 0x004DA14B; SprayBuilding::Simulate "
                "load 0x005DAB62");
    CheckOffset("kGameObjectTargetHandle", kGameObjectTargetHandle, 0x21C,
                "GameObject::SetTarget 0x0049F450 `mov [eax+0x21C],ecx` and "
                "GetTarget 0x00462610 `mov ecx,[eax+0x21C]`");
    CheckOffset("kGameObjectHitch", kGameObjectHitch, 0x220,
                "zero test 0x004A8229, self-handle fill 0x004A8255, "
                "'TUG ' clear 0x004A828A; BZ 1.5 PDB names it hitch");
    CheckOffset("kGameObjectMaxAmmoObfuscated", kGameObjectMaxAmmoObfuscated,
                0x214,
                "GameObject::GetMaxAmmo 0x0046D060 `mov eax,[eax+0x214]` then "
                "`xor eax,0x33333333`");
    CheckOffset("kGameObjectOwnerHandle", kGameObjectOwnerHandle, 0x224,
                "GameObject::SetOwner 0x0046FC40 `mov [ecx+0x224],eax` and "
                "GetOwner 0x004B0400 `mov ecx,[eax+0x224]`");
    CheckOffset("kOrdnanceOwnerObj", kOrdnanceOwnerObj, 0xD8,
                "Ordnance::Init 0x00585292 `mov [edx+0xD8],eax` from [ebp+0xC]");
    CheckOffset("kOrdnanceOwnerHandle", kOrdnanceOwnerHandle, 0xDC,
                "Ordnance::Init 0x005852A4 zeroes +0xDC for a null owner");
    CheckOffset("kObj76GameObject", kObj76GameObject, 0x8C,
                "GameObject ctor back-pointer store 0x004DA183");

    // The defects themselves, stated as invariants rather than as literals:
    // these are adjacent fields and confusing them is silent at runtime.
    // Both wrong values landed on a real, populated neighbour, which is why
    // each read as plausible data for months instead of crashing.
    //
    //   ownerHandle  was 0x220 -- hitch, an adjacent field that looked like it.
    //   targetHandle was 0x214 -- the BZ 1.5 offset, Redux shift never applied,
    //                             which in Redux is obfuscated maxAmmo.
    Check(kGameObjectOwnerHandle != kGameObjectHitch,
          "owner handle must not alias the hitch field");
    Check(kGameObjectOwnerHandle != kGameObjectTargetHandle,
          "owner handle must not alias the target handle");
    Check(kGameObjectOwnerHandle == kGameObjectHitch + 4,
          "owner handle sits one dword above hitch");
    Check(kGameObjectHitch == kGameObjectTargetHandle + 4,
          "hitch sits one dword above the target handle");
    Check(kGameObjectTargetHandle != kGameObjectMaxAmmoObfuscated,
          "target handle must not alias obfuscated maxAmmo (the 1.5 offset)");
    Check(kGameObjectTargetHandle == kGameObjectMaxAmmoObfuscated + 8,
          "target handle sits two dwords above maxAmmo");
    Check(kGameObjectAmmoObfuscationKey == 0x33333333u,
          "ammo obfuscation key is 0x33333333");

    // Perceived and actual team are distinct fields 0xC apart. Collapsing them
    // is what made the earlier attack-reveal helper a permanent no-op: it read
    // and wrote the same address and always concluded "already revealed".
    Check(kGameObjectPerceivedTeam == kGameObjectActualTeam + 0xC,
          "perceivedTeam sits 0xC above the actual team field");

    if (g_Failures == 0)
        std::printf("object_layout_tests: all checks passed\n");
    return g_Failures == 0 ? 0 : 1;
}
