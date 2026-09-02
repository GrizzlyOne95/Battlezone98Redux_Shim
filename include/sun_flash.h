#pragma once

// Sun "flashbang" whiteout: what it actually is, and the one call site that
// produces it.
//
// Traced statically against the shipped GOG v2.2.301 executable
// (battlezone98redux.exe, ImageBase 0x00400000). Every address and offset
// below was read out of that binary, not out of the advisory PDB.
//
// ---------------------------------------------------------------------------
// The chain
// ---------------------------------------------------------------------------
//
//   map .trn "SunTexture"
//        -> g_SunSpriteTexture (0x02CF4000), loaded at 0x006151C0
//
//   The sun DISC is drawn separately at 0x00615300 from that same handle.
//   Nothing below touches it.
//
//   LensFlare::Render (0x004F95D0), an Ogre::RenderQueueListener:
//     0x004F95E9  bail out unless g_SunSpriteTexture != 0
//     0x004F95F7  bail out when the mode enum at 0x008EAAD8 is 9 or 10,
//                 or when 0x02CECF74 != 0
//     0x004F9638  rotate the world sun direction (0x02CEB830, unit length)
//                 into camera space with the camera basis at camera+0x40
//     0x004F9660  t := the resulting Z component, i.e.
//                     t = dot(cameraForward, sunDirection)
//                 stored at [ebp-0x08]
//     0x004F967A  bail out unless t > camera+0x108 (the near threshold),
//                 so the sun has to be in front of you at all
//     ...         project the sun to screen space, reject it if it lands
//                 outside the viewport rect, then submit a small
//                 DynamicGeometry quad as a hardware occlusion query using
//                 the "QueryArea" / "QueryVisible" materials resolved in
//                 LensFlare::Init (0x004F9430)
//     0x004F9EED  if (this->visiblePixels [+0x48] == 0) do nothing
//     0x004F9EF7  t32 := t squared five times  ->  t^32   [ebp-0xE8]
//     0x004F9F7C  flash := (float)visiblePixels * t32 * this->scale [+0x4C]
//     0x004F9FD3  CALL ScreenFlash::AddFlash (0x0049B4C0) on the global
//                 ScreenFlash at 0x0097838C           <-- THE WHITEOUT
//     0x004F9FD8  ... and only then the ordinary six-sprite lens flare
//                 (ring_0.. from the table at 0x008E8690) is drawn along the
//                 sun-to-screen-centre line.
//
//   ScreenFlash::AddFlash (0x0049B4C0), __thiscall, ret 4:
//        this->pending [+0x28] += amount;
//
//   ScreenFlash::Render (0x0049B520, virtual, vtable slot at 0x00877798):
//        a := min(pending, 1.0) * 224;  pending = 0;
//        combined with the separate decaying coloured flash at +0x2C
//        (+0x30 decay rate, +0x34/35/36 RGB), then
//        0x0043FB00 draws ONE FULLSCREEN QUAD over the whole viewport rect.
//        With only the sun contributing, the colour term collapses to
//        0xFFFFFF -- pure white -- at up to 224/255 alpha.
//
// ---------------------------------------------------------------------------
// What this rules out
// ---------------------------------------------------------------------------
//
// The whiteout is NOT bloom, NOT the Glow compositor (BZ_ASSETS_CORE/common/
// programs/glow.compositor), NOT the sun sprite material, NOT additive
// blending of that sprite, NOT atmospheric scattering, and NOT anything in the
// terrain or BZBase shaders. It is a dedicated 2D fullscreen quad drawn by the
// engine's own ScreenFlash object. Turning down sun intensity in the enhanced
// shaders would not have touched it.
//
// ---------------------------------------------------------------------------
// Why it reads as a flashbang
// ---------------------------------------------------------------------------
//
// Two independent things:
//
//  1. t^32 is an extremely sharp angular window. cos(15 deg)^32 = 0.33,
//     cos(30 deg)^32 = 0.0097. The term is essentially zero until the sun is
//     within roughly 20 degrees of the view axis, then slams to 1.
//
//  2. The other factor is the RAW VISIBLE PIXEL COUNT of the occlusion query,
//     not a fraction of the query area. That is a number in the thousands, and
//     ScreenFlash::Render only clamps the product at 1.0. So for any pose
//     where the sun is anywhere near centre-screen and not almost entirely
//     hidden, the product is far above 1 and the quad renders at its 224/255
//     ceiling. Partial occlusion scales a value that is already saturated,
//     which is why putting a mountain edge across the sun barely dims it --
//     occlusion IS respected, it just cannot be seen until the sun is nearly
//     gone.
//
// The suppression therefore targets exactly one thing: the sun's contribution
// to ScreenFlash. The disc, the six flare sprites, the sky, the directional
// light, PSSM and the Glow compositor are all downstream of nothing we touch.
//
// ---------------------------------------------------------------------------
// The intervention
// ---------------------------------------------------------------------------
//
// One REL32 rewrite of the operand at 0x004F9FD4 so the CALL at 0x004F9FD3
// lands on SunFlashAddThunk instead of ScreenFlash::AddFlash. The thunk either
// tail-jumps to the stock routine (bit-identical stock behaviour) or consumes
// the callee-cleaned argument and returns.
//
// The other two callers of ScreenFlash::AddFlash -- 0x0047F605 and 0x004AD2C2,
// both explosion flashes -- are untouched by construction, because the patch
// is at the sun call site and not in the shared callee.

