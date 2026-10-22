#pragma once

// Explosion whiteout and player damage flash: the two fullscreen ScreenFlash
// effects OpenShim lets a player cap or remove, and the call sites that
// produce them. The sun's contribution is handled separately (sun_flash.h).
//
// Traced statically against the shipped GOG v2.2.301 executable
// (battlezone98redux.exe, ImageBase 0x00400000).
//
// ---------------------------------------------------------------------------
// ScreenFlash (global instance 0x0097838C)
// ---------------------------------------------------------------------------
//
//   AddFlash      0x0049B4C0  __thiscall(float amount), ret 4
//                 pending [+0x28] += amount
//   AddColorFlash 0x0049B430  __thiscall(float amount, float decay,
//                             u8 r, u8 g, u8 b), ret 0x14
//                 colour [+0x2C] += amount; decay [+0x30]; rgb [+0x34..36]
//   Render        0x0049B520  draws one fullscreen quad over world, cockpit
//                 and HUD. pending is clamped at 1.0, scaled to 224/255 alpha
//                 and zeroed each frame. colour is clamped the same way but
//                 decays by colour * decay * dt per frame instead.
//
// ---------------------------------------------------------------------------
// Explosion whiteout (AddFlash)
// ---------------------------------------------------------------------------
//
// Two explosion routines (0x0047F330, 0x004AD070) hand 3 * size / depth to
// AddFlash when the explosion's size is above 5.0. Because pending lives one
// frame, any explosion closer than three times its own size paints a single
// near-opaque white frame: a strobe, not a glow. Call sites 0x0047F605 and
// 0x004AD2C2.
//
// ---------------------------------------------------------------------------
// Player damage flash (AddColorFlash)
// ---------------------------------------------------------------------------
//
// Three damage paths call AddColorFlash only when the damaged object is the
// user's craft (DAT_00917AFC), each with decay 5.0:
//
//   0x004AA6FB  in 0x004AA630, amount = damage * 0.002
//   0x004AB278  in 0x004AAEA0, amount = damage * 0.01, orange (FF 40 00)
//   0x005A0D57  in 0x005A0C90, amount = damage * 0.03, red (FF 00 00)
//
// The remaining callers -- Lua's colour fade (0x00506F72), a team-coloured
// event flash (0x0050BBE5) and two white event flashes (0x005E1D3A,
// 0x005E1E0A) -- are deliberate scripted or event effects and are not hooked.
//
// ---------------------------------------------------------------------------
// The intervention
// ---------------------------------------------------------------------------
//
// Every hooked site is the byte sequence
//     mov ecx, 0x0097838C / call rel32
// and each CALL operand is rewritten to a thunk, after an instruction-anchored
// check that the call resolves to the expected ScreenFlash method. Stock
// tail-jumps to the original; Soft reduces the amount; Off drops the call.

#include <cmath>

namespace BZROpenShim::ScreenFlash
{
    inline constexpr unsigned long kInstanceAddr = 0x0097838Cul;
    inline constexpr unsigned long kAddFlashAddr = 0x0049B4C0ul;
    inline constexpr unsigned long kAddColorFlashAddr = 0x0049B430ul;
    // ScreenFlash::pending, the float AddFlash accumulates into.
    inline constexpr unsigned long kPendingOffset = 0x28ul;

    enum class Mode : unsigned char
    {
        Stock = 0,
        Soft = 1,
        Off = 2,
    };

    enum class Effect : unsigned char
    {
        Explosion = 0,
        Damage = 1,
    };

    struct CallSite
    {
        const char* patchName;
        unsigned long opcodeAddr;
        unsigned long callee;
        Effect effect;
    };

    inline constexpr CallSite kCallSites[] = {
        { "Explosion Screen Flash Hook 1/2", 0x0047F605ul, kAddFlashAddr, Effect::Explosion },
        { "Explosion Screen Flash Hook 2/2", 0x004AD2C2ul, kAddFlashAddr, Effect::Explosion },
        { "Damage Screen Flash Hook 1/3", 0x004AA6FBul, kAddColorFlashAddr, Effect::Damage },
        { "Damage Screen Flash Hook 2/3", 0x004AB278ul, kAddColorFlashAddr, Effect::Damage },
        { "Damage Screen Flash Hook 3/3", 0x005A0D57ul, kAddColorFlashAddr, Effect::Damage },
    };
    inline constexpr unsigned long kCallSiteCount =
        static_cast<unsigned long>(sizeof(kCallSites) / sizeof(kCallSites[0]));

    // Soft caps what explosions may leave pending in one frame. 0.25 renders
    // at 56/255 alpha: a visible flicker rather than a whiteout.
    inline constexpr float kSoftExplosionPendingCap = 0.25f;
    // Soft scales each damage flash. The colour channel decays over a few
    // frames, so a scaled hit still reads as a hit without filling the screen.
    inline constexpr float kSoftDamageScale = 0.35f;

    // What Soft leaves pending after one explosion adds `amount` on top of
    // `pending`. Explosions never push the total past the cap, but a larger
    // value already there (the sun, in stock mode) is never reduced.
    inline float SoftPendingAfter(float pending, float amount)
    {
        if (!std::isfinite(pending))
            pending = 0.0f;
        if (!(amount > 0.0f) || !std::isfinite(amount))
            return pending;
        if (pending >= kSoftExplosionPendingCap)
            return pending;
        const float sum = pending + amount;
        return sum > kSoftExplosionPendingCap ? kSoftExplosionPendingCap : sum;
    }

    // Returns the index into kCallSites for a patches.json entry name, or -1.
    inline int CallSiteIndex(const char* patchName)
    {
        if (!patchName)
            return -1;
        for (unsigned long i = 0; i < kCallSiteCount; ++i)
        {
            const char* a = kCallSites[i].patchName;
            const char* b = patchName;
            while (*a && *a == *b)
            {
                ++a;
                ++b;
            }
            if (*a == '\0' && *b == '\0')
                return static_cast<int>(i);
        }
        return -1;
    }

    // --- runtime surface (implemented in src/patches/screen_flash.cpp) ---

    // Reads [Display] ExplosionFlash and [Display] DamageFlash
    // (Stock | Soft | Off; 1 = Stock, 0 = Off). Latched.
    void LoadConfig();
    // Drops the latch and re-reads; the thunks sample the mode on every call.
    void ReloadConfig();

    // Instruction-anchored check that kCallSites[site] is still
    // mov ecx, ScreenFlash / call <expected method>.
    bool VerifyCallSite(unsigned long site, int maxAttempts, unsigned delayMs);
    void* ThunkAddress(unsigned long site);
    void SetPatchInstalled(unsigned long site);
}
