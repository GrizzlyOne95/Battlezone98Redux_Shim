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

#pragma once

#include <cstddef>

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

        // Target handle. Resolver 0x00462610: `mov ecx,[eax+0x21C]` then
        // GetObj 0x004DA060.
        //
        // NOT yet reconciled with bzr_hooks.cpp, which carries
        // kGameObjectTargetHandleOffset = 0x214 marked UNVERIFIED and feeds it
        // to the satellite diagnostic's `target` column only. 0x21C is the
        // value the engine's own resolver reads, so that constant is very
        // probably four dwords low, but it belongs to a different feature and
        // is deliberately left alone here rather than changed in passing. There
        // is intentionally no static_assert tying the two together.
        inline constexpr std::size_t kGameObjectTargetHandle = 0x21C;

        // NOT the owner. Tug/cargo claim handle: tested for zero at 0x004A8229,
        // lazily filled with the object's OWN GetHandle at 0x004A8255 when the
        // carrier slot +0xFC is empty, and cleared at 0x004A828A when the
        // carrier at +0xF8 is not class 'TUG ' (0x54554700). Named here so the
        // four-byte confusion that produced the 2026-09-13 defect cannot recur
        // silently.
        inline constexpr std::size_t kGameObjectTugCargoClaim = 0x220;

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
