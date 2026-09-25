// x86_length_tests.cpp
// Host-side checks for the x86-32 length decoder behind InstallInlineDetour32.
//
// The site prologues below are the bytes read from GOG 2.2.301 at the nine
// MPAUTH detour targets and the two Under Attack Alert blocks; the decoder was
// also diffed against capstone over every instruction in that build's .text
// section (10 mismatches, all the undocumented SALC opcode it refuses on
// purpose). These tests pin the encodings the shim actually steals plus the
// refusal cases, so a regression shows up here instead of as a torn trampoline.
#include "x86_length.h"

#include <cstdint>
#include <cstdio>
#include <initializer_list>
#include <vector>

using namespace BZROpenShim;

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what)
    {
        if (condition) return;
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++g_Failures;
    }

    void ExpectLength(std::initializer_list<uint8_t> bytes, size_t expected, const char* what)
    {
        const std::vector<uint8_t> code(bytes);
        const size_t got = X86InstructionLength32(code.data(), code.size());
        if (got == expected) return;
        std::fprintf(stderr, "FAIL: %s: expected length %zu, got %zu\n", what, expected, got);
        ++g_Failures;
    }

    X86StealPlan Plan(const std::vector<uint8_t>& code, size_t patchLen)
    {
        return PlanDetourSteal32(code.data(), code.size(), patchLen);
    }

    // push ebp; mov ebp,esp; sub esp,imm8 (six of the nine MPAUTH sites).
    const std::vector<uint8_t> kSubImm8Prologue =
        { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x4C, 0xA1, 0x00, 0x70, 0x8E, 0x00, 0x33, 0xC5, 0x89, 0x45, 0xFC };
    // push ebp; mov ebp,esp; sub esp,imm32 (Ordnance_Receive, SprayBomb::Hit, ordinary reader).
    const std::vector<uint8_t> kSubImm32Prologue =
        { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x50, 0x01, 0x00, 0x00, 0xA1, 0x00, 0x70, 0x8E, 0x00, 0x33, 0xC5 };
    // Under Attack Alert Hook 1/2: the full 52-byte block the JMP5 replaces.
    const std::vector<uint8_t> kUnderAttackBlock =
        { 0x0F, 0x2F, 0x05, 0xD0, 0x73, 0x91, 0x00, 0x76, 0x2B, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00,
          0x68, 0x20, 0x72, 0x87, 0x00, 0xE8, 0xE2, 0x5C, 0xFA, 0xFF, 0x83, 0xC4, 0x10,
          0xF3, 0x0F, 0x10, 0x85, 0x48, 0xFE, 0xFF, 0xFF, 0xF3, 0x0F, 0x58, 0x05, 0x04, 0x26, 0x8A, 0x00,
          0xF3, 0x0F, 0x11, 0x05, 0xD0, 0x73, 0x91, 0x00, 0x8B, 0x0D, 0xC0, 0x9F, 0x97, 0x00 };
}

