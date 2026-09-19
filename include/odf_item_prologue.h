#pragma once

// odf_item_prologue.h
// BZR Open Shim - how many prologue bytes the ODF item-hook trampolines must
// relocate.
//
// A 5-byte JMP detour overwrites the first five bytes of the target, so the
// trampoline has to replay those bytes and then jump back. The bytes it
// replays must be WHOLE INSTRUCTIONS. All three engine item thunks start:
//
//     55        push ebp
//     8B EC     mov  ebp, esp
//     8B 45 08  mov  eax, [ebp+8]     <-- three bytes, ending at offset 6
//     50        push eax              <-- offset 6
//
// Five bytes lands in the middle of `mov eax,[ebp+8]`, one byte short of its
// displacement. Relocating five therefore produces a trampoline reading
// `55 8B EC 8B 45 E9 ...`, where the JMP opcode that was meant to return
// control is consumed as that instruction's displacement byte instead - so the
// trampoline never jumps back and execution runs off into the relative offset.
// The first six bytes are the smallest whole-instruction cover.
//
// This is kept as a pure function so the boundary rule is covered by
// tests/odf_item_prologue_tests.cpp on any host, with no engine present.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
namespace OdfPrologue
{

// Bytes the generic JMP5 writer overwrites at the site.
inline constexpr std::size_t kDetourSize = 5;

// The exact prologue all three item thunks are required to still hold.
inline constexpr std::uint8_t kExpectedPrologue[6] = {
    0x55,             // push ebp
    0x8B, 0xEC,       // mov  ebp, esp
    0x8B, 0x45, 0x08, // mov  eax, [ebp+8]
};
inline constexpr std::size_t kExpectedPrologueSize = sizeof(kExpectedPrologue);

// Returns the number of leading bytes a trampoline must relocate so that it
// ends on an instruction boundary at or after kDetourSize, or 0 when the
// bytes are not a prologue this hook recognises.
//
// Deliberately an exact match against one known shape rather than a length
// disassembler: these three sites are pinned by signature to one build, and a
// hook that silently relocates an unrecognised prologue is the failure this
// function exists to prevent.
inline std::size_t TrampolineCopyLength(const std::uint8_t* prologue, std::size_t available)
{
    if (prologue == nullptr || available < kExpectedPrologueSize)
    {
        return 0;
    }
    for (std::size_t i = 0; i < kExpectedPrologueSize; ++i)
    {
        if (prologue[i] != kExpectedPrologue[i])
        {
            return 0;
        }
    }

    static_assert(kExpectedPrologueSize >= kDetourSize,
                  "the relocated span must cover everything the detour overwrites");
    return kExpectedPrologueSize;
}

} // namespace OdfPrologue
} // namespace BZROpenShim