#include <cmath>

namespace BZROpenShim::SunFlash
{
    // Call instruction: E8 E8 14 FA FF at 0x004F9FD3.
    inline constexpr unsigned long kAddFlashCallOpcodeAddr = 0x004F9FD3ul;
    // The rel32 operand the patch rewrites.
    inline constexpr unsigned long kAddFlashCallOperandAddr = 0x004F9FD4ul;
    // ScreenFlash::AddFlash, the stock callee the operand currently selects.
    inline constexpr unsigned long kScreenFlashAddFlashAddr = 0x0049B4C0ul;
    // The global ScreenFlash instance the call site loads into ECX.
    inline constexpr unsigned long kScreenFlashInstanceAddr = 0x0097838Cul;

    // Frame offsets inside LensFlare::Render. The thunk is entered before any
    // prologue of ours runs, so EBP still addresses that frame and the
    // diagnostic can read the inputs that produced the value it was handed.
    inline constexpr long kFrameOffsetDot = -0x08;          // t
    inline constexpr long kFrameOffsetDotPow32 = -0xE8;     // t^32
    inline constexpr long kFrameOffsetLensFlareThis = -0xF4;
    inline constexpr long kLensFlareVisiblePixels = 0x48;
    inline constexpr long kLensFlareScale = 0x4C;

    // ScreenFlash::Render's ceiling: the pending term is clamped at 1.0 and
    // scaled by 224, so 224/255 is the most opaque white the quad can be.
    inline constexpr int kScreenFlashMaxAlpha = 224;

    // What ScreenFlash::Render would put on screen for a given pending value.
    // Pure, so tests/sun_flash_tests.cpp can pin the saturation claim above
    // without a running game.
    inline int WhiteoutAlpha(float pending)
    {
        if (!(pending > 0.0f) || !std::isfinite(pending))
            return 0;
        if (pending > 1.0f)
            return kScreenFlashMaxAlpha;
        return static_cast<int>(pending * static_cast<float>(kScreenFlashMaxAlpha));
    }

    // The engine's angular term, for documenting and testing the window.
    inline float AngularTerm(float dotCameraForwardSun)
    {
        float t = dotCameraForwardSun;
        for (int i = 0; i < 5; ++i)
            t *= t;
        return t;
    }

    // The whole product the call site passes to ScreenFlash::AddFlash.
    inline float FlashAmount(float dotCameraForwardSun, int visiblePixels, float scale)
    {
        return static_cast<float>(visiblePixels) * AngularTerm(dotCameraForwardSun) * scale;
    }

    // --- runtime surface (implemented in src/patches/sun_flash.cpp) ---
    // Declarations only, so tests/sun_flash_tests.cpp can include this header
    // on a host without Windows or the shim.

    // Reads [Display] SunFlashbang / DisableSunFlashbang and
    // [Diagnostics] TraceSunFlash. Latched; safe to call more than once.
    void LoadConfig();
    // Drops the latch and re-reads. g_SunFlashSuppress is sampled by the thunk
    // on every flash, so a settings-page write takes effect on the next frame.
    void ReloadConfig();
    bool IsSuppressionEnabled();
    bool IsTraceEnabled();

    // Instruction-anchored check that the CALL at kAddFlashCallOpcodeAddr is
    // still a CALL rel32 resolving to ScreenFlash::AddFlash. Must return true
    // before the REL32 payload is built; it also captures the stock callee the
    // thunk tail-jumps to. SteamStub decrypts .text in stages, so a Steam
    // install needs the same settle window the other rel32 hooks use; on GOG
    // one attempt is enough.
    bool VerifyCallSite(int maxAttempts, unsigned delayMs);
    void* ThunkAddress();

    void SetPatchInstalled(bool installed);
    bool IsPatchInstalled();

    // What the arm actually did. A suppressed count of zero after a session
    // spent looking at the sun means the arm never engaged, not that
    // suppression made no difference.
    long SuppressedCallCount();
    long PassedThroughCallCount();
}