int main()
{
    // --- single-instruction lengths ---
    ExpectLength({ 0x55 }, 1, "push ebp");
    ExpectLength({ 0x8B, 0xEC }, 2, "mov ebp,esp");
    ExpectLength({ 0x83, 0xEC, 0x4C }, 3, "sub esp,imm8");
    ExpectLength({ 0x81, 0xEC, 0x50, 0x01, 0x00, 0x00 }, 6, "sub esp,imm32");
    ExpectLength({ 0x81, 0xEC, 0x50, 0x01 }, 0, "sub esp,imm32 truncated");
    ExpectLength({ 0xA1, 0x00, 0x70, 0x8E, 0x00 }, 5, "mov eax,[moffs32]");
    ExpectLength({ 0x67, 0xA1, 0x00, 0x70 }, 4, "mov eax,[moffs16]");
    ExpectLength({ 0x33, 0xC5 }, 2, "xor eax,ebp");
    ExpectLength({ 0x89, 0x45, 0xFC }, 3, "mov [ebp-4],eax");
    ExpectLength({ 0x8B, 0x04, 0x8D, 0x00, 0x00, 0x00, 0x00 }, 7, "mov eax,[ecx*4+disp32] (SIB no base)");
    ExpectLength({ 0x8B, 0x84, 0x24, 0xA0, 0x00, 0x00, 0x00 }, 7, "mov eax,[esp+disp32]");
    ExpectLength({ 0x8B, 0x0D, 0xC0, 0x9F, 0x97, 0x00 }, 6, "mov ecx,[disp32]");
    ExpectLength({ 0xC7, 0x45, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF }, 7, "mov dword [ebp-4],imm32");
    ExpectLength({ 0x66, 0xC7, 0x45, 0xFC, 0x00, 0x00 }, 6, "mov word [ebp-4],imm16");
    ExpectLength({ 0xC6, 0x00, 0x00 }, 3, "mov byte [eax],imm8");
    ExpectLength({ 0xF7, 0x45, 0xFC, 0x01, 0x00, 0x00, 0x00 }, 7, "test dword [ebp-4],imm32");
    ExpectLength({ 0xF7, 0x5D, 0xFC }, 3, "neg dword [ebp-4]");
    ExpectLength({ 0xF6, 0x45, 0xFC, 0x01 }, 4, "test byte [ebp-4],imm8");
    ExpectLength({ 0xF6, 0x5D, 0xFC }, 3, "neg byte [ebp-4]");
    ExpectLength({ 0x6A, 0x00 }, 2, "push imm8");
    ExpectLength({ 0x68, 0x20, 0x72, 0x87, 0x00 }, 5, "push imm32");
    ExpectLength({ 0x69, 0xC0, 0x10, 0x00, 0x00, 0x00 }, 6, "imul eax,eax,imm32");
    ExpectLength({ 0x6B, 0xC0, 0x10 }, 3, "imul eax,eax,imm8");
    ExpectLength({ 0xC2, 0x04, 0x00 }, 3, "ret imm16");
    ExpectLength({ 0xC3 }, 1, "ret");
    ExpectLength({ 0xC8, 0x00, 0x00, 0x00 }, 4, "enter");
    ExpectLength({ 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 7, "call far ptr16:32");
    ExpectLength({ 0xE8, 0xE2, 0x5C, 0xFA, 0xFF }, 5, "call rel32");
    ExpectLength({ 0xE9, 0x00, 0x00, 0x00, 0x00 }, 5, "jmp rel32");
    ExpectLength({ 0xEB, 0x10 }, 2, "jmp rel8");
    ExpectLength({ 0x76, 0x2B }, 2, "jbe rel8");
    ExpectLength({ 0xE3, 0x02 }, 2, "jecxz rel8");
    ExpectLength({ 0xFF, 0x15, 0x00, 0x00, 0x00, 0x00 }, 6, "call [disp32]");
    ExpectLength({ 0xFF, 0x24, 0x85, 0x00, 0x00, 0x00, 0x00 }, 7, "jmp [eax*4+disp32]");
    ExpectLength({ 0xFF, 0xD2 }, 2, "call edx");
    ExpectLength({ 0xD9, 0x45, 0x08 }, 3, "fld dword [ebp+8]");
    ExpectLength({ 0xDD, 0xD8 }, 2, "fstp st(0)");
    ExpectLength({ 0x0F, 0x2F, 0x05, 0xD0, 0x73, 0x91, 0x00 }, 7, "comiss xmm0,[disp32]");
    ExpectLength({ 0xF3, 0x0F, 0x10, 0x85, 0x48, 0xFE, 0xFF, 0xFF }, 8, "movss xmm0,[ebp-disp32]");
    ExpectLength({ 0xF3, 0x0F, 0x10, 0x84, 0x24, 0xA0, 0x00, 0x00, 0x00 }, 9, "movss xmm0,[esp+disp32]");
    ExpectLength({ 0x66, 0x0F, 0x6E, 0xC0 }, 4, "movd xmm0,eax");
    ExpectLength({ 0x0F, 0x84, 0x94, 0x00, 0x00, 0x00 }, 6, "je rel32");
    ExpectLength({ 0x0F, 0xB6, 0x48, 0x68 }, 4, "movzx ecx,byte [eax+0x68]");
    ExpectLength({ 0x0F, 0x94, 0xC0 }, 3, "sete al");
    ExpectLength({ 0x0F, 0x31 }, 2, "rdtsc");
    ExpectLength({ 0x0F, 0xC8 }, 2, "bswap eax");
    ExpectLength({ 0x0F, 0xBA, 0xE0, 0x05 }, 4, "bt eax,imm8");
    ExpectLength({ 0x0F, 0xA4, 0xC2, 0x08 }, 4, "shld edx,eax,imm8");
    ExpectLength({ 0x0F, 0xC2, 0xC1, 0x01 }, 4, "cmpps xmm0,xmm1,imm8");
    ExpectLength({ 0x66, 0x0F, 0x70, 0xC0, 0x1B }, 5, "pshufd xmm0,xmm0,imm8");
    ExpectLength({ 0x66, 0x0F, 0x73, 0xD8, 0x08 }, 5, "psrldq xmm0,imm8");
    ExpectLength({ 0x66, 0x0F, 0x38, 0x00, 0xC1 }, 5, "pshufb xmm0,xmm1");
    ExpectLength({ 0x66, 0x0F, 0x3A, 0x0B, 0xC1, 0x0B }, 6, "roundsd xmm0,xmm1,imm8");
    ExpectLength({ 0x0F, 0x1F, 0x44, 0x00, 0x00 }, 5, "nop [eax+eax]");
    ExpectLength({ 0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00 }, 7, "nop [eax+disp32]");
    ExpectLength({ 0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00 }, 9, "nop word [eax+eax+disp32]");
    ExpectLength({ 0xF0, 0x0F, 0xB1, 0x0A }, 4, "lock cmpxchg [edx],ecx");
    ExpectLength({ 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00 }, 6, "mov eax,fs:[0]");
    ExpectLength({ 0xF3, 0xA5 }, 2, "rep movsd");
    ExpectLength({ 0x66, 0xAB }, 2, "stosw");
    ExpectLength({ 0xD6 }, 0, "salc refused");
    ExpectLength({ 0xC5, 0xF8, 0x77 }, 0, "VEX vzeroupper refused");
    ExpectLength({ 0xC4, 0xE1, 0x78, 0x77 }, 0, "3-byte VEX refused");
    ExpectLength({ 0x0F, 0x0F, 0xC1, 0x9E }, 0, "3DNow! refused");
    ExpectLength({}, 0, "empty buffer");

    // --- steal plans over the recorded site bytes ---
    {
        const X86StealPlan five = Plan(kSubImm8Prologue, 5);
        Check(five.status == X86StealStatus::NotOnBoundary, "sub esp,imm8 prologue: 5-byte steal splits sub");
        Check(five.boundary == 6, "sub esp,imm8 prologue: next boundary is 6");

        const X86StealPlan six = Plan(kSubImm8Prologue, 6);
        Check(six.status == X86StealStatus::Ok, "sub esp,imm8 prologue: 6-byte steal ok");
        Check(six.instructionCount == 3 && six.boundary == 6 && six.rel32Count == 0,
              "sub esp,imm8 prologue: three instructions, no rel32");
    }
    {
        Check(Plan(kSubImm32Prologue, 5).status == X86StealStatus::NotOnBoundary,
              "sub esp,imm32 prologue: 5-byte steal splits sub");
        Check(Plan(kSubImm32Prologue, 6).status == X86StealStatus::NotOnBoundary,
              "sub esp,imm32 prologue: 6-byte steal splits sub");
        Check(Plan(kSubImm32Prologue, 6).boundary == 9, "sub esp,imm32 prologue: next boundary is 9");
        const X86StealPlan nine = Plan(kSubImm32Prologue, 9);
        Check(nine.status == X86StealStatus::Ok && nine.instructionCount == 3,
              "sub esp,imm32 prologue: 9-byte steal ok");
    }
    {
        // The Under Attack block has a jbe rel8 at +7, which is why that patch
        // replaces the whole 52-byte block with a JMP5 and never trampolines
        // through it. The decoder must refuse it as a steal.
        const X86StealPlan ua = Plan(kUnderAttackBlock, 52);
        Check(ua.status == X86StealStatus::ShortBranch, "under-attack block: rel8 refused");
        Check(ua.failOffset == 7, "under-attack block: refusal points at the jbe");
        Check(Plan(kUnderAttackBlock, 7).status == X86StealStatus::Ok, "under-attack block: comiss alone is stealable");
        // 0x34 is an instruction boundary, i.e. the JMP5 resume address is sound.
        size_t off = 0;
        while (off < 0x34)
        {
            const size_t len = X86InstructionLength32(kUnderAttackBlock.data() + off, kUnderAttackBlock.size() - off);
            if (len == 0) break;
            off += len;
        }
        Check(off == 0x34, "under-attack block: +0x34 is an instruction boundary");
    }
    {
        // Prologue that begins with a call: rel32 is allowed and located.
        const std::vector<uint8_t> callFirst = { 0xE8, 0x10, 0x00, 0x00, 0x00, 0x90, 0x90 };
        const X86StealPlan p = Plan(callFirst, 6);
        Check(p.status == X86StealStatus::Ok && p.rel32Count == 1 && p.rel32Offsets[0] == 1,
              "call rel32 + nop: relocatable, field at +1");

        const std::vector<uint8_t> jccFirst = { 0x0F, 0x84, 0x94, 0x00, 0x00, 0x00, 0x55 };
        const X86StealPlan q = Plan(jccFirst, 7);
        Check(q.status == X86StealStatus::Ok && q.rel32Count == 1 && q.rel32Offsets[0] == 2,
              "je rel32 + push: relocatable, field at +2");

        const std::vector<uint8_t> pushThenJmp = { 0x55, 0x8B, 0xEC, 0xE9, 0x00, 0x00, 0x00, 0x00 };
        const X86StealPlan r = Plan(pushThenJmp, 8);
        Check(r.status == X86StealStatus::Ok && r.rel32Count == 1 && r.rel32Offsets[0] == 4,
              "push; mov; jmp rel32: field at +4");
    }
    {
        Check(Plan({ 0x55, 0xEB, 0x10, 0x90, 0x90 }, 5).status == X86StealStatus::ShortBranch, "jmp rel8 refused");
        Check(Plan({ 0x55, 0x66, 0xE8, 0x00, 0x00, 0x90 }, 6).status == X86StealStatus::Rel16Branch, "call rel16 refused");
        Check(Plan({ 0x55, 0xD6, 0x90, 0x90, 0x90 }, 5).status == X86StealStatus::Undecodable, "salc in range refused");
        Check(Plan({ 0x55, 0xD6, 0x90, 0x90, 0x90 }, 5).failOffset == 1, "refusal offset is the bad instruction");
        Check(Plan({ 0x55, 0x8B, 0xEC }, 5).status == X86StealStatus::Undecodable, "patchLen beyond buffer refused");
        Check(Plan({ 0x55, 0x8B, 0xEC }, 0).status == X86StealStatus::Undecodable, "zero patchLen refused");
        Check(PlanDetourSteal32(nullptr, 0, 5).status == X86StealStatus::Undecodable, "null code refused");
        std::vector<uint8_t> calls;
        for (int i = 0; i < 5; ++i) { calls.push_back(0xE8); calls.insert(calls.end(), { 0, 0, 0, 0 }); }
        Check(Plan(calls, 25).status == X86StealStatus::TooManyRel32, "more than kMaxRel32 rel32 refused");
        Check(Plan(calls, 20).status == X86StealStatus::Ok, "exactly kMaxRel32 rel32 accepted");
    }
    Check(X86StealStatusName(X86StealStatus::NotOnBoundary)[0] == 'n', "status names are populated");

    if (g_Failures)
    {
        std::fprintf(stderr, "%d failure(s)\n", g_Failures);
        return 1;
    }
    std::printf("x86_length_tests: all checks passed\n");
    return 0;
}
