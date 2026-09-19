// bzr_object_layout.h
//
// GameObject / Ordnance field offsets for exact GOG Redux 2.2.301
// (battlezone98redux.exe SHA-256 8d71f56c...3377413), kept here rather than
// only inside bzr_hooks.cpp so a host test can pin them.
//
// Every value below is derived from the shipped image, not from the advisory
// PDB, and each carries the address of the instruction that proves it. The
// reason this file exists at all is that kGameObjectOwnerHandleOffset was
// wrong by four bytes from 2026-09-13 to 2026-09-19: it had been taken from
// two inline stores that resemble SetOwner rather than from the engine's own
// accessor pair, and the resulting owner walk silently resolved nothing.
//
// Unless a comment says otherwise, offsets are COMPLETE-object relative. The
// GameObject interface subobject lives at complete+0x18, so a virtual such as
// GameObject::GetTeam (0x00462450, `mov eax,[ecx+0x15C]`) reads complete+0x174
// and is NOT directly comparable with the values here.
//
// THE REDUX SHIFT IS NOT A CONSTANT. Redux is often described as "BZ 1.5 plus
// 0xC", and that holds up to perceivedTeam, but past it the shift narrows to
// 0x8. Both defects this file exists to prevent came from applying the wrong
// one, or none at all. The 1.5 side is the PDB struct in
// reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/bsim/out/object_model/:
//
//     field            1.5     Redux   shift
//     teamNumber       0x168   0x174   +0xC
//     teamList         0x170   0x17C   +0xC
//     perceivedTeam    0x174   0x180   +0xC
//     ---- the shift narrows somewhere in 0x178..0x184 ----
//     isVisible        0x184   0x18C   +0x8
//     seen             0x188   0x190   +0x8
//     enemyShot        0x1E0   0x1E8   +0x8
//     who_shot_JR      0x1EC   0x1F4   +0x8
//     maxAmmo          0x20C   0x214   +0x8
//     targetHandle     0x214   0x21C   +0x8
//     hitch            0x218   0x220   +0x8
//     ownerHandle      0x21C   0x224   +0x8
//
// Note what that table makes obvious: 1.5's targetHandle offset (0x214) is
// Redux's maxAmmo. Carrying a 1.5 value across unshifted lands on a real,
// populated neighbour rather than on empty space, so it reads as plausible
// data forever. Derive Redux offsets from Redux, and use 1.5 to corroborate
// ordering and adjacency -- never as the source.

#pragma once

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace ObjectLayout
    {
        // --- GameObject, complete-object relative -------------------------

        // Save walker: "seqNo" .rdata 0x0087405C, xref 0x004DE211 `add ecx,0x15C`
        // on the interface subobject; GetTeam 0x00462450 reads the same field.
        inline constexpr std::size_t kGameObjectActualTeam = 0x174;

        // Save walker: "perceivedTeam" .rdata 0x00879E2C, xref 0x004DE7E0
        // `add ecx,0x180`. SetPerceivedTeam 0x004DB4F0 `mov [ecx+0x180],edx`;
        // GetPerceivedTeam 0x004625B0 `mov eax,[ecx+0x180]`, non-virtual.
        inline constexpr std::size_t kGameObjectPerceivedTeam = 0x180;

        // The obj76 back-pointer. GameObject's ctor stores it at 0x004DA14B,
        // and SprayBuilding::Simulate loads it at 0x005DAB62 to own its payload.
        inline constexpr std::size_t kGameObjectObj76 = 0xF4;

        // Target handle, from the engine's own accessor pair:
        //   GameObject::SetTarget 0x0049F450 -- 0x0049F479 `mov [eax+0x21C],ecx`
        //                                       (the handle, or 0 for a null target)
        //   GameObject::GetTarget 0x00462610 -- 0x0046261A `mov ecx,[eax+0x21C]`
        //                                       then GetObj 0x004DA060
        // Reached from Lua exactly as the owner pair is: name literals
        // .rdata 0x0087C4CC "SetTarget" / 0x0087C4D8 "GetTarget" are entries at
        // 0x00871D18 / 0x00871D20 -- the two slots immediately above SetOwner --
        // pointing at 0x005007A0 / 0x005007E0, which tail into the handle-level
        // pair 0x005C8950 / 0x005C8990.
        //
        // Complete-object relative and non-virtual, like the owner pair: the
        // call site at 0x005AA94E does `sub ecx,0x18` before calling GetTarget
        // and re-adds 0x18 to the result, and neither address appears anywhere
        // in .rdata (the virtual GetTeam 0x00462450 has 20+ vtable slots).
        //
        // CORRECTED 2026-09-19. bzr_hooks.cpp carried 0x214, which is the
        // BZ 1.5 offset for this field with the Redux shift never applied --
        // see the layout table below.
        inline constexpr std::size_t kGameObjectTargetHandle = 0x21C;

        // NOT a handle at all: obfuscated maxAmmo. GameObject::GetMaxAmmo
        // 0x0046D060 reads `[this+0x214]` and XORs it with 0x33333333 before
        // returning; SprayBuilding::Simulate performs the same unscramble
        // inline when it checks ammoCost. Reading this as targetHandle prints a
        // scrambled ammo count. Named so the mistake cannot recur silently.
        inline constexpr std::size_t kGameObjectMaxAmmoObfuscated = 0x214;
        inline constexpr std::uint32_t kGameObjectAmmoObfuscationKey = 0x33333333u;

        // NOT the owner. This is `hitch` -- BZ 1.5 names it that in the PDB
        // struct, typed _OBJ76*, sitting between targetHandle and ownerHandle
        // exactly as it does here. Tested for zero at 0x004A8229, lazily filled
        // with the object's OWN GetHandle at 0x004A8255 when the carrier slot
        // +0xFC is empty, and cleared at 0x004A828A when the carrier at +0xF8
        // is not class 'TUG ' (0x54554700). Named here so the four-byte
        // confusion that produced the 2026-09-13 defect cannot recur silently.
        inline constexpr std::size_t kGameObjectHitch = 0x220;

        // The owner handle, from the engine's own accessor pair:
        //   GameObject::SetOwner 0x0046FC40 -- 0x0046FC58 `mov [ecx+0x224],eax`
        //                                      0x0046FC63 `mov [edx+0x224],0`
        //   GameObject::GetOwner 0x004B0400 -- 0x004B040A `mov ecx,[eax+0x224]`
        // Reached from Lua: name literals .rdata 0x0087C4E4 "SetOwner" and
        // 0x0087C4F0 "GetOwner" are entries 0 and 1 of the binding table at
        // 0x00871D28 -> 0x00500820 / 0x00500860 -> 0x005C89D0 / 0x005C8A10.
        // Complete-object relative: the call site at 0x005AA91C does
        // `sub ecx,0x18` before calling GetOwner and re-adds 0x18 to the result.
        inline constexpr std::size_t kGameObjectOwnerHandle = 0x224;

        // --- Ordnance -----------------------------------------------------

        // Ordnance::Init 0x00585292 `mov [edx+0xD8],eax` where eax is the
        // owner obj76 argument ([ebp+0xC]); the paired handle is stored at
        // +0xDC, zeroed at 0x005852A4 when the owner argument is null.
        inline constexpr std::size_t kOrdnanceOwnerObj = 0xD8;
        inline constexpr std::size_t kOrdnanceOwnerHandle = 0xDC;

        // --- obj76 --------------------------------------------------------

        // The GameObject back-pointer SetDamageFlags uses to turn
        // damage.damager into the object it reveals; ctor store 0x004DA183.
        inline constexpr std::size_t kObj76GameObject = 0x8C;
    }
}
