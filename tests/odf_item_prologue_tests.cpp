// Regression tests for the ODF item-hook trampoline boundary.
//
// The bug these pin down shipped and broke the game outright: the trampoline
// relocated five prologue bytes because the detour is five bytes wide. But the
// fifth byte lands inside `mov eax,[ebp+8]`:
//
//     55        push ebp
//     8B EC     mov  ebp, esp
//     8B 45 08  mov  eax, [ebp+8]
//     50        push eax
//
// so the relocated copy read `55 8B EC 8B 45 E9 xx xx xx xx` - the 0xE9 that
// was meant to be the return JMP became the displacement of a truncated `mov`,
// and control never came back. Every engine item read went through that
// trampoline, so `spritea.st` and `bzfont.st` failed to load, the game dropped
// to a UI screen, and no mission would start. Nothing in the log said so: all
// three hooks reported a unique signature match and a successful 5-byte write.
//
// The rule is that a trampoline relocates WHOLE INSTRUCTIONS covering at least
// the detour width. Here that is six bytes, not five.

#include "odf_item_prologue.h"

#include <cstdio>
#include <cstdlib>

namespace
{
using namespace BZROpenShim::OdfPrologue;

int g_failures = 0;

void Require(bool condition, const char* message)
{
    if (!condition)
    {
        std::fprintf(stderr, "odf_item_prologue_tests: %s\n", message);
        ++g_failures;
    }
}

void RequireEqual(std::size_t actual, std::size_t expected, const char* message)
{
    if (actual != expected)
    {
        std::fprintf(stderr, "odf_item_prologue_tests: %s (expected %zu, got %zu)\n", message,
                     expected, actual);
        ++g_failures;
    }
}

// Exactly the bytes at 0x00481AF0 / 0x00481A60 / 0x00481990 in the GOG build.
const std::uint8_t kRealSite[] = {
    0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0x50, 0x6A, 0x00, 0xE8, 0x12, 0x00, 0x00, 0x00,
};

void TestRelocatesSixNotFive()
{
    const std::size_t n = TrampolineCopyLength(kRealSite, sizeof(kRealSite));
    RequireEqual(n, 6, "the real site must relocate six bytes");
    Require(n != 5, "relocating five bytes is the shipped bug, not an acceptable answer");
    Require(n >= kDetourSize, "the relocated span must cover the whole detour");
}

// The property that actually matters: the byte after the relocated span must
// be the start of a real instruction (0x50, push eax), never a displacement.
void TestResumePointIsAnInstructionBoundary()
{
    const std::size_t n = TrampolineCopyLength(kRealSite, sizeof(kRealSite));
    Require(n < sizeof(kRealSite), "resume point is inside the sample");
    RequireEqual(kRealSite[n], 0x50, "execution must resume on `push eax`");
    // And the five-byte answer must NOT be a boundary - this is what made the
    // original trampoline swallow its own jump.
    RequireEqual(kRealSite[5], 0x08, "byte 5 is the displacement of mov eax,[ebp+8]");
}

void TestRejectsUnknownPrologues()
{
    const std::uint8_t wrongOpcode[] = {0x53, 0x8B, 0xEC, 0x8B, 0x45, 0x08};
    Require(TrampolineCopyLength(wrongOpcode, sizeof(wrongOpcode)) == 0,
            "a different first opcode is refused");

    // A plausible near-miss: same shape but a different displacement, i.e. a
    // function reading a different argument slot.
    const std::uint8_t wrongDisp[] = {0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x0C};
    Require(TrampolineCopyLength(wrongDisp, sizeof(wrongDisp)) == 0,
            "a different displacement is refused rather than relocated blindly");

    const std::uint8_t truncated[] = {0x55, 0x8B, 0xEC, 0x8B, 0x45};
    Require(TrampolineCopyLength(truncated, sizeof(truncated)) == 0,
            "fewer bytes than the prologue needs is refused");

    Require(TrampolineCopyLength(nullptr, 16) == 0, "a null pointer is refused");
    Require(TrampolineCopyLength(kRealSite, 0) == 0, "a zero-length buffer is refused");
}

// Build the trampoline image the way BuildTrampoline does and assert the jump
// opcode survives - the direct expression of the shipped failure.
void TestTrampolineImageKeepsItsJump()
{
    const std::size_t n = TrampolineCopyLength(kRealSite, sizeof(kRealSite));
    std::uint8_t tramp[16] = {};
    for (std::size_t i = 0; i < n; ++i)
    {
        tramp[i] = kRealSite[i];
    }
    tramp[n] = 0xE9;

    RequireEqual(tramp[n], 0xE9, "the return jump opcode is present");
    // With the old five-byte relocation the JMP would have landed at index 5,
    // which is the `mov`'s displacement slot.
    Require(n != 5, "the jump must not occupy a displacement slot");
    RequireEqual(tramp[3], 0x8B, "mov opcode intact");
    RequireEqual(tramp[4], 0x45, "modrm intact");
    RequireEqual(tramp[5], 0x08, "displacement intact - this is the byte the old code lost");
}
}

int main()
{
    TestRelocatesSixNotFive();
    TestResumePointIsAnInstructionBoundary();
    TestRejectsUnknownPrologues();
    TestTrampolineImageKeepsItsJump();

    if (g_failures != 0)
    {
        std::fprintf(stderr, "odf_item_prologue_tests: %d failure(s)\n", g_failures);
        return EXIT_FAILURE;
    }
    std::puts("odf_item_prologue_tests: all checks passed");
    return EXIT_SUCCESS;
}
