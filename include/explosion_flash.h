#pragma once

// Explosion screen flash: the single-frame fullscreen white strobe a nearby
// explosion paints, and the two call sites that produce it.
//
// Traced statically against the shipped GOG v2.2.301 executable
// (battlezone98redux.exe, ImageBase 0x00400000).
//
// ---------------------------------------------------------------------------
// The chain
// ---------------------------------------------------------------------------
//
// Two explosion routines (0x0047F330 and 0x004AD070) end their setup with the
// same block: when the explosion's size field is above 5.0, project its
// position into camera space and, if that succeeds, hand
//
//     flash = 3.0 * size / depth
//
// to ScreenFlash::AddFlash (0x0049B4C0) on the global ScreenFlash at
// 0x0097838C. Both sites are the byte-identical sequence
//
//     push ecx / movss [esp], xmm0 / mov ecx, 0x0097838C / call AddFlash
//
// at 0x0047F605 and 0x004AD2C2.
//
// ScreenFlash::Render (see include/sun_flash.h) clamps the pending amount at
// 1.0, draws ONE fullscreen white quad at up to 224/255 alpha over the world,
// the cockpit and the HUD, and zeroes the pending amount. Nothing carries over
// to the next frame, so any explosion closer than three times its own size
// produces a one-frame, near-opaque white frame: a strobe, not a glow. Several
// explosions in one frame simply add.
//
// ---------------------------------------------------------------------------
// The intervention
// ---------------------------------------------------------------------------
//
// The same REL32 operand rewrite the sun hook uses (sun_flash.cpp), applied to
// both explosion call sites. The thunk either tail-jumps to the stock routine
// (Stock), adds a capped amount itself (Soft), or drops the argument (Off).
// The sun call site, the colour-flash path, the explosion's sprites, particles
// and point light are all untouched.

#include <cmath>

namespace BZROpenShim::ExplosionFlash
{
    inline constexpr unsigned long kCallSiteCount = 2;
    // CALL rel32 opcodes: E8 B6 BE 01 00 and E8 F9 E1 FE FF.
    inline constexpr unsigned long kCallOpcodeAddrs[kCallSiteCount] = {
        0x0047F605ul,
        0x004AD2C2ul,
    };
    inline constexpr unsigned long kScreenFlashAddFlashAddr = 0x0049B4C0ul;
    inline constexpr unsigned long kScreenFlashInstanceAddr = 0x0097838Cul;
    // ScreenFlash::pending, the float AddFlash accumulates into.
    inline constexpr unsigned long kScreenFlashPendingOffset = 0x28ul;

    enum class Mode : unsigned char
    {
        Stock = 0,
        Soft = 1,
        Off = 2,
    };

    // Soft caps what explosions may leave pending in one frame. 0.25 renders
    // at 56/255 alpha: a visible flicker rather than a whiteout.
    inline constexpr float kSoftPendingCap = 0.25f;

    // What Soft leaves pending after one explosion adds `amount` on top of
    // `pending`. Explosions never push the total past the cap, but a larger
    // value already there (the sun, in stock mode) is never reduced.
    inline float SoftPendingAfter(float pending, float amount)
    {
        if (!std::isfinite(pending))
            pending = 0.0f;
        if (!(amount > 0.0f) || !std::isfinite(amount))
            return pending;
        if (pending >= kSoftPendingCap)
            return pending;
        const float sum = pending + amount;
        return sum > kSoftPendingCap ? kSoftPendingCap : sum;
    }

    // Accepts Stock / Soft / Off (case-insensitive) and the boolean spellings
    // 1 (Stock) and 0 (Off). Returns false for anything else.
    bool ParseMode(const char* text, Mode& out);

    // --- runtime surface (implemented in src/patches/explosion_flash.cpp) ---

    // Reads [Display] ExplosionFlash. Latched; safe to call more than once.
    void LoadConfig();
    // Drops the latch and re-reads; the thunk samples the mode on every call.
    void ReloadConfig();

    // Instruction-anchored check that the CALL at kCallOpcodeAddrs[site] is
    // still a CALL rel32 resolving to ScreenFlash::AddFlash.
    bool VerifyCallSite(unsigned long site, int maxAttempts, unsigned delayMs);
    void* ThunkAddress();
    void SetPatchInstalled(unsigned long site);
}
