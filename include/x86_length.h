#pragma once
// x86-32 instruction length decoder for inline-detour steals.
//
// InstallInlineDetour32 copies the first `patchLen` bytes of a function into
// a trampoline and resumes at target+patchLen. That is only sound when the
// copied range ends on an instruction boundary and every copied instruction
// still means the same thing at the trampoline address. This decoder is the
// check: it knows enough of the 32-bit legacy encoding (prefixes, ModRM/SIB,
// immediates, the 0F/0F38/0F3A maps) to measure every instruction MSVC emits
// into the Redux executable, and it reports 0 for anything it does not
// recognise so the caller fails closed instead of guessing.
//
// No <Windows.h>: the Linux host lane compiles and tests this file.
#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    // Length in bytes of the instruction starting at code[0], or 0 when the
    // bytes are not a complete, recognised x86-32 instruction within `size`.
    size_t X86InstructionLength32(const uint8_t* code, size_t size);

    enum class X86StealStatus : uint8_t
    {
        Ok,
        Undecodable,     // an instruction in the range was not recognised
        NotOnBoundary,   // patchLen falls inside an instruction
        ShortBranch,     // rel8 jump/loop in the range (cannot be relocated)
        Rel16Branch,     // 66-prefixed rel16 call/jmp/jcc (cannot be relocated)
        TooManyRel32,    // more rel32 branches than the plan can record
    };

    struct X86StealPlan
    {
        static constexpr size_t kMaxRel32 = 4;

        X86StealStatus status = X86StealStatus::Undecodable;
        size_t boundary = 0;          // end of the last decoded instruction
        size_t instructionCount = 0;
        size_t failOffset = 0;        // where decoding stopped on failure
        size_t rel32Count = 0;
        size_t rel32Offsets[kMaxRel32] = {};  // offsets of each rel32 field
    };

    // Walks the instructions in code[0..patchLen) and reports whether they can
    // be copied verbatim to a trampoline. rel32 call/jmp/jcc are allowed and
    // their displacement offsets are returned so the copier can re-base them.
    X86StealPlan PlanDetourSteal32(const uint8_t* code, size_t size, size_t patchLen);

    const char* X86StealStatusName(X86StealStatus status);
}
